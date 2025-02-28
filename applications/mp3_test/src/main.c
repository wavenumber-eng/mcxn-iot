/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include "mp3_files.h"

LOG_MODULE_REGISTER(main);



// ANSI color codes
#define ANSI_RESET   "\x1B[0m"
#define ANSI_RED     "\x1B[31m"
#define ANSI_GREEN   "\x1B[32m"
#define ANSI_YELLOW  "\x1B[33m"
#define ANSI_BLUE    "\x1B[34m"
#define ANSI_CYAN    "\x1B[36m"

// Macro function for colored printk
#define PRINTK_COLOR(color, fmt, ...) printk(color fmt ANSI_RESET, ##__VA_ARGS__)

// Specific color macros
#define PRINTK_RED(fmt, ...)    PRINTK_COLOR(ANSI_RED, fmt, ##__VA_ARGS__)
#define PRINTK_GREEN(fmt, ...)  PRINTK_COLOR(ANSI_GREEN, fmt, ##__VA_ARGS__)
#define PRINTK_YELLOW(fmt, ...) PRINTK_COLOR(ANSI_YELLOW, fmt, ##__VA_ARGS__)
#define PRINTK_BLUE(fmt, ...)   PRINTK_COLOR(ANSI_BLUE, fmt, ##__VA_ARGS__)
#define PRINTK_CYAN(fmt, ...)   PRINTK_COLOR(ANSI_CYAN, fmt, ##__VA_ARGS__)





#define CONFIG__MP3_MAX_SAMPLES_PER_FRAME 1024
#define CONFIG__MP3_FILE_SIZE 1024

// MiniMP3 configurations
#define MINIMP3_IMPLEMENTATION
#define MINIMP3_ONLY_MP3
#define MINIMP3_NO_SIMD
#include "minimp3.h"

mp3dec_t mp3d;
mp3dec_frame_info_t info;
int16_t pcm[CONFIG__MP3_MAX_SAMPLES_PER_FRAME];
uint8_t mp3_chunk[CONFIG__MP3_FILE_SIZE];


uint32_t frame_samples;

float frames_per_second;

uint32_t get_mp3_chunk(uint8_t * src, uint32_t src_len, uint8_t *dest, uint32_t chunk_size, uint32_t offset);
void mp3_file_decode(char* file_name, uint8_t * src_mp3, uint32_t mp3_len);

int main(void)
{
	printk("---------------------------------\r\n");
	printk("MP3 decode test using %s\r\n", CONFIG_BOARD);
	printk("---------------------------------\r\n\n\n");


	mp3_file_decode("Celebration_mp3", Celebration_mp3, Celebration_mp3_size);
	mp3_file_decode("Countdown_mp3", Countdown_mp3, Countdown_mp3_size);
	mp3_file_decode("firefly_mp3", firefly_mp3, firefly_mp3_size);

	while (1) 
	{
		k_sleep(K_MSEC(10));
	}

	return 0;
}

void mp3_file_decode(char* file_name, uint8_t * src_mp3, uint32_t mp3_len)
{	
	uint64_t elapsed_time;
	uint32_t offset = 0;
	uint32_t accumulated_samples = 0;
	uint32_t chunk_size;

	mp3dec_init(&mp3d);

	PRINTK_GREEN("MP3 file %s size: %dB\r\n", file_name, mp3_len);

	elapsed_time = k_uptime_get();
	do
	{	
		chunk_size = get_mp3_chunk(src_mp3, mp3_len, mp3_chunk, CONFIG__MP3_FILE_SIZE, offset);
		accumulated_samples += mp3dec_decode_frame(&mp3d, mp3_chunk, chunk_size, pcm, &info);
		offset += info.frame_bytes;

	} while (info.frame_bytes != 0);
	elapsed_time = k_uptime_delta(&elapsed_time);

	frames_per_second = (float)accumulated_samples / (float)elapsed_time * 1000.0f;
	printk("Elapsed time to decode %d PCM samples: %lldms\r\n", accumulated_samples, elapsed_time);
	printk("Decoded PCM samples per second: %.2f\r\n\n", frames_per_second);
}



uint32_t get_mp3_chunk(uint8_t * src, uint32_t src_len, uint8_t *dest, uint32_t chunk_size, uint32_t offset)
{
	uint32_t int_size;

	int_size = (offset + chunk_size > src_len)? (src_len - offset) : chunk_size;
	memcpy(dest, &src[offset], int_size);
	return int_size;
}
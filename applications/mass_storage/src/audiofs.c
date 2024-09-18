#include "audiofs.h"
#include <zephyr/fs/fs.h>
#include <stdio.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


#define CONFIG__SAMPLE_FREQUENCY 16000
#define CONFIG__SAMPLE_BIT_WIDTH 16
#define CONFIG__BYTES_PER_SAMPLE sizeof(int16_t)
#define CONFIG__NUMBER_OF_CHANNELS 1
#define CONFIG__SAMPLES_PER_BLOCK 1600                                    // 100ms time per block
#define BLOCK_SIZE (CONFIG__BYTES_PER_SAMPLE * CONFIG__SAMPLES_PER_BLOCK) // 3200 bytes, 1600 samples of 2 bytes
#define CONFIG__TIMEOUT 250 //block duration

#define WAV_HEADER_SIZE 44


LOG_MODULE_REGISTER(audiofs);
K_MEM_SLAB_DEFINE_STATIC(i2s_mem_slab, BLOCK_SIZE, 2, 4); // Memory slabs for I2S_TX queue, 2 blocks of 3200 bytes

// Audio variables
const struct device *const i2s_dev_tx = DEVICE_DT_GET(DT_NODELABEL(i2s_rxtx));
struct i2s_config i2s_configurations;

static struct gpio_dt_spec amp1_sd_pin = GPIO_DT_SPEC_GET(DT_ALIAS(amp1_sd), gpios);
#ifdef CONFIG_BOARD_PLAYTEST_NODE__NRF52840_B
static struct gpio_dt_spec amp2_sd_pin = GPIO_DT_SPEC_GET(DT_ALIAS(amp2_sd), gpios);
#endif

uint8_t data_block[BLOCK_SIZE]; // Audio buffer
int16_t audio_block[CONFIG__SAMPLES_PER_BLOCK]; // Audio buffer ptr


#define CONFIG__SOUND_TH_STACK_SIZE (500 * 10)	//could be tunned
#define CONFIG__SOUND_TH_PRIORITY 5
void sound_thread_task(void *, void *, void *);
K_THREAD_DEFINE(sound_thread, CONFIG__SOUND_TH_STACK_SIZE,
                sound_thread_task, NULL, NULL, NULL,
                CONFIG__SOUND_TH_PRIORITY, 0, 0);


// FS variables
struct fs_mount_t fs_mnt;


void audiofs__i2s_init()
{
	int ret;

    gpio_pin_configure_dt(&amp1_sd_pin, GPIO_OUTPUT);
    //audio__amp_state(1, 1);

#ifdef CONFIG_BOARD_PLAYTEST_NODE__NRF52840_B
    gpio_pin_configure_dt(&amp2_sd_pin, GPIO_OUTPUT);
    //audio__amp_state(2, 0);
#endif

    i2s_configurations.word_size = CONFIG__SAMPLE_BIT_WIDTH;
    i2s_configurations.channels = CONFIG__NUMBER_OF_CHANNELS;
    i2s_configurations.format = I2S_FMT_DATA_FORMAT_I2S;
    i2s_configurations.options = I2S_OPT_BIT_CLK_MASTER | I2S_OPT_FRAME_CLK_MASTER;
    i2s_configurations.frame_clk_freq = CONFIG__SAMPLE_FREQUENCY;
    i2s_configurations.mem_slab = &i2s_mem_slab;
    i2s_configurations.block_size = BLOCK_SIZE;
    i2s_configurations.timeout = CONFIG__TIMEOUT;

    ret = i2s_configure(i2s_dev_tx, I2S_DIR_TX, &i2s_configurations);
    if (ret < 0)
    {
        LOG_ERR("Audio not ready \n");
    }

    LOG_INF("I2S ready\n");
}



void audiofs__read_available_files()
{
	struct fs_mount_t *mp = &fs_mnt;
	struct fs_dir_t dir;
	int rc;

	fs_dir_t_init(&dir);
	rc = fs_opendir(&dir, mp->mnt_point);
	
	printk("%s opendir: %d\n", mp->mnt_point, rc);

	if (rc < 0)
	{
		LOG_ERR("Failed to open directory");
	}


	LOG_INF("Type \tSize \tName");

	while (rc >= 0)
	{
		struct fs_dirent ent = {0};

		rc = fs_readdir(&dir, &ent);
		if (ent.name[0] == 0)
		{
			break;
		}
		LOG_INF("%c \t%u \t%s", (ent.type == FS_DIR_ENTRY_FILE) ? 'F' : 'D', ent.size, ent.name);
	}

	(void)fs_closedir(&dir);
}


uint8_t file_path[50];

void audiofs__play_file(char *file_name)
{

	// absolute path to the file
	sprintf(file_path, "/NAND:/%s", file_name);
	k_thread_resume(sound_thread);

}


void apply_block_volume(int16_t *block, uint32_t block_size, uint32_t volume) 
{
	for(uint32_t i = 0; i < block_size; i++)
	{
		block[i] = ((int32_t)block[i] * (int32_t)volume) >> 8;
    	//return ((int32_t)sample * (int32_t)actual_audio.volume) >> 8; // 8 bit volume control
	}
}


/*
    _  _   _ ___ ___ ___  ___ ___   _____ _  _ ___ ___   _   ___  
   /_\| | | |   \_ _/ _ \| __/ __| |_   _| || | _ \ __| /_\ |   \ 
  / _ \ |_| | |) | | (_) | _|\__ \   | | | __ |   / _| / _ \| |) |
 /_/ \_\___/|___/___\___/|_| |___/   |_| |_||_|_|_\___/_/ \_\___/ 

*/                                                                  

void sound_thread_task(void *, void *, void *)
{
	struct fs_file_t audio_file;
	uint32_t read_bytes;
	sub_chunk_data_t metadata_chunk;
	
    while (1){

		k_thread_suspend(sound_thread);


		fs_file_t_init(&audio_file);

		if (fs_open(&audio_file, file_path, FS_O_READ) < 0)
		{
			LOG_ERR("Failed to open %s\n", file_path);
			return;
		}

		// /////////////////////////////////////////////////////////////////
		// Read .wav file header and metadata
		read_bytes = fs_read(&audio_file, data_block, WAV_HEADER_SIZE);
		memcpy(&metadata_chunk, &data_block[36], sizeof(sub_chunk_data_t));	// Read chunk info

		// Iterate until find the data chunk	
		while(memcmp(metadata_chunk.id, "data", 4))
		{
			read_bytes = fs_read(&audio_file, data_block, metadata_chunk.size);		// Read chunk data
			read_bytes = fs_read(&audio_file, data_block, sizeof(sub_chunk_data_t));	// Read chunk info
			memcpy(&metadata_chunk, data_block, sizeof(sub_chunk_data_t));
		}


		// First block filled with zeros
		memset(audio_block, 0, BLOCK_SIZE);
		i2s_write_block(i2s_dev_tx, audio_block);
		if (!i2s_trigger_cmd(i2s_dev_tx, I2S_TRIGGER_START)){
			return;
		}

		// Read samples from the file and play them
		while(read_bytes > 0)
		{	
			apply_block_volume(audio_block, BLOCK_SIZE, 0xff);
			i2s_write_block(i2s_dev_tx, audio_block);
			read_bytes = fs_read(&audio_file, audio_block, BLOCK_SIZE);
		}

		if (!i2s_trigger_cmd(i2s_dev_tx, I2S_TRIGGER_STOP)){    // Wait the end of transmision and stop audio streaming
			return;
		}

		fs_close(&audio_file);	

       

    }
}


/*
  ___ ___ ___   ___ _   _ _  _  ___ _____ ___ ___  _  _ ___ 
 |_ _|_  ) __| | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | | / /\__ \ | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
 |___/___|___/ |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/
                                                            
*/

bool i2s_trigger_cmd(const struct device *i2s_dev_tx, enum i2s_trigger_cmd cmd)
{
    int ret;

    ret = i2s_trigger(i2s_dev_tx, I2S_DIR_TX, cmd);
    if (ret < 0)
    {
        LOG_ERR("Failed to trigger command %d on TX: %d\n", cmd, ret);
        return false;
    }

    return true;
}


bool i2s_write_block(const struct device *i2s_dev_tx, int16_t *sound_block)
{
    int ret = 1;

    //Waiting for the I2S state to come out of the stopping state 
    while(ret != 0){
        ret = i2s_buf_write(i2s_dev_tx, sound_block, BLOCK_SIZE);
    }

    return true;
}
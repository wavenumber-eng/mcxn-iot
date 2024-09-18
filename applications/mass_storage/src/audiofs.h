#ifndef AUDIOFS_H_
#define AUDIOFS_H_

#include <inttypes.h>
#include <stdbool.h>
#include <zephyr/drivers/i2s.h>


typedef struct 
{
    char id [4];
    uint32_t size;
} sub_chunk_data_t;


extern struct fs_mount_t fs_mnt;

extern void audiofs__i2s_init();
extern void audiofs__read_available_files();
extern void audiofs__read_header_basic_info(char * file_name);
extern void audiofs__read_n_samples(char *file_name, uint32_t n);

extern void audiofs__play_file(char *file_name);


bool i2s_trigger_cmd(const struct device *i2s_dev_tx, enum i2s_trigger_cmd cmd);
bool i2s_write_block(const struct device *i2s_dev_tx, int16_t* sound_block);

#endif
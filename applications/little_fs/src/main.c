/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/sd/sdmmc.h>
#include <zephyr/device.h>
#include <zephyr/drivers/disk.h>
#include "lfs.h"
#include <zephyr/logging/log.h>

#define CONFIG__LFS_ENABLE	1
// SDMMC DEFINITIONS
#define SECTOR_COUNT 32
#define SECTOR_SIZE 512 /* subsystem should set all cards to 512 byte blocks */
#define BUF_SIZE SECTOR_SIZE * SECTOR_COUNT
static const struct device *const sdhc_dev = DEVICE_DT_GET(DT_ALIAS(sdhc0));
static struct sd_card card;
static uint8_t buf[BUF_SIZE] __aligned(CONFIG_SDHC_BUFFER_ALIGNMENT);
static uint8_t check_buf[BUF_SIZE] __aligned(CONFIG_SDHC_BUFFER_ALIGNMENT);
static uint32_t sector_size;
static uint32_t sector_count;
#define SDMMC_UNALIGN_OFFSET 1


// LFS DEFINITION


// LFS PROTOTYPES
int lfs_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
int lfs_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
int lfs_erase(const struct lfs_config *cfg, lfs_block_t block);
int lfs_sync(const struct lfs_config *cfg);


LOG_MODULE_REGISTER(MAIN);

#if CONFIG__LFS_ENABLE == 1
// variables used by the little filesystem
lfs_t lfs;
lfs_file_t file;

// configuration of the filesystem is provided by this struct
const struct lfs_config cfg = {
    // block device operations
    .read  = lfs_read,
    .prog  = lfs_prog,
    .erase = lfs_erase,
    .sync  = lfs_sync,

    // block device configuration
    .read_size = 16,
    .prog_size = 16,
    .block_size = 4096,
    .block_count = 128,
    .cache_size = 16,
    .lookahead_size = 16,
    .block_cycles = 500,
};
#endif

int main(void)
{
	int ret;

	LOG_INF("LFS Wavenumber sample \n\n");

	ret = device_is_ready(sdhc_dev);

	ret = sd_is_card_present(sdhc_dev);
	if(ret == 0)
	{
		LOG_ERR("SD card not present in slot\n");
	}

	ret = sd_init(sdhc_dev, &card);
	if(ret != 0)
	{
		LOG_ERR("Card initialization failed\n");
		return -1;
	}
	LOG_INF("SD card present and initialized\n");


	ret = sdmmc_ioctl(&card, DISK_IOCTL_GET_SECTOR_COUNT, &sector_count);
	LOG_INF("SD card reports sector count of %d\n", sector_count);

	ret = sdmmc_ioctl(&card, DISK_IOCTL_GET_SECTOR_SIZE, &sector_size);
	LOG_INF("SD card reports sector size of %d\n", sector_size);




#if CONFIG__LFS_ENABLE == 1
	// mount the filesystem
    int err = lfs_mount(&lfs, &cfg);

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
		LOG_ERR("Error mounting LFS");
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);
#endif
	return 0;
}



int lfs_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
	uint32_t sd_addr;
	int32_t error;

	sd_addr =  cfg->block_size + off;
	error = sdmmc_read_blocks(&card, buffer, sd_addr, size);
	return error;
}

int lfs_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
	uint32_t sd_addr;
	int32_t error;

	sd_addr =  cfg->block_size + off;
	error = sdmmc_write_blocks(&card, buffer, sd_addr, size);

	return 0;
}

int lfs_erase(const struct lfs_config *cfg, lfs_block_t block)
{
	uint32_t sd_addr;
	int32_t error;
	uint8_t clean_buff[cfg->block_size];

	memset(clean_buff, 0, cfg->block_size);

	sd_addr =  cfg->block_size;
	error = sdmmc_write_blocks(&card, clean_buff, sd_addr, 1);


	return 0;
}

int lfs_sync(const struct lfs_config *cfg)
{
	return 0;
}
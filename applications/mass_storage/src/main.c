/*
 * Copyright (c) 2016 Intel Corporation.
 * Copyright (c) 2019-2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sample_usbd.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/usb/class/usbd_msc.h>
#include <zephyr/fs/fs.h>
#include <stdio.h>
#include <zephyr/storage/flash_map.h>
#include <ff.h>
#include "audiofs.h"
#include <zephyr/shell/shell.h>

#define STORAGE_PARTITION			storage_partition
#define STORAGE_PARTITION_ID		FIXED_PARTITION_ID(STORAGE_PARTITION)




LOG_MODULE_REGISTER(main);


static int setup_flash(struct fs_mount_t *mnt)
{
	int rc = 0;
	unsigned int id;
	const struct flash_area *pfa;

	mnt->storage_dev = (void *)STORAGE_PARTITION_ID;
	id = STORAGE_PARTITION_ID;

	rc = flash_area_open(id, &pfa);
	printk("Area %u at 0x%x on %s for %u bytes\n",
	       id, (unsigned int)pfa->fa_off, pfa->fa_dev->name,
	       (unsigned int)pfa->fa_size);

	if (rc < 0 && IS_ENABLED(CONFIG_APP_WIPE_STORAGE)) {
		printk("Erasing flash area ... ");
		rc = flash_area_flatten(pfa, 0, pfa->fa_size);
		printk("%d\n", rc);
	}

	if (rc < 0) {
		flash_area_close(pfa);
	}
	return rc;
}

static int mount_app_fs(struct fs_mount_t *mnt)
{
	int rc;
	static FATFS fat_fs;

	mnt->type = FS_FATFS;
	mnt->fs_data = &fat_fs;
	mnt->mnt_point = "/NAND:";

	rc = fs_mount(mnt);

	return rc;
}

static void setup_disk(void)
{
	struct fs_mount_t *mp = &fs_mnt;
	struct fs_dir_t dir;
	struct fs_statvfs sbuf;
	int rc;

	fs_dir_t_init(&dir);

	rc = setup_flash(mp);
	if (rc < 0) {
		LOG_ERR("Failed to setup flash area");
		return;
	}


	rc = mount_app_fs(mp);
	if (rc < 0) {
		LOG_ERR("Failed to mount filesystem");
		return;
	}

	/* Allow log messages to flush to avoid interleaved output */
	k_sleep(K_MSEC(50));

	printk("Mount %s: %d\n", fs_mnt.mnt_point, rc);

	rc = fs_statvfs(mp->mnt_point, &sbuf);
	if (rc < 0) {
		printk("FAIL: statvfs: %d\n", rc);
		return;
	}

	printk("%s: bsize = %lu ; frsize = %lu ;"
	       " blocks = %lu ; bfree = %lu\n",
	       mp->mnt_point,
	       sbuf.f_bsize, sbuf.f_frsize,
	       sbuf.f_blocks, sbuf.f_bfree);

	rc = fs_opendir(&dir, mp->mnt_point);
	printk("%s opendir: %d\n", mp->mnt_point, rc);


	if (rc < 0) {
		LOG_ERR("Failed to open directory");
	}

	while (rc >= 0) {
		struct fs_dirent ent = { 0 };

		rc = fs_readdir(&dir, &ent);

		if (ent.name[0] == 0) {
			printk("End of files\n");
			break;
		}

		printk("  %c \t%u \t%s\n",
		       (ent.type == FS_DIR_ENTRY_FILE) ? 'F' : 'D',
		       ent.size,
		       ent.name);
	}


	(void)fs_closedir(&dir);


	return;
}




/******************************************* SHELL COMMANDS ********************************************/
static int play_wave_file_handler(const struct shell *shell, size_t argc, char **argv)
{
//	if (argc == 6)
//	{
//		play_audio_file(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
//	}

	shell_fprintf(shell, SHELL_VT100_COLOR_YELLOW, "Playing file: %s\n", argv[1]);
	audiofs__play_file(argv[1]);
	return 0;
}

static int read_available_files_handler(const struct shell *shell, size_t argc, char **argv)
{
	audiofs__read_available_files();
	return 0;
}

SHELL_CMD_REGISTER(play_wave_file, NULL, "Play .wav file", play_wave_file_handler);
SHELL_CMD_REGISTER(ls, NULL, "Play .wav file", read_available_files_handler);



int main(void)
{
	int ret;
	
	LOG_INF("ON");

	setup_disk();

	ret = usb_enable(NULL);

	if (ret != 0) {
		LOG_ERR("Failed to enable USB");
		return 0;
	}

	LOG_INF("The device is put in USB mass storage mode.\n");


	audiofs__i2s_init();

//	audiofs__read_available_files();
//
//	// Check all the existing items in the system
//	audiofs__read_header_basic_info("celeb.wav");
//
//	k_sleep(K_MSEC(1000));
//	audiofs__read_n_samples("crckt.wav", 25);

//	audiofs__play_file("celeb.wav");

	return 0;
}



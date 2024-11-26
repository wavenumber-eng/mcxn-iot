/*
 * Copyright (c) 2018, NXP
 * Copyright (c) 2018, Nordic Semiconductor ASA
 * Copyright (c) 2018-2019, Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/ipm.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainX(void)
{


	int count = 100;
	while (1)
	{
		count++;
		if (count % 1000 == 0) {
			printk("\r\[remote] Hello World 3 cm4 %d block %d\r\n", 1, 2);
		}
		k_sleep(K_MSEC(1));
	}



}

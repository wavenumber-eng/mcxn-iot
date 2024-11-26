/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/ipm.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.pb.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	while (1) {
		printk("\r\[remote] Hello World\r\n");
		LOG_INF("Hello World from CM4!");
		k_sleep(K_MSEC(1000));
	}
}

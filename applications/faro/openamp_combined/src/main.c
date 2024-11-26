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
#include <zephyr/init.h>

#include "common.h"

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <zephyr/drivers/uart.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_syslog, LOG_LEVEL_DBG);
#include <zephyr/logging/log_backend.h>
#include <zephyr/logging/log_backend_net.h>
#include <zephyr/logging/log_ctrl.h>

#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/drivers/uart.h>

int main(void)
{
	if (usb_enable(NULL)) {
		
	}
	int i = 0;
	while (1) {
		printk("OpenAMP demo ended.\n");
		printf("OpenAMP demo ended.\n");
		LOG_ERR("Info message (%d)", i++);
		k_sleep(K_MSEC(1000));
	}
}


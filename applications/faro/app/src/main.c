/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

#include "pwm_control.h"


LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

int main(void)
{

	printk("Hello world from %s\n", CONFIG_BOARD_TARGET);
	
	
	pwm_configure();

	while (1) {
		pwm_update_duty_cycle();
		k_sleep(K_MSEC(1000));
	}

	return 0;
}


/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT board_id_phoenix

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

#include <drivers/board_id.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(board_id, CONFIG_SENSOR_LOG_LEVEL);

//Replace with better macro at some point
#define BRD_NUMBER_PINS 3 

struct board_id_data {
	int state;
};

struct board_id_config {
	struct gpio_dt_spec brd_id[3];
};

static enum BOARD_ID_ENUM  get_board_id(const struct device* dev) {
	const struct board_id_config* config = dev->config;
	int retVal = 0;
	for (int i = 0; i < 3; i++)
	{
		int id = gpio_pin_get_dt(&config->brd_id[i]);
		id = id << (i);
		retVal = retVal | id;
	}

	return retVal;
}

static const struct board_id_driver_api board_id_api = {
	.get_board_id = &get_board_id,
};

static int board_id_init(const struct device *dev)
{
	const struct board_id_config *config = dev->config;

	if (BRD_NUMBER_PINS != 3)
	{
		LOG_ERR("board_id_init only supports 3 input pins");
	}

	int ret;
	for (int i = 0; i < BRD_NUMBER_PINS; i++)
	{
		if (!device_is_ready(config->brd_id[i].port)) {
			LOG_ERR("Input GPIO not ready");
			return -ENODEV;
		}

		ret = gpio_pin_configure_dt(&config->brd_id[i], GPIO_INPUT);
		if (ret < 0) {
			LOG_ERR("Could not configure input GPIO (%d)", ret);
			return ret;
		}
	}

	return 0;
}

#define BOARD_ID_INIT(i)						       \
	static struct board_id_data board_id_data_##i;	       \
									       \
	static const struct board_id_config board_id_config_##i = {\
		.brd_id = {GPIO_DT_SPEC_INST_GET_BY_IDX(i, input_gpios, 0), GPIO_DT_SPEC_INST_GET_BY_IDX(i, input_gpios, 1), GPIO_DT_SPEC_INST_GET_BY_IDX(i, input_gpios, 2)},		       \
	};								       \
									       \
	DEVICE_DT_INST_DEFINE(i, board_id_init, NULL,		       \
			      &board_id_data_##i,			       \
			      &board_id_config_##i, POST_KERNEL,	       \
			      CONFIG_GPIO_INIT_PRIORITY, &board_id_api);

DT_INST_FOREACH_STATUS_OKAY(BOARD_ID_INIT)

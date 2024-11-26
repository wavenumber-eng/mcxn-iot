/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT board_id_sim

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

#include <drivers/board_id.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(board_id_sim, CONFIG_SENSOR_LOG_LEVEL);

//Replace with better macro at some point
#define BRD_NUMBER_PINS 3 

struct board_id_sim_data {
	int simulated_id;
};

struct board_id_sim_config {

};

static enum BOARD_ID_ENUM  get_board_sim_id(const struct device* dev) {
	const struct board_id_sim_data* data = dev->data;
	
	return data->simulated_id;
}

static const struct board_id_driver_api board_id_sim_api = {
	.get_board_id = &get_board_sim_id,
};

static int board_id_sim_init(const struct device* dev)
{

	return 0;
};

#define BOARD_ID_SIM_INIT(i)						       \
	static struct board_id_sim_data board_id_sim_data_##i = {	       \
	.simulated_id = DT_INST_PROP(i, simulated_id),				\
	};	\
									       \
	static const struct board_id_sim_config board_id_sim_config_##i;	       \
									       \
	DEVICE_DT_INST_DEFINE(i, board_id_sim_init, NULL,		       \
			      &board_id_sim_data_##i,			       \
			      &board_id_sim_config_##i, POST_KERNEL,	       \
			      CONFIG_GPIO_INIT_PRIORITY, &board_id_sim_api);

DT_INST_FOREACH_STATUS_OKAY(BOARD_ID_SIM_INIT)

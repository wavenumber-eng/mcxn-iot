/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT tracker_sync_phoenix

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys_clock.h>

#include <drivers/tracker_sync.h>


#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(tracker_sync, CONFIG_SENSOR_LOG_LEVEL);

const struct device* dev_local;

extern void sync_timer_expiry(struct k_timer* timer_id);





struct tracker_sync_data {
	struct k_work* work;
	struct k_work_q* queue;
	k_timeout_t period;
	struct k_timer sync_timer;
};

struct tracker_sync_config {
	struct gpio_dt_spec sync_in;
	struct gpio_dt_spec sync_out;
};

void sync_timer_expiry(struct k_timer* timer_id)
{
	// printf("sync_timer_expiry toggling pin\n");
	const struct tracker_sync_config* config = dev_local->config;
	gpio_pin_toggle_dt(&config->sync_out);
}

static int  register_sync_in_kwork(const struct device* dev, struct k_work* work, struct k_work_q* queue) {
	struct tracker_sync_data* data = dev->data;
	data->work = work;
	data->queue = queue;

	return 0;
}

static int  set_sync_out_rate(const struct device* dev, k_timeout_t period) {
	struct tracker_sync_data* data = dev->data;
	data->period.ticks = period.ticks/2;
	if (data->period.ticks != 0)
	{
		k_timer_start(&data->sync_timer, data->period, data->period);
	}
	else {
		k_timer_stop(&data->sync_timer);
	}
	
	return 0;
}

static const struct tracker_sync_driver_api tracker_sync_api = {
	.register_sync_in_kwork = &register_sync_in_kwork,
	.set_sync_out_rate = &set_sync_out_rate,
};

static struct gpio_callback sync_in_cb_data;

void sync_in_received(const struct device* dev, struct gpio_callback* cb,
	uint32_t pins)
{
	// printk("sync_in_received pressed at %" PRIu32 "\n", k_cycle_get_32());
	struct tracker_sync_data* data = dev_local->data;
	if (data->work && data->queue) {
		k_work_submit_to_queue(data->queue, data->work);
	}
	
}

static int tracker_sync_init(const struct device *dev)
{
	dev_local = dev;

	const struct tracker_sync_config *config = dev->config;
	struct tracker_sync_data* data = dev->data;

	if (!device_is_ready(config->sync_in.port)) {
		LOG_ERR("Input GPIO not ready");
		return -ENODEV;
	}

	int ret = gpio_pin_configure_dt(&config->sync_in, GPIO_INPUT);
	if (ret < 0) {
		LOG_ERR("Could not configure input GPIO (%d)", ret);
		return ret;
	}

	if (!device_is_ready(config->sync_in.port)) {
		LOG_ERR("Input GPIO not ready");
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(&config->sync_out, GPIO_OUTPUT);
	if (ret < 0) {
		LOG_ERR("Could not configure input GPIO (%d)", ret);
		return ret;
	}

	ret = gpio_pin_interrupt_configure_dt(&config->sync_in,
		GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		LOG_ERR("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, config->sync_in.port->name, config->sync_in.pin);
		return 0;
	}

	gpio_init_callback(&sync_in_cb_data, sync_in_received, BIT(config->sync_in.pin));
	gpio_add_callback(config->sync_in.port, &sync_in_cb_data);

	k_timer_init(&data->sync_timer, sync_timer_expiry, NULL);

	return 0;
}

#define TRACKER_SYNC_INIT(i)						       \
	static struct tracker_sync_data tracker_sync_data_##i = { \
		.work = NULL, \
		.period = K_MSEC(0), \
	};	       \
									       \
	static const struct tracker_sync_config tracker_sync_config_##i = {\
		.sync_in = GPIO_DT_SPEC_INST_GET_BY_IDX(i, input_gpios, 0),  \
		.sync_out = GPIO_DT_SPEC_INST_GET_BY_IDX(i, output_gpios, 0),		       \
	};								       \
									       \
	DEVICE_DT_INST_DEFINE(i, tracker_sync_init, NULL,		       \
			      &tracker_sync_data_##i,			       \
			      &tracker_sync_config_##i, POST_KERNEL,	       \
			      CONFIG_GPIO_INIT_PRIORITY, &tracker_sync_api);

DT_INST_FOREACH_STATUS_OKAY(TRACKER_SYNC_INIT)

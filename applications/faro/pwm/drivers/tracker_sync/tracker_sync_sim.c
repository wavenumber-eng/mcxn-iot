/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT tracker_sync_sim

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

#include <drivers/tracker_sync.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(tracker_sync_sim, CONFIG_SENSOR_LOG_LEVEL);

const struct device* dev_local;

extern void sync_timer_expiry(struct k_timer* timer_id);
void sync_in_received();


struct tracker_sync_data {
	int simulated_rate_ms;
	struct k_timer sync_timer;
	struct k_work* work;
	struct k_work_q* queue;
	k_timeout_t period;
};

struct tracker_sync_config {

};



void sync_timer_expiry(struct k_timer* timer_id)
{
	// printf("sync_timer_expiry simulating toggling\n");
	sync_in_received();
}

static int  register_sync_in_kwork(const struct device* dev, struct k_work* work, struct k_work_q* queue) {
	struct tracker_sync_data* data = dev->data;
	data->work = work;
	data->queue = queue;

	return 0;
}

static int  set_sync_out_rate(const struct device* dev, k_timeout_t period) {
	struct tracker_sync_data* data = dev->data;
	data->period.ticks = period.ticks;
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


void sync_in_received()
{
	// printk("sync_in_received pressed at %" PRIu32 "\n", k_cycle_get_32());
	struct tracker_sync_data* data = dev_local->data;
	if (data->work && data->queue) {
		k_work_submit_to_queue(data->queue, data->work);
	}

}

static int tracker_sync_init(const struct device* dev)
{
	dev_local = dev;
	struct tracker_sync_data* data = dev->data;
	k_timer_init(&data->sync_timer, sync_timer_expiry, NULL);

	
	if (data->period.ticks != 0)
	{
		k_timer_start(&data->sync_timer, data->period, data->period);
	}
	else {
		k_timer_stop(&data->sync_timer);
	}

	return 0;
}

#define TRACKER_SYNC_INIT(i)						       \
	static struct tracker_sync_data tracker_sync_data_##i = { \
		.work = NULL, \
		.period = DT_INST_PROP(i, simulated_rate_ms), \
	};	       \
									       \
	static const struct tracker_sync_config tracker_sync_config_##i = {\
	};								       \
									       \
	DEVICE_DT_INST_DEFINE(i, tracker_sync_init, NULL,		       \
			      &tracker_sync_data_##i,			       \
			      &tracker_sync_config_##i, POST_KERNEL,	       \
			      CONFIG_GPIO_INIT_PRIORITY, &tracker_sync_api);

DT_INST_FOREACH_STATUS_OKAY(TRACKER_SYNC_INIT)

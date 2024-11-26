/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <drivers/board_id.h>
#include <drivers/tracker_sync.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/drivers/uart.h>
#include <app_version.h>

#include <zephyr/net/socket.h>
#include <zephyr/net/net_core.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/ethernet.h>
#include <zephyr/net/net_mgmt.h>

#include "pwm_control.h"
#include "version.pb.h"

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#define BLINK_PERIOD_MS_STEP 100U
#define BLINK_PERIOD_MS_MAX  1000U

#define MY_IPADDR { { { 192, 168, 1, 100 } } }
#define BROADCAST_PORT 4242

#if !DT_NODE_EXISTS(DT_NODELABEL(boardida))
//#error "Board ID Not defined"
#endif

//static const struct gpio_dt_spec board_id = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(boardida), gpios, { 0 });

/** Workqueue stack size for bounding processing (this configuration is not optimized). */
#define EP_BOUND_WORK_Q_STACK_SIZE (512U)

static struct k_work ipm_work;
static struct k_work_q ep_bound_work_q;
static K_THREAD_STACK_DEFINE(ep_bound_work_q_stack, EP_BOUND_WORK_Q_STACK_SIZE);

static void ipm_callback_process(struct k_work* work)
{
	// printf("Into callback\n");
}

int main(void)
{

	if (usb_enable(NULL)) {
		printf("USB enable failed\n");
	}
	// for(uint8_t i =0; i<10; i++)
	// {
	// 	printk("Waiting sec %d\n", i);
	// 	k_sleep(K_MSEC(1000));
	// }

	printk("Hello world from %s\n", CONFIG_BOARD_TARGET);
	printk("Running on CM7\n");

	const struct device* board_id_device;

	board_id_device = DEVICE_DT_GET(DT_NODELABEL(board_id));

	const struct device* tracker_sync_device;

	tracker_sync_device = DEVICE_DT_GET(DT_NODELABEL(tracker_sync));

	if (!device_is_ready(board_id_device)) {
		LOG_ERR("Sensor not ready");
		return 0;
	}

	if (!device_is_ready(tracker_sync_device)) {
		LOG_ERR("Sensor not ready");
		return 0;
	}
	
	k_work_queue_init(&ep_bound_work_q);
	k_work_queue_start(&ep_bound_work_q, ep_bound_work_q_stack,
		K_THREAD_STACK_SIZEOF(ep_bound_work_q_stack),
		CONFIG_SYSTEM_WORKQUEUE_PRIORITY, NULL);
	
	k_work_init(&ipm_work, ipm_callback_process);

	tracker_sync_register_sync_in_kwork(tracker_sync_device, &ipm_work, &ep_bound_work_q);
	tracker_sync_set_sync_out_rate(tracker_sync_device, K_MSEC(100));
	
	pwm_configure();

	while (1) {
		enum BOARD_ID_ENUM id = board_id_get_board_id(board_id_device);
		char* boardName = board_id_get_name(board_id_device);
		// printf("The board ID is %d string = %s\n", id, boardName);
		// printf("App version "APP_VERSION_EXTENDED_STRING"\n" );
		pwm_update_duty_cycle();
		k_sleep(K_MSEC(1000));
	}

	return 0;
}


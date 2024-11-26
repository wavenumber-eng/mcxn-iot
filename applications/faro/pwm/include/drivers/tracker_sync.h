/*
 * Copyright (c) 2024 FARO
 *
 */

#ifndef APP_DRIVERS_TRACKER_SYNC_H_
#define APP_DRIVERS_TRACKER_SYNC_H_

#include <zephyr/device.h>
#include <zephyr/toolchain.h>
#include <zephyr/sys_clock.h>

/**
 * @defgroup drivers_tracker_sync Reads the board ID from the Phoenix boards
 * @ingroup drivers
 * @{
 *
 * @brief Reads the board ID from the Phoenix boards
 *
 */



/** @brief board id driver class operations */
__subsystem struct tracker_sync_driver_api {
	int (*register_sync_in_kwork)(const struct device* dev, struct k_work* work, struct k_work_q* queue);
	int (*set_sync_out_rate)(const struct device* dev, k_timeout_t period);
	
};

/** @} */



__syscall int tracker_sync_register_sync_in_kwork(const struct device *dev, struct k_work* work, struct k_work_q* queue);



static inline int z_impl_tracker_sync_register_sync_in_kwork(const struct device *dev, struct k_work* work, struct k_work_q* queue)
{
	const struct tracker_sync_driver_api* api =
		(const struct tracker_sync_driver_api*)dev->api;

	return api->register_sync_in_kwork(dev, work, queue);
}

__syscall int tracker_sync_set_sync_out_rate(const struct device* dev, k_timeout_t period);

static inline int z_impl_tracker_sync_set_sync_out_rate(const struct device* dev, k_timeout_t period)
{
	const struct tracker_sync_driver_api* api =
		(const struct tracker_sync_driver_api*)dev->api;

	return api->set_sync_out_rate(dev, period);
}


#include <syscalls/tracker_sync.h>


#endif /* APP_DRIVERS_BLINK_H_ */

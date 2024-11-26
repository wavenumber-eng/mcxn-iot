/*
 * Copyright (c) 2024 FARO
 *
 */

#ifndef APP_DRIVERS_BOOARD_ID_H_
#define APP_DRIVERS_BOOARD_ID_H_

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/**
 * @defgroup drivers_board_id Reads the board ID from the Phoenix boards
 * @ingroup drivers
 * @{
 *
 * @brief Reads the board ID from the Phoenix boards
 *
 */


enum BOARD_ID_ENUM {
	SKIRT_BACKPLANE = 0,
	AZ_CONTROLLER = 1,
	DATA_PROCESSING_UNIT = 2,
	ZE_CONTROLLER = 3,
	PADM_CONTROLLER = 4,
	SIX_DOF_PROCESSOR = 5,
	PAYLOAD_BACKPLANE = 6,
};

/** @brief board id driver class operations */
__subsystem struct board_id_driver_api {
	
	enum BOARD_ID_ENUM (*get_board_id)(const struct device *dev);
};

/** @} */



__syscall enum BOARD_ID_ENUM  board_id_get_board_id(const struct device *dev);



static inline enum BOARD_ID_ENUM  z_impl_board_id_get_board_id(const struct device *dev)
{
	const struct board_id_driver_api* api =
		(const struct board_id_driver_api*)dev->api;

	return api->get_board_id(dev);
}



/**
 * @brief Get the board ID as a string
 *
 * This is a convenience function to get the board ID as a string
 */
static inline char * board_id_get_name(const struct device *dev)
{
	enum BOARD_ID_ENUM id = board_id_get_board_id(dev);
	switch (id) {
	case SKIRT_BACKPLANE:
		return "skirt backplane";
		break;
	case AZ_CONTROLLER:
		return "azimuth controller";
		break;
	case DATA_PROCESSING_UNIT:
		return "data processing unit";
		break;
	case ZE_CONTROLLER:
		return "zenith controller";
		break;
	case PADM_CONTROLLER:
		return "PADM controller";
		break;
	case SIX_DOF_PROCESSOR:
		return "six DOF processor";
		break;
	case PAYLOAD_BACKPLANE:
		return "payload backplane";
		break;
	default:
		return "unknown processor";
	}
}

#include <syscalls/board_id.h>


#endif /* APP_DRIVERS_BLINK_H_ */

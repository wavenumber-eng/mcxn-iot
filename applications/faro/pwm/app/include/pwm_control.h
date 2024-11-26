/*
 * Copyright (c) 2024 FARO
 *
 */

#ifndef PWM_CONTROL_H_
#define PWM_CONTROL_H_

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/**
 * @brief Configures PWM
 */
void pwm_configure();

/**
 * @brief Updates the duty cycle of the PWM signal
 */
void pwm_update_duty_cycle(void);


#endif /* PWM_CONTROL_H_ */

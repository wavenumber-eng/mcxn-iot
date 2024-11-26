/*
 * Copyright (c) 2024 FARO
 *
 */

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

/* Define PWM device aliases */
#define PWM_DEVICE_PWM0 DT_ALIAS(pwm3_pwm0)
#define PWM_DEVICE_PWM1 DT_ALIAS(pwm3_pwm1)
#define PWM_DEVICE_PWM2 DT_ALIAS(pwm3_pwm2)

#if !DT_NODE_HAS_STATUS(PWM_DEVICE_PWM0, okay)
#warning "PWM3-PWM0 device not defined"
#endif

#if !DT_NODE_HAS_STATUS(PWM_DEVICE_PWM1, okay)
#warning "PWM3-PWM1 device not defined"
#endif

#if !DT_NODE_HAS_STATUS(PWM_DEVICE_PWM2, okay)
#warning "PWM3-PWM2 device not defined"
#endif

LOG_MODULE_REGISTER(pwm_control, CONFIG_APP_LOG_LEVEL);

#define PWM_FREQUENCY_HZ (1000U)

const struct device *pwm_dev0 = DEVICE_DT_GET(PWM_DEVICE_PWM0);
const struct device *pwm_dev1 = DEVICE_DT_GET(PWM_DEVICE_PWM1);
const struct device *pwm_dev2 = DEVICE_DT_GET(PWM_DEVICE_PWM2);
static uint32_t pwm_period = 1000; 
static uint32_t pwm_val = 500;

void pwm_configure(void)
{
    if (!device_is_ready(pwm_dev0) || !device_is_ready(pwm_dev1) || !device_is_ready(pwm_dev2))
    {
        printk("Motor Control PWM device not ready");
        return;
    }
    
    int ret = pwm_set(pwm_dev0, 0, pwm_period, pwm_val, 0);
    if (ret) {
        printk("Failed to set PWM device 0\n");
    }

    ret = pwm_set(pwm_dev1, 0, pwm_period, pwm_val, 0);
    if (ret) {
        printk("Failed to set PWM device 1\n");
    }

    ret = pwm_set(pwm_dev2, 0, pwm_period, pwm_val, 0);
    if (ret) {
        printk("Failed to set PWM device 2\n");
    }

    printk("PWM devices configured\n");
}

void pwm_update_duty_cycle(void)
{
    printk("updating pwm dutycycle\n");

    int ret = pwm_set(pwm_dev0, 0, pwm_period, pwm_val, PWM_POLARITY_NORMAL);
    if (ret) {
        printk("Failed to update PWM0 motor dutycycle\n");
    }
    
    ret = pwm_set(pwm_dev1, 0, pwm_period, pwm_val, PWM_POLARITY_NORMAL);
    if (ret) {
        printk("Failed to update PWM1 motor dutycycle\n");
    }

    ret = pwm_set(pwm_dev2, 0, pwm_period, pwm_val, PWM_POLARITY_NORMAL);
    if (ret) {
        printk("Failed to update PWM2 motor dutycycle\n");
    }
}

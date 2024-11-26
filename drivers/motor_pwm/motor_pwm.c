/*
 * Copyright (c) 2024 FARO
 */

#define DT_DRV_COMPAT motor_pwm

#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/clock_control.h>
#include <soc.h>
#include <fsl_pwm.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(motor_pwm, 4);

#define CHANNEL_COUNT 2
static bool initialized[3] = {false};

struct motor_pwm_config {
	PWM_Type *base;
	uint8_t index;
	const struct device *clock_dev;
	pwm_init_source_t init_control;
	clock_control_subsys_t clock_subsys;
	pwm_clock_prescale_t prescale;
	pwm_register_reload_t reload;
	pwm_mode_t mode;
	pwm_init_source_t init_source;
	pwm_chnl_pair_operation_t pair_operation;
	bool run_wait;
	bool run_debug;
	const struct pinctrl_dev_config *pincfg;
	uint16_t deadtime_value;
	uint8_t clock_source;
	uint8_t channel;
	uint32_t pwm_freq;
	uint32_t clock_freq;
};

struct motor_pwm_data {
	uint32_t period_cycles[CHANNEL_COUNT];
	pwm_signal_param_t channel[CHANNEL_COUNT];
	struct k_mutex lock;
};

static int motor_pwm_set_cycles_internal(const struct device *dev, uint32_t channel,
			       uint32_t period_cycles, uint32_t pulse_cycles,
			       pwm_flags_t flags)
{
	const struct motor_pwm_config *config = dev->config;
	struct motor_pwm_data *data = dev->data;
	pwm_level_select_t level;
	
	if (flags & PWM_POLARITY_INVERTED) {
		level = kPWM_LowTrue;
	} else {
		level = kPWM_HighTrue;
	}

	if (period_cycles != data->period_cycles[channel]
	    || level != data->channel[channel].level) {
		uint32_t clock_freq;
		status_t status;

		data->period_cycles[channel] = config->pwm_freq;
		clock_freq = config->clock_freq;

		// if (clock_control_get_rate(config->clock_dev, config->clock_subsys,
		// 		&clock_freq)) {
		// 	return -EINVAL;
		// }

		data->channel[channel].pwmchannelenable = true;

		PWM_StopTimer(config->base, 1U << config->index);

		/*
		 * We will directly write the duty cycle pulse width
		 * and full pulse width into the VALx registers to
		 * setup PWM with higher resolution.
		 * Therefore we use dummy values for the duty cycle
		 * and frequency.
		 */
		data->channel[channel].dutyCyclePercent = 50;
		data->channel[channel].level = level;
		data->channel[channel].deadtimeValue = config->deadtime_value;
		memcpy(&data->channel[1], &data->channel[0], sizeof(pwm_signal_param_t));
		data->channel[1].pwmChannel = kPWM_PwmB;
		data->channel[0].pwmChannel = kPWM_PwmA;

		if(!initialized[config->index])
		{
			uint8_t num_of_channels = 1;
			if(!config->index)
			{
				num_of_channels = 2;
			}
			status = PWM_SetupPwm(config->base, config->index,
						&data->channel[channel], num_of_channels,
						config->mode, data->period_cycles[channel], clock_freq);
				
			PWM_SetPwmLdok(config->base, 1U << config->index, true);

			PWM_StartTimer(config->base, 1U << config->index);
			initialized[config->index] = true;
		}
		else
		{
			if(config->index == 0)
			{
				data->channel[channel].dutyCyclePercent = 10;
			}
			else if(config->index == 1)
			{
				data->channel[channel].dutyCyclePercent = 5;
			}
			else{
				data->channel[channel].dutyCyclePercent = 2;
			}
		    
			uint16_t reload_val = ((65535 * data->channel[channel].dutyCyclePercent) +50U)/100U;
			uint16_t modulo = PWM_GetVALxValue(config->base, config->index, kPWM_ValueRegister_1);
			uint16_t pulse_cnt = modulo * 2U;
			uint16_t pwm_high_pulse = (pulse_cnt * reload_val) / 65535U;
			uint16_t pwm_high_pulse_compl = (~pwm_high_pulse +1);
			
			if (channel == 1) {
				PWM_SetVALxValue(config->base, config->index,
					 kPWM_ValueRegister_4, (pwm_high_pulse_compl / 2U));
				PWM_SetVALxValue(config->base, config->index,
					 kPWM_ValueRegister_5,
					 (pwm_high_pulse / 2U));
			}
			else{
				PWM_SetVALxValue(config->base, config->index,
					 kPWM_ValueRegister_2, (pwm_high_pulse_compl / 2U));
				PWM_SetVALxValue(config->base, config->index,
					 kPWM_ValueRegister_3,
					 (pwm_high_pulse / 2U));
			}
			PWM_SetPwmLdok(config->base, 1U << config->index, true);
		}
	} else {
		PWM_UpdatePwmDutycycle(config->base, config->index, data->channel[channel].pwmChannel, config->mode, data->channel[channel].dutyCyclePercent);
        PWM_SetPwmLdok(config->base, 1U << config->index, true);
	}

	return 0;
}

static int motor_pwm_set_cycles(const struct device *dev, uint32_t channel,
			       uint32_t period_cycles, uint32_t pulse_cycles,
			       pwm_flags_t flags)
{
	struct motor_pwm_data *data = dev->data;
	int result;

	if (channel >= CHANNEL_COUNT) {
		LOG_ERR("Invalid channel");
		return -EINVAL;
	}

	if (period_cycles == 0) {
		LOG_ERR("Channel can not be set to inactive level");
		return -ENOTSUP;
	}

	if (period_cycles > UINT16_MAX) {
		/* 16-bit resolution */
		LOG_ERR("Too long period (%u), adjust pwm prescaler!",
			period_cycles);
		/* TODO: dynamically adjust prescaler */
		return -EINVAL;
	}
	k_mutex_lock(&data->lock, K_FOREVER);
	result = motor_pwm_set_cycles_internal(dev, channel, period_cycles, pulse_cycles, flags);
	k_mutex_unlock(&data->lock);
	return result;
}

static int motor_pwm_get_cycles_per_sec(const struct device *dev,
				       uint32_t channel, uint64_t *cycles)
{
	const struct motor_pwm_config *config = dev->config;
	uint32_t clock_freq;

	if (clock_control_get_rate(config->clock_dev, config->clock_subsys,
			&clock_freq)) {
		return -EINVAL;
	}
	*cycles = clock_freq >> config->prescale;

	printf("Called from get pwm cycles. clock_fre= %d, cycles = %lld\n",clock_freq, *cycles);
	return 0;
}

static int motor_pwm_init(const struct device *dev)
{
	const struct motor_pwm_config *config = dev->config;
	struct motor_pwm_data *data = dev->data;
	pwm_config_t pwm_config;
	status_t status;
	int i, err;

	k_mutex_init(&data->lock);

	if (!device_is_ready(config->clock_dev)) {
		LOG_ERR("clock control device not ready");
		return -ENODEV;
	}

	err = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (err < 0) {
		return err;
	}

	LOG_DBG("Set prescaler %d, reload mode %d",
			1 << config->prescale, config->reload);

	PWM_GetDefaultConfig(&pwm_config);
	pwm_config.enableDebugMode = config->run_debug;
	pwm_config.clockSource = config->clock_source;
	pwm_config.prescale = config->prescale;
	pwm_config.pairOperation = config->pair_operation;
	pwm_config.reloadLogic = config->reload;
	pwm_config.initializationControl = config->init_control;
	pwm_config.pairOperation = config->pair_operation;

#if !defined(FSL_FEATURE_PWM_HAS_NO_WAITEN) || (!FSL_FEATURE_PWM_HAS_NO_WAITEN)
	pwm_config.enableWait = config->run_wait;
#endif

	status = PWM_Init(config->base, config->index, &pwm_config);
	if (status != kStatus_Success) {
		LOG_ERR("Unable to init PWM");
		return -EIO;
	}

	/* Disable fault sources */
	for (i = 0; i < FSL_FEATURE_PWM_FAULT_CH_COUNT; i++) {
		config->base->SM[config->index].DISMAP[i] = 0x0000;
	}

	// data->channel[0].pwmChannel = kPWM_PwmA;
	data->channel[0].level = kPWM_HighTrue;
	// data->channel[1].pwmChannel = kPWM_PwmB;
	data->channel[1].level = kPWM_HighTrue;

	return 0;
}

static const struct pwm_driver_api motor_pwm_driver_api = {
	.set_cycles = motor_pwm_set_cycles,
	.get_cycles_per_sec = motor_pwm_get_cycles_per_sec,
};

#define PWM_DEVICE_INIT_MOTOR(n)			  \
	static struct motor_pwm_data motor_pwm_data_ ## n;		  \
	PINCTRL_DT_INST_DEFINE(n);					  \
									  \
	static const struct motor_pwm_config motor_pwm_config_ ## n = {     \
		.base = (PWM_Type *)DT_REG_ADDR(DT_INST_PARENT(n)),	  \
		.index = DT_INST_PROP(n, index),			  \
		.mode =  DT_ENUM_IDX_OR(DT_DRV_INST(n), mode, 0),				  \
		.prescale = _CONCAT(kPWM_Prescale_Divide_, DT_INST_PROP(n, nxp_prescaler)),\
		.reload = DT_ENUM_IDX_OR(DT_DRV_INST(n), nxp_reload,\
				kPWM_ReloadPwmFullCycle),\
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),		\
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(n, name),\
		.run_wait = DT_INST_PROP(n, run_in_wait),		  \
		.run_debug = DT_INST_PROP(n, run_in_debug),		  \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(n),		  \
		.pair_operation = DT_INST_PROP(n, pair_operation),\
		.deadtime_value = DT_INST_PROP(n, dead_time),\
		.clock_source = DT_ENUM_IDX_OR(DT_DRV_INST(n), clock_source, 0),\
		.init_control = DT_ENUM_IDX_OR(DT_DRV_INST(n), init_source, 0),\
		.pwm_freq = DT_INST_PROP(n, pwm_freq),\
		.clock_freq = DT_INST_PROP(n, clock_freq),\
	};								  \
									  \
	DEVICE_DT_INST_DEFINE(n,					  \
			    motor_pwm_init,				  \
			    NULL,					  \
			    &motor_pwm_data_ ## n,			  \
			    &motor_pwm_config_ ## n,			  \
			    POST_KERNEL, CONFIG_PWM_INIT_PRIORITY,	  \
			    &motor_pwm_driver_api);

DT_INST_FOREACH_STATUS_OKAY(PWM_DEVICE_INIT_MOTOR)

#-------------------------------------------------------------------------------
# Copyright (c) 2024 FARO
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.13.1)

zephyr_library_sources_ifndef(CONFIG_CUSTOM_PWM pwm_mcux.c)
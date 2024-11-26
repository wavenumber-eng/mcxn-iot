# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0
#
# This CMake file is picked by the Zephyr build system because it is defined
# as the module CMake entry point (see zephyr/module.yml).
add_subdirectory(drivers)

zephyr_syscall_include_directories(include)

zephyr_include_directories(include)

set(ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/drivers/motor_pwm)

message("Zephyr extra modules: ${ZEPHYR_EXTRA_MODULES}")
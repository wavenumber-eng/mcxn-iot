# Copyright (c) 2018 Nordic Semiconductor ASA
# Copyright (c) 2019 Linaro Limited
# Copyright 2022 NXP
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})


project(MIMXRT1176_CM4)
message(STATUS "${BOARD} compiles as remote in this sample")
message(STATUS " ZEPHYR_BASE=${ZEPHYR_BASE}")

list(APPEND CMAKE_MODULE_PATH ${ZEPHYR_BASE}/modules/nanopb)
include(nanopb)
zephyr_nanopb_sources(app ../../proto/version.proto)

target_sources(app PRIVATE src/main.c
                           src/log_control.c)
                           
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)


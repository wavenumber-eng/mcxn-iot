#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

set(REMOTE_ZEPHYR_DIR ${CMAKE_CURRENT_BINARY_DIR}/../MIMXRT1176_CM4/zephyr)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH ${ZEPHYR_BASE}/modules/nanopb)
include(nanopb)

message(STATUS "${BOARD} compile as Master in this sample")

if(CONFIG_INCLUDE_REMOTE_DIR)
  target_include_directories(zephyr_interface
    INTERFACE ${REMOTE_ZEPHYR_DIR}/include/public)
endif()


zephyr_nanopb_sources(app ../proto/version.proto)
target_sources(app PRIVATE src/main.c
                      src/pwm_control.c)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

zephyr_include_directories(include)


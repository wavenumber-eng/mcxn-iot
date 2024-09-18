# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

include_directories(${CMAKE_SOURCE_DIR}/littlefs)

project(little_fs)

# Collect all .c files in the src directory
file(GLOB app_sources 
        src/*.c
        littlefs/*.c)

target_sources(app PRIVATE ${app_sources})

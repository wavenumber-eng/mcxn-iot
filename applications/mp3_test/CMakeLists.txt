# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(mp3_test VERSION 1.0.0)

target_include_directories(app PRIVATE ./src)

target_sources(app PRIVATE 
                src/main.c
                src/mp3_files.c
                )

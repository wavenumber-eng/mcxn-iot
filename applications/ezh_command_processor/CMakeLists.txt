cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ezh_command_processor)

target_sources(app PRIVATE  src/main.cpp
                            src/t2.c)

target_sources(app PRIVATE ../../../modules/bunny_build/src/bunny_build.c)
target_sources(app PRIVATE ../../../modules/bunny_build/src/ezh_init.c)
target_sources(app PRIVATE src/ezh_app.c)

target_include_directories(app PRIVATE ../../../modules/bunny_build/src)
target_include_directories(app PRIVATE ./src)                            
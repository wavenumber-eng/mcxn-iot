# Install script for directory: C:/companies/wavenumber/mcxn-iot/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/jerpa77/zephyr-sdk-0.16.8/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/golioth-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/adi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/altera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/companies/wavenumber/mcxn-iot/mcxn-iot/applications/little_fs/ebug/zephyr/cmake/reports/cmake_install.cmake")
endif()


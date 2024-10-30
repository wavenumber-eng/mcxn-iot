#
# Copyright (c) 2019, NXP
#
# SPDX-License-Identifier: Apache-2.0
#


## DAP Link implementation in pyocd is underway,
## until then jlink can be used or copy image to storage

if(CONFIG_BOARD_GIBBON_D_LPC55S69_CPU0)
board_runner_args(jlink "--device=LPC55S66_M33_0")
endif()

board_runner_args(pyocd "--target=lpc55s69" "--frequency=10M")

include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)

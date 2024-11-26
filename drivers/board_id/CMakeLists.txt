# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_BOARD_ID_PHOENIX board_id_phoenix.c)
zephyr_library_sources_ifdef(CONFIG_BOARD_ID_SIM board_id_sim.c)

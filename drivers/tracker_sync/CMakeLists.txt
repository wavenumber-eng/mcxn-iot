# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_TRACKER_SYNC_PHOENIX tracker_sync_phoenix.c)
zephyr_library_sources_ifdef(CONFIG_TRACKER_SYNC_SIM tracker_sync_sim.c)

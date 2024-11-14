/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>

#include <zephyr/kernel.h>
#include <zephyr/linker/sections.h>
#include <errno.h>
#include <stdio.h>

#include <zephyr/net/net_core.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/net/net_config.h>

LOG_MODULE_REGISTER(net_telnet_sample, LOG_LEVEL_DBG);


int main(void)
{
	int ret =0 ;
	
	ret = usb_enable(NULL);

	if (ret != 0) {
		LOG_ERR("Cannot enable USB (%d)", ret);
		return ret;
	}
	
	//(void)net_config_init_app(NULL, "Initializing network");


	//Wired Ethernet
	struct net_if *iface1 = net_if_get_by_index(1);
	//rndis
    struct net_if *iface2 = net_if_get_by_index(2);

    struct in_addr addr1, addr2;
	struct in_addr gateway1,gateway2;

    // Set IP for wired ethernet
    net_addr_pton(AF_INET, "192.168.0.100", &addr1);
    net_if_ipv4_addr_add(iface1, &addr1, NET_ADDR_MANUAL, 0);

	net_addr_pton(AF_INET, "192.168.0.100", &gateway1); 
	net_if_ipv4_set_gw(iface1, &gateway1);

	net_if_up(iface1);

    // Set IP RNDIS Interface
    net_addr_pton(AF_INET, "192.168.2.100", &addr2);
    net_if_ipv4_addr_add(iface2, &addr2, NET_ADDR_MANUAL, 0);

	net_addr_pton(AF_INET, "192.168.2.100", &gateway2);  
	net_if_ipv4_set_gw(iface2, &gateway2);

	net_if_up(iface2);

	while (true)
    {
        k_sleep(K_MSEC(100));
    }

	return 0;
}

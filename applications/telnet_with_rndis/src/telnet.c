/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_telnet_sample, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>
#include <zephyr/linker/sections.h>
#include <errno.h>
#include <stdio.h>

#include <zephyr/net/net_core.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/net/net_config.h>

//#if defined(CONFIG_NET_DHCPV4)
//static struct net_mgmt_event_callback mgmt_cb;
//
//static void ipv4_addr_add_handler(struct net_mgmt_event_callback *cb,
//				  uint32_t mgmt_event,
//				  struct net_if *iface)
//{
//	char hr_addr[NET_IPV4_ADDR_LEN];
//	int i = 0;
//
//	if (mgmt_event != NET_EVENT_IPV4_ADDR_ADD) {
//		/* Spurious callback. */
//		return;
//	}
//
//	for (i = 0; i < NET_IF_MAX_IPV4_ADDR; i++) {
//		struct net_if_addr *if_addr =
//			&iface->config.ip.ipv4->unicast[i];
//
//		if (if_addr->addr_type != NET_ADDR_DHCP || !if_addr->is_used) {
//			continue;
//		}
//
//		LOG_INF("IPv4 address: %s",
//			net_addr_ntop(AF_INET,
//				      &if_addr->address.in_addr,
//				      hr_addr, NET_IPV4_ADDR_LEN));
//		LOG_INF("Lease time: %u seconds",
//			 iface->config.dhcpv4.lease_time);
//		LOG_INF("Subnet: %s",
//			net_addr_ntop(AF_INET,
//				      &iface->config.ip.ipv4->netmask,
//				      hr_addr, NET_IPV4_ADDR_LEN));
//		LOG_INF("Router: %s",
//			net_addr_ntop(AF_INET,
//				      &iface->config.ip.ipv4->gw,
//				      hr_addr, NET_IPV4_ADDR_LEN));
//		break;
//	}
//}
//
//static void setup_dhcpv4(struct net_if *iface)
//{
//	LOG_INF("Running dhcpv4 client...");
//
//	net_mgmt_init_event_callback(&mgmt_cb, ipv4_addr_add_handler,
//				     NET_EVENT_IPV4_ADDR_ADD);
//	net_mgmt_add_event_callback(&mgmt_cb);
//
//	net_dhcpv4_start(iface);
//}
//
//#else
//#define setup_dhcpv4(...)
//#endif /* CONFIG_NET_DHCPV4 */
//
//#if defined(CONFIG_NET_IPV4) && !defined(CONFIG_NET_DHCPV4)
//
//#if !defined(CONFIG_NET_CONFIG_MY_IPV4_ADDR)
//#error "You need to define an IPv4 Address or enable DHCPv4!"
//#endif
//
//static void setup_ipv4(struct net_if *iface)
//{
//	char hr_addr[NET_IPV4_ADDR_LEN];
//	struct in_addr addr;
//
//	if (net_addr_pton(AF_INET, CONFIG_NET_CONFIG_MY_IPV4_ADDR, &addr)) {
//		LOG_ERR("Invalid address: %s", CONFIG_NET_CONFIG_MY_IPV4_ADDR);
//		return;
//	}
//
//	net_if_ipv4_addr_add(iface, &addr, NET_ADDR_MANUAL, 0);
//
//	LOG_INF("IPv4 address: %s",
//		net_addr_ntop(AF_INET, &addr, hr_addr,
//			      NET_IPV4_ADDR_LEN));
//}
//
//#else
//#define setup_ipv4(...)
//#endif /* CONFIG_NET_IPV4 && !CONFIG_NET_DHCPV4 */

//#if defined(CONFIG_NET_IPV6)
//
//#define MCAST_IP6ADDR "ff84::2"
//
//#ifndef CONFIG_NET_CONFIG_MY_IPV6_ADDR
//#error "You need to define an IPv6 Address!"
//#endif

//static void setup_ipv6(struct net_if *iface)
//{
//	char hr_addr[NET_IPV6_ADDR_LEN];
//	struct in6_addr addr;
//
//	if (net_addr_pton(AF_INET6, CONFIG_NET_CONFIG_MY_IPV6_ADDR, &addr)) {
//		LOG_ERR("Invalid address: %s", CONFIG_NET_CONFIG_MY_IPV6_ADDR);
//		return;
//	}
//
//	net_if_ipv6_addr_add(iface, &addr, NET_ADDR_MANUAL, 0);
//
//	LOG_INF("IPv6 address: %s",
//		net_addr_ntop(AF_INET6, &addr, hr_addr, NET_IPV6_ADDR_LEN));
//
//	if (net_addr_pton(AF_INET6, MCAST_IP6ADDR, &addr)) {
//		LOG_ERR("Invalid address: %s", MCAST_IP6ADDR);
//		return;
//	}
//
//	net_if_ipv6_maddr_add(iface, &addr);
//}
//
//#else
//#define setup_ipv6(...)
//#endif /* CONFIG_NET_IPV6 */


static void start_dhcpv4_client(struct net_if *iface, void *user_data)
{
	ARG_UNUSED(user_data);

	LOG_INF("Start on %s: index=%d", net_if_get_device(iface)->name,
		net_if_get_by_iface(iface));
	net_dhcpv4_start(iface);
}

int init_usb(void)
{
	int ret;

	ret = usb_enable(NULL);
	if (ret != 0) {
		LOG_ERR("Cannot enable USB (%d)", ret);
		return ret;
	}

	(void)net_config_init_app(NULL, "Initializing network");

	return 0;
}



int main(void)
{
	init_usb();

	struct net_if * usb_eth = net_if_get_by_index(2);	
//	struct net_if *iface = net_if_get_by_index(2);
//
//	LOG_INF("Starting Telnet sample");
//
//	LOG_INF("Setting up IPV4");
//	setup_ipv4(iface);

//	LOG_INF("Setting up DHCPV4");
//	setup_dhcpv4(iface);
//
//	LOG_INF("Setting up IPV6");
//	setup_ipv6(iface);

//	start_dhcpv4_client(usb_eth, "USB ETHERNET");
	//net_if_foreach(start_dhcpv4_client, NULL);


	struct net_if *iface1 = net_if_get_by_index(1);
    struct net_if *iface2 = net_if_get_by_index(2);

    struct in_addr addr1, addr2;

    // Set IP for first interface
    net_addr_pton(AF_INET, "192.168.1.131", &addr1);
    net_if_ipv4_addr_add(iface1, &addr1, NET_ADDR_MANUAL, 0);


    // Set IP for second interface
    net_addr_pton(AF_INET, "192.168.1.132", &addr2);
    net_if_ipv4_addr_add(iface2, &addr2, NET_ADDR_MANUAL, 0);


	struct in_addr gateway;
	net_addr_pton(AF_INET, "192.168.1.9", &gateway);  // Replace with your actual gateway IP
	net_if_ipv4_set_gw(iface1, &gateway);
	net_if_ipv4_set_gw(iface2, &gateway);


	// DHCP
    //start_dhcpv4_client(iface2, "DEB");

	while (true)
    {
        k_sleep(K_MSEC(100));
    }

	return 0;
}

/**
 * Copyright ? 2019 Zhejiang Raying IoT Technology Co., Ltd.
 * All rights reserved. 
 *
 * File: Global_Callbacks.c
 * Description: This file implements global callbacks.
 *
 * Author(s): yuxiaoqiang@rexense.com	
 * Data: 2020/02/20
 */
#if defined(RZ_STACK_API_USAGE)

#include "../include/global_apis.h"
#include "pin_def.h"
#include "app_common.h"

#define  DEFINEEEPTYPE
#include "common/app_sim_eep.h"	//type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#if defined(RZ_STACK_TC_LINK_API_USAGE)

#warning "tc link plugin api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

#define APP_HEARTBEAT_MIN_PERIOD_S 20
#define APP_HEARTBEAT_MAX_PERIOD_S 40

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_TC_LINK_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_TC_LINK_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

void app_hal_uart_config(void)
{
	app_serial_init(TYPE_UART_SERIAL,
					APP_UART_TX_PIN,
					APP_UART_RX_PIN,
					APP_UART_BAUDRATE,
					UART_PARITY_NONE,
					1);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if(util_match_uart_command_fixed_length("AT+GETNWKSTATE", data, length))
	{
		uint8_t nwk_state = app_get_network_state();

		uint8_t tc_link_state = app_tc_link_plugin_get_link_state();

		app_serial_port_printf(port, "\r\n[AT CMD]Network state %d, tc link state %d", nwk_state, tc_link_state);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+APPSCAN", data, length))
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Scan command, %d, %d, %s", 0xff, 120, "TRUE");

		app_scan_network_v2_start(0xff, 120, true);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+APPLEAVE", data, length))
	{
		uint8_t status = app_leave_network();
		app_serial_port_printf(port, "\r\n[AT CMD]Leave command 0x%x", status);

		return true;
	}

	return false;
}

static void tc_link_state_changed_cb(uint8_t last_state, uint8_t state)
{
	uint32_t current_time = halCommonGetInt32uMillisecondTick();

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[TC LINK]%d->%d, cur time %d", last_state, state, current_time);
}

void app_stack_status_changed_callback(EmberStatus status,
									   EmberNetworkStatus last_network_state,
									   EmberNetworkStatus network_state)
{
	if(last_network_state != network_state)
	{
		uint32_t current_time = halCommonGetInt32uMillisecondTick();

		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[NWK STATE]%d->%d, cur time %d", last_network_state, network_state, current_time);
	}
}

void app_plugin_init_callback(void)
{
	app_at_command_handle_register(user_at_command_handler);

	app_reporting_plugin_reporting_config_register										//定时上报注册，可选，使设备支持定时上报（心跳包）
	(
		 1, true, (APP_HEARTBEAT_MAX_PERIOD_S - APP_HEARTBEAT_MIN_PERIOD_S),																	//共1个配置，随机增加0 ~ 120s的心跳延迟
		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (APP_HEARTBEAT_MIN_PERIOD_S), 0			//配置 cluster 0x0000, attr 0x0000, 4-6分钟心跳
	);

	app_tc_link_plugin_link_state_monitor_v2_register(true, 3, false, 5000, tc_link_state_changed_cb, true);
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

#endif

#endif


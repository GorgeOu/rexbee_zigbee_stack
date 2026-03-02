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

#if defined(RZ_STACK_NWK_MGMT_API_USAGE)

#warning "network management api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

// Key plugin: 25 means each count++ takes 25ms, and 250 means that after 250 counts it will stop incrementing upward.
#define APP_BUTTON_EVENT_LOOP_PERIOD_MS 25
#define APP_BUTTON_INVALID_COUNTS		250
#define APP_BUTTON_DEBOUNCE_COUNTS		2

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_NWK_MGMT_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_NWK_MGMT_USAGE",
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

static void scan_network_event_callback(app_scan_network_event_enum_t event)
{
	if(event == APP_SCAN_NETWORK_EVENT_INIT)
	{
		 debugPortAll("\r\n[SCAN]Scan init.");
	}
	else if( (event == APP_SCAN_NETWORK_EVENT_JOINED) ||
			 (event == APP_SCAN_NETWORK_EVENT_ZBCK_JOINED) )
	{
		debugPortAll("\r\n[SCAN]Scan joined.");
	}
	else if(event == APP_SCAN_NETWORK_EVENT_TIMEOUT)
	{
		debugPortAll("\r\n[SCAN]Scan timeout.");
	}
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if(util_match_uart_command_fixed_length("AT+GETNWKSTATE", data, length))
	{
		uint8_t nwk_state = app_get_network_state();

		uint8_t backup_nwk_state = app_get_backup_network_state();

		app_serial_port_printf(port, "\r\n[AT CMD]Network state %d, backup network state %d", nwk_state, backup_nwk_state);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+APPSCAN", data, length))
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Scan command, %d, %d, %s", 0xff, 120, "TRUE");

		app_scan_network_v3_start(120, true, 0, scan_network_event_callback);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+APPLEAVE", data, length))
	{
		uint8_t status = app_leave_network();
		app_serial_port_printf(port, "\r\n[AT CMD]Leave command 0x%x", status);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+BACKUPNWK", data, length))
	{
		app_backup_current_network_token_data();

		app_serial_port_printf(port, "\r\n[AT CMD]Backup current network");

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+BACKUPNWKCLEAR", data, length))
	{
		app_clear_backup_network_token_data();

		app_serial_port_printf(port, "\r\n[AT CMD]Clear backup network");

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+BACKUPNWKRECOVER", data, length))
	{
		EmberStatus status = app_recover_network_from_backup_data();

		app_serial_port_printf(port, "\r\n[AT CMD]Recover backup network, status 0x%x", status);

		return true;
	}

	return false;
}

void app_plugin_init_callback(void)
{
	app_at_command_handle_register(user_at_command_handler);
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

void app_device_network_start_callback(uint8_t event)
{
	//we can report here, after joined or reboot(joined)

	debugPortAll("\r\n[NWM MGMT]Network start, event %d", event);
}

void app_device_network_leaved_callback(uint8_t event)
{
	debugPortAll("\r\n[NWM MGMT]Leaved, event %d", event);
}

#endif

#endif


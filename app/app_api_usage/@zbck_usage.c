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

#if defined(RZ_STACK_ZBCK_API_USAGE)

#warning "zbck api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_ZBCK_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_ZBCK_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

void app_hal_uart_config(void)
{
	app_serial_init(TYPE_VCP_SERIAL,
					PORTD_PIN(2),
					0,
					115200,
					0,
					0);

	app_serial_init(TYPE_UART_SERIAL,
					APP_UART_TX_PIN,
					APP_UART_RX_PIN,
					APP_UART_BAUDRATE,
					UART_PARITY_NONE,
					1);
}

static void _zbck_handshake_event_callback(uint8_t state)
{
	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[ZBCK]Handshake event state %d", state);
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
	if(util_match_uart_command_fixed_length("AT+APPSCAN", data, length))
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Scan command, %d, %d, %s", 0xff, 120, "TRUE");

		app_scan_network_v3_start(120, true, APP_SCAN_NETWORK_OPT_ALTER_WITH_HANDSHAKE_BR_2_1, scan_network_event_callback);

		return true;
	}

	if(util_strncmp("AT+ZBCKNOTIFY", (const char* )data, 13) == 0)
	{
		stack_zbck_device_send_default_handshake_notify(_zbck_handshake_event_callback);

		app_serial_port_printf(port, "\r\n[AT CMD]ZBCK notify start");

		return true;
	}

	if( (util_strncmp("AT+ZBCKMODE=", (const char* )data, 12) == 0) && (length > 12) )
	{
		uint8_t mode = (uint8_t)util_dec_string_to_signed_int(data + 12, length - 12);

		stack_set_zbck_secure_mode(mode);

		app_serial_port_printf(port, "\r\n[AT CMD]Set ZBCK mode to %d", mode);

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
	app_version_printf(TYPE_VCP_SERIAL);
	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

#endif

#endif


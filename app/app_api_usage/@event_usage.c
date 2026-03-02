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

#if defined(RZ_STACK_EVENT_API_USAGE)

#warning "event api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_EVENT_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_EVENT_USAGE",
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

static const char* oneshot_event_tag 	= "This is oneshot event";
static const char* loop_event_tag 		= "This is loop event";
static const char* condition_event_tag  = "This is condition event";

static uint8_t s_event_test_oneshot = 0xff;
static uint8_t s_event_test_loop    = 0xff;
static uint8_t s_event_test_condition = 0xff;

static int oneshot_event_handler(void* args)
{
	char* tag = (char* )args;

	uint32_t current_tick_ms = halCommonGetInt32uMillisecondTick();

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[EVENT]%s : %l", tag, current_tick_ms);

	app_event_v3_cancel(&s_event_test_oneshot);

	return -1;
}

static int loop_event_handler(void* args)
{
	char* tag = (char* )args;

	uint32_t current_tick_ms = halCommonGetInt32uMillisecondTick();

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[EVENT]%s: %l", tag, current_tick_ms);

	//1000ms loop
	return 1000;
}

static int condition_event_handler(void* args)
{
	char* tag = (char* )args;

	uint32_t current_tick_ms = halCommonGetInt32uMillisecondTick();

	if(current_tick_ms > 10000)
	{
		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[EVENT]%s: %l, stopped", tag, current_tick_ms);

		app_event_v3_cancel(&s_event_test_condition);

		return -1;
	}

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[EVENT]%s: %l", tag, current_tick_ms);

	//1000ms loop
	return 1000;
}


static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if(util_strncmp("AT+CANCELLOOP", (const char* )data, 13) == 0)
	{
		app_event_v3_cancel(&s_event_test_loop);

		app_serial_port_printf(port, "\r\n[AT CMD]Cancel loop event");

		return true;
	}

	if(util_strncmp("AT+RESTARTLOOP", (const char* )data, 14) == 0)
	{
		//Trigger after 500ms
		app_event_v3_register(true, &s_event_test_loop, 500, loop_event_handler, (void* )loop_event_tag);

		uint32_t current_tick_ms = halCommonGetInt32uMillisecondTick();

		app_serial_port_printf(port, "\r\n[AT CMD]Restart loop event at %l", current_tick_ms);

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

	uint32_t current_tick_ms = halCommonGetInt32uMillisecondTick();

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[EVENT]Init event %l", current_tick_ms);

	//Trigger after 5000ms
	app_event_v3_register(true, &s_event_test_oneshot, 5000, oneshot_event_handler, (void* )oneshot_event_tag);

	//Trigger after 2000ms
	app_event_v3_register(true, &s_event_test_loop, 2000, loop_event_handler, (void* )loop_event_tag);

	//run immediately on stack event loop
	app_event_v3_register(true, &s_event_test_condition, 0, condition_event_handler, (void* )condition_event_tag);
}

void app_main_tick_callback(void)
{

}

#endif

#endif


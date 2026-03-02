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

#if defined(RZ_STACK_BUTTON_API_USAGE)

#warning "button api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

// Key plugin: 25 means each count++ takes 25ms, and 250 means that after 250 counts it will stop incrementing upward.
#define APP_BUTTON_EVENT_LOOP_PERIOD_MS 25
#define APP_BUTTON_INVALID_COUNTS		250
#define APP_BUTTON_DEBOUNCE_COUNTS		2

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_BUTTON_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_BUTTON_USAGE",
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

void user_button_pressed_callback(key_scan_t* key)
{
	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[PRESSED]%d, %d",
											 key->key_id,
											 key->key_hold_on_counts);
}

void user_button_released_callback(key_scan_t* key)
{
	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[RELEASED]%d, %d",
											  key->key_id,
											  key->key_hold_on_counts);

	if(key->key_id == DEVICE_TEST_KEY_ID)
	{
		app_serial_port_printf(TYPE_UART_SERIAL, "\r\nThe test key is released after being held down for %dms",
						  	  	  	  	  	  	  (uint32_t)key->key_hold_on_counts * APP_BUTTON_EVENT_LOOP_PERIOD_MS);
	}
}

void app_plugin_init_callback(void)
{
	// Key plugin: 25 means each count++ takes 25ms, and 250 means that after 250 counts it will stop incrementing upward.

	//buuton plugin depend on HAL_BUTTON_PIN_LIST
	//key_id is the index number in the list

	app_button_plugin_v2_register(APP_BUTTON_EVENT_LOOP_PERIOD_MS,
								  APP_BUTTON_INVALID_COUNTS,
								  APP_BUTTON_DEBOUNCE_COUNTS,
								  user_button_pressed_callback,
								  user_button_released_callback);
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


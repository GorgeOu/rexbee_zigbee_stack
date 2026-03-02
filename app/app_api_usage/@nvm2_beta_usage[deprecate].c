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

#if defined(RZ_STACK_NVM2_API_USAGE)

#warning "nvm2 api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_NVM2_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_NVM2_USAGE",
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

#define USER_TEST_1_NVM2_TAG 1

//note : app_nvm_attribute_storage_plugin_register must be registered within the app_post_token_init_callback
//
//{ 0x0000, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }
//if attribute mask ATTRIBUTE_MASK_TOKENIZE, it will be automatically stored in the nvm when the attribute changes

void app_post_token_init_callback(void)
{
	app_nvm2_plugin_register();
}

static void user_nvs_read_callback(uint16_t id, const uint8_t* data, uint32_t length, void* user_data)
{
	uint8_t port = (uint8_t)user_data;

	app_serial_port_printf(port, "\r\n[%2x]%a", id, data, length);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	//AT+REBOOT (has already imp in the sdk), use AT+REBOOT or power down to reboot chip

	if( (util_strncmp("AT+GETNVMFREE", (const char* )data, 13) == 0) && (length == 13) )
	{
		uint32_t free_space = app_nvm2_get_free_space();

		app_serial_port_printf(port, "\r\n[AT CMD]Nvm2 free space %dB", free_space);

		return true;
	}

	if( (util_strncmp("AT+SETUSERNVM", (const char* )data, 13) == 0) && (length == 13) )
	{
		static uint32_t set_value_add = 1;

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
	    set_value_add++;
		bool result = app_set_user_nvm2_data(USER_TEST_1_NVM2_TAG, (uint8_t* )&set_value_add, sizeof(set_value_add));
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Set nvm2 tag1, result %d, value : %d, time elapsed %dms",
							   result, set_value_add, elapsed_ms);

		return true;
	}

	if( (util_strncmp("AT+SETUSERNVM=", (const char* )data, 14) == 0) && (length > 14) )
	{
		uint32_t set_value = (uint32_t)util_dec_string_to_signed_int(data + 14, length - 14);

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_set_user_nvm2_data(USER_TEST_1_NVM2_TAG, (uint8_t* )&set_value, sizeof(set_value));
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Set nvm2 tag1, result %d, value : %d, time elapsed %dms",
							   result, set_value, elapsed_ms);

		return true;
	}

	if(util_strncmp("AT+GETUSERNVM", (const char* )data, 13) == 0)
	{
		uint32_t get_value   = 0;
		uint32_t read_length = 0;

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_get_user_nvm2_data(USER_TEST_1_NVM2_TAG, (uint8_t* )&get_value, sizeof(get_value), &read_length);
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Get nvm2 tag1, result %d, read length %d, value : %d, time elapsed %dms",
							   result, read_length, get_value, elapsed_ms);

		return true;
	}

	if(util_strncmp("AT+NVMDUMP", (const char* )data, 10) == 0)
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Nvm2 dump");

		app_nvm2_read_all_entries(user_nvs_read_callback, (void* )port);

		return true;
	}

	if(util_strncmp("AT+NVMHISTDUMP", (const char* )data, 14) == 0)
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Nvm2 dump with history");

		app_nvm2_read_all_entries_with_history(user_nvs_read_callback, (void* )port);

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

#endif

#endif


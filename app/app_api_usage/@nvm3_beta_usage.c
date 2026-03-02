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

#if defined(RZ_STACK_NVM3_API_USAGE)

#warning "nvm3 api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_NVM3_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_NVM3_USAGE",
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

#define USER_TEST_1_NVM3_TAG 1
#define USER_TEST_2_NVM3_TAG "1234567890"
#define USER_TEST_3_NVM3_TAG "ABCDEFGHIJ"

//note : app_nvm_attribute_storage_plugin_register must be registered within the app_post_token_init_callback
//
//{ 0x0000, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }
//if attribute mask ATTRIBUTE_MASK_TOKENIZE, it will be automatically stored in the nvm when the attribute changes

void app_post_token_init_callback(void)
{
	app_nvm3_attribute_storage_plugin_register();
}

static void user_nvm3_read_callback(const char *key_id, uint8_t key_size, const uint8_t* data, uint32_t length, void* user_data)
{
	uint8_t port = (uint8_t)(uintptr_t)user_data;

	app_serial_port_printf(port, "\r\n[%b]%a", key_id, key_size, data, length);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	uint8_t content[128];

	//AT+REBOOT (has already imp in the sdk), use AT+REBOOT or power down to reboot chip

	if( (util_strncmp("AT+SETTOKENATTR=", (const char* )data, 16) == 0) && (length > 16) )
	{
		uint8_t set_value = ((uint8_t)util_dec_string_to_signed_int(data + 16, length - 16)) ? 1 : 0;

		app_write_server_attribute(1,
								   ZCL_ON_OFF_CLUSTER_ID,
								   ZCL_ON_OFF_ATTRIBUTE_ID,
								   0x0000,
								   (uint8_t*)&set_value,
								   ZCL_BOOLEAN_ATTRIBUTE_TYPE);

		app_serial_port_printf(port, "\r\n[AT CMD]Set onoff attr to %d", set_value);

		return true;
	}

	if(util_strncmp("AT+GETTOKENATTR", (const char* )data, 15) == 0)
	{
		uint8_t get_value;

		app_read_server_attribute(1,
								  ZCL_ON_OFF_CLUSTER_ID,
								  ZCL_ON_OFF_ATTRIBUTE_ID,
								  0x0000,
								  (uint8_t*)&get_value,
								  sizeof(get_value));

		app_serial_port_printf(port, "\r\n[AT CMD]Get onoff attr, value : %d", get_value);

		return true;
	}


	if( (util_strncmp("AT+GETNVMFREE", (const char* )data, 13) == 0) && (length == 13) )
	{
		uint32_t free_space = app_nvm3_get_free_space();

		app_serial_port_printf(port, "\r\n[AT CMD]Nvm2 free space %dB", free_space);

		return true;
	}

	if( (util_strncmp("AT+SETUSERNVM", (const char* )data, 13) == 0) && (length == 13) )
	{
		static uint32_t set_value_add = 1;

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
	    set_value_add++;
		bool result = app_set_user_nvm3_data(USER_TEST_1_NVM3_TAG, (uint8_t* )&set_value_add, sizeof(set_value_add));
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Set nvm3 tag1, result %d, value : %d, time elapsed %dms",
							   result, set_value_add, elapsed_ms);

		return true;
	}

	if( (util_strncmp("AT+SETUSERNVM=", (const char* )data, 14) == 0) && (length > 14) )
	{
		uint32_t set_value = (uint32_t)util_dec_string_to_signed_int(data + 14, length - 14);

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_set_user_nvm3_data(USER_TEST_1_NVM3_TAG, (uint8_t* )&set_value, sizeof(set_value));
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Set nvm3 tag1, result %d, value : %d, time elapsed %dms",
							   result, set_value, elapsed_ms);

		return true;
	}

	if( (util_strncmp("AT+GETUSERNVM", (const char* )data, 13) == 0) && (length == 13) )
	{
		uint32_t get_value   = 0;
		uint32_t read_length = 0;

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_get_user_nvm3_data(USER_TEST_1_NVM3_TAG, (uint8_t* )&get_value, sizeof(get_value), &read_length);
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Get nvm3 tag1, result %d, read length %d, value : %d, time elapsed %dms",
							   result, read_length, get_value, elapsed_ms);

		return true;
	}

	if( (util_strncmp("AT+SETUSERNVM2", (const char* )data, 14) == 0) && (length == 14) )
	{
		static uint8_t set_value = 1;

		set_value++;

		MEMSET(content, set_value, sizeof(content));

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_set_nvm3_data(USER_TEST_2_NVM3_TAG, util_strnlen(USER_TEST_2_NVM3_TAG, 16), (uint8_t* )content, sizeof(content));
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Set nvm3 tag2, result %d, value : %d(len %d), time elapsed %dms",
							   result, set_value, sizeof(content), elapsed_ms);

		return true;
	}

	if( (util_strncmp("AT+GETUSERNVM2", (const char* )data, 14) == 0) && (length == 13) )
	{
		uint32_t read_length = 0;

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_get_nvm3_data(USER_TEST_2_NVM3_TAG, util_strnlen(USER_TEST_2_NVM3_TAG, 16), (uint8_t* )content, sizeof(content), &read_length);
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Get nvm3 tag2, result %d, read length %d, value : %d, time elapsed %dms",
							   result, read_length, content[0], elapsed_ms);

		return true;
	}

	if( (util_strncmp("AT+SETUSERNVM3", (const char* )data, 14) == 0) && (length == 14) )
	{
		static uint8_t set_value = 0xD0;

		set_value++;

		MEMSET(content, set_value, sizeof(content));

	    uint32_t start_ms = halCommonGetInt32uMillisecondTick();
		bool result = app_set_nvm3_data(USER_TEST_3_NVM3_TAG, util_strnlen(USER_TEST_3_NVM3_TAG, 16), (uint8_t* )content, sizeof(content));
		uint32_t elapsed_ms = halCommonGetInt32uMillisecondTick() - start_ms;

		app_serial_port_printf(port, "\r\n[AT CMD]Set nvm3 tag3, result %d, value : %d(len %d), time elapsed %dms",
							   result, set_value, sizeof(content), elapsed_ms);

		return true;
	}

	if(util_strncmp("AT+NVMDUMP", (const char* )data, 10) == 0)
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Nvm3 dump");

		app_nvm3_read_all_entries(user_nvm3_read_callback, (void* )(uintptr_t)port);

		return true;
	}

	if(util_strncmp("AT+NVMHISTDUMP", (const char* )data, 14) == 0)
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Nvm3 dump with history");

		app_nvm3_read_all_entries_with_history(user_nvm3_read_callback, (void* )(uintptr_t)port);

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


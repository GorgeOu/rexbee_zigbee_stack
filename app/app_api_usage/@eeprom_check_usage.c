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

#if defined(RZ_STACK_EEPROM_CHECK_API_USAGE)

#warning "eeprom check api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_EEPROM_CHECK_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_EEPROM_CHECK_USAGE",
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
	uint8_t content[128];

	if( (util_strncmp("AT+TOKENDUMP", (const char* )data, 12) == 0) && (length ==  12) )
	{
		eeprom_list_current_printf(port, true);

		return true;
	}

	if( (util_strncmp("AT+TOKENDUMPALL", (const char* )data, 15) == 0) && (length ==  15) )
	{
		eeprom_list_raw_printf(port, true);

		return true;
	}

	if( (util_strncmp("AT+TOKENCHECK", (const char* )data, 13) == 0) && (length ==  13) )
	{
		eeprom_list_check_printf(port);

		uint16_t err_id = 0;

		if(eeprom_chain_integrity_check(&err_id))
		{
			app_serial_port_printf(port, "\r\n[AT CMD]Chain integrity check pass");
		}
		else
		{
			app_serial_port_printf(port, "\r\n[AT CMD]Chain integrity check failed, id %d, err code %d", err_id, eeprom_check_id_chain(err_id));
		}

		return true;
	}

	if( (util_strncmp("AT+TOKENPAGEINFO", (const char* )data, 16) == 0) && (length ==  16) )
	{
		eeprom_list_page_info_printf(port);

		return true;
	}

	if( (util_strncmp("AT+CIBDUMP", (const char* )data, 10) == 0) && (length ==  10) )
	{
		cib_list_printf(port);

		return true;
	}

	if( (util_strncmp("AT+TOKENSET=", (const char* )data, 12) == 0) && (length ==  16) )
	{
		uint16_t id = atoh_build_int16u(true, data + 12);

		static uint32_t s_value = 1;

		MEMSET(content, s_value, sizeof(content));

		bool result = halCommonSetIndexedToken(id, 0, content);

		app_serial_port_printf(port, "\r\n[AT CMD]Set token 0x%2x, result %d, value %d", id, result, s_value);

		s_value++;
	}

	if( (util_strncmp("AT+TOKENGET=", (const char* )data, 12) == 0) && (length == 16) )
	{
		uint16_t id = atoh_build_int16u(true, data + 12);

		bool result = halCommonGetIndexedToken(content, id, 0);

		app_serial_port_printf(port, "\r\n[AT CMD]Get token 0x%2x, result %d, value %a", id, result, content, sizeof(content));
	}

	if( (util_strncmp("AT+TOKENDUMP=", (const char* )data, 13) == 0) && (length ==  17) )
	{
		uint16_t id = atoh_build_int16u(true, data + 13);

		eeprom_dump_dest_id_data(port, true, id, 0, 0);

		eeprom_dump_dest_id_data(port, false, id, 0, 0);

		return 0;
	}

	if ( ( MEMCOMPARE( data, "AT+TOKENPAGECHECK=", 18) == 0 ) &&
		 ( length == 20 ) )
	{
		uint8_t id = util_atoh(data + 12);

		eeprom_list_page_check(port, id);

		return 0;
	}

	if ( ( MEMCOMPARE( data, "AT+TOKENPAGECHECK=", 18) == 0 ) &&
		 ( length == 20 ) )
	{
		uint8_t id = util_atoh(data + 12);

		eeprom_list_page_check(port, id);

		return 0;
	}

	if( (util_strncmp("AT+DVT", (const char* )data, 6) == 0) && (length == 6) )
	{
		sim_eep_full_test(port);
		testBindTableFull(port);

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


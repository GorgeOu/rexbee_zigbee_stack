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

#if defined(RZ_STACK_EASY_TOKEN_API_USAGE)

#warning "easy token api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_EASY_TOKEN_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_EASY_TOKEN_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

typedef struct
{
	uint32_t value1;
    uint8_t  value2;
    uint8_t  reserved[43]; //Reserved, struct size must be 48
} user_token_def_t;

CT_ASSERT((sizeof(user_token_def_t) == APP_GLOBAL_TOKEN_DATA_SIZE), EASY_TOKEN);

user_token_def_t* g_token_def = (user_token_def_t*)g_app_global_token_data;

void app_get_token_data_to_ram_callback(void)
{
    if (!app_is_global_token_data_used())
    {
        //If token uninit, set default token value
        MEMSET((uint8_t*)g_token_def, 0, APP_GLOBAL_TOKEN_DATA_SIZE);

        g_token_def->value1 = 12345678;
        g_token_def->value2 = 1;

        app_set_global_token_data((uint8_t*)g_token_def);
    }

    //Get token data to user ram
    app_get_global_token_data((uint8_t*)g_token_def);
}

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
	//AT+REBOOT (has already imp in the sdk), use AT+REBOOT or power down to reboot chip

	if(util_strncmp("AT+GETEASYTOKEN", (const char* )data, 15) == 0)
	{
		app_get_global_token_data((uint8_t*)g_token_def);

		app_serial_port_printf(port, "\r\n[AT CMD]Token value1 : %d, value2 : %d",
							   g_token_def->value1, g_token_def->value2);

		return true;
	}

	if( (util_strncmp("AT+SETEASYTOKEN=", (const char* )data, 16) == 0) && (length > 16) )
	{
		uint32_t set_value = (uint32_t)util_dec_string_to_signed_int(data + 16, length - 16);

		g_token_def->value1 = set_value;

		app_set_global_token_data((uint8_t*)g_token_def);

		app_serial_port_printf(port, "\r\n[AT CMD]Set token value1 to %d", g_token_def->value1);

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


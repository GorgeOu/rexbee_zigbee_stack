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

#if defined(RZ_STACK_UART_API_USAGE)

#warning "uart api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_UART_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_UART_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

//Excepted message hex : 55 04 11 22 33 44 AA
#define SIMPLE_CHECK_HEADER 		0x55
#define SIMPLE_CHECK_LENGTH 		0x04
#define SIMPLE_CHECK_FOOTER		 	0xAA
#define SIMPLE_MIN_FRAME_LENGTH 	0x03

//e.g.
//1. input hex : 55 04 11 22 33 44 AA
//[VALIDATE]Port 1, data(3) : 55 04 11
//[VALIDATE]Port 1, data(4) : 55 04 11 22
//[VALIDATE]Port 1, data(5) : 55 04 11 22 33
//[VALIDATE]Port 1, data(6) : 55 04 11 22 33 44
//[VALIDATE]Port 1, data(7) : 55 04 11 22 33 44 AA
//[ON PACKET]Port 1, validate pass or timeout(validate pass), data(7) : 55 04 11 22 33 44 AA

//2. input hex : 00 FF 55 04 11 22 33 44 55 55 55 04 11 22 33 44 AA 00 11 55 04 11 22 33 44 AA 00 11
//[VALIDATE]Port 1, data(3) : 00 FF 55
//[VALIDATE]Port 1, data(3) : FF 55 04
//[VALIDATE]Port 1, data(3) : 55 04 41
//[VALIDATE]Port 1, data(4) : 55 04 41 54
//[VALIDATE]Port 1, data(5) : 55 04 41 54 2B
//[VALIDATE]Port 1, data(6) : 55 04 41 54 2B 44
//[VALIDATE]Port 1, data(7) : 55 04 41 54 2B 44 55
//[VALIDATE]Port 1, data(6) : 04 41 54 2B 44 55
//[VALIDATE]Port 1, data(5) : 41 54 2B 44 55
//[VALIDATE]Port 1, data(4) : 54 2B 44 55
//[VALIDATE]Port 1, data(3) : 2B 44 55
//[VALIDATE]Port 1, data(3) : 44 55 55
//[VALIDATE]Port 1, data(3) : 55 55 55
//[VALIDATE]Port 1, data(4) : 55 55 55 04
//[VALIDATE]Port 1, data(5) : 55 55 55 04 11
//[VALIDATE]Port 1, data(6) : 55 55 55 04 11 22
//[VALIDATE]Port 1, data(7) : 55 55 55 04 11 22 33
//[VALIDATE]Port 1, data(6) : 55 55 04 11 22 33
//[VALIDATE]Port 1, data(7) : 55 55 04 11 22 33 44
//[VALIDATE]Port 1, data(6) : 55 04 11 22 33 44
//[VALIDATE]Port 1, data(7) : 55 04 11 22 33 44 AA
//[ON PACKET]Port 1, validate pass or timeout(validate pass), data(7) : 55 04 11 22 33 44 AA
//[VALIDATE]Port 1, data(3) : 00 11 55
//[VALIDATE]Port 1, data(3) : 11 55 04
//[VALIDATE]Port 1, data(3) : 55 04 11
//[VALIDATE]Port 1, data(4) : 55 04 11 22
//[VALIDATE]Port 1, data(5) : 55 04 11 22 33
//[VALIDATE]Port 1, data(6) : 55 04 11 22 33 44
//[VALIDATE]Port 1, data(7) : 55 04 11 22 33 44 AA
//[ON PACKET]Port 1, validate pass or timeout(validate pass), data(7) : 55 04 11 22 33 44 AA

//3. input hex : 00 12 34 56 78
//[VALIDATE]Port 1, data(3) : 00 12 34
//[VALIDATE]Port 1, data(3) : 12 34 56
//[VALIDATE]Port 1, data(3) : 34 56 78

static serial_validate_result_t serial_validate_packet(uint8_t port, uint8_t* data, uint32_t* length)
{
	if(port == TYPE_UART_SERIAL)
	{
		if(*length < SIMPLE_MIN_FRAME_LENGTH)
		{
			return SERIAL_VALIDATE_RESULT_IN_PROGRESS;
		}

		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[VALIDATE]Port %d, data(%d) : %a", port, *length, data, *length);

		if(data[0] != SIMPLE_CHECK_HEADER)
		{
			return SERIAL_VALIDATE_RESULT_1B_DROPPED;
		}

		if(*length >= (SIMPLE_CHECK_LENGTH + 3))
		{
			if(data[SIMPLE_CHECK_LENGTH + 2] == SIMPLE_CHECK_FOOTER)
			{
				return SERIAL_VALIDATE_RESULT_SUCCESS;
			}

			return SERIAL_VALIDATE_RESULT_1B_DROPPED;
		}

		return SERIAL_VALIDATE_RESULT_IN_PROGRESS;
	}

	return SERIAL_VALIDATE_RESULT_UNHANDLED;
}

static void serial_on_packet_received(bool is_timeout, uint8_t port, uint8_t* data, uint32_t length)
{
	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[ON PACKET]Port %d, validate pass or timeout(%s), data(%d) : %a",
					  port, is_timeout ? "timeout" : "validate pass", length, data, length);
}

void app_hal_uart_config(void)
{
	app_serial_init(TYPE_UART_SERIAL,
					APP_UART_TX_PIN,
					APP_UART_RX_PIN,
					APP_UART_BAUDRATE,
					UART_PARITY_NONE,
					1);

	app_serial_callback_register(TYPE_UART_SERIAL, false, serial_validate_packet, serial_on_packet_received);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if(util_strncmp("AT+SENDHEX", (const char* )data, 10) == 0)
	{
		uint8_t send_hex[] = {0x11, 0x22, 0x33, 0x44};

		app_serial_port_write_data(port, send_hex, sizeof(send_hex));

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


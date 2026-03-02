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

#if defined(RZ_STACK_CLI_API_USAGE)

#warning "cli api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_CLI_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_CLI_USAGE",
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

void app_plugin_init_callback(void)
{
	app_command_line_plugin_register();
	app_command_line_enable(true);

	//if command line disable, type AT+REXCLI=<cli input\r\n>
	//if command line enable, type <cli input\r\n>

	//e.g. 1
	//uart input : help
	//uart output:
	/*
	 /-----------------------------------------------------------------------------\
	| /--------------------------------------------------------------------------\ |
	| |                                                                          | |
	| |          ,------.                                                        | |
	| |          |  .--. ' ,---. ,--.  ,--.,---. ,--,--,  ,---.  ,---.           | |
	| |          |  '--'.'| .-. : \  `'  /| .-. :|      \(  .-' | .-. :          | |
	| |          |  |\  \ \   --. /  /.  \\   --.|  ||  |.-'  `)\   --.          | |
	| |          `--' '--' `----''--'  '--'`----'`--''--'`----'  `----'          | |
	| |                                     Z I G B E E     S T A C K            | |
	| |                                                                          | |
	| |   REV : V 1.0.0                                                          | |
	| |                                                                          | |
	| ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	| ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	| |Usage:
	| |<x>: input 12 or 0x1A, x means x bytes of data
	| |<string(x)>: "123" or {1A 1B 1C}, (x) means input x bytes,
	| |             if haven't (x) means variable string
	| |help -
	| |hal... -
	| |print... -
	| |child -
	| |zcl... -
	| |zigbee... -
	| |stack... -
	| |watch... -
	| |upgrade - via uart xmodem
	| |reboot -
	| \--------------------------------------------------------------------------/ |
	 \-----------------------------------------------------------------------------/
	*/
	//e.g. 2
	//uart input : stack info
	//uart output:
	//	[STACK INFO]Info
	//	   stack/sdk ver    : V3.0.0d2/V3.0.5
	//	   signature        : AUTHORIZED VERSION
	//	   system(clock, ms): (83352616,5209)
	//	   stack date code  : 2025/07/21 14:50:27
	//	   app date code    : 2025/07/22 13:57:04
	//	   mac(big-endian)  : C4 98 94 FF FE CF 76 9B
	//	   mass prod test   : 0x00, (2000/01/01 00:00:00 - 0xFF)
	//	   node type        : router(2)
	//	   stack state      : no network(0x00, 0x00, 0x00)
	//	   node id          : 0xFFFF
	//	   channel          : (0x0B, 0x0B), idle
	//	   radio power      : 10
	//	   radio mode       : rx[](0x01, 0x65, 0x3F)
	//	   security level   : 0x05
	//	   lqi rssi         : 0, 0
	//	   pan id           : 0xFFFF
	//	   extended pan id  : FF FF FF FF FF FF FF FF
	//	   secure mode      : global
	//	   trust center mac : FF FF FF FF FF FF FF FF
	//	   parent node & fc : 0xFFFF, 0x00000000
	//	   parent mac       : FF FF FF FF FF FF FF FF
	//	   install code     : FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF - FFFF
	//	   frame counter    : 0x00000000, 0x00000000
	//	   network key      : [0] - FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
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


#if defined(RZ_STACK_MFG_LIB_DEMO)
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
#include "../include/global_apis.h"
#include "mfglib.h"

#define debugPortAll(format,...)

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_Mfglib_Demo",
	.model_id							= "MFGLIB",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

PhyLayerRegisterCallback appRegisterPhyLayerCallbacks = { NULL, };
RexUniversalLibRegisterCallback rexUniversalLibCallbacksRegister = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, };

const eeprom_default_data_t* c_eeprom_default_data = NULL;
const uint16_t c_eeprom_default_data_counts = 0;

hal_fixed_gpio_list_t g_hal_fixed_gpio_list[] 	 = {{0}};
uint16_t 			  g_hal_fixed_gpio_list_size = 0;

hal_fixed_gpio_ext_cfg_list_t g_hal_fixed_gpio_ext_cfg_list[]	 = {{0}};
uint16_t 					  g_hal_fixed_gpio_ext_cfg_list_size = 0;

void app_hal_uart_config(void)
{
	app_serial_init(TYPE_VCP_SERIAL,
					APP_SW_TX_PIN,
					0,
					APP_SW_BAUDRATE,
					0,
					0);

	app_serial_init(TYPE_UART_SERIAL,
					APP_UART_TX_PIN,
					APP_UART_RX_PIN,
					APP_UART_BAUDRATE,
					UART_PARITY_NONE,
					1);
}

void mfglib_rx_callback(uint8_t *packet, uint8_t linkQuality, int8_t rssi)
{
	//app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[RX][%d,%d]%a", rssi, linkQuality, packet, packet[0] + 1);
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_VCP_SERIAL);

	app_version_printf(TYPE_UART_SERIAL);

	mfglibStart(mfglib_rx_callback);
}

void app_main_tick_callback(void)
{

}

void app_process_uart_data(uint8_t* data, uint8_t length)
{
	if(util_match_uart_command_fixed_length("AT+MFGLIBTONESTART", data, length))
	{
		mfglibStartTone();

		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[TONE]Start");

		return;
	}

	if(util_match_uart_command_fixed_length("AT+MFGLIBTONESTOP", data, length))
	{
		mfglibStopTone();

		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[TONE]Stop");

		return;
	}
}

#endif

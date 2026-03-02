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

#if defined(RZ_STACK_SIM_I2C_API_USAGE)

#warning "sim i2c api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_SIM_I2C_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_SIM_I2C_USAGE",
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

void app_hal_config(void)
{
	hal_sim_i2c_gpio_init(PORTB_PIN(7), PORTC_PIN(2), 1);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if( (util_strncmp("AT+I2CWB=", (const char* )data, 9) == 0) &&
		( (length > 9) && ((length - 9) % 2 == 0) ) )
	{
		uint8_t write_data[64];

		util_array_atoh(write_data, data + 9, ((length - 9) / 2));

		uint8_t status = hal_sim_i2c_write_iram(0x02, write_data, (length - 9) / 2, 0x11);

		app_serial_port_printf(port, "\r\n[AT CMD]I2C write bytes, status 0x%x, data : %a",
							   status, write_data, ((length - 9) / 2));

		return true;
	}

	if(util_strncmp("AT+I2CRB", (const char* )data, 8) == 0)
	{
		uint8_t read_data[4];

		uint8_t status = hal_sim_i2c_read_iram(0x02, read_data, sizeof(read_data), 0x11);

		app_serial_port_printf(port, "\r\n[AT CMD]I2C read bytes, status 0x%x, data : %a", status, read_data, sizeof(read_data));

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


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

#if defined(RZ_STACK_GPIO_API_USAGE)

#warning "gpio api demo"

#define APP_RELEASE_VERSION "1.0.0"

#define APP_TEST_GPIO_OUT PORTA_PIN(0)
#define APP_TEST_GPIO_IN  PORTA_PIN(1)

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_GPIO_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_GPIO_USAGE",
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
	if(util_strncmp("AT+GPIOL", (const char* )data, 8) == 0)
	{
		app_hal_gpio_clear(APP_TEST_GPIO_OUT);

		app_serial_port_printf(port, "\r\n[AT CMD]Gpio out low");

		return true;
	}

	if(util_strncmp("AT+GPIOH", (const char* )data, 8) == 0)
	{
		app_hal_gpio_set(APP_TEST_GPIO_OUT);

		app_serial_port_printf(port, "\r\n[AT CMD]Gpio out high");

		return true;
	}

	if(util_strncmp("AT+GPIOT", (const char* )data, 8) == 0)
	{
		app_hal_gpio_toggle(APP_TEST_GPIO_OUT);

		app_serial_port_printf(port, "\r\n[AT CMD]Gpio out toggle");

		return true;
	}


	if(util_strncmp("AT+GPIOGET", (const char* )data, 10) == 0)
	{
		bool level = app_hal_gpio_read(APP_TEST_GPIO_IN);

		app_serial_port_printf(port, "\r\n[AT CMD]Gpio read %d", level);
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

	app_hal_gpio_config(APP_TEST_GPIO_OUT, GPIOCFG_OUT,   false);
	app_hal_gpio_config(APP_TEST_GPIO_IN, GPIOCFG_IN_PUD, false);

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[GPIO]Init");
}

void app_main_tick_callback(void)
{

}

#endif

#endif


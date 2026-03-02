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

#if defined(RZ_STACK_FAST_GPIO_API_USAGE)

#warning "fast gpio api demo"

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_FAST_GPIO_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_FAST_GPIO_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

static hal_fast_gpio_t s_fg_out_test;
static hal_fast_gpio_t s_fg_in_test;

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
		hal_fast_gpio_clear(&s_fg_out_test);

		app_serial_port_printf(port, "\r\n[AT CMD]Fast gpio out low");

		return true;
	}

	if(util_strncmp("AT+GPIOH", (const char* )data, 8) == 0)
	{
		hal_fast_gpio_set(&s_fg_out_test);

		app_serial_port_printf(port, "\r\n[AT CMD]Fast gpio out high");

		return true;
	}

	if(util_strncmp("AT+GPIOT", (const char* )data, 8) == 0)
	{
		hal_fast_gpio_toggle(&s_fg_out_test);

		app_serial_port_printf(port, "\r\n[AT CMD]Fast gpio out toggle");

		return true;
	}


	if(util_strncmp("AT+GPIOGET", (const char* )data, 10) == 0)
	{
		bool level = hal_fast_gpio_read(&s_fg_in_test);

		app_serial_port_printf(port, "\r\n[AT CMD]Fast gpio read %d", level);
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

	hal_fast_gpio_init(&s_fg_out_test, PORTA_PIN(1));
	hal_fast_gpio_dir(&s_fg_out_test, 1);

	hal_fast_gpio_init(&s_fg_in_test, PORTA_PIN(0));
	hal_fast_gpio_dir(&s_fg_in_test, 0);

	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[FAST GPIO]Init");
}

void app_main_tick_callback(void)
{

}

#endif

#endif


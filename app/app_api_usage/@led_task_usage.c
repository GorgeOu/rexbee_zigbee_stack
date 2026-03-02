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

#if defined(RZ_STACK_LED_TASK_API_USAGE)

#warning "led task api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_LED_TASK_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_LED_TASK_USAGE",
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

//led task depend on HAL_CONTROL_PIN_LIST
//control_pin_list_index is the index number in the list

#define LED_TASK_1_PRIORITY			0
#define LED_TASK_2_PRIORITY			0
#define LED_TASK_3_PRIORITY			1

static const led_list_t _led_slow_blink[] =
{
	{CONTROL_ACTION_ON,  1000},
	{CONTROL_ACTION_OFF, 1000},
	{CONTROL_ACTION_END, 0},
};

static  const led_list_t _led_fast_blink[] =
{
	{CONTROL_ACTION_ON,  100},
	{CONTROL_ACTION_OFF, 100},
	{CONTROL_ACTION_END, 0},
};

static  const led_list_t _led_1s_on[] =
{
	{CONTROL_ACTION_ON, 	1000},
	{CONTROL_ACTION_OFF, 	50},
	{CONTROL_ACTION_END,	0},
};


void app_control_pin_no_led_task_callback(uint8_t control_pin_list_index)
{
	if(control_pin_list_index == DEVICE_TEST_LED_ID)
	{
		//led task end, turn on led
		app_control_pin_action(DEVICE_TEST_LED_ID, CONTROL_ACTION_ON);
	}
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if(util_match_uart_command_fixed_length("AT+LEDTASK1", data, length))
	{
		app_add_led_task(DEVICE_TEST_LED_ID, _led_slow_blink, 60000, 0xff, LED_TASK_1_PRIORITY, true);

		app_serial_port_printf(port, "\r\n[AT CMD]Start led task 1, exec 60000ms");

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+CANCELLEDTASK1", data, length))
	{
		app_cancel_led_task(DEVICE_TEST_LED_ID, _led_slow_blink);

		app_serial_port_printf(port, "\r\n[AT CMD]Cancel _led_slow_blink task");

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+CANCELALLTASK", data, length))
	{
		app_cancel_led_task(DEVICE_TEST_LED_ID, NULL);

		app_serial_port_printf(port, "\r\n[AT CMD]Cancel led id %d, all task", DEVICE_TEST_LED_ID);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+LEDTASK2", data, length))
	{
		app_add_led_task(DEVICE_TEST_LED_ID, _led_fast_blink, 10000, 0xff, LED_TASK_2_PRIORITY, true);

		app_serial_port_printf(port, "\r\n[AT CMD]Start led task 2, exec 10000ms");

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+LEDTASK3", data, length))
	{
		app_add_led_task(DEVICE_TEST_LED_ID, _led_1s_on, 0xffffff, 1, LED_TASK_3_PRIORITY, true);

		app_serial_port_printf(port, "\r\n[AT CMD]Start led task 3, exec once");

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


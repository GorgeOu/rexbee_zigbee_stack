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

#if defined(RZ_STACK_PWM_API_USAGE)

#warning "pwm api demo"

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_PWM_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_PWM_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

#define TEST_PWM_FREQ_HZ 1000

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
	if( (util_strncmp("AT+SETPWMDUTY=", (const char* )data, 14) == 0) && (length > 14) )
	{
		uint8_t duty = (uint8_t)util_dec_string_to_signed_int(data + 11, length - 11);

		app_v2_set_pwm_freq_duty(TEST_PWM_FREQ_HZ, duty, DEVICE_TEST_PWM_ID);

		app_serial_port_printf(port, "\r\n[AT CMD]Set pwm duty %l", duty);
	}

	if(util_strncmp("AT+PWMSTART", (const char* )data, 11) == 0)
	{
		app_v2_pwm_start(DEVICE_TEST_PWM_ID);

		app_serial_port_printf(port, "\r\n[AT CMD]Pwm start");
	}

	if(util_strncmp("AT+PWMSTOP", (const char* )data, 10) == 0)
	{
		app_v2_pwm_stop(DEVICE_TEST_PWM_ID);

		app_serial_port_printf(port, "\r\n[AT CMD]Pwm stop");
	}

	return false;
}

void app_plugin_init_callback(void)
{
	app_at_command_handle_register(user_at_command_handler);

	app_pwm_timer_init();

	app_v2_set_pwm_freq_duty(TEST_PWM_FREQ_HZ, 100, DEVICE_TEST_PWM_ID);

	app_v2_pwm_start(DEVICE_TEST_PWM_ID);
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


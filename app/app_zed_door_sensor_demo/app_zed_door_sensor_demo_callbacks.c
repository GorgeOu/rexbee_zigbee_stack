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

#if defined(RZ_STACK_ZED_DEMO)

#include "../include/global_apis.h"
#include "pin_def.h"

#define  DEFINEEEPTYPE
#include "common/app_sim_eep.h"	//type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#define debugPortAll(format,...)	app_debug_printf(format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

/*  radio tx power
 * 	PAģ��֧��     : [-4,-1,6,10,14,15,16,17,18,19,20],
 *	��PAģ��֧��  : [-10,-9,...,9,10],
 */
app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_ZED_Door_Sensor_Demo_" APP_RELEASE_VERSION,
	.model_id							= "RZ0001",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20, ////����Ϊ20(���ֵ),δʹ��PAʱ���Զ�����Ϊ10(���ֵ)
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

zcl_zone_type_list_t g_user_zone_type_list[] =
{
	{1 , ZCL_IAS_ZONE_TYPE_CONTACT_SWITCH},
};

const led_list_t led_key_pressed_indicate[] =
{
	{CONTROL_ACTION_ON, 	5000},

	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},
	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},

	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},
	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},

	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},
	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},

	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},
	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},

	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},
	{CONTROL_ACTION_OFF, 	250},
	{CONTROL_ACTION_ON, 	250},

	{CONTROL_ACTION_OFF, 	50},

	{CONTROL_ACTION_END,	0},
};

const led_list_t led_fast_blink[] =
{
	{CONTROL_ACTION_ON,  250},
	{CONTROL_ACTION_OFF, 250},
	{CONTROL_ACTION_END, 0},
};

const led_list_t led_slow_blink[] =
{
	{CONTROL_ACTION_ON,  1000},
	{CONTROL_ACTION_OFF, 1000},
	{CONTROL_ACTION_END, 0},
};

const led_list_t led_0_25s_on[] =
{
	{CONTROL_ACTION_ON, 	250},
	{CONTROL_ACTION_OFF, 	50},
	{CONTROL_ACTION_END,	0},
};

const led_list_t led_1s_on[] =
{
	{CONTROL_ACTION_ON, 	1000},
	{CONTROL_ACTION_OFF, 	50},
	{CONTROL_ACTION_END,	0},
};

const led_list_t led_2s_on[] =
{
	{CONTROL_ACTION_ON, 	2000},
	{CONTROL_ACTION_OFF, 	50},
	{CONTROL_ACTION_END,	0},
};

const led_list_t led_turn_off[] =
{
	{CONTROL_ACTION_OFF, 	50},
	{CONTROL_ACTION_END,	0},
};

#define SCAN_LED_TASK_PRIORITY						0 //highest
#define BUTTON_LED_TASK_PRIORITY					1
#define NETWORK_STATE_LED_TASK_PRIORITY				1
#define SENSOR_LED_TASK_PRIORITY					1

#define USER_NO_NETWORK_INDICATE_LED_TASK()		app_add_led_task(DOOR_SENSOR_LED_ID, led_2s_on, 	 0xffffff, 	1,  NETWORK_STATE_LED_TASK_PRIORITY, true)
#define USER_NO_PARENT_INDICATE_LED_TASK()		app_add_led_task(DOOR_SENSOR_LED_ID, led_slow_blink, 0xffffff, 	3,  NETWORK_STATE_LED_TASK_PRIORITY, true)
#define USER_JOINED_NETWORK_INDICATE_LED_TASK()	app_add_led_task(DOOR_SENSOR_LED_ID, led_turn_off, 	 0xffffff, 	1,  NETWORK_STATE_LED_TASK_PRIORITY, true)

#define USER_NETWORK_STATUS_INDICATE_LED_TASK(network_state) \
		do{\
			(network_state == EMBER_JOINED_NETWORK_NO_PARENT) ? \
						   USER_NO_PARENT_INDICATE_LED_TASK() : \
								  ( (network_state == EMBER_JOINED_NETWORK) ? \
									USER_JOINED_NETWORK_INDICATE_LED_TASK() : \
									USER_NO_NETWORK_INDICATE_LED_TASK() );\
		}while(0)

#define USER_SCAN_NETWORK_INDICATE_LED_TASK()			app_add_led_task(DOOR_SENSOR_LED_ID, led_slow_blink, 0xffffff, 	30, SCAN_LED_TASK_PRIORITY, true)
#define USER_SCAN_NETWORK_INDICATE_LED_TASK_CANCEL()	app_cancel_led_task(DOOR_SENSOR_LED_ID, led_slow_blink)

#define BUTTON_INDICATE_LED_TASK()						app_add_led_task(DOOR_SENSOR_LED_ID, led_key_pressed_indicate, 0xffffff, 1, BUTTON_LED_TASK_PRIORITY, true)
#define BUTTON_INDICATE_LED_TASK_CANCEL()				app_cancel_led_task(DOOR_SENSOR_LED_ID, led_key_pressed_indicate)

#define SENSOR_TEMPAR_LED_TASK()						app_add_led_task(DOOR_SENSOR_LED_ID, led_1s_on, 	0xffffff, 1, SENSOR_LED_TASK_PRIORITY, true)
#define SENSOR_ALARM_LED_TASK()							app_add_led_task(DOOR_SENSOR_LED_ID, led_0_25s_on, 	0xffffff, 1, SENSOR_LED_TASK_PRIORITY, true)

void app_control_pin_no_led_task_callback(uint8_t control_pin_list_index)
{
	if( (control_pin_list_index == DOOR_SENSOR_LED_ID) ||
		(control_pin_list_index == 0xff) )
	{
		app_control_pin_action(DOOR_SENSOR_LED_ID, CONTROL_ACTION_OFF);
	}
}

uint8_t user_battery_percentage_algorithm(uint16_t milli_voltage, bool* is_low_power);
void user_low_power_notification(void);

void app_scan_network_process_init_callback(void)
{
	USER_SCAN_NETWORK_INDICATE_LED_TASK();
}

void app_scan_network_process_joined_callback(void)
{
	USER_SCAN_NETWORK_INDICATE_LED_TASK_CANCEL();
}

void app_scan_network_process_timeout_callback(void)
{
	USER_SCAN_NETWORK_INDICATE_LED_TASK_CANCEL();
}

void stack_key_parameter_configuration(void)
{
#if defined(STACK_NON_SLEEPY_END_DEVICE)
	//set device as non sleepy end device
	stack_set_non_sleepy_end_device();
#endif
}

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

static void _zbck_handshake_event_callback(uint8_t state)
{
	app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[ZBCK]Handshake event state %d", state);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if( (MEMCOMPARE( data, "AT+APPSCAN", 10 ) == 0 ) &&
		(length == 10) )
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Scan command, %d, %d, %s", 0xff, 30, "TRUE");

		app_scan_network_v2_start(0xff, 30, TRUE);

		return true;
	}

	if( (MEMCOMPARE( data, "AT+APPLEAVE", 11 ) == 0 ) &&
		(length == 11) )
	{
		uint8_t status = app_leave_network();
		app_serial_port_printf(port, "\r\n[AT CMD]Leave command 0x%x", status);

		return true;
	}

	if( (MEMCOMPARE( data, "AT+APPSEND", 10 ) == 0 ) &&
		(length == 10) )
	{
		app_send_zone_status_change_notification(1, 0x0020, 0);
		app_serial_port_printf(port, "\r\n[AT CMD]Send zone status change");

		return true;
	}

	if(util_strncmp("AT+ZBCKNOTIFY", (const char* )data, 13) == 0)
	{
		stack_set_zbck_secure_mode(ZBCK_SECURE_MODE_NWK_KEY_PROTECTION);

		stk_zbck_device_send_handshake_notify(0x07FFF800, 120, 0, _zbck_handshake_event_callback);

		app_serial_port_printf(port, "\r\n[AT CMD]ZBCK notify start");

		return true;
	}

	return false;
}

void app_universal_plugin_init_callback(void)
{

}

void app_plugin_init_callback(void)
{
	app_command_line_plugin_register();													//������ע�ᣬ��ѡ������ʹ�ô���������

	app_at_command_handle_register(user_at_command_handler);

#if defined(STACK_NON_SLEEPY_END_DEVICE)
	app_poll_server_plugin_register(true, (1800 * 1000), 250, 4, 1, 1, NULL);
#else
	app_poll_server_plugin_register(true, (1800 * 1000), 250, 4, 30, 3, NULL);			//poll serverע�ᣬ��ѡ��ʹzed�豸֧��long poll,short poll�Լ�poll cluster���������
#endif

	app_ota_client_plugin_register(REXENSE_MANUFACTURER_CODE,							//ota clientע�ᣬ��ѡ��ʹ�豸֧��ota����
								   REX_OTA_IMAGETYPE_CONTACT_SENSOR,
								   util_get_bcd_app_release_version(),
								   0,
								   0,
								   NULL);

	app_reporting_plugin_reporting_config_register																	//��ʱ�ϱ�ע�ᣬʹ�豸֧�ֶ�ʱ�ϱ�����������
	(
		 1, true, 60,																								//��1�����ã��������0 ~ 60s�������ӳ�
		 1, ZCL_POWER_CONFIG_CLUSTER_ID, ZCL_BATTERY_PERCENTAGE_REMAINING_ATTRIBUTE_ID, 0x0000, 16, (3600), 0		//���� cluster 0x0000, attr 0x0000, 1Сʱ��������
	);

	app_button_plugin_register(50, 400);

	app_contact_plugin_register(25, 4);

	app_control_plugin_init();

	app_ias_zone_plugin_register(sizeof(g_user_zone_type_list) / sizeof(g_user_zone_type_list[0]), g_user_zone_type_list, NULL);

	app_battery_monitor_plugin_register(3, 60 * 60 * 12, user_battery_percentage_algorithm, user_low_power_notification); //��ؼ�⣬����30���Ӳ��������12Сʱ�͵���֪ͨ���
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_VCP_SERIAL);

	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

bool app_ok_to_sleep_callback(void)
{
    return true;
}

void app_sleep_wakeup_callback(void)
{

}

uint8_t user_battery_percentage_algorithm(uint16_t milli_voltage, bool* is_low_power)
{
/*
	e.g.
*/
	uint16_t min_voltage = 2400;
	uint16_t max_voltage = 3000;

	milli_voltage = (milli_voltage > max_voltage) ? max_voltage : milli_voltage;
	milli_voltage = (milli_voltage < min_voltage) ? min_voltage : milli_voltage;

	uint32_t diff = (uint32_t)(milli_voltage - min_voltage) * 100;

	uint8_t percentage = (uint8_t)(diff / (uint32_t)(max_voltage - min_voltage));

	*is_low_power = (percentage <= 10) ? true : false;

	debugPortAll("\r\n[BATTERY]Percentage %d, %dmv, %d.", percentage, milli_voltage, *is_low_power);

	return percentage;
}

void user_low_power_notification(void)
{
	//send low power alarm

	uint16_t zone_status = 0;

	app_write_or_read_zone_status_attribute(false, 1, &zone_status);

	zone_status |= EMBER_AF_IAS_ZONE_STATUS_BATTERY;

	app_write_or_read_zone_status_attribute(true, 1, &zone_status);

	app_send_zone_status_change_notification(1, zone_status, 0);
}

/** ����  �� contact plugin�����ص�����
 *     contact_id    ��  HAL_CONTACT_PIN_LIST�е�id
 *     contact_io    ��  HAL_CONTACT_PIN_LIST�����õ�io�ϲ�ֵ
 *	   contact_state ��   ע �� contact_state���Ǳ�ʾ��ƽ״̬
 *					   true  - ��ʾ��ǰ״̬��HAL_CONTACT_PIN_LIST�����ã�DOOR_SENSOR_DETECT_OPEN_STATE����״̬һ��
 *					   false - ��ʾ��ǰ״̬��HAL_CONTACT_PIN_LIST�����ã�DOOR_SENSOR_DETECT_OPEN_STATE����״̬��һ��
 */
void app_contact_changed_callback(uint8_t contact_id, uint8_t contact_io, bool contact_state)
{
	uint16_t original_zone_status = 0;
	uint16_t current_zone_status = 0;

	app_write_or_read_zone_status_attribute(false, 1, &original_zone_status);

	current_zone_status = original_zone_status;

	if(contact_id == DOOR_SENSOR_DETECT_CONTACT_ID)
	{
		if(contact_state)
		{
			current_zone_status |= EMBER_AF_IAS_ZONE_STATUS_ALARM1;
		}
		else
		{
			current_zone_status &= (~EMBER_AF_IAS_ZONE_STATUS_ALARM1);
		}

		if(original_zone_status != current_zone_status)
		{
			SENSOR_ALARM_LED_TASK();
		}
	}

	if(contact_id == DOOR_SENSOR_TAMPER_CONTACT_ID)
	{
		if(contact_state)
		{
			current_zone_status |= EMBER_AF_IAS_ZONE_STATUS_TAMPER;
		}
		else
		{
			current_zone_status &= (~EMBER_AF_IAS_ZONE_STATUS_TAMPER);
		}

		if(original_zone_status != current_zone_status)
		{
			SENSOR_TEMPAR_LED_TASK();
		}
	}

	if(original_zone_status != current_zone_status)
	{
		app_write_or_read_zone_status_attribute(true, 1, &current_zone_status);

		app_send_zone_status_change_notification(1, current_zone_status, 0);

		debugPortAll("\r\n[CONTACT]Contact changed %d, zone status 0x%2x -> 0x%2x, ", contact_state, original_zone_status, current_zone_status);
	}
}

void app_io_press_callback(key_scan_t key)
{
	//app_serial_printf("\r\n[PRESSED]%d, 0x%2x, %d, %d, %d, %d", key.key_id, key.key_io, key.key_hold_on_counts, key.key_state, key.key_toggle, key.key_continue);

	//in app_button_plugin_register(50, 400); we config check interval 50ms, key.key_hold_on_counts = 100, | 100 * 50 = 5000ms

	if( (key.key_id == DEVICE_RESET_KEY_ID) && (key.key_hold_on_counts == 1) )
	{
		BUTTON_INDICATE_LED_TASK();
	}
}

void app_io_release_callback(key_scan_t key)
{
	//app_serial_printf("\r\n[RELEASED]%d, 0x%2x, %d, %d, %d, %d", key.key_id, key.key_io, key.key_hold_on_counts, key.key_state, key.key_toggle, key.key_continue);

	if( (key.key_id == DEVICE_RESET_KEY_ID) && key.key_hold_on_counts )
	{
		BUTTON_INDICATE_LED_TASK_CANCEL();

		if(key.key_hold_on_counts < 100)
		{
			USER_NETWORK_STATUS_INDICATE_LED_TASK(app_get_network_state());
		}
		else if( (key.key_hold_on_counts >= 100) &&
				 (key.key_hold_on_counts <= 200) )
		{
			debugPortAll("\r\n[SCAN]Call scan network api");
			app_scan_network_v2_start(0xff, 60, true); //start scan network 60s
		}
	}
}

void app_device_fresh_start_callback(void)
{
	uint16_t zone_status = 0;

	app_write_or_read_zone_status_attribute(false, 1, &zone_status);

	app_send_zone_status_change_notification(1, zone_status, 0);
}

void app_device_rejoin_successful_callback(void)
{
	//rejoin success, do something
}

/**���ܣ��豸�ⲿ���ѻص�
* ������ wakeupReason �� ����ԭ��
* ���أ�������Ҫ���ֻ��ѵ�ʱ������λms
*/
uint32_t app_keep_wakeup_ext_trigger_callback(uint8_t wakeup_reason)
{
	stack_attempt_recovery_network(true, 0);
	return 50; //keep wakeup 50ms
}

bool app_uart_frame_check(uint8_t* data, uint8_t length)
{
	return false;
}

#endif

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
#if defined(RZ_STACK_TRANSPARENT_DEMO)

#include "../include/global_apis.h"
#include "pin_def.h"
#include "app_common.h"

#define  DEFINEEEPTYPE
#include "common/app_sim_eep.h"	//type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

/*  radio tx power
 * 	PAģ��֧��     : [-4,-1,6,10,14,15,16,17,18,19,20],
 *	��PAģ��֧��  : [-10,-9,...,9,10],
 */
app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_ROT_Transparent_Demo_" APP_RELEASE_VERSION,
	.model_id							= "RZ0002",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20, 	//����Ϊ20(���ֵ),δʹ��PAʱ���Զ�����Ϊ10(���ֵ)
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

#define debugPortAll(format,...) 	app_debug_printf(format, ##__VA_ARGS__)

#define HL_VIRTUAL_INDEX_UART 		0x0FA0
#define	UART_MAX_DATA_LENGTH		72

/*********************����led��˸�ķ�ʽ**************************************/
#define SCAN_LED_TASK_PRIORITY			0 //0��ʾ������ȼ�

const led_list_t network_led_slow_blink[] =
{
	{CONTROL_ACTION_ON,  1000},
	{CONTROL_ACTION_OFF, 1000},
	{CONTROL_ACTION_END, 0},
};

#define NETWORK_LED_ADD_JOINING_STATE() 				app_add_led_task(DEVICE_ONOFF_NETWORK_LED_ID,    network_led_slow_blink, 90000, 0xff, SCAN_LED_TASK_PRIORITY, true)
#define NETWORK_LED_CANCEL_LEAVE_OR_NONETWORK_STATE() 	app_cancel_led_task(DEVICE_ONOFF_NETWORK_LED_ID, network_led_slow_blink)

/***********************��ĳ��ָʾ�����������Ϊ������ʱ����һ�λص�,����ͬ����ָʾ��״̬***************************/
void app_control_pin_no_led_task_callback(uint8_t control_pin_list_index)
{
	if(control_pin_list_index == DEVICE_ONOFF_NETWORK_LED_ID)
	{
		if(app_get_network_state() == EMBER_NO_NETWORK)
		{
			app_control_pin_action(DEVICE_ONOFF_NETWORK_LED_ID, CONTROL_ACTION_ON);//��������״̬��,������
		}
		else
		{
			app_control_pin_action(DEVICE_ONOFF_NETWORK_LED_ID, CONTROL_ACTION_OFF);//Ϩ������״̬��,������
		}
	}
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

void user_button_released_callback(key_scan_t* key)
{
	if(key->key_id == DEVICE_RESET_KEY_ID)
	{
		if(key->key_hold_on_counts >= 200) //upto 5000ms
		{
			app_scan_network_v2_start(0xff, 90, true);  //��������5s�����ɿ�ʱ��ﵽ����ɨ��
		}
	}
}

/***********************��Ҫʹ�õ���plugin��ʼ��***************************/
void app_plugin_init_callback(void)
{
	app_command_line_plugin_register();														//������ע�ᣬ��ѡ������ʹ�ô���������

	app_ota_client_plugin_register(REXENSE_MANUFACTURER_CODE,								//ota clientע�ᣬ��ѡ��ʹ�豸֧��ota����
								   REX_OTA_IMAGETYPE_RANGE_EXTENDER,
								   util_get_bcd_app_release_version(),
								   0,
								   0,
								   NULL);

	app_reporting_plugin_reporting_config_register											//��ʱ�ϱ�ע�ᣬ��ѡ��ʹ�豸֧�ֶ�ʱ�ϱ�����������
	(
		 1, true, 120,																		//��1�����ã��������0 ~ 120s�������ӳ�
		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (240), 0			//���� cluster 0x0000, attr 0x0000, 4-6��������
	);

	app_button_plugin_v2_register(25, 250, 2, NULL, user_button_released_callback);			//����plugin,25��ʾÿ��count++��Ҫ25ms,250��ʾ����250�μ���֮��Ͳ������ϼ���,�˲�ʱ��2*25ms
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_VCP_SERIAL);

	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

void app_wireless_port_send_message(void)
{

}

bool app_pre_zdo_handler(uint16_t node_id, EmberApsFrame* apsFrame, uint8_t* message, uint16_t length)
{
	if(apsFrame->clusterId == HL_VIRTUAL_INDEX_UART)		// forward to UART
	{
		if( (length > 0) &&
			(length <= UART_MAX_DATA_LENGTH) )
		{
			app_serial_port_write_data(TYPE_UART_SERIAL, message + 1, length - 1);
		}

		return	true;
	}

	return false;
}

bool app_uart_frame_check(uint8_t* data, uint8_t length)
{
	return false;
}

void app_process_uart_data(uint8_t* data, uint8_t length)
{
	if ( ( length > 0 ) && ( length <= UART_MAX_DATA_LENGTH ) )
	{
		app_send_zdo_msg_hops(g_report_target_node,
							  HL_VIRTUAL_INDEX_UART,
							  length,
							  data,
							  (EMBER_APS_OPTION_RETRY | EMBER_APS_OPTION_SOURCE_EUI64), 0);
	}
}

void app_device_fresh_start_callback(void)
{
	//we can report here, after joined or reboot(joined)
}

/******************�ûص���Ҫע��,��app_register_callback.c��ע��,����ʱ����������д�ڸûص���********************************/
void app_leave_network_detected_callback(void)
{
	app_control_pin_action(DEVICE_ONOFF_NETWORK_LED_ID, CONTROL_ACTION_ON); //��������״̬��
}

/******************ɨ�������ĳ�ʼ��,�����ڵ�������********************************/
void app_scan_network_process_init_callback(void)
{
	 NETWORK_LED_ADD_JOINING_STATE();
	 debugPortAll("\r\n[SCAN]Scan init.");
}

/******************ɨ�����������ɹ�,�����ڵ�������********************************/
void app_scan_network_process_joined_callback(void)
{
	NETWORK_LED_CANCEL_LEAVE_OR_NONETWORK_STATE();
	debugPortAll("\r\n[SCAN]Scan joined.");
}

/******************ɨ��������ʱ,�����ڵ�������********************************/
void app_scan_network_process_timeout_callback(void)
{
	NETWORK_LED_CANCEL_LEAVE_OR_NONETWORK_STATE();
	debugPortAll("\r\n[SCAN]Scan timeout.");
}

#endif

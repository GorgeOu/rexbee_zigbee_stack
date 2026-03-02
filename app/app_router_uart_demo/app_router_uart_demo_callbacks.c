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
#if defined(RZ_STACK_UART_DEMO)

#include "../include/global_apis.h"
#include "pin_def.h"
#include "app_common.h"

#define  DEFINEEEPTYPE
#include "common/app_sim_eep.h"	//type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#include "uart_protocol_desc.h"

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

/*  radio tx power
 * 	PAģ��֧��     : [-4,-1,6,10,14,15,16,17,18,19,20],
 *	��PAģ��֧��  : [-10,-9,...,9,10],
 */
app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_ROT_Uart_Demo_" APP_RELEASE_VERSION,
	.model_id							= "TS0105",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20, 	//����Ϊ20(���ֵ),δʹ��PAʱ���Զ�����Ϊ10(���ֵ)
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

#define debugPortAll(format,...) 	app_debug_printf(format, ##__VA_ARGS__)

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

/***********************��Ҫʹ�õ���plugin��ʼ��***************************/
void app_plugin_init_callback(void)
{
	app_command_line_plugin_register();														//������ע�ᣬ��ѡ������ʹ�ô���������

	app_ota_client_plugin_register(REXENSE_MANUFACTURER_CODE,								//ota clientע�ᣬ��ѡ��ʹ�豸֧��ota����
								   REX_OTA_IMAGETYPE_THERMOSTAT,
								   util_get_bcd_app_release_version(),
								   0,
								   0,
								   NULL);

	app_reporting_plugin_reporting_config_register											//��ʱ�ϱ�ע�ᣬ��ѡ��ʹ�豸֧�ֶ�ʱ�ϱ�����������
	(
		 1, true, 120,																		//��1�����ã��������0 ~ 120s�������ӳ�
		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (240), 0			//���� cluster 0x0000, attr 0x0000, 4-6��������
	);

	user_uart_message_init();
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_VCP_SERIAL);

	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

void app_stack_status_changed_callback(EmberStatus status,
									   EmberNetworkStatus last_network_state,
									   EmberNetworkStatus network_state)
{
	if( ( (network_state == EMBER_JOINED_NETWORK) ||
		  (network_state == EMBER_JOINED_NETWORK_NO_PARENT) ||
		  (network_state == EMBER_NO_NETWORK) ) &&
		  (last_network_state != network_state) )
	{
		//we can print network state here
	}
}

void app_device_network_start_callback(uint8_t event)
{
	//we can report here
}

void app_device_network_leaved_callback(uint8_t event)
{

}

void app_scan_network_process_init_callback(void)
{
	 debugPortAll("\r\n[SCAN]Scan init.");
}

void app_scan_network_process_joined_callback(void)
{
	debugPortAll("\r\n[SCAN]Scan joined.");
}

void app_scan_network_process_timeout_callback(void)
{
	debugPortAll("\r\n[SCAN]Scan timeout.");
}

#endif

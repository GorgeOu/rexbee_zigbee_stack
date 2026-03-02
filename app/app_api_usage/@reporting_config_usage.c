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

#if defined(RZ_STACK_REPORTING_CONFIG_API_USAGE)

#warning "reporting config api demo"

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_RPT_CFG_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_RPT_CFG",
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
	if( (util_strncmp("AT+RPTCLEAR", (const char* )data, 11) == 0) && (length == 11) )
	{
		app_device_clear_reporting_table();

		app_serial_port_printf(port, "\r\n[AT CMD]Reporting table clear");
	}

	return false;
}

void app_plugin_init_callback(void)
{
	app_at_command_handle_register(user_at_command_handler);

	app_reporting_plugin_reporting_config_register											//定时上报注册，可选，使设备支持定时上报（心跳包）
	(
		 1, true, 120,																		//共1个配置，随机增加0 ~ 120s的心跳延迟
		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (240), 0			//配置 cluster 0x0000, attr 0x0000, 4-6分钟心跳
	);

//	添加2个的例子如下 :
//	app_reporting_plugin_reporting_config_register											//定时上报注册，可选，使设备支持定时上报（心跳包）
//	(
//		 2, true, 120,																		//共2个配置，随机增加0 ~ 120s的心跳延迟
//		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (240), 0			//配置 cluster 0x0000, attr 0x0000, 4-6分钟心跳
//		 1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, 0x0000, 16, (240), 0			//配置 cluster 0x0006, attr 0x0000, 4-6分钟心跳
//	);
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


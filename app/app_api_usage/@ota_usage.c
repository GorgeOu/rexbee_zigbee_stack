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

#if defined(RZ_STACK_OTA_API_USAGE)

#warning "ota api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define CONFIG_DEVICE_MFG_CODE				REXENSE_MANUFACTURER_CODE			 //厂商自定义
#define CONFIG_DEVICE_IMAGE_TYPE   			REX_OTA_IMAGETYPE_ON_OFF_LIGHT_KEY_1 //厂商自定义
#define CONFIG_DEVICE_OTA_VERSION  			util_get_bcd_app_release_version() 	 //厂商自定义UINT32的ota版本号
#define CONFIG_OTA_PLUGIN_CB_REGISTER		1
#define CONFIG_OTA_PLUGIN_EXTERNAL_MCU		1

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_OTA_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_OTA_USAGE",
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

#if (CONFIG_OTA_PLUGIN_CB_REGISTER > 0)

#if (CONFIG_OTA_PLUGIN_EXTERNAL_MCU > 0)
void user_external_mcu_ota_notify(uint16_t image_type)
{
	debugPortAll("\r\n[MCU OTA]Mcu ota notify, image type 0x%2x", image_type);
}

void user_external_mcu_next_image_response(uint16_t mfg_code, uint16_t image_type, uint32_t version, uint32_t image_length)
{
	debugPortAll("\r\n[MCU OTA]Mcu ota next image resp, image type 0x%2x, version 0x%4x, size 0x%4x", image_type, version, image_length);
}

void user_external_mcu_image_block_response(uint8_t status, uint16_t mfg_code, uint16_t image_type, uint32_t version, uint32_t offset, uint8_t length, uint8_t* data)
{
	debugPortAll("\r\n[MCU OTA]Mcu ota image block resp, image type 0x%2x. version 0x%4x, offset 0x%4x, block size 0x%4x", image_type, version, offset, length);
}
#endif

void user_ota_in_progress_indicate(uint8_t received_percentage)
{

}

void user_ota_upgrade_abort(void)
{

}

void user_ota_recevied_finished_notify(bool firmware_check)
{

}

void user_ota_reboot_upgrade_firmware_notifiy(void)
{
	debugPortAll("\r\n[OTA]Ota upgrade firmware notify, will restart immediately");

	//不可再发送无线数据，可以选择存储token，写flash等操作
}

#endif

#if (CONFIG_OTA_PLUGIN_CB_REGISTER > 0)
const app_ota_plugin_handle_list_t c_user_ota_plugin_handle_list =
{
	.ota_start_notify 						= NULL,
	.ota_in_progress_indicate 				= user_ota_in_progress_indicate,
	.ota_recevied_finished_notify 			= user_ota_recevied_finished_notify,
	.ota_reboot_upgrade_firmware_notifiy 	= user_ota_reboot_upgrade_firmware_notifiy,
	.ota_single_request_timeout 			= NULL,
	.ota_upgrade_abort 						= user_ota_upgrade_abort,
	.ota_upgrade_wait_for_data 				= NULL,
	#if (CONFIG_OTA_PLUGIN_EXTERNAL_MCU > 0)
	.external_mcu_ota_notify 				= user_external_mcu_ota_notify,
	.external_mcu_next_image_response 		= user_external_mcu_next_image_response,
	.external_mcu_image_block_response		= user_external_mcu_image_block_response,
	#else
	.external_mcu_ota_notify 				= NULL,
	.external_mcu_next_image_response 		= NULL,
	.external_mcu_image_block_response		= NULL,
	#endif
	.ota_hal_flash_read  					= NULL,
	.ota_hal_flash_write 					= NULL,
	.ota_hal_flash_erase 					= NULL,
};
#endif

void app_plugin_init_callback(void)
{
	//ota client注册，使设备支持ota升级
	app_ota_client_plugin_register(CONFIG_DEVICE_MFG_CODE,
								   CONFIG_DEVICE_IMAGE_TYPE,
								   CONFIG_DEVICE_OTA_VERSION,
								   0,
								   0,
								   #if (CONFIG_OTA_PLUGIN_CB_REGISTER > 0)
								   (stack_application_zcl_handle_t* )&c_user_ota_plugin_handle_list
								   #else
								   NULL
								   #endif
								   );

	#if (CONFIG_OTA_PLUGIN_EXTERNAL_MCU > 0)
	app_set_external_mcu_image_type((CONFIG_DEVICE_IMAGE_TYPE | 0x0F00));
	#endif
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

/*
 * MCU REF.
 */
void user_uart_protocol_device_info_resp_handler(...)
{
	//mcu software_version

	app_analysis_ota_querry_next_img(g_report_target_node,
									 g_report_target_ep,
									 app_get_manufacture_id(),
									 app_get_external_mcu_image_type(),
									 software_version);
}


void user_uart_protocol_ota_notify_resp_handler(uint8_t seq, uint8_t msg_type, bool wcb, uint16_t payload_length, const uint8_t *payload)
{
	uint8_t index = 0;

	uint8_t upgrade_result = payload[index++];

	debugPortAll("\r\n[CMD]Ota nofity resp result %d", upgrade_result);

	if(upgrade_result)
	{
		uint32_t new_software_version = build_int32u(false, &payload[index]);
		index += 4;

		uint8_t result = app_analysis_ota_upgrade_end_request(g_report_target_node,
															  g_report_target_ep,
															  EMBER_ZCL_STATUS_ABORT,
															  app_get_manufacture_id(),
															  app_get_external_mcu_image_type(),
															  new_software_version);
		(void)result;
	}
}

void user_uart_protocol_ota_image_block_req_handler(...)
{
	//mcu req new_software_version
	//mcu req file offset
	//mcu req block size

	uint8_t result = app_analysis_ota_querry_img_block_with_aps_ack(g_report_target_node,
																	g_report_target_ep,
																	app_get_manufacture_id(),
																	app_get_external_mcu_image_type(),
																	new_software_version,
																	file_offset,
																	block_size);
}

void user_uart_protocol_ota_upgrade_result_handler(...)
{
	//mcu upgrade_result
	//mcu new version

	uint8_t result = app_analysis_ota_upgrade_end_request(g_report_target_node,
														  g_report_target_ep,
														  (upgrade_result == UART_MCU_OTA_UPGRADE_SUCCESS) ? EMBER_ZCL_STATUS_SUCCESS :
															( (upgrade_result == UART_MCU_OTA_UPGRADE_INVALID_IMAGE) ? EMBER_ZCL_STATUS_INVALID_IMAGE : EMBER_ZCL_STATUS_ABORT ),
														  app_get_manufacture_id(),
														  app_get_external_mcu_image_type(),
														  new_software_version);
}


#endif

#endif


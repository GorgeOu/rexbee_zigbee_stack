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

#if defined(RZ_STACK_ZIGBEE_SEND_API_USAGE)

#warning "zigbee send api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_ZIGBEE_SEND_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_ZIGBEE_SEND_USAGE",
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
	if(util_match_uart_command_fixed_length("AT+APPSCAN", data, length))
	{
		app_serial_port_printf(port, "\r\n[AT CMD]Scan command, %d, %d, %s", 0xff, 120, "TRUE");

		app_scan_network_v2_start(0xff, 120, true);

		return true;
	}

	if(util_match_uart_command_fixed_length("AT+APPLEAVE", data, length))
	{
		uint8_t status = app_leave_network();
		app_serial_port_printf(port, "\r\n[AT CMD]Leave command 0x%x", status);

		return true;
	}

	if(util_strncmp("AT+RAWZCL", (const char* )data, 9) == 0)
	{
		EmberStatus status = app_v2_send_zcl_message(HA_PROFILE_ID, //profile id
													 0x0000, 		//sent to node id 0x0000
													 0, 	 		//0 is not a multicast message
													 1,		 		//local ep
													 1, 	 		//dest ep
													 ZCL_ON_OFF_CLUSTER_ID,	//zcl cluster id
													 (ZCL_CLUSTER_SPECIFIC_COMMAND + ZCL_FRAME_CONTROL_CLIENT_TO_SERVER + ZCL_DISABLE_DEFAULT_RESPONSE_MASK), //zcl frame
													 0x0000, 			//zcl standard command(set manufacture_code 0x0000)
													 ZCL_ON_COMMAND_ID, //command id
													 0, 	 			//no command payload
													 NULL, 	 			//no command payload
													 app_get_zcl_message_default_option(),
													 0,      			//radius 0 is max support radius(12)
													 stack_get_next_zcl_sequence());

		app_serial_port_printf(port, "\r\n[AT CMD]Send raw zcl message, status 0x%x", status);

		return true;
	}

	if(util_strncmp("AT+ZCLREPORT", (const char* )data, 12) == 0)
	{
		bool onoff = false;

		uint8_t status = app_read_server_attribute(1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, 0x0000, (uint8_t*)&onoff, 1);

		if(status == EMBER_SUCCESS)
		{
			status = app_v2_device_report_attr_mfg(0x0000, 						//sent to node id 0x0000
											       1, 	   						//local endpoint
											       1, 	   						//dest endpoint
											       ZCL_ON_OFF_CLUSTER_ID,    	//zcl cluster id
											       ZCL_ON_OFF_ATTRIBUTE_ID,  	//zcl attribute id
											       ZCL_BOOLEAN_ATTRIBUTE_TYPE,  //zcl attribute id
											       (uint8_t* )&onoff, 						//attribute data
											       0x0000);						//zcl standard attribute(set manufacture_code 0x0000)
		}

		app_serial_port_printf(port, "\r\n[AT CMD]Send zcl report message, status 0x%x", status);

		return true;
	}

	if(util_strncmp("AT+ZCLMULTIREPORT", (const char* )data, 17) == 0)
	{
		uint8_t zcl_verion;
		uint8_t app_verion;
		uint8_t stack_verion;

		app_read_server_attribute(1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, &zcl_verion, 1);
		app_read_server_attribute(1, ZCL_BASIC_CLUSTER_ID, ZCL_APPLICATION_VERSION_ATTRIBUTE_ID, 0x0000, &app_verion, 1);
		app_read_server_attribute(1, ZCL_BASIC_CLUSTER_ID, ZCL_STACK_VERSION_ATTRIBUTE_ID, 0x0000, &stack_verion, 1);

		attribute_data_t report_data[] =
		{
			{ .id = ZCL_VERSION_ATTRIBUTE_ID, 				.type = ZCL_INT8U_ATTRIBUTE_TYPE, .size = 1, .value = &zcl_verion },
			{ .id = ZCL_APPLICATION_VERSION_ATTRIBUTE_ID,   .type = ZCL_INT8U_ATTRIBUTE_TYPE, .size = 1, .value = &app_verion },
			{ .id = ZCL_STACK_VERSION_ATTRIBUTE_ID, 		.type = ZCL_INT8U_ATTRIBUTE_TYPE, .size = 1, .value = &stack_verion },
		};

		uint8_t status = app_v2_device_report_multi_attr_mfg(0x0000, 					//sent to node id 0x0000
															 1, 	   					//local endpoint
															 1, 	   					//dest endpoint
															 ZCL_BASIC_CLUSTER_ID,    	//zcl cluster id
															 0x0000,  					//zcl standard attribute(set manufacture_code 0x0000)
															 sizeof(report_data) / sizeof(report_data[0]), //attribute entry number
															 report_data);

		app_serial_port_printf(port, "\r\n[AT CMD]Send zcl multi report message, status 0x%x", status);

		return true;
	}

	if(util_strncmp("AT+RAWZDO", (const char* )data, 9) == 0)
	{
		uint8_t spec_zdo_message_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		EmberStatus status = app_send_zdo_msg_hops(0x0000,  //sent to node id 0x0000
												   0xF100, 	//zdo cluster, private zdo cluster 0xF100
												   sizeof(spec_zdo_message_data), 		//payload length
												   spec_zdo_message_data,  //private zdo payload
												   0, 		//0, use default option
												   0);		//radius 0 is max support radius(12)

		app_serial_port_printf(port, "\r\n[AT CMD]Send raw zdo message, status 0x%x", status);

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


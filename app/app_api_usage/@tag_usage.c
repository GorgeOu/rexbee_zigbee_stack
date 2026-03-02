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

#if defined(RZ_STACK_TAG_API_USAGE)

#warning "tag api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_TAG_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_TAG_USAGE",
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

enum
{
	TAG_MODE_IDLE,
	TAG_MODE_RECEIVER,
	TAG_MODE_ANCHOR,
};

static uint8_t s_select_mode = TAG_MODE_IDLE;

static uint8_t s_tag_event_id = 0xff;

typedef struct
{
    int32_t x;       // 当前估计的“真实 RSSI”，内部为放大 KF_SCALE 倍
    int32_t p;       // 估计协方差（同样放大 KF_SCALE 倍）
    int32_t q;       // 过程噪声协方差（调响应速度）
    int32_t r;       // 测量噪声协方差（调平滑程度）
    uint8_t inited;  // 是否已初始化
} rex_kalman_rssi_int_t;

static rex_kalman_rssi_int_t s_rssi_kf;

#define IEEE_15_4_CMD_RF_TEST	0xE3

#define RF_TEST_SUB_COMMAND_ANCHOR_REQ 0x10

static uint8_t s_payload_seq = 0;

#define FILL_RF_TEST_SUB_COMMAND_SEQ()	(s_payload_seq++)
#define GET_RF_TEST_SUB_COMMAND_SEQ()	(s_payload_seq)

static void _build_mfg_spec_ieee_command_frame(bool mac_ack_require,
												 uint8_t mac_seq,
												 uint16_t pan_id,
												 uint16_t dest_node,
												 uint8_t rf_sub_test_command,
												 uint8_t rf_test_frame_control,
												 uint8_t* seq,
												 uint8_t* data,
												 uint8_t length,
												 uint8_t* result)
{
	uint8_t index = 1; //0 is phy length

	uint16_t macFrameControl = 0x8843 | (mac_ack_require ? 0x0020 : 0);

	MEMCOPY(result + index, (uint8_t* )&macFrameControl, 2);

	index += 2;

	result[index++] = mac_seq; //FILL_MAC_SEQ();

	uint16_t source_node = stackGetNodeId();

	MEMCOPY(result + index, (uint8_t* )&pan_id, 2);
	index += 2;

	MEMCOPY(result + index, (uint8_t* )&dest_node, 2);
	index += 2;

	MEMCOPY(result + index, (uint8_t* )&source_node, 2);
	index += 2;

	result[index++] = IEEE_15_4_CMD_RF_TEST;

	result[index++] = rf_sub_test_command;

	result[index++] = rf_test_frame_control;

	if(seq)
	{
		result[index++] = *seq;
	}
	else
	{
		result[index++] = FILL_RF_TEST_SUB_COMMAND_SEQ();
	}

	if(data)
	{
		MEMCOPY(result + index, (uint8_t* )data, length);
	}

	index += length;

	index += 2; //added crc, value auto gen by hw

	result[0] = index - 1;
}

static int _tag_anchor_event_callback(void)
{
	uint8_t tag_anchor_msg[128];

	uint8_t* stackGetMacAddress(void);
	uint8_t stack_fill_mac_seq(void);

	_build_mfg_spec_ieee_command_frame(false,
										stack_fill_mac_seq(),
										0xffff,
										0xffff,
										RF_TEST_SUB_COMMAND_ANCHOR_REQ,
										0x00,
										NULL,
										stackGetMacAddress(),
										8,
										tag_anchor_msg);

	app_send_15_4_raw_message(tag_anchor_msg, false);

	return 100;
}

static EmberStatus _tag_received_callback(StackZigbeeMessageType type, uint8_t* data, uint8_t length)
{
	#define IEEE_15_4_CMD_OFFSET 	10

	if(type == ZIGBEE_MESSAGE_TYPE_MAC)
	{
		if(data[IEEE_15_4_CMD_OFFSET] == IEEE_15_4_CMD_RF_TEST)
		{
			uint8_t sub_command_id 		 	= data[IEEE_15_4_CMD_OFFSET + 1];
			uint8_t rf_test_fc				= data[IEEE_15_4_CMD_OFFSET + 2];
			uint8_t rf_test_seq				= data[IEEE_15_4_CMD_OFFSET + 3];
			uint8_t* command_payload 		= &data[IEEE_15_4_CMD_OFFSET + 4];
			uint8_t command_payload_length 	= length - (IEEE_15_4_CMD_OFFSET + 4 + 2);
			int8_t last_rssi 				= stk_get_last_hop_rssi();

			if(sub_command_id == RF_TEST_SUB_COMMAND_ANCHOR_REQ)
			{
			    int8_t rssi_est = rex_kalman_rssi_int_update(&s_rssi_kf, last_rssi);

				app_serial_printf("\r\nMAC:%n,RSSI:%d,%d", command_payload, rssi_est, last_rssi);

				return EMBER_SUCCESS;
			}
		}
	}

	return EMBER_SUCCESS;
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if( (util_strncmp("AT+RECVSTART", (const char* )data, 12) == 0) && (length == 12) )
	{
		app_event_v2_cancel(&s_tag_event_id);

		rex_kalman_rssi_int_init(&s_rssi_kf, -70, 2, 10);

		s_select_mode = TAG_MODE_RECEIVER;

		app_incoming_raw_message_handle_register(_tag_received_callback);

		return true;
	}

	if( (util_strncmp("AT+ANCHORSTART", (const char* )data, 14) == 0) && (length == 14) )
	{
		app_event_v2_cancel(&s_tag_event_id);

		app_incoming_raw_message_handle_register(NULL);

		s_select_mode = TAG_MODE_ANCHOR;

		app_event_v2_register(true, &s_tag_event_id, 100, _tag_anchor_event_callback);

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


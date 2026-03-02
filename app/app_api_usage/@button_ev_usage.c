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
#include "common/app_sim_eep.h" //type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#if defined(RZ_STACK_BUTTON_EV_API_USAGE)

#warning "button ev api demo"

#define debugPortAll(format,...) app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
    .firmware_print_version             = "REX_ZB_BUTTON_EV_USAGE_" APP_RELEASE_VERSION,
    .model_id                           = "BUTTON_EV",
    .manufacture_name                   = "REXENSE",
    .manufacture_code                   = REXENSE_MANUFACTURER_CODE,
    .radio_tx_power                     = 20,
    .zigbee_type                        = ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
    .default_zcl_message_aps_ack_enable = true,
    .send_device_announce_after_reboot  = true,
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

static const char* button_event_to_str(button_ev_type_t type)
{
	if(type == BUTTON_EV_SINGLE_CLICK)
		return "SINGLE";

	if(type == BUTTON_EV_DOUBLE_CLICK)
		return "DOUBLE";

	if(type == BUTTON_EV_TRIPLE_CLICK)
		return "TRIPLE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_1_RELEASE)
		return "LP1_RELEASE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_2_RELEASE)
		return "LP2_RELEASE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_3_RELEASE)
		return "LP3_RELEASE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_4_RELEASE)
		return "LP4_RELEASE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_1_IMMEDIATE)
		return "LP1_IMMEDIATE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_2_IMMEDIATE)
		return "LP2_IMMEDIATE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_3_IMMEDIATE)
		return "LP3_IMMEDIATE";

	if(type == BUTTON_EV_LONG_PRESS_MODE_4_IMMEDIATE)
		return "LP4_IMMEDIATE";

	if(type == BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_1_CLICK)
		return "LPM1_CLICK";

	if(type == BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_2_CLICK)
		return "LPM2_CLICK";

	return "UNKNOWN";
}

//static void user_button_default_event_callback(const button_ev_data_t* ev)
//{
//    debugPortAll("\r\n[BTN_EV]%s key=%d io=0x%x hold=%ldms click=%d",
//                 button_event_to_str(ev->type),
//                 ev->key_id,
//                 ev->key_io,
//                 ev->hold_ms,
//                 ev->click_count);
//}

static void user_test_key_event_callback(const button_ev_data_t* ev)
{
    debugPortAll("\r\n[TEST_KEY]%s key=%d",
                 button_event_to_str(ev->type),
                 ev->key_id);
}

static void user_test_key2_event_callback(const button_ev_data_t* ev)
{
    debugPortAll("\r\n[TEST_KEY2]%s key=%d",
                 button_event_to_str(ev->type),
                 ev->key_id);
}

void app_plugin_init_callback(void)
{
    button_ev_config_t cfg =
    {
    	// button scan tick
        .button_hold_on_counter_tick_ms = 25,
        .button_hold_on_max_counts = 800,
        .button_debounce_counts = 2,

    	// button event config
        .click_gap_ms = 500, // 设置为0时，不检测双击/三击，短按抬手立即上报单击
        .click_block_ms = 0, // 单/双/三击后屏蔽0ms连续操作
        .long_press_immediate_mode_ms 		= {5000, 	10000, 	0, 		0},
        .long_press_release_mode_ms 		= {10000, 	0, 		0, 		0},
        .long_press_then_multi_mode_ms 		= {5000, 	0},
        .long_press_then_multi_click_gap_ms = {800, 	0},
        .long_press_then_multi_click_times 	= {3,		0},
    };

    button_ev_bind_item_t bind_list[] =
    {
        {
            .key_id = DEVICE_TEST_KEY_ID,
            .event_bitmap = BUTTON_EV_EVENT_MASK_SINGLE_CLICK |
                            BUTTON_EV_EVENT_MASK_DOUBLE_CLICK |
                            BUTTON_EV_EVENT_MASK_TRIPLE_CLICK |
                            BUTTON_EV_EVENT_MASK_LONG_PRESS_THEN_MULTI_MODE_1_CLICK,
            .callback = user_test_key_event_callback,
        },
        {
            .key_id = DEVICE_TEST_KEY2_ID,
            .event_bitmap = BUTTON_EV_EVENT_MASK_SINGLE_CLICK |
            				BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_1_IMMEDIATE |
            				BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_2_IMMEDIATE |
                            BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_1_RELEASE,
            .callback = user_test_key2_event_callback,
        },
    };

    app_button_ev_plugin_register(&cfg,
								  NULL, //user_button_default_event_callback
								  bind_list,
								  sizeof(bind_list) / sizeof(bind_list[0]));

    // 注册后仍可动态调整：
    // button_ev_unbind_key_callback(DEVICE_TEST_KEY_ID);
    // button_ev_bind_key_callback(DEVICE_TEST_KEY_ID, BUTTON_EV_EVENT_MASK_ALL, user_test_key_event_callback);
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

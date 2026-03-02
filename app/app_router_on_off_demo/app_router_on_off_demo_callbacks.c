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
#if defined(RZ_STACK_ROUTER_DEMO)

#include "../include/global_apis.h"
#include "pin_def.h"
#include "app_common.h"

#define  DEFINEEEPTYPE
#include "common/app_sim_eep.h"	//type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#define APP_RELEASE_VERSION "1.0.1" //format "x.y.z" range[0 ~ 9]

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

/*  radio tx power
 * 	PA模组支持     : [-4,-1,6,10,14,15,16,17,18,19,20],
 *	非PA模组支持  : [-10,-9,...,9,10],
 */
app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_ROT_On_Off_Demo_" APP_RELEASE_VERSION,
	.model_id							= "RZ0000",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20, 	//设置为20(最大值),未使能PA时会自动限制为10(最大值)
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

#define debugPortAll(format,...) 	app_debug_printf(format, ##__VA_ARGS__)

/******************全局变量********************************/
typedef struct _user_device_status_
{
    uint8_t control_action;
    uint8_t key_id;
    uint8_t relay_id;
    uint8_t led_id;
} user_device_status_t;

user_device_status_t g_local_user_device_status[FIXED_ENDPOINT_COUNTS] =
{
    {
        .control_action  = CONTROL_ACTION_END,
        .key_id          = DEVICE_ONOFF_EP1_KEY_ID,
        .relay_id        = DEVICE_ONOFF_EP1_RELAY_ID,
        .led_id          = DEVICE_ONOFF_EP1_LED_ID,
    },
};

/***********************定义开关状态需要存入token中***************************/
typedef struct
{
    uint8_t   onoff_state[FIXED_ENDPOINT_COUNTS]; //开关
    uint8_t   reserved[48 - FIXED_ENDPOINT_COUNTS];//保留值,总共字节保留了48字节,请勿填写错误总数
} APP_TOKEN_DEF;
APP_TOKEN_DEF* g_token_def = (APP_TOKEN_DEF* )g_app_global_token_data;

/*********************定义led闪烁的方式**************************************/
#define SCAN_LED_TASK_PRIORITY			0 //0表示最高优先级

const led_list_t network_led_slow_blink[] =
{
	{CONTROL_ACTION_ON,  1000},
	{CONTROL_ACTION_OFF, 1000},
	{CONTROL_ACTION_END, 0},
};

#define NETWORK_LED_ADD_JOINING_STATE() 				app_add_led_task(DEVICE_ONOFF_NETWORK_LED_ID,    network_led_slow_blink, 90000, 0xff, SCAN_LED_TASK_PRIORITY, true)
#define NETWORK_LED_CANCEL_LEAVE_OR_NONETWORK_STATE() 	app_cancel_led_task(DEVICE_ONOFF_NETWORK_LED_ID, network_led_slow_blink)

#include "app_attr_handler.i"
#include "app_command_handler.i"
#include "onoff_plugin_handler.i"

static void scan_network_event_callback(app_scan_network_event_enum_t event);

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

void app_universal_plugin_init_callback(void)
{
	app_group_plugin_register(0, NULL);
	app_aps_message_filter_plugin_register();
}

/***********************当某个指示灯由有任务变为无任务时进入一次回调,用于同步此指示灯状态***************************/
void app_control_pin_no_led_task_callback(uint8_t control_pin_list_index)
{
	if(control_pin_list_index == DEVICE_ONOFF_NETWORK_LED_ID)
	{
		if(app_get_network_state() == EMBER_NO_NETWORK)
		{
			app_control_pin_action(DEVICE_ONOFF_NETWORK_LED_ID, CONTROL_ACTION_ON);//点亮网络状态灯,无网络
		}
		else
		{
			app_control_pin_action(DEVICE_ONOFF_NETWORK_LED_ID, CONTROL_ACTION_OFF);//熄灭网络状态灯,有网络
		}
	}
}

void app_post_token_init_callback(void)
{
	app_nvm_attribute_storage_plugin_register();
}
/**介绍：长按或长按后在规定时间内长按次数
*  参数：init_start 0: 平常都是0
                     1: 按到5s置1就可以开始短按操作计数
         enable     0：连按3次是否开启，不选择向上加就是0
                    1：向上加就是1
         count      0：需要短按的次数，如果说不需要下面两个参数的话就填0进入直接扫网
                    1-0xff：需要
         out_time   0：
                    1-0xffffffff：短按多次的超时时间
         maintick中：user_continuous_press_assign_time(false, fasle, 3, 3000);
         短按按键松开的时候：user_continuous_press_assign_time(fasle, true, 3, 3000);
         长按按键松开的时候：user_continuous_press_assign_time(true,false, 3, 3000);
         短按时间为3次，超时时间为3000。

         若想要长按之后松开直接进行扫网的话，调用接口user_continuous_press_assign_time(true, false, 0, 0);

        次数使用宏定义：SHORT_PRESS_COUNT，修改为多少次就是多少次
        短按超时时间使用宏定义：SHORT_PRESS_TIMEOUT，修改为多少就是多少ms（1000为1s）

*  返回：无
*/
void user_continuous_press_assign_time(bool init_start, bool enable, uint8_t count, uint32_t out_time)
{
    uint32_t time = app_system_time();

	static bool     init        = false;
	static uint16_t press_count = 0;
    static uint32_t count_time 	= 0UL;

    if(enable && init)
    {
       enable = 0;

       press_count++;

       debugPortAll("\r\n[KEY]Press continues, cnt %d.", press_count);
    }

    if(init_start)
    {
        if((!count) && (!out_time))
        {
           app_scan_network_v3_start(90, true, 0, scan_network_event_callback); //长按按键松开时间达到后开启扫网
        }
        else
        {
            count_time = app_system_time();
            init_start = 0;
            init       = true;
            debugPortAll("\r\n[KEY]Long press key init.");
        }
    }
    else if(init)
    {
        if(press_count == count)
        {
           app_scan_network_v3_start(90, true, 0, scan_network_event_callback); //在规定时间内短按次数达到后开启扫网
           debugPortAll("\r\n[KEY]Press continues counts reached");
           press_count = 0;
           init = 0;
        }

        if(time - count_time >= out_time)
        {
            debugPortAll("\r\n[KEY]Short press continues timeout");
            press_count = 0;
            init = false;
        }
    }
}

void user_button_pressed_callback(key_scan_t* key)
{
	//debugPortAll("\r\n[PRESSED]%d, 0x%2x, %d, %d, %d, %d", key->key_id, key->key_io, key->key_hold_on_counts, key->key_state, key->key_toggle, key->key_continue);
}

/******************按键按下回调********************************/
void user_button_released_callback(key_scan_t* key)
{
	//debugPortAll("\r\n[RELEASED]%d, 0x%2x, %d, %d, %d, %d", key->key_id, key->key_io, key->key_hold_on_counts, key->key_state, key->key_toggle, key->key_continue);
	if(key->key_id == DEVICE_RESET_KEY_ID)
	{
		if( (key->key_hold_on_counts >= 4) &&
            (key->key_hold_on_counts < 200) ) //unit 25ms, 100ms ~ 5000ms
		{
			bool state = false;

			app_global_read_server_attribute((key->key_id + 1), ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t* )&state, 1);

			state = state ? false : true;

			app_global_write_server_attribute((key->key_id + 1), ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t* )&state, ZCL_BOOLEAN_ATTRIBUTE_TYPE);

			user_continuous_press_assign_time(false, true, 3, 3000);
		}
		if(key->key_hold_on_counts >= 200) //upon 5000ms
		{
			user_continuous_press_assign_time(true, false, 3, 3000);
		}
	}
}

void stack_key_parameter_configuration(void)
{
#if defined(APP_USE_FRAGMENTATION_PLUGIN)
	app_fragmentation_plugin_config_register();
#endif
}

/***********************需要使用到的plugin初始化***************************/
void app_plugin_init_callback(void)
{
	//app_command_line_plugin_register();														//命令行注册，可选，方便使用串口做调试

	app_ota_client_plugin_register(REXENSE_MANUFACTURER_CODE,								//ota client注册，可选，使设备支持ota升级
								   REX_OTA_IMAGETYPE_ON_OFF_LIGHT_KEY_1,
								   util_get_bcd_app_release_version(),
								   0,
								   0,
								   NULL);

	app_reporting_plugin_reporting_config_register											//定时上报注册，可选，使设备支持定时上报（心跳包）
	(
		 1, true, 120,																		//共1个配置，随机增加0 ~ 120s的心跳延迟
		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (240), 0			//配置 cluster 0x0000, attr 0x0000, 4-6分钟心跳
	);

	user_zcl_cmd_list_register();
	user_zcl_attr_list_register();

	user_onoff_plugin_register();

	app_button_plugin_v2_register(25, 250, 2, user_button_pressed_callback, user_button_released_callback);	 //按键plugin,25表示每次count++需要25ms,250表示经过250次计数之后就不在向上计数
																											 //消抖时间为2*25，回调函数为user_button_pressed_callback, user_button_released_callback

}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_VCP_SERIAL);

	app_version_printf(TYPE_UART_SERIAL);

	for(uint8_t i = 0;i < FIXED_ENDPOINT_COUNTS; i++)
	{
		app_global_write_server_attribute(i + 1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID,	// re-store summation
								 	 	  (uint8_t* )&(g_token_def->onoff_state[i]), ZCL_BOOLEAN_ATTRIBUTE_TYPE);
	}
}

void app_main_tick_callback(void)
{
    user_continuous_press_assign_time(false, false, 3, 3000);   					//按键连按多少次，间隔多少ms
}

bool app_uart_frame_check(uint8_t* data, uint8_t length)
{
	return false;
}


/******************扫网函数的初始化,可用于灯闪操作********************************/
void app_scan_network_process_init_callback(void)
{

}

/******************扫网函数入网成功,可用于灯闪操作********************************/
void app_scan_network_process_joined_callback(void)
{

}

void app_process_uart_data(uint8_t* data, uint8_t length)
{
	if(util_match_uart_command_fixed_length("AT+CCA", data, length))
	{
		int8_t hal_radio_energy_detect(void);

		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[AT CMD]Ed %d", hal_radio_energy_detect());

		return;
	}

	if(util_match_uart_command_fixed_length("AT+APPSCAN", data, length))
	{
		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[AT CMD]Scan command, %d, %d, %s", 0xff, 120, "TRUE");

		app_scan_network_v3_start(120, true, 0, scan_network_event_callback);

		return;
	}

	if(util_match_uart_command_fixed_length("AT+APPLEAVE", data, length))
	{
		uint8_t status = app_leave_network();
		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[AT CMD]Leave command 0x%x", status);

		return;
	}

	if(util_match_uart_command_fixed_length("AT+APPSEND", data, length))
	{
		uint8_t onoff = 0xff;

		app_read_server_attribute(1, 0x0006, 0x0000, 0x0000, &onoff, 1);

		uint8_t status = app_v2_device_report_attr_mfg(g_report_target_node, 1, g_report_target_ep, 0x0006, 0x0000, ZCL_BOOLEAN_ATTRIBUTE_TYPE, &onoff, 0x0000);

		app_serial_port_printf(TYPE_UART_SERIAL, "\r\n[AT CMD]App send report command 0x%x", status);

		return;
	}
}

void app_device_network_start_callback(uint8_t event)
{
	//we can report here, after joined or reboot(joined)

	uint8_t state = 0;

	for(uint8_t i = 0;i < FIXED_ENDPOINT_COUNTS; i++)
	{
		app_global_read_server_attribute(i + 1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, &state, 1);
		app_device_report_attr_mfg(g_report_target_node, i + 1, g_report_target_ep, ZCL_ON_OFF_CLUSTER_ID,
                               ZCL_ON_OFF_ATTRIBUTE_ID, ZCL_BOOLEAN_ATTRIBUTE_TYPE, &state, 0x0000);
	}
}

/******************读取token中的开关状态,若没有被使用过则初始化状态********************************/
void app_get_token_data_to_ram_callback(void)
{
	if(!app_is_global_token_data_used())
	{
        MEMSET((uint8_t* )g_token_def, 0, 48);
		app_set_global_token_data((uint8_t* )g_token_def);
	}
	app_get_global_token_data((uint8_t* )g_token_def);
}

void app_device_network_leaved_callback(uint8_t event)
{
	app_control_pin_action(DEVICE_ONOFF_NETWORK_LED_ID, CONTROL_ACTION_ON);//点亮网络状态灯
}

static void scan_network_event_callback(app_scan_network_event_enum_t event)
{
	if(event == APP_SCAN_NETWORK_EVENT_INIT)
	{
		 NETWORK_LED_ADD_JOINING_STATE();
		 debugPortAll("\r\n[SCAN]Scan init.");
	}
	else if( (event == APP_SCAN_NETWORK_EVENT_JOINED) ||
			 (event == APP_SCAN_NETWORK_EVENT_ZBCK_JOINED) )
	{
		NETWORK_LED_CANCEL_LEAVE_OR_NONETWORK_STATE();
		debugPortAll("\r\n[SCAN]Scan joined.");
	}
	else if(event == APP_SCAN_NETWORK_EVENT_TIMEOUT)
	{
		NETWORK_LED_CANCEL_LEAVE_OR_NONETWORK_STATE();
		debugPortAll("\r\n[SCAN]Scan timeout.");
	}
}

#endif

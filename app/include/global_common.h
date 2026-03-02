/**
 * Copyright ? 2019 Zhejiang Raying IoT Technology Co., Ltd.
 * All rights reserved. 
 *
 * File: Global_Common.h
 * Description: This file definitions global common include
 *
 * Author(s): yuxiaoqiang@rexense.com	
 * Data: 2020/02/20
 */



#ifndef __GLOBAL_COMMON_H__
#define __GLOBAL_COMMON_H__

#define SIGNED_ENUM

#include "rename_function.h"

#include "board/8258/driver_8258.h"

#include <stdint.h>
#include <stdbool.h>
#include "platform-common.h"
#include "ember-types.h"
#include "af-types.h"
#include "attribute-id.h"
#include "attribute-type.h"
#include "att-storage.h"
#include "cluster-id.h"
#include "efr32-mirco-common.h"
#include "command-id.h"

#include "rex_ota_image_type.h"

#define __weak __attribute__((weak))

#define PGM const

typedef struct
{
	uint8_t  data[132];
	uint8_t  length;
	uint8_t  status;
	uint16_t receive_time;
} uart_buffer_t;

typedef struct 
{
	E_GPIO_PORT_TYPES   port;
	uint8_t             pin;
	E_GPIO_PORT_MODE    up_mode;
	uint8_t             up_out;
	E_GPIO_PORT_MODE    down_mode;
	uint8_t             down_out;
} hal_fixed_gpio_list_t;

typedef struct
{
	E_GPIO_PORT_TYPES   port;
	uint8_t             pin;
	uint32_t        	intNo;
	bool 				risingEdge;
	bool 				fallingEdge;
	bool			 	enable;
	void 				(*callback)(uint8_t pin);
} hal_fixed_gpio_ext_cfg_list_t;

typedef struct
{
	uint8_t   key_id;
	uint8_t   key_io;
	bool      key_state;
	bool      key_toggle;
	bool      key_continue;
	uint16_t  key_hold_on_counts;
	uint8_t   key_trigger;
} key_scan_t;

typedef uint8_t trigger_mode_enum_t;
enum
{
  	LOW_LEVEL_TRIGGER  = 0,
	HIGH_LEVEL_TRIGGER = 1,
};

typedef struct 
{
  E_GPIO_PORT_TYPES   		port;
  uint8_t              	 	pin;
  trigger_mode_enum_t   	trigger_mode;
} hal_gpio_config_list_t;

//PWM
typedef struct 
{
	E_GPIO_PORT_TYPES   	port;
	uint8_t              	pin;
	trigger_mode_enum_t     trigger_mode;
	uint8_t               	loc;
} hal_pwm_gpio_config_list_t;

typedef uint8_t app_serial_type_enum_t;
enum
{
	TYPE_VCP_SERIAL         	      = 0,
	TYPE_UART_SERIAL             	  = 1,
	TYPE_SECONDARY_UART_SERIAL   	  = 2,
	HAL_COMMON_VIRTUAL_SERIAL 		  =	0,
	HAL_COMMON_UART1_SERIAL			  =	1,
	HAL_COMMON_UART2_SERIAL     	  =	2,
	HAL_COMMON_ZIGBEE_WIRELESS_SERIAL = 0xf0,
	HAL_COMMON_INVALID_SERIAL		  = 0xff,
};

typedef uint32_t app_uart_parity_type_enum_t;
enum
{
  UART_PARITY_NONE   = (0x00000000UL << 8),
  UART_PARITY_EVEN   = (0x00000002UL << 8),
  UART_PARITY_ODD    = (0x00000003UL << 8)
};

typedef enum
{
    SERIAL_VALIDATE_RESULT_SUCCESS       = 0,
    SERIAL_VALIDATE_RESULT_IN_PROGRESS   = 1,
    SERIAL_VALIDATE_RESULT_ALL_DROPPED   = 10,
    SERIAL_VALIDATE_RESULT_1B_DROPPED    = 11,
    SERIAL_VALIDATE_RESULT_2B_DROPPED    = 12,
    SERIAL_VALIDATE_RESULT_3B_DROPPED    = 13,
    SERIAL_VALIDATE_RESULT_4B_DROPPED    = 14,
    SERIAL_VALIDATE_RESULT_UNHANDLED     = 0xFF,
} serial_validate_result_t;

typedef serial_validate_result_t (* serial_validate_packet_t)(uint8_t port, uint8_t* data, uint32_t* length);
typedef void (* serial_on_packet_received_t)(bool is_timeout, uint8_t port, uint8_t* data, uint32_t length);

typedef enum _control_action_enum
{
	CONTROL_ACTION_OFF 			= 0,
	CONTROL_ACTION_ON  			= 1,
	CONTROL_ACTION_TOGGLE 		= 2,
	CONTROL_ACTION_PWM_OFF 		= 3,
	CONTROL_ACTION_PWM_ON  		= 4,
	CONTROL_ACTION_PWM_TOGGLE 	= 5,
	CONTROL_ACTION_END 			= 0xff,
} control_action_enum_t;

typedef enum
{
	BAUDRATE_256000 = 0 ,
	BAUDRATE_921600 ,
	BAUDRATE_1000000 ,
	BAUDRATE_1200 ,
	BAUDRATE_2400 ,
	BAUDRATE_4800 ,
	BAUDRATE_9600 ,
	BAUDRATE_14400 ,
	BAUDRATE_19200 ,
	BAUDRATE_28800 ,
	BAUDRATE_38400 ,
	BAUDRATE_50000 ,
	BAUDRATE_57600 ,
	BAUDRATE_76800 ,
	BAUDRATE_100000 ,
	BAUDRATE_115200 ,
	BAUDRATE_230400 ,
} hal_baudrate_sel_index_enum_t;

//typedef struct
//{
//	union
//	{
//		control_action_enum_t state;
//
//		struct
//		{
//			control_action_enum_t pwm_state;
//			uint8_t pwm_duty;
//		} pwm_config_t;
//	};
//	uint32_t time_ms;
//} led_list_t;

typedef struct
{
	control_action_enum_t state;
	uint32_t time_ms;
} led_list_t;

typedef struct _user_hal_pa_config
{
	bool pa_enable;
	uint8_t pa_tx_pin;
	uint8_t pa_rx_pin;
} user_hal_pa_config_t;

typedef struct _stack_zigbee_node_info
{
	uint16_t zigbee_panid;
	int8_t 	 phy_radio_tx_power;
	uint8_t  phy_radio_channel;
	uint8_t  stack_profile;
	uint8_t  zigbee_node_type;
	uint16_t zigbee_node_id;
	uint8_t  extended_panid[8];
	uint8_t  trust_center_eui64[8];
	uint8_t  parent_eui64[8];
	uint16_t parent_node_id;
	uint16_t security_mode;
	uint32_t parent_frame_counter;
	uint8_t  network_state;
	uint8_t  network_updateId;
	uint8_t  active_network_key_id;
	uint8_t  zigbee_radio_channel;
	uint8_t  reserved[2];
} stack_zigbee_node_info_t;

#define APP_GENERATED_IAS_ZONE_EVENT_CODE
#define APP_GENERATED_IAS_ZONE_EVENTS

#define APP_GENERATED_IAS_ZONE_EVENT_STRINGS

#define APP_GENERATED_ONOFF_EVENT_CONTEXT
#define APP_GENERATED_ONOFF_EVENT_CODE
#define APP_GENERATED_ONOFF_EVENTS

#define APP_GENERATED_ONOFF_EVENT_STRINGS
	  
#define APP_GENERATED_IAS_ZONE_EVENT_CONTEXT
	  
	 
// Code used to configure the cluster event mechanism
#define APP_GLOBAL_GENERATED_EVENT_CODE

// EmberEventData structs used to populate the EmberEventData table
#define APP_GLOBAL_GENERATED_EVENTS

#define APP_GLOBAL_GENERATED_EVENT_STRINGS

#define APP_GLOBAL_GENERATED_EVENT_CONTEXT_LENGTH 0

#define APP_GLOBAL_GENERATED_EVENT_CONTEXT

extern	int16u	g_report_target_node;
extern	int8u	g_report_target_ep;
extern  int32u 	systemGetMillisecondTick(void);

#define	Send_ZCL_ALL(Pr, Nd, Grp, Se, De, Cl, ZCL, cmd, Len, Data, Hop)	\
		Send_ZCL_MFG( Pr, Nd, Grp, Se, De, Cl, ZCL, 0, cmd, Len, Data, Hop )
#define	Send_ZCL_Full(Node, Grp, S_EP, D_EP, Clus, ZCL, cmd, Len, Data)	\
		Send_ZCL_ALL( HA_PROFILE_ID, Node, Grp, S_EP, D_EP, Clus, ZCL, cmd, Len, Data, ZA_MAX_HOPS )
#define	Send_ZCL_Frame(Node,		D_EP, Clus, ZCL, cmd, Length, Data)	\
		Send_ZCL_Full( Node, 0, 1,	  D_EP, Clus, ZCL, cmd, Length, Data )
#define	Send_ZCL_SrcEP(Node, S_EP, D_EP, Clus, ZCL, cmd, Length, Data)	\
		Send_ZCL_Full( Node, 0, S_EP, D_EP, Clus, ZCL, cmd, Length, Data )

#define halCommonGetInt32uMillisecondTick		stackSystemClockMs
#define stackSystemClockMs						systemGetMillisecondTick
#define stackSystemClockTick()					clock_time()

extern uint8_t g_app_global_token_data[48];

#define System_Time()	systemGetMillisecondTick()
#define app_system_time	System_Time

#define emberNetworkState()															app_get_network_state()
#define emberAfWriteServerAttribute(endpoint, cluster, attribute, data, dataType) 	app_write_server_attribute(endpoint, cluster, attribute, 0x0000, data, dataType)
#define emberAfReadServerAttribute(endpoint, cluster, attribute, data, length) 		app_read_server_attribute(endpoint, cluster, attribute, 0x0000, data, length)

#define app_device_reporting_cfg(cfg_count, is_add, endpoint, cluster, attribute, mfg_code, min_interval, max_interval, report_change, ...) \
		app_reporting_plugin_reporting_config_register(cfg_count, is_add, 0, endpoint, cluster, attribute, mfg_code, min_interval, max_interval, report_change, ##__VA_ARGS__)


#endif //__GLOBAL_COMMON_H__

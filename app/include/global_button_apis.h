#ifndef __GLOBAL_BUTTON_APIS_H__
#define __GLOBAL_BUTTON_APIS_H__

#include "global_common.h"

typedef enum
{
    BUTTON_EV_SINGLE_CLICK = 1,
    BUTTON_EV_DOUBLE_CLICK,
    BUTTON_EV_TRIPLE_CLICK,
    BUTTON_EV_LONG_PRESS_MODE_1_RELEASE,
    BUTTON_EV_LONG_PRESS_MODE_2_RELEASE,
    BUTTON_EV_LONG_PRESS_MODE_3_RELEASE,
    BUTTON_EV_LONG_PRESS_MODE_4_RELEASE,
    BUTTON_EV_LONG_PRESS_MODE_1_IMMEDIATE,
    BUTTON_EV_LONG_PRESS_MODE_2_IMMEDIATE,
    BUTTON_EV_LONG_PRESS_MODE_3_IMMEDIATE,
    BUTTON_EV_LONG_PRESS_MODE_4_IMMEDIATE,
    BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_1_CLICK,
    BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_2_CLICK,
} button_ev_type_t;

typedef uint32_t button_ev_event_bitmap_t;

#define BUTTON_EV_EVENT_MASK(type) \
    (1UL << ((uint32_t)(type) - 1UL))

#define BUTTON_EV_EVENT_MASK_SINGLE_CLICK \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_SINGLE_CLICK)
#define BUTTON_EV_EVENT_MASK_DOUBLE_CLICK \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_DOUBLE_CLICK)
#define BUTTON_EV_EVENT_MASK_TRIPLE_CLICK \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_TRIPLE_CLICK)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_1_RELEASE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_1_RELEASE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_2_RELEASE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_2_RELEASE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_3_RELEASE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_3_RELEASE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_4_RELEASE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_4_RELEASE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_1_IMMEDIATE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_1_IMMEDIATE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_2_IMMEDIATE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_2_IMMEDIATE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_3_IMMEDIATE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_3_IMMEDIATE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_4_IMMEDIATE \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_MODE_4_IMMEDIATE)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_THEN_MULTI_MODE_1_CLICK \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_1_CLICK)
#define BUTTON_EV_EVENT_MASK_LONG_PRESS_THEN_MULTI_MODE_2_CLICK \
    BUTTON_EV_EVENT_MASK(BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_2_CLICK)
#define BUTTON_EV_EVENT_MASK_ALL \
    (0xFFFFFFFFUL)

#define BUTTON_EV_LONG_PRESS_MODE_MAX            (4U)
#define BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_MAX (2U)

typedef struct
{
    button_ev_type_t type;
    uint8_t          key_id;
    uint8_t          key_io;
    uint16_t         hold_ticks;
    uint32_t         hold_ms;
    uint8_t          click_count;
} button_ev_data_t;

typedef void (*button_ev_callback_t)(const button_ev_data_t* ev);
typedef struct
{
    uint8_t key_id;
    button_ev_event_bitmap_t event_bitmap;
    button_ev_callback_t callback;
} button_ev_bind_item_t;


typedef struct
{
    // 对应原 app_button_plugin_v2_register 的三个参数
    uint16_t button_hold_on_counter_tick_ms;
    uint16_t button_hold_on_max_counts;
    uint8_t  button_debounce_counts;

    // 单/双/三击判定窗口（ms），设置为0时关闭双击/三击检测，短按抬手立刻触发单击
    uint16_t click_gap_ms;

    // 按键点击事件屏蔽时间（ms），设置为0表示关闭屏蔽
    // 当某个按键触发单击/双击/三击事件后，在该时间窗口内该按键的单/双/三击无效
    uint16_t click_block_ms;

    // 4档长按按住立即触发阈值（ms），为0表示该档关闭
    uint16_t long_press_immediate_mode_ms[BUTTON_EV_LONG_PRESS_MODE_MAX];

    // 4档长按抬手触发阈值（ms），为0表示该档关闭
    uint16_t long_press_release_mode_ms[BUTTON_EV_LONG_PRESS_MODE_MAX];

    // 2档“长按后连按”配置
    // long_press_then_multi_mode_ms: 长按触发阈值（ms），0表示该档关闭
    // click_gap_ms:      连按间隔窗口（ms）
    // click_times:       连按次数（m）
    uint16_t long_press_then_multi_mode_ms[BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_MAX];
    uint16_t long_press_then_multi_click_gap_ms[BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_MAX];
    uint8_t  long_press_then_multi_click_times[BUTTON_EV_LONG_PRESS_THEN_MULTI_MODE_MAX];
} button_ev_config_t;

/** 介绍：hal button ev plugin注册，统一完成事件参数配置 + 全局回调配置 + button扫描插件挂接
 *		  注：该函数会引用app_button_plugin_v2_register作为基础实现，无法同时与app_button_plugin_v2_register共用
 *  参数：ev_cfg                         : button ev参数；为NULL时使用默认值
 *        default_callback               : 全局事件回调，为NULL时不回调
 *        bind_list                      : 按键绑定列表；为NULL或bind_count=0时，不执行一次性绑定
 *        bind_count                     : bind_list元素个数
 *  返回： true - 注册成功， false - 注册失败
 *  e.g.
 *  button_ev_config_t cfg =
 *  {
 *      .button_hold_on_counter_tick_ms = 25,
 *      .button_hold_on_max_counts = 800,
 *      .button_debounce_counts = 2,
 *      .click_gap_ms = 0, // 设置为0时，不检测双击/三击，短按抬手立即上报单击
 *      .click_block_ms = 250, // 250ms内屏蔽该按键后续单/双/三击
 *      .long_press_immediate_mode_ms = {3000, 5000, 10000, 20000},
 *      .long_press_release_mode_ms = {3000, 5000, 10000, 20000},
 *      .long_press_then_multi_mode_ms = {3000, 5000},
 *      .long_press_then_multi_click_gap_ms = {300, 250},
 *      .long_press_then_multi_click_times = {2, 3},
 *  };
 *
 *  button_ev_bind_item_t bind_list[] =
 *  {
 *      {
 *          .key_id = DEVICE_TEST_KEY_ID,
 *          .event_bitmap = BUTTON_EV_EVENT_MASK_SINGLE_CLICK |
 *                          BUTTON_EV_EVENT_MASK_DOUBLE_CLICK |
 *                          BUTTON_EV_EVENT_MASK_TRIPLE_CLICK,
 *          .callback = user_test_key_event_callback,
 *      },
 *  };
 *
 *  app_button_ev_plugin_register(&cfg, user_button_default_event_callback, bind_list, 1);
 *
 *  // 注册完成后，仍然可以通过bind/unbind接口动态增删按键事件绑定
 *  app_button_ev_bind_key_callback(DEVICE_TEST_KEY2_ID,
 *                              	BUTTON_EV_EVENT_MASK_SINGLE_CLICK |
 *                              	BUTTON_EV_EVENT_MASK_DOUBLE_CLICK |
 *                              	BUTTON_EV_EVENT_MASK_TRIPLE_CLICK |
 *                              	BUTTON_EV_EVENT_MASK_LONG_PRESS_MODE_1_IMMEDIATE,
 *                              	user_test_key2_event_callback);
 */
bool app_button_ev_plugin_register(const button_ev_config_t* ev_cfg,
                                   button_ev_callback_t default_callback,
                                   const button_ev_bind_item_t* bind_list,
                                   uint8_t bind_count);

bool app_button_ev_bind_key_callback(uint8_t key_id,
									 button_ev_event_bitmap_t event_bitmap,
									 button_ev_callback_t cb);
void app_button_ev_unbind_key_callback(uint8_t key_id);

/** 介绍：hal button v2 plugin注册，用于可回弹开关的注册
 *	参数： button_hold_on_counter_tick_ms : 检测计次间隔 / ms
 *		  button_hold_on_max_counts  	 : 最大计次次数，到达该值后停止计次任务（主要针对zed设备，存在异常按键时及时停止任务减小功耗）
 *		  button_debounce_counts 		 : 按键消抖次数，小于该次数不会进入pressed和released, 最小值为1
 *		  pressed_callback				 : 当为NULL时，回调仍然使用V1版本的 void app_io_press_callback(key_scan_t key),
 *		  								      不为NULL时，按键按住时进入注册的pressed_callback，注意参数为key_scan_t* key
 *		  released_callback				 : 当为NULL时，回调仍然使用V1版本的 void app_io_release_callback(key_scan_t key),
 *		  								      不为NULL时，按键抬起进入注册的released_callback，注意参数为key_scan_t* key
 *	返回:-
 *	e.g.
 *	设置PC0,硬件为按下时低电平， 检测间隔25ms, 最大计次次数800次（25 * 800）20s后超时结束计次任务
 *	-------------------------------------------------------------
 *	pin_def.h
 *	-------------------------------------------------------------
 *	#define DEVICE_RESET_KEY_ID					  0
 *	#define HAL_BUTTON_PIN_LIST \
 *	{\
 *		{PORTC,	0,	LOW_LEVEL_TRIGGER}, 		  \
 *	}
 *	-------------------------------------------------------------
 *	插件注册:
 *	兼容V1版本时参考以下使用
 *	app_button_plugin_v2_register(25, 800, 2, NULL, NULL);
 *
 *	触发的按下检测回调函数
 *	void app_io_press_callback(key_scan_t key)
 *	{
 *		//in app_button_plugin_register(25, 800); we config check interval 25ms, key.key_hold_on_counts = 200, | 200 * 25 = 5000ms
 *		if( (key.key_id == DEVICE_RESET_KEY_ID) && (key.key_hold_on_counts == 200) )
 *		{
 *			...
 *		}
 *	}
 *
 *	触发的抬起检测回调函数
 *	void app_io_release_callback(key_scan_t key)
 *	{
 *
 *	}
 *	或
 *	app_button_plugin_v2_register(25, 800, 2, user_button_pressed_callback, user_button_released_callback);
 *
 *	触发的按下检测回调函数
 *	void user_button_pressed_callback(key_scan_t* key)
 *	{
 *		if( (key->key_id == DEVICE_RESET_KEY_ID) && (key->key_hold_on_counts == 200) )
 *		{
 *			...
 *		}
 *	}
 *
 *	触发的抬起检测回调函数
 *	void user_button_released_callback(key_scan_t* key)
 *	{
 *		if( (key->key_id == DEVICE_RESET_KEY_ID) && (key->key_hold_on_counts >= 200) )
 *		{
 *			...
 *		}
 *	}
 */
//建议使用新的app_button_ev_plugin_register, 按键事件注册函数
void app_button_plugin_v2_register(uint16_t button_hold_on_counter_tick_ms,
								   uint16_t button_hold_on_max_counts,
								   uint8_t  button_debounce_counts,
								   void (*pressed_callback)(key_scan_t* key),
								   void (*released_callback)(key_scan_t* key));
//V1 : DEPRECATED API
		void app_button_plugin_register(uint16_t button_hold_on_counter_tick_ms, uint16_t button_hold_on_max_counts)  __attribute__((deprecated));


/** 介绍：hal contact plugin注册，用于支持双向开关检测
 *	参数： debounce_counter_tick_ms : 消抖检测间隔  / ms
 *		contact_debounce_counts  : 消抖检测次数
 *	返回:-
 *	e.g.
 *	设置PC0,消抖检测间隔25ms, 连续检测到6次触发回调
 *	-------------------------------------------------------------
 *	pin_def.h
 *	-------------------------------------------------------------
 *	#define DOOR_SENSOR_DETECT_CONTACT_ID 		0
 *	#define DOOR_SENSOR_DETECT_OPEN_STATE 		LOW_LEVEL_TRIGGER
 *
 *	#define HAL_CONTACT_PIN_LIST \
 *	{\
 *	  {PORTC,	0,	DOOR_SENSOR_DETECT_OPEN_STATE},             \
 *	}
 *	-------------------------------------------------------------
 *	插件注册:
 *	app_contact_plugin_register(25, 6);
 *
 *	触发的回调函数
 *	注： contact_state ：   contact_state不是表示电平状态
 *					   true  - 表示当前状态与HAL_CONTACT_PIN_LIST中设置（DOOR_SENSOR_DETECT_OPEN_STATE）的状态一致
 *					   false - 表示当前状态与HAL_CONTACT_PIN_LIST中设置（DOOR_SENSOR_DETECT_OPEN_STATE）的状态不一致
 *	void app_contact_changed_callback(uint8_t contact_id, uint8_t contact_io, bool contact_state)
 *	{
 *		if(contact_id == DOOR_SENSOR_DETECT_CONTACT_ID)
 *		{
 *			if(contact_state)
 *				...
 *		}
 *	}
 */
void app_contact_plugin_register(uint16_t debounce_counter_tick_ms, uint16_t contact_debounce_counts);

#endif

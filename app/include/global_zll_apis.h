#ifndef __GLOBAL_ZLL_APIS_H__
#define __GLOBAL_ZLL_APIS_H__

/** 介绍：zll initiator plugin注册，用于支持标准zll comm流程，initiator用于遥控设备
 *	参数： rssi_min 	  : 可自定义设置, 用于touch link过程中过滤小于该rssi的信号，建议值 : 大于-35
 *		  handle_list : zll initiator plugin设置为NULL
 *	返回:-
 *
 *	e.g.
 *	app_zll_initiator_plugin_register(-35, NULL);
 */
void app_zll_initiator_plugin_register(int8_t rssi_min, stack_application_zcl_handle_t* handle_list);

/** 介绍：zll initiator发起发现连接设备
 *	参数： extended_scan 	  : true  - 扫描信道为[11, 15, 20, 25]以及[12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26]
 *							false - 扫描信道为[11, 15, 20, 25]
 *	返回:-
 *
 *	e.g.
 *	app_zll_initiator_scan_start(false);
 *	注： 通常遥控器使用false, 扫描primary channel即可，可以根据具体使用情景变更
 *
 *	可能使用到的回调
 *	参照weak_function.c里的函数回调说明
 * 	void app_zll_initiator_comm_state(zll_initiator_comm_state_t state);
 * 	void app_zll_initiator_link_target_callback(uint16_t node_id, uint8_t* mac);
 */
void app_zll_initiator_scan_start(bool extended_scan);


/** 介绍：zll initiator发送touch reset
 *	参数： extended_scan 	  : true  - 扫描信道为[11, 15, 20, 25]以及[12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26]
 *							false - 扫描信道为[11, 15, 20, 25]
 *	返回:-
 */
void app_zll_initiator_touch_reset(bool extended_scan);


/** 介绍：zll target plugin注册，用于支持标准zll comm流程，target用于灯具设备
 *	参数： rssi_min 	      : 可自定义设置, 用于touch link过程中过滤小于该rssi的信号，建议值 : 大于-35
 *		  rssi_correction : rssi补偿值，用于自己和遥控设备的rssi补偿（外壳对rssi影响），范围0 ~ 32
 *		  zll_identify_handle : zll identify命令回调
 *		  handle_list 	  : zll target plugin设置为NULL
 *	返回:-
 *
 *	e.g.
 *	注：duration单位： 秒， 为0xffff时，设备需根据自己的默认值进行处理（如10s）,而不是使用0xffff秒。
 *	bool app_zll_identify_handler(uint16_t duration)
 *	{
 *		...
 *		//light bink event
 *		...
 *		return true;
 *	}
 *	app_zll_target_plugin_register(-35, 10, app_zll_identify_handler, NULL);
 */
void app_zll_target_plugin_register(int8_t rssi_min,
									uint8_t rssi_correction,
									bool (*zll_identify_handle)(uint16_t duration),
									stack_application_zcl_handle_t* handle_list);

#endif

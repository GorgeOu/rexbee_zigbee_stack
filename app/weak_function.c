
#include "include/global_apis.h"

char const c_app_build_time_stack_use[] = { __DATE__ __TIME__ }; //don't modify

//#if defined(APP_RELEASE_VERSION_MAJOR) &&
//	defined(APP_RELEASE_VERSION_MINOR) &&
//	defined(APP_RELEASE_VERSION_PATCH)
////base on Semantic Versioning 2.0.0
////MAJOR.MINOR.PATCH
////e.g. :  1.2.1
//char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify
//#else
//
//#endif

/**
 *
 stack init callbacks timing :
	app_general_pre_hal_config(...) -> {do internal hal init} -> app_hal_uart_config(...) -> app_hal_config(...) ->
	{do simeep init} -> app_get_token_data_to_ram_callback(...) -> app_post_token_init_callback(...) ->
	stack_key_parameter_configuration(...) -> {do some stack memory alloc & network parameter init} ->
	app_post_endpoint_config_callback(...) -> {do cluster & attribute list init} ->
	app_plugin_init_callback(...) -> app_main_init_callback(...)

{sleep wakeup} :
	app_general_pre_hal_config(...) -> {do internal hal init} -> app_hal_uart_config(...) -> app_hal_config(...) -> sleep_wakeup_callback() -> (ext trigger, e.g. io wakeup)app_keep_wakeup_ext_trigger_callback
 	-> app_ok_to_sleep_callback(...)
 *
 **/

/**
 *
 network message callbacks timing :
 app_pre_message_handler(...) -> {check message type} ->
 1. zdo : app_pre_zdo_handler(...) -> {zdo register handle} -> {release message}
 2. zcl : app_pre_command_handler(...) -> {do plugin command handle} ->
    2.1 : {plugin handle success} -> {release message}
    2.2 : {no plugin register this command} -> {check zcl message type} ->
    	2.2.1 client to server : app_cluster_specific_c2s_command_parse(...) -> {release message}
    	2.2.2 server to client : app_cluster_specific_s2c_command_parse(...) -> {release message}
 *
 **/

/**
 *
 network scan callbacks timing :
	{do app_scan_network_v2_start(...) call} ->
 	 	app_scan_network_process_init_callback(...) -> {cycle} app_scan_network_process_indicate(...) ->
 	 	{check joined network & timeout} ->
 	 	 	1. {joined network} -> app_stack_status_callback(...) ->
 	 	 		app_integrated_network_state_changed_callback(...)
 	 	 	    app_scan_network_process_joined_callback(...) ->
 	 	 	    app_device_fresh_start_callback(...)
 	 	 	2. {scan timeout} -> app_scan_network_process_timeout_callback(...)
 *
 **/

__weak void app_main_init_callback(void)
{

}

__weak void app_main_tick_callback(void)
{

}

__weak void app_general_pre_hal_config(void)
{

}

__weak void app_hal_config(void)
{

}

__weak void app_hal_uart_config(void)
{
	app_serial_init(TYPE_VCP_SERIAL,
					PORTD_PIN(7),
					0,
					1000000,
					0,
					0);

	app_serial_init(TYPE_UART_SERIAL,
					PORTB_PIN(1),
					PORTC_PIN(3),
					115200,
					UART_PARITY_NONE,
					1);
}

__weak void stack_key_parameter_configuration(void)
{

}

__weak void app_scan_network_process_init_callback(void)
{

}

__weak void app_scan_network_process_indicate(void)
{

}

__weak void app_scan_network_process_joined_callback(void)
{

}

__weak void app_scan_network_process_timeout_callback(void)
{

}

__weak void app_scan_network_process_zbck_connected_callback(void)
{

}

__weak void app_scan_network_process_zbck_joined_callback(void)
{

}

__weak void app_scan_network_process_zbck_disconnected_callback(void)
{

}

__weak void app_fast_join_process_init_callback(void)
{

}

__weak void app_fast_join_process_indicate_callback(void)
{

}

__weak void app_fast_join_process_joined_callback(void)
{

}

__weak void app_fast_join_process_timeout_callback(void)
{

}

__weak bool app_uart_frame_check(uint8_t* data, uint8_t length)
{
	return false;
}

__weak bool app_uart_frame_clip_check(uint8_t* data, uint32_t* length)
{
	if(app_uart_frame_check(data, (uint8_t)((uint32_t)(*length))))
	{
		return true;
	}

	return false;
}

__weak void app_process_uart_data(uint8_t* data, uint8_t length)
{

}

__weak void app_process_long_uart_data(uint8_t* data, uint32_t length)
{
	app_process_uart_data(data, (uint8_t)length);
}

__weak bool app_pre_message_handler(EmberAfIncomingMessage* incoming_message)
{
	return false;
}

__weak bool app_pre_zdo_handler(uint16_t node_id, EmberApsFrame* apsFrame, uint8_t* message, uint16_t length)
{
	return false;
}

__weak bool app_pre_command_handler(EmberAfClusterCommand* command)
{
    return false;
}

__weak bool app_post_attr_change_handler(uint8_t  endpoint,
										    uint16_t cluster_id,
										    uint16_t attribute_id,
										    uint8_t	 mask,
										    uint16_t manufacturer_code,
										    uint8_t	 type,
										    uint8_t	 size,
										    uint8_t* value)
{ 
	return false;
}

__weak bool app_pre_message_send_callback(EmberAfMessageStruct* messageStruct, EmberStatus* status)
{
	return false;
}

/**介绍：系统复位指示
*  参数：无
*  返回：无
*/
__weak void app_rex_system_reset_indicate(void)
{

}

__weak void app_second_tick_callback(void)
{

}

__weak void app_plugin_init_callback(void)
{

}

extern void app_group_plugin_register(uint8_t group_name_support_max_length, stack_application_zcl_handle_t* handle_list); //reserved for expansion

#if defined(BTL_XMODEM_UPGRADE_SUPPORT)
extern 	void app_xmodem_upgrade_handler_register(void);
#endif

__weak void app_universal_plugin_init_callback(void)
{
	app_group_plugin_register(0, NULL);
	app_scene_plugin_register(NULL, 0, 0, NULL); //about 5k
	app_aps_message_filter_plugin_register();

#if defined(BTL_XMODEM_UPGRADE_SUPPORT)
#warning "bootloader xdodem upgrade support"
	app_xmodem_upgrade_handler_register();
#endif
}

__weak void app_get_token_data_to_ram_callback(void)
{

}

__weak void app_post_token_init_callback(void)
{
	//optional call app_nvm_attribute_storage_plugin_register() in application
}

/**介绍 ： ZED重连成功回调（ZED专属回调）
 * 参数： 无
 * 返回： 无
 */
__weak void app_device_rejoin_successful_callback(void)
{

}

__weak void app_post_endpoint_config_callback(void)
{

}

__weak void app_stack_status_callback(EmberStatus status)
{

}

__weak void app_stack_status_changed_callback(EmberStatus status,
											  EmberNetworkStatus last_network_state,
											  EmberNetworkStatus network_state)
{
	app_stack_status_callback(status);
}

__weak bool app_message_transmit_result_callback(EmberOutgoingMessageType type,
												 uint16_t dest_node_id,
												 EmberApsFrame* aps_frame,
												 uint16_t message_length,
												 uint8_t* message,
												 EmberStatus status)
{
	return false;
}

__weak bool app_message_sent_callback(EmberOutgoingMessageType type,
									  uint16_t			index_Or_destination,
									  EmberApsFrame*	aps_frame,
									  uint16_t			message_length,
									  uint8_t*			message,
									  EmberStatus		status)
{
    return app_message_transmit_result_callback(type, index_Or_destination, aps_frame, message_length, message, status);
}

/**介绍：设备入网或重启检测到入网，检测回调
*  参数：无
*  返回：无
*/
__weak void app_device_fresh_start_callback(void)
{

}

__weak void app_integrated_network_state_changed_callback(uint8_t state)
{

}

__weak void app_end_device_common_poll_result_callback(EmberStatus status)
{

}

/**介绍：离网成功触发回调
*  参数：无
*  返回：无
*/
__weak void app_leave_network_detected_callback(void)
{

}

/**介绍：led task 第一优先级任务关闭时进入回调
*  参数：无
*  返回：无
*/
__weak void app_highest_priority_task_cancel_callback(uint8_t control_pin_list_index, led_list_t* task)
{

}

/**介绍：led task 对应control pin index无存在led task时进入回调
*  参数：control_pin_list_index ： 0xff 所有引脚不存在任何led task, [0 , 31]对应的control pin index不存在led task
*  返回：无
*/
__weak void app_control_pin_no_led_task_callback(uint8_t control_pin_list_index)
{

}

/**介绍 :  虚拟gpio操作回调（PORTM_PIN(x)）
*  参数 :  io    : PORTM_PIN(x)
*  		  level : true - high, false - low
*  返回 :  无
*/
__weak void app_hal_virtual_gpio_output_callback(uint8_t io, bool level)
{

}

/**介绍 :  V1按键插件按下回调保留，现在推荐使用V2自行注册
*  参数 :  key    : 触发按键信息
*  返回 :  无
*/
__weak void app_io_press_callback(key_scan_t key)
{

}

/**介绍 :  V1按键插件抬起回调保留，现在推荐使用V2自行注册
*  参数 :  key    : 触发按键信息
*  返回 :  无
*/__weak void app_io_release_callback(key_scan_t key)
{

}

/**介绍 :  产测状态变更回调
 * 参数 :  state : 参照 app_mfg_mt_state_enum_t
 * 返回 :  无
 */
__weak void app_mass_production_test_status_changed_callback(uint8_t state)
{

}

__weak void app_rex_vain_network_joined_callback(void)
{

}


/**介绍 ：  zcl on off plugin on off属性变更回调(已经调用写属性，用户无需再写on off属性)
 * 参数 ：  trigger type : 参照 app_write_attribute_trigger_type_enum_t
 * 		  endpoint	   : 触发端点号
 * 		  last_onoff_status		 : 变更前的状态
 * 		  current_onoff_status   ： 变更后的状态（当前属性状态）
 * 返回: result : true - 不再次进入post attribute change callback, false - 允许进入post attribute change callback
 */
__weak bool app_onoff_plugin_onoff_status_callback(uint8_t trigger_type,
												   uint8_t endpoint,
												   bool last_onoff_status,
												   bool current_onoff_status)
{
	return false;
}

__weak bool app_move_to_level_start_callback(uint8_t  endpoint,
											 uint8_t  current_level,
											 uint8_t  target_level,
											 uint32_t transition_time_ms)
{
	return false;
}

/**介绍 ：  zcl level plugin level命令触发回调(未调用写属性，用户需要写level属性)
 * 参数 ：  trigger type : 参照 app_write_attribute_trigger_type_enum_t
 * 		  endpoint	   : 触发端点号
 * 		  current_level	 : 当前level(未变更前的值)
 * 		  target_level   ： 目标level（目标的变更值）
 * 		  transition_time_ms : 渐变时长，单位ms
 * 		  option : -
 * 返回: result : true - 用户自行处理渐变，写属性, false - 交由协议栈处理渐变，写属性
 * 注：协议栈处理渐变为固定10ms间隔，很难满足用户需要，建议根据灯情况自行处理
 */
__weak bool app_level_plugin_level_change_start_callback(uint8_t  trigger_type,
														 uint8_t  endpoint,
														 uint8_t  current_level,
														 uint8_t  target_level,
														 uint32_t transition_time_ms,
														 uint8_t* option)
{
	if(app_move_to_level_start_callback(endpoint, current_level, target_level, transition_time_ms))
	{
		return true;
	}

	return false;
}

__weak void app_move_to_level_finish_callback(uint8_t endpoint, uint8_t current_level)
{

}

__weak void app_level_plugin_level_change_stop_callback(uint8_t trigger_type, uint8_t endpoint, uint8_t current_level)
{
	app_move_to_level_finish_callback(endpoint, current_level);
}

__weak bool app_move_to_color_start_callback(uint8_t  endpoint,
											 uint16_t current_temperature_value,
											 uint16_t target_temperature_value,
											 uint8_t  current_hue_value,
											 uint8_t  target_hue_value,
											 uint8_t  current_saturation_value,
											 uint8_t  target_saturation_value,
											 bool     is_hue_mode_up,
											 uint32_t transition_time_ms)
{
	return false;
}

__weak void app_move_to_color_finish_callback(uint8_t  endpoint,
											  uint16_t current_temperature_value,
											  uint8_t  current_hue_value,
											  uint8_t  current_saturation_value)
{

}

/**介绍 ：  zcl color plugin - xyY 命令触发回调(未调用写属性，用户需要写对应的color control属性)
 * 参数 ：  trigger type : 参照 app_write_attribute_trigger_type_enum_t
 * 		  endpoint	   : 触发端点号
 * 		  current_x_value	 : 当前x值(未变更前的值)
 * 		  target_x_value     ： 目标x值（目标的变更值）
 * 		  current_y_value	 : 当前y值(未变更前的值)
 * 		  target_y_value     ： 目标y值（目标的变更值）
 * 		  x_transition_time_ms : x渐变时长，单位ms
 * 		  y_transition_time_ms : y渐变时长，单位ms
 * 返回: result : true - 用户自行处理渐变，写属性, false - 交由协议栈处理渐变，写属性
 * 注：协议栈处理渐变为固定10ms间隔，很难满足用户需要，建议根据灯情况自行处理
 */
__weak bool app_color_plugin_color_xy_mode_change_start_callback(uint8_t  trigger_type,
														  uint8_t  endpoint,
														  uint16_t current_x_value,
														  uint16_t target_x_value,
														  uint16_t current_y_value,
														  uint16_t target_y_value,
														  uint32_t x_transition_time_ms,
														  uint32_t y_transition_time_ms)
{
	return false;
}

__weak void app_color_plugin_color_xy_mode_change_stop_callback(uint8_t  trigger_type,
														 uint8_t  endpoint,
														 uint16_t current_x_value,
														 uint16_t current_y_value)
{

}

/**介绍 ：  zcl color plugin - temperature命令触发回调(未调用写属性，用户需要写对应的color control属性)
 * 参数 ：  trigger type : 参照 app_write_attribute_trigger_type_enum_t
 * 		  endpoint	   : 触发端点号
 * 		  current_temperature_value	   : 当前色温值(未变更前的值)
 * 		  target_temperature_value     : 目标色温值（目标的变更值）
 * 		  transition_time_ms 		   : 色温渐变时长，单位ms
 * 返回: result : true - 用户自行处理渐变，写属性, false - 交由协议栈处理渐变，写属性
 * 注：协议栈处理渐变为固定10ms间隔，很难满足用户需要，建议根据灯情况自行处理
 */
__weak bool app_color_plugin_color_temperature_change_start_callback(uint8_t  trigger_type,
																	 uint8_t  endpoint,
																	 uint16_t current_temperature_value,
																	 uint16_t target_temperature_value,
																	 uint32_t transition_time_ms)
{
	if(app_move_to_color_start_callback(endpoint,
										current_temperature_value,
										target_temperature_value,
										0xff,
										0xff,
										0xff,
										0xff,
										false,
										transition_time_ms))
	{
		return true;
	}

	return false;
}

__weak void app_color_plugin_color_temperature_change_stop_callback(uint8_t  trigger_type,
															 uint8_t  endpoint,
															 uint16_t current_temperature_value)
{
	app_move_to_color_finish_callback(endpoint, current_temperature_value, 0xff, 0xff);
}

/**介绍 ：  zcl color plugin - temperature命令触发回调(未调用写属性，用户需要写对应的color control属性)
 * 参数 ：  trigger type : 参照 app_write_attribute_trigger_type_enum_t
 * 		  endpoint	   : 触发端点号
 * 		  current_hue_value	   		: 当前色度值(未变更前的值)
 * 		  target_hue_value     		: 目标色度值（目标的变更值）
 * 		  current_saturation_value	: 当前饱和度值(未变更前的值)
 * 		  target_saturation_value   : 目标饱和度值（目标的变更值）
 * 		  is_hue_mode_up 			: 色度变化方向，单位ms
 * 		  transition_time_ms 		: 色彩渐变时长，单位ms
 * 返回: result : true - 用户自行处理渐变，写属性, false - 交由协议栈处理渐变，写属性
 * 注：协议栈处理渐变为固定10ms间隔，很难满足用户需要，建议根据灯情况自行处理
 */
__weak bool app_color_plugin_color_hue_and_saturation_change_start_callback(uint8_t  trigger_type,
																	 uint8_t  endpoint,
																	 uint8_t  current_hue_value,
																	 uint8_t  target_hue_value,
																	 uint8_t  current_saturation_value,
																	 uint8_t  target_saturation_value,
																	 bool     is_hue_mode_up,
																	 uint32_t transition_time_ms)
{
	if(app_move_to_color_start_callback(endpoint,
										0xffff,
										0xffff,
										current_hue_value,
										target_hue_value,
										current_saturation_value,
										target_saturation_value,
										is_hue_mode_up,
										transition_time_ms))
	{
		return true;
	}

	return false;
}


__weak void app_color_plugin_color_hue_and_saturation_change_stop_callback(uint8_t  trigger_type,
																		   uint8_t  endpoint,
																		   uint8_t  current_hue_value,
																		   uint8_t  current_saturation_value)
{
	app_move_to_color_finish_callback(endpoint, 0xffff, current_hue_value, current_saturation_value);
}

__weak bool app_color_plugin_color_loop_set_callback(uint8_t trigger_type,
													 uint8_t endpoint,
													 uint8_t active,
													 uint16_t time,
													 bool hue_up_mode,
													 uint16_t start_hue)
{
	return false;
}

/*
 *  stop_mode : 参照app_color_plugin_stop_mode_enum_t
 */
__weak bool app_color_plugin_color_change_stop_callback(uint8_t trigger_type, uint8_t endpoint, uint8_t stop_mode)
{
	return false;
}

/**介绍 :  zcl window covering plugin - 命令触发回调(未调用写属性，用户需要写对应的window convering属性)
 * 参数 :  trigger type   : 参照 app_write_attribute_trigger_type_enum_t
 * 		  endpoint	     : 触发端点号
 * 		  action	     : 窗帘动作，参照window_convering_action_enum_t
 * 		  current_value	 : 当前窗帘位置值(未变更前的值)
 * 		  target_value   : 目标窗帘位置值（目标的变更值）
 * 返回: result : true - 无作用
 * 注： current_value和target_value仅在action为:
 * 	   WINDOEW_CONVERING_LIFT_VALUE/WINDOEW_CONVERING_LIFT_PERCENT/
 * 	   WINDOEW_CONVERING_TILT_VALUE/WINDOEW_CONVERING_TILT_PERCENT
 * 	      时有效
 */
__weak bool app_window_covering_plugin_window_status_callback(uint8_t trigger_type,
															  uint8_t endpoint,
															  window_convering_action_enum_t action,
															  uint16_t current_value,
															  uint16_t target_value)
{
	return false;
}

/** 介绍：zll initiator comm state回调，用于指示initiator touch link时的一些指示
 *	参数： state 	  :
 *	ZLL_INITIATOR_COMM_STATE_NOT_FOUND			-  touch scan未找到设备
 *	ZLL_INITIATOR_COMM_STATE_LINK_NO_RESP		-  touch scan未收到设备network resp
 *	ZLL_INITIATOR_COMM_STATE_LINK_NEW_TARGET	-  touch scan连接上新设备
 *	ZLL_INITIATOR_COMM_STATE_LINK_UPDATE		-  touch scan连接上旧设备
 *	ZLL_INITIATOR_COMM_STATE_TOUCH_RESET		-  touch scan发送touch reset命令
 * 	ZLL_INITIATOR_COMM_STATE_REJOIN_FAILURE		-  touch scan后重连失败
 *	返回:-
 */
__weak void app_zll_initiator_comm_state(zll_initiator_comm_state_t state)
{

}

/** 介绍：zll initiator连接target成功回调，用于指示initiator touch连接成功的指示
 *	参数：node_id : touch link连接成功设备的node id
 *		 mac     : touch link连接成功设备的mac
 *	返回:-
 */
__weak void app_zll_initiator_link_target_callback(uint16_t node_id, uint8_t* mac)
{

}

__weak void app_zll_initiator_link_target_v2_callback(bool new_target, uint16_t node_id, uint8_t* mac, zll_touch_link_device_info_t* endpoint_info, uint8_t endpoint_count)
{
	app_zll_initiator_link_target_callback(node_id, mac);
}

/**介绍：Cluster Command Client->Server 解析接口
*  参数：Cluster Command ：命令数据，result : 处理结果
*  返回：EmberAfStatus
*/
__weak EmberAfStatus app_cluster_specific_c2s_command_parse(EmberAfClusterCommand* command, EmberAfStatus result)
{	
	if(command->apsFrame->clusterId)
	{

	}

	return result;
}

/**介绍：Cluster Command Server->Client 解析接口
*  参数：Cluster Command ：命令数据，result : 处理结果
*  返回：EmberAfStatus
*/
__weak EmberAfStatus app_cluster_specific_s2c_command_parse(EmberAfClusterCommand *command, EmberAfStatus result)
{
	if(command->apsFrame->clusterId)
	{

	}

	return result;
}

/**介绍：无效的签名信息指示，在签名错误时持续调用
*  参数：无
*  返回：无
*/
__weak void app_detect_invalid_rexense_signature_indicate(void)
{

}

/**介绍：无效的签名回调
*  参数：无
*  返回：无
*/
__weak void app_detect_invalid_rexense_signature_callback(void)
{

}

/**介绍： 设备网络连接回调（入网成功或上电发现有网时回调）
 * 参数： event参考app_network_start_event_action_enum_t
 * 返回： 无
 */
__weak void app_device_network_start_callback(uint8_t event)
{

}

/**介绍： 设备网络离网回调
 * 参数： event参考leave_network_reason_store_t
 * 返回： 无
 */
__weak void app_device_network_leaved_callback(uint8_t event)
{

}

/**介绍： fota stub, 后续迭代支持
 * 参数： -
 * 返回： -
 */
__weak bool stack_is_fota_message_frame(void)
{
	return false;
}

/**介绍： fota stub, 后续迭代支持
 * 参数： -
 * 返回： -
 */
__weak bool stack_fota_common_mac_command_handler(uint8_t* data, uint16_t length)
{
	return false;
}


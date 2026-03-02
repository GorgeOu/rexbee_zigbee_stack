#ifndef __GLOBAL_APIS_H__
#define __GLOBAL_APIS_H__

#include "global_common.h"
#include "zcl-global-command-desc.h"
#include "zcl-spec-command-desc.h"
#include "zcl-attr-desc.h"
#include "global_string_util_apis.h"
#include "global_hal_common_apis.h"
#include "global_zll_apis.h"
#include "global_mass_production_test_apis.h"
#include "global_nvm_apis.h"
#include "global_binding_mgmt_apis.h"
#include "global_group_scene_apis.h"
#include "global_message_apis.h"
#include "global_nwk_mgmt_apis.h"
#include "global_mem_heap_apis.h"
#include "fast_join_apis.h"
#include "uart_message_queue.h"
#include "global_button_apis.h"

#include "device/sim_win_panel.h"

/**介绍： 设备mac地址获取接口
*  参数: result : 8字节mac地址存储数组, 拷贝8字节mac地址数据至result
*  返回： -
*/
void app_get_mac_address(uint8_t* result);

/**介绍： 仅ZED设备有效，将ZED设置为非休眠模式，RX常开，需要在stack_key_parameter_configuration中调用
*  参数: -
*  返回： -
*/
void stack_set_non_sleepy_end_device(void);

/**介绍：设备清空全部binding table和scene table(需在离网后手动调用)
*  参数: -
*  返回： -
*/
void stack_clear_used_table(void);

/**介绍：获取当前无线处理内容指针
*  参数：-
*  返回：当前无线处理内容指针
*/
EmberAfClusterCommand* app_get_current_remote_command(void);
#define emberAfCurrentCommand() app_get_current_remote_command()

/**介绍：发送ZCL协议帧
*  参数：-
*  返回：返回写入缓存区结果
*/
uint8_t app_send_zcl_mfg(uint16_t profile, uint16_t node_id, uint16_t group, uint8_t source_ep, \
						 uint8_t dest_ep, uint16_t cluster_id, uint8_t zcl_frame, uint16_t manufacture_code, \
						 uint8_t command_id, uint8_t length, uint8_t* data, uint8_t hops);

/**介绍：发送ZCL协议帧, 指定aps option和zcl seq
 * 		aps option可以使用默认值
 * 		EmberApsOption app_get_zcl_message_default_option(void);
 *		或者自己根据EmberApsOption组合
 *  参数：-
 *  返回：返回写入缓存区结果
 */
uint8_t app_send_zcl_message(uint16_t profile, uint16_t dest_node, uint16_t group, uint8_t source_ep, uint8_t dest_ep,
						 	 uint16_t cluster, uint8_t zcl_frame, uint16_t mfg_code, uint8_t zcl_command,
						 	 uint8_t length, uint8_t* data, EmberApsOption option, uint8_t hops, uint8_t zcl_seq);

/**介绍：发送ZDO协议帧
*  参数：-
*  返回：返回写入缓存区结果
*/
uint8_t app_send_zdo_msg_hops(uint16_t dest_node_id, uint16_t cluster_id, uint8_t length, \
							  uint8_t* data, uint16_t option, uint8_t hops);

/**介绍：ZCL Report发送接口
* 参数：
* 返回：0 - 成功, 其他 - 失败
*/
uint8_t app_device_report_attr_mfg(uint16_t dest_node_Id, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster_id, \
								   uint16_t attribute_id, uint8_t zcl_data_type, uint8_t* data, uint16_t manufacuture_code);

/**介绍：主动上报多属性集合
*  参数：-
*  返回：返回写入缓存区结果
*/
void app_device_report_multi_attr_mfg(uint16_t dest_node_id, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster_id, \
									  uint16_t manufacture_code, uint8_t attribute_entry_number, attribute_data_t* data);

/**介绍：zcl message format发送接口
*  参数：format : zcl command payload format -
*  				 '1' - uint8_t, map8, int8_t, bool, etc(1 byte type)...
*  				 '2' - uint16_t, map16, int16_t, etc(2 bytes type)...
*  				 '4' - uint32_t, map32, int32_t, etc(4 bytes type)...
*  				 's' - otc string type, [0] is length
*  				 'a' - array type, next arg is length
*  				 	   e.g.
*  				 	   app_send_unicast_formative_zcl_message(profile_id,
*															  ...
*															  zcl_command,
*															  "a", array_test, 64);
*  返回：0 - 成功, 其他 - 失败
*/
uint8_t app_send_unicast_formative_zcl_message(uint16_t profile_id,
											   uint16_t dest_node_id,
											   uint8_t  source_ep,
											   uint8_t  dest_ep,
											   uint16_t cluster_id,
											   bool     cluster_specific_command,
											   bool	  	client_to_server,
											   bool	  	disable_default_resp,
											   uint16_t manufacture_code,
											   uint8_t  zcl_command,
											   const char* format, ...);

EmberStatus app_send_broadcast_formative_zcl_message(uint16_t profile_id,
												     uint16_t dest_node_id,
												     uint8_t  source_ep,
												     uint8_t  dest_ep,
													 uint16_t cluster_id,
													 bool     cluster_specific_command,
													 bool	  client_to_server,
													 bool	  disable_default_resp,
													 uint16_t manufacture_code,
													 uint8_t  zcl_command,
												     const char* format, ...);

EmberStatus app_send_multicast_formative_zcl_message(uint16_t profile_id,
												     uint16_t group_id,
												     uint8_t  source_ep,
												     uint8_t  dest_ep,
												     uint16_t cluster_id,
													 bool     cluster_specific_command,
													 bool	  client_to_server,
													 bool	  disable_default_resp,
													 uint16_t manufacture_code,
													 uint8_t  zcl_command,
												     const char* format, ...);

EmberStatus app_send_via_bind_formative_zcl_message(uint16_t profile_id,
													uint8_t  source_ep,
													uint16_t cluster_id,
												    bool     cluster_specific_command,
												    bool	 client_to_server,
												    bool	 disable_default_resp,
												    uint16_t manufacture_code,
													uint8_t  zcl_command,
													const char* format, ...);

EmberStatus app_send_via_bind_table_index_formative_zcl_message(uint16_t profile_id,
																uint16_t bind_table_index,
																uint8_t  source_ep,
																uint8_t  dest_ep,
																uint16_t cluster_id,
															    bool     cluster_specific_command,
															    bool	 client_to_server,
															    bool	 disable_default_resp,
																uint16_t manufacture_code,
																uint8_t  zcl_command,
																const char* format, ...);
/**介绍：设备发送数据请求包
*  参数：-
*  返回：-
*/
void app_poll_for_data(void);

/**介绍：设置系统软重启时间
*  参数：无
*  返回：无
*/
void app_set_reset_seed(uint8_t second);

/**介绍：应用事件注册
* 参数：trigger_time_ms 事件触发的延迟时间/毫秒，appEventCallback 事件回调
* 返回：事件列表索引 0 ~ 0xF0 注册成功对应的列表索引 , 0xF1 ~ 0xFF 注册失败
* e.g. 设置 1s 后的 poll 事件
注册事件返回值：-1执行后删除事件，0 ~ 0xfffffffe：下次重复执行时间间隔ms
int app_poll_event_handler(void)
{
	app_poll_for_data();
	return -1;
}
调用
app_event_register(1000, app_poll_event_handler);
*/
//建议使用v2版本 - bool app_event_v2_register(bool refresh_event, uint8_t* id, int32u trigger_time_ms, int (*app_event_callback_t)(void));
//uint8_t app_event_register(uint32_t trigger_time_ms, int (*app_event_callback_t)(void));

/**介绍：应用事件取消
* 参数：eventId : 事件Id，0 ~ 0xF0 删除对应索引的事件，0xFF 删除全部事件
* 返回：true 删除成功，false 删除失败（不存在该事件）
*/
//建议使用v2版本 - bool app_event_v2_cancel(uint8_t* id);
//bool app_event_cancel(uint8_t event_id);


/**介绍：应用事件注册 V2
* 参数：
* 	  refresh_event    : 如果事件正在处于激活状态，是否重置事件， TRUE - 重置， FALSE - 不重置
* 	  id			   : 事件标志指针
* 	  trigger_time_ms  : 事件触发的延迟时间/毫秒，
* 	  appEventCallback : 事件回调
* 返回：true - 成功， false - 失败
* e.g. 设置 1s 后的 poll 事件
注册事件返回值：-1执行后删除事件，0 ~ 0xfffffffe：下次重复执行时间间隔ms
注意 ： 在事件标志变量初始化时， 默认值需要设置为0xFF, 表示事件未激活。
uint8_t poll_event_control_id = 0xFF;

//设置 1s 后的 poll 事件
int app_poll_event_handler(void)
{
	app_poll_for_data();

	app_event_v2_cancel(&poll_event_control_id);

	return -1;
}
//或
//设置每 1s poll 事件
int app_poll_event_handler(void)
{
	app_poll_for_data();

	//该情况下无需取消事件，设置返回值执行下次即可

	return 1000;
}

调用
app_event_v2_register(true, &poll_event_control_id, 1000, app_poll_event_handler);
*/
bool app_event_v2_register(bool refresh_event, uint8_t* id, int32u trigger_time_ms, int (*app_event_callback_t)(void));

/**介绍：应用事件取消V2
* 参数：eventId : 事件Id，1 ~ 0xF0 : 删除对应索引的事件， 0 : 删除全部事件, 0xF1 ~ 0xFF : 无效
* 返回：TRUE 删除成功，FALSE 删除失败（不存在该事件）
*/
bool app_event_v2_cancel(uint8_t* id);

/**介绍：应用事件是否激活V2
* 参数：eventId : 事件Id，1 ~ 0xF0 : 对应索引的事件， 0 : 删除全部事件, 0xF1 ~ 0xFF : 无效
* 返回：true 激活中，false 未激活或id不存在
*/
bool app_event_v2_is_active(uint8_t* id);

/**介绍：应用事件注册 V3
* 参数：
* 	  refresh_event    : 如果事件正在处于激活状态，是否重置事件， TRUE - 重置， FALSE - 不重置
* 	  id			   : 事件标志指针
* 	  trigger_time_ms  : 事件触发的延迟时间/毫秒，
* 	  event_callback   : 事件回调
*	  args			   : 注册传参
*	  
* 返回：true - 成功， false - 失败
* e.g. 设置 1s 后的 poll 事件
注册事件返回值：-1执行后删除事件，0 ~ 0xfffffffe：下次重复执行时间间隔ms
注意 ： 在事件标志变量初始化时， 默认值需要设置为0xFF, 表示事件未激活。
uint8_t poll_event_control_id   = 0xFF;
uint8_t print_event_port		= 0;
//设置 1s 后的 poll 事件
int app_poll_event_handler(void* args)
{
	app_poll_for_data();

	app_event_v3_cancel(&poll_event_control_id);

	return -1;
}
//或
//设置每 1s printf 事件
int app_print_event_handler(void* args)
{
	uint8_t port = *((uint8_t* )args);

	printf(port, ....);

	//该情况下无需取消事件，设置返回值执行下次即可

	return 1000;
}

调用
app_event_v3_register(true, &poll_event_control_id, 1000, app_poll_event_handler, NULL);
app_event_v3_register(true, &poll_event_control_id, 1000, app_print_event_handler, &print_event_port);
*/
bool app_event_v3_register(bool refresh_event,
						   uint8_t* id,
						   uint32_t trigger_time_ms,
						   int (*event_callback)(void* args),
						   void* args);
/**介绍：应用事件取消V3
* 参数：eventId : 事件Id，1 ~ 0xF0 : 删除对应索引的事件， 0 : 删除全部事件, 0xF1 ~ 0xFF : 无效
* 返回：TRUE 删除成功，FALSE 删除失败（不存在该事件）
*/
bool app_event_v3_cancel(uint8_t* id);

/**介绍：应用事件是否激活V3
* 参数：eventId : 事件Id，1 ~ 0xF0 : 对应索引的事件， 0 : 删除全部事件, 0xF1 ~ 0xFF : 无效
* 返回：true 激活中，false 未激活或id不存在
*/
bool app_event_v3_is_active(uint8_t* id);

/**介绍：应用事件触发剩余时间查询
* 参数：eventId : 事件Id，1 ~ 0xF0 : 对应索引的事件， 0 : 删除全部事件, 0xF1 ~ 0xFF : 无效
* 返回：事件触发的剩余时间，若不存在，则返回0xffffffff
*/
uint32_t app_event_time_remaining_ms(uint8_t* id);

/** 介绍 ：定时器任务注册（使用TIMER1），用于需要精准时间的任务，最大任务支持8个
* 	参数：
* 	  refresh_event 	   : 如果事件正在处于激活状态，是否重置事件， TRUE - 重置， FALSE - 不重置
* 	  id				   : 事件标志指针
* 	  trigger_time_1_48_us : 事件触发的延迟时间单位时间/(1/48us)，
* 	  app_timer_event_callback_t : 事件回调
*
*   返回：true - 成功， false - 失败
*
*   使用方式与app_event_v2_register类似，除单位时间不同，其余均相同，注册的回调返回值单位也为(1/48us)
*/
bool app_tl_timer_interrupt_event_register(bool refresh_event, uint8_t* id, int32u trigger_time_1_48_us, int (*app_timer_event_callback_t)(void));

/** 介绍 ：定时器任务删除（使用TIMER1），用于需要精准时间的任务，最大任务支持8个
* 	参数：
* 	  id				   : 事件标志指针
*   返回：true - 成功， false - 失败
*
*   使用方式与app_event_v2_cancel相同
*/
bool app_timer_interrupt_event_cancel(uint8_t* id);

/**介绍：定时器任务是否激活
* 参数：id : 事件Id指针
* 返回：true 激活中，false 未激活或id不存在
*/
bool app_timer_interrupt_event_is_active(uint8_t* id);

/** 介绍 ：定时器是否有任务在进行中
* 	参数： 无
*   返回：true - 进行中， false - 未进行
*/
bool app_is_timer_interrupt_underway(void);

/**介绍：属性表打印函数
* 参数： port：使用的的串口号
* 返回：-
*/
void app_print_attribute_table(uint8_t port);

/**介绍：设备zcl message default aps option
* 参数： option 参照 EmberApsOption
* 返回：-
*/
void app_set_zcl_message_default_option(EmberApsOption option);

/**介绍：获取设备zcl message default aps option
* 参数：-
* 返回：EmberApsOption
*/
EmberApsOption app_get_zcl_message_default_option(void);

/**介绍：设备zdo message default aps option
* 参数： option 参照 EmberApsOption
* 返回：-
*/
void app_set_zdo_message_default_option(uint16_t option);

/**介绍：获取设备zdo message default aps option
* 参数：-
* 返回：EmberApsOption
*/
uint16_t app_get_zdo_message_default_option(void);

/**介绍：设备版本号打印
* 参数： port : 打印端口映射 e.g. TYPE_VCP_SERIAL, TYPE_UART_SERIAL
* 返回：-
*/
void app_version_printf(uint8_t port);

/**介绍：注册 AT 命令处理回调
 *
 * 该函数用于向系统注册一个 AT 命令处理函数，当接收到串口 AT 命令时，
 * 系统会调用此回调函数来处理命令并返回处理结果。
 *
 * 参数：handle : 指向处理函数的指针，函数原型如下：
 *               bool handle(uint8_t port, uint8_t* data, uint32_t length);
 *               - port   : 串口端口号，用于区分不同的 UART 通道
 *               - data   : 指向接收到的 AT 命令数据缓冲区
 *               - length : 缓冲区中数据的长度（字节数）
 *               - 返回 ： true - 用户已处理该命令， false - 交由sdk继续处理
 * 返回：-
 * @note  当多次调用本函数时，后注册的回调会覆盖之前的设置。
 */
void app_at_command_handle_register(bool (*handle)(uint8_t port, uint8_t* data, uint32_t length));

/**介绍：读取设备属性信息
* 参数： -
* 返回： 0 - 成功, 其他 - 失败
*/
EmberAfStatus app_global_read_server_attribute(uint8_t endpoint, uint16_t cluster_id, uint16_t attribute_id, uint8_t* data, uint8_t length);

/**介绍：写入设备属性信息
* 参数： -
* 返回： 0 - 成功, 其他 - 失败
*/
EmberAfStatus app_global_write_server_attribute(uint8_t endpoint, uint16_t cluster_id, uint16_t attribute_id, uint8_t* data, uint8_t data_type);


/**介绍：读取设备属性信息（厂商私有）
* 参数： -
* 返回： 0 - 成功, 其他 - 失败
*/
EmberAfStatus app_read_server_attribute(uint8_t  endpoint, uint16_t cluster_id, uint16_t attribute_id, \
										uint16_t manufacturer_code, uint8_t* data, uint8_t  length);

/**介绍：写入设备属性信息（manufacturer_code !=0为厂商私有）
* 参数： with_callback : true -  写属性后进入app_post_attr_change_handler回调， 功能与app_write_server_attribute一致
* 					  false - 写属性后不进入app_post_attr_change_handler回调
* 返回：  0 - 成功, 其他 - 失败
*/
EmberAfStatus app_write_server_attribute_with_callback(bool with_callback, \
													   uint8_t endpoint, uint16_t cluster_id, uint16_t attribute_id, \
													   uint16_t manufacturer_code, uint8_t* data, uint8_t data_type);

/**介绍：写入设备属性信息（manufacturer_code !=0为厂商私有）
* 参数： -
* 返回：  0 - 成功, 其他 - 失败
*/
EmberAfStatus app_write_server_attribute(uint8_t endpoint, uint16_t cluster_id, uint16_t attribute_id, \
										 uint16_t manufacturer_code, uint8_t* data, uint8_t data_type);

/**介绍： 应用Token(最大48bytes)
*  e.g.
*	void app_get_token_data_to_ram_callback()
*	{
		//首次使用时，初始化token data
*		if(!app_is_global_token_data_used())
*		{
*			  app_set_global_token_data(...); //设置默认数据
*		}
*		app_get_global_token_data(...);
*	}
*/
#define APP_GLOBAL_TOKEN_DATA_SIZE	48
extern uint8_t g_app_global_token_data[APP_GLOBAL_TOKEN_DATA_SIZE];

/**介绍：应用token是否初始化值
* 返回： true - 已初始化, false - 未初始化
*/
bool app_is_global_token_data_used(void);

/**介绍：应用token（48字节）读写
* 参数： data : 48字节buffer
* 返回：true - 成功, false - 失败
*/
bool app_set_global_token_data(uint8_t* data);
bool app_get_global_token_data(uint8_t* data);

/**介绍：模拟eeprom读写接口
* 参数： id : 使用生成的ID， TOKEN_XXX
* 	  write_index : 多条目的索引， 使用INDEX_TOKEN时使用，其他使用0
* 	  context 	  : 读写内存
* 返回：  true - 成功, false - 失败
*/
bool app_eeprom_write_data(uint16_t id, uint8_t write_index, uint8_t* context);
bool app_eeprom_read_data(uint16_t id, uint8_t write_index, uint8_t* context);

/**介绍：模拟eeprom读写接口
* 参数： id : 使用生成的ID， TOKEN_XXX
* 	  write_index : 多条目的索引， 使用INDEX_TOKEN时使用，其他使用0
* 	  context 	  : 读写内存
* 	  internal_read : true时， 可以读取或修改token的部分数据， data_index为读写的偏移量， data_length为读写长度
* 返回： true - 成功, false - 失败
*/
bool app_eeprom_internal_read_data(uint16_t id, uint8_t read_index, uint8_t* context, bool internal_read, uint16_t data_index, uint16_t data_length);
bool app_eeprom_internal_write_data(uint16_t id, uint8_t write_index, uint8_t* context, bool internal_write, uint16_t data_index, uint16_t data_length);

/**介绍 ： zed重连配置
 * 参数 :
 *   config : 配置表
 *   count  : 配置表条目数
 * e.g.
 * recovery_network_config_t recovery_config[] =
 * {
 * 		{0,  255,  true, 0, 60000},   //在掉网后尝试重连0次之后，按照secure方式，当前信道，1分钟间隔进行重连
 * };
 * stack_recovery_network_config(recovery_config, sizeof(recovery_config) / sizeof(recovery_config[0]));
 * 用户未配置的情况下，协议栈默认使用以下配置
 * {
 * 		{0,  14,  true, 0, 60000},   //在掉网后尝试重连0 ~ 14次，按照secure方式，当前信道，1分钟间隔进行重连
 *		{15, 255, true, 0, 1800000}, //在掉网后尝试重连15次之后，按照secure方式，当前信道，30分钟间隔进行重连
 * }
 *
 */
void stack_recovery_network_config(recovery_network_config_t* config, uint8_t count);

/**介绍 ： zed重连接口，尝试一次重连
 * 参数 :
 * 	 secure : rejoin模式
 * 	 channel_mask : 重连尝试信道掩码， 0为当前信道
 */
bool stack_attempt_recovery_network(bool secure, uint32_t channel_mask);

/**介绍：命令行注册（必须注册后，命令行激活才有效，注册后默认激活命令行，如需关闭可以调用app_command_line_enable关闭）
 * 参数： -
 * 返回： -
 */
void app_command_line_plugin_register(void);

/**介绍：命令行激活
* 参数： enable : true - 支持   false - 不支持
* 返回：-
*/
void app_command_line_enable(bool enable);

/**介绍：设备定时上报配置(最大支持6个)
*  参数：   cfg_count : 配置的个数， 大于1个，配置...后的值
*  		force_add : true  - 表中存在相同ep, cluster，attribute，mfgcode会按照现在的配置重写min interval, max interval，report change, 不存在直接新增
*  					false - 表中存在相同ep, cluster，attribute，mfgcode就不做任何操作, 不存在直接新增
*   	max_random_second : 从0 ~ max_random_second取一个随机偏移值加上各自的max_interval，作为心跳周期
*  		... cycle : uint8_t endpoint, uint16_t cluster_id, uint16_t attribute_id,
*					uint16_t manufacture_code, uint16_t min_interval, uint16_t max_interval, uint32_t report_change
*  e.g. :
*	app_reporting_plugin_reporting_config_register
*	(
*		 2, false, 60,																	//共2个配置，随机增加0 ~ 60s的心跳延迟
*		 1, ZCL_BASIC_CLUSTER_ID, ZCL_VERSION_ATTRIBUTE_ID, 0x0000, 16, (7200), 0,		//配置 cluster 0x0000, attr 0x0000, 2小时心跳周期
*		 1, ZCL_BASIC_CLUSTER_ID, 0xfff1, 					0x1163, 16, (3600), 0		//配置私有 cluster 0x0000, attr 0xfff1, mfg code 0x1163, 1小时心跳周期
*	);
*  返回：无
*/
void app_reporting_plugin_reporting_config_register(uint8_t cfg_count, bool force_add, uint8_t max_random_second,
												    uint8_t endpoint, uint16_t cluster, uint16_t attribute, uint16_t mfg_code,
												    uint16_t min_interval, uint16_t max_interval, uint32_t report_change, ...);

/**介绍：获取设备定时上报列表中最小的上报时间间隔
*  参数： -
*  返回：列表中最小的上报时间间隔
*/
uint16_t app_reporting_plugin_get_min_report_interval(void);

/**介绍：定时上报回调注册，发送完定时上报数据后回调
* 参数： callback : 定时上报回调， 发送完定时上报数据后回调
* 返回： -
*
* e.g.
*	  //endpint, cluster, attribute, mfg_code 为当前已发送的定时上报信息
*	  void user_reporting_data_sent_callback(uint8_t endpint, uint16_t cluster, uint16_t attribute, uint16_t mfg_code)
*	  {
*
*	  }
*
*     app_reporting_data_sent_register(user_reporting_data_sent_callback);
*
*/
void app_reporting_data_sent_register(void (*callback)(uint8_t endpint, uint16_t cluster, uint16_t attribute, uint16_t mfg_code));

/**介绍：使能向绑定表定时上报，默认关闭
* 参数： send_to_binding_enable : true - 允许向对应cluster的binding节点上报， false - 禁用使用绑定表上报
* 返回： -
*/
void app_reporting_plugin_set_send_to_binding(bool send_to_binding_enable);

/**介绍：设备更新定时上报信息
*  参数： endpoint/cluster/attribute/manufacture_code : 通过该信息查找定时上报列表中的节点
*  		 update_last_report_time : 是否把上次上报的时候更新为现在
*  返回： -
*/
void app_reporting_plugin_update_data(uint8_t endpoint,
									  uint16_t cluster,
									  uint16_t attribute,
									  uint16_t manufacture_code,
									  bool update_last_report_time,
									  bool update_last_report_change);

/**介绍：设备清除全部定时上报
*  参数： -
*  返回： -
*/
void app_device_clear_reporting_table(void);

/**介绍：设备打印全部定时上报信息表
*  参数： -
*  返回： -
*/
void app_print_report_table(void);

//GATEWAY -> parent(ROT) (CACHE)

//ZED -> Poll parent(ROT) -> (CACHE) -> ZED

//ZED -> Poll parent (Lost ack) -> retry poll > max_poll_failure_count -> lost parent

/**介绍：设备Poll Server初始化
* 参数： support_poll_cluster : 属性表中是否支持poll cluster, true - 支持 false - 不支持
*	  long_poll_interval_ms : 配置long poll间隔
*	  short_poll_interval_ms : 配置short poll间隔, 推荐值4次
*	  max_poll_failure_count : poll超时次数，达到超时次数后进入掉网状态
*	  polling_after_joined_sec : 从无网络到入网成功后执行short poll的持续时间/秒, 推荐30s
*	  polling_after_rejoin_sec : 从丢失父节点（掉网）到入网成功后执行short poll的持续时间/秒, 推荐3s
*	  handle_list		 : 用于注册部分应用回调, poll server plugin设置为NULL
* 返回：-
*/
void app_poll_server_plugin_register(bool support_poll_cluster,
									 uint32_t long_poll_interval_ms,
									 uint16_t short_poll_interval_ms,
									 uint8_t max_poll_failure_count,
									 uint8_t polling_after_joined_sec,
									 uint8_t polling_after_rejoin_sec,
									 stack_application_zcl_handle_t* handle_list);

/**介绍 ： zcl on off plugin 注册，用于支持标准on off命令处理
 * 参数 ： is_sleepy_device : 是否为休眠设置
 * 		 time_unit_ms	 : on with timed off单位时间，标准为100ms， 可自行配置，0为使用默认。
 * 		 handle_list		 : 用于注册部分应用回调, onoff plugin设置为NULL
 * on off plugin使用到的回调 :
 * 		 当收到命令(已对onoff属性进行写操作)或本地写onoff属性时，会触发以下回调，可以在该回调中处理onoff相关操作
 * 		 trigger type   : 参照 app_write_attribute_trigger_type_enum_t
 * 		 bool app_onoff_plugin_onoff_status_callback(uint8_t trigger_type, uint8_t endpoint, bool last_onoff_status, bool current_onoff_status)
 * 		 {
 * 		 	...
 * 		 }
 * 返回:-
 */
void app_onoff_plugin_register(bool is_sleepy_device, uint32_t time_unit_ms, stack_application_zcl_handle_t* handle_list) __attribute__((deprecated));


/**介绍 ： zcl on off plugin v2 注册，用于支持标准on off命令处理
 * 参数 ： is_sleepy_device  : 是否为休眠设置
 * 		 time_unit_ms	     : on with timed off单位时间，标准为100ms， 可自行配置，0为使用默认。
		 status_changed_cb   : 注册on off plugin回调，
							   注：v2版本不会使用默认的app_onoff_plugin_onoff_status_callback
 * 		 handle_list		 : 用于注册部分应用回调, onoff plugin设置为NULL
 * on off plugin使用到的回调 :
 * 		 当收到命令(已对onoff属性进行写操作)或本地写onoff属性时，会触发以下回调，可以在该回调中处理onoff相关操作
 * 		 trigger type   : 参照 app_write_attribute_trigger_type_enum_t
 *       effect_id / effect_var : 当收到off with effect命令时，会置位， 0xFF时为无效值
 *		 transition_time : 当收到recall scene触发onoff变更时，会携带transition_time，其余情况下为0
 * 		 bool user_onoff_status_callback(uint8_t trigger_type, uint8_t endpoint, bool last_onoff_status, bool current_onoff_status, uint8_t effect_id, uint8_t effect_var, uint32_t transition_time)
 * 		 {
 * 		 	...
 * 		 }
 *		 app_onoff_plugin_v2_register(false, 100, user_onoff_status_callback, NULL);
 * 返回:-
 */
void app_onoff_plugin_v2_register(bool is_sleepy_device,
								  uint32_t time_unit_ms,
								  bool (*status_changed_cb)(uint8_t trigger_type,
										  	  	  	  	  	uint8_t endpoint,
										  	  	  	  	  	bool last_onoff_status,
										  	  	  	  	  	bool current_onoff_status,
										  	  	  	  	  	uint8_t effect_id,
										  	  	  	  	  	uint8_t effect_var,
										  	  	  	  	  	uint32_t transition_time),
								  stack_application_zcl_handle_t* handle_list);

/**介绍 ： zcl level plugin 注册，用于支持标准level命令处理
 * 参数 ： min_level : 最小支持亮度 0 ~ 0xfe， min level 为 0xff 时， 使用默认值(min, max)(0, 255)
 * 		 max_level : 最大支持亮度 1 ~ 0xff, max level 为 0x00 时，  使用默认值(min, max)(0, 255)
 * 		handle_list		 : 用于注册部分应用回调, level 设置为NULL
 * 返回:-
 */
void app_level_plugin_register(uint8_t min_level, uint8_t max_level, stack_application_zcl_handle_t* handle_list);

/**介绍 ： zcl color control plugin 注册，用于支持标准color control命令处理, 建议device id : Color Dimmable Light(0x0102)
 *       色温 : kelvins = 1000000 / mireds, 范围在 (1000000 / min_temperature_mireds) ~ (1000000 / max_temperature_mireds), 默认值mireds(1, 65279)对应kelvins(1000000, 15.32)
 * 参数 ：
 * 		 temperature_mode_support : 支持色温模式 : 注册color_control_cluster_plugin_register_temperature_callback, 需要实现(min_temperature_mireds和max_temperature_mireds)
 * 		 							不支持色温模式 : 填NULL
 * 		 hsv_mode_support		  : 支持HSV模式 : 注册	color_control_cluster_plugin_register_hsv_callback
 * 		 							不支持HSV模式	: 填NULL
 * 		 xy_mode_support		  : 支持XY模式 : 注册	color_control_cluster_plugin_register_xy_callback
 * 		 							不支持XY模式	: 填NULL
 * 		 color_loop_support		  : 支持色彩循环模式 : 注册 color_control_cluster_plugin_register_color_loop_callback
 * 		 							不支持色彩循环模式	: 填NULL
 * 		 min_temperature_mireds : 最小色温mired 1 ~ 65279，  min level 不为(1 ~ 65279) 时，使用默认值(min, max)(1, 65279)
 * 		 max_temperature_mireds : 最大色温mired 1 ~ 65279,  max level 不为(1 ~ 65279) 时，使用默认值(min, max)(1, 65279)
 * 		 handle_list		    : 用于注册部分应用回调, color 设置为NULL
 * 返回:-
 *
 *	e.g.
 *		色温灯注册 : app_color_light_plugin_v2_register(color_control_cluster_plugin_register_temperature_callback, NULL, NULL, NULL, 1, 65279, NULL)
 *		HSL彩灯注册 : app_color_light_plugin_v2_register(color_control_cluster_plugin_register_temperature_callback,
 *													   color_control_cluster_plugin_register_hsv_callback,
 *													   NULL, NULL, 1, 65279, NULL)
 *
 * callback :
 * 彩色灯控制通过以下函数回调给应用, current_xxx_value为当前值, target_xxx_value为目标值, xxx_transition_time_ms为渐变时间
 * 返回值: true - 应用处理该变更
 *
 * 色温控制回调 :
 * bool app_color_plugin_color_temperature_change_start_callback(uint8_t  trigger_type,
 *															     uint8_t  endpoint,
 *																 uint16_t current_temperature_value,
 *																 uint16_t target_temperature_value,
 *																 uint32_t transition_time_ms);
 *
 * 色彩(HSL)控制回调 :
 * bool app_color_plugin_color_hue_and_saturation_change_start_callback(uint8_t  trigger_type,
 *																		uint8_t  endpoint,
 *																		uint8_t  current_hue_value,
 *																		uint8_t  target_hue_value,
 *																		uint8_t  current_saturation_value,
 *																		uint8_t  target_saturation_value,
 *																		bool     is_hue_mode_up,
 *																		uint32_t transition_time_ms);
 * 色彩(xyY)控制回调 :
 * bool app_color_plugin_color_xy_mode_change_start_callback(uint8_t  trigger_type,
 *														     uint8_t  endpoint,
 *														   	 uint16_t current_x_value,
 *														  	 uint16_t target_x_value,
 *														  	 uint16_t current_y_value,
 *														  	 uint16_t target_y_value,
 *														  	 uint32_t x_transition_time_ms,
 *														  	 uint32_t y_transition_time_ms);
 * 色彩循环控制回调 :
 * bool app_color_plugin_color_loop_set_callback(uint8_t  trigger_type,
 *												 uint8_t  endpoint,
 *												 uint8_t active,
 *												 uint16_t time,
 *												 uint16_t start_hue);
 *
 */
void color_control_cluster_plugin_register_temperature_callback(uint16_t min_temperature_mireds, uint16_t max_temperature_mireds);
void color_control_cluster_plugin_register_hsv_callback(void);
void color_control_cluster_plugin_register_xy_callback(void);
void color_control_cluster_plugin_register_color_loop_callback(void);
void app_color_light_plugin_v2_register(void (*temperature_mode_support)(uint16_t min_temperature_mireds, uint16_t max_temperature_mireds),
									    void (*hsv_mode_support)(void),
									    void (*xy_mode_support)(void),
									    void (*color_loop_support)(void),
									    uint16_t min_temperature_mireds,
									    uint16_t max_temperature_mireds,
									    stack_application_zcl_handle_t* handle_list);
//void app_color_light_plugin_register(void (*temperature_mode_support)(uint16_t min_temperature_mireds, uint16_t max_temperature_mireds),
//									 void (*hsl_mode_support)(void),
//									 void (*xy_mode_support)(void),
//									 uint16_t min_temperature_mireds,
//									 uint16_t max_temperature_mireds,
//									 stack_application_zcl_handle_t* handle_list);

/** 介绍：ota read attribute handle注册，用于支持读取ota升级进度
 *  参数：-
 *  返回：-
 */
void app_ota_plugin_read_attribute_handle_register(void);

/** 介绍：zcl ota plugin配置，用于支持使能ota定时发送next image request(协议栈默认为开启)
 *	参数：enable : true  - 开启定时发送next image request
 *				  false - 关闭定时发送next image request
 *	返回:-
 */
void app_ota_plugin_set_timed_querry_next_image_enable(bool enable);

/** 介绍：zcl ota plugin注册，用于支持标准ota流程处理
 *	参数：mfg_code 	   : 可自定义设置,OTA时需要校验,请根据自己公司的填写
 *		 image_type    : 可自定义设置,OTA时需要校验,根据设备类型定义
 *		 image_version : 可自定义设置,OTA时需要校验,
 *		 				  使用宏OTA_PLUGIN_USE_BCD_DATE_CODE_AS_OTA_IMAGE_VERSION时,设备使用编译日期BCD作为image version
 *		 				  其他值可自定义配置
 *		 resquest_time_sec : 长请求时间,单位s , 设置为0时使用default value 1800s,
 *							 (next image request和断点续传image block request)共用时间
 *							 最大值为0x1FFFFF(2097151)s, 约24天
 *							 如需要关闭定时next image request, 可以使用接口
 *							 void app_ota_plugin_set_timed_querry_next_image_enable(bool enable);
 *							 app_ota_plugin_set_timed_querry_next_image_enable(false);
 *		request_bytes_in_block : 每一包OTA请求的字节个数(4 ~ 64), 设置为0时使用default value 64
 *		handle_list		 : 用于注册部分应用回调, 参照app_ota_plugin_handle_list_t, 根据需要选择注册
 *	返回:-
 */
void app_ota_client_plugin_register(uint16_t mfg_code,
									uint16_t image_type,
									uint32_t image_version,
									uint32_t resquest_time_sec,
									uint8_t  request_bytes_in_block,
									stack_application_zcl_handle_t* handle_list);

/** 介绍：zcl ota plugin v2注册，用于支持标准ota流程处理
 *	参数：mfg_code 	   : 可自定义设置,OTA时需要校验,请根据自己公司的填写
 *		 image_type    : 可自定义设置,OTA时需要校验,根据设备类型定义
 *		 image_version : 可自定义设置,OTA时需要校验,
 *		 				  使用宏OTA_PLUGIN_USE_BCD_DATE_CODE_AS_OTA_IMAGE_VERSION时,设备使用编译日期BCD作为image version
 *		 				  其他值可自定义配置
 *		 resquest_time_sec : 非升级状态下的长请求时间,单位s , 设置为0时使用default value 1800s,
 *							 next image request间隔时间
 *							 最大值为0x1FFFFF(2097151)s, 约24天
 *							 如需要关闭定时next image request, 可以使用接口
 *							 void app_ota_plugin_set_timed_querry_next_image_enable(bool enable);
 *							 app_ota_plugin_set_timed_querry_next_image_enable(false);
 *		image_block_time_sec : 升级状态下的请求时间,单位s , 设置为0时使用default value 1800s,
 *							 断点续传image block request间隔时间
 *							 最大值为0x1FFFFF(2097151)s, 约24天
 *		ota_timeout_protection_ms : 设备本地超时时间，0xffffffff表示无超时，其余为xms后超时触发本地abort, 并向coo发送end request(abort)消息
 *		request_bytes_in_block : 每一包OTA请求的字节个数(4 ~ 64), 设置为0时使用default value 64
 *		handle_list		 : 用于注册部分应用回调, 参照app_ota_plugin_handle_list_t, 根据需要选择注册
 *	返回:-
 */
void app_ota_client_plugin_v2_register(uint16_t mfg_code,
									   uint16_t image_type,
									   uint32_t image_version,
									   uint32_t next_image_time_sec,
									   uint32_t image_block_time_sec,
									   uint32_t ota_timeout_protection_ms,
									   uint8_t  request_bytes_in_block,
									   stack_application_zcl_handle_t* handle_list);

/** 介绍：zcl zone plugin注册，用于支持标准ias zone处理流程
 *	参数： support_zone_endpoint_count : 需要支持ias zone的endpoint数量
 *		list  		: 对应的endpoint id&zone type
 *		handle_list	: 用于注册部分应用回调, zone plugin设置为NULL
 *	返回:-
 *	e.g.
 *	某设备支持endpoint 1 为 door sensor (zone type 0x0015), endpoint 3 为 motion sensor (zone type 0x000d),
 *	 zcl_zone_type_list_t g_user_zone_type_list[] =
 *	 {
 *	 	{1 , 0x0015},
 *	 	{3 , 0x000d}
 *	 };
 *	 app_ias_zone_plugin_register(sizeof(g_user_zone_type_list) / sizeof(g_user_zone_type_list[0]), g_user_zone_type_list, NULL);
 */
void app_ias_zone_plugin_register(uint8_t support_zone_endpoint_count,
								  zcl_zone_type_list_t* list,
								  stack_application_zcl_handle_t* handle_list);

/** 介绍：zcl window covering plugin注册，用于支持标准window covering处理流程
 *	参数：handle_list : 用于注册部分命令回调, 注册回调后由用户直接处理相关命令，
 *					      若未注册则进入app_window_covering_plugin_window_status_callback回调
 *	返回: -
 *	e.g.
 *		EmberAfStatus user_window_open_callback(uint8_t endpoint)
 *		{
 *			return EMBER_ZCL_STATUS_SUCCESS;
 *		}
 *		window_convering_calback_t window_convering_calback_register_list =
 *		{
 *			.open_callback 			= (void* )user_window_open_callback,
 *			.close_callback 		= (void* )NULL,
 *			.stop_callback 			= (void* )NULL,
 *			.lift_value_callback 	= (void* )NULL,
 *			.lift_percent_callback 	= (void* )NULL,
 *			.tift_value_callback 	= (void* )NULL,
 *			.tift_percent_callback 	= (void* )NULL,
 *		};
 *		app_window_covering_plugin_register(&window_convering_calback_register_list);
 */
void app_window_covering_plugin_register(stack_application_zcl_handle_t* handle_list);

/** 介绍：aps message过滤注册，用于过滤同一节点相同aps counter的数据（过滤由于aps重发导致的重复处理情况）
 *	参数：无
 *	返回：无
 */
void app_aps_message_filter_plugin_register(void);

/** 介绍：zcl re support plugin注册，用于支持主子网关方案v1(不再支持)
 *	参数：handle_list	: 用于注册部分应用回调, 设置为NULL
 */
void app_re_support_plugin_register(stack_application_zcl_handle_t* handle_list)
    __attribute__((error("app_re_support_plugin_register() is no longer supported")));

/**brief : send zcl command zone changed notify
*  para  : zone_ep (local endpoint)
*  		   zone_status (current send zone status)
*  		   delay_time (qs delay time, see zcl7-ias-zone)
*  return : none
*/
void app_send_zone_status_change_notification(uint8_t zone_ep, uint16_t zone_status, uint16_t delay_time);

/**brief : write/read zone status attr
*  para  : write (true - write, false - read)
*  		   endpoint (write/read local endpoint)
*  		   *zonestatus (write/read memory pointer)
*  return : af status
*/
EmberAfStatus app_write_or_read_zone_status_attribute(bool write, uint8_t endpoint, uint16_t* zone_status);

/** 介绍：配合battery monitor plugin使用，用于设置平均采样值的采集次数
 *  参数：size，平均采样值窗口大小，默认值为16，即使用滚动窗口取最后的16次数据平均值作为采样值
 *  返回：-
 */
void app_battery_plugin_set_average_fifo_size(uint8_t size);

/** 介绍：battery monitor plugin注册，用于支持电池监测（默认采样芯片VDD电压无需额外IO）
 * 		  如需采样外部电池电压，使用app_external_battery_monitor_configuration接口配置
 *	参数： battery_measure_interval_second : 采样间隔 /秒， 首次注册后会500ms后采样第一次， 之后按照设置的采样间隔采样
 *		low_power_notification_interval_second : app_low_power_notification - 低电量通知间隔 /秒， 首次触发低电量时会1000ms后通知， 之后按照设置的间隔通知
 *		app_battery_percentage_algorithm : 用户电池电量算法实现，采样后会调用该函数获取电量百分比和低电量， 用户实现的该函数返回值为电量百分比（0 ~ 100），
 *										         传参 milli_voltage 为采样到的电压值
 *											 *is_low_power（true or false）用户修改该标志表明是否满足低电量
 *		app_low_power_notification : 用户低电量处理实现， 会按照配置的间隔定期调用该通知
 *	返回:-
 *	e.g.
 *	电池监测，设置30分钟采样间隔，12小时低电量通知间隔
 *	uint8_t user_battery_percentage_algorithm(uint16_t milli_voltage, bool* is_low_power)
 *	{
 *		uint8_t percentage = milli_voltage ...
 *		*is_low_power = (percentage < 10) ? true : false;
 *		return percentage;
 *	}
 *
 *	void user_low_power_notification(void)
 *	{
 *		//send low power alarm
 *	}
 *
 *	app_battery_monitor_plugin_register(60 * 30, 60 * 60 * 12, user_battery_percentage_algorithm, user_low_power_notification);
 */
void app_battery_monitor_plugin_register(uint32_t battery_measure_interval_second,
										 uint32_t low_power_notification_interval_second,
										 uint8_t (*app_battery_percentage_algorithm)(uint16_t milli_voltage, bool* is_low_power),
										 void (*app_low_power_notification)(void));


/** 介绍：battery monitor v2 配置项，用于battery monitor plugin支持外部电池采样，
 * 		  修改采样IO（未配置时采样芯片VDD电压无需IO采样）,
 * 		  新增采样使能脚ce io
 *  参数： sampling_io : adc采样IO
 *  	  multiplier : 采样值乘数
 *  	  divisor    : 采样值除数
 *  	  ce_io		 : 采样使能脚
 *  	  ce_level   : 采样使能电平
 *  	  ce_setup_time_us : 采样前使能准备时间（保持xus后开始采样）
 *  返回 ：无
 *
 *  注 : battery_mv = adc_result_mv * multiplier / divisor
 */
void app_external_battery_monitor_v2_configuration(uint8_t sampling_io,
												   uint16_t multiplier,
												   uint16_t divisor,
												   uint8_t ce_io,
												   bool ce_level,
												   uint32_t ce_setup_time_us);

/** 介绍：battery monitor配置项，用于battery monitor plugin支持外部电池采样，修改采样IO（未配置时采样芯片VDD电压无需IO采样）
 *  参数： io 		 : adc采样IO
 *  	  multiplier : 采样值乘数
 *  	  divisor    : 采样值除数
 *  返回 ：无
 *
 *  注 : battery_mv = adc_result_mv * multiplier / divisor
 */
void app_external_battery_monitor_configuration(uint8_t io, uint16_t multiplier, uint16_t divisor);

/** 介绍: 过零检测引脚注册,闭合继电器延时时间,打开继电器延时时间,过零检测损坏时超时时间
 * 		   注: 占用外部中断interrput id 0
 *	参数：zero_cross_detect_signal_pin: 过零检测信号接收引脚
 *		  on_delay_time_us: 触发过零延迟on_delay_time_us/us触发on回调即app_zero_cross_detect_trigger_callback(true)
 *		  off_delay_time_us: 触发过零延迟on_delay_time_us/us触发on回调即app_zero_cross_detect_trigger_callback(false)
 *		  timeout_us: 过零超时us,同时触发app_zero_cross_detect_trigger_callback(true), app_zero_cross_detect_trigger_callback(false)
 *        use_hal_timer: 是否使用硬件定时器，true - 使用硬件定时器计时， false - 使用阻塞式延时计时
 *  返回: -
 *
 * e.g.
 *	app_zero_cross_detect_register(PORTC_PIN(1), 5000, 4000, 25000);
 *
 *	在需要处调用app_enabled_single_pass_zero_cross_detect()使能单次过零检测功能
 *  触发回调：过零检测事件到了或者超时情况下进入的回调
 *	参数： on_off: true -  on_delay_time_us条件触发或超时触发
 *				false - off_delay_time_us条件触发或超时触发
 *	返回: -
 *  void app_zero_cross_detect_trigger_callback(bool on_off)
 *  {
 *  	...
 *  }
 */
void app_zero_cross_detect_register(uint8_t pin,
									uint32_t on_delay_time_us,
									uint32_t off_delay_time_us,
									uint32_t timeout_us,
									bool use_hal_timer);

/** 介绍: 过零检测单次使能，调用后，检测到过零信号或超时会触发回调
 * 		 void app_zero_cross_detect_trigger_callback(bool on_off)
 *  参数: -
 *  返回: -
 */
void app_enabled_single_pass_zero_cross_detect(void);

/** 介绍：hal control plugin注册，用于初始化control pin list(使用led task也需要初始化该函数)
 *	参数： -
 *	返回: -
 */
void app_control_plugin_init(void);

/** 介绍：control pin操作接口（on, off, toggle）
 * 		注 ： on off对应的不是电平状态， 与HAL_CONTROL_PIN_LIST中trigger state相同电平状态为on
 *	参数：
 *		control_list_index : HAL_CONTROL_PIN_LIST index
 *	返回: true - 执行成功， false - 执行失败
 */
bool app_control_off(uint8_t control_list_index);
bool app_control_on(uint8_t control_list_index);
bool app_control_toggle(uint8_t control_list_index);

/**介绍：设置led任务最小单位时间，如果设置的任务时间间隔无法被最小单位时间整除，则会存在误差（默认最小单位时间为50ms）
 * 		例如使用50ms作为单位时间，当设置闪烁间隔为125ms时，会在150ms处触发，导致存在25ms的偏差
 * 		此时可以设置最小单位时间为25ms，那么可以满足准确触发的条件
*  参数： ms - 单位时间 ms
*  返回：-
*/
void app_led_task_set_unit_time(uint32_t ms);

/**介绍：增加led任务
*  参数：control_list_index : HAL_CONTROL_PIN_LIST index
*  	   task: 任务执行列表
*  	   注：当execute_time_ms 和 execute_count任一一个到达时，结束任务，execute_time_ms为0x00ffffff execute_count为0xff 时永久执行任务
*  	   execute_time_ms : 任务总时长, 范围为50 ~ 0x00fffffe, 设置为0x00ffffff时为不计时长
*  	   execute_count   : 任务总次数, 范围为1 ~ 0xfe, 设置为0xff时为不计次数
*  	   priority:任务优先级(0 ~ 31) 0为最高优先级
*  	   keep_awake_when_task_underway : led task执行过程中是否保持唤醒， true - 强制保持唤醒， false - 不强制保持唤醒， 对于非休眠设备该值无效
*  返回：返回： true - 成功, false - 失败
*/
bool app_add_led_task(uint8_t control_list_index, const led_list_t* task, uint32_t execute_time_ms, uint8_t execute_count, uint8_t priority, bool keep_awake_when_task_underway);

/**介绍：关闭led任务
*  参数：task:任务执行列表
*  返回： true - 成功, false - 失败
*/
bool app_cancel_led_task(uint8_t control_list_index, const led_list_t* task);

/**介绍：控制输出
*  参数：
*      control_list_index： control list索引
*  	   action		   ： 执行的输出动作	(CONTROL_ACTION_OFF, CONTROL_ACTION_ON, CONTROL_ACTION_TOGGLE)
*  返回： true - 成功, false - 失败
*/
bool app_control_pin_action(uint8_t control_pin_list_index, control_action_enum_t action);


/**介绍：zcl命令表注册
*  参数：
*      handle_list 					：命令列表
*  	   handle_list_member_count		：命令列表成员数
*  返回：无
*  e.g.
*   bool user_onoff_cluster_on_command_handler(uint8_t trigger_type, uint8_t endpoint, uint8_t* data, uint16_t length, uint8_t* default_resp_status)
*	{
*		...
*		return ...; //true - 结束命令处理， false - 交由栈继续处理该命令
*	}
*   bool user_onoff_cluster_off_command_handler(uint8_t trigger_type, uint8_t endpoint, uint8_t* data, uint16_t length, uint8_t* default_resp_status)
*	{
*		...
*		return ...; //true - 结束命令处理， false - 交由栈继续处理该命令
*	}
*  	const app_custom_zcl_cmd_handle_t c_test_zcl_cmd_handle_list[] =
*	{
*		{HA_PROFILE_ID, 0x0006, 0x0000, 0x01, 0x00, user_onoff_cluster_on_command_handler, {true, true, false, true}},
*		{HA_PROFILE_ID, 0x0006, 0x0000, 0x01, 0x01, user_onoff_cluster_off_command_handler, {true, true, false, true}},
*	};
*/
void app_custom_zcl_command_handle_register(app_custom_zcl_cmd_handle_t* handle_list, uint16_t handle_list_member_count) __attribute__((deprecated));

/**介绍：zcl已注册命令表打印
*  参数：
*      port ：打印端口
*  返回：无
*/
void app_print_custom_zcl_command_handle_list_to_port(uint8_t port) __attribute__((deprecated));

/**介绍：结构帧拆分
 * 参数：
 *		buffer : 待拆分的buffer
 *		lenght : buffer长度
 *		format : "uvw" -> 小端 uint8 uint16 uint32 
 *				 "UVW" -> 大端 uint8 uint16 uint32
 *				 "l" -> 小端 MAC 
 *				 "L" -> 大端 MAC 	
 *				 "b" -> array ptr
 *				 "a" -> array buffer, [0]是长度
 *				 "s" -> string
 *  e.g.
 *  		  UINT16 UINT8 UINT8  UINT32
 *  buffer ->  03 00  01    02  11 22 33 44
 *
 *  app_format_spilt_buffer(buffer, length, "vuuw", &arg1, &arg2, &arg3, &arg4);
 *
 */
bool app_format_spilt_buffer(uint8_t* buffer, uint16_t length, const char* format, ...) __attribute__((deprecated));

/**介绍：zcl time client注册插件
*  参数：
*      time_update_interval_ms : 定时请求时间
*	   time_compensation	   : 校准时间
*	   sync_time_callback	   : 时间同步回调
*  返回：无
*/
void app_time_client_plugin_register(uint32_t time_update_interval_ms,
									 int32_t time_compensation,
									 void (*sync_time_callback)(uint32_t utc_time,
											 	 	 	 	 	uint32_t standard_time));

/**介绍：zcl attr list注册函数
*  参数：
*      attr_list  : 属性处理注册列表,
*      				Endpoint 				: 0xff表示支持所有ep
*      				app_check_attr_legality : 该回调支持为NULL
*      				app_attr_handler 		: 该回调支持为NULL
*      attr_count : 属性个数
*
*  e.g.
*  //准备写属性前回调，用于校验写入值是否满足要求，write_data允许被修改，返回true，允许写入，返回false，拒绝写入
*  bool user_xxx_pre_write_attr_handler(uint8_t  trigger_type,
*										uint8_t  endpoint,
*										uint8_t  data_type,
*		 	 	 	 	 	 	 	 	uint8_t  current_data_length,
*		 	 	 	 	 	 	 	 	uint8_t* current_data,
*		 	 	 	 	 	 	 	 	uint8_t  write_data_length,
*		 	 	 	 	 	 	 	 	uint8_t* write_data)
*  {
*		return true; //返回true，允许后续写入，返回false，拒绝后续写入
*  }
*
*  void user_xxx_post_write_attr_handler(uint8_t  trigger_type,
*										 uint8_t  endpoint,
*										 uint8_t  data_type,
*										 uint8_t  data_length,
*										 uint8_t* data)
*  {
*		//写入属性表后的回调，可以用于上报等操作
*  }
*  const app_attr_desc_t c_user_attr_desc[] =
*  {
*  		ZCL_GLOBAL_SERVER_ATTR_DESC(0xFF, ZCL_ON_OFF_CLUSTER_ID, 0xFFF1, user_xxx_pre_write_attr_handler, user_xxx_post_write_attr_handler),
*  };
*
*  void app_plugin_init_callback(void)
*  {
*  		app_zcl_attr_list_register(c_user_attr_desc, sizeof(c_user_attr_desc) / sizeof(c_user_attr_desc[0]));
*  }
*
*  返回：无
*/
void app_zcl_attr_list_register(const app_attr_desc_t* attr_list, uint16_t attr_count);

/**介绍：zcl command list注册函数
*  参数：
*      cmd_list  : 命令处理注册列表,
*      			   Endpoint  : 0xff表示支持所有ep
*      cmd_count : 命令个数
*
*  e.g.
*  返回true表示处理结束，返回false表示继续交由协议栈处理（可能会返回不支持或由插件继续处理）
*  bool user_on_with_timed_off_zcl_cmd_handler(uint8_t trigger_type,
*                              				   EmberAfClusterCommand* cmd,
*                              				   uint8_t* default_resp_status,
*                              				   uint8_t* command_payload,
											   uint16_t command_length,
											   void* cmd_payload_struct)
*  {
*		zcl_on_off_cluster_on_with_timed_off_command_t* cmd_struct = (zcl_on_off_cluster_on_with_timed_off_command_t* )cmd_struct;
*
*		//cmd_struct->on_time
*
*  		return true;
*  }
*  const app_decode_zcl_cmd_list_t c_user_zcl_cmd_list[] =
*  {
*      ZCL_ONOFF_CLUSTER_OFF_COMMAND_DESC(0xff, user_on_with_timed_off_zcl_cmd_handler),
*  }
*
*  void app_plugin_init_callback(void)
*  {
*  		app_zcl_cmd_list_register(c_user_zcl_cmd_list, sizeof(c_user_zcl_cmd_list) / sizeof(c_user_zcl_cmd_list[0]));
*  }
*
*  返回：无
*/
void app_zcl_cmd_list_register(const app_decode_zcl_cmd_list_t* cmd_list, uint16_t cmd_count);

bool app_internal_put_int8u_in_resp(uint8_t value);
bool app_internal_put_int16u_in_resp(uint16_t value);
bool app_internal_put_int24u_in_resp(uint32_t value);
bool app_internal_put_int32u_in_resp(uint32_t value);
bool app_internal_put_block_in_resp(const uint8_t* data, uint16_t length);
bool app_internal_put_zcl_string_in_resp(const uint8_t* zcl_str);
bool app_internal_put_string_in_resp(const char* str);
bool app_internal_put_attr_status_in_resp(uint16_t attr, uint8_t status);
bool app_internal_put_attr_status_record_in_resp(uint16_t attr, uint8_t status, const uint8_t* data, uint16_t length);
/**
 *  介绍：注册 ZCL 全局属性访问 Hook（读属性、写属性、上报、响应等）
 *
 *  参数：
 *      hooks : 指向 zcl_internal_global_hooks_t 结构体的指针，
 *              该结构体包含所有 ZCL 属性相关的回调函数指针，包括：
 *                  - on_read_attr        : 处理 Read Attributes 请求的分片回调（已经按照单个属性拆分）
 *                  - on_write_attr       : 处理 Write Attributes 请求的分片回调（已经按照单个属性拆分）
 *                  - on_report_attr      : 处理 Report Attributes 的分片回调（暂不支持）
 *                  - on_write_attr_resp  : 处理 Write Attributes Response 的分片回调（暂不支持）
 *                  - on_read_attr_resp   : 处理 Read Attributes Response 的分片回调（暂不支持）
 *                  - on_default_resp     : 处理 Default Response 的回调（暂不支持）
 *
 *  返回：无
 *  on read attr可以通过app_internal_put_*函数填充返回数据，例如
 *  static bool app_on_read_attr(uint8_t endpoint,
								 uint16_t cluster,
								 uint16_t attr,
								 uint8_t mask,
								 uint16_t mfg_code,
								 uint8_t* payload_tail,
								 uint16_t* payload_length,
								 uint16_t max_length)
	{
		if(cluster == 0x0000 && attr == 0x0005)
		{
			if(app_internal_put_attr_status_in_resp(attr, EMBER_ZCL_STATUS_SUCCESS) &&
			   app_internal_put_string_in_resp("RH0001"))
			{
				return true; //协议栈不继续处理该属性
			}
		}

		return false; //返回false后协议栈会自动处理该属性
	}
 */
void app_internal_global_attr_hooks_register(const zcl_internal_global_hooks_t* hooks);

/** 介绍 ：快速上下电监测
 *  参数 ：required_min_count : 触发回调最小次数 （最大31次）
 *  	 required_max_count : 触发回调最大次数（最大31次）, 触发次数在[required_min_count, required_max_count]内有效
 *  	 first_record_backoff_min_ms    : 初次记录时需要保持的上电时间最小时间
 *  	 first_record_backoff_max_ms	: 初次记录时需要保持的上电时间最大时间,
 *  	 								     触发时间在[first_record_backoff_min_ms, first_record_backoff_max_ms]内有效,
 *  	 								     当达到first_record_backoff_min_ms时，记录值 = 1
 *  	 								     当达到first_record_backoff_max_ms时，记录值清零
 *  	 								     当first_record_backoff_min_ms >= first_record_backoff_max_ms时，不触发清零操作
 *  	 timeout_ms			: 上电保持timeout_ms后，清除记录值
 *  	 trigger_clear_backoff_ms : 触发回调后清除记录值的退避时间
 *  	 trigger_cb			: 满足条件，触发回调
 *  返回 ：-
 *  使用范例参考 : @fast_power_cycle_usage.c
 */
void app_fast_power_cycle_monitor_plugin_register(uint8_t required_min_count,
		  	  	  	  	  	  	  	  	  	  	  uint8_t required_max_count,
		  	  	  	  	  	  	  	  	  	  	  uint32_t first_record_backoff_min_ms,
		  	  	  	  	  	  	  	  	  	  	  uint32_t first_record_backoff_max_ms,
												  uint32_t timeout_ms,
												  uint32_t trigger_clear_backoff_ms,
												  void (*trigger_cb)(uint8_t counts));

/** 介绍 ：手动清除快速上下电记录
 *  参数 ：-
 *  返回 ：-
 */
void app_fast_power_cycle_record_clear(void);

/** 介绍：fragmentation插件注册接口
 *  注:该接口需要在void stack_key_parameter_configuration(void)调用，或者更早的回调
 *  调用前需在app_common.h中定义以下宏
 *  #define APP_USE_FRAGMENTATION_PLUGIN
 *  #define APP_FRAGMENTATION_PLUGIN_MAX_TX_PACKETS		2
 *  #define APP_FRAGMENTATION_PLUGIN_MAX_RX_PACKETS		2
 *  #define APP_FRAGMENTATION_PLUGIN_BUFFER_SIZE		256
 *  例如以上宏配置表明支持最大单包支持256字节，最大同时支持2个tx包同时发送及2个rx包同时接收
 *  占用内存为（APP_FRAGMENTATION_PLUGIN_MAX_TX_PACKETS + APP_FRAGMENTATION_PLUGIN_MAX_RX_PACKETS）* APP_FRAGMENTATION_PLUGIN_BUFFER_SIZE
 */
void app_fragmentation_plugin_config_register(void);

/**介绍：sleepy end device使用，保持唤醒 x ms
*  参数：
*      ms : 保持唤醒的时间，单位ms
*  返回：无
*/
void app_keep_wakeup_milli_seconds(uint32_t ms);

#endif

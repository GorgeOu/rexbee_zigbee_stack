#ifndef __GLOBAL_GROUP_SCENE_APIS_H__
#define __GLOBAL_GROUP_SCENE_APIS_H__

//注：group table与binding table共用一个列表，
//	  查询可以通过binding list中type为EMBER_UNICAST_BINDING即为group
//	 总大小也可以通过app_get_binding_table_size()获取

/** 介绍：本地增加group接口
 *	参数：endpoint : 设备端点号
 *		 group_id : 1 ~ 0xfffe
 *		 group_name : 该值暂不支持，可以填NULL
 *	返回：EmberAfStatus
 */
EmberAfStatus app_group_plugin_internal_add_group(uint8_t endpoint, uint16_t group_id, uint8_t* group_name);

/** 介绍：本地删除单个group，会连同关联该组的场景一起清除
 *	参数：endpoint : 设备端点号
 *		 group_id : 1 ~ 0xfffe
 *	返回：EmberAfStatus
 */
EmberAfStatus app_group_plugin_internal_remove_group(uint8_t endpoint, uint16_t group_id);

/** 介绍：本地删除endpoint下的所有组，会连同关联该组的场景一起清除
 *	参数：endpoint : 设备端点号
 *	返回：EmberAfStatus
 */
EmberAfStatus app_group_plugin_internal_remove_endpoint_all_group(uint8_t endpoint);

/** 介绍：本地删除所有组，并清除所有场景
 *	参数：无
 *	返回：无
 */
EmberAfStatus app_group_plugin_internal_remove_all_group(void);

/** 介绍：删除组回调注册接口
 *	参数：callback : 注册的回调，在删除组时会调用注册回调
 *	返回：无
 */
void app_groups_plugin_remove_entry_callback_register(void (*callback)(uint8_t endpoint, uint16_t group_id));

/** 介绍：打印组列表
 *	参数：无
 *	返回：无
 */
void app_group_plugin_print_group_table(void);

/** 介绍：zcl scene plugin注册，用于支持标准场景处理流程
 *	参数：extended_scene_table : 用于拓展自定义或未支持的场景属性
 *		 extended_scene_table_entry_count : 拓展数量
 *		 scene_name_support_max_length : 场景名最大字节数，如无需支持场景名，设为0
 *		 handle_list	: 用于注册部分应用回调, scene设置为NULL
 *	返回: 无
 *
 *	默认支持的场景属性：
 *
 *	{ZCL_ON_OFF_CLUSTER_ID, 			ZCL_ON_OFF_ATTRIBUTE_ID, 							},
 *	{ZCL_LEVEL_CONTROL_CLUSTER_ID, 		ZCL_CURRENT_LEVEL_ATTRIBUTE_ID, 					},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_CURRENT_X_ATTRIBUTE_ID,			},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_CURRENT_Y_ATTRIBUTE_ID,			},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_ENHANCED_CURRENT_HUE_ATTRIBUTE_ID	},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_CURRENT_SATURATION_ATTRIBUTE_ID	},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_COLOR_LOOP_ACTIVE_ATTRIBUTE_ID	},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_COLOR_LOOP_DIRECTION_ATTRIBUTE_ID	},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_COLOR_LOOP_TIME_ATTRIBUTE_ID		},
 *	{ZCL_COLOR_CONTROL_CLUSTER_ID, 		ZCL_COLOR_CONTROL_COLOR_TEMPERATURE_ATTRIBUTE_ID	},
 *	{ZCL_WINDOW_COVERING_CLUSTER_ID, 	ZCL_CURRENT_LIFT_PERCENTAGE_ATTRIBUTE_ID			},
 *	{ZCL_WINDOW_COVERING_CLUSTER_ID, 	ZCL_CURRENT_TILT_PERCENTAGE_ATTRIBUTE_ID			},
 *
 *	e.g.
 *	  1. 使用默认场景表
 *      app_scene_plugin_register(NULL, 0, 0, NULL);
 *    2. 增加额外场景拓展表（在默认场景表基础上增加额外场景属性支持）
 *		const app_scene_plugin_scene_entry_t c_extended_scene_table[] =
 *		{
 *			{ZCL_THERMOSTAT_CLUSTER_ID, ZCL_OCCUPIED_COOLING_SETPOINT_ATTRIBUTE_ID, ZCL_INT16S_ATTRIBUTE_TYPE, 2, {0, 0}},
 *			{ZCL_THERMOSTAT_CLUSTER_ID, ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID, ZCL_INT16S_ATTRIBUTE_TYPE, 2, {0, 0}},
 *			{ZCL_THERMOSTAT_CLUSTER_ID, ZCL_SYSTEM_MODE_ATTRIBUTE_ID, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, {0, 0}},
 *			{ZCL_FAN_CONTROL_CLUSTER_ID, ZCL_FAN_CONTROL_FAN_MODE_ATTRIBUTE_ID, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, {0, 0}},
 *			{ZCL_FAN_CONTROL_CLUSTER_ID, ZCL_FAN_ON_OFF, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, {0, 0}},
 *		};
 *      app_scene_plugin_register(c_extended_scene_table, (sizeof(c_extended_scene_table) / sizeof(c_extended_scene_table[0])), 0, NULL);
 *    3. 需要场景名记录支持，例如需要最大8字节的场景名
 *      app_scene_plugin_register(NULL, 0, 8, NULL);
 *	注：
 *	该注册接口默认在__weak void app_universal_plugin_init_callback(void)已经调用,
 *	如不希望使用可以在应用中实现空函数void app_universal_plugin_init_callback(void){}
 */
void app_scene_plugin_register(app_scene_plugin_scene_entry_t* extended_scene_table,
							   uint8_t extended_scene_table_entry_count,
							   uint8_t scene_name_support_max_length,
							   stack_application_zcl_handle_t* handle_list);

/** 介绍：本地增加场景(使用zcl定义数据)
 *	参数：endpoint : 设备端点号
 *		 group_id : 1 ~ 0xfffe
 *		 scene_id : 1 ~ 0xff
 *		 force_add_group : true - 如无该设置组，则强制增加该组, false - 如无该设置组，则返回EMBER_ZCL_STATUS_INVALID_FIELD
 *		 enhanced_scene  : true - transition time使用100ms做单位, false - transition time使用秒做单位
 *		 transition_time : 过渡时间，单位参照enhanced_scene
 *		 scene_name		 : 场景名，e.g. {0x05,0x73,0x6C,0x65,0x65,0x70}, length + name string 不设场景名可以设为NULL
 *		 extension_field_sets_length : 场景内容集长度
 *		 extension_field_sets		 : 场景内容集，参照zcl chapter scenes : add scene command extension field sets介绍
 *	返回：EmberAfStatus
 */
EmberAfStatus app_scene_plugin_internal_primitive_add_scene(uint8_t  endpoint,
														    uint16_t group_id,
														    uint8_t  scene_id,
														    bool     force_add_group,
														    bool     enhanced_scene,
														    uint16_t transition_time,
														    uint8_t* scene_name,
														    uint8_t  extension_field_sets_length,
														    uint8_t* extension_field_sets);

/** 介绍：本地存储当前状态为场景
 *	参数：endpoint : 设备端点号
 *		 group_id : 1 ~ 0xfffe
 *		 scene_id : 1 ~ 0xff
 *		 force_add_group : true - 如无该设置组，则强制增加该组, false - 如无该设置组，则返回EMBER_ZCL_STATUS_INVALID_FIELD
 *	返回：EmberAfStatus
 */
EmberAfStatus app_scene_plugin_internal_store_scene(uint8_t  endpoint,
												    uint16_t group_id,
												    uint8_t  scene_id,
												    bool     force_add_group);

/** 介绍：本地删除单个场景
*	参数：endpoint : 设备端点号
*		 group_id : 1 ~ 0xfffe
*		 scene_id : 1 ~ 0xff
*	返回：EmberAfStatus
*/
EmberAfStatus app_scene_plugin_internal_remove_scene(uint8_t  endpoint,
												     uint16_t group_id,
												     uint8_t  scene_id);

/** 介绍：本地某个组下的所有场景
*	参数：endpoint : 设备端点号
*		 group_id : 1 ~ 0xfffe
*	返回：EmberAfStatus
*/
EmberAfStatus app_scene_plugin_internal_remove_all_scene(uint8_t  endpoint,
														 uint16_t group_id);

/** 介绍：获取场景表总大小
*	参数：无
*	返回：场景表总大小
*/
uint8_t app_scene_plugin_scene_table_size(void);

/** 介绍：通过索引号获取场景内容
*	参数：index : 列表索引号
*		 entry : 返回的节点信息，通过拷贝形式
*	返回：EMBER_SUCCESS - 获取到有效节点内容，其他 - 获取失败
*
*	e.g.
*	app_scene_plugin_scene_table_entry_t entry;
*	EmberStatus status = app_scene_plugin_get_scene_entry(0, &entry);
*/
EmberStatus app_scene_plugin_get_scene_entry(uint8_t index, app_scene_plugin_scene_table_entry_t* entry);

/** 介绍：删除场景回调注册接口
*	参数：callback : 在设备删除场景时会调用注册回调，注 ： endpoint为0xFF时表示删除所有组内的场景，此时group id和scene id无效。
*	返回：无
*/
void app_scenes_plugin_remove_entry_callback_register(void (*callback)(uint8_t endpoint, uint16_t group_id, uint8_t scene_id, void* data));

/** 介绍：打印场景表
*	参数：无
*	返回：无
*/
void app_scene_plugin_print_scene_table(void);

#endif

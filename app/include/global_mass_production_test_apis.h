#ifndef __GLOBAL_MT_TEST_APIS_H__
#define __GLOBAL_MT_TEST_APIS_H__

typedef enum _app_mfg_mt_state_enum
{
	APP_MFG_MT_STATE_IDLE,
	APP_MFG_MT_STATE_SCAN,
	APP_MFG_MT_STATE_PASSIVE_SCAN,
	APP_MFG_MT_STATE_START,
	APP_MFG_MT_STATE_PRE_AGING,
	APP_MFG_MT_STATE_IN_AGING,
	APP_MFG_MT_STATE_POST_AGING,
	APP_MFG_MT_STATE_END_SUCCESS  = 0xF0,
	APP_MFG_MT_STATE_END_FAILURE  = 0xF1,
	APP_MFG_MT_STATE_SCAN_TIMEOUT = 0xF2,
	APP_MFG_MT_STATE_STOP_BY_APP  = 0xF3,
	APP_MFG_MT_STATE_STOP_BY_CERT = 0xF4,
	APP_MFG_MT_STATE_STOP_NO_TASK = 0xF5,
	APP_MFG_MT_STATE_STOP_LINK_TIMEOUT = 0xF6,
} app_mfg_mt_state_enum_t;

extern void app_incoming_raw_message_handle_unregister(void);

/** 介绍：被动式搜索产测, 用于开始被动式产测
 *  参数： scan_timeout_ms 					: 等待接收信标的时长，若等待期间内未收到，则退出产测(state : APP_MFG_MT_STATE_SCAN_TIMEOUT)
 *  	 link_cert_keep_rx_on_timeout_ms 	: 连接cert后保持连接的时长
 *  	 callback    	  		  			: 产测命令接收回调
 *  	 only_no_network_allowed 			: true - 仅在无网络时允许注册产测， false - 无条件注册产测
 *  返回 ：无
 */
void app_passive_mass_production_test_start(uint32_t scan_timeout_ms,
											uint32_t link_cert_keep_rx_on_timeout_ms,
											uint8_t (*callback)(uint8_t* source_eui64,
																uint16_t index,
																uint8_t  sub,
																uint16_t command,
																uint8_t* data,
																uint8_t  length,
																uint8_t  rssi_abs,
																void*    extra),
											bool only_no_network_allowed);

void app_v3_passive_mass_production_test_start(uint32_t scan_timeout_ms,
												uint32_t link_cert_keep_rx_on_timeout_ms,
												uint8_t (*callback)(uint8_t* source_eui64,
																	uint16_t index,
																	uint8_t sub,
																	uint16_t command,
																	uint8_t* data,
																	uint8_t length,
																	uint8_t rssi_abs,
																	void* extra),
												bool only_no_network_allowed,
												uint16_t module_type);

/** 介绍：  主动式搜索产测, 用于开始主动式产测
 *  参数：  channel 							: 主动式产测搜索的信道， 0x0B ~ 0x1A
 *  	  scan_timeout_ms 					: 等待接收信标的时长，若等待期间内未收到，则退出产测(state : APP_MFG_MT_STATE_SCAN_TIMEOUT)
 *  	  link_cert_keep_rx_on_timeout_ms 	: 连接cert后保持连接的时长
 *  	  callback    	  		  			: 产测命令接收回调
 *  	  only_no_network_allowed			: true - 仅在无网络时允许注册产测， false - 无条件注册产测
 *  返回： 无
 */
void app_active_mass_production_test_start(uint8_t  channel,
										   uint32_t scan_timeout_ms,
										   uint32_t link_cert_keep_rx_on_timeout_ms,
										   uint8_t (*callback)(uint8_t* source_eui64,
															   uint16_t index,
															   uint8_t  sub,
															   uint16_t command,
															   uint8_t* data,
															   uint8_t  length,
															   uint8_t  rssi_abs,
															   void*    extra),
										   bool only_no_network_allowed);

void app_v3_active_mass_production_test_start(uint8_t  channel,
										   uint32_t scan_timeout_ms,
										   uint32_t link_cert_keep_rx_on_timeout_ms,
										   uint8_t (*callback)(uint8_t* source_eui64,
															   uint16_t index,
															   uint8_t sub,
															   uint16_t command,
															   uint8_t* data,
															   uint8_t length,
															   uint8_t rssi_abs,
															   void* extra),
										   bool only_no_network_allowed,
										   uint16_t module_type);

/** 介绍：  产测终止接口
 *  参数：  -
 *  返回： 无
 */
void app_mass_production_test_stop(void);

/** 介绍：  产测是否进行中判定接口
 *  参数：  -
 *  返回： true - 产测进行中, false - 产测未进行
 */
bool app_is_mass_production_test_underway(void);

/** 介绍：  产测数据（无线）发送接口
 *  参数： command, index(OD), sub等参数参照文档
 *  返回： 0 - 成功, 其他 - 失败
 */
EmberStatus app_send_mt_message(uint16_t command,
								uint16_t index,
								uint8_t  sub,
								uint8_t* data,
								uint8_t  length);

#endif

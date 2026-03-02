
#ifndef __GLOBAL_NWK_MGMT_APIS_H__
#define __GLOBAL_NWK_MGMT_APIS_H__

/** 介绍：设置应用扫描网络的选项
 *  参数：opt - 参考 APP_SCAN_NETWORK_OPT_# 定义
 */
#define APP_SCAN_NETWORK_OPT_OOO_CHANNEL               		BIT(0) // 无序信道
#define APP_SCAN_NETWORK_OPT_RANDOM_NAP                		BIT(1) // 每次信道扫描后随机休眠
#define APP_SCAN_NETWORK_OPT_TC_KEY_REQ_BUSY           		BIT(2) // 当 TC 密钥请求进行时禁用中继
#define APP_SCAN_NETWORK_OPT_DISABLE_GLOBAL_LINK_KEY   		BIT(3) // 禁用全局链路密钥
#define APP_SCAN_NETWORK_OPT_DISABLE_INSTALL_LINK_KEY  		BIT(4) // 禁用安装链路密钥
#define APP_SCAN_NETWORK_OPT_DISABLE_DIST_LINK_KEY     		BIT(5) // 禁用分发链路密钥
#define APP_SCAN_NETWORK_OPT_ALTER_WITH_HANDSHAKE_BR_2_1   	BIT(6) // 启用扫网交替发送增强型握手br（2次普通br + 1次增强型br）
#define APP_SCAN_NETWORK_OPT_ALTER_WITH_HANDSHAKE_BR_1_1	BIT(7) // 启用扫网交替发送增强型握手br（1次增强型br + 1次普通br）

typedef enum
{
	APP_SCAN_NETWORK_EVENT_INIT,				//扫网初始化通知
	APP_SCAN_NETWORK_EVENT_INDICATE,			//扫网过程指示，每500ms触发一次
	APP_SCAN_NETWORK_EVENT_JOINED,				//入网成功通知
	APP_SCAN_NETWORK_EVENT_TIMEOUT,				//扫网超时通知
	APP_SCAN_NETWORK_EVENT_ZBCK_CONNECTED,		//与zbck握手成功通知
	APP_SCAN_NETWORK_EVENT_ZBCK_DISCONNECTED,	//与zbck连接断开通知
	APP_SCAN_NETWORK_EVENT_ZBCK_JOINED,			//通过zbck配网成功通知
} app_scan_network_event_enum_t;

void app_set_scan_network_options(uint16_t opt);

/** 介绍：每次信道扫描后休眠一段时间
 *  参数：nap_ms - 休眠时长范围，随机在 0 ~ nap_ms 毫秒之间
 *  返回：-
 *  注意：仅当启用 APP_SCAN_NETWORK_OPT_RANDOM_NAP 选项时生效
 */
void app_set_scan_network_channel_nap(uint16_t nap_ms);

/** 介绍：应用是否正在配网
 *  返回：true  - 正在扫描
 *       false - 空闲
 */
bool app_is_scan_network_v3_underway(void);
bool app_is_scan_network_v2_underway(void) __attribute__((deprecated));

/** 介绍：配网启动函数（V3）
 *  参数：timeout      - 扫描时长限制（秒），取值范围 1 ~ 0xFFFF；0xFFFF 表示不限制时长，直到轮数结束或成功加入网络
 *       wait_tc_link - 是否等待 TC 链接密钥传输；true：等待 TC 链接完成后再继续；false：默认模式
 *       scan_opt	  - 扫网选项，参照APP_SCAN_NETWORK_OPT_#定义
 *       event_cb     - 扫网过程事件回调
 *  返回：-
 *  注意：timeout 为 0xFFFFFFFF 时，扫描将持续进行，直到加入网络
 *  示例：重置网络并刷新扫描 300 秒，使用默认扫描参数
 *         static void user_scan_event_cb(app_scan_network_event_enum_t event)
 *         {
 *
 *         }
 *         app_scan_network_v3_start(300, true, 0, user_scan_event_cb);
 */
void app_scan_network_v3_start(uint32_t timeout_s,
							   bool wait_tc_link,
							   uint16_t scan_opt,
							   void (*event_cb)(app_scan_network_event_enum_t event));

void app_scan_network_v2_start(uint8_t counts, uint16_t timeout, bool wait_tc_link) __attribute__((deprecated));

/** 介绍：配网启动函数增强型（V3)
 *  参数：counts       - 扫描轮数，取值范围 1 ~ 0xFE；0xFF 表示不限制轮数，直到超时或成功加入网络
 *       timeout      - 扫描时长限制（秒），取值范围 1 ~ 0xFFFF；0xFFFF 表示不限制时长，直到轮数结束或成功加入网络
 *       wait_tc_link - 是否等待 TC 链接密钥传输；true：等待 TC 链接完成后再继续；false：默认模式
 *       scan_opt	  - 扫网选项，参照APP_SCAN_NETWORK_OPT_#定义
 *       event_cb     - 扫网过程事件回调
 *       primary_channel_mask   - 交替扫网信道掩码，例如11,15,20, 可以使用BIT(11)|BIT(15)|BIT(20)，全信道掩码可以使用ZIGBEE_2_4_GHZ_ALL_802_15_4_CHANNELS_MASK
 *       secondary_channel_mask - 交替扫网信道掩码，例如11,15,20, 可以使用BIT(11)|BIT(15)|BIT(20)，全信道掩码可以使用
 *       scan_duration          - zigbee 2.4g 建议使用3, subg 建议用5
 *  返回：-
 *  注意：当 counts 为 0xFFFF 且 timeout 为 0xFFFFFFFF 时，扫描将持续进行，直到加入网络
 *  示例：重置网络并刷新扫描 300 秒，使用默认扫描参数
 *         static void user_scan_event_cb(app_scan_network_event_enum_t event)
 *         {
 *
 *         }
 *         app_scan_network_v3_start_with_enhanced_option(0xFFFF, 300, true,
 *         												  APP_SCAN_NETWORK_OPT_OOO_CHANNEL,
 *         												  user_scan_event_cb,
 *         												  BIT(11)|BIT(15)|BIT(20)|BIT(25),
 *         												  BIT(12)|BIT(13)|BIT(14)|BIT(16)|BIT(17)|BIT(18)|\
 *         												  BIT(19)|BIT(21)|BIT(22)|BIT(23)|BIT(24)|BIT(26),
 *         												  3);
 */
void app_scan_network_v3_start_with_enhanced_option(uint16_t counts,
													uint32_t timeout_s,
													bool wait_tc_link,
													uint16_t scan_opt,
													void (*event_cb)(app_scan_network_event_enum_t event),
													uint32_t primary_channel_mask,
													uint32_t secondary_channel_mask,
													uint8_t scan_duration);

void app_scan_network_v2_start_with_enhanced_option(uint8_t counts,
													uint16_t timeout,
													bool waitTcLink,
													uint32_t primary_channel_mask,
													uint32_t secondary_channel_mask,
													uint8_t scan_duration) __attribute__((deprecated));

/** 介绍：配网停止函数（V2），停止当前的网络扫描
 *  功能：
 *  参数：-
 *  返回：-
 */
bool app_scan_network_v3_stop(void);
void app_scan_network_v2_stop(void) __attribute__((deprecated));

/**介绍：获取设备的网络状态
*  参数: -
*  返回：
*		EMBER_NO_NETWORK					= 0,
*		EMBER_JOINING_NETWORK				= 1,
*		EMBER_JOINED_NETWORK				= 2,
*		EMBER_JOINED_NETWORK_NO_PARENT		= 3,
*		EMBER_LEAVING_NETWORK				= 4,
*		//仅当启用app_tc_link_monitor_register插件且使能link_to_network_state时，存在EMBER_JOINED_NETWORK_NO_TC状态
*		//表示与coordinator连接中断
*		EMBER_JOINED_NETWORK_NO_TC			= 5,
*
*/
EmberNetworkStatus app_get_network_state(void);

/**介绍： 设备zigbee信息获取接口
*  参数: info : 返回拷贝的zigbee node info数据
*  返回： -
*/
void app_get_zigbee_node_info(stack_zigbee_node_info_t* info);

/**介绍：设备离网
*  参数: -
*  返回： 0x00 : 执行成功， 0x70 : 未入网
*/
EmberStatus app_leave_network(void);

/**介绍： 设备extended pan id获取接口
*  参数: result : 8字节extended pan id存储数组, 拷贝8字节extended pan id数据至result
*  返回： -
*/
void app_get_extended_pan_id(uint8_t* result);

/**介绍： 设备parent mac获取接口(父节点mac)
*  参数: result : 8字节parent mac存储数组, 拷贝8字节parent mac数据至result
*  返回： -
*/
void app_get_parent_mac(uint8_t* result);

/**介绍： 设备父节点node id获取接口
*  参数: -
*  返回：设备父节点node id
*/
uint16_t app_get_parent_node_id(void);

/**介绍： 设备node id(网络短地址)获取接口
*  参数: -
*  返回：设备node id
*/
uint16_t app_get_node_id(void);

/**介绍： 设备pan id获取接口
*  参数: -
*  返回：设备pan id
*/
uint16_t app_get_pan_id(void);

/**介绍： 设备射频发射功率获取接口
*  参数: -
*  返回：设备发射功率
*/
int8_t app_get_radio_power(void);

/**介绍： 设备网络信道获取接口
*  参数: -
*  返回：设备网络信道
*/
uint8_t app_get_zigbee_radio_channel(void);

/**介绍： 设备当前物理信道获取接口
*  参数: -
*  返回：设备当前物理信道
*/
uint8_t app_get_radio_channel(void);

/**介绍： 设备获取上一次通讯的rssi
*  参数: rssi : 获取rssi的内存变量指针
*  返回： -
*/
void app_get_last_hop_rssi(int8_t* rssi);

/**介绍： 设备获取上一次通讯的lqi
*  参数: lqi : 获取lqi的内存变量指针
*  返回： -
*/
void app_get_last_hop_lqi(uint8_t* lqi);

/**介绍：获取设备网络备份区的网络状态
*  参数: -
*  返回：
*		EMBER_NO_NETWORK					= 0,
*		EMBER_JOINING_NETWORK				= 1,
*		EMBER_JOINED_NETWORK				= 2,
*		EMBER_JOINED_NETWORK_NO_PARENT		= 3,
*		EMBER_LEAVING_NETWORK				= 4,
*/
EmberNetworkStatus app_get_backup_network_state(void);

/**介绍：清除设备网络备份区的网络数据，清除后备份区网络变更为无网络
*  参数: -
*  返回： -
*/
void app_clear_backup_network_token_data(void);

/**介绍：备份当前的网络数据
*  参数: -
*  返回： -
*/
void app_backup_current_network_token_data(void);

/**介绍：从备份区恢复网络
*  参数: -
*  返回: EMBER_SUCCESS 		- 恢复成功
*       EMBER_ERR_FATAL 	- 备份区数据无效
*  		EMBER_NOT_JOINED 	- 备份区无网络
*  		EMBER_INVALID_CALL 	- 当前设备已有网络
*
*/
EmberStatus app_recover_network_from_backup_data(void);

/**介绍：获取上次与中心节点的通讯时间到当前的时间差（ms）
 * 参数： -
 * 返回：上次与中心节点的通讯时间到当前的时间差（ms）
 */
uint32_t app_get_app_dest_node_last_comm_interval(void);

typedef enum _app_tc_link_status_enum
{
	APP_TC_LINK_INIT,
	APP_TC_LINK_CONNECTED,
	APP_TC_LINK_DISCONNECTED,
	APP_TC_LINK_NO_NETWORK,
} app_tc_link_status_enum_t;

/**介绍：Trust Center (TC) 链接监测与维护  V2
 * 参数：
 *   via_report_tbl				  : true  - 断连判定时间参照心跳表中的最小心跳间隔 * disconn_sec_or_report_count,
 *   								false - 直接使用disconn_sec_or_report_count作为超时时间
 *   disconn_sec_or_report_count  : 当via_report_tbl为true时，断连判定的心跳次数，单位：次，有效范围 1 ~ 65535, 建议设置为 ≥2 次心跳周期
 *   								当via_report_tbl为false时，断连判定时间, 单位：秒， 有效范围1 ~ 1048575s（距上次收到 TC 消息超过该时间即判定为断连并触发回调），建议设置为 ≥2 次心跳周期
 *   auto_reconnect  			  : 断连后是否自动发送快速重连消息，建议根据网络环境需求选择开启或关闭，建议关关闭，开启后容易产生较多的路由请求数据
 *   startup_backoff_ms           : 上电或网络初始化阶段的退避时间（在此期间不进行断连判定），建议设置为 ≥5000ms，以避免初始化时误判
 *   state_changed_cb             : 链接状态变更回调函数；参数 last_state 和 state 分别表示前一状态与当前状态，状态值参考 app_tc_link_status_enum_t
 *   link_to_network_state        : 是否将 TC 链接状态映射为整体网络状态，在 TC 链接断开/恢复时同步更新设备网络可达性,
 *   								true - 与TC断联的情况下将状态关联至app_get_network_state - EMBER_JOINED_NETWORK_NO_TC
 * 返回：-
 */
void app_tc_link_plugin_link_state_monitor_v2_register(bool via_report_tbl,
													   uint32_t disconn_sec_or_report_count,
													   bool auto_reconnect,
													   uint32_t startup_backoff_ms,
													   void (*state_changed_cb)(uint8_t last_state, uint8_t state),
													   bool link_to_network_state);

void app_tc_link_plugin_link_state_monitor_register(uint32_t disconnected_ms,
												    bool auto_reconnect,
												    uint32_t startup_backoff_ms,
												    void (*state_changed_cb)(uint8_t last_state, uint8_t state),
												    bool link_to_network_state) __attribute__((deprecated));

/**介绍：获取Trust Center (TC) 链接状态
 * 		仅当app_tc_link_plugin_link_state_monitor_register注册后有效
 * 参数：-
 * 返回：app_tc_link_status_enum_t
 */
app_tc_link_status_enum_t app_tc_link_plugin_get_link_state(void);


/**介绍：zbck apis
 *
 */
enum
{
	ZBCK_SECURE_MODE_NONE 				= 0,	//allow all zbck operation
	ZBCK_SECURE_MODE_NWK_KEY_PROTECTION = 1,	//enabled unsecure operation before device joined
	ZBCK_SECURE_MODE_OPERATE_PROTECTION = 2, 	//enabled unsecure device disc, protect device operation
	ZBCK_SECURE_MODE_HIDDEN				= 3,	//disable device disc before unlocking
	ZBCK_SECURE_MODE_DENY_ANY = 0xff,			//deny any zbck operation
};
void stack_set_zbck_secure_mode(uint8_t mode);

enum
{
	ZBCK_SERVER_NOTIFY_STATE_IDLE,
	ZBCK_SERVER_NOTIFY_STATE_SENDING_ROUND_1,
	ZBCK_SERVER_NOTIFY_STATE_SENDING_ROUND_2,
	ZBCK_SERVER_NOTIFY_STATE_SENDING_ROUND_3,
	ZBCK_SERVER_NOTIFY_STATE_TIMEOUT,
	ZBCK_SERVER_NOTIFY_STATE_FOUND,
};
/**介绍：设备主动向zbck发送握手请求
 * 参数：
 *   channel_mask             : 搜索的信道掩码，default api中默认为0x07FFF800
 *   expiration  		      : 设备退出zbck连接状态的超时时间，单位秒，default api中默认为120s
 *   resident_channel         : 得到握手应答后，停留的信道，设置为0时，停留到收到握手应答的信道，default api中默认为0
 *   callback                 : 链接状态变更回调函数；state参考ZBCK_SERVER_NOTIFY_STATE_IDLE ~ ZBCK_SERVER_NOTIFY_STATE_FOUND
 * 返回：-
 */
void stk_zbck_device_send_handshake_notify(uint32_t channel_mask, uint32_t expiration, uint8_t resident_channel, void (*callback)(uint8_t state));
	void stack_zbck_device_send_default_handshake_notify(void (*callback)(uint8_t state));


#endif

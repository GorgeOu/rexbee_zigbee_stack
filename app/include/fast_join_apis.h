#ifndef __FAST_JOIN_APIS_H__
#define __FAST_JOIN_APIS_H__

typedef enum _fast_join_v3_client_status_enum
{
	FAST_JOIN_V3_CLIENT_STATUS_IDLE,
	FAST_JOIN_V3_CLIENT_STATUS_SCAN,
	FAST_JOIN_V3_CLIENT_STATUS_REPORTING,
	FAST_JOIN_V3_CLIENT_STATUS_JOINED,
	FAST_JOIN_V3_CLIENT_STATUS_REJECTED,
	FAST_JOIN_V3_CLIENT_STATUS_NO_ACK,
	FAST_JOIN_V3_CLIENT_STATUS_TIMEOUT,
	FAST_JOIN_V3_CLIENT_STATUS_STOP,
} fast_join_v3_client_status_enum_t;

typedef struct _fast_join_v3_client_scan_cb
{
	void (*init_cb)(void);
	void (*joined_cb)(fast_join_v3_client_status_enum_t status);
	void (*failure_cb)(fast_join_v3_client_status_enum_t status);
	void (*status_changed_cb)(fast_join_v3_client_status_enum_t last_status, fast_join_v3_client_status_enum_t status);
} fast_join_v3_client_scan_cb_t;

/**介绍：Rexense自有快速入网V3版本： 快速入网启动函数
*  参数: scan_timeout_s : 快速入网尝试时长/秒
*        callbacks	    : 快速入网回调注册（包含初始化回调，入网成功回调，入网失败回调，状态变更回调）
*        				    详情参照fast_join_v3_client_scan_cb_t
*  返回： 0 - success, other - failure
*/
uint8_t app_fast_join_v3_client_scan_start(uint16_t scan_timeout_s, const fast_join_v3_client_scan_cb_t* callbacks);

/**介绍：Rexense自有快速入网V3版本： 快速入网停止函数
*  参数: 无
*  返回： 无
*/
void app_fast_join_v3_client_scan_stop(void);

/**介绍：Rexense自有快速入网V3版本： 快速入网进行状态
*  参数: 无
*  返回： true - 进行中, false - 未进行
*/
bool app_is_fast_join_v3_client_scan_underway(void);


#if 0
弃用V2版本快配接口
/**介绍： Rexense自有快速入网相关： 设置快速入网发射功率（-10 ~ 10）
*  参数: power : 快速入网时的发设功率[-10 , 10]
*  返回： 0 - success, other - failure
*/
EmberStatus app_set_fast_join_tx_power(int8_t power);

/**介绍：Rexense自有快速入网相关： 快速入网启动函数
*  参数: duraion_second : 快速入网尝试时长/秒
*  返回： 0 - success, other - failure
*/
EmberStatus app_fast_join_v2_start(uint16_t duraion_second);

/**介绍： Rexense自有快速入网相关： 快速入网停止函数
*  参数: 无
*  返回：  0 - success, other - failure
*/
EmberStatus	app_fast_join_v2_stop(void);

/**介绍： Rexense自有快速入网相关： 快速入网进行中判断
*  参数: 无
*  返回： true - 进行中, false - 未进行
*/
bool app_is_fast_join_v2_underway(void);
#endif

#endif

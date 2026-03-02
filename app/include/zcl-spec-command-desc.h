
#ifndef __ZCL_SPEC_CLUSTER_COMMAND_DESC_H__
#define __ZCL_SPEC_CLUSTER_COMMAND_DESC_H__

//note : format support up to 16 members

/** Format : "uvw" -> 小端 uint8 uint16 uint32
 * 			 "l" -> 小端 MAC
 *			 "+" -> 可选，无该参数时补0xFF
 *			 "-" -> 可选，无该参数时补0x00
 *			 "p" -> 后续的数据头指针
 *			 "b" -> 数组指针
 */

//Find Standard Protocol : Cluster : 0x????, Command : 0x??, Direction : ?->?
//e.g. : Cluster : 0x0006, Command : 0x00, Direction : C->S

//Find Private Protocol : Cluster : 0x????, Command : 0x??, Direction : ?->?, MFG : ??
//e.g. : Cluster : 0x0006, Command : 0x00, Direction : C->S, MFG : REX


//User private protocol description :
// typedef struct _private_struct
//{
//	uint8_t a;
//	uint8_t b;
//	uint8_t c;
//} zcl_private_command_t;
//{profile, cluster, mfg_code, endpoint(0xff allow all ep), command_id, format,
//		callback,
//		{zcl_server_to_client_command, auto_default_resp, zcl_mfg_command, zcl_spec_command, padding(0)},
//		{offsetof(zcl_private_command_t, a), offsetof(zcl_private_command_t, b), offsetof(zcl_private_command_t, c), ...}}

//--------------------------------------------
//Identify Cluster(Client->Server)
//
//

//Cluster : 0x0003, Command : 0x00, Direction : C->S
typedef struct __zcl_identify_cluster_identify_command
{
	uint16_t identify_time;
} zcl_identify_cluster_identify_command_t;
#define ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_IDENTIFY_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_IDENTIFY_COMMAND_ID, "v", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_identify_cluster_identify_command_t, identify_time)}}

//Cluster : 0x0003, Command : 0x01, Direction : C->S
#define ZCL_IDENTIFY_CLUSTER_QUERY_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_IDENTIFY_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_IDENTIFY_QUERY_COMMAND_ID, "", \
		cb, {false, true, false, true, 0}, \
		{NULL}}

//Cluster : 0x0003, Command : 0x02, Direction : C->S
typedef struct __zcl_identify_cluster_ez_mode_invoke_command
{
	uint8_t action;
} zcl_identify_cluster_ez_mode_invoke_command_t;
#define ZCL_IDENTIFY_CLUSTER_EZ_MODE_INVOKE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_IDENTIFY_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_E_Z_MODE_INVOKE_COMMAND_ID, "u", \
		cb, {false, true, false, true, 0}, \
		{offsetof(zcl_identify_cluster_ez_mode_invoke_command_t, action)}}

//Cluster : 0x0003, Command : 0x03, Direction : C->S
typedef struct __zcl_identify_cluster_update_commission_state_command
{
	uint8_t action;
	uint8_t commission_state_mask;
} zcl_identify_cluster_update_commission_state_command_t;
#define ZCL_IDENTIFY_CLUSTER_UPDATE_COMMISSION_STATE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_IDENTIFY_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_UPDATE_COMMISSION_STATE_COMMAND_ID, "uu", \
		cb, {false, true, false, true, 0}, \
		{offsetof(zcl_identify_cluster_update_commission_state_command_t, action), \
		 offsetof(zcl_identify_cluster_update_commission_state_command_t, commission_state_mask)}}

//Cluster : 0x0003, Command : 0x40, Direction : C->S
typedef struct __zcl_identify_cluster_trigger_effect_command
{
	uint8_t effect_id;
	uint8_t effect_variant;
} zcl_identify_cluster_trigger_effect_command_t;
#define ZCL_IDENTIFY_CLUSTER_TRIGGER_EFFECT_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_IDENTIFY_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_TRIGGER_EFFECT_COMMAND_ID, "uu", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_identify_cluster_trigger_effect_command_t, effect_id), \
		  offsetof(zcl_identify_cluster_trigger_effect_command_t, effect_variant)}}

//Identify Cluster(Server->Client)
//
//

//Cluster : 0x0003, Command : 0x00, Direction : S->C
typedef struct __zcl_identify_cluster_query_response_command
{
	uint16_t timeout;
} zcl_identify_cluster_query_response_command_t;
#define ZCL_IDENTIFY_CLUSTER_QUERY_RESPONSE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_IDENTIFY_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_IDENTIFY_QUERY_RESPONSE_COMMAND_ID, "v", \
		 cb, {true, true, false, true, 0}, \
		 {offsetof(zcl_identify_cluster_query_response_command_t, timeout)}}

//--------------------------------------------
//Groups Cluster(Client->server)
//
//Recommended use of groups plugin

//Groups Cluster(Server->Client)
//
//NULL

//--------------------------------------------
//Scenes Cluster(Client->server)
//
//Recommended use of scenes plugin

//Scenes Cluster(Server->Client)
//
//NULL

//--------------------------------------------
//OnOff Cluster(Client->Server)
//
//

//Cluster : 0x0006, Command : 0x00, Direction : C->S
#define ZCL_ONOFF_CLUSTER_OFF_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_ON_OFF_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_OFF_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0006, Command : 0x01, Direction : C->S
#define ZCL_ONOFF_CLUSTER_ON_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_ON_OFF_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_ON_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0006, Command : 0x02, Direction : C->S
#define ZCL_ONOFF_CLUSTER_TOGGLE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_ON_OFF_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_TOGGLE_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0006, Command : 0x40, Direction : C->S
typedef struct __zcl_on_off_cluster_off_with_effect_command
{
	uint8_t effect_id;
	uint8_t effect_variant;
} zcl_on_off_cluster_off_with_effect_command_t;
#define ZCL_ONOFF_CLUSTER_OFF_WITH_EFFECT_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_ON_OFF_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_OFF_WITH_EFFECT_COMMAND_ID, "uu", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_on_off_cluster_off_with_effect_command_t, effect_id), \
		  offsetof(zcl_on_off_cluster_off_with_effect_command_t, effect_variant)}}

//Cluster : 0x0006, Command : 0x42, Direction : C->S
typedef struct __zcl_on_off_cluster_on_with_timed_off_command
{
	uint8_t  onoff_control;
	uint16_t on_time;
	uint16_t off_wait_time;
} zcl_on_off_cluster_on_with_timed_off_command_t;
#define ZCL_ONOFF_CLUSTER_ON_WITH_TIMED_OFF_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_ON_OFF_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_ON_WITH_TIMED_OFF_COMMAND_ID, "uvv", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_on_off_cluster_on_with_timed_off_command_t, onoff_control), \
		  offsetof(zcl_on_off_cluster_on_with_timed_off_command_t, on_time), \
		  offsetof(zcl_on_off_cluster_on_with_timed_off_command_t, off_wait_time)}}

//OnOff Cluster(Server->Client)
//
//NULL

//--------------------------------------------
//Level Cluster(Client->Server)
//
//
// Cluster: 0x0008, Command: 0x00, Direction: C->S
typedef struct __zcl_level_cluster_move_to_level_command
{
    uint8_t level;
    uint16_t transition_time;
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_move_to_level_command_t;

#define ZCL_LEVEL_CLUSTER_MOVE_TO_LEVEL_COMMAND_DESC(endpoint, cb) \
    {HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_MOVE_TO_LEVEL_COMMAND_ID, "uv++", \
     cb, {false, true, false, true, 0}, \
     {offsetof(zcl_level_cluster_move_to_level_command_t, level), \
      offsetof(zcl_level_cluster_move_to_level_command_t, transition_time), \
      offsetof(zcl_level_cluster_move_to_level_command_t, options_mask), \
      offsetof(zcl_level_cluster_move_to_level_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x01, Direction: C->S
typedef struct __zcl_level_cluster_move_command
{
    uint8_t move_mode;
    uint8_t rate;
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_move_command_t;
#define ZCL_LEVEL_CLUSTER_MOVE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_MOVE_COMMAND_ID, "uu++", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_level_cluster_move_command_t, move_mode), \
		  offsetof(zcl_level_cluster_move_command_t, rate), \
		  offsetof(zcl_level_cluster_move_command_t, options_mask), \
		  offsetof(zcl_level_cluster_move_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x02, Direction: C->S
typedef struct __zcl_level_cluster_step_command
{
    uint8_t step_mode;
    uint8_t step_size;
    uint16_t transition_time;
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_step_command_t;
#define ZCL_LEVEL_CLUSTER_STEP_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_STEP_COMMAND_ID, "uuv++", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_level_cluster_step_command_t, step_mode), \
		  offsetof(zcl_level_cluster_step_command_t, step_size), \
		  offsetof(zcl_level_cluster_step_command_t, transition_time), \
		  offsetof(zcl_level_cluster_step_command_t, options_mask), \
		  offsetof(zcl_level_cluster_step_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x03, Direction: C->S
typedef struct __zcl_level_cluster_stop_command
{
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_stop_command_t;
#define ZCL_LEVEL_CLUSTER_STOP_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_STOP_COMMAND_ID, "++", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_level_cluster_stop_command_t, options_mask), \
		  offsetof(zcl_level_cluster_stop_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x04, Direction: C->S
typedef struct __zcl_level_cluster_move_to_level_with_onoff_command
{
    uint8_t level;
    uint16_t transition_time;
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_move_to_level_with_onoff_command_t;
#define ZCL_LEVEL_CLUSTER_MOVE_TO_LEVEL_WITH_ONOFF_COMMAND_DESC(endpoint, cb) \
    {HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID, "uv++", \
     cb, {false, true, false, true, 0}, \
     {offsetof(zcl_level_cluster_move_to_level_with_onoff_command_t, level), \
      offsetof(zcl_level_cluster_move_to_level_with_onoff_command_t, transition_time), \
      offsetof(zcl_level_cluster_move_to_level_with_onoff_command_t, options_mask), \
      offsetof(zcl_level_cluster_move_to_level_with_onoff_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x05, Direction: C->S
typedef struct __zcl_level_cluster_move_with_onoff_command
{
    uint8_t move_mode;
    uint8_t rate;
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_move_with_onoff_command_t;
#define ZCL_LEVEL_CLUSTER_MOVE_WITH_ONOFF_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_MOVE_WITH_ON_OFF_COMMAND_ID, "uu++", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_level_cluster_move_with_onoff_command_t, move_mode), \
		  offsetof(zcl_level_cluster_move_with_onoff_command_t, rate), \
		  offsetof(zcl_level_cluster_move_with_onoff_command_t, options_mask), \
		  offsetof(zcl_level_cluster_move_with_onoff_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x06, Direction: C->S
typedef struct __zcl_level_cluster_step_with_onoff_command
{
    uint8_t step_mode;
    uint8_t step_size;
    uint16_t transition_time;
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_step_with_onoff_command_t;
#define ZCL_LEVEL_CLUSTER_STEP_WITH_ONOFF_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_STEP_WITH_ON_OFF_COMMAND_ID, "uuv++", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_level_cluster_step_with_onoff_command_t, step_mode), \
		  offsetof(zcl_level_cluster_step_with_onoff_command_t, step_size), \
		  offsetof(zcl_level_cluster_step_with_onoff_command_t, transition_time), \
		  offsetof(zcl_level_cluster_step_with_onoff_command_t, options_mask), \
		  offsetof(zcl_level_cluster_step_with_onoff_command_t, options_override)}}

// Cluster: 0x0008, Command: 0x07, Direction: C->S
typedef struct __zcl_level_cluster_stop_with_onoff_command
{
    uint8_t options_mask;
    uint8_t options_override;
} zcl_level_cluster_stop_with_onoff_command_t;
#define ZCL_LEVEL_CLUSTER_STOP_WITH_ONOFF_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_LEVEL_CONTROL_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_STOP_WITH_ON_OFF_COMMAND_ID, "++", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_level_cluster_stop_with_onoff_command_t, options_mask), \
		  offsetof(zcl_level_cluster_stop_with_onoff_command_t, options_override)}}

//Level Cluster(Server->Client)
//
//NULL

//--------------------------------------------
//Window Covering Cluster(Client->Server)
//
//

//Cluster : 0x0102, Command : 0x00, Direction : C->S
#define ZCL_WINDOW_COVERING_CLUSTER_UP_OPEN_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_UP_OPEN_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0102, Command : 0x01, Direction : C->S
#define ZCL_WINDOW_COVERING_CLUSTER_DOWN_CLOSE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_DOWN_CLOSE_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0102, Command : 0x02, Direction : C->S
#define ZCL_WINDOW_COVERING_CLUSTER_STOP_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_STOP_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0102, Command : 0x04, Direction : C->S
typedef struct __zcl_window_covering_cluster_go_to_lift_value_command
{
	uint16_t lift_value;
} zcl_window_covering_cluster_go_to_lift_value_command_t;
#define ZCL_WINDOW_COVERING_CLUSTER_GO_TO_LIFT_VALUE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_GO_TO_LIFT_VALUE_COMMAND_ID, "v", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_window_covering_cluster_go_to_lift_value_command_t, lift_value)}}

//Cluster : 0x0102, Command : 0x05, Direction : C->S
typedef struct __zcl_window_covering_cluster_go_to_lift_percentage_command 
{
	uint8_t lift_percentage;
} zcl_window_covering_cluster_go_to_lift_percentage_command_t;
#define ZCL_WINDOW_COVERING_CLUSTER_GO_TO_LIFT_PERCENTAGE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE_COMMAND_ID, "u", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_window_covering_cluster_go_to_lift_percentage_command_t, lift_percentage)}}

//Cluster : 0x0102, Command : 0x07, Direction : C->S
typedef struct __zcl_window_covering_cluster_go_to_tilt_value_command
{
	uint16_t tilt_value;
} zcl_window_covering_cluster_go_to_tilt_value_command_t;
#define ZCL_WINDOW_COVERING_CLUSTER_GO_TO_TILT_VALUE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_GO_TO_TILT_VALUE_COMMAND_ID, "v", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_window_covering_cluster_go_to_tilt_value_command_t, tilt_value)}}

//Cluster : 0x0102, Command : 0x08, Direction : C->S
typedef struct __zcl_window_covering_cluster_go_to_tilt_percentage_command
{
	uint8_t tilt_percentage;
} zcl_window_covering_cluster_go_to_tilt_percentage_command_t;
#define ZCL_WINDOW_COVERING_CLUSTER_GO_TO_TILT_PERCENTAGE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE_COMMAND_ID, "u", \
		 cb, {false, true, false, true, 0}, \
		 {offsetof(zcl_window_covering_cluster_go_to_tilt_percentage_command_t, tilt_percentage)}}

//Window Covering Cluster(Server->Client)
//
//NULL


//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
//--------------------------------------------
//Private Protocol
//
//

//Manufacture Name : Tuya
//Cluster : 0xE000, Command : 0xFB, Direction : C->S, MFG : Tuya
#define ZCL_TUYA_PRIVATE_CLUSTER0_INCHING_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_TUYA_PRIVATE_CLUSTER0_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_TUYA_INCHING_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

//Cluster : 0x0102, Command : 0x04, Direction : C->S, MFG : Tuya
#define ZCL_TUYA_WINDOW_COVERING_CLUSTER_GO_TO_LIFT_VALUE_COMMAND_DESC(endpoint, cb) \
		{HA_PROFILE_ID, ZCL_WINDOW_COVERING_CLUSTER_ID, EMBER_AF_NULL_MANUFACTURER_CODE, endpoint, ZCL_WINDOW_COVERING_GO_TO_LIFT_VALUE_COMMAND_ID, "", \
		 cb, {false, true, false, true, 0}, \
		 {NULL}}

#endif // __ZCL_SPEC_CLUSTER_COMMAND_DESC_H__

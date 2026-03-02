
#ifndef __ZCL_GLOBAL_COMMAND_DESC_H__
#define __ZCL_GLOBAL_COMMAND_DESC_H__

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
//Global command(Client->Server)
//
//

//Cluster : 0x????, Command : 0x00, Direction : C->S
#define ZCL_READ_ATTRIBUTE_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, mfg_code, cb) \
		{HA_PROFILE_ID, cluster, mfg_code, endpoint, ZCL_READ_ATTRIBUTES_COMMAND_ID, "", \
		 cb, {false, true, false, false, 0}, \
		 {NULL}}

#define ZCL_READ_ATTRIBUTE_CLIENT_COMMAND_DESC(endpoint, cluster, cb) \
		ZCL_READ_ATTRIBUTE_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, EMBER_AF_NULL_MANUFACTURER_CODE, cb)

//Cluster : 0x????, Command : 0x02, Direction : C->S
#define ZCL_WRITE_ATTRIBUTE_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, mfg_code, cb) \
		{HA_PROFILE_ID, cluster, mfg_code, endpoint, ZCL_WRITE_ATTRIBUTES_COMMAND_ID, "", \
		 cb, {false, true, false, false, 0}, \
		 {NULL}}

#define ZCL_WRITE_ATTRIBUTE_CLIENT_COMMAND_DESC(endpoint, cluster, cb) \
		ZCL_WRITE_ATTRIBUTE_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, EMBER_AF_NULL_MANUFACTURER_CODE, cb)

//Cluster : 0x????, Command : 0x04, Direction : S->C
#define ZCL_WRITE_ATTRIBUTE_RESP_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, mfg_code, cb) \
		{HA_PROFILE_ID, cluster, mfg_code, endpoint, ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID, "", \
		 cb, {true, true, false, false, 0}, \
		 {NULL}}

#define ZCL_WRITE_ATTRIBUTE_RESP_CLIENT_COMMAND_DESC(endpoint, cluster, cb) \
		ZCL_WRITE_ATTRIBUTE_RESP_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, EMBER_AF_NULL_MANUFACTURER_CODE, cb)

//Cluster : 0x????, Command : 0x05, Direction : C->S
#define ZCL_WRITE_ATTRIBUTE_NO_RESP_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, mfg_code, cb) \
		{HA_PROFILE_ID, cluster, mfg_code, endpoint, ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID, "", \
		 cb, {false, true, false, false, 0}, \
		 {NULL}}

#define ZCL_WRITE_ATTRIBUTE_NO_RESP_CLIENT_COMMAND_DESC(endpoint, cluster, cb) \
		ZCL_WRITE_ATTRIBUTE_NO_RESP_CLIENT_MFG_COMMAND_DESC(endpoint, cluster, EMBER_AF_NULL_MANUFACTURER_CODE, cb)

#endif // __ZCL_GLOBAL_COMMAND_DESC_H__


static bool user_on_with_time_off_cmd_handler(uint8_t trigger_type,
											  EmberAfClusterCommand* cmd,
											  uint8_t* default_resp_status,
											  uint8_t*  command_payload,
											  uint16_t command_length,
											  void* cmd_payload_struct);

static bool user_identify_cmd_handler(uint8_t trigger_type,
											  EmberAfClusterCommand* cmd,
											  uint8_t* default_resp_status,
											  uint8_t*  command_payload,
											  uint16_t command_length,
											  void* cmd_payload_struct);
										 
const app_decode_zcl_cmd_list_t c_zcl_cmd_list[] = 
{
	ZCL_IDENTIFY_CLUSTER_IDENTIFY_COMMAND_DESC(0xff, user_identify_cmd_handler),
	ZCL_ONOFF_CLUSTER_ON_WITH_TIMED_OFF_COMMAND_DESC(0xff, user_on_with_time_off_cmd_handler), 
};

void user_zcl_cmd_list_register(void)
{
	app_zcl_cmd_list_register(c_zcl_cmd_list, sizeof(c_zcl_cmd_list) / sizeof(app_decode_zcl_cmd_list_t));
}

static bool user_on_with_time_off_cmd_handler(uint8_t trigger_type,
											  EmberAfClusterCommand* cmd,
											  uint8_t* default_resp_status,
											  uint8_t*  command_payload,
											  uint16_t command_length,
											  void* cmd_payload_struct)
{
	zcl_on_off_cluster_on_with_timed_off_command_t* payload_struct = 
			(zcl_on_off_cluster_on_with_timed_off_command_t* )cmd_payload_struct;

	uint8_t endpoint = cmd->apsFrame->destinationEndpoint;

	app_v2_device_report_attr_mfg(g_report_target_node,	
								  endpoint, 
								  g_report_target_ep, 
								  ZCL_ON_OFF_CLUSTER_ID, 
								  ZCL_ON_TIME_ATTRIBUTE_ID,
								  ZCL_INT16U_ATTRIBUTE_TYPE,
								  (uint8_t* )&payload_struct->on_time,
								  0x0000);

	app_v2_device_report_attr_mfg(g_report_target_node,	
								  endpoint, 
								  g_report_target_ep, 
								  ZCL_ON_OFF_CLUSTER_ID, 
								  ZCL_OFF_WAIT_TIME_ATTRIBUTE_ID,
								  ZCL_INT16U_ATTRIBUTE_TYPE,
								  (uint8_t* )&payload_struct->off_wait_time,
								  0x0000);
	return false;
}

static bool user_identify_cmd_handler(uint8_t trigger_type,
											  EmberAfClusterCommand* cmd,
											  uint8_t* default_resp_status,
											  uint8_t*  command_payload,
											  uint16_t command_length,
											  void* cmd_payload_struct)
{
	zcl_identify_cluster_identify_command_t* payload_struct = 
			(zcl_identify_cluster_identify_command_t* )cmd_payload_struct;

	(void)payload_struct;
	
	return false;
}



extern uint16_t stack_get_zcl_data_length_by_type(uint8_t type, uint8_t* data);

static bool user_basic_cmd_read_handler(uint8_t trigger_type,
									    EmberAfClusterCommand* cmd,
									    uint8_t* default_resp_status,
									    uint8_t*  command_payload,
									    uint16_t command_length,
									    void* cmd_payload_struct);

static bool user_basic_cmd_write_handler(uint8_t trigger_type,
										 EmberAfClusterCommand* cmd,
										 uint8_t* default_resp_status,
										 uint8_t*  command_payload,
										 uint16_t command_length,
										 void* cmd_payload_struct);
										 
const app_decode_zcl_cmd_list_t c_zcl_cmd_list[] = 
{
	ZCL_READ_ATTRIBUTE_CLIENT_COMMAND_DESC(0xff, 0xF000, user_basic_cmd_read_handler),
	ZCL_WRITE_ATTRIBUTE_CLIENT_COMMAND_DESC(0xff, 0xF000, user_basic_cmd_write_handler),
};

static bool user_basic_cmd_read_handler(uint8_t trigger_type,
									    EmberAfClusterCommand* cmd,
									    uint8_t* default_resp_status,
									    uint8_t*  command_payload,
									    uint16_t command_length,
									    void* cmd_payload_struct)
{
	debugPortAll("\r\n[USER READ]%a", command_payload, command_length);

//single attribute handler
	uint16_t attribute_id = build_int16u(false, command_payload);
	
	debugPortAll(", attr 0x%2x", attribute_id);
	
	if(attribute_id == 0x0300)
	{
		uint8_t attr_value = 0x01;
	
		app_v2_send_zcl_read_response(cmd->source, 
									  cmd->apsFrame->destinationEndpoint,
							   		  cmd->apsFrame->sourceEndpoint,
							   		  cmd->apsFrame->clusterId,
	                                  cmd->mfgCode, 
	                                  attribute_id, 
	                                  ZCL_INT8U_ATTRIBUTE_TYPE, 
	                                  EMBER_ZCL_STATUS_SUCCESS, 
	                                  &attr_value,
	                                  cmd->seqNum);
	                                  
	    return true;
	}

	return false;
	
//Multi attribute handler
/*
	uint8_t resp_buffer[78];
	uint8_t resp_index = 0;
	
	for(uint16_t i = 0; i < command_length; i += 2)
	{
		uint16_t attribute_id = build_int16u(false, command_payload[i]);

		if(attribute_id == 0x0000)
		{
			uint8_t attr_value = 0x01;
		
			uint8_t data_size = stack_get_zcl_data_length_by_type(ZCL_INT8U_ATTRIBUTE_TYPE, &attr_value);
			
			if((resp_index + (data_size + 4)) >= sizeof(resp_buffer))
			{
				break;
			}
			
			resp_buffer[resp_index++] = command_payload[i];
			resp_buffer[resp_index++] = command_payload[i + 1];
		
			resp_buffer[resp_index++] = EMBER_ZCL_STATUS_SUCCESS;
			resp_buffer[resp_index++] = ZCL_INT8U_ATTRIBUTE_TYPE;

			MEMCOPY(&resp_buffer[resp_index], (uint8_t* )&attr_value, data_size);
			resp_index += data_size;
		}
	}
	
	if(resp_index)
	{
		app_v2_send_zcl_message(cmd->apsFrame->profileId, 
								cmd->source,
								0, 
								cmd->apsFrame->destinationEndpoint,
						   		cmd->apsFrame->sourceEndpoint,
						   		cmd->apsFrame->clusterId, 
						   		ZCL_FRAME_CONTROL_SERVER_TO_CLIENT | ZCL_DISABLE_DEFAULT_RESPONSE_MASK,
						   		cmd->mfgCode, 
								ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID
		                        resp_index, resp_buffer, 
		                        app_get_zcl_message_default_option(),
		                        0,
		                        cmd->seqNum);
	                        
	     return true;
	}
	
	return false;
*/	
}

static bool user_basic_cmd_write_handler(uint8_t trigger_type,
										 EmberAfClusterCommand* cmd,
										 uint8_t* default_resp_status,
										 uint8_t*  command_payload,
										 uint16_t command_length,
										 void* cmd_payload_struct)
{
	debugPortAll("\r\n[USER WRITE]%a", command_payload, command_length);

	uint16_t attribute_id  = build_int16u(false, command_payload);
	
	if(attribute_id == 0x0300)
	{
		uint8_t data_type = command_payload[2];
		
		uint8_t data_size = stack_get_zcl_data_length_by_type(data_type, command_payload + 3);
	
		if(data_size + 3 <= command_length)
		{
			debugPortAll(", attr 0x%2x, type 0x%x, data : %a", attribute_id, data_type, command_payload + 3, data_size);
		}
		
		app_v2_send_zcl_write_response(cmd->source,
									   cmd->apsFrame->destinationEndpoint,
									   cmd->apsFrame->sourceEndpoint,
									   cmd->apsFrame->clusterId, 
									   cmd->mfgCode, 		
                               		   EMBER_ZCL_STATUS_SUCCESS,
                               		   cmd->seqNum);
		
		return true;
	}
	
	return false;
}

void user_zcl_cmd_list_register(void)
{
	app_zcl_cmd_list_register(c_zcl_cmd_list, sizeof(c_zcl_cmd_list) / sizeof(app_decode_zcl_cmd_list_t));
}

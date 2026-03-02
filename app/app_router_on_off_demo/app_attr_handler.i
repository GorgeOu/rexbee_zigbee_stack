

static void user_off_wait_time_attr_handler(uint8_t trigger_type,uint8_t endpoint, uint8_t data_type, uint8_t data_length, uint8_t* data);

const app_attr_desc_t c_app_attr_desc[] = 
{
	ZCL_GLOBAL_SERVER_ATTR_DESC(0xFF, ZCL_ON_OFF_CLUSTER_ID, 		ZCL_OFF_WAIT_TIME_ATTRIBUTE_ID, 	NULL, user_off_wait_time_attr_handler),
};

void user_zcl_attr_list_register(void)
{
	app_zcl_attr_list_register(c_app_attr_desc, sizeof(c_app_attr_desc)/sizeof(app_attr_desc_t));
}

static void user_off_wait_time_attr_handler(uint8_t  trigger_type,
										  uint8_t  endpoint,
										  uint8_t  data_type,
										  uint8_t  data_length,
										  uint8_t* data)
{
	if (data_length != 2)
	{
		return;
	}

	app_v2_device_report_attr_mfg(	g_report_target_node,	
									endpoint, 
									g_report_target_ep, 
									ZCL_ON_OFF_CLUSTER_ID, 
									ZCL_OFF_WAIT_TIME_ATTRIBUTE_ID,
									ZCL_INT16U_ATTRIBUTE_TYPE,
									data,
									0x0000 );
}
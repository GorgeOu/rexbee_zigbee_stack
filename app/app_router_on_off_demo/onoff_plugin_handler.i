
void app_zero_cross_detect_trigger_callback(bool on_off)
{
    for(uint8_t i = 0; i < FIXED_ENDPOINT_COUNTS; i++)
    {
        if(g_local_user_device_status[i].control_action != CONTROL_ACTION_END)
        {
            uint8_t action = on_off ? CONTROL_ACTION_ON : CONTROL_ACTION_OFF;

            if(action == g_local_user_device_status[i].control_action)
            {
                if(action == CONTROL_ACTION_ON)
                {
                    app_control_pin_action(g_local_user_device_status[i].relay_id,  CONTROL_ACTION_ON);
                    app_control_pin_action(g_local_user_device_status[i].led_id,    CONTROL_ACTION_OFF);
                }
                else
                {
                    app_control_pin_action(g_local_user_device_status[i].relay_id,  CONTROL_ACTION_OFF);
                    app_control_pin_action(g_local_user_device_status[i].led_id,    CONTROL_ACTION_ON);
                }

                g_local_user_device_status[i].control_action = CONTROL_ACTION_END;
            }
        }
    }
}

bool user_onoff_plugin_onoff_status_callback(uint8_t trigger_type,
						  	  	  	  	  	 uint8_t endpoint,
						  	  	  	  	  	 bool last_onoff_status,
						  	  	  	  	  	 bool current_onoff_status,
						  	  	  	  	  	 uint8_t effect_id,
						  	  	  	  	  	 uint8_t effect_var,
						  	  	  	  	  	 uint32_t transition_time)
{
	debugPortAll("\r\n[PLUGIN]On off status changed, type 0x%x, ep 0x%x, status 0x%x -> 0x%x",
				  trigger_type, endpoint, last_onoff_status, current_onoff_status);

    if(endpoint > FIXED_ENDPOINT_COUNTS || endpoint == 0)
    {
        return false;
    }

	g_local_user_device_status[endpoint - 1].control_action = current_onoff_status ? CONTROL_ACTION_ON : CONTROL_ACTION_OFF;

    g_token_def->onoff_state[endpoint - 1] = current_onoff_status;
    app_set_global_token_data((uint8_t* )g_token_def);

    app_v2_device_report_attr_mfg(g_report_target_node, endpoint, g_report_target_ep, ZCL_ON_OFF_CLUSTER_ID,
                                  ZCL_ON_OFF_ATTRIBUTE_ID, ZCL_BOOLEAN_ATTRIBUTE_TYPE, (uint8_t* )&current_onoff_status, 0x0000);

	#ifdef ZERO_CROSS_DETECT_ENABLE
    app_enabled_single_pass_zero_cross_detect();
	#else
	app_zero_cross_detect_trigger_callback(current_onoff_status);
	#endif

	return true;
}

void user_onoff_plugin_register(void)
{
	app_onoff_plugin_v2_register(false, 100, user_onoff_plugin_onoff_status_callback, NULL);											//on off plugin注册，可选，用于自动解析处理on off cluster的相关命令

	#ifdef ZERO_CROSS_DETECT_ENABLE
    app_zero_cross_detect_register(ZERO_CROSS_DETECT_PIN, (6000), (7000), (25000), false);           //过零检测注册,注册过零检测引脚,闭合继电器的延时时间为6ms,断开继电器的延时时间为7ms,过零检测超时时间为25ms
	#endif
}
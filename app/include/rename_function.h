#ifndef __RENAME_FUNCTION_SDK_H__
#define __RENAME_FUNCTION_SDK_H__

#define aucFirmware_Ver											c_firmware_ver									
#define aucModelid												c_model_id
#define aucApp_Global_Token_Data								g_app_global_token_data

#define UART_BUFFER												uart_buffer_t
#define HAL_FIXED_GPIO_LIST										hal_fixed_gpio_list_t
#define HAL_FIXED_GPIO_EXT_CFG_LIST								hal_fixed_gpio_ext_cfg_list_t
#define E_TRIGGER_MODE											trigger_mode_enum_t
#define HAL_GPIO_CONFIG_LIST									hal_gpio_config_list_t
#define	HAL_PWM_GPIO_CONFIG_LIST								hal_pwm_gpio_config_list_t
#define E_SERIAL_TYPE											app_serial_type_enum_t
#define E_UART_PARITY_TYPE										app_uart_parity_type_enum_t
#define	E_UART_RATE												app_uart_rate_enum_t	
#define StackZigbeeCommandType									stack_zigbee_command_type_enum_t

#define sHal_Fixed_Gpio_List									g_hal_fixed_gpio_list
#define sHal_Fixed_Gpio_Ext_Cfg_List							g_hal_fixed_gpio_ext_cfg_list
#define sHal_Button_Pin_List									g_hal_button_pin_list
#define sHal_Contact_Pin_List									g_hal_contact_pin_list
#define sHal_Control_Pin_List									g_hal_control_pin_list

#define uiHal_Fixed_Gpio_List_Size								g_hal_fixed_gpio_list_size
#define uiHal_Fixed_Gpio_Ext_Cfg_List_Size						g_hal_fixed_gpio_ext_cfg_list_size
#define ucHal_Button_Pin_List_Counts							g_hal_button_pin_list_counts
#define ucHal_Contact_Pin_List_Counts							g_hal_contact_pin_list_counts
#define ucHal_Control_Pin_List_Counts							g_hal_control_pin_list_counts

#define ucHal_Gpio_Max_Counts									g_hal_gpio_max_counts
#define ucFixed_Endpoint_Count									g_fixed_endpoint_count
#define uiRex_OTA_Image_Type									g_rex_ota_image_type
#define scRadio_Tx_Power_Config									g_radio_tx_power_config
#define ucApp_Support_Ias_Zone									g_app_support_ias_zone
#define uiDevice_Config_Zone_Type								g_device_config_zone_type

#define	uiReport_Target_Node									g_report_target_node
#define	ucReport_Target_EP										g_report_target_ep

#define sApp_Led_Task											g_app_led_task									


/*
*  io.a
*/
#define App_IO_Init												app_io_init										
#define App_IO_Tick												app_io_tick	
#define App_Control_On											app_control_on									
#define App_Control_Off											app_control_off									
#define App_Control_Toggle										app_control_toggle								
#define App_IO_Press_Callback									app_io_press_callback							
#define App_IO_Release_Callback									app_io_release_callback							
#define App_Sensor_IO_Init										app_sensor_io_init								
#define App_Control_Init										app_control_init
#define Sensor_Filter_Handler									app_sensor_filter_handler	
#define App_Zone_Sensor_Trigger_Callback						app_zone_sensor_trigger_callback				
#define App_Zone_Sensor_Release_Callback						app_zone_sensor_release_callback

#define App_Set_Manufacture_Id									app_set_manufacture_id
#define App_Get_Manufacture_Id									app_get_manufacture_id

#define App_Flash_Area_Erase									app_flash_area_erase

#define Safe_Virtual_Delay_Milli_Seconds						app_safe_virtual_delay_milli_seconds

#define Safe_Erase_User_Data_Area								app_safe_erase_user_data_area

#define App_Print_Attribute_Table								app_print_attribute_table

#define App_Event_Register										app_event_register								
#define App_Event_Cancel										app_event_cancel

#define App_Event_V2_Register									app_event_v2_register
#define App_Event_V2_Cancel										app_event_v2_cancel
#define App_Event_V2_Is_Active									app_event_v2_is_active


#define I2C_IO_Configuration									app_io_configuration
#define I2C_Write_Interface										app_i2c_write_interface			
#define I2C_Write_Read_Interface								app_i2c_write_read_interface			
#define I2C_Read_Interface										app_i2c_read_interface			

#define App_Device_Endpoint_Descriptor_Init						app_device_endpoint_descriptor_init
#define App_Measure_Battery_Value								app_measure_battery_value						
#define App_Send_Zone_Status_Change								app_send_zone_status_change						
#define App_Report_Random_Init									app_report_random_init							
#define Device_Reporting_Cfg									app_device_reporting_cfg						

#define App_General_Pre_Hal_Config								app_general_pre_hal_config						
#define App_Pre_Hal_Config										app_pre_hal_config								
#define App_Hal_Uart_Config										app_hal_uart_config			
#define App_Main_Init_Callback									app_main_init_callback
#define App_Main_Tick_Callback									app_main_tick_callback							
#define App_Second_Tick_Callback								app_second_tick_callback						
#define APP_Message_Sent_Callback								app_message_sent_callback

#define Device_Fresh_Start_Callback								app_device_fresh_start_callback					
#define Leave_Network_Detected_Callback							app_leave_network_detected_callback	
#define App_Reset_Factory_New_Handler							app_reset_factory_new_handler					

#define emberAfColorControlClusterServerCommandParse			app_color_control_cluster_server_command_parse	
#define emberAfLevelControlClusterServerCommandParse			app_level_control_cluster_server_command_parse	
#define emberAfOnOffClusterServerCommandParse					app_on_off_cluster_server_command_parse		

#define Clear_Scene_Selector_Info_Table_With_Group				app_clear_scene_selector_info_table_with_group
#define Clear_Scene_Selector_Info_Table							app_clear_scene_selector_info_table
#define Get_Scene_Info_By_Key_Id								app_get_scene_info_by_key_id
#define App_Pre_Scene_Selector_Command_Handler					app_pre_scene_selector_command_handler


#define Rex_Vain_Network_Enable									app_rex_vain_network_enable
#define	Is_Rex_Vain_Network_UnderWay							app_is_rex_vain_network_underway

#define Stack_Leave_Network										app_leave_network
#define Stack_Network_State										app_get_network_state

#define App_Command_Line_Enable									app_command_line_enable
#define App_Set_Zcl_Message_Default_Option						app_set_zcl_message_default_option
#define App_Poll_Server_Parameter_Init							app_poll_server_parameter_init
#define App_Version_Printf										app_version_printf

#define App_Process_UART_Data									app_process_uart_data							
#define App_UART_Frame_Check									app_uart_frame_check							
#define App_Pre_ZDO_Handler										app_pre_zdo_handler								
#define App_Pre_ZDO_Bind_Command_Handler						app_pre_zdo_bind_command_handler				
#define App_Pre_Command_Handler									app_pre_command_handler							
#define App_Post_Attr_Change_Handler							app_post_attr_change_handler					
#define App_Stack_Status_Callback								app_stack_status_callback						
#define Extern_Process_AT_CMD									app_extern_process_at_cmd									
#define App_Get_Token_Data_To_Ram_Callback						app_get_token_data_to_ram_callback				
#define Rex_System_Reset_Indicate								app_rex_system_reset_indicate					
#define App_Cluster_Specific_C2S_Command_Parse					app_cluster_specific_c2s_command_parse			
#define App_Plugin_Init_Callback								app_plugin_init_callback						
#define App_Plugin_Stack_Status_Function_Callback				app_plugin_stack_status_function_callback		
#define App_Poll_Complete_Callback								app_poll_complete_callback						
#define App_Sleep_Wakeup_Callback								app_sleep_wakeup_callback						
#define App_Ok_To_Sleep_Callback								app_ok_to_sleep_callback						
#define Reboot_Move_Network_Indicate							app_reboot_move_network_indicate				
#define Reboot_Move_Network_Exit_Callback						app_reboot_move_network_exit_callback			
#define Reboot_Move_Network_Timeout_Callback					app_reboot_move_network_timeout_callback		
#define Device_Battery_Monitor_Callback							app_device_battery_monitor_callback				
#define Write_Battery_Power_Attribute_Voltage					app_write_battery_power_attribute_voltage		
#define App_Battery_Init_Callback								app_battery_init_callback						
#define App_Network_Init_Callback								app_network_init_callback						
#define App_Keep_Wakeup_Ext_Trigger_Callback					app_keep_wakeup_ext_trigger_callback			
#define App_Identify_Start_Handler								app_identify_start_handler						
#define App_Identify_Stop_Handler								app_identify_stop_handler						
#define App_Device_Endpoint_Descriptor_Init						app_device_endpoint_descriptor_init				
#define App_Ota_Start_Notification								app_ota_start_notification						
#define App_Ota_In_Progress_Indicate							app_ota_in_progress_indicate					
#define App_Ota_Recevie_Finished_Notification					app_ota_recevie_finished_notification			
#define App_Ota_Reboot_Upgrade_Firmware_Notification			app_ota_reboot_upgrade_firmware_notification	
#define App_Ota_Single_Request_Timeout_Callback					app_ota_single_request_timeout_callback			
#define Rex_Vain_Network_Joined_Callback						app_rex_vain_network_joined_callback			
#define App_Pre_Message_Handler									app_pre_message_handler							
#define App_Detect_Invalid_Rexense_Signature_Indicate			app_detect_invalid_rexense_signature_indicate	
#define App_Detect_Invalid_Rexense_Signature_Callback			app_detect_invalid_rexense_signature_callback	
#define App_External_Mcu_Ota_Notify_Callback					app_external_mcu_ota_notify_callback			
#define App_External_Mcu_Next_Image_Response_Callback			app_external_mcu_next_image_response_callback	
#define App_External_Mcu_Image_Block_Response_Callback			app_external_mcu_image_block_response_callback	
#define App_Ota_Upgrade_Abort_Callback							app_ota_upgrade_abort_callback					
#define App_Ota_Upgrade_Wait_For_Data_Callback					app_ota_upgrade_wait_for_data_callback			

#define App_Device_Rejoin_Successful_Callback					app_device_rejoin_successful_callback			
#define App_Pre_Recovery_Network_Callback						app_pre_recovery_network_callback				
#define App_Led_Task_Handler									app_led_task_handler							
#define App_Poll_Schedule_End_Callback							app_poll_schedule_end_callback					
																
#define Move_To_Color_Start_Callback							app_move_to_color_start_callback				
#define Move_To_Color_Finish_Callback							app_move_to_color_finish_callback				
//#define app_system_time System_Time ------ defined in global_common.h																			

#define Move_To_Level_Finish_Callback							app_move_to_level_finish_callback				
#define Move_To_Level_Start_Callback							app_move_to_level_start_callback	

#define App_Process_UART_Data									app_process_uart_data							

#define app_serial_type_enum_t									E_SERIAL_TYPE																				
#define app_uart_parity_type_enum_t								E_UART_PARITY_TYPE
#define	attibute_data_t											AttributeData				

#define App_Serial_Init											app_serial_init									
#define App_Serial_Printf										app_serial_printf								

#define App_Debug_Printf										app_debug_printf								
#define App_Secondary_Serial_Printf								app_secondary_serial_printf
#define App_Virtual_Serial_Printf								app_virtual_serial_printf
#define App_Debug_Printf										app_debug_printf								
#define App_Secondary_Debug_Printf								app_secondary_debug_printf
#define App_Serial_Bytes_Printf									app_serial_bytes_printf
#define App_Secondary_Serial_Bytes_Printf						app_secondary_serial_bytes_printf
#define App_Serial_Bytes_Printf									app_serial_bytes_printf
#define App_Debug_Bytes_Printf									app_debug_bytes_printf							
#define App_Secondary_Debug_Bytes_Printf						app_secondary_debug_bytes_printf				
#define App_Virtual_Serial_Bytes_Printf							app_virtual_serial_bytes_printf

#define	App_Serial_Send_Hex_Data								app_serial_send_hex_data
#define App_Secondary_Serial_Send_Hex_Data						app_secondary_serial_send_hex_data
#define	App_Virtual_Serial_Send_Hex_Data						app_virtual_serial_send_hex_data

#define App_Incoming_Command_Handler							app_incoming_command_handler					

#define Is_Global_Token_Data_Used								app_is_global_token_data_used					
#define Set_App_Global_Token_Data								app_set_global_token_data		
#define Get_App_Global_Token_Data								app_get_global_token_data

#define App_Scan_Network_Process_Timeout						app_scan_network_process_timeout				

#define App_Scan_Network_Config									app_scan_network_config
#define App_Scan_Network_V2_Start								app_scan_network_v2_start
#define App_Scan_Network_V2_Stop								app_scan_network_v2_stop
#define App_Scan_Network_V2_Processor							app_scan_network_v2_processor
#define App_Scan_Network_V2_Info_Print							app_scan_network_v2_info_print
#define App_Is_Scan_Network_V2_Underway							app_is_scan_network_v2_underway

#define Scan_Network_Process_Init_Callback						app_scan_network_process_init_callback			
#define Scan_Network_Process_Indicate							app_scan_network_process_indicate				
#define Scan_Network_Process_Joined_Callback					app_scan_network_process_joined_callback		
#define Scan_Network_Process_Timeout_Callback					app_scan_network_process_timeout_callback		
 
#define Find_Binding											app_find_binding
#define Sync_Bind_Member_Status									app_sync_bind_member_status

#define Device_Report_Attr_MFG									app_device_report_attr_mfg						
#define Device_Report_Multi_Attr_MFG							app_device_report_multi_attr_mfg

#define Send_ZCL_MFG											app_send_zcl_mfg
#define Send_ZDO_Msg											app_send_zdo_msg

#define Send_ZDO_Msg_Hops										app_send_zdo_msg_hops

#define Rex_Send_Zone_Status_Change_Notification				app_rex_send_zone_status_change_notification
#define ZoneDeviceWriteServerAttributeWithCheckRestoreReports   app_zone_device_write_server_attribute_with_check_restore_reports

#define	Get_Network_Up_Report_Enable							app_get_network_up_report_enable

#define App_Ota_Status_Control_Stop								app_ota_status_control_stop
#define Set_Ext_Mcu_Image_Type									app_set_external_mcu_image_type
#define Get_Ext_Mcu_Image_Type									app_get_external_mcu_image_type

#define Hal_App_Gpio_Config										app_hal_gpio_config
#define Hal_Gpio_INT_Callback_Register							app_hal_gpio_int_callback_register
#define Hal_Gpio_INT_Config										app_hal_gpio_int_config
#define Hal_App_Gpio_Read										app_hal_gpio_read
#define Hal_App_SWD_Interface_Enable							app_hal_swd_interface_enable
#define Hal_App_Gpio_Toggle										app_hal_gpio_toggle
#define Hal_App_Gpio_Set										app_hal_gpio_set
#define Hal_App_Gpio_Clear										app_hal_gpio_clear


#define app_event_callback_t									appEventCallback	
#define Set_Reset_Seed											app_set_reset_seed

#define App_Read_Server_Attribute								app_read_server_attribute
#define App_Write_Server_Attribute								app_write_server_attribute
/*
* end device
*/
#define App_Set_Poll_Interval									app_set_poll_interval
#define App_Get_Poll_Interval									app_get_poll_interval
#define App_Poll_For_Data										app_poll_for_data

#define App_Set_Poll_Schedule									app_set_poll_schedule
#define App_Get_Poll_Schedule									app_get_poll_schedule
#define App_Delete_Poll_Schedule								app_delete_poll_schedule
#define App_Device_Set_Connective_Timeout						app_device_set_connective_timeout
#define App_Device_Get_Connective_Timeout						app_device_get_connective_timeout										
#define App_Recovery_Network_Control							app_recovery_network_control
	
#endif

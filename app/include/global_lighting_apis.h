#ifndef __GLOBAL_LIGNTING_APIS_H__
#define __GLOBAL_LIGNTING_APIS_H__

//COMMON
void app_build_fast_server_attribute_init(uint8_t endpoint);

void app_color_plugin_set_rgb_limit_enable(bool enable);

//USE app_color_plugin_set_calibration_paramter or app_color_plugin_set_v2_calibration_paramter
void app_color_plugin_set_calibration_paramter(uint16_t r_white_balance,
										  	   uint16_t g_white_balance,
										  	   uint16_t b_white_balance,
										  	   const uint16_t* r_gamma_curve,
										  	   const uint16_t* g_gamma_curve,
										  	   const uint16_t* b_gamma_curve);

void app_color_plugin_set_v2_calibration_paramter(const uint16_t* r_white_balance_table,
												  const uint16_t* g_white_balance_table,
												  const uint16_t* b_white_balance_table,
												  const uint16_t* r_gamma_curve,
												  const uint16_t* g_gamma_curve,
												  const uint16_t* b_gamma_curve);

void app_color_plugin_dimmer_init(uint32_t gradual_time_ms,
								  uint8_t color_mode,
								  bool onoff,
								  uint16_t x,
								  uint16_t y,
								  uint16_t mireds,
								  uint16_t enhanced_hue,
								  uint8_t saturation,
								  uint8_t level,
								  uint8_t on_level);

void app_onoff_pwm_task(bool onoff, uint32_t transition_time);

void app_level_pwm_task(uint8_t level, uint32_t transition_time);
bool app_stop_level_pwm_task(void);

void app_hsv_pwm_task(bool up_down,
					  uint16_t enhanced_hue,
					  uint8_t saturation,
					  uint32_t transition_hue_time,
					  uint32_t transition_sat_time);
bool app_stop_hsv_pwm_task(void);

void app_xy_pwm_task(uint16_t x,
					 uint16_t y,
					 uint32_t transition_x_time,
					 uint32_t transition_y_time);
bool app_stop_xy_pwm_task(void);

void app_temperature_pwm_task(uint16_t mireds, uint32_t transition_time);
bool app_stop_temp_pwm_task(void);

//CW Light
void app_color_plugin_cw_hal_setting_init(uint16_t pwm_freq,
										  uint8_t c_index,
										  uint8_t w_index,
										  uint16_t min_mireds,
										  uint16_t max_mireds,
										  const uint16_t* level_percentage_curve);
void app_cw_pwm_driver(uint16_t c, uint16_t w);

//CCT Light
void app_color_plugin_cct_hal_setting_init(uint16_t pwm_freq,
										   uint8_t l_index,
										   uint8_t w_index,
										   bool cold,
										   uint16_t min_mireds,
										   uint16_t max_mireds,
										   const uint16_t* level_percentage_curve);
void app_cct_pwm_driver(uint16_t l, uint16_t w);

//RGBCCT Light
void app_color_plugin_rgbcct_hal_setting_init(uint16_t pwm_freq,
											  uint8_t r_index,
											  uint8_t g_index,
											  uint8_t b_index,
											  uint8_t l_index,
											  uint8_t w_index,
											  bool cold,
											  uint16_t min_mireds,
											  uint16_t max_mireds,
											  const uint16_t* level_percentage_curve);
void app_rgbcct_pwm_driver(uint16_t r, uint16_t g, uint16_t b, uint16_t l, uint16_t w);

//RGBCW Light
void app_color_plugin_rgbcw_hal_setting_init(uint16_t pwm_freq,
											 uint8_t r_index,
											 uint8_t g_index,
											 uint8_t b_index,
											 uint8_t c_index,
											 uint8_t w_index,
											 uint16_t min_mireds,
											 uint16_t max_mireds,
											 const uint16_t* level_percentage_curve);
void app_rgbcw_pwm_driver(uint16_t r, uint16_t g, uint16_t b, uint16_t c, uint16_t w);

//RGBW Light
void app_color_plugin_rgbw_hal_setting_init(uint16_t pwm_freq,
										    uint8_t r_index,
										    uint8_t g_index,
										    uint8_t b_index,
										    uint8_t w_index,
										    uint16_t min_mireds,
										    uint16_t max_mireds,
										    const uint16_t* level_percentage_curve);
void app_rgbw_pwm_driver(uint16_t r, uint16_t g, uint16_t b, uint16_t w);

#endif


#ifndef __SIM_WIN_PANEL_H__
#define __SIM_WIN_PANEL_H__

typedef struct
{
    int total_distance;
    int current_distance;
    int movement_speed;
    uint32_t action_time_ms;
    uint8_t  action;
    uint8_t  event_control_id;
    void (*action_callback)(void *instance, uint8_t action);
} app_sim_win_panel_inst_t;

typedef enum
{
	APP_SIM_WIN_PANEL_ACTION_OPEN 	= 0,
	APP_SIM_WIN_PANEL_ACTION_CLOSE  = 1,
	APP_SIM_WIN_PANEL_ACTION_STOP 	= 2,
} app_sim_win_panel_action_enum_t;

uint16_t app_sim_win_panel_plugin_get_percentage(app_sim_win_panel_inst_t *instance);

void app_sim_win_panel_plugin_set_percentage(app_sim_win_panel_inst_t *instance, uint16_t percentage);

void app_sim_win_panel_plugin_action_start(app_sim_win_panel_inst_t *instance, uint8_t action);

void app_sim_win_panel_plugin_inst_init(app_sim_win_panel_inst_t *instance,
										int total_distance,
										int current_position,
										void (*action_callback)(app_sim_win_panel_inst_t *instance, uint8_t action));

#endif


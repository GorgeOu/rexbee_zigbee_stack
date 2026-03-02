

#ifndef __APP_PIN_DEF_H__
#define __APP_PIN_DEF_H__

#include "../include/global_common.h"

#define HAL_GPIO_INIT \
{\
	{PORTB,	5,	GPIOCFG_IN_PUD, 	1,	GPIOCFG_IN_PUD,		1},		  /* 1  LED */ \
	{PORTC,	2,	GPIOCFG_IN_PUD, 	1,	GPIOCFG_IN_PUD,		1},	 	  /* 2  RESET */ \
	{PORTA,	0,	GPIOCFG_IN, 		0,	GPIOCFG_IN,			0},	 	  /* 3  DOOR SENSOR */ \
	{PORTD,	7,	GPIOCFG_IN, 		0,	GPIOCFG_IN,			0},	 	  /* 4  TAMPER */ \
}

#define HAL_GPIO_EXT_CFG \
{\
	{PORTC,	2,	2,	1,	1,	1, NULL},\
	{PORTA,	0,	0,	1,	1,	1, NULL},\
	{PORTD,	7,	7,	1,	1,	1, NULL},\
	{PORTC,	3,	3,	0,	1,	1, NULL}, /*uart rx pin wakeup config*/\
}

#define DEVICE_RESET_KEY_ID				0
#define DEVICE_RESET_PIN_PRESSED_STATE	LOW_LEVEL_TRIGGER

/*PORT, PIN, TRIGGER(the way of trigger)*/
#define HAL_BUTTON_PIN_LIST \
{\
	{PORTC,	2,	LOW_LEVEL_TRIGGER}, 		  \
}

#define DOOR_SENSOR_DETECT_CONTACT_ID 		0
#define DOOR_SENSOR_TAMPER_CONTACT_ID 		1

#define DOOR_SENSOR_DETECT_OPEN_STATE 		HIGH_LEVEL_TRIGGER
#define DOOR_SENSOR_TEMPER_RELEASE_STATE 	HIGH_LEVEL_TRIGGER

/*PORT, PIN, TRIGGER(the way of trigger)*/
#define HAL_CONTACT_PIN_LIST \
{\
	{PORTA,	0,	DOOR_SENSOR_DETECT_OPEN_STATE},             \
	{PORTD,	7,	DOOR_SENSOR_TEMPER_RELEASE_STATE},          \
}

#define DOOR_SENSOR_LED_ID					0
#define DOOR_SENSOR_LED_ON_STATE 			LOW_LEVEL_TRIGGER

#define HAL_CONTROL_PIN_LIST \
{\
	{PORTB,	5,	DOOR_SENSOR_LED_ON_STATE},    \
}

#endif

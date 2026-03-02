

#ifndef __APP_PIN_DEF_H__
#define __APP_PIN_DEF_H__

#include "../include/global_common.h"

#define DEVICE_RESET_KEY_ID					0
#define DEVICE_RESET_PIN_PRESSED_STATE		LOW_LEVEL_TRIGGER

#define DEVICE_ONOFF_NETWORK_LED_ID		    1
#define DEVICE_ONOFF_NETWORK_LED_STATE  	LOW_LEVEL_TRIGGER

/*PORT, PIN, TRIGGER(the way of trigger)*/
#define HAL_BUTTON_PIN_LIST \
{\
	{PORTA,	0,	DEVICE_RESET_PIN_PRESSED_STATE},    \
}

/*PORT, PIN, TRIGGER(the way of trigger)*/
#define HAL_CONTROL_PIN_LIST \
{\
	{PORTB,	7,	DEVICE_ONOFF_NETWORK_LED_STATE}, 	\
}

#endif

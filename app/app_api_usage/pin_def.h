

#ifndef __APP_PIN_DEF_H__
#define __APP_PIN_DEF_H__

#include "../include/global_common.h"

#define DEVICE_TEST_KEY_ID					0
#define DEVICE_TEST_KEY_PRESSED_STATE		LOW_LEVEL_TRIGGER

#define DEVICE_TEST_KEY2_ID					1
#define DEVICE_TEST_KEY2_PRESSED_STATE		LOW_LEVEL_TRIGGER

#define DEVICE_TEST_LED_ID		   		 	0
#define DEVICE_TEST_LED_STATE  				LOW_LEVEL_TRIGGER

#define DEVICE_TEST_PWM_ID		   		 	0
#define DEVICE_TEST_PWM_STATE  				HIGH_LEVEL_TRIGGER


/*PORT, PIN, TRIGGER(the way of trigger)*/
#define HAL_BUTTON_PIN_LIST \
{\
	{PORTA,	0,	DEVICE_TEST_KEY_PRESSED_STATE},    \
	{PORTA,	1,	DEVICE_TEST_KEY_PRESSED_STATE},    \
}

/*PORT, PIN, TRIGGER(the way of trigger)*/
#define HAL_CONTROL_PIN_LIST \
{\
	{PORTB,	7,	DEVICE_TEST_LED_STATE}, 	\
}

#define HAL_PWM_PIN_LIST \
{\
	{PORTC,  0,  DEVICE_TEST_PWM_STATE,	0xff}, \
}

#endif

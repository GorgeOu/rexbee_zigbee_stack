/**
 * Copyright ? 2019 Zhejiang Raying IoT Technology Co., Ltd.
 * All rights reserved. 
 *
 * File: Common_Implements.c
 * Description: This file implements global device describe data.
 *
 * Author(s): yuxiaoqiang@rexense.com	
 * Data: 2020/02/20
 */
#if defined(RZ_STACK_ZED_DEMO)

#include "../app_common.h"
#include "../pin_def.h"

/* Common hal config
*
*/
#if defined(HAL_GPIO_INIT)
hal_fixed_gpio_list_t g_hal_fixed_gpio_list[] 	 = HAL_GPIO_INIT;
uint16_t 			  g_hal_fixed_gpio_list_size = sizeof(g_hal_fixed_gpio_list);
#else
hal_fixed_gpio_list_t g_hal_fixed_gpio_list[] 	 = {{0}};
uint16_t 			  g_hal_fixed_gpio_list_size = 0;
#endif
#if defined(HAL_GPIO_EXT_CFG)
hal_fixed_gpio_ext_cfg_list_t g_hal_fixed_gpio_ext_cfg_list[]  	 = HAL_GPIO_EXT_CFG;
uint16_t 					  g_hal_fixed_gpio_ext_cfg_list_size = sizeof(g_hal_fixed_gpio_ext_cfg_list);
#else
hal_fixed_gpio_ext_cfg_list_t g_hal_fixed_gpio_ext_cfg_list[]	 = {{0}};
uint16_t 					  g_hal_fixed_gpio_ext_cfg_list_size = 0;
#endif

#if defined(HAL_BUTTON_PIN_LIST)
hal_gpio_config_list_t g_hal_button_pin_list[] 		= HAL_BUTTON_PIN_LIST;
uint8_t  			   g_hal_button_pin_list_counts = sizeof(g_hal_button_pin_list) / sizeof(hal_gpio_config_list_t);
#endif

#if defined(HAL_CONTACT_PIN_LIST)
hal_gpio_config_list_t g_hal_contact_pin_list[] 	 = HAL_CONTACT_PIN_LIST;
uint8_t  			   g_hal_contact_pin_list_counts = sizeof(g_hal_contact_pin_list) / sizeof(hal_gpio_config_list_t);
#endif

#if defined(HAL_CONTROL_PIN_LIST)
hal_gpio_config_list_t  g_hal_control_pin_list[] 	  = HAL_CONTROL_PIN_LIST;
uint8_t  				g_hal_control_pin_list_counts = sizeof(g_hal_control_pin_list) / sizeof(hal_gpio_config_list_t);
#endif

#if defined(HAL_PWM_PIN_LIST)
hal_pwm_gpio_config_list_t g_hal_pwm_pin_list[] 	 = HAL_PWM_PIN_LIST;
uint8_t 				   g_hal_pwm_pin_list_counts = sizeof(g_hal_pwm_pin_list) / sizeof(hal_pwm_gpio_config_list_t);
#endif

uint8_t  g_fixed_endpoint_count  = FIXED_ENDPOINT_COUNTS;

#if defined(FIXED_FAST_JOIN_MAIN_OD) && defined(FIXED_FAST_JOIN_SUB_OD_LIST)
const uint16_t c_rex_fast_join_main_od 		 = FIXED_FAST_JOIN_MAIN_OD;
const uint16_t c_rex_fast_join_sub_od_list[] = FIXED_FAST_JOIN_SUB_OD_LIST;
#endif
//------------------------------------------------------------------------------
// Globals
// This is not declared CONST in order to handle dynamic endpoint information
// retrieved from tokens.
EmberAfDefinedEndpoint emAfEndpoints[FIXED_ENDPOINT_COUNTS];

int8u attributeData[ATTRIBUTE_MAX_SIZE];

int8u singletonAttributeData[ATTRIBUTE_SINGLETONS_SIZE];

// If we have attributes that are more than 2 bytes, then
// we need this data block for the defaults
#ifdef GENERATED_DEFAULTS
const int8u generatedDefaults[]               						=	GENERATED_DEFAULTS;
#endif // GENERATED_DEFAULTS

const EmberAfAttributeMetadata generatedAttributes[] 				= 	GENERATED_ATTRIBUTES;
const EmberAfCluster generatedClusters[]             				=	GENERATED_CLUSTERS;
const EmberAfEndpointType generatedEmberAfEndpointTypes[]   		= 	GENERATED_ENDPOINT_TYPES;

const EmberAfManufacturerCodeEntry clusterManufacturerCodes[] 		= 	GENERATED_CLUSTER_MANUFACTURER_CODES;
const int16u clusterManufacturerCodeCount 							= 	GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT;
const EmberAfManufacturerCodeEntry attributeManufacturerCodes[] 	= 	GENERATED_ATTRIBUTE_MANUFACTURER_CODES;
const int16u attributeManufacturerCodeCount 						= 	GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT;

const int8u fixedEndpoints[]   	  									= FIXED_ENDPOINT_ARRAY;
const int16u fixedProfileIds[] 	  									= FIXED_PROFILE_IDS;
const int16u fixedDeviceIds[]  	  									= FIXED_DEVICE_IDS;
const int8u fixedEmberAfEndpointTypes[] 							= FIXED_ENDPOINT_TYPES;
#if defined(FIXED_NETWORKS)
const int8u fixedNetworks[] 				  						= FIXED_NETWORKS;
#else
const int8u fixedNetworks[FIXED_ENDPOINT_COUNTS] 					= {0};
#endif

#if defined(FIXED_DEVICE_VERSIONS)
const int8u fixedDeviceVersions[] 				      				= FIXED_DEVICE_VERSIONS;
#else
const int8u fixedDeviceVersions[FIXED_ENDPOINT_COUNTS] 		 		= FIXED_DEVICE_VERSIONS;
#endif

#if !defined(APP_REGISTER_CALLBACK_CONFIG)
PhyLayerRegisterCallback appRegisterPhyLayerCallbacks =
{
	.powerManagementEnterSleepCallback = NULL,
};

RexUniversalLibRegisterCallback rexUniversalLibCallbacksRegister =
{
	.appPreHalConfig  			= (void* )NULL,
	.appGetTokenToRam 			= (void* )NULL,
	.appFreshNetworkStart		= (void* )NULL,
	.appLeaveNetworkDetect 		= (void* )NULL,
	.appStackStatusChanged		= (void* )NULL,
	.appResetIndicate			= (void* )NULL,
	.appCertCheckFailedInit		= (void* )NULL,
	.appCertCheckFailedIndicate = (void* )NULL,
	.appMessageSentCallback 	= (void* )NULL,
	.appReceviedPacketHandler 	= (void* )NULL,
};
#endif

#if defined(HAL_USER_CONFIG_PA_ENABLE)

#if defined(HAL_USER_CONFIG_PA_TX_PIN) && defined(HAL_USER_CONFIG_PA_RX_PIN)
const user_hal_pa_config_t c_user_hal_pa_config = {true, HAL_USER_CONFIG_PA_TX_PIN, HAL_USER_CONFIG_PA_RX_PIN};
user_hal_pa_config_t* g_user_pa_config = (user_hal_pa_config_t* )&c_user_hal_pa_config;

#warning "User module pa enable"

#else
#error "user pa tx & rx pin no defined"
#endif

#elif defined(HAL_3TP_PA_ENABLE)

const user_hal_pa_config_t c_user_hal_pa_config = {true, PORTC_PIN(4), PORTB_PIN(4)};
user_hal_pa_config_t* g_user_pa_config = (user_hal_pa_config_t* )&c_user_hal_pa_config;

#warning "Rexense 3TP module pa enable"

#elif defined(HAL_3YP_PA_ENABLE)

const user_hal_pa_config_t c_user_hal_pa_config = {true, PORTC_PIN(4), PORTB_PIN(4)};
user_hal_pa_config_t* g_user_pa_config = (user_hal_pa_config_t* )&c_user_hal_pa_config;

#warning "Rexense 3YPT module pa enable"

#elif defined(HAL_3UP_PA_ENABLE)

const user_hal_pa_config_t c_user_hal_pa_config = {true, PORTC_PIN(4), PORTB_PIN(4)};
user_hal_pa_config_t* g_user_pa_config = (user_hal_pa_config_t* )&c_user_hal_pa_config;

#warning "Rexense 3UPT module pa enable"

#elif defined(HAL_3AP_PA_ENABLE)

const user_hal_pa_config_t c_user_hal_pa_config = {true, PORTC_PIN(0), PORTB_PIN(6)};
user_hal_pa_config_t* g_user_pa_config = (user_hal_pa_config_t* )&c_user_hal_pa_config;

#warning "Rexense 3APT module pa enable"

#elif defined(HAL_3CSP_PA_ENABLE)

const user_hal_pa_config_t c_user_hal_pa_config = {true, PORTC_PIN(0), PORTB_PIN(6)};
user_hal_pa_config_t* g_user_pa_config = (user_hal_pa_config_t* )&c_user_hal_pa_config;

#warning "Rexense 3CSP module pa enable"

#else

user_hal_pa_config_t* g_user_pa_config = NULL;

#endif

#include "../app_sim_eep_assign.h"

#if defined(APP_USE_SIM_EEP)

#define  DEFINEEEPTYPE
#include "app_sim_eep.h"
#undef   DEFINEEEPTYPE

#define	 DEFINEEEPARRAY

#define DEFINEEEPMEMASSIGN
#include "app_sim_eep.h"
#undef DEFINEEEPMEMASSIGN

#define DEFINEEEPDEFCONSTVALUE
#include "app_sim_eep.h"
#include "../app_sim_eep_assign.h"
#undef DEFINEEEPDEFCONSTVALUE

#undef DEFINEEEPARRAY

const eeprom_default_data_t c_app_eeprom_default_data[] =
{
	#define	 DEFINEEEPARRAY
	#define	LOCALDEFCONSTVALUE
	#include "app_sim_eep.h"
	#include "../app_sim_eep_assign.h"
	#undef LOCALDEFCONSTVALUE
	#undef	DEFINEEEPARRAY
};

const eeprom_default_data_t* c_eeprom_default_data = (eeprom_default_data_t* )c_app_eeprom_default_data;
const uint16_t c_eeprom_default_data_counts = sizeof(c_app_eeprom_default_data) / sizeof(c_app_eeprom_default_data[0]);

#else
const eeprom_default_data_t* c_eeprom_default_data = NULL;
const uint16_t c_eeprom_default_data_counts = 0;
#warning "app not use eeprom"
#endif

//#define APP_USE_FRAGMENTATION_PLUGIN
//#define APP_FRAGMENTATION_PLUGIN_MAX_TX_PACKETS		8
//#define APP_FRAGMENTATION_PLUGIN_MAX_RX_PACKETS		8
//#define APP_FRAGMENTATION_PLUGIN_BUFFER_SIZE			600

#if defined(APP_USE_FRAGMENTATION_PLUGIN)

typedef struct
{
	uint16_t        a1;
	uint8_t    		a2;
	uint8_t         a3;
	EmberApsFrame   a4;
	uint8_t*        a5;
	uint16_t        a6;
	uint8_t         a7;
	uint8_t         a8;
	uint8_t         a9;
	uint8_t         a10;
} _fgtx_packet_t;

typedef struct
{
	uint8_t		  	b1;
	uint8_t      	b2;
	uint8_t*      	b3;
	uint16_t   		b4;
	uint8_t       	b5;
	uint8_t       	b6;
	uint16_t      	b7;
	uint8_t       	b8;
	uint8_t       	b9;
	uint8_t       	b10;
	uint8_t       	b11;
	uint8_t       	b12;
	uint8_t		  	b13;
} _fgrx_packet_t;

#define APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE		(APP_FRAGMENTATION_PLUGIN_BUFFER_SIZE + 16)

extern uint8_t _app_fragmentation_plugin_packet_buffer[];

#define align(value) (((value) + 3) & ~0x03)

static uint8_t* s_app_fragment_tx_packets_ptr = (uint8_t *)&_app_fragmentation_plugin_packet_buffer[0];
#define END_APP_FRAGMENT_TX_PACKETS \
		(align(sizeof(_fgtx_packet_t) * APP_FRAGMENTATION_PLUGIN_MAX_TX_PACKETS))

static uint8_t* s_tx_message_buffers_ptr = (uint8_t *)&_app_fragmentation_plugin_packet_buffer[END_APP_FRAGMENT_TX_PACKETS];
#define END_APP_FRAGMENT_TX_BUFFERS \
		(END_APP_FRAGMENT_TX_PACKETS + align(APP_FRAGMENTATION_PLUGIN_MAX_TX_PACKETS * APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE))

static uint8_t* s_app_fragment_rx_packets_ptr = (uint8_t *)&_app_fragmentation_plugin_packet_buffer[END_APP_FRAGMENT_TX_BUFFERS];
#define END_APP_FRAGMENT_RX_PACKETS \
		(END_APP_FRAGMENT_TX_BUFFERS + align(sizeof(_fgrx_packet_t) * APP_FRAGMENTATION_PLUGIN_MAX_RX_PACKETS))

static uint8_t* s_rx_message_buffers_ptr = (uint8_t *)&_app_fragmentation_plugin_packet_buffer[END_APP_FRAGMENT_RX_PACKETS];
#define END_APP_FRAGMENT_RX_BUFFERS \
		(END_APP_FRAGMENT_RX_PACKETS + align(APP_FRAGMENTATION_PLUGIN_MAX_RX_PACKETS * APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE))

static uint8_t* s_aps_resp_buffer_ptr = (uint8_t *)&_app_fragmentation_plugin_packet_buffer[END_APP_FRAGMENT_RX_BUFFERS];
#define END_APP_APS_RESP_BUFFERS \
		(END_APP_FRAGMENT_RX_BUFFERS + align(APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE))

#define END_OF_APP_FRAGMENT_PACKET_BUFFER_SIZE 	END_APP_APS_RESP_BUFFERS

_attribute_warning_use_custom_bss_ uint8_t _app_fragmentation_plugin_packet_buffer[END_OF_APP_FRAGMENT_PACKET_BUFFER_SIZE];

void app_fragment_plugin_register(uint8_t* tx_packets,
								  uint8_t* tx_buffer,
								  uint8_t  tx_buffer_number,
								  uint32_t tx_single_buffer_size,
								  uint8_t* rx_packets,
								  uint8_t* rx_buffer,
								  uint8_t  rx_buffer_number,
								  uint32_t rx_single_buffer_size);

void app_reconfig_aps_response_buffer(uint8_t* buffer, uint16_t max_size);

void app_fragmentation_plugin_config_register(void)
{
	app_fragment_plugin_register((uint8_t* )s_app_fragment_tx_packets_ptr,
								 (uint8_t* )s_tx_message_buffers_ptr,
								 APP_FRAGMENTATION_PLUGIN_MAX_TX_PACKETS,
								 APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE,
								 (uint8_t* )s_app_fragment_rx_packets_ptr,
								 (uint8_t* )s_rx_message_buffers_ptr,
								 APP_FRAGMENTATION_PLUGIN_MAX_RX_PACKETS,
								 APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE);

	app_reconfig_aps_response_buffer(s_aps_resp_buffer_ptr, APP_FRAGMENTATION_PLUGIN_SINGLE_BUFFER_SIZE);
}
#else
void app_fragmentation_plugin_config_register(void)
{

}
#endif

#endif

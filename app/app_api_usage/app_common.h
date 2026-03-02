

#ifndef __GLOBAL_APP_COMMON_H__
#define __GLOBAL_APP_COMMON_H__

#include "../include/global_common.h"

//#define RZ_STACK_OTA_API_USAGE
//#define RZ_STACK_PWM_API_USAGE
//#define RZ_STACK_SIM_I2C_API_USAGE
//#define RZ_STACK_UART_API_USAGE
//#define RZ_STACK_VCOM_API_USAGE
//#define RZ_STACK_FLASH_API_USAGE
//#define RZ_STACK_ZBCK_API_USAGE
//#define RZ_STACK_TAG_API_USAGE
//#define RZ_STACK_MEM_HEAP_API_USAGE
//#define RZ_STACK_EVENT_API_USAGE
//#define RZ_STACK_EASY_TOKEN_API_USAGE
//#define RZ_STACK_TC_LINK_API_USAGE
//#define RZ_STACK_CLI_API_USAGE
//#define RZ_STACK_BUTTON_API_USAGE
//#define RZ_STACK_BUTTON_EV_API_USAGE
//#define RZ_STACK_LED_TASK_API_USAGE
//#define RZ_STACK_NVM_API_USAGE
//#define RZ_STACK_NVM2_API_USAGE
//#define RZ_STACK_NVM3_API_USAGE
#define RZ_STACK_EEPROM_CHECK_API_USAGE
//#define RZ_STACK_FAST_GPIO_API_USAGE
//#define RZ_STACK_GPIO_API_USAGE
//#define RZ_STACK_ZIGBEE_SEND_API_USAGE
//#define RZ_STACK_NWK_MGMT_API_USAGE
//#define RZ_STACK_FAST_POWER_CYCLE_API_USAGE

#define FIXED_ENDPOINT_COUNTS	4

// Generated attributes
#define GENERATED_ATTRIBUTES { \
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x03 } }, /* 0 / Basic / ZCL version*/\
    { 0x0001, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x04 } }, /* 1 / Basic / application version*/\
    { 0x0002, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x64 } }, /* 2 / Basic / stack version*/\
    { 0x0003, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 3 / Basic / hardware version*/\
    { 0x0004, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } }, /* 4 / Basic / manufacturer name*/\
    { 0x0005, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } }, /* 5 / Basic / model identifier*/\
    { 0x0006, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } }, /* 6 / Basic / date code*/\
    { 0x0007, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x01 } }, /* 7 / Basic / power source*/\
    { 0x0014, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, /* 8 / Basic / disable local config*/\
    { 0x4000, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } }, /* 9 / Basic / sw build id*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0001 } }, /* 10 / Basic / cluster revision*/\
    { 0x0000, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 11 / Identify / identify time*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 12 / Identify / cluster revision*/\
    { 0x0000, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 13 / Groups / name support*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 14 / Groups / cluster revision*/\
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 15 / Scenes / scene count*/\
    { 0x0001, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 16 / Scenes / current scene*/\
    { 0x0002, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0000 } }, /* 17 / Scenes / current group*/\
    { 0x0003, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 18 / Scenes / scene valid*/\
    { 0x0004, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (0x00), { (uint8_t*)0x00 } }, /* 19 / Scenes / name support*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 20 / Scenes / cluster revision*/\
    { 0x0000, ZCL_BOOLEAN_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }, /* 21 / On/off / on/off*/\
    { 0x4001, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 22 / On/off / on time*/\
    { 0x4002, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } }, /* 23 / On/off / off wait time*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } }, /* 24 / On/off / cluster revision*/\
  }

// Cluster manufacturer codes
#define GENERATED_CLUSTER_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT (0)

// Attribute manufacturer codes
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODES {      \
{0x00, 0x00} \
  }
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT (0)

// Clusters definitions
#define GENERATED_CLUSTERS { \
    { 0x0000, (EmberAfAttributeMetadata*)&(generatedAttributes[0]), 11, 0, (CLUSTER_MASK_SERVER), NULL, },     \
    { 0x0003, (EmberAfAttributeMetadata*)&(generatedAttributes[11]), 2, 4, (CLUSTER_MASK_SERVER), NULL, },     \
    { 0x0004, (EmberAfAttributeMetadata*)&(generatedAttributes[13]), 2, 3, (CLUSTER_MASK_SERVER), NULL, },     \
    { 0x0005, (EmberAfAttributeMetadata*)&(generatedAttributes[15]), 6, 8, (CLUSTER_MASK_SERVER), NULL, },     \
    { 0x0006, (EmberAfAttributeMetadata*)&(generatedAttributes[21]), 4, 7, (CLUSTER_MASK_SERVER), NULL, },     \
    { 0x0019, (EmberAfAttributeMetadata*)&(generatedAttributes[24]), 0, 0, (CLUSTER_MASK_CLIENT), NULL, },     \
  }

// Endpoint types
#define GENERATED_ENDPOINT_TYPES {        \
    { (EmberAfCluster*)&(generatedClusters[0]), 6, 22 }, \
  }

// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (108)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE 132

// Array of endpoints that are supported
#define FIXED_ENDPOINT_ARRAY { 1, 2, 3, 4 }

// Array of profile ids
#define FIXED_PROFILE_IDS { 260, 260, 260, 260 }

// Array of device ids
#define FIXED_DEVICE_IDS { 256, 256, 256, 256 }

// Array of device versions
#define FIXED_DEVICE_VERSIONS { 0, 0, 0, 0 }

// Array of endpoint types supported on each endpoint
#define FIXED_ENDPOINT_TYPES { 0, 0, 0, 0 }

// Array of networks supported on each endpoint
#define FIXED_NETWORKS { 0, 0, 0, 0 }

#endif

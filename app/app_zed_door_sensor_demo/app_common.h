

#ifndef __GLOBAL_APP_COMMON_H__
#define __GLOBAL_APP_COMMON_H__

#include "../include/global_common.h"

#define FIXED_ENDPOINT_COUNTS 	(1)

// Generated attributes
#define GENERATED_ATTRIBUTES { \
    { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x03 } },                                                    /* 0 / Basic / ZCL version*/\
    { 0x0001, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x04 } },                                                    /* 1 / Basic / application version*/\
    { 0x0002, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x64 } },                                                    /* 2 / Basic / stack version*/\
    { 0x0003, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } },                                                    /* 3 / Basic / hardware version*/\
    { 0x0004, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } },                          					/* 4 / Basic / manufacturer name*/\
    { 0x0005, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 33, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } },                         					/* 5 / Basic / model identifier*/\
    { 0x0006, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } },                         					/* 6 / Basic / date code*/\
    { 0x0007, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x03 } },                                                    /* 7 / Basic / power source*/\
    { 0x0014, ZCL_BITMAP8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_TOKENIZE|ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } },  /* 8 / Basic / disable local config*/\
    { 0x4000, ZCL_CHAR_STRING_ATTRIBUTE_TYPE, 17, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)NULL } },                         					/* 9 / Basic / sw build id*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0001 } },                                                 /* 10 / Basic / cluster revision*/\
    { 0x0020, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00UL } },                                                  /* 11 / Power Configuration / battery voltage*/\
    { 0x0021, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } },                                                    /* 12 / Power Configuration / battery percentage remaining*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } },                                                                     /* 13 / Power Configuration / cluster revision*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_CLIENT), { (uint8_t*)0x0001 } },                                                    /* 14 / Identify / cluster revision*/\
    { 0x0000, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0000 } },                                                  /* 15 / Identify / identify time*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } },                                                                     /* 16 / Identify / cluster revision*/\
	{ 0x0000, ZCL_INT32U_ATTRIBUTE_TYPE, 4, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)NULL } },                               						/* 16 / Poll Control / check-in interval*/\
    { 0x0001, ZCL_INT32U_ATTRIBUTE_TYPE, 4, (0x00), { (uint8_t*)NULL } },                                                  						/* 17 / Poll Control / long poll interval*/\
    { 0x0002, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0002 } },                                                                     /* 19 / Poll Control / short poll interval*/\
    { 0x0003, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_WRITABLE), { (uint8_t*)0x0028 } },                                                  /* 20 / Poll Control / fast poll timeout*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } },                                                                     /* 21 / Poll Control / cluster revision*/\
    { 0x0000, ZCL_ENUM8_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } },                                                     /* 22 / IAS Zone / zone state*/\
    { 0x0001, ZCL_ENUM16_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0015 } },                                                    					/* 23 / IAS Zone / zone type*/\
    { 0x0002, ZCL_BITMAP16_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0000 } },                                                                   /* 24 / IAS Zone / zone status*/\
    { 0x0010, ZCL_IEEE_ADDRESS_ATTRIBUTE_TYPE, 8, (ATTRIBUTE_MASK_WRITABLE|ATTRIBUTE_MASK_TOKENIZE), { NULL } },                                /* 25 / IAS Zone / IAS CIE address*/\
    { 0x0011, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0xff } },                                                     /* 26 / IAS Zone / Zone ID*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (0x00), { (uint8_t*)0x0001 } },                                                                     /* 27 / IAS Zone / cluster revision*/\
	{ 0x0000, ZCL_IEEE_ADDRESS_ATTRIBUTE_TYPE, 8, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, 		                                                /* 28 / Over the Air Bootloading / OTA Upgrade Server ID*/\
    { 0x0001, ZCL_INT32U_ATTRIBUTE_TYPE, 4, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, 				                                            /* 29 / Over the Air Bootloading / Offset (address) into the file*/\
    { 0x0002, ZCL_INT32U_ATTRIBUTE_TYPE, 4, (ATTRIBUTE_MASK_SINGLETON), { NULL } },					                                            /* 30 / Over the Air Bootloading / OTA Current File Version*/\
    { 0x0004, ZCL_INT32U_ATTRIBUTE_TYPE, 4, (ATTRIBUTE_MASK_SINGLETON), { NULL } },					                                            /* 31 / Over the Air Bootloading / OTA Downloaded File Version*/\
    { 0x0006, ZCL_ENUM8_ATTRIBUTE_TYPE,  1, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x00 } }, 		                                            /* 32 / Over the Air Bootloading / OTA Upgrade Status*/\
    { 0x0007, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x1163 } }, 	                                            /* 33 / Over the Air Bootloading / Manufacturer ID*/\
    { 0x0008, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0001 } }, 	                                            /* 34 / Over the Air Bootloading / Image Type ID*/\
    { 0x0009, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0000UL } }, 	                                            /* 35 / Over the Air Bootloading / Minimum Block Request Period*/\
    { 0x000A, ZCL_INT32U_ATTRIBUTE_TYPE, 4, (ATTRIBUTE_MASK_SINGLETON), { NULL } }, 				                                            /* 36 / Over the Air Bootloading / Image Stamp*/\
    { 0xFFFD, ZCL_INT16U_ATTRIBUTE_TYPE, 2, (ATTRIBUTE_MASK_SINGLETON), { (uint8_t*)0x0001 } }, 	                                            /* 37 / Over the Air Bootloading / cluster revision*/\
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
    { 0x0000, (EmberAfAttributeMetadata*)&(generatedAttributes[0]), 11, 0, (CLUSTER_MASK_SERVER), NULL,  },    \
    { 0x0001, (EmberAfAttributeMetadata*)&(generatedAttributes[11]), 3, 2, (CLUSTER_MASK_SERVER), NULL,  },    \
    { 0x0003, (EmberAfAttributeMetadata*)&(generatedAttributes[14]), 1, 2, (CLUSTER_MASK_CLIENT), NULL,  },    \
    { 0x0003, (EmberAfAttributeMetadata*)&(generatedAttributes[15]), 2, 4, (CLUSTER_MASK_SERVER), NULL, },    \
    { 0x0020, (EmberAfAttributeMetadata*)&(generatedAttributes[17]), 5, 14, (CLUSTER_MASK_SERVER), NULL, },    \
    { 0x0500, (EmberAfAttributeMetadata*)&(generatedAttributes[22]), 6, 16, (CLUSTER_MASK_SERVER), NULL, },    \
	{ 0x0019, (EmberAfAttributeMetadata*)&(generatedAttributes[28]), 0, 0, (CLUSTER_MASK_CLIENT), NULL,},    \
  }


// Endpoint types
#define GENERATED_ENDPOINT_TYPES {        \
    { (EmberAfCluster*)&(generatedClusters[0]), 7, 38 }, \
  }

// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (143)//(110)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE 71

// Array of endpoints that are supported
#define FIXED_ENDPOINT_ARRAY { 1 }

// Array of profile ids
#define FIXED_PROFILE_IDS { 260 }

// Array of device ids
#define FIXED_DEVICE_IDS { 1026 }

// Array of device versions
#define FIXED_DEVICE_VERSIONS { 1 }

// Array of endpoint types supported on each endpoint
#define FIXED_ENDPOINT_TYPES { 0 }

// Array of networks supported on each endpoint
#define FIXED_NETWORKS { 0 }

#endif

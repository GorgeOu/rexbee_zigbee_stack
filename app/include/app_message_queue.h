
#ifndef __ZCL_MESSAGE_QUEUE_H__
#define __ZCL_MESSAGE_QUEUE_H__

typedef enum
{
	APP_MESSAGE_NORAML	  			= 0,
	APP_MESSAGE_NO_ZCL_RETRY	 	= 0,
	APP_MESSAGE_CUSTOM_SEQ 			= BIT(0),
	APP_MESSAGE_ZCL_RETRY 			= BIT(1),
} app_message_mask_t;

typedef struct
{
	app_message_mask_t mask;
	uint16_t profile_id;
	uint8_t  source_ep;
	uint8_t  dest_ep;
	uint16_t cluster_id;
	union
	{
		uint8_t  zcl_frame_control;

		struct
		{
			uint8_t frame_type 	 		 : 2;
			uint8_t mfg_spec  	 		 : 1; //auto set to 1 if manufacture_code is not 0
			uint8_t direction 	     	 : 1;
			uint8_t disable_default_resp : 1;
			uint8_t reserved 			 : 3;
		} zcl_frame_control_s;
	} u_zcl_frame;
	uint8_t  command_id;
	uint16_t manufacture_code;
	union
	{
		int8_t  zcl_seq; 	// It takes effect if message masked APP_MESSAGE_CUSTOM_SEQ
		int8_t  padding;
	} u_seq;
} app_zcl_message_header_t;

typedef struct
{
	app_zcl_message_header_t* header;
	uint16_t command_length;
	uint8_t* command_payload;
} app_zcl_message_t;

typedef enum
{
	APP_DELIVERY_TYPE_UNICAST,
	APP_DELIVERY_TYPE_RESERVED_1,
	APP_DELIVERY_TYPE_VIA_BIND,
	APP_DELIVERY_TYPE_GROUP,
	APP_DELIVERY_TYPE_RESERVED_2,
	APP_DELIVERY_TYPE_RESERVED_3,
	APP_DELIVERY_TYPE_BROADCAST,
	APP_DELIVERY_TYPE_VIA_EUI64,
	APP_DELIVERY_TYPE_UNKNOW,
} app_message_delivery_type_t;

typedef enum
{
	APP_DELIVERY_OPT_SOURCE_EUI64_DISABLE 		= BIT(0),
	APP_DELIVERY_OPT_APS_RETRY_DISABLE    		= BIT(1),
	APP_DELIVERY_OPT_ROUTE_DISCOVERY_DISABLE 	= BIT(2),
	APP_DELIVERY_OPT_ADDRESS_DISCOVERY_DISABLE 	= BIT(3),
    APP_DELIVERY_OPT_BLOCKING_MODE 				= BIT(4), //zcl retry enable will set APP_DELIVERY_OPT_APS_RETRY_DISABLE & APP_DELIVERY_OPT_BLOCKING_MODE
    APP_DELIVERY_OPT_SINGLETON_MODE 			= BIT(5),
} app_message_delivery_optional_t;

typedef struct
{
	uint8_t  dest_eui64[8];

	union
	{
		struct
		{
			uint16_t dest_node;
		} unicast;

		struct
		{
			uint16_t bind_table_index;
		} bind;

		struct
		{
			uint16_t group_id;
		} group;

		struct
		{
			uint16_t broadcast_node;
		} broadcast;
		uint16_t destination;
	} u_addr;
} app_message_destination_t;

typedef struct
{
	app_message_delivery_type_t type;
	uint8_t hops;
	app_message_delivery_optional_t options;
	uint8_t  dest_eui64[8];
	union
	{
		struct
		{
			uint16_t dest_node;
		} unicast;

		struct
		{
			uint16_t bind_table_index;
		} bind;

		struct
		{
			uint16_t group_id;
		} group;

		struct
		{
			uint16_t broadcast_node;
		} broadcast;
		uint16_t destination;
	} u_addr;
} app_message_delivery_t;

typedef uint16_t (*app_message_queue_fill_content_callback_t)(uint8_t* content_head, uint8_t* content, void* args);

typedef uint8_t (*app_message_queue_sent_callback_t)(EmberOutgoingMessageType type,
												     app_message_destination_t* destination,
												     EmberApsFrame* apsFrame,
												     uint16_t msgLen,
												     uint8_t* message,
												     EmberStatus status);

void app_default_uart_message_queue_init(uint8_t  retry_max_counts,
										 uint16_t retry_interval_ms,
										 uint16_t min_message_interval_ms,
										 void (*pre_send_cb)(void),
										 void (*post_send_cb)(void));

uint8_t app_uart_message_queue_send(bool send_imm, const char* format, ...);

void app_uart_message_queue_remove_head(void);

bool app_uart_message_queue_is_empty(void);

#endif

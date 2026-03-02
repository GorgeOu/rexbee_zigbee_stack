#ifndef __GLOBAL_MESSAGE_APIS_H__
#define __GLOBAL_MESSAGE_APIS_H__

#include "app_message_queue.h"

void app_message_queue_set_min_backoff(uint32_t backoff_ms);

void app_message_queue_set_ext_backoff_interval(uint32_t ext_backoff_ms);

void app_message_queue_set_zcl_message_retry(uint8_t max_retry_count, int* interval_ms);

void app_set_zcl_message_queue_default_options(uint16_t options);

uint8_t app_zcl_message_queue_format_send(const app_message_delivery_t* delivery,
										  app_zcl_message_header_t* header,
										  const uint16_t queue_delay_ms,
										  app_message_queue_sent_callback_t sent_callback,
										  const char* format,
										  ...);

void app_print_zcl_message_queue(void);

// legacy apis
//
//
//
uint8_t stack_get_next_zcl_sequence(void);

uint8_t stack_get_next_zdo_sequence(void);

EmberStatus app_v2_send_zcl_message(uint16_t profile, uint16_t destNodeId,
                                    uint16_t group, uint8_t sourceEndpoint,
                                    uint8_t destEndpoint, uint16_t cluster,
                                    uint8_t zclFrame, uint16_t manufactureCode,
                                    uint8_t zclCommand, uint8_t length,
                                    uint8_t* data, EmberApsOption apsOption,
                                    uint8_t hops, uint8_t zclSequence);

uint8_t app_v2_send_zcl_mfg_all_bind(uint16_t profile,
									 uint16_t filter_node_id,
									 uint8_t  filter_endpoint,
									 uint8_t source_endpoint,
									 uint16_t cluster,
									 uint8_t zcl_frame,
									 uint16_t manufacture_code,
									 uint8_t zcl_command,
									 uint8_t length,
									 uint8_t* data);

uint8_t app_v2_send_zcl_mfg(uint16_t profile, uint16_t dest_node, uint16_t group, uint8_t source_ep, uint8_t dest_ep,
                            uint16_t cluster, uint8_t zcl_frame, uint16_t mfg_code, uint8_t zcl_command,
                            uint8_t length, uint8_t* data, uint8_t hops);

uint8_t app_v2_device_report_attr_mfg(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster_id,
                                      uint16_t attribute_id, uint8_t data_type, uint8_t* data, uint16_t mfg_code);

uint8_t app_v2_device_report_multi_attr_mfg(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                            uint16_t mfg_code, uint8_t num, attribute_data_t* data);

uint8_t app_v2_send_zcl_write_response(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                       uint16_t mfg_code, uint8_t status, uint8_t zcl_seq);

uint8_t app_v2_send_zcl_read_request_with_seq(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                              uint16_t mfg_code, uint16_t* attribute, uint8_t count, uint8_t zcl_seq);

uint8_t app_v2_send_zcl_read_attributes_request(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                                uint16_t mfg_code, uint16_t* attribute, uint8_t count);

uint8_t app_v2_send_zcl_read_request(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                     uint16_t mfg_code, uint16_t attribute);

uint8_t app_v2_send_zcl_read_response(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                      uint16_t mfg_code, uint16_t attribute, uint8_t type, uint8_t status, uint8_t* data,
                                      uint8_t zcl_seq);

uint8_t app_v2_send_zcl_write_request_with_seq(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                               uint16_t mfg_code, uint16_t attribute, uint8_t type, uint8_t* data, uint8_t zcl_seq);

uint8_t app_v2_send_zcl_write_request(uint16_t dest_node, uint8_t source_ep, uint8_t dest_ep, uint16_t cluster,
                                      uint16_t mfg_code, uint16_t attribute, uint8_t type, uint8_t* data);

void app_v2_sync_bind_member_status(uint16_t cluster, uint8_t* fields, uint8_t size, uint8_t ep, uint8_t is_client);

#endif


#ifndef __UART_MESSAGE_QUEUE_H__
#define __UART_MESSAGE_QUEUE_H__

void app_default_uart_message_queue_init(uint8_t  retry_max_counts,
										 uint16_t retry_interval_ms,
										 uint16_t min_message_interval_ms,
										 void (*pre_send_cb)(void),
										 void (*post_send_cb)(void));

/** 介绍：串口消息发送
 * 参数：
 *		send_imm : true - 立即发送, false - 插入队列，等待发送
 *		format : "uvw" -> 小端 uint8 uint16 uint32
 *				 "UVW" -> 大端 uint8 uint16 uint32
 *				 "l" -> 小端 MAC
 *				 "L" -> 大端 MAC
 *				 "b" -> array ptr, 第二个参数为长度，例如(..., "b", buffer, len)
 *				 "a" -> array buffer, 第二个参数并写入到array buffer[0]
 *				 "B" -> callback 原型为 : app_message_queue_fill_content_callback_t,
 *				 				  第二个参数为回调的入参args
 *
 *	e.g. :
 *	static uint16_t _fill_content_callback(uint8_t* content_head, uint8_t* content, void* args)
 *	{
 *		content[0] = 0xEE;
 *		content[1] = 0xFF;
 *		return 2;
 *	}
 *	uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
 *	app_uart_message_queue_send(false, "uUvVwWbB", \
 *								0x01, 0x02, 0x1234, 0x1234, 0x12345678, 0x12345678, data, sizeof(data), \
 *								_fill_content_callback, NULL);
 *
 *	输出结果为：01 02 34 12 12 34 78 56 34 12 12 34 56 78 AA BB CC DD EE FF
 */
uint8_t app_uart_message_queue_send(bool send_imm, const char* format, ...);

void app_uart_message_queue_remove_head(void);

bool app_uart_message_queue_is_empty(void);

#endif

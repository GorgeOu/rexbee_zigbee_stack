
#ifndef __UART_PROTOCOL_DESC_H__
#define __UART_PROTOCOL_DESC_H__

#define UART_FRAME_MIN_LENGTH  		9

#define UART_PROTOCOL_HEADER     	0x55AA //big endian
#define UART_PROTOCOL_VERSION    	0x03

#define UART_FRAME_GET_HEADER(p)	(HIGH_LOW_TO_INT(p[0], p[1])) //big endian
#define UART_FRAME_HEADER_CHECK(p)	(UART_FRAME_GET_HEADER(p) == UART_PROTOCOL_HEADER)

#define UART_FRAME_GET_VERSION(p)	(p[2])
#define UART_FRAME_VERSION_CHECK(p)	(UART_FRAME_GET_VERSION(p) == UART_PROTOCOL_VERSION)

#define UART_FRAME_GET_SEQ(p)		 (HIGH_LOW_TO_INT(p[3], p[4])) //big endian
#define UART_FRAME_GET_CMD(p)		 (p[5])
#define UART_FRAME_GET_LENGTH(p)	 (HIGH_LOW_TO_INT(p[6], p[7])) //big endian
#define UART_FRAME_GET_PAYLOAD(p)	 (p + 8)

void user_uart_message_init(void);

uint8_t app_generate_uart_protocol_frame(uint8_t cmd, uint16_t seq, uint8_t* data, uint16_t length);


#endif

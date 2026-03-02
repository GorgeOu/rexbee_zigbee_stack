
#if defined(RZ_STACK_UART_DEMO)

#include "../include/global_apis.h"
#include "uart_protocol_desc.h"

#define debugPortAll(format,...) 	app_debug_printf(format, ##__VA_ARGS__)

void user_uart_message_init(void)
{
	app_default_uart_message_queue_init(3, 100, 50, NULL, NULL);
}

static uint8_t _uart_protocol_check_sum(uint8_t* content, uint16_t length)
{
	uint32_t sum = 0;

	for(uint16_t i = 0; i < length; i++)
	{
		sum += content[i];
	}

	return (sum % 256);
}

static uint16_t _uart_message_queue_fill_content_callback(uint8_t* content_head, uint8_t* content, void* args)
{
	uint8_t sum = _uart_protocol_check_sum(content_head, content - content_head);

	content[0] = sum;

	return 1;
}

uint8_t app_generate_uart_protocol_frame(uint8_t cmd, uint16_t seq, uint8_t* data, uint16_t length)
{
	return app_uart_message_queue_send(false, "VuVuVbB",
										UART_PROTOCOL_HEADER,
										UART_PROTOCOL_VERSION,
										seq,
										cmd,
										length,
										data,
										length,
										_uart_message_queue_fill_content_callback,
										NULL);
}

bool app_uart_frame_clip_check(uint8_t* p, uint32_t* len)
{
    if ( (*len) >= UART_FRAME_MIN_LENGTH )
    {
        uint16_t   pos   = 0;

        while( (pos + UART_FRAME_MIN_LENGTH) <= (*len) )
        {
            if(UART_FRAME_HEADER_CHECK(p) && UART_FRAME_VERSION_CHECK(p))
            {
                uint16_t length = HIGH_LOW_TO_INT(p[pos + 6], p[pos + 7]);

                //debugPortAll("\r\n[UART CHECK]Header pas, length %d, *len %d", length, *len);

                if((pos + UART_FRAME_MIN_LENGTH + length) <= (*len))
                {
                    //debugPortAll(", data : %a", p + pos, UART_FRAME_MIN_LENGTH + length);

                    uint8_t cal_check_sum = _uart_protocol_check_sum(p + pos, UART_FRAME_MIN_LENGTH + length - 1);

                    //debugPortAll(", checksum(0x%x, 0x%x)", p[pos + UART_FRAME_MIN_LENGTH + length - 1], cal_check_sum);

                    if(p[pos + UART_FRAME_MIN_LENGTH + length - 1]== cal_check_sum)
                    {
                        debugPortAll("\r\n[UART CHECK]UART frame check sum pass.");

                        if(pos)
                        {
                            for(int8u i = pos; i < (*len); i++)
                            {
                                p[i - pos]  = p[i];
                            }

                            (*len) = (*len) - pos;
                        }

                        return  true;
                    }
                    else
                    {
                        debugPortAll("\r\n[UART CHECK]UART frame check sum error.");
                    }
                }
            }

            pos++;
        }
    }

	return false;
}

void app_process_long_uart_data(uint8_t* data, uint32_t length)
{
	//The checksum has been determined in the app_uart_frame_clip_check
	if(UART_FRAME_HEADER_CHECK(data) &&
	  (data[length - 1] == _uart_protocol_check_sum(data, length - 1)))
	{
		uint16_t seq		 = UART_FRAME_GET_SEQ(data);
		uint8_t cmd 		 = UART_FRAME_GET_CMD(data);
		uint16_t cmd_length  = UART_FRAME_GET_LENGTH(data);
		uint8_t* cmd_payload = UART_FRAME_GET_PAYLOAD(data);

		debugPortAll("\r\n[UART]Seq 0x%x, cmd 0x%x, length %d, payload : %a", \
					 seq, cmd, cmd_length, cmd_payload, cmd_length);
	}
}

#endif


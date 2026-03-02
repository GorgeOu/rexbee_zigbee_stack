/**
 * Copyright ? 2019 Zhejiang Raying IoT Technology Co., Ltd.
 * All rights reserved. 
 *
 * File: Global_Callbacks.c
 * Description: This file implements global callbacks.
 *
 * Author(s): yuxiaoqiang@rexense.com	
 * Data: 2020/02/20
 */
#if defined(RZ_STACK_API_USAGE)

#include "../include/global_apis.h"
#include "pin_def.h"
#include "app_common.h"

#define  DEFINEEEPTYPE
#include "common/app_sim_eep.h"	//type def
#undef   DEFINEEEPTYPE
#include "common/app_sim_eep.h" //api def

#if defined(RZ_STACK_FLASH_API_USAGE)

#warning "flash api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_FLASH_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_FLASH_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

void app_hal_uart_config(void)
{
	app_serial_init(TYPE_UART_SERIAL,
					APP_UART_TX_PIN,
					APP_UART_RX_PIN,
					APP_UART_BAUDRATE,
					UART_PARITY_NONE,
					1);
}

static void flash_test_command(uint8_t port, uint32_t address_start, uint16_t page_number, uint32_t count)
{
	extern uint8_t sim_eeprom_buffer[];

	uint32_t test_count	= 0;

    uint32_t time           = halCommonGetInt32uMillisecondTick();

    app_serial_port_printf(port, "\r\n[FLASH]Flash test (0x%4x ~ 0x%4x, %d) start, wait for result...", address_start, address_start + ((uint32_t)page_number * HAL_FLASH_PAGE_SIZE), count);

	while(true)
	{
        bool test_failed = false;

	    for(uint16_t page = 0; page < page_number; page++)
	    {
            uint32_t address = address_start + ((uint32_t)page * HAL_FLASH_PAGE_SIZE);

    		hal_internal_erase_flash(address);

    		MEMSET(sim_eeprom_buffer, 0, HAL_FLASH_PAGE_SIZE);

    		hal_internal_read_flash(address, sim_eeprom_buffer, HAL_FLASH_PAGE_SIZE);

    		if(!util_data_compare(sim_eeprom_buffer, HAL_FLASH_PAGE_SIZE, 0xff))
    		{
    		    test_failed = true;
    			break;
    		}

    		MEMSET(sim_eeprom_buffer, (uint8_t)test_count, HAL_FLASH_PAGE_SIZE);

    		hal_internal_write_flash(address, sim_eeprom_buffer, HAL_FLASH_PAGE_SIZE);

    		MEMSET(sim_eeprom_buffer, 0, HAL_FLASH_PAGE_SIZE);

    		hal_internal_read_flash(address, sim_eeprom_buffer, HAL_FLASH_PAGE_SIZE);

    		if(!util_data_compare(sim_eeprom_buffer, HAL_FLASH_PAGE_SIZE, (uint8_t)test_count))
    		{
    		    test_failed = true;
    			break;
    		}
        }

		test_count++;

        if(test_failed)
        {
            break;
        }

		if(test_count >= count)
		{
            uint32_t diff = (halCommonGetInt32uMillisecondTick() - time);

            app_serial_port_printf(port, "\r\n[FLASH]Flash test pass, total count %d, time %dms", test_count, diff, diff / (test_count * page_number));

			return;
		}
	}

    uint32_t diff = (halCommonGetInt32uMillisecondTick() - time);

    app_serial_port_printf(port, "\r\n[FLASH]Flash test failure, total count %d, time %dms, each page %dms",
	                test_count, diff, diff / (test_count * page_number));
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	//AT+REBOOT (has already imp in the sdk), use AT+REBOOT or power down to reboot chip

	if( (util_strncmp("AT+FLASHTEST", (const char* )data, 12) == 0) && (length == 12) )
	{
		flash_test_command(port, 0x3A000, 1, 10000);

		return true;
	}

	return false;
}

void app_plugin_init_callback(void)
{
	app_at_command_handle_register(user_at_command_handler);
}

void app_main_init_callback(void)
{
	app_version_printf(TYPE_UART_SERIAL);
}

void app_main_tick_callback(void)
{

}

#endif

#endif


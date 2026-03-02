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

#if defined(RZ_STACK_MEM_HEAP_API_USAGE)

#warning "mem heap api demo"

#define debugPortAll(format,...) 			app_serial_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)

#define APP_RELEASE_VERSION "1.0.0"

char const c_app_release_version[] = { APP_RELEASE_VERSION }; //don't modify

app_user_device_info_t app_user_device_info =
{
	.firmware_print_version 			= "REX_ZB_MEM_HEAP_USAGE_" APP_RELEASE_VERSION,
	.model_id							= "REX_ZB_MEM_HEAP_USAGE",
	.manufacture_name 					= "REXENSE",
	.manufacture_code   				= REXENSE_MANUFACTURER_CODE,
	.radio_tx_power 					= 20,
	.zigbee_type						= ZIGBEE_TYPE_ZIGBEE_3_0_CONFIG,
	.default_zcl_message_aps_ack_enable = true,
	.send_device_announce_after_reboot	= true,
};

static uint8_t s_heap_memory[4096];

#define TEST_HEAP_INIT          stack_heap_init
#define TEST_HEAP_MALLOC        stack_heap_malloc
#define TEST_HEAP_FREE          stack_heap_free
#define TEST_HEAP_REALLOC       stack_heap_realloc
#define TEST_HEAP_CALLOC        stack_heap_calloc
#define TEST_HEAP_STATISTICS    stack_heap_statistics

void app_hal_uart_config(void)
{
	app_serial_init(TYPE_UART_SERIAL,
					APP_UART_TX_PIN,
					APP_UART_RX_PIN,
					APP_UART_BAUDRATE,
					UART_PARITY_NONE,
					1);
}

static void print_stats(uint8_t port, const char* tag)
{
    size_t total, free_space;
    TEST_HEAP_STATISTICS(&total, &free_space);
    app_serial_port_printf(port, "\r\n%s Total: %d, Free: %d", tag, total, free_space);
}

static int heap_test(uint8_t port)
{
    // initialize heap
    uint8_t status = TEST_HEAP_INIT(s_heap_memory, sizeof(s_heap_memory));

    if(status != 0x00)
    {
    	app_serial_port_printf(port, "\r\nheap init failed 0x%x", status);
    }

    print_stats(port, "After initialization");

    // malloc test
    void* p1 = TEST_HEAP_MALLOC(128);
    if (p1 == NULL)
    {
        app_serial_port_printf(port, "\r\nmalloc failed");
        return -1;
    }
    print_stats(port, "After malloc(128)");

    // calloc test
    int* p2 = (int*)TEST_HEAP_CALLOC(10, sizeof(int));
    if (p2 == NULL)
    {
        app_serial_port_printf(port, "\r\ncalloc failed\n");
        return -1;
    }
    // verify calloc zeroes memory
    for (int i = 0; i < 10; i++)
    {
        if (p2[i] != 0)
        {
            app_serial_port_printf(port, "\r\ncalloc did not zero memory!\n");
            break;
        }
    }
    print_stats(port, "After calloc(10, sizeof(int))");

    // realloc test: grow
    p1 = TEST_HEAP_REALLOC(p1, 256);
    if (p1 == NULL)
    {
        app_serial_port_printf(port, "\r\nrealloc (grow) failed\n");
        return -1;
    }
    print_stats(port, "After realloc to 256");

    // realloc test: shrink
    p1 = TEST_HEAP_REALLOC(p1, 64);
    if (p1 == NULL)
    {
        app_serial_port_printf(port, "\r\nrealloc (shrink) failed\n");
        return -1;
    }
    print_stats(port, "After realloc to 64");

    // **full-allocation test**
    enum { MAX_ALLOCS = 100 };
    void* ptrs[MAX_ALLOCS];
    int count = 0;
    for (; count < MAX_ALLOCS; count++)
    {
        ptrs[count] = TEST_HEAP_MALLOC(64);
        if (ptrs[count] == NULL)
        {
            break;
        }
    }
    app_serial_port_printf(port, "\r\nmalloc until full: allocated %d blocks of 64 bytes", count);
    print_stats(port, "After exhausting heap");

    // free all allocated in full-allocation test
    for (int i = 0; i < count; i++)
    {
        TEST_HEAP_FREE(ptrs[i]);
    }
    print_stats(port, "After free full-allocation test blocks");

    // free tests
    TEST_HEAP_FREE(p2);
    print_stats(port, "After free(p2)");

    TEST_HEAP_FREE(p1);
    print_stats(port, "After free(p1)");

    // final stats
    print_stats(port, "Before exit");

    return 0;
}

#define ALLOC_COUNT   100
#define ALLOC_SIZE    32

void heap_benchmark_run(uint8_t port)
{
    // initialize heap
    uint8_t status = TEST_HEAP_INIT(s_heap_memory, sizeof(s_heap_memory));

    if(status != 0x00)
    {
    	app_serial_port_printf(port, "\r\nheap init failed 0x%x", status);
    }

    void* ptrs[ALLOC_COUNT];
    uint32_t start_ms, end_ms;
    int i;

    // ------------ malloc ------------
    start_ms = halCommonGetInt32uMillisecondTick();
    for (i = 0; i < ALLOC_COUNT; i++)
    {
        ptrs[i] = TEST_HEAP_MALLOC(ALLOC_SIZE);
        if (!ptrs[i])
        {
            app_serial_port_printf(port, "\r\nmalloc failed at #%d", i);
            break;
        }
    }
    end_ms = halCommonGetInt32uMillisecondTick();
    app_serial_port_printf(port, "\r\nmalloc %d blocks of %d bytes: %l ms",
                   i, ALLOC_SIZE, end_ms - start_ms);

    // ------------ free ------------
    start_ms = halCommonGetInt32uMillisecondTick();
    for (int j = 0; j < i; j++)
    {
        TEST_HEAP_FREE(ptrs[j]);
    }
    end_ms = halCommonGetInt32uMillisecondTick();
    app_serial_port_printf(port, "\r\nfree %d blocks: %l ms", i, end_ms - start_ms);

    // ------------ calloc ------------
    start_ms = halCommonGetInt32uMillisecondTick();
    for (i = 0; i < ALLOC_COUNT; i++) {
        ptrs[i] = TEST_HEAP_CALLOC(1, ALLOC_SIZE);
        if (!ptrs[i]) {
            app_serial_port_printf(port, "\r\ncalloc failed at #%l", i);
            break;
        }
    }
    end_ms = halCommonGetInt32uMillisecondTick();
    app_serial_port_printf(port, "\r\ncalloc %d blocks of %d bytes: %l ms",
                   i, ALLOC_SIZE, end_ms - start_ms);

    // ------------ free after calloc ------------
    start_ms = halCommonGetInt32uMillisecondTick();
    for (int j = 0; j < i; j++) {
        TEST_HEAP_FREE(ptrs[j]);
    }
    end_ms = halCommonGetInt32uMillisecondTick();
    app_serial_port_printf(port, "\r\nfree after calloc %d blocks: %l ms", i, end_ms - start_ms);

    // ------------ realloc ------------
    for (i = 0; i < ALLOC_COUNT; i++)
    {
        ptrs[i] = TEST_HEAP_MALLOC(ALLOC_SIZE);
        if (!ptrs[i])
        {
            app_serial_port_printf(port, "\r\nprep malloc failed at #%d", i);
            break;
        }
    }

    start_ms = halCommonGetInt32uMillisecondTick();

    for (int j = 0; j < i; j++)
    {
        ptrs[j] = TEST_HEAP_REALLOC(ptrs[j], ALLOC_SIZE * 2);
        if (!ptrs[j])
        {
            app_serial_port_printf(port, "\r\nrealloc failed at #%d", j);
            break;
        }
    }
    end_ms = halCommonGetInt32uMillisecondTick();

    app_serial_port_printf(port, "\r\nrealloc grow %d blocks to %d bytes: %l ms",
                   	   	   i, ALLOC_SIZE * 2, end_ms - start_ms);

    // ------------ free after realloc ------------
    start_ms = halCommonGetInt32uMillisecondTick();
    for (int j = 0; j < i; j++)
    {
        TEST_HEAP_FREE(ptrs[j]);
    }
    end_ms = halCommonGetInt32uMillisecondTick();

    app_serial_port_printf(port, "\r\nfree after realloc %d blocks: %l ms", i, end_ms - start_ms);
}

static bool user_at_command_handler(uint8_t port, uint8_t* data, uint32_t length)
{
	if(util_strncmp("AT+HEAPTEST", (const char* )data, 10) == 0)
	{
		heap_test(port);
		return true;
	}

	if(util_strncmp("AT+HEAPBENCHMARK", (const char* )data, 16) == 0)
	{
		heap_benchmark_run(port);
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


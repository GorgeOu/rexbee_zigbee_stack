#ifndef __GLOBAL_HAL_COMMON_APIS_H__
#define __GLOBAL_HAL_COMMON_APIS_H__

/* GPIO配置部分
*  io : PORTX_PIN(Y)

   mode :
   GPIOCFG_IN
   GPIOCFG_IN_PUD
   GPIOCFG_OUT
   GPIOCFG_OUT_ALT
   GPIOCFG_OUT_OD

   output : TRUE - high level, FALSE - low level
*/
void app_hal_gpio_config(uint8_t io, uint8_t mode, bool output);
bool app_hal_gpio_read(uint8_t io);
void app_hal_gpio_toggle(uint8_t io);
void app_hal_gpio_set(uint8_t io);
void app_hal_gpio_clear(uint8_t io);

bool hal_common_gpio_config_and_read(uint8_t io, uint8_t mode, bool output);

#define Read_GPIO(io)							app_hal_gpio_read(io)
#define Set_GPIO(io)							app_hal_gpio_set(io)
#define Clear_GPIO(io)							app_hal_gpio_clear(io)
#define Toggle_GPIO(io)							app_hal_gpio_toggle(io)

//define pwm pin in HAL_PWM_PIN_LIST

//|  port  |  pin | trigger level | pwm direction |
// note :  pwm direction only support gpio which have dual direction pwm mode, view pwm_driver.h
//		   same pwm way _N mode and non _N mode will interacted with each other
// pwm direction : 1 - first,  2 - second, other - default 1
// e.g. PC1 support PWM1_N/PWM0, 1 - use PWM1_N, 2 use PWM0

/*
#define HAL_PWM_PIN_LIST \
{\
	{PORTD,  2,  HIGH_LEVEL_TRIGGER,	0xff}, \
}
*/

//pwm引脚可选列表
/* PA0->PWM0_N
 * PA2->PWM0
 * PA3->PWM1
 * PA4->PWM2
 * PB0->PWM3
 * PB1->PWM4
 * PB2->PWM5
 * PB3->PWM0_N
 * PB4->PWM4
 * PB5->PWM5
 * PC0->PWM4_N
 * PC1->PWM1_N/PWM0
 * PC2->PWM0
 * PC3->PWM1
 * PC4->PWM2/PWM0_N
 * PC5->PWM3_N
 * PC6->PWM4_N
 * PC7->PWM5_N
 * PD2->PWM3
 * PD3->PWM1_N
 * PD4->PWM2_N
 * PD5->PWM0/PWM0_N
 */


/**介绍：PWM时钟初始化
 * 参数： -
 * 返回：-
 */
void app_pwm_timer_init(void);

/**介绍：PWM pin list注册（可选调用）
 * 		注 ：  1. 如果未调用，默认使用旧版本的pin_def.h中定义的HAL_PWM_PIN_LIST
 * 	        2. 该函数默认内部调用 app_pwm_timer_init
 * 参数： pins: 格式与HAL_PWM_PIN_LIST相同,
 * 		pin_counts: pwm pin数量
 * 返回：-
 * e.g.
 * 	const hal_pwm_gpio_config_list_t c_user_pwm_pin_list[] =
 * 	{
 * 		{PORTD,  2,  HIGH_LEVEL_TRIGGER,	0xff},
 * 		{PORTA,  2,  HIGH_LEVEL_TRIGGER,	0xff},
 * 		{PORTA,  3,  HIGH_LEVEL_TRIGGER,	0xff}
 *	};
 *
 *	app_v2_pwm_pin_list_register(c_user_pwm_pin_list, ARRAY_SIZE(c_user_pwm_pin_list));
 */
void app_v2_pwm_pin_list_register(const hal_pwm_gpio_config_list_t* pins, uint8_t pin_counts);

/**介绍：开始指定PWM端口V2
 * 参数： index : PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引
 * 返回：-
 */
void app_v2_pwm_start(uint8_t index);

/**介绍：停止指定PWM端口V2
 * 参数： index : PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引
 * 返回：-
 */
void app_v2_pwm_stop(uint8_t index);

/**介绍：读取当前pwm占空比
*  参数：index : PWM引脚索引, 从 0 - 5 可选, 按照pin_def.h中的PWM list索引
*  返回：当前pwm占空比
*/
uint16_t app_v2_get_current_pwm_value(uint8_t index);

/**介绍：设置函数占空比以及频率
* 参数： freq	   PWM波频率, 范围184-47000HZ
* 		rgb_val	   PWM波占空比, 范围0-255之间表示占空比0-100%
* 		index      PWM引脚索引, 从 0 - 5 可选, 按照pin_def.h中的PWM list索引
* 返回：-
*/
void app_v2_set_pwm_freq_duty(uint16_t freq, uint16_t rgb_val, uint8_t index);

/**介绍：PWM渐变曲线插件初始化，设置渐变曲线(自定义精度版本)
 *  参数: pwm_curve : 定义的精度长度字节的数据，按照要求需要从小到大列出，单个字节，若中间需要跳跃则填写相同值
 *  返回: accuracy  : 精度值建议大于256, 范例中c_pwm_driver_curve的大小与精度值有关
 *		 pwm_gradual_finish_callback : 渐变结束回调注册（注: 如果注册了改回调, 回调内不可加入串口打印）
 *  e.g. : 设置精度为256
 *  const uint16_t c_pwm_driver_curve[256] =
 *	{
 *		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
 *		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
 *		40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
 *		60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
 *		80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
 *		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
 *		120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
 *		140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
 *		160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
 *		180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
 *		200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
 *		220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
 *		240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
 *	};
 *
 *	app_pwm_gradual_change_curve_v2_register(c_pwm_driver_curve, 256, NULL);
 */
void app_pwm_gradual_change_curve_v2_register(const uint16_t* pwm_curve,
											  uint16_t accuracy,
											  void (*pwm_gradual_finish_callback)(uint8_t index));

/**介绍：新增单路PWM渐变事件
 * 参数：index		: PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引
 *		frequence   : pwm频率Hz
 *		total_time	: 渐变总时长ms(0 ~ 0xffffff)
 *		step_time	: 每一个步进的时间ms(0 ~ 0xffffff)
、 *		target		: 目标亮度值
 * 返回：true - 成功, false - 失败
 */
bool app_v2_add_single_pwm_task(uint8_t index, uint16_t freqence, uint32_t total_time, uint32_t step_time, uint16_t target);

/**介绍: 新增2路互补PWM渐变事件
 * 参数: index		  : PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引
 * 		index_invert  : 互补路PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引
 *		frequence     : pwm频率Hz
 *		total_time	  : 渐变总时长ms(0 ~ 0xffffff)
 *		step_time	  : 每一个步进的时间ms(0 ~ 0xffffff)
 *		target		  : 目标亮度值
 *		target_invert : 互补路目标亮度值
 * 返回：true - 成功, false - 失败
 */
bool app_v2_add_complementary_pwm_task(uint8_t  index,
									   uint8_t  index_invert,
									   uint16_t freqence,
									   uint32_t total_time,
									   uint32_t step_time,
									   uint16_t target,
									   uint16_t target_invert);
/**介绍：pwm task是否进行中
 * 参数：index : PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引， 0xff表示检查全部
 * 返回：true - 成功, false - 失败
 */
bool app_v2_is_pwm_task_underway(uint8_t index);

/**介绍：删除PWM渐变事件
 * 参数：index : PWM引脚索引, 从0 - 5可选, 按照pin_def.h中的PWM list索引
 * 返回：true - 成功, false - 失败
 */
bool app_cancel_pwm_task(uint8_t index);

/**介绍：软复位函数
*  参数：无
*  返回：无
*/
void hal_reboot(void);

/**介绍：串口初始化函数
*  参数：port见枚举值，（TYPE_UART_SERIAL）为支持AT指令的串口
*		 txLocation, rxLocation为串口IO配置
		 rate 波特率, 如: 115200, 57600, 9600...
		 parity : 见枚举值定义
		 stopBits : 1或2, 如无特殊需要,默认为1
*  返回：无
*/
uint8_t app_serial_init(app_serial_type_enum_t  port,
						uint8_t  txLocation,
						uint8_t  rxLocation,
						uint32_t rate,
						app_uart_parity_type_enum_t parity,
						uint8_t stopBits);

/**
 * 介绍：注册串口回调函数
 * 参数:
 *   port       			  - 串口端口号，仅支持 HAL_COMMON_UART1_SERIAL
 *   allow_timeout_on_receive - true  => 启用超时数据透传
 *            				  -	false => 接收回调(on_packet)只处理完整包，超时数据丢弃
 *
 *   validate   			  - 数据包验证回调函数，类型 serial_validate_packet_t
 *   on_packet  			  - 数据包接收回调函数，类型 serial_on_packet_received_t
 * 返回:
 *   EMBER_SUCCESS         		成功
 *   EMBER_SERIAL_INVALID_PORT   无效的串口端口
*/
EmberStatus app_serial_callback_register(uint8_t port,
										 bool allow_timeout_on_receive,
                                         serial_validate_packet_t validate,
                                         serial_on_packet_received_t on_packet);

/**
* 介绍：注销串口回调函数，移除指定端口的验证和接收回调
* 参数:
*   port - 串口端口号，仅支持 HAL_COMMON_UART1_SERIAL
* 返回:
*   EMBER_SUCCESS       成功
*   EMBER_NOT_FOUND		未找到对应的端口
*/
EmberStatus app_serial_callback_unregister(uint8_t port);

/**介绍：同app_serial_internal_printf，但不支持%f(浮点型), %o(八进制)打印
*  参数：port : TYPE_VCP_SERIAL | TYPE_UART_SERIAL | HAL_COMMON_ZIGBEE_WIRELESS_SERIAL
*  返回：无
*/
void app_serial_port_printf(uint8_t port, const char *format, ...);
	void app_serial_printf(const char* format, ...) __attribute__((deprecated));
	void app_virtual_serial_printf(const char *format, ...) __attribute__((deprecated));

/**介绍：设备应用额外的打印, port输出口类型选择， 并且额外支持%f(浮点型), %o(八进制)打印
 * 		注：使用该函数打印会额外增加约2k的固件大小
 *  参数：port : TYPE_VCP_SERIAL | TYPE_UART_SERIAL
 *  返回：无
 */
void app_serial_internal_printf(uint8_t port, const char *format, ...);

/**介绍：设备应用调试的打印, port输出口类型选择(需要AT+DEBUG=01使能后才能输出)
*  参数：port : TYPE_VCP_SERIAL | TYPE_UART_SERIAL 
*  返回：无
*/
#define app_debug_printf(format, ...) 			app_debug_port_printf(TYPE_UART_SERIAL, format, ##__VA_ARGS__)
#define app_virtual_debug_printf(format, ...)	app_debug_port_printf(TYPE_VCP_SERIAL, format, ##__VA_ARGS__)
void app_debug_port_printf(uint8_t port, const char *format, ...);

/**介绍：设备调试打印Hex字符串数组（需使能应用串口）, virtual为虚拟串口
*  参数：-
*  返回：无
*/
void app_serial_port_bytes_printf(uint8_t port, const char* format, uint8_t* buffer, uint8_t length);
	void app_serial_bytes_printf(const char* format, uint8_t* buffer, uint8_t length) __attribute__((deprecated));
	void app_virtual_serial_bytes_printf(const char* format, uint8_t* buffer, uint8_t length) __attribute__((deprecated));

/**介绍：设备输出Hex数组, virtual为虚拟串口
*  参数：-
*  返回：无
*/
void app_serial_port_write_data(uint8_t port, uint8_t* buffer, uint16_t length);
	void app_serial_send_hex_data(uint8_t *data, uint16_t length) __attribute__((deprecated));
	void app_virtual_serial_send_hex_data(uint8_t *data, uint16_t length) __attribute__((deprecated));

/**介绍：设备等待串口数据发送完成
*  参数：-
*  返回：无
*/
void app_serial_port_wait_send(uint8_t port);
void app_serial_wait_send(void) __attribute__((deprecated));

/**介绍：存储串口配置到token
*  参数：uart_config : | baudrate index | stop bit mask | parity mask |
*  				      |	   bit 0 - 4   |	  bit 5    |  bit 6 - 7  |
*  				    1) baudrate index : 参照 hal_baudrate_sel_index_enum_t
*					2） stop bit mask  : " BIT(5) = 0 : 1-stop-bit "
*										" BIT(5) = 1 : 2-stop-bit "
*					3） parity mask    : " BIT(6, 7) = 0 : parity none "
*										" BIT(6, 7) = 1 : parity odd  "
*										" BIT(6, 7) = 2 : parity even "
*  e.g. : 存储115200-N-1串口配置, app_store_uart_configuration_to_token(BAUDRATE_115200);
*  		    存储9600-O-1串口配置,   app_store_uart_configuration_to_token(BAUDRATE_9600 | BIT(6));
*  返回：无
*/
void app_store_uart_configuration_to_token(uint8_t uart_config);

/**介绍：使用token中的参数配置串口
*  参数：-
*  返回：无
*/
void app_recover_uart_configuration_from_token(void);

/**介绍：设备开关调试信息
*  参数： port 	- TYPE_UART_SERIAL/TYPE_VCP_SERIAL
*  	   onoff 	- true 打开	false 关闭 , 指定id的调试信息
*  	   debug_id - debug id见 debug list
*  	   e.g.
*  	   stack_debug_echo_config(TYPE_UART_SERIAL, true, 25);
*  返回：无
*/
void stack_debug_echo_config(uint8_t port, bool onoff, uint8_t debug_id);

/** 介绍 ： 阻塞式微秒级延时
 *  参数 ：us 延时时间 /us
 *  返回 ：-
 */
void app_safe_virtual_delay_micro_seconds(uint32_t us);

/** 介绍 ： 阻塞式毫秒级延时
 *  参数 ：ms 延时时间 /ms
 *  返回 ：-
 */
void app_safe_virtual_delay_milli_seconds(uint32_t ms);

/** 介绍 ： gpio中断注册接口
 *  参数 ：
 *  	io : PORTX_PIN(Y)
 *  	int_number : 0 ~ 2, support 3 gpio interrupt
 * 	 	rising_edge  : 上升沿触发中断 , true - 使能， false - 不使能
 *  	falling_edge : 下降沿触发中断, true - 使能， false - 不使能
 *		enhance_gpio_interrupt_callback : 注册中断回调， int_number注册时的中断号
 *	返回 ：-
 */
void app_hal_gpio_interrupt_register(uint8_t io, uint8_t interrupt_id, bool rising_edge,
                                     bool falling_edge, void (*gpio_interrupt_callback)(uint8_t int_number));

/** 介绍 ： gpio中断注册接口(回调提供上升下沿及2次中断的时间间隔)
 *  参数 ：
 *  	io : PORTX_PIN(Y)
 *  	int_number : 0 ~ 2, support 3 gpio interrupt
 *  	rising_edge  : 上升沿触发中断 , true - 使能， false - 不使能
 *  	falling_edge : 下降沿触发中断, true - 使能， false - 不使能
 *		enhance_gpio_interrupt_callback : 注册中断回调， int_number注册时的中断号， rising_or_falling - true(上升沿) false(下降沿), elapse_us两次中断的时间间隔us
 *	返回 ：-
 */
void app_hal_enhance_gpio_interrupt_register(uint8_t io, uint8_t interrupt_id, bool rising_edge, bool falling_edge,
											 void (*enhance_gpio_interrupt_callback)(uint8_t int_number, bool rising_or_falling, uint32_t elapse_us));

/** 介绍 ： gpio中断取消接口
 *  参数 ：
 *  	io : PORTX_PIN(Y)
 *  	int_number : 0 ~ 2, support 3 gpio interrupt
 *  返回 ：-
 */
void app_hal_gpio_interrupt_cancel(uint8_t io, uint8_t interrupt_id);

/** 介绍 ： adc采样接口
 *  参数 ：
 *  	io : PORTX_PIN(Y)
 *  返回 ：adc采样结果，单位mV
 */
uint32_t hal_adc_get_sample_result(uint8_t io);

/** 介绍 ： adc采样接口(多次采样平均)
 *  参数 ：
 *  	io : PORTX_PIN(Y)
 *  	counts : 采样次数，推荐4次
 *  返回 ：adc采样结果，单位mV
 */
uint32_t hal_adc_get_sample_result_counts(uint8_t io, uint8_t counts);

/** 介绍 ： vdd电压采样接口
 *  参数 ：无
 *  返回 ：adc采样结果，单位mV
 */
uint32_t hal_adc_get_vdd_milli_voltage(void);

/** 介绍 ： flash写操作
 *  参数 ： address ： 写入地址 0 ~ flash size
 *  	  data   : 写入数据
 *  	  length : 写入数据长度
 *  返回 ：-
 */
void hal_internal_write_flash(uint32_t address, uint8_t* data, uint32_t length);

/** 介绍 ： flash读操作
 *  参数 ： address ： 读取地址 0 ~ flash size
 *  	  data   : 读取数据
 *  	  length : 读取数据长度
 *  返回 ：-
 */
void hal_internal_read_flash(uint32_t address, uint8_t* data, uint32_t length);

/** 介绍 ： flash擦除操作
 *  参数 ： address ： 擦除地址 0 ~ flash size，必须为HAL_FLASH_PAGE_SIZE的整数倍
 *  返回 ：-
 */
void hal_internal_erase_flash(uint32_t address);

/**
 * 介绍 ：模拟 I2C 接口 GPIO 引脚初始化
 * 参数 ：
 *   i2c_scl : SCL 引脚编号（PORTX_PIN(Y)）
 *   i2c_sda : SDA 引脚编号（PORTX_PIN(Y)）
 *   clk_period_us : 时钟两个跳变之间的最小时间
 * 返回 ：无
 */
void hal_sim_i2c_gpio_init(uint8_t i2c_scl, uint8_t i2c_sda, uint16_t clk_period_us);

/**
 * 介绍 ：通过模拟 I2C 总线读取设备寄存器数据
 *  	_iram为ram code function，希望函数执行更快可以使用_iram func, 但会占用内存
 * 参数 ：
 *   dev_addr : I2C 从设备地址
 *   data     : 指向接收数据缓冲区的指针
 *   length   : 要读取的字节数
 *   reg_addr : 目标寄存器地址
 * 返回 ：
 *   操作状态，0 - 成功，非 0 - 失败
 */
uint8_t hal_sim_i2c_read(uint8_t dev_addr, uint8_t *data, uint16_t length, uint8_t reg_addr);
uint8_t hal_sim_i2c_read_iram(uint8_t dev_addr, uint8_t *data, uint16_t length, uint8_t reg_addr);

/**
 * 介绍 ：通过模拟 I2C 总线向设备寄存器写入数据
 * 		_iram为ram code function，希望函数执行更快可以使用_iram func, 但会占用内存
 * 参数 ：
 *   dev_addr : I2C 从设备地址
 *   data     : 指向要写入数据缓冲区的指针（只读）
 *   length   : 要写入的字节数
 *   reg_addr : 目标寄存器地址
 * 返回 ：
 *   操作状态，0 - 成功，非 0 - 失败
 */
uint8_t hal_sim_i2c_write(uint8_t dev_addr, const uint8_t *data, uint16_t length, uint8_t reg_addr);
uint8_t hal_sim_i2c_write_iram(uint8_t dev_addr, const uint8_t *data, uint16_t length, uint8_t reg_addr);

/**
 * 介绍 ：看门狗喂狗
 * 参数 ：-
 * 返回 ：-
 */
void hal_feed_watchdog(void);

#endif

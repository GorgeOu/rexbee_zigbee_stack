/*
 * fast_gpio.h
 *
 *  Created on: 2022-6-1
 *      Author: yuxiaoqiang
 */

#ifndef __HAL_FAST_GPIO_H__
#define __HAL_FAST_GPIO_H__

// —— Fast GPIO API ——

#define GPIO_OUT_REG_BASE       0x800583
#define GPIO_IN_REG_BASE        0x800580
#define GPIO_OUT_EN_REG_BASE    0x800582
#define GPIO_IN_EN_REG_BASE     0x800581

#define GPIO_AREG_GROUP1_IE			0xbd
#define GPIO_AREG_GROUP2_IE			0xc0

#define AGPIO_GROUP1 0x100
#define	AGPIO_GROUP2 0x200

extern unsigned char analog_read(unsigned char addr);
extern  void analog_write(unsigned char addr, unsigned char v);
extern void gpio_set_data_strength(unsigned short pin, unsigned int value);

#define FN_GPIO_SET_DS		gpio_set_data_strength

#define FN_ANALOG_READ 		analog_read
#define FN_ANALOG_WRITE 	analog_write

/**
 * @brief Fast GPIO 结构体
 * @note  支持普通 GPIO 与 I²C‑style open‑drain 输入，以及 PORTB/PORTC 的模拟寄存器配置
 */
typedef struct {
    volatile unsigned char *out_reg;      // GPIO 输出寄存器
    volatile unsigned char *in_reg;       // GPIO 输入寄存器
    volatile unsigned char *out_en_reg;   // 输出使能寄存器
    volatile unsigned char *in_en_reg;    // 输入使能寄存器
    unsigned char           high_mask;    // “1”位掩码
    unsigned char           low_mask;     // “0”位掩码
    unsigned char           analog_grp;   // true=PORTB/C 需配置模拟寄存器
    unsigned char           analog_addr;  // 模拟寄存器地址
    unsigned char           analog_set_val;   // 预计算：使能模拟输入时写入的值
} hal_fast_gpio_t;

/**
 * @brief  初始化 fast_gpio 结构
 * @param  fg         指向 hal_fast_gpio_t 的指针
 * @param  port_pin  PORTY_PIN(X)
 */
static inline void hal_fast_gpio_init(hal_fast_gpio_t *fg, unsigned char io)
{
	unsigned short port_pin = ((unsigned short)((unsigned short)((unsigned short)io & 0x00F0) << 4) | (unsigned short)(1 << (unsigned short)((unsigned short)io & 0x000F)));

    unsigned int grp = port_pin >> 8;      // 高 8 位：口组索引
    unsigned int off = grp << 3;           // 每组寄存器间距 8

    fg->out_reg    = (volatile unsigned char*)(GPIO_OUT_REG_BASE    + off);
    fg->in_reg     = (volatile unsigned char*)(GPIO_IN_REG_BASE     + off);
    fg->out_en_reg = (volatile unsigned char*)(GPIO_OUT_EN_REG_BASE + off);
    fg->in_en_reg  = (volatile unsigned char*)(GPIO_IN_EN_REG_BASE  + off);

    fg->high_mask  = (unsigned char)(port_pin & 0xFF);
    fg->low_mask   = (unsigned char)~(fg->high_mask);

    FN_GPIO_SET_DS(port_pin, 1);

    // 检测 PORTB / PORTC，需用模拟寄存器
    if (grp == AGPIO_GROUP1)
    {
    	fg->analog_grp  = 1;
    	fg->analog_addr = GPIO_AREG_GROUP1_IE;
    }
    else if (grp == AGPIO_GROUP2)
    {
    	fg->analog_grp  = 1;
    	fg->analog_addr = GPIO_AREG_GROUP2_IE;
    }
    else
    {
    	fg->analog_grp  = 0;
    }

    // 如果需要模拟寄存器，预读并计算写入值
    if (fg->analog_grp)
    {
        unsigned char v = FN_ANALOG_READ(fg->analog_addr);
        fg->analog_set_val = (v & fg->low_mask) | fg->high_mask;
    }
}

/**
 * @brief  设置引脚为输出或输入
 * @param  g       fast_gpio 对象
 * @param  output  true=输出, false=输入（open‑drain）
 */
static inline void hal_fast_gpio_dir(hal_fast_gpio_t *fg, unsigned char output)
{
    if (output)
    {
        // en out, ban in
        *fg->out_en_reg |=  fg->high_mask;
        *fg->in_en_reg  &=  fg->low_mask;
    }
    else
    {
        if (fg->analog_grp)
        {
            //gp1 & gp2 set analog reg
        	FN_ANALOG_WRITE(fg->analog_addr, fg->analog_set_val);
        }
        *fg->in_en_reg  |=  fg->high_mask;
        *fg->out_en_reg &=  fg->low_mask;
    }
}

/**
 * @brief  输出高
 */
static inline void hal_fast_gpio_set(hal_fast_gpio_t *fg)
{
	*fg->out_reg |= fg->high_mask;
}

/**
 * @brief  输出低
 */
static inline void hal_fast_gpio_clear(hal_fast_gpio_t *fg)
{
	*fg->out_reg &= fg->low_mask;
}

/**
 * @brief  输出翻转
 */
static inline void hal_fast_gpio_toggle(hal_fast_gpio_t *fg)
{
	*fg->out_reg ^= fg->high_mask;
}

/**
 * @brief  	    读取引脚输入电平
 * @return    0 或 1
 */
static inline unsigned char hal_fast_gpio_read(hal_fast_gpio_t *fg)
{
    return ((*fg->in_reg & fg->high_mask) != 0) ? 1 : 0;
}

#endif /* __HAL_FAST_GPIO_H__ */

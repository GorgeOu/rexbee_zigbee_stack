#ifndef __PWM_DRIVER_H__
#define __PWM_DRIVER_H__

/*****************************可用引脚*******************************************
 * PA0->PWM0_N
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

#define FREQUENCY_FACTOR    (4)
#define CLOCK_SYS_CLOCK_HZ 	(48000000)
#define CLOCK_PWM_CLOCK_HZ  (CLOCK_SYS_CLOCK_HZ / FREQUENCY_FACTOR)

extern unsigned short g_pwm_accuracy; //define in pwm_task

/**介绍：PWM初始化
* 参数： -
* 返回：-
*/
void app_pwm_timer_init(void);

/**介绍：设置pwm占空比以及频率(设置后自动启动pwm)
* 参数：  freq	   	  : PWM频率,范围184-47000HZ
* 		rgb_val(duty) :	PWM占空比,范围[0 ~ 预设精度]之间表示占空比0~100%
* 		index      	  :	PWM引脚索引,按照pin_def.h中的PWM内容从0开始,最多支持6个[0 ~ 5]
* 返回：-
*/
void app_v2_set_pwm_freq_duty(unsigned short freq, unsigned short rgb_val, unsigned char index);

/**介绍: 设置一对互补pwm占空比以及频率(设置后自动启动pwm)
*  参数: freq	   	   			: PWM频率, 范围184-47000HZ
* 		rgb_val(duty)			: PWM占空比,     范围[0 ~ 预设精度]之间表示占空比0~100%
* 		rgb_val_invert(duty)	: 互补PWM占空比,  范围[0 ~ 预设精度]之间表示占空比0~100%
* 		index      				: PWM引脚索引,    按照pin_def.h中的PWM内容从0开始,最多支持6个[0 ~ 5]
* 		index_invert      		: 互补PWM引脚索引, 按照pin_def.h中的PWM内容从0开始,最多支持6个[0 ~ 5]
*  返回：-
*/
void app_v2_set_invert_pwm_freq_duty(unsigned short freq,
									 unsigned short rgb_val,
									 unsigned short rgb_val_invert,
									 unsigned char  index,
									 unsigned char  index_invert);

/**介绍：索引开始指定PWM端口
*  参数： index : PWM引脚索引, 按照pin_def.h中的PWM内容从0开始,最多支持6个[0 ~ 5]
*  返回：-
*/
void app_v2_pwm_start(unsigned char index);

/**介绍：索引停止指定PWM端口
*  参数： index : PWM引脚索引, 按照pin_def.h中的PWM内容从0开始,最多支持6个[0 ~ 5]
*  返回：-
*/
void app_v2_pwm_stop(unsigned char index);

#endif

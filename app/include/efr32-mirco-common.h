#ifndef __EFR32_MICRO_COMMON_DEF__
#define	__EFR32_MICRO_COMMON_DEF__

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port A pins into a single number.
 */
#define PORTA_PIN(y) ((0u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port B pins into a single number.
 */
#define PORTB_PIN(y) ((1u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port C pins into a single number.
 */
#define PORTC_PIN(y) ((2u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port D pins into a single number.
 */
#define PORTD_PIN(y) ((3u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port E pins into a single number.
 */
#define PORTE_PIN(y) ((4u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port F pins into a single number.
 */
#define PORTF_PIN(y) ((5u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port G pins into a single number.
 */
#define PORTG_PIN(y) ((6u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port H pins into a single number.
 */
#define PORTH_PIN(y) ((7u << 4) | (y))

//PORTM for output virtual gpio  ('M' - 'A') 12
#define PORTM_PIN(y) ((12u << 4) | (y))

//PORTN for input  virtual gpio  ('N' - 'A') 13
#define PORTN_PIN(y) ((13u << 4) | (y))

//PORTO for input virtual gpio  ('O' - 'A') 14
#define PORTO_PIN(y) ((14u << 4) | (y))

#define  PA(x)               PORTA_PIN(x)
#define  PB(x)               PORTB_PIN(x)
#define  PC(x)               PORTC_PIN(x)
#define  PD(x)               PORTD_PIN(x)
#define  PE(x)               PORTE_PIN(x)
#define  PF(x)               PORTF_PIN(x)
#define  PG(x)               PORTG_PIN(x)
#define  PH(x)               PORTH_PIN(x)
#define  PM(x)               PORTM_PIN(x)
#define  PN(x)               PORTN_PIN(x)
#define  PO(x)               PORTO_PIN(x)

typedef enum {
  PORTA = 0,
  PORTB = 1,
  PORTC = 2,
  PORTD = 3,
  PORTE = 4,
  PORTF = 5,
  PORTM = 12, //vir out port part1 bit 0~15
  PORTN = 13, //vir in port part1 bit 0~15
  PORTO = 14, //vir in port part2 bit 15~31
} E_GPIO_PORT_TYPES;

#define _GPIO_P_MODEL_MODE0_DISABLED                    0x00000000UL                                        /**< Mode DISABLED for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_INPUT                       0x00000001UL                                        /**< Mode INPUT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_INPUTPULL                   0x00000002UL                                        /**< Mode INPUTPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_PUSHPULL                    0x00000004UL                                        /**< Mode PUSHPULL for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_PUSHPULLALT                 0x00000005UL                                        /**< Mode PUSHPULLALT for GPIO_P_MODEL */
#define _GPIO_P_MODEL_MODE0_WIREDAND                    0x00000008UL                                        /**< Mode WIREDAND for GPIO_P_MODEL */

#define _GPIO_P_MODEL_MODE0_PWM                   	 	0x0000000AUL                                        /**< Mode WIREDAND for PWM */

#define E_GPIO_PORT_MODE HalCommonGpioMode

typedef unsigned char HalCommonGpioMode;
enum
{
   GPIOCFG_UNUSE		 = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set. */
   GPIOCFG_IN     		 =  _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction. */
   GPIOCFG_IN_PUD        = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Push-pull output. */
   GPIOCFG_OUT           = _GPIO_P_MODEL_MODE0_PUSHPULL,
  /** Push-pull using alternate control. */
   GPIOCFG_OUT_ALT       =  _GPIO_P_MODEL_MODE0_PUSHPULLALT,
  /** Open-drain output. */
   GPIOCFG_OUT_OD        =  _GPIO_P_MODEL_MODE0_WIREDAND,

   GPIOCFG_OUT_L        = _GPIO_P_MODEL_MODE0_PUSHPULL | 0x000000F0UL,

   GPIOCFG_OUT_ALT_L    =  _GPIO_P_MODEL_MODE0_PUSHPULLALT | 0x000000F0UL,

   GPIOCFG_OUT_OD_L     =  _GPIO_P_MODEL_MODE0_WIREDAND | 0x000000F0UL,

   GPIOCFG_IN_PU_1M		= _GPIO_P_MODEL_MODE0_INPUTPULL | 0x000000F0UL,

   GPIOCFG_PWM		 	= _GPIO_P_MODEL_MODE0_PWM,
   GPIOCFG_N_PWM		= _GPIO_P_MODEL_MODE0_PWM | 0x000000F0UL,
};

#endif

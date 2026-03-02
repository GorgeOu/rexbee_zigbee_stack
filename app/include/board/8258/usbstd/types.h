/********************************************************************************************************
 * @file     types.h
 *
 * @brief    the file used to define the data types
 *
 * @author
 * @date     Oct. 8, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *           The information contained herein is confidential property of Telink
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *           Co., Ltd. and the licensee or the terms described here-in. This heading
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#ifndef __NORMAL_TYPES_H__
#define __NORMAL_TYPES_H__

#define BIT32(x) (((uint32_t) 1) << (x))

#define CLOCK_SYS_CLOCK_1US 		16
#define	CONV2_TICK(x)				(u32)(((u32)x) * (CLOCK_SYS_CLOCK_1US * 1000))
#define systemClockTime()			clock_time()

#define VAILD_PERIOD_TIME			(5)

#define PGM     const
#define PGM_P   const char *
#define PGM_PU  const unsigned char *

typedef unsigned char  int8u;
typedef unsigned short int16u;
typedef unsigned int   int32u;

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef int16_t coffee_page_t;

typedef unsigned char u8 ;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef int s32;
typedef unsigned int u32;

typedef long long s64;
typedef unsigned long long u64;

typedef int				intptr_t;
typedef unsigned int	uintptr_t;
typedef int             ptrdiff_t;
typedef int				intmax_t;
typedef unsigned int	uintmax_t;

typedef void (*fn_ptr)(u8*);

typedef u32  u24;
typedef s32	 s24;

// Generic Status return
typedef u8 status_t;
typedef u32 UTCTime;

typedef u32 arg_t;

#define MAX_INT32U_VALUE      (0xFFFFFFFFUL)
#define HALF_MAX_INT32U_VALUE (0x80000000UL)

/* LIMIT MACROS */
#define INT8_MIN    (-0x7f - 1)
#define INT16_MIN   (-0x7fff - 1)
#define INT32_MIN   (-0x7fffffff - 1)
#define INT64_MIN   (-0x7fffffffffffffff - 1)

#define INT8_MAX    0x7f
#define INT16_MAX   0x7fff
#define INT32_MAX   0x7fffffff
#define INT64_MAX   0x7fffffffffffffff

#define UINT8_MAX   0xff
#define UINT16_MAX  0xffff
#define UINT32_MAX  0xffffffff
#define UINT64_MAX  0xffffffffffffffff

#define INT_LEAST8_MIN    (-0x7f - 1)
#define INT_LEAST16_MIN   (-0x7fff - 1)
#define INT_LEAST32_MIN   (-0x7fffffff - 1)
#define INT_LEAST64_MIN   (-0x7fffffffffffffff - 1)

#define INT_LEAST8_MAX    0x7f
#define INT_LEAST16_MAX   0x7fff
#define INT_LEAST32_MAX   0x7fffffff
#define INT_LEAST64_MAX   0x7fffffffffffffff

#define UINT_LEAST8_MAX   0xff
#define UINT_LEAST16_MAX  0xffff
#define UINT_LEAST32_MAX  0xffffffff
#define UINT_LEAST64_MAX  0xffffffffffffffff

#define INT_FAST8_MIN     (-0x7f - 1)
#define INT_FAST16_MIN    (-0x7fff - 1)
#define INT_FAST32_MIN    (-0x7fffffff - 1)
#define INT_FAST64_MIN    (-0x7fffffffffffffff - 1)

#define INT_FAST8_MAX     0x7f
#define INT_FAST16_MAX    0x7fff
#define INT_FAST32_MAX    0x7fffffff
#define INT_FAST64_MAX    0x7fffffffffffffff

#define UINT_FAST8_MAX    0xff
#define UINT_FAST16_MAX   0xffff
#define UINT_FAST32_MAX   0xffffffff
#define UINT_FAST64_MAX   0xffffffffffffffff

#define INTPTR_MIN        (-0x7fffffff - 1)
#define INTPTR_MAX        0x7fffffff
#define UINTPTR_MAX       0xffffffff

#ifndef UNUSED_VAR

/**
 * @description Useful macro for avoiding compiler warnings related to unused
 * function arguments or unused variables.
 */
#define UNUSED_VAR(x) (void)(x)
#endif

enum{
  ZB_FALSE = 0,
  ZB_TRUE = 1
};

typedef u8 cId_t;

/**
 *  @brief Type definition for extended address
 */
typedef u8 addrExt_t[8];
typedef u8 extPANId_t[8];

typedef addrExt_t	extAddr_t;

typedef union {
	u16  shortAddr;
	addrExt_t extAddr;
}tl_zb_addr_t;

typedef union
{
	u32	srcId;
	addrExt_t gpdIeeeAddr;
}gpdId_t;

/**
 *  @brief Type definition for combined short/extended device address
 */
typedef struct
{
    union
    {
        u16         shortAddr;         //!< Short address
        addrExt_t   extAddr;           //!< Extended address
    } addr;
    u8  addrMode;                      //!< Address mode
} addr_t;

typedef struct
{
	u16 id;
    u8  mode;                      //!< Address mode
} pan_id_t;

#ifdef WIN32
#   ifndef FALSE
#        define FALSE 0
#    endif

#   ifndef TRUE
#        define TRUE 1
#    endif

#define PACK_1
#define CODE
#define __no_init
#define GENERIC

#define NULL_OK
#define INP
#define OUTP
#define UNUSED
#define ONLY
#define READONLY
#define SHARED
#define KEEP
#endif

#ifndef NULL
#define NULL 	0
#endif

#ifndef __cplusplus

typedef u8 bool;
typedef u8 boolean;

#ifndef FALSE
#define FALSE 	0
#endif
#ifndef TRUE
#define TRUE 	(!FALSE)
#endif

#define false     FALSE
#define true     TRUE

#elif defined WIN32

#ifndef FALSE
#define FALSE     0
#endif

#ifndef TRUE
#define TRUE      1
#endif

#endif

// There is no way to directly recognise whether a typedef is defined
// http://stackoverflow.com/questions/3517174/how-to-check-if-a-datatype-is-defined-with-typedef
#ifdef __GNUC__
typedef	u16	wchar_t;		
#endif

#ifndef WIN32
typedef u32 size_t;
#endif

#define U32_MAX ((u32)0xffffffff)
#define U16_MAX ((u16)0xffff)
#define U8_MAX ((u8)0xff)
#define U31_MAX ((u32)0x7fffffff)
#define U15_MAX ((u16)0x7fff)
#define U7_MAX ((u8)0x7f)


/*** Generic Status Return Values ***/
#define SUCCESS                   0x00
#define FAILURE                   0x01
#define INVALIDPARAMETER          0x02
#define INVALID_TASK              0x03
#define MSG_BUFFER_NOT_AVAIL      0x04
#define INVALID_MSG_POINTER       0x05
#define INVALID_EVENT_ID          0x06
#define INVALID_INTERRUPT_ID      0x07
#define NO_TIMER_AVAIL            0x08
#define NV_ITEM_UNINIT            0x09
#define NV_OPER_FAILED            0x0A
#define INVALID_MEM_SIZE          0x0B
#define NV_BAD_ITEM_LEN           0x0C


#define ADDR_MODE_NONE       0        //!< Address not present
#define ADDR_MODE_SHORT      2        //!< Short address
#define ADDR_MODE_EXT        3        //!< Extended address

/**
 * @brief Returns the low byte of the 32-bit value \c n as an \c uint8_t.
 */
#define BYTE_0(n)                    ((uint8_t)((n) & 0xFF))

/**
 * @brief Returns the second byte of the 32-bit value \c n as an \c uint8_t.
 */
#define BYTE_1(n)                    ((uint8_t)(BYTE_0((n) >> 8)))

/**
 * @brief Returns the third byte of the 32-bit value \c n as an \c uint8_t.
 */
#define BYTE_2(n)                    ((uint8_t)(BYTE_0((n) >> 16)))

/**
 * @brief Returns the high byte of the 32-bit value \c n as an \c uint8_t.
 */
#define BYTE_3(n)                    ((uint8_t)(BYTE_0((n) >> 24)))

/**
 * @brief Returns the low byte of the 16-bit value \c n as an \c uint8_t.
 */
#define LOW_BYTE(n)                     ((uint8_t)((n) & 0xFF))

/**
 * @brief Returns the high byte of the 16-bit value \c n as an \c uint8_t.
 */
#define HIGH_BYTE(n)                    ((uint8_t)(LOW_BYTE((n) >> 8)))

/**
 * @brief Returns the value built from the two \c uint8_t
 * values \c high and \c low.
 */
#define HIGH_LOW_TO_INT(high, low) (                              \
                                    (( (uint16_t) (high) ) << 8) +  \
                                    (  (uint16_t) ( (low) & 0xFF))  \
                                   )

/**
 * @brief Some platforms need to cast enum values that have the high bit set.
 */
#define SIGNED_ENUM

#define assert(condition)  \
  do { if (!(condition)) { while(1); } } while (0)


#define assertShow(condition, format, ...)  \
  do { CORE_ATOMIC_SECTION(if (!(condition)) { simPrintf("\r\n[ASSERT]%s, %d, ", __FILE__, __LINE__); simPrintf(format, ##__VA_ARGS__); while(1);) } } while (0)

#endif


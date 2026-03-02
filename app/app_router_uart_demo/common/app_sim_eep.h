/************************* (C) COPYRIGHT 2019 REXENSE TECH Copration *************************
* File Name        		: sim-eep.h
* Author             	: Yu xiaoQ
* Version            	: V1.0.0
* Date First Issued		: 2019/01/30
* Description        	: This file implementation sim eep process
*********************************************************************************************/
#if defined(DEFINEEEPARRAY) || defined(DEFINEEEPTYPE)
#if defined(DEFINEEEPTYPE)

#define DEFINE_BASIC_TOKEN		DEF_EEP_BASIC
#define DEFINE_INDEXED_TOKEN	DEF_EEP_INDEXED_BASIC
/*****************TOKEN ID**********************/
#if defined(DEFINEEEPTYPE)
#undef DEFINEEEPTYPE
#define DEFINETOKENID

#undef  DEF_EEP_INDEXED_BASIC
#undef  DEF_EEP_BASIC

#define DEF_EEP_INDEXED_BASIC(id, type, member, ...) TOKEN_##id,
#define DEF_EEP_BASIC(id,type,...) DEF_EEP_INDEXED_BASIC(id, type, 1, __VA_ARGS__)
enum
{
	#include "../app_sim_eep_assign.h"
	APP_SIM_EEP_ID_END = 0x7FF0,
};

#undef DEFINETOKENID
#undef DEF_EEP_INDEXED_BASIC
#undef DEF_EEP_BASIC
#define DEFINEEEPTYPE
#endif
/*****************END TOKEN ID**********************/

#include "../app_sim_eep_assign.h"

#else
#undef  DEF_EEP_INDEXED_BASIC
#undef  DEF_EEP_BASIC

#ifdef DEFINEEEPMEMASSIGN
#define DEF_EEP_INDEXED_BASIC(id, type, member, ...)

#define DEF_EEP_BASIC(id,type,...) DEF_EEP_INDEXED_BASIC(id, type, 1, __VA_ARGS__)
#endif

#ifdef DEFINEEEPDEFCONSTVALUE
#define DEF_EEP_INDEXED_BASIC(id, type, member, ...) \
		const type id##_def[] = {__VA_ARGS__} ;

#define DEF_EEP_BASIC(id,type,...) DEF_EEP_INDEXED_BASIC(id, type, 1, __VA_ARGS__)
#endif

#ifdef LOCALDEFCONSTVALUE
#define DEF_EEP_INDEXED_BASIC(id, type, member, ...) \
		{TOKEN_##id, sizeof(type), member, (uint8_t* )(uint32_t)(id##_def)},
		
#define DEF_EEP_BASIC(id,type,...) 	DEF_EEP_INDEXED_BASIC(id, type, 1, __VA_ARGS__)

#endif

#endif

#else
#ifndef __SIM_EEP_H__
#define	__SIM_EEP_H__

#undef  DEF_EEP_INDEXED_BASIC
#undef  DEF_EEP_BASIC

//left 3072 / 32 = 96
#include "../app_sim_eep_assign.h"
#define DEF_EEP_INDEXED_BASIC(id,type,m,v)
#define DEF_EEP_BASIC(id,type,v)

#define halCommonGetToken(data, x)	  	  				eeprom_read_data(x, 0, (uint8_t*)data)
#define halCommonSetToken(x, data)	  	  				eeprom_write_data(x, 0, (uint8_t*)data)

#define halCommonGetIndexedToken(data, x, index)		eeprom_read_data(x, index, (uint8_t*)data)
#define halCommonSetIndexedToken(x, index, data) 		eeprom_write_data(x, index, (uint8_t*)data)

#define halInternalGetMfgTokenData(data,x,index,len) 	eeprom_internal_read_data(x, 0, (uint8_t*)data, true, index, len)
#define halInternalSetMfgTokenData(x,data,index,len) 	eeprom_internal_write_data(x, 0, (uint8_t*)data, true, index, len)

bool eeprom_internal_read_data(uint16_t id, uint8_t read_index, uint8_t* context, bool internal_read, uint16_t data_index, uint16_t data_length);
bool eeprom_internal_write_data(uint16_t id, uint8_t write_index, uint8_t* context, bool internal_write, uint16_t data_index, uint16_t data_length);
bool eeprom_read_data(uint16_t id, uint8_t read_index, uint8_t* context);
bool eeprom_write_data(uint16_t id, uint8_t write_index, uint8_t* context);

#endif

#endif

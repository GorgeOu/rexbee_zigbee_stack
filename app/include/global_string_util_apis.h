#ifndef __GLOBAL_STRING_UTIL_APIS_H__
#define __GLOBAL_STRING_UTIL_APIS_H__

#include <stdarg.h>

void* memset(void* dest, int val, unsigned int length);
void* memcpy(void* out, const void * in, unsigned int length);
int memcmp(const void* m1, const void* m2, unsigned int length);

#ifndef MEMMOVE
#define MEMMOVE(out, in, length) 	memmove(out, in, length)
#endif

#ifndef MEMCOMPARE
#define MEMCOMPARE(m1, m2, length)  memcmp(m1, m2, length)
#endif

#ifndef MEMCOPY
#define MEMCOPY(out, in, length)	memcpy(out, in, length)
#endif

#ifndef MEMSET
#define MEMSET(dest, val, length)	memset(dest, val, length)
#endif

bool util_match_uart_command_fixed_length(const char* command, uint8_t* uart_data, uint16_t length);
bool util_match_uart_command(const char* command, uint8_t* uart_data);

#if defined(_USE_LIBC_STD_API_)
/* std string */
size_t strlen(const char* s);
size_t strnlen(const char* s, size_t n);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strchr(const char* s, int c);
char* strrchr(const char* s, int c);
char* strstr(const char* haystack, const char* needle);
char* strtok(char* str, const char* delim);

/* tiny printf */
int vsnprintf(char* buffer, size_t count, const char* format, va_list va);
int sprintf(char* buffer, const char* format, ...);
int snprintf(char* buffer, size_t count, const char* format, ...);

void hal_set_putchar_port(uint8_t port);
int vprintf(const char* format, va_list va);
int printf(const char* format, ...);
#endif

/* util string apis */
uint16_t util_strnlen(const char *str, uint16_t max_length);
int util_strncmp(const char* str1, const char* str2, uint16_t max_length);
char* util_strncpy(char *s, const char *t, uint16_t max_length);
char* util_strchr(const char *s, int c);
char* util_strstr(const char *haystack, const char *needle);
char* util_strncat(char* dest, const char* src, uint16_t max_length);
char* util_strtok(char* str, const char* delim);
void* util_memchr(const void* ptr, int value, uint16_t max_length);

uint8_t util_atod(uint8_t* data); //ascii -> dec   e.g. "100" -> 100
void util_htos(uint8_t* data, uint8_t* result, uint8_t length); //hex -> hex string		  e.g. {0x11, 0xAA, 0xBB}->"11aabb"
void util_htoS(uint8_t* data, uint8_t* result, uint8_t length); //hex -> hex string(caps) e.g. {0x11, 0xAA, 0xBB}->"11AABB"
void util_htoa(uint8_t byte, uint8_t result[2]); //hex -> ascii   e.g. 0xA1 -> "a1"
void util_htoA(uint8_t byte, uint8_t result[2]); //hex -> ascii(caps) e.g. 0xA1 -> "A1"
uint8_t util_atoh(uint8_t* data); //ascii -> hex  e.g. "A0" -> 0xA0

/* 	e.g.
 * 	uint8_t* content = "11223344";
 *  uint8_t result[4];
 * 	uint16_t result_size = util_array_atoh(result, content, 4);
 *  //result = {0x11, 0x22, 0x33, 0x44} / result_size = 4
 */
uint16_t util_array_atoh(uint8_t* result, uint8_t* contents, uint16_t array_size); //hex string -> array

uint8_t atoh_build_int8u(const uint8_t* contents);
uint16_t atoh_build_int16u(bool big_endian, const uint8_t* contents);
uint32_t atoh_build_int32u(bool big_endian, const uint8_t* contents);
#define build_int8u(contents)	((contents)[0])
uint16_t build_int16u(bool big_endian, const uint8_t* contents);
uint32_t build_int32u(bool big_endian, const uint8_t* contents);

void htoa_build_int8u(bool upper, bool big_endian, uint8_t data, uint8_t* result);
void htoa_build_int16u(bool upper, bool big_endian, uint16_t data, uint8_t* result);
void htoa_build_int32u(bool upper, bool big_endian, uint32_t data, uint8_t* result);

/* 	e.g.
 * 	uint8_t* str1 = "11223344";
 * 	int value1 = util_dec_string_to_signed_int(str1, 8);
 *  //value1 = 11223344;
 *  uint8_t* str2 = "-5566";
 * 	int value2 = util_dec_string_to_signed_int(str1, 5);
 *  //value2 = -5566;
 */
int util_dec_string_to_signed_int(uint8_t* str, uint8_t length);

uint32_t util_dectobcd(uint32_t dec);
bool util_get_build_date_time(const char* date, uint16_t* year, uint8_t* month, uint8_t* day);
uint32_t util_get_build_dec_time(const char* date);
uint32_t util_get_build_bcd_time(const char* date);
void util_get_build_ascii_time(const char* date, uint8_t* result);
uint32_t util_get_bcd_app_release_version(void);

double util_log(double x);
double util_log10(double x);

/* global util apis */
void util_reverse_array(void *arr, uint32_t arr_member_count, uint8_t element_size); //(a, 3, 2)[0x1111, 0x2222, 0x3333] -> [0x3333, 0x2222, 0x1111]
void util_swap_array(uint8_t *data, uint16_t length);
bool util_data_compare(uint8_t *data, uint16_t length, uint8_t char_cmp);
uint32_t util_random_in_range(uint32_t a, uint32_t b);
void util_gen_random_data(uint8_t* result, uint16_t length);
uint32_t util_int32u_rand(void);
uint8_t util_add8_check_sum(uint8_t* data, uint32_t length);   //add sum & 0xff
uint16_t util_add16_check_sum(uint8_t* data, uint32_t length); //add sum & 0xffff
uint32_t util_add32_check_sum(uint8_t* data, uint32_t length); //add sum

void util_get_md5(const uint8_t* data, uint32_t length, uint8_t* result); //md5sum result 16bytes

#endif

#ifndef __GLOBAL_NVM_APIS_H__
#define __GLOBAL_NVM_APIS_H__

/*  注：
 *  nvm数据块大小限制，所有tag数据块大小总和不得超过4032
 *
 *  e.g.
 *  假设用户定义以下数据块
 *  ATTR TOKEN : SIZE 1024
 *  TAG ID 1   : SIZE 1024
 *  TAG ID 2   : SIZE 1024
 *  x TAG ID 3 : SIZE 1024
 *  那么TAG ID 3将会写入失败，因为数据大小总和已经大于4032
 */

/**介绍：nvm功能注册，注册之后才可以使用attribute nvm & user nvm功能
* 		注 ：该注册函数需要在void app_post_token_init_callback(void);回调函数中调用
* 		1. 启用后在GENERATED_ATTRIBUTES里描述为 ATTRIBUTE_MASK_TOKENIZE 的属性, 会在设备属性表初始化后自动写入nvm存储的数据
* 		2. 启用后用户可以通过user nvm api写入/读取/删除自定义的持续化保存数据块
*  参数：无
*  返回：无
*
*  e.g.
*  #define GENERATED_ATTRIBUTES { \
*      { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE | ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }, \
*  }
*  声明完属性后调用write attr之后就会自动保存至token
*  初始化属性表时也会自动保存从token写入至属性表
*  void app_post_token_init_callback(void)
*  {
*  		app_nvm_attribute_storage_plugin_register();
*  }
*/
void app_nvm_attribute_storage_plugin_register(void);

/**介绍：写入用户nvm数据
*  参数：
*      tag_id 	  : 标签 : 0x0000 ~ 0xFEFF
*	   data	 	  : 写入数据缓存指针
*	   max_length : 期望写入的最大长度
*  返回：true - 写入成功 , false - 写入失败
*  e.g.
*	#define USER_DATA_1_TAG_ID	10
*	uint8_t write_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
*	bool result = app_set_user_nvm_data(USER_DATA_1_TAG_ID, write_data, sizeof(write_data));
*/
bool app_set_user_nvm_data(uint32_t tag_id, uint8_t* data, uint16_t length);

/**介绍：获取用户nvm数据
*  参数：
*      tag_id 	  : 标签 : 0x0000 ~ 0xFEFF
*	   data	 	  : 读取数据缓存指针
*	   max_length : 期望读取的最大长度
*	   data_length : 返回数据的长度
*  返回：true - 读取到有效数据 , false - 无有效数据
*  e.g.
*	#define USER_DATA_1_TAG_ID	10
*	uint8_t result_data[32];
*	uint16_t result_length = 0;
*	bool result = app_get_user_nvm_data(USER_DATA_1_TAG_ID, result_data, 32, &result_length);
*	app_serial_printf("\r\n[NVM]Get %d, result %d, data : %a", USER_DATA_1_TAG_ID, result, result_data, *result_length);
*/
bool app_get_user_nvm_data(uint32_t tag_id, uint8_t* data, uint16_t max_length, uint16_t* data_length);

/**介绍：删除用户nvm数据
*  参数：
*      tag_id 	  : 标签 : 0x0000 ~ 0xFEFF
*  返回：true - 删除成功 , false - 删除失败, 仅在tag id错误时会返回false, 其余情况都是true
*  e.g.
*	#define USER_DATA_1_TAG_ID	10
*	bool result = app_delete_user_nvm_data(USER_DATA_1_TAG_ID);
*/
bool app_delete_user_nvm_data(uint32_t tag_id);


/*
+--------------------------------------+ 0x00000
|               APP1                   |
|         (0x00000,  232K)             |
+--------------------------------------+ 0x3A000
|               NVM3                   |
|         (0x3A000,   20K)             |
+--------------------------------------+ 0x3F000
|              SCENE                   |
|         (0x3F000,    4K)             |
+--------------------------------------+ 0x40000
|               APP2                   |
|         (0x40000,  232K)             |
+--------------------------------------+ 0x7A000
|             STACK NVM                |
|         (0x7A000,   20K)             |
+--------------------------------------+ 0x7F000
|                CIB                   |
|         (0x7F000,    4K)             |
+--------------------------------------+ 0x80000
*/
/**介绍：nvm3功能注册，注册之后才可以使用attribute nvm & user nvm功能
* 		注 ：该注册函数需要在void app_post_token_init_callback(void);回调函数中调用
* 		1. 启用后在GENERATED_ATTRIBUTES里描述为 ATTRIBUTE_MASK_TOKENIZE 的属性, 会在设备属性表初始化后自动写入nvm存储的数据
* 		2. 启用后用户可以通过user nvm api写入/读取/删除自定义的持续化保存数据块
*  app_nvm3_attribute_storage_plugin_register 在512k模组下等效于 app_nvm3_attribute_storage_plugin_custom_size_register(0x3A000, 20 * 1024)
*  当调用app_nvm3_attribute_storage_plugin_custom_size_register时
*  参数： offset : flash偏移, 512k版本下建议使用 default 0x3A000, 1M版本可以自行配置
*  		size   : nvm3总大小, 512k版本下建议使用 default 20k, 1M版本可以自行配置
*  返回：无
*
*  e.g.
*  #define GENERATED_ATTRIBUTES { \
*      { 0x0000, ZCL_INT8U_ATTRIBUTE_TYPE, 1, (ATTRIBUTE_MASK_WRITABLE | ATTRIBUTE_MASK_TOKENIZE), { (uint8_t*)0x00 } }, \
*  }
*  声明完属性后调用write attr之后就会自动保存至token
*  初始化属性表时也会自动保存从token写入至属性表
*  void app_post_token_init_callback(void)
*  {
*  		app_nvm3_attribute_storage_plugin_register();
*  		//或调用app_nvm3_attribute_storage_plugin_custom_size_register(0x3A000, 20 * 1024);
*  }
*/
void app_nvm3_attribute_storage_plugin_custom_size_register(uint32_t offset, uint32_t size);
void app_nvm3_attribute_storage_plugin_register(void);

/**介绍：nvm3剩余可用空间
*  参数：-
*  返回：剩余大小（单位Byte）
*/
uint32_t app_nvm3_get_free_space(void);

/**介绍：写入用户nvm3数据
*  参数：
*      tag_id 	  : 标签 : 0x00000000 ~ 0xFFFFFFFF
*	   data	 	  : 写入数据缓存指针
*	   max_length : 期望写入的最大长度
*  返回：true - 写入成功 , false - 写入失败
*  e.g.
*	#define USER_DATA_1_TAG_ID	10
*	uint8_t write_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
*	bool result = app_set_user_nvm3_data(USER_DATA_1_TAG_ID, write_data, sizeof(write_data));
*/
bool app_set_user_nvm3_data(uint32_t tag_id, const uint8_t* data, uint32_t length);

/**介绍：获取用户nvm3数据
*  参数：
*      tag_id 	  : 标签 : 0x00000000 ~ 0xFFFFFFFF
*	   data	 	  : 读取数据缓存指针
*	   max_length : 期望读取的最大长度
*	   data_length : 返回数据的长度
*  返回：true - 读取到有效数据 , false - 无有效数据
*  e.g.
*	#define USER_DATA_1_TAG_ID	10
*	uint8_t result_data[32];
*	uint16_t result_length = 0;
*	bool result = app_get_user_nvm3_data(USER_DATA_1_TAG_ID, result_data, 32, &result_length);
*	app_serial_printf("\r\n[NVM]Get %d, result %d, data : %a", USER_DATA_1_TAG_ID, result, result_data, *result_length);
*/
bool app_get_user_nvm3_data(uint32_t tag_id, uint8_t* data, uint32_t max_length, uint32_t* data_length);

/**介绍：删除用户nvm3数据
*  参数：
*      tag_id 	  : 标签 : 0x00000000 ~ 0xFFFFFFFF
*  返回：true - 删除成功 , false - 删除失败, 仅在tag id错误时会返回false, 其余情况都是true
*  e.g.
*	#define USER_DATA_1_TAG_ID	10
*	bool result = app_delete_user_nvm3_data(USER_DATA_1_TAG_ID);
*/
bool app_delete_user_nvm3_data(uint32_t tag_id);

/**介绍：写入nvm3数据
*  参数：
*      key 	 	  : 任意key, 最大长度15
*      key_size   : key size, 例如"key1", key_size就为4
*	   data	 	  : 写入数据缓存指针
*	   max_length : 期望写入的最大长度
*  返回：true - 写入成功 , false - 写入失败
*  e.g.
*	#define USER_DATA_1_TAG_ID	"test_key_1"
*	uint8_t write_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
*	bool result = app_set_nvm3_data(USER_DATA_1_TAG_ID,  util_strnlen(USER_DATA_1_TAG_ID, 15), write_data, sizeof(write_data));
*	或者
*	uint8_t key[5] = {0x10, 0x20, 0x30, 0x40, 0x50};
*	uint8_t write_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
*	bool result = app_set_nvm3_data(key, sizeof(key), write_data, sizeof(write_data));
*
*/
bool app_set_nvm3_data(const char *key, uint8_t key_size, const uint8_t* data, uint32_t length);

/**介绍：获取nvm3数据
*  参数：
*      key 	 	  : 任意key, 最大长度15
*      key_size   : key size, 例如"key1", key_size就为4
*	   data	 	  : 读取数据缓存指针
*	   max_length : 期望读取的最大长度
*	   data_length : 返回数据的长度
*  返回：true - 读取到有效数据 , false - 无有效数据
*  e.g.
*	#define USER_DATA_1_TAG_ID	"test_key_1"
*	uint8_t result_data[32];
*	uint16_t result_length = 0;
*	bool result = app_get_nvm3_data(USER_DATA_1_TAG_ID, util_strnlen(USER_DATA_1_TAG_ID, 15), result_data, 32, &result_length);
*	app_serial_printf("\r\n[NVM]Get %a, result %d, data : %a", USER_DATA_1_TAG_ID, util_strnlen(USER_DATA_1_TAG_ID, 15), result, result_data, *result_length);
*/
bool app_get_nvm3_data(const char *key, uint8_t key_size, uint8_t* data, uint32_t max_length, uint32_t* data_length);

/**介绍：删除nvm3数据
*  参数：
*      key 	 	  : 任意key, 最大长度15
*      key_size   : key size, 例如"key1", key_size就为4
*  返回：true - 删除成功 , false - 删除失败, 仅在tag id错误时会返回false, 其余情况都是true
*  e.g.
*	#define USER_DATA_1_TAG_ID	"test_key_1"
*	bool result = app_delete_nvm3_data(USER_DATA_1_TAG_ID, util_strnlen(USER_DATA_1_TAG_ID, 15));
*/
bool app_delete_nvm3_data(const char *key, uint8_t key_size);

/**介绍：遍历获取全部nvm3记录条目
*  参数：
*      read_callback : 最新有效条目回调
*      user_data   	 : 回调参数
*  返回：-
*  e.g.
*   static void user_nvm3_read_callback(const char *key_id, uint8_t key_size, const uint8_t* data, uint32_t length, void* user_data)
*	{
*		uint8_t port = (uint8_t)(uintptr_t)user_data;
*
*		app_serial_port_printf(port, "\r\n[%b]%a", key_id, key_size, data, length);
*	}
*
*   app_nvm3_read_all_entries(user_nvm3_read_callback, (void* )(uintptr_t)port);
*/
void app_nvm3_read_all_entries(void (*read_callback)(const char *key_id, uint8_t key_size, const uint8_t* data, uint32_t length, void* user_data), void* user_data);

/**介绍：遍历获取全部nvm3记录条目(含历史记录条目)
*  参数：
*      read_callback : 有效条目回调（含历史记录条目）
*      user_data   	 : 回调参数
*  返回：-
*  e.g.
*   static void user_nvm3_read_callback(const char *key_id, uint8_t key_size, const uint8_t* data, uint32_t length, void* user_data)
*	{
*		uint8_t port = (uint8_t)(uintptr_t)user_data;
*
*		app_serial_port_printf(port, "\r\n[%b]%a", key_id, key_size, data, length);
*	}
*
*   app_nvm3_read_all_entries_with_history(user_nvm3_read_callback, (void* )(uintptr_t)port);
*/
void app_nvm3_read_all_entries_with_history(void (*read_callback)(const char *key_id, uint8_t key_size, const uint8_t* data, uint32_t length, void* user_data), void* user_data);

#endif

#ifndef __GLOBAL_BINDING_MGMT_APIS_H__
#define __GLOBAL_BINDING_MGMT_APIS_H__

/*  遍历获取binding table的实现
 *	-----------------------------------------------------------------------------------
 *	方式 1 :
 *  stack_ram_binding_table_init();
 *
 *  for(uint8_t i = 0; i < app_get_binding_table_size(); i++)
 *  {
 *  	uint8_t dest_ep; //return dest ep
 *
 *      if(app_find_binding_use_ram(i, find_cluster_id, source_ep, &dest_ep) != 0xffff)
 *      {
 *			uint16_t binding_node_id = stackGetBindingRemoteNodeId(i);
 *
 *			if(binding_node_id != 0xffff)
 *			{
 *				//...
 *			}
 *      }
 *  }
 *  -----------------------------------------------------------------------------------
 *  方式2 :
 *  EmberBindingTableEntry entry;
 *
 *  stack_ram_binding_table_init();
 *
 *  for(uint8_t i = 0; i < app_get_binding_table_size(); i++)
 *  {
 *		if(stackGetRamBinding(i, &entry) == EMBER_SUCCESS)
 *		{
 *			if( (binding.type == EMBER_UNICAST_BINDING) && ... )
 *			{
 *				uint16_t binding_node_id = stackGetBindingRemoteNodeId(i);
 *
 *				if(binding_node_id != 0xffff)
 *				{
 *					//...
 *				}
 *			}
 *		}
 *	}
 *  -----------------------------------------------------------------------------------
 *  方式3 :
 *	使用api app_get_ram_binding_table_entry, 具体参照app_get_ram_binding_table_entry接口说明
 *	-----------------------------------------------------------------------------------
 */

/**介绍：预载入binding table
 *
 */
void stack_ram_binding_table_init(void);

/**介绍：根据索引号获取binding table内容
 * 参数：...
 * 返回：EmberStatus
 */
EmberStatus stackGetRamBinding(uint8_t index, EmberBindingTableEntry *result);

/**介绍：根据索引号获取binding node id
 * 参数：...
 * 返回：node id
 */
uint16_t stackGetBindingRemoteNodeId(uint8_t index);

/**介绍：获取binding table大小
 * 参数：无
 * 返回：binding table大小
 */
#define app_get_binding_table_size stack_get_binding_table_size
uint8_t stack_get_binding_table_size(void);

/**介绍：遍历获取binding table entry
*  参数：
*      ignore_inactive_entry 		 : true - 跳过无效记录, false - 不跳过无效记录
*	   get_binding_table_callback	 : binding entry回调, 返回true终止查询，返回false继续查询下一条
*  返回：无
*  e.g.
*  bool get_binding_table_callback(uint8_t index, EmberBindingTableEntry* entry, uint16_t node)
*  {
*	  return false; //keep find next entry
*  }
*
*  app_get_ram_binding_table_entry(true, user_get_binding_table_callback);
*/
void app_get_ram_binding_table_entry(bool ignore_inactive_entry,
									 bool* get_binding_table_callback(uint8_t index,
											 	 	 	 	 	 	  EmberBindingTableEntry* entry,
											 	 	 	 	 	 	  uint16_t node));
/**介绍：新增binding
 * 参数：binding entry ptr
 * 返回：EmberStatus
 */
EmberStatus stackAddBindingEntry(EmberBindingTableEntry *value);

/**介绍：根据index删除binding
 * 参数：...
 * 返回：EmberStatus
 */
EmberStatus stackDeleteBinding(uint8_t index);

/**介绍：清空binding table
 * 		注：离网时协议栈默认删除binding table, 如果不希望协议栈自动删除binding table，
 * 		       可以手动在初始化时调用stack_set_clear_binding_table_after_leave_enable(false)禁用协议栈离网删除binding table
 * 参数：无
 * 返回：EmberStatus
 */
EmberStatus stackClearBindingTable(void);

/**介绍：应用无线binding处理回调，在收到add binding或del binding命令后触发以下注册回调
 * 参数：add_binding_permission_callback : 收到add binding后触发的回调函数，回调返回EMBER_SUCCESS则允许后续的新增处理，返回其他为应用不允许新增
 * 		remove_binding_permission_callback : 收到del binding后触发的回调函数，回调返回EMBER_SUCCESS则允许后续的删除处理，返回其他为应用不允许删除
 * 返回：-
 * e.g.
 * static EmberStatus user_add_binding_permission_callback(EmberBindingTableEntry* entry)
 * {
 * 	   if(...)
 * 	   {
 * 	   	   return EMBER_SUCCESS;
 * 	   }
 *
 * 	   return EMBER_ERR_FATAL;
 * }
 *
 * app_remote_binding_permission_callback_register(user_add_binding_permission_callback, NULL);
 */
void app_remote_binding_permission_callback_register(EmberStatus (*add_binding_permission_callback)(EmberBindingTableEntry* entry),
													 EmberStatus (*remove_binding_permission_callback)(EmberBindingTableEntry* entry));

#endif

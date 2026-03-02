
#ifndef __ZCL_ATTR_DESC_H__
#define __ZCL_ATTR_DESC_H__

#define ZCL_GLOBAL_SERVER_ATTR_DESC(endpoint, cluster, attribute, pre_write_attr_cb, post_write_attr_cb)		\
		{ {endpoint, 0 , cluster , attribute , 0x0000}, pre_write_attr_cb, post_write_attr_cb }

#define ZCL_MFG_SERVER_ATTR_DESC(endpoint, cluster, attribute, pre_write_attr_cb, post_write_attr_cb, mfg_code)		\
		{ {endpoint, ATTRIBUTE_MASK_MANUFACTURER_SPECIFIC , cluster , attribute , mfg_code} , pre_write_attr_cb , post_write_attr_cb }

#define ZCL_GLOBAL_CLIENT_ATTR_DESC(endpoint, cluster, attribute, pre_write_attr_cb, post_write_attr_cb)		\
		{ {endpoint, ATTRIBUTE_MASK_CLIENT , cluster , attribute , 0x0000}, pre_write_attr_cb, post_write_attr_cb }

#define ZCL_MFG_CLIENT_ATTR_DESC(endpoint, cluster, attribute, pre_write_attr_cb, post_write_attr_cb, mfg_code)		\
		{ {endpoint, ATTRIBUTE_MASK_CLIENT | ATTRIBUTE_MASK_MANUFACTURER_SPECIFIC , cluster , attribute , mfg_code} , pre_write_attr_cb , post_write_attr_cb }





//deprecated marco
#define ZCL_MFG_SERVER_CLIENT_DESC ZCL_MFG_CLIENT_ATTR_DESC
//

#endif // __ZCL_ATTR_DESC_H__

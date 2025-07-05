/**
 * @file base_lock_conversion.h
 * @author chenyg@tuya.com
 * @brief base conversion
 * @version 1.0
 * @date 2021-09-08
 * @copyright Copyright (c) tuya.inc 2021
 * A service that supports the password base conversion
 */

#ifndef __SVC_LOCK_BASE_CONVERSION_H__
#define __SVC_LOCK_BASE_CONVERSION_H__


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_com_api.h"

#define BASE_MSG_KEY "base_msg_key"

/**
* @brief Get the state that if enable password base conversion
* @return init_flag
*/

BOOL_T tuya_base_conversion_state(VOID);

/**
* @brief Get the base that if enable password base conversion
* @param[out] base  the password number base
* @param[out] offset  The password number start value
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_base_conversion_get(OUT UCHAR_T *base, OUT UCHAR_T *offset);
OPERATE_RET delete_base_conversion(VOID);
/**
* @brief Set the password base and start value
* @param[in] base  the password number base
* @param[in] offset  The password number start value
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_base_conversion_init(IN UCHAR_T base, IN UCHAR_T offset);

/**
* @brief Get the base that if enable password base conversion
* @param[out] base  the password number base
* @param[out] offset  The password number start value
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_base_conversion_get(OUT UCHAR_T *base, OUT UCHAR_T *offset);

/**
* @brief Converts the source number array to specified base number array
* @param[in] is_ascii  The source array number is ASCII code or integer
* @param[in] source_array  The source array pointer
* @param[in] source_array_len  The source array len
* @param[out] object_array  The object array pointer
* @param[out] object_array_len  The object array len
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_base_conversion_src2obj(IN BOOL_T is_ascii,
        IN UCHAR_T *source_array, IN  UCHAR_T source_array_len,
        OUT UCHAR_T *object_array, OUT UCHAR_T *object_array_len);



#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SVC_LOCK_BASE_CONVERSION_H__


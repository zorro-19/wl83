/**
 * @file tbl_lock_dynamic_pw.h
 * @author chenyg@tuya.com
 * @brief Lock dynamic password verify function
 * @version 1.0
 * @date 2021-07-17
 * @copyright Copyright (c) tuya.inc 2021
 */

#ifndef __SVC_LOCK_DYNAMIC_PW_H__
#define __SVC_LOCK_DYNAMIC_PW_H__


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_com_api.h"

typedef enum {
    DYN_PASS_OK = 0,
    DYN_PASS_ERR,
    DYN_PASS_NO_ACTIVE,
    DYN_PASS_LEN_ERR,
} TY_DYNAMIC_PW_RET_E;

typedef struct {
    INT_T   year; // start 1990
    INT_T   mon;  // 0-11
    INT_T   day;  // 1-31
    INT_T   hour; // 0-11
    INT_T   min;  // 0-59
    INT_T   sec;  // 0-59
} TY_DYNAMIC_PW_TIME_S;

typedef struct {
    TY_DYNAMIC_PW_TIME_S    time;       /*the stantard format time*/
    UCHAR_T                 pw_len;     /*len of the password*/
    UCHAR_T                 *password;   /*the ASCII of password*/
} TY_DYNAMIC_PW_INFO_S;


/**
 * @brief  Verify the validity of the dynamic password
 * @param  p_pw_info: The struct of dynamic password and current time
 * @param  p_ret: The result of valify
 * @return Function operation result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_lock_dynamic_pw_verify(IN TY_DYNAMIC_PW_INFO_S *p_pw_info, OUT TY_DYNAMIC_PW_RET_E *p_ret);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SVC_LOCK_DYNAMIC_PW_H__


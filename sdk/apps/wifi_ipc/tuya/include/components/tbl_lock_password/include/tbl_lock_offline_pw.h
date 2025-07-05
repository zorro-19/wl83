/**
 * @file tbl_lock_offline.h
 * @author chenyg@tuya.com
 * @brief offline password
 * @version 1.0
 * @date 2021-08-24
 * @copyright Copyright (c) tuya.inc 2021
 * A service that supports the offline password function for the lock
 */


#ifndef __SVC_LOCK_OFFLINE_PW_H__
#define __SVC_LOCK_OFFLINE_PW_H__


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_com_api.h"
typedef enum {
    RESULT_SUCC = 0,
    RESULT_FAILED,
} TY_OFFLINE_PW_RET_T;

typedef enum {
    RET_TYPE_TIME       = 0x00,     //reusable password
    RET_TYPE_ONCE       = 0x01,     //one-off password
    RET_TYPE_CLEAR_ONE  = 0x02,     //clear one password
    RET_TYPE_CLEAR_ALL  = 0x04,     //clear all password
    RET_TYPE_TIME_FIRST = 0x10,     //password first time to activate
    RET_TYPE_ERR        = 0xFF,     //check error
} TY_OFFLINE_PW_RET_TYPE_T;


typedef struct {
    INT_T   year; // start 1990
    INT_T   mon;  // 0-11
    INT_T   day;  // 1-31
    INT_T   hour; // 0-11
    INT_T   min;  // 0-59
    INT_T   sec;  // 0-59
} TY_OFFLINE_PW_TIME_S;

typedef struct {
    TY_OFFLINE_PW_TIME_S time;
    UCHAR_T     pw_len;
    UCHAR_T     *pw;
} TY_OFFLINE_PW_INFO_S;

typedef struct {
    TY_OFFLINE_PW_RET_T   ret;
    TY_OFFLINE_PW_RET_TYPE_T   type;
    UCHAR_T   decode_len;
    UCHAR_T   decode[16];
} TY_OFFLINE_PW_RESULT_S;

/**
* @brief Verify whether the password is valid
* @param[in] active_time  The device activation time
* @param[in] p_pw_info  The original password info struct pointer
* @param[inout] p_result  Pointer to the password verification structure result
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_svc_lock_offline_pw_check(IN UINT_T active_time, IN TY_OFFLINE_PW_INFO_S *p_pw_info, INOUT TY_OFFLINE_PW_RESULT_S *p_result);

/**
* @brief Initialize the offline password list and structure
* @param[in] max_num  Max number of offline passwords
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_svc_lock_offline_pw_init(IN UINT_T max_num);

/**
* @brief Clear all offline password records and information
* @return Function Operation Result  OPRT_OK is ok other is fail
*/
OPERATE_RET tuya_svc_lock_offline_pw_deinit(VOID);



#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SVC_LOCK_OFFLINE_PW_H__


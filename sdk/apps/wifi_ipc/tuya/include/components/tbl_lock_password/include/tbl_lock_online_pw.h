/**
 * @file tbl_lock_online_pw.h
 * @author chenyg@tuya.com
 * @brief
 * @version 1.0
 * @date 2021-07-06
 * @copyright Copyright (c) tuya.inc 2021
 * lock online password function
 */

#ifndef __SVC_LOCK_ONLINE_PW_H__
#define __SVC_LOCK_ONLINE_PW_H__


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_com_api.h"
#define TY_SVC_LOCK_ONLINE_PW_TIME_LEN      6
#define TY_SVC_LOCK_ONLINE_PW_MAX_LEN       16
#define TY_SVC_LOCK_ONLINE_PW_SCHEDULE_MAX  3

typedef struct {
    UCHAR_T  allday;        /*0:The password is valid at the specified time 1:password is valid all day*/
    UCHAR_T  start_hour;
    UCHAR_T  start_min;
    UCHAR_T  end_hour;
    UCHAR_T  end_min;
    UCHAR_T  week;          /*bit0:Sunday bit1:Monday ... bit6:Saturday*/
} TY_PW_SCHEDULE_S;

typedef struct {
    UCHAR_T             cnt;
    TY_PW_SCHEDULE_S    info[TY_SVC_LOCK_ONLINE_PW_SCHEDULE_MAX];
} TY_PW_SCHEDULE_ARR_S;

typedef struct {
    INT_T   year; // start 1990
    INT_T   mon;  // 0-11
    INT_T   day;  // 1-31
    INT_T   hour; // 0-11
    INT_T   min;  // 0-59
    INT_T   sec;  // 0-59
} TY_ONLINE_PW_TIME_S;

typedef struct {
    UCHAR_T pw_len;         /*len of the password*/
    UINT_T num;            /*number of the password*/
    UCHAR_T one_off;        /*0:unlimited 1:use only once*/
    UCHAR_T state;          /*0:the password is valid 1:the password had deleted by app*/
    TY_ONLINE_PW_TIME_S start_time;     /* green time */
    TY_ONLINE_PW_TIME_S end_time;       /* green time */
    UCHAR_T password[TY_SVC_LOCK_ONLINE_PW_MAX_LEN];        /*the ascii code of the password*/
    TY_PW_SCHEDULE_ARR_S schedule;
} TY_PW_INFO_S;

/**
 * @brief  The callback function of get online password result
 * @param  ret: True get online password success, False get online passowrd fail
 * @param  pw_cnt: the number of online passowrd return from cloud
 * @param  pw_info: the struct polinter of online password information
 * @return void
 */
typedef VOID (*ONLINE_PW_RESULT_CB)(IN BOOL_T ret, IN UCHAR_T pw_cnt, IN TY_PW_INFO_S *pw_info);

/**
 * @brief  Online password function get interface
 * @param  None
 * @return Function operation result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_lock_online_pw_get_pw_list(IN ONLINE_PW_RESULT_CB callback);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SVC_LOCK_ONLINE_PW_H__


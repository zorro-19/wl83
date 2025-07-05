/**
 * @file    tbl_lock_dp_report.h
 * @author  mengjinlong@tuya.com
 * @brief   tuya dp report include recorded data
 * @version 1.0
 * @date    2021-10-20
 * @copyright Copyright (c) tuya.inc 2020.
 */
#ifndef _SVC_LOCK_DP_REPORT_H
#define _SVC_LOCK_DP_REPORT_H


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_com_api.h"
#include "tuya_iot_wifi_api.h"
#include "uni_time.h"
#ifdef  __SVC_LOCK_DP_REPORT_GLOBALS
#define __SVC_LOCK_DP_REPORT_EXT
#else
#define __SVC_LOCK_DP_REPORT_EXT extern
#endif

#define TY_SINGLE_RECORD_MAX_LEN                   56u
#define TY_RECORD_NUM_MAX                          20u

typedef enum {
    DP_TYPE_RAW		= 0,                /* tuya datapoint type raw */
    DP_TYPE_BOOL	= 1,                /* tuya datapoint type bool */
    DP_TYPE_VALUE	= 2,                /* tuya datapoint type value */
    DP_TYPE_STRING	= 3,                /* tuya datapoint type string */
    DP_TYPE_ENUM	= 4,                /* tuya datapoint type enum */
    DP_TYPE_BITMAP	= 5,                /* tuya datapoint type bitmap */
    TY_DP_TYPE,
} TY_LOCK_DP_TYPE_E;

typedef enum {
    TIME_TYPE_VOID	 = 0,               /* tuya time type null */
    TIME_TYPE_LOCAL	 = 1,               /* tuya time type local */
    TIME_TYPE_GREEKN = 2,               /* tuya time type green */
} TY_LOCK_TIME_TYPE_E;

typedef struct {
    TY_LOCK_TIME_TYPE_E   type;         /* tuya time type*/
    POSIX_TM_S time;                    /* tuya time, if type is TIME_TYPE_VOID, time is invalid*/
} DP_TIME_S;

typedef struct {
    UCHAR_T			    dpid;	        /* tuya datapoint id */
    TY_LOCK_DP_TYPE_E	type;	        /* tuya datapoint type */
    WORD_T			    data_len;	    /* tuya datapoint len */
    UCHAR_T			    *data;	        /* tuya datapoint data */
} TY_LOCK_DP_S;

/**
 * Init tuya lock datapoint report.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_init(VOID);

/**
 * Init tuya lock datapoint report thrd stack.  must use befor tuya_svc_lock_dp_report_init,otherwise set failure.  default 3096
 * use becareful ,stack too small ,thrd will  run failed
 * @return null
 */
__SVC_LOCK_DP_REPORT_EXT \
VOID tuya_svc_lock_dp_report_thrd_stack_set(UINT_T stack_size);
/**
 * Tuya datapoint wil be reported synchronously.
 * @param  dp_data[]    datapoint.
 * @param  dp_data_num  datapoint number.
 * @param  time         the time of datapoint.
 * @param  timeout      time out,unit s.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_syn(IN TY_LOCK_DP_S dp_data[], IN UINT_T dp_data_num, DP_TIME_S *time, IN UINT_T timeout);

/**
 * Tuya datapoint wil be reported asynchronously.
 * @param  dp_data[]    datapoint.
 * @param  dp_data_num  datapoint number.
 * @param  time         the time of datapoint.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_asyn(IN TY_LOCK_DP_S dp_data[], IN UINT_T dp_data_num, DP_TIME_S *time);

/**
 * Tuya datapoint wil be reported synchronously, and it will be stored when sending fails.
 * @param  dp_data[]    datapoint.
 * @param  dp_data_num  datapoint number.
 * @param  time         the time of datapoint.
 * @param  timeout      time out,unit s.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_with_record_syn(IN TY_LOCK_DP_S dp_data[], IN UINT_T dp_data_num, DP_TIME_S *time, IN UINT_T timeout);

/**
 * Tuya datapoint wil be reported asynchronously, and it will be stored when sending fails.
 * @param  dp_data[]    datapoint.
 * @param  dp_data_num  datapoint number.
 * @param  time         the time of datapoint.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_with_record_asyn(IN TY_LOCK_DP_S dp_data[], IN UINT_T dp_data_num, DP_TIME_S *time);

/**
 * Tuya one datapoint stored in the flash wil be reported synchronously, and it will be deleted when sending success.
 * @param  timeout      time out,unit s.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_one_flash_record_syn(IN UINT_T timeout);

/**
 * Tuya one datapoint stored in the flash wil be reported asynchronously, and it will be deleted when sending success.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_dp_report_one_flash_record_asyn(VOID);


/**
 * Get the number of datapoints in the flash.
 * @return the number of datapoints in the flash
 */
__SVC_LOCK_DP_REPORT_EXT \
UINT_T tuya_svc_lock_get_flash_record_num(VOID);

/**
 * clean the datapoints in the flash.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__SVC_LOCK_DP_REPORT_EXT \
OPERATE_RET tuya_svc_lock_clr_flash_record(VOID);

#ifdef __cplusplus
}
#endif

#endif

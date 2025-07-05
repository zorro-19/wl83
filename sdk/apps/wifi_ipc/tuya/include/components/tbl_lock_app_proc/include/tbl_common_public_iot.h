/**
 * @file    ty_uart_public_iot.h
 * @author  fengzhiquan@tuya.com
 * @brief   tuya iot os handle
 * @version 1.0
 * @date    2021-07-27
 * @copyright Copyright (c) tuya.inc 2020
 * Provide data point analysis, status callback and other related functions.
 */
#ifndef _TBL_COMMON_PUBLIC_IOT_H
#define _TBL_COMMON_PUBLIC_IOT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "gw_intf.h"
#include "tbl_lock_dp_report.h"
#ifdef __TY_UART_PUBLIC_IOT_GLOBALS
#define __TY_UART_PUBLIC_IOT_EXT
#else
#define __TY_UART_PUBLIC_IOT_EXT extern
#endif

#define APP_VERSION_LEN			16
#define FIRM_KEY_LEN			20

typedef struct {
    CHAR_T	firmware_key[FIRM_KEY_LEN + 1];			/* tuya firmware key */
    CHAR_T	firmware_version[SW_VER_LEN + 1];		/* tuya firmware version information */
    CHAR_T	product_key[PRODUCT_KEY_LEN + 1];		/* tuya product key */
    GW_WF_CFG_MTHD_SEL	cfg_mode;					/* tuya wifi operating mode */
    GW_WF_START_MODE	start_mode;					/* tuya wifi initialization mode */
    CHAR_T	app_sw_version[APP_VERSION_LEN + 1];	/* tuya mcu firmware version information */
} TY_IOT_INFO_S;

typedef enum {
    WIFI_DATA_ASYNC_UP,
    WIFI_DATA_SYNC_UP,
} TY_WIFI_UP_TYPE_E;


typedef struct {
    UCHAR_T			dpid;	/* tuya datapoint id */
    TY_LOCK_DP_TYPE_E	type;	/* tuya datapoint type */
    WORD_T			len;	/* tuya datapoint len */
    UCHAR_T			*data;	/* tuya datapoint data */
} TY_DATAPOINT_DATA_S;

/**
 * receive datapoint callback.
 * @param  datapoint   datapoint include id,type,len,data.
 * @return none
 */
typedef VOID (*TY_DEV_DP_CB)(IN CONST TY_DATAPOINT_DATA_S *datapoint);

typedef struct {
    GW_STATUS_CHANGED_CB	gw_status_cb;	/* tuya gateway status changed callback */
    GW_UG_INFORM_CB		gw_ug_cb;			/* tuya gateway ota firmware available nofity callback */
    GW_RESET_IFM_CB		gw_reset_cb;		/* tuya gateway restart callback */
    TY_DEV_DP_CB		ty_dev_dp_recv_cb;	/* tuya dp info cmd callback */
    GET_WF_NW_STAT_CB	wf_nw_stat_cb;		/* tuya network check callback (wifi version) */
    GW_UG_INFORM_CB		pre_gw_ug_cb;	    /* tuya gateway ota firmware available pre nofity callback. */
} TY_IOT_CB_S;

/**
 * tuya uart cloud init.
 * @param  p_iot_info   iot configuration information
 * @param  ty_iot_cb   tuya iot receive and notify callback
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
__TY_UART_PUBLIC_IOT_EXT \
OPERATE_RET tuya_uart_cloud_init(IN TY_IOT_INFO_S *p_iot_info, IN TY_IOT_CB_S ty_iot_cb);


#ifdef __cplusplus
}
#endif

#endif

/***********************************************************
*  File: tuya_device.h
*  Author: mjl
*  Date: 20210507
***********************************************************/
#ifndef _TUYA_DEVICE_H
#define _TUYA_DEVICE_H

#include "tuya_cloud_types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define FIRM_KEY "keyn87hvg4jymcxd"

#define TY_USER_RECV_MAX 1200   //2048 /*数据接收缓存buf最大大小，单位Byte */

#define SN_CFG_TYPE_PARAM_E             "sn_param"
#define PID_CFG_PARAM_E                 "pid_key"

#define TY_USER_UART_ "TUYA_UART_0"

#ifdef __cplusplus
}
#endif

#endif

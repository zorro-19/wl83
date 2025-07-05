/***********************************************************
*  File: tbl_common_ota.h
*  Author: mengjinlong
*  Date: 201211101
***********************************************************/
#ifndef _TUYA_OTA_H
#define _TUYA_OTA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tbl_lock_mcu_ota.h"
#include "tdl_com_dev_mange.h"



OPERATE_RET tuya_kiwi_ota_service_init(IN TY_TRANS_HANDLE_S  trans_cfg);
INT_T pre_gw_ug_kiwi_proc(IN CONST FW_UG_S *fw);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/**
 * @file tbl_mcu_ota.h
 * @author wangwei@tuya.com
 * @brief semaphore
 * @version 1.0
 * @date 2021-03-30
 * @copyright Copyright (c) tuya.inc 2021
 * MCU upgrades services
 */
#ifndef __SVC_MCU_OTA_H__
#define __SVC_MCU_OTA_H__

#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_com_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OTA_PACK_GO_ON = 0,  /*Continue to drag the package*/
    OTA_PACK_WAIT,   /*Waiting for confirmation notice*/
} TY_OTA_PACK_E;

typedef enum {
    POST_SUCCESS = 0,     /*Continue to update the packet and confirm success*/
    POST_FAIL,        /*Continue to upgrade packet confirmation failed*/
} TY_OTA_POST_RESULT_E;

typedef enum {
    OTA_SUCCESS = 0,     /*Continue to update the packet and confirm success*/
    OTA_FAIL,        /*Continue to upgrade packet confirmation failed*/
} TY_OTA_END_STATUS_E;

typedef struct {
    OPERATE_RET(*iot_dev_ota_start_cb)(IN CONST FW_UG_S *p_ug_info, OUT TY_OTA_PACK_E *action_type);                           /*Begin the escalation notification callback*/
    OPERATE_RET(*iot_dev_ota_data_cb)(IN CONST UCHAR_T *data, IN CONST UINT_T len, IN UINT_T offset, OUT TY_OTA_PACK_E *action_type);           /*Upgrade the data callback*/
    OPERATE_RET(*iot_dev_ota_end_sta_cb)(IN TY_OTA_END_STATUS_E ota_status, IN UINT_T offset);                                                  /*The MCU upgrade completes the callback function*/
} TY_OTA_CB_HANDLE_S;

/**
 * MCU upgrade service initialization
 * @param  handle_cb Upgrade data callback function registration parameters
 * @param  pack_len  The length of data transferred to the user per pull packet swap
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_mcu_ota_serve_init(IN TY_OTA_CB_HANDLE_S handle_cb, IN UINT_T pack_len);

/**
 * Inform the MCU to upgrade and continue to pull packets,while choice OTA_PACK_WAIT
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_mcu_ota_wait_type_post(IN TY_OTA_POST_RESULT_E result);

/**
 * Start the MCU upgrade service, input parameters need to be obtained in the IOT specified callback
 * @param  p_ug_info Information about the upgraded file
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_mcu_ota_serve_start(IN CONST FW_UG_S *p_ug_info);

/**
 * Upgrade the packet processing callback function
 * Rereport the changed MCU version number after the system upgrade
 * HTTP report will start after 1S after the interface is used. If it fails, 5S retry
 * @param  p_mcu_ver Upgraded file information pointer
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_mcu_ota_ver_report_syn(IN CONST CHAR_T *p_mcu_ver);

/**
 * MCU upgrades subcontract length Settings
 * @param  pack_len  The length of data transferred to the user per pull packet swap,256,512,1024
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_svc_mcu_ota_pack_len_set(IN UINT_T pack_len);

#ifdef __cplusplus
}
#endif

#endif





































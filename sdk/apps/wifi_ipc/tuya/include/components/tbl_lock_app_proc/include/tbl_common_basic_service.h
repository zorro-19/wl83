/**
 * @file    tbl_common_basic_sevice.h
 * @author  www.tuya.com
 * @brief 通用对接最小系统功能协议交互处理
 * @version 1.0
 * @date    2021-07-31
 * @copyright Copyright (c) tuya.inc 2020
 * Provides related interfaces for heartbeat watchdog.
 */

#ifndef _TBL_COMMON_BASIC_SERVICE_H
#define _TBL_COMMON_BASIC_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "tfm_cmd_list.h"
#include "tbl_kiwi_cmd_def.h"
#include "tbl_common_public_iot.h"
#include "tdl_com_dev_mange.h"
/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/
#define FIRM_KEY_LEN 20
#define PID_CFG_PARAM_E                 "pid_key"
/***********************************************************************
 ** STRUCT                                                            **
 **********************************************************************/
#define PID_STR_LEN     32

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/

/**
 * @brief 最小系统功能初始化
 * @param[in] info 模组可使用gpio list信息
 * @param[in] auto_baud 是否是波特率自适应
 * @param[in] trans_handle 控制操作句柄，包含通信方式以及通信port信息
 * @return 操作结果，OPRT_OK表示成功，其他表示失败，具体查看@OPERATE_RET 定义
 * @note 无
 */
OPERATE_RET tbl_common_basic_funtion_init(IN TY_TRANS_HANDLE_S trans_handle);
VOID send_kiwi_common_result(UCHAR_T cmd,  UCHAR_T first, UCHAR_T second);
VOID send_kiwi_wf_state(UART_KIWI_WF_STATE_E stat);

VOID tuya_change_wifi_en(VOID);
OPERATE_RET tuya_flash_set_wifi_en(BOOL_T en);
OPERATE_RET tuya_get_wifi_en(BOOL_T *en);


OPERATE_RET tuya_get_wifi_to_mcu(BOOL_T *pWifi_to_mcu);
OPERATE_RET tuya_flash_set_wifi_to_mcu(BOOL_T flag);
VOID ty_proc_kiwi_req_secret_key(VOID);
VOID proc_kiwi_update_tem_password_cache(VOID *data);
VOID ty_proc_dp(TY_DATAPOINT_DATA_S *datapoint);
VOID tuya_get_time(VOID *data);
OPERATE_RET proc_kiwi_dp_54_upload(VOID *data);


OPERATE_RET kiwi_uart_get_time(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_update_mcu_state(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_update_info(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_remote_unlock_ack(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_start_snap_pic(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_update_cache_info(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_get_check_user_info_result(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_get_module_info(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_get_version(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_get_dev_cap(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_set_proactive_view(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_user_control_ack(IN TY_CMD_S *p_service_data);
OPERATE_RET kiwi_uart_user_control_feed_back(IN TY_CMD_S *p_service_data);


#ifdef __cplusplus
}
#endif

#endif

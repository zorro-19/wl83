/**
 * @file tdl_send_data_syn.c
 * @author www.tuya.com
 * @brief 数据同步发送处理
 * @version 1.0
 * @date 2022-05-27
 * @copyright Copyright (c) tuya.inc 2021
 * Provides a serial port service interface that supports multithreaded calls
 */

#ifndef __TDL_SEND_DATA_SYN_H__
#define __TDL_SEND_DATA_SYN_H__

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_os_adapter.h"
#include "tdl_com_dev_mange.h"
#include "tdl_data_send_recv_init.h"

typedef VOID (*PRE_SYNC_TIME_OUT_CB)(UCHAR_T ack_cmd);

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * @brief  数据接收到ack推送
 * @param[in]  handle 控制操作句柄
 * @param[in]     cmd    命令表示信息
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note  无
 */
OPERATE_RET tdl_send_syn_ack(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T cmd);

/**
 * @brief  服务数据入队
 * @param[in]  handle 控制操作句柄
 * @param[in]  p_buf  入队数据指针
 * @param[in]  len  入队数据长度,长度大于零
 * @param[in]  timeout_s 队列数据超时重传的时间单位为毫秒，范围为1~30s
 * @param[in]  send_time 队列数据的超时重传次数，范围为1~100
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   删除队列数据由用户调用删除操作
 */
#define tdl_data_send_syn_default(handle, p_buf, len, ack_cmd) tdl_data_send_syn(handle, p_buf, len, ack_cmd, TRUE, 1000, 3)

OPERATE_RET tdl_data_send_syn(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T *p_buf, IN UINT_T len, IN UCHAR_T ack_cmd,
                              IN BOOL_T is_retrans, IN UINT_T timeout, IN UINT_T send_time);

/**
 * @brief  同步发送处理业务初始化
 * @param[in]  handle 控制操作句柄
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
OPERATE_RET tdl_data_send_syn_init(IN TY_TRANS_HANDLE_S handle, IN PRE_SYNC_TIME_OUT_CB cb);

/**
 * @brief  同步发送处理数据释放
 * @param[in]  handle 控制操作句柄
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
OPERATE_RET tdl_data_send_syn_deinit(IN TY_TRANS_HANDLE_S handle);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

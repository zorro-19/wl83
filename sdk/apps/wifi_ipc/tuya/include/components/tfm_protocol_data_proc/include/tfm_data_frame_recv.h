/**
 * @file    tfm_data_frame_recv.h
 * @author  lanbo.feng@tuya.com
 * @brief   接收涂鸦协议数据
 * @version 2.0
 * @date    2022-4-26
 * @copyright Copyright (c) tuya.inc 2022
 * 提供接收协议数据服务的接口
 */
#ifndef __TFM_DATA_FRAME_RECV_H
#define __TFM_DATA_FRAME_RECV_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_cloud_types.h"
#include "tfm_cmd_list.h"
#include "uni_thread.h"
#include "tdl_data_send_recv_init.h"
#include "tdl_send_data_syn.h"

/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/

typedef void *TY_RECV_HANDLE;

/**
 * @brief  数据接收回调
 * @param[in] recv_handle: 接收句柄
 * @param[in] p_cmd_data: 数据，包括命令字，数据长度，数据内容
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
typedef OPERATE_RET(*TY_RECV_DATA_CB)(IN TY_CMD_S *p_cmd_data);

/**
 * @brief  数据接收ack通知回调
 * @param[in] recv_handle: 接收句柄
 * @param[in] p_cmd_data: 数据，包括命令字，数据长度，数据内容
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
typedef OPERATE_RET(*TY_RECV_ACK_CB)(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T cmd);

/**
 * @brief 数据处理状态枚举定义
 */
typedef enum {
    UART_RECV = 0, /* 数据接收状态 */
    UART_PROC,     /* 数据处理状态 */
} TY_UART_TYPE_E;

/***********************************************************************
 ** STRUCT                                                            **
 **********************************************************************/
/**
 * @brief 数据接收处理相关数据定义
 */
typedef struct {
    TY_TRANS_HANDLE_S port;     /* 传输控制句柄 */
    UINT_T          stackDepth; /* 数据接收处理线程栈深度,最小128，默认3K */
    UINT8_T         priority;   /* 数据接收处理线程优先级 */
    UINT_T loop_wait_time_ms;   /* 等待时间 */
    UINT_T recv_len;            /* 接收长度 */
    UINT_T cache_len;           /* 接收缓存长度 */
    UCHAR_T *p_cache;           /* 接收缓存区 */
    TY_RECV_ACK_CB recv_ack_cb; /* 接收ack处理回调 */
    TY_RECV_DATA_CB recv_cb;    /* 接收回调 */
} TY_RECV_MSG_S;

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
* @brief 涂鸦协议传输链路反初始化
* @param[out] port: 传输控制句柄
* @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
* @note 无
*/
OPERATE_RET tfm_data_frame_proc_deinit(IN TY_TRANS_HANDLE_S trans_handle);


/**
 * @brief 涂鸦协议接收数据初始化
 * @param[out] p_recv_handle: 数据接收句柄
 * @param[in] p_cfg: 数据接收配置
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_data_frame_proc_init(IN TY_RECV_MSG_S *p_cfg, IN UINT_T send_queue_num, IN PRE_SYNC_TIME_OUT_CB cb);

/**
 * @brief  涂鸦协议处理接收数据的间隔设置
 * @param[in] p_recv_handle: 数据接收句柄
 * @param[in] uart_loop_interval_time_ms: 接收数据间隔时间
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_data_frame_recv_set_interval_time(IN TY_RECV_HANDLE recv_handle, IN UINT_T uart_loop_interval_time_ms);

#ifdef __cplusplus
}
#endif

#endif

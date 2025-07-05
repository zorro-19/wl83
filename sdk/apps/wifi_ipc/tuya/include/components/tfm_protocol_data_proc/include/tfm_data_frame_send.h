/**
 * @file    tfm_data_frame_send.h
 * @author  www.tuya.com
 * @brief   发送涂鸦协议数据
 * @version 2.0
 * @date    2022-4-26
 * @copyright Copyright (c) tuya.inc 2022
 * 提供发送命令字数据服务的接口
 */

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 ** INCLUDE                                                           **
 **********************************************************************/
#ifndef __TFM_DATA_FRAME_DEND_H
#define __TFM_DATA_FRAME_DEND_H

#include "tuya_cloud_types.h"
#include "tdl_send_data_queue.h"
#include "tdl_send_data_syn.h"
#include "tdl_data_send_recv_init.h"

/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/
/**
 * @brief 数据发送处理类型
 */
typedef enum {
    SEND_TYPE_DIRECT = 0, /* 直接发送帧数据 */
    SEND_TYPE_IN_QUE,     /* 在队列中发送帧数据，支持是否需要等待应答 */
    SEND_TYPE_SYN,        /* 同步发送帧数据，等待应答 */
} TY_SEND_TYPE_E;

/***********************************************************************
 ** VARIABLE                                                          **
 **********************************************************************/

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * @brief  发送协议初始化功能
 * @param[in] trans_handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in] queue_num: 入队发送 队列最大缓存数量
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note queue_num 所有入队发送处理函数共用一个que，请注意结合设备资源设置queue_num的值
 */
OPERATE_RET tfm_data_frame_send_init(IN TY_TRANS_HANDLE_S trans_handle, IN UINT_T queue_num, IN PRE_SYNC_TIME_OUT_CB cb);

/**
 * @brief  发送协议反初始化功能
 * @param[in]  port 控制操作句柄，包含通信方式以及通信port信息
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_data_frame_send_deinit(IN TY_TRANS_HANDLE_S trans_handle);

/**
 * @brief  直接发送用户数据协议
 * @param[in] trans_handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in] cmd: 发送帧数据命令字
 * @param[in] data: 发送帧数据内容
 * @param[in] len: 发送帧数据长度
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_data_frame_send_direct(IN TY_TRANS_HANDLE_S trans_handle, IN UCHAR_T cmd, IN UCHAR_T *data,
                                       IN UINT_T len);

/**
 * @brief 入队发送处理函数
 * @param[in] trans_handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in] cmd: 发送帧数据命令字
 * @param[in] data: 发送帧数据内容
 * @param[in] len: 发送帧数据长度
 * @param[in] timerout_ms: 等待确认超时，单位为ms
 * @param[in] send_time: 重试发送计数
 * @param[in] TY_QUEUE_TIMEOUT_CB 发送处理失败通知回调
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
#define tfm_data_frame_in_queue_default(trans_handle, cmd, data, len)                                                  \
    tfm_data_frame_in_queue(trans_handle, cmd, data, len, 1000, 3, NULL)

#define tfm_data_frame_in_queue_noretry(trans_handle, cmd, data, len)                                                  \
    tfm_data_frame_in_queue(trans_handle, cmd, data, len, 0, 0, NULL)

OPERATE_RET tfm_data_frame_in_queue(IN TY_TRANS_HANDLE_S trans_handle, IN UCHAR_T cmd, IN UCHAR_T *data, IN UINT_T len,
                                    IN UINT_T timerout_ms, IN UINT_T send_time, IN TY_QUEUE_TIMEOUT_CB cb);

/**
 * @brief 同步发送处理函数
 * @param[in] trans_handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in] cmd: 发送帧数据命令字
 * @param[in] data: 发送帧数据内容
 * @param[in] len: 发送帧数据长度
 * @param[in] ack_cmd: 返回校验的命令字
 * @param[in] is_retrans: 是否重发，TRUE:是  FALSE:否
 * @param[in] timeout_ms: 等待确认超时，单位为ms，精度100ms，范围为100~30000ms
 * @param[in] send_time: 重试发送计数，范围为1~100
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 同步发送命令处理函数用注册进入的cmd_list的func;超时未接收ack，或数据不合法，此接口均会返回失败。
 *       同步发送过程中,将会停止入队发送查询，即所有入队发送的命令将会暂停发送。
 */
#define tfm_data_frame_send_syn_default(trans_handle, cmd, data, len, ack_cmd)                                         \
    tfm_data_frame_send_syn(trans_handle, cmd, data, len, ack_cmd, TRUE, 1000, 3)

OPERATE_RET tfm_data_frame_send_syn(IN TY_TRANS_HANDLE_S trans_handle, IN UCHAR_T cmd, IN UCHAR_T *data, IN UINT_T len,
                                    IN UCHAR_T ack_cmd, BOOL_T is_retrans, UINT_T timeout_ms, UINT_T send_time);

/**
 * @brief  清除队列所有成员数据
 * @param  无
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_data_frame_clear_member_all(VOID);

#ifdef __cplusplus
}
#endif

#endif

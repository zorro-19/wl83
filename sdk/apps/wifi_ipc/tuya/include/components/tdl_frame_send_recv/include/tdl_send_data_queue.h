/**
 * @file tdl_data_queue.c
 * @author wangwei@tuya.com
 * @brief tdl_data_queue, base timer、queue、work queue
 * @version 1.0
 * @date 2021-03-27
 * @copyright Copyright (c) tuya.inc 2021
 * service that implements serial port support for cache retransmission
 * Data first in, first out
 */

#ifndef __TDL_SEND_DATA_QUEUE_H__
#define __TDL_SEND_DATA_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
//#include "tuya_uart_legacy.h"
#include "tuya_os_adapter.h"
#include "tdl_com_dev_mange.h"
#include "tdl_com_dev_mange.h"

#include "tdl_data_send_recv_init.h"

/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/

/**
 * @brief  队列处理回调函数
 * @param[in]  p_data 入队数据指针
 * @param[in]  len 数据长度
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
typedef OPERATE_RET(*TY_QUEUE_TIMEOUT_CB)(IN UCHAR_T *p_data, IN UINT_T len);

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * @brief  服务数据入队
 * @param[in]  port 控制操作句柄，包含通信方式以及通信port信息
 * @param[in]  p_buf  入队数据指针
 * @param[in]  len  入队数据长度,长度大于零
 * @param[in]  timeout_s 队列数据超时重传的时间单位为秒，范围为1~30
 * @param[in]  send_time 队列数据的超时重传次数，范围为1~100
 * @param[in]  timeout_cb 发送超时通知回调函数
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   删除队列数据由用户调用删除操作
 */
#define tdl_data_queue_in_queue_default(port, name, p_buf, len)                                                        \
    tdl_data_queue_in_queue(port, name, p_buf, len, 1000, 3, NULL)

OPERATE_RET tdl_data_queue_in_queue(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T *p_buf, IN UINT_T len, IN UINT_T timerout_s,
                                    IN UINT_T send_time, IN TY_QUEUE_TIMEOUT_CB timeout_cb);

/**
 * @brief  串口队列服务初始化,
 * @param[in]  handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in]  queue_num   队列支持最大缓存数量，范围1-100
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   队列支持多个字段初始化，如tdl_data_multi_thread_send_init
 */
OPERATE_RET tdl_data_queue_sever_init(IN TY_TRANS_HANDLE_S handle, IN UINT_T queue_num);

/**
 * @brief  清除当前队列成员数据
 * @param[in]  handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in]  cmd  命令字
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
OPERATE_RET tdl_data_queue_delete_current(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T cmd);

/**
 * @brief  清除所有队列成员数据
 * @param  无
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
OPERATE_RET tdl_data_queue_clear_member_all(VOID);

/**
 * @brief  关闭队列发送检测
 * @param[in]  handle 控制操作句柄，包含通信方式以及通信port信息
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
OPERATE_RET tdl_data_queue_send_stop(IN TY_TRANS_HANDLE_S handle);

/**
 * @brief  队列发送检测启动
 * @param[in]  handle 控制操作句柄，包含通信方式以及通信port信息
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   无
 */
OPERATE_RET tdl_data_queue_send_start(IN TY_TRANS_HANDLE_S handle);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

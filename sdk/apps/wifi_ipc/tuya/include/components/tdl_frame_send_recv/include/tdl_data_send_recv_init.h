/**
 * @file tdl_data_send_recv.h
 * @author www.tuya.com
 * @brief 数据收发接口
 * @version 1.0
 * @date 2021-03-27
 * @copyright Copyright (c) tuya.inc 2021
 * Provides a serial port service interface that supports multithreaded calls
 */
#ifndef __TDL_DATA_SEND_RECV_INIT_H__
#define __TDL_DATA_SEND_RECV_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_os_adapter.h"
#include "tdl_com_dev_mange.h"

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * @brief  数据读取
 * @param[in]     handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[inout]  p_buf  接收缓冲区
 * @param[in]     len    缓冲区大小
 * @param[inout]  p_read_len 实际读取数据长度(单位：字节)
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   从底层串行驱动程序的缓存中获取串行端口接收的数据
 */
OPERATE_RET tdl_hw_com_data_get_ack(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T cmd);

/**
 * @brief  数据读取
 * @param[in]     handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[inout]  p_buf  接收缓冲区
 * @param[in]     len    缓冲区大小
 * @param[inout]  p_read_len 实际读取数据长度(单位：字节)
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 * @note   从底层串行驱动程序的缓存中获取串行端口接收的数据
 */
OPERATE_RET tdl_hw_com_data_read(IN TY_TRANS_HANDLE_S handle, OUT UCHAR_T *p_buf, IN UINT_T len,
                                 OUT UINT_T *p_read_len);

/**
 * @brief
 * 多线程支持保护的串行数据传输接口,如果调用者不调用初始化，函数在内部调用
 * @param[in]  handle 控制操作句柄，包含通信方式以及通信port信息
 * @param[in]  p_buf  数据发送指针
 * @param[in]  len  数据长度
 * @return     函数返回值，OPRT_OK 成功, 其它 失败
 */
OPERATE_RET tdl_hw_com_data_send(IN TY_TRANS_HANDLE_S handle, IN UCHAR_T *p_buf, IN UINT_T len);

/**
 * @brief 通信初始化
 * @param[in] cfg 需要使用的硬件通信方式初始化资源信息
 * @return  函数返回值，OPRT_OK 成功, 其它 失败
 * @note   受多线程支持保护的串行数据传输接口,
 * 相同的串行端口资源使用相同的锁资源
 */
OPERATE_RET tdl_hw_com_data_init(IN TY_TRANS_HANDLE_S handle, IN TY_TRANS_SEND_PRE_HANDLE_S send_pre_handle, IN TY_TRANS_SEND_PRE_HANDLE_S read_pre_handle);


/**
 * @brief  通信资源释放
 * @param  handle 控制操作句柄，包含通信方式以及通信port信息
 * @return 函数返回值，OPRT_OK 成功, 其它 失败
 */
OPERATE_RET tdl_hw_com_data_deinit(IN TY_TRANS_HANDLE_S handle);

#ifdef __cplusplus
}
#endif

#endif

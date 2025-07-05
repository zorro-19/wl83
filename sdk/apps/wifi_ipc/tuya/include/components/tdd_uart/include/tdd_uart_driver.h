/**
 * @file tdd_uart_driver.h
 * @author www.tuya.com
 * @brief 串口设备驱动
 * @version 1.0
 * @date 2022-05-27
 * @copyright Copyright (c) tuya.inc 2022
 * Provides a serial port service interface that supports multithreaded calls
 */
#ifndef __TDL_UART_DRIVER_H__
#define __TDL_UART_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_os_adapter.h"
#include "tuya_uart_legacy.h"

/***********************************************************************
** STRUCT                                                            **
**********************************************************************/
/**
 * @brief 串口初始化相关数据结构定义
 */
typedef struct {
    TY_UART_PORT_E port;      /*串口号 TY_UART0或者TY_UART1*/
    TY_UART_BAUD_E baud_rate; /*波特率*/
    TY_DATA_BIT_E bits;       /*数据位*/
    TY_PARITY_E parity;       /*校验位*/
    TY_STOPBITS_E stop;       /*停止位*/
    UINT_T cache_len;         /*底层驱动缓冲长度*/
    BOOL_T unblock_marks;     /*是否阻塞标志*/
} TY_UART_MULTI_CONFIG_S;

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/

/**
 * @brief 串口设备注册
 * @param[in] dev_name: 设备name
 * @param[in] uart_cfg: 串口初始化参数
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @notice
 */
int tdd_uart_driver_register(char *dev_name, TY_UART_MULTI_CONFIG_S uart_cfg);

#ifdef __cplusplus
}
#endif

#endif

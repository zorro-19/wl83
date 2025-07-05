/**
 * @file tdl_com_dev_mange.h
 * @author www.tuya.com
 * @brief 通信设备驱动管理
 * @version 1.0
 * @date 2021-03-27
 * @copyright Copyright (c) tuya.inc 2021
 * Provides a serial port service interface that supports multithreaded calls
 */
#ifndef __TDL_COM_DEV_MANGE__H__
#define __TDL_COM_DEV_MANGE__H__

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_os_adapter.h"

/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/

typedef void *TY_TRANS_HANDLE_S;
typedef VOID (*TY_TRANS_SEND_PRE_HANDLE_S)(VOID);
typedef VOID (*TY_TRANS_READ_PRE_HANDLE_S)(VOID);

#define COM_DEV_NAME_MAX_LEN (16u) /*NAME最大长度*/

/**
 * @brief 通信设备类型枚举
 */
typedef enum {
    TY_USER_UART = 0x00,
    TY_USER_SPI,
    TY_USER_IIC,
    TY_USER_IIS,
    TY_USER_HDMI,
    TY_USER_SDIO,
    TY_USER_TYPE_MAX = TY_USER_SDIO,
} TY_TRNAS_TYPE_E;

/***********************************************************************
 ** STRUCT                                                            **
 **********************************************************************/

/**
 * @brief 多图数据头结构体
 */
typedef struct {
    TY_TRNAS_TYPE_E type; /*通信方式*/
    VOID *cfg_data;       /*通信初始化配置数据信息*/
} TY_TRANS_CONFIG_S;

/**
 * @brief 设备初始化收发接口
 */
typedef struct {
    int (*send)(IN TY_TRANS_CONFIG_S cfg, IN UCHAR_T *p_buf, IN UINT_T len);
    int (*read)(IN TY_TRANS_CONFIG_S cfg, OUT UCHAR_T *p_buf, IN UINT_T len, OUT UINT_T *p_read_len);
    int (*init)(IN TY_TRANS_CONFIG_S cfg);
    int (*deinit)(IN TY_TRANS_CONFIG_S cfg);
} TDD_DATA_TRANS_S;

/**
 * @brief 设备节点
 */
typedef struct com_dev_list {
    struct com_dev_list *next;
    BOOL_T is_open;                        /*初始化开启标志*/
    CHAR_T name[COM_DEV_NAME_MAX_LEN + 1]; /*设备name*/
    TY_TRANS_CONFIG_S com_dev_cfg;         /*通信初始化参数*/
    TDD_DATA_TRANS_S *drv_intfs;           /*设备接口*/
} COM_DEV_NODE_T, COM_DEV_LIST_T;

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * @brief 通信设备注册接口（TDD调用）
 * @param[in] dev_name: 地图数据可以缓存的最大队列数
 * @param[in] com_dev_cfg: 地图数据可以缓存的最大队列数
 * @param[in] com_intfs: 地图数据可以缓存的最大队列数
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @notice
 */
OPERATE_RET tdl_hw_com_dev_register(CHAR_T *dev_name, TY_TRANS_CONFIG_S com_dev_cfg, TDD_DATA_TRANS_S *com_intfs);

/**
 * @brief 设备句柄查询
 * @param[in] dev_name: 地图数据可以缓存的最大队列数
 * @param[in] handle: 地图数据可以缓存的最大队列数
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @notice
 */
OPERATE_RET tdl_com_dev_find(CHAR_T *dev_name, TY_TRANS_HANDLE_S *handle);

#ifdef __cplusplus
}
#endif

#endif

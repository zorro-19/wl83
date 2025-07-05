/**
 * @file	tfm_cmd_list.h
 * @author	lanbo.feng@tuya.com
 * @brief	注册串口命令字服务
 * @version	2.0
 * @date	2022-4-26
 * @copyright Copyright (c) tuya.inc 2022
 * 提供多个接口处理接收到的cmd数据和分发cmd回调函数。
 */

#ifndef __TFM_CMD_LIST_H
#define __TFM_CMD_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_cloud_types.h"

/***********************************************************************
 ** STRUCT                                                            **
 **********************************************************************/
/**
 * @brief 涂鸦涂鸦协议结构定义
 * @note 当是son_cmd内容时,会将son_cmd填充到cmd信息中,data 内容会自动偏移1字节，datalen-1 返回。
 */
typedef struct {
    UCHAR_T version; /* 串口数据版本 */
    UCHAR_T cmd;     /* 串口数据命令 */
    UINT_T datalen;  /* 串口数据长度 */
    UCHAR_T *data;   /* 串口数据 */
} TY_CMD_S;

/**
 * @brief 数据处理函数指针定义
 */
typedef OPERATE_RET(*TY_CMD_HANDLE_CB)(IN TY_CMD_S *p_cmd_data);

/**
 * @brief list注册数据结构定义
 */
typedef struct {
    UCHAR_T cmd;                 /* 命令字 */
    TY_CMD_HANDLE_CB cb;         /* 命令字回调函数 */
    UCHAR_T son_cmd;             /* 子命令码 */
    TY_CMD_HANDLE_CB son_cmd_cb; /* 子命令字回调函数 */
} TY_CMD_CFG_S;

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * @brief  处理已经解析过的串口命令字数据
 * @param[in] p_data: 用户传入数据信息
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_cmd_list_proc(IN TY_CMD_S *p_data);

/**
 * @brief  注册服务，该服务包含所有具有相同功能的命令。
 * @param[in] cmd_list: 用户注册的命令
 * @param[in] cmd_count: 命令数量
 * @return 执行结果,返回 OPRT_OK表示成功，返回 其他 则表示失败
 * @note 无
 */
OPERATE_RET tfm_cmd_list_reg(IN TY_CMD_CFG_S *cmd_list, IN UINT_T cmd_count);

#ifdef __cplusplus
}
#endif

#endif

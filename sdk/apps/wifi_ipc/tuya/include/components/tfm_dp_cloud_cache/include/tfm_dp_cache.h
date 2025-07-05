/**
* @file tfm_dp_cache.h
* @author www.tuya.com
* @brief tfm_dp_cache module is used to
* @version 0.1
* @date 2023-04-07
*
* @copyright Copyright (c) tuya.inc 2023
*
*/
#ifndef __TFM_DP_CACHE_H__
#define __TFM_DP_CACHE_H__
#include "tuya_cloud_types.h"
/***********************************************************
*************************micro define***********************
***********************************************************/

/***********************************************************
***********************typedef define***********************
***********************************************************/
typedef struct {
    UCHAR_T  dp_num;
    UCHAR_T  dp_arr[0];
} DP_CACHE_STATE_T;

/***********************************************************
***********************variable define**********************
***********************************************************/


/***********************************************************
***********************function define**********************
***********************************************************/
/**
* @brief 协议转码成串口协议格式输出
*
* @param[in] data
* @param[out] pp_out
* @return
*/
UINT_T tfm_dp_cache_transcode_to_uart_dataformat(VOID *data, UCHAR_T **pp_out);

/**
* @brief 获取dp缓存数据
*
* @param[in] dp_state
* @param[out] pp_out
* @return
*/
OPERATE_RET tfm_dp_cache_get_data(DP_CACHE_STATE_T *dp_state, CHAR_T **pp_out);

#endif
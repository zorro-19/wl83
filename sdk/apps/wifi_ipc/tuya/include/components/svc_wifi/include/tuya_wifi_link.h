/**
* @file tuya_wifi_link.h
* @brief tuya wifi link interface:open/close,start/stop config,reset,etc.
* @version 0.1
* @date 2021-03-15
*
* @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
*
*/

#ifndef __TUYA_WIFI_LINK__
#define __TUYA_WIFI_LINK__
#ifdef __cplusplus
extern "C" {
#endif


#include "tuya_cloud_wifi_defs.h"
/**
 * @brief tuya wifi netcfg params, mthd and start mode
 */
typedef struct tuya_wifi_cfg_param {
    GW_WF_CFG_MTHD_SEL mthd;
    GW_WF_START_MODE start_mode;
    BOOL_T enable_station_ap;
} TUYA_WIFI_CFG_PARAM, *P_TUYA_WIFI_CFG_PARAM;


/**
 * @brief do wifi activate.
 *
 * @param[in] token token of netcfg.
 *
 * @param[in] t_len length of token
  *
 * @note refer to P_TUYA_WIFI_CFG_PARAM.
 *
 * @return P_TUYA_WIFI_CFG_PARAM on success. NULL on error
 */

OPERATE_RET do_wifi_activate(VOID *token, UINT_T t_len);


/**
 * @brief get wifi netcfg params.
 *
 *
 * @note refer to P_TUYA_WIFI_CFG_PARAM.
 *
 * @return P_TUYA_WIFI_CFG_PARAM on success. NULL on error
 */
P_TUYA_WIFI_CFG_PARAM get_wifi_config_params();


/**
 * @brief do wifi link init.
 *
 *
 * @note before using wifi, do wifi link init first.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */

OPERATE_RET tuya_svc_wifi_init(TUYA_WIFI_CFG_PARAM cfg_param);

/**
 * @brief set wifi config para.
 *
 *
 * @note
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET set_wifi_config_params(TUYA_WIFI_CFG_PARAM cfg_param);

/**
 * @brief send wifi link up or down event to network manager layer
 *
 * @param[in] isLinkUp wifi link is up or down
 *
 * @note
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */

OPERATE_RET tuya_wifi_send_link_event(BOOL_T isLinkUp);

/**
 * @brief start ap mode
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET wifi_netcfg_start_ap_mode(VOID_T);

/**
 * @brief init country code
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_wifi_init_ccode();

/**
 * @brief set country code
 *
 * @param[in] ccode country code
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_wifi_set_ccode(CHAR_T *ccode);

/**
 * @brief get country code
 *
 * @return country code
 */
CHAR_T *tuya_wifi_get_ccode();

/**
 * @brief set station disconnect timeout
 *
 * @param[in] timeout timeout
 *
 */
VOID tuya_wifi_set_station_dis_timeout(INT_T timeout);

/**
 * @brief set netcfg fast mode
 *
 * @param[in] ssid ssid
 * @param[in] passwd passwd
 *
 */
VOID tuya_wifi_set_netcfg_fast_mode(CHAR_T *ssid, CHAR_T *passwd);
#ifdef __cplusplus
}
#endif

#endif

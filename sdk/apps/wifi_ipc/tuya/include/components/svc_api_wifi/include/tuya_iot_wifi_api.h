/**
 * @file tuya_iot_wifi_api.h
 * @brief
 * @author tuya
 * @version 1.0.0
 * @date 2021-01-12
 * @copyright Copyright(C),2017, 涂鸦科技 www.tuya.comm
 */

#ifndef _TUYA_IOT_WIFI_API_H
#define _TUYA_IOT_WIFI_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_cloud_wifi_defs.h"
#include "tuya_iot_com_api.h"
#include "gw_intf.h"

/***********************************************************
*************************micro define***********************
***********************************************************/

/***********************************************************
*************************variable define********************
***********************************************************/

/***********************************************************
*************************function define********************
***********************************************************/

/**
* @brief tuya_iot_set_wf_gw_prod_info
*
* @param[in] wf_prod_info： device product info
*
* @return OPERATE_RET
*/
OPERATE_RET tuya_iot_set_wf_gw_prod_info(IN CONST WF_GW_PROD_INFO_S *wf_prod_info);

/**
 * @brief tuya_iot_wf_timeout_set
 * @desc set wifi timeout
 *
 * @param[in] timeout: time in sec
 *
 * @return none
 *
 * @note must call befor tuya_iot_wf_xxx_init
 */
VOID tuya_iot_wf_timeout_set(IN CONST UINT_T timeout);

/**
 * @brief tuya_iot_wf_dev_init
 *
 * @param[in] cfg: wifi device work mode
 * @param[in] start_mode: wifi netcfg mode
 * @param[in] cbs: tuya wifi sdk user callbacks
 * @param[in] firmware_key: the firmware key
 * @param[in] product_key: product key/proudct id,get from tuya open platform
 * @param[in] wf_sw_ver: wifi module software version format:xx.xx.xx (0<=x<=9)
 * @param[in] attr: the attach firmware of this device
 * @param[in] attr_num: the attach firmware number
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_dev_init(IN CONST GW_WF_CFG_MTHD_SEL cfg, IN CONST GW_WF_START_MODE start_mode,
                                 IN CONST TY_IOT_CBS_S *cbs, IN CHAR_T *firmware_key,
                                 IN CHAR_T *product_key, IN CHAR_T *wf_sw_ver, IN CONST DEV_TYPE_T tp,
                                 IN GW_ATTACH_ATTR_T *attr, IN CONST UINT_T attr_num);

/**
 * @brief tuya_iot_wf_mcu_dev_init
 *
 * @param[in] cfg: wifi device work mode
 * @param[in] start_mode: wifi netcfg mode
 * @param[in] cbs: tuya wifi sdk user callbacks
 * @param[in] p_firmware_key: the firmware key
 * @param[in] product_key: product key/proudct id,get from tuya open platform
 * @param[in] wf_sw_ver: wifi module software version format:xx.xx.xx (0<=x<=9)
 * @param[in] mcu_sw_ver: mcu software version format:xx.xx.xx (0<=x<=9)
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_mcu_dev_init(IN CONST GW_WF_CFG_MTHD_SEL cfg, IN CONST GW_WF_START_MODE start_mode,
                                     IN CONST TY_IOT_CBS_S *cbs, IN CHAR_T *p_firmware_key,
                                     IN CHAR_T *product_key, IN CHAR_T *wf_sw_ver, IN CONST CHAR_T *mcu_sw_ver);

/**
 * @brief tuya_iot_wf_soc_dev_init_param
 *
 * @param[in] cfg
 * @param[in] start_mode
 * @param[in] cbs: tuya wifi sdk user callbacks,note cbs->dev_ug_cb is useless
 * @param[in] firmware_key
 * @param[in] product_key: product key/proudct id,get from tuya open platform
 * @param[in] wf_sw_ver: wifi module software version format:xx.xx.xx (0<=x<=9)
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_soc_dev_init_param(IN CONST GW_WF_CFG_MTHD_SEL cfg, IN CONST GW_WF_START_MODE start_mode,
        IN CONST TY_IOT_CBS_S *cbs, IN CHAR_T *firmware_key,
        IN CHAR_T *product_key, IN CHAR_T *wf_sw_ver);
#define tuya_iot_wf_soc_dev_init(cfg, start_mode,cbs,product_key,wf_sw_ver) \
        tuya_iot_wf_soc_dev_init_param(cfg, start_mode,cbs,NULL,product_key,wf_sw_ver)


/**
 * @brief tuya_iot_reg_get_wf_nw_stat_cb_params
 *
 * @param wf_nw_stat_cb: network status monitor callback
 * @param min_interval_s: network status detect interval
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_reg_get_wf_nw_stat_cb_params(IN CONST GET_WF_NW_STAT_CB wf_nw_stat_cb, IN CONST INT_T min_interval_s);
#define tuya_iot_reg_get_wf_nw_stat_cb(wf_nw_stat_cb) \
    tuya_iot_reg_get_wf_nw_stat_cb_params(wf_nw_stat_cb, 1)

/**
 * @brief tuya_iot_set_wf_cfg_err_code_cb
 *
 * @param wf_nw_cfg_err_code_cb
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_set_wf_cfg_err_code_cb(IN CONST WF_NW_CFG_ERR_CODE_CB wf_nw_cfg_err_code_cb);

/**
 * @brief tuya_iot_wf_gw_unactive
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_gw_unactive(VOID);

/**
 * @brief tuya_iot_wf_gw_reset
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_gw_reset(VOID);

/**
 * @brief tuya_iot_wf_gw_fast_unactive
 *
 * @param[in] mthd: new work mode after reboot
 * @param[in] wifi_start_mode: new netcfg mode after reboot
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_gw_fast_unactive(IN CONST GW_WF_CFG_MTHD_SEL mthd, IN CONST GW_WF_START_MODE wifi_start_mode);

/**
 * @brief tuya_iot_wf_fast_get_nc_type
 *
 * @param[in] nc_type
 *
 * @return OPERATE_RET
 */
OPERATE_RET tuya_iot_wf_fast_get_nc_type(GW_WF_NWC_FAST_STAT_T *nc_type);

/**
 * @brief tuya_iot_set_user_def_ap_if
 *
 * @param[in] ssid: user defined ssid of device ap
 * @param[in] passwd: user defined ssid of device ap
 *
 * @return OPERATE_RET
 *
 * @note need call before tuya_iot_wf_xxx_init
 */
OPERATE_RET tuya_iot_set_user_def_ap_if(IN CONST CHAR_T *ssid, IN CONST CHAR_T *passwd);

/**
 * @brief tuya_iot_get_dev_ap_if
 *
 * @param[in] ssid: the ssid of deivce ap
 * @param[in] passwd: the passwd of device ap
 *
 * @return OPERATE_RET
 *
 */
OPERATE_RET tuya_iot_get_dev_ap_if(OUT CHAR_T *ssid, OUT CHAR_T *passwd);

/**
 * @brief tuya_iot_gw_wf_user_cfg
 *
 * @param[in] ssid: user config router ap ssid
 * @param[in] passwd: user config router ap passwd
 * @param[in] token: the token of tuya cloud
 *
 * @return OPERATE_RET
 *
 * @note device will scan and connect to the router ap, and try to active on tuya cloud use the token
 */
OPERATE_RET tuya_iot_gw_wf_user_cfg(IN CONST CHAR_T *ssid, IN CONST CHAR_T *passwd, IN CONST CHAR_T *token);

/**
 * @brief tuya_iot_set_max_sta_conn
 *
 * @param[in] max_conn
 *
 * @return
 *
 * @note need call before tuya_iot_wf_xxx_init
 */
VOID tuya_iot_set_max_sta_conn(IN CONST UCHAR_T max_conn);

/**
 * @brief tuya_iot_set_nw_ip
 *
 * @param[in] ip
 * @param[in] mask
 * @param[in] gw
 *
 * @return none
 *
 * @note need call before tuya_iot_wf_xxx_init
 */
VOID tuya_iot_set_nw_ip(IN CONST CHAR_T *ip, IN CONST CHAR_T *mask, IN CONST CHAR_T *gw);

/**
 * @brief tuya_iot_netcfg_init
 *
 * @return OPERATE_RET
 *
 * @note need call after tuya_svc_wifi_init
 */
OPERATE_RET tuya_iot_netcfg_init(IN CONST GW_WF_START_MODE start_mode, IN GW_WORK_STAT_MAG_S *p_gw_wsm);

OPERATE_RET tuya_iot_netcfg_reinit(VOID_T);

/**
 * @brief iot_wf_gw_unactive_custom_mode
 *
 * @param[in] wifi_mode
 *
 * @return OPERATE_RET
 */
OPERATE_RET iot_wf_gw_unactive_custom_mode(GW_WF_START_MODE wifi_mode);

#ifdef __cplusplus
}
#endif

#endif  /*_TUYA_IOT_API_H*/


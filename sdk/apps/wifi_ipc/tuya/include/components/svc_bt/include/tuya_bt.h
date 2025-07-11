/**
* @file tuya_bt.h
* @brief Common process - Initialization
* @version 0.1
* @date 2020-11-09
*
* @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
*
*/

#ifndef TUYA_BT_H__
#define TUYA_BT_H__

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "base_event_info.h"
#include "tal_bluetooth_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef BYTE_T TUYA_BLE_ABILITY_T;
#define TUYA_BLE_ABILITY_NONE      0x0
#define TUYA_BLE_ABILITY_NETCFG    0x1
#define TUYA_BLE_ABILITY_DP_CTRL   0x2
#define TUYA_BLE_ABILITY_ALL       0xFF

/**
 * @brief connection status for bluetooth
 */
typedef enum {
    TUYA_BT_UNBONDING_UNCONN = 0,
    TUYA_BT_UNBONDING_CONN,
    TUYA_BT_BONDING_UNCONN,
    TUYA_BT_BONDING_CONN,
    TUYA_BT_UNKNOW_STATUS
} TUYA_BT_CONN_STAT;

/**
 * @brief status for bluetooth service
 */
typedef enum {
    TUYA_BT_SERV_OPENED = 0,
    TUYA_BT_SERV_OPENING,
    TUYA_BT_SERV_CLOSED,
    TUYA_BT_SERV_CLOSING
} TUYA_BT_SERV_STAT;

/**
 * @brief bind type for bluetooth remote controller
 */
typedef enum {
    TUYA_BLE_OP_UNBIND = 0,
    TUYA_BLE_OP_BIND,
} TUYA_BLE_BIND_TYPE;


/**
 * @brief parameters for bluetooth
 */
typedef struct {
    CHAR_T *uuid;    //uuid
    CHAR_T *auth_key;//authentication key
} TY_BT_SDK_PARAM_S;

//callback function for user dp query
typedef VOID_T(*BT_DP_QUERY_CB)(VOID_T);
typedef UINT_T(*BT_DP_GET_TM_CB)(CHAR_T       *time_str);

typedef struct {
    UINT8_T priority_flag;      //0:wifi first  1:bt first
    UINT8_T share_flag;         //0:no shared device  1:tuya shared device
    UINT8_T dp_rept_with_time;  //0:without time  1:with time
    UINT8_T rsvd;               //reserved param
    BT_DP_QUERY_CB query_dp_cb; //callback function for dp query
    BT_DP_GET_TM_CB get_timestamp_cb;
} TUYA_BLE_BT_PARA;

#if defined(ENABLE_BT_MF) && (ENABLE_BT_MF == 1)
OPERATE_RET ty_ble_init_for_mftest(VOID_T);
OPERATE_RET ty_ble_deinit_for_mftest(VOID_T);
#endif

/**
 * @brief Set name for bluetooth device.
 *
 * @param[in] dev_name: device name
 *
 * @note This API is used for setting name for bluetooth device. this API should be called before bluetooth initialized.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_set_bt_device_name(CHAR_T *dev_name);

/**
 * @brief Update local key
 *
 * @param[in] p_buf: local key
 * @param[in] len: lenth of local key
 *
 * @note This API is used for update local key.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_bt_update_local_key(UINT8_T *p_buf, UINT8_T len);

/**
* @brief Support dp sync report by bluetooth
*
* @param[in] flag: true - enable, false - disable
*
* @note This API is used to support dp sync report by bluetooth
*
* @return VOID
*/
VOID_T ty_bt_support_dp_sync_report(BOOL_T flag);

/**
 * @brief Report dp by bluetooth
 *
 * @param[in] dp_rept_type: dp report type
 * @param[in] data: dp data
 * @param[in] sync: true-support sync report
 *
 * @note This API is used for reporting dp data
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_bt_dp_report(IN CONST DP_REPT_TYPE_E dp_rept_type, IN CONST VOID_T *data, IN BOOL_T sync);

/**
 * @brief Monitor for bluetooth
 *
 * @param VOID
 *
 * @note This API is used for monitor for bluetooth.
 * if the device connected cloud, start advertisement, otherwise stoo it.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_monitor_init(VOID_T);

/**
 * @brief Check bluetooth is connected.
 *
 * @param VOID
 *
 * @note This API is used to check whether the bluetooth is connected.
 *
 * @return be connected or not
 */
BOOL_T is_bt_connected(VOID_T);

//callback function for getting the connection status of bluetooth
typedef VOID (*GET_BT_CONN_STAT_CB)(IN CONST TUYA_BT_CONN_STAT stat);

/**
 * @brief Register callback function for getting the connection status of bluetooth
 *
 * @param[in] bt_conn_stat_cb: callback function
 *
 * @note This API is used for registering callback function for getting the connection status of bluetooth
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_reg_get_bt_stat_cb(IN CONST GET_BT_CONN_STAT_CB bt_conn_stat_cb);

/**
 * @brief Get connection status of bluetooth
 *
 * @param VOID
 *
 * @note This API is used for getting the connection status of bluetooth
 *
 * @return connection status
 */
TUYA_BT_CONN_STAT tuya_bt_get_connect_status(VOID);

/**
 * @brief Set device name for bluetooth.
 *
 * @param[in] dev_name: device name for bluetooth
 *
 * @note This API is used for setting device name for bluetooth. this API should be called before bluetooth initialized.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_set_bt_device_name(CHAR_T *dev_name);

/**
 * @brief Set parameters for bluetooth.
 *
 * @param[in] para: parameters for bluetooth
 *
 * @note This API is used for setting parameters for bluetooth. this API should be called before bluetooth initialized.
 *
 * @return VOID
 */
VOID_T tuya_ble_set_bt_para(TUYA_BLE_BT_PARA *para);

#if defined(ENABLE_BT_REMOTE_CTRL) && (ENABLE_BT_REMOTE_CTRL==1)

/**
 * @brief Init beacon key for bluetooth remote control.
 *
 * @param VOID
 *
 * @note This API is used for initialize beacon key for bluetooth remote control.
 * This API is userd for new remote control.
 *
 * @return VOID
 */
VOID_T tuya_ble_init_beacon_key(VOID_T);

/**
 * @brief Save beacon key for bluetooth remote control.
 *
 * @param VOID
 *
 * @note This API is used for saving beacon key for bluetooth remote control.
 * This API is userd for new remote control.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_save_beacon_key(BOOL_T force);

/**
 * @brief Clear up beacon key for bluetooth remote control.
 *
 * @param VOID
 *
 * @note This API is used for clearing up beacon key for bluetooth remote control.
 * This API is userd for new remote control.
 *
 * @return VOID
 */
VOID_T tuya_ble_clear_beacon_key(VOID_T);

/**
 * @brief Clear up all flash information of bluetooth remote control.
 *
 * @param VOID
 *
 * @note This API is used for all flash information of bluetooth remote control.
 * This API is userd for new remote control.
 *
 * @return VOID
 */
VOID_T tuya_ble_clear_rmt_ctrl_info(UINT8_T stat);


//callback function for advertisement scanning data processing
typedef VOID (*TUYA_BLE_APP_SCAN_HANDLE)(UCHAR_T *data, UCHAR_T len,  UCHAR_T type, UCHAR_T *mac);

/**
 * @brief Register callback function for advertisement scanning data processing
 *
 * @param[in] cb: callback function
 *
 * @note This API is used for registering callback function for advertisement scanning data processing
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_reg_app_scan_adv_cb(TUYA_BLE_APP_SCAN_HANDLE cb);

/**
 * @brief Check whether there is user regist bluetooth remote controller
 *
 * @param VOID
 *
 * @note This API is used to check whether there is user regist bluetooth remote controller
 *
 * @return TRUE or FALSE
 */
BOOL_T tuya_ble_is_user_registed(VOID_T);

//callback function for advertisement scanning raw data processing
typedef VOID (*TUYA_BLE_RAW_SCAN_HANDLE)(TAL_BLE_ADV_REPORT_T *scan_info);

/**
 * @brief Register callback function for advertisement scanning raw data processing
 *
 * @param[in] cb: callback function
 *
 * @note This API is used for registering callback function for advertisement scanning raw data processing
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_reg_raw_scan_adv_cb(TUYA_BLE_RAW_SCAN_HANDLE cb);


//callback function for validity check for bind or unbind operation
typedef OPERATE_RET(*BLE_SCAN_ADV_BIND_CHECK_CB)(TUYA_BLE_BIND_TYPE type, UCHAR_T *data, UCHAR_T len);
//callback function for result notify for bind or unbind operation
typedef VOID_T(*BLE_SCAN_ADV_BIND_RSLT_NOTIFY_CB)(TUYA_BLE_BIND_TYPE type, int rslt);
//callback function for result notify for bind or unbind operation
typedef VOID_T(*BLE_SCAN_ADV_BIND_RSLT_NOTIFY_EX_CB)(UCHAR_T *data, UCHAR_T len, int rslt, UCHAR_T *mac);

typedef struct {
    BLE_SCAN_ADV_BIND_CHECK_CB          bind_check;
    BLE_SCAN_ADV_BIND_RSLT_NOTIFY_CB    bind_notify;
    BLE_SCAN_ADV_BIND_RSLT_NOTIFY_EX_CB bind_notify_ex;
} TUYA_BLE_SCAN_ADV_HANDLE_CBS;

/**
 * @brief Register callback function for advertisement scanning data processing
 *
 * @param[in] cbs: callback function
 *
 * @note This API is used for registering callback function for advertisement scanning data processing
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_reg_app_scan_adv_handle_cbs(TUYA_BLE_SCAN_ADV_HANDLE_CBS *cbs);

/**
 * @brief Set timeout window for binding remote controller
 *
 * @param[in] time_out: time out in second, 0: no window
 *
 * @note This API is used for setting timeout window for binding remote controller
 *
 * @return VOID
 */
VOID_T tuya_ble_set_bind_window(UINT_T time_out);

/**
 * @brief Open window for binding remote controller
 *
 * @param[in] VOID
 *
 * @note This API is used for opening window for binding remote controller
 *
 * @return VOID
 */
VOID_T tuya_ble_open_bind_window(VOID_T);

/**
 * @brief disable clearing bind of ble remote controller
 *
 * @param[in] VOID
 *
 * @note This API is used to disable clearing bind of ble remote controller
 *
 * @return VOID
 */
VOID_T tuya_ble_disable_clr_bind_info(VOID_T);
#endif

/**
 * @brief Start user defined advertising of bluetooth with time limited
 *
 * @param[in] data: adv data
 * @param[in] len: adv data lenth
 * @param[in] sec_time: time in second
 *
 * @note This API is used for registering callback function for advertisement scanning raw data processing
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_ble_start_user_beacon_adv(UCHAR_T *data, UCHAR_T len, UINT_T sec_time);

/**
 * @brief Set enable switch for bluetooth service
 *
 * @param[in] switch: enable switch: TRUE-open, FALSE-close
 *
 * @note This API is used for setting enable switch for bluetooth service, it should be called before sdk initialization.
 *
 * @return VOID
 */
VOID_T tuya_ble_set_serv_switch(BOOL_T swith);

/**
 * @brief Get status of bluetooth service
 *
 * @param VOID
 *
 * @note This API is used to get status of the bluetooth service.
 *
 * @return status of the bluetooth service
 */
TUYA_BT_SERV_STAT tuya_ble_get_serv_stat(VOID_T);

/**
 * @brief Resend the ble adv data to hal and start ble adv
 *
 * @param
 *
 * @note
 *
 * @return VOID
 */
VOID_T tuya_ble_restart_adv(VOID_T);
VOID tuya_ble_restart_adv_with_check(VOID);

/**
 * @brief Forbid the ble adv data
 *
 * @param[in] flag: TRUE-forbid, FALSE-forbid cancel
 *
 * @note
 *
 * @return VOID
 */
VOID_T tuya_ble_forbid_adv(BOOL_T flag);

/**
 * @brief Disable function for execept unbinding
 *
 * @param VOID
 *
 * @note  This API is used for disable function for execept unbinding
 *
 * @return VOID
 */
VOID_T tuya_ble_disable_expt_unbind(VOID_T);

/**
 * @brief Set abilitiy attribute of bluetooth
 *
 * @param attr
 *
 * @note  This API is used to set abilitiy attribute of bluetooth.
 *
 * @return VOID
 */
VOID_T tuya_ble_set_startup_attr(TUYA_BLE_ABILITY_T attr);

/**
 * @brief stop ble netcfg and plug_play when dev under lowpower status
 *
 * @param VOID
 *
 * @note  This API is used for stopping ble netcfg and plug_play when dev under lowpower status
 *
 * @return VOID
 */
VOID_T tuya_ble_lowpower_handle(VOID_T);

/**
 * @brief Report netcfg status
 *
 * @param type: 0-report 1-query
 *
 * @note  This API is used for reporting netcfg status
 *
 * @return VOID
 */
VOID_T tuya_ble_rept_netcfg_stat(IN UINT_T type);

/**
 * @brief Response dp query with report flag
 *
 * @param dpid: query dpid array
 * @param num: query dp num
 *
 * @note  This API is used for responsing dp query with report flag
 *
 * @return VOID
 */
VOID_T tuya_ble_dp_response_query(IN CONST BYTE_T *dpid, IN CONST BYTE_T num);

/**
 * @brief Init tuya bluetooth service
 *
 * @param[in] VOID
 *
 * @note This API is used for initializing tuya bluetooth service
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_bt_init(VOID_T);

VOID_T tuya_enable_ble_dp_ctrl(BOOL_T swith);
VOID_T tuya_enable_ble_timer(BOOL_T swith);
VOID_T tuya_enable_ble_netcfg(BOOL_T swith);
VOID_T tuya_enable_ble_active(BOOL_T swith);
VOID_T tuya_enable_ble_mftst(BOOL_T swith);
VOID_T tuya_enable_ble_wifi_list(BOOL_T swith);
VOID_T tuya_enable_ble_reset(BOOL_T swith);
BOOL_T tuya_ble_is_mftst_enable(VOID_T);

#if defined(ENABLE_BT_SUB_DEV) && (ENABLE_BT_SUB_DEV == 1)
typedef VOID (*TUYA_BLE_SUB_DEV_HANDLE)(UCHAR_T *data, UCHAR_T len, UCHAR_T *mac, UINT_T sn);
OPERATE_RET tuya_ble_sub_dev_reg_dp_cb(TUYA_BLE_SUB_DEV_HANDLE cb);
typedef VOID (*TUYA_BLE_SUB_DEV_BIND_NOTIFY_CB)(VOID_T);
OPERATE_RET tuya_ble_sub_dev_reg_bind_notify_cb(TUYA_BLE_SUB_DEV_BIND_NOTIFY_CB cb);
VOID_T tuya_enable_ble_sub_dev(BOOL_T swith);
#endif
VOID_T tuya_enable_ble_dp_ctrl_ex(BOOL_T swith);
#ifdef __cplusplus
}
#endif

#endif


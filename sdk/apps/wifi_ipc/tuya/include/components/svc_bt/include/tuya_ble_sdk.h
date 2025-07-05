/**
* @file tuya_ble_sdk.h
* @brief Common process - Initialization
* @version 0.1
* @date 2020-11-09
*
* @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
*
*/
#ifndef TUYA_BLE_SDK_H__
#define TUYA_BLE_SDK_H__

#if defined(ENABLE_BT_SERVICE) && (ENABLE_BT_SERVICE==1)

//#include <stdbool.h>
#include <stdint.h>
#include "tuya_cloud_types.h"
#include "tal_bluetooth_def.h"

#define DEVICE_NAME_LEN         16

typedef enum {
    TY_BT_SCAN_BY_NAME = 0x01,
    TY_BT_SCAN_BY_MAC = 0x02,
    TY_BT_SCAN_BY_ADV = 0x03, //接收蓝牙广播
} ty_bt_scan_type_t;

typedef struct {
    unsigned int len;
    unsigned char *data;
} tuya_ble_data_buf_t;

typedef VOID (*TY_BT_MSG_CB)(INT_T id, TAL_BLE_EVT_TYPE_E e, tuya_ble_data_buf_t *buf);
typedef VOID (*TY_BT_SCAN_ADV_CB)(CHAR_T *data, UINT_T len, UCHAR_T *mac, UINT8_T type);

typedef struct {
    CHAR_T scan_type; /* ref ty_bt_scan_type_t. */
    CHAR_T name[DEVICE_NAME_LEN];
    CHAR_T bd_addr[6];
    SCHAR_T rssi;
    UCHAR_T channel;
    UCHAR_T timeout_s; /* second. */
    TY_BT_SCAN_ADV_CB scan_adv_cb;
} ty_bt_scan_info_t;

typedef VOID (*TUYA_BLE_RAW_SCAN_HANDLE)(TAL_BLE_ADV_REPORT_T *scan_info);

/**
 * @brief Init bluetooth.
 *
 * @param[in] mode: ble role
 * @param[in] cb: callback function for msg handling
 *
 * @note This API is used for initialization of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_port_init(TAL_BLE_ROLE_E mode, TY_BT_MSG_CB cb);

/**
 * @brief De-init bluetooth.
 *
 * @param void
 *
 * @note This API is used for de-initialization of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_port_deinit(TAL_BLE_ROLE_E mode);

/**
 * @brief Disconnect bluetooth.
 *
 * @param void
 *
 * @note This API is used for disconnecting bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_gap_disconnect(void);

/**
 * @brief Send data by bluetooth.
 *
 * @param[in] data: send data
 * @param[in] len: data lenth
 *
 * @note This API is used for sending data by bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_send(BYTE_T *data, UINT8_T len);

/**
 * @brief Reset advertisement data of bluetooth.
 *
 * @param[in] adv: advertisement data
 * @param[in] scan_resp: advertisement scan data
 *
 * @note This API is used for reseting advertisement data of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_reset_adv(tuya_ble_data_buf_t *adv, tuya_ble_data_buf_t *scan_resp);

/**
 * @brief Update advertisement data content of bluetooth.
 *
 * @param[in] adv: advertisement data
 * @param[in] scan_resp: advertisement scan data
 *
 * @note This API is used for updating advertisement data of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_upd_adv_content(IN tuya_ble_data_buf_t *adv, IN tuya_ble_data_buf_t *scan_resp);

/**
 * @brief Get rssi info.
 *
 * @param[out] rssi: rssi info
 *
 * @note This API is used for getting rssi info.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_get_rssi(SCHAR_T *rssi);

/**
 * @brief Start advertising of bluetooth.
 *
 * @param void
 *
 * @note This API is used to start advertising of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_start_adv(void);

/**
 * @brief Stop advertising of bluetooth.
 *
 * @param void
 *
 * @note This API is used to stopping advertising of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_stop_adv(void);

/**
 * @brief Forbid advertising of bluetooth.
 *
 * @param void
 *
 * @note This API is used to forbid advertising of bluetooth.
 *
 * @return VOID
 */
VOID_T tuya_sdk_bt_forbid_adv(BOOL_T flag);

/**
 * @brief Get scan info of bluetooth.
 *
 * @param[out] info: scan info of bluetooth.
 *
 * @note This API is used for getting scan info of bluetooth for mf test
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_assign_scan(INOUT ty_bt_scan_info_t *info);

/**
 * @brief Get ability of bluetooth.
 *
 * @param VOID
 *
 * @note This API is used to getting ability of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_get_ability(VOID_T);


/**
 * @brief Init advertisement scanning of bluetooth.
 *
 * @param[in] scan_adv_cb: callback function of advertisement scanning
 * @param[in] scan_resp: advertisement scan data
 *
 * @note This API is used for Initializion for advertisement scanning of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_scan_init(IN TY_BT_SCAN_ADV_CB scan_adv_cb);

/**
 * @brief Start advertising scanning of bluetooth.
 *
 * @param VOID
 *
 * @note This API is used to start advertising scanning of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_start_scan(VOID_T);

/**
 * @brief Stop advertising scanning of bluetooth.
 *
 * @param VOID
 *
 * @note This API is used to stop advertising scanning of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_stop_scan(VOID_T);

// OPERATE_RET tuya_hal_bt_central_init(ty_ble_central_param_t *p);

// OPERATE_RET tuya_hal_bt_central_deinit(VOID_T);

// OPERATE_RET tuya_hal_bt_master_connect(UINT8_T mac[6], ty_ble_addr_type_t type, UINT_T timeout_ms, ty_ble_gap_conn_params_t *params);

// OPERATE_RET tuya_hal_bt_master_disconnect(UINT8_T mac[6], ty_ble_addr_type_t type);

// OPERATE_RET tuya_hal_bt_master_scan(BOOL_T enable);

// OPERATE_RET tuya_hal_bt_master_get_max_slave_num(UINT16_T *num);

// OPERATE_RET tuya_hal_bt_gattc_send_data(UINT8_T mac[6], UINT8_T *data, UINT_T length);

// OPERATE_RET tuya_hal_bt_gattc_start_discovery(UINT8_T mac[6], ty_bt_uuid_t *uuid);


/**
 * @brief Bluetooth interface initialization
 *
 * @param VOID
 *
 * @note This API is used for initialization of bluetooth interface.
 *
 * @return VOID
 */
//VOID_T tuya_os_bt_intf_init(VOID_T);


/**
 * @brief Get mac
 *
 * @param[out] mac: refer NW_MAC_S struct
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_get_mac(NW_MAC_S *mac);

/**
 * @brief Set mac
 *
 * @param[in] mac: refer NW_MAC_S struct
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_sdk_bt_set_mac(CONST NW_MAC_S *mac);

/**
 * @brief Update ble status for lp management.
 *
 * @param[in] adv_stat: ble adv status, 0xff-invalid
 * @param[in] conn_stat: ble connect status, 0xff-invalid
 * @param[in] adv_scan_stat: ble adv scan status, 0xff-invalid
 *
 * @note This API is used to update ble status for lp management.
 *
 * @return VOID
 */
VOID_T tuya_sdk_bt_upd_stat_for_lp(UINT8_T adv_stat, UINT8_T conn_stat, UINT8_T adv_scan_stat);

#endif

#endif



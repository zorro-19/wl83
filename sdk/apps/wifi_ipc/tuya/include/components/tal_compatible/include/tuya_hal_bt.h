/**
* @file tuya_hal_bt.h
* @brief Common process - Initialization
* @version 0.1
* @date 2020-11-09
*
* @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
*
*/
#ifndef TUYA_HAL_BT_H__
#define TUYA_HAL_BT_H__

#if defined(TY_BT_MOD) && (TY_BT_MOD==1)

#include "tuya_bt_basic_intf.h"

/**
 * @brief Init bluetooth.
 *
 * @param[in] p: parameters of bluetooth
 *
 * @note This API is used for initialization of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_port_init(p)   tuya_sdk_bt_port_init(p)

/**
 * @brief De-init bluetooth.
 *
 * @param void
 *
 * @note This API is used for de-initialization of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_port_deinit()   tuya_sdk_bt_port_deinit()

/**
 * @brief Disconnect bluetooth.
 *
 * @param void
 *
 * @note This API is used for disconnecting bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_gap_disconnect()    tuya_sdk_bt_gap_disconnect()

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
#define tuya_hal_bt_send(data, len)    tuya_sdk_bt_send(data, len)

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
#define tuya_hal_bt_reset_adv(adv, scan_resp)    tuya_sdk_bt_reset_adv(adv, scan_resp)

/**
 * @brief Get rssi info.
 *
 * @param[out] rssi: rssi info
 *
 * @note This API is used for getting rssi info.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_get_rssi(rssi)    tuya_sdk_bt_get_rssi(rssi)

/**
 * @brief Start advertising of bluetooth.
 *
 * @param void
 *
 * @note This API is used to start advertising of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_start_adv()    tuya_sdk_bt_start_adv()

/**
 * @brief Stop advertising of bluetooth.
 *
 * @param void
 *
 * @note This API is used to stopping advertising of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_stop_adv()    tuya_sdk_bt_stop_adv()

/**
 * @brief Get scan info of bluetooth.
 *
 * @param[out] info: scan info of bluetooth.
 *
 * @note This API is used for getting scan info of bluetooth for mf test
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_assign_scan(info)    tuya_sdk_bt_assign_scan(info)

/**
 * @brief Get ability of bluetooth.
 *
 * @param VOID
 *
 * @note This API is used to getting ability of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_get_ability()    tuya_sdk_bt_get_ability()


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
#define tuya_hal_bt_scan_init(scan_adv_cb)    tuya_sdk_bt_scan_init(scan_adv_cb)

/**
 * @brief Start advertising scanning of bluetooth.
 *
 * @param VOID
 *
 * @note This API is used to start advertising scanning of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_start_scan()    tuya_sdk_bt_start_scan()

/**
 * @brief Stop advertising scanning of bluetooth.
 *
 * @param VOID
 *
 * @note This API is used to stop advertising scanning of bluetooth.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_stop_scan()    tuya_sdk_bt_stop_scan()

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
VOID_T tuya_os_bt_intf_init(VOID_T);


/**
 * @brief Get mac
 *
 * @param[out] mac: refer NW_MAC_S struct
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_get_mac(mac)    tuya_sdk_bt_get_mac(mac)

/**
 * @brief Set mac
 *
 * @param[in] mac: refer NW_MAC_S struct
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define tuya_hal_bt_set_mac(mac)    tuya_sdk_bt_set_mac(mac)
#endif

#endif



#ifndef __TKL_BLUETOOTH_H__
#define __TKL_BLUETOOTH_H__

#include "tkl_bluetooth_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Function for initializing the ble stack
 * @param   role                Indicate the role for ble stack.
 *                              role = 1: ble peripheral    @TKL_BLE_ROLE_SERVER
 *                              role = 2: ble central       @TKL_BLE_ROLE_CLIENT
 * @return  SUCCESS             Initialized successfully.
 *          ERROR
 * */
OPERATE_RET tkl_ble_stack_init(UCHAR_T role);

/**
 * @brief   Function for de-initializing the ble stack features
 * @param   role                 Indicate the role for ble stack.
 *                               role = 1: ble peripheral
 *                               role = 2: ble central
 * @return  SUCCESS             Deinitialized successfully.
 *          ERROR
 * */
OPERATE_RET tkl_ble_stack_deinit(UCHAR_T role);

/**
 * @brief   Function for getting the GATT Link-Support.
 * @param   p_link              return gatt link
 * @return  SUCCESS             Support Gatt Link
 *          ERROR               Only Beacon or Mesh Beacon, Not Support Gatt Link.
 * */
OPERATE_RET tkl_ble_stack_gatt_link(USHORT_T *p_link);

/**
 * @brief   Register GAP Event Callback
 * @param   TKL_BLE_GAP_EVT_FUNC_CB Refer to @TKL_BLE_GAP_EVT_FUNC_CB
 * @return  SUCCESS         Register successfully.
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_callback_register(CONST TKL_BLE_GAP_EVT_FUNC_CB gap_evt);

/**
 * @brief   Register GATT Event Callback
 * @param   TKL_BLE_GATT_EVT_FUNC_CB Refer to @TKL_BLE_GATT_EVT_FUNC_CB
 * @return  SUCCESS         Register successfully.
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatt_callback_register(CONST TKL_BLE_GATT_EVT_FUNC_CB gatt_evt);

/******************************************************************************************************************************/
/** @brief Define All GAP Interface
 */
/**
 * @brief   Set the local Bluetooth identity address.
 *          The local Bluetooth identity address is the address that identifies this device to other peers.
 *          The address type must be either @ref TKL_BLE_GAP_ADDR_TYPE_PUBLIC or @ref TKL_BLE_GAP_ADDR_TYPE_RANDOM.
 * @param   [in] p_peer_addr:   pointer to local address parameters
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_addr_set(TKL_BLE_GAP_ADDR_T CONST *p_peer_addr);

/**
 * @brief   Get the local Bluetooth identity address.
 * @param   [out] p_peer_addr:  pointer to local address
 * @return  SUCCESS             Set Address successfully.
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_address_get(TKL_BLE_GAP_ADDR_T *p_peer_addr);

/**
 * @brief   Start advertising
 * @param   [in] p_adv_params : pointer to advertising parameters
 * @return  SUCCESS
 *  ERROR
 * */
OPERATE_RET tkl_ble_gap_adv_start(TKL_BLE_GAP_ADV_PARAMS_T CONST *p_adv_params);

/**
 * @brief   Stop advertising
 * @param   VOID
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_adv_stop(VOID);

/**
 * @brief   Setting advertising data
 * @param   [in] p_adv:         Data to be used in advertisement packets, and include adv data len
 *          [in] p_scan_rsp:    Data to be used in advertisement respond packets, and include rsp data len
 * @Note    Please Check p_adv and p_scan_rsp, if data->p_data == NULL or data->length == 0, we will not update these values.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_adv_rsp_data_set(TKL_BLE_DATA_T CONST *p_adv, TKL_BLE_DATA_T CONST *p_scan_rsp);

/**
 * @brief   Update advertising data
 * @param   [in] p_adv: Data    to be used in advertisement packets, and include adv data len
 *          [in] p_scan_rsp:    Data to be used in advertisement respond packets, and include rsp data len
 * @Note    Please Check p_adv and p_scan_rsp, if data->p_data == NULL or data->length == 0, we will not update these values.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_adv_rsp_data_update(TKL_BLE_DATA_T CONST *p_adv, TKL_BLE_DATA_T CONST *p_scan_rsp);

/**
 * @brief   Create extended advertising
 * @param   [in] p_ext_adv:     extended advertising handle
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_ext_adv_create(TKL_BLE_GAP_EXT_ADV_T *p_ext_adv);

/**
 * @brief   Config extended advertising
 * @param   [in] p_ext_adv:     extended advertising handle
 *          [in] p_adv_params:  pointer to advertising parameters
 *          [in] p_adv:         Data to be used in advertisement packets, and include adv data len
 *          [in] p_scan_rsp:    Data to be used in advertisement respond packets, and include rsp data len
 * @Note    Please Check p_adv and p_scan_rsp, if data->p_data == NULL or data->length == 0, we will not update these values.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_ext_adv_config(TKL_BLE_GAP_EXT_ADV_T ext_adv, TKL_BLE_GAP_EXT_ADV_PARAMS_T CONST *p_adv_params,
                                       TKL_BLE_DATA_T CONST *p_adv_data, TKL_BLE_DATA_T CONST *p_scan_rsp);

/**
 * @brief   Start extended advertising
 * @param   [in] p_ext_adv:     extended advertising handle
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_ext_adv_start(TKL_BLE_GAP_EXT_ADV_T ext_adv);

/**
 * @brief   Stop extended advertising
 * @param   [in] p_ext_adv:     extended advertising handle
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_ext_adv_stop(TKL_BLE_GAP_EXT_ADV_T ext_adv);

/**
 * @brief   Delete extended advertising
 * @param   [in] p_ext_adv:     extended advertising handle
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_ext_adv_delete(TKL_BLE_GAP_EXT_ADV_T ext_adv);

/**
 * @brief   Clear all extended advertising
 * @param   VOID
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_ext_adv_clear(void);

/**
 * @brief   Query the max data length of extended advertising supported by the controller
 * @param   VOID
 * @return  SUCCESS
 *          ERROR
 * */
uint16_t    tkl_ble_gap_ext_adv_get_max_data_length(void);

/**
 * @brief   Query the max number of extended advertising supported by the controller
 * @param   VOID
 * @return  SUCCESS
 *          ERROR
 * */
uint8_t     tkl_ble_gap_ext_adv_get_support_number(void);

/**
 * @brief   Start scanning
 * @param   [in] scan_param:    scan parameters including interval, windows
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_scan_start(TKL_BLE_GAP_SCAN_PARAMS_T CONST *p_scan_params);

/**
 * @brief   Stop scanning
 * @param   VOID
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_scan_stop(VOID);

/**
 * @brief   Start connecting one peer
 * @param   [in] p_peer_addr:   include address and address type
 *          [in] p_scan_params: scan parameters
 *          [in] p_conn_params: connection  parameters
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_connect(TKL_BLE_GAP_ADDR_T CONST *p_peer_addr, TKL_BLE_GAP_SCAN_PARAMS_T CONST *p_scan_params, TKL_BLE_GAP_CONN_PARAMS_T CONST *p_conn_params);

/**
 * @brief   Disconnect from peer
 * @param   [in] conn_handle:   the connection handle
 *          [in] hci_reason:    terminate reason
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_disconnect(USHORT_T conn_handle, UCHAR_T hci_reason);

/**
 * @brief   Start to update connection parameters
 * @param   [in] conn_handle:   connection handle
 *          [in] p_conn_params: connection  parameters
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_conn_param_update(USHORT_T conn_handle, TKL_BLE_GAP_CONN_PARAMS_T CONST *p_conn_params);

/**
 * @brief   Set the radio's transmit power.
 * @param   [in] role:          0: Advertising Tx Power; 1: Scan Tx Power; 2: Connection Power
 *          [in] tx_power:      tx power:This value will be magnified 10 times.
 *                              If the tx_power value is -75, the real power is -7.5dB.(or 40 = 4dB)
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_tx_power_set(UCHAR_T role, INT_T tx_power);

/**
 * @brief   Get the received signal strength for the last connection event.
 * @param   [in]conn_handle:    connection handle
 * @return  SUCCESS             Successfully read the RSSI.
 *          ERROR               No sample is available.
 * */
OPERATE_RET tkl_ble_gap_rssi_get(USHORT_T conn_handle);

/**
 * @brief   Set the GAP Name For Bluetooth
 * @param   [in]p_name:         GAP Name String
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gap_name_set(CHAR_T *p_name);

/**
 * @brief   Add Ble Gatt Service
 * @param   [in] p_service: define the ble service
 *
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatts_service_add(TKL_BLE_GATTS_PARAMS_T *p_service);

/**
 * @brief   [Optional] Indicates a change in attribute assignment to all subscribed peers(Specify conn_handle).
 *
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] start_handle   The start of the affected handle range.
 * @param   [in] end_handle     The end of the affected handle range.
 *
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatts_service_change(USHORT_T conn_handle, USHORT_T start_handle, USHORT_T end_handle);

/**
 * @brief   Set the value of a given attribute. After Config Tuya Read-Char, we can update read-value at any time.
 * @param   [in] conn_handle    Connection handle.
 *          [in] char_handle    Attribute handle.
 *          [in,out] p_value    Attribute value information.
 * @return  SUCCESS
 *          ERROR
 *
 * @note Values other than system attributes can be set at any time, regardless of whether any active connections exist.
 * */
OPERATE_RET tkl_ble_gatts_value_set(USHORT_T conn_handle, USHORT_T char_handle, UCHAR_T *p_data, USHORT_T length);

/**
 * @brief   Get the value of a given attribute.
 * @param   [in] conn_handle    Connection handle. Ignored if the value does not belong to a system attribute.
 * @param   [in] char_handle    Attribute handle.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatts_value_get(USHORT_T conn_handle, USHORT_T char_handle, UCHAR_T *p_data, USHORT_T length);

/**
 * @brief   Notify an attribute value.
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] char_handle    Attribute handle.
 *          [in] p_data         Notify Values
 *          [in] length         Value Length
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatts_value_notify(USHORT_T conn_handle, USHORT_T char_handle, UCHAR_T *p_data, USHORT_T length);

/**
 * @brief   Indicate an attribute value.
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] char_handle    Attribute handle.
 *          [in] p_data         Notify Values
 *          [in] length         Value Length
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatts_value_indicate(USHORT_T conn_handle, USHORT_T char_handle, UCHAR_T *p_data, USHORT_T length);

/**
 * @brief   Reply to an ATT_MTU exchange request by sending an Exchange MTU Response to the client.
 * @param   [in] conn_handle    Connection handle.
 *          [in] server_rx_mtu  mtu size.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gatts_exchange_mtu_reply(USHORT_T conn_handle, USHORT_T server_rx_mtu);

/******************************************************************************************************************************/
/** @brief Define All Gatt Client Interface, Refer to current ble gw and ble stack.
 *
 *  Notes: notice the handle will be the one of signed point.
 *  Discovery Operations belongs to GAP Interface, But declear here, because it will be used for the gatt client.
 */

/**
 * @brief   [Ble Central] Will Discovery All Service
 * @param   [in] conn_handle    Connection handle.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gattc_all_service_discovery(USHORT_T conn_handle);

/**
 * @brief   [Ble Central] Will Discovery All Characteristic
 * @param   [in] conn_handle    Connection handle.
 *          [in] start_handle   Handle of start
 *          [in] end_handle     Handle of End
 * @return  SUCCESS
 *          ERROR
 * @Note:   For Tuya Service, it may contains more optional service, it is more better to find all Characteristic
 *          instead of find specific uuid.
 * */
OPERATE_RET tkl_ble_gattc_all_char_discovery(USHORT_T conn_handle, USHORT_T start_handle, USHORT_T end_handle);

/**
 * @brief   [Ble Central] Will Discovery All Descriptor of Characteristic
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] conn_handle    Connection handle.
 *          [in] start_handle   Handle of start
 *          [in] end_handle     Handle of End
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gattc_char_desc_discovery(USHORT_T conn_handle, USHORT_T start_handle, USHORT_T end_handle);

/**
 * @brief   [Ble Central] Write Data without Response
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] char_handle    Attribute handle.
 *          [in] p_data         Write Values
 *          [in] length         Value Length
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gattc_write_without_rsp(USHORT_T conn_handle, USHORT_T char_handle, UCHAR_T *p_data, USHORT_T length);

/**
 * @brief   [Ble Central] Write Data with response
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] char_handle    Attribute handle.
 *          [in] p_data         Write Values
 *          [in] length         Value Length
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gattc_write(USHORT_T conn_handle, USHORT_T char_handle, UCHAR_T *p_data, USHORT_T length);

/**
 * @brief   [Ble Central] Read Data
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] char_handle    Attribute handle.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gattc_read(USHORT_T conn_handle, USHORT_T char_handle);

/**
 * @brief   Start an ATT_MTU exchange by sending an Exchange MTU Request to the server.
 * @param   [in] conn_handle    Connection handle.
 *          [in] client_rx_mtu  mtu size.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_gattc_exchange_mtu_request(USHORT_T conn_handle, USHORT_T client_rx_mtu);

/**
 * @brief   [Special Command Control] Base on Bluetooth, We can do some special commands for exchanging some informations.
 * @param   [in] opcode         Operations Opcode.
 *          [in] user_data      Post Some Special Commands Data.
 *          [in] data_len       User's Data Length.
 * @note    For Operations Codes, we can do anythings after exchange from TAL Application
 *          And We define some Opcodes as below for reference.
 *          For Bluetooth NCP Module: Mask=0x01, Code ID: 0x00~0xff. Opcode = ((0x01 << 8) & Code ID)
 *          eg:     0x0100: Special Vendor Module Init
 *                  0x0101: Special Vendor Module Deinit
 *                  0x0102: Special Vendor Module Reset
 *                  0x0103: Special Vendor Module Check Exist: Return OPRT_OK or OPRT_NOT_FOUND ..
 *                  0x0104: Specail Vendor Module Version Get.
 *                  0x0105: Specail Vendor Module Version Set.
 *                  0x0106: Specail Vendor Module Version Update.
 *                  0x0107: Specail Vendor Module Scan Switch.
 *                  0x0108: Specail Vendor Module Scan Stop.
 *                  0x0109: Specail Vendor Module Auth Check.
 *                  0x0110: Specail Vendor Module Auth Erase.
 *
 *  * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_vendor_command_control(USHORT_T opcode, VOID_T *user_data, USHORT_T data_len);

/**
 * @brief set ble mode, used in wifi ble coexist mode
 *
 * @param[in]       enable     enbale mode
 * @param[in]       mode       the ble mode
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_ble_set_mode(CONST BOOL_T enable, CONST UCHAR_T mode);

#ifdef __cplusplus
}
#endif

#endif


#ifndef __TKL_BLUETOOTH_SM_H__
#define __TKL_BLUETOOTH_SM_H__

#include "tkl_bluetooth_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************[Option][Bluetooth SecurityManager]********************************************/

#define TUYA_BLE_SM_IO_CAPS_DISPLAY_ONLY      0x00          /**< Display Only. */
#define TUYA_BLE_SM_IO_CAPS_DISPLAY_YESNO     0x01          /**< Display and Yes/No entry. */
#define TUYA_BLE_SM_IO_CAPS_KEYBOARD_ONLY     0x02          /**< Keyboard Only. */
#define TUYA_BLE_SM_IO_CAPS_NONE              0x03          /**< No I/O capabilities. */
#define TUYA_BLE_SM_IO_CAPS_KEYBOARD_DISPLAY  0x04          /**< Keyboard and Display. */

#define TUYA_BLE_SM_AUTH_KEY_TYPE_NONE        0x00          /**< No key (may be used to reject). */
#define TUYA_BLE_SM_AUTH_KEY_TYPE_PASSKEY     0x01          /**< 6-digit Passkey. */
#define TUYA_BLE_SM_AUTH_KEY_TYPE_OOB         0x02          /**< Out Of Band data. */

typedef enum {
    TUYA_BLE_SM_CONN_SEC_START = 0x01,                      /**< [Info Event] A security procedure has started on a link, initiated either locally or remotely. no action is needed for the procedure to proceed.*/

    TUYA_BLE_SM_CONN_SEC_SUCCEEDED,                         /**< A link has been encrypted, Will report the identified Address and the keys of the peer */

    TUYA_BLE_SM_CONN_SEC_FAILED,                            /**< A pairing or encryption procedure has failed. */

    TUYA_BLE_SM_PASSKEY_DISPLAY,                            /**< Request to display a passkey to the user.*/

    TUYA_BLE_SM_AUTH_KEY_REQUEST,                           /**< Request to provide an authentication key. */
} TUYA_BLE_SM_EVT_TYPE_E;

typedef struct {
    UINT8_T                             bond      : 1;      /**< Perform bonding. */
    UINT8_T                             mitm      : 1;      /**< Enable Man In The Middle protection. */
    UINT8_T                             lesc      : 1;      /**< Enable LE Secure Connection pairing. */
    UINT8_T                             keypress  : 1;      /**< Enable generation of keypress notifications. */
    UINT8_T                             io_caps   : 3;      /**< IO capabilities, see @ref TUYA_BLE_SM_IO_CAPS. */
    UINT8_T                             oob       : 1;      /**< The OOB data flag.*/

    UINT8_T                             key_size;           /**< Encryption key size in octets between @param key_size and 16. */
    UINT8_T                             enable_paring;      /**< [Optional] Start the Paring After enable @param enbale_paring or not. */
    USHORT_T                            bonding_num_max;    /**< The number of bonding */
} TUYA_BLE_SM_PARAMS_T;

typedef struct {
    UINT8_T                             bonding     : 1;    /**< The procedure of bonding that has started. */
    UINT8_T                             encryption  : 1;    /**< The procedure of encryption that has started. */
    UINT8_T                             reserved    : 6;    /**< Reserved bit */
} TUYA_BLE_SM_STATUS_PARAM_T;

typedef struct {
    TUYA_BLE_SM_STATUS_PARAM_T          status;             /**< Current SM Status */

    UINT8_T                             peer_irk[16];       /**< The irk of the peer */
    UINT8_T                             peer_ltk[16];       /**< The ltk of the peer, not the local ltk. */
    TKL_BLE_GAP_ADDR_T                  peer_address;       /**< The resolved address of the peer, will be shown on "SMP Identity Address Information"*/
    USHORT_T                            peer_index;         /**< Report the storage index if neccessary, indicate the peer id for one link. */
} TUYA_BLE_SM_INFO_PARAM_T;

typedef struct {
    UINT8_T                             index_flag : 1;     /**< The Flag of peer index, and post @param peer_index*/
    UINT8_T                             addr_flag  : 1;     /**< The Flag of peer address, and post @param peer_address */
    UINT8_T                             irk_flag   : 1;     /**< The Flag of peer irk, and post @param peer_irk */
    UINT8_T                             reserved_flag : 5;  /**< Reserved bit */

    union {
        USHORT_T                        peer_index;         /**< The index of the peer */
        TKL_BLE_GAP_ADDR_T              peer_address;       /**< The resolved address of the peer, will be shown on "SMP Identity Address Information"*/
        UINT8_T                         peer_irk[16];       /**< The irk of the peer */
    } source;
} TUYA_BLE_SM_SOURCE_ID_T;

typedef struct {
    TUYA_BLE_SM_EVT_TYPE_E              type;               /**< Security Manager Protocol Event */
    USHORT_T                            conn_handle;        /**< Connection Handle */
    INT_T                               result;             /**< Will Refer to HOST STACK Error Code */

    union {
        TUYA_BLE_SM_STATUS_PARAM_T      security_fail;      /**< Report fail event for this link, See @ref TUYA_BLE_SM_FAIL_EVT_T. */
        TUYA_BLE_SM_INFO_PARAM_T        security_success;   /**< Show successful info for this security link, See @ref TUYA_BLE_SM_SUCCESS_EVT_T. */
        UINT8_T                         display_passkey[6]; /**< Display the passkey for user. */
        UINT8_T                         request_key_type;   /**< Report the key type for requesting, See @ref TUYA_BLE_SM_AUTH_KEY. */
    } sm_event;
} TUYA_BLE_SM_PARAMS_EVT_T;

typedef VOID(*TUYA_BLE_SM_FUNC_CB)(TUYA_BLE_SM_PARAMS_EVT_T *p_event);

/**
 * @brief   [Optional][SM Required] Init the Security Manager And Post The Correct Parameters
 *
 * @param   [in] p_security_parameter   the pointer of security parameters.
 * @return  SUCCESS
 *          ERROR   Must have either IO capabilities or OOB if MITM.
 * */
OPERATE_RET tkl_ble_security_manager_init(TUYA_BLE_SM_PARAMS_T CONST *p_security_parameter);

/**
 * @brief   [Optional][SM Required] Register the Callback While Using Security Manager.
 *
 * @param   [in] security_callback      the callback of security event, @ref TUYA_BLE_SM_PARAMS_EVT_T
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_security_callback_register(CONST TUYA_BLE_SM_FUNC_CB security_callback);

/**
 * @brief   [Optional][SM Required][Ble Peripheral/Central] Security Request, Function For Initiate the GAP Authentication procedure.
 * In the central role, this function will send an SMP Pairing Request (or an SMP Pairing Failed if rejected),
 * Otherwise in the peripheral role, an SMP Security Request will be sent.
 *
 * @param   [in] conn_handle    Connection handle.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_security_request(USHORT_T conn_handle);

/**
 * @brief   [Optional][Ble Central] Encryption Request, Function For Initiate GAP Encryption procedure
 * In the central role, this function will initiate the encryption procedure using the encryption information provided.
 *
 * @param   [in] conn_handle    Connection handle.
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_encryption_request(USHORT_T conn_handle);

/**
 * @brief   [Optional][SM Required][Ble Peripheral] Reply with an authentication key. Function Using During Authentication Procedures
 * Check the Key Type During Repling the info, if key_type = 0 @def TUYA_BLE_SM_AUTH_KEY , Will Reject this Auth Request
 *
 * @param   [in] conn_handle    Connection handle.
 * @param   [in] key_type       key type for this event @ref TUYA_BLE_SM_AUTH_KEY_REQUEST+ @param request_key_type
 * @param   [in] p_key          If key type is @ref TUYA_BLE_SM_AUTH_KEY_TYPE_NONE, then NULL.
 *                              If key type is @ref TUYA_BLE_SM_AUTH_KEY_TYPE_PASSKEY, then a 6-byte ASCII string (digit 0..9 only, no NULL termination)
 *                              or NULL when confirming LE Secure Connections Numeric Comparison.
 *                              If key type is @ref TUYA_BLE_SM_AUTH_KEY_TYPE_OOB, then a 16-byte OOB key value in little-endian format.
 * @return  SUCCESS
 *          ERROR
 * @note    Please Check the key_type and p_key, will reject this procedure if key_type = TUYA_BLE_SM_AUTH_KEY_TYPE_NONE or p_key = NULL
 *
 * */
OPERATE_RET tkl_ble_security_key_reply(USHORT_T conn_handle, UINT8_T key_type, UINT8_T CONST *p_key);

/**
 * @brief   [Optional] Get the Bonding Information.
 *
 * @param   [in] peer_index     The Peer Index for bonding information.
 * @param   [out] p_info_get    The information for one peer.
 *
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_security_info_get(TUYA_BLE_SM_SOURCE_ID_T *source_id, TUYA_BLE_SM_INFO_PARAM_T *p_info_get);

/**
 * @brief   [Optional] Delete the Bonding Information.
 *
 * @param   [in] peer_index     The Peer Index for bonding information.
 *
 * @return  SUCCESS
 *          ERROR
 * */
OPERATE_RET tkl_ble_security_info_delete(TUYA_BLE_SM_SOURCE_ID_T *source_id);

#ifdef __cplusplus
}
#endif

#endif


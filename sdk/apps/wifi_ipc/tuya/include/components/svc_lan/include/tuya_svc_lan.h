/**
 * @file tuya_svc_lan.h
 * @brief TUYA LAN service
 * @version 0.1
 * @date 2019-08-20
 *
 * @copyright Copyright 2019-2021 Tuya Inc. All Rights Reserved.
 *
 */

#ifndef __TUYA_SVC_LAN_H__
#define __TUYA_SVC_LAN_H__

#include <stdint.h>
#include "tuya_cloud_types.h"
#include "ty_cJSON.h"
#include "tuya_svc_netmgr_linkage.h"

#ifdef __cplusplus
extern "C" {
#endif

// LAN protocol frame type
#define FRM_TP_CFG_WF           0x01 // only used for ap 3.0 network config
#define FRM_TP_ACTV             0x02 // discard
#define FRM_TP_BIND_DEV         0x03 // discard
#define FRM_TP_UNBIND_DEV       0x06 // discard
#define FRM_TP_CMD              0x07 //
#define FRM_TP_STAT_REPORT      0x08 //
#define FRM_TP_HB               0x09 //
#define FRM_QUERY_STAT          0x0a //
#define FRM_SSID_QUERY          0x0b // discard
#define FRM_USER_BIND_REQ       0x0c // {"token","yyyyyyyyyyyyyy"}
#define FRM_TP_NEW_CMD          0x0d //
#define FRM_ADD_SUB_DEV_CMD     0x0e //
#define FRM_CFG_WIFI_INFO       0x0f // {"ssid":"xxxx","passwd":"yyyyy"}
#define FRM_QUERY_STAT_NEW      0x10 //
#define FRM_SCENE_EXEC          0x11 //
#define FRM_LAN_QUERY_DP        0x12 //

#define FRM_SECURITY_TYPE3 0x03
#define FRM_SECURITY_TYPE4 0x04
#define FRM_SECURITY_TYPE5 0x05

#define FRM_TYPE_REG_CENTER 0x24
#define FRM_TYPE_APP_UDP_BOARDCAST 0x25
#define FRM_TYPE_LAN_FILE   0x26

#define FRM_LAN_EXT_STREAM      0x40
#define FRM_LAN_EXT_BEFORE_ACTIVATE 0x42
#define FRM_LAN_UPD_LOG    0x30

/**
 * @brief Definition of LAN configuration
 */
typedef enum {
    CFG_UDP_DISCOVERY_FORCE,    // send upd discovery even if clients exceed(BOOL_T)
    CFG_UDP_EXT_UPDATE,         // add/update new key/value(ty_cJSON)
    CFG_UDP_EXT_DELETE,         // delete key/value(ty_cJSON)
    CFG_SET_CLT_NUM,            // set clinet number(UINT_T)
    CFG_UDP_DISCOVERY_INTERVAL, // set udp discovery interval(UINT_T, unit:s, default:5)
    CFG_REV_BUF_SIZE,           // receive buffer size(UINT, default:512)
    CFG_SET_LAN_CLOSED_CB,      // set lan can be closed
    CFG_DEFAULT_LINKAGE,        // default lan linkage (netmgr_linkage_t)
    CFG_HEART_BEAT_TIMEOUT,     // set heart beat time out(default 30)
    CFG_DEBUG_SWITCH,           // debug switch(BOOL_T)
    CFG_SEQ_ERR_THRESHOLD,      // sequence error threshold(default 0)
    CFG_WIFI_NETCFG,            // token bind use wifi
    CFG_MAX
} Lan_Cfg_e;

/**
 * @brief Init and start LAN service
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_init(VOID);

/**
 * @brief Stop and uninit LAN service
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_exit(VOID);

/**
 * @brief Disable LAN service
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_disable(VOID);

/**
 * @brief Enable LAN service
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_enable(VOID);

/**
 * @brief LAN dp report
 *
 * @param[in] data data buf
 * @param[in] len buf length
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_dp_report(IN VOID *data, IN CONST UINT_T len);

/**
 * @brief distribute data to all connections
 *
 * @param[in] fr_type refer to LAN_PRO_HEAD_APP_S
 * @param[in] ret_code refer to LAN_PRO_HEAD_APP_S
 * @param[in] data refer to LAN_PRO_HEAD_APP_S
 * @param[in] len refer to LAN_PRO_HEAD_APP_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_data_report(IN CONST UINT_T fr_type, IN CONST UINT_T ret_code,
                                     IN CONST BYTE_T *data, IN CONST UINT_T len);

/**
 * @brief get count of vaild connections
 *
 * @return vaild count
 */
INT_T tuya_svc_lan_get_valid_connections(VOID);

/**
 * @brief disconnect all connections
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_disconnect_all(VOID);

/**
 * @brief lan configure
 *
 * @param[in] cfg refer to Lan_Cfg_e
 * @param[in] data buf
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_cfg(IN CONST Lan_Cfg_e cfg, IN CONST VOID *data);

/**
 * @brief lan cmd extersion
 *
 * @param[in] data data of frame type
 * @param[out] out data to send back (shall be string const)
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
typedef OPERATE_RET(*lan_cmd_handler_cb)(IN CONST BYTE_T *data, OUT BYTE_T **out);

/**
 * @brief register callback
 *
 * @param[in] frame_type refer to LAN_PRO_HEAD_APP_S
 * @param[in] frame_type refer to lan_cmd_handler_cb
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_register_cb(IN UINT_T frame_type, IN lan_cmd_handler_cb handler);

/**
 * @brief unregister callback
 *
 * @param[in] frame_type refer to LAN_PRO_HEAD_APP_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_unregister_cb(IN UINT_T frame_type);

/**
 * @brief get lan client number
 *
 * @return client number
 */
UINT_T tuya_svc_lan_get_client_num(VOID);

/**
 * @brief Callback to handle lan protocol data
 *
 * @param[in] root_json Json encoded protocol data
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
typedef OPERATE_RET(*lan_ext_protocol_handler_cb)(IN ty_cJSON *root_json);

/**
 * @brief Register extend lan protocol
 *
 * @param[in] ext_lan_pro Protocol string
 * @param[in] handler Protocol handler
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_ext_proto_reg(CONST CHAR_T *ext_lan_pro, lan_ext_protocol_handler_cb handler);

/**
 * @brief Unregister extend lan protocol
 *
 * @param[in] ext_lan_pro Protocol string
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_ext_proto_unreg(CONST CHAR_T *ext_lan_pro);

/**
 * @brief uninit extend lan protocol
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_ext_proto_uninit(VOID);

/**
 * @brief extend lan protocol data report
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_lan_ext_proto_data_report(IN CONST VOID *data, IN CONST UINT_T len);

/**
 * @brief check lan canbe closed
 *
 * @return TRUE:can be closed,FALSE:can't be closed
 */
typedef BOOL_T(*lan_canbe_closed)(VOID);

/**
 * @brief check lan can be closed
 *
 * @return TRUE: canbe closed,FALSE:can't be closed
 */
BOOL_T tuya_svc_lan_canbe_closed(VOID);

typedef struct {
    INT_T socket;
    UINT_T frame_num;
    UINT_T frame_type;
    UINT_T frame_len;
} LAN_EXT_CMD_PARAM_S;

OPERATE_RET tuya_svc_lan_pro_cntl_get_ext_cmd_param(LAN_EXT_CMD_PARAM_S *ext_cmd_param);

OPERATE_RET tuya_svc_lan_data_com_send(IN CONST INT_T socket, IN CONST UINT_T fr_num, IN CONST UINT_T fr_type,
                                       IN CONST UINT_T ret_code, IN CONST BYTE_T *data, IN CONST UINT_T len);

OPERATE_RET tuya_svc_lan_set_linkage_priority(IN LINKAGE_TYPE_E *types, IN UINT_T count);

/**
 * @brief judge if lan connect
 *
 * @return TRUE/FALSE
 */
#define is_lan_connected() (tuya_svc_lan_get_valid_connections() != 0)

#ifdef __cplusplus
}
#endif
#endif //__TUYA_SVC_LAN_H__


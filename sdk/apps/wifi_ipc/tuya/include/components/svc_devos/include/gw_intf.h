/**
* @file gw_intf.h
* @brief Facility of DevOS definitions
* @version 0.1
* @date 2015-08-22
*
* @copyright Copyright 2015-2021 Tuya Inc. All Rights Reserved.
*/

#ifndef _GW_INTF_H
#define _GW_INTF_H

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_base_utilities.h"
#include "tuya_iot_internal_api.h"
#include "tuya_error_code.h"
#include "tal_mutex.h"

#if defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE==1)
#include "tuya_cloud_wifi_defs.h"
#include "tal_wifi.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SERIAL_NO_STR_LEN 32    // max string length of sn
#define GET_ACCESS_TOKEN_INTERVAL  (300 * 1000) //5min

/**
 * @brief auth info for ext module
 */
typedef struct {
    CHAR_T uuid[GW_UUID_LEN + 1];    //uuid
    CHAR_T auth_key[AUTH_KEY_LEN + 1]; /** auth key */
    CHAR_T psk_key[PSK_KEY_LEN + 1]; /** psk key */
} TY_EXT_AUTH_INFO;

/**
 * @brief Definition gw BASE information
 */
typedef struct {
    /** uuid, assigned by TUYA */
    CHAR_T uuid[GW_UUID_LEN + 1];
    /** psk1.0/2.0 key only */
    CHAR_T psk_key[PSK_KEY_LEN + 1];
    /** auth key */
    CHAR_T auth_key[AUTH_KEY_LEN + 1];

#if defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE==1)
    /** ap ssid info */
    CHAR_T ap_ssid[WIFI_SSID_LEN + 1];
    /** ap passwd info */
    CHAR_T ap_passwd[WIFI_PASSWD_LEN + 1];

#endif
#if (defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE==1)) || (defined(GW_SUPPORT_COUNTRY_CODE) && (GW_SUPPORT_COUNTRY_CODE==1))
    /** country code */
    CHAR_T country_code[COUNTRY_CODE_LEN];
#endif
#if defined(GPRS_GW) && (GPRS_GW==1)
    /** imei */
    CHAR_T imei[TUYA_IMEI_LEN + 1];
    /** sn */
    CHAR_T sn[TUYA_SN_LEN + 1];
#endif
    /** production test */
    BOOL_T prod_test;
#if defined(ENABLE_BT_SERVICE) && (ENABLE_BT_SERVICE == 1)
    /** bt mac */
    CHAR_T bt_mac[BT_MAC_LEN + 1];
    /** bt hid */
    CHAR_T bt_hid[BT_HID_LEN + 1];
#endif
    /** fac_pin == pid */
    CHAR_T fac_pin[20 + 1];
    /** psk3.0 key */
    CHAR_T psk30_key[PSK_KEY_LEN + 1];
    /** pin for wifi qrcode */
    CHAR_T pin[10];
} GW_BASE_IF_S;

// gw register status
typedef BYTE_T GW_WORK_STAT_T;
#define UNREGISTERED 0 // unregistered
#define REGISTERED 1 // registered & activate start
#define ACTIVATED 2 // already active
#define PROXY_ACTIVING    (3)//start ble active
#define PROXY_ACTIVATED   (4) // ble actived

/**
 * @brief Definition of device work state
 */
typedef struct {
#if defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE==1)
    /** see GW_WF_NWC_STAT_T, valid when gateway is wireless */
    GW_WF_NWC_STAT_T nc_tp;
    /** see GW_WF_MD_T */
    GW_WF_MD_T md;
    /** ssid */
    CHAR_T ssid[WIFI_SSID_LEN + 1];
    /** passwd */
    CHAR_T passwd[WIFI_PASSWD_LEN + 1];
#endif
    /** dns priority, see TY_DNS_PRIO_T */
    TY_DNS_PRIO_T dns_prio; // not saved in kv to save flash life-cycle
    /** work state, see GW_WORK_STAT_T */
    GW_WORK_STAT_T stat;
    /** token, recvive from app */
    CHAR_T token[TOKEN_LEN + 1];
    /** region, recvive from app */
    CHAR_T region[REGION_LEN + 1];
    /** regist key, recvive from app */
    CHAR_T regist_key[REGIST_KEY_LEN + 1];
    /** check if it was psk30 app config */
    BOOL_T is_psk30_cfg;
} GW_WORK_STAT_MAG_S;

/**
 * @brief Definition of device description info
 */
typedef struct {
    /** ability, see GW_ABI */
    GW_ABI abi;
    /** virtual id */
    CHAR_T id[GW_ID_LEN + 1];
    /** firmware ver, format xx.xx.xx */
    CHAR_T sw_ver[SW_VER_LEN + 1];
    /** base version xx.xx */
    CHAR_T bs_ver[SW_VER_LEN + 1];
    /** protocol version */
    CHAR_T prtl_ver[SW_VER_LEN + 1];
    /** lan protocol version */
    CHAR_T lan_prtl_ver[SW_VER_LEN + 1];
    /** cad version */
    CHAR_T cad_ver[SW_VER_LEN + 1];
    /** cd version */
    CHAR_T cd_ver[SW_VER_LEN + 1];
    /** KEY of product */
    CHAR_T product_key[PRODUCT_KEY_LEN + 1];
    /** KEY of firmware */
    CHAR_T firmware_key[PRODUCT_KEY_LEN + 1];

    /** networklink module single device struct */
    CHAR_T dev_sw_ver[SW_VER_LEN + 1];
    /** schema id */
    CHAR_T schema_id[SCHEMA_ID_LEN + 1];
    /** device ota channel */
    DEV_TYPE_T tp;

    /** count of GW attach attribute */
    BYTE_T attr_num;
    /** GW attach attribute */
    GW_ATTACH_ATTR_T attr[GW_ATTACH_ATTR_LMT];

    /** need sync or not */
    BOOL_T sync;
} GW_DESC_IF_S;

/**
 * @brief Definition of stride update info
 */
typedef struct {
    /** KEY of product */
    CHAR_T product_key[PRODUCT_KEY_LEN + 1];
    /** KEY of firmware */
    CHAR_T firmware_key[PRODUCT_KEY_LEN + 1];
} GW_STRIDE_UPDATE_S;

/**
 * @brief Definition of active info
 */
typedef struct {
    /** key used by HTTP */
    CHAR_T key[SEC_KEY_LEN + 1];
    /** key used by lan/mqtt/... */
    CHAR_T local_key[LOCAL_KEY_LEN + 1];
    /** domain of http */
    CHAR_T http_url[HTTP_URL_LMT + 1];
    /** ip of http */
    CHAR_T http_ip[HTTP_URL_LMT + 1];
    /** domain of https */
    CHAR_T https_url[HTTP_URL_LMT + 1];
    /** ip of https */
    CHAR_T https_ip[HTTP_URL_LMT + 1];
    /** domain of https-psk */
    CHAR_T httpsPSK_url[HTTP_URL_LMT + 1];
    /** ip of https-psk */
    CHAR_T httpsPSK_ip[HTTP_URL_LMT + 1];

    /** domain of mqtt psk */
    CHAR_T mq_psk_url[MQ_URL_LMT + 1];
    /** ip of mqtt psk */
    CHAR_T mq_psk_ip[MQ_URL_LMT + 1];
    /** domain of mqtts */
    CHAR_T mq_tls_url[MQ_URL_LMT + 1];
    /** ip of mqtts */
    CHAR_T mq_tls_ip[MQ_URL_LMT + 1];
    /** domain of mqtt */
    CHAR_T mq_proto_url[MQ_URL_LMT + 1];
    /** ip of mqtt */
    CHAR_T mq_proto_ip[MQ_URL_LMT + 1];
    /** domain of ai speech */
    CHAR_T ai_speech_url[HTTP_URL_LMT + 1];
    /** ip of ai speech */
    CHAR_T ai_speech_ip[HTTP_URL_LMT + 1];
    /** domain of lowpower */
    CHAR_T lowpower_url[MQ_URL_LMT + 1];
    /** ip of lowpower */
    CHAR_T lowpower_ip[MQ_URL_LMT + 1];

    /** timezone */
    CHAR_T time_zone[TIME_ZONE_LEN + 1];
    /** summer timezone */
    CHAR_T summer_time_zone[SUMMER_TM_ZONE_LEN + 1];

    /** app id, assigned by WX */
    CHAR_T wx_app_id[WXAPPID_LEN + 1];
    /** uuid of wx */
    CHAR_T wx_uuid[WXUUID_LEN + 1];
    /** cloud capability */
    INT_T cloud_capability;

    /** 0:invalid 1:disable 2:psk_only 3:ecc_psk 4:ecc_only 6:client auth */
    BYTE_T dynamic_tls_mode;
} GW_ACTV_IF_S;

/**
 * @brief Denifition of capability in cloud
*/
#define CLOUD_CAPABILITY_WIFI         0     // wifi
#define CLOUD_CAPABILITY_CABLE        1     // cable
#define CLOUD_CAPABILITY_GPRS         2     // gprs
#define CLOUD_CAPABILITY_NBIOT        3     // nb-iot
#define CLOUD_CAPABILITY_BLUETOOTH    10    // bt
#define CLOUD_CAPABILITY_BLEMESH      11    // blemesh
#define CLOUD_CAPABILITY_ZIGBEE       12    // zigbee
#define CLOUD_CAPABILITY_INFRARED     13    // infrared
#define CLOUD_CAPABILITY_SUBPIECES    14    // subpieces
#define CLOUD_CAPABILITY_SIGMESH      15    // sigmesh
#define CLOUD_CAPABILITY_MCU          16    // mcu

/**
 * @brief Definiton of DP status
 */
typedef BYTE_T DP_PV_STAT_E;
#define INVALID 0       // dp is invalid
#define VALID_LC 1      // dp is valid in local
#define VALID_ULING 2   // dp is uploading to cloud
#define VALID_CLOUD 3   // dp is synced with cloud

/**
 * @brief Definition of dp id report rule
 */
typedef BYTE_T DP_ID_REPT_TYPE_E;
#define DP_ID_REPT_RULE_ROUTE    (0x1) //dp report rule from route

/**
 * @brief Definition of dp report flow control unit
 */
typedef struct {
    UINT_T   period; // long filter period
    UINT_T   limit;  // dpcount limit in long filter period
    UINT_T   rept_cnt; // report counter
    TIME_S   fir_rept_timestamp;//the first report success timestamp
} DP_REPT_FLOW_CTRL_UNIT;

/**
 * @brief Definition of dp report flow control
 */
typedef struct {
    DP_REPT_FLOW_CTRL_UNIT filter_short;//flow control rules for short period
    DP_REPT_FLOW_CTRL_UNIT filter_long;//flow control rules for long period
} DP_REPT_FLOW_CTRL;

#if defined(RELIABLE_TRANSFER) && (RELIABLE_TRANSFER==1)
/**
 * @brief Definition of dp current set report control
 */
typedef struct {
    /** cur set time */
    TIME_S cur_set_time;
    /** cur set rept num */
    UINT_T cur_set_rept_num;
} DP_CUR_SET_REPT_CNTL_S;
#endif

/**
 * @brief Definition of dp  control
 */
typedef struct {
    /** see DP_DESC_IF_S */
    DP_DESC_IF_S dp_desc;
    /** see DP_PROP_VALUE_U */
    DP_PROP_VALUE_U prop;
    /** cache status, see DP_PV_STAT_E */
    DP_PV_STAT_E pv_stat;
    BYTE_T       uling_cnt;
    /** see DP_REPT_FLOW_CTRL */
    DP_REPT_FLOW_CTRL rept_flow_ctrl;
    /** time stamp for dp sync */
    UINT_T time_stamp;
    /** sn for ble dp sync report */
    UINT_T ble_send_sn;
#if defined(RELIABLE_TRANSFER) && (RELIABLE_TRANSFER==1)
    /** see TIME_S */
    TIME_S rept_new_time;
    /** current dp cmd value, see DP_PROP_VALUE_U  */
    DP_PROP_VALUE_U cur_set;
    /** see DP_CUR_SET_REPT_CNTL_S */
    DP_CUR_SET_REPT_CNTL_S cur_set_rept;
    /** whether to check consistency between dp cmd value and actual state */
    BYTE_T is_set_flag;//是否要检查当前下发的值与实际状态是否一样
#endif
} DP_CNTL_S;


/**
 * @brief Definition of schema other attribute
 */
typedef struct {
    /** need preprecess or not */
    BOOL_T preprocess;
} SCHEMA_OTHER_ATTR_S;


#define GRP_LMT 64 // group limit
#define SCENE_LMT 64 // scene limit
#define LOG_PHAT_MAX_LEN 64

/**
 * @brief Definition of group info
 */
typedef struct {
    /** group id */
    CHAR_T gid[GRP_ID_LEN + 1];
} GRP_REC_S;

/**
 * @brief Definition of scene info
 */
typedef struct {
    /** secene id */
    CHAR_T s_id[SCENE_ID_LEN + 1];
    /** group id */
    CHAR_T g_id[GRP_ID_LEN + 1];
} SCENE_REC_S;

/**
 * @brief Definition of group management
 */
typedef struct {
    /** group info */
    GRP_REC_S g_rec[GRP_LMT];
    /** group count */
    BYTE_T cnt;
} GRP_MAG_S;

/**
 * @brief Definition of scene management
 */
typedef struct {
    /** secene info */
    SCENE_REC_S s_rec[SCENE_LMT];
    /** secene count */
    BYTE_T cnt;
} SCENE_MAG_S;

/**
 * @brief Definition of device actv attribute
 */

typedef struct {
    /** is attach dp info or not */
    BOOL_T attach_dp_if;
    /** need preprecess or not */
    BOOL_T preprocess;
} DEV_ACTV_ATTR_S;

/**
 * @brief Definition of device control info
 */
typedef struct dev_cntl_n_s {
    /** virtual id */
    CHAR_T id[DEV_ID_LEN + 1];
    /** device attribute, see DEV_ACTV_ATTR_S */
    DEV_ACTV_ATTR_S attr;
#if defined(RELIABLE_TRANSFER) && (RELIABLE_TRANSFER==1)
    /** support reliable transfer or not */
    BYTE_T reliable_transfer_flag;//1表示要可靠性检测
#endif

    /** exclusive access to dp */
    MUTEX_HANDLE dp_mutex;//dp本地缓存互斥锁
    /** count of dp */
    BYTE_T dp_num;
    /** dp info */
    DP_CNTL_S dp[0];
} DEV_CNTL_N_S;

/**
 * @brief Handler to get sub-device control info
 *
 * @param[in] id Virtual id of sub-device
 *
 * @return See DEV_CNTL_N_S, NULL on error
 */
typedef DEV_CNTL_N_S *(*subdev_dev_cntl_get_cb)(IN CHAR_T *id);

/**
 * @brief Definition of core device management
 */
typedef struct {
    /** serial num */
    CHAR_T *serial_no;
    /** see DEV_ATTRIBUTE */
    UINT_T ext_attribute;
    /** Extension state, see GW_EXT_STAT_T */
    GW_EXT_STAT_T ext_stat;

    /** Is oem device or not */
    BOOL_T is_oem;
    /** Inited or not */
    BOOL_T is_init;
    /** Is stride(pid/key) or not */
    BOOL_T is_stride;
    /** Is need recovery or not */
    BOOL_T is_need_recovery;

    /** device base info, see GW_BASE_IF_S */
    GW_BASE_IF_S gw_base;
    /** device work state management, see GW_WORK_STAT_MAG_S */
    GW_WORK_STAT_MAG_S gw_wsm;
    /** device description info, see GW_DESC_IF_S */
    GW_DESC_IF_S gw_if;
    /** device active info, see GW_ACTV_IF_S */
    GW_ACTV_IF_S gw_actv;

    /** device manage */
    DEV_CNTL_N_S *dev_cntl;

    /** nofity callback */
    TY_IOT_CBS_S cbs;

    /** global data update time */
    TIME_MS data_update_time;
    /** sub-device related info */
    subdev_dev_cntl_get_cb subdev_dev_get_cb;
} GW_CNTL_S;

typedef BYTE_T GW_RESET_TP_T;
#define GRT_LOCAL 0     // reset is triggerd by device itself
#define GRT_REMOTE 1    // reset is triggerd by cloud/app

/**
 * @brief Definition of gateway device reset info
 */
typedef struct {
    /** reset type, see GW_RESET_TP_T */
    GW_RESET_TP_T gw_rst_tp;
    /** FALSE: reset all, TRUE: reset linkage*/
    BOOL_T lazy;
} GW_RESET_S;

/**
 * @brief Definition of sub-device reset info
 */
typedef struct {
    /** reset type, see GW_RESET_TP_T */
    GW_RESET_TP_T tp;
    /** virtual id of sub-device */
    CHAR_T dev_id[DEV_ID_LEN + 1];
} DEV_RESET_S;

/**
 * @brief Definition Wi-Fi country code
 */
typedef enum {
    /** China */
    TY_COUNTRY_CODE_CN,
    /** USA */
    TY_COUNTRY_CODE_US,
    /** Japan */
    TY_COUNTRY_CODE_JP,
    /** Europe */
    TY_COUNTRY_CODE_EU
} TUYA_COUNTRY_CODE_E;

/**
 * @brief Get gateway device cntl
 *
 * @return Gateway device cntl, see DEV_CNTL_N_S
 */
DEV_CNTL_N_S *get_gw_dev_cntl(VOID);

/**
 * @brief Get gateway description
 *
 * @return Gateway description, see GW_DESC_IF_S
 */
GW_DESC_IF_S *get_gw_dev_if(VOID);

/**
 * @brief Get device cntl
 *
 * @param[in] id Device id, NULL indicates gateway
 *
 * @return Device cntl, see DEV_CNTL_N_S
 */
DEV_CNTL_N_S *get_dev_cntl(IN CHAR_T *id);

/**
 * @brief Get DP cntl
 *
 * @param[in] id Device id
 * @param[in] dpid DP id
 *
 * @return DP cntl, see DP_CNTL_S
 */
DP_CNTL_S *get_dev_dp_cntl(IN CHAR_T *id, IN CONST BYTE_T dpid);

/**
 * @brief Get gateway cntl
 *
 * @return Gateway cntl, see GW_CNTL_S
 */
GW_CNTL_S *get_gw_cntl(VOID);

/**
 * @brief Get device schema info
 *
 * @param[in] dev_id Device id
 * @param[in] dp_num Count of dp
 * @param[out] dp_info DP info
 *
 * @note Caller shall free the returned memory explictly
 *
 * @return Schema info, NULL on fail
 */
CHAR_T *tuya_get_schema(VOID);

/**
 * @brief Get device dp info
 *
 * @param[in] dev_id Device id
 * @param[in] dp_num Count of dp
 * @param[out] dp_info DP info
 *
 * @note Caller shall free the memory of dp_info explictly
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_get_dp_info(IN CONST CHAR_T *dev_id, INT_T *dp_num, DP_CNTL_S **dp_info);

/**
 * @brief Get device ota channel
 *
 * @param[in] type Device type
 * @param[out] gpd Device ota channel
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_get_gpd_type(IN CONST UINT_T type, OUT GW_PERMIT_DEV_TP_T *gpd);

/**
 * @brief Set device extension attribute
 *
 * @param[in] attr Device extension attribute
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_set_ext_attribute(UINT_T attr);

/**
 * @brief Get device extension attribute
 *
 * @return Device extension attribute
 */
UINT_T gw_get_ext_attribute(VOID);

/**
 * @brief Create device cntl instance
 *
 * @param[in] dev_id Device ID
 * @param[in] sch_json Device schema
 * @param[out] dev_cnt Device cntl
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_create_dev_cntl(IN CONST CHAR_T *dev_id, IN CONST CHAR_T *sch_json, OUT DEV_CNTL_N_S **dev_cnt_out);

/**
 * @brief Destroy device cntl instance
 *
 * @param[in] dev_cnt Device cntl
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_destroy_dev_cntl(IN DEV_CNTL_N_S *dev_cnt);

/**
 * @brief Duplicate device cntl
 *
 * @param[in] dev_cnt_src Original device cntl
 * @param[out] dev_cnt_out New device cntl
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_dup_dev_cntl(IN DEV_CNTL_N_S *dev_cnt_src,  OUT DEV_CNTL_N_S **dev_cnt_out);

/**
 * @brief Register handler to get sub-device cntl
 *
 * @param[in] cb Callback to get sub-device cntl
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_subdev_dev_cntl_get_register_cb(IN subdev_dev_cntl_get_cb cb);

/**
 * @brief Faset reset device to register state
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_fast_unactive(IN CONST GW_RESET_S *rst_t);

/**
 * @brief Reset device to unregister state
 *
 * @param[in] rst_t Reset type, see GW_RESET_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_unregister(IN CONST GW_RESET_S *rst_t);

/**
 * @brief Reset device to register state
 *
 * @param[in] rst_t Reset type, see GW_RESET_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_unactive(IN CONST GW_RESET_S *rst_t);

/**
 * @brief Enable hot reset
 *
 * @param[in] flag
 *
 * @return VOID
 */
VOID_T tuya_devos_enable_hot_reset(BOOL_T flag);

/**
 * @brief Check devos is support hot reset
 *
 * @param[in] VOID
 *
 * @return BOOL_T
 */
BOOL_T tuya_devos_is_hot_reset(VOID_T);

/**
 * @brief Get last reset region
 *
 * @param[in] region buffer with length REGION_LEN + 1
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET gw_get_last_reset_region(INOUT CHAR_T *region);
VOID gw_clear_last_reset_region(VOID);

#ifdef __cplusplus
}
#endif

#include "tuya_devos_utils.h"

#endif


/**
* @file iot_httpc.h
* @brief HTTP APIs to interact with TUYA cloud
* @version 0.1
* @date 2015-05-27
*
* @copyright Copyright 2015-2021 Tuya Inc. All Rights Reserved.
*
*/

#ifndef _IOT_HTTPC_H
#define _IOT_HTTPC_H

#include "tuya_cloud_types.h"
#include "ty_cJSON.h"
#include "gw_intf.h"
#include "http_inf.h"
#include "tuya_matop.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief POST HTTP request without memory realloc
 *
 * @param[in] api_name Name of API
 * @param[in] api_ver Version of API
 * @param[in] uuid UUID of device
 * @param[in] devid ID of device
 * @param[in] post_data Pointer to data
 * @param[in] data_total_len Length of data
 * @param[in] p_head_other Additional header to send
 * @param[out] pp_result Json encoded result
 *
 * @note Caller ot this API shall ensure data buffer is bigger enough to include data padding
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_common_post_no_remalloc(IN CONST CHAR_T *api_name, IN CONST CHAR_T *api_ver, IN CONST CHAR_T *uuid, IN CONST CHAR_T *devid, IN CHAR_T *post_data, IN UINT_T data_total_len, IN CONST CHAR_T *p_head_other, OUT ty_cJSON **pp_result);
/**
 * @brief POST HTTP request
 *
 * @param[in] api_name Name of API
 * @param[in] api_ver Version of API
 * @param[in] uuid UUID of device
 * @param[in] devid ID of device
 * @param[in] post_data Pointer to data
 * @param[in] p_head_other Additional header to send
 * @param[out] pp_result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_common_post(IN CONST CHAR_T *api_name, IN CONST CHAR_T *api_ver, IN CONST CHAR_T *uuid, IN CONST CHAR_T *devid, IN CHAR_T *post_data, IN CONST CHAR_T *p_head_other, OUT ty_cJSON **pp_result);
OPERATE_RET httpc_common_post_raw(IN CONST CHAR_T *url, IN CONST CHAR_T *api_name, IN CONST CHAR_T *api_ver,
                                  IN CONST CHAR_T *uuid, IN CONST CHAR_T *aes_key, IN CONST CHAR_T *devid,
                                  IN CHAR_T *post_data, IN UINT_T data_total_len, IN CONST CHAR_T *p_head_other,
                                  OUT ty_cJSON **pp_result);

OPERATE_RET httpc_common_post_session(IN CONST CHAR_T *api_name, IN CONST CHAR_T *api_ver, IN CONST CHAR_T *uuid, IN CONST CHAR_T *devid, IN CHAR_T *post_data, IN CONST CHAR_T *p_head_other, OUT ty_cJSON **pp_result);

OPERATE_RET httpc_common_post_sesssion_raw(
    IN CONST CHAR_T *url,
    IN CONST CHAR_T *api_name, IN CONST CHAR_T *api_ver,
    IN CONST CHAR_T *uuid, IN CONST CHAR_T *aes_key, IN CONST CHAR_T *devid,
    IN CHAR_T *post_data, IN UINT_T data_total_len, IN CONST CHAR_T *p_head_other,
    OUT ty_cJSON **pp_result, BOOL_T is_session);

/**
 * @brief Get the count of local timers
 *
 * @param[in] lastFetchTime Last fetch time returned
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_get_timer_cnt(IN CONST INT_T lastFetchTime, OUT ty_cJSON **result);

/**
 * @brief Get the count of local timers, without flow limit
 *
 * @param[in] lastFetchTime Last fetch time returned
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_notify_timer_cnt(IN CONST INT_T lastFetchTime, OUT ty_cJSON **result);

/**
 * @brief Get content local timers
 *
 * @param[in] offset Timer index
 * @param[in] limit Max count of timers
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_get_timer_content(IN CONST INT_T offset, IN CONST INT_T limit, OUT ty_cJSON **result);

/**
 * @brief Transfer HTTP error string to error code
 *
 * @param[in] ErroValu HTTP error state
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_gw_extra_erro_code_tranfer(char *ErroValu);

/**
 * @brief Reset device
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_reset(IN CONST GW_WORK_STAT_T stat);

/**
 * @brief Retrieve URLs from TUYA IoT DNS service, device will use URLs to interact with
 * TUYA cloud later on
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_iot_dns_get_cloud_url(VOID);

/**
 * @brief Retrieve special URLs from TUYA IoT DNS service, device will use URLs to interact with
 * TUYA cloud later on
 *
 * @param[in] env Device runtime env
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_iot_dns_get_fast_cloud_url(CHAR_T *env);

/**
 * @brief Load URLs and related Ips of TUYA cloud to DNS cache
 *
 */
VOID http_iot_dns_cache_cloud_url(VOID);

/**
 * @brief Use TUYA IoT DNS service to translate domain to ip
 *
 * @param[in] domain Domain name
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_iot_dns_get_host_ip(IN CONST CHAR_T *domain, OUT ty_cJSON **result);

/**
 * @brief Register a device on TUYA cloud
 *
 * @param[out] result Json encoded result
 *
 * @note This API is deprecated
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_register_V41(OUT ty_cJSON **result);

/**
 * @brief Register and active a device on TUYA cloud
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_active_v41(OUT ty_cJSON **result);

/**
 * @brief Dynamic mesh gw Register and active a device on TUYA cloud
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_active_mesh(IN CONST CHAR_T *data, OUT ty_cJSON **result);

/**
 * @brief Update versions of device on TUYA cloud
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_update_version_v41(VOID);

/**
 * @brief Pre-active of FFS netcfg
 *
 * @param[in] wss_token wss token
 * @param[in] gw_endpoint gateway endpoint
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_ffs_pre_active(IN CONST CHAR_T *wss_token, IN CONST CHAR_T *gw_endpoint);

typedef OPERATE_RET(*HTTP_GW_GET_FILE_DATA_CB)(IN PVOID_T priv_data, IN CONST UINT_T total_len, IN CONST UINT_T offset, \
        IN CONST BYTE_T *data, IN CONST UINT_T len, OUT UINT_T *remain_len);
/**
 * @brief Download file
 *
 * @param[in] url URL of the file to download
 * @param[in] mlk_buf_len block size of dowload buffer
 * @param[in] gfd_cb Hander when download file
 * @param[in] priv_data Private data
 * @param[in] total_len Total length of file
 * @param[in] p_key HTTP decode key
 * @param[in] key_len Lenght od decode key
 * @param[in,out] file_hmac HMAC of download file
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_get_file(IN CONST CHAR_T *url, IN CONST UINT_T mlk_buf_len,
                           IN CONST HTTP_GW_GET_FILE_DATA_CB gfd_cb, IN PVOID_T priv_data,
                           IN CONST UINT_T total_len,  IN CONST UINT_T offset,
                           IN CONST BYTE_T *p_key, IN CONST UINT_T key_len, INOUT BYTE_T file_hmac[32]);
#define http_gw_download_file(url, mlk_buf_len, gfd_cb, priv_data, total_len, p_key, key_len, file_hmac) \
        httpc_get_file(url, mlk_buf_len, gfd_cb, priv_data, total_len, 0, p_key, key_len, file_hmac)


/**
 * @brief Retrieve PSK key
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_pskkey_get(OUT ty_cJSON **result);

/**
 * @brief Upload information of device reset to TUYA cloud
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_put_rst_log(VOID);

/**
 * @brief Definition of dynamic config
 */
typedef enum {
    /** time zone */
    HTTP_DYNAMIC_CFG_TZ = 0x0001,
    /** rate rule for dp */
    HTTP_DYNAMIC_CFG_RATERULE = 0x0002,
    /** senior ability */
    HTTP_DYNAMIC_CFG_SENIOR_ABILITY = 0x0004,
    /** all configs */
    HTTP_DYNAMIC_CFG_ALL = 0xFFFF
} HTTP_DYNAMIC_CFG_TYPE;

/**
 * @brief Retrieve dynamic config
 *
 * @param[in] type Defined by HTTP_DYNAMIC_CFG_TYPE
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_dynamic_cfg_get(IN CONST HTTP_DYNAMIC_CFG_TYPE type, OUT ty_cJSON **result);

/**
 * @brief ACK of dynamic config(some configs need ack to ensure it is handled correctly)
 *
 * @param[in] timezone_ackId ACK id of timezone
 * @param[in] rateRule_actId ACK id of dp rate rule
 * @param[in] ability_actId ACK id of senior ability
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_dynamic_cfg_ack_v20(IN CONST CHAR_T *timezone_ackId, IN CONST CHAR_T *rateRule_actId, IN CONST CHAR_T *ability_actId);

/**
 * @brief Upload config to TUYA cloud
 *
 * @param[in] data Private data to upload
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_put_cloud_config(IN CONST CHAR_T *data);

/**
 * @brief Save property to TUYA cloud
 *
 * @param[in] data Private data to upload
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_property_save(IN CONST CHAR_T *data);

/**
 * @brief Definition of status to check
 */
typedef enum {
    /** Unknown status */
    DEV_STATUS_UNKNOWN,
    /** Device need reset */
    DEV_STATUS_RESET,
    /** Device need refactory */
    DEV_STATUS_RESET_FACTORY,
    /** Device is normal */
    DEV_STATUS_ENABLE,
} DEV_SYNC_STATUS_E;

/**
 * @brief Retrieve device status
 *
 * @param[out] p_status Device status on TUYA cloud, defined by DEV_SYNC_STATUS_E
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_dev_sync_check(DEV_SYNC_STATUS_E *p_status);

/**
 * @brief Sync device status
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_dev_sync_proc(VOID_T);

/**
 * @brief Retrieve certs of special domain
 *
 * @param[in] url_msg Domain name to get certs
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_iot_certificate_get_v10(OUT ty_cJSON **result, IN CONST CHAR_T *url_msg);

/**
 * @brief Retrieve encrypt key of cloud storage
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_iot_cloud_storage_encrypt_key_get(OUT ty_cJSON **result);

/**
 * @brief Retrieve customized config
 *
 * @param[in] biztype Customized key
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_custom_cfg_get(IN CONST INT_T biztype, OUT ty_cJSON **result);

/**
 * @brief Register and active a device on TUYA cloud
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_get_active_info(OUT ty_cJSON **result);
/**
 * @brief Retrieve location info
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_gw_location_info_get(OUT ty_cJSON **result);

typedef PVOID_T RAW_HTTP_S;
/**
 * @brief Read header of raw HTTP respose
 *
 * @param[in,out] pp_raw_http Pointer to RAW_HTTP_S
 * @param[out] p_status_code Status code from HTTP response
 * @param[out] p_chunked Data is chunk or not
 * @param[out] p_content_len Total length of response content
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_raw_read_resp_header(INOUT RAW_HTTP_S p_raw_http, OUT INT_T *p_status_code, OUT BOOL_T *p_chunked, OUT UINT_T *p_content_len);

/**
 * @brief Read content of raw HTTP response
 *
 * @param[in] pp_raw_http Pointer to RAW_HTTP_S
 * @param[in] buf Pointer of data to write
 * @param[in] buf_len Length of buffer
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
INT_T httpc_raw_read_content(IN RAW_HTTP_S p_raw_http, IN BYTE_T *buf, IN CONST UINT_T buf_len);

/**
 * @brief Write raw HTTP request
 *
 * @param[in] pp_raw_http Pointer to RAW_HTTP_S
 * @param[in] buf Pointer of data to write
 * @param[in] buf_len Length of buffer
 * @param[in] chunked Is chunk enabled
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
INT_T httpc_raw_write_content(IN RAW_HTTP_S p_raw_http, IN CONST BYTE_T *buf, IN CONST UINT_T buf_len, BOOL_T chunked);

/**
 * @brief Close raw HTTP request
 *
 * @param[in] pp_raw_http Pointer to RAW_HTTP_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_raw_close(IN RAW_HTTP_S p_raw_http);

/**
 * @brief Raw HTTP POST request
 *
 * @param[in] p_url URL to request
 * @param[in] data_total_len Total length of raw request
 * @param[in,out] pp_raw_http Pointer to RAW_HTTP_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_raw_post(IN CONST CHAR_T *p_url, IN CONST UINT_T data_total_len, INOUT RAW_HTTP_S *pp_raw_http);

/**
 * @brief Raw HTTP GET request
 *
 * @param[in] p_url URL to request
 * @param[in,out] pp_raw_http Pointer to RAW_HTTP_S
 * @param[in] offset Offset of buffer
 * @param[in] total_len Total length of buffer
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
#define httpc_raw_get(p_url, pp_raw_http, offset, total_len) \
    httpc_raw_get_with_head(p_url, pp_raw_http, offset, total_len, NULL, NULL) \

/**
 * @brief Raw HTTP GET request
 *
 * @param[in] p_url URL to request
 * @param[in,out] pp_raw_http Pointer to RAW_HTTP_S
 * @param[in] offset Offset of buffer
 * @param[in] total_len Total length of buffer
 * @param[in] add_head_cb Hook before HTTP request sent, to add more HTTP header
 * @param[in] add_head_data Header data of add_head_cb
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_raw_get_with_head(IN CONST CHAR_T *p_url, INOUT RAW_HTTP_S *pp_raw_http,
                                    IN UINT_T offset, IN UINT_T total_len,
                                    IN HTTP_HEAD_ADD_CB add_head_cb,
                                    IN VOID *add_head_data);

/**
 * @brief Raw HTTP PUT request
 *
 * @param[in] p_url URL to request
 * @param[in] data_total_len Total length of raw request
 * @param[in,out] pp_raw_http Pointer to RAW_HTTP_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_raw_put(IN CONST CHAR_T *p_url, IN CONST UINT_T data_total_len, INOUT RAW_HTTP_S *pp_raw_http);

/**
 * @brief Retrieve token from cloud
 *
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_get_dev_token_create_v20(OUT ty_cJSON **result);

/**
 * @brief Retrieve active HTTP url of TUYA cloud
 *
 * @return NULL on error.
 */
CHAR_T *http_active_url(VOID);

/**
 * @brief Retrieve active HTTP url of TUYA cloud
 *
 * @return NULL on error.
 */
CHAR_T *http_url(VOID);

/**
 * @brief Retrieve short url of QR active
 *
 * @param[in] uuid UUID of device
 * @param[in] appid ID of app
 * @param[out] result Json encoded result
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET httpc_active_shorturl_get(char *uuid, char *appid, ty_cJSON **result);

/**
 * @brief Enalbe wifi after activated by BLE
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET http_ble_actived_enable_wifi(VOID);
OPERATE_RET tuya_get_ble_beacon_key(OUT CHAR_T **beaconKey);
OPERATE_RET http_inf_client_post_field_psk_mode(IN CONST CHAR_T *url,
        IN CONST HTTP_INF_CB callback,
        IN CONST BYTE_T *data,
        IN CONST UINT_T len,
        IN HTTP_HEAD_ADD_CB add_head_cb,
        IN VOID *add_head_data,
        IN CONST CHAR_T *p_decode_key,
        INOUT PVOID_T *pri_data,
        IN CONST http_hdr_field_sel_t field_flags);

OPERATE_RET httpc_dev_ext_module_report(OUT ty_cJSON **result);

/**
 * @brief Definition of Atop Access enable
 */
typedef enum {
    ATOP_TYPE_ONLINE_DEBUG_LOG,    // "atop.online.debug.log"
    ATOP_TYPE_GET_DYNAMIC_CFG,     // "tuya.device.dynamic.config.get"
    ATOP_TYPE_GET_TIMER_COUNT,     // "tuya.device.timer.count"
    ATOP_TYPE_GET_UPGRADE_SILENT,  // "tuya.device.upgrade.silent.get"
    ATOP_TYPE_GET_NEWEST_SCHEMA,   // "tuya.device.schema.newest.get"
    ATOP_TYPE_UPDATE_VERSION       // "tuya.device.versions.update"
} ATOP_TYPE_E;

typedef enum {
    ATOP_ACCESS_DISABLE,
    ATOP_ACCESS_ENABLE
} ATOP_ACCESS_E;

/**
 * @brief set atop access enable or disable
 *
 * @param[in] atop type
 * @param[in] atop access
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_set_atop_access(ATOP_TYPE_E type, ATOP_ACCESS_E access);

/**
 * @brief Enable or disable time update from httpc (enable by default)
 *
 * @param[in] is_auto_update Auto update from httpc or not
 */
VOID httpc_update_localtime_set(BOOL_T is_auto_update);

typedef BOOL_T(*ATOP_API_DEBUG)(IN CHAR_T *api);

#ifdef __cplusplus
}
#endif
#endif


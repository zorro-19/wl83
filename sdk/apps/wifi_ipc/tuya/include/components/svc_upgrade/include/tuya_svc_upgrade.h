/**
* @file tuya_svc_upgrade.h
* @brief TUYA OTA service
* @version 0.1
* @date 2019-08-28
*
* @copyright Copyright 2019-2021 Tuya Inc. All Rights Reserved.
*/

#ifndef __TUYA_SVC_UPGRADE_H__
#define __TUYA_SVC_UPGRADE_H__

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "ty_cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STACK_SIZE_UPGRADE
#define STACK_SIZE_UPGRADE (4096) //Bytes
#endif

typedef BYTE_T TI_UPGRD_STAT_S;
#define TUS_RD 1 // ready
#define TUS_UPGRDING 2 // upgrading
#define TUS_UPGRD_FINI 3 // finish
#define TUS_UPGRD_EXEC 4 // error

#define TUS_DOWNLOAD_START 10 // download start
#define TUS_DOWNLOAD_COMPLETE 11 // download complete
#define TUS_UPGRADE_START 12 // upgrade start
#define TUS_UPGRADE_SUCCESS 3 //upgrade success

#define TUS_DOWNLOAD_ERROR_UNKONW 40 // unknown error
#define TUS_DOWNLOAD_ERROR_LOW_BATTERY 41 // low battery
#define TUS_DOWNLOAD_ERROR_STORAGE_NOT_ENOUGH 42 // storage not enough
#define TUS_DOWNLOAD_ERROR_MALLOC_FAIL 43 // malloc fail
#define TUS_DOWNLOAD_ERROR_TIMEOUT 44 // download timeout
#define TUS_DOWNLOAD_ERROR_HMAC 45 // hmac not match
#define TUS_UPGRADE_ERROR_LOW_BATTERY 46 // low battery
#define TUS_UPGRADE_ERROR_MALLOC_FAIL 47 // malloc fail
#define TUS_UPGRADE_ERROR_VERSION 48 // version invalid
#define TUS_UPGRADE_ERROR_HMAC 49 // hmac not match

/*
* @param[out] dev_id device id for gw or nodeId for subdev
* @return OPERATE_RET OPRT_OK indicates a valid device need detect
*/
typedef OPERATE_RET(*UPGRADE_GET_DEV)(OUT CHAR_T dev_id[DEV_ID_LEN + 1]);

/*
* @param[in] is_err TRUE indicates error happen, detect process is over
* @param[in] is_exe valid when !is_err
                TRUE indicates upgrade is got and notified
                FALSE indicates upgrade is got but execute time not arrival
* @param[in] detect_interval valid when !is_err && !is_exe
                         upgrade should be detected again after detect_interval(s)
*/
typedef VOID (*UPGRADE_DETECT_RESULT)(IN BOOL_T is_err, IN BOOL_T is_exe, IN UINT_T detect_interval);

/**
 * @brief Definition of firmware upgrade workload
 */
typedef struct {
    UPGRADE_GET_DEV upgrade_get_dev;
    UPGRADE_DETECT_RESULT upgrade_detect_result;
} TUYA_UPGRADE_DETECT_T;

/**
 * @brief Handler of GW upgrade inform
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
typedef INT_T(*DEV_UPGRADE_INFORM_CB)(CONST FW_UG_S *fw);

/**
 * @brief Handler of pre-process inform
 */
typedef VOID (*DEV_UPGRADE_PRE_INFORM_CB)(BOOL_T *handled, CONST FW_UG_S *fw);

/**
 * @brief Handler of sub-device upgrade inform
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
typedef INT_T(*SUBDEV_UPGRADE_INFORM_CB)(CONST CHAR_T *dev_id, CONST FW_UG_S *fw);

/**
 * @brief Handler of process inform for some upgrade type
 *
 * @return OPRT_OK on had handled. Others should process by svc_upgrade
 */
typedef INT_T(*dev_upgrade_mq15_inform_cb)(ty_cJSON *root_json);

/**
 * @brief Definition of firmware upgrade handler
 */
typedef struct {
    /** Handler of gw upgrade inform */
    DEV_UPGRADE_INFORM_CB dev_upgrade_cb;
    /** Handler of sub-device upgrade inform */
    SUBDEV_UPGRADE_INFORM_CB subdev_upgrade_cb;
    /** Handler of gw upgrade pre-precess */
    DEV_UPGRADE_INFORM_CB pre_dev_upgrade_cb;
    /** Handler of sub-device pre-precess */
    SUBDEV_UPGRADE_INFORM_CB pre_subdev_upgrade_cb;
} TUYA_UPGRADE_PARAM_T;

/**
 * @brief Initilize firmware upgrade framework
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_init(TUYA_UPGRADE_PARAM_T *ota_param);

/**
 * @brief Need upgrade or not(multi-section ota)
 *
 * @return TRUE or FALSE
 */
BOOL_T tuya_svc_devos_get_upgrade(VOID);
TUYA_OTA_PATH_E tuya_upgrade_get_path(VOID);

/**
 * @brief Continue to process multi section upgrade
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_continue(VOID_T);

/**
 * @brief Run firmware upgrade framework, workloads registered will be executed
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_active(VOID_T);

/**
 * @brief Register a new firmware upgrade workload
 *
 * @param[in] detect The workload, see tuya_upgrade_detect_t
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_detect_register(TUYA_UPGRADE_DETECT_T *detect);

/**
 * @brief Register process handler for some upgrade type
 *
 * @param[in] mq15_cb The process handler
 */
VOID tuya_svc_upgrade_register_mq15_cb(dev_upgrade_mq15_inform_cb mq15_cb);

OPERATE_RET tuya_svc_upgrade_ug_info_parse(ty_cJSON *result, UPGRADE_TYPE_T type, FW_UG_S *ug_info);

/**
 * @brief Register pre-precess handler to replace the default one
 *
 * @param[in] pre_ug_cb The new handler
 */
VOID tuya_svc_upgrade_register_pre_cb(DEV_UPGRADE_PRE_INFORM_CB pre_ug_cb);

/**
 * @brief Reset firmware upgrade check interval
 *
 * @param[in] upgrade_interval Next interval to check(unit sec)
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_detect_reset(CONST INT_T upgrade_interval);

/**
 * @brief Refuse to download the specific firmware
 *
 * @param[in] dev_id ID of sub-device, or NULL for GW
 * @param[in] fw Firmware info to download
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_refuse(CONST FW_UG_S *fw, CONST CHAR_T *dev_id);

/**
 * @brief Sync dowload result to cloud
 *
 * @param[in] dev_id ID of sub-device, or NULL for GW
 * @param[in] tp OTA channel, see DEV_TYPE_T
 * @param[in] result See TI_UPGRD_STAT_S
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_result_report(CONST CHAR_T *dev_id, CONST DEV_TYPE_T type, CONST int result);

/**
 * @brief Start to download the specific firmware
 *
 * @param[in] dev_id ID of sub-device, or NULL for GW
 * @param[in] fw Firmware info to download
 * @param[in] get_file_cb Callback to transfer data while downloading
 * @param[in] pri_data Private data
 * @param[in] upgrd_nofity_cb Callback when upgrade complete or error
 * @param[in] upload_upgrade_percent Upload upgrade percent or not
 * @param[in] download_buf_size Buffer size allocated for OTA
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_svc_upgrade_start(CONST CHAR_T *dev_id,
                                   CONST FW_UG_S *fw,
                                   CONST GET_FILE_DATA_CB get_file_cb,
                                   VOID *pri_data,
                                   CONST UPGRADE_NOTIFY_CB upgrd_nofity_cb,
                                   CONST BOOL_T upload_upgrade_percent,
                                   CONST UINT_T download_buf_size);

/**
* @brief Notify to upgrade immediately like mqtt15
*
* @param[in] dev_id ID of sub-device, or NULL for GW
* @param[in] dev type to upgrade
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tuya_svc_upgrade_mqtt_notify(CHAR_T *dev_id, DEV_TYPE_T tp);

/**
* @brief 局域网升级启动
*
* @param[in] p_ug_info 升级固件信息
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tuya_lan_upgrade_start(ty_cJSON *p_upgrade_info);

/**
* @brief 局域网升级数据处理
*
* @param[in] p_data_block 升级固件数据块指针
* @param[in] u_data_block_len 数据块长度
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tuya_lan_upgrade_data_proc(BYTE_T *p_data_block, UINT_T u_data_block_len);

/**
* @brief 局域网升级数据请求
*
* @param[out] request_string 升级固件数据请求字符串，包括file_offset, data_block_len
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tuya_lan_upgrade_data_request_string(CHAR_T *request_string);

/**
* @brief enable mqtt notify
*
*/
VOID tuya_svc_upgrade_enable_mqtt_notify();

#define SVC_UPGRADE_SIGN_CONTENT_MAX_LEN 4096

typedef enum {
    SignContent_TYPE_USER = 0,
    SignContent_TYPE_TUYA = 1,
}
SignContent_TYPE;

typedef struct {
    uint8_t *pub_key_der;
    uint32_t pub_key_der_size;
    int8_t *pub_key_name;
} key_pub_info;

typedef struct {
    uint32_t sign_content_len;
    uint32_t magiclow;
    uint32_t magichigh;
} SignHead;
typedef struct {
    uint32_t type;
    uint32_t usage;
    uint32_t alg;
    int8_t *user_id;
    int8_t *key_name;
    int8_t *sign_time;
    int8_t *fw_key;
    int8_t *fw_ver;
    uint8_t *sig_value;
    uint32_t sig_value_len;
} SignBlock;
typedef struct {
    int8_t *version;
    uint32_t num;
    SignBlock *block;
} SignContent;
typedef struct {
    uint32_t save_addr;
    uint32_t len;
} file_info;

#if defined(ENABLE_FIRMWARE_SIGN_USER) && (ENABLE_FIRMWARE_SIGN_USER == 1)
OPERATE_RET tuya_svc_upgrade_set_user_pub_key(uint8_t *pub_key_der, uint32_t der_size, int8_t *pub_key_name);
OPERATE_RET tuya_svc_upgrade_set_tuya_pub_key(uint8_t *pub_key_der, uint32_t der_size, int8_t *pub_key_name);
#endif
OPERATE_RET tuya_svc_upgrade_verify_init(void);
OPERATE_RET tuya_svc_upgrade_verify_process(IN CONST FW_UG_S *fw, IN CONST UINT_T total_len, \
        IN CONST UINT_T offset, IN CONST BYTE_T *data, \
        IN CONST UINT_T len, OUT UINT_T *remain_len, IN PVOID_T pri_data);
OPERATE_RET tuya_svc_upgrade_verify_end(IN CONST FW_UG_S *fw, IN CONST INT_T download_result, IN PVOID_T pri_data);
#ifdef __cplusplus
}
#endif

#endif

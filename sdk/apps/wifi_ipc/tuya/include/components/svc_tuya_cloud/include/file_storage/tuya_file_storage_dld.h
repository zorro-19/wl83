/**
 * @file tuya_file_storage_dld.h
 * @brief file storage download
 * @version 0.1
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2023 Tuya Inc. All Rights Reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), Under the premise of complying
 * with the license of the third-party open source software contained in the software,
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software.
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 */

#ifndef _TUYA_FILE_STORAGE_DLD_H
#define _TUYA_FILE_STORAGE_DLD_H

#include <stdio.h>
#include <stdlib.h>
#include "tuya_cloud_types.h"
#include "ty_cJSON.h"

typedef enum {
    /** all file trans start notify*/
    FILE_DL_TYPE_START = 0,
    /** single file trans start */
    FILE_DL_TYPE_TRANS_START = 1,
    /** single file trans */
    FILE_DL_TYPE_TRANS = 2,
    /** single file trans end */
    FILE_DL_TYPE_TRANS_END = 3,
    /** all file trans end notify */
    FILE_DL_TYPE_END = 4,
    /** query file exist or not */
    FILE_DL_TYPE_QUERY = 5,
    /** delete file */
    FILE_DL_TYPE_DELETE = 6,
} FILE_DL_NOTIFY_TYPE_E;

typedef struct {
    /** prefix of file */
    CHAR_T prefix[16];
    /** count of files */
    UINT_T files_count;
} FILE_DL_START_INFO_T;

typedef struct {
    /** file name */
    CHAR_T *file_name;
    /** file title, optional*/
    CHAR_T *title;
    /** 0:picture, 1:video*/
    UINT_T file_type;
    /** file coordinates x, vaild when file type was 0*/
    INT_T center_x;
    /** file coordinates y, vaild when file type was 0*/
    INT_T center_y;
    /** used to picture like report */
    CHAR_T meta[64];
} FILE_DL_TRANS_START_INFO_T;

typedef struct {
    /** file data len */
    UINT_T len;
    /** file data */
    UCHAR_T *data;
} FILE_DL_TRANS_INFO_T;

typedef struct {
    /** trans end ret 0:success, other failed*/
    UINT_T ret;
} FILE_DL_TRANS_END_INFO_T;

typedef struct {
    /** app actual upload file count*/
    UINT_T upd_fc;
    /** SDK actual download file count*/
    UINT_T dld_fc;
} FILE_DL_END_INFO_T;

//query file, return 1:exist, 0:not exist
typedef struct {
    /** file name */
    CHAR_T *file_name;
} FILE_DL_QUERY_DEL_INFO_T;

/**
 * @brief file storage download notify
 *
 * @param[in] type see FILE_DL_NOTIFY_TYPE_E
 * @param[in] info notify data info
 * @param[out] errmsg error message if failed
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
typedef OPERATE_RET(*FILE_DL_NOTIFY)(FILE_DL_NOTIFY_TYPE_E type, VOID *info, CHAR_T **errmsg);

typedef struct {
    CHAR_T resolution[16]; //"1920*1080"
    /** support format, include picture and video */
    CHAR_T allow_formats[8][8]; //"jpg,png,mp4"
    /** default 10*1024*1024, optional */
    UINT_T max_per_file_size;
    /** max file cnt per trans, default 10, optional */
    UINT_T max_file_cnt;
    /** file http download unit size, default 32*1024 */
    UINT_T unit_size;
    /** file data notify */
    FILE_DL_NOTIFY notify_cb;
} FILE_DL_CONFIG_CB_T;

/**
 * @brief set file storage download config
 *
 * @param[in] config app set config
 *
 * @note called after iot init, canbe in pre_device_init
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_file_storage_dl_set_config(FILE_DL_CONFIG_CB_T config);

/**
 * @brief file storage local event report
 *
 * @param[in] prefix file prefix
 * @param[in] name file name
 * @param[in] meta file meta
 * @param[in] event opt event
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tuya_file_storage_dl_mq_rept(CHAR_T *prefix, CHAR_T *name, CHAR_T *meta, CHAR_T *event);
#endif
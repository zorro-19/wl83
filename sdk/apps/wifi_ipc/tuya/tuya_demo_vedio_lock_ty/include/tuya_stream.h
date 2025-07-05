/**
 * @file    tuya_stream.h
 * @author  mengjinlong@tuya.com
 * @brief
 * @version 1.0
 * @date    2024-03-11
 * @copyright Copyright (c) tuya.inc 2020
 */
#ifndef _TY_PHOTO_AND_STREAM_H
#define _TY_PHOTO_AND_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  __TY_PHOTO_AND_STREAM_GLOBALS
#define __TY_PHOTO_AND_STREAM_EXT
#else
#define __TY_PHOTO_AND_STREAM_EXT extern
#endif

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"

#define  TRIGGER_64_OPEN_LCD   0


#define PT_EVENT_ALARM_PRY              0x0000
#define PT_EVENT_ALARM_REMOTE           0x0001
#define PT_EVENT_ALARM_FINGER           0x0002
#define PT_EVENT_ALARM_PSW              0x0003
#define PT_EVENT_ALARM_CARD             0x0004
#define PT_EVENT_ALARM_FACE             0x0005
#define PT_EVENT_ALARM_HAND             0x0006
#define PT_EVENT_ALARM_VEIN             0x0007
#define PT_EVENT_ULOCK_FIGER            0x0008
#define PT_EVENT_ULOCK_PSW              0x0009
#define PT_EVENT_ULOCK_CARD             0x000A
#define PT_EVENT_ULOCK_FACE             0x000B
#define PT_EVENT_ULOCK_HVEIN            0x000C
#define PT_EVENT_ULOCK_VEIN             0x000D
#define PT_EVENT_ULOCK_PWS_TMP          0x000E
#define PT_EVENT_ULOCK_PWS_DYN          0x000F
#define PT_EVENT_ULOCK_REMOTE           0x0010
#define PT_EVENT_ULOCK_PWS_OFFLINE      0x0011
#define PT_EVENT_DOORBELL_REQUEST       0x0012
#define PT_EVENT_ALARM_HIJACK           0x0013
#define PT_EVENT_ALARM_LOWPOWER         0x0014
#define PT_EVENT_ALARM_KEY_IN           0x0015
#define PT_EVENT_ALARM_HIGH_TEMP        0x0016
#define PT_EVENT_DOORBELL_AND_REMOTE    0x0017
#define PT_EVENT_ALARM_STAY             0x0018
#define PT_EVENT_ALARM_DESTROYED        0x0019
#define PT_EVENT_ULOCK_SPECIAL_FINGER   0x001A

typedef enum {
    STREAM_SEND_TYPE_DIRECT = 0,          /*send frame data directly*/
} TY_STREAM_SEND_TYPE_E;

typedef struct {
    TY_STREAM_SEND_TYPE_E          type;           /*tuya send  data type*/
    UCHAR_T                     cmd;           /*tuya send  cmd*/
    UINT_T 		            data_len;		/*tuya send data len*/
    CHAR_T 		            *data;	        /*tuya send  data content*/
} TY_STREAM_SEND_FRAME_S;


typedef OPERATE_RET(*TY_STREAM_SEND_FRAME_HANDLE_CB)(IN TY_STREAM_SEND_FRAME_S *p_send_frame);


OPERATE_RET ty_photo_proc_init(TY_STREAM_SEND_FRAME_HANDLE_CB cb);


OPERATE_RET ty_photo_cloudp2p_iot_init(VOID);


OPERATE_RET ty_photo_kiwi_trigger_proc(UCHAR_T trigger_type, USHORT_T event_type, BOOL_T is_snap_flag, TIME_T *time);

OPERATE_RET ty_photo_kiwi_trigger_proc_indoor(UCHAR_T trigger_type, USHORT_T event_type, BOOL_T is_snap_flag, TIME_T *time);


VOID ty_stream_actice_force_uplord(VOID);

VOID ty_stream_init(VOID);


VOID ty_stream_deinit_resoure_cb(VOID);


OPERATE_RET ty_spk_in_queue(UCHAR_T *p_data, UINT_T len, UCHAR_T type);

#ifdef __cplusplus
}
#endif

#endif

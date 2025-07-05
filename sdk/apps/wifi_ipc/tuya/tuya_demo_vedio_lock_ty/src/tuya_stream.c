/**
 * @file    tuya_photo_and_stream.c
 * @author  mjl@tuya.com
 * @version 1.0
 * @date    2021-07-27
 * @copyright Copyright (c) tuya.inc 2020
 */
#define __TY_PHOTO_AND_STREAM_GLOBALS

#include "app_config.h"
#include "asm/jpeg_codec.h"
#include "asm/aes_hw.h"
#include "string.h"

#include "tuya_stream.h"
#include "gw_intf.h"
#include "uni_log.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "ty_cJSON.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_uart_legacy.h"
#include "tdl_data_send_recv_init.h"
#include "tfm_data_frame_recv.h"
#include "tfm_cmd_list.h"
#include "tal_queue.h"
#include "uni_msg_queue.h"
#include "tuya_ipc_streamer.h"
#include "tbl_common_basic_service.h"
#include "tuya_device.h"
#include "uni_time.h"
#include "tuya_ws_db.h"
#include "tal_time_service.h"
#include "sys_timer.h"
#include "tkl_queue.h"
#include "mqc_app.h"
#include "tbl_kiwi_cmd_def.h"
#include "tuya_video.h"


#define AUDIO_CHANNEL_DEFAULT   1
#define AUDIO_BIT_DEFAULT       16
#define AUDIO_RATE_DEFAULT      8000

#define VEDIO_W_DEFAULT         CONFIG_VIDEO_IMAGE_W
#define VEDIO_H_DEFAULT         CONFIG_VIDEO_IMAGE_H
#define VEDIO_ROTE_DEFAULT      0  //CONFIG_VIDEO_IMAGE_ROTE
#define VEDIO_FPS_DEFAULT       10 //CONFIG_VIDEO_IMAGE_FPS



#define PT_TRIGGER_RET_SUCCESS          0x00
#define PT_TRIGGER_RET_FIALED           0x01

#define TRIGGER_TYPE_INIT           0x00
#define TRIGGER_TYPE_PHOTO          0x01
#define TRIGGER_TYPE_STREAM         0x02

typedef UCHAR_T TRANS_STATE_E;
#define PT_PROC_NULL                    0x00
#define PT_PROC_START                   0x01
#define PT_PROC_READY                   0x02
#define PT_PROC_UPLOAD                  0x03
#define PT_PROC_FAILED                  0x04


#define PT_DATA_INIT                     0
#define PT_STREAM_START                  1
#define PT_DATA_END                      2
#define PT_UP_SKILL                      3

#define PT_STREAM_DATA_START             7

#define PT_RET_SUCC                     0x00
#define PT_RET_NET_FAILED               0x01
#define PT_RET_SIZE_OUT                 0x02
#define PT_RET_TIME_OUT                 0x03
#define PT_RET_OTHER_FAILED             0x04
#define PT_RET_STREAM_STOP              0x05

#define PHOTO_NAME_SIZE         15
#define MEDIA_NAME_SIZE         17
#define UPLOAD_TIMEBUFF_SIZE    6
#define FORCE_PUSH_STREAM_OFF_TIMEOUT     (4*60*1000)
#define TRIGGER_TIMEOUT                   30*1000
#define DATA_TIMEOUT                   10*1000
#define USB_IN_TIMEOUT                 10*1000
#define PT_SYS_DP                            212
#define TY_URL_BIZTYPE_IMAGE    "lock_snapshot_image"
#define TY_URL_CONTENTYPE_IMAGE "image/jpg"
#define TY_DP212_VER_50         "5.0"
#define TY_DP212_TYPE_IMAGE     "image"
#define TY_DP212_TYPE_MEDIA     "media"
#define TY_DP212_CMD_COVER      "door_lock_video_cover"
#define TY_DP212_CMD_VIDEO      "door_lock_video"
#define TY_DP212_WITH_RESORCES  "resources"
#define TY_SVC_STREAM_GET_ATOP  "tuya.device.rtc.stream.push.start"
#define TY_SVC_STREAM_GET_VER   "1.0"
#define TY_SVC_PHOTO_GET_ATOP  "tuya.device.rtc.image.push"
#define TY_SVC_PHOTO_GET_VER   "1.0"
#define TY_SVC_DEV_SKILL_UPDATE "tuya.device.skill.update"
#define TY_SVC_SKILL_UPDATE_VER   "1.0"
#define TY_SVC_CAMER_INFO       "camer_info"
#define TY_SVC_STREAM_NEW_GET_ATOP  "thing.lock.rtc.stream.push.start"
#define TY_SVC_STREAM_NEW_GET_VER   "1.0"

#define  IPC_SKILLS_BUF_LEN  128u
#define TUYA_P2P_TYPE           4

//#define TY_STREAM_VIDEO_FPS     25
#define TY_STREAM_AUDIO_FPS     25

#define STREAM_BUFFER_MAX_NUM  35
#define AUDIO_BUFFER_LEN      (1280 * 2)
#define IPC_ENCRYPTION_SPACE_HEAD 128

#define TUYA_H264_SELF_DEFINE_SEI_SIZE (96)

#define SEI_UUID_SIZE (16)

#define AUDIO_FRAM_LEN        (320)

#define  TUYA_SPC_MALLOC Malloc
#define  TUYA_SPC_FREE Free
//nal类型
enum nal_unit_type_e {
    NAL_UNKNOWN     = 0,
    NAL_SLICE       = 1,
    NAL_SLICE_DPA   = 2,
    NAL_SLICE_DPB   = 3,
    NAL_SLICE_DPC   = 4,
    NAL_SLICE_IDR   = 5,    /* ref_idc != 0 */
    NAL_SEI         = 6,    /* ref_idc == 0 */
    NAL_SPS         = 7,
    NAL_PPS         = 8
                      /* ref_idc == 0 for 6,9,10,11,12 */
};

typedef enum {
    VIDEO_TRIGGER_APP,
    VIDEO_TRIGGER_MCU,
    VIDEO_TRIGGER_INDOOR,
} VIDEO_TRIGGER_SOURCE;


typedef struct {
    UINT_T              cmd;
    UCHAR_T             *data;
    UINT_T              data_len;
} PHOTO_CTRL_MSG;

typedef struct {
    BOOL_T          photo_init;
    UCHAR_T         trigger_type;
    UINT_T          audio_seq;
    UINT_T          photo_id;
    UINT_T          seq_id;
    THRD_HANDLE     handle;
    OS_QUEUE        msg_que;
    TIMER_ID        timer;
    TRANS_STATE_E   proc_state;
    BOOL_T          is_busy;
    BOOL_T          stream_is_busy;
    BOOL_T          is_support_audio;
    TY_STREAM_SEND_FRAME_HANDLE_CB cb;
    BOOL_T          stream_is_over_time;
    UCHAR_T         tm[UPLOAD_TIMEBUFF_SIZE];
} PHOTO_CRTL;


typedef struct {
    BOOL_T          stream_que_init;
    OS_QUEUE        stream_queue;
    UINT_T          queue_cnt;
    MUTEX_HANDLE    queue_mutex;
    BOOL_T          need_i_frame;
    CHAR_T         *audio_buffer;  //用于临时缓存音频数据
    UINT_T          audio_put_len; //用于记录缓存中放入的音频帧长度
} STREAM_CRTL;


typedef struct {
    UCHAR_T         time_flag;
    UCHAR_T         tm[UPLOAD_TIMEBUFF_SIZE];
    USHORT_T        id;
    USHORT_T        event_type;
    CHAR_T         name[MEDIA_NAME_SIZE];
    UINT_T          expire;
    BYTE_T         *url;
    CHAR_T        *key;
    CHAR_T        *ckey;
    CHAR_T        *auth;
    CHAR_T        *date;
    CHAR_T        *cont;
    CHAR_T        *url_id;
    CHAR_T        *bucket;
} UPLOAD_INFO;

#pragma pack(1)
typedef struct {
    UCHAR_T     sub_cmd;
    USHORT_T    event_type;
    UCHAR_T     trigger_type;
    UCHAR_T     ph_reserve1;
    UCHAR_T     ph_reserve2;
    UCHAR_T     time_flag;
    UCHAR_T     time[6];
} PT_TRIGGER_PROT;


typedef struct {
    UCHAR_T     type; //0:手机下发 1:设备文件读取
    UINT_T      len;
    UCHAR_T     *data;
} SVC_SPKER_INFO;



#pragma pack()


STATIC PHOTO_CRTL g_pt_ctrl;
STATIC UPLOAD_INFO *g_photo_info = NULL;
STATIC UPLOAD_INFO *g_stream_info = NULL;
STATIC CHAR_T ipc_skills[IPC_SKILLS_BUF_LEN];
STATIC BOOL_T send_frame_type = FALSE;

STATIC STREAM_CRTL g_stream_ctrl = {0};

STATIC TIMER_ID print_net_rate_timer = 0;


//STATIC UINT_T real_size = 0;
//STATIC INT_T jpeg_count = 0;
//STATIC UINT_T tatal_size = 0;
//STATIC INT_T voice_count = 0;

UINT_T real_size = 0;
INT_T jpeg_count = 0;
UINT_T tatal_size = 0;
INT_T voice_count = 0;

STATIC VOID print_net_timer_cb(TIMER_ID timerID, PVOID_T pTimerArg);
STATIC VOID ty_data_info_clean(UPLOAD_INFO **info);
STATIC VOID tuya_doorbell_upload(UPLOAD_INFO *upload_info);
STATIC OPERATE_RET tuya_rotating_upload(UINT_T rotation_angle);
STATIC OPERATE_RET ty_sys_dp_upload_media(UPLOAD_INFO *upload_info);
STATIC OPERATE_RET ty_sys_dp_upload_photo(UPLOAD_INFO *upload_info);


typedef unsigned short WORD;
/****************未定义*******************/

//BOOL_T tuya_push_stream_status_get(VOID)
//{
//    PR_DEBUG("tuya_push_stream_status_get");
//    return FALSE;
////    return ipc_push_stream_start;
//}
//
//STATIC VOID tuya_push_stream_start(VOID)
//{
//    PR_DEBUG("tuya_push_stream_status_get");
////    ipc_push_stream_start = TRUE;
////    g_pt_ctrl.audio_seq = 0;
////    sys_start_timer(print_net_rate_timer, 1000, TIMER_ONCE);
//}
//
//STATIC VOID tuya_clear_stream_que(VOID)
//{
//    PR_DEBUG("tuya_clear_stream_que");
////    UINT_T i = 0, queue_cnt = 0;
////    SVC_STREAM_INFO *stream_info = NULL;
////    queue_cnt = g_stream_ctrl.queue_cnt;
////    for (i = 0; i < queue_cnt; i++) {
////        stream_info = ipc_stream_out_queue();
////        if (stream_info) {
////            /* putchar('c'); */
////            Free(stream_info);
////            stream_info = NULL;
////        }
////    }
//    return ;
//}
//
//STATIC VOID tuya_push_stream_stop(VOID)
//{
//    PR_DEBUG("tuya_push_stream_stop");
////    ipc_push_stream_start = FALSE;
////    sys_stop_timer(print_net_rate_timer);
//}

/***********************************/

STATIC VOID print_net_timer_cb(TIMER_ID timerID, PVOID_T pTimerArg)
{
    if (tuya_push_stream_status_get()) {
        sys_start_timer(print_net_rate_timer, 1000, TIMER_ONCE);
        PR_NOTICE("stream video fps %d audio fps %d que num %d net %d KB, real_size %d KB/s",  \
                  jpeg_count, voice_count, g_stream_ctrl.queue_cnt, (tatal_size / 1024), (real_size / 1024));
        jpeg_count = 0;
        tatal_size = 0;
        voice_count = 0;
        real_size = 0;
    }
}


OPERATE_RET ty_param_load(CHAR_T *type, UCHAR_T *input_param, UINT_T input_len, UINT_T *out_read_len)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T *load_param = NULL;
    UINT_T param_len;

    if (NULL == input_param || input_len == 0) {
        PR_ERR("ty_param_load input_param err!");
        return OPRT_INVALID_PARM;
    }

    op_ret = wd_common_read(type, &load_param, &param_len);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_param_load  err:%0d", op_ret);
        return op_ret;
    } else {
        if (input_len < param_len) {
            PR_ERR("ty_param_load input_len < param_len");
            Free(load_param);
            return OPRT_COM_ERROR;
        }
        memcpy(input_param, load_param, param_len);
        *out_read_len = param_len;
        PR_NOTICE("ty_param_load success!");
        Free(load_param);
    }
    return op_ret;
}

OPERATE_RET ty_param_save(CHAR_T *type, UCHAR_T *input_param, UINT_T inlen)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (NULL == input_param || inlen == 0) {
        PR_ERR("ty_sn_save input_param err!");
        return OPRT_INVALID_PARM;
    }

    op_ret = wd_common_write(type, input_param, inlen);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_common_write camera_param err:%d", op_ret);
    } else {
        PR_NOTICE("save  success");
    }
    return op_ret;
}

STATIC OPERATE_RET ty_photo_send_msg(IN CONST UINT_T msgid, IN CONST VOID *data, IN CONST UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    PHOTO_CTRL_MSG *msg_data;
    msg_data = Malloc(SIZEOF(PHOTO_CTRL_MSG) + 1);
    if (!msg_data) {
        return OPRT_MALLOC_FAILED;
    }
    memset(msg_data, 0, SIZEOF(PHOTO_CTRL_MSG) + 1);
    msg_data->cmd = msgid;
    if (data && len) {
        msg_data->data = Malloc(len + 1);
        if (!(msg_data->data)) {
            if (msg_data) {
                Free(msg_data);
            }
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data->data, 0, len + 1);
        memcpy(msg_data->data, data, len);
        msg_data->data_len = len;
    }

    op_ret = os_q_post(&g_pt_ctrl.msg_que, msg_data);
//    op_ret = tal_queue_post(g_pt_ctrl.msg_que,&msg_data,500);
    if (OPRT_OK != op_ret) {
        if (msg_data->data) {
            Free(msg_data->data);
        }
        if (msg_data) {
            Free(msg_data);
        }
        return op_ret;
    }
    return OPRT_OK;
}

////////////////////////////////////////////
#define IPC_STREAM_MAX_NUM      10
#if (__SDRAM_SIZE__ == (8 * 1024 * 1024))
#define MAX_FRGE_SIZE           (1024*100) //(1024*40)
#else if (__SDRAM_SIZE__ == (16 * 1024 * 1024))
#define MAX_FRGE_SIZE           (1024*200)
#endif

#pragma pack(1)
typedef struct {
    UINT_T      seqNo;
    UCHAR_T     fragStatus;
    UCHAR_T     fragNo;
    USHORT_T    frameType;
    UINT64_T    timestamp_ms;
    UINT_T      len;
    UCHAR_T     data[0];
} SVC_STREAM_INFO;
#pragma pack()




//STATIC P_QUEUE_CLASS stream_queue;
STATIC BOOL_T ipc_push_stream_start = FALSE;//FALSE;//FALSE;
STATIC BOOL_T is_ipc_stream_que_init = FALSE;
STATIC SVC_STREAM_INFO *last_stream_info = NULL;
//STATIC P_QUEUE_CLASS audio_stream_queue;


STATIC TY_CAMERA_PARAM camera_param = {
    .video_width = VEDIO_W_DEFAULT,
    .video_height = VEDIO_H_DEFAULT,
    .video_rotat_angle = VEDIO_ROTE_DEFAULT,
    .video_fps = VEDIO_FPS_DEFAULT,
};

STATIC TY_AUDIO_PARAM audio_param = {
    .channel_num = AUDIO_CHANNEL_DEFAULT,
    .bit_dept = AUDIO_BIT_DEFAULT,
    .sample_rate = AUDIO_RATE_DEFAULT,
};

/////////////////////////////////////
BOOL_T tuya_push_stream_status_get(VOID)
{
    return ipc_push_stream_start;
}
STATIC VOID tuya_push_stream_start(VOID)
{
    ipc_push_stream_start = TRUE;
    g_pt_ctrl.audio_seq = 0;
    sys_start_timer(print_net_rate_timer, 1000, TIMER_ONCE);
}

STATIC VOID tuya_push_stream_stop(VOID)
{
    ipc_push_stream_start = FALSE;
    sys_stop_timer(print_net_rate_timer);
}


STATIC SVC_STREAM_INFO *ipc_stream_out_queue(VOID)
{
//    PR_DEBUG("into ipc stream out queue!");
    SVC_STREAM_INFO *info = NULL;
    OPERATE_RET op_ret = OPRT_OK;

    tuya_hal_mutex_lock(g_stream_ctrl.queue_mutex);
//    PR_DEBUG("ipc_stream_out_queue os_q_pend");

    int msg[16] = {0,};
    op_ret = os_q_recv(&g_stream_ctrl.stream_queue, msg, 1);
    if (op_ret) {
        tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
        return NULL;
    } else {
        g_stream_ctrl.queue_cnt--;
    }
    info = (SVC_STREAM_INFO *)msg[0];
    tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);

    return info;
}

STATIC VOID tuya_clear_stream_que(VOID)
{
    PR_DEBUG("clear stream que");
    UINT_T i = 0, queue_cnt = 0;
    SVC_STREAM_INFO *stream_info = NULL;
    queue_cnt = g_stream_ctrl.queue_cnt;
    for (i = 0; i < queue_cnt; i++) {
        stream_info = ipc_stream_out_queue();
        if (stream_info) {
            /* putchar('c'); */
            Free(stream_info);
            stream_info = NULL;
        }
    }
    return ;
}


STATIC OPERATE_RET ipc_stream_in_queue(CHAR_T *p_image_data, UINT_T image_len, USHORT_T type)
{
    /* TAL_PR_DEBUG("ipc_stream_in_queue!"); */
    SVC_STREAM_INFO *pstream_info = NULL;
    UCHAR_T image_max_frage = 0;
    UCHAR_T i = 0;
    UINT_T malloc_len = 0;
    UINT64_T    cur_timestamp_ms;
    OPERATE_RET ret = OPRT_OK;
    STATIC UCHAR_T frage = 0;
    UINT_T timeout = 0;

    if (!ipc_push_stream_start) {
        /* TAL_PR_DEBUG("ipc push stream not start"); */
        return OPRT_COM_ERROR;
    }

    if (g_stream_ctrl.queue_cnt > STREAM_BUFFER_MAX_NUM - 5) {
//        PR_WARN("need get i frame, heap=%d\n",tuya_hal_system_getheapsize());
//        PR_WARN("g_stream_ctrl :%d", g_stream_ctrl.queue_cnt);
        tuya_clear_stream_que();
        return OPRT_OK;
    }

    image_max_frage = (image_len + (MAX_FRGE_SIZE - 1)) / MAX_FRGE_SIZE;


    tuya_hal_mutex_lock(g_stream_ctrl.queue_mutex);

#if 1

    cur_timestamp_ms = tal_time_get_posix_ms();
    for (i = 0; i < image_max_frage; i++) {
        if (i == image_max_frage - 1) {
            malloc_len = sizeof(SVC_STREAM_INFO) + image_len % MAX_FRGE_SIZE;
        } else {
            malloc_len = sizeof(SVC_STREAM_INFO) + MAX_FRGE_SIZE;
        }
//        PR_DEBUG("malloc data");
        pstream_info = Malloc(malloc_len);
        if (NULL == pstream_info) {
            PR_ERR("malloc failed");
            tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
            return OPRT_MALLOC_FAILED;
        }
        pstream_info->frameType = type;
        pstream_info->timestamp_ms = cur_timestamp_ms;
        if (E_AUDIO_FRAME == type) {
            pstream_info->seqNo = g_pt_ctrl.audio_seq++;
        } else {
            pstream_info->seqNo = g_pt_ctrl.seq_id;
        }
        // pstream_info->seqNo = g_pt_ctrl.seq_id;
        pstream_info->len = malloc_len - sizeof(SVC_STREAM_INFO);
        memcpy(pstream_info->data, p_image_data + i * MAX_FRGE_SIZE, pstream_info->len);
        if (1 == image_max_frage) {
            pstream_info->fragStatus = STREAMING_FRAG_DISABLE;
            pstream_info->fragNo = 0;
            g_pt_ctrl.seq_id++;
        } else if (2 == image_max_frage) {
            if (i == 0) {
                pstream_info->fragStatus = STREAMING_FRAG_START;
                pstream_info->fragNo = 0;
            } else {
                pstream_info->fragStatus = STREAMING_FRAG_END;
                pstream_info->fragNo = 1;
                g_pt_ctrl.seq_id++;
            }
        } else {
            if (i == 0) {
                pstream_info->fragStatus = STREAMING_FRAG_START;
                frage = 0;
                pstream_info->fragNo = 0;
            } else if (i == image_max_frage - 1) {
                pstream_info->fragStatus = STREAMING_FRAG_END;
                frage++;
                pstream_info->fragNo = frage;
                g_pt_ctrl.seq_id++;
            } else {
                pstream_info->fragStatus = STREAMING_FRAG_INSIDE;
                frage++;
                pstream_info->fragNo = frage;
            }

        }

        ret = os_q_post(&g_stream_ctrl.stream_queue, pstream_info);
        if (ret) {
            PR_DEBUG("post work_mode_queue failed, ret(%d)\n", ret);
            Free(pstream_info);
            ret = OPRT_COM_ERROR;
        } else {
            g_stream_ctrl.queue_cnt++;
        }
//        PR_DEBUG("frameType %d inque 0x%x t %lld seqNo %d len %d frag %d %d\r\n",pstream_info->frameType, pstream_info,pstream_info->timestamp_ms,pstream_info->seqNo,pstream_info->len,pstream_info->fragStatus,pstream_info->fragNo);
    }
    tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
#endif
    return ret;
}



OPERATE_RET ty_stream_in_queue(CHAR_T *p_image_data, UINT_T image_len, UINT_T frame_type)
{
//    PR_DEBUG("ty_stream_in_queue");
    if (!ipc_push_stream_start) {
        return OPRT_NOT_SUPPORTED;
    }
    if (!image_len) {
        return OPRT_INVALID_PARM;
    }
//    PR_NOTICE("put data to stream queue");
    /* PR_NOTICE("put %d to stream queue", image_len); */
    return ipc_stream_in_queue(p_image_data, image_len, frame_type);
}


STATIC OPERATE_RET ty_stream_clear_and_in_queue(CHAR_T *p_image_data, UINT_T image_len)
{
    tuya_clear_stream_que();
    return ipc_stream_in_queue(p_image_data, image_len, E_VIDEO_I_FRAME);
}


VOID ty_audio_stream_in_queue(CHAR_T *p_audio_data, UINT_T audio_len)
{
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        return ;
    }
    if (!ipc_push_stream_start) {
        return ;
    }
    if (!audio_len) {
        return;
    }
    // PR_DEBUG("put audio data len:%d", audio_len);
    // put_buf(p_audio_data, 32);

    ipc_stream_in_queue(p_audio_data, audio_len, E_AUDIO_FRAME);
    return ;
}

STATIC OPERATE_RET ty_stream_queue_init(VOID)
{
    PR_DEBUG("into ty_stream_queue_init");
    OPERATE_RET op_ret = OPRT_OK;
    if (g_stream_ctrl.stream_que_init) {
        return op_ret;
    }

    QS queue_size = (SIZEOF(SVC_STREAM_INFO *) * STREAM_BUFFER_MAX_NUM + sizeof(WORD) - 1) / sizeof(WORD);

    op_ret = os_q_create(&g_stream_ctrl.stream_queue, queue_size);
    if (NULL == &g_stream_ctrl.stream_queue) {
        return OPRT_COM_ERROR;
    }
    op_ret = tuya_hal_mutex_create_init(&g_stream_ctrl.queue_mutex);
    if (OPRT_OK != op_ret) {
        return op_ret;
    }
    sys_add_timer(print_net_timer_cb, NULL, &print_net_rate_timer);
    g_stream_ctrl.stream_que_init = TRUE;
    return op_ret;
}

BOOL_T ty_stream_is_support(VOID)
{
    BOOL_T op_ret = FALSE;
    op_ret = TRUE;
    return op_ret;
}


//////////////////////////////////////////

STATIC VOID photo_ack_time_Proc(VOID)
{
    OPERATE_RET  op_ret = OPRT_OK;
    POSIX_TM_S   tm;

    op_ret = tal_time_get_local_time_custom(0, &tm);
    if (OPRT_OK != op_ret) {
        PR_ERR("uni_local_time_get failed! op_ret:%d", op_ret);
        return ;
    }

    /*convert*/
    g_photo_info->tm[0] = tm.tm_year - 100;
    g_photo_info->tm[1] = tm.tm_mon + 1;
    g_photo_info->tm[2] = tm.tm_mday;
    g_photo_info->tm[3] = tm.tm_hour;
    g_photo_info->tm[4] = tm.tm_min;
    g_photo_info->tm[5] = tm.tm_sec;

    return ;
}
STATIC TIME_T ty_trigger_time_proc(BOOL_T time_flag, UCHAR_T *time)
{
    TIME_T time_t = 0;
    INT_T zone_num = 0;

    if (time_flag > 0) {

        POSIX_TM_S  stu_timer;
        stu_timer.tm_year = (time[0] + 100); //(2000-1900)
        stu_timer.tm_mon  = (time[1] - 1);
        stu_timer.tm_mday = time[2];
        stu_timer.tm_hour = time[3];
        stu_timer.tm_min  = time[4];
        stu_timer.tm_sec  = time[5];
        time_t = uni_mktime(&stu_timer);

        if (0x01 == time_flag) {
            if (uni_get_time_zone_seconds(&zone_num) != OPRT_OK) {
                PR_ERR("tuya_get_time_zone err ");
            }

            PR_DEBUG("zone_num %d", zone_num);
            time_t -= zone_num;

            if (TRUE == uni_is_in_sum_zone(time_t)) {
                PR_DEBUG("sumer timer");
                time_t -= 3600;
            }
        }
    } else {
        time_t = uni_time_get_posix();
        photo_ack_time_Proc();

    }
    PR_DEBUG("time:%d,time flag:%d", time_t, time_flag);
    return time_t;
}

STATIC OPERATE_RET ty_data_init_photo(PVOID_T msgdata)
{

    if (NULL == g_photo_info) {
        g_photo_info = (UPLOAD_INFO *)Malloc(SIZEOF(UPLOAD_INFO));
        if (NULL == g_photo_info) {
            PR_ERR("g_photo_info malloc error");
            return OPRT_MALLOC_FAILED;
        }
    }

    memset(g_photo_info, 0, SIZEOF(UPLOAD_INFO));
    PT_TRIGGER_PROT *pdata = (PT_TRIGGER_PROT *)msgdata;
    g_photo_info->event_type = WORD_SWAP(pdata->event_type);
    g_photo_info->id = 0;
    g_photo_info->time_flag = pdata->time_flag;
    memcpy(g_photo_info->tm, pdata->time, UPLOAD_TIMEBUFF_SIZE);

    PR_DEBUG("ty_data_init_photo success! heapsize:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC OPERATE_RET ty_data_init_stream(PVOID_T msgdata)
{
    if (NULL == g_stream_info) {
        g_stream_info = (UPLOAD_INFO *)Malloc(SIZEOF(UPLOAD_INFO));
        if (NULL == g_stream_info) {
            PR_ERR("g_stream_info malloc error");
            return OPRT_MALLOC_FAILED;
        }
    }
    memset(g_stream_info, 0, SIZEOF(UPLOAD_INFO));

    //get photo_ctrl infomation
    PT_TRIGGER_PROT *pdata = (PT_TRIGGER_PROT *)msgdata;
    g_stream_info->event_type = WORD_SWAP(pdata->event_type);
    g_stream_info->id = 0;
    g_stream_info->time_flag = pdata->time_flag;
    memcpy(g_stream_info->tm, pdata->time, UPLOAD_TIMEBUFF_SIZE);

    PR_DEBUG("ty_data_init_stream success! heapsize:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC OPERATE_RET ty_photo_data_init_proc(PVOID_T msgdata)
{
    OPERATE_RET op_ret = OPRT_OK;

    g_pt_ctrl.is_busy = TRUE;
    g_pt_ctrl.stream_is_over_time = FALSE;
    g_pt_ctrl.proc_state = PT_PROC_NULL;
    send_frame_type = FALSE;

    sys_stop_timer(g_pt_ctrl.timer);
    memset(g_pt_ctrl.tm, 0, UPLOAD_TIMEBUFF_SIZE);
    op_ret = ty_data_init_photo(msgdata);
    if (op_ret != OPRT_OK) {
        return op_ret;
    }
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
        op_ret = ty_data_init_stream(msgdata);
        if (op_ret != OPRT_OK) {
            return op_ret;
        }
    }

    return op_ret;
}



STATIC INT_T __event_cb(IN CONST TRANSFER_EVENT_E event)
{
    PR_NOTICE("*************************");
    PR_NOTICE("svc_stream state is %d", event);
    PR_NOTICE("*************************");
    UCHAR_T ret;


    if ((event == TRANS_STREAMING_VIDEO_START) && (!g_pt_ctrl.stream_is_busy)) {
        g_pt_ctrl.stream_is_busy = TRUE;
        g_pt_ctrl.stream_is_over_time = FALSE;
        g_pt_ctrl.proc_state = PT_PROC_READY;

        ret = PT_RET_SUCC;
        tuya_push_stream_start();
        ty_photo_send_msg(PT_STREAM_DATA_START, &ret, 1);

    }

    if ((event == TRANS_STREAMING_VIDEO_STOP) && g_pt_ctrl.stream_is_busy) {
        tuya_push_stream_stop();
        if (FALSE == g_pt_ctrl.stream_is_over_time) {
            if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
                ret = PT_RET_SUCC;
                /* 传图之后要更改到传流的类型，防止app直接拉流拉不到 */
                g_pt_ctrl.trigger_type = TRIGGER_TYPE_STREAM;
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
                return 0;  // 图片直接返回
            } else if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
                ret = PT_RET_STREAM_STOP;
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
            } else {
                ret = PT_RET_STREAM_STOP;
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
            }
        } else {
            g_pt_ctrl.stream_is_over_time = FALSE;
        }
        g_pt_ctrl.stream_is_busy = FALSE;

    }

    return 0;
}


INT_T __get_frame_cb(IN INT_T get_latest_frame, IN STREAM_TYPE_E stream_type, IN INT_T retry, OUT FRAME_INFO_S *frame_info)
{
    sys_start_timer(g_pt_ctrl.timer, USB_IN_TIMEOUT, TIMER_ONCE);
    //todo  获取数据
    TIME_S time_s = 0;
    TIME_S time_ms = 0;
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T send_len = 0;
    INT_T time1 = 0;
    INT_T time2 = 0;

    if (NULL != last_stream_info) {
        Free(last_stream_info);
        last_stream_info = NULL;
    }
    SVC_STREAM_INFO *stream_info = NULL;
    PR_DEBUG("out stream data");
    stream_info = ipc_stream_out_queue();
    /* PR_DEBUG("out stream data"); */
    /* malloc_stats(); 	 */
    if (stream_info) {
        frame_info->type = stream_info->frameType;
        frame_info->timestamp = stream_info->timestamp_ms;
        frame_info->pts = frame_info->timestamp * 1000;
        frame_info->data = stream_info->data;
        frame_info->size = stream_info->len;
        frame_info->seqNo = stream_info->seqNo;
        frame_info->fragStatus = stream_info->fragStatus;    //音频数据无需分包
        frame_info->fragNo = stream_info->fragNo;
        last_stream_info = stream_info;
    } else {
        PR_DEBUG("wait");
        return OPRT_COM_ERROR;
    }
    tatal_size += frame_info->size;
    PR_DEBUG("out stream data, type:%d", stream_info->frameType);
    return OPRT_OK;
}

VOID __recv_audio_cb(IN CONST TRANSFER_AUDIO_FRAME_S *p_audio_frame)
{
    /* PR_NOTICE("__recv_audio_cb recv len %d audio_codec %d audio_databits %d audio_sample %d", p_audio_frame->buf_len, p_audio_frame->audio_codec, p_audio_frame->audio_databits, p_audio_frame->audio_sample); */
    //todo 发送音频数据
    ty_device_write_net_voice_data(p_audio_frame->p_audio_buf, p_audio_frame->buf_len);
    return ;
}



STATIC OPERATE_RET ty_update_skill_and_rotate(INT_T rotate)
{
    OPERATE_RET op_ret = OPRT_OK;
    CHAR_T *skill_info = Malloc(512);
    if (NULL == skill_info) {
        return OPRT_COM_ERROR;
    }
    memset(skill_info, 0, 512);
    TSTREAMER_S *pstreamer = GetTStreamerInstance();
    if (pstreamer) {
        pstreamer->SupportAudio(g_pt_ctrl.is_support_audio);
        pstreamer->FillSkills(skill_info, 512);
    }

    GW_CNTL_S *gw_cntl = get_gw_cntl();
    op_ret = http_device_update_skill(gw_cntl->gw_if.id, skill_info);
    if (op_ret != OPRT_OK) {
        PR_ERR("http_device_update_skill failed!!");
    } else {
        PR_NOTICE("svc_stream_start done!! g_pt_ctrl.is_support_audio =%d rotate=%d", g_pt_ctrl.is_support_audio, rotate);
        if (rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270) {
            op_ret = tuya_rotating_upload(rotate);
        }

    }
    Free(skill_info);
    return op_ret;
}


STATIC OPERATE_RET httpc_proc_url_state(ty_cJSON *result, UPLOAD_INFO *upload_info)
{
    ty_cJSON *item = NULL, *key = NULL, *ckey = NULL;

    PR_DEBUG("httpc_proc_url_state:%d", tuya_hal_system_getheapsize());
    item = ty_cJSON_GetObjectItem(result, "url");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem url err");
        return OPRT_CJSON_GET_ERR;
    }

    upload_info->url = (BYTE_T *)Malloc(strlen(item->valuestring) + 1);
    if (NULL == upload_info->url) {
        PR_ERR("httpc_proc_url_state url malloc error");
        return OPRT_MALLOC_FAILED;
    }

    memset(upload_info->url, 0, strlen(item->valuestring) + 1);
    memcpy(upload_info->url, item->valuestring, strlen(item->valuestring));

    PR_DEBUG("recv url:%s, url:%s,len:%d", item->valuestring, upload_info->url, strlen(item->valuestring));

    item = ty_cJSON_GetObjectItem(result, "allocateId");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem allocateId err");
        return OPRT_CJSON_GET_ERR;
    }

    PR_DEBUG("url_id len = %d", strlen(item->valuestring) + 1);
    upload_info->url_id = (BYTE_T *)Malloc(strlen(item->valuestring) + 1);
    if (NULL == upload_info->url_id) {
        PR_ERR("httpc_proc_url_state url_id malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->url_id, 0, strlen(item->valuestring) + 1);
    memcpy(upload_info->url_id, item->valuestring, strlen(item->valuestring));

    item = ty_cJSON_GetObjectItem(result, "bucket");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem bucket err");
        return OPRT_CJSON_GET_ERR;
    }

    upload_info->bucket = (BYTE_T *)Malloc(strlen(item->valuestring) + 1);
    if (NULL == upload_info->bucket) {
        PR_ERR("httpc_proc_url_state bucket malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->bucket, 0, strlen(item->valuestring) + 1);
    memcpy(upload_info->bucket, item->valuestring, strlen(item->valuestring));

    item = ty_cJSON_GetObjectItem(result, "expire");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem expire err");
    } else {
        upload_info->expire = item->valueint;
        PR_DEBUG("recv expire:%d", upload_info->expire);
    }
    key = ty_cJSON_GetObjectItem(result, "localKey");
    if (NULL == key) {
        PR_ERR("cJSON_Parse:%s failed", result->valuestring);
        return OPRT_CJSON_PARSE_ERR;
    }
    upload_info->key = (UCHAR_T *)Malloc((strlen(key->valuestring) + 1) * SIZEOF(UCHAR_T));
    if (NULL == upload_info->key) {
        PR_ERR("httpc_proc_url_state photo_key malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->key, 0, (strlen(key->valuestring) + 1)*SIZEOF(UCHAR_T));
    memcpy(upload_info->key, key->valuestring, strlen(key->valuestring));
    PR_DEBUG("recv key:%s,photo_key:%s,len:%d",  key->valuestring, upload_info->key, strlen(key->valuestring));

    ckey = ty_cJSON_GetObjectItem(result, "cloudKey");
    if (NULL == ckey) {
        PR_ERR("cJSON_Parse:%s failed", result->valuestring);
        return OPRT_CJSON_PARSE_ERR;
    }
    upload_info->ckey = (UCHAR_T *)Malloc((strlen(ckey->valuestring) + 1) * SIZEOF(UCHAR_T));
    if (NULL == upload_info->ckey) {
        PR_ERR("httpc_proc_url_state photo_url malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->ckey, 0, (strlen(ckey->valuestring) + 1)*SIZEOF(UCHAR_T));
    memcpy(upload_info->ckey, ckey->valuestring, strlen(ckey->valuestring));
    PR_DEBUG("recv ckey:%s,photo_ckey:%s,len:%d",  ckey->valuestring, upload_info->ckey, strlen(ckey->valuestring));

    PR_DEBUG("httpc_proc_url_state succ!:%d", tuya_hal_system_getheapsize());

    return OPRT_OK;
}

STATIC OPERATE_RET tuya_svc_stream_proc_result(ty_cJSON *result)
{

    ty_cJSON  *cloudStorage = NULL, *imgCloudStorage = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("tuya_svc_stream_proc_result:%d", tuya_hal_system_getheapsize());

    //cloudstorage image info
    imgCloudStorage = ty_cJSON_GetObjectItem(result, "imgCloudStorage");
    if (NULL == imgCloudStorage) {
        PR_ERR("ty_cJSON_GetObjectItem imgCloudStorage err");
        return OPRT_CJSON_GET_ERR;
    } else {
        PR_DEBUG("get imgCloudStorage!!!!");
        op_ret = httpc_proc_url_state(imgCloudStorage, g_photo_info);
        if (op_ret != OPRT_OK) {
            PR_ERR("get imgCloudStorage err!");
            return op_ret;
        }
    }

    //cloudstorage media info
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
        cloudStorage = ty_cJSON_GetObjectItem(result, "cloudStorage");
        if (NULL == cloudStorage) {
            PR_ERR("ty_cJSON_GetObjectItem cloudStorage err");
            return OPRT_CJSON_GET_ERR;
        } else {
            PR_DEBUG("get cloudStorage!");
            op_ret = httpc_proc_url_state(cloudStorage, g_stream_info);
            if (op_ret != OPRT_OK) {
                PR_ERR("get cloudStorage err!");
                return op_ret;
            }
        }
    }
    return OPRT_OK;
}

STATIC OPERATE_RET tuya_svc_stream_start(UCHAR_T type)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *result = NULL;
    CHAR_T *out = NULL;
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }
    GW_CNTL_S *gw_cntl = get_gw_cntl();
    ty_cJSON_AddStringToObject(root, "devId", gw_cntl->gw_if.id);
    ty_cJSON_AddNumberToObject(root, "streamType", type); //buff

    TIME_T tm = uni_time_get_posix();
    snprintf((CHAR_T *)(g_photo_info->name), PHOTO_NAME_SIZE, "%010d.%s", tm, "jpg"); //time.jpg;
    ty_cJSON_AddStringToObject(root, "fileName", (CHAR_T *)(g_photo_info->name)); //buff
    ty_cJSON_AddStringToObject(root, "bizType", TY_URL_BIZTYPE_IMAGE);
    ty_cJSON_AddStringToObject(root, "contentType", TY_URL_CONTENTYPE_IMAGE);

    out = ty_cJSON_PrintUnformatted(root);
    PR_INFO("tuya_svc_stream_get out :%s", out);
    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR ;
    }

    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        op_ret = iot_httpc_common_post(TY_SVC_PHOTO_GET_ATOP, TY_SVC_PHOTO_GET_VER, NULL, gw_cntl->gw_if.id, out, NULL, &result);
    } else {
        op_ret = iot_httpc_common_post(TY_SVC_STREAM_NEW_GET_ATOP, TY_SVC_STREAM_NEW_GET_VER, NULL, gw_cntl->gw_if.id, out, NULL, &result);
    }

//    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
//        op_ret = iot_httpc_common_post(TY_SVC_PHOTO_GET_ATOP, TY_SVC_PHOTO_GET_VER, NULL, gw_cntl->gw_if.id, out, NULL, &result);
//    } else {
//        op_ret = iot_httpc_common_post(TY_SVC_STREAM_GET_ATOP, TY_SVC_STREAM_GET_VER, NULL, gw_cntl->gw_if.id, out, NULL, &result);
//    }



    Free(out);
    out = NULL;

    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_common_post TY_SVC_STREAM_GET_ATOP failed! op_ret:%d", op_ret);
        return op_ret;
    }

    if (result == NULL) {
        PR_ERR("http TY_SVC_STREAM_GET_ATOP result is null");
        op_ret = OPRT_COM_ERROR;
        return op_ret;
    }

    op_ret = tuya_svc_stream_proc_result(result); //,info
    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_proc_url_state failed! op_ret:%d", op_ret);
    }
    PR_NOTICE("ty_photo_url_get succ!:%d", tuya_hal_system_getheapsize());

    ty_cJSON_Delete(result);
    result = NULL;


    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        ty_sys_dp_upload_photo(g_photo_info);
    } else if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
        ty_sys_dp_upload_media(g_stream_info);
        tuya_doorbell_upload(g_photo_info);
    } else {
        ty_sys_dp_upload_media(g_stream_info);
        tuya_doorbell_upload(g_photo_info);
    }
    return op_ret;
}


OPERATE_RET get_camer_config(IN CHAR_T *pstr, OUT IPC_MEDIA_INFO_S  *av_info, OUT INT_T *flash_rotat_angle, BOOL_T *is_uplord_new_skill, BOOL_T *is_support_audio)
{
    OPERATE_RET op_ret = OPRT_OK;
    cJSON *root = NULL;
    cJSON *item;
    PR_DEBUG("get_camer_config info:%s", pstr);
    root = cJSON_Parse(pstr);
    if (NULL == root) {
        PR_ERR("pdata:%s", pstr);
        return OPRT_COM_ERROR;
    }

    item = cJSON_GetObjectItem(root, "is_uplord_new_skill");
    if (NULL == item) {
        PR_ERR("cj get itemfailed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        *is_uplord_new_skill = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "is_support_audio");
    if (NULL == item) {
        PR_ERR("cj get itemfailed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        *is_support_audio = item->valueint;
    }
    item = cJSON_GetObjectItem(root, "video_fps");
    if (NULL == item) {
        PR_ERR("cj get itemfailed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_fps[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "video_width");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_width[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "video_height");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_height[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "video_codec");
    if (NULL == item) {
        PR_ERR("cj get item  failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_codec[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "audio_codec");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_codec[E_CHANNEL_AUDIO] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "audio_sample");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_sample[E_CHANNEL_AUDIO] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "audio_databits");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_databits[E_CHANNEL_AUDIO] = item->valueint;
    }
    item = cJSON_GetObjectItem(root, "audio_channel");
    if (NULL == item) {
        PR_ERR("cj get item  failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_channel[E_CHANNEL_AUDIO] = item->valueint;
    }
    item = cJSON_GetObjectItem(root, "audio_fps");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_fps[E_CHANNEL_AUDIO] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "rotat_angle");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        *flash_rotat_angle = item->valueint;
    }

PROCE_END:
    cJSON_Delete(root);

    return op_ret;
}

STATIC OPERATE_RET save_camer_config(IN IPC_MEDIA_INFO_S  *av_info, INT_T rotat_angle, BOOL_T is_uplord_new_skill, BOOL_T is_support_audio)
{
    OPERATE_RET op_ret = OPRT_OK;
    PCHAR_T  out;
    cJSON *root = NULL;

    root = cJSON_CreateObject();
    if (NULL == root) {
        return OPRT_CR_CJSON_ERR;
    }
    cJSON_AddNumberToObject(root, "is_uplord_new_skill", is_uplord_new_skill);
    cJSON_AddNumberToObject(root, "is_support_audio", is_support_audio);
    cJSON_AddNumberToObject(root, "video_fps", av_info->video_fps[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "video_width", av_info->video_width[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "video_height", av_info->video_height[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "video_codec", av_info->video_codec[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "audio_codec", av_info->audio_codec[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_sample", av_info->audio_sample[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_databits", av_info->audio_databits[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_channel", av_info->audio_channel[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_fps", av_info->audio_fps[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "rotat_angle", rotat_angle);
    out = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (NULL == out) {
        return OPRT_MALLOC_FAILED;
    }
    PR_NOTICE("save_camer_config:%s", out);

    op_ret = wd_common_write(TY_SVC_CAMER_INFO, (const BYTE_T *)out, strlen(out));

    Free(out);

    return op_ret;
}


OPERATE_RET stream_infor_delete(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = wd_common_delete(TY_SVC_CAMER_INFO);
    if (OPRT_OK != op_ret) {
        PR_ERR("stream_infor_delete  err:%d", op_ret);
    }
    return op_ret;
}

STATIC BOOL_T ty_check_camer_info(IPC_MEDIA_INFO_S *av_info, IPC_MEDIA_INFO_S *flash_info)
{
    BOOL_T ret = TRUE;
    if (!g_pt_ctrl.is_support_audio) {
        if (av_info->video_fps[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_fps[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_width[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_width[E_CHANNEL_VIDEO_MAIN] \
            || av_info->video_height[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_height[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_codec[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_codec[E_CHANNEL_VIDEO_MAIN]) {
            return FALSE;
        }
    } else {
        if (av_info->video_fps[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_fps[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_width[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_width[E_CHANNEL_VIDEO_MAIN] \
            || av_info->video_height[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_height[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_codec[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_codec[E_CHANNEL_VIDEO_MAIN] \
            || av_info->audio_codec[E_CHANNEL_AUDIO] !=  flash_info->audio_codec[E_CHANNEL_AUDIO]  \
            || av_info->audio_sample[E_CHANNEL_AUDIO] !=  flash_info->audio_sample[E_CHANNEL_AUDIO] \
            || av_info->audio_databits[E_CHANNEL_AUDIO] !=  flash_info->audio_databits[E_CHANNEL_AUDIO]  \
            || av_info->audio_channel[E_CHANNEL_AUDIO] !=  flash_info->audio_channel[E_CHANNEL_AUDIO]  \
            || av_info->audio_fps[E_CHANNEL_AUDIO] !=  flash_info->audio_fps[E_CHANNEL_AUDIO]) {
            return FALSE;
        }
    }

    return ret;
}
STATIC UINT_T get_camera_is_h264(VOID_T)
{
    //0 jpeg 1 264  2 265
    return 0;
}

STATIC VOID tuya_stream_default_init(IPC_MEDIA_INFO_S *av_info)
{
#if (TCFG_HOST_AUDIO_ENABLE==1)
    ty_usb_audio_get_cfg(&audio_param.channel_num, &audio_param.bit_dept, &audio_param.sample_rate);
    PR_NOTICE("camera param:sample_rate %d bit_dept %d channel_num %d", audio_param.sample_rate, audio_param.bit_dept, audio_param.channel_num);
#endif
    //可更改
    av_info->channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
    av_info->video_fps[E_CHANNEL_VIDEO_MAIN] = camera_param.video_fps;
    av_info->video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
    av_info->video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;
    av_info->video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;
    av_info->video_width[E_CHANNEL_VIDEO_MAIN] = camera_param.video_width;
    av_info->video_height[E_CHANNEL_VIDEO_MAIN] = camera_param.video_height;
    av_info->video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;

    av_info->audio_codec[E_CHANNEL_AUDIO] = TUYA_CODEC_AUDIO_PCM;
    /* av_info->audio_sample[E_CHANNEL_AUDIO] = 16000;//audio_param.sample_rate;//8000; */
    /* av_info->audio_databits[E_CHANNEL_AUDIO] = 16;//audio_param.bit_dept;//16; */
    av_info->audio_sample[E_CHANNEL_AUDIO] = audio_param.sample_rate;//8000;
    av_info->audio_databits[E_CHANNEL_AUDIO] = audio_param.bit_dept;//16;
    av_info->audio_channel[E_CHANNEL_AUDIO] = TUYA_AUDIO_CHANNEL_MONO;
    av_info->audio_fps[E_CHANNEL_AUDIO] = TY_STREAM_AUDIO_FPS;
}


STATIC OPERATE_RET ty_photo_stream_init(UCHAR_T trigger_type)
{
    OPERATE_RET op_ret = OPRT_OK;
    IPC_MEDIA_INFO_S av_info = {0};

    g_pt_ctrl.is_support_audio = TRUE;

    tuya_stream_default_init(&av_info);


    BOOL_T need_uplord_skill = FALSE;
    IPC_MEDIA_INFO_S flash_av_info = {0};
    INT_T flash_rotat_angle = 0;
    INT_T uplord_rotat_angle = -1;

    UINT_T read_len = 0;
    CHAR_T *flash_dat = NULL;
    UINT_T flash_len = 0;
    BOOL_T is_support_audio;
    BOOL_T is_uplord_new_skill;
    op_ret = wd_common_read(TY_SVC_CAMER_INFO, (BYTE_T **)(&flash_dat), &flash_len);
    if (OPRT_OK != op_ret) {
        need_uplord_skill = TRUE;
        PR_DEBUG("wd_common_read fail need_uplord_skill");
    } else {
        if (OPRT_OK != get_camer_config(flash_dat, &flash_av_info, &flash_rotat_angle, &is_uplord_new_skill, &is_support_audio)) {
            need_uplord_skill = TRUE;
            PR_DEBUG("get_camer_config fail need_uplord_skill");
        } else {
            if (trigger_type) {
                if (!is_uplord_new_skill) {
                    need_uplord_skill = TRUE;
                    PR_DEBUG("uplord fail need_uplord_skill");
                } else if (FALSE == ty_check_camer_info(&flash_av_info, &av_info)) {
                    need_uplord_skill = TRUE;
                    PR_DEBUG("check fail need_uplord_skill");
                } else if (is_support_audio != g_pt_ctrl.is_support_audio) {
                    need_uplord_skill = TRUE;
                    PR_DEBUG("is_support_audio fail need_uplord_skill");
                }
            } else {
                if (!is_uplord_new_skill) {
                    need_uplord_skill = TRUE;
                    memcpy(&av_info, &flash_av_info, SIZEOF(IPC_MEDIA_INFO_S));
                    PR_DEBUG("____uplord fail need_uplord_skill");
                }
            }
        }

    }
    Free(flash_dat);
    flash_dat = NULL;
    TSTREAMER_S *pstreamer = GetTStreamerInstance();
    if (pstreamer) {
        pstreamer->RegisterCb(__event_cb, __recv_audio_cb, __get_frame_cb);
        pstreamer->SupportAudio(g_pt_ctrl.is_support_audio);
        pstreamer->SetMediaSetting(&av_info);
    }

    if (need_uplord_skill) {
        op_ret = ty_update_skill_and_rotate(uplord_rotat_angle);
        if (OPRT_OK == op_ret) {
            is_uplord_new_skill = TRUE;
            save_camer_config(&av_info, uplord_rotat_angle, is_uplord_new_skill, g_pt_ctrl.is_support_audio);
        }
    } else {
        PR_DEBUG("not need_uplord_skill!!");
    }


    return op_ret;
}

STATIC OPERATE_RET ty_photo_stream_first_uplord(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    IPC_MEDIA_INFO_S av_info = {0};

    g_pt_ctrl.is_support_audio = TRUE;
    tuya_stream_default_init(&av_info);

    INT_T uplord_rotat_angle = -1;

    UINT_T read_len = 0;

    TSTREAMER_S *pstreamer = GetTStreamerInstance();
    if (pstreamer) {
        pstreamer->RegisterCb(__event_cb, __recv_audio_cb, __get_frame_cb);
        pstreamer->SupportAudio(g_pt_ctrl.is_support_audio);
        pstreamer->SetMediaSetting(&av_info);
    }
    op_ret = ty_update_skill_and_rotate(uplord_rotat_angle);
    if (OPRT_OK == op_ret) {
        save_camer_config(&av_info, uplord_rotat_angle, TRUE, g_pt_ctrl.is_support_audio);
    } else {
        save_camer_config(&av_info, uplord_rotat_angle, FALSE, g_pt_ctrl.is_support_audio);
    }
    return op_ret;
}

STATIC OPERATE_RET ty_photo_stream_init_and_start(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T type = E_STREAM_VIDEO_MAIN;
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        type = E_STREAM_VIDEO_MAIN;
    } else {
        type = E_STREAM_VIDEO_AUDIO;
    }
    g_pt_ctrl.proc_state = PT_PROC_START;
    op_ret = ty_photo_stream_init(g_pt_ctrl.trigger_type);
    op_ret = tuya_svc_stream_start(type);
    return op_ret;
}

STATIC OPERATE_RET ty_sys_dp_upload_photo(UPLOAD_INFO *upload_info)
{

    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *pt_arry = NULL, *file_arry = NULL, *ext = NULL;
    CHAR_T *out = NULL;
    CHAR_T expire_time[11];
    memset(expire_time, 0, sizeof(expire_time));
    PR_NOTICE("ty_sys_dp_upload_photo :%d", tuya_hal_system_getheapsize());
    root = ty_cJSON_CreateObject();
    ext = ty_cJSON_CreateObject();
    pt_arry = ty_cJSON_CreateArray();
    file_arry = ty_cJSON_CreateArray();

    if (upload_info == NULL) {
        PR_ERR("ty_sys_dp_upload_photo param error!");
        return OPRT_INVALID_PARM;
    }
    if ((NULL == root) || (NULL == pt_arry) || (NULL == file_arry) || (NULL == ext)) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }

    ty_cJSON_AddStringToObject(root, "v", TY_DP212_VER_50);
    ty_cJSON_AddStringToObject(root, "cmd", TY_DP212_CMD_COVER);
    ty_cJSON_AddStringToObject(root, "type", TY_DP212_TYPE_IMAGE);
    ty_cJSON_AddStringToObject(root, "with", TY_DP212_WITH_RESORCES);
    ty_cJSON_AddBoolToObject(root, "alarm", TRUE);//默认给1

    /*add time segment*/
    TIME_T time = ty_trigger_time_proc(upload_info->time_flag, upload_info->tm);
    ty_cJSON_AddNumberToObject(root, "time", time);
    sprintf(expire_time, "%d", time + upload_info->expire);

    /*add files segment*/
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(upload_info->bucket));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(upload_info->ckey));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(upload_info->key));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(expire_time));
    ty_cJSON_AddItemToArray(file_arry, pt_arry);

    ty_cJSON_AddItemToObject(root, "files", file_arry);

    /*add ext segment*/
    ty_cJSON_AddBoolToObject(ext, "record", TRUE);
    ty_cJSON_AddNumberToObject(ext, "id", upload_info->id);
    ty_cJSON_AddNumberToObject(ext, "type", upload_info->event_type);
    ty_cJSON_AddStringToObject(ext, "fileId", upload_info->url_id);
    ty_cJSON_AddBoolToObject(ext, "hasMedia", FALSE);
    ty_cJSON_AddItemToObject(root, "ext", ext);

    out = ty_cJSON_PrintUnformatted(root);

    PR_DEBUG("ty_photo_sys_dp_upload out :%s", out);

    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR;
    }

    op_ret = dev_report_dp_raw_sync_extend_with_time(get_gw_cntl()->gw_if.id, PT_SYS_DP, (const BYTE_T *)out, strlen(out), 5, TRUE, NULL);
    if (OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_raw_sync failed op_ret:%d", op_ret);
        Free(out);
        out = NULL;
        return OPRT_COM_ERROR;
    }
    Free(out);
    out = NULL;

    PR_NOTICE("ty_photo_sys_dp_upload succ:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC OPERATE_RET ty_sys_dp_upload_media(UPLOAD_INFO *upload_info)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *pt_arry = NULL, *md_arry = NULL, *file_arry = NULL, *ext = NULL;
    CHAR_T *out = NULL;
    CHAR_T expire_time[20];
    memset(expire_time, 0, sizeof(expire_time));
    PR_NOTICE("ty_sys_dp_upload_media :%d", tuya_hal_system_getheapsize());
    root = ty_cJSON_CreateObject();
    ext = ty_cJSON_CreateObject();
    pt_arry = ty_cJSON_CreateArray();
    md_arry = ty_cJSON_CreateArray();
    file_arry = ty_cJSON_CreateArray();

    if (upload_info == NULL) {
        PR_ERR("ty_sys_dp_upload_media param error!");
        return OPRT_INVALID_PARM;
    }

    if ((NULL == root) || (NULL == pt_arry) || (NULL == file_arry) || (NULL == ext)) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }

    ty_cJSON_AddStringToObject(root, "v", TY_DP212_VER_50);
    ty_cJSON_AddStringToObject(root, "cmd", TY_DP212_CMD_VIDEO);
    ty_cJSON_AddStringToObject(root, "type", TY_DP212_TYPE_MEDIA);
    ty_cJSON_AddStringToObject(root, "with", TY_DP212_WITH_RESORCES);
    ty_cJSON_AddBoolToObject(root, "alarm", TRUE);//默认给1

    /*add time segment*/
    TIME_T time = ty_trigger_time_proc(upload_info->time_flag, upload_info->tm);
    ty_cJSON_AddNumberToObject(root, "time", time);

    /*add files segment*/
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(g_photo_info->bucket));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(g_photo_info->ckey));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(g_photo_info->key));
    sprintf(expire_time, "%d", time + g_photo_info->expire);
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(expire_time));
    ty_cJSON_AddItemToArray(file_arry, pt_arry);

    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(upload_info->bucket));
    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(upload_info->ckey));
    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(upload_info->key));
    sprintf(expire_time, "%d", time + upload_info->expire);
    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(expire_time));
    ty_cJSON_AddItemToArray(file_arry, md_arry);

    ty_cJSON_AddItemToObject(root, "files", file_arry);

    /*add ext segment*/
    ty_cJSON_AddBoolToObject(ext, "record", TRUE);
    ty_cJSON_AddNumberToObject(ext, "id", upload_info->id);
    ty_cJSON_AddNumberToObject(ext, "type", upload_info->event_type);
    ty_cJSON_AddStringToObject(ext, "fileId", upload_info->url_id);
    ty_cJSON_AddItemToObject(root, "ext", ext);

    out = ty_cJSON_PrintUnformatted(root);

    PR_DEBUG("ty_photo_sys_dp_upload out :%s", out);

    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR;
    }

    op_ret = dev_report_dp_raw_sync_extend_with_time(get_gw_cntl()->gw_if.id, PT_SYS_DP, (const BYTE_T *)out, strlen(out), 5, TRUE, NULL);
    if (OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_raw_sync failed op_ret:%d", op_ret);
        Free(out);
        out = NULL;
        return OPRT_COM_ERROR;
    }
    Free(out);
    out = NULL;

    PR_NOTICE("ty_photo_sys_dp_upload succ:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC VOID ty_data_info_clean(UPLOAD_INFO **info)
{
    UPLOAD_INFO *upload_info = *info;
    //PR_NOTICE("ty_data_info_clean :%d",tuya_hal_system_getheapsize());
    if (NULL == upload_info) {
        PR_NOTICE("g_photo_info is null,do not need free");
        return;
    }

    if (NULL != upload_info->url) {
        PR_DEBUG("free photo_url");
        Free(upload_info->url);
        upload_info->url = NULL;
    }
    if (NULL != upload_info->auth) {
        PR_DEBUG("free photo_auth");
        Free(upload_info->auth);
        upload_info->auth = NULL;
    }
    if (NULL != upload_info->date) {
        PR_DEBUG("free photo_date");
        Free(upload_info->date);
        upload_info->date = NULL;
    }
    if (NULL != upload_info->cont) {
        PR_DEBUG("free photo_cont");
        Free(upload_info->cont);
        upload_info->cont = NULL;
    }
    if (NULL != upload_info->ckey) {
        PR_DEBUG("free photo_ckey");
        Free(upload_info->ckey);
        upload_info->ckey = NULL;
    }
    if (NULL != upload_info->url_id) {
        PR_DEBUG("free id");
        Free(upload_info->url_id);
        upload_info->url_id = NULL;
    }
    if (NULL != upload_info->key) {
        PR_DEBUG("free photo_key");
        Free(upload_info->key);
        upload_info->key = NULL;
    }

    if (NULL != upload_info->bucket) {
        PR_DEBUG("free bucket");
        Free(upload_info->bucket);
        upload_info->bucket = NULL;
    }

    //PR_NOTICE("ty_photo_info_clean succ!!!");
    return;
}
/***********************************************************
*  Function: tuya_doorbell_mq43_msg_upload
*  Input: none
*  Output: none
*  Return: none
*  Note: 43 Popup window
***********************************************************/
STATIC OPERATE_RET tuya_doorbell_mq43_msg_upload(UPLOAD_INFO *upload_info)
{

    ty_cJSON *root = NULL;
    UCHAR_T *out = NULL;
    UINT_T wakeup_data;
    GW_CNTL_S *gw_cntl = get_gw_cntl();

    if (NULL == gw_cntl) {
        PR_ERR("get_gw_cntl is null");
        return OPRT_COM_ERROR;
    }

    //PR_NOTICE("ty_doorbell_mq43_msg_upload :%d",tuya_hal_system_getheapsize());
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        return OPRT_MALLOC_FAILED;
    }

    ty_cJSON_AddNumberToObject(root, "protocol", 43);
    TIME_T time = ty_trigger_time_proc(upload_info->time_flag, upload_info->tm);
    ty_cJSON_AddNumberToObject(root, "time", time);

    ty_cJSON_AddStringToObject(root, "etype", "doorlock");


    CHAR_T edata1[20] = {0};
    CHAR_T edata2[20] = {0};
    CHAR_T edata3[40] = {0};

    wakeup_data = hash_crc32i_total(gw_cntl->gw_actv.local_key, strlen(gw_cntl->gw_actv.local_key));

    snprintf(edata1, 20, "%x", wakeup_data);
    snprintf(edata2, 20, "%d", (INT_T)time);
    strncpy(edata3, edata1, 39);
    strcat(edata3, edata2);
    ty_cJSON_AddStringToObject(root, "edata", edata3);

    ty_cJSON_AddStringToObject(root, "filename", upload_info->name);

    ty_cJSON_AddStringToObject(root, "devId", gw_cntl->gw_if.id);

    out = ty_cJSON_PrintUnformatted(root);

    PR_DEBUG("ty_doorbell_mq43_msg_upload out :%s\n", out);
    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR;
    }

    INT_T ret = mqc_send_custom_mqtt_msg(43, (BYTE_T *)out);
    if (OPRT_OK > ret) {
        PR_ERR("mqc_send_custom_mqtt_msg failed op_ret:%d", ret);
        Free(out);
        out = NULL;
        return OPRT_COM_ERROR;
    }
    Free(out);
    out = NULL;

    PR_NOTICE("ty_doorbell_mq43_msg_upload succ:%d,ret:%d", tuya_hal_system_getheapsize(), ret);
    return OPRT_OK;
}

STATIC VOID tuya_doorbell_upload(UPLOAD_INFO *upload_info)
{
    //PR_NOTICE("evevt type is:%d", upload_info->event_type);
    if (upload_info->event_type == PT_EVENT_ALARM_REMOTE || \
        upload_info->event_type == PT_EVENT_DOORBELL_REQUEST || \
        upload_info->event_type == PT_EVENT_DOORBELL_AND_REMOTE) {
        tuya_doorbell_mq43_msg_upload(upload_info);
    }
}

STATIC VOID tuya_stream_start(VOID *data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T ret = 0;

    op_ret = ty_photo_stream_init_and_start();
    if (op_ret != OPRT_OK) {
        ret = PT_RET_NET_FAILED;
        ty_photo_send_msg(PT_DATA_END, &ret, 1);
    } else {
        PR_NOTICE("TUYA_STREAM_START succ!:%d", tuya_hal_system_getheapsize());
    }

}

STATIC VOID photo_process(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    PHOTO_CTRL_MSG *msg_data;
    UCHAR_T ret = 0;
    int msg[16] = {0,};

    while (1) {
        op_ret = os_q_pend(&g_pt_ctrl.msg_que, 0, msg);
        if (op_ret == OPRT_OK && msg[0] != NULL)  {
            msg_data = (PHOTO_CTRL_MSG *)msg[0];
            PR_NOTICE("tal_queue_fetch cmd %d", msg_data->cmd);
            PR_NOTICE("os_q_pend cmd %d", msg_data->cmd);
            PR_DEBUG("printf pend data:");
            put_buf(msg_data->data, msg_data->data_len);


            switch (msg_data->cmd) {

            case PT_DATA_INIT: {
                g_pt_ctrl.photo_id = 0;
                g_pt_ctrl.seq_id = 0;
                g_pt_ctrl.audio_seq = 0;

                op_ret = ty_photo_data_init_proc(msg_data->data);
                if (op_ret != OPRT_OK) {
                    ret = PT_RET_OTHER_FAILED;
                    PR_ERR("ty_photo_data_init_proc op_ret:%d", op_ret);
                    ty_photo_send_msg(PT_DATA_END, &ret, 1);
                } else {
                    sys_start_timer(g_pt_ctrl.timer, TRIGGER_TIMEOUT, TIMER_ONCE);
                    ty_photo_send_msg(PT_STREAM_START, NULL, 0);
                }
            }
            break;
            case PT_STREAM_START: {
                if (g_pt_ctrl.is_busy != TRUE) {
                    break;
                }
                GW_WIFI_NW_STAT_E cur_nw_stat = 0;
                op_ret = get_wf_gw_nw_status(&cur_nw_stat);
                if (OPRT_OK == op_ret && (cur_nw_stat != STAT_CLOUD_CONN && cur_nw_stat != STAT_AP_CLOUD_CONN)) {
                    tuya_hal_system_sleep(10);
                    ty_photo_send_msg(PT_STREAM_START, NULL, 0);
                    break;
                }

                ty_work_queue_add(tuya_stream_start, NULL);
            }
            break;

            case PT_DATA_END: {
                UCHAR_T msg_result = *((UCHAR_T *)msg_data->data);
                PR_NOTICE("ty_photo_ack = %d g_photo_info=%d", msg_result, g_photo_info);
                ty_data_info_clean(&g_photo_info);
                ty_data_info_clean(&g_stream_info);
                tuya_clear_stream_que();
                if (NULL != last_stream_info) {
                    free(last_stream_info);
                    last_stream_info = NULL;
                }
                g_pt_ctrl.stream_is_busy = FALSE;
                g_pt_ctrl.is_busy = FALSE;
                if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
                    ty_device_net_audio(FALSE);
                }
                tuya_video_ctr(FALSE, 0);
                sys_stop_timer(g_pt_ctrl.timer);

                PR_NOTICE("PT_DATA_END succ! type=%d", g_pt_ctrl.trigger_type);
            }
            break;
            case PT_STREAM_DATA_START: {
                UCHAR_T msg_result = *((UCHAR_T *)msg_data->data);
                PR_NOTICE("ty_photo_ack = %d g_photo_info=%d", msg_result, g_photo_info);
                PR_NOTICE("PT_STREAM_DATA_START succ! type=%d", g_pt_ctrl.trigger_type);

                sys_start_timer(g_pt_ctrl.timer, DATA_TIMEOUT, TIMER_ONCE);
                if (FALSE == is_audio_play_open()) {
                    ty_device_net_audio(TRUE);
                }
                tuya_video_ctr(TRUE, 0);
                if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
                    if (g_photo_info) {
                        memcpy(g_pt_ctrl.tm, g_photo_info->tm, UPLOAD_TIMEBUFF_SIZE);
                    }
                }
                ty_data_info_clean(&g_photo_info);
                ty_data_info_clean(&g_stream_info);
                g_pt_ctrl.is_busy = FALSE;
            }
            break;

            }
        }
        if (msg_data) {
            if (msg_data->data) {
                tal_free(msg_data->data);
            }
            tal_free(msg_data);
            msg_data = NULL;
        }
    }
}

STATIC VOID ty_stream_timeout_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    UCHAR_T ret = PT_RET_TIME_OUT;
    USHORT_T id = 0;
    PR_NOTICE("ty_stream_timeout_cb proc_state =%d g_pt_ctrl.is_busy=%d", g_pt_ctrl.proc_state, g_pt_ctrl.is_busy);
    if (PT_PROC_NULL == g_pt_ctrl.proc_state || PT_PROC_START == g_pt_ctrl.proc_state) {
        ret = PT_RET_NET_FAILED;
    }
    g_pt_ctrl.stream_is_over_time = TRUE;
    ty_photo_send_msg(PT_DATA_END, &ret, 1);
    return ;
}


OPERATE_RET ty_photo_proc_init(TY_STREAM_SEND_FRAME_HANDLE_CB cb)
{
    OPERATE_RET op_ret = OPRT_OK;

    tuya_ipc_streamer_set_max_frame_size(MAX_FRGE_SIZE);
    if (g_pt_ctrl.photo_init) {
        PR_NOTICE("ty_photo_proc_init is already done!!!");
        return op_ret;
    }
    if (NULL == cb) {
        return OPRT_INVALID_PARM;
    }

    memset(&g_pt_ctrl, 0, sizeof(PHOTO_CRTL));
    g_pt_ctrl.trigger_type = TRIGGER_TYPE_STREAM;
    g_pt_ctrl.cb = cb;


    QS queue_size = (SIZEOF(PHOTO_CTRL_MSG *) * 20 + sizeof(WORD) - 1) / sizeof(WORD);
    op_ret = os_q_create(&g_pt_ctrl.msg_que, queue_size);
    if (OPRT_OK != op_ret) {
        PR_ERR("os_q_create op_ret:%d", op_ret);
        return op_ret;
    }

    op_ret = ty_stream_queue_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_stream_queue_init op_ret:%d", op_ret);
        return op_ret;
    }

    sys_add_timer(print_net_timer_cb, NULL, &print_net_rate_timer);

    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_2;
    thrd_param.stackDepth = 1024 + 512;
    thrd_param.thrdname = "ty_photo_task";
    op_ret = CreateAndStart(&g_pt_ctrl.handle, NULL, NULL, photo_process, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("CreateAndStart failed!");
        return op_ret;
    }

    op_ret = sys_add_timer(ty_stream_timeout_cb, NULL, &g_pt_ctrl.timer);
    if (op_ret != OPRT_OK) {
        PR_ERR("sys_add_timer query_master_tm_cb failed! op_ret:%d", op_ret);
        return op_ret;
    }


    tuya_ipc_streamer_init();
    tuya_ipc_packager_init();
    tuya_ipc_encrypt_init();
    g_pt_ctrl.photo_init = TRUE;

    PR_NOTICE("ty_photo_proc_init malloc sucess:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}




OPERATE_RET ty_photo_kiwi_trigger_proc(UCHAR_T trigger_type, USHORT_T event_type, BOOL_T is_snap_flag, TIME_T *time)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    PT_TRIGGER_PROT trigger_data = {0};
    POSIX_TM_S   tm = {0};
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;

    if (TRUE != is_snap_flag) {
        PR_INFO("not need snap\n");
        op_ret = OPRT_OK;
        goto out;
    }


    if (!g_pt_ctrl.photo_init) {
        PR_ERR("photo proc not init,Please check whether the function is enabled");
        goto out;
    }

    GW_CNTL_S *gw_cntl = get_gw_cntl();
    if (gw_cntl->gw_wsm.stat != ACTIVATED) {
        PR_ERR("ty_photo_trigger_proc dev is not actived %d %s %s %s!!!", gw_cntl->gw_wsm.stat, gw_cntl->gw_wsm.token, gw_cntl->gw_wsm.region, gw_cntl->gw_wsm.regist_key);
        goto out;
    }

    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK != op_ret) {
        PR_ERR("get_wf_gw_nw_status err =%d", op_ret);
        goto out;
    }

    if ((STAT_CLOUD_CONN != cur_nw_stat) && (STAT_AP_CLOUD_CONN != cur_nw_stat)) {
        PR_WARN("no connect cloud\n");
        goto out;
    }


    if (g_pt_ctrl.is_busy) {
        PR_ERR("ty_photo_kiwi_trigger_proc is busy");
        goto out;
    }


    op_ret = uni_time_get(&tm);
    if (OPRT_OK != op_ret) {
        PR_ERR("uni_time_get failed! op_ret:%d", op_ret);
        goto out;
    }

    g_pt_ctrl.trigger_type = trigger_type;

    trigger_data.sub_cmd = 0x00;
    trigger_data.event_type = WORD_SWAP(event_type);
    trigger_data.trigger_type = trigger_type;
    trigger_data.time_flag = 0x02;
    trigger_data.time[0] = tm.tm_year - 100;
    trigger_data.time[1] = tm.tm_mon + 1;
    trigger_data.time[2] = tm.tm_mday;
    trigger_data.time[3] = tm.tm_hour;
    trigger_data.time[4] = tm.tm_min;
    trigger_data.time[5] = tm.tm_sec;

    *time = ty_trigger_time_proc(trigger_data.time_flag, trigger_data.time);

    PR_INFO("ty_photo_kiwi_trigger_proc time=%d\n", *time);

    op_ret = ty_photo_send_msg(PT_DATA_INIT, &trigger_data, sizeof(trigger_data));
    if (op_ret) {
        PR_ERR("ty_photo_kiwi_trigger_proc PT_DATA_INIT failed\n");
    }

out:

    return op_ret;

}



STATIC VOID __ipc_http_fill_skills_cb(INOUT CHAR_T *skills)
{
    if (NULL == skills) {
        return;
    }
    INT_T Num = 0;
    strcat(skills, "{\\\"localStorage\\\":1");
    strcat(skills, ",\\\"cloudP2P\\\":1");
    strcat(skills, ",\\\"cloudGW\\\":1}");
}

OPERATE_RET ty_photo_cloudp2p_iot_init(VOID)
{
    memset(ipc_skills, 0, sizeof(ipc_skills));
    strcpy(ipc_skills, "\"skillParam\":\"");
    snprintf(ipc_skills + strlen(ipc_skills), IPC_SKILLS_BUF_LEN - strlen(ipc_skills), "{\\\"type\\\":%d,\\\"skill\\\":", TUYA_P2P_TYPE);
    __ipc_http_fill_skills_cb(ipc_skills);
    strcat(ipc_skills, "}\"");
    PR_DEBUG("cloudp2p_iot_init ! %s", ipc_skills);
    gw_active_set_ext_param(ipc_skills);
    return 0;
}


STATIC OPERATE_RET tuya_rotating_upload(UINT_T rotation_angle)
{
#define MATOP_POST_DATA_LEN               30
#define MATOP_POST_DATA_LEN_RESERVED      35

    OPERATE_RET op_ret = OPRT_OK;

    ty_cJSON *root = NULL, *result = NULL;
    CHAR_T *out = NULL;
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }
    CHAR_T *post_data = Malloc(MATOP_POST_DATA_LEN_RESERVED);
    if (post_data == NULL) {
        PR_ERR("Malloc Fail");
        return OPRT_MALLOC_FAILED;
    }
    memset(post_data, 0, MATOP_POST_DATA_LEN_RESERVED);

    snprintf(post_data, MATOP_POST_DATA_LEN, "{\"LOCK_ROTATE_ANGLE\":\"%d\"}", rotation_angle);

    PR_DEBUG("TI_DEV_SKILL_UPDATE post_data:%s", post_data);


    GW_CNTL_S *gw_cntl = get_gw_cntl();
    ty_cJSON_AddStringToObject(root, "devId", gw_cntl->gw_if.id);

    ty_cJSON_AddStringToObject(root, "propKvs", post_data); //buff

    Free(post_data);
    post_data = NULL;


    out = ty_cJSON_PrintUnformatted(root);
    PR_DEBUG("tuya_svc_stream_get out :%s", out);
    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR ;
    }

    op_ret = iot_httpc_common_post_simple("tuya.device.props.save", "1.0", out, NULL, &result);

    Free(out);
    out = NULL;


    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_common_post TY_SVC_ROATING_SET_ATOP failed! op_ret:%d", op_ret);
        return op_ret;
    }

    PR_NOTICE("rotation angle upload success");

    ty_cJSON_Delete(result);
    result = NULL;

    return op_ret;
}

STATIC VOID tuya_normal_up_skill(VOID *data)
{
    ty_photo_stream_init(g_pt_ctrl.trigger_type);
    return;
}


VOID ty_stream_init(VOID)
{
    ty_work_queue_add(tuya_normal_up_skill, NULL);
    return ;
}

STATIC VOID tuya_force_up_skill(VOID *data)
{
    ty_photo_stream_first_uplord();
    return;
}
VOID ty_stream_actice_force_uplord(VOID)
{
    ty_work_queue_add(tuya_force_up_skill, NULL);
    return ;
}

BOOL_T ty_get_stream_status(VOID)
{
    return g_pt_ctrl.stream_is_busy;
}
BOOL_T ty_get_stream_trigger_status(VOID)
{
    return g_pt_ctrl.is_busy;
}

VOID ty_set_camera_pic_w_h_r_f(INT_T w, INT_T h, INT_T rotation, INT_T f)
{
    camera_param.video_width = w;
    camera_param.video_height = h;
    camera_param.video_rotat_angle = rotation;
    camera_param.video_fps = f;
    return ;
}
VOID ty_get_camera_pic_w_h(INT_T *w, INT_T *h)
{
    *w = camera_param.video_width;
    *h = camera_param.video_height;
    return ;
}
VOID ty_get_camera_pic_w_h_r_f(INT_T *w, INT_T *h, INT_T *rotation, INT_T *f)
{
    *w = camera_param.video_width;
    *h = camera_param.video_height;
    *rotation = camera_param.video_rotat_angle;
    *f = camera_param.video_fps;
    return ;
}

VOID ty_set_audio_cfg(INT_T chan, INT_T bit, INT_T rate)
{
    audio_param.sample_rate = rate;
    audio_param.bit_dept = bit;
    audio_param.channel_num = chan;
    return ;
}
INT_T ty_get_audio_rate(VOID)
{
    return audio_param.sample_rate;
}


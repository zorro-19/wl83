#include "app_config.h"

#ifdef CONFIG_TUYA_SDK_ENABLE
#include "stream_core.h"
#include "system/includes.h"
#include "device/device.h"
#include "server/video_server.h"
#include "event/device_event.h"
#include "server/video_dec_server.h"
#include "yuv_soft_scalling.h"
#include "update.h"
#include "server/server_core.h"
#include "event/key_event.h"
#include "tuya_hal_network.h"
#include "uni_log.h"
#include "tuya_hal_system.h"
#include "sys_timer.h"
#include "tuya_hal_mutex.h"
#include "tuya_device.h"
#include "sys_timer.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "cJSON.h"
#include "ty_cJSON.h"
#include "tuya_iot_wifi_api.h"
#include "uni_thread.h"
#include "uni_msg_queue.h"
#include "tuya_hal_semaphore.h"
#include "tuya_video.h"
#include "tuya_ipc_streamer.h"

#include "tkl_queue.h"
#include "lcd_config.h"
#include "app_database.h"
#include "video_rec.h"
/***************************************************************************************/

#define TY_USE_IMAGE_TIMER  0
#define LCD_USE_YUV_CUT  0

#if  defined(TY_OLD_BORD) && (TY_OLD_BORD == 1)
#define  BUTTON_MENU_WAKE_UP_BIT            U8_BIT(1)
#define  POWER_EN_WAKE_UP_BIT               U8_BIT(0)
#define  DOOR_BELL_WAKE_UP_BIT              U8_BIT(2)
#else
#define  BUTTON_MENU_WAKE_UP_BIT            U8_BIT(1)
#define  POWER_EN_WAKE_UP_BIT               U8_BIT(0)
#define  DOOR_BELL_WAKE_UP_BIT              U8_BIT(2)
#define  UART_WAKE_UP_BIT                   U8_BIT(3)
#endif

#define CAMERA_INIT_DELAY_MS   10
#define CAMERA_MAX_JPEG_SIZE   512*1024 //JPEG_DEFAULT_BUFF_SIZE
#define AUDIO_MAX_SIZE   64*1024 //audio_DEFAULT_BUFF_SIZE
#define CAMERA_H264_MAX_SIZE   (80*1024)
#define USB_AUDIO_BUF_SIZE     (16*1024)
//#define MSG_START_VIDEO   1
//#define MSG_STOP_VIDEO    2
//#define MSG_LCD_BL_ON     3
//#define MSG_LCD_BL_OFF    4
#define MSG_START_VIDEO_SYN   5
#define MSG_STOP_VIDEO_SYN    6
#define MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS   7
#define MSG_LCD_BL_ON_SYN     8
#define MSG_LCD_BL_OFF_SYN    9
#define MSG_STOP_VIDEO_NEW_SYN    10

#define TY_DROP_JPEG_COUNT    15
#define TY_VIDEO_TASK_NAME    "ty_video_task"
#define TY_CAMERA_TASK_NAME    "camera_deal_task"

#define TY_WAIT_SEM_TIMEOUT   8000

typedef unsigned short WORD;

typedef struct {
    BOOL_T          lcd_open;
    BOOL_T          lcd_display_camera;
    BOOL_T          camera_open;
    BOOL_T          show_page_open;
    BOOL_T          is_clear_jpeg_lbuf;
    BOOL_T          camera_start[4];
    BOOL_T          rec_start[4];
    BOOL_T          uvc_start[4];
    BOOL_T          uvc_rec_start[4];
    UINT_T          lcd_width;
    UINT_T          lcd_height;
    MUTEX_HANDLE    mutex;
    SEM_HANDLE      semphore;
    OS_QUEUE        msg_que;
    THRD_HANDLE     task_handle;
    THRD_HANDLE     task_stream_handle;
    BOOL_T          camera_online;
    BOOL_T          audio_online;
    TIMER_ID        restart_camera_id;
} TY_VIDEO_CTRL;

//#pragma pack(4)
typedef struct {
    UINT_T              cmd;
    UCHAR_T             *data;
    UINT_T              data_len;
} TY_VIDEO_CTRL_MSG;
//#pragma pack()

STATIC TY_VIDEO_CTRL g_video_ctrl = {0};
STATIC UCHAR_T  uvcid = 1;
STATIC CHAR_T  audioid = -1;
/* STATIC int video0 = 0; */
/* STATIC int video1 = 0; */
/* STATIC int video2 = 0; */
STATIC struct server *video_server[4] = {NULL,};
STATIC struct server *uvc_server[4] = {NULL,};
STATIC struct server *video_rec[4] = {NULL,};
STATIC struct server *uvc_rec[4] = {NULL,};
STATIC struct servet *video_display[4] = {NULL,};
STATIC CHAR_T req_buf[CAMERA_MAX_JPEG_SIZE];
STATIC CHAR_T uvc_req_buf[CAMERA_MAX_JPEG_SIZE];
STATIC CHAR_T req_audio_buf[AUDIO_MAX_SIZE];
STATIC CHAR_T h264_buf[CAMERA_H264_MAX_SIZE];
STATIC INT_T yuv_data_size = 480 * 320 * 3 / 2;
STATIC UCHAR_T get_one_photo_jpeg = 0;
STATIC INT_T get_one_photo_jpeg_real_len = 0;
STATIC CHAR_T *get_one_photo_jpeg_buf = 0;
STATIC INT_T get_one_photo_jpeg_result = 0;
STATIC INT_T drop_jpeg_count = 0;
//STATIC INT_T camera_power_off = 0;
STATIC CHAR_T *yuv_temp = NULL;
STATIC UINT_T camera_is_h264 = 0;
STATIC UINT_T camera_h264_w = 0;
STATIC UINT_T camera_h264_h = 0;
STATIC INT_T video_state = 0;

STATIC int rec_state = 0;
STATIC u8 disp_state = 0;

char *audio_buf[CONFIG_VIDEO_REC_NUM] = {NULL,};
char *video_buf[CONFIG_VIDEO_REC_NUM] = {NULL,};

STATIC CHAR_T video_uvc_online[CONFIG_VIDEO_UVC_REC_NUM] = {0,};
STATIC int ty_uvc_id[CONFIG_VIDEO_UVC_REC_NUM] = {-1,};
char *uvc_audio_buf[CONFIG_VIDEO_UVC_REC_NUM] = {NULL,};
char *uvc_video_buf[CONFIG_VIDEO_UVC_REC_NUM] = {NULL,};
/* typedef struct { */

/* } ty_file; */
u8 gsen_lock;
struct vfscan *f_scan[2][CONFIG_VIDEO_REC_NUM];
u16 file_number[2][CONFIG_VIDEO_REC_NUM];
u16 old_file_number[2][CONFIG_VIDEO_REC_NUM];

u32 total_size;
u32 lock_fsize;

u8 need_restart_rec;

#define FILE_NAME_MAX_SIZE 128

FILE *file[CONFIG_VIDEO_REC_NUM];
FILE *new_file[CONFIG_VIDEO_REC_NUM];
u32 new_file_size[CONFIG_VIDEO_REC_NUM];
char fname[CONFIG_VIDEO_REC_NUM][MAX_FILE_NAME_LEN];

FILE *file_uvc[CONFIG_VIDEO_REC_NUM];
FILE *new_file_uvc[CONFIG_VIDEO_REC_NUM];
u32 new_file_size_uvc[CONFIG_VIDEO_REC_NUM];
char fname_uvc[CONFIG_VIDEO_REC_NUM][MAX_FILE_NAME_LEN];
static char date_uvc_file[3][FILE_NAME_MAX_SIZE];
static int uvc_online_num = 0;

#define TY_AUDIO_BUF_SIZE  64*1024
#define TY_VREC_FBUF_SIZE  512*1024 //200*1024
#define LOCK_FILE_PERCENT	40    //0~100

int video_flag;

/* static struct strm_video_hdl *fv_rec_handler = NULL; */
static struct video_rec_hdl *rec_handler = NULL;

/* #define __this_net  (&net_rec_handler) */
/* #define __this_strm	(fv_rec_handler) */
#define __this 	(rec_handler)


extern u32 user_uac_audio_read_input(u8 id, u8 *buf, u32 len);

STATIC OPERATE_RET tuya_send_video_msg(IN CONST UINT_T msgid, IN CONST VOID *data, IN CONST UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T msg_num = 0;
    if (!&g_video_ctrl.msg_que) {
        return OPRT_MSG_OUT_OF_LMT;
    }

    TY_VIDEO_CTRL_MSG *msg_data;
    msg_data = Malloc(sizeof(TY_VIDEO_CTRL_MSG) + 1);
    if (!msg_data) {
        return OPRT_MALLOC_FAILED;
    }
    memset(msg_data, 0, SIZEOF(TY_VIDEO_CTRL_MSG) + 1);
    msg_data->cmd = msgid;

    if (data && len) {
        msg_data->data = Malloc(len + 1);
        if (!msg_data->data) {
            if (msg_data) {
                Free(msg_data);
            }
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data->data, 0, len + 1);
        memcpy(msg_data->data, data, len);
        msg_data->data_len = len;
    } else {
        msg_data->data = NULL;
    }

    op_ret = os_q_post(&g_video_ctrl.msg_que, msg_data);
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

VOID_T tuya_video_stop_syn(VOID_T)
{
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_STOP_VIDEO_SYN, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        tuya_hal_semaphore_release(wait_sem);
        PR_ERR(" send fail");
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_stop_syn");
    tuya_hal_semaphore_release(wait_sem);
}

VOID_T tuya_video_stop_new_syn(INT_T force)
{
    INT_T send_data[2] ;
    send_data[0] = force;

    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    send_data[1] = wait_sem;
    op_ret =  tuya_send_video_msg(MSG_STOP_VIDEO_NEW_SYN, &send_data, SIZEOF(send_data));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_stop_new_syn");
    tuya_hal_semaphore_release(wait_sem);
}
VOID_T tuya_video_start_syn(VOID_T)
{
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_START_VIDEO_SYN, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_start_syn");
    tuya_hal_semaphore_release(wait_sem);
}
VOID_T tuya_video_start_syn_without_camer_on(VOID_T)
{
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_start_syn_without_camer_on");
    tuya_hal_semaphore_release(wait_sem);
}

VOID_T tuya_video_ctr(BOOL_T status, INT_T force)
{
    if (status) {
        tuya_video_start_syn();
    } else  {
        tuya_video_stop_new_syn(force);
    }
    return ;
}

CHAR_T *my_mem_find_str(UCHAR_T *src, UINT_T len, UCHAR_T **p_start, UCHAR_T **p_end, UCHAR_T **p_h264_start, UINT_T *p_h264_len, UINT_T *p_h264_type)
{
#define FAST_MAX_DATA_LEN   520    //必须>512
    CHAR_T *result = NULL;
    UCHAR_T *cur = src;
    UCHAR_T *last_cur = src;
    UCHAR_T seg_have = 0;
    UCHAR_T *start = NULL;
    UCHAR_T *end = NULL;
    UCHAR_T flag = 0;
    UCHAR_T end_flag = 0;
    UINT_T total_len = 0;
    UINT_T fast_find_ff_d9 = 0;
    UCHAR_T fast_find_ff_d9_count = 0;
    UINT_T h264_pos = 0;
    UINT_T ex_h264_len = 0;
    UINT_T ex_h264_type = 0;
    STATIC INT_T h264_p_count = 0;
    while (cur < src + len) {
        switch (cur[0]) {
        case 0xff: {
            seg_have = 1;
            last_cur = cur;
            switch (cur[1]) {
            case 0xd8:
                flag = 1;
                start = cur;
                cur += 2;
                ex_h264_len = 0;
                break;

            case 0xda:
                cur = src + len - FAST_MAX_DATA_LEN;
                fast_find_ff_d9 = 1;

                //  cur += 2;
                //  fast_find_ff_d9 = 0;
                break;

            case 0xd9:
                if (flag) {
                    end_flag = 1;
                    end = cur;
                }
                break;

            case 0xe7:
            case 0xe8:
            case 0xe9:
#if 0
                camera_is_h264 = 1;

                total_len = cur[2];
                total_len = (total_len << 8) + cur[3];
                memcpy(h264_buf + ex_h264_len, cur + 14, total_len - 12);
                ex_h264_len += (total_len - 12);
                if (cur[1] == 0xe7) {
                    ex_h264_type = GetFrameType(h264_buf);
                    camera_h264_w = 640;
                    camera_h264_h = 480;

                    if (ex_h264_type == NAL_SPS || ex_h264_type == NAL_SLICE_IDR) {
                        h264_p_count = 0;
                    } else {
                        h264_p_count++;
                    }
                    PR_NOTICE("h264_p_count = %d", h264_p_count);
                }
                cur = cur + 2 + total_len;

#endif // 0
                break;

            case 0xe0:
            case 0xe1:
            case 0xe2:
            case 0xe3:
            case 0xe4:
            case 0xe5:
            case 0xe6:
                goto JUMP_POSITION;
                break;

            case 0xea:
            case 0xeb:
            case 0xec:
            case 0xed:
            case 0xee:
            case 0xef:
                goto JUMP_POSITION;
                break;


            case 0xdb:
            case 0xdc:
            case 0xdd:
            case 0xde:
            case 0xdf:
                goto JUMP_POSITION;
                break;


            case 0xc0:
            case 0xc2:
            case 0xc4:
                goto JUMP_POSITION;
                break;

            case 0xc1:
            case 0xc3:
            case 0xc5:
            case 0xc6:
            case 0xc7:
            case 0xcc:
            case 0xcd:
            case 0xce:
            case 0xcf:
JUMP_POSITION:
                total_len = cur[2];
                total_len = (total_len << 8) + cur[3];
                cur = cur + 2 + total_len;
                break;

            default:
                seg_have = 0;
                cur++;
                if (fast_find_ff_d9) {
                    fast_find_ff_d9_count++;
                }
                break;

            }
#if 0
            if (seg_have) {
                if (last_cur[1] == 0xd8 || last_cur[1] == 0xd9) {
                    PR_NOTICE("find 0xff 0x%2x pos=%d count=%d\n", last_cur[1], last_cur - src, fast_find_ff_d9_count);
                } else if (last_cur[1] == 0xe7 || last_cur[1] == 0xe8 || last_cur[1] == 0xe9) {
                    PR_NOTICE("find 0xff 0x%2x pos=%d len=%d ex_h264_type=%d ex_h264_len=%d\n", last_cur[1], last_cur - src, total_len, ex_h264_type, ex_h264_len);
                } else {
                    PR_NOTICE("find 0xff 0x%2x pos=%d len=%d\n", last_cur[1], last_cur - src, total_len);
                }
            }
#endif
        }
        break;

        default:
            if (fast_find_ff_d9) {
                fast_find_ff_d9_count++;
            }

            cur++;
            break;
        }
        if (end_flag) {
            //PR_NOTICE("position 0x%x len %d  data 0x%x 0x%x 0x%x 0x%x\n",cur,len,cur[0],cur[1],cur[2],cur[3]);
            *p_start = start;
            *p_end = end;
            if (ex_h264_len) {
                *p_h264_start = h264_buf;
                *p_h264_len = ex_h264_len;
                *p_h264_type = ex_h264_type;
            }
            return cur;
        }

    }
    return result;
}



#define VPBUF_SIZE CAMERA_MAX_JPEG_SIZE/2
struct strm_ptl_info {
    u8 kill;
    u8 vd_use;
    u8 ad_use;
    u8 err;
    u8 init;
    u8 copy;
    SEM_HANDLE sem;
    u8 *video_pkbuff;
    u32 vd_len;
};
struct strm_ptl_info strm_ptl_info_ = {0};
#define strm_ptl (&strm_ptl_info_)

extern UINT_T real_size;
extern INT_T jpeg_count;
extern INT_T voice_count;

/* STATIC INT_T ty_video_frame_cb(UCHAR_T type, UCHAR_T *buf, UINT_T size) */
STATIC INT_T ty_stream_write(void *file,  UCHAR_T *buf, UINT_T size, UCHAR_T type)
{
    /* PR_NOTICE("into ty video frame cb, buf size:%d", size); */
    static int cnt;
    PR_DEBUG("buf size:%d, %s", size, os_current_task());
    // printf("buf size:%d, %s", size, os_current_task());
    if (size == 512 || size == 8192 || size == 1024) {
        return size;
    }
    if ((size < 2000) && (size != 1024)) {
        return size;
    }
#define jl_ntohl(x) (UINT_T)((((UINT_T)(x))>>24) | ((((UINT_T)(x))>>8)&0xff00) | (((UINT_T)(x))<<24) | ((((UINT_T)(x))&0xff00)<<8))
#define JL_ENDF     	jl_ntohl(0x56185719)
#define JPEG_HEAD 		0xE0FFD8FF
#define JL_000DC		jl_ntohl(0x30306463)
#define JL_001WB		jl_ntohl(0x30317762)

    if (type == VIDEO_REC_JPEG_TYPE_VIDEO) {
        u32 *head = (u32 *)buf;
        /* if (!strm_ptl->init || strm_ptl->err || strm_ptl->kill) { */
        /* return size; */
        /* } else  */
        if ((size <= 8) && (*head == JL_ENDF)) {
            return size;
        }

        if (drop_jpeg_count < TY_DROP_JPEG_COUNT) {
            drop_jpeg_count++;
            return size;
        }

        if (size > VPBUF_SIZE) {
            PR_NOTICE("VDPKBUFF_SIZE no enough !!!\n");
            return size;
        }

        if ((*head == JL_000DC && *(head + 2) == JPEG_HEAD) || *(head + 2) == JPEG_HEAD) {
            buf += 8;
            size -= 8;
        }
        jpeg_count++;
        real_size += size;
        /* PR_DEBUG("buf size:%d, %s", size, os_current_task()); */
        ty_stream_in_queue(buf, size, E_VIDEO_I_FRAME);
    } else if (type == VIDEO_REC_PCM_TYPE_AUDIO) {
        voice_count++;
        ty_audio_stream_in_queue(buf, size);
    }
    return size;
}

void *ty_stream_open(const char *path, const char *mode)
{
    return 1;
}

void ty_stream_close(void *file)
{

}


STATIC UINT_T get_camera_is_h264(VOID_T)
{
    //0 jpeg 1 264  2 265
    return 0;
}

void get_h264_width_and_height(UINT_T *width, UINT_T *height)
{
    *width = camera_h264_w;
    *height = camera_h264_h;
}



STATIC VOID_T stream_protocol_task(PVOID_T pArg)
{
    /* PR_NOTICE("into stream protocol task!"); */
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T jpeg_count = 0;
    INT_T now_time_ms = 0;
    INT_T ret = 0;
    INT_T w = 0;
    INT_T h = 0;

    UINT_T data_len = 0;
    UINT_T jpeg_size = 0;
    UCHAR_T *head_ffd8 = NULL;
    UCHAR_T *tail_ffd9 = NULL;
    UCHAR_T *h264_head = NULL;
    UINT_T h264_len = 0;
    UINT_T h264_type = 0;
    UCHAR_T *buf = NULL;
    UINT_T  size = 0;
    STATIC BOOL_T  inqueue_err = 0;
    STATIC BOOL_T  last_inqueue_err = 0;
    strm_ptl->init = true;
    PR_NOTICE("stream_protocol run");
    while (1) {
        ret = tuya_hal_semaphore_wait(strm_ptl->sem);

        /* if (strm_ptl->vd_use) { */
        head_ffd8 = strm_ptl->video_pkbuff;
        data_len = strm_ptl->vd_len;
        buf = strm_ptl->video_pkbuff;
        size = strm_ptl->vd_len;
        while (1) {
            /*  -----------------------将摄像头数据通过 ty_stream_in_queue 函数放入队列中------------------*/
            if (my_mem_find_str(head_ffd8, data_len, &head_ffd8, &tail_ffd9, &h264_head, &h264_len, &h264_type)) {
                jpeg_size = tail_ffd9 + 2 - head_ffd8;
                if (jpeg_size <= 2048) {
                    PR_NOTICE("jpeg size < 2048");
                    break;
                }
            } else {
                break;
            }
            ty_stream_in_queue(head_ffd8, (UINT_T)jpeg_size, E_VIDEO_I_FRAME);
            if (buf + size - tail_ffd9 < 2048) {
                break;
            } else {
                head_ffd8 = tail_ffd9 + 2;
                data_len -= jpeg_size;
#if TY_LCD_VIDEO_DEBUG_TIME
                PR_NOTICE("jpeg size %d left size %d total size %d", jpeg_size, data_len, size);
#endif
            }
        }
        strm_ptl->vd_use = false;
    }

}
OPERATE_RET stream_protocol_task_create(void)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (strm_ptl->init) {
        return OPRT_OK;
    }
    strm_ptl->kill = 0;
    strm_ptl->err = 0;
    strm_ptl->vd_use = 0;
    strm_ptl->ad_use = 0;

    tuya_hal_semaphore_create_init(&strm_ptl->sem, 0, 1);
    strm_ptl->video_pkbuff = Malloc(VPBUF_SIZE);
    if (!strm_ptl->video_pkbuff) {
        strm_ptl->err = true;
        PR_ERR("stream_protocol_task malloc err");
        return OPRT_MALLOC_FAILED;
    }

    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_0;//+10;//+5;
    thrd_param.stackDepth = 1024 * 4;
    thrd_param.thrdname = "ty_stream_protocol_task";
    op_ret = CreateAndStart(&g_video_ctrl.task_stream_handle, NULL, NULL, stream_protocol_task, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("stream_protocol_task err");
        strm_ptl->kill = true;
        strm_ptl->init = false;
    }
    return op_ret;
}


INT_T get_image_jpeg(CHAR_T **jpeg_buf, INT_T *real_len, INT_T time_out)
{
    STATIC UCHAR_T count = 0;
    if (0 == jpeg_buf || 0 == real_len) {
        return -1;
    }
    g_video_ctrl.camera_open = true;
    get_one_photo_jpeg = 1;
    get_one_photo_jpeg_result = -1;
    get_one_photo_jpeg_buf = NULL;
    tuya_hal_semaphore_waittimeout(g_video_ctrl.semphore, time_out);
    count = 0;
    *real_len = get_one_photo_jpeg_real_len;
    *jpeg_buf = get_one_photo_jpeg_buf;
    return get_one_photo_jpeg_result;
}


#define SCREEN_W   LCD_W
#define SCREEN_H   LCD_H

// #define SCREEN_W   800
// #define SCREEN_H   480
static struct video_window disp_window[DISP_MAX_WIN][4] = {0};

static void ty_video_set_disp_window()
{
    u16 small_screen_w;
    u16 small_screen_h;

    if (LCD_W > 1280) {
        small_screen_w = 480; //16 aline
        small_screen_h = 400; //16 aline
    } else if (LCD_W > 480) {
        small_screen_w = 320; //16 aline
        small_screen_h = 240; //16 aline
    } else {
        small_screen_w = 192; //16 aline
        small_screen_h = 160; //16 aline
    }

    //DISP_MAIN_WIN
    disp_window[DISP_MAIN_WIN][0].width  = SCREEN_W;
    disp_window[DISP_MAIN_WIN][0].height = SCREEN_H;
    disp_window[DISP_MAIN_WIN][1].width  = small_screen_w;
    disp_window[DISP_MAIN_WIN][1].height = small_screen_h;
    disp_window[DISP_MAIN_WIN][2].left   = SCREEN_W - small_screen_w;
    disp_window[DISP_MAIN_WIN][2].width  = small_screen_w;
    disp_window[DISP_MAIN_WIN][2].height = small_screen_h;

    //DISP_HALF_WIN
    disp_window[DISP_HALF_WIN][0].width  = SCREEN_W;// / 2;
    disp_window[DISP_HALF_WIN][0].height = SCREEN_H / 2;
    disp_window[DISP_HALF_WIN][1].left   = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][1].width  = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][1].height = SCREEN_H;
    /* disp_window[DISP_HALF_WIN][2].left   = SCREEN_W / 2; */
    disp_window[DISP_HALF_WIN][2].top   = SCREEN_H / 2;
    disp_window[DISP_HALF_WIN][2].width  = SCREEN_W;
    disp_window[DISP_HALF_WIN][2].height = SCREEN_H / 2;

    //DISP_FRONT_WIN
    disp_window[DISP_FRONT_WIN][0].width  = SCREEN_W;
    disp_window[DISP_FRONT_WIN][0].height = SCREEN_H;
    disp_window[DISP_FRONT_WIN][1].width  = (u16) - 1;
    disp_window[DISP_FRONT_WIN][1].height = SCREEN_H;

    //DISP_BACK_WIN
    disp_window[DISP_BACK_WIN][0].width  = (u16) - 1;
    disp_window[DISP_BACK_WIN][0].height = SCREEN_H;
    disp_window[DISP_BACK_WIN][1].width  = SCREEN_W;
    disp_window[DISP_BACK_WIN][1].height = SCREEN_H;
    disp_window[DISP_BACK_WIN][2].width  = SCREEN_W;
    disp_window[DISP_BACK_WIN][2].height = SCREEN_H;

    //DISP_PARK_WIN
    disp_window[DISP_PARK_WIN][0].width  = (u16) - 1;
    disp_window[DISP_PARK_WIN][0].height = SCREEN_H;
    disp_window[DISP_PARK_WIN][1].width  = SCREEN_W;
    disp_window[DISP_PARK_WIN][1].height = SCREEN_H;
    disp_window[DISP_PARK_WIN][2].width  = SCREEN_W;
    disp_window[DISP_PARK_WIN][2].height = SCREEN_H;
}


static void video_set_disp_mirror(int id, u16 mirror)
{
    for (int i = 0; i < DISP_MAX_WIN; i++) {
        disp_window[i][id].mirror = mirror;
    }
}



int  tuya_video_display(INT_T id, const struct video_window *win)
{
    union video_req req = {0};
    char fb_name[4];
    char dev_name[20];

    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);

    if (id == 2) {
        if (uvc_host_online() < 0) {
            PR_DEBUG("uvc is not online");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    }

#ifdef CONFIG_DISPLAY_ENABLE
    printf("video_disp_start: %d, %d x %d\n", id, win->width, win->height);

    if (win->width == (u16) - 1) {
        puts("video_disp_hide\n");
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
#ifdef CONFIG_UVC_VIDEO_ENABLE //CONFIG_VIDEO2_ENABLE
    if (id == 2) {
        if (uvc_host_online() < 0) {
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    }
#endif
    if (id == 2) {
        sprintf(dev_name, "video%d.%d", 10 + uvc_host_online(), 2);
    } else {
        sprintf(dev_name, "video%d.%d", id, 2);
    }
    if (!video_display[id]) {
        video_display[id] = server_open("video_server", (void *)dev_name);
        if (!video_display[id]) {
            PR_DEBUG("open video_server: faild, id = %d\n", id);
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    } else {
        PR_DEBUG("video server has open");
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    }
    memset(fb_name, 0, sizeof(fb_name));
    sprintf(fb_name, "fb%d", id + 1);
    req.display.fb 		        = fb_name;
    req.display.left  	        = win->left;
    req.display.top 	        = win->top;
    req.display.width 	        = win->height;//win->width;//win->height;
    req.display.height 	        = win->width;
    req.display.border_left     = win->border_left;
    req.display.border_top      = win->border_top;
    req.display.border_right    = win->border_right;
    req.display.border_bottom   = win->border_bottom;
    req.display.mirror   		= 0;//win->mirror;
    req.display.jaggy			= 0;	// IMC 抗锯齿
    req.display.state 	        = VIDEO_STATE_START;
    req.display.pctl            = NULL;

    /* #ifndef CONFIG_VIDEO2_ENABLE */
    if (id != 2) {
        req.display.camera_config   = NULL;
        req.display.camera_type     = VIDEO_CAMERA_NORMAL;
        // req.display.src_w           = CONFIG_VIDEO_IMAGE_W;//640;
        // req.display.src_h           = CONFIG_VIDEO_IMAGE_H;//480;
        req.display.rotate          = 90;
    } else {
        /* #else */
        req.display.uvc_id          = uvc_host_online();
        req.display.camera_config   = NULL;
        req.display.camera_type     = VIDEO_CAMERA_UVC;
        // req.display.src_w           = CONFIG_VIDEO_IMAGE_W;//640;
        // req.display.src_h           = CONFIG_VIDEO_IMAGE_H;//480;
        req.display.rotate          = 90; //usb后视频图像旋转显示
        /* #endif // CONFIG_VIDEO2_ENABLE */
    }
    if (video_display[id]) {
        int err = server_request(video_display[id], VIDEO_REQ_DISPLAY, &req);
        if (err) {
            printf("video server request error!");
            server_close(video_display[id]);
            video_display[id] = NULL;
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return err;
    }
    tuya_hal_mutex_unlock(g_video_ctrl.mutex);
    return -1;
#endif
}




void tuya_display_stop(int id)
{
    union video_dec_req dec_req = {0};
    union video_req req = {0};

    if (video_display[id]) {
        req.display.state 	= VIDEO_STATE_STOP;
        server_request(video_display[id], VIDEO_REQ_DISPLAY, &req);
        server_close(video_display[id]);
        video_display[id] = NULL;
    }
}


int display_convert(int flag)
{
    int ret;
    ty_video_set_disp_window();
    for (int i = 0; i < 4; i++) {
        tuya_display_stop(i);
    }
    switch (video_state) {
    case 2: //mipi
        ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 6: //mipi + uvc
#if 0
        if (!flag) {
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(0, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(2, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(0);
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 3: //dvp
        ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 7: //dvp + uvc
#if 0
        if (!flag) {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(1, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(2, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(1);
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 4: //uvc
        ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 8: // video3
        ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 12:// video+uvc
#if 0
        if (!flag) {
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(3, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(2, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(3);
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 5: //mipi+dvp
#if 0
        if (!flag) {
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(0, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(1, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(0);
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 11: //mipi video 3+dvp
#if 0
        if (!flag) {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(1, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(3, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(1);
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    default:
        ret = -1;
        break;
    }
    return ret;
}



void ty_net_video_stop();
void video_convert(INT_T flag); //双路摄像头切换
#if 1
static void rec_dev_server_event_handler(void *priv, int argc, int *argv)
{
    /*
     *该回调函数会在录像过程中，写卡出错被当前录像APP调用，例如录像过程中突然拔卡
     */
    int mark = 2;
    struct intent it;

    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        PR_DEBUG("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        PR_DEBUG("video_server_pkg_err\n");
        if (__this->state == VIDREC_STA_START) {
            video_rec_stop(0);
        }
        break;
    case VIDEO_SERVER_PKG_END:
        PR_DEBUG("video_server_pkg_end\n");
        if (db_select("cyc") > 0) {
            if (priv >= 10) {
                /* ty_net_video_stop(); */
                video_rec_uvc_savefile((int)priv - 10);
                /* video_convert(0);	 */
            } else {
                /* ty_net_video_stop(); */
                video_rec_savefile((int)priv);
                /* video_convert(0);	 */
            }
        } else {
            video_rec_stop(0);
        }
        break;
    case VIDEO_SERVER_NET_ERR:
        PR_DEBUG("\nVIDEO_SERVER_NET_ERR\n");
        /* init_intent(&it); */
        /* it.data = &mark; */
        /* net_video_rec_stop(0); */
        /* set_net_video_rec_state(0); */
        /* __this_net->is_open = FALSE; */
        break;

    default :
        PR_DEBUG("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}


#endif

INT_T  ty_video_start(INT_T id, INT_T img_w, INT_T img_h, INT_T fps) //net
{
    PR_DEBUG("into ty video start id:%d", id);
    INT_T ret = 0;
    char dev_name[20];
    union video_req req = {0};
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    /* 打开摄像头 */
    tuya_hal_mutex_lock(g_video_ctrl.mutex);
    if (id == 2) {
        if (uvc_host_online() < 0) {
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    }
    PR_DEBUG("uvc id:%d", uvc_host_online());
    PR_DEBUG("video_server:%x", video_server[id]);
    if (video_server[id] == NULL) {
        if (video_state == 2 || video_state == 3 || video_state == 4 || video_state == 8) {
#ifdef  CONFIG_UVC_VIDEO2_ENABLE
            goto __switch;
#endif
            if (id == 2) {
                PR_DEBUG("uvc id:%d", uvc_host_online());
                sprintf(dev_name, "video%d.%d", 10 + uvc_host_online(), 1);
            } else {
                sprintf(dev_name, "video%d.%d", id, 1);
            }
        } else {
__switch:
            switch (id) {
            case 0:
                video_server[id] = __this->video_rec0;
                break;
            case 1:
                video_server[id] = __this->video_rec1;
                break;
            case 2:
                if (uvc_host_online() == 0) {
                    video_server[id] = __this->video_uvc_rec0;
                } else if (uvc_host_online() == 1) {
                    video_server[id] = __this->video_uvc_rec1;
                } else if (uvc_host_online() == 2) {
                    video_server[id] = __this->video_uvc_rec2;
                }
                break;
            case 3:
                video_server[id] = __this->video_rec3;
                break;
            default:
                break;
            }
            if (video_server[id] == NULL) {
                if (id == 2) {
                    sprintf(dev_name, "video%d.%d", 10 + uvc_host_online(), 0);
                } else {
                    sprintf(dev_name, "video%d.%d", id, 0);
                }
            }
        }
    }
    /* puts(dev_name); */
    /* PR_DEBUG("dev_name:%s", dev_name); */
    if (video_server[id] == NULL) {
        video_server[id] = server_open("video_server", dev_name);
        if (video_server[id] == NULL) {
            PR_DEBUG("video server open err");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
        if (video_state == 2 || video_state == 3 || video_state == 4 || video_state == 8) {
        } else {
            switch (id) {
            case 0:
                __this->video_rec0 = video_server[id];
                break;
            case 1:
                __this->video_rec1 = video_server[id];
                break;
            case 2:
                if (uvc_host_online() == 0) {
                    __this->video_uvc_rec0 = video_server[id];
                } else if (uvc_host_online() == 1) {
                    __this->video_uvc_rec1 = video_server[id];
                } else {
                    __this->video_uvc_rec2 = video_server[id];
                }
                break;
            case 3:
                __this->video_rec3 = video_server[id];
                break;
            default:
                break;
            }
            if (id == 2) {
                server_register_event_handler_to_task(video_server[id], (VOID_T *)(uvc_host_online() + 10), rec_dev_server_event_handler, "app_core");
            } else {
                server_register_event_handler_to_task(video_server[id], (VOID_T *)id, rec_dev_server_event_handler, "app_core");
            }
        }
    }
    PR_DEBUG("video_server:%x", video_server[id]);

    if (video_server[id]) {
        PR_DEBUG("open video%d, g_video_ctrl.camera_start[%d]:%d", id, id, g_video_ctrl.camera_start[id]);
        if (g_video_ctrl.camera_start[id]) {
            PR_NOTICE("camera_start is already start");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return 0;
        }

        req.rec.camera_type = VIDEO_CAMERA_NORMAL;
        req.rec.channel = 1;
        req.rec.width 	= img_w;//img_w;//CONFIG_USER_VIDEO_WIDTH;
        req.rec.src_w 	= 1280;//CONFIG_USER_VIDEO_WIDTH;
        req.rec.height 	= img_h;//img_h;//CONFIG_USER_VIDEO_HEIGHT;
        req.rec.src_h 	= 720;//CONFIG_USER_VIDEO_HEIGHT;
        req.rec.state 	= VIDEO_STATE_START;
        req.rec.format 	= USER_VIDEO_FMT_AVI;
        req.rec.quality = VIDEO_LOW_Q;//VIDEO_MID_Q;//VIDEO_LOW_Q;//VIDEO_MID_Q;

        req.rec.IP_interval = 0;
        if (id == 2) {
            req.rec.online = 0;//0;
        } else {
            req.rec.online = 1;
        }

        if (id == 2) {
            if (uvc_host_online() < 0) {
                tuya_hal_mutex_unlock(g_video_ctrl.mutex);
                return -1;
            }
#ifdef CONFIG_UVC_VIDEO_ENABLE //CONFIG_VIDEO2_ENABLE
            req.rec.uvc_id = uvc_host_online();
#endif
        }

        if (id == 2) {
            req.rec.fps = fps;//10;
            req.rec.real_fps = fps;
        } else {
            req.rec.fps = fps;//10;
            req.rec.real_fps = fps;
        }

        req.rec.cycle_time = 1;
        req.rec.cycle_time = req.rec.cycle_time * 60;
        req.rec.abr_kbps = 1300;//1300;//user_video_rec_get_abr(req.rec.width);//JPEG图片码率

        memset(req_buf, 0, CAMERA_MAX_JPEG_SIZE);
        req.rec.buf = req_buf;
        req.rec.buf_len = CAMERA_MAX_JPEG_SIZE;
        /* PR_DEBUG("video req.rec.buf : 0x%x", req.rec.buf); */

        drop_jpeg_count = TY_DROP_JPEG_COUNT + 1;

        /* if (video_state == 2 || video_state == 3 || video_state == 4 || video_state == 8) { */

        /* } else { */
#if 0
        /* if (g_video_ctrl.rec_start[id]) { */
        /*
         *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
        */
        memset(req_audio_buf, 0, AUDIO_MAX_SIZE);
        req.rec.audio.sample_rate = 8000;
        req.rec.audio.channel 	= 1;
        req.rec.audio.volume    = 100;
        req.rec.audio.buf = req_audio_buf;//audio_buf[id];
        req.rec.audio.buf_len = AUDIO_MAX_SIZE;
        req.rec.audio.aud_interval_size = 1024;
        /* req.rec. */

        /* req.rec.audio.sample_source = "mic"; */
        //req.rec.audio.sample_source = "user";
        /* req.rec.audio.fmt_format = AUDIO_FMT_PCM; */
        req.rec.pkg_mute.aud_mute = 0;//!db_select("mic");
#if TCFG_HOST_AUDIO_ENABLE
        req.rec.audio.read_input = user_uac_audio_read_input,
                      req.rec.audio.sample_source = "virtual",
#endif
#endif
                                    //数据外引，用于网络
#if 1
                                    req.rec.target = VIDEO_TO_OUT;
        req.rec.out.path = NULL;//req.rec.net_par.netpath;
        req.rec.out.arg  = NULL;
        req.rec.out.open = ty_stream_open;//NULL;//stream_open;
        req.rec.out.send = ty_stream_write;//stream_write;
        req.rec.out.close = ty_stream_close;//NULL;//stream_close;
#endif

#if 0
        req.rec.packet_cb = ty_video_frame_cb;//uvc_jpeg_cb;//注册数据包回调函数进行协议转发

        server_request(video_server[id], VIDEO_REQ_SET_PACKET_CALLBACK, &req);
#endif

        ret = server_request(video_server[id], VIDEO_REQ_REC, &req);
        if (0 == ret) {
            g_video_ctrl.camera_start[id] = TRUE;
            PR_NOTICE("video server open w=%d h=%d f=%d", img_w, img_h, fps);
        } else {
            PR_NOTICE("video server open err ! w=%d h=%d f=%d", img_w, img_h, fps);
            ret = -1;
        }

        tuya_hal_mutex_unlock(g_video_ctrl.mutex);

        return ret;
    } else {
        ret = -1;
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return ret;
    }
}

INT_T  ty_video_stop(INT_T id)
{
    union video_req req = {0};
    PR_DEBUG("into ty video stop");
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);
    if (!g_video_ctrl.camera_start[id]) {
        printf("video%d is not open", id);
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
    if (video_server[id]) {
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(video_server[id], VIDEO_REQ_REC, &req);
        PR_NOTICE("video server stop");
        g_video_ctrl.camera_start[id] = FALSE;
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    } else {
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
}

INT_T  ty_video_close(INT_T id)
{
    union video_req req = {0};
    PR_DEBUG("into ty video stop");
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);
    if (!g_video_ctrl.camera_start[id]) {
        printf("video%d is not open", id);
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
    if (video_server[id]) {
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(video_server[id], VIDEO_REQ_REC, &req);
        PR_NOTICE("video server stop");
        g_video_ctrl.camera_start[id] = FALSE;
        server_close(video_server[id]);
        video_server[id] = NULL;
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    } else {
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
}


void ty_net_video_stop()
{
    for (int i = 0; i < 4; i++) {
        ty_video_stop(i);
    }
}

void ty_net_video_close()
{
    for (int i = 0; i < 4; i++) {
        ty_video_close(i);
    }
}

void video_convert(INT_T flag) //双路摄像头切换
{
    int w, h, r, f;
    int ret;
    ty_get_camera_pic_w_h_r_f(&w, &h, &r, &f);
    PR_DEBUG("video_state:%d, flag:%d", video_state, flag);
    for (int i = 0; i < 4; i++) {
        ty_video_stop(i);
    }
    switch (video_state) {
    case 2: //mipi
        ret = ty_video_start(0, w, h, f);
        break;
    case 3: //dvp
        ret = ty_video_start(1, w, h, f);
        break;
    case 4: //uvc
        ret = ty_video_start(2, w, h, f);
        break;
    case 8: //mipi video3
        ret = ty_video_start(3, w, h, f);
        break;
    case 5: //mipi+dvp
        if (!flag) {
            ret = ty_video_start(0, w, h, f);
            if (ret != 0) {
                ty_video_start(1, w, h, f);
            }
        } else {
            ret = ty_video_start(1, w, h, f);
            if (ret != 0) {
                ty_video_start(0, w, h, f);
            }
        }
        break;
    case 6://mipi+uvc
        if (!flag) {
            ret = ty_video_start(0, w, h, f);
            if (ret != 0) {
                ty_video_start(2, w, h, f);
            }
        } else {
            ret = ty_video_start(2, w, h, f);
            if (ret != 0) {
                ty_video_start(0, w, h, f);
            }
        }
        break;
    case 7: //dvp+uvc
        if (!flag) {
            ret = ty_video_start(1, w, h, f);
            if (ret != 0) {
                ty_video_start(2, w, h, f);
            }
        } else {
            ret = ty_video_start(2, w, h, f);
            if (ret != 0) {
                ty_video_start(1, w, h, f);
            }
        }
        break;
    case 11: //mipi video 3+dvp
        if (!flag) {
            ret = ty_video_start(3, w, h, f);
            if (ret != 0) {
                ty_video_start(1, w, h, f);
            }
        } else {
            ret = ty_video_start(1, w, h, f);
            if (ret != 0) {
                ty_video_start(3, w, h, f);
            }
        }
        break;
    case 12://mipi video3+uvc
        if (!flag) {
            ret = ty_video_start(3, w, h, f);
            if (ret != 0) {
                ty_video_start(2, w, h, f);
            }
        } else {
            ret = ty_video_start(2, w, h, f);
            if (ret != 0) {
                ty_video_start(3, w, h, f);
            }
        }
        break;

    default:
        break;
    }
    return;
}

static int ty_video_take_photo(void)
{
    union video_req req = {0};
    for (int i = 0; i < 4; i++) {
        if (g_video_ctrl.camera_start[i]) {
            PR_DEBUG("video%d is online", i);
            if (i == 0) {
                req.rec.rec_save_path = CAMERA0_CAP_PATH"img_***.jpg";
            } else if (i == 1) {
                req.rec.rec_save_path = CAMERA1_CAP_PATH"img_***.jpg";
            } else if (i == 2) {
                req.rec.rec_save_path = CAMERA1_CAP_PATH"img_***.jpg";
            } else {
                req.rec.rec_save_path = CAMERA2_CAP_PATH"img_***.jpg";
            }
            req.rec.channel = 1;
            /* req.rec.rec_save_path = CAMERA0_CAP_PATH"img_***.jpg"; */
            int ret = server_request(video_server[i], VIDEO_REQ_SAVE_FRAME, &req);

            if (ret != 0) {
                printf("save photo error");
            } else {
                printf("save photo to sd card succ");
            }
            return 0;
        }
    }
}

#if TCFG_HOST_AUDIO_ENABLE

CHAR_T get_audio_id(VOID_T)
{
    return audioid;
}

#endif

BOOL_T get_camera_state()
{
    return g_video_ctrl.camera_open;
}

STATIC VOID_T __video_task(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    TY_VIDEO_CTRL_MSG *msg_data;
    INT_T w, h, r, f;
    int msg[16] = {0,};

    while (1) {
        //阻塞等待消息
        op_ret = os_q_pend(&g_video_ctrl.msg_que, 0, msg);
        if (op_ret != OPRT_OK && msg[0] == NULL) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("WaitMessage op_ret:%d", op_ret);
            }
            continue;
        }
        msg_data = (TY_VIDEO_CTRL_MSG *)msg[0];

        INT_T flag = 0;
        INT_T *p = (INT_T *)(msg_data->data);
        if (p) {
            flag = p[0];
        }
        switch (msg_data->cmd) {
        case MSG_START_VIDEO_SYN:
        case MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS: {
#if 1
            if (!g_video_ctrl.camera_open) {
                if (msg_data->cmd != MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS) {
                    g_video_ctrl.camera_open = true;
                }
                video_flag = 1;
                video_convert(video_flag);
            } else {
                PR_NOTICE("camera already open");
            }

            tuya_hal_semaphore_post((SEM_HANDLE)flag);
            /* PR_NOTICE("uvc_video_satrt os_sem_post"); */
#endif
        }
        break;

        case MSG_STOP_VIDEO_SYN: {
#if 1
            ty_net_video_stop();
            g_video_ctrl.camera_open = false;
            tuya_hal_semaphore_post((SEM_HANDLE)flag);
            //PR_NOTICE("uvc_video_stop os_sem_post");
#endif
        }
        break;
        case MSG_STOP_VIDEO_NEW_SYN: {
#if 1
            VOID_T *sem;
            INT_T *p = (INT_T *)(msg_data->data);
            p++;
            sem = *p;
            if (flag == 1) {
                ty_net_video_stop();
                g_video_ctrl.camera_open = false;
                goto common_deal;
            } else if (flag == 0) {
                if (!g_video_ctrl.camera_open) {
                    ty_net_video_stop();
                    goto common_deal;
                }
                if (ty_get_stream_status()) {
                    goto common_deal;
                }
                ty_net_video_stop();
                g_video_ctrl.camera_open = false;
            }
common_deal:
            tuya_hal_semaphore_post((SEM_HANDLE)sem);
            PR_NOTICE("uvc_video_satrt os_sem_post");
#endif // 0
        }
        break;

        default:
            break;
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


OPERATE_RET cameraPara_init(TY_CAMERA_PARAM *camera_param)
{
//    camera_power_off = camera_param->video_power_off;
//    PR_NOTICE("camera param:%d %d %d %d %d" ,camera_param->video_width,camera_param->video_height,camera_param->video_rotat_angle,camera_param->video_fps,camera_power_off);
    ty_set_camera_pic_w_h_r_f(camera_param->video_width, camera_param->video_height, camera_param->video_rotat_angle, camera_param->video_fps);
    return OPRT_OK;
}

static void video_handler_init(void)
{
    if (!rec_handler) {
        rec_handler  = (struct video_rec_hdl *)get_video_rec_handler();
    }
}

INT_T tuya_video_init(TY_CAMERA_PARAM *camera_param)
{
    TAL_PR_DEBUG("into tuya video init");
    STATIC UCHAR_T init = 0;
    OPERATE_RET op_ret;
    INT_T w, h;

    memset(g_video_ctrl.rec_start, 0, 4);
    memset(g_video_ctrl.camera_start, 0, 4);


    g_video_ctrl.lcd_width = camera_param->video_width;//640;
    g_video_ctrl.lcd_height = camera_param->video_height;//480;

    cameraPara_init(camera_param);
    PR_NOTICE("tuya_video_init get lcd %d %d\n", g_video_ctrl.lcd_width, g_video_ctrl.lcd_height);
    if (NULL == video_server[0] || NULL == video_server[1] || NULL == video_server[2] || NULL == video_server[3]) {

#ifdef CONFIG_VIDEO0_ENABLE
        video_state = video_state + 2;
#endif

#ifdef CONFIG_VIDEO1_ENABLE
        video_state = video_state + 3;
#endif

        /* #ifdef CONFIG_VIDEO2_ENABLE */
        /* video_state = video_state + 4; */
        /* #endif */
#ifdef CONFIG_UVC_VIDEO_ENABLE
        video_state = video_state + 4;
#endif

#ifdef CONFIG_VIDEO3_ENABLE
        video_state = video_state + 8;
#endif
    }
    PR_DEBUG("video_state = %d", video_state);
    video_handler_init();
    if (!init) {
        tuya_hal_semaphore_create_init(&g_video_ctrl.semphore, 0, 1);
        QS queue_size = (SIZEOF(TY_VIDEO_CTRL_MSG *) * 20 + sizeof(WORD) - 1) / sizeof(WORD);
        op_ret = os_q_create(&g_video_ctrl.msg_que, queue_size);

        if (op_ret != OPRT_OK) {
            PR_NOTICE("tal queue creat init error!");
        }
        // video_flag = 0;
        /* video_convert(video_flag); */
        display_convert(0);

        THRD_PARAM_S thrd_param;
        thrd_param.priority = TRD_PRIO_1;
        thrd_param.stackDepth = 1024 * 4;
        thrd_param.thrdname = TY_VIDEO_TASK_NAME;
        CreateAndStart(&g_video_ctrl.task_handle, NULL, NULL, __video_task, NULL, &thrd_param);
        // stream_protocol_task_create();

    }

    init = 1;
    return 0;
}


#if 1
/*UVC插拔的事件总入口*/
static int video_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;
    int err = 0;
    UCHAR_T *type;
    INT_T w, h, r, f;
    if (e->from == DEVICE_EVENT_FROM_SD) {
        switch (event->event) {
        case DEVICE_EVENT_IN:
            printf("sd card in");
            /* ty_rec_switch(); */
            break;
        case DEVICE_EVENT_OUT:
            printf("sd card out");
            /* for (int i = 0; i < 4; i++) { */
            /* ty_rec_stop(i); */
            /* } */
            /* video_convert(video_flag); */
            break;
        }
    }
#ifdef CONFIG_UVC_VIDEO_ENABLE //CONFIG_VIDEO2_ENABLE
    else if (e->from == DEVICE_EVENT_FROM_USB_HOST) {
        type = event->value;
        if (event->event == DEVICE_EVENT_IN) {
            if (!strncmp((const char *)event->value, "uvc", 3)) {
                PR_DEBUG("video_server[2]:%x", video_server[2]);
                display_convert(0);
                /* video_flag = 1; */
                /* video_convert(video_flag); */

                /* printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__); */
            }
#if TCFG_HOST_AUDIO_ENABLE
            if (!strncmp((const char *)event->value, "audio", 5)) {
                audioid = type[5] - '0';
                g_video_ctrl.audio_online = true;
                PR_NOTICE("audio online : %s, id=%d", type, audioid);
            }
#endif
        } else if (event->event == DEVICE_EVENT_OUT) {
            if (!strncmp((const char *)event->value, "uvc", 3)) {
                /* uvc_online_num = 0; */
                display_convert(0);
                /* video_flag = 0; */
                /* video_convert(video_flag); */
                /* printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__); */
            }

        }
    }
#endif

    return 0;
}

/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(ty_device_event, 0) = {
    .event_type     = SYS_DEVICE_EVENT,
    .prob_handler   = video_event_handler,
    .post_handler   = NULL,
};

/*
 *按键响应函数
 */
static int video_key_event_handler(struct sys_event *e)
{
    int err;
    static int flag = 0;
    struct key_event *key = (struct key_event *)e->payload;

    printf("key value:%d ", key->value);
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
            PR_DEBUG("convert video0");
            /* flag = !flag; */
            video_flag = 0;
            video_convert(video_flag);
            break;
        case KEY_MENU:
            break;
        case KEY_POWER:
            /* ty_rec_switch(); */
            /* display_convert(1); */
            break;
        case KEY_MODE:
            /* for (int i = 0; i < 4; i++) { */
            /* ty_rec_stop(i); */
            /* } */
            /* video_convert(video_flag); */
            break;
        case KEY_UP:
            printf("key3 \n\n\n\n");
            ty_video_take_photo();
            break;
        case KEY_DOWN:
            PR_DEBUG("convert video2");
            video_flag = 1;
            video_convert(video_flag);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return false;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(ty_key_event, 0) = {
    .event_type     = SYS_KEY_EVENT,
    .prob_handler   = video_key_event_handler,
    .post_handler   = NULL,
};
#endif

#endif

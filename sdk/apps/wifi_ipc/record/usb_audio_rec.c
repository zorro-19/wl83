#include "system/includes.h"
#include "server/audio_server.h"
#include "server/server_core.h"
#include "server/usb_syn_api.h"
#include "video/video_ioctl.h"
#include "event/device_event.h"
#include "app_config.h"

extern void get_cfg_file_aec_config(struct aec_s_attr *aec_param);

#define LOG_TAG_CONST       USB
#define LOG_TAG             "[USER_USB_AUDIO]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#if TCFG_HOST_AUDIO_ENABLE

#include "host/audio.h"

struct usb_host_spk_handle {
    OS_SEM rd_sem;
    void *play_dev;
    cbuffer_t play_cbuf;
    void *play_buf;
    u8 play_start;
    u8 single_channel_to_double;
    u8 task_id;
};

typedef struct {
    int is_active;           // 数组是否在使用
    int camera_id;           // 对应的摄像头ID
    /* int* audio_buffer;       // 音频数据缓冲区 */
} AudioArray;

static struct usb_host_spk_handle **uac_host_spk_handle;
static u8 online_num;

static OS_MUTEX mutex;
static int init;
AudioArray *audio_arrays;

// 获取音频数组索引
int get_video_num()
{
    return online_num;
}

char *get_audio_array()
{
    return audio_arrays;
}

static int get_array_index(AudioArray *arrays, int camera_id)
{
    // 先查找camera_id是否已经分配了数组
    for (int i = 0; i < online_num; i++) {
        if (arrays[i].is_active && arrays[i].camera_id == camera_id) {
            return i;
        }
    }

    // 如果没有，找一个空闲的位置
    for (int i = 0; i < online_num; i++) {
        if (!arrays[i].is_active) {
            arrays[i].is_active = 1;
            arrays[i].camera_id = camera_id;
            return i;
        }
    }

    return -1; // 没有可用的数组
}


//获取到usb mic的数据
static int usb_host_audio_play_put_buf(const usb_dev usb_id, void *ptr, u32 len, u8 channel, u32 sample_rate)
{

#if 1
    struct usb_host_spk_handle **hdl = uac_host_spk_handle;

    if (channel == 0 && sample_rate == 0) {
        uac_host_spk_handle = NULL;
        return 0;
    }
    if (!init) {
        /* printf("create mutex %s", os_current_task()); */
        os_mutex_create(&mutex);
        init = 1;
    }

    if (!hdl) {
#ifdef CONFIG_TUYA_SDK_ENABLE
        usb_audio_set_cfg(channel, 16, sample_rate);
#endif
        audio_arrays = zalloc(sizeof(AudioArray) * online_num);
        hdl = zalloc(sizeof(struct usb_host_spk_handle *)*online_num);
        uac_host_spk_handle = hdl;

        for (int i = 0; i < online_num; i++) {
            hdl[i] = zalloc(sizeof(struct usb_host_spk_handle));
        }

        int play_buf_size = sample_rate * 4 * channel / 1000 * 10;

        for (int i = 0; i < online_num; i++) {
            if (channel & BIT(7)) {
                channel &= ~BIT(7);
                hdl[i]->single_channel_to_double = 1;
            }
            hdl[i]->play_buf = malloc(play_buf_size);
            if (!hdl[i]->play_buf) {
                return -1;
            }
            cbuf_init(&hdl[i]->play_cbuf, hdl[i]->play_buf, play_buf_size);
        }
    }
    if (hdl && len > 0) {

        for (int i = 0; i < online_num; i++) {
            cbuf_write(&hdl[i]->play_cbuf, ptr, len);
        }
        //req.rec.packet_cb中已经发出去了
        /* #ifdef CONFIG_XCIOT_ENABLE /
        / xc_send_audio(ptr,len); /
        / #endif */

    }
#endif
#ifdef CONFIG_TUYA_SDK_ENABLE
    ty_usb_audio_play_put_buf_net(ptr, len);
#endif
    return len;
}

//传入到video_server封装录像文件
u32 user_uac_audio_read_input(u8 *buf, u32 len)
{

#if 1
    int rlen = 0;

    struct usb_host_spk_handle **hdl = uac_host_spk_handle;


    if (!hdl) {
        return 0;
    }

    if (!init) {
        /* printf("create mutex %s", os_current_task()); */
        os_mutex_create(&mutex);
        init = 1;
    }

    os_mutex_pend(&mutex, 0);

    /* printf(" %s pid:%d", os_current_task(), get_cur_thread_pid()); */
    int id = get_array_index(audio_arrays, get_cur_thread_pid());
    /* printf("id:%d", id); */
    while (!rlen) {
        rlen = cbuf_get_data_size(&hdl[id]->play_cbuf);
        if (!rlen) {
            continue;
        }
    }

    if (hdl[id]->single_channel_to_double) {
        if (rlen > len / 2) {
            rlen = len / 2;
        }
    } else {
        if (rlen > len) {
            rlen = len;
        }
    }
    cbuf_read(&hdl[id]->play_cbuf, buf, rlen);
    os_mutex_post(&mutex);
#endif

    return rlen;
    /* return 0; */
}


static int usb_host_audio_record_get_buf(const usb_dev usb_id, void *ptr, u32 len, u8 channel, u32 sample_rate)
{
#ifdef CONFIG_XCIOT_ENABLE
    xc_talkback_read(ptr, len);
#endif
#ifdef CONFIG_TUYA_SDK_ENABLE
    usb_audio_set_cfg(channel, 16, sample_rate);
    ty_usb_audio_record_get_buf_net(ptr, len);
#endif
    return len;
}

extern int usb_host_audio_record_get_buf_test(const usb_dev usb_id, void *ptr, u32 len, u8 channel, u32 sample_rate);
int usb_host_audio_set_init(u8 num, u8 channel, u32 sample_rate)
{
    /* online_num = num; */
    online_num = 2;

    //默认开启的是fusb接入uac,不支持多个uac接入录像文件
    usb_host_audio_init(0, usb_host_audio_play_put_buf, usb_host_audio_record_get_buf);
    usb_host_audio_init(1, usb_host_audio_play_put_buf, usb_host_audio_record_get_buf);

    return 0;
}

int usb_host_audio_uninit(void)
{
    struct usb_host_spk_handle **hdl = uac_host_spk_handle;
    if (!hdl) {
        return 0;
    }

    for (int i = 0; i < online_num; i++) {
        cbuf_clear(&hdl[i]->play_cbuf);
        free(hdl[i]->play_buf);
        free(hdl[i]);
        hdl[i] = NULL;
    }
}
late_initcall(usb_host_audio_set_init);

#endif

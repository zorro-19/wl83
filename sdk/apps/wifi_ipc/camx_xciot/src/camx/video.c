#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rt_stream_pkg.h"
#include "action.h"
#include "app_config.h"
#include "system/includes.h"
#include "event/event.h"
#include "event/device_event.h"


#include "xciot_api.h"

#ifdef CONFIG_XCIOT_ENABLE
#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "video.c"
#include "xc_log.h"



int isCS = 0;
cs_hdl_ref_t cs_hdl = NULL;


uint64_t hal_get_utc(void)
{
    return osal_clock_utctime();
}

void dev_cs_video_end(void)
{

    /*结束云存储*/
    if (cs_hdl) {
        isCS = 0;
        int rc = avsdk_cs_end(&cs_hdl, NULL);

        T_I("cloud_storage_end , rc = %d\r\n", rc);
    }
}

int dev_cs_video_start(int event_id, uint8_t *thum_data, uint32_t thum_len)
{
    int64_t ret = 0;
    int rc = 0;
    int64_t start_time = 0;
    avsdk_cs_set_log_level(LOG_LEVEL_INFO);

    iot_event_opt_t event = {
        .channel = 0,
        .id = event_id,
        .value = 0,
        .utc_ms = 0,
        .isCS = true
    };
    ret = avsdk_push_event(&event);
    T_I("----->start_time2222=%ld\r\n", ret);

    if (ret < 0) {
        //事件上报失败
        return -1;
    } else if (ret == 0) {
        //事件上报成功，但是设备没开通云存
        return 0;
    } else {
        //只要返回值大于0，才给start_time赋值
        start_time = ret;
    }

    T_D("test cloud storage write start:%llu", start_time);

    cs_start_opt_t opt = {
        .event_id = event_id,
        .start_timems = start_time,
        .channel = 0,
        .memsize = 40 * 1024,
        .upload_way = e_cs_upload_way_memory,
        .file_name = "./cloud_file",
        .nocache = 1,
    };

    /*开始云储存*/
    rc = avsdk_cs_start(&cs_hdl, &opt);
    if (rc) {
        T_E("avsdk_cs_start, rc=%d", rc);
        return rc;
    }


    /*设置音视频格式*/
    {
        struct coord xy = {0};
        xy.isHaveCoord = false;
        uint8_t picture_num = 1;
        uint8_t fps = 10;
        avsdk_cs_set_format_v2(cs_hdl,
                               e_cs_encrypt_none, //e_cs_encrypt_aes_256_cbc,
                               e_cs_stream_mjpeg,             //视频格式
                               fps,
                               e_cs_stream_pcm,              //音频格式
                               e_cs_sound_frequeency_8k,  //声音采样频率
                               e_cs_sound_depth_16bit,        //声音采样深度
                               e_cs_sound_channel_mono,      //声音声道
                               picture_num,                  //图片数量；0没有缩略图
                               e_cs_picture_type_thumb);     //图片质量
    }

    /*追加缩略图*/
    {
        rc = avsdk_cs_append_thumbnail_v2(cs_hdl,
                                          thum_data,  //缩略图的内容
                                          thum_len,   //内容的长度
                                          NULL);

        T_I("thumbnail size = %d, rc=%d", thum_len, rc);
    }

    if (rc) {
        dev_cs_video_end();
    }
    return rc;
}

int dev_cs_get_diff_time(bool reset)
{
    static uint64_t utcms_start = 0;
    int diff_time = 0;

    if (reset == true) {
        utcms_start = hal_get_utc();
    }

    diff_time = (int)(hal_get_utc() - utcms_start);
    return diff_time;
}

int dev_cs_video_append(uint8_t *p, uint32_t len)
{
    int rc = 0;
    /* printf("dev_cs_video_append  len:%d\n", len); */
    rc = avsdk_cs_append_video_v2(cs_hdl,
                                  0,
                                  true,              // 是不是关键帧
                                  e_cs_frame_none,   // @e_frame_features
                                  dev_cs_get_diff_time(false),         // 相对于开始的时间戳ms
                                  NULL,
                                  p,                 // 视频内容
                                  len);              // 视频内容长度
    return rc;
}

int dev_cs_audio_append(uint8_t *p, uint32_t len)
{
    int rc = 0;
    if (cs_hdl) {
        /* printf("dev_cs_audio_append  len:%d\n", len); */
        rc = avsdk_cs_append_audio_v2(cs_hdl,
                                      0,
                                      e_cs_frame_none,   // @e_frame_features
                                      dev_cs_get_diff_time(false),         // 相对于开始的时间戳ms
                                      p,                 // 视频内容
                                      len);              // 视频内容长度
    }
    return rc;
}

int test_cs_pulish_video(int event_id, uint8_t *p, int len)
{
    //return 0,表示云录结束; -5表示还没录够
    int rc = -5;
    int min_index = 10; //最少录制帧数
    int min_record_time = 10000;//ms，最少录制时长
    static int index = 0;
    if (!isCS) {
        return 0;
    }

    int diff_time = 0;

    if (index == 0 && cs_hdl == NULL) {
        dev_cs_video_start(event_id, p, len); //E_IOT_EVENT_MOTION_DETECTION
        dev_cs_get_diff_time(true);
    }

    if (cs_hdl) {
        if (dev_cs_video_append(p, len) != -6) {
            index++;
        }

    }


    diff_time = dev_cs_get_diff_time(false);
    /*每次云存最少录30帧，时长最少8s*/
    if (index > min_index && diff_time > min_record_time) {
        T_I("min_index=%d, index=%d,diff_time=%d, min_record_time=%d", min_index, index, diff_time, min_record_time);
        dev_cs_video_end();
        index = 0;
        rc = 0;
    }

    return rc;
}


int test_cs_pulish_picture(int event_id, uint8_t *p, int len)
{
    int rc = 0;
    T_I("------test_cs_pulish_picture start-------\r\n");

    ipc_picture_t picture = {0};
    picture.count = 1;
    picture.data[0].p = p;//图片数据
    picture.data[0].len = len; //图片数据长度


    avsdk_cs_set_picture_maxsize(len + 1024);
    rc = avsdk_cs_picture_pulish_v2(event_id,
                                    0,
                                    0,
                                    &picture,
                                    NULL);
    T_I("------test_cs_pulish_picture end-------\r\n");
    return rc;
}

#define JL_ENDF         ntohl(0x56185719)
int xc_send_video(uint8_t *data, int len)
{
    int rc = 0;
    static uint64_t msec = 0;
    uint64_t time = osal_clock_utctime();

    u32 *head = (u32 *)data;
    if ((len <= 8) && (*head == JL_ENDF)) {
        return len;
    }

    static int max_size = 0;
    if (len > max_size) {
        max_size = len;
    }

    if (isCS == 1) {
        cs_service_type_t cs_type = avsdk_cs_get_service_type();
        if (cs_type == E_CS_SERVICE_PICTURE) {
            //云存图片
            rc = test_cs_pulish_picture(E_IOT_EVENT_MOTION_DETECTION, data, len);
        } else if (cs_type == E_CS_SERVICE_VIDEO) {
            //云存视频
            rc = test_cs_pulish_video(E_IOT_EVENT_MOTION_DETECTION, data, len);
        } else {
            //未开通任何服务，只报事件
            iot_event_opt_t event = {
                .channel = 0,
                .id = E_IOT_EVENT_MOTION_DETECTION,
                .value = 0,
                .utc_ms = 0,
                .isCS = true
            };
            rc = avsdk_push_event(&event);
        }

        if (!rc) {
            //云存结束
            struct device_event e = {0};
            e.arg = "mot_event";
            e.value = 0;
            e.event = DEVICE_EVENT_CHANGE;
            device_event_notify(DEVICE_EVENT_FROM_VIDEO, &e);


        }

    }

    /* printf("video time :%ld\n",time); */
    avsdk_write_video_data(E_IOT_MEDIASTREAM_TYPE_MJPEG,
                           1,
                           (uint64_t)0,
                           E_IOT_ENCRYPT_TYPE_NONE,
                           time,
                           0, NULL, 0, data, len);

    return len;
}

int xc_send_audio(uint8_t *data, int len)
{

    int rc = 0;
    static uint64_t msec = 0;
    uint64_t time = osal_clock_utctime();
    /* static int index = 0; */

    /* index++; */
    /* if (msec < time) { */
    /* int fps = index / 3.0; */
    /* T_I("audio:len=%d, sec=%lld, fps=%d", len, time, fps); */
    /* msec = time + 2000; */
    /* index = 0; */
    /* } */

    /*云存音频*/
    dev_cs_audio_append(data, len);

    /*实时音频*/
    /* printf("audio time %ld\n",time); */
    avsdk_write_audio_data(E_IOT_MEDIASTREAM_TYPE_PCM,
                           (uint64_t)0,
                           E_IOT_ENCRYPT_TYPE_NONE,
                           time,
                           0,
                           NULL,
                           0,
                           data,
                           len);



    return 0;
}



/* unsigned char MICO_CTL = 0; */
/* extern unsigned char MICO_CTL; */
/* static u32 time1=0,time2=0; */
/* static u32 time3=0,time4=0; */
u32 xc_video_frame_callback(u8 type, void *data, u32 len)
{
    //T_I("------------------>,type=%d,len=%d\n", type, len);
    if (type == JPEG_TYPE_VIDEO) { //jpeg视频
        /* printf("V, len=%d\n", len); */
        xc_send_video(data, len);
        /* time1 = timer_get_ms(); */
        /* printf("video=%dms\n",time1-time2); */
        /* time2 = time1; */

    } else if (type == PCM_TYPE_AUDIO) { //PCM音频

        /* time3 = timer_get_ms(); */
        /* printf("audio=%dms\n",time3-time4); */
        /* time4 = time3; */

        /* printf(">A,len=%d\n", len); */
        /* if (!MICO_CTL) { */
        xc_send_audio(data, len);
        /* } */
        /*put_buf(data, len);*/
    }
    return 0;
}


void cloud_storage_cs(void)
{
    struct device_event e = {0};

    time_t timep;

    extern int32_t get_time_offset(void);
    int32_t temp = get_time_offset();

    /* timep += (temp * 60); */
    timep += temp;
    printf("timep =======%d\n", timep);
    if (is_need_mov_detecte(timep)) {

        T_I("start cloud storage cs!");

        e.arg = "mot_event";
        e.value = 1;
        e.event = DEVICE_EVENT_CHANGE;
        device_event_notify(DEVICE_EVENT_FROM_VIDEO, &e);
    } else {
        T_I("------------ cloud storage cs but not in time!");
    }




}


#if 1
/*
 * 智能事件处理
 */
static void ai_event_handler(struct device_event *event)
{

    extern int IOT_CONNECT_FLAG;

    switch (event->event) {
    case DEVICE_EVENT_CHANGE:
        if (event->value) {
            T_I("dur cloud storage");
            printf("isCS ===%d\n", isCS);
            if (!isCS) {
                //todo yhh
                /* motion_detection_uninit(); */
#if 0
                struct intent it;
                init_intent(&it);
                it.name	= "video_rec";//APP状态机在：video_rec.c
                it.action = ACTION_VIDEO_REC_MAIN;
                start_app(&it);
#endif

                void **user_video_handle = get_user_video_handle();
                *user_video_handle = user_video_rec_open(TCFG_USER_VIDEO_SOURCE);


                isCS = 1;

            }
        } else {

#if 0
            struct intent it;
            init_intent(&it);
            it.name	= "video_rec";//APP状态机在：video_rec.c
            it.action = ACTION_BACK;
            start_app(&it);
#endif

            isCS = 0;

            void **user_video_handle = get_user_video_handle();
            if (*user_video_handle) {
                user_video_rec_close(*user_video_handle);
                *user_video_handle = NULL;
            }
            //todo
            /* motion_detection_init(); */
        }


        break;
    }
}




static int device_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;

    if (e->from == DEVICE_EVENT_FROM_VIDEO) {
        if (!strcmp(event->arg, "mot_event")) {
            ai_event_handler(event);
        }
    }

    return 0;
}
/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(device_event3, 0) = {
    .event_type     = SYS_DEVICE_EVENT,
    .prob_handler   = device_event_handler,
    .post_handler   = NULL,
};

#endif














#endif


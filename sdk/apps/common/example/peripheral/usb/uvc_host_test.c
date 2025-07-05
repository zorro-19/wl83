
#include "device/device.h"
#include "os/os_api.h"
#include "generic/lbuf.h"
#include "yuv_soft_scalling.h"
#include "yuv_to_rgb.h"
#include "get_yuv_data.h"
#include "system/sys_time.h"
#include "system/init.h"
#include "event/device_event.h"
#include "asm/uvc_device.h"
#include "fs/fs.h"
#include "app_config.h"
#include "uvc_test_data.h"

#if TCFG_HOST_UVC_ENABLE
/* #if 1 */

#define UVC_TEST_BUF_SIZE  (1 * 1024 * 1024)
/* #define UVC_TEST_BUF_SIZE  (3 * 1024 * 1024) */

struct uvc_cam_test_t {
    volatile u8 streamon;
    u16 cur_width;
    u16 cur_height;
    u32 frame_cnt;
    struct video_format f;
    struct video_var_param_info info;
};
struct uvc_cam_test_t _uvc_cam_test = {0};

#define __this   (&_uvc_cam_test)

static u8 buf_test[3072];
static void uvc_test_recv_task(void *arg)
{
    void *fd = NULL;
    struct uvc_reqbufs breq = {0};
    struct video_buffer b = {0};
    struct uvc_capability uvc_cap;
    int err = -1;
    int msg[32];
    u8 i = 0;

    fd = dev_open("uvc", (void *)&__this->info); //指定uvc设备
    if (fd) {
        dev_ioctl(fd, UVCIOC_QUERYCAP, (unsigned int)&uvc_cap);
        for (i = 0; i < uvc_cap.reso_num; i++) {
            printf("reso[%d] w:%d h=%d\n", i, uvc_cap.reso[i].width, uvc_cap.reso[i].height);
            if (__this->cur_width == uvc_cap.reso[i].width && __this->cur_height == uvc_cap.reso[i].height) {
                break;
            }
        }
        if (i == uvc_cap.reso_num) {
            log_w("can not find reso,please check!!\n");
            i = 0; //传入的分辨率非法时,默认输出第一个分辨率
        }
        dev_ioctl(fd, UVCIOC_SET_CAP_SIZE, (unsigned int)i + 1);
        breq.buf = NULL;
        breq.size = UVC_TEST_BUF_SIZE;

        printf("set uvc video buf\n");
        err = dev_ioctl(fd, UVCIOC_REQBUFS, (unsigned int)&breq);
        if (!err) {
            dev_ioctl(fd, UVCIOC_STREAM_ON, 0);
        } else {
            err = -1;
            puts("uvc1 video open err1--------------------\n");
        }
    }

    /* FILE *f = fopen(CONFIG_ROOT_PATH"test***.264", "w+"); */
    /* if (!f) { */
    /* log_e("fopen faild\n"); */
    /* } */
    while (1) {
        os_taskq_accept(ARRAY_SIZE(msg), msg);
        if (msg[0] == Q_MSG) {
            if (msg[1] == 0xaa) {
                if (os_task_del_req(OS_TASK_SELF) == OS_TASK_DEL_REQ) {
                    //准备退出线程
                    if (fd) {
                        dev_ioctl(fd, UVCIOC_STREAM_OFF, 0);
                        dev_close(fd);
                    }
                    /* if (f) { */
                    /* fclose(f); */
                    /* } */
                    log_d("del test task del self\n");
                    os_task_del_res(OS_TASK_SELF);
                }
            }
        }
        //从uvc 缓存中请求一帧H264图像
        if (fd) {
            err = dev_ioctl(fd, UVCIOC_DQBUF, (unsigned int)&b);
        }
        if (err || b.len <= 0) { //请求失败
            os_time_dly(1);
            continue;
        }
        //请求成功
        //TODO
        /* putchar('R'); */

        if (memcmp(jpeg_data, b.baddr, b.len) == 0) {
            putchar('y');
        } else {

            putchar('n');
        }
        /* put_buf(buf_test,b.len); */
        /* } */
        dev_ioctl(fd, UVCIOC_QBUF, (unsigned int)&b);
    }
}

int video2_uvc_test_stream_open(u16 width, u16 height)
{
    printf("video2_uvc_test_stream_open\n");
    if (__this->streamon) {
        return -1;
    }
    memset(__this, 0x00, sizeof(struct uvc_cam_test_t));
    __this->cur_width = width;
    __this->cur_height = height;
    __this->streamon = 1;
    __this->frame_cnt = 0;

    __this->f.uvc_id = 1;
    __this->f.pixelformat  = VIDEO_PIX_FMT_H264 | VIDEO_PIX_FMT_YUV420;
    __this->info.width = width;
    __this->info.height = height;
    __this->info.f = &__this->f;
    return os_task_create(uvc_test_recv_task, NULL, 20, 1024, 32, "uvc_test_recv");
}

int video2_uvc_test_stream_close()
{
    while (OS_TASK_NOT_EXIST != os_task_del_req((const char *)"uvc_test_recv")) {
        os_taskq_post_msg((const char *)"uvc_test_recv", 1,  0xaa);
        os_time_dly(1);
    }
    __this->streamon = 0;

    return 0;
}

static int device_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;
    int err = 0;

    if (e->from == DEVICE_EVENT_FROM_USB_HOST) {
        if (event->event == DEVICE_EVENT_IN) {
            if (!strncmp((const char *)event->value, "uvc", 3)) {
                video2_uvc_test_stream_open(640, 480);
                printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
                /* 初始化usb ep */
            }
        }
    }

    return 0;
}
/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(uvc_test_device_event, 0) = {
    .event_type     = SYS_DEVICE_EVENT,
    .prob_handler   = device_event_handler,
    .post_handler   = NULL,
};

#endif

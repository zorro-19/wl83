
#include "system/includes.h"
#include "os/os_api.h"
#include "app_config.h"
#include "get_yuv_data.h"
#include "asm/isc.h"
#include "video_ioctl.h"
#include "device.h"
#include "video.h"

static get_yuv_cfg  __info;

void get_qr_yuv_task(void *priv)
{
    int ret;
    void *video_dev_fd = NULL, *fb5 = NULL;
    struct fb_map_user map1;

    //数据来源video，输出到fb2
    struct video_format f = {0};
    struct fb_var_screeninfo fb2_info = {0};
    const char *dev_name = YUV_DATA_SOURCE;
    const char *fb_name = "fb5";//fb5 之后不是合成
    f.type  = VIDEO_BUF_TYPE_VIDEO_OVERLAY;
    f.win.left = 0;
    f.win.top    = 0;
    f.win.width  = YUV_DATA_WIDTH;
    f.win.height = YUV_DATA_HEIGHT;
    f.win.border_left   = 0;
    f.win.border_top    = 0;
    f.win.border_right  = 0;
    f.win.border_bottom = 0;
    f.pixelformat = VIDEO_PIX_FMT_YUV420;
    f.private_data   = fb_name;
#ifdef CONFIG_VIDEO2_ENABLE
    f.uvc_id   = uvc_host_online();
#endif

    video_dev_fd = dev_open(dev_name, NULL);
    if (video_dev_fd == NULL) {
        printf("%s test open device %s faild\n", fb_name, dev_name);
        return;
    }

    ret = dev_ioctl(video_dev_fd, VIDIOC_SET_FMT, (u32)&f);
    if (ret) {
        printf("VIDIOC_SET_FMT faild\n");
        dev_close(video_dev_fd);
        return;
    }

    ret = dev_ioctl(video_dev_fd, VIDIOC_OVERLAY, 1);
    if (ret) {
        printf("VIDIOC_OVERLAY faild\n");
        dev_close(video_dev_fd);
        return;
    }

    //打开显示通道
    fb5 = dev_open(f.private_data, (void *)FB_COLOR_FORMAT_YUV422);
    if (!fb5) {
        printf(" ||| %s ,,, %d \r\n", __FUNCTION__, __LINE__);
        dev_close(video_dev_fd);
        return;
    }

    int count = 0;
    while (1) {

        if (__info.exit_state) {
            break;
        }

        dev_ioctl(fb5, FBIOGET_FBUFFER_INUSED, (int)&map1);
        if ((u32)map1.baddr) {

            //需要使用YUV数据的任务的回调
            if (__info.cb) {
                __info.cb(map1.baddr);
            }
            //获取到才释放
            dev_ioctl(fb5, FBIOPUT_FBUFFER_INUSED, (int)&map1);

        } else {
            //获取不到重试
            continue;
        }

    }

    dev_close(fb5);
    dev_ioctl(video_dev_fd, VIDIOC_OVERLAY, 0);
    dev_close(video_dev_fd);
    printf("get_yuv_task exit\n\n ");

}

void get_qr_yuv_init(void (*cb)(u8 *data))
{
    if (__info.init) {
        return;
    }
    __info.cb = cb;
    __info.init = 1;
    __info.exit_state = 0;
    thread_fork("GET_QR_YUV_TASK", 10, 0x4000, 0, &__info.pid, get_qr_yuv_task, NULL);
}
void get_qr_yuv_uninit(void)
{
    if (!__info.init) {
        return;
    }

    __info.exit_state = 1;
    thread_kill(&__info.pid, KILL_WAIT);
    __info.cb = NULL;
    __info.exit_state = 0;
    __info.init = 0;
}
/* late_initcall(get_qr_yuv_init); */

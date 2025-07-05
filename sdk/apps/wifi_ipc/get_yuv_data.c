
#include "system/includes.h"
#include "os/os_api.h"
#include "app_config.h"
#include "get_yuv_data.h"
#include "asm/isc.h"
#include "video_ioctl.h"
#include "device.h"
#include "video.h"
#include "md.h"


/* #ifdef CONFIG_VIDEO_ENABLE */

#define YUV_BLOCK_SCAN	1

#define ISC_YUV_LINE_	    32
#define ISC_YUV_DATA_WIDTH  640

#if YUV_BLOCK_SCAN
/* static u8 isc_buf[ISC_YUV_DATA_WIDTH * ISC_YUV_LINE_ * 3 / 2] SEC_USED(.sram) ALIGNE(32); */
static u8 *isc_buf = NULL;//[ISC_YUV_DATA_WIDTH * ISC_YUV_LINE_ * 3 / 2] ALIGNE(32);
#endif

//光流的Y
#define YUV_TEST_WIDTH  640
#define YUV_TEST_HEIGHT	480

/* static u8 yuv_buf[YUV_TEST_WIDTH * YUV_TEST_HEIGHT] = {0}; */

static void (*cb)(u8 *data, u32 len, int width, int height, u16 line);

struct yuv_app_info {
    volatile u8 *base;
    volatile u8 *y;
    volatile u8 yuv_used;
    volatile u16 w;
    volatile u16 h;
    volatile u16 line;
};

static struct yuv_app_info yuv_app = {0};

static get_yuv_cfg  __info;

#if 0
u8 *video1_get_buf(void)
{
    return YUV_BLOCK_SCAN ? isc_buf : NULL;
}
int video1_get_buf_size(void)
{
    return YUV_BLOCK_SCAN ? sizeof(isc_buf) : 0;
}

#endif
u8 *yuv420_block_buf_get(int *size)
{
    if (yuv_app.yuv_used) {
        *size = yuv_app.w * yuv_app.h;
        return yuv_app.base;
    } else {
        return NULL;
    }
}
void yuv420_block_buf_clean(void)
{
    yuv_app.yuv_used = 0;
}
int yuv420_block_scan(void *info) SEC_USED(.volatile_ram_code)
{
    int i, j, k;
    struct yuv_block_info *yuv_info = (struct yuv_block_info *)info;
    /*
     *算法处理，禁止加延时函数！
     */
    if (!yuv_app.base) {
        yuv_app.base = isc_buf;
        yuv_app.y = yuv_app.base;
        yuv_app.w = YUV_TEST_WIDTH;
        yuv_app.h = YUV_TEST_HEIGHT;
        yuv_app.line = 0;
    }
    if (yuv_app.yuv_used) {
        return 0;
    }
    if (yuv_info->start && yuv_app.line < yuv_app.h) { //根据传入的Y进行裁剪
        for (j = 0, k = 0; j < yuv_info->line && k < yuv_info->line; yuv_app.line++) {
            k = (++j);
        }
        if (cb) {
            cb(yuv_app.y, YUV_DATA_WIDTH * ISC_YUV_LINE_ * 3 / 4, YUV_DATA_WIDTH, ISC_YUV_LINE_ / 2, yuv_app.line);
        }
    } else if (!yuv_info->start) {
        yuv_app.line = 0;
        yuv_app.yuv_used = true;
        __asm_csync();
    }


    return 0;
}

static void get_yuv_task(void *priv)
{
    int err;
    struct video_format f = {0};
    struct yuv_image yuv = {0};
    void *dev;
    /*
     *step 1
     */
    dev = dev_open(YUV_DATA_SOURCE, NULL);
    if (!dev) {
        printf("open video err !!!!\n\n");
        return;
    }

    /********************YUV支持外部静态BUF,上层处理时间较短************************/
    /*
     *step 2
     */
    f.type = VIDEO_BUF_TYPE_VIDEO_OVERLAY;
    f.pixelformat = VIDEO_PIX_FMT_YUV420;
    f.static_buf = (u8 *)isc_buf;
    f.sbuf_size = ISC_YUV_DATA_WIDTH * ISC_YUV_LINE_ * 3 / 2;//sizeof(isc_buf);
#if YUV_BLOCK_SCAN
    f.block_done_cb = yuv420_block_scan;
#endif
    err = dev_ioctl(dev, VIDIOC_SET_FMT, (u32)&f);
    if (err) {
        goto error;
    }

    //BUFF配置2：使用内部BUFF，内存节省450K,上层处理时间最大为摄像头的帧结束到帧起始时间，需要看摄像头帧同步信号波形测量，GC0308默认驱动处理最大时间16ms
    err = dev_ioctl(dev, VIDIOC_SET_OVERLAY, (u32)0);
    if (err) {
        goto error;
    }

    cb = __info.cb;
    while (1) {
        if (thread_kill_req()) {
            break;
        }

        /*
         *step 4
         */
        err = dev_ioctl(dev, VIDIOC_GET_OVERLAY, (u32)&yuv);
        if (!err) {
            //do something in this step
#if YUV_BLOCK_SCAN
            int len;
            u8 *buf = yuv420_block_buf_get(&len);
            if (buf) {
                //putchar('R');
                yuv420_block_buf_clean();
            }
#else
#endif
        }
        /*
         *step 5
         */
        dev_ioctl(dev, VIDIOC_CLEAR_OVERLAY, 0);
    }
error:
    /*
     *step 6
     */
    dev_close(dev);
}

void get_yuv_init(void (*cb)(u8 *data, u32 len, int width, int height, u16 line))
{
    if (__info.init) {
        return;
    }
    __info.init = 1;
    __info.cb = cb;
    thread_fork("GET_YUV_TASK", 30, 1024, 0, &__info.pid, get_yuv_task, NULL);
}

void get_yuv_uninit(void)
{
    if (!__info.init) {
        return;
    }
    __info.cb = NULL;
    thread_kill(&__info.pid, KILL_WAIT);
    __info.init = 0;
}

void set_get_yuv_data_cb(void (*cb)(u8 *data, u32 len, int width, int height))
{
    __info.cb = cb;
}


int first_start = 1;
int time_level_flag = 0;
int count = 0;

#if 0
int row_num = 0;
static void mot_data_check()
{
    printf("first_start:%d count:%d row_num:%d\n", first_start, count, row_num);
}
#endif

void yuv_cb(u8 *data, u32 len, int width, int height, u16 line)
{
    int i, num;
    int row_num = line / 16 - 1;
    /*row_num = line / 16 - 1;*/
    if (!__info.init) {
        return;
    }


    if (first_start) {
        line_downsample_init(data, row_num);
        if (row_num == 29) {

            first_start = 0;
        }
    } else {

        line_downsample_process(data, row_num);
    }


    if (first_start == 0 && row_num == 29) {
        object_info_t *obj = malloc(sizeof(object_info_t) * 16);
        if (!obj) {
            printf("md process malloc fail\n");
            return;
        }
        num = md_process(NULL, obj);
        if (num > 1) {
            printf("num = %d\n", num);
        }
        if (num >= 2 && count >= 20 && time_level_flag == 1) {
            cloud_storage_cs();
            time_level_flag = 0;
        }
        count++;

        free(obj);
    }
}

static int id = 0;

static void get_time_level()
{
    time_level_flag = 1;
}
void motion_detection_init(void)
{
ag:
    if (!isc_buf) {
        isc_buf = malloc(ISC_YUV_DATA_WIDTH * ISC_YUV_LINE_ * 3 / 2);
        if (!isc_buf) {

            printf("yuv buf malloc again");
            os_time_dly(50);
            goto ag;
        }
    }
    first_start = 1;
    count  = 0;

    //id = sys_timer_add_to_task("sys_timer", NULL, mot_data_check, 3000);
    /* id = sys_timer_add_to_task("sys_timer", NULL, get_time_level, (db_select("time_level")*1000)); */

    md_init(64, db_select("motion"), 1, 12, 0, NULL);
    get_yuv_init(yuv_cb);
    id = sys_timer_add_to_task("sys_timer", NULL, get_time_level, (db_select("time_level") * 1000));
}

void motion_detection_uninit(void)
{
    get_yuv_uninit();
    md_deinit();
    //sys_timer_del(id);
    sys_timer_del(id);
    time_level_flag = 0;
    if (isc_buf) {
        free(isc_buf);
        isc_buf = NULL;
    }
}









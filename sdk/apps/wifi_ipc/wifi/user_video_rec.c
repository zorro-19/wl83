#include "system/includes.h"
#include "server/video_server.h"
#include "app_config.h"
#include "asm/debug.h"
#include "asm/osd.h"
#include "asm/isc.h"
#include "app_database.h"
#include "storage_device.h"
#include "server/ctp_server.h"
#include "os/os_api.h"
#include "camera.h"
#include "net_server.h"
#include "server/net_server.h"
#include "stream_protocol.h"

#ifdef PRODUCT_TEST_ENABLE
#include "product_main.h"
#endif

#ifdef CONFIG_USR_VIDEO_ENABLE

struct user_video_hdl {
    u8 state;
    u8 page_turning;
    u8 req_send;
    u8 *user_isc_buf;
    u8 *user_video_buf;
    u8 *user_audio_buf;
    struct server *user_video_rec;
};

static struct user_video_hdl user_handler = {0};
#define __this_user  (&user_handler)

#ifdef CONFIG_VIDEO_720P
#define USER_ISC_SBUF_SIZE     		(CONFIG_VIDEO_IMAGE_W*64*3/2)
#define USER_VIDEO_SBUF_SIZE   		(200 * 1024)
#define CAP_IMG_SIZE 				(150*1024)
#define CONFIG_USER_VIDEO_WIDTH		1280
#define CONFIG_USER_VIDEO_HEIGHT	720
#else
#define USER_ISC_SBUF_SIZE     		(CONFIG_VIDEO_IMAGE_W*32*3/2)
#define USER_VIDEO_SBUF_SIZE   		(300 * 1024)
#define CAP_IMG_SIZE 				(40*1024)
#define CONFIG_USER_VIDEO_WIDTH		640
#define CONFIG_USER_VIDEO_HEIGHT	480
#endif

#define USER_ISC_STATIC_BUFF_ENABLE	0	//1使用静态内部ram

#if USER_ISC_STATIC_BUFF_ENABLE
extern u8 net_isc_sbuf[USER_ISC_SBUF_SIZE];
static u8 *user_isc_sbuf = net_isc_sbuf;
/*static u8 user_isc_sbuf[USER_ISC_SBUF_SIZE] SEC(.sram) ALIGNE(32);//必须32对齐*/
#endif
#endif

static const unsigned char user_osd_format_buf[] = "yyyy-nn-dd hh:mm:ss";

/*码率控制，根据具体分辨率设置*/
int user_video_rec_get_abr(u32 width)
{
    if (width <= 640) {
        return 1800;
    } else {
        return 2000;
    }
}

int user_video_rec_take_photo(void)
{
#ifdef CONFIG_USR_VIDEO_ENABLE
#define USER_IMAGE_SAVE_BUFF 	1
    struct server *server = NULL;
    union video_req req = {0};
    char *path;
    char buf[48];
    char name_buf[20];
    int *image_len_addr;
    int image_len;
    u8 *image_addr;
    int err;

    server = __this_user->user_video_rec;
    if (!server) {
        server = server_open("video_server", "video0.2");
        if (!server) {
            puts("user_video_rec_take_photo err !!!\n");
            goto error;
        }
    }

    req.icap.quality = VIDEO_MID_Q;
    req.icap.buf_size = CAP_IMG_SIZE;
    req.icap.buf = malloc(CAP_IMG_SIZE);
    if (!req.icap.buf) {
        goto error;
    }
    req.rec.text_osd = NULL;
    req.rec.graph_osd = NULL;
    req.icap.text_label = NULL;
    req.icap.file_name = name_buf;
#if !USER_IMAGE_SAVE_BUFF
    req.icap.path = CAMERA0_CAP_PATH"IMG_****.jpg";
    path = CAMERA0_CAP_PATH;
#endif

#if USER_IMAGE_SAVE_BUFF
    req.icap.save_cap_buf = TRUE;//保存到cap_buff写TRUE，数据格式，前4字节为数据长度，4字节后为有效数据
#endif

    err = server_request(server, VIDEO_REQ_IMAGE_CAPTURE, &req);
    if (err != 0) {
        puts("user_video_rec_take_photo err !!!\n");
        goto error;
    }
#if USER_IMAGE_SAVE_BUFF
    image_addr =  req.icap.buf + 4;
    image_len_addr = (int *)req.icap.buf;
    image_len = *image_len_addr;
    printf("image_len = %d\n", image_len);
    //JPG使用地址：image_addr，使用长度：image_len
    //在这里获取图片数据

    /*put_buf(image_addr,image_len);*/
#else
    sprintf(buf, "%s%s", path, req.icap.file_name);
    printf("%s\n\n", buf);
#endif

    if (req.icap.buf) {
        free(req.icap.buf);
    }
    if (server && server != __this_user->user_video_rec) {
        server_close(server);
    }
    return 0;

error:
    if (req.icap.buf) {
        free(req.icap.buf);
    }
    if (server && server != __this_user->user_video_rec) {
        server_close(server);
    }
#endif
    return -EINVAL;
}

static void *xopen(const char *path, void *arg)
{
    log_d("\n\n\nxopen\n\n");

    return 1;

}

static int xsend(void *fd, char *data, int len, unsigned int flag)
{
    printf("flag:%d  len:%d\n", flag, len);
    return len;
}

static void xclose(void *fd)
{
    log_d("\n\n\nxclose\n\n\n");
}




int user_video_rec0_open(void)
{
    int err = 0;
#ifdef CONFIG_USR_VIDEO_ENABLE
    union video_req req = {0};
    char path[48];

    if (__this_user->state) {
        printf("user already open \n");
        return 0;
    }
    if (!__this_user->user_video_buf) {
        __this_user->user_video_buf = malloc(USER_VIDEO_SBUF_SIZE);
        if (!__this_user->user_video_buf) {
            puts("no mem \n");
            return -1;
        }
    }
#if USER_ISC_STATIC_BUFF_ENABLE
    __this_user->user_isc_buf = user_isc_sbuf;
#else
    if (!__this_user->user_isc_buf) {
        __this_user->user_isc_buf = malloc(USER_ISC_SBUF_SIZE);
        if (!__this_user->user_isc_buf) {
            puts("no mem \n");
            goto __exit;
        }
    }
#endif

    if (!__this_user->user_video_rec) {

#if   defined CONFIG_VIDEO0_ENABLE
        __this_user->user_video_rec = server_open("video_server", "video0.1");
#elif defined CONFIG_VIDEO1_ENABLE
        __this_user->user_video_rec = server_open("video_server", "video1.1");
#elif defined CONFIG_VIDEO2_ENABLE
        __this_user->user_video_rec = server_open("video_server", "video2.1");
#elif defined CONFIG_VIDEO3_ENABLE
        __this_user->user_video_rec = server_open("video_server", "video3.1");
#endif
        if (!__this_user->user_video_rec) {
            goto __exit;
        }
    }

    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.channel = 1;
    req.rec.width 	= CONFIG_USER_VIDEO_WIDTH;
    req.rec.src_w 	= CONFIG_USER_VIDEO_WIDTH;
    req.rec.height 	= CONFIG_USER_VIDEO_HEIGHT;
    req.rec.src_h 	= CONFIG_USER_VIDEO_HEIGHT;
    req.rec.state 	= VIDEO_STATE_START;
    req.rec.format 	= USER_VIDEO_FMT_AVI;
    req.rec.quality = VIDEO_LOW_Q;//VIDEO_MID_Q;
    req.rec.fps = 10;
#ifdef CONFIG_VIDEO2_ENABLE
    req.rec.uvc_id      = uvc_host_online();
#endif

#ifdef PRODUCT_TEST_ENABLE
    req.rec.real_fps = is_product_mode() ? PRODUCT_UVC_FPS : 15;//帧率
#else
    req.rec.real_fps = 10;
#endif
    req.rec.cycle_time = 60;
    //需要音频：请写audio.sample_rate和audio.buf、audio.buf_len
    req.rec.audio.sample_rate = 8000;//8000 音频采样率
    req.rec.audio.channel 	= 1;
    req.rec.audio.volume    = 64;//音频增益0-100
    req.rec.audio.buf = NULL;//音频BUFF
    req.rec.audio.buf_len = 0;//音频BUFF长度
    req.rec.audio.aud_interval_size = 1024;
    req.rec.abr_kbps = user_video_rec_get_abr(req.rec.width);//JPEG图片码率
    req.rec.buf = __this_user->user_video_buf;
    req.rec.buf_len = USER_VIDEO_SBUF_SIZE;

#ifdef CONFIG_OSD_ENABLE
    struct video_text_osd text_osd = {0};
    text_osd.font_w = OSD_DEFAULT_WIDTH;//必须16对齐
    text_osd.font_h = OSD_DEFAULT_HEIGHT;//必须16对齐
    text_osd.text_format = user_osd_format_buf;
    text_osd.x = (req.rec.width - text_osd.font_w * strlen(text_osd.text_format) + 15) / 16 * 16;
    text_osd.y = (req.rec.height - text_osd.font_h + 15) / 16 * 16;
    text_osd.osd_yuv = 0xe20095;
    req.rec.text_osd = &text_osd;
#endif

    sprintf(path, "usr://%s", "192.168.1.1");
    strcpy(req.rec.net_par.netpath, path);


#if 1 /*需要加上video_rt_usr.c文件则可以创建协议转发任务*/
    err = stream_protocol_task_create(path, NULL);//协议转发任务创建
    if (err != 0) {
        puts("stream_packet_cb set err\n");
        goto __exit;
    }
#endif

    req.rec.target = VIDEO_TO_OUT;

    err = server_request(__this_user->user_video_rec, VIDEO_REQ_REC, &req);
    if (err != 0) {
        puts("user start rec err\n");
        goto __exit;
    }

    extern u32 xc_video_frame_callback(u8 type, void *data, u32 len);
    req.rec.packet_cb = xc_video_frame_callback;//stream_packet_cb;//注册数据包回调函数进行协议转发
    err = server_request(__this_user->user_video_rec, VIDEO_REQ_SET_PACKET_CALLBACK, &req);
    if (err != 0) {
        puts("stream_packet_cb set err\n");
        goto __exit;
    }

    __this_user->state = true;
    printf("user video rec open ok\n");

    return err;

__exit:
    if (__this_user->user_video_rec) {
        memset(&req, 0, sizeof(req));
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(__this_user->user_video_rec, VIDEO_REQ_REC, &req);
        server_close(__this_user->user_video_rec);
        __this_user->user_video_rec = NULL;
    }
    if (__this_user->user_video_buf) {
        free(__this_user->user_video_buf);
        __this_user->user_video_buf = NULL;
    }
#if !USER_ISC_STATIC_BUFF_ENABLE
    if (__this_user->user_isc_buf) {
        free(__this_user->user_isc_buf);
        __this_user->user_isc_buf = NULL;
    }
#endif
#endif

    return err;
}

int user_video_rec0_close(void)
{
    int err = 0;
#ifdef CONFIG_USR_VIDEO_ENABLE
    union video_req req = {0};
    if (__this_user->user_video_rec) {
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(__this_user->user_video_rec, VIDEO_REQ_REC, &req);
        if (err != 0) {
            printf("\nstop rec err 0x%x\n", err);
            return -1;
        }
        server_close(__this_user->user_video_rec);
#if 1 /*需要加上video_rt_usr.c文件则可删除协议转发任务*/
        stream_protocol_task_kill();
#endif
        __this_user->user_video_rec = NULL;
        __this_user->state = false;
        printf("user video rec close ok\n");
    }
    if (__this_user->user_video_buf) {
        free(__this_user->user_video_buf);
        __this_user->user_video_buf = NULL;
    }
#if !USER_ISC_STATIC_BUFF_ENABLE
    if (__this_user->user_isc_buf) {
        free(__this_user->user_isc_buf);
        __this_user->user_isc_buf = NULL;
    }
#endif
#endif
    return 0;
}





#include "system/includes.h"
#include "server/video_server.h"
#include "server/audio_server.h"
#include "lcd_config.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "action.h"
#include "app_config.h"
#include "vrec_osd.h"
#include "baby_monitor.h"
#include "stream_core.h"
#include "sock_api/sock_api.h"
#include "ctp_server.h"

#define VIDEO_OSD_BUF_SIZE      64                  //水印缓存
#define VIDEO_RT_BUF_SIZE       200 * 1024          //实时流缓存
#define VIDEO_REC_BUF_SIZE      1 * 1024 * 1024     //录像视频(JPG)缓存,内存充足的情况下建议给大点

#define AUDIO_BUF_SIZE          64 * 1024           //实时流or录像音频缓存
#define AUDIO_VOLUME	        100                 //实时流or录像音频音量
#define AUDIO_RT_INTERVAL_SIZE      2*640             //实时流音频包大小,尽量设置小一些降低延迟
#define AUDIO_REC_INTERVAL_SIZE     8192            //录像音频包大小

#define AUDIO_RT_RECV_PORT               9981            //接收数据端口
#define AUDIO_DEC_BUF_MAX_LEN            AUDIO_RX_ENC_BUF_MAX_LEN
#define AUDIO_RT_RECV_BUF_MAX_LEN        200*1024

enum {
    WIFI_RAW_MODE = 0,
    WIFI_MODE,
};

struct video_rec_hdl {
    struct list_head dev_list_head;
    u8 cur_wifi_mode;
};
struct video_rec_hdl rec_handler;
#define __this 	(&rec_handler)

struct audio_recv_hdl {
    u8 *recv_buf;
    u32 recv_buf_len;
    void *recv_sockfd;
    int recv_task_pid;
    u8 task_exit;

    u8 *audio_dec_buf;
    cbuffer_t audio_dec_save_cbuf;
    struct server *audio_dec_server;
};
static u8 *tmp_buf = NULL;

//id用于区别摄像头设备(板级对应)比如id0(video0)->MIPI摄像头
//sub_id,在此工程中用于区别同一摄像头设备的实时流/录像
struct video_dev_hdl {
    struct list_head entry;
    struct server *video_server;
    char *video_osd_buf;
    char *video_buf;
    char *audio_buf;
    struct video_rec_config config;
    void *file;

    struct audio_recv_hdl *audio_recv_hdl;
};


static int vfs_audio_dec_fread(void *file, void *data, u32 len)
{
    u32 rlen = 0;
    int ret;
    struct audio_recv_hdl *hdl = file;

    do {

        rlen = cbuf_read(&hdl->audio_dec_save_cbuf, data, len);
        if (rlen == len) {
            break;
        }
    } while (rlen);

    return len;
}

static int vfs_audio_dec_fclose(void *file)
{
    return 0;
}

static int vfs_audio_dec_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_audio_dec_ops = {
    .fwrite = NULL,
    .fread  = vfs_audio_dec_fread,
    .fclose = vfs_audio_dec_fclose,
    .flen   = vfs_audio_dec_flen,
};


static int audio_dec_init(struct audio_recv_hdl *hdl)
{
    union audio_req req = {0};
    int err;

    if (!tmp_buf) {
        tmp_buf = (u8 *)malloc(AUDIO_DEC_BUF_MAX_LEN);
        if (tmp_buf == NULL) {
            printf("tmp_buf malloc fail");
            goto __err;
        }
    }

    hdl->audio_dec_server = server_open("audio_server", "dec");
    if (!hdl->audio_dec_server) {
        printf("open audio_dec_server fail");
        goto __err;
    }

    hdl->audio_dec_buf = (u8 *)malloc(AUDIO_DEC_BUF_MAX_LEN);
    if (hdl->audio_dec_buf == NULL) {
        printf("audio_dec_buf malloc fail");
        goto __err;

    }
    cbuf_init(&hdl->audio_dec_save_cbuf, hdl->audio_dec_buf, AUDIO_DEC_BUF_MAX_LEN);


    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = 100;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = 4096;
    //使用双通道,避免叠音卡顿
    req.dec.channel         = 2;
    req.dec.sample_rate     = 8000;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &vfs_audio_dec_ops;
    req.dec.file            = hdl;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";

    err = server_request(hdl->audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req open err\n");
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    err = server_request(hdl->audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req start err\n");
        goto __err;
    }

    return 0;

__err:
    if (hdl->audio_dec_server) {
        server_close(hdl->audio_dec_server);
        hdl->audio_dec_server = NULL;
    }
    if (hdl->audio_dec_buf) {
        free(hdl->audio_dec_buf);
        hdl->audio_dec_buf = NULL;
    }
    if (tmp_buf) {
        free(tmp_buf);
        tmp_buf = NULL;
    }
    return -1;
}

static int audio_dec_exit(struct audio_recv_hdl *hdl)
{
    int ret;
    union audio_req req = {0};


    if (hdl->audio_dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        ret = server_request(hdl->audio_dec_server, AUDIO_REQ_DEC, &req);
        if (ret) {
            printf("audio server dec stop err %d \n", ret);
        }

        server_close(hdl->audio_dec_server);
        hdl->audio_dec_server = NULL;
    }
    if (hdl->audio_dec_buf) {
        free(hdl->audio_dec_buf);
        hdl->audio_dec_buf = NULL;
    }
    if (tmp_buf) {
        free(tmp_buf);
        tmp_buf = NULL;
    }

    return 0;
}

static int audio_dec_write_cbuf(cbuffer_t *cbuf, u8 *buf, u32 size)
{
    u32 cur_size;
    cur_size =  cbuf_get_data_size(cbuf);

    if (cur_size + (size * 2) >= AUDIO_DEC_BUF_MAX_LEN) {
        cbuf_clear(cbuf);
    }

    u16 *data_in = (u16 *)buf;          // 原始单通道数据
    u16 *data_out = (u16 *)tmp_buf;     // 扩展后的双通道数据

    for (u32 i = 0; i < size / 2; i++) {
        data_out[2 * i] = data_in[i];
        data_out[2 * i + 1] = data_in[i];
    }

    cbuf_write(cbuf, data_out, size * 2);

    return 0;
}

static void rt_audio_recv_task(void *priv)
{
    int ret;
    int recv_len = 0;

    struct audio_recv_hdl *hdl = priv;

    sock_set_recv_timeout(hdl->recv_sockfd, 100);

    while (1) {
        if (hdl->task_exit) {
            printf("rt audio recv task exit\n");
            break;
        }

        recv_len = sock_recvfrom(hdl->recv_sockfd, hdl->recv_buf, hdl->recv_buf_len, 0, NULL, NULL);
        if (recv_len <= 0) {
            putchar('e');
            continue;
        }

        audio_dec_write_cbuf(&hdl->audio_dec_save_cbuf, hdl->recv_buf, recv_len);
    }

}

static int rt_audio_recv_init(struct audio_recv_hdl *hdl)
{
    int ret;
    struct sockaddr_in conn_addr;
    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = htonl(INADDR_ANY) ;
    conn_addr.sin_port = htons(AUDIO_RT_RECV_PORT);

    ret = audio_dec_init(hdl);
    if (ret) {
        return -1;
    }

    hdl->recv_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (hdl->recv_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }

    ret = sock_bind(hdl->recv_sockfd, (struct sockaddr *)&conn_addr, sizeof(struct sockaddr));
    if (ret) {
        printf("sock_bind err:%d\n", ret);
        return -1;
    }

    hdl->recv_buf_len = AUDIO_RT_RECV_BUF_MAX_LEN;
    hdl->recv_buf = malloc(hdl->recv_buf_len);
    if (!hdl->recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        sock_unreg(hdl->recv_sockfd);
        hdl->recv_sockfd = NULL;
        return -1;
    }

    thread_fork("thread_socket_recv", 15, 2048, 2048, &hdl->recv_task_pid, rt_audio_recv_task, hdl);

    return 0;
}

static int rt_audio_recv_exit(struct audio_recv_hdl *hdl)
{

    if (hdl->recv_task_pid) {
        hdl->task_exit = 1;
        thread_kill(&hdl->recv_task_pid, KILL_WAIT);
        hdl->task_exit = 0;
    }

    audio_dec_exit(hdl);

    if (hdl->recv_buf) {
        free(hdl->recv_buf);
        hdl->recv_buf = NULL;
    }

    if (hdl->recv_sockfd) {
        sock_unreg(hdl->recv_sockfd);
        hdl->recv_sockfd = NULL;
    }


    return 0;
}

static int video_rec_close_file(struct video_dev_hdl *dev_hdl)
{
    int ret;
    char fname[32];
    char path[128];

    if (!dev_hdl->file) {
        printf("close file is null \n");
        return 0;
    }

    ret = fget_name(dev_hdl->file, fname, ARRAY_SIZE(fname));
    if (ret <= 0) {
        printf("fget_name err\n");
        fclose(dev_hdl->file);
        return -1;
    }
    strcpy(path, CONFIG_REC_PATH_0);
    strcat(path, fname);

    fclose(dev_hdl->file);
    dev_hdl->file = NULL;

    FILE_LIST_ADD(0, path, 0);

    return 0;
}

static void rec_dev_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        printf("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        printf("VIDEO_SERVER_PKG_ERR\n");
        break;
    case VIDEO_SERVER_PKG_END:
        printf("VIDEO_SERVER_PKG_END\n");
        struct video_dev_hdl *hdl = priv;
        //循环录影
        video_rec_close_file(hdl);
        video_rec_create_file(hdl);
        video_savefile(hdl);
        break;
    case VIDEO_SERVER_NET_ERR:
        printf("VIDEO_SERVER_NET_ERR\n");
        break;
    default :
        printf("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}

static u32 video_rec_get_fsize(u16 abr, u8 cycle_time)
{
    u32 fsize;

    fsize = abr * cycle_time * 10000;

    fsize = fsize + fsize / 4;

    return fsize;
}

static int video_rec_del_first_file(void)
{
    struct vfscan *fs = NULL;
    void *file = NULL;

    fs = fscan(CONFIG_REC_PATH_0, "-d -tPNGBINAVITTLDAT -sn", 2);
    file = fselect(fs, FSEL_FIRST_FILE, 0);
    fdelete(file);

    return 0;
}

static int video_rec_create_file(struct video_dev_hdl *dev_hdl)
{
    int i;
    int err;
    FILE *file;
    u32 cur_space;
    u32 need_space = 0;

    need_space =  video_rec_get_fsize(dev_hdl->config.abr_kbps, dev_hdl->config.cycle_time);

    err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
    if (err) {
        printf("fget free space err\n");
        return err;
    }

    printf("video rec cur space: %dMB, need: %dMB\n", cur_space / 1024, need_space / 1024 / 1024);

    //TODO
    while (cur_space < need_space / 1024) {
        video_rec_del_first_file();

        err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
        if (err) {
            return err;
        }
    }

    file = fopen(CONFIG_REC_PATH_0"VID_****.AVI", "w+");
    if (!file) {
        printf("video rec fopen err\n");
        return -1;
    }
    err = fseek(file, need_space, SEEK_SET);
    if (err) {
        printf("video rec fseek err \n");
        fclose(file);
        return -1;
    }

    fseek(file, 0, SEEK_SET);

    dev_hdl->file = file;

    return 0;
}

static int video_savefile(struct video_dev_hdl *dev_hdl)
{
    union video_req req = {0};
    int err;

    req.rec.channel = dev_hdl->config.sub_id;
    req.rec.width 	= dev_hdl->config.width;
    req.rec.height 	= dev_hdl->config.height;
    req.rec.format  = VIDEO_FMT_AVI;
    req.rec.state 	= VIDEO_STATE_SAVE_FILE;
    req.rec.file    = dev_hdl->file;

    req.rec.fps 	    = dev_hdl->config.fps;
    req.rec.real_fps 	= dev_hdl->config.fps;
    req.rec.abr_kbps    = dev_hdl->config.abr_kbps;
    req.rec.cycle_time  = dev_hdl->config.cycle_time * 60;

    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = AUDIO_VOLUME;

    err = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    if (err != 0) {
        printf("video_save_file: err=%d\n", err);
        return err;
    }

    return 0;
}

static int video_start(struct video_rec_config *config)
{
    int ret;
    char dev_name[20];
    u8 *osd_buf;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;
    struct video_dev_hdl *dev_hdl = NULL;

    u8 id = config->id;
    u8 sub_id = config->sub_id;

    dev_hdl = malloc(sizeof(struct video_dev_hdl));
    if (!dev_hdl) {
        printf("malloc dev_hdl err\n");
        goto err;
    }
    memset(dev_hdl, 0x00, sizeof(struct video_dev_hdl));
    memcpy(&dev_hdl->config, config, sizeof(struct video_rec_config));

    sprintf(dev_name, "video%d.%d", id, sub_id);
    printf("video_rec_start: %s \n", dev_name);

    dev_hdl->video_server = server_open("video_server", dev_name);
    if (!dev_hdl->video_server) {
        printf("video_server open err \n");
        goto err;
    }
    server_register_event_handler(dev_hdl->video_server, dev_hdl, rec_dev_server_event_handler);

    //video
    req.rec.channel     = sub_id;
    req.rec.state       = VIDEO_STATE_START;
    req.rec.quality     = VIDEO_MID_Q;

    req.rec.width       = config->width;
    req.rec.height      = config->height;
    req.rec.fps         = 0;
    req.rec.real_fps    = config->fps;
    req.rec.abr_kbps    = config->abr_kbps;

    //区分录像还是实时流
    if (config->net_path) {
        //实时流
        req.rec.buf_len = VIDEO_RT_BUF_SIZE;
        req.rec.format  = USER_VIDEO_FMT_AVI;
        req.rec.online  = 1;
        req.rec.cycle_time = 5 * 60;

        req.rec.audio.aud_interval_size =
            config->aud_interval_size ? config->aud_interval_size : AUDIO_RT_INTERVAL_SIZE;

        //双向语音
        dev_hdl->audio_recv_hdl = malloc(sizeof(struct audio_recv_hdl));
        if (!dev_hdl->audio_recv_hdl) {
            printf("audio_recv_hdl malloc err\n");
            goto err;
        }
        memset(dev_hdl->audio_recv_hdl, 0x00, sizeof(struct audio_recv_hdl));
        rt_audio_recv_init(dev_hdl->audio_recv_hdl);

    } else {
        //录像
        req.rec.buf_len = VIDEO_REC_BUF_SIZE;
        req.rec.format  = VIDEO_FMT_AVI;
        req.rec.online  = 1;

        if (!config->cycle_time) {
            config->cycle_time = 3;
        }
        req.rec.cycle_time = config->cycle_time * 60;

        req.rec.audio.aud_interval_size = AUDIO_REC_INTERVAL_SIZE;

        ret = video_rec_create_file(dev_hdl);
        if (ret) {
            goto err;
        }

        req.rec.file    = dev_hdl->file;
    }

    //uvc
    if (id == 10) {
        req.rec.camera_type = VIDEO_CAMERA_UVC;
        if (sub_id < 5) {
            req.rec.uvc_id = 0;
        } else {
            req.rec.uvc_id = 1;
        }
        if (uvc_host_online() < 0) {
            printf(" uvc host online err !\n");
            goto err;
        }
        //实时流+录像联动jpeg数量不够
        req.rec.online  = 0;
    } else {
        req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    }


    dev_hdl->video_buf = malloc(req.rec.buf_len);
    if (!dev_hdl->video_buf) {
        printf("malloc video rt buf err\n");
        goto err;
    }
    req.rec.buf = dev_hdl->video_buf;

    //OSD
    dev_hdl->video_osd_buf = malloc(VIDEO_OSD_BUF_SIZE);
    if (!dev_hdl->video_osd_buf) {
        printf("malloc video rt osd buf err\n");
        goto err;
    }
    memset(dev_hdl->video_osd_buf, 0x00, VIDEO_OSD_BUF_SIZE);
    osd_buf = dev_hdl->video_osd_buf;

    memset(osd_buf, ' ', 8);
    osd_buf[8] = '\\';
    memcpy(osd_buf + 9, osd_str_buf, strlen(osd_str_buf));
    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(osd_buf);
    osd_line_num = 1;
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);
    text_osd.direction = 1;

    //实时流不开启水印
    if (config->net_path) {
        req.rec.text_osd = NULL;
    } else {
        req.rec.text_osd = &text_osd;
    }
    req.rec.graph_osd = NULL;//&graph_osd;

    //audio
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = AUDIO_VOLUME;

    dev_hdl->audio_buf = malloc(AUDIO_BUF_SIZE);
    if (!dev_hdl->audio_buf) {
        printf("malloc audio rt buf err \n");
        goto err;
    }
    req.rec.audio.buf = dev_hdl->audio_buf;
    req.rec.audio.buf_len = AUDIO_BUF_SIZE;

    //回声消除,默认使用软件的
    //如要改动其他采样率或硬件回声消除请查看开源文档
    req.rec.audio.aec_enable = 1;
    struct aec_s_attr aec_param = {0};
    req.rec.audio.aec_attr = &aec_param;

    extern void get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);

    if (aec_param.EnableBit == 0) {
        req.rec.audio.aec_enable = 0;
        req.rec.audio.aec_attr = NULL;
    }
    aec_param.wideband = 0;
    aec_param.hw_delay_offset = 75;


    //实时流
    if (config->net_path) {
        strcpy(req.rec.net_par.netpath, config->net_path);
        printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
        req.rec.target = VIDEO_TO_OUT;
        req.rec.out.path = req.rec.net_par.netpath;
        req.rec.out.arg  = NULL ;
        req.rec.out.open = stream_open;
        req.rec.out.send = stream_write;
        req.rec.out.close = stream_close;
    }

    ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        puts("\n\n\nstart rec err\n\n\n");
        goto err;
    }

    if (config->net_path) {
        req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
        server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    }

    list_add_tail(&dev_hdl->entry, &__this->dev_list_head);

    return 0;

err:
    if (dev_hdl) {
        if (dev_hdl->video_buf) {
            free(dev_hdl->video_buf);
        }
        if (dev_hdl->video_osd_buf) {
            free(dev_hdl->video_osd_buf);
        }
        if (dev_hdl->audio_buf) {
            free(dev_hdl->audio_buf);
        }
        if (dev_hdl->audio_recv_hdl) {
            rt_audio_recv_exit(dev_hdl->audio_recv_hdl);
            free(dev_hdl->audio_recv_hdl);
        }

        server_close(dev_hdl->video_server);

        free(dev_hdl);
    }
    return -1;
}

static int video_stop(struct video_rec_config *config)
{
    struct video_dev_hdl *dev_hdl = NULL;

    union video_req req = {0};
    int ret;
    u8 id = config->id;
    u8 sub_id = config->sub_id;
    u8 find = 0;

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            find = 1;
            list_del(&dev_hdl->entry);
            break;
        }
    }

    if (!find) {
        printf(" not found dev hdl  id:%d sub_id:%d \n", id, sub_id);
        return -1;
    }

    req.rec.channel = dev_hdl->config.sub_id;
    req.rec.state = VIDEO_STATE_STOP;
    ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        printf("\nstop rec err 0x%x\n", ret);
        return -1;
    }

    video_rec_close_file(dev_hdl);

    server_close(dev_hdl->video_server);


    if (dev_hdl->video_buf) {
        free(dev_hdl->video_buf);
    }
    if (dev_hdl->video_osd_buf) {
        free(dev_hdl->video_osd_buf);
    }
    if (dev_hdl ->audio_buf) {
        free(dev_hdl->audio_buf);
    }
    if (dev_hdl->audio_recv_hdl) {
        rt_audio_recv_exit(dev_hdl->audio_recv_hdl);
        free(dev_hdl->audio_recv_hdl);
    }


    free(dev_hdl);

    return 0;
}

static int video_stop_all(void)
{
    struct video_dev_hdl *dev_hdl = NULL;
    struct video_dev_hdl *n = NULL;

    union video_req req = {0};
    int ret;

    list_for_each_entry_safe(dev_hdl, n, &__this->dev_list_head, entry) {
        list_del(&dev_hdl->entry);
        req.rec.channel = dev_hdl->config.sub_id;
        req.rec.state = VIDEO_STATE_STOP;
        ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
        if (ret) {
            printf("\nstop rec err 0x%x\n", ret);
            return -1;
        }
        video_rec_close_file(dev_hdl);

        server_close(dev_hdl->video_server);

        if (dev_hdl->video_buf) {
            free(dev_hdl->video_buf);
        }
        if (dev_hdl->video_osd_buf) {
            free(dev_hdl->video_osd_buf);
        }
        if (dev_hdl ->audio_buf) {
            free(dev_hdl->audio_buf);
        }

        if (dev_hdl->audio_recv_hdl) {
            rt_audio_recv_exit(dev_hdl->audio_recv_hdl);
            free(dev_hdl->audio_recv_hdl);
        }
        free(dev_hdl);
    }

    return 0;
}

static int video_stop_all_rec(void)
{
    struct video_dev_hdl *dev_hdl = NULL;
    struct video_dev_hdl *n = NULL;

    union video_req req = {0};
    int ret;

    list_for_each_entry_safe(dev_hdl, n, &__this->dev_list_head, entry) {
        if (!dev_hdl->file) {
            //实时流
            continue;
        }

        list_del(&dev_hdl->entry);
        req.rec.channel = dev_hdl->config.sub_id;
        req.rec.state = VIDEO_STATE_STOP;
        ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
        if (ret) {
            printf("\nstop rec err 0x%x\n", ret);
            return -1;
        }
        video_rec_close_file(dev_hdl);

        server_close(dev_hdl->video_server);

        if (dev_hdl->video_buf) {
            free(dev_hdl->video_buf);
        }
        if (dev_hdl->video_osd_buf) {
            free(dev_hdl->video_osd_buf);
        }
        if (dev_hdl ->audio_buf) {
            free(dev_hdl->audio_buf);
        }

        if (dev_hdl->audio_recv_hdl) {
            rt_audio_recv_exit(dev_hdl->audio_recv_hdl);
            free(dev_hdl->audio_recv_hdl);
        }
        free(dev_hdl);
    }

    return 0;
}


static int video_set_abr(struct video_rec_config *config)
{
    int ret = 0;
    union video_req req = {0};
    u8 find = 0;
    u8 id = config->id;
    u8 sub_id = config->sub_id;
    struct video_dev_hdl *dev_hdl = NULL;

    printf("set abr:%d id:%d  sub_id:%d \n"
           , config->abr_kbps, config->id, config->sub_id);

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            find = 1;
            break;
        }
    }

    if (!find) {
        printf(" video_set_abr not found dev hdl id:%d sub_id:%d \n", id, sub_id);
        return -1;
    }

    req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
    req.rec.channel     = sub_id;
    req.rec.abr_kbps    = config->abr_kbps;

    if (dev_hdl->video_server) {
        ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
        if (ret) {
            printf("reset bits rate err :%d \n", ret);
        }
    }

    return ret;
}

static int video_take_photo(struct video_rec_config *config)
{
    int ret = -1;
    int find = 0;
    char buf[128];
    char fname[32];
    union video_req req = {0};
    struct video_dev_hdl *dev_hdl = NULL;
    void *fp;

    u8 id = config->id;
    u8 sub_id = config->sub_id;

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            find = 1;
            break;
        }
    }

    if (find) {
        if (dev_hdl->video_server) {
            printf("video save frame \n");
            fp = fopen(CAMERA0_CAP_PATH"img_****.jpg", "w+");
            if (!fp) {
                printf("video take photo fopen err \n");
                return -1;
            }
            ret = fget_name(fp, fname, ARRAY_SIZE(fname));
            if (ret <= 0) {
                printf("video take photo fget_name err\n");
                fclose(fp);
                return -1;
            }
            fclose(fp);
            sprintf(buf, "%s%s", CAMERA0_CAP_PATH, fname);
            req.rec.rec_save_path = buf;
            req.rec.channel = sub_id;
            ret = server_request(dev_hdl->video_server, VIDEO_REQ_SAVE_FRAME, &req);
            if (ret) {
                printf("video save frame err:%d \n", ret);
            } else {
#if defined CONFIG_ENABLE_VLIST
                sprintf(buf, "%s", req.rec.rec_save_path);
                FILE_LIST_ADD(0, buf, 0);
#endif
            }
        }
    }

    return ret;
}


static int video_get_status(struct video_rec_config *config, int *status)
{
    u8 id = config->id;
    u8 sub_id = config->sub_id;
    struct video_dev_hdl *dev_hdl = NULL;

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            *status = 1;
            return 0;
        }
    }

    *status = 0;

    return 0;
}

static int switch_wifi_mode(void)
{
    if (__this->cur_wifi_mode == WIFI_RAW_MODE) {
        wifi_raw_exit();
        wifi_init();
        __this->cur_wifi_mode = WIFI_MODE;
        video_stop_all();
    } else {
        wifi_exit();
        wifi_raw_init();
        __this->cur_wifi_mode = WIFI_RAW_MODE;
        video_stop_all();
    }
}

static int video_rec_state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;

    switch (state) {
    case APP_STA_CREATE:
        log_d("\n >>>>>>> video_rec: create\n");
        memset(__this, 0, sizeof(struct video_rec_hdl));
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_VIDEO_REC_MAIN:
            INIT_LIST_HEAD(&__this->dev_list_head);
            puts("ACTION_VIDEO_REC_MAIN\n");
            break;
        case ACTION_VIDEO_START:
            puts("ACTION_VIDEO_START\n");
            ret = video_start(it->exdata);
            break;
        case ACTION_VIDEO_STOP:
            puts("ACTION_VIDEO_STOP\n");
            ret = video_stop(it->exdata);
            break;
        case ACTION_VIDEO_STOP_ALL:
            puts("ACTION_VIDEO_STOP_ALL\n");
            ret = video_stop_all();
            break;
        case ACTION_VIDEO_SET_ABR:
            puts("ACTION_VIDEO_SET_ABR\n");
            ret = video_set_abr(it->exdata);
            break;
        case ACTION_VIDEO_GET_STATUS:
            puts("ACTION_VIDEO_GET_STATUS\n");
            ret = video_get_status(it->exdata, it->data);
            break;
        case ACTION_VIDEO_TAKE_PHOTO:
            puts("ACTION_VIDEO_TAKE_PHOTO\n");
            ret = video_take_photo(it->exdata);
            break;
        }
        break;
    case APP_STA_PAUSE:
        puts("--------app_rec: APP_STA_PAUSE\n");
        break;
    case APP_STA_RESUME:
        puts("--------app_rec: APP_STA_RESUME\n");
        break;
    case APP_STA_STOP:
        puts("--------app_rec: APP_STA_STOP\n");
        break;
    case APP_STA_DESTROY:
        break;
    }

    return ret;
}


static int video_rec_key_event_handler(struct key_event *key)
{
    int ret = false;
    printf("key->action:%d key->value:%d \n", key->action, key->value);

#ifdef CONFIG_BBM_TX
    switch (key->value) {
    case KEY_POWER:
        printf("KEY1\n");
        break;
    case KEY_MENU:
        printf("KEY2\n");
        break;
    case KEY_UP:
        printf("KEY3\n");
        break;
    case KEY_DOWN:
        printf("KEY4\n");
        if (key->action == KEY_EVENT_CLICK) {
            ret = true;
            switch_wifi_mode();
        }
        break;
    case KEY_OK:
        ret = true;
        if (key->action == KEY_EVENT_DOWN) {
            printf("KEY5 DOWN\n");
            if (__this->cur_wifi_mode == WIFI_RAW_MODE) {
                bbm_tx_enter_pairing();
            }
        } else if (key->action == KEY_EVENT_UP) {
            printf("KEY5 UP\n");
            if (__this->cur_wifi_mode == WIFI_RAW_MODE) {
                bbm_tx_exit_pairing();
            }
        }
        break;
    }
#endif

    return ret;
}

static int video_rec_device_event_handler(struct sys_event *e)
{
    int ret = false;
    char buf[16];
    struct device_event *device_eve = (struct device_event *)e->payload;

    if (e->from == DEVICE_EVENT_FROM_SD) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            FILE_LIST_IN_MEM(1);
            ret = true;
            break;
        case DEVICE_EVENT_OUT:
            FILE_LIST_EXIT();
            snprintf(buf, sizeof(buf), "online:0");
            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "SD_STATUS", "NOTIFY", buf);
            ret = true;
            video_stop_all_rec();
            break;
        default:
            break;
        }
    }


    return ret;
}

int video_rec_net_event_hander(void *e)
{
    struct net_event *event = (struct net_event *)e;
    struct ctp_arg *event_arg = (struct ctp_arg *)event->arg;
    /* struct net_event *net = &event->u.net; */

    switch (event->event) {
    case NET_EVENT_CMD:
        printf("IN NET_EVENT_CMD\n");
        ctp_cmd_analysis(event_arg->topic, event_arg->content, event_arg->cli);
        if (event_arg->content) {
            free(event_arg->content);
        }
        event_arg->content = NULL;
        if (event_arg) {
            free(event_arg);
        }
        event_arg = NULL;
        return true;
        break;
    case NET_EVENT_DATA:
        /* printf("IN NET_EVENT_DATA\n"); */
        break;
    }
    return false;
}

/*录像app的事件总入口*/
static int video_rec_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return video_rec_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return video_rec_device_event_handler(event);
    case SYS_NET_EVENT:
        return video_rec_net_event_hander((void *)event->payload);
    default:
        return false;
    }
}


static const struct application_operation video_rec_ops = {
    .state_machine  = video_rec_state_machine,
    .event_handler 	= video_rec_event_handler,
};

REGISTER_APPLICATION(app_video_rec) = {
    .name 	= "video_rec",
    .action	= ACTION_VIDEO_REC_MAIN,
    .ops 	= &video_rec_ops,
    .state  = APP_STA_DESTROY,
};






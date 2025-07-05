#include "sock_api/sock_api.h"
#include "os/os_api.h"
#include "server/net_server.h"
#include "server/server_core.h"
#include "server/ctp_server.h"
#include "server/simple_mov_unpkg.h"
#include "server/rt_stream_pkg.h"
#include "fs/fs.h"
#include "sys_common.h"
#include "generic/list.h"
#include "packet.h"

#define VIDEO_PLAYBACK_TASK_NAME "video_playback"
#define VIDEO_PLAYBACK_TASK_STK  0x300
#define VIDEO_PLAYBACK_TASK_PRIO 22


struct __playback {
    u32 id;
    u8 state;
    void *video_playback_sock_hdl;
    int (*cb)(void *priv, u8 *data, size_t len);
    u8 kill_flag;
    OS_MUTEX mutex;
    struct list_head cli_head;
};


static struct __playback playback_info;
#define playback_info_hander (&playback_info)
static u32 cout = 0;//thread_fork name;
struct __playback_cli_info {
    struct list_head entry;
    u32 msec;
    u32 state;
    struct sockaddr_in remote_addr;
    int pid;
    u8 stop;
    u8 kill_flag;
    u16 fast_ctrl;
    u32 tmp_is_30fps;
    struct __packet_info pinfo;
    OS_SEM   sem;

};
//offset : cnt
static int find_idr_frame(struct __packet_info *pinfo, u32 offset)
{
    int i = 0;
    char buf[5];
    int sample_offset;
    int sample_size;
    int ret;

    float  frame_per_ts = 0 ;

    /* printf(" pinfo->info.durition=%d   pinfo->info.scale=%d \n", pinfo->info.durition, pinfo->info.scale); */
    /* frame_per_ts = (pinfo->info.durition * 1000) / (pinfo->info.video_sample_count * pinfo->info.scale); */

    /* i = offset / frame_per_ts; */

#ifdef CONFIG_NET_H264
    i = offset * pinfo->info.scale / (pinfo->info.sample_duration * 1000);
    while (1) {

        if (i >= pinfo->info.video_sample_count) {
            return pinfo->info.video_sample_count - 1;
        }

        sample_size = get_sample_size(pinfo->info.stsz_tab, i);
        if (sample_size == -1) {
            return -1;
        }

        sample_offset = get_chunk_offset(pinfo->info.stco_tab, i);
        if (sample_offset == -1) {
            return -1;
        }

        if (false == fseek(pinfo->fd, sample_offset, SEEK_SET)) {
            return -1;
        }
        ret = fread(pinfo->fd, buf, 5);
        if (ret != 5) {
            return -1;
        }

        if (buf[4] != 0x67) {
            i--;
        } else {
            return i;
        }

    }
#endif

#ifdef CONFIG_NET_JPEG
    return  avi_get_video_num(pinfo->fd, offset, pinfo->state); //返回seq
#endif
    return 0;
}

static int send_date_end_packet(struct __playback_cli_info *cli, u32 i)
{
    if (cli->tmp_is_30fps != i) {
        return send_date_packet(&cli->pinfo, 1);
    } else {
        return 0;
    }
}

static int send_date_per_fps(struct __playback_cli_info *cli, u32 i)
{
    int ret = 0;
    u32  is_30fps = 0;
    u32 sec = 0;
    int fps;
    int cnt = i + 1;

#ifdef CONFIG_NET_H264
    fps = cli->pinfo.info.scale / cli->pinfo.info.sample_duration;
#endif

#ifdef CONFIG_NET_JPEG
    fps = avi_get_fps(cli->pinfo.fd, cli->pinfo.state);
#endif

    sec = (cnt - cli->tmp_is_30fps) / fps;

    if (sec) {
        //printf("vd_cnt :  %d , all : %d , fp : %d \n", i + 1, cli->pinfo.info.video_sample_count, fps);
        ret = send_date_packet(&cli->pinfo, sec);
#if 0
        send_gps_data_packet(&cli->pinfo);
#endif
        cli->tmp_is_30fps = cnt - cnt % fps;//消除快进时间累计误差
    }
    return ret;
}

static void video_playback_cli_thread_udp(void *arg)
{
    int ret;
    FILE *fd;
    u8 name[32];
    char buf[64];
    int i = 0, j = 0;
    u32 msec = 0;
    int last_video_num = 0;
    struct __playback_cli_info *cli = (struct __playback_cli_info *)arg;

    puts("start  video_playback_cli_thread_udp\n");
    cli->pinfo.data = (u8 *)zalloc(IMAGE_SIZE);
    cli->pinfo.len = IMAGE_SIZE;
    if (!cli->pinfo.data) {
        cli->pinfo.data = (u8 *)zalloc(IMAGE_SIZE / 2);
        cli->pinfo.len = IMAGE_SIZE / 2;
    }
    if (cli->pinfo.data == NULL) {
        printf("%s err , no mem !!!\n\n", __func__);
        CTP_CMD_COMBINED(NULL, CTP_OPEN_FILE, "TIME_AXIS_PLAY", "NOTIFY", buf);
        goto err1;
    }
    cli->pinfo.fd = fopen(cli->pinfo.file_name, "r");
    cli->fast_ctrl = 0;
    cli->pinfo.state = 1;//回放模式

    if (cli->pinfo.fd == NULL) {
        puts("open fail\n");
        fget_name(cli->pinfo.fd, name, 32);
        sprintf(buf, "path:%s", name);
        CTP_CMD_COMBINED(NULL, CTP_OPEN_FILE, "TIME_AXIS_PLAY", "NOTIFY", buf);
        goto err1;
    }

    avi_net_playback_unpkg_init(cli->pinfo.fd, cli->pinfo.state);
    if (!is_vaild_avi_file(cli->pinfo.fd, cli->pinfo.state)) {
        puts("open fail\n");
        fget_name(cli->pinfo.fd, name, 32);
        sprintf(buf, "path:%s", name);
        CTP_CMD_COMBINED(NULL, CTP_OPEN_FILE, "TIME_AXIS_PLAY", "NOTIFY", buf);
        goto err1;
    }

    cli->pinfo.type = JPEG_TYPE_VIDEO;

    //get video media info
    if (get_video_media_info(&cli->pinfo)) {
        puts("get video media fail\n");
        goto err1;
    }
    i = find_idr_frame(&cli->pinfo, cli->msec);

    if (send_media_packet(&cli->pinfo) <= 0) {
        printf("send media packet fail \n\n");
        CTP_CMD_COMBINED(NULL, CTP_NET_ERR, "TIME_AXIS_PLAY", "NOTIFY", CTP_NET_ERR_MSG);
        goto err1;

    }

    incr_date_time(&cli->pinfo.time, cli->msec / 1000);

    cli->tmp_is_30fps = i;

    j = avi_video_base_to_get_audio_frame(i, cli->pinfo.state);

    int frame_interval = 1000 / cli->pinfo.info.sample_duration;
    int last_send_time = 0;

    while (1) {
        if (cli->stop) {
            os_sem_pend(&cli->sem, 0);
        }

        if (cli->kill_flag) {
            printf("--kill_flag---\n");
            goto err1;
        }

        if (cli->pinfo.info.video_sample_count && i >= last_video_num) {
            if (!cli->fast_ctrl) {
                if (j < cli->pinfo.info.audio_chunk_num && cli->pinfo.info.audio_chunk_num) {
                    ret = send_audio_packet(&cli->pinfo, j);
                    if (ret <= 0) {
                        goto send_video;
                    }
                    last_video_num = avi_audio_base_to_get_video_frame(j, cli->pinfo.state);
                    /*printf("ad : %d , vd : %d , num :%d \n",j,i,last_video_num);*/
                    j++;
                }
            }
        }

send_video:

        if (i >= cli->pinfo.info.video_sample_count) {
            send_end_packet(&cli->pinfo);
            goto err1;
        }

        /*printf("vd_cnt :  %d , all : %d \n", i + 1, cli->pinfo.info.video_sample_count);*/
        int now = timer_get_ms();
        int expected_time = last_send_time + frame_interval;
        if (now < expected_time) {
            os_time_dly((expected_time - now) / 10 + 1);
        }
        last_send_time = timer_get_ms();
        ret = send_video_packet(&cli->pinfo, i);

        if (ret < 0) {
            /* CTP_CMD_COMBINED(NULL, CTP_NET_ERR, "TIME_AXIS_PLAY", "NOTIFY", CTP_NET_ERR_MSG); */
            puts("send vidoe err!\n");
            goto err1;
        } else if (ret == 0) {
            goto err1;
        }

        i++;
        send_date_per_fps(cli, i);
    }

err1:
    avi_net_unpkg_exit(cli->pinfo.fd, cli->pinfo.state);

    if (cli->pinfo.info.stco_tab != NULL) {
        free(cli->pinfo.info.stco_tab);
        cli->pinfo.info.stco_tab = NULL;
    }

    if (cli->pinfo.info.stsz_tab != NULL) {
        free(cli->pinfo.info.stsz_tab);
        cli->pinfo.info.stsz_tab = NULL;
    }

    if (cli->pinfo.info.audio_stco_tab != NULL) {
        free(cli->pinfo.info.audio_stco_tab);
        cli->pinfo.info.audio_stco_tab = NULL;
    }

    if (cli->pinfo.fd != NULL) {
        fclose(cli->pinfo.fd);
        cli->pinfo.fd = NULL;
    }
    if (cli->pinfo.data) {
        free(cli->pinfo.data);
    }
    os_mutex_pend(&playback_info_hander->mutex, 0);
    list_del(&cli->entry);
    sock_unreg(cli->pinfo.sock);
    cli->pinfo.data = NULL;
    cli->kill_flag = 0;

    free(cli);
    os_mutex_post(&playback_info_hander->mutex);
}

int video_playback_post_msg_udp(struct net_req *req)
{
    char buf[128];
    char name[32];
    int ret1 = 0;

    os_mutex_create(&playback_info_hander->mutex);
    INIT_LIST_HEAD(&playback_info_hander->cli_head);

    sprintf(buf, "status:%d", 0);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "TIME_AXIS_PLAY", "NOTIFY", buf);
    //malloc cli info res
    struct __playback_cli_info *cli = zalloc(sizeof(struct __playback_cli_info));//&cli_playback_info;

    if (cli == NULL) {
        printf("%s ::%d calloc \n", __func__, __LINE__);
        goto err1;
    }

    void *fd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (fd == NULL) {
        printf("%s %d->Error in socket()\n", __func__, __LINE__);
        return -1;
    }

    //get req
    strcpy(cli->pinfo.file_name, req->playback.file_name);
    cli->msec = req->playback.msec;
    cli->pinfo.sock = fd;
    cli->pinfo.is_udp = 1;

    printf("old req->playback.filename : %s sec:%d\n", req->playback.file_name, req->playback.msec);
    printf("new req->playback.filename : %s sec:%d\n", cli->pinfo.file_name, cli->msec);

    //malloc data's bufffer
    cli->pinfo.data = NULL;//(u8 *)calloc(IMAGE_SIZE, 1);
    cli->pinfo.len = 0;//IMAGE_SIZE;

    memcpy(&cli->remote_addr, &req->remote_addr, sizeof(struct sockaddr_in));
    memcpy(&cli->pinfo.remote_addr, &req->remote_addr, sizeof(struct sockaddr_in));

    os_sem_create(&cli->sem, 0);
    os_mutex_pend(&playback_info_hander->mutex, 0);
    list_add_tail(&cli->entry, &playback_info_hander->cli_head);
    os_mutex_post(&playback_info_hander->mutex);

    printf("create cli thread\n");
    sprintf(name, "playback_cli_%d", cout++);
    ret1 = thread_fork(name, 19, 1024, 0, &cli->pid, video_playback_cli_thread_udp, (void *)cli);
    if (ret1 != OS_NO_ERR) {
        free(cli);
        printf("thread fork err =%d\n", ret1);
        goto err1;
    }

err1:
    return ret1;
}

static int playback_disconnect_all_cli(void)
{
    puts("---------------playback_disconnect_all_cli\n\n");
    struct __playback_cli_info *cli = NULL;
    struct list_head *pos = NULL, *node = NULL;
    os_mutex_pend(&playback_info_hander->mutex, 0);
    if (list_empty(&playback_info_hander->cli_head)) {
        puts("video_playback cli is emtry\n");
        os_mutex_post(&playback_info_hander->mutex);
        return -1;
    }
    list_for_each_safe(pos, node, &playback_info_hander->cli_head) {
        cli = list_entry(pos, struct __playback_cli_info, entry);
        cli->kill_flag = 1;
        if (cli->stop) {
            os_sem_post(&cli->sem);
        }

        sock_set_quit(cli->pinfo.sock);
    }

    os_mutex_post(&playback_info_hander->mutex);
    return -1;
}


void playback_udp_init(void)
{
    puts("playback_udp_init\n");
    os_mutex_create(&playback_info_hander->mutex);
    INIT_LIST_HEAD(&playback_info_hander->cli_head);
}

void playback_udp_uninit(void)
{
    puts("playback_udp_uninit\n");
    playback_disconnect_all_cli();
}

int playback_udp_disconnect_cli(struct sockaddr_in *dst_addr)
{
    /*puts("---------------playback_disconnect_cli\n\n"); */
    struct __playback_cli_info *cli = NULL;
    os_mutex_pend(&playback_info_hander->mutex, 0);
    struct list_head *pos = NULL, *node = NULL;
    if (list_empty(&playback_info_hander->cli_head)) {
        puts("video_playback cli is emtry\n");
        os_mutex_post(&playback_info_hander->mutex);
        return -1;
    }
    list_for_each_safe(pos, node, &playback_info_hander->cli_head) {
        cli = list_entry(pos, struct __playback_cli_info, entry);

        /* printf("remote_addr:%s:%d\n", inet_ntoa(cli->remote_addr.sin_addr.s_addr), ntohs(cli->remote_addr.sin_port)); */
        if (dst_addr != NULL
            && cli->remote_addr.sin_addr.s_addr == dst_addr->sin_addr.s_addr) {
            cli->kill_flag = 1;
            if (cli->stop) {
                os_sem_post(&cli->sem);
            }

            sock_set_quit(cli->pinfo.sock);
        } else {
            printf("not find dst_addr:%s:%d\n", inet_ntoa(dst_addr->sin_addr.s_addr), ntohs(dst_addr->sin_port));
        }

        os_mutex_post(&playback_info_hander->mutex);
        return 0;
        //break;
    }

    os_mutex_post(&playback_info_hander->mutex);
    return -1;
}

int playback_udp_cli_pause(struct sockaddr_in *dst_addr)
{
    puts("-----------playback_cli_pause\n\n");
    struct __playback_cli_info *cli = NULL;
    struct list_head *pos = NULL, *node = NULL;

    os_mutex_pend(&playback_info_hander->mutex, 0);
    list_for_each_safe(pos, node, &playback_info_hander->cli_head) {
        cli = list_entry(pos, struct __playback_cli_info, entry);

        if (cli->remote_addr.sin_addr.s_addr == dst_addr->sin_addr.s_addr) {
            cli->stop = 1;
            os_mutex_post(&playback_info_hander->mutex);
            return 0;
            //		break;
        }
    }
    os_mutex_post(&playback_info_hander->mutex);
    return -1;
}

int playback_udp_cli_continue(struct sockaddr_in *dst_addr)
{
    puts("---------------playback_cli_continue\n\n");
    struct __playback_cli_info *cli = NULL;
    struct list_head *pos = NULL, *node = NULL;
    os_mutex_pend(&playback_info_hander->mutex, 0);
    list_for_each_safe(pos, node, &playback_info_hander->cli_head) {
        cli = list_entry(pos, struct __playback_cli_info, entry);

        if (cli->remote_addr.sin_addr.s_addr == dst_addr->sin_addr.s_addr) {
            cli->stop = 0;

            os_sem_post(&cli->sem);
            os_mutex_post(&playback_info_hander->mutex);
            return 0;
            //break;
        }
    }
    os_mutex_post(&playback_info_hander->mutex);
    return -1;

}


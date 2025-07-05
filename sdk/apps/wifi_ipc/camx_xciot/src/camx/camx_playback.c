
#define _STDIO_H_
#include "xciot_api.h"
#include "packet.h"
#include "init.h"



extern uint64_t get_utc_ms(void);
extern int net_video_rec_get_fps(void);
extern int video_rec_get_audio_sampel_rate();

typedef struct cloud_playback_info {
    struct list_head entry;
    u8 kill_flag;
    int task_id;
    char task_name[32];
    int32_t conn_id;
    uint64_t file_id;
    int64_t start_time;
} CLOUD_PLAYBACK_INFO;

#define VIDEO_INTERVAL  (1000 / (net_video_rec_get_fps()*fast_ctrl))
//包长度 / 每ms音频长度  = 音频间隔, -8 每次提前8ms进行发送
#define AUDIO_INTERVAL   (40/fast_ctrl)
#define AUDIO_PACKET_LEN        (640)
static LIST_HEAD(cloud_playback_list_head);
static OS_MUTEX cloud_playback_mutex;
static u32 fast_ctrl = 1;

/*
 * 获取文件缩略图
 * name: 文件名
 * type: 文件类型(loop, emr)---暂时用不上
 * thm_addr:缩略图二进制文件的存放地址
 * 返回值:读到的缩略图的长度
 * */
int get_file_thm(char *name, char type, char *thm_addr, int len)
{
    int ret;
    FILE *fd;

    fd = fopen(name, "r");
    if (!fd) {

        thm_addr = NULL;
        return 0;
    }

    struct __packet_info pinfo = {0};
    pinfo.state = 0;
    pinfo.fd = fd;

    avi_net_playback_unpkg_init(fd, pinfo.state);

    if (!is_vaild_avi_file(fd, pinfo.state)) {
        fclose(fd);

        thm_addr = NULL;
        return 0;
    }


    //get video media info
    if (get_video_media_info(&pinfo)) {
        puts("get video media fail\n");

    }

    ret = avi_video_get_frame(pinfo.fd, 1, thm_addr, len,  pinfo.state);
    if (ret <= 0) {
        return ret;
    }

    if (!pinfo.state) {
        printf("get video frame ok...\n");
    }
    /* printf("frame len:%d\n", ret); */
    put_buf(thm_addr, 64);
    avi_net_unpkg_exit(pinfo.fd, pinfo.state);
    fclose(fd);
    return ret;

}

int cloud_playback_get_speed(void)
{
    return fast_ctrl;
}

int cloud_playback_set_speed(int s)
{

    fast_ctrl = s;

    return 0;
}

static int areTimestampsOnSameDay(time_t timestamp1, time_t timestamp2)
{
    struct tm tm1, tm2;

    covUnixTimeStp2Beijing(timestamp1, &tm1);
    covUnixTimeStp2Beijing(timestamp2, &tm2);

    /* printf("%d-%d-%d\n", tm1.tm_year, tm1.tm_mon, tm1.tm_mday); */
    /* printf("%d-%d-%d\n", tm2.tm_year, tm2.tm_mon, tm2.tm_mday); */
    return (tm1.tm_year == tm2.tm_year) && (tm1.tm_mon == tm2.tm_mon) && (tm1.tm_mday == tm2.tm_mday);
}


void cloud_playback_task(void *priv)
{

    CLOUD_PLAYBACK_INFO *p = (struct avplay_info *)priv;

    int32_t conn_id = p->conn_id;
    int32_t file_id = p->file_id;
    char file_name[64];
    char name[64];
    struct tm t;
    uint64_t a_send_time, v_send_time;
    int64_t a_timestamp_ms, v_timestamp_ms;


    a_timestamp_ms = v_timestamp_ms = p->start_time * 1000;

    char *pcm_data = NULL;
    int offset = 0;
    int audio_remain = 0;
    int send_audio_flag = 1;
    int send_video_flag = 1;
    struct __packet_info pinfo = {0};
    int ret = 0;
    int i = 0, j = 0;
    fast_ctrl = 1;

    /*printf("\nreq->file_id =%llu \n", file_id);*/

#if NAME_FILE_BY_DATE
    char time_str[64] = {0};
    u8 dir_len = 0;
    struct tm timeinfo = {0};
    time_t timestamp = file_id;
    localtime_r(&timestamp, &timeinfo);
    strcpy(time_str, CONFIG_REC_PATH_0);
    dir_len = strlen(time_str);
    strftime(time_str + dir_len, sizeof(time_str) - dir_len, "VID_%Y%m%d_%H%M%S.AVI", &timeinfo);
    log_i("recorder file name : %s\n", time_str);

    memcpy(file_name, time_str, sizeof(time_str));


    printf("\nfile_name = %s \n", file_name);

    char path_file[128];
    int len;

    len = long_file_name_encode(file_name, (u8 *)path_file, sizeof(path_file));
    memcpy(file_name, path_file, len);
#else
    snprintf(file_name, sizeof(file_name), "%sVID_%04d.AVI", CONFIG_REC_PATH_0, file_id);
    printf("\nfile_name = %s \n", file_name);
#endif
    pinfo.len = IMAGE_SIZE;
    pinfo.data = (u8 *)zalloc(IMAGE_SIZE);
    if (pinfo.data == NULL) {
        printf("\n[Error] %s %d malloc fali\n", __func__, __LINE__);
        goto err1;
    }

    pinfo.fd =  fopen(file_name, "r");
    if (!pinfo.fd) {
        printf("\n[Error] %s %d fopen fali  %s\n", __func__, __LINE__, file_name);
        goto err1;
    }
    pinfo.state = 1;
    ret =  avi_net_playback_unpkg_init(pinfo.fd, pinfo.state);
    if (ret) {
        printf("\n[Error] %s %d avi unpkg fali  %s\n", __func__, __LINE__, file_name);
        goto err1;
        /* ASSERT(0, "\n >>>>>>>>>>>>>>>>%s %d\n", __func__, __LINE__); */
    }
    if (!is_vaild_avi_file(pinfo.fd, pinfo.state)) {
        printf("\n[Error] %s %d FILE is vaild\n", __func__, __LINE__);
        goto err1;
    }
    pinfo.type = JPEG_TYPE_VIDEO;

    if (get_video_media_info(&pinfo)) {
        printf("\n[Error] %s %d  get media info fail\n", __func__, __LINE__);
        goto err1;
    }

    pcm_data = calloc(1, 8192);
    if (!pcm_data) {
        puts("\n pcm_data malloc fail\n");
        goto err1;
    }

//
    /* printf("\n  pinfo.info.video_sample_count = %d  pinfo.info.audio_chunk_num = %d\n", pinfo.info.video_sample_count, pinfo.info.audio_chunk_num); */

    uint64_t file_create_time = covBeijing2UnixTimeStp(&pinfo.time);
    int offset_time = p->start_time - file_create_time;
    i = avi_get_fps(pinfo.fd, pinfo.state) * offset_time;
    j = (1000 / 200) * offset_time; // 200ms
    /* printf("\n>>>>> i = %d j = %d offset_time = %d\n", i, j, offset_time); */
    while (1) {
        if (p->kill_flag) {
            break;
        }

        if (send_audio_flag) {
            /*send  audio*/
            if (pinfo.info.video_sample_count && pinfo.info.audio_chunk_num && audio_remain == 0) {
                if (j < pinfo.info.audio_chunk_num) {

                    ret = avi_audio_get_frame(pinfo.fd, j, pcm_data,   8192, pinfo.state);
                    audio_remain = ret;
                }
            }
            /* printf("send_audio_flag:%d  audio_remain:%d\n", send_audio_flag, audio_remain); */
            send_audio_flag = 0;
            if (audio_remain > 0) {
                a_send_time = get_utc_ms();
                int audio_len = audio_remain > AUDIO_PACKET_LEN ? AUDIO_PACKET_LEN : audio_remain;
                /* printf("AUDIO_INTERVAL:%d,%d\n", AUDIO_INTERVAL, j); */
                if (fast_ctrl <= 1) {
                    putchar('A');
                    ret = avsdk_write_history_audio(conn_id, E_IOT_MEDIASTREAM_TYPE_PCM, 0, a_timestamp_ms, file_id, NULL, pcm_data + offset, audio_len); //Ã¿´Î·¢1024£¬²»Ö§³Ö·¢´ó°ü
                    if (ret == -9) {
                        goto err1;
                    }
                }
                audio_remain -= audio_len;
                offset += audio_len;
                if (audio_remain == 0) {
                    j++;
                    offset = 0;
                }
            }
            a_timestamp_ms += AUDIO_INTERVAL;
        }


        if (send_video_flag) {
            send_video_flag  = 0;



            char *buffer = NULL;
            buffer = (char *)pinfo.data;

            ret = avi_video_get_frame(pinfo.fd, i, buffer,    pinfo.len, pinfo.state); //全回放功能获取帧
            v_send_time = get_utc_ms();
            if (ret > 0) {
                putchar('V');
                ret = avsdk_write_history_video(conn_id, E_IOT_MEDIASTREAM_TYPE_MJPEG, 1, 0, v_timestamp_ms, file_id, NULL, buffer, ret);
            }


            v_timestamp_ms += VIDEO_INTERVAL;
            /* printf("VIDEO_INTERVAL:%d\n", VIDEO_INTERVAL); */
            i++;
            if (i >= pinfo.info.video_sample_count) {
                uint64_t start_time = file_create_time + i / avi_get_fps(pinfo.fd, pinfo.state) ;
                uint64_t end_time = file_create_time + 86400 - (file_create_time % 86400);

                file_id = cloud_playback_file_next(start_time, end_time);
                if (file_id < 0) {
                    printf("end\n");
                    break;
                }

                if (pinfo.fd != NULL) {
                    avi_net_unpkg_exit(pinfo.fd, pinfo.state);
                    fclose(pinfo.fd);
                    pinfo.fd = NULL;
                }
                struct tm prev_time = {0};
                memcpy(&prev_time, &pinfo.time, sizeof(struct tm));

#if NAME_FILE_BY_DATE
                char time_str[64] = {0};
                u8 dir_len = 0;
                struct tm timeinfo = {0};
                time_t timestamp = file_id;
                localtime_r(&timestamp, &timeinfo);
                strcpy(time_str, CONFIG_REC_PATH_0);
                dir_len = strlen(time_str);
                strftime(time_str + dir_len, sizeof(time_str) - dir_len, "VID_%Y%m%d_%H%M%S.AVI", &timeinfo);
                log_i("recorder file name : %s\n", time_str);

                memcpy(file_name, time_str, sizeof(time_str));


                /* printf("\nfile_name = %s \n", file_name); */
                printf("\nplay next file_name = %s \n", file_name);

                char path_file[128];
                int len;

                len = long_file_name_encode(file_name, (u8 *)path_file, sizeof(path_file));
                memcpy(file_name, path_file, len);
#else
                snprintf(file_name, sizeof(file_name), "%sVID_%04d.AVI", CONFIG_REC_PATH_0, file_id);
                printf("\nplay next file_name = %s \n", file_name);
#endif

                pinfo.fd =  fopen(file_name, "r");
                avi_net_playback_unpkg_init(pinfo.fd, pinfo.state);
                update_data(&pinfo);

                file_create_time = covBeijing2UnixTimeStp(&pinfo.time);

                a_timestamp_ms = v_timestamp_ms = file_create_time * 1000;
                ////////////////////////////////

                if ((pinfo.time.tm_year == prev_time.tm_year) && (pinfo.time.tm_mon == prev_time.tm_mon) && (pinfo.time.tm_mday == prev_time.tm_mday)) {

                    /* printf("Same day\n"); */
                } else {
                    /* printf("Different day\n"); */
                    break;

                }

                i = 0;
                j = 0;


            }

        }



        if ((get_utc_ms() - v_send_time) >= VIDEO_INTERVAL - 20) {
            send_video_flag = 1;
        }
        if ((get_utc_ms() - a_send_time) >= AUDIO_INTERVAL) {
            send_audio_flag = 1;
        }
        if (!send_video_flag && !send_audio_flag) {
            os_time_dly(1);
        }
    }

err1:
//    fclose(fd);
    if (pinfo.info.stco_tab != NULL) {
        free(pinfo.info.stco_tab);
        pinfo.info.stco_tab = NULL;
    }
    if (pinfo.info.stsz_tab != NULL) {
        free(pinfo.info.stsz_tab);
        pinfo.info.stsz_tab = NULL;
    }
    if (pinfo.info.audio_stco_tab != NULL) {
        free(pinfo.info.audio_stco_tab);
        pinfo.info.audio_stco_tab = NULL;
    }


    avi_net_unpkg_exit(pinfo.fd, pinfo.state);
    if (pinfo.fd != NULL) {
        fclose(pinfo.fd);
        pinfo.fd = NULL;
    }
    if (pinfo.data) {
        free(pinfo.data);
    }
    if (pcm_data) {
        free(pcm_data);
    }
    pinfo.data = NULL;
}



int cloud_playback_init(int32_t conn_id,  uint64_t file_id, int64_t start_time)
{
    static int count;
    char name[32];

    CLOUD_PLAYBACK_INFO *p = calloc(1, sizeof(CLOUD_PLAYBACK_INFO));
    if (p) {
        p->conn_id = conn_id;
        p->file_id = file_id;
        p->start_time = start_time;

        /* printf("\n  p->file_id  = %llu   p->start_time = %lld\n", p->file_id, p->start_time); */
    } else {
        return -1;
    }

    snprintf(p->task_name, sizeof(p->task_name), "cloud_playback_task%d", count++);
    thread_fork(p->task_name, 8, 0x1000, 0, &p->task_id, cloud_playback_task, p);


    os_mutex_pend(&cloud_playback_mutex, 0);
    list_add_tail(&p->entry, &cloud_playback_list_head);
    os_mutex_post(&cloud_playback_mutex);
    return 0;
}

int cloud_playback_uninit(int32_t conn_id,  uint64_t file_id)
{
    CLOUD_PLAYBACK_INFO *p;
    struct list_head *pos = NULL, *node = NULL;
    os_mutex_pend(&cloud_playback_mutex, 0);
    if (list_empty(&cloud_playback_list_head)) {
        os_mutex_post(&cloud_playback_mutex);
        return 0;
    }
    list_for_each_safe(pos, node, &cloud_playback_list_head) {
        p = list_entry(pos, CLOUD_PLAYBACK_INFO, entry);
        if (p) {
            if (p->conn_id == conn_id) {
                list_del(&p->entry);
                p->kill_flag = 1;
                thread_kill(&p->task_id, 0);
                free(p);
                break;
            }
        }
    }
    os_mutex_post(&cloud_playback_mutex);

    return 0;
}
int cloud_playback_mutex_init(void)
{
    return os_mutex_create(&cloud_playback_mutex);
}
late_initcall(cloud_playback_mutex_init);

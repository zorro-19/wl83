#include "packet.h"
#include "app_config.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"


int send_date_packet(struct __packet_info *pinfo, u32 msec);

int get_video_media_info(struct __packet_info *pinfo)
{
    char buf[64];
    u32  nlen = 0;
    struct vfs_attr attr;
    fget_attrs(pinfo->fd, &attr);

    pinfo->time.tm_year = attr.crt_time.year;
    pinfo->time.tm_mon  = attr.crt_time.month;
    pinfo->time.tm_mday = attr.crt_time.day;
    pinfo->time.tm_hour = attr.crt_time.hour;
    pinfo->time.tm_min  = attr.crt_time.min;
    pinfo->time.tm_sec  = attr.crt_time.sec;
#if 0
    printf("start=%d-%d-%d-%d-%d-%d\n"
           , pinfo->time.tm_year
           , pinfo->time.tm_mon
           , pinfo->time.tm_mday
           , pinfo->time.tm_hour
           , pinfo->time.tm_min
           , pinfo->time.tm_sec);
#endif

    /*if (strstr(pinfo->file_name, get_rec_path_1())) {*/
    /*fget_name(pinfo->fd, (u8 *)pinfo->file_name + strlen(get_rec_path_1()), 48);*/
    /*} else if (strstr(pinfo->file_name, get_rec_path_2())) {*/
    /*fget_name(pinfo->fd, (u8 *)pinfo->file_name + strlen(get_rec_path_2()), 48);*/
    /*}*/
    /*printf("pinfo->file_name=%s\n", pinfo->file_name); */
#ifdef CONFIG_NET_PKG_H264
    read_time_scale_dur(pinfo->fd, &pinfo->info);
    read_height_and_length(pinfo->fd, &pinfo->info);
    read_stts(pinfo->fd, &pinfo->info);
    pinfo->info.sample_rate = get_audio_sample_rate(pinfo->fd);
    if (pinfo->info.sample_rate == -1) {
        return -1;
    }
    if (is_has_audio(pinfo->fd)) {
        u32 count = get_audio_sample_count(pinfo->fd);
        if (count == -1) {
            return -1;
        }

        pinfo->info.audio_chunk_num = get_audio_chunk_offset_entry(pinfo->fd);
        if (pinfo->info.audio_chunk_num == -1) {
            return -1;
        }
        pinfo->info.audio_block_size = (count * 2) / pinfo->info.audio_chunk_num;
        /* printf("audio block size -> %d\n", pinfo->info.audio_block_size); */
        /* printf("audio size  -> %d\n", (count * 2) / pinfo->info.audio_chunk_num); */
        pinfo->info.audio_stco_tab = get_audio_chunk_table(pinfo->fd, &pinfo->info);
        if (pinfo->info.audio_stco_tab == NULL) {
            return -1;
        }
    }

    /* printf("weight:%d  height :%d  durition:%d \n", pinfo->info.length >> 16, pinfo->info.height >> 16, pinfo->info.durition / pinfo->info.scale); */
    //get table

    pinfo->info.stco_tab = get_chunk_index_table(pinfo->fd, &pinfo->info);
    pinfo->info.stsz_tab = get_sample_index_table(pinfo->fd, &pinfo->info);
    if (pinfo->info.stco_tab == NULL && pinfo->info.stsz_tab == NULL) {
        printf(" pinfo->info.stco_tab == NULL\n\n");
        return -1;
    }
#endif

#ifdef CONFIG_NET_PKG_JPEG
    pinfo->info.scale = 1;
    pinfo->info.durition = avi_get_file_time(pinfo->fd, pinfo->state);
    pinfo->info.sample_rate = avi_get_audio_sample_rate(pinfo->fd, pinfo->state);
    pinfo->info.sample_duration = avi_get_fps(pinfo->fd, pinfo->state);
    pinfo->info.video_sample_count = avi_get_video_chunk_num(pinfo->fd, pinfo->state);
    pinfo->info.audio_chunk_num = avi_get_audio_chunk_num(pinfo->fd, pinfo->state);
    avi_get_width_height(pinfo->fd, (void *)&pinfo->info, pinfo->state);
    if (pinfo->info.sample_rate == -1) {
        return -1;
    }
#endif

    return 0;
}


int send_video_packet(struct __packet_info  *pinfo, u32 i)
{
    int ret;
    u32 tmp ;
    char *buffer = NULL;
    u32 tmp2;
    u32 start_code = 0x01000000;
    u32 send_len = 0;
    int flen;

    struct frm_head *frame_head = (struct frm_head *)pinfo->data;
    memset(frame_head, 0, sizeof(struct frm_head));

#ifdef CONFIG_NET_PKG_H264
    int sample_size = get_sample_size(pinfo->info.stsz_tab, i);
    if (sample_size == -1) {
        return -1;
    }
    int sample_offset = get_chunk_offset(pinfo->info.stco_tab, i);
    if (sample_offset == -1) {
        return -1;
    }
    if (sample_size > pinfo->len) {
        printf("I frame size:0x%x   offset:0x%x buffer size:%d\n", sample_size, sample_offset, pinfo->len);
        ASSERT(!(sample_size > pinfo->len), "I frame is too large");
    }
    fseek(pinfo->fd, sample_offset, SEEK_SET);

    frame_head->type = pinfo->type ;//| pinfo->fast_play_mask;
//   frame_head->type = H264_TYPE_VIDEO;
    frame_head->seq = i;

    /* printf("video seq=%d\n", frame_head->seq); */
    frame_head->timestamp = 90000 / (pinfo->info.scale / pinfo->info.sample_duration);


    ret = fread(pinfo->fd, pinfo->data + sizeof(struct frm_head), sample_size);
    if (ret <= 0) {
        return ret;
    }
    frame_head->frm_sz = ret;
    buffer = (char *)pinfo->data + sizeof(struct frm_head);
    if (*((char *)(buffer + 4)) == 0x67) {
        //处理PPS帧和SPS帧 I帧
        memcpy(&tmp, buffer, 4);
        tmp = htonl(tmp);
        memcpy(buffer, &start_code, 4);
        memcpy(&tmp2, buffer + tmp + 4, 4);
        tmp2 = htonl(tmp2);
        memcpy(buffer + tmp + 4, &start_code, 4);
        memcpy(buffer + tmp + tmp2 + 8, &start_code, 4);
        //printf("tmp %d  tmp2 %d\n",tmp,tmp2);
        //printf("&&&&&& video-I seq = %d\n",i);
    } else {
        //	   处理P帧
        memcpy(buffer, &start_code, 4);
    }
    ret = sock_send(pinfo->sock, (char *)pinfo->data, ret + sizeof(struct frm_head), 0);
    return ret;
#endif

#ifdef CONFIG_NET_PKG_JPEG
    /*frame_head->type = PREVIEW_TYPE;*/
    frame_head->type = pinfo->type;// | pinfo->fast_play_mask;
    frame_head->seq = i;
    /* printf("video seq=%d\n", frame_head->seq); */
    frame_head->timestamp = 90000 / avi_get_fps(pinfo->fd, pinfo->state);

#if 0
    flen = avi_video_set_frame_addr(pinfo->fd, frame_head->seq + 1, pinfo->state);
    if (flen <= 0) {
        return flen;
    }
    frame_head->frm_sz = flen;
    ret = sock_send(pinfo->sock, (char *)pinfo->data, sizeof(struct frm_head), 0);
    if (ret <= 0) {
        return ret;
    }

    while (flen > 0) {
        ret = fread(pinfo->fd, pinfo->data, MIN(flen, IMAGE_SIZE));
        if (ret <= 0) {
            return ret;
        }
        flen -= ret;
        ret = sock_send(pinfo->sock, (char *)pinfo->data, ret, 0);
        if (ret <= 0) {
            return ret;
        }
        send_len += ret;
    }
    return send_len;
#else
    /*printf("get video frame...\n");*/
    pinfo->data_len = pinfo->len - sizeof(struct frm_head);
    flen = avi_video_get_frame(pinfo->fd, frame_head->seq + 1, pinfo->data + sizeof(struct frm_head), pinfo->data_len,  pinfo->state);
    if (flen <= 0) {
        return flen;
    }
    if (!pinfo->state) {
        printf("get video frame ok...\n");
    }
    frame_head->frm_sz = flen;
    ret = sock_send(pinfo->sock, (char *)pinfo->data, flen + sizeof(struct frm_head), 0);
    return ret;
#endif
#endif

    return ret;
}

int send_audio_packet(struct __packet_info *pinfo, u32 j)
{
    int ret;
    static u32 tmp = 0;
    static u32 tmp2 = 0;
    struct frm_head *frame_head = (struct frm_head *)pinfo->data;

#ifdef CONFIG_NET_PKG_H264
    int audio_offset = get_audio_chunk_offset(pinfo->info.audio_stco_tab, j);
    if (audio_offset == -1) {
        return -1;
    }
    if (false == fseek(pinfo->fd, audio_offset, SEEK_SET)) {
        return -1;
    }

    tmp = frame_head->seq;
    frame_head->type = PCM_TYPE_AUDIO;
    frame_head->frm_sz = pinfo->info.audio_block_size;
    ret = fread(pinfo->fd, pinfo->data + sizeof(struct frm_head), pinfo->info.audio_block_size);
    if (ret <= 0) {
        return ret;
    }
    ret = sock_send(pinfo->sock, (char *)pinfo->data, ret + sizeof(struct frm_head), 0);
    tmp2++;
    if (tmp2 == pinfo->info.audio_chunk_num) {
        tmp = 0;
    }
#endif

#ifdef CONFIG_NET_JPEG
    pinfo->data_len = pinfo->len - sizeof(struct frm_head);
    ret = avi_audio_get_frame(pinfo->fd, j + 1, pinfo->data + sizeof(struct frm_head),  pinfo->data_len, pinfo->state);
    if (ret <= 0) {
        return ret;
    }
    pinfo->info.audio_block_size = ret;
    frame_head->type = PCM_TYPE_AUDIO;
    frame_head->frm_sz = pinfo->info.audio_block_size;
    ret = sock_send(pinfo->sock, (char *)pinfo->data, ret + sizeof(struct frm_head), 0);
#endif
    return ret;
}

void incr_date_time(struct tm *tm_time, int incr)
{
    do {
        if (incr >= 60) {
            tm_time->tm_sec += 60;
            incr -= 60;
        } else {
            tm_time->tm_sec += incr;
            incr = 0;
        }

        if (tm_time->tm_sec > 59) {
            tm_time->tm_sec -= 60;
            tm_time->tm_min += 1;

            if (tm_time->tm_min > 59) {
                tm_time->tm_min -= 60;
                tm_time->tm_hour += 1;

                if (tm_time->tm_hour > 23) {
                    tm_time->tm_hour -= 24;
                    tm_time->tm_mday += 1;

                    if (tm_time->tm_mday > cal_days(tm_time->tm_year, tm_time->tm_mon)) {
                        tm_time->tm_mday = 1;
                        tm_time->tm_mon += 1;

                        if (tm_time->tm_mon > 12) {
                            tm_time->tm_mon = 1;
                            ++tm_time->tm_year;
                        }
                    }
                }
            }
        }
    } while (incr);
}
u32 conver_date_time(struct tm *tm_time)
{
    u32 date_time;

    date_time = tm_time->tm_sec;
    date_time |= tm_time->tm_min << 6;
    date_time |= tm_time->tm_hour << 12;
    date_time |= tm_time->tm_mday << 17;
    date_time |= tm_time->tm_mon << 22;
    date_time |= (tm_time->tm_year - 2015) << 26;

    return date_time;
}

int send_media_packet(struct __packet_info *pinfo)
{
    /* puts("send_media_packet\n"); */
    int ret = 0;
    char name[32] = {0};

    struct frm_head *frame_head = (struct frm_head *)pinfo->data;
    memset(frame_head, 0, sizeof(struct frm_head) + sizeof(struct media_info));
    //send media info packet
    frame_head->type = MEDIA_INFO_TYPE;
    frame_head->seq = 0;


    struct media_info *media = (struct media_info *)(pinfo->data + sizeof(struct frm_head));
#ifdef  CONFIG_NET_PKG_H264
    media->length = pinfo->info.length >> 16;
    media->height = pinfo->info.height >> 16;
    media->fps    = pinfo->info.scale / pinfo->info.sample_duration;
#endif
#ifdef  CONFIG_NET_PKG_JPEG
    media->length = pinfo->info.length;
    media->height = pinfo->info.height;
    media->fps    = pinfo->info.sample_duration;
#endif
    media->audio_rate   = pinfo->info.sample_rate;

    media->dur_time = pinfo->info.durition / pinfo->info.scale;


    /* printf("fps = %d\n",media->fps); */

    /*printf("=====media->dur_time=%d\n", media->dur_time);*/
    strcpy(media->filename, pinfo->file_name);
    /* strcpy(pinfo->data + sizeof(struct frm_head) + sizeof(struct media_info),pinfo->file_name); */
    size_t len = sizeof(struct frm_head) + sizeof(struct media_info)  + strlen(pinfo->file_name);
    frame_head->frm_sz = len - sizeof(struct frm_head);

    ret = sock_send(pinfo->sock, (char *)pinfo->data, len, 0);
    if (ret <= 0) {
        return ret;
    }
    ret = send_date_packet(pinfo, 0);//发送起始时间包
    return ret;
}
int send_date_packet(struct __packet_info *pinfo, u32 msec)
{
    int ret = 0;
    u32 date = 0;
    struct tm tm_time;
#if (defined  CONFIG_NET_PKG_H264 || defined  CONFIG_NET_PKG_JPEG)
    struct frm_head *frame_head = (struct frm_head *)pinfo->data;
    frame_head->type = DATE_TIME_TYPE;
    frame_head->frm_sz = 4;
    incr_date_time(&pinfo->time, msec);
    date = conver_date_time(&pinfo->time);

    if (!msec) {
        printf("file start timer : %d-%d-%d-%d-%d-%d\n"
               , pinfo->time.tm_year
               , pinfo->time.tm_mon
               , pinfo->time.tm_mday
               , pinfo->time.tm_hour
               , pinfo->time.tm_min
               , pinfo->time.tm_sec);
    } else {
#if 1
        printf("xdt=%d-%d-%d-%d-%d-%d\n"
               , pinfo->time.tm_year
               , pinfo->time.tm_mon
               , pinfo->time.tm_mday
               , pinfo->time.tm_hour
               , pinfo->time.tm_min
               , pinfo->time.tm_sec);
#endif
    }

    memcpy(pinfo->data + sizeof(struct frm_head), &date, frame_head->frm_sz);

    ret = sock_send(pinfo->sock, (char *)pinfo->data, sizeof(struct frm_head) + 4, 0);
#endif
    return ret;
}
int send_end_packet(struct __packet_info *pinfo)
{
    puts("send_end_packet\n");
    int ret = 0;
    struct frm_head *frame_head = (struct frm_head *)pinfo->data;
    memset(frame_head, 0, sizeof(struct frm_head));
#if (defined CONFIG_NET_PKG_H264 || defined CONFIG_NET_PKG_JPEG)

    if (pinfo->fd == NULL) {
        puts("PLAY_OVER_TYPE | LAST_FREG_MAKER\n");
        frame_head->type = (PLAY_OVER_TYPE | LAST_FREG_MAKER);
    } else {

        puts("PLAY_OVER_TYPE\n");
        frame_head->type = PLAY_OVER_TYPE;
    }

    ret = sock_send(pinfo->sock, (char *)pinfo->data, sizeof(struct frm_head), 0);
#endif
    return ret;

}
int update_data(struct __packet_info *pinfo)
{

    if (pinfo->info.stco_tab != NULL) {
        free(pinfo->info.stco_tab);
        pinfo->info.stco_tab = NULL;
    }

    if (pinfo->info.stsz_tab != NULL) {
        free(pinfo->info.stsz_tab);
        pinfo->info.stsz_tab = NULL;
    }

    if (pinfo->info.audio_stco_tab != NULL) {
        free(pinfo->info.audio_stco_tab);
        pinfo->info.audio_stco_tab = NULL;
    }
#if 0
    if (pinfo->fd != NULL) {
        fclose(pinfo->fd);
        pinfo->fd = NULL;

    }
#endif

    return get_video_media_info(pinfo);
}




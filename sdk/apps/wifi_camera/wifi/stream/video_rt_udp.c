#include "sys_common.h"
#include "system/spinlock.h"
#include "os/os_api.h"
#include "server/rt_stream_pkg.h"
#include "app_config.h"
#include "lwip.h"
#include "lwip/sockets.h"
#include "sock_api/sock_api.h"
#include "os/os_api.h"
#include "stream_core.h"



/*
 UDP端口:2224
 UDP 每片数据包 格式:
|1byte 类型 |  1byte 保留 | 2byte  payload长度 | 4byte 序号 |  4byte  帧大小 |  4byte 偏移  | 4byte 时间戳  |  payload  |
*/
#define UDP_SEND_BUF_SIZE  (4*1460)
/* #define CONFIG_UDP_STREAM_DROP1_ENABLE */
#define CONFIG_UDP_STREAM_DROP2_ENABLE

#ifdef CONFIG_UDP_STREAM_DROP2_ENABLE
static u32 drop_counter_lcm = 0;
static u32 original_fps = 25; // 原始帧率
static u32 target_fps = 18;   // 目标帧率
static u32 lcm_threshold = 0;//lcm(original_fps, target_fps);
static u32 lcm_drop_step = 0;//lcm_threshold - (u32)((double)target_fps / original_fps * lcm_threshold);


// 辅助函数：计算最大公约数 (GCD) - 辗转相除法
u32 gcd(u32 a, u32 b)
{
    while (b != 0) {
        u32 temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 计算最小公倍数 (LCM)
u32 lcm(u32 a, u32 b)
{
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a * b) / gcd(a, b);
}


#endif


#define MAX_PAYLOAD (1460-sizeof(struct frm_head))//最后4字节属于h264流的

static u32 video_timestramp  = 0;
static u32 audio_timestramp  = 0;
static u32 seq = 1;
static u32 aux_frame_cnt = 0;
static u32 old_times = 0;
static u32 new_times = 0;
static struct rt_stream_info *rt_info = NULL;
extern int atoi(const char *__nptr);
extern int net_video_rec_get_list_vframe(void);
extern int net_video_buff_set_frame_cnt(void);

static int  path_analyze(struct rt_stream_info *info, const *path)
{

    char *tmp = NULL;
    char *tmp2 = NULL;
    char ip[15] = {0};
    u16 port = 0;
    tmp = strstr(path, "udp://");
    if (!tmp) {
        return -1;
    }

    tmp += strlen("udp://");

    tmp2 = strchr(tmp, ':');
    printf("tmp=%s  len=%d\n", tmp, tmp2 - tmp);
    strncpy(ip, tmp, tmp2 - tmp);
    port = atoi(tmp2 + 1);

    printf("remote ip:%s  port:%d\n", ip, port);


    info->addr.sin_family = AF_INET;
    info->addr.sin_addr.s_addr = inet_addr(ip);
    info->addr.sin_port = htons(port);
    return 0;

}

static int net_rt_pkg_udp_callback(enum sock_api_msg_type type, void *p)
{
    //缓存大于2帧丢帧
    struct rt_stream_info *info = (struct rt_stream_info *)p;
    int vcnt = net_video_rec_get_list_vframe();
    int set_cnt = net_video_buff_set_frame_cnt();
    if (vcnt > set_cnt && set_cnt > 0) {
        if (info) {
            info->cb_flag = 1;
        }
        return -1;
    }
    return 0;
}


static void *get_sock_handler(int (*cb_func)(enum sock_api_msg_type type, void *priv), void *priv)
{
    void *fd = NULL;


    if (0) { //条件链表
        //add P2P code
    } else {

        fd = sock_reg(AF_INET, SOCK_DGRAM, 0, cb_func, priv);

        if (fd == NULL) {
            printf("%s %d->Error in socket()\n", __func__, __LINE__);
            return NULL;
        }

        u32 millsec = 100;
        sock_setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (const void *)&millsec, sizeof(millsec));
        return fd;
    }
}

struct rt_stream_info *net_rt_vpkg_open(const char *path, const char *mode)
{

    int flags = 0;
    int err;
    struct rt_stream_info *info = (struct rt_stream_info *)calloc(1, sizeof(struct rt_stream_info));

    if (info == NULL) {
        printf("%s %d->Error in malloc()\n", __func__, __LINE__);
        return NULL;
    }

    os_mutex_create(&info->mutex);

    info->udp_send_buf = (char *)malloc(UDP_SEND_BUF_SIZE);

    if (info->udp_send_buf == NULL) {
        printf("%s %d->Error in malloc()\n", __func__, __LINE__);
        free(info);
        return NULL;
    }

    if (path_analyze(info, path)) {

        printf("%s %d->Error in path_analyze\n", __func__, __LINE__);
        free(info);
        return NULL;
    }

    info->fd = get_sock_handler(net_rt_pkg_udp_callback, info);
    if (!info->fd) {
        printf("%s %d->Error get_sock_handler\n", __func__, __LINE__);
        free(info);
        return NULL;
    }
#ifdef CONFIG_UDP_STREAM_DROP2_ENABLE
    lcm_threshold = lcm(original_fps, target_fps);
    lcm_drop_step = lcm_threshold - (u32)((double)target_fps / original_fps * lcm_threshold);
#endif

    rt_info = info;
    return info;
err1:
    free(info->udp_send_buf);
    free(info);
    return NULL;
}
int net_rt_vpkg_write(struct rt_stream_info *info, char *buffer, size_t len, struct sockaddr *addr, int addrlen)
{
    /* struct sockaddr_in * addr2 = (struct sockaddr_in *)addr; */
    return sock_sendto(info->fd, buffer, len, 0, addr, addrlen);
}

int net_rt_vpkg_close(struct rt_stream_info *info)
{
    video_timestramp = 0;
    audio_timestramp = 0;
    aux_frame_cnt = 0;
    os_mutex_del(&info->mutex, OS_DEL_ALWAYS);
    if (info->fd) {
        sock_unreg(info->fd);
    }
    if (info->udp_send_buf) {
        free(info->udp_send_buf);
    }
    free(info);

    rt_info = NULL;
    return 0;
}

int UDP_client_socket_unreg(int addr)
{
    if (rt_info) {
        printf("UDP_client_socket_quit , addr 0x%x , 0x%x\n", rt_info->addr.sin_addr.s_addr, addr);
        if (rt_info->addr.sin_addr.s_addr == addr) {
            video_timestramp = 0;
            audio_timestramp = 0;
            aux_frame_cnt = 0;
            sock_set_quit(rt_info->fd);
            sock_unreg(rt_info->fd);
            rt_info->fd = NULL;
            rt_info = NULL;
            return 0;
        }
    }
    return -1;
}




int net_rt_send_frame(struct rt_stream_info *info, char *buffer, size_t len, u8 type)
{
    u16 payload_len = 0;
    u32 total_udp_send = 0;
    struct frm_head frame_head = {0};
    u32 change_data = 0x01000000;
    u32 tmp, tmp2, tmp3;
    int ret;

    u32 remain_len = len;

    ret = os_mutex_pend(&info->mutex, 400);
    if (ret < 0) {
        return -1;
    }

    if (info == NULL || info->udp_send_buf == NULL || info->fd == NULL) {
        printf("use net_rt_stream_open_pkg\n");
        os_mutex_post(&info->mutex);
        return -1;
    }

    if (len <= 556) {
        os_mutex_post(&info->mutex);
        return len;
    }

#ifdef CONFIG_UDP_STREAM_DROP1_ENABLE



    static u32 drop_counter = 0; // 静态变量，记录计数器状态
    static const u32 drop_threshold = 25; // 阈值，代表原始帧率 (近似)
    static const u32 drop_step = 7;      // 步进值，每 25 帧丢弃 7 帧 (25-18=7)

    drop_counter += drop_step; // 计数器累加步进值   // 3
    if (drop_counter >= drop_threshold) {
        // 计数器超过阈值，需要丢帧
        drop_counter -= drop_threshold; // 计数器减去阈值，保持在合理范围内
        putchar('D'); // 可以保留 'D' 输出作为丢帧标记 (调试用)
        os_mutex_post(&info->mutex); // 释放互斥锁
        return len; // 直接返回，相当于丢弃当前帧，不再进行后续的发送处理
    }
    // 如果 drop_counter < drop_threshold，则不丢帧，继续正常发送流程
#endif

#ifdef CONFIG_UDP_STREAM_DROP2_ENABLE
    drop_counter_lcm += lcm_drop_step;
    if (drop_counter_lcm >= lcm_threshold) {
        drop_counter_lcm -= lcm_threshold;
        putchar('L');
        os_mutex_post(&info->mutex);
        return len;
    }
#endif


    //缓存大于2帧丢帧
    int vcnt = net_video_rec_get_list_vframe();
    int set_cnt = net_video_buff_set_frame_cnt();
    if (vcnt > set_cnt && set_cnt > 0) {
        os_mutex_post(&info->mutex);
        return len;
    }

    info->cb_flag = 0;

    frame_head.offset = 0;
    frame_head.frm_sz = len;
    frame_head.type &= ~LAST_FREG_MAKER;
    frame_head.type |=  type;
    if (frame_head.type == H264_TYPE_VIDEO || frame_head.type == JPEG_TYPE_VIDEO) {
        if (len == 512) {
            if (buffer[8] == 0xab & buffer[9] == 0x56) {
                os_mutex_post(&info->mutex);
                return len;
            }
        }

        //video_timestramp += 90000 / VIDEO_FRQ_30HZ;
        new_times = timer_get_ms();

        if (aux_frame_cnt < 60) {
            video_timestramp = 0;
        } else {
            video_timestramp += 0;//(new_times - old_times) * 100;
        }

        /* printf("p=%d\n",new_times-old_times); */
        old_times = new_times;
        frame_head.timestamp = video_timestramp;

    } else {
        audio_timestramp = 501;
        frame_head.timestamp = audio_timestramp;
    }
    frame_head.timestamp = 0;
    frame_head.seq = seq++;

    while (remain_len) {
        if (remain_len < MAX_PAYLOAD) {
            payload_len = remain_len;
            frame_head.type |= LAST_FREG_MAKER;
        } else {
            payload_len = MAX_PAYLOAD;
        }

        frame_head.payload_size = payload_len;
        memcpy(info->udp_send_buf + total_udp_send, &frame_head, sizeof(struct frm_head));
        total_udp_send += sizeof(struct frm_head);

        memcpy(info->udp_send_buf + total_udp_send, buffer + frame_head.offset, payload_len);
        if (frame_head.offset  == 0 &&
            frame_head.type == H264_TYPE_VIDEO) {
            if (*((char *)(info->udp_send_buf + total_udp_send + 4)) == 0x67) {
                //处理PPS帧和SPS帧 I帧
                memcpy(&tmp, info->udp_send_buf + total_udp_send, 4);
                tmp = htonl(tmp);
                memcpy(info->udp_send_buf + total_udp_send, &change_data, 4);
                memcpy(&tmp2, info->udp_send_buf + total_udp_send + tmp + 4, 4);
                tmp2 = htonl(tmp2);
                memcpy(info->udp_send_buf + total_udp_send + tmp + 4, &change_data, 4);
                memcpy(info->udp_send_buf + total_udp_send + tmp + tmp2 + 8, &change_data, 4);

            } else {
                //	   处理P帧
                memcpy(info->udp_send_buf + total_udp_send, &change_data, 4);
            }

        }

        total_udp_send += payload_len;

        if ((total_udp_send == UDP_SEND_BUF_SIZE) || (payload_len < MAX_PAYLOAD)) {
            if ((ret = net_rt_vpkg_write(info, info->udp_send_buf, total_udp_send, (struct sockaddr *)&info->addr, sizeof(struct sockaddr_in))) != total_udp_send) {

                if (info->cb_flag) {
                    os_mutex_post(&info->mutex);
                    return len;
                }
                /* printf("ret:%d    total_udp_send:%d\n", ret, total_udp_send); */
                puts("rt_stream_sent error!\n");
                os_mutex_post(&info->mutex);
                return -1;

            }

            total_udp_send = 0;
        }

        remain_len -= payload_len;
        frame_head.offset += payload_len;
    }

    os_mutex_post(&info->mutex);
    return len;
}


REGISTER_NET_VIDEO_STREAM_SUDDEV(udp_video_stream_sub) = {
    .name = "udp",
    .open = net_rt_vpkg_open,
    .write = net_rt_send_frame,
    .close = net_rt_vpkg_close,
};



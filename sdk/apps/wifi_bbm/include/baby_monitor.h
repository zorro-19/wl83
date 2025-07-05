#ifndef __BABY_MONITOR_H
#define __BABY_MONITOR_H

#include "system/includes.h"
#include "app_config.h"
#include "utils/uthash/uthash.h"

#define AUDIO_RX_ENC_SAMPLE_RATE   8000
#define AUDIO_RX_ENC_FRAME_SIZE    640*2       //每个音频包的大小，越大会导致延迟高
#define AUDIO_RX_ENC_BUF_MAX_LEN   AUDIO_RX_ENC_FRAME_SIZE * 64    //编码音频缓存

typedef struct {
    int file_no;             // 文件序号key
    UT_hash_handle hh;       // 哈希表句柄
} file_entry;

struct net_ctp_thumb {
    int start_index;
    int file_num;
    u8 **file_buf_list;
    int *file_buf_len_list;
    char file_name_buf[6][32];
    OS_SEM sem;
};

struct video_rec_config {
    u16 width;
    u16 height;

    u8 id;
    u8 sub_id;
    u8 fps;
    u16 abr_kbps;
    u8 cycle_time;

    u16 aud_interval_size;

    char *net_path;
    void *priv;
};

struct bbm_client_hdl {
    OS_SEM ctp_msg_sem;         //CTP接收消息同步信号量
    int ctp_msg_arg;
    void *ctp_cli_hdl;          //CTP句柄
    u32 ip_addr;                //CTP ip地址
    u32 ch;                     //设备通道号
    u16 alive_timer;

    //实时流/录像
    struct video_rec_config rt_config;      //实时流配置
    struct video_rec_config rec_config;     //录像配置

    u8 tx_is_recording;
    u8 rx_is_recording;

    //文件列表
    int ctp_get_file_task_pid;  //获取文件列表线程PID
    u8 ctp_get_file_task_exit;  //文件列表线程退出标记
    char **file_name_list;      //文件列表指针
    int  file_total_num;        //文件总数量
    char vf_list[128];          //虚拟文件路径，用于获取网络获取文件列表
    char local_path[128];       //本地SD卡路径
    u8 is_local_dev;            //本地设备标记
    struct vfscan *fs;          //本地文件扫描

    //缩略图
    int ctp_file_thumb_task_pid;    //缩略图获取线程PID
    u8 ctp_file_thumb_task_exit;    //缩略图线程退出标记
    char ctp_file_thumb_task_name[64];//缩略图线程名(taskq使用)

    //回放
    int ctp_file_play_task_pid;     //文件播放线程PID
    u8 ctp_file_play_task_exit;     //文件播放线程退出标记
    u8 video_play_state;            //播放状态
    int play_index;
};


enum {
    BBM_FILE_PLAY_STOP = 0,
    BBM_FILE_PLAY_START,
    BBM_FILE_PLAY_PAUSE,
    BBM_FILE_PLAY_RESUME,
    BBM_FILE_PLAY_DONE,
};

enum {
    RT_DISP_WIN_MAIN = 0,
    RT_DISP_WIN_LEFT,
    RT_DISP_WIN_RIGHT,
};

enum {
    FILE_PLAY_VIDEO_CONTINUE = 0,
    FILE_PLAY_VIDEO_PAUSE,
    FILE_PLAY_VIDEO_STOP,
};








#endif /* __BABY_MONITOR_H */


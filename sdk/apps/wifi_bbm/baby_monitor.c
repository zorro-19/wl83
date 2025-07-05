#include "system/includes.h"
#include "action.h"
#include "app_config.h"
#include "generic/log.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "lcd_config.h"
#include "net_event.h"
#include "udp_multicast.h"
#include "pairing_data_model.h"
#include "arp_static_table.h"
#include "baby_monitor.h"
#include "fs/fs.h"
#include "wifi/wifi_connect.h"
#include "video_ioctl.h"

#define DEVICE_ONLINE_TIMEOUT   2000            //设备在线超时时间

#define MAX_PAIR_NUM    MAX_ARP_STATIC_ENTRY    //最大配对数量
#define MIN_PAIR_CH     0                       //0
#define MAX_PAIR_CH     (MAX_PAIR_NUM - 1)      //6

#define RX_DEVICE_CH    MAX_PAIR_NUM

enum {
    BBM_TX_OFFLINE = 0,
    BBM_TX_ONLINE,
};

enum {
    BBM_RT_STOP = 100,
    BBM_RT_RESET,
    BBM_RT_START,
};

enum {
    BBM_MODE_IDLE = 0,
    BBM_MODE_STREAM = 10,
    BBM_MODE_FILE_BROWSER,
    BBM_MODE_VIDEO_PLAY,
};


struct wifi_bbm_hdl {
    u8 online_table[MAX_PAIR_NUM];          //设备在线表
    u8 online_dev_cnt;                      //设备当前在线数量
    u32 online_cnt_table[MAX_PAIR_NUM];     //设备在线包计数
    u32 online_timeout[MAX_PAIR_NUM];       //设备超时定时器
    int cur_channel;                        //当前通讯通道
    int last_opened_ch;                     //上一次开启的通道
    u8 bbm_cur_mode;                        //当前模式,实时流/文件预览/视频文件播放
    u8 is_pairing;

    struct bbm_client_hdl *bbm_client_hdl[MAX_PAIR_NUM + 1];        //设备client管理句柄
};
static struct wifi_bbm_hdl bbm_hdl;
#define __this (&bbm_hdl)

extern struct video_window disp_win_1[1];
extern struct video_window disp_win_2[2];
extern struct video_window disp_win_3[3];
extern struct video_window disp_win_4[4];

static int bbm_tx_sd_offline(void *priv)
{
    struct bbm_client_hdl *bbm_client_hdl = priv;
    int ch = bbm_client_hdl->ch;

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        if (bbm_client_hdl->tx_is_recording) {
            bbm_client_hdl->tx_is_recording = 0;
        }
        break;
    case BBM_MODE_FILE_BROWSER:
    case BBM_MODE_VIDEO_PLAY:
        if (__this->cur_channel & BIT(ch)) {
            post_home_msg_to_ui("back_home_page", 0);
            char *lab = "SD Card offline !";
            post_home_msg_to_ui("show_sys_prompt", lab);
            bbm_quit_cur_mode();
        }
        break;
    default:
        break;
    }
    bbm_clean_file_list(priv);
}

static int bbm_file_list_update(void *priv, char *fname)
{
    struct bbm_client_hdl *bbm_client_hdl = priv;
    char **new_file_name_list = NULL;
    int new_file_total_num = bbm_client_hdl->file_total_num + 1;
    int list_size = new_file_total_num * sizeof(char *);

    new_file_name_list = malloc(list_size);
    if (!new_file_name_list) {
        printf("new_file_name_list malloc err \n");
        return -1;
    }
    new_file_name_list[0] = (char *)malloc(strlen(fname) + 1);
    if (new_file_name_list[0]  == NULL) {
        printf("malloc failed for new_file_list[%d]\n", 0);
        free(new_file_name_list);
        return -1;
    }
    strcpy(new_file_name_list[0], fname);

    memcpy(new_file_name_list + 1,
           bbm_client_hdl->file_name_list,
           bbm_client_hdl->file_total_num * sizeof(char *));
    free(bbm_client_hdl->file_name_list);

    bbm_client_hdl->file_name_list  = new_file_name_list;
    bbm_client_hdl->file_total_num  = new_file_total_num;
    return 0;
}

static int bbm_file_list_create(void *priv)
{
    return bbm_ctp_file_init(priv);
}

static int bbm_path_to_ch(char *text)
{
    while (*text && !isdigit(*text)) {
        text++;
    }

    return atoi(text);
}

static int bbm_get_dir_num(char *dev_path)
{
    int i, ch, num = 0;
    char name[128];
    FILE *dir;
    struct vfscan *fs = NULL;

    if (strstr(dev_path, "storage")) {
        fs = fscan(CONFIG_DEC_ROOT_PATH, "-d -tPNGBINAVITTLDAT -sn", 2);
        if (!fs) {
            printf("fscan err!!");
            return 0;
        }
        dir = fselect(fs, FSEL_FIRST_FILE, 0);
        for (i = 0; i < fs->file_number; i++) {
            fget_name(dir, name, sizeof(name));
            printf("name %s\n", name);
            ch = bbm_path_to_ch(name);

            num |= BIT(ch);

            fclose(dir);
            dir = fselect(fs, FSEL_NEXT_FILE, 0);
        }
        fscan_release(fs);
    } else {
        for (i = 0; i < ARRAY_SIZE(__this->online_table); i++) {
            if (__this->online_table[i] == BBM_TX_ONLINE) {
                //在线设备的ch号对应的bit位置1
                num |= BIT(i);
            }
        }
    }

    //TODO
    /*     bbm_quit_cur_mode(); */
    /* __this->bbm_cur_mode = BBM_MODE_FILE_BROWSER; */

    return num;
}

static int bbm_get_file_num(int ch, int *num)
{
    if (!__this->bbm_client_hdl[ch]) {
        printf("client hdl invalid \n");
        return -1;
    }

    int total_num = __this->bbm_client_hdl[ch]->file_total_num;

    *num = total_num;

    if (!total_num) {
        printf("file total num 0 \n");
        return -1;
    }

    return 0;
}

static int bbm_get_file_name_list(int ch, char ***list)
{
    if (!__this->bbm_client_hdl[ch]) {
        printf("client hdl invalid \n");
        return -1;
    }

    char **name_list  = __this->bbm_client_hdl[ch]->file_name_list;

    *list = name_list;

    if (!name_list) {
        if (__this->bbm_client_hdl[ch]->is_local_dev) {
            //区分本机设备
            //拷贝文件名太占用时间
            printf("is local dev \n");
        } else {
            printf("file list is null !\n");
            return -1;
        }
    }

    return 0;
}

static int bbm_tx_start_rec_all(void)
{
    int ch;
    int ret;
    if (__this->bbm_cur_mode != BBM_MODE_STREAM) {
        printf("TX start rec err \n cur mode err :%d ", __this->bbm_cur_mode);
        return -1;
    }

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->online_table[ch] == BBM_TX_ONLINE) {
            if (__this->bbm_client_hdl[ch]->tx_is_recording) {
                printf("ch:%d Tx Device is recording ! \n", ch);
            } else {
                ret = bbm_ctp_rec_start(__this->bbm_client_hdl[ch]);
                if (ret) {
                    printf("ch:%d Tx Device start rec err \n", ch);
                } else {
                    __this->bbm_client_hdl[ch]->tx_is_recording = 1;
                }
            }
        }
    }

    return 0;
}

static int bbm_tx_stop_rec_all(void)
{
    int ch;
    int ret;
    if (__this->bbm_cur_mode != BBM_MODE_STREAM) {
        printf("TX stop rec err \n cur mode err :%d ", __this->bbm_cur_mode);
        return -1;
    }

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->online_table[ch] == BBM_TX_ONLINE) {
            if (__this->bbm_client_hdl[ch]->tx_is_recording) {
                ret = bbm_ctp_rec_stop(__this->bbm_client_hdl[ch]);
                if (ret) {
                    printf("ch:%d Tx Device stop rec err \n", ch);
                } else {
                    __this->bbm_client_hdl[ch]->tx_is_recording = 0;
                }
            } else {
                printf("ch:%d Tx Device  No video recording ! \n", ch);
            }
        }
    }

    return 0;
}

static int bbm_tx_start_rec_err(void *priv)
{
    struct bbm_client_hdl *bbm_client_hdl = priv;

    if (bbm_client_hdl->tx_is_recording) {
        bbm_client_hdl->tx_is_recording = 0;
    }

    return 0;
}

static int bbm_rx_start_rec_all(void)
{
    int ch;
    int ret;
    if (__this->bbm_cur_mode != BBM_MODE_STREAM) {
        printf("Rx start rec err \n cur mode err :%d \n", __this->bbm_cur_mode);
        return -1;
    }

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->online_table[ch] == BBM_TX_ONLINE) {
            if (__this->cur_channel & BIT(ch)) {
                if (__this->bbm_client_hdl[ch]->rx_is_recording) {
                    printf("ch:%d Rx Device is recording ! \n", ch);
                } else {
                    ret = bbm_rx_rec_start(__this->bbm_client_hdl[ch]);
                    if (ret) {
                        printf("ch:%d Rx Device start rec err \n", ch);
                    } else {
                        __this->bbm_client_hdl[ch]->rx_is_recording = 1;
                    }
                }
            } else {
                printf("rx start Rec err \n Please open the rt stream of ch:%d first !\n", ch);
            }
        }
    }

    return 0;
}

static int bbm_rx_stop_rec_all(void)
{
    int ch;
    int ret;
    if (__this->bbm_cur_mode != BBM_MODE_STREAM) {
        printf("Rx stop rec err \n cur mode err :%d ", __this->bbm_cur_mode);
        return -1;
    }

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->online_table[ch] == BBM_TX_ONLINE) {
            if (__this->cur_channel & BIT(ch)) {
                if (__this->bbm_client_hdl[ch]->rx_is_recording) {
                    ret = bbm_rx_rec_stop(__this->bbm_client_hdl[ch]);
                    if (ret) {
                        printf("ch:%d Rx Device stop rec err \n", ch);
                    } else {
                        __this->bbm_client_hdl[ch]->rx_is_recording = 0;
                    }
                } else {
                    printf("ch:%d Rx Device  No video recording ! \n", ch);
                }
            } else {
                printf("ch:%d Rx rec has stopped \n", ch);
            }
        }
    }

    return 0;
}


static int find_next_camera(int ch)
{
    int find_ch = ch;
    do {
        find_ch++;
        if (find_ch > MAX_PAIR_NUM) {
            find_ch = MIN_PAIR_CH;
        }

        //遍历了一圈没有找到可以用设备
        if (ch == find_ch) {
            printf("no available dev \n ");
            return -1;
        }

        if (__this->online_table[find_ch] == BBM_TX_ONLINE || find_ch == MAX_PAIR_NUM) {
            return find_ch;
        }
    } while (1);
}

static int find_any_online_camera(void)
{
    int ch;
    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->online_table[ch] == BBM_TX_ONLINE) {
            return ch;
        }
    }
    printf("no online camera device \n");
    return -1;
}

static int bbm_reset_camera_pipe_by_ch(int ch, int disp_mode)
{
    printf("rt stream reset:%d mode:%d \n", ch, disp_mode);
    int ret;

    ret = bbm_rt_stream_reset_pipe(__this->bbm_client_hdl[ch], disp_mode);
    if (ret) {
        printf("ch:%d rt stream start err\n", ch);
        return -1;
    }

    return 0;
}

static int bbm_start_camera_by_ch(int ch, struct video_window *win)
{
    printf("rt stream start:%d \n", ch);
    int ret;

    //可根据分辨率、码率调整
    if (win != &disp_win_1[0]) {
        bbm_ctp_send_modify_txrate(__this->bbm_client_hdl[ch]->ctp_cli_hdl, WIFI_TXRATE_11M);
    } else {
        bbm_ctp_send_modify_txrate(__this->bbm_client_hdl[ch]->ctp_cli_hdl, WIFI_TXRATE_11M);
    }

    ret = bbm_ctp_rt_start(__this->bbm_client_hdl[ch], win);
    if (ret) {
        printf("ch:%d rt stream start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_stop_camera_by_ch(int ch)
{
    if (__this->bbm_cur_mode != BBM_MODE_STREAM) {
        return 0;
    }

    printf("rt stream stop:%d \n", ch);
    int ret;

    ret = bbm_ctp_rt_stop(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d rt stream stop err\n", ch);
    }
    __this->cur_channel &= ~BIT(ch);

    return 0;
}

static int bbm_start_thumb_by_ch(int ch)
{
    printf("file thumb start:%d \n", ch);
    int ret;

    bbm_ctp_send_modify_txrate(__this->bbm_client_hdl[ch]->ctp_cli_hdl, WIFI_TXRATE_11M);
    ret = ctp_file_thumb_start(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d file thumb start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_stop_thumb_by_ch(int ch)
{
    if (__this->bbm_cur_mode != BBM_MODE_FILE_BROWSER) {
        return 0;
    }

    printf("rt thumb stop:%d \n", ch);
    int ret;

    ret = ctp_file_thumb_stop(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d thumb stop err\n", ch);
        return -1;
    }
    __this->cur_channel &= ~BIT(ch);

    return 0;
}

static int bbm_start_file_play_by_ch(int ch, int arg)
{
    printf("file play start:%d \n", ch);
    int ret;

    bbm_ctp_send_modify_txrate(__this->bbm_client_hdl[ch]->ctp_cli_hdl, WIFI_TXRATE_11M);
    ret = bbm_file_play_start(__this->bbm_client_hdl[ch], arg);
    if (ret) {
        printf("ch:%d file play start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_switch_file_play_by_ch(int ch, int arg)
{
    printf("file play switch:%d \n", ch);
    int ret;

    ret = bbm_file_play_switch(__this->bbm_client_hdl[ch], arg);
    if (ret) {
        printf("ch:%d file play start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_stop_file_play_by_ch(int ch)
{
    if (__this->bbm_cur_mode != BBM_MODE_VIDEO_PLAY) {
        return 0;
    }

    printf("rt play stop:%d \n", ch);
    int ret;

    ret = bbm_file_play_stop(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d file play stop err\n", ch);
        return -1;
    }
    __this->cur_channel &= ~BIT(ch);

    return 0;
}

static int bbm_stop_file_play_all(void)
{
    int ret = 0;
    int ch;

    //+1本机
    for (ch = 0; ch < MAX_PAIR_NUM + 1; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            ret = bbm_stop_file_play_by_ch(ch);
        }
    }

    return ret;
}

static int bbm_stop_thumb_all(void)
{
    int ret = 0;
    int ch;

    //+1本机
    for (ch = 0; ch < MAX_PAIR_NUM + 1; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            ret = bbm_stop_thumb_by_ch(ch);
        }
    }

    return ret;
}


static int bbm_stop_camera_all(void)
{
    int ret;
    int ch;

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            printf("rt stream stop all:%d \n", ch);
            ret = bbm_ctp_rt_stop(__this->bbm_client_hdl[ch]);
            if (ret) {
                printf("ch:%d rt stream stop err\n", ch);
                continue;
            }
            __this->cur_channel &= ~BIT(ch);
        }
    }
    return 0;
}


static int bbm_switch_camera(void)
{
    int i, ch;
    int start_ch;

    printf("switch camera \n");

    if (__this->online_dev_cnt <= 0) {
        printf("no online camera switch \n");
        return 0;
    } else {
        for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
            if (__this->cur_channel & BIT(ch)) {
                bbm_stop_camera_by_ch(ch);
            }
        }

        start_ch = find_next_camera(__this->last_opened_ch);
        if (start_ch == -1) {
            return 0;
        } else if (start_ch == MAX_PAIR_NUM) {
            //开启全部分屏显示
            struct video_window *selected_win = NULL;
            switch (__this->online_dev_cnt) {
            case 1:
                selected_win = disp_win_1;
                break;
            case 2:
                selected_win = disp_win_2;
                break;
            case 3:
                selected_win = disp_win_3;
                break;
            case 4:
                selected_win = disp_win_4;
                break;
            default:
                break;
            }
            if (!selected_win) {
                printf("selected_win err \n");
                return -1;
            }

            int select = 0;
            for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
                if (__this->online_table[ch] == BBM_TX_ONLINE) {
                    bbm_start_camera_by_ch(ch, &selected_win[select++]);
                }
            }
            if (__this->online_dev_cnt == 1) {
                start_ch = ch;
            }

        } else {
            bbm_start_camera_by_ch(start_ch, &disp_win_1[0]);
        }
        __this->last_opened_ch = start_ch;
    }


    return 0;

}

static int bbm_quit_cur_mode(void)
{
    int ret = 0;

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        printf("bbm quit mode stream \n");
        ret = bbm_stop_camera_all();
        bbm_rt_stream_exit();
        break;
    case BBM_MODE_FILE_BROWSER:
        printf("bbm quit mode file browser \n");
        ret = bbm_stop_thumb_all();
        break;
    case BBM_MODE_VIDEO_PLAY:
        printf("bbm quit mode file play \n");
        ret = bbm_stop_file_play_all();
        ctp_file_play_exit();
        break;
    case BBM_MODE_IDLE:
        printf("bbm cur mode is idle \n");
        //nothing
        break;
    default:
        printf("Unknow cur mode \n");
        break;
    }
    if (ret) {
        printf("bbm quit cur mode err\n");
        return -1;
    }

    __this->bbm_cur_mode = BBM_MODE_IDLE;
    return 0;
}

static int bbm_enter_mode(u8 mode, int ch, int arg)
{
    int ret;
    switch (mode) {
    case BBM_MODE_STREAM:
        printf("bbm enter mode stream \n");
        bbm_rt_stream_init();
        ret = bbm_switch_camera();
        if (__this->online_dev_cnt > 1) {
            post_stream_msg_to_ui("show switch btn", 0);
        } else {
            post_stream_msg_to_ui("hide switch btn", 0);
        }
        break;
    case BBM_MODE_FILE_BROWSER:
        printf("bbm enter mode file browser \n");
        ret = bbm_start_thumb_by_ch(ch);
        break;
    case BBM_MODE_VIDEO_PLAY:
        printf("bbm enter mode file play \n");
        ctp_file_play_init(__this->bbm_client_hdl[ch]);
        ret = bbm_start_file_play_by_ch(ch, arg);
        break;
    case BBM_MODE_IDLE:
        //nothing
        break;
    default:
        printf("Unknow cur mode \n");
        break;
    }

    __this->bbm_cur_mode = mode;

    return ret;
}

static int bbm_switch_mode(u8 mode, int ch, int arg)
{
    int ret = -1;

    if (__this->bbm_cur_mode == mode) {
        printf("cur mode is %d . no switch \n", mode);
        //TODO
        if (__this->bbm_cur_mode == BBM_MODE_STREAM) {
            //nothing
            return 0;
        } else if (__this->bbm_cur_mode == BBM_MODE_FILE_BROWSER) {
            //
        }
    }

    ret = bbm_quit_cur_mode();

    ret = bbm_enter_mode(mode, ch, arg);

    return ret;
}


static int bbm_tx_offline(void *priv)
{
    int ret;
    int ch = (int)priv;

    if (__this->online_table[ch] == BBM_TX_OFFLINE) {
        printf("device already offline \n");
        return 0;
    }

    //标记不在线
    __this->online_table[ch] = BBM_TX_OFFLINE;
    __this->online_cnt_table[ch] = 0;
    __this->online_dev_cnt--;

    //log
    struct arp_entry_t *arp_entry = get_arp_static_entry_by_id(ch);
    if (arp_entry) {
        printf("ch:%d ip:%s not online ! ", ch, inet_ntoa(arp_entry->ipaddr));
    }

    if (__this->online_timeout[ch]) {
        sys_timeout_del(__this->online_timeout[ch]);
        __this->online_timeout[ch] = 0;
    }

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        if (__this->online_dev_cnt < 2) {
            post_stream_msg_to_ui("hide switch btn", 0);
        }
        if (__this->cur_channel & BIT(ch)) {
            bbm_stop_camera_by_ch(ch);

            bbm_switch_camera();
        }
        break;
    case BBM_MODE_FILE_BROWSER:
    case BBM_MODE_VIDEO_PLAY:
        if (__this->cur_channel & BIT(ch)) {
            post_home_msg_to_ui("back_home_page", 0);
            char *lab = "Device Not Online !";
            post_home_msg_to_ui("show_sys_prompt", lab);
            bbm_quit_cur_mode();
        }
        break;
    case BBM_MODE_IDLE:
        break;
    }

    //ctp client退出
    bbm_ctp_client_exit(&__this->bbm_client_hdl[ch]->ctp_cli_hdl);
    free(__this->bbm_client_hdl[ch]);
    __this->bbm_client_hdl[ch] = NULL;

}

static int bbm_tx_online(int ch, u32 ip_addr)
{
    int ret;

    __this->online_dev_cnt++;
    __this->online_table[ch] = BBM_TX_ONLINE;
    printf("ch:%d online current dev num:%d \n", ch, __this->online_dev_cnt);

    __this->bbm_client_hdl[ch]  = malloc(sizeof(struct bbm_client_hdl));
    if (!__this->bbm_client_hdl[ch]) {
        printf("ch:%d bbm client malloc err \n", ch);
        goto err;
    }
    memset(__this->bbm_client_hdl[ch], 0x00, sizeof(struct bbm_client_hdl));
    __this->bbm_client_hdl[ch]->ch = ch;
    __this->bbm_client_hdl[ch]->ip_addr = ip_addr;

    ret = bbm_ctp_client_init(&__this->bbm_client_hdl[ch]->ctp_cli_hdl,
                              ip_addr, __this->bbm_client_hdl[ch]);
    if (ret) {
        goto err;
    }

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        if (__this->online_dev_cnt > 1 && __this->cur_channel) {
            //两个设备以上,显示切摄像头图标
            post_stream_msg_to_ui("show switch btn", 0);
        } else {
            ret = bbm_switch_camera();
        }
        break;
    case BBM_MODE_FILE_BROWSER:
        break;
    case BBM_MODE_VIDEO_PLAY:
        break;
    case BBM_MODE_IDLE:
        break;
    }

    return 0;

err:
    if (__this->bbm_client_hdl[ch]) {
        free(__this->bbm_client_hdl[ch]);
        __this->bbm_client_hdl[ch] = NULL;
    }

    __this->online_dev_cnt--;
    __this->online_table[ch] = BBM_TX_OFFLINE;
    return -1;
}


static int bbm_online_event_hander(struct intent *it)
{
    int ch;
    int timeout = DEVICE_ONLINE_TIMEOUT;
    u32 ip_addr = it->data;
    u32 online_cnt = it->exdata;

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        struct arp_entry_t *arp_entry = get_arp_static_entry_by_id(ch);

        if (!__this->is_pairing && arp_entry && arp_entry->ipaddr.addr == ip_addr) {

            //设备上线处理
            if (__this->online_table[ch] == BBM_TX_OFFLINE) {
                bbm_tx_online(ch, ip_addr);
            } else {
                //设备短时间内重启处理
                if (online_cnt < __this->online_cnt_table[ch]) {
                    printf("ch:%d reboot \n", ch);
                    if (__this->online_timeout[ch]) {
                        sys_timeout_del(__this->online_timeout[ch]);
                        __this->online_timeout[ch] = 0;
                    }
                    bbm_tx_offline(ch);
                }
            }

            __this->online_cnt_table[ch] = online_cnt;

            //创建超时定时器,timeout内还没收到在线时间,认为设备已下线
            //在超时定时器内标记设备下线
            if (!__this->online_timeout[ch]) {
                __this->online_timeout[ch]  = sys_timeout_add(ch, bbm_tx_offline, timeout);
            } else {
                //重置超时定时器时间
                sys_timer_modify(__this->online_timeout[ch], timeout);
            }

            break;
        }

    }

    return 0;
}

static int bbm_rx_init(void)
{
    int ret;
    int ch;

    for (ch = MIN_PAIR_CH; ch < MAX_PAIR_NUM; ch++) {
        struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);
        if (arp_entry) {
            bbm_config_arp_entry(arp_entry);
            break;
        }
    }

    __this->bbm_client_hdl[RX_DEVICE_CH]  = malloc(sizeof(struct bbm_client_hdl));
    if (!__this->bbm_client_hdl[RX_DEVICE_CH]) {
        printf("ch:%d bbm client malloc err \n", RX_DEVICE_CH);
        return -1;
    }
    memset(__this->bbm_client_hdl[RX_DEVICE_CH], 0x00, sizeof(struct bbm_client_hdl));
    __this->bbm_client_hdl[RX_DEVICE_CH]->is_local_dev = 1;
    __this->bbm_client_hdl[RX_DEVICE_CH]->ch = ch;


    return 0;
}

static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;
    int ch;
    int arg;
    void *priv;
    char *path;
    switch (state) {
    case APP_STA_CREATE:
        log_d("\n>>>>> baby_monitor_init <<<<<\n");
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_BBM_MAIN:
            log_d("\n>>>>>baby_monitor_main <<<<<\n");
            bbm_rx_init();
            break;
        case ACTION_BBM_START_RT:
            log_d("\n>>>>>baby_monitor start stream <<<<<\n");
            ret = bbm_switch_mode(BBM_MODE_STREAM, 0, 0);
            break;
        case ACTION_BBM_STOP_RT:
            log_d("\n>>>>>baby_monitor stop stream <<<<<\n");
            break;
        case ACTION_BBM_GET_PAIR_STATUS:
            log_d("\n>>>>>baby_monitor get pair status <<<<<\n");
            ch = it->exdata;
            it->exdata = bbm_get_pair_status(ch);
            log_d("ch:%d pair status:%d \n", ch, it->exdata);
            break;
        case ACTION_BBM_ENTER_PAIRING:
            log_d("\n>>>>>baby_monitor start pairing <<<<<\n");
            ch = it->exdata;
            __this->is_pairing = 1;
            bbm_set_enter_pairing(ch);
            break;
        case ACTION_BBM_EXIT_PAIRING:
            log_d("\n>>>>>baby_monitor exit pairing <<<<<\n");
            __this->is_pairing = 0;
            bbm_set_exit_pairing();
            break;
        case ACTION_BBM_UNPAIR:
            log_d("\n>>>>>baby_monitor start unpair <<<<<\n");
            ch = it->exdata;
            bbm_tx_offline(ch);
            bbm_set_unpair(ch);
            break;
        case ACTION_BBM_SWITCH_WIN:
            log_d("\n>>>>>baby_monitor switch win <<<<<\n");
            bbm_switch_camera();
            break;
        case ACTION_BBM_START_FILE_BROWSER:
            log_d("\n>>>>>baby_monitor start file stream <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
                strcpy(__this->bbm_client_hdl[ch]->local_path, path);
            } else {
                ch = bbm_path_to_ch(path);
            }
            ret = bbm_switch_mode(BBM_MODE_FILE_BROWSER, ch, 0);
            break;
        case ACTION_BBM_STOP_FILE_BROWSER:
            log_d("\n>>>>>baby_monitor stop file stream <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
                strcpy(__this->bbm_client_hdl[ch]->local_path, path);
            } else {
                ch = bbm_path_to_ch(path);
            }
            bbm_stop_thumb_by_ch(ch);
            break;
        case ACTION_BBM_GET_FILE_NUM:
            log_d("\n>>>>>baby_monitor get_file_browser num <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }

            int *num = it->exdata;
            ret = bbm_get_file_num(ch, num);
            break;
        case ACTION_BBM_GET_FILE_LIST:
            log_d("\n>>>>>baby_monitor get_file_browser list <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }

            char ***list = it->exdata;
            ret = bbm_get_file_name_list(ch, list);
            break;
        case ACTION_BBM_GET_FILE_THUMB_REQ:
            log_d("\n>>>>>baby_monitor get_file_browser thumb <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }

            struct net_ctp_thumb *thumb_data = it->exdata;
            ret = bbm_ctp_get_file_thumb(__this->bbm_client_hdl[ch], thumb_data);
            break;
        case ACTION_BBM_FILE_PLAY_START:
            log_d("\n>>>>>baby_monitor file play start <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }
            arg = it->exdata;
            ret = bbm_switch_mode(BBM_MODE_VIDEO_PLAY, ch, arg);
            break;
        case ACTION_BBM_FILE_PLAY_STOP:
            log_d("\n>>>>>baby_monitor file play stop <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }
            bbm_stop_file_play_by_ch(ch);
            break;
        case ACTION_BBM_FILE_PLAY_SWITCH:
            log_d("\n>>>>>baby_monitor file play switch <<<<<\n");
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }
            arg = it->exdata;
            ret = bbm_switch_file_play_by_ch(ch, arg);
            break;
        case  ACTION_BBM_ONLINE:
            bbm_online_event_hander(it);
            break;
        case ACTION_BBM_GET_ONLINE_DEV_STATUS:
            char *dev_path = it->exdata;
            int *status = it->data;

            *status = bbm_get_dir_num(dev_path);

            break;
        case ACTION_BBM_TX_SD_OFFLINE:
            priv = it->data;
            ret = bbm_tx_sd_offline(priv);
            break;
        case ACTION_BBM_FILE_LIST_UPDATE:
            ret = bbm_file_list_update(it->data, it->exdata);
            break;
        case ACTION_BBM_FILE_LIST_CREATE:
            priv = it->data;
            ret = bbm_file_list_create(priv);
            break;
        case ACTION_BBM_TX_START_REC_ERR:
            priv = it->data;
            ret = bbm_tx_start_rec_err(priv);
            break;
        case ACTION_BBM_DELETE_FILE:
            path = it->data;
            if (strstr(path, "storage")) {
                ch = RX_DEVICE_CH;
            } else {
                ch = bbm_path_to_ch(path);
            }
            ret = bbm_ctp_file_delete(__this->bbm_client_hdl[ch], it->exdata);
            break;
        case ACTION_BBM_CLEAN_PAIR:
            arp_static_table_reset_to_flash();
            break;
        }
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        //todo
        break;
    case APP_STA_DESTROY:
        log_d("\n>>>>> baby_monitor_exit <<<<<\n");
        //todo
        break;
    default:
        break;
    }

    return ret;
}


static int baby_monitor_key_event_handler(struct key_event *key)
{
    int ret = false;
    printf("key->action:%d key->value:%d \n", key->action, key->value);
    if (key->action == KEY_EVENT_CLICK) {
        ret = true;
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
            //测试
            //
            //TX开始录像
            /* bbm_ctp_rec_start(__this->bbm_client_hdl[1]); */
            //RX开始录像
            /* bbm_rx_rec_start(__this->bbm_client_hdl[1]); */
            //数字变焦
            /* bbm_rt_stream_digital_zomm(__this->bbm_client_hdl[1], 1); */
            //设置码率
            /* bbm_ctp_set_abr(__this->bbm_client_hdl[1], 1000); */
            //开启全部TX设备录像
            bbm_tx_start_rec_all();
            //开启全部RX录像
            bbm_rx_start_rec_all();
            //RX设备拍照
            //bbm_ctp_take_photo(__this->bbm_client_hdl[1]);
            break;
        case KEY_OK:
            printf("KEY5\n");
            //测试
            //
            //TX停止录像
            /* bbm_ctp_rec_stop(__this->bbm_client_hdl[1]); */
            //RX停止录像
            /* bbm_rx_rec_stop(__this->bbm_client_hdl[1]); */
            //数字变焦
            /* bbm_rt_stream_digital_zomm(__this->bbm_client_hdl[1], 2); */
            //设置码率
            /* bbm_ctp_set_abr(__this->bbm_client_hdl[1], 4000); */
            //关闭全部TX设备录像
            bbm_tx_stop_rec_all();
            //关闭全部RX录像
            bbm_rx_stop_rec_all();
            break;
        default:
            printf("Unknow KEY\n");
            break;
        }
    }

    return ret;
}



static int baby_monitor_device_event_handler(struct sys_event *e)
{
    int ret = false;
    struct device_event *device_eve = (struct device_event *)e->payload;

    /*
     * SD卡插拔处理
     */
    if (e->from == DEVICE_EVENT_FROM_SD) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            printf("bbm device handler sd in \n");
            ret = true;
            break;
        case DEVICE_EVENT_OUT:
            printf("bbm device handler sd out \n");
            ret = true;
            if (__this->bbm_cur_mode == BBM_MODE_FILE_BROWSER ||
                __this->bbm_cur_mode == BBM_MODE_VIDEO_PLAY) {

                if (__this->cur_channel & BIT(RX_DEVICE_CH)) {
                    post_home_msg_to_ui("back_home_page", 0);
                    char *lab = "SD Card Not Online !";
                    post_home_msg_to_ui("show_sys_prompt", lab);
                    bbm_quit_cur_mode();
                }
            }
            break;
        default:
            break;
        }


    }


    return ret;
}

static int event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return  baby_monitor_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return  baby_monitor_device_event_handler(event);
    case SYS_NET_EVENT:
    default:
        return false;
    }
}


static const struct application_operation baby_monitor_ops = {
    .state_machine  = state_machine,
    .event_handler  = event_handler,
};

REGISTER_APPLICATION(app_baby_monitor) = {
    .name 	= "baby_monitor",
    .action	= ACTION_BBM_MAIN,
    .ops 	= &baby_monitor_ops,
    .state  = APP_STA_DESTROY,
};




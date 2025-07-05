#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "os/os_api.h"
#include "system/init.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "lwip/dns.h"
#include "device/device.h"
#include "system/app_core.h"
#include "server/server_core.h"
#include "action.h"
#include "system/timer.h"
#include "asm/debug.h"
#include "app_config.h"
#include "http/http_cli.h"
#include "system/timer.h"
#include "database.h"
#include "dev_desc.h"
#include "http/http_server.h"
#include "server/ctp_server.h"
#include "server/net_server.h"
#include "video_rt_tcp.h"
#include "ftpserver/stupid-ftpd.h"
#include "streaming_media_server/fenice_config.h"
#include "syscfg/syscfg_id.h"
#include "udp_multicast.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "net_event.h"
#include "pairing_data_model.h"

#define RSSI_HIGH_THRESHOLD     0
#define RSSI_LOW_THRESHOLD      -5
#define WIFI_PWR_MIN            1
#define WIFI_PWR_MAX            6

const u8 bbm_tx_pair_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};
const u8 bbm_rx_src_mac[6] = {0x15, 0x81, 0x54, 0x33, 0x13, 0x87};
const u8 bbm_bssid_mac[6] = {0x88, 0x88, 0x88, 0x99, 0x88, 0x77};
const int bbm_tx_pair_wifi_channel = 1;
static int cur_pwr;

#define WIFI_APP_TASK_NAME "wifi_app_task"

#define MAC_ADDR_LEN 6
#define HEAD_802_11_OFFSET 20

static int multicast_recv_task_pid;
static int bbm_tx_online_task_pid;
static int bbm_rx_online_task_pid;
static int bbm_tx_online_task_exit;
static int bbm_rx_online_task_exit;
static u8 multicast_recv_task_exit;
static int net_state_timer;

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event);

#define DEST_IP_ADDR "192.168.1.1"

static struct server *ctp = NULL;
static struct ctp_server_info server_info = {
    .ctp_vaild = true,
    .ctp_port = CTP_CTRL_PORT,
    .cdp_vaild = true,
    .cdp_port = CDP_CTRL_PORT,
    .k_alive_type = NOT_USE_ALIVE,
    /*.k_alive_type = CDP_ALIVE,*/
};

struct bbm_online_packet {
    u32 magic[2];
    u32 online_cnt;
    int rssi;
};

struct rx_device_check {
    u32 last_seen;   // 上次收到数据包的时间（可以是系统滴答数或时间戳）
    u8 online;      // 状态标记，1 表示在线，0 表示离线
};


#define PACKAGE_MAX_SIZE    1024

struct parse_recv_info {
    u32 bbm_rx_ip;
    u32 bbm_tx_ip;

    u8 bbm_rx_mac[6];
    u8 bbm_tx_mac[6];
    int  wifi_channel;
};

static char default_dest_ip[20];

typedef struct _head_802_11 {
    unsigned short  fc;
    unsigned short  duration;
    unsigned char   addr1[MAC_ADDR_LEN];
    unsigned char   addr2[MAC_ADDR_LEN];
    unsigned char	addr3[MAC_ADDR_LEN];
    unsigned short	frag: 4;
    unsigned short	sequence: 12;
    unsigned char 	data[0];
} head_802_11, *phead_802_11;

struct lan_setting lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 1,
#ifdef CONFIG_BBM_RX
    .WIRELESS_IP_ADDR3  = 1,
#else
    .WIRELESS_IP_ADDR3  = 2,
#endif

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 1,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 1,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 1,
    .CLIENT_IPADDR4  = 2,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};


static void wifi_raw_state_timer_func(void *p)
{
    static u8 cnt = 0;

    //内存
    if (++cnt == 5) {
        cnt = 0;
        malloc_stats();
    }

    //信号强度
    char rssi = wifi_raw_rssi_get();
    printf("rssi:%d pwr:%d \n", rssi, cur_pwr);
}

static void wifi_state_timer_func(void *p)
{
    printf("WIFI U= %d KB/s, D= %d KB/s\r\n",
           wifi_get_upload_rate() / 1024, wifi_get_download_rate() / 1024);

    malloc_stats();
}

static int lwip_set_lan_info(struct lan_setting *__lan_setting_info)
{
    struct lan_setting *lan_setting_info = net_get_lan_info(WIFI_RAW_NETIF);
    if (!lan_setting_info) {
        return -1;
    }

    lan_setting_info->WIRELESS_IP_ADDR0  = __lan_setting_info->WIRELESS_IP_ADDR0;
    lan_setting_info->WIRELESS_IP_ADDR1  = __lan_setting_info->WIRELESS_IP_ADDR1;
    lan_setting_info->WIRELESS_IP_ADDR2  = __lan_setting_info->WIRELESS_IP_ADDR2;
    lan_setting_info->WIRELESS_IP_ADDR3  = __lan_setting_info->WIRELESS_IP_ADDR3;

    lan_setting_info->WIRELESS_NETMASK0  = __lan_setting_info->WIRELESS_NETMASK0;
    lan_setting_info->WIRELESS_NETMASK1  = __lan_setting_info->WIRELESS_NETMASK1;
    lan_setting_info->WIRELESS_NETMASK2  = __lan_setting_info->WIRELESS_NETMASK2;
    lan_setting_info->WIRELESS_NETMASK3  = __lan_setting_info->WIRELESS_NETMASK3;

    lan_setting_info->WIRELESS_GATEWAY0  = __lan_setting_info->WIRELESS_GATEWAY0;
    lan_setting_info->WIRELESS_GATEWAY1  = __lan_setting_info->WIRELESS_GATEWAY1;
    lan_setting_info->WIRELESS_GATEWAY2  = __lan_setting_info->WIRELESS_GATEWAY2;
    lan_setting_info->WIRELESS_GATEWAY3  = __lan_setting_info->WIRELESS_GATEWAY3;

    lan_setting_info->SERVER_IPADDR1     = __lan_setting_info->SERVER_IPADDR1;
    lan_setting_info->SERVER_IPADDR2     = __lan_setting_info->SERVER_IPADDR2;
    lan_setting_info->SERVER_IPADDR3     = __lan_setting_info->SERVER_IPADDR3;
    lan_setting_info->SERVER_IPADDR4     = __lan_setting_info->SERVER_IPADDR4;

    lan_setting_info->CLIENT_IPADDR1     = __lan_setting_info->CLIENT_IPADDR1;
    lan_setting_info->CLIENT_IPADDR2     = __lan_setting_info->CLIENT_IPADDR2;
    lan_setting_info->CLIENT_IPADDR3     = __lan_setting_info->CLIENT_IPADDR3;
    lan_setting_info->CLIENT_IPADDR4     = __lan_setting_info->CLIENT_IPADDR4;

    lan_setting_info->SUB_NET_MASK1      = __lan_setting_info->SUB_NET_MASK1;
    lan_setting_info->SUB_NET_MASK2      = __lan_setting_info->SUB_NET_MASK2;
    lan_setting_info->SUB_NET_MASK3      = __lan_setting_info->SUB_NET_MASK3;
    lan_setting_info->SUB_NET_MASK4      = __lan_setting_info->SUB_NET_MASK4;

    return 0;
}

void config_send_pkg_head(u8 *src_mac, u8 *dest_mac);

void mac_to_string(char *mac_str, const u8 mac[6])
{
    sprintf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void string_to_mac(const char *mac_str, u8 mac[6])
{
    sscanf(mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
}



static int ctp_init(void)
{
#ifdef CONFIG_BBM_TX
    ctp = server_open("ctp_server", (void *)&server_info);
    if (!ctp) {
        printf("ctp server fail\n");
    }
    puts("http server init\n");
    extern int http_virfile_reg(const char *path, const char *contents, unsigned long len);

    http_virfile_reg(DEV_DESC_PATH, DEV_DESC_CONTENT, strlen(DEV_DESC_CONTENT)); //注册虚拟文件描述文档,可在dev_desc.h修改
    http_get_server_init(HTTP_PORT); //8080
    video_rt_tcp_server_init(2229);
#ifdef CONFIG_ENABLE_VLIST
    preview_init(VIDEO_PREVIEW_PORT, NULL); //2226

    if (server_info.k_alive_type = NOT_USE_ALIVE) {
        //BBM回放使用UDP
        playback_udp_init();
    } else {
        playback_init(VIDEO_PLAYBACK_PORT, NULL);
    }
#endif

#else
    ctp_cli_init();
#endif
}

void ctp_exit(void)
{
    puts("ctp server uninit\n");
    server_close(ctp);
    puts("http server uninit\n");
    http_get_server_uninit(); //8080
    video_rt_tcp_server_uninit();
    preview_uninit(); //2226
    playback_uninit();
}

static int deal_pair_request_package(u8 *payload_buf, struct parse_recv_info *info)
{
    //解析json
    json_object *new_obj = NULL;
    json_object *data_obj = NULL;
    char *bbm_rx_ip_str, *bbm_rx_mac_str, *bbm_tx_ip_str, *bbm_tx_mac_str, *wifi_ch;

    new_obj = json_tokener_parse(payload_buf);
    data_obj =  json_object_object_get(new_obj, "data");

    bbm_rx_ip_str = json_object_get_string(json_object_object_get(data_obj, "bbm_rx_ip"));
    bbm_rx_mac_str = json_object_get_string(json_object_object_get(data_obj, "bbm_rx_mac"));
    bbm_tx_ip_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_ip"));
    bbm_tx_mac_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_mac"));
    wifi_ch =  json_object_get_string(json_object_object_get(data_obj, "wifi_channel"));

    printf("request rx ip:%s rx mac:%s tx ip:%s tx mac:%s wifi_ch:%s",
           bbm_rx_ip_str, bbm_rx_mac_str, bbm_tx_ip_str, bbm_tx_mac_str, wifi_ch);

    //ip
    info->bbm_rx_ip = inet_addr(bbm_rx_ip_str);
    info->bbm_tx_ip = inet_addr(bbm_tx_ip_str);
    //channel
    info->wifi_channel = atoi(wifi_ch);
    //mac
    string_to_mac(bbm_rx_mac_str, info->bbm_rx_mac);
    string_to_mac(bbm_tx_mac_str, info->bbm_tx_mac);

    return 0;
}

static void fill_respone_data(u8 *data)
{
    //获取本机MAC
    char bbm_tx_mac[6];
    char bbm_tx_mac_str[20];
    wifi_raw_get_mac(bbm_tx_mac);
    mac_to_string(bbm_tx_mac_str, bbm_tx_mac);

    //获取本机IP
    struct netif_info netif_info;
    lwip_get_netif_info(WIFI_RAW_NETIF, &netif_info);
    char *bbm_tx_ip_str = inet_ntoa(netif_info.ip);

    sprintf(data, PAIRING_RESPONE, bbm_tx_ip_str, bbm_tx_mac_str);
}

static void bbm_tx_pair_config(void)
{
    int ret;
    struct parse_recv_info recv_pair_info = {0};

    ret = syscfg_read(BBM_TX_MAC_INDEX, &recv_pair_info, sizeof(struct parse_recv_info));
    if (ret > 0) {
        wifi_raw_set_static(recv_pair_info.bbm_tx_ip, recv_pair_info.bbm_tx_mac,
                            recv_pair_info.bbm_rx_ip, recv_pair_info.bbm_rx_mac);
        wifi_set_channel(recv_pair_info.wifi_channel);
    } else {
        printf("tx pair config err \n");
    }

}

static void multicast_recv_task(void)
{
    struct sockaddr_in dstaddr;
    struct parse_recv_info recv_pair_info = {0};
    u32 addrlen = sizeof(dstaddr);
    int multi_sock = 0;
    u8 *recv_buf = NULL, *send_buf = NULL, *tem_buf = NULL, *payload_buf = NULL;
    int recv_len, send_len, payload_len;
    int ret;

    multi_sock = CreateUdpMulticast(MULTICAST_PORT);
    if (multi_sock < 0) {
        printf("CreateUdpMulticast err \n");
        goto exit;
    }

    recv_buf = malloc(PACKAGE_MAX_SIZE);
    send_buf = malloc(PACKAGE_MAX_SIZE);
    tem_buf = malloc(PACKAGE_MAX_SIZE);
    if ((!recv_buf) || (!send_buf) || (!tem_buf)) {
        printf("package buf malloc fail \n");
        goto exit;
    }

    sock_set_recv_timeout(multi_sock, 100);
    while (1) {

        if (multicast_recv_task_exit) {
            printf("multicast_recv_task_exit\n");
            break;
        }

        wifi_raw_set_mac(bbm_tx_pair_mac);
        wifi_set_channel(bbm_tx_pair_wifi_channel);

        recv_len = sock_recvfrom(multi_sock, recv_buf, PACKAGE_MAX_SIZE, 0, &dstaddr, &addrlen);
        if (recv_len <= 0) {
            /* printf("multicast udp recv err\n"); */
            continue;
        }
        printf("multi recv \n");

        //检查包头
        payload_len = get_package_payload_len(recv_buf);
        if (payload_len < 0) {
            printf("package head err \n");
            continue;
        }
        payload_buf = recv_buf + (recv_len - payload_len);

        //检查是不是配对请求包
        if (!strstr(payload_buf, "pair_req")) {
            printf("no pair req package \n");
            continue;
        }

        //解析json
        deal_pair_request_package(payload_buf, &recv_pair_info);

        //配置网络
        wifi_raw_set_static(recv_pair_info.bbm_tx_ip, recv_pair_info.bbm_tx_mac,
                            recv_pair_info.bbm_rx_ip, recv_pair_info.bbm_rx_mac);

        //等待网络准备就绪
        os_time_dly(30);

        //填充包数据
        fill_respone_data(tem_buf);
        send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);

        //接收ack包
        int timeout_cnt = 10;
        int i;
        for (i = 0; i < timeout_cnt; i++) {

            send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dstaddr, sizeof(dstaddr));
            if (send_len <= 0) {
                printf("respone udp send err\n");
                continue;
            }
            printf("multi send ack \n");

            recv_len = sock_recvfrom(multi_sock, recv_buf, PACKAGE_MAX_SIZE, 0, &dstaddr, &addrlen);
            if (recv_len <= 0) {
                printf("recv ack timeout %d\n", i);
                continue;
            }
            payload_len = get_package_payload_len(recv_buf);
            if (payload_len < 0) {
                continue;
            }
            payload_buf = recv_buf + (recv_len - payload_len);
            if (!strstr(payload_buf, "pair_ack")) {
                continue;
            }
            break;
        }

        if (i < timeout_cnt) {
            //写入flash
            ret = syscfg_write(BBM_TX_MAC_INDEX, &recv_pair_info, sizeof(struct parse_recv_info));
            if (ret <= 0) {
                printf("syscfg_write err :%d \n", ret);
                goto exit;
            }
            printf("bbm TX pair success !\n");
            break;

        } else {
            printf("bbm TX pair fail ! No recv ack\n");
        }

    }

exit:
    bbm_tx_pair_config();

    if (multi_sock > 0) {
        sock_unreg(multi_sock);
    }
    if (recv_buf) {
        free(recv_buf);
    }
    if (send_buf) {
        free(send_buf);
    }
    if (tem_buf) {
        free(tem_buf);
    }
}

//修改发送包头部信息、及arp映射
int wifi_raw_set_static(u32 src_ip_addr, u8 *src_mac, u32 dest_ip_addr, u8 *dest_mac)
{
    //mac
    wifi_raw_set_mac(src_mac);

    lwip_etharp_remove_static_entry(default_dest_ip);

    //ip
    struct netif *netif = net_get_netif_handle(WIFI_RAW_NETIF);
    netif_set_ipaddr(netif, &src_ip_addr);

    config_send_pkg_head(src_mac, dest_mac);

    strcpy(default_dest_ip, inet_ntoa(dest_ip_addr));

    lwip_etharp_add_static_entry(default_dest_ip, dest_mac);

    //设置本机硬件MAC, 需要在wifi_raw_on后调用
    wf_asic_set_mac(src_mac);

    return 0;
}

void config_send_pkg_head(u8 *src_mac, u8 *dest_mac)
{
    //设置发送包的802.11头部信息, 设置源mac， 目标mac， seq号等信息
    phead_802_11 pHdr = wifi_get_wifi_send_pkg_ptr() + HEAD_802_11_OFFSET;
    memcpy(pHdr->addr1, dest_mac, 6);
#ifdef CONFIG_BBM_RX
    //对于RX设备,此MAC地址固定.用于鉴别是否有其他RX设备在同一信道
    memcpy(pHdr->addr2, bbm_rx_src_mac, 6);
#else
    memcpy(pHdr->addr2, src_mac, 6);
#endif
    memcpy(pHdr->addr3, bbm_bssid_mac, 6);
    pHdr->frag = 8;
}

#ifdef CONFIG_BBM_RX
#define OFFLINE_THRESHOLD   3 * 1000 / 10   //3s

static struct rx_device_check rx_dev;

//lwip接收回调调用
void check_wifi_mac(const u8 *mac)
{
    //检查这些包是否有BBM_RX设备
    if (!memcmp(mac, bbm_rx_src_mac, sizeof(bbm_rx_src_mac))) {
        rx_dev.online = 1;
        rx_dev.last_seen = jiffies;
    }
}

void check_bbm_rx_devices(void)
{
    if (!rx_dev.online || (rx_dev.online && (jiffies - rx_dev.last_seen) > OFFLINE_THRESHOLD)) {
        rx_dev.online = 0;
        //没有其他RX设备
        //TODO
        //notify app?
    } else {
        //有其他RX设备
        printf("Discover other RX device\n");
        //TODO
        //notify app?
    }
}

#endif

//TX创建组播线程
#ifdef CONFIG_BBM_TX

void bbm_tx_enter_pairing(void)
{
    if (!multicast_recv_task_pid) {
        thread_fork("multicast_recv_task", 10, 2048, 2048
                    , &multicast_recv_task_pid, multicast_recv_task, NULL);
    }
}

void bbm_tx_exit_pairing(void)
{
    if (multicast_recv_task_pid) {
        multicast_recv_task_exit = 1;
        thread_kill(&multicast_recv_task_pid, KILL_WAIT);
        multicast_recv_task_exit = 0;
        multicast_recv_task_pid = 0;
    }
}

static void bbm_tx_online_task(void)
{
    void *multi_sock = NULL;
    u8 send_buf[32];
    int send_len = sizeof(send_buf);
    u8 recv_buf[32];
    int recv_len = sizeof(recv_buf);
    struct bbm_online_packet send_pkg = {0};
    struct bbm_online_packet recv_pkg = {0};
    struct bbm_online_packet old_pkg = {0};

    multi_sock = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (multi_sock == NULL) {
        printf("online multi sock_reg err\n");
        return;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(UDP_MULTICAST_ADDR);
    dest_addr.sin_port = htons(MULTICAST_ONLINE_PORT);
    u32 addrlen = sizeof(dest_addr);

    while (1) {

        if (bbm_tx_online_task_exit) {
            break;
        }

        /*================send=================*/
        send_pkg.magic[0] = PACKAGE_MAGIC;
        send_pkg.magic[1] = rand32();
        send_pkg.online_cnt++;
        send_pkg.rssi = wifi_raw_rssi_get();

        memcpy(send_buf, &send_pkg, sizeof(send_pkg));

        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dest_addr, sizeof(dest_addr));
        if (send_len < 0) {
            printf("online sock send err\n");
            continue;
        }

        //200ms
        os_time_dly(20);

        /*================recv=================*/
        recv_len = sock_recvfrom(multi_sock, recv_buf, 32, MSG_DONTWAIT, &dest_addr, &addrlen);
        if (recv_len <= 0) {
            continue;
        }

        memcpy(&recv_pkg, recv_buf, sizeof(recv_pkg));
        if (recv_pkg.magic[0] != PACKAGE_MAGIC) {
            printf("magic err\n");
            continue;
        }

        //过滤重发包
        if (!memcmp(&recv_pkg, &old_pkg, sizeof(recv_pkg))) {
            printf("recv same data \n");
            continue;
        }
        memcpy(&old_pkg, &recv_pkg, sizeof(recv_pkg));

#if BBM_WIFI_PA_ENABLE
        //带PA时需要调整防止近距离卡顿
        //根据rssi调整wifi模拟增益
        //TODO粗略值
        if (recv_pkg.rssi >= RSSI_HIGH_THRESHOLD) {
            cur_pwr = --cur_pwr < WIFI_PWR_MIN ? WIFI_PWR_MIN : cur_pwr;
            wifi_set_pwr(cur_pwr);
        } else if (recv_pkg.rssi <= RSSI_LOW_THRESHOLD) {
            cur_pwr = ++cur_pwr > WIFI_PWR_MAX ? WIFI_PWR_MAX : cur_pwr;
            wifi_set_pwr(cur_pwr);
        }
#endif
    }

    sock_unreg(multi_sock);
    printf("bbm tx online task exit \n");
}

#else

static void bbm_rx_online_task(void)
{
    int multi_sock = 0;
    u8 recv_buf[32];
    int recv_len = sizeof(recv_buf);
    u8 send_buf[32];
    int send_len = sizeof(send_buf);
    struct bbm_online_packet send_pkg = {0};
    struct bbm_online_packet recv_pkg = {0};
    struct bbm_online_packet old_pkg = {0};

    struct sockaddr_in dstaddr;
    u32 addrlen = sizeof(dstaddr);

    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_ONLINE;

    multi_sock = CreateUdpMulticast(MULTICAST_ONLINE_PORT);
    if (multi_sock < 0) {
        printf("CreateUdpMulticast err \n");
        return;
    }

    while (1) {
        /*================recv=================*/
        recv_len = sock_recvfrom(multi_sock, recv_buf, 32, 0, &dstaddr, &addrlen);
        if (recv_len <= 0) {
            continue;
        }

        memcpy(&recv_pkg, recv_buf, sizeof(recv_pkg));
        if (recv_pkg.magic[0] != PACKAGE_MAGIC) {
            printf("magic err\n");
            continue;
        }

        //过滤重发包
        if (!memcmp(&recv_pkg, &old_pkg, sizeof(recv_pkg))) {
            printf("same data \n");
            continue;
        }
        memcpy(&old_pkg, &recv_pkg, sizeof(recv_pkg));

#if BBM_WIFI_PA_ENABLE
        //带PA时需要调整防止近距离卡顿
        //根据rssi调整wifi模拟增益
        //TODO粗略值
        if (recv_pkg.rssi >= RSSI_HIGH_THRESHOLD) {
            cur_pwr = --cur_pwr < WIFI_PWR_MIN ? WIFI_PWR_MIN : cur_pwr;
            wifi_set_pwr(cur_pwr);
            /* printf("set pwr val:%d \n", cur_pwr); */
        } else if (recv_pkg.rssi <= RSSI_LOW_THRESHOLD) {
            cur_pwr = ++cur_pwr > WIFI_PWR_MAX ? WIFI_PWR_MAX : cur_pwr;
            wifi_set_pwr(cur_pwr);
            /* printf("set pwr val:%d \n", cur_pwr); */
        }
#endif

        it.data = dstaddr.sin_addr.s_addr;
        it.exdata = recv_pkg.online_cnt;
        start_app_async(&it, NULL, NULL);


        /*================send=================*/
        send_pkg.magic[0] = PACKAGE_MAGIC;
        send_pkg.magic[1] = rand32();
        send_pkg.online_cnt++;
        send_pkg.rssi = wifi_raw_rssi_get();
        memcpy(send_buf, &send_pkg, sizeof(send_pkg));

        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dstaddr, sizeof(dstaddr));
        if (send_len < 0) {
            printf("online sock send err\n");
            continue;
        }
    }
}
#endif

int bbm_online_init(void)
{
#ifdef CONFIG_BBM_RX
    //RX设备online处理线程
    //BBM处理设备上线下线.
    thread_fork("bbm_rx_online_task", 16, 2048, 2048
                , &bbm_rx_online_task_pid, bbm_rx_online_task, NULL);
#else
    //TX设备online处理线程
    thread_fork("bbm_tx_online_task", 16, 2048, 2048
                , &bbm_tx_online_task_pid, bbm_tx_online_task, NULL);
#endif
}

int bbm_online_exit(void)
{
#ifdef CONFIG_BBM_RX
    //TODO
    //rx线程暂时不用关
#else
    if (bbm_tx_online_task_pid) {
        bbm_tx_online_task_exit = 1;
        thread_kill(&bbm_tx_online_task_pid, KILL_WAIT);
        bbm_tx_online_task_exit = 0;
    }
#endif
}

void wifi_raw_init(void)
{
    int i;
    int ret;

    printf("\n========== WiFi Raw Init ==========\n");

    strcpy(default_dest_ip, DEST_IP_ADDR);

    u8 dest_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};
    int wifi_channel;

#ifdef  CONFIG_BBM_TX
    struct parse_recv_info recv_pair_info = {0};
    u8 src_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};

    //TX根据FLASH来修改IP
    ret = syscfg_read(BBM_TX_MAC_INDEX, &recv_pair_info, sizeof(struct parse_recv_info));
    if (ret > 0) {
        u32 ip_addr = recv_pair_info.bbm_tx_ip;
        lan_setting_info.WIRELESS_IP_ADDR0 = (ip_addr & 0xFF);
        lan_setting_info.WIRELESS_IP_ADDR1 = (ip_addr >> 8) & 0xFF;
        lan_setting_info.WIRELESS_IP_ADDR2 = (ip_addr >> 16) & 0xFF;
        lan_setting_info.WIRELESS_IP_ADDR3 = (ip_addr >> 24) & 0xFF;

        memcpy(src_mac, recv_pair_info.bbm_tx_mac, sizeof(src_mac));
        memcpy(dest_mac, recv_pair_info.bbm_rx_mac, sizeof(dest_mac));
        wifi_channel = recv_pair_info.wifi_channel;
        strcpy(default_dest_ip, inet_ntoa(recv_pair_info.bbm_rx_ip));
        printf("syscfg read ok ! \n ip:%s \n", inet_ntoa(ip_addr));
        printf("src mac: \n");
        put_buf(src_mac, sizeof(src_mac));
        printf("dest mac: \n");
        put_buf(dest_mac, sizeof(dest_mac));
    }
#else
    //BBM_RX端MAC地址，多RX同时用时，MAC地址要不一样
    u8 src_mac[6];

    ret = syscfg_read(BBM_RX_MAC_INDEX, src_mac, sizeof(src_mac));
    if (ret > 0) {
        //读取成功
        printf("read flash mac addr : \n");
        put_buf(src_mac, sizeof(src_mac));
    } else {
        //读取失败
        for (i = 0 ; i < ARRAY_SIZE(src_mac); i++) {
            src_mac[i] = rand32() >> 24;
        }

        printf("random mac addr : \n");
        put_buf(src_mac, sizeof(src_mac));

        ret = syscfg_write(BBM_RX_MAC_INDEX, src_mac, sizeof(src_mac));
        if (ret < 0) {
            printf("bbm rx mac addr write flash fail !!!\n");
        } else {
            printf("bbm rx mac addr write flash success !!!\n");
        }

        //清空配对表
        arp_static_table_reset_to_flash();
    }

    ret = syscfg_read(BBM_WIFI_CH_INDEX, &wifi_channel, sizeof(wifi_channel));
    if (ret > 0) {
        //读取成功
        printf("read flash wifi_channel:%d \n", wifi_channel);
    } else {
        //读取失败
        wifi_channel = bbm_tx_pair_wifi_channel;
        printf("use default wifi_channel:%d \n", wifi_channel);
        arp_static_table_reset_to_flash();

        ret = syscfg_write(BBM_WIFI_CH_INDEX, &wifi_channel, sizeof(wifi_channel));
        if (ret < 0) {
            printf("wifi channel write flash fail !!!\n");
        } else {
            printf("wifi channel write flash success !!!\n");
        }
    }
#endif

    //设置静态IP
    lwip_set_lan_info(&lan_setting_info);

    //设置mac地址,软件mac地址过滤
    wifi_raw_set_mac(src_mac);

    //启动wifi_raw
    wifi_raw_on(1);
    lwip_set_default_netif(WIFI_RAW_NETIF);

    //设置信道
    wifi_set_channel(wifi_channel);

    //重发时不降速
    wf_tx_speed_maintain();

#ifdef CONFIG_BBM_TX
    //raw不需要退避
    //会干扰到其他设备,暂不开启
    /* wifi_edca_parm_set(0, 255, 0, 0, 0); */
#endif

    //过滤掉一些不用的包
    filt_pack_not_need();

    //设置发送包头信息
    config_send_pkg_head(src_mac, dest_mac);

    //设置硬件bssid过滤
    wf_asic_set_bssid(bbm_bssid_mac);
    filt_not_my_bssid();

    //设置本机硬件MAC, 需要在wifi_raw_on后调用
    wf_asic_set_mac(src_mac);

    //模拟增益
#if BBM_WIFI_PA_ENABLE
    cur_pwr = WIFI_PWR_MIN;
    wifi_set_pwr(cur_pwr);
#else
    //不带PA时不需要调整该值,默认最大
#endif

    //TX创建CTP_SERVER
    //RX初始化CTP_CLIENT
    //BBM连接不需要心跳包
    server_info.k_alive_type = NOT_USE_ALIVE;
    ctp_init();
    //ctp_srv_set_keep_alive_timeout(10*1000);

#ifdef CONFIG_BBM_RX
    //初始化RX端配对表
    arp_static_table_init();
#else
    // arp/mac映射
    lwip_etharp_add_static_entry(default_dest_ip, dest_mac);
#endif

    //添加定时器,打印内存及网络信息
    net_state_timer = sys_timer_add_to_task("app_core", NULL, wifi_raw_state_timer_func, 1000);

    //上线通知在app启动之后
    bbm_online_init();
}

void wifi_raw_exit(void *priv)
{
    printf("\n========== WiFi Raw Exit ==========\n");

    //关闭BBM心跳包线程
    bbm_online_exit();

    //删除网络状态定时器
    if (net_state_timer) {
        sys_timer_del(net_state_timer);
        net_state_timer = 0;
    }

    ctp_exit();

    //Wifi Raw关闭
    wifi_raw_off();
    lwip_netif_remove(WIFI_RAW_NETIF);
    struct netif *netif = net_get_netif_handle(WIFI_RAW_NETIF);
    memset(netif, 0x00, sizeof(struct netif));
    if (netif) {
        memset(netif, 0x00, sizeof(struct netif));
    }
}

void wifi_init(void)
{
    printf("\n========== WiFi Init ==========\n");

    //添加回调,一些配置在回调里配置
    wifi_set_event_callback(wifi_event_callback);

    //Wifi启动
    wifi_on();

    //手机app需要心跳包
    server_info.k_alive_type = CTP_ALIVE;
    ctp_init();
    //ctp_srv_set_keep_alive_timeout(60*1000);

    //添加定时器,打印内存及网络信息
    net_state_timer = sys_timer_add_to_task("app_core", NULL, wifi_state_timer_func, 5 * 1000);
}

void wifi_exit(void)
{
    printf("\n========== WiFi Exit ==========\n");

    //删除网络状态定时器
    if (net_state_timer) {
        sys_timer_del(net_state_timer);
        net_state_timer = 0;
    }

    ctp_exit();

    //Wifi关闭
    wifi_off();
    lwip_netif_remove(WIFI_NETIF);
    struct netif *netif = net_get_netif_handle(WIFI_NETIF);
    if (netif) {
        memset(netif, 0x00, sizeof(struct netif));
    }
}

#ifdef CONFIG_WIFI_ENABLE
int wireless_net_init(void)
{
    wifi_raw_init();
}
late_initcall(wireless_net_init);
#endif

//TODO
const char *get_root_path(void)
{
    return CONFIG_ROOT_PATH;
}
#if defined CONFIG_ENABLE_VLIST
unsigned short DUMP_PORT()
{
    return _DUMP_PORT;
}

unsigned short FORWARD_PORT()
{
    return _FORWARD_PORT;
}

unsigned short BEHIND_PORT()
{
    return _BEHIND_PORT;
}

const char *get_rec_path_0()
{
    return NULL;
}
const char *get_rec_path_1()
{
    return CONFIG_REC_PATH_0;
}
const char *get_rec_path_2()
{
    return CONFIG_REC_PATH_1;
}
const char *get_rec_path_3()
{
    return CONFIG_REC_PATH_2;
}
const char *get_rec_emr_path_1()
{
#ifdef CONFIG_EMR_REC_PATH_0
    return CONFIG_EMR_REC_PATH_0;
#else
    return NULL;
#endif
}
const char *get_rec_emr_path_2()
{
#ifdef CONFIG_EMR_REC_PATH_1
    return CONFIG_EMR_REC_PATH_1;
#else
    return NULL;
#endif
}
const char *get_rec_emr_path_3()
{
#ifdef CONFIG_EMR_REC_PATH_2
    return CONFIG_EMR_REC_PATH_2;
#else
    return NULL;
#endif
}
#endif

static int wifi_connect_sta_mac(int offset, u8 *mac, int len, int index)//存储、查找、删除连接的STA设备的mac
{
    static u8 store_mac[6 * 5] = {0};
    int i;
    offset = offset < sizeof(store_mac) ? offset : sizeof(store_mac);
    for (i = offset; i < sizeof(store_mac); i += 6) { //只支持6个mac地址
        if (index == 0) { //写入
            if (store_mac[i] == 0 || !memcmp(&store_mac[i], mac, len)) {
                memcpy(&store_mac[i], mac, len);
                break;
            }
        } else if (index == 1) { //读取
            if (store_mac[i] != 0) {
                memcpy(mac, &store_mac[i], len);
                return i + len;
            }
        } else if (index == 2) { //清空
            if (!memcmp(&store_mac[i], mac, len)) {
                memset(&store_mac[i], 0, len);
                break;
            }
        }
    }
    return 0;
}

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;

    switch (event) {

    case WIFI_EVENT_MODULE_INIT:
        puts("|network_user_callback->WIFI_EVENT_MODULE_INIT\n");
        wifi_set_smp_cfg_timeout(30);       //配置MONITOR模式超时后事件回调通知时间

        struct wifi_store_info wifi_default_mode_parm = {0};
        wifi_default_mode_parm.mode = AP_MODE;
        strcpy(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], "bbm_tx_device111");
        strcpy(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], "12345678");

        wifi_set_default_mode(&wifi_default_mode_parm, 1, 1);
        break;

    case WIFI_EVENT_MODULE_START:
        if (!get_MassProduction()) {

            u32  tx_rate_control_tab = // 不需要哪个速率就删除掉,可以动态设定
                0
                | BIT(0) //0:CCK 1M
                | BIT(1) //1:CCK 2M
                | BIT(2) //2:CCK 5.5M
                | BIT(3) //3:OFDM 6M
                | BIT(4) //4:MCS0/7.2M
                | BIT(5) //5:OFDM 9M
                | BIT(6) //6:CCK 11M
                | BIT(7) //7:OFDM 12M
                | BIT(8) //8:MCS1/14.4M
                | BIT(9) //9:OFDM 18M
                | BIT(10) //10:MCS2/21.7M
                | BIT(11) //11:OFDM 24M
                | BIT(12) //12:MCS3/28.9M
                | BIT(13) //13:OFDM 36M
                | BIT(14) //14:MCS4/43.3M
                | BIT(15) //15:OFDM 48M
                | BIT(16) //16:OFDM 54M
                | BIT(17) //17:MCS5/57.8M
                | BIT(18) //18:MCS6/65.0M
                | BIT(19) //19:MCS7/72.2M
                ;
            wifi_set_tx_rate_control_tab(tx_rate_control_tab);

        }
#if BBM_WIFI_PA_ENABLE
        cur_pwr = WIFI_PWR_MAX;
        wifi_set_pwr(cur_pwr);
#else
        //不带PA时不需要调整该值,默认最大
#endif
        break;
    case WIFI_EVENT_MODULE_STOP:
        puts("|network_user_callback->WIFI_EVENT_MODULE_STOP\n");
        break;
    case WIFI_EVENT_AP_START:
        printf("|network_user_callback->WIFI_EVENT_AP_START,CH=%d\n", wifi_get_channel());
        break;
    case WIFI_EVENT_AP_STOP:
        puts("|network_user_callback->WIFI_EVENT_AP_STOP\n");
        break;
    case WIFI_EVENT_STA_START:
        puts("|network_user_callback->WIFI_EVENT_STA_START\n");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        puts("|network_user_callback->WIFI_EVENT_MODULE_START_ERR\n");
        break;
    case WIFI_EVENT_STA_STOP:
        puts("|network_user_callback->WIFI_EVENT_STA_STOP\n");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        puts("|network_user_callback->WIFI_STA_DISCONNECT\n");
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        puts("|network_user_callback->WIFI_STA_SCAN_COMPLETED\n");
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        printf("|network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d\r\n", wifi_get_channel());
        break;
    case WIFI_EVENT_MP_TEST_START:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_START\n");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_STOP\n");
        break;
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        puts("|network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID\n");
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        puts("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL .....\n");
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_TIMEOUT:
        puts("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_TIMEOUT .....\n");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_P2P_START:
        puts("|network_user_callback->WIFI_EVENT_P2P_START\n");
        break;
    case WIFI_EVENT_P2P_STOP:
        puts("|network_user_callback->WIFI_EVENT_P2P_STOP\n");
        break;
    case WIFI_EVENT_P2P_GC_DISCONNECTED:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_DISCONNECTED\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_START:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_START\n");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_STOP\n");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED\n");
        break;
    case WIFI_EVENT_PM_SUSPEND:
        puts("|network_user_callback->WIFI_EVENT_PM_SUSPEND\n");
        break;
    case WIFI_EVENT_PM_RESUME:
        puts("|network_user_callback->WIFI_EVENT_PM_RESUME\n");
        break;
    case WIFI_EVENT_AP_ON_ASSOC:
#ifdef TCFG_WIFI_ENABLE
        lwip_set_default_netif(WIFI_NETIF);   //设置本地网卡为默认模块,兼容双网卡
#endif
        struct eth_addr *hwaddr = (struct eth_addr *)network_ctx;
        printf("WIFI_EVENT_AP_ON_ASSOC hwaddr = %02x:%02x:%02x:%02x:%02x:%02x \r\n\r\n",
               hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
        wifi_connect_sta_mac(0,  hwaddr->addr, 6, 0);//存储mac
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        hwaddr = (struct eth_addr *)network_ctx;
        struct ip4_addr ipaddr;
        dhcps_get_ipaddr(hwaddr->addr, &ipaddr);
        printf("WIFI_EVENT_AP_ON_DISCONNECTED hwaddr = %02x:%02x:%02x:%02x:%02x:%02x, ipaddr = [%d.%d.%d.%d] \r\n\r\n",
               hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5],
               ip4_addr1(&ipaddr), ip4_addr2(&ipaddr), ip4_addr3(&ipaddr), ip4_addr4(&ipaddr));
        ctp_keep_alive_find_dhwaddr_disconnect((struct eth_addr *)hwaddr->addr);
        cdp_keep_alive_find_dhwaddr_disconnect((struct eth_addr *)hwaddr->addr);
        wifi_connect_sta_mac(0,  hwaddr->addr, 6, 2);//清空mac
        break;
    case WIFI_EVENT_STA_IP_GOT_IPV6_SUCC:
        puts("network_user_callback->WIFI_EVENT_STA_IP_GOT_IPV6_SUCC");
        break;
    default:
        break;
    }

    return ret;
}



/****************************************************************************/
/* camx_uwifi.c
 *
 ****************************************************************************/

/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

#include "camx.h"
#include "iotsdk_xspp.h"

#include "app_config.h"
#include "system/includes.h"
#include "wifi/wifi_connect.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "event/net_event.h"
#include "net/assign_macaddr.h"
#include "syscfg_id.h"
#include "action.h"

#ifdef PRODUCT_TEST_ENABLE
#include "product_main.h"
#endif

#if defined CONFIG_XCIOT_ENABLE
/****************************************************************************/
/* Trace Definitions                                                        */
/****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "uwifi"
#include "xc_log.h"

/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

// 配置如果启动WIFI后在STA模式下, 是否挑选连接记忆过的信号最优WIFI
#define CAMX_UWIFI_STA_CONNECT_BEST_SSID 0
// 配置 wifi_on之后的模式,
// 0     - 为使用最后记忆的模式,
// 1     - 为强制默认模式,
// 3-200 - 为STA连接超时时间多少秒,
// 如果超时都连接不上就连接最后记忆的或者最优网络
#define CAMX_UWIFI_STA_FORCE_DEFAULT_MODE 0

// CONFIG_STATIC_IPADDR_ENABLE 记忆路由器分配的IP,下次直接使用记忆IP节省DHCP时间
#define CAMX_UWIFI_STA_STATIC_IPADDR_ENABLE 1

/****************************************************************************/
/* Private Types                                                            */
/****************************************************************************/

/****************************************************************************/
/* Private Function Prototypes                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Data                                                             */
/****************************************************************************/

// 记忆路由器分配的IP,下次直接使用记忆IP节省DHCP时间
uint8_t s_camx_wifi_use_sipaddr_flag;
// 标记是否存储ssid
char s_camx_wifi_save_ssid_flag;
// 标记是否是请求连接
char s_camx_wifi_request_connect_flag;
// 标记wifi是否开启
bool s_camx_wifi_is_on;

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

// 标记是否在配网状态
bool g_camx_wifi_netcfg_running = false;
// 标记是否在配网连接中
bool g_camx_wifi_netcfg_connecting = false;

bool g_camx_wifi_connected         = false;

char g_camx_netcfg_ble_name[64] = {0};

void camx_uwifi_netcfg_stop(void);
/****************************************************************************/
/* Private Functions                                                        */
/****************************************************************************/

#if CONFIG_WIFI_BEST_IMPL
/////////////////////////////////////////////////////
// csdk weak function
/////////////////////////////////////////////////////
#if CAMX_APP_USE_JL_SDK_1_1_X < 1 //JL SDK old(1.0.3) ;new(1.1.x)
#ifdef CONFIG_STATIC_IPADDR_ENABLE
const u8 IPV4_ADDR_CONFLICT_DETECT = 1;
#else
const u8 IPV4_ADDR_CONFLICT_DETECT = 0;
#endif /* CONFIG_STATIC_IPADDR_ENABLE */
#else
#ifdef CONFIG_STATIC_IPADDR_ENABLE
static u8 use_static_ipaddr_flag;
#endif
#endif

#ifdef CONFIG_STATIC_IPADDR_ENABLE
struct sta_ip_info {
    u8  ssid[33];
    u32 ip;
    u32 gw;
    u32 netmask;
    u32 dns;
    u8  gw_mac[6];
    u8  local_mac[6];
    u8  chanel;
};

void dns_set_server(u32 *dnsserver)
{
    struct sta_ip_info sta_ip_info;
    if (syscfg_read(VM_STA_IPADDR_INDEX,
                    &sta_ip_info,
                    sizeof(struct sta_ip_info)) < 0) {
        *dnsserver = 0;
    } else {
        *dnsserver = sta_ip_info.dns;
    }
}
#endif /* CONFIG_STATIC_IPADDR_ENABLE */

#if CAMX_UWIFI_STA_STATIC_IPADDR_ENABLE
static void uwifi_sipaddr_set_sta_ip_info(void)
{
    struct sta_ip_info sta_ip_info;
    syscfg_read(VM_STA_IPADDR_INDEX,
                (char *)&sta_ip_info,
                sizeof(struct sta_ip_info));

    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0 = (u8)(sta_ip_info.ip >> 0),
        .WIRELESS_IP_ADDR1 = (u8)(sta_ip_info.ip >> 8),
        .WIRELESS_IP_ADDR2 = (u8)(sta_ip_info.ip >> 16),
        .WIRELESS_IP_ADDR3 = (u8)(sta_ip_info.ip >> 24),

        .WIRELESS_NETMASK0 = (u8)(sta_ip_info.netmask >> 0),
        .WIRELESS_NETMASK1 = (u8)(sta_ip_info.netmask >> 8),
        .WIRELESS_NETMASK2 = (u8)(sta_ip_info.netmask >> 16),
        .WIRELESS_NETMASK3 = (u8)(sta_ip_info.netmask >> 24),

        .WIRELESS_GATEWAY0 = (u8)(sta_ip_info.gw >> 0),
        .WIRELESS_GATEWAY1 = (u8)(sta_ip_info.gw >> 8),
        .WIRELESS_GATEWAY2 = (u8)(sta_ip_info.gw >> 16),
        .WIRELESS_GATEWAY3 = (u8)(sta_ip_info.gw >> 24),
    };

    net_set_lan_info(&lan_setting_info);
    T_I(
        "<wifi> sta set sipaddr, ip(%d.%d.%d.%d/%d.%d.%d.%d), gw(%d.%d.%d.%d)",
        lan_setting_info.WIRELESS_IP_ADDR0,
        lan_setting_info.WIRELESS_IP_ADDR1,
        lan_setting_info.WIRELESS_IP_ADDR2,
        lan_setting_info.WIRELESS_IP_ADDR3,
        lan_setting_info.WIRELESS_NETMASK0,
        lan_setting_info.WIRELESS_NETMASK1,
        lan_setting_info.WIRELESS_NETMASK2,
        lan_setting_info.WIRELESS_NETMASK3,
        lan_setting_info.WIRELESS_GATEWAY0,
        lan_setting_info.WIRELESS_GATEWAY1,
        lan_setting_info.WIRELESS_GATEWAY2,
        lan_setting_info.WIRELESS_GATEWAY3);
}

static int uwifi_sipaddr_compare_dhcp_ipaddr(void)
{
    int rc;

    /* clean it */
    s_camx_wifi_use_sipaddr_flag = 0;

    /* read sta_ip_info */
    struct sta_ip_info msta_ip_info;
    rc = syscfg_read(
             VM_STA_IPADDR_INDEX, &msta_ip_info, sizeof(struct sta_ip_info));
    if (rc < 0) {
        T_E("Failed to  syscfg_read VM_STA_IPADDR_INDEX, rc:%d", rc);
        return -1;
    }

    /* get netif_info */
    struct netif_info netif_info;
    lwip_get_netif_info(1, &netif_info);

    // get sta mode info
    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    // get channel
    u8 sta_channel;
    sta_channel = wifi_get_channel();

    // get local_mac
    u8 gw_mac[6];
    wifi_get_bssid(gw_mac);

    // get local_mac
    u8 local_mac[6];
    wifi_get_mac(local_mac);

    T_I(
        "<wifi> last sta ip info, ssid(%s), local_mac(%02x:%02x:%02x:%02x:%02x:%02x), gw_mac(%02x:%02x:%02x:%02x:%02x:%02x)",
        msta_ip_info.ssid,
        msta_ip_info.local_mac[0],
        msta_ip_info.local_mac[1],
        msta_ip_info.local_mac[2],
        msta_ip_info.local_mac[3],
        msta_ip_info.local_mac[4],
        msta_ip_info.local_mac[5],
        msta_ip_info.gw_mac[0],
        msta_ip_info.gw_mac[1],
        msta_ip_info.gw_mac[2],
        msta_ip_info.gw_mac[3],
        msta_ip_info.gw_mac[4],
        msta_ip_info.gw_mac[5]);
    T_I(
        "<wifi> this sta ip info, ssid(%s), local_mac(%02x:%02x:%02x:%02x:%02x:%02x), gw_mac(%02x:%02x:%02x:%02x:%02x:%02x)",
        info.ssid,
        local_mac[0],
        local_mac[1],
        local_mac[2],
        local_mac[3],
        local_mac[4],
        local_mac[5],
        gw_mac[0],
        gw_mac[1],
        gw_mac[2],
        gw_mac[3],
        gw_mac[4],
        gw_mac[5]);

    if (!strcmp(info.ssid, msta_ip_info.ssid) &&
        !memcmp(local_mac, msta_ip_info.local_mac, 6) &&
        !memcmp(gw_mac, msta_ip_info.gw_mac, 6)
        /*&& sta_ip_info.gw==sta_ip_info.dns//如果路由器没接网线/没联网,每次连接都去重新获取DHCP*/
       ) {
        s_camx_wifi_use_sipaddr_flag = 1;
        T_I("<wifi> compare_dhcp_ipaddr Match");
        return 0;
    } else {
        T_I("<wifi> compare_dhcp_ipaddr UnMatch");
        return (-1);
    }
}

static void uwifi_sipaddr_store_dhcp_ipaddr(void)
{
    struct sta_ip_info sta_ip_info = { 0 };
    u8                 sta_channel;
    u8                 local_mac[6];
    u8                 gw_mac[6];

    // 记忆IP匹配成功,不需要重新保存
    if (s_camx_wifi_use_sipaddr_flag) {
        return;
    }

    struct netif_info netif_info;
    lwip_get_netif_info(1, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    sta_channel = wifi_get_channel();
    wifi_get_mac(local_mac);
    wifi_get_bssid(gw_mac);

    strcpy(sta_ip_info.ssid, info.ssid);
    memcpy(sta_ip_info.gw_mac, gw_mac, 6);
    memcpy(sta_ip_info.local_mac, local_mac, 6);
    sta_ip_info.ip      = netif_info.ip;
    sta_ip_info.netmask = netif_info.netmask;
    sta_ip_info.gw      = netif_info.gw;
    sta_ip_info.chanel  = sta_channel;
    sta_ip_info.dns     = *(u32 *)dns_getserver(0);

    syscfg_write(VM_STA_IPADDR_INDEX,
                 (char *)&sta_ip_info,
                 sizeof(struct sta_ip_info));

    puts("store_dhcp_ipaddr\r\n");
}

#endif /* CAMX_UWIFI_STA_STATIC_IPADDR_ENABLE */

static void uwifi_sta_save_ssid(void)
{
    if (s_camx_wifi_save_ssid_flag) {
        s_camx_wifi_save_ssid_flag = 0;

        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        wifi_store_mode_info(STA_MODE, info.ssid, info.pwd);
        T_I("<wifi>, save sta ssid(%s) pwd(%s)", info.ssid, info.pwd);
        //小内存，配网后重启
        /* reboot_async(1500); */


    }
}

static void uwifi_sta_connect(char *ssid, char *pwd, char save)
{
    s_camx_wifi_save_ssid_flag       = save;
    s_camx_wifi_request_connect_flag = 1;
    wifi_set_sta_connect_best_ssid(0);
    wifi_enter_sta_mode(ssid, pwd);
    T_I("<wifi>, do sta connect, ssid(%s) pwd(%s), save(%d)",
        ssid,
        pwd,
        save);
}

static void uwifi_sta_get_info(camx_uwifi_sta_info_t *info)
{
    memset(info, 0, sizeof(camx_uwifi_sta_info_t));
    // ssid/pwd
    {
        struct wifi_mode_info mode_info;
        mode_info.mode = STA_MODE;
        wifi_get_mode_cur_info(&mode_info);

        // fill it
        snprintf(info->ssid, sizeof(info->ssid), "%s", mode_info.ssid);
        snprintf(info->pwd, sizeof(info->pwd), "%s", mode_info.pwd);
    }

    // channel
    info->channel = wifi_get_channel();

    // local_mac/gw_mac
    {
        u8 local_mac[6], gw_mac[6];
        wifi_get_mac(local_mac);
        wifi_get_bssid(gw_mac);

        snprintf(info->local_mac,
                 sizeof(info->local_mac),
                 "%02x:%02x:%02x:%02x:%02x:%02x",
                 local_mac[0],
                 local_mac[1],
                 local_mac[2],
                 local_mac[3],
                 local_mac[4],
                 local_mac[5]);
        snprintf(info->gw_mac,
                 sizeof(info->gw_mac),
                 "%02x:%02x:%02x:%02x:%02x:%02x",
                 gw_mac[0],
                 gw_mac[1],
                 gw_mac[2],
                 gw_mac[3],
                 gw_mac[4],
                 gw_mac[5]);
    }
    // ipaddr/netmask/gateway
    {
        /* get local ipaddr */
        osal_ipaddr_t localaddr;
        int           rc = osal_local_ipaddr(&localaddr);
        if (rc) {
            T_E("Failed to osal_local_ipaddr, rc:%d", rc);
        } else {
            T_I("~~~~localip:%s", localaddr.addr);
        }

        struct netif_info netif_info;
        lwip_get_netif_info(1, &netif_info);

        snprintf(info->ipaddr,
                 sizeof(info->ipaddr),
                 "%d.%d.%d.%d",
                 (u8)(netif_info.ip >> 0),
                 (u8)(netif_info.ip >> 8),
                 (u8)(netif_info.ip >> 16),
                 (u8)(netif_info.ip >> 24));
        snprintf(info->netmask,
                 sizeof(info->netmask),
                 "%d.%d.%d.%d",
                 (u8)(netif_info.netmask >> 0),
                 (u8)(netif_info.netmask >> 8),
                 (u8)(netif_info.netmask >> 16),
                 (u8)(netif_info.netmask >> 24));
        snprintf(info->gateway,
                 sizeof(info->gateway),
                 "%d.%d.%d.%d",
                 (u8)(netif_info.gw >> 0),
                 (u8)(netif_info.gw >> 8),
                 (u8)(netif_info.gw >> 16),
                 (u8)(netif_info.gw >> 24));
    }
    // dns1/dns2
    {
        u32 dns1 = *(u32 *)dns_getserver(0);
        snprintf(info->dns1,
                 sizeof(info->dns1),
                 "%d.%d.%d.%d",
                 (u8)(dns1 >> 0),
                 (u8)(dns1 >> 8),
                 (u8)(dns1 >> 16),
                 (u8)(dns1 >> 24));

#if 0
        u32 dns2 = *(u32 *)dns_getserver(1);
        snprintf(info->dns2,
                 sizeof(info->dns2),
                 "%d.%d.%d.%d",
                 (u8)(dns2 >> 0),
                 (u8)(dns2 >> 8),
                 (u8)(dns2 >> 16),
                 (u8)(dns2 >> 24));
#endif
    }
}

static u8 bat_flag = 0;
int push_wifi_cqi(void)
{

    dev_base_info_t info = {0};

    int i = wifi_get_cqi();
    if (i >= 80) {
        info.netQos = 6;
    } else if (i >= 60 && i < 80) {
        info.netQos = 5;
    } else if (i >= 40 && i < 60) {
        info.netQos = 4;
    } else if (i >= 20 && i < 40) {
        info.netQos = 3;
    } else if (i >= 0 && i < 20) {
        info.netQos = 2;
    } else {
        info.netQos = 1;
    }
    int TIMEZONE = db_select("tzone");

    if (TIMEZONE > 8000) {
        int t1 = (TIMEZONE ^ 0x7FFF) + 1;
        TIMEZONE = -(t1 & 0x7FFF);
    }


#if 1
    u8 vbat;
    vbat = get_vbat_percent();

    info.batteryLevel = vbat;
    printf("info.batteryLevel ===%d\n", info.batteryLevel);

    if (info.batteryLevel < 20 && bat_flag == 0) { //低电量提醒
        int ret = 0;
        iot_event_opt_t event = {
            .channel = 0,
            .id = E_IOT_EVENT_LOW_BATTERY,
            .value = 0,
            .utc_ms = 0,
            .isCS = true
        };
        ret = avsdk_push_event(&event);
        if (ret < 0) {
            //事件上报失败
            return -1;
        } else if (ret == 0) {
            bat_flag = 1;
            printf("avsdk_push_event E_IOT_EVENT_LOW_BATTERY success!!!!!!\n");
            //事件上报成功
            /* return 0; */
        }

    } else {
        bat_flag = 0; //低电量上报一次后不再上报
    }
#endif

    info.timeOffset = TIMEZONE;

    T_D("info.timeOffset = %d", info.timeOffset);

    printf("info.netQos ====%d\n", info.netQos);
    avsdk_push_info(&info);
    return 0;
}

static int uwifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;

    /* net event */
    struct net_event net = { 0 };
    net.arg              = "net";

    switch (event) {
    case WIFI_EVENT_MODULE_INIT:
        T_I("===<`wifi_event`>===, WIFI_EVENT_MODULE_INIT");
        {
            // 配置STA模式连接超时后事件回调通知时间
            // todo
            wifi_set_sta_connect_timeout(140);

            // 默认配置
            struct wifi_store_info param;

            /* clean it */
            memset(&param, 0, sizeof(struct wifi_store_info));

            /* fill param */
            param.mode = STA_MODE;
            snprintf((char *)param.ssid[param.mode - STA_MODE],
                     sizeof(param.ssid[param.mode - STA_MODE]),
                     "%s",
                     CAMX_UWIFI_DEFULT_STA_SSID);
            snprintf((char *)param.pwd[param.mode - STA_MODE],
                     sizeof(param.pwd[param.mode - STA_MODE]),
                     "%s",
                     CAMX_UWIFI_DEFULT_STA_PWD);
            param.connect_best_network = CAMX_UWIFI_STA_CONNECT_BEST_SSID;

            // 配置STA模式情况下,把默认配置SSID也存储起来,
            // 以后即使保存过其他SSID,也不会覆盖丢失,
            // 使用连接最优信号SSID策略的情况下可以匹配连接
            wifi_set_default_mode(
                &param, CAMX_UWIFI_STA_FORCE_DEFAULT_MODE, 0);
        }
        break;
    case WIFI_EVENT_MODULE_START:
        T_I("===<`wifi_event`>===, WIFI_EVENT_MODULE_START");
        {
            struct wifi_mode_info info;
            info.mode = NONE_MODE;
            wifi_get_mode_cur_info(&info);
            if (info.mode == STA_MODE) {
                T_I("<wifi> sta will connect, ssid(%s), pwd(%s)",
                    info.ssid,
                    info.pwd);
            } else {
                /* T_I("<wifi> mode(%d) not support", (int)info.mode); */
                if (info.mode == AP_MODE) {

                    T_I("<wifi> module_start ap_ mode");
                } else {
                    T_I("<wifi> mode(%d) not support", (int)info.mode);
                }
            }

            u32 tx_rate_control_tab = // 不需要哪个速率就删除掉,可以动态设定
                0 | BIT(0) //0:CCK 1M
                | BIT(1)   //1:CCK 2M
                | BIT(2)   //2:CCK 5.5M
                | BIT(3)   //3:OFDM 6M
                | BIT(4)   //4:MCS0/7.2M
                | BIT(5)   //5:OFDM 9M
                | BIT(6)   //6:CCK 11M
                | BIT(7)   //7:OFDM 12M
                | BIT(8)   //8:MCS1/14.4M
                | BIT(9)   //9:OFDM 18M
                | BIT(10)  //10:MCS2/21.7M
                | BIT(11)  //11:OFDM 24M
                | BIT(12)  //12:MCS3/28.9M
                | BIT(13)  //13:OFDM 36M
                | BIT(14)  //14:MCS4/43.3M
                | BIT(15)  //15:OFDM 48M
                | BIT(16)  //16:OFDM 54M
                | BIT(17)  //17:MCS5/57.8M
                | BIT(18)  //18:MCS6/65.0M
                | BIT(19)  //19:MCS7/72.2M
                ;
            // TX速率表，不需要哪个速率就删除掉,可以动态设定
            wifi_set_tx_rate_control_tab(tx_rate_control_tab);
            // 把WIFI模拟功率调整到最低档位节电
            // wifi_set_pwr(0);
        }
        break;
    case WIFI_EVENT_MODULE_STOP:
        T_I("===<`wifi_event`>===, WIFI_EVENT_MODULE_STOP");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        T_I("===<`wifi_event`>===, WIFI_EVENT_MODULE_START_ERR");
        break;
    case WIFI_EVENT_STA_START:
        T_I("===<`wifi_event`>===, WIFI_EVENT_STA_START");
        break;
    case WIFI_EVENT_STA_STOP:
        T_I("===<`wifi_event`>===, WIFI_EVENT_STA_STOP");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        T_I("===<`wifi_event`>===, WIFI_EVENT_STA_STOP");
        /*wifi_rxfilter_cfg(0);*/
        net.event = NET_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        // 如果是应用程序主动请求连接导致断线就不需要发送重连事件,
        // 否则像信号不好导致断线的原因就发送重连事件
        if (!s_camx_wifi_request_connect_flag) {
            net.event = NET_EVENT_DISCONNECTED_AND_REQ_CONNECT;
            net_event_notify(NET_EVENT_FROM_USER, &net);
        }
        g_camx_wifi_connected = false;
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        T_I("===<`wifi_event`>===, WIFI_EVENT_STA_SCAN_COMPLETED");
        // 通知门锁网络连接中

        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        T_I("===<`wifi_event`>===, WIFI_EVENT_STA_CONNECT_SUCC");
        {
            // bssid

            u8 bssid[6];
            wifi_get_bssid(bssid);

            // wifi info
            struct wifi_mode_info info;
            info.mode = NONE_MODE;
            wifi_get_mode_cur_info(&info);

            T_I(
                "wifi sta, connected ch(%d), bssid(%02x:%02x:%02x:%02x:%02x:%02x),ssid(%s),pwd(%s)",
                wifi_get_channel(),
                bssid[0],
                bssid[1],
                bssid[2],
                bssid[3],
                bssid[4],
                bssid[5],
                info.ssid,
                info.pwd);
            // 过滤not_my_bssid,如果需要使用扫描空中SSID就不要过滤
            /* wifi_rxfilter_cfg(3); */
#if CAMX_UWIFI_STA_STATIC_IPADDR_ENABLE >0
            if (0 == uwifi_sipaddr_compare_dhcp_ipaddr()) {
                uwifi_sipaddr_set_sta_ip_info();
                ret = 1;
            }
#endif


        }
        break;
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        T_I(
            "===<`wifi_event`>===, WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID");
        {
            net.event = NET_CONNECT_TIMEOUT_NOT_FOUND_SSID;
            net_event_notify(NET_EVENT_FROM_USER, &net);
        }
        break;
#if CAMX_APP_USE_JL_SDK_1_1_X > 0
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        T_I(
            "===<`wifi_event`>===, WIFI_STA_CONNECT_ASSOCIAT_FAIL");
        {
            // net.arg = "net";
            net.event = NET_CONNECT_ASSOCIAT_FAIL;
            net_event_notify(NET_EVENT_FROM_USER, &net);
            camx_plat_reset(0);

        }
        break;
#else
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_ASSOCIAT_FAIL:
        T_I(
            "===<`wifi_event`>===, WIFI_STA_CONNECT_ASSOCIAT_FAIL");
        {
            // net.arg = "net";
            net.event = NET_CONNECT_TIMEOUT_ASSOCIAT_FAIL;
            net_event_notify(NET_EVENT_FROM_USER, &net);
        }
        break;
#endif
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        /* T_I( */
        /* "===<`wifi_event`>===, WIFI_EVENT_STA_CONNECT_TIMEOUT_ASSOCIAT_FAIL"); */
    {
        // 有些使用了加密的路由器刚获取IP地址后前几个包都会没响应
        // 怀疑路由器没转发成功
        extern void connect_broadcast(void);
        connect_broadcast();

        // 确认获取IP成功再真正去考虑要不要保存配置,
        // 否则如果配置有误就保存的情况下导致下次连不上WIFI
        uwifi_sta_save_ssid();

#if CAMX_UWIFI_STA_STATIC_IPADDR_ENABLE >0
        // 保存当前dhcp 信息
        uwifi_sipaddr_store_dhcp_ipaddr();
#endif

        // 连接成功清除标记
        s_camx_wifi_request_connect_flag = 0;
        g_camx_wifi_connected = true;

        sys_timer_add_to_task("sys_timer", NULL, push_wifi_cqi, 5000);
        // notify
        net.event = NET_EVENT_CONNECTED;
        net_event_notify(NET_EVENT_FROM_USER, &net);

#if 1
        camx_uwifi_netcfg_stop();
#endif
        /* network_mssdp_init(); */
        /* void check_platform(); */
        /* check_platform(); */
        // 通知门锁网络连接成功
        //CAMX_ZUSP_SEND_EVT_NETSTA_ROUTER_CONNECTED(camx_dev_ptr);
    }
    break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        T_I(
            "===<`wifi_event`>===, WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT");
        break;
    case WIFI_EVENT_PM_SUSPEND:
        T_I("===<`wifi_event`>===, WIFI_EVENT_PM_SUSPEND");
        break;
    case WIFI_EVENT_PM_RESUME:
        T_I("===<`wifi_event`>===, WIFI_EVENT_PM_RESUME");
        break;
    case WIFI_EVENT_AP_START:
        T_I("network_user_callback->WIFI_EVENT_AP_START,CH=%d", wifi_get_channel());
        //wifi_rxfilter_cfg(7);    //过滤广播+多播+not_my_bssid
        break;

    default:
        T_I("===<`wifi_event`>===, unkown(%d)", (int)event);
        break;
    }

    return ret;
}

static void uwifi_init(void)
{
    // sta模式下最多保存的SSID数目，工程中默认为5
    wifi_set_store_ssid_cnt(NETWORK_SSID_INFO_CNT);
    // WIFI事件回调函数
    wifi_set_event_callback(uwifi_event_callback);
    // wifi_on之后即可初始化服务器类型的网络应用程序
    wifi_on();
    s_camx_wifi_is_on = true;
}
#endif /* CONFIG_WIFI_BEST_IMPL */

/****************************************************************************/
/* Public Functions                                                         */
/****************************************************************************/

void camx_uwifi_init(void)
{

#if CONFIG_WIFI_BEST_IMPL
    uwifi_init();
#endif /* CONFIG_WIFI_BEST_IMPL */

}
void camx_uwifi_enter_ap_mode(const char *ssid, const char *pwd)
{
    wifi_enter_ap_mode(ssid, pwd);
    wifi_store_mode_info(AP_MODE, ssid, pwd);
}
bool camx_uwifi_sta_connected(void)
{
    return g_camx_wifi_connected;
}
void camx_uwifi_netcfg_start(void)
{

    if (g_camx_wifi_netcfg_running == false) {

        // wifi_off
        if (s_camx_wifi_is_on) {
            //wifi_off();//todo
            /* osal_mdelay(1000); */
            s_camx_wifi_is_on = false;
        }

        // 获取wifi ssid 和 passed
        char g_camx_netcfg_wifi_pwd[64];
        avsdk_get_wifi_conf(g_camx_netcfg_ble_name, g_camx_netcfg_wifi_pwd);
        T_I("netcfg  blename(`%s`)", g_camx_netcfg_ble_name);

        // start ble
        //蓝牙配网占code 110k

        //双倍备份空间不够，用AP配网
        camx_netcfg_ble_start();

        qr_net_cfg_init();


        //进入AP模式
        //wifi_on();
        //camx_uwifi_enter_ap_mode(g_camx_netcfg_ble_name,g_camx_netcfg_wifi_pwd);

        // mark under netcfg
        g_camx_wifi_netcfg_running = true;

        //60s还没配网杀掉配网相关线程
        sys_timer_add_to_task("sys_timer", NULL, camx_uwifi_netcfg_stop, 60 * 1000);
    }

    g_camx_wifi_netcfg_connecting = false;

    // /* player file */
    // camx_audio_player_file_NetCfgEnter();
    /* os stats */
    camx_plat_os_stats();

}

void camx_uwifi_netcfg_stop(void)
{
    if (g_camx_wifi_netcfg_running) {
        g_camx_wifi_netcfg_running = false;

        // stop ble
        camx_netcfg_ble_stop();
        //stop 二维码配网
        qr_net_cfg_uninit();

    }

    // connecting stop
    g_camx_wifi_netcfg_connecting = false;

    /* os stats */
    camx_plat_os_stats();
}

void camx_uwifi_sta_connect(char *ssid, char *pwd, char save)
{

    if (!s_camx_wifi_is_on) {
        wifi_on();
        s_camx_wifi_is_on = true;
    }
#if CONFIG_WIFI_BEST_IMPL
    uwifi_sta_connect(ssid, pwd, save);
#else
    wifi_sta_connect(ssid, pwd, save);
#endif /* CONFIG_WIFI_BEST_IMPL */

    // /* has netcfg */
    // g_camx_zudb_sys_param.hasnetcfg = 1;
    // CAMX_ZUDB_UPDATE2FS(CAMX_ZUDB_SYS_PARAM);

    if (g_camx_wifi_netcfg_running) {
        g_camx_wifi_netcfg_connecting = true;
    }

}

void camx_uwifi_sta_get_info(camx_uwifi_sta_info_t *info)
{

    uwifi_sta_get_info(info);

}

void camx_uwifi_show_info(void)
{

    if (!wifi_is_on()) {
        T_I("<wifi> is off");
    } else {
        struct wifi_mode_info info;
        wifi_get_mode_cur_info(&info);
        T_I(
            "<wifi> SSID(%s),PWD(%s),RSSI(%d),QOS(%d),U=%dKB/s,D=%dKB/s",
            info.ssid,
            info.pwd,
            wifi_get_rssi(),
            wifi_get_cqi(),
            wifi_get_upload_rate() / 1024,
            wifi_get_download_rate() / 1024);
    }

}



extern void led_status_speed(u32 state);
static void wifi_app_task(void *priv)
{
    if (storage_device_ready()) {
        if (0 == check_disk_upgrade()) {
            /* set_upgrade(1); */
            return;
        }
    } else {
        /* led_status_speed(5000); */
    }

    xc_main();

}

#ifdef CONFIG_XCIOT_ENABLE

int wireless_net_init(void)//主要是create wifi 线程的
{
#ifdef PRODUCT_TEST_ENABLE
    u8 product_enter_check(void);
    if (product_enter_check()) {
        return 0;
    }
#endif

    /* extern void led_status_ctl(void); */
    /* led_status_ctl(); */
    /* led_status_speed(5000); */

    return thread_fork("wifi_app_task", 10, 3096, 64, 0, wifi_app_task, NULL);
}
late_initcall(wireless_net_init);
#endif

#endif

//TODO
__attribute__((weak)) void clear_wpa_scan_record(void)
{

}


/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

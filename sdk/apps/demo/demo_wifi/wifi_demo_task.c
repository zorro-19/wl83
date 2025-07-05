#include "app_config.h"
#include "wifi/wifi_connect.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "event/net_event.h"
#include "net/assign_macaddr.h"
#include "syscfg_id.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "os/os_api.h"
#include "system/init.h"
#include "system/timer.h"

#if TCFG_WIFI_ENABLE

#define LOG_TAG             "[WIFI]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

static char save_ssid_flag, request_connect_flag;

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
static char mac_addr_succ_flag;
#endif

#ifdef CONFIG_STATIC_IPADDR_ENABLE
static u8 use_static_ipaddr_flag;
#endif

//#define WIFI_MODE_CYCLE_TEST //从起始测试模式开始(FORCE_DEFAULT_MODE=1)或者最后记忆模式开始((FORCE_DEFAULT_MODE=0)), 循环测试WIFI模式切换: ->AP_MODE ->STA_MODE ->MONITOR_MODE ->AP_MODE ...

#define FORCE_DEFAULT_MODE 0 //配置wifi_on之后的模式,0为使用最后记忆的模式, 1为强制默认模式, 3-200为STA连接超时时间多少秒,如果超时都连接不上就连接最后记忆的或者最优网络

#define AP_SSID  WIFI_AP_SSID
#define AP_PWD   WIFI_AP_PWD
#define STA_SSID WIFI_STA_SSID
#define STA_PWD  WIFI_STA_PWD
#define CONNECT_BEST_SSID  0 //配置如果啟動WIFI后在STA模式下, 是否挑选连接记忆过的信号最优WIFI

#ifdef CONFIG_STATIC_IPADDR_ENABLE
struct sta_ip_info {
    u8 ssid[33];
    u32 ip;
    u32 gw;
    u32 netmask;
    u32 dns;
    u8 gw_mac[6];
    u8 local_mac[6];
    u8 chanel;
};

static void wifi_set_sta_ip_info(void)
{
    struct sta_ip_info  sta_ip_info;
    syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    struct lan_setting lan_setting_info = {

        .WIRELESS_IP_ADDR0  = (u8)(sta_ip_info.ip >> 0),
        .WIRELESS_IP_ADDR1  = (u8)(sta_ip_info.ip >> 8),
        .WIRELESS_IP_ADDR2  = (u8)(sta_ip_info.ip >> 16),
        .WIRELESS_IP_ADDR3  = (u8)(sta_ip_info.ip >> 24),

        .WIRELESS_NETMASK0  = (u8)(sta_ip_info.netmask >> 0),
        .WIRELESS_NETMASK1  = (u8)(sta_ip_info.netmask >> 8),
        .WIRELESS_NETMASK2  = (u8)(sta_ip_info.netmask >> 16),
        .WIRELESS_NETMASK3  = (u8)(sta_ip_info.netmask >> 24),

        .WIRELESS_GATEWAY0   = (u8)(sta_ip_info.gw >> 0),
        .WIRELESS_GATEWAY1   = (u8)(sta_ip_info.gw >> 8),
        .WIRELESS_GATEWAY2   = (u8)(sta_ip_info.gw >> 16),
        .WIRELESS_GATEWAY3   = (u8)(sta_ip_info.gw >> 24),
    };

    net_set_lan_info(&lan_setting_info);
}

static int compare_dhcp_ipaddr(void)
{
    use_static_ipaddr_flag = 0;

    u8 local_mac[6];
    u8 gw_mac[6];
    struct sta_ip_info  sta_ip_info;
    struct netif_info netif_info;
    int ret = syscfg_read(VM_STA_IPADDR_INDEX, (char *)&sta_ip_info, sizeof(struct sta_ip_info));

    if (ret < 0) {
        log_info("compare_dhcp_ipaddr NO VM_STA_IPADDR_INDEX");
        return -1;
    }

    lwip_get_netif_info(WIFI_NETIF, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    wifi_get_bssid(gw_mac);
    wifi_get_mac(local_mac);

    if (!strcmp(info.ssid, (const char *)sta_ip_info.ssid)
        && !memcmp(local_mac, sta_ip_info.local_mac, 6)
        && !memcmp(gw_mac, sta_ip_info.gw_mac, 6)
        /*&& sta_ip_info.gw==sta_ip_info.dns//如果路由器没接网线/没联网,每次连接都去重新获取DHCP*/
       ) {
        use_static_ipaddr_flag = 1;
        log_info("compare_dhcp_ipaddr Match");
        return 0;
    }

    log_info("compare_dhcp_ipaddr not Match!!! [%s][%s],[0x%x,0x%x][0x%x,0x%x],[0x%x]", info.ssid, sta_ip_info.ssid, local_mac[0], local_mac[5], sta_ip_info.local_mac[0], sta_ip_info.local_mac[5], sta_ip_info.dns);

    return -1;
}

static void store_dhcp_ipaddr(void)
{
    struct sta_ip_info  sta_ip_info = {0};
    u8 sta_channel;
    u8 local_mac[6];
    u8 gw_mac[6];

    if (use_static_ipaddr_flag) { //记忆IP匹配成功,不需要重新保存
        return;
    }

    struct netif_info netif_info;
    lwip_get_netif_info(WIFI_NETIF, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    sta_channel = wifi_get_channel();
    wifi_get_mac(local_mac);
    wifi_get_bssid(gw_mac);

    strcpy((char *)sta_ip_info.ssid, info.ssid);
    memcpy(sta_ip_info.gw_mac, gw_mac, 6);
    memcpy(sta_ip_info.local_mac, local_mac, 6);
    sta_ip_info.ip =  netif_info.ip;
    sta_ip_info.netmask =  netif_info.netmask;
    sta_ip_info.gw =  netif_info.gw;
    sta_ip_info.chanel = sta_channel;
    sta_ip_info.dns = *(u32 *)dns_getserver(0);

    syscfg_write(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    log_info("store_dhcp_ipaddr");
}

void dns_set_server(u32 *dnsserver)
{
    struct sta_ip_info  sta_ip_info;
    if (syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info)) < 0) {
        *dnsserver = 0;
    } else {
        *dnsserver = sta_ip_info.dns;
    }
}

#endif

static void wifi_set_lan_setting_info(void)
{
    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0  = 192,
        .WIRELESS_IP_ADDR1  = 168,
        .WIRELESS_IP_ADDR2  = 1,
        .WIRELESS_IP_ADDR3  = 1,

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
    net_set_lan_info(&lan_setting_info);
}

static void wifi_sta_save_ssid(void)
{
    if (save_ssid_flag) {
        save_ssid_flag = 0;

        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        wifi_store_mode_info(STA_MODE, info.ssid, info.pwd);
    }
}

void wifi_return_sta_mode(void)
{
    if (!wifi_is_on()) {
        return;
    }
    struct wifi_mode_info info;
    info.mode = STA_MODE;
    int ret = wifi_get_mode_stored_info(&info);
    if (ret) {//如果没保存过SSID
        info.ssid = STA_SSID;
        info.pwd = STA_PWD;
    }
    wifi_clear_scan_result(); //根据扫描结果连接信号最优ssid之前先清除之前结果,防止之前最优信号的ssid已下线
    wifi_set_sta_connect_best_ssid(1); //自动连接保存过的最佳WIFI
    save_ssid_flag = 0;
    wifi_enter_sta_mode(info.ssid, info.pwd);
}

void wifi_sta_connect(char *ssid, char *pwd, char save)
{
    save_ssid_flag = save;
    request_connect_flag = 1;
    wifi_set_sta_connect_best_ssid(0);
    wifi_enter_sta_mode(ssid, pwd);
}

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    struct net_event net = {0};
    net.arg = "net";
    int ret = 0;

    switch (event) {
    case WIFI_EVENT_MODULE_INIT:
        wifi_set_sta_connect_timeout(30);   //配置STA模式连接超时后事件回调通知时间
        wifi_set_smp_cfg_timeout(30);       //配置MONITOR模式超时后事件回调通知时间

//    u8 airkiss_aes_key[16] = {0x65, 0x31, 0x63, 0x33, 0x36, 0x31, 0x63, 0x63,0x32, 0x39, 0x65, 0x34, 0x33, 0x66, 0x62, 0x38};
//    wifi_set_airkiss_key(airkiss_aes_key);        //配置 airkiss_aes_key

        struct wifi_store_info wifi_default_mode_parm;
        memset(&wifi_default_mode_parm, 0, sizeof(struct wifi_store_info));

#if (WIFI_TEST_MODE == AP_TEST_MODE)
        wifi_set_lan_setting_info();    //AP模式配置IP地址信息和DHCP池起始分配地址

        u8 mac_addr[6];
        char ssid[64];
        int init_net_device_mac_addr(char *macaddr, char ap_mode); //如果AP模式需要配置SSID和MAC地址相关,需要在这里先产生MAC地址
        init_net_device_mac_addr((char *)mac_addr, 1);
        sprintf((char *)ssid, AP_SSID"%02x%02x%02x%02x%02x%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        wifi_default_mode_parm.mode = AP_MODE;
        strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], (const char *)ssid, sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], (const char *)AP_PWD, sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
#elif (WIFI_TEST_MODE == STA_TEST_MODE)
        wifi_default_mode_parm.mode = STA_MODE;
        strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], (const char *)STA_SSID, sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], (const char *)STA_PWD, sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        wifi_default_mode_parm.connect_best_network = CONNECT_BEST_SSID;
#elif (WIFI_TEST_MODE == MONITOR_TEST_MODE)
        memset(&wifi_default_mode_parm, 0, sizeof(struct wifi_store_info));
        wifi_default_mode_parm.mode = SMP_CFG_MODE;
#endif
        wifi_set_default_mode(&wifi_default_mode_parm, FORCE_DEFAULT_MODE, wifi_default_mode_parm.mode == STA_MODE); //配置STA模式情况下,把默认配置SSID也存储起来,以后即使保存过其他SSID,也不会覆盖丢失,使用连接最优信号SSID策略的情况下可以匹配连接
        break;

    case WIFI_EVENT_MODULE_START:
        log_info("network_user_callback->WIFI_EVENT_MODULE_START");

        struct wifi_mode_info info;
        info.mode = NONE_MODE;
        wifi_get_mode_cur_info(&info);
        if (info.mode == SMP_CFG_MODE) {
            net.arg = "net";
            net.event = NET_EVENT_SMP_CFG_FIRST;
            net_event_notify(NET_EVENT_FROM_USER, &net);
        }

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
#if 0
        wifi_set_pwr(0); //把WIFI模拟功率调整到最低档位节电
#endif

        break;
    case WIFI_EVENT_MODULE_STOP:
        log_info("network_user_callback->WIFI_EVENT_MODULE_STOP");
        break;

    case WIFI_EVENT_AP_START:
        log_info("network_user_callback->WIFI_EVENT_AP_START,CH=%d", wifi_get_channel());
        //wifi_rxfilter_cfg(7);    //过滤广播+多播+not_my_bssid
        break;
    case WIFI_EVENT_AP_STOP:
        log_info("network_user_callback->WIFI_EVENT_AP_STOP");
        break;

    case WIFI_EVENT_STA_START:
        log_info("network_user_callback->WIFI_EVENT_STA_START");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        log_info("network_user_callback->WIFI_EVENT_MODULE_START_ERR");
        break;
    case WIFI_EVENT_STA_STOP:
        log_info("network_user_callback->WIFI_EVENT_STA_STOP");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        log_info("network_user_callback->WIFI_STA_DISCONNECT");

        /*wifi_rxfilter_cfg(0);*/

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
        if (!mac_addr_succ_flag) {
            break;
        }
#endif

        net.event = NET_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_USER, &net);

#ifndef WIFI_MODE_CYCLE_TEST
        if (!request_connect_flag) { //如果是应用程序主动请求连接导致断线就不需要发送重连事件, 否则像信号不好导致断线的原因就发送重连事件
            net.event = NET_EVENT_DISCONNECTED_AND_REQ_CONNECT;
            net_event_notify(NET_EVENT_FROM_USER, &net);
        }
#endif
        break;

    case WIFI_EVENT_STA_SCANNED_SSID:
        log_info("network_user_callback->WIFI_EVENT_STA_SCANNED_SSID");
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        log_info("network_user_callback->WIFI_STA_SCAN_COMPLETED");
#ifdef CONFIG_AIRKISS_NET_CFG
        extern void airkiss_ssid_check(void);
        airkiss_ssid_check();
#endif
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        log_info("network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d", wifi_get_channel());
        /*wifi_rxfilter_cfg(3);    //过滤not_my_bssid,如果需要使用扫描空中SSID就不要过滤*/
#ifdef CONFIG_STATIC_IPADDR_ENABLE
        if (0 == compare_dhcp_ipaddr()) {
            wifi_set_sta_ip_info();
            ret = 1;
        }
#endif

#if 0
        u8 txop_limit, cwmin, cwmax, aifsn;
        wifi_edca_parm_get(0, &txop_limit, &cwmin, &cwmax, &aifsn);
        printf("txop_limit: %d, cwmin: %d, cwmax: %d, aifsn: %d\n", txop_limit, cwmin, cwmax, aifsn);
        wifi_edca_parm_set(0, 30, 4, 10, 2);
#endif
        break;

    case WIFI_EVENT_MP_TEST_START:
        log_info("network_user_callback->WIFI_EVENT_MP_TEST_START");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        log_info("network_user_callback->WIFI_EVENT_MP_TEST_STOP");
        break;

    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        log_info("network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID");
        net.event = NET_CONNECT_TIMEOUT_NOT_FOUND_SSID;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        log_info("network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL");
        net.event = NET_CONNECT_ASSOCIAT_FAIL;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_TIMEOUT:
        log_info("network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_TIMEOUT");
        break;

    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        log_info("network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC");

        //有些使用了加密的路由器刚获取IP地址后前几个包都会没响应，怀疑路由器没转发成功
        void connect_broadcast(void);
        connect_broadcast();

        wifi_sta_save_ssid(); //确认获取IP成功再真正去考虑要不要保存配置, 否则如果配置有误就保存的情况下导致下次连不上WIFI

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
        if (!is_server_assign_macaddr_ok()) { //如果使用服务器分配MAC地址的情况,需要确认MAC地址有效才发送连接成功事件到APP层,否则先访问服务器分配mac地址
            server_assign_macaddr(wifi_return_sta_mode);
            break;
        }
        mac_addr_succ_flag = 1;
#endif
#ifdef CONFIG_STATIC_IPADDR_ENABLE
        store_dhcp_ipaddr();
#endif
        request_connect_flag = 0;
        net.event = NET_EVENT_CONNECTED;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        log_info("etwork_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT");
        break;

    case WIFI_EVENT_SMP_CFG_START:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_START");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_STOP");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT");
        net.event = NET_EVENT_SMP_CFG_TIMEOUT;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED");
        net.event = NET_SMP_CFG_COMPLETED;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_AP_ON_ASSOC:
        ;
        struct eth_addr *hwaddr = (struct eth_addr *)network_ctx;
        log_info("WIFI_EVENT_AP_ON_ASSOC hwaddr = %02x:%02x:%02x:%02x:%02x:%02x",
                 hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        struct ip4_addr ipaddr;
        hwaddr = (struct eth_addr *)network_ctx;
        dhcps_get_ipaddr(hwaddr->addr, &ipaddr);
        log_info("WIFI_EVENT_AP_ON_DISCONNECTED hwaddr = %02x:%02x:%02x:%02x:%02x:%02x, ipaddr = [%d.%d.%d.%d]",
                 hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5],
                 ip4_addr1(&ipaddr), ip4_addr2(&ipaddr), ip4_addr3(&ipaddr), ip4_addr4(&ipaddr));
        break;
    case WIFI_EVENT_STA_IP_GOT_IPV6_SUCC:
        log_info("network_user_callback->WIFI_EVENT_STA_IP_GOT_IPV6_SUCC");
        break;

    default:
        break;
    }

    return ret;
}

static void wifi_rx_cb(void *rxwi, struct ieee80211_frame *wh, void *data, u32 len, void *priv)
{
    char *str_frm_type;

    switch (wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) {
    case IEEE80211_FC0_TYPE_MGT:
        switch (wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) {
        case IEEE80211_FC_STYPE_ASSOC_REQ:
            str_frm_type = "association req";
            break;
        case IEEE80211_FC_STYPE_ASSOC_RESP:
            str_frm_type = "association resp";
            break;
        case IEEE80211_FC_STYPE_REASSOC_REQ:
            str_frm_type = "reassociation req";
            break;
        case IEEE80211_FC_STYPE_REASSOC_RESP:
            str_frm_type = "reassociation resp";
            break;
        case IEEE80211_FC_STYPE_PROBE_REQ:
            str_frm_type = "probe req";
            break;
        case IEEE80211_FC_STYPE_PROBE_RESP:
            str_frm_type = "probe resp";
            break;
        case IEEE80211_FC_STYPE_BEACON:
            str_frm_type = "beacon";
            break;
        case IEEE80211_FC_STYPE_ATIM:
            str_frm_type = "atim";
            break;
        case IEEE80211_FC_STYPE_DISASSOC:
            str_frm_type = "disassociation";
            break;
        case IEEE80211_FC_STYPE_AUTH:
            str_frm_type = "authentication";
            break;
        case IEEE80211_FC_STYPE_DEAUTH:
            str_frm_type = "deauthentication";
            break;
        case IEEE80211_FC_STYPE_ACTION:
            str_frm_type = "action";
            break;
        default:
            str_frm_type = "unknown mgmt";
            break;
        }
        break;
    case IEEE80211_FC0_TYPE_CTL:
        str_frm_type = "control";
        break;
    case IEEE80211_FC0_TYPE_DATA:
        str_frm_type = "data";
        break;
    default:
        str_frm_type = "unknown";
        break;
    }

    log_info("wifi recv:%s", str_frm_type);
}

static void wifi_status(void *p)
{
    if (wifi_is_on()) {
        /* stats_display(); //LWIP stats */
        log_info("WIFI U= %d KB/s, D= %d KB/s", wifi_get_upload_rate() / 1024, wifi_get_download_rate() / 1024);

        struct wifi_mode_info info;
        info.mode = NONE_MODE;
        wifi_get_mode_cur_info(&info);
        if (info.mode == AP_MODE) {
            for (int i = 0; i < 8; i++) {
                char *rssi;
                u8 *evm, *mac;
                if (wifi_get_sta_entry_rssi(i, &rssi, &evm, &mac)) {
                    break;
                }
                if (*rssi) { //侦测连接到AP端的设备信号质量
                    log_info("MAC[%x:%x:%x:%x:%x:%x],RSSI=%d,EVM=%d", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], *rssi, *evm);
                }
            }
        } else if (info.mode == STA_MODE) {
            log_info("Router_RSSI=%d,Quality=%d", wifi_get_rssi(), wifi_get_cqi()); //侦测路由器端信号质量
        }
    }
}

char *check_enc_mode(int enc)
{
    if (ENC_MODE_BIT_IS_SET(enc, ENC_WPA3)) {
        return "ENC_WPA3";
    } else if (ENC_MODE_BIT_IS_SET(enc, ENC_WPA2)) {
        return "ENC_WPA2";
    } else if (ENC_MODE_BIT_IS_SET(enc, ENC_WPA)) {
        return "ENC_WPA";
    } else if (ENC_MODE_BIT_IS_SET(enc, ENC_WEP)) {
        return "ENC_WEP";
    } else {
        return "ENC_NONE";
    }
}

static void wifi_scan_test(void)
{
    struct wifi_scan_ssid_info *sta_ssid_info;
    u32 sta_ssid_num;

    wifi_clear_scan_result();// 测试之前清掉之前连接路由器的扫描缓存,也可以放在STA连上后调用

    wifi_scan_req();

#if 0//若用户为了实时显示，每扫描到1个通道及时获取扫描到的结果, 甚至可以每扫描到一个SSID就马上获取结果

    for (char ch = 1; ch < 14; ch++) { //扫描13个信道
        os_time_dly(22); //根据MAX_CHANNEL_TIME_BSS_INFRA简单等待一些时间, 或者通过信号量/标志位 等待事件 WIFI_EVENT_STA_SCANNED_SSID 扫描到SSID之后才去获取结果
        sta_ssid_num = 0;
        sta_ssid_info = wifi_get_scan_result(&sta_ssid_num);
        log_info("wifi_sta_scan_channel_test channel %d, ssid_num =%d", ch, sta_ssid_num);
        for (int i = 0; i < sta_ssid_num; i++) {
            log_info("wifi_sta_scan_channel_test ssid = [%s],rssi = %d,snr = %d, enc = %s", sta_ssid_info[i].ssid, sta_ssid_info[i].rssi, sta_ssid_info[i].snr, check_enc_mode(sta_ssid_info[i].enc));
        }
        free(sta_ssid_info);
    }

#else//等待所有信道扫描完成再获取结果, 对CPU性能更友好

    os_time_dly(4 * 100); //根据MAX_CHANNEL_TIME_BSS_INFRA简单等待一些时间, 或者通过信号量/标志位 等待事件 WIFI_EVENT_STA_SCAN_COMPLETED 扫描完成之后才去获取结果
    sta_ssid_num = 0;
    sta_ssid_info = wifi_get_scan_result(&sta_ssid_num);
    log_info("wifi_sta_scan_test ssid_num =%d", sta_ssid_num);

    for (int i = 0; i < sta_ssid_num; i++) {
        log_info("wifi_sta_scan_test ssid = [%s],rssi = %d,snr = %d, enc = %s", sta_ssid_info[i].ssid, sta_ssid_info[i].rssi, sta_ssid_info[i].snr, check_enc_mode(sta_ssid_info[i].enc));
    }

    free(sta_ssid_info);
#endif

    static u8 scan_cnt;
    if (++scan_cnt > 4) { //累积多几次扫描结果再去清空列表, 有利于显示出更多ssid,长期不清空有可能会导致ssid已下线都不知道
        scan_cnt = 0;
        wifi_clear_scan_result();//若使用连接最优WIFI(connect_best_network)的情况下,如果不使用等待WIFI_EVENT_STA_SCAN_COMPLETED事件的方式, 在WIFI还未连接成功的情况下,有概率会造成wifi内部获取的结果被这里清空导致当次获取不到空中准备WIFI列表,需要等到下次扫描结果,因此如果使用connect_best_network的情况下,推荐使用等待事件 WIFI_EVENT_STA_SCAN_COMPLETED 扫描完成之后才去获取结果
    }
}

static void wifi_demo_task(void *priv)
{
#if 1

    wifi_set_store_ssid_cnt(NETWORK_SSID_INFO_CNT);
    wifi_set_event_callback(wifi_event_callback);

    wifi_on();

    //wifi_on之后即可初始化服务器类型的网络应用程序
#ifdef CONFIG_IPERF_ENABLE
    extern void iperf_test(void);
    iperf_test();
#endif

    sys_timer_add_to_task("app_core", NULL, wifi_status, 60 * 1000); //打印一下WIFI一些信息

#if 0 //一个简单存储SSID测试
    u8 ssid_stored_cnt;
    struct wifi_stored_sta_info wifi_stored_sta_info[32];

    os_time_dly(5 * 100); //假设等待已经连接上路由器
    wifi_store_mode_info(STA_MODE, "GJ12", "123456789");
    wifi_store_mode_info(STA_MODE, "WL83", "12345678");
    wifi_store_mode_info(STA_MODE, "WIFI_PS_TEST", "12345678");

    ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
    for (int i = 0; i < ssid_stored_cnt; i++) {
        printf("1:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
    }

    wifi_del_stored_sta_info("WIFI_PS_TEST"); //中途删除掉其中一个存储过的SSID

    ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
    for (int i = 0; i < ssid_stored_cnt; i++) {
        printf("2:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
    }
#endif

    while (1) {
#if (defined WIFI_MODE_CYCLE_TEST)
        char ssid[64];
        u8 mac_addr[6];
        wifi_get_mac(mac_addr);
        sprintf((char *)ssid, AP_SSID"%02x%02x%02x%02x%02x%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        wifi_set_lan_setting_info();    //AP模式配置IP地址信息和DHCP池起始分配地址
        wifi_enter_ap_mode(ssid, AP_PWD);

        os_time_dly(60 * 100);

        wifi_sta_connect(STA_SSID, STA_PWD, 0);

        os_time_dly(60 * 100);

        wifi_enter_smp_cfg_mode();
        wifi_set_frame_cb(wifi_rx_cb, NULL); //注册接收802.11数据帧回调

        os_time_dly(60 * 100);
        wifi_set_frame_cb(NULL, NULL);

#elif (WIFI_TEST_MODE == MONITOR_TEST_MODE)
        wifi_enter_smp_cfg_mode();
        wifi_set_frame_cb(wifi_rx_cb, NULL); //注册接收802.11数据帧回调
        while (1) {
            os_time_dly(50 * 100);
        }
#else
        os_time_dly(50 * 100);
//        wifi_off();
        os_time_dly(5 * 100);
//        wifi_on();

//wifi_scan_test();
#endif // WIFI_MODE_CYCLE_TEST
    }
#else

    //wifi raw 测试
    wifi_raw_test();
    while (1) {
        os_time_dly(50 * 100);
    }
#endif
}

static int demo_wifi(void)
{
#ifndef RF_FCC_TEST_ENABLE
    return os_task_create(wifi_demo_task, NULL, 10, 1000, 0, "wifi_demo_task");
#endif
}
late_initcall(demo_wifi);

#endif

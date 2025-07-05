#include "wifi/wifi_connect.h"
#include "os/os_api.h"
#include "app_config.h"
#include "event/net_event.h"
#include "syscfg/syscfg_id.h"
#include "system/init.h"
#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
#include "net/assign_macaddr.h"
#include "net/config_network.h"
#endif

#ifdef CONFIG_NET_ENABLE

#define LOG_TAG             "[WIFI_APP]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

#define CONNECT_TIMEOUT_SEC	60

static struct {
    u32 use_static_ipaddr_flag : 1;
    u32 net_app_init_flag : 1;
    u32 request_connect_flag : 1;
    u32 save_ssid_flag : 1;
    u32 mac_addr_succ_flag : 1;
    u32 reserved : 26;
} wifi_app_hdl;

#define __this	(&wifi_app_hdl)

#if 1
#define INIT_MODE STA_MODE
#define FORCE_DEFAULT_MODE 1
#else
#define INIT_MODE SMP_CFG_MODE
#define FORCE_DEFAULT_MODE 0 //配置wifi_on之后的模式,0为使用最后记忆的模式, 1为强制默认模式, 3-200为连接超时时间多少秒,如果超时都连接不上就连接最后记忆的或者最优网络
#endif
#define INIT_STORED_SSID (INIT_MODE==STA_MODE)//配置STA模式情况下,把默认配置SSID也存储起来, 以后即使保存过其他SSID,也不会覆盖丢失,使用连接最优信号SSID策略的情况下可以匹配连接
#define INIT_CONNECT_BEST_SSID 1 //配置如果啟動WIFI后在STA模式下, 是否挑选连接记忆过的信号最优WIFI

#define WIFI_FORCE_DEFAULT_MODE  FORCE_DEFAULT_MODE
#define WIFI_INIT_MODE  INIT_MODE
#define WIFI_INIT_SSID INIT_SSID
#define WIFI_INIT_PWD INIT_PWD
#define WIFI_INIT_CONNECT_BEST_SSID  INIT_CONNECT_BEST_SSID
#define WIFI_INIT_STORED_SSID  INIT_STORED_SSID

void wifi_return_sta_mode(void)
{
    if (!wifi_is_on()) {
        return;
    }
    int ret;
    struct wifi_mode_info info;
    info.mode = STA_MODE;
    ret = wifi_get_mode_stored_info(&info);
    if (ret) {//如果没保存过SSID
        info.ssid = WIFI_INIT_SSID;
        info.pwd = WIFI_INIT_PWD;
    }
    wifi_clear_scan_result(); //根据扫描结果连接信号最优ssid之前先清除之前结果,防止之前最优信号的ssid已下线
    wifi_set_sta_connect_best_ssid(1);
    wifi_enter_sta_mode(info.ssid, info.pwd);

    __this->save_ssid_flag = 0;
}

static int wifi_is_in_smp_cfg_mode(void)
{
    struct wifi_mode_info info;
    info.mode = NONE_MODE;
    wifi_get_mode_cur_info(&info);
    return info.mode == SMP_CFG_MODE;
}

static void wifi_sta_save_ssid(void)
{
    if (__this->save_ssid_flag) {
        __this->save_ssid_flag = 0;

        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        wifi_store_mode_info(STA_MODE, info.ssid, info.pwd);
    }
}

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;
    struct net_event net = {0};

    switch (event) {

    case WIFI_EVENT_MODULE_INIT:

        struct wifi_store_info wifi_default_mode_parm;
        wifi_default_mode_parm.mode = WIFI_INIT_MODE;
        if (wifi_default_mode_parm.mode == AP_MODE || wifi_default_mode_parm.mode == STA_MODE) {
            strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], (const char *)WIFI_INIT_SSID, sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
            strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], (const char *)WIFI_INIT_PWD, sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        }
        wifi_default_mode_parm.connect_best_network = WIFI_INIT_CONNECT_BEST_SSID;
        wifi_set_default_mode(&wifi_default_mode_parm, WIFI_FORCE_DEFAULT_MODE, WIFI_INIT_STORED_SSID);
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
#if 1
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
#endif
        break;

    case WIFI_EVENT_MODULE_STOP:
        log_info("network_user_callback->WIFI_EVENT_MODULE_STOP");
        break;

    case WIFI_EVENT_AP_START:
        log_info("network_user_callback->WIFI_EVENT_AP_START");
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

    case WIFI_EVENT_STA_SCAN_COMPLETED:
        log_info("network_user_callback->WIFI_STA_SCAN_COMPLETED");
        break;

    case WIFI_EVENT_STA_CONNECT_SUCC:
        /*wifi_rxfilter_cfg(3);    //过滤not_my_bssid,如果需要使用扫描空中SSID就不要过滤*/
        log_info("network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d", wifi_get_channel());
        break;

    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        log_info("network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID");
        net.arg = "net";
        net.event = NET_CONNECT_TIMEOUT_NOT_FOUND_SSID;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        log_info("network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL");
        net.arg = "net";
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

        wifi_sta_save_ssid();

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
        if (!is_server_assign_macaddr_ok()) { //如果使用服务器分配MAC地址的情况,需要确认MAC地址有效才发送连接成功事件到APP层,否则先访问服务器分配mac地址
            server_assign_macaddr(wifi_return_sta_mode);
            break;
        }
        __this->mac_addr_succ_flag = 1;
#endif
        wifi_set_sta_connect_best_ssid(0);
        __this->request_connect_flag = 0;

        net.arg = "net";
        net.event = NET_EVENT_CONNECTED;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_STA_DISCONNECT:
        log_info("network_user_callback->WIFI_STA_DISCONNECT");

        /*wifi_rxfilter_cfg(0);*/

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
        if (!__this->mac_addr_succ_flag) {
            break;
        }
#endif
        net.arg = "net";
        net.event = NET_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_USER, &net);

        if (!wifi_is_in_smp_cfg_mode() && !__this->request_connect_flag) {
            memset(&net, 0, sizeof(net));
            net.arg = "net";
            net.event = NET_EVENT_DISCONNECTED_AND_REQ_CONNECT;
            net_event_notify(NET_EVENT_FROM_USER, &net);
        }
        break;

    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        log_info("network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT");
        break;

    case WIFI_EVENT_SMP_CFG_START:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_START");
        break;

    case WIFI_EVENT_SMP_CFG_STOP:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_STOP");
        break;

    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT");
        net.arg = "net";
        net.event = NET_EVENT_SMP_CFG_TIMEOUT;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_SMP_CFG_COMPLETED:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED");
        net.arg = "net";
        net.event = NET_SMP_CFG_COMPLETED;
        net_event_notify(NET_EVENT_FROM_USER, &net);
        break;

    case WIFI_EVENT_AP_ON_ASSOC:
        log_info("network_user_callback->WIFI_EVENT_AP_ON_ASSOC");
        break;

    case WIFI_EVENT_AP_ON_DISCONNECTED:
        log_info("network_user_callback->WIFI_EVENT_AP_ON_DISCONNECTED");
        break;

    default:
        break;
    }

    return ret;
}

static void net_app_init(void)
{
    if (__this->net_app_init_flag) {
        return;
    }
    __this->net_app_init_flag = 1;
}

static void net_app_uninit(void)
{
}

static void wifi_and_network_on(void)
{
    if (wifi_is_on()) {
        return;
    }
    wifi_on();
    net_app_init();
}

void wifi_and_network_off(void)
{
    if (wifi_is_on() == 0) {
        return;
    }
    net_app_uninit();

    wifi_off();
}

void wifi_sta_connect(char *ssid, char *pwd, char save, void *priv)
{
    if (save) {
        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        if (strcmp(info.ssid, ssid) || strcmp(info.pwd, pwd)) {
            __this->save_ssid_flag = 1;    //防止输错密码还保存ssid, 等待确保连接上路由器再保存
        }
    }

    __this->request_connect_flag = 1;
    if (save) {
        /* wifi_store_mode_info(STA_MODE,ssid,pwd); */
    }
    wifi_enter_sta_mode(ssid, pwd);
}

int get_wifi_scan_ssid_info(struct wifi_scan_ssid_info **ssid_info)
{
    struct wifi_scan_ssid_info *sta_ssid_info;
    u32 sta_ssid_num = 0;
    sta_ssid_info = wifi_get_scan_result(&sta_ssid_num);
    wifi_clear_scan_result();

    for (u32 i = 0; i < sta_ssid_num; i++) {
        log_info("find scan ssid = [%s]", sta_ssid_info[i].ssid);
    }

    *ssid_info = sta_ssid_info;
    return sta_ssid_num;
}

static void wifi_app_task(void *priv)  //主要是create wifi 线程的
{
    wifi_set_store_ssid_cnt(NETWORK_SSID_INFO_CNT);
    wifi_set_sta_connect_timeout(CONNECT_TIMEOUT_SEC);
    wifi_set_event_callback(wifi_event_callback);
    wifi_and_network_on();
}

#if TCFG_WIFI_ENABLE
static int wireless_net_init(void)   //主要是create wifi 线程的
{
    return thread_fork("wifi_app_task", 10, 1792, 0, 0, wifi_app_task, NULL);
}
late_initcall(wireless_net_init);
#endif

void wf_low_power_request(void *priv, u32 usec)
{

}

#endif

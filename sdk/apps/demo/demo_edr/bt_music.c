#include "server/server_core.h"
#include "server/audio_server.h"
#include "app_config.h"
#include "btstack/avctp_user.h"
#include "btstack/btstack_task.h"
#include "btstack/a2dp_media_codec.h"
#include "btctrler/btctrler_task.h"
#include "btcontroller_modules.h"
#include "common/include/hci_event.h"
#include "third_party/common/spp_user.h"
#include "bt_emitter.h"
#include "btstack/bluetooth.h"
#include "classic/hci_lmp.h"
#include "event/bt_event.h"
#include "syscfg/syscfg_id.h"
#include "system/timer.h"
#include "event/key_event.h"
#include "event/bt_event.h"
#include "asm/power_interface.h"

#ifdef CONFIG_BT_ENABLE

#define LOG_TAG_CONST        BT
#define LOG_TAG             "[BT]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"


#define BT_TIMEOUT_CONN_TIME      30 //超时断开之后回连的时间s
#define BT_POWERON_AUTO_CONN_TIME 18 //开机去回连的时间,要取6的倍数
#define BT_INBAND_RINGTONE        1  //播放手机彩铃

#define VOLUME_STEP 5
#define MIN_VOLUME_VALUE	5
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE  	50

void *phone_call_begin(int call_format, u8 volume);
void phone_call_end(void);
void *earphone_a2dp_audio_codec_open(int media_format, u8 volume, u8 *bt_addr);
void earphone_a2dp_audio_codec_close(u8 *bt_addr);
void get_remote_device_info_from_vm(void);
void bredr_close_all_scan(void);
void bt_set_simple_pair_flag(bool flag);
bool is_1t2_connection(void);

typedef struct {
    //phone
    u8 phone_ring_flag: 1;
    u8 phone_num_flag: 1;
    u8 phone_income_flag: 1;
    u8 phone_call_dec_begin: 1;
    u8 phone_con_sync_num_ring: 1;
    u8 phone_con_sync_ring: 1;
    u8 emitter_or_receiver: 2;

    u8 media_play_flag : 1;
    u8 call_flag : 1;	// 1-由于蓝牙打电话命令切回蓝牙模式
    u8 exit_flag : 1;	// 1-可以退出蓝牙标志
    u8 enable    : 1;
    u8 emitter   : 1;
    u8 mute      : 1;
    u8 siri_stu;		// ios siri

    u8 call_volume;
    u8 media_volume;
    u8 inband_ringtone;
    u8 auto_connection_addr[6];
    u8 income_phone_num[30];
    u8 income_phone_len;
    u16 phone_timer_id;
    u16 poweroff_timer_id;
    u16 get_music_player_timer;
    u16 auto_connection_timer;
    u16 sniff_timer;
    int auto_connection_counter;
    void *dec_server;
} app_bt_handle_t;

static app_bt_handle_t app_bt_hdl;
#define __this 	(&app_bt_hdl)

/* void (*lmp_ch_update_resume_hdl)(void *priv) = NULL; */

/*配置通话时前面丢掉的数据包包数*/
#define ESCO_DUMP_PACKET_ADJUST		1	/*配置使能*/
#define ESCO_DUMP_PACKET_DEFAULT	0
#define ESCO_DUMP_PACKET_CALL		120 /*0~0xFF*/

static u8 esco_dump_packet = ESCO_DUMP_PACKET_CALL;

#if ESCO_DUMP_PACKET_ADJUST
u8 get_esco_packet_dump(void)
{
    //log_info("esco_dump_packet:%d\n", esco_dump_packet);
    return esco_dump_packet;
}
#endif


/*开关可发现可连接的函数接口*/
static void bt_wait_phone_connect_control(u8 enable)
{
    if (!__this->enable && enable) {
        return;
    }

    if (enable) {
        log_info("is_1t2_connection:%d \t total_conn_dev:%d", is_1t2_connection(), bt_get_total_connect_dev());
        if (is_1t2_connection()) {
            /*达到最大连接数，可发现(0)可连接(0)*/
            bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
            bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
        } else {
            if (bt_get_total_connect_dev() == 1) {
                /*支持连接2台，只连接一台的情况下，可发现(0)可连接(1)*/
                bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
                bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
            } else {
                /*可发现(1)可连接(1)*/
                bt_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);
                bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
            }
        }
    } else {
        bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
        bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
    }
}

static void bt_init_ok_search_index(void)
{
    if (!__this->auto_connection_counter && bt_get_current_poweron_memory_search_index(__this->auto_connection_addr)) {
        log_info("bt_wait_connect_and_phone_connect_switch");
        bt_clear_current_poweron_memory_search_index(1);
#if TCFG_BT_DUAL_CONN_ENABLE
        bt_clear_current_poweron_memory_search_index(1);
#endif
        __this->auto_connection_counter = BT_POWERON_AUTO_CONN_TIME * 1000; //8000ms
    }
}

//蓝牙回连流程
static int bt_wait_connect_and_phone_connect_switch(void *p)
{
    int ret = 0;
    int timeout = 0;

    log_info("connect_switch: %d, %d", (int)p, __this->auto_connection_counter);

    if (!__this->enable) {
        return 0;
    }

    __this->auto_connection_timer = 0;

    if (__this->auto_connection_counter <= 0) {
        __this->auto_connection_counter = 0;
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);

        if (bt_get_current_poweron_memory_search_index(NULL)) {
            bt_init_ok_search_index();
            return bt_wait_connect_and_phone_connect_switch(0);
        } else {
            bt_wait_phone_connect_control(1);
            return 0;
        }
    }
    /* log_info(">>>phone_connect_switch=%d\n",__this->auto_connection_counter ); */
    if (!p) {
        if (__this->auto_connection_counter) {
            timeout = 4000;
            bt_wait_phone_connect_control(0);
            bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, __this->auto_connection_addr);
            ret = 1;
        }
    } else {
        timeout = 2000;
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
        bt_wait_phone_connect_control(1);
    }

    if (__this->auto_connection_counter) {
        __this->auto_connection_counter -= timeout;
        log_info("do=%d", __this->auto_connection_counter);
    }

    __this->auto_connection_timer = sys_timeout_add((void *)(!(int)p),
                                    (void (*)(void *))bt_wait_connect_and_phone_connect_switch, timeout);

    return ret;
}

//设置设备的媒体音量
static void bt_set_music_device_volume(int volume)
{
    if (volume == 0xff) {
        return;
    }

    volume = volume * 100 / 127;
    log_info("bt music set volume : %d", volume);
    __this->media_volume = volume;

    if (__this->dec_server) {
        union audio_req req = {0};
        req.dec.cmd     = AUDIO_DEC_SET_VOLUME;
        req.dec.volume  = volume;
        server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    }
}

//获取设备的通话音量
static int phone_get_device_vol(void)
{
    log_info("bt music get volume");
    return __this->call_volume * 127 / 100;
}

static void phone_sync_vol(u8 volume)
{
    volume = (u16)volume * 15 / 100;
    bt_cmd_prepare(USER_CTRL_HFP_CALL_SET_VOLUME, 1, &volume);
}

//蓝牙电话本获取回调函数
void phonebook_packet_handler(u8 type, const u8 *name, const u8 *number, const u8 *date)
{
    static u16 number_cnt = 0;
    log_debug("NO.%d:", number_cnt);
    number_cnt++;
    log_debug("type:%d ", type);
    if (type == 0xff) {
        number_cnt = 0;
    }
    if (name) {
        log_debug(" NAME:%s  ", name);
    }
    if (number) {
        log_debug("number:%s  ", number);
    }
    if (date) {
        log_debug("date:%s ", date);
    }
}

static void music_player_time_deal(void *priv)
{
    if (BT_STATUS_PLAYING_MUSIC == bt_get_connect_status()) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_GET_PLAY_TIME, 0, NULL);
    }
}

//定时获取歌曲信息
static void bt_music_player_time_timer_deal(u8 en)
{
    if (en) {
        if (__this->get_music_player_timer == 0) {
            __this->get_music_player_timer = sys_timer_add(NULL, music_player_time_deal, 800);
        }
    } else {
        if (__this->get_music_player_timer) {
            sys_timer_del(__this->get_music_player_timer);
            __this->get_music_player_timer = 0;
        }
    }
}

//获取歌曲信息
static void user_get_bt_music_info(u8 type, u32 time, u8 *info, u16 len)
{
    static u8 deal_type = 0;
    char buf[65] = {0};

    if (type != 0 && info == NULL) {
        return;
    }

    switch (type) {
    case 0:
        if (time) {
            u32 player_time_min = time / 1000 / 60;
            u32 player_time_sec = time / 1000 - (player_time_min * 60);
            log_debug("muisc time %d:%d->", player_time_min, player_time_sec);
        }
        break;
    case 1:
        if (len > 0) {
            memcpy(buf, info, len >= sizeof(buf) ? sizeof(buf) - 1 : len);
            log_debug("bt music title : %s", buf);
        }
        deal_type |= BIT(type);
        break;
    case 2:
        if (len > 0) {
            memcpy(buf, info, len >= sizeof(buf) ? sizeof(buf) - 1 : len);
            log_debug("bt music artist : %s", buf);
        }
        deal_type |= BIT(type);
        break;
    case 3:
        if (len > 0) {
            memcpy(buf, info, len >= sizeof(buf) ? sizeof(buf) - 1 : len);
            log_debug("bt music album : %s", buf);
        }
        deal_type |= BIT(type);
        break;
    case 4:
        memcpy(buf, info, 1);
        log_debug("bt music num : %d", atoi(buf));
        deal_type |= BIT(type);
        break;
    case 5:
        memcpy(buf, info, 1);
        log_debug("bt music total num : %d", atoi(buf));
        deal_type |= BIT(type);
        break;
    case 6:
        if (len > 0) {
            memcpy(buf, info, len >= sizeof(buf) ? sizeof(buf) - 1 : len);
            log_debug("bt music genre : %s", buf);
        }
        deal_type |= BIT(type);
        break;
    case 7:
        if (len > 8) {
            len = 8;
        }
        memcpy(buf, info, len);
        log_debug("bt music total time : %s ms", buf);
        deal_type |= BIT(type);
        deal_type = 0;
        break;
    default:
        break;
    }
}

//获取对端名称
static void bt_read_remote_name(u8 status, u8 *addr, u8 *name)
{
    if (status) {
        log_error("remote_name fail");
    } else {
        log_info("remote_name : %s", name);
    }

    put_buf(addr, 6);

#if TCFG_USER_EMITTER_ENABLE
    emitter_search_noname(status, addr, (char *)name);
#endif
}

static int bt_get_battery_value(void)
{
    //取消默认蓝牙定时发送电量给手机，需要更新电量给手机使用USER_CTRL_HFP_CMD_UPDATE_BATTARY命令
    /*电量协议的是0-9个等级，请比例换算*/
    return 9;
}

static void bt_dut_api(u8 value)
{
    log_info("bt in dut");
    bredr_close_all_scan();
}

static void bredr_handle_register(void)
{
#if TCFG_BT_SUPPORT_PROFILE_SPP
    extern void user_spp_data_handler(u8 packet_type, u16 ch, u8 * packet, u16 size);
    bt_spp_data_deal_handle_register(user_spp_data_handler_in_lib);
#endif

#if TCFG_BT_SUPPORT_MUSIC_VOL_SYNC
    ///蓝牙音乐和通话音量同步
    bt_music_vol_change_handle_register(bt_set_music_device_volume, phone_get_device_vol);
#endif
#if TCFG_BT_SUPPORT_DISPLAY_BAT
    ///电量显示获取电量的接口
    bt_get_battery_value_handle_register(bt_get_battery_value);   /*电量显示获取电量的接口*/
#endif
    ///被测试盒链接上进入快速测试回调
    /* bt_fast_test_handle_register(bt_fast_test_api); */

    ///样机进入dut被测试仪器链接上回调
    bt_dut_test_handle_register(bt_dut_api);

    ///获取远端设备蓝牙名字回调
    bt_read_remote_name_handle_register(bt_read_remote_name);

    ////获取歌曲信息回调
    bt_music_info_handle_register(user_get_bt_music_info);

#if TCFG_USER_EMITTER_ENABLE
    ////发射器设置回调等
    bt_inquiry_result_handle_register(emitter_search_result);
#endif
}

static void bt_function_select_init(void)
{
    __this->media_volume = INIT_VOLUME_VALUE;
    __this->call_volume = INIT_VOLUME_VALUE;

    bt_set_support_msbc_flag(1);
#if TCFG_BT_SUPPORT_AAC
    bt_set_support_aac_flag(1);
#endif
#if TCFG_BT_SUPPORT_DISPLAY_BAT
    bt_set_update_battery_time(60);
#else
    bt_set_update_battery_time(0);
#endif
    bt_set_page_timeout_value(8000); /*回连搜索时间长度设置,可使用该函数注册使用，ms单位,u16*/
    bt_set_super_timeout_value(8000); /*回连时超时参数设置。ms单位。做主机有效*/

    bt_set_simple_pair_flag(1); //是否打开简易配对功能，打开后不需要输入pincode
    ////设置蓝牙加密的level
    //io_capabilities ; /*0: Display only 1: Display YesNo 2: KeyboardOnly 3: NoInputNoOutput*/
    //authentication_requirements: 0:not protect  1 :protect
    bt_set_simple_pair_param(3, 0, 2);

#if (TCFG_BT_SUPPORT_PROFILE_PBAP==1)
    ////设置蓝牙设备类型
    bt_change_hci_class_type(BD_CLASS_CAR_AUDIO);
#endif

#if TCFG_BT_DUAL_CONN_ENABLE
    bt_set_user_ctrl_conn_num(2);
    ////设置开机回链的设备个数
    bt_set_auto_conn_device_num(2);
#else
    bt_set_user_ctrl_conn_num(1);
#endif

#if (TCFG_BT_SNIFF_ENABLE == 0)
    lmp_set_sniff_disable();
#endif
}

#define  SNIFF_CNT_TIME               5/////<空闲5S之后进入sniff模式

#define SNIFF_MAX_INTERVALSLOT        800
#define SNIFF_MIN_INTERVALSLOT        100
#define SNIFF_ATTEMPT_SLOT            4
#define SNIFF_TIMEOUT_SLOT            1

static u16 exit_sniff_timer = 0;

static void bt_check_exit_sniff(void)
{
    sys_timeout_del(exit_sniff_timer);
    exit_sniff_timer = 0;
    bt_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
}

static void bt_check_enter_sniff(void *priv)
{
    struct sniff_ctrl_config_t sniff_ctrl_config;
    u8 addr[12];
    u8 conn_cnt = 0;
    u8 i = 0;
    /*putchar('H');*/
    conn_cnt = bt_api_enter_sniff_status_check(SNIFF_CNT_TIME, addr);

    ASSERT(conn_cnt <= 2);

    for (i = 0; i < conn_cnt; i++) {
        log_info("-----USER SEND SNIFF IN %d %d", i, conn_cnt);
        sniff_ctrl_config.sniff_max_interval = SNIFF_MAX_INTERVALSLOT;
        sniff_ctrl_config.sniff_mix_interval = SNIFF_MIN_INTERVALSLOT;
        sniff_ctrl_config.sniff_attemp = SNIFF_ATTEMPT_SLOT;
        sniff_ctrl_config.sniff_timeout  = SNIFF_TIMEOUT_SLOT;
        memcpy(sniff_ctrl_config.sniff_addr, addr + i * 6, 6);
        bt_cmd_prepare(USER_CTRL_SNIFF_IN, sizeof(struct sniff_ctrl_config_t), (u8 *)&sniff_ctrl_config);
    }
}

static void sys_auto_sniff_controle(u8 enable, u8 *addr)
{
#if (TCFG_BT_SNIFF_ENABLE == 0)
    return;
#endif

    if (addr) {
        if (bt_api_conn_mode_check(enable, addr) == 0) {
            log_info("sniff ctr not change");
            return;
        }
    }

    if (enable) {
        if (bt_get_total_connect_dev() == 0) {
            return;
        }

        if (addr) {
            log_info("sniff cmd timer init");
            bt_cmd_prepare(USER_CTRL_HALF_SEC_LOOP_CREATE, 0, NULL);
        }

        if (__this->sniff_timer == 0) {
            log_info("check_sniff_enable");
            __this->sniff_timer = sys_timer_add(NULL, bt_check_enter_sniff, 1000);
        }
    } else {
        if (bt_get_total_connect_dev() > 0) {
            return;
        }

        if (addr) {
            log_info("sniff cmd timer remove");
            bt_cmd_prepare(USER_CTRL_HALF_SEC_LOOP_DEL, 0, NULL);
        }

        if (__this->sniff_timer) {
            log_info("check_sniff_disable");
            sys_timeout_del(__this->sniff_timer);
            __this->sniff_timer = 0;

            if (exit_sniff_timer == 0) {
                /* exit_sniff_timer = sys_timer_add(NULL, bt_check_exit_sniff, 5000); */
            }
        }
    }
}

static void phone_num_play_timer(void *priv)
{
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        log_info("hangup,--phone num play return");
        return;
    }

    if (__this->phone_num_flag) {
        //TODO 播放手机号码
    } else {
        /*电话号码还没有获取到，定时查询*/
        __this->phone_timer_id = sys_timeout_add(NULL, phone_num_play_timer, 200);
    }
}

//屏蔽彩铃，播放手机号码
static void phone_num_play_start(void)
{
    /* check if support inband ringtone */
    if (!__this->inband_ringtone) {
        __this->phone_num_flag = 0;
        __this->phone_timer_id = sys_timeout_add(NULL, phone_num_play_timer, 500);
    }
}

static void phone_ring_play_timer(void *priv)
{
    //通话铃声逻辑暂未处理
    __this->phone_timer_id = sys_timeout_add(NULL, phone_ring_play_timer, 1000);
}

//播放彩铃
static void phone_ring_play_start(void)
{
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        log_info("hangup,--phone ring play return");
        return;
    }
    /* check if support inband ringtone */
    if (!__this->inband_ringtone) {
        __this->phone_timer_id = sys_timeout_add(NULL, phone_ring_play_timer, 1000);
    }
}

void bt_ble_module_init(void)
{
    bt_function_select_init();
    bredr_handle_register();
    btstack_init();
}

//打开蓝牙
void bt_connection_enable(void)
{
    if (__this->enable) {
        return;
    }
    if (__this->poweroff_timer_id) {
        sys_timeout_del(__this->poweroff_timer_id);
        __this->poweroff_timer_id = 0;
    }
#ifdef CONFIG_LOW_POWER_ENABLE
    low_power_hw_unsleep_lock();
    btctrler_task_init_bredr();
    low_power_hw_unsleep_unlock();
#endif
    __this->enable = 1;
    __this->auto_connection_counter = 0;
    get_remote_device_info_from_vm();
    bt_init_ok_search_index();

#if ((TCFG_BT_MODE == BT_BQB)||(TCFG_BT_MODE == BT_PER))
    bt_wait_phone_connect_control(1);
#else
#if TCFG_BT_ENABLE_AUTO_RECONNECT
    bt_wait_connect_and_phone_connect_switch(0);
#else
    bt_wait_phone_connect_control(1);
#endif
#endif
}

static void bt_power_off(void *p)
{
    if (is_1t2_connection() || bt_get_total_connect_dev() > 0) {
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
        bt_cmd_prepare(USER_CTRL_CONNECTION_CANCEL, 0, NULL);
        bt_cmd_prepare(USER_CTRL_DISCONNECTION_HCI, 0, NULL);
        __this->poweroff_timer_id = sys_timeout_add(NULL, bt_power_off, 100);
        return;
    }
    __this->poweroff_timer_id = 0;
    bt_cmd_prepare(USER_CTRL_POWER_OFF, 0, NULL);
#ifdef CONFIG_LOW_POWER_ENABLE
    os_time_dly(50);
    low_power_hw_unsleep_lock();
    btctrler_task_close_bredr();
    low_power_hw_unsleep_unlock();
#if TCFG_BT_SNIFF_ENABLE
    lmp_set_sniff_establish_by_remote(0);
#endif
#endif
}

//关闭蓝牙
void bt_connection_disable(void)
{
#if TCFG_USER_EMITTER_ENABLE
    __this->emitter = 0;
    emitter_or_receiver_switch(0);
#else
    if (!__this->enable) {
        return;
    }
#endif

    __this->enable = 0;
    if (__this->auto_connection_timer) {
        sys_timer_del(__this->auto_connection_timer);
        __this->auto_connection_timer = 0;
    }
    bt_wait_phone_connect_control(0);
    bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
    bt_cmd_prepare(USER_CTRL_CONNECTION_CANCEL, 0, NULL);
    bt_cmd_prepare(USER_CTRL_DISCONNECTION_HCI, 0, NULL);
    if (!__this->poweroff_timer_id) {
        __this->poweroff_timer_id = sys_timeout_add(NULL, bt_power_off, 500);
    }
    /* bt_cmd_prepare(USER_CTRL_INQUIRY_CANCEL, 0, NULL); */
}

#if TCFG_USER_EMITTER_ENABLE
//打开蓝牙发射器
static void bt_emitter_enable(void *priv)
{
    __this->enable = 1;
    __this->emitter = 1;
    key_event_enable();
#ifdef CONFIG_LOW_POWER_ENABLE
#if TCFG_BT_SNIFF_ENABLE
    lmp_set_sniff_establish_by_remote(1);
#endif
    low_power_hw_unsleep_lock();
    btctrler_task_init_bredr();
    low_power_hw_unsleep_unlock();
#endif
    emitter_or_receiver_switch(BT_EMITTER_EN);
}

//关闭蓝牙发射器
static void bt_emitter_disable(void)
{
    __this->enable = 0;
    __this->emitter = 0;
    if (__this->auto_connection_timer) {
        sys_timer_del(__this->auto_connection_timer);
        __this->auto_connection_timer = 0;
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
        bt_cmd_prepare(USER_CTRL_CONNECTION_CANCEL, 0, NULL);
    }
    bt_wait_phone_connect_control(0);
    emitter_or_receiver_switch(BT_RECEIVER_EN);
    bt_connection_enable();
}
#endif

void bredr_a2dp_open_and_close(void)
{
    if (bt_get_curr_channel_state() & A2DP_CH) {
        log_info("start to disconnect a2dp ");
        bt_cmd_prepare(USER_CTRL_DISCONN_A2DP, 0, NULL);
    } else {
        log_info("start to connect a2dp ");
        bt_cmd_prepare(USER_CTRL_CONN_A2DP, 0, NULL);
    }
}

void bredr_hfp_open_and_close(void)
{
    if (bt_get_curr_channel_state() & HFP_CH) {
        bt_cmd_prepare(USER_CTRL_HFP_DISCONNECT, 0, NULL);
    } else {
        bt_cmd_prepare(USER_CTRL_HFP_CMD_BEGIN, 0, NULL);
    }
}

static void bt_phone_income(u8 *addr)
{
    esco_dump_packet = ESCO_DUMP_PACKET_CALL;
    /*
     *(1)1t2有一台通话的时候，另一台如果来电不要提示
     *(2)1t2两台同时来电，先来的提示，后来的不播
     */
    if ((bt_check_esco_state_via_addr(addr) != BD_ESCO_BUSY_OTHER) && (__this->phone_ring_flag == 0)) {
#if BT_INBAND_RINGTONE
        extern u8 get_device_inband_ringtone_flag(void);
        __this->inband_ringtone = get_device_inband_ringtone_flag();
#else
        lmp_private_esco_suspend_resume(3);
#endif
        __this->phone_ring_flag = 1;
        __this->phone_income_flag = 1;
#if BT_PHONE_NUMBER
        phone_num_play_start();
#else
        phone_ring_play_start();
#endif
        bt_cmd_prepare(USER_CTRL_HFP_CALL_CURRENT, 0, NULL); //发命令获取电话号码
    } else {
        log_info("SCO busy now:%d,%d", bt_check_esco_state_via_addr(addr), __this->phone_ring_flag);
    }
}

static void bt_phone_out(void)
{
    lmp_private_esco_suspend_resume(4);
    esco_dump_packet = ESCO_DUMP_PACKET_CALL;
    __this->phone_income_flag = 0;
    bt_cmd_prepare(USER_CTRL_HFP_CALL_CURRENT, 0, NULL); //发命令获取电话号码
}

static void bt_phone_active(void)
{
    if (__this->phone_call_dec_begin) {
        log_info("call_active,dump_packet clear");
        esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;
    }
    if (__this->phone_ring_flag) {
        __this->phone_ring_flag = 0;
        if (__this->phone_timer_id) {
            sys_timeout_del(__this->phone_timer_id);
            __this->phone_timer_id = 0;
        }
    }
    lmp_private_esco_suspend_resume(4);
    __this->phone_income_flag = 0;
    __this->phone_num_flag = 0;
    __this->phone_con_sync_num_ring = 0;
    __this->phone_con_sync_ring = 0;
    log_info("phone_active:%d", __this->call_volume);
}

static void bt_phone_hangup(void)
{
    esco_dump_packet = ESCO_DUMP_PACKET_CALL;
    log_info("phone_handup");
    if (__this->phone_ring_flag) {
        __this->phone_ring_flag = 0;
        if (__this->phone_timer_id) {
            sys_timeout_del(__this->phone_timer_id);
            __this->phone_timer_id = 0;
        }
    }
    lmp_private_esco_suspend_resume(4);
    __this->phone_num_flag = 0;
    __this->phone_con_sync_num_ring = 0;
    __this->phone_con_sync_ring = 0;
}

static void bt_phone_number(u8 *phone_number)
{
    if (__this->phone_num_flag == 1) {
        return;
    }
    __this->income_phone_len = 0;
    memset(__this->income_phone_num, '\0', sizeof(__this->income_phone_num));
    for (int i = 0; i < strlen((const char *)phone_number); i++) {
        if (phone_number[i] >= '0' && phone_number[i] <= '9') {
            //过滤，只有数字才能报号
            __this->income_phone_num[__this->income_phone_len++] = phone_number[i];
            if (__this->income_phone_len >= sizeof(__this->income_phone_num)) {
                break;    /*buffer 空间不够，后面不要了*/
            }
        }
    }
    if (__this->income_phone_len > 0) {
        __this->phone_num_flag = 1;
    } else {
        log_info("PHONE_NUMBER len err");
    }
}

static void bt_a2dp_media_start(int media_format, u8 *bt_addr)
{
    if (!__this->dec_server) {
        __this->dec_server = earphone_a2dp_audio_codec_open(media_format, __this->media_volume, bt_addr);
        if (__this->dec_server) {
            __this->media_play_flag = 1;
        }
    }
    bt_music_player_time_timer_deal(1);
}

static void bt_a2dp_media_stop(u8 *bt_addr)
{
    bt_music_player_time_timer_deal(0);
    __this->dec_server = NULL;
    earphone_a2dp_audio_codec_close(bt_addr);
    __this->media_play_flag = 0;
}

static void bt_phone_sco_start(int call_format)
{
    if (!__this->dec_server) {
        __this->dec_server = phone_call_begin(call_format, __this->call_volume);
    }
    __this->call_flag = 1;
    __this->phone_call_dec_begin = 1;

    if (bt_get_call_status() == BT_CALL_ACTIVE) {
        log_info("dec_begin,dump_packet clear");
        esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;
    }
}

static void bt_phone_sco_stop(void)
{
    __this->phone_call_dec_begin = 0;
    esco_dump_packet = ESCO_DUMP_PACKET_CALL;
    if (__this->dec_server) {
        phone_call_end();
        __this->dec_server = NULL;
    }
    __this->call_flag = 0;
}

static void bt_phone_call_volume_change(int volume)
{
    volume = 100 * volume / 15;
    u8 call_status = bt_get_call_status();
    __this->call_volume = volume;
    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING) || __this->siri_stu) {
        if (__this->dec_server) {
            union audio_req req = {0};
            req.dec.cmd     = AUDIO_DEC_SET_VOLUME;
            req.dec.volume  = volume;
            server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
        }
    } else if (call_status != BT_CALL_HANGUP) {
        /*只保存，不设置到dac*/
        __this->call_volume = volume;
    }
}

static void bt_a2dp_media_start_timer(void *p)
{
    if (!__this->media_play_flag) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
    }
}

/*
 * 对应原来的状态处理函数，连接，电话状态等
 */
static int bt_connction_status_event_handler(struct bt_event *bt)
{
    log_info("-----------------------bt_connction_status_event_handler %d", bt->event);

    switch (bt->event) {
    case BT_STATUS_INIT_OK:
        /*
         * 蓝牙初始化完成
         */
        log_info("===================BT_STATUS_INIT_OK");
#if TCFG_SPP_TRANS_DATA_EN
        extern void transport_spp_init(void);
        transport_spp_init();
#endif
        bt_connection_enable();
        break;
    case BT_STATUS_START_CONNECTED:
        log_info("BT_STATUS_START_CONNECTED");
        break;
    case BT_STATUS_ENCRY_COMPLETE:
        log_info("BT_STATUS_ENCRY_COMPLETE");
        break;
    case BT_STATUS_SECOND_CONNECTED:
        bt_clear_current_poweron_memory_search_index(0);
    case BT_STATUS_FIRST_CONNECTED:
        //蓝牙连接成功
        log_info("BT_STATUS_CONNECTED");
        sys_auto_sniff_controle(1, NULL);
        /* bt_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL); */
#if TCFG_BT_DUAL_CONN_ENABLE
        if (bt_get_current_poweron_memory_search_index(NULL) == 0 && __this->emitter == 0) {
            bt_wait_phone_connect_control(1);
        }
#endif
#if TCFG_BT_SUPPORT_RECEIVER_AUTO_A2DP_START
        if (__this->emitter == 0 && bt_get_total_connect_dev() == 1 && !__this->dec_server) {
            sys_timeout_add(NULL, bt_a2dp_media_start_timer, 1000);
        }
#endif
        break;
    case BT_STATUS_FIRST_DISCONNECT:
    case BT_STATUS_SECOND_DISCONNECT:
        //蓝牙连接断开
        log_info("BT_STATUS_DISCONNECT");
        sys_auto_sniff_controle(0, NULL);
#if TCFG_USER_EMITTER_ENABLE
        bt_emitter_stu_set(0);
#endif
        break;
    //phone status deal
    case BT_STATUS_PHONE_INCOME:
        //接到来电
        log_info("BT_STATUS_PHONE_INCOME");
        bt_phone_income(bt->args);
        break;
    case BT_STATUS_PHONE_OUT:
        //通话打出
        log_info("BT_STATUS_PHONE_OUT");
        bt_phone_out();
        break;
    case BT_STATUS_PHONE_ACTIVE:
        //通话接通
        log_info("BT_STATUS_PHONE_ACTIVE");
        bt_phone_active();
        break;
    case BT_STATUS_PHONE_HANGUP:
        //通话挂断
        log_info("BT_STATUS_PHONE_HANGUP");
        bt_phone_hangup();
        break;
    case BT_STATUS_PHONE_NUMBER:
        log_info("BT_STATUS_PHONE_NUMBER");
        bt_phone_number((u8 *)bt->value);
        break;
    case BT_STATUS_INBAND_RINGTONE:
        log_info("BT_STATUS_INBAND_RINGTONE");
#if BT_INBAND_RINGTONE
        __this->inband_ringtone = bt->value;
#endif
        break;
    case BT_STATUS_BEGIN_AUTO_CON:
        log_info("BT_STATUS_BEGIN_AUTO_CON");
        break;
    case BT_STATUS_A2DP_MEDIA_START:
        log_info("BT_STATUS_A2DP_MEDIA_START");
        bt_a2dp_media_start(bt->value, bt->args);
        break;
    case BT_STATUS_A2DP_MEDIA_STOP:
        log_info("BT_STATUS_A2DP_MEDIA_STOP");
        bt_a2dp_media_stop(bt->args);
        break;
    case BT_STATUS_SCO_STATUS_CHANGE:
        log_info("BT_STATUS_SCO_STATUS_CHANGE len:%d ,type:%d", (bt->value >> 16), (bt->value & 0x0000ffff));
        if (bt->value != 0xff) {
            bt_phone_sco_start(bt->value);
        } else {
            bt_phone_sco_stop();
        }
        break;
    case BT_STATUS_CALL_VOL_CHANGE:
        log_info("BT_STATUS_CALL_VOL_CHANGE %d", bt->value);
        bt_phone_call_volume_change(bt->value);
        break;
    case BT_STATUS_SNIFF_STATE_UPDATE:
        log_info("BT_STATUS_SNIFF_STATE_UPDATE %d", bt->value);    //0退出SNIFF
        if (bt->value == 0) {
            sys_auto_sniff_controle(1, bt->args);
        } else {
            sys_auto_sniff_controle(0, bt->args);
        }
        break;
    case BT_STATUS_LAST_CALL_TYPE_CHANGE:
        log_info("BT_STATUS_LAST_CALL_TYPE_CHANGE:%d", bt->value);
        break;
    case BT_STATUS_CONN_A2DP_CH:
#if TCFG_USER_EMITTER_ENABLE
#if defined TCFG_SBC_ENCODER_CHANNEL_NUM && defined TCFG_SBC_ENCODER_SAMPLERATE
        sbc_param_change(TCFG_SBC_ENCODER_CHANNEL_NUM, TCFG_SBC_ENCODER_SAMPLERATE);
#endif
        bt_emitter_stu_sw();
#endif
        break;
    case BT_STATUS_CONN_HFP_CH:
        if ((!is_1t2_connection()) && (bt_get_current_poweron_memory_search_index(NULL))) { //回连下一个device
            bt_cmd_prepare(USER_CTRL_START_CONNECTION, 0, NULL);
        }
        break;
    case BT_STATUS_PHONE_MANUFACTURER:
        log_info("BT_STATUS_PHONE_MANUFACTURER:%d", bt->value);
        extern const u8 hid_conn_depend_on_dev_company;
        if (hid_conn_depend_on_dev_company) {
            if (bt->value) {
                //bt_cmd_prepare(USER_CTRL_HID_CONN, 0, NULL);
            } else {
                bt_cmd_prepare(USER_CTRL_HID_DISCONNECT, 0, NULL);
            }
        }
        break;
    case BT_STATUS_VOICE_RECOGNITION:
        log_info("BT_STATUS_VOICE_RECOGNITION:%d", bt->value);
        esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;
        /* put_buf(bt, sizeof(struct bt_event)); */
        __this->siri_stu = bt->value;
        break;
    case BT_STATUS_AVRCP_INCOME_OPID:
        log_info("BT_STATUS_AVRCP_INCOME_OPID:%d", bt->value);
        break;
    case BT_STATUS_RECONN_OR_CONN:
        log_info("BT_STATUS_RECONN_OR_CONN");
        break;
    default:
        log_info("BT STATUS DEFAULT");
        break;
    }

    return 0;
}

static void bt_send_pair(u8 en)
{
    bt_cmd_prepare(USER_CTRL_PAIR, 1, &en);
}

static void hci_event_disconnection_complete(int value)
{
#if TCFG_BT_DUAL_CONN_ENABLE
    if ((value == ERROR_CODE_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR) ||
        (value == ERROR_CODE_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED)) {
        /*
         *连接接受超时
         *如果支持1t2，可以选择继续回连下一台，除非已经回连完毕
         */
        if (bt_get_current_poweron_memory_search_index(NULL)) {
            bt_cmd_prepare(USER_CTRL_START_CONNECTION, 0, NULL);
            return;
        }
    }
#endif
#if TCFG_USER_EMITTER_ENABLE
    if (bt_emitter_disconnect() != 0)
#endif
    {
        bt_wait_phone_connect_control(1);
    }
}

static void hci_event_connection_complete(void)
{
    if (__this->auto_connection_timer) {
        sys_timeout_del(__this->auto_connection_timer);
        __this->auto_connection_timer = 0;
    }
    __this->auto_connection_counter = 0;
    bt_wait_phone_connect_control(0);
    bt_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
}

static void hci_event_page_timeout(void)
{
    if (__this->auto_connection_timer) {
        sys_timer_del(__this->auto_connection_timer);
        __this->auto_connection_timer = 0;
    }
#if TCFG_USER_EMITTER_ENABLE
    if (bt_emitter_page_timeout() != 0)
#endif
    {
        bt_wait_phone_connect_control(1);
    }
}

static void hci_event_connection_timeout(u8 *bt_addr)
{
    if (!bt_get_remote_test_flag()) {
        __this->auto_connection_counter = (BT_TIMEOUT_CONN_TIME * 1000);
        memcpy(__this->auto_connection_addr, bt_addr, 6);
        if (__this->auto_connection_timer) {
            sys_timer_del(__this->auto_connection_timer);
            __this->auto_connection_timer = 0;
        }
#if ((TCFG_BT_MODE == BT_BQB)||(TCFG_BT_MODE == BT_PER))
        bt_wait_phone_connect_control(1);
#else
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
        bt_wait_connect_and_phone_connect_switch(0);
#endif
        //bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, bt->args);
    } else {
        bt_wait_phone_connect_control(1);
    }
}

static int bt_hci_event_handler(struct bt_event *bt)
{
    //对应原来的蓝牙连接上断开处理函数  ,bt->value=reason
    log_info("------------------------bt_hci_event_handler reason %x", bt->event);

    switch (bt->event) {
    case HCI_EVENT_INQUIRY_COMPLETE:
        log_info("HCI_EVENT_INQUIRY_COMPLETE");
#if TCFG_USER_EMITTER_ENABLE
        emitter_search_stop(bt->value);
#endif
        break;
    case HCI_EVENT_IO_CAPABILITY_REQUEST:
        log_info("HCI_EVENT_IO_CAPABILITY_REQUEST");
        break;
    case HCI_EVENT_USER_CONFIRMATION_REQUEST:
        log_info("HCI_EVENT_USER_CONFIRMATION_REQUEST");
        ///<可通过按键来确认是否配对 1：配对   0：取消
        bt_send_pair(1);
        break;
    case HCI_EVENT_USER_PASSKEY_REQUEST:
        log_info("HCI_EVENT_USER_PASSKEY_REQUEST");
        ///<可以开始输入6位passkey
        break;
    case HCI_EVENT_USER_PRESSKEY_NOTIFICATION:
        log_info("HCI_EVENT_USER_PRESSKEY_NOTIFICATION %x", bt->value);
        ///<可用于显示输入passkey位置 value 0:start  1:enrer  2:earse   3:clear  4:complete
        break;
    case HCI_EVENT_PIN_CODE_REQUEST:
        log_info("HCI_EVENT_PIN_CODE_REQUEST");
        bt_send_pair(1);
        break;
    case HCI_EVENT_VENDOR_NO_RECONN_ADDR:
        log_info("HCI_EVENT_VENDOR_NO_RECONN_ADDR");
    case HCI_EVENT_DISCONNECTION_COMPLETE:
        log_info("HCI_EVENT_DISCONNECTION_COMPLETE");
        hci_event_disconnection_complete(bt->value);
        break;
    case BTSTACK_EVENT_HCI_CONNECTIONS_DELETE:
    case HCI_EVENT_CONNECTION_COMPLETE:
        log_info("HCI_EVENT_CONNECTION_COMPLETE");
        switch (bt->value) {
        case ERROR_CODE_SUCCESS:
            log_info("ERROR_CODE_SUCCESS");
            hci_event_connection_complete();
            break;
        case ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION:
        case ERROR_CODE_PIN_OR_KEY_MISSING:
            log_info("ERROR_CODE_PIN_OR_KEY_MISSING");
        case ERROR_CODE_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED:
        case ERROR_CODE_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES:
        case ERROR_CODE_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR:
        case ERROR_CODE_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED:
        case ERROR_CODE_CONNECTION_TERMINATED_BY_LOCAL_HOST:
        case ERROR_CODE_AUTHENTICATION_FAILURE:
        case CUSTOM_BB_AUTO_CANCEL_PAGE:
            hci_event_disconnection_complete(bt->value);
            break;
        case ERROR_CODE_PAGE_TIMEOUT:
            log_info("ERROR_CODE_PAGE_TIMEOUT");
            hci_event_page_timeout();
            break;
        case ERROR_CODE_CONNECTION_TIMEOUT:
            log_info(" ERROR_CODE_CONNECTION_TIMEOUT");
            hci_event_connection_timeout(bt->args);
            break;
        case ERROR_CODE_ACL_CONNECTION_ALREADY_EXISTS:
            log_info("ERROR_CODE_ACL_CONNECTION_ALREADY_EXISTS");
            hci_event_connection_timeout(bt->args);
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return 0;
}

//蓝牙协议栈事件处理
int app_music_bt_event_handler(struct sys_event *event)
{
    if (event->from == BT_EVENT_FROM_CON) {
        return bt_connction_status_event_handler((struct bt_event *)event->payload);
    } else if (event->from == BT_EVENT_FROM_HCI) {
        return bt_hci_event_handler((struct bt_event *)event->payload);
    }
    return false;
}

//暂停/继续播放
static int bt_music_play_pause(void)
{
#if TCFG_USER_EMITTER_ENABLE
    if (__this->emitter) {
        return bt_emitter_stu_sw();
    }
#endif
    if (__this->phone_ring_flag) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
    } else if (__this->call_flag) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
    }

    return 0;
}

//切换歌曲
static int bt_music_switch_song(int fsel_mode)
{
    if (!__this->call_flag) {
        if (fsel_mode == FSEL_NEXT_FILE) {
            bt_cmd_prepare(USER_CTRL_AVCTP_OPID_NEXT, 0, NULL);
        } else if (fsel_mode == FSEL_PREV_FILE) {
            bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PREV, 0, NULL);
        }
    }

    return 0;
}

//调整设备音量
static int bt_music_set_volume_step(int step)
{
    union audio_req req = {0};

    if (__this->media_play_flag) {
        int volume = __this->media_volume + step;
        if (volume < MIN_VOLUME_VALUE) {
            volume = MIN_VOLUME_VALUE;
        } else if (volume > MAX_VOLUME_VALUE) {
            volume = MAX_VOLUME_VALUE;
        }
        if (volume == __this->media_volume) {
            return 0;
        }
        __this->media_volume = volume;
        __this->call_volume = volume;

        if (step > 0) {
            bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
        }
        if (__this->dec_server) {
            req.dec.cmd     = AUDIO_DEC_SET_VOLUME;
            req.dec.volume  = volume;
            return server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
        }
    } else if (__this->call_flag) {
        int volume = __this->call_volume + step;
        if (volume < MIN_VOLUME_VALUE) {
            volume = MIN_VOLUME_VALUE;
        } else if (volume > MAX_VOLUME_VALUE) {
            volume = MAX_VOLUME_VALUE;
        }
        if (volume == __this->call_volume) {
            return 0;
        }
        __this->media_volume = volume;
        __this->call_volume = volume * 127 / 100;

        if (step > 0) {
            bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_UP, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_DOWN, 0, NULL);
        }
        if (__this->dec_server) {
            req.dec.cmd     = AUDIO_DEC_SET_VOLUME;
            req.dec.volume  = volume;
            return server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
        }
    }

    return 0;
}

int bt_music_key_event_handler(struct key_event *key)
{
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
            bt_music_play_pause();
            break;
        case KEY_VOLUME_DEC:
            if (__this->emitter) {
#if TCFG_USER_EMITTER_ENABLE
                bt_emitter_enc_gain_set(-VOLUME_STEP);
#endif
            } else {
                bt_music_set_volume_step(-VOLUME_STEP);
            }
            break;
        case KEY_VOLUME_INC:
            if (__this->emitter) {
#if TCFG_USER_EMITTER_ENABLE
                bt_emitter_enc_gain_set(VOLUME_STEP);
#endif
            } else {
                bt_music_set_volume_step(VOLUME_STEP);
            }
            break;
        case KEY_MODE:
            if (__this->enable) {
                bt_connection_disable();
            } else {
                bt_connection_enable();
            }
            break;
        default:
            break;
        }
        break;
    case KEY_EVENT_LONG:
        switch (key->value) {
        case KEY_OK:
#if TCFG_USER_EMITTER_ENABLE
            if (__this->emitter) {
                if (bt_get_call_status() == BT_CALL_HANGUP) {
                    bt_emitter_esco_pp(1);
                } else {
                    bt_emitter_esco_pp(0);
                }
            }
#endif
            break;
        case KEY_VOLUME_DEC:
            if (!__this->emitter) {
                bt_music_switch_song(FSEL_PREV_FILE);
            }
            break;
        case KEY_VOLUME_INC:
            if (!__this->emitter) {
                bt_music_switch_song(FSEL_NEXT_FILE);
            }
            break;
        case KEY_MODE:
#if TCFG_USER_EMITTER_ENABLE
            //发射器或者接收器切换
            if (__this->enable) {
                if (__this->emitter) {
                    bt_emitter_disable();
                } else {
                    key_event_disable();
                    bt_connection_disable();
                    sys_timeout_add(NULL, bt_emitter_enable, 1000);
                }
            }
#endif
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return false;
}

#endif

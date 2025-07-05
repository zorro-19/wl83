#include "system/includes.h"
#include "action.h"
#include "app_config.h"
#include "storage_device.h"
#include "generic/log.h"
#include "os/os_api.h"
#include "event/key_event.h"
#include "event/bt_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "wifi/wifi_connect.h"


/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
#ifdef CONFIG_IPMASK_ENABLE
    //不可屏蔽中断方法：支持写flash，但中断函数和调用函数和const要全部放在内部ram
    { IRQ_SOFT5_IDX,      6,   0    }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,      6,   1    }, //此中断强制注册到cpu1
#if 0 //如下，SPI1使用不可屏蔽中断设置
    { IRQ_SPI1_IDX,      7,   1    },//中断强制注册到cpu0/1
#endif
#endif
#if CPU_CORE_NUM == 1
    { IRQ_SOFT5_IDX,      7,   0    }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,      7,   1    }, //此中断强制注册到cpu1
    { -2,     			-2,   -2   },//如果加入了该行, 那么只有该行之前的中断注册到对应核, 其他所有中断强制注册到CPU0
#endif

    { -1,     -1,   -1    },
};


/*创建使用 os_task_create_static 或者task_create 接口的 静态任务堆栈*/
#define SYS_TIMER_STK_SIZE 512
#define SYS_TIMER_Q_SIZE 256
static u8 sys_timer_tcb_stk_q[sizeof(StaticTask_t) + SYS_TIMER_STK_SIZE * 4 + sizeof(struct task_queue) + SYS_TIMER_Q_SIZE] ALIGNE(4);

#define SYSTIMER_STK_SIZE 256
static u8 systimer_tcb_stk_q[sizeof(StaticTask_t) + SYSTIMER_STK_SIZE * 4] ALIGNE(4);

#define SYS_EVENT_STK_SIZE 512
static u8 sys_event_tcb_stk_q[sizeof(StaticTask_t) + SYS_EVENT_STK_SIZE * 4] ALIGNE(4);

#define APP_CORE_STK_SIZE 2048
#define APP_CORE_Q_SIZE 1024
static u8 app_core_tcb_stk_q[sizeof(StaticTask_t) + APP_CORE_STK_SIZE * 4 + sizeof(struct task_queue) + APP_CORE_Q_SIZE] ALIGNE(4);

/*创建使用  thread_fork 接口的 静态任务堆栈*/
#define WIFI_TASKLET_STK_SIZE 1400
static u8 wifi_tasklet_tcb_stk_q[sizeof(struct thread_parm) + WIFI_TASKLET_STK_SIZE * 4] ALIGNE(4);

#define WIFI_CMDQ_STK_SIZE 300
static u8 wifi_cmdq_tcb_stk_q[sizeof(struct thread_parm) + WIFI_CMDQ_STK_SIZE * 4] ALIGNE(4);

#define WIFI_MLME_STK_SIZE 900
static u8 wifi_mlme_tcb_stk_q[sizeof(struct thread_parm) + WIFI_MLME_STK_SIZE * 4] ALIGNE(4);

#define WIFI_RX_STK_SIZE 256
static u8 wifi_rx_tcb_stk_q[sizeof(struct thread_parm) + WIFI_RX_STK_SIZE * 4] ALIGNE(4);


/*任务列表 */
const struct task_info task_info_table[] = {
    { "app_core",            15,     APP_CORE_STK_SIZE,      APP_CORE_Q_SIZE,    app_core_tcb_stk_q  },
    { "sys_event",           29,     SYS_EVENT_STK_SIZE,                   0,    sys_event_tcb_stk_q },
    { "systimer",            14,     SYSTIMER_STK_SIZE,                    0,    systimer_tcb_stk_q  },
    { "sys_timer",            9,     SYS_TIMER_STK_SIZE,    SYS_TIMER_Q_SIZE,    sys_timer_tcb_stk_q },
    { "thread_fork_kill",    25,     256,      0 },
#ifdef CONFIG_AUDIO_ENABLE
    { "audio_server",        16,     512,     64 },
    { "audio_mix",           28,     512,      0 },
    { "audio_encoder",       12,     384,     64 },
    { "speex_encoder",       13,     512,      0 },
    { "mp3_encoder",         13,     768,      0 },
    { "opus_encoder",        13,    1536,      0 },
    { "vir_dev_task",        14,     256,      0 },
    { "amr_encoder",         13,    1024,      0 },
    { "cvsd_encoder",        13,     512,      0 },
    { "vad_encoder",         14,     768,      0 },
    { "aec_encoder",         13,    1024,      0 },
    { "dns_encoder",         13,     512,      0 },
    { "msbc_encoder",        13,     256,      0 },
    { "sbc_encoder",         13,     512,      0 },
    { "adpcm_encoder",       13,     512,      0 },
    { "echo_deal",           11,    1024,     32 },
#endif
#ifdef CONFIG_MEDIA_ENABLE
    { "jlstream_",           25,     768,      0 },
    { "jlstream",            23,     768,    128 },
    { "a2dp_dec",            24,     768,      0 },
    /* file dec任务不打断jlstream任务运行,故优先级低于jlstream */
    { "file_dec",            24,     768,      0 },
    { "file_cache",          26,     512,      0 },
    { "write_file",          25,     512,      0 },
    /* 麦克风音效任务优先级要高 */
    { "mic_effect",          26,     768,      0 },
    /* 为了防止dac buf太大，通话一开始一直解码，导致编码输入数据需要很大的缓存，这里提高编码的优先级 */
    { "audio_enc",           26,     768,    128 },
    { "aec",                 12,     768,    128 },
    { "aec_dbg",             13,     512,    128 },
    { "aud_capture",         24,     512,    256 },
    { "dac",                 22,     256,    128 },
    { "spec_adv",            23,     512,    128 },
    { "kws",                  3,     256,     64 },
    { "audio_vad",           11,     512,    128 },
    { "key_tone",            25,     256,     32 },
    { "cvp_ref",             24,     256,    128 },
#endif
    { "uac_sync",            20,     512,      0 },
    { "uac_play",            26,     512,     32 },
    { "uac_record",          26,     512,      0 },
    { "usb_msd",              1,     512,    128 },
    { "uda_main",             2,    7000,      0 },
    { "update",              21,     512,     32 },
    { "dw_update",           21,     512,     32 },

#ifdef CONFIG_NET_ENABLE
    { "update_rtc_task",      1,     512,      0 },
    { "ntp_client_get_time", 10,    1024,      0 },
    { "get_profile_task",    22,    3328,      0 },
    { "get_macaddr_task",    22,    1536,      0 },
    { "tcpip_thread",        16,     800,      0 },
    { "iperf_test",          15,    1024,      0 },
    { "net_download_task",   11,    1536,      0 },
    { "websocket_client_recv", 18,  1024,      0 },
    { "websocket_client_heart", 19,  1024,      0 },
#ifdef CONFIG_DUI_SDK_ENABLE
    { "dui_net_task",        20,    1536,    256 },
    { "dui_app_task",        20,    1536,    256 },
    { "dui_iot_poll_online", 21,    1024,      0 },
    { "dui_iot_ctl_proc",    20,    1024,      0 },
    { "dui_iot_parse_proc",  22,     768,      0 },
#endif
#ifdef CONFIG_TURING_SDK_ENABLE
    { "turing_app_task",     22,    1536,    128 },
    { "turing_mqtt_task",    21,    1536,      0 },
    { "wechat_api_task",     21,    1536,     64 },
    { "turing_bind_device_task", 11, 768,     64 },
#endif
#ifdef CONFIG_ALI_SDK_ENABLE
    { "ali_app_task",        20,    2048,     64 },
#endif
#ifdef CONFIG_DLNA_SDK_ENABLE
    { "RunMiniServerTask",   20,    1536,     16 },
    { "HandleRequestTask",   21,    1536,    128 },
    { "GenaNotifyTask",      23,    1024,      0 },
    { "dlna_app_task",       22,    1024,     64 },
#endif
#if TCFG_WIFI_ENABLE
    { "voiceprint",          11,    2048,     32 },
    { "change_channel",      10,    2000,      0 },
    { "tasklet",             10,    WIFI_TASKLET_STK_SIZE,   0,		 wifi_tasklet_tcb_stk_q },//通过调节任务优先级平衡WIFI收发占据总CPU的比重
    { "RtmpMlmeTask",        17,    WIFI_MLME_STK_SIZE,  	 0, 	 wifi_mlme_tcb_stk_q    },
    { "RtmpCmdQTask",        17,    WIFI_CMDQ_STK_SIZE,   	 0,  	 wifi_cmdq_tcb_stk_q    },
    { "wl_rx_irq_thread",     7,    WIFI_RX_STK_SIZE,    	 0,  	 wifi_rx_tcb_stk_q      },
    { "wl_rx_query_thread",   2,    WIFI_RX_STK_SIZE,    	 0,  	 wifi_rx_tcb_stk_q      },
#endif
#if TCFG_ETH_ENABLE
    { "eth_rx_task_n",        7,     256,      0 },
#endif
#if TCFG_LTE_PHY_ENABLE
    { "lte_rx_task",          7,     256,      0 },
#endif
#endif
#ifdef CONFIG_BT_ENABLE
    { "btencry",             14,     512,    128 },
    { "btctrler",            19,     512,    384 },
    { "btstack",             18,     768,    384 },
#endif
#ifdef CONFIG_VIDEO_ENABLE
    { "net_video_server",    16,     256,     64 },
    { "video_server_transfer", 23,  1024,      0 },
    { "video_server",        16,     768,    128 },
    { "vpkg_server",         16,     512,    128 },
    { "video0_rec",          20,     256,    128 },
    { "video1_rec",          20,     512,    128 },
    { "video2_rec",          20,     512,    128 },
    { "video3_rec",          20,    1024,    128 },
    { "audio0_rec",          20,    1024,    128 },
    { "audio1_rec",          20,    1024,    128 },
    { "audio2_rec",          20,    1024,    128 },
    { "audio3_rec",          20,    1024,    128 },
    { "net_avi",             18,     512,      0 },
    { "avi",                 11,     320,     64 },
    { "jpg_dec",             10,    1024,     32 },
    { "dynamic_huffman",     15,    1024,     32 },
    { "video_dec_server",    16,    1024,    256 },
    { "vunpkg_server",       16,    1024,    128 },
#endif
#ifdef CONFIG_UI_ENABLE
    { "lvgl_v8_main_task",   25,    8192,   1024 },
    { "touch_interupt_task", 15,     256,      0 },
#endif

    {0, 0},
};

#if 0
char task_designated_cpu(const char *task_name)//返回0指定CPU0运行,返回1指定CPU1运行,返回-1 CPU01都可以运行
{
    if (!strcmp(task_name, "init")) {
        return -1;//操作系统第一个任务init任务必须安装在核0,运行完会自动删除
    }
    if (!strcmp(task_name, "thread_fork_kill")) {
        return -1;
    }

    //用户在此增加指定任务

    return -1;
}
#endif


/*
 * 默认的系统事件处理函数
 * 当所有活动的app的事件处理函数都返回false时此函数会被调用
 */
void app_default_event_handler(struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        break;
    case SYS_TOUCH_EVENT:
        break;
    case SYS_DEVICE_EVENT:
        break;
    case SYS_NET_EVENT:
        break;
    case SYS_BT_EVENT:
        break;
    default:
        ASSERT(0, "unknow event type: %s\n", __func__);
        break;
    }
}


/*
 * 应用程序主函数
 */
void app_main()
{
    struct intent it;

    puts("------------- wifi_story_machine app main-------------\n");
#ifdef USE_LVGL_V8_UI_DEMO
    int lvgl_main_task_init(void);
    lvgl_main_task_init();
#endif

#if !TCFG_RF_FCC_TEST_ENABLE
    init_intent(&it);
    it.name = "app_music";
    it.action = ACTION_MUSIC_PLAY_MAIN;
    start_app(&it);
#endif

#if defined CONFIG_BT_ENABLE && !TCFG_WIFI_ENABLE
    extern void bt_ble_module_init(void);
    bt_ble_module_init();
#endif
}


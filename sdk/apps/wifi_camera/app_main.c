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
#include "asm/gpio.h"
#include "asm/clock.h"
#include "ctp_server.h"
#include "logo_show.h"

#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
#include "usb_stack.h"
#endif


/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
    /* { IRQ_ISC_IDX,		7,	0}, */
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
    { IRQ_WF_IDX,      3,   0    }, //此中断强制注册到cpu1
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
    {"thread_fork_kill",    25,      256,   0     },
    {"app_core",            15,     APP_CORE_STK_SIZE,	  APP_CORE_Q_SIZE,		 app_core_tcb_stk_q },
    {"sys_event",           29,     SYS_EVENT_STK_SIZE,	   0, 					 sys_event_tcb_stk_q },
    {"systimer",            14,     SYSTIMER_STK_SIZE, 	   0,					 systimer_tcb_stk_q },
    {"sys_timer",            9,     SYS_TIMER_STK_SIZE,	  SYS_TIMER_Q_SIZE,		 sys_timer_tcb_stk_q },
    {"audio_server",        16,      512,   64    },
    {"audio_mix",           28,      512,   0     },
    {"audio_encoder",       12,      384,   64    },
    {"mp3_encoder",         13,      768,   0     },
    {"vir_dev_task",        14,      256,   0     },
    {"vad_encoder",         14,      768,   0     },
    {"aec_encoder",         13,     1024,   0     },
    {"dns_encoder",         13,      512,   0     },
    {"msbc_encoder",        13,      256,   0     },
    {"sbc_encoder",         13,      512,   0     },
    {"adpcm_encoder",       13,      512,   0     },
    {"dynamic_huffman0",    15,		300,	32    },
    {"dynamic_huffman1",    15,		300,	32    },


    {"echo_deal",           11,     1024,   32    },
    {"uac_sync",            20,      512,   0     },
    {"uac_play0",           26,      512,   32    },
    {"uac_play1",           26,      512,   32    },
    {"uac_record0",         26,      512,   0     },
    {"uac_record1",         26,      512,   0     },
#if (RCSP_MODE)
    {"rcsp",            	4,       768,   128  },
    {"dev_mg",              3,       512,   512  },
#endif//RCSP_MODE
#if (TCFG_DEV_MANAGER_ENABLE)
    {"file_bs",              1,       768,   0  },
    {"ftran_back",           1,       512,   0  },
#endif
    {"usb_msd0",             10,      512,   128   },
    {"usb_msd1",             10,      512,   128   },
    {"uda_main",             2,     7000,   0     },

    {"update",              21,      512,   32    },
    {"dw_update",           21,      512,   32    },

#ifdef CONFIG_WIFI_ENABLE
    {"iperf_test",          15,     1024,   0     },
    {"tcpip_thread",        16,      800,   0     },
    {"tasklet",             19,     WIFI_TASKLET_STK_SIZE,   0,		 wifi_tasklet_tcb_stk_q	 },//通过调节任务优先级平衡WIFI收发占据总CPU的比重
    {"RtmpMlmeTask",        28,     WIFI_MLME_STK_SIZE,  	 0, 	 wifi_mlme_tcb_stk_q	 },
    {"RtmpCmdQTask",        17,     WIFI_CMDQ_STK_SIZE,   	 0,  	 wifi_cmdq_tcb_stk_q	 },
    {"wl_rx_irq_thread",    16,     WIFI_RX_STK_SIZE,    	 0,  	 wifi_rx_tcb_stk_q  	 },

    {"ctp_server",          28,     600,   64    },
    {"net_video_server",    16,     256,   64 	 },
    {"net_avi0",            18,     600,   600	 },
    {"net_avi1",            18,     600,   600	 },
    {"net_mov0",            18,     600,   600	 },
    {"net_mov1",            18,     600,   600	 },
    {"mov_unpkg0",          18,     600,   600	 },
    {"stream_avi0",         18,     320,   600	 },
    {"stream_avi1",         18,     320,   600	 },
    {"stream_mov0",         18,     320,   600	 },
    {"stream_mov1",         18,     320,   600	 },



#endif
#ifdef CONFIG_BT_ENABLE
    {"btencry",             14,      512,   128   },
    {"btctrler",            19,      512,   384   },
    {"btstack",             18,      768,   384   },
#endif
    {"wl80_test",            1,     2048,   64    },

    {"video_engine_server", 10,     1024,   1024  },
    {"video_engine_task",   10,     2048,   0     },

    {"vpkg_server",         16,      512,   128   },





    {"avi0",                28,      320,   64    },
    {"avi1",                28,      320,   64    },
    {"avi2",                28,      320,   64    },
    {"jpg_dec",             10,     1024,   32    },
    {"video_dec_server",    16,     1024,   256   },
    {"vunpkg_server",       16,     1024,   128   },
    {"lvgl_v8_main_task",   7,     2048,  1024   },

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
#ifdef CONFIG_NET_ENABLE
int net_video_event_hander(void *e)
{
    struct net_event *event = (struct net_event *)e;
    struct ctp_arg *event_arg = (struct ctp_arg *)event->arg;
    /* struct net_event *net = &event->u.net; */

    switch (event->event) {
    case NET_EVENT_CMD:
        printf("IN NET_EVENT_CMD\n");
        ctp_cmd_analysis(event_arg->topic, event_arg->content, event_arg->cli);
        if (event_arg->content) {
            free(event_arg->content);
        }
        event_arg->content = NULL;
        if (event_arg) {
            free(event_arg);
        }
        event_arg = NULL;
        return true;
        break;
    case NET_EVENT_DATA:
        /* printf("IN NET_EVENT_DATA\n"); */
        break;
    }
    return false;
}
#endif



/*
 * sd卡插拔事件处理
 */
static void sd_event_handler(struct device_event *event)
{


    /* struct vfs_partition *part = NULL; */
    switch (event->event) {

    case DEVICE_EVENT_IN:
#if defined CONFIG_ENABLE_VLIST

     printf("\n============%s========%d\n ",__FUNCTION__,__LINE__  );

        FILE_LIST_IN_MEM(1);
#endif
        break;
    case DEVICE_EVENT_OUT:
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_EXIT();
#endif
        break;


    }
}


#include "app_power_manage.h"
static void power_off_timer_cb(void *p)
{
    //杀掉lvgl线程


    //软关机
    sys_power_poweroff();
}

static int device_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;

    if (e->from == DEVICE_EVENT_FROM_OTG) {
    } else if (e->from == DEVICE_EVENT_FROM_SD) {
#if TCFG_SD0_ENABLE || TCFG_SD1_ENABLE
        sd_event_handler(event);
#endif
    } else if (e->from == DEVICE_EVENT_FROM_PC) {
        switch (event->event) {
        //添加USB弹窗
        case DEVICE_EVENT_IN:
#ifdef CONFIG_UI_ENABLE
            extern void usb_page_show(int arg);
            lvgl_rpc_post_func(usb_page_show, 1, 0);
#endif
            break;
        case DEVICE_EVENT_OUT:
#ifdef CONFIG_UI_ENABLE
            extern void usb_page_hide(int arg);
            lvgl_rpc_post_func(usb_page_hide, 1, 0);
#endif
            break;
        }

    } else if (e->from == DEVICE_EVENT_FROM_POWER && POWER_EVENT_POWER_AUTOOFF == event->event) { //关机事件
        //退出当前运行模式
        struct intent it;
        struct application *app;
        init_intent(&it);
        app = get_current_app();
        if (app) {
            it.action = ACTION_BACK;
            start_app(&it);
        }
#ifdef USE_LVGL_V8_UI_DEMO
        u8 time_out = 2;
        const char *image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweroff.jpg";
        const char *audio_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweroff.mp3";
        int ret = logo_show(image_path, audio_path, time_out, NULL);
#endif

        //倒计时软件关机
        sys_timeout_add(0, power_off_timer_cb, 3000);//3000是关机动画显示时间
#ifdef CONFIG_PARK_ENABLE
    } else if (e->from == DEVICE_EVENT_FROM_VIDEO && !strncmp((const char *)event->arg, "parking", 7)) {


        struct intent it;
        struct application *app;

        switch (event->event) {
        case DEVICE_EVENT_IN:
            puts("parking on\n"); //parking on
            puts("\n =============parking on eee video rec=========\n");
            extern u8 rec_park_flag;
            rec_park_flag++;
#ifdef CONFIG_UI_ENABLE
            extern void parking_page_show(int arg);
            lvgl_rpc_post_func(parking_page_show, 1, 0);
#endif

            sys_power_auto_shutdown_pause();
            return true;

        }
#endif
    }

    return 0;
}


/*
 *录像app的按键响应函数
 */
static int default_key_event_handler(struct key_event *key)
{
    int err;

    printf("\n ===%s,%d,key->action=====================%s,%d\n ",__FUNCTION__,__LINE__,key->action);
    switch (key->action) {
    case KEY_EVENT_LONG:
        switch (key->value) {
        case KEY_POWER:
            sys_power_shutdown();
            break;
        }
        break;
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_DOWN:
          #if 1
            struct intent it;
            init_intent(&it);

            it.name	= "video_rec";//APP状态机在：video_rec.c
            it.action = ACTION_VIDEO_REC_CONTROL;
            start_app(&it);
         #endif
            break;
        case KEY_OK:
           #if 1
            extern int user_video_rec_switch(u8 id);
            user_video_rec_switch(1);

           #endif
            break;
        }
    default:
        break;
    }

    return false;
}



/*
 * 默认的系统事件处理函数
 * 当所有活动的app的事件处理函数都返回false时此函数会被调用
 */
void app_default_event_handler(struct sys_event *event)
{
    printf("\n event->type=====================%d\n ",event->type);
    switch (event->type) {
    case SYS_KEY_EVENT:
        default_key_event_handler((struct key_event *)event->payload);
        break;
    case SYS_TOUCH_EVENT:
        break;
    case SYS_DEVICE_EVENT:
        device_event_handler(event);
        break;
    case SYS_NET_EVENT:
#ifdef CONFIG_NET_ENABLE
        net_video_event_hander((void *)event->payload);
#endif
        break;
    case SYS_BT_EVENT:
        break;
    default:
        ASSERT(0, "unknow event type: %s\n", __func__);
        break;
    }
}
static void pipe_test()
{
#if 0
    JL_PORTA->DIR = 0;
    JL_PORTB->DIR = 0;
    JL_PORTC->DIR = 0;
    JL_PORTD->DIR = 0;
    JL_PORTE->DIR = 0;
    while (1) {
        JL_PORTB->OUT ^= 0XFFFF;
        JL_PORTC->OUT ^= 0XFFFF;
        JL_PORTA->OUT ^= 0XFFFF;
        JL_PORTD->OUT ^= 0XFFFF;
        JL_PORTE->OUT ^= 0XFFFF;
    }
#endif
    os_time_dly(200);
    extern void pipeline_base_test();
    pipeline_base_test();
}

/*
 * 开机动画播放完毕
 */
static void logo_poweron_play_end(void)
{
    lvgl_main_task_init();

#if TCFG_USB_SLAVE_ENABLE
    //检测usb从机在线并显示usb界面
    u32 state;
    u8 usb_slave_online = 0;
    for (usb_dev usb_id = 0; usb_id < USB_MAX_HW_NUM; usb_id++) {
        state = usb_otg_online(usb_id);
        if ((state == SLAVE_MODE) || (state == SLAVE_MODE_WAIT_CONFIRMATION)) {
            usb_slave_online = 1;
            break;
        }
    }
    if (usb_slave_online) {
        while (lvgl_ui_is_suspended()) {
            os_time_dly(1);
        }
#ifdef CONFIG_UI_ENABLE
        extern void usb_page_show(int arg);
        lvgl_rpc_post_func(usb_page_show, 1, 0);
#endif
    }
#endif

    key_event_enable();
    touch_event_enable();
}

/*
 * 应用程序主函数
 */
void app_main()
{
    struct intent it;

    os_time_dly(20);
    //开机后检测是否需要升级
    fs_update_task();

#ifdef CONFIG_VIDEO_IQ_TOOLS_ENABLE
    u8 lcd_tools_main(void);
    lcd_tools_main();
#endif


    init_intent(&it);
    it.name = "video_system";
    it.action = ACTION_SYSTEM_MAIN;
    start_app(&it);

//语音唤醒
#if defined CONFIG_ASR_ALGORITHM
    extern int aisp_open(u16 sample_rate);
    aisp_open(16000);
#endif

#ifdef CONFIG_VIDEO5_ENABLE
  extern int first_open_video_server();
  first_open_video_server();
#endif
#ifdef USE_LVGL_V8_UI_DEMO
    int lvgl_main_task_init(void);
    u8 time_out = 2; //播放开机动画时间
    const char *image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.jpg";
    const char *audio_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.mp3";
    key_event_disable();
    int ret = logo_show(image_path, audio_path, time_out, (void *)logo_poweron_play_end);
    if (ret < 0) { //开机logo播放失败,则直接显示lvgl ui
        lvgl_main_task_init();
        key_event_enable();
        touch_event_enable();
    }
#else

    puts("------------- wifi_camera app main-------------\n");
    init_intent(&it);

    it.name	= "video_rec";//APP状态机在：video_rec.c
    it.action = ACTION_VIDEO_REC_MAIN;
    start_app(&it);
#endif

#if 0
   os_time_dly(200);
   usb_start(TCFG_USB_DEBUG_ID, MASSSTORAGE_CLASS | UVC_CLASS | CDC_CLASS);

   os_time_dly(100);
#endif
    /*生成文件列表*/
    if (dev_online(SDX_DEV)) {
        char buf[64];


#if defined CONFIG_ENABLE_VLIST
         printf("\n============%s========%d\n ",__FUNCTION__,__LINE__  );
        FILE_LIST_IN_MEM(1);
#endif
        strcpy(buf, "online:1");
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "SD_STATUS", "NOTIFY", buf);

    }

}



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

#include "tuya_video.h"

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

    { -1,     -1,   -1    },
};


/*创建使用 os_task_create_static 或者task_create 接口的 静态任务堆栈*/
#define SYS_TIMER_STK_SIZE 1024
#define SYS_TIMER_Q_SIZE 128
static u8 sys_timer_tcb_stk_q[sizeof(StaticTask_t) + SYS_TIMER_STK_SIZE * 4 + sizeof(struct task_queue) + SYS_TIMER_Q_SIZE] ALIGNE(4);

#define SYSTIMER_STK_SIZE 256
static u8 systimer_tcb_stk_q[sizeof(StaticTask_t) + SYSTIMER_STK_SIZE * 4] ALIGNE(4);

#define SYS_EVENT_STK_SIZE 1024
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
    {"led_ui_server",       30,      256,   64    },
    {"app_core",            15,     APP_CORE_STK_SIZE,	  APP_CORE_Q_SIZE,		 app_core_tcb_stk_q },
    {"sys_event",           29,     SYS_EVENT_STK_SIZE,	   0, 					 sys_event_tcb_stk_q },
    {"systimer",            14,     SYSTIMER_STK_SIZE, 	   0,					 systimer_tcb_stk_q },
    {"sys_timer",            9,     SYS_TIMER_STK_SIZE,	  SYS_TIMER_Q_SIZE,		 sys_timer_tcb_stk_q },
    {"audio_server",        16,      512,   64    },
    {"audio_mix",           28,      512,   0     },
    {"audio_encoder",       12,      384,   64    },
    {"speex_encoder",       13,      512,   0     },
    {"mp3_encoder",         13,      768,   0     },
    {"opus_encoder",        13,     1536,   0     },
    {"vir_dev_task",        14,      256,   0     },
    {"amr_encoder",         13,     1024,   0     },
    {"cvsd_encoder",        13,      512,   0     },
    {"vad_encoder",         14,      768,   0     },
    {"aec_encoder",         13,     1024,   0     },
    {"dns_encoder",         13,      512,   0     },
    {"msbc_encoder",        13,      256,   0     },
    {"sbc_encoder",         13,      512,   0     },
    {"adpcm_encoder",       13,      512,   0     },
    {"video_server_transfer",        28,     1024,   0},
    {"dynamic_huffman0",    15,		1024,	32    },
    {"dynamic_huffman1",    15,		1024,	32    },


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
    {"usb_msd0",             1,      512,   128   },
    {"usb_msd1",             1,      512,   128   },
    {"uda_main",             2,     7000,   0     },

    {"update",              21,      512,   32    },
    {"dw_update",           21,      512,   32    },
    {"iperf_test",          15,     1024,   0     },

    {"tcpip_thread",        16,      800,    0    },
#ifdef TCFG_WIFI_ENABLE
    {"tcpip_thread",        16,      800,   0     },
    {"tasklet",             10,     WIFI_TASKLET_STK_SIZE,   0,		 wifi_tasklet_tcb_stk_q	 },//通过调节任务优先级平衡WIFI收发占据总CPU的比重
    {"RtmpMlmeTask",        17,     WIFI_MLME_STK_SIZE,  	 0, 	 wifi_mlme_tcb_stk_q	 },
    {"RtmpCmdQTask",        17,     WIFI_CMDQ_STK_SIZE,   	 0,  	 wifi_cmdq_tcb_stk_q	 },
    {"wl_rx_irq_thread",     7,     WIFI_RX_STK_SIZE,    	 0,  	 wifi_rx_tcb_stk_q  	 },
#endif
#ifdef CONFIG_BT_ENABLE
    {"btencry",             14,      512,   128   },
    {"btctrler",            19,      512,   384   },
    {"btstack",             18,      768,   384   },
#endif
    {"wl80_test",            1,     2048,   64    },

    {"video_server",        16,      768,   128   },
    {"vpkg_server",         16,      512,   128   },

    {"net_video_server",    16,      256,   64    },

    {"net_avi0",            18,      512,   0     },
    {"net_avi1",            18,      512,   0     },

    {"avi0",                11,      320,   64    },
    {"avi1",                11,      320,   64    },
    {"mov0",                11,      512,   64    },
    {"mov1",                11,      512,   64    },
    {"mov2",                11,      512,   64    },
    {"jpg_dec",             10,     1024,   32    },
    {"video_dec_server",    16,     1024,   256   },
    {"vunpkg_server",       16,     1024,   128   },
    {"ui",                  21,      768,   256   },
    {"lvgl_v8_main_task",   25,     8192,  1024   },

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
#ifndef CONFIG_TUYA_SDK_ENABLE
    struct intent it;

#ifdef USE_LVGL_V8_UI_DEMO
    int lvgl_main_task_init(void);
    lvgl_main_task_init();
#endif

    puts("------------- wifi_ipc app main-------------\n");
    init_intent(&it);
    it.name	= "video_rec";//APP状态机在：video_rec.c
    /* it.action = ACTION_VIDEO_REC_MAIN; */
    it.action = ACTION_VIDEO_REC_DISPLAY;
    start_app(&it);
#endif
}




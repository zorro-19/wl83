/****************************************************************************/
/* camx_plat.c
 *
 ****************************************************************************/

/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

#include "camx.h"

/****************************************************************************/
/* Trace Definitions                                                        */
/****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "camx_key"
#include "xc_log.h"
/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/
/* key entry */
#define CAMX_KEY_ENTRY(name_, from_, action_, keyval_, fn_)                  \
    {                                                                        \
        name_, from_, action_, keyval_, fn_                                  \
    }
#define CAMX_KEY_ENTRY0(name_, from_, action_, keyval_, fn_)
/****************************************************************************/
/* Private Types                                                            */
/****************************************************************************/
struct camx_key_item {
    const char *name;     // KEY function name
    uint8_t     from;     // KEY_EVENT_FROM_KEY
    uint8_t     action;   // KEY_EVENT_CLICK
    uint8_t     keyval;   // KEY_K1
    void (*key_fn)(void); // key_fn
};

/****************************************************************************/
/* Private Function Prototypes                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Data                                                             */
/****************************************************************************/

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Functions                                                        */
/****************************************************************************/

/****************************************************************************/
/* Public Functions                                                         */
/****************************************************************************/
int led_speed = 5000;
#define LED_PIN  1 //todo
#define IR_LED_PIN  1 //todo
void led_status_speed(u32 state)
{
    led_speed = state;
}
// LED闪烁函数，作为线程执行的任务
void  blink_led(int arg)
{
    int ret = 0;

    u32 totleSecNum = 0;

    while (1) {

        if (led_speed >= 5000) {
            gpio_direction_output(LED_PIN, 1);
            os_time_dly(100);
        } else {
            ret ^= 1;
            gpio_direction_output(LED_PIN, ret);
            os_time_dly(led_speed); // 等待一段时间，使用速度参数控制闪烁周期
        }

        if (camx_uwifi_sta_connected()) {

            totleSecNum = ((get_utc_ms()) / 1000) % (24 * 60 * 60); //当天剩余的秒速

            /* if (totleSecNum / 3600 == 0 && (totleSecNum % 3600) / 60 == 0 && (totleSecNum % 3600) % 60 == 0) { */
            if ((totleSecNum % 3600) == 0) {  //每小时设置一下
                set_utc_ms(get_utc_ms()); //每24小时就设置一下rtc

            }
        }
    }
}

void led_status_ctl(void)
{
    thread_fork("LED_STATUS_CTL_THREAD", 10, 256, 0, 0, blink_led, led_speed);
}


static void keyfn_reset(void)
{
    camx_plat_reset(0);
}


static void keyfn_poweroff(void)
{
    sys_power_poweroff();
    //camx_plat_reset(0);
}

void ir_led_ctl(u8 ctl)
{
    gpio_direction_output(IR_LED_PIN, ctl);
}

static void keyfn_ota_upg(void)
{
    //python -m SimpleHTTPServer 9999
    /* const char *url = "http://192.168.137.1:9999/update-ota.ufw"; */
    /* camx_ota_upgrade(url); */
}

static void keyfn_reboot(void)
{
    camx_plat_reboot(0);
}

const struct camx_key_item s_camx_key_items[] = {
#if TCFG_ADKEY_ENABLE
    CAMX_KEY_ENTRY(
        /* name   */ "reset",
        /* from   */ KEY_EVENT_FROM_KEY,
        /* action */ KEY_EVENT_HOLD,
        /* keyval */ KEY_MODE,
        /* keyfn  */ keyfn_reset),
    CAMX_KEY_ENTRY(
        /* name   */ "poweroff",
        /* from   */ KEY_EVENT_FROM_KEY,
        /* action */ KEY_EVENT_HOLD,
        /* keyval */ KEY_POWER,
        /* keyfn  */ keyfn_poweroff),
#endif /* TCFG_IOKEY_ENABLE */


#if TCFG_IOKEY_ENABLE
    CAMX_KEY_ENTRY(
        /* name   */ "reset",
        /* from   */ KEY_EVENT_FROM_KEY,
        /* action */ KEY_EVENT_LONG,
        /* keyval */ KEY_MODE,
        /* keyfn  */ keyfn_reset),
    CAMX_KEY_ENTRY(
        /* name   */ "poweroff",
        /* from   */ KEY_EVENT_FROM_KEY,
        /* action */ KEY_EVENT_LONG,
        /* keyval */ KEY_POWER,
        /* keyfn  */ keyfn_poweroff),
#endif /* TCFG_IOKEY_ENABLE */


};

int camx_key_handler(u8 from, u8 action, u8 keyval)
{
    int i;
    for (i = 0; i < OSAL_ARRAY_SIZE(s_camx_key_items); i++) {
        if (s_camx_key_items[i].action == action &&
            s_camx_key_items[i].keyval == keyval) {
            T_I("`KEY_TRIG` -> `%s`", s_camx_key_items[i].name);
            s_camx_key_items[i].key_fn();
            return (0);
        }
    }

    return (-1);
}



/*
 * 默认的系统事件处理函数
 * 当所有活动的app的事件处理函数都返回false时此函数会被调用
 */
void key_event_handler(struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        printf("key_event_handler!!!!!!!!!!!!!!!!!!!!!\n");
        //ipc_key_event_handler((struct key_event *)event->payload);
        struct key_event *e = (struct key_event *)event->payload;
        printf("event->type:%d  e->action:%d  e->value:%d\n", event->type, e->action, e->value);
        camx_key_handler(event->type, e->action, e->value);
        break;
    case SYS_DEVICE_EVENT:
        break;
    case SYS_BT_EVENT:
        break;
    case SYS_NET_EVENT:
        break;
    default:
        //ASSERT(0, "unknow event type: %s\n", __func__);
        break;
    }
}


/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(camx_key_event, 0) = {
    .event_type     = SYS_KEY_EVENT,
    .prob_handler   = key_event_handler,
    .post_handler   = NULL,
};




/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

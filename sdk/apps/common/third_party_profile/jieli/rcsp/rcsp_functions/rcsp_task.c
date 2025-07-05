#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_task.data.bss")
#pragma data_seg(".rcsp_task.data")
#pragma const_seg(".rcsp_task.text.const")
#pragma code_seg(".rcsp_task.text")
#endif
#include "rcsp_task.h"
#include "app_config.h"
#include "rcsp.h"
#include "rcsp_extra_flash_opt.h"
#include "file_transfer.h"
#include "file_delete.h"
#include "dev_format.h"
#include "btstack/avctp_user.h"
#include "file_bluk_trans_prepare.h"
#include "sport_data_func.h"
#include "ble_rcsp_server.h"
#include "timer.h"
#include "rcsp_define.h"
/* #include "app_task.h" */

#if (RCSP_MODE)

/* #define RCSP_DEBUG_EN */
#ifdef RCSP_DEBUG_EN
#define rcsp_putchar(x)                	putchar(x)
#define rcsp_printf                    	printf
#define rcsp_put_buf(x,len)				put_buf(x,len)
#else
#define rcsp_putchar(...)
#define rcsp_printf(...)
#define rcsp_put_buf(...)
#endif

//这个模式主要是提供一个空模式， 处理一些需要占用时间不较长的交互处理， 处理做完之后退回到原来的模式
struct __action_event {
    u8	type;		//1:手机端触发, 0:固件触发
    u8 	OpCode_SN;
    u8	action;
};
static struct __action_event action_prepare = {0};
static u8 file_transfer_idle = 1;
static u8 temp_a2dp_en_flag = 0;
static u8 rcsp_file_bluk_trans_flag = 0;
static u8 g_disable_opt_before_start = 1;
static u16 task_switch_flag;

u8 bt_get_a2dp_en_status();
void bt_set_a2dp_en_status(u8 on);
void lmp_esco_rejust_establish(u8 value);
void set_rcsp_watch_upgrade_flag(u8 flag);

static void app_rcsp_task_get_ready(void)
{
    rcsp_printf("%s\n", __FUNCTION__);
    notify_update_connect_parameter(3);
    if (action_prepare.type) {
        JL_CMD_response_send(JL_OPCODE_ACTION_PREPARE, JL_PRO_STATUS_SUCCESS, action_prepare.OpCode_SN, NULL, 0, 0, NULL);
    }
}

static int app_rcsp_action_mode(void)
{
#if JL_RCSP_EXTRA_FLASH_OPT
    if (rcsp_eflash_update_flag_get() || rcsp_file_bluk_trans_flag) {
        return -1;
    }
#endif
    return 0;
}

__attribute__((weak))
int app_goto_prev_mode()
{
    rcsp_printf("%s not implement", __func__);
    return 0;
}


__attribute__((weak))
int app_task_switch_to(u8 app_task, int priv)
{
    rcsp_printf("%s not implement", __func__);
    return false;
}

__attribute__((weak))
u8 app_get_curr_task(void)
{
    rcsp_printf("%s not implement", __func__);
    return 0;
}

static void app_rcsp_action_end_callback(void)
{
    app_rcsp_task_switch_stop();
    //cppcheck-suppress knownConditionTrueFalse
    if (app_rcsp_action_mode()) {
        return;
    }
    printf("=======RCSP TODO==%s=%d========\n\r", __func__, __LINE__);
#if 0 ///RCSP TODO
    if (app_get_curr_task() == APP_RCSP_ACTION_TASK) {
        rcsp_printf("action end callback!!\n");
        app_task_switch_back();
    }
#endif
}

static void app_rcsp_bluk_trans_end_callback(void)
{
    rcsp_file_bluk_trans_flag = 0;
    app_rcsp_action_end_callback();
}

static void app_rcsp_task_start(void)
{
#if (RCSP_MODE == RCSP_MODE_WATCH)
    lmp_esco_rejust_establish(1);
    set_rcsp_watch_upgrade_flag(1);
    temp_a2dp_en_flag = bt_get_a2dp_en_status();
    bt_set_a2dp_en_status(0);
#endif
    if (g_disable_opt_before_start) {
        /* clock_add_set(RCSP_ACTION_CLK); */
    }
#if (RCSP_MODE == RCSP_MODE_WATCH)
    user_send_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
    file_transfer_idle = 0;
#endif
    app_rcsp_task_get_ready();
    //根据不同的场景， 做不同的处理， 例如：初始化不同的UI显示
    switch (action_prepare.action)		{
#if TCFG_DEV_MANAGER_ENABLE
    case RCSP_TASK_ACTION_FILE_TRANSFER:
        //cppcheck-suppress knownConditionTrueFalse
        if (!app_rcsp_action_mode()) {
#if UI_UPGRADE_RES_ENABLE   //升级界面功能
#if TCFG_UI_ENABLE
            UI_WINDOW_PREEMPTION_POSH(ID_WINDOW_UPGRADE, NULL, NULL, UI_WINDOW_PREEMPTION_TYPE_UPGRADE);
            UI_MSG_POST("upgrade:wait=%4", 4);
#endif
#endif
        }
        rcsp_file_transfer_init(app_rcsp_action_end_callback);
        break;
    case RCSP_TASK_ACTION_FILE_DELETE:
        //cppcheck-suppress knownConditionTrueFalse
        if (!app_rcsp_action_mode()) {
#if UI_UPGRADE_RES_ENABLE   //升级界面功能
#if TCFG_UI_ENABLE
            UI_WINDOW_PREEMPTION_POSH(ID_WINDOW_UPGRADE, NULL, NULL, UI_WINDOW_PREEMPTION_TYPE_UPGRADE);
            UI_MSG_POST("upgrade:wait=%4", 4);
#endif
#endif
        }
        rcsp_file_delete_init(app_rcsp_action_end_callback);
        break;
    case RCSP_TASK_ACTION_DEV_FORMAT:
        //cppcheck-suppress knownConditionTrueFalse
        if (!app_rcsp_action_mode()) {
#if UI_UPGRADE_RES_ENABLE   //升级界面功能
#if TCFG_UI_ENABLE
            UI_WINDOW_PREEMPTION_POSH(ID_WINDOW_UPGRADE, NULL, NULL, UI_WINDOW_PREEMPTION_TYPE_UPGRADE);
            UI_MSG_POST("upgrade:wait=%4", 4);
#endif
#endif
        }
        rcsp_dev_format_init(app_rcsp_action_end_callback);
        break;
    case RCSP_TASK_ACTION_BLUK_TRANSFER:
        rcsp_file_bluk_trans_flag = 1;
        rcsp_file_bluk_trans_init(app_rcsp_bluk_trans_end_callback);
        break;
#endif
#if JL_RCSP_EXTRA_FLASH_OPT
    case RCSP_TASK_ACTION_WATCH_TRANSFER:
        rcsp_extra_flash_init();
        break;
    case RCSP_TASK_ACTION_RESET_EX_FLASH:
#if RCSP_UPDATE_EN
        rcsp_eflash_update_flag_set(1);
        rcsp_eflash_flag_set(1);
        extern void set_update_ex_flash_flag(u8 update_flag);
        set_update_ex_flash_flag(1);
#if TCFG_UI_ENABLE
        UI_WINDOW_PREEMPTION_POSH(ID_WINDOW_UPGRADE, NULL, NULL, UI_WINDOW_PREEMPTION_TYPE_UPGRADE);
        UI_MSG_POST("upgrade:wait=%4", 4);
#endif
#else
        app_rcsp_action_end_callback();
#endif
        break;
#endif
    default:
        break;
    }
}

void app_rcsp_prepare_update_ex_flash(void)
{
    app_rcsp_task_prepare(0, RCSP_TASK_ACTION_RESET_EX_FLASH, 0);
}

static void app_rcsp_task_stop(void)
{
#if (RCSP_MODE == RCSP_MODE_WATCH)
    extern int f_flush_wbuf(const char *path);
    notify_update_connect_parameter(-1);
#endif
    switch (action_prepare.action)		{
    case RCSP_TASK_ACTION_FILE_TRANSFER:
#if (RCSP_MODE == RCSP_MODE_WATCH)
        f_flush_wbuf("storage/sd1/C/");
#endif
        break;
    case RCSP_TASK_ACTION_FILE_DELETE:
        break;
    case RCSP_TASK_ACTION_DEV_FORMAT:
        break;
    case RCSP_TASK_ACTION_WATCH_TRANSFER:
#if JL_RCSP_EXTRA_FLASH_OPT
        rcsp_extra_flash_close();
        f_flush_wbuf("storage/virfat_flash/C/");
#endif
        break;
    default:
        break;
    }

    if (g_disable_opt_before_start) {
        /* clock_remove_set(RCSP_ACTION_CLK); */
    } else {
        g_disable_opt_before_start = 1;
    }
#if (RCSP_MODE == RCSP_MODE_WATCH)
    file_transfer_idle = 1;
    lmp_esco_rejust_establish(0);
    extern u8 get_call_status();
    //传输结束后如果仍在通话状态，则不清变量标志位，等到挂断后再清
    if (get_call_status() == BT_CALL_HANGUP) {
        set_rcsp_watch_upgrade_flag(0);
    }
    bt_set_a2dp_en_status(temp_a2dp_en_flag);
    sport_data_func_get_finish_deal();
    rcsp_printf("app_rcsp_task_stop\n");
#if UI_UPGRADE_RES_ENABLE   //升级界面功能
    UI_WINDOW_PREEMPTION_POP(ID_WINDOW_UPGRADE);
#endif
#endif
}

void file_trans_idle_set(u8 file_trans_idle_flag)
{
    file_transfer_idle = file_trans_idle_flag;
}

u8 file_trans_idle_query(void)
{
    return file_transfer_idle;
}

#if (RCSP_MODE == RCSP_MODE_WATCH)
REGISTER_LP_TARGET(rcsp_lp_target) = {
    .name = "rcsp",
    .is_idle = file_trans_idle_query,
};
#endif

static int app_rcsp_task_event_handle(struct sys_event *event)
{
    switch (action_prepare.action)		{
    case RCSP_TASK_ACTION_FILE_TRANSFER:
        break;
    case RCSP_TASK_ACTION_FILE_DELETE:
        break;
    case RCSP_TASK_ACTION_DEV_FORMAT:
        break;
    case RCSP_TASK_ACTION_WATCH_TRANSFER:
#if JL_RCSP_EXTRA_FLASH_OPT
        return rcsp_extra_flash_event_deal(event);
#endif
        break;
    case RCSP_TASK_ACTION_BLUK_TRANSFER:
        break;
    default:
        break;
    }
    return 0;
}

/* extern u16 sys_timeout_add(void *priv, void (*func)(void *priv), u32 msec); */
static void app_rcsp_task_switch(void *priv)
{
    u16 flag = (u16)priv;
    if (flag != task_switch_flag) {
        rcsp_printf("\n\n %s, %d \n\n", __func__, __LINE__);
        rcsp_printf("flag:%d, %d \n", flag, task_switch_flag);
        return ;
    }
    task_switch_flag ++;
    printf("=======RCSP TODO==%s=%d========\n\r", __func__, __LINE__);
#if 0 ///RCSP TODO
    int ret = app_task_switch_to(APP_RCSP_ACTION_TASK, NULL_VALUE);
    if (ret == false) {
        /* rcsp_printf("\n\n %s, %d \n\n", __func__, __LINE__); */
        sys_timeout_add((void *)(long)task_switch_flag, app_rcsp_task_switch, 500);
    }
#endif
}

void app_rcsp_task_switch_stop(void)
{
    task_switch_flag ++;
}

void app_rcsp_task_prepare(u8 type, u8 action, u8 OpCode_SN)
{
    action_prepare.type = type;
    action_prepare.action = action;
    action_prepare.OpCode_SN = OpCode_SN;

    task_switch_flag ++;

    //切换模式
    printf("=======RCSP TODO==%s=%d========\n\r", __func__, __LINE__);
#if 0 //TODO
    if (app_get_curr_task() != APP_RCSP_ACTION_TASK) {
#if (RCSP_MODE == RCSP_MODE_WATCH)
        sport_data_func_get_prepare_deal();
#endif
        int ret = app_task_switch_to(APP_RCSP_ACTION_TASK, NULL_VALUE);
        if (ret == false) {
            /* rcsp_printf("\n\n %s, %d \n\n", __func__, __LINE__); */
            sys_timeout_add((void *)(long)task_switch_flag, app_rcsp_task_switch, 500);
        }
    } else if (app_rcsp_action_mode()) {
        app_rcsp_task_start();
    } else {
        app_rcsp_task_get_ready();
    }
#endif
}

void app_rcsp_task_disable_opt(void)
{
    g_disable_opt_before_start = 0;
}

__attribute__((weak))
void app_task_get_msg(int *msg, int msg_size, int block)
{
    rcsp_printf("%s not implement", __func__);
}

__attribute__((weak))
void app_default_event_deal(struct sys_event *event)
{
    rcsp_printf("%s not implement", __func__);
}

void app_rcsp_task(void)
{
    int msg[32];
    app_rcsp_task_start();
    while (1) {
        app_task_get_msg(msg, ARRAY_SIZE(msg), 1);

        switch (msg[0]) {
        /* case APP_MSG_SYS_EVENT: */
        case Q_EVENT:
            if (app_rcsp_task_event_handle((struct sys_event *)(msg + 1)) == false) {
                app_default_event_deal((struct sys_event *)(&msg[1]));
            }
            break;
        default:
            break;
        }
#if 0 ///RCSP TODO
        if (app_task_exitting()) {
            app_rcsp_task_stop();
            return;
        }
#endif
    }
}

#else // RCSP_MODE

void app_rcsp_task(void)
{

}

void file_trans_idle_set(u8 file_trans_idle_flag)
{

}

#endif // RCSP_MODE


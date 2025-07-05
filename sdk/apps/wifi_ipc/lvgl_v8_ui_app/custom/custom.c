/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include <time.h>
#include "events_init.h"
#include <stdio.h>
#include "callback_handler.h"
#include "gui_timelines.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
enum {
    MENU_ITEM_APP = 1,
    MENU_ITEM_LANGUAGE,
    MENU_ITEM_SYSSET,
    MENU_ITEM_SYSINFO,
};


/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */

}

#if LV_USE_GUIBUILDER_SIMULATOR//添加仿真宏---使用工具仿真自定义的代码有可能找不到定义编译不过

#else
#include "event/key_event.h"
#include "ui.h"
#include "syscfg/syscfg_id.h"
#include "ut_dev_ipc_cmd.h"
/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_timer_t *t_timer = 0;
lv_group_t *adkey_group = 0;
extern lv_indev_t *indev_keypad;
extern int net_qr_start;

/**********************
 *  STATIC VARIABLES
 **********************/

void lvgl_key_value_remap(u8 key_value, uint32_t *key_remap)
{
    switch (key_value) {
    case KEY_POWER:
        *key_remap = LV_KEY_UP;
        break;
    case KEY_MODE:
        *key_remap = LV_KEY_DOWN;
        break;
    case KEY_UP:
        *key_remap = LV_KEY_LEFT;
        break;
    case KEY_DOWN:
        *key_remap = LV_KEY_RIGHT;
        break;
    case KEY_OK:
        *key_remap = LV_KEY_ENTER;
        break;
    }

}

/* 注册控件模型 */
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_POWER)
.onchange = gui_model_msg_power_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_SIGNAL)
.onchange = gui_model_msg_signal_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_POWER_NUMBER)
.onchange = gui_model_msg_power_number_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_SYSTIME)
.onchange = gui_model_msg_systime_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_TIPS)
.onchange = gui_model_msg_tips_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_WEATHER)
.onchange = gui_model_msg_weather_cb,
};


void bat_reflesh_timer_cb_t(struct _lv_timer_t *p)
{
    static int flg = 0;
    static int net_qr_start = 0;//开始配网
    static int netcfg_cnt = 0;//3秒后重启 让用户打开蓝牙或者扫码配网
    static int netcfg_rest = 0;//配网前的重启

    if (++flg > 4) {
        flg = 0;
    }

    syscfg_read(CFG_USER_NET_CFG, &net_qr_start, sizeof(net_qr_start));
    syscfg_read(CFG_USER_NET_CFG_REST, &netcfg_rest, sizeof(netcfg_rest));

    if (net_qr_start) { //是否启动了二维码配网
        extern int camx_plat_reset(uint32_t flag);
        if (++netcfg_cnt > 3 && !netcfg_rest) {
            netcfg_rest = 1;
            syscfg_write(CFG_USER_NET_CFG_REST, &netcfg_rest, sizeof(netcfg_rest));
            app_play_tone_file("PowerOff.mp3");
            os_time_dly(300);
#ifdef CONFIG_XCIOT_ENABLE
            camx_plat_reset(0);
#else
            system_reset(1);
#endif //CONFIG_XCIOT_ENABLE

        }
        if (netcfg_rest) { //配网前的重启
            lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TIPS, _("ScanCode"), strlen(_("ScanCode")), 0);
        } else {
            lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TIPS, _("resetinfo"), strlen(_("resetinfo")), 0);
        }
//            lv_obj_clear_flag(guider_ui.home_lbl_note, LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TIPS, " ", strlen(" "), 0);
    }

    //电量更新
    int vbt = get_vbat_level() * 10 / 42;
    if (vbt <= 15) {
        lv_imglist_set_act(guider_ui.home_imglist_bat, 0);
    } else if (vbt > 15 && vbt <= 25) {
        lv_imglist_set_act(guider_ui.home_imglist_bat, 1);
    } else if (vbt > 25 && vbt <= 50) {
        lv_imglist_set_act(guider_ui.home_imglist_bat, 2);
    } else if (vbt > 50 && vbt <= 75) {
        lv_imglist_set_act(guider_ui.home_imglist_bat, 3);
    } else if (vbt > 75 && vbt <= 100) {
        lv_imglist_set_act(guider_ui.home_imglist_bat, 4);
    }
    if (sys_power_is_charging()) {
        lv_imglist_set_act(guider_ui.home_imglist_bat, 5);
    }

    //wifi信号图标更新
    if (wifi_is_on()) {
        int rssi = wifi_get_rssi();

        if (rssi > -60 && rssi <= -40) { //强
            lv_imglist_set_act(guider_ui.home_imglist_wifi, 4);
        } else if (rssi > -70 && rssi <= -60) { //良好
            lv_imglist_set_act(guider_ui.home_imglist_wifi, 3);
        } else if (rssi > -85 && rssi <= -70) { //中等
            lv_imglist_set_act(guider_ui.home_imglist_wifi, 2);
        } else if (rssi < -85) { //弱
            lv_imglist_set_act(guider_ui.home_imglist_wifi, 1);
        } else {
            lv_imglist_set_act(guider_ui.home_imglist_wifi, 0);
        }
#if 1
        //测试模型消息发送--天气更新
        iot_weatherInfo_t weather_info = {0};
        avsdk_get_weather(&weather_info);
        int32_t res_id_test;
        //天气 1.晴 2.大部晴朗 3.多云 4.少云 5.阴
        // 6.阵雨 7.局部阵雨 8.小阵雨 9.强阵雨 10.阵雪
        // 11.小阵雪 12.雾 13.冻雾 14.沙尘暴 15.浮尘
        // 16.尘卷风 17.扬沙 18.强沙尘暴 19.霾 20.雷阵雨
        // 21.雷电 22.雷暴 23.雷阵雨伴有冰雹 24.冰雹 25.冰针
        // 26.冰粒 27.雨夹雪 28.雨 29.小雨 30.中雨
        // 31.大雨 32.暴雨 33.大暴雨 34.特大暴雨 35.雪
        // 36.小雪 37.中雪 38.大雪 39.暴雪 40.冻雨
        // 41.小到中雨 42.中到大雨 43.大到暴雨 44.小到中雪
        switch (weather_info.info.condition) {
        case 1:
            res_id_test = RES_WEATHER_001;
            break;
        case 2:
            res_id_test = RES_WEATHER_004;
            break;
        case 3:
            res_id_test = RES_WEATHER_005;
            break;
        case 4:
            res_id_test = RES_WEATHER_002;
            break;
        default:
            res_id_test = RES_WEATHER_004;
            break;

        }
        lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_WEATHER, res_id_test, 0);
#endif // 0

    }
}
void home_timer_create(void)
{
    if (!t_timer) {
        t_timer = lv_timer_create(bat_reflesh_timer_cb_t, 1000, NULL);
    }
}

void home_timer_delete(void)
{
    if (t_timer) {
        lv_timer_del(t_timer);
        t_timer = 0;
    }
}

/* 各个控件模型的消息处理回调 */
int gui_model_msg_tips_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    char tips_init_var[] = "";
    bool tips_is_init = false;
    char *tips_var = NULL;
    if (tips_is_init == false) {
        tips_var = lv_mem_alloc(strlen(tips_init_var) + 1);
        strcpy(tips_var, tips_init_var);
        tips_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(tips_var);
        tips_var = lv_mem_alloc(strlen((char *)data->value_string) + 1);
        strcpy(tips_var, (char *)data->value_string);
    }
    data->value_string = tips_var;
#else
#endif
}

int gui_model_msg_weather_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{

    int32_t power_var = RES_WEATHER_010;
    data->value_int = power_var;
}

#include "sys_time.h"
static struct sys_time usr_time;
extern void get_sys_time(struct sys_time *time);

int gui_model_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    struct tm systime_var = {0};

    get_sys_time(&usr_time);
    systime_var.tm_year = usr_time.year - 1900;
    systime_var.tm_mon = usr_time.month - 1;
    systime_var.tm_mday = usr_time.day;
    systime_var.tm_hour = usr_time.hour;
    systime_var.tm_min = usr_time.min;
    systime_var.tm_sec = usr_time.sec;
    data->value_time = systime_var;
#else
#endif
}

int gui_model_msg_power_number_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    char power_str[16] = "100%";
    sprintf(power_str, "%d%%", get_vbat_level() * 10 / 42);
    data->value_string = power_str;
#else
#endif
}

int gui_model_msg_power_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    int32_t power_var = RES_ICON_BATTERY_100;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    int vbt = get_vbat_level() * 10 / 42;
    if (vbt <= 15) {
        power_var = RES_ICON_BATTERY_15;
    } else if (vbt > 15 && vbt <= 25) {
        power_var = RES_ICON_BATTERY_25;
    } else if (vbt > 25 && vbt <= 50) {
        power_var = RES_ICON_BATTERY_50;
    } else if (vbt > 50 && vbt <= 75) {
        power_var = RES_ICON_BATTERY_75;
    } else if (vbt > 75 && vbt <= 100) {
        power_var = RES_ICON_BATTERY_100;
    }
    if (sys_power_is_charging()) {
        power_var = RES_ICON_BATTERY_CHARGING;
    }

    data->value_int = power_var;
#else
#endif
}

int gui_model_msg_signal_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    int32_t signal_var = RES_ICON_WIFI;
    int rssi = 0;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (wifi_is_on()) {
        rssi = wifi_get_rssi();
    }

    if (rssi > -60 && rssi <= -40) { //强
        signal_var = RES_WIFI_04;
    } else if (rssi > -70 && rssi <= -60) { //良好
        signal_var = RES_WIFI_03;
    } else if (rssi > -85 && rssi <= -70) { //中等
        signal_var = RES_WIFI_2;
    } else if (rssi < -85) { //弱
        signal_var = RES_WIFI_01;
    } else {
        signal_var = RES_WIFI_00;
    }

    data->value_int = signal_var;
#else
#endif
}

int gui_model_msg_keyfun1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    int32_t keyfun1_var = RES_ICON_CALL_OUT;
    data->value_int = keyfun1_var;
#else
#endif
}

int gui_model_msg_keyfun2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    int32_t keyfun2_var = RES_ICON_WALKIE_TALKIE;
    data->value_int = keyfun2_var;
#else
#endif
}

int gui_model_msg_keyfun3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    int32_t keyfun3_var = RES_ICON_RECOVER;
    data->value_int = keyfun3_var;
#else
#endif
}

#endif

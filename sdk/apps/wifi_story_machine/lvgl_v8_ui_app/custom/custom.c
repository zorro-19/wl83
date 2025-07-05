#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include <time.h>
#include "gui_guider.h"

#if LV_USE_GUIBUILDER_SIMULATOR

#else

#include "ui.h"
#include "key_event.h"
#include "device_event.h"
#include "net_event.h"
#include "bt_event.h"
#include "avctp_user.h"
#include "wifi/wifi_connect.h"
#include "video_ioctl.h"
#include "action.h"

#endif


static char sta_text[100];
static char bt_name[50];
static char bt_state[50];
static int recorder_volume = 50;

void gui_connect_wifi(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    char *ssid = (char *)lv_textarea_get_text(guider_ui.wifi_ssid_txt);
    char *pwd = (char *)lv_textarea_get_text(guider_ui.wifi_pwd_txt);
    printf("ssid :%s  pwd: %s \n", ssid, pwd);
#else
#if defined CONFIG_NET_ENABLE
    char *ssid = (char *)lv_textarea_get_text(guider_ui.wifi_ssid_txt);
    char *pwd = (char *)lv_textarea_get_text(guider_ui.wifi_pwd_txt);
    printf("-----ssid :%s pwd: %s -----\n", ssid, pwd);
    extern void wifi_sta_connect(char *ssid, char *pwd, char save);
    wifi_sta_connect(ssid, pwd, 0);
#endif
#endif
}

void gui_open_camera(unsigned char id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("open camera id: %d\n", id);
#else
#if defined CONFIG_VIDEO_ENABLE
    struct video_window win1 = {0};
    win1.width = 480;
    win1.height = 800;

    //CAM3(MIPI)  video_id:1
    //CAM2(DVO)   video_id:0
    //CAM1(MIPI)  video_id:3
    extern int user_video_disp_start(int video_id, int sub_id, const struct video_window * win);
    user_video_disp_start(id, 0, &win1);
#endif
#endif
}

void gui_close_camera(unsigned char id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("open camera id: %d\n", id);
#else
#if defined CONFIG_VIDEO_ENABLE
    //CAM3(MIPI)  video_id:1
    //CAM2(DVO)   video_id:0
    //CAM1(MIPI)  video_id:3
    extern int user_video_disp_stop(int video_id);
    user_video_disp_stop(id);
#endif
#endif
}

void gui_open_local_music(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("open local music\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int local_music_mode_init(void);
    local_music_mode_init();
#endif
#endif
}

void gui_close_local_music(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("close local music\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern void local_music_mode_exit(void);
    local_music_mode_exit();
#endif
#endif
}

void gui_open_recorder(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_open_recorder\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int recorder_mode_init(void);
    recorder_mode_init();
#endif
#endif
}

void gui_close_recorder(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_close_recorder\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern void recorder_mode_exit(void);
    recorder_mode_exit();
#endif
#endif
}

void gui_play_pause_music(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_play_pause_music\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int local_music_dec_play_pause(void);
    local_music_dec_play_pause();
#endif
#endif
}

void gui_play_next_music(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_play_next_music\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int local_music_dec_switch_file(int fsel_mode);
    local_music_dec_switch_file(2);
#endif
#endif
}
void gui_play_prev_music(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_play_prev_music\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int local_music_dec_switch_file(int fsel_mode);
    local_music_dec_switch_file(3);
#endif
#endif
}


void gui_set_music_volume(int value)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_set_music_volume\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int local_music_set_dec_volume(int value);
    extern int recorder_dec_volume_change(int value);

    if (lv_obj_is_valid(guider_ui.audio_local_music)) {
        local_music_set_dec_volume(value);
    } else {
        recorder_dec_volume_change(value);
    }
    lvgl_module_msg_send_value(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME, value, 0);
#endif
#endif
}

void gui_set_recoder_volume(int value)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("gui_set_music_volume\n");
#else
#if defined CONFIG_AUDIO_ENABLE
    extern int recorder_enc_gain_change(int value);
    recorder_enc_gain_change(value);
    recorder_volume = value;
    lvgl_module_msg_send_value(GUI_RECORDER_VOLUME_MSG_ID_VOLUME, value, 0);
#endif
#endif
}

void post_msg2player_name(const char *name)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    char *play_name = lvgl_module_msg_get_ptr(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME, strlen(name) + 1);
    strcpy(play_name, name);
    lvgl_module_msg_send_ptr(play_name, 0);
#endif
}

void post_msg2player_time(int time)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    lvgl_module_msg_send_value(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME, time, 0);
#endif
}

#if !LV_USE_GUIBUILDER_SIMULATOR

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_KEY_MSG_ID_KEY_TEXT)
.onchange = gui_key_msg_key_text_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME)
.onchange = gui_local_music_volume_msg_volume_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_RECORDER_VOLUME_MSG_ID_VOLUME)
.onchange = gui_recorder_volume_msg_volume_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID)
.onchange = gui_wifi_state_label_msg_cur_ssid_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_BLUETOOTH_MSG_ID_BT_NAME)
.onchange = gui_bluetooth_msg_bt_name_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_BLUE_MSG_ID_BT_STATE)
.onchange = gui_blue_msg_bt_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_SD_CARD_MSG_ID_SDCARD)
.onchange = gui_sd_card_msg_sdcard_cb,
};

static int play_prompt(const char *prompt)
{
    struct intent it;
    struct application *app;

    init_intent(&it);
    app = get_current_app();
    if (!app) {
        printf("get_current_app fail");
        return -1;
    }

    if (strcmp(app->name, "app_music") == 0) {
        it.name = "app_music";
        it.action = ACTION_MUSIC_PLAY_VOICE_PROMPT;
        //it.data = "Volume.mp3";
        it.data = prompt;
        it.exdata = 1;
        start_app(&it);
    }
    return 0;
}

//网络事件处理
static int lvgl_net_event_handler(struct sys_event *sys_eve)
{
#if defined CONFIG_NET_ENABLE
    struct net_event *net_eve = (struct net_event *)sys_eve->payload;
    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);
    char *cur_ssid = info.ssid;

    switch (net_eve->event) {
    case NET_EVENT_CONNECTED:
        sprintf(sta_text, "WIFI Connected\n%s", cur_ssid);
        lvgl_module_msg_send_string(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, sta_text, 1);
        break;
    case NET_EVENT_DISCONNECTED:
        lvgl_module_msg_send_string(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, "WIFI Disconnect", 1);
        break;
    case NET_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        sprintf(sta_text, "WIFI Connect Timeout Not Found SSID:%s", cur_ssid);
        lvgl_module_msg_send_string(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, sta_text, 1);
        break;
    case NET_CONNECT_ASSOCIAT_FAIL:
        sprintf(sta_text, "WIFI Connect Fail\nSSID:%s", cur_ssid);
        lvgl_module_msg_send_string(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, sta_text, 1);
        break;
    case NET_CONNECT_ASSOCIAT_TIMEOUT:
        sprintf(sta_text, "WIFI Connect Timeout\nSSID:%s", cur_ssid);
        lvgl_module_msg_send_string(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, "WIFI Connect Timeout", 1);
        break;
    }
#endif
    return true;
}


//蓝牙事件处理
static int lvgl_bt_event_handler(struct sys_event *sys_eve)
{
#if defined CONFIG_BT_ENABLE
    if (sys_eve->from == BT_EVENT_FROM_CON) {
        struct bt_event *bt = (struct bt_event *)sys_eve->payload;
        switch (bt->event) {
        case BT_STATUS_START_CONNECTED:
            strcpy(bt_state, "Bluetooth\nConnecting...");
            lvgl_module_msg_send_string(GUI_BLUE_MSG_ID_BT_STATE, bt_state, 0);
            printf("--%s--BT_STATUS_START_CONNECTED\n", __FUNCTION__);
            break;

        case BT_STATUS_SECOND_CONNECTED:
        case BT_STATUS_FIRST_CONNECTED:
            strcpy(bt_state, "Bluetooth\nConnected");
            lvgl_module_msg_send_string(GUI_BLUE_MSG_ID_BT_STATE, bt_state, 0);
            printf("--%s--BT_STATUS_CONNECTED\n", __FUNCTION__);
            break;
        case BT_STATUS_FIRST_DISCONNECT:
        case BT_STATUS_SECOND_DISCONNECT:
            strcpy(bt_state, "Bluetooth\nDisconnect !!!!!!");
            lvgl_module_msg_send_string(GUI_BLUE_MSG_ID_BT_STATE, bt_state, 0);
            printf("--%s--BT_STATUS_DISCONNECT\n", __FUNCTION__);
            break;
        }
    }
//    else if (sys_eve->from == BT_EVENT_FROM_HCI) {
//        return bt_hci_event_handler((struct bt_event *)event->payload);
//    }


#endif
    return true;
}

//设备事件处理 SD卡
static int lvgl_device_event_handler(struct sys_event *sys_eve)
{
    struct device_event *device_eve = (struct device_event *)sys_eve->payload;
    if (sys_eve->from == DEVICE_EVENT_FROM_SD) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            if (lv_obj_is_valid(guider_ui.sdcard)) {
                printf("\n---%s---SD IN\n", __FUNCTION__);
                lvgl_module_msg_send_string(GUI_SD_CARD_MSG_ID_SDCARD, "SD Card Ready", 0);
            }
            break;
        case DEVICE_EVENT_OUT:
            if (lv_obj_is_valid(guider_ui.sdcard)) {
                printf("\n---%s---SD OUT\n", __FUNCTION__);
                lvgl_module_msg_send_string(GUI_SD_CARD_MSG_ID_SDCARD, "SD Card Not Found", 0);
            }
            break;
        }
    }

    return true;
}

static int get_sd_space(u32 *total_space, u32 *free_space)
{
    int err;

    err = fget_free_space(CONFIG_ROOT_PATH, free_space);
    if (err) {
        printf("fget_free_space err:%d \n", err);
        return err;
    }
    err = fget_physical_total_space(CONFIG_ROOT_PATH, total_space);
    if (err) {
        printf("fget_physical_total_space err:%d \n", err);
        return err;
    }
    printf("sd total:%d  free:%d \n", *total_space, *free_space);

    return 0;
}


static void show_sd_state(void)
{
    int err;
    u32 total, free;
    u32 bar_val;
    err = get_sd_space(&total, &free);
    if (!err) {
        char text[50];
        sprintf(text, "%dMB available,%dMB total", free / 1024, total / 1024);
        lv_label_set_text(guider_ui.sdcard_sdcard_total_label, text);
        lv_label_set_text(guider_ui.sdcard_sdcard_path_label, CONFIG_ROOT_PATH);
        lv_obj_clear_flag(guider_ui.sdcard_show_sdcard_state, LV_OBJ_FLAG_HIDDEN);

        bar_val = ((float)(total - free) / total) * 100;
        lv_bar_set_value(guider_ui.sdcard_capacity_bar, bar_val, LV_ANIM_OFF);
    } else {
        printf("get_sd_space err:%d \n", err);
        lv_obj_add_flag(guider_ui.sdcard_show_sdcard_state, LV_OBJ_FLAG_HIDDEN);
    }
}

int gui_sd_card_msg_sdcard_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int err;
    if (access == GUI_MSG_ACCESS_SET) {
        if (strcmp(data->value_string, "SD Card Ready") == 0) {
            show_sd_state();
        } else {
            lv_obj_add_flag(guider_ui.sdcard_show_sdcard_state, LV_OBJ_FLAG_HIDDEN);
        }
    }
    if (access == GUI_MSG_ACCESS_GET) {
        if (storage_device_ready()) {
            data->value_string = "SD Card Ready";
            show_sd_state();
        } else {
            data->value_string = "SD Card Not Found";
            lv_obj_add_flag(guider_ui.sdcard_show_sdcard_state, LV_OBJ_FLAG_HIDDEN);
        }

    }
    return 0;
}


int gui_key_msg_key_text_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char *key_text_init_var = "Please press the key";
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_string = key_text_init_var;
    }
    if (access == GUI_MSG_ACCESS_SET) {

    }
    return 0;
}


int gui_local_music_volume_msg_volume_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int32_t volume_var = 50;

    if (access == GUI_MSG_ACCESS_SET) {
        volume_var = data->value_int;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        if (syscfg_read(83, &volume_var, 1) < 0) {
            volume_var = 50;
        }
    }
    data->value_int = volume_var;
}



int gui_recorder_volume_msg_volume_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int32_t volume_var = 50;

    if (access == GUI_MSG_ACCESS_SET) {
        volume_var = data->value_int;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        volume_var = recorder_volume;
    }
    data->value_int = volume_var;
}


int gui_wifi_state_label_msg_cur_ssid_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if defined CONFIG_NET_ENABLE
    if (access == GUI_MSG_ACCESS_GET) {
        enum wifi_sta_connect_state sta = wifi_get_sta_connect_state();
        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        switch (sta) {
        case WIFI_STA_DISCONNECT:
            data->value_string = "WIFI Disconnect";
            break;
        case WIFI_STA_CONNECT_SUCC:
            sprintf(sta_text, "WIFI Connected\n%s", info.ssid);
            data->value_string = sta_text;
            break;
        default:
            break;
        }

    }

#endif
}

int gui_bluetooth_msg_bt_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if defined CONFIG_BT_ENABLE
    if (access == GUI_MSG_ACCESS_GET) {
        extern const char *bt_get_local_name(void);
        sprintf(bt_name, "Bluetooth Name:\n%s", bt_get_local_name());
        data->value_string = bt_name;
    }
    if (access == GUI_MSG_ACCESS_SET) {

    }
#endif
    return 0;
}

int gui_blue_msg_bt_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if defined CONFIG_BT_ENABLE
    if (access == GUI_MSG_ACCESS_SET) {
        data->value_string = bt_state;
    }

    if (access == GUI_MSG_ACCESS_GET) {
        data->value_string = bt_state;
    }
#endif
    return 0;
}


#endif

#if DEV_HARDWARE_VERIFY_UI_ENABLE

static int key_handler(struct key_event *key)
{
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_POWER:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY1 down", 1);
            break;
        case KEY_MODE:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY2 down", 1);
            break;
        case KEY_UP:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY3 down", 1);
            break;
        case KEY_DOWN:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY4 down", 1);
            break;
        case KEY_OK:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY5 down", 1);
            break;
        default:
            break;
        }
        break;
    case KEY_EVENT_LONG:
        switch (key->value) {
        case KEY_POWER:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY1 long down", 1);
            break;
        case KEY_MODE:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY2 long down", 1);
            break;
        case KEY_UP:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY3 long down", 1);
            break;
        case KEY_DOWN:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY4 long down", 1);
            break;
        case KEY_OK:
            play_prompt("ring.mp3");
            lvgl_module_msg_send_string(GUI_KEY_MSG_ID_KEY_TEXT, "KEY5 long down", 1);
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

REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_KEY)
.key_onchange = key_handler,
};

void lvgl_key_value_remap(u8 key_value, uint32_t *key_remap)
{
    switch (key_value) {
    case KEY_POWER:
        *key_remap = LV_KEY_HOME;
        break;
    case KEY_MODE:
        *key_remap = LV_KEY_HOME;
        break;
    case KEY_UP:
        *key_remap = LV_KEY_HOME;
        break;
    case KEY_DOWN:
        *key_remap = LV_KEY_HOME;
        break;
    default:
        *key_remap = LV_KEY_HOME;
        break;
    }

}

//返回1时，则将按键信息交给app core处理
int ui_scr_key_event_handler_ext(struct key_event *event)
{
#if DEV_HARDWARE_VERIFY_UI_ENABLE
    if (event->value == KEY_ENC) {
        struct intent it;
        init_intent(&it);
        it.name = "app_music";
        it.action = ACTION_MUSIC_PLAY_VOICE_PROMPT;
        it.data = "AiSpeaker.mp3";
        it.exdata = 1;
        start_app(&it);
    }
    return 0;
#else
    return 1;
#endif
}

SYS_EVENT_STATIC_HANDLER_REGISTER(static_lvgl_device_event_handler, 0) = {
    .event_type = SYS_DEVICE_EVENT,
    .prob_handler = lvgl_device_event_handler,
    .post_handler = NULL,
};
SYS_EVENT_STATIC_HANDLER_REGISTER(static_lvgl_bt_event_handler, 0) = {
    .event_type  = SYS_BT_EVENT,
    .prob_handler = lvgl_bt_event_handler,
    .post_handler  = NULL,
};
SYS_EVENT_STATIC_HANDLER_REGISTER(static_lvgl_net_event_handler, 0) = {
    .event_type  = SYS_NET_EVENT,
    .prob_handler  = lvgl_net_event_handler,
    .post_handler = NULL,
};

#endif

void custom_init(lv_ui *ui)
{

}

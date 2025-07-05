#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR

void post_stream_msg_to_ui(const char *msg, int arg)
{
    static u8 switch_prev_state = 0;

    if (!strcmp(msg, "show switch btn")) {
        if (switch_prev_state != 1) {
            printf("ui show switch btn\n");
            lvgl_module_msg_send_value(GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, 1, 0);
        }
        switch_prev_state = 1;
    } else if (!strcmp(msg, "hide switch btn")) {
        if (switch_prev_state != 0) {
            printf("ui hide switch btn\n");
            lvgl_module_msg_send_value(GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, 0, 0);
        }
        switch_prev_state = 0;
    } else if (!strcmp(msg, "show stream info")) {
        char *text = (char *)arg;
        char *lab = lvgl_module_msg_get_ptr(GUI_RT_STREAM_MSG_ID_STREAM_INFO, strlen(text) + 1);
        strcpy(lab, text);
        lvgl_module_msg_send_ptr(lab, 0);
    } else {
        printf("Unknow Msg\n");
    }
}

#endif

int gui_bbm_switch_camera(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_SWITCH_WIN;
    start_app(&it);
#endif

    return 0;
}

int gui_bbm_start_stream(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_START_RT;
    start_app(&it);
#endif

    return 0;
}

int gui_bbm_stop_stream(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_STOP_RT;
    start_app(&it);
#endif

    return 0;
}


#if !LV_USE_GUIBUILDER_SIMULATOR
static int gui_src_action_wifi_bbm(int action)
{
    struct intent it;
    struct application *app;

    init_intent(&it);
    app = get_current_app();

    printf("[chili] %s %d   \n", __func__, __LINE__);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(guider_ui.rt_stream->rt_stream, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(guider_ui.rt_stream->rt_stream, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        gui_bbm_start_stream();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_RT_STREAM)
.onchange = gui_src_action_wifi_bbm,
};

//开发板的KEY4 / KEY5 不映射LVGL. 按键事件发给app_core.
static int bbm_rt_stream_key_handler(struct key_event *key)
{
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_DOWN:
            //key4
            return 1;
            break;
        case KEY_OK:
            //key5
            return 1;
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
REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_RT_STREAM)
.key_onchange = bbm_rt_stream_key_handler,
};
#endif





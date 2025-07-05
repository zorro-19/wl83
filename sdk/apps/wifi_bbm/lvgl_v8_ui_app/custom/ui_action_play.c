#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif
static int cur_play_index = 0;
static char full_path[128];

#if !LV_USE_GUIBUILDER_SIMULATOR

void post_video_play_msg_to_ui(const char *msg, int arg)
{
    if (!strcmp(msg, "play_time")) {
        int percent = arg;
        lvgl_module_msg_send_value(GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR, percent, 0);
    } else if (!strcmp(msg, "play_control")) {
        //0:暂停图标 1:播放图标
        lvgl_module_msg_send_value(GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL, arg, 1);

    } else {
        printf("Unknow Msg\n");
    }
}

void gui_bbm_set_cur_play_index(int index)
{
    cur_play_index = index;
}

int gui_bbm_play_file_start(void)
{
    int ret;
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_START;
    sprintf(full_path, "%s%d/%s", gui_bbm_get_cur_dev_path(), gui_bbm_get_cur_dir_ch());
    it.data = full_path;
    it.exdata = cur_play_index;
    ret = start_app(&it);

    if (ret) {
        char *lab = "File Error !";
        post_home_msg_to_ui("show_sys_prompt", lab);
    }

    return 0;
}

int gui_bbm_play_file_stop(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_STOP;
    it.data = full_path;
    start_app(&it);

    return 0;
}

int gui_bbm_play_file_control(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_SWITCH;
    it.data = full_path;
    it.exdata = cur_play_index;
    start_app(&it);

    return 0;
}

int gui_bbm_play_file_next(void)
{
    int file_total_num;

    gui_bbm_get_file_num(&file_total_num);

    gui_bbm_play_file_stop();

    cur_play_index = (cur_play_index + 1) % file_total_num;

    gui_bbm_play_file_start();

    return 0;
}

int gui_bbm_play_file_prev(void)
{
    int file_total_num;

    gui_bbm_get_file_num(&file_total_num);

    gui_bbm_play_file_stop();

    cur_play_index = (cur_play_index - 1 + file_total_num) % file_total_num;

    gui_bbm_play_file_start();

    return 0;
}

static int gui_src_action_play(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(guider_ui.video_play->video_play, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(guider_ui.video_play->video_play, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        gui_bbm_play_file_start();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_PLAY)
.onchange = gui_src_action_play,
};


int gui_video_play_msg_progress_bar_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = 0;
    }
    return 0;
}
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR)
.onchange = gui_video_play_msg_progress_bar_cb,
};

#endif




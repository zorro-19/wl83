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

static void (*global_yes_options_callback)(void) = NULL;
static void (*global_no_options_callback)(void) = NULL;
static lv_group_t *top_level_group;

void gui_load_home_page(void)
{
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_HOME);
    ui_load_scr_anim(&guider_ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
}

void gui_load_dev_sel_page(void)
{
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_DEVICE_SELECT);
    ui_load_scr_anim(&guider_ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
}

void gui_load_folder_sel_page(void)
{
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_DIR_SELECT);
    ui_load_scr_anim(&guider_ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
}


void gui_show_sys_prompt(void)
{
    lv_ui_sys_prompt *_ui_sys_prompt = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
    if (_ui_sys_prompt && _ui_sys_prompt->sys_prompt_del == false && lv_obj_is_valid(_ui_sys_prompt->sys_prompt)) {
        lv_obj_clear_flag(_ui_sys_prompt->sys_prompt, LV_OBJ_FLAG_HIDDEN);
    } else {
        setup_scr_sys_prompt(&guider_ui);
    }
}

void gui_show_sys_options(void)
{
    lv_ui_sys_options *_ui_sys_options = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_OPTIONS);
    if (_ui_sys_options && _ui_sys_options->sys_options_del == false && lv_obj_is_valid(_ui_sys_options->sys_options)) {
        lv_obj_clear_flag(_ui_sys_options->sys_options, LV_OBJ_FLAG_HIDDEN);
    } else {
        setup_scr_sys_options(&guider_ui);
    }

    //按键导航
    top_level_group = lv_group_create();
    if (top_level_group) {
        lv_ui_sys_options *_ui_sys_options = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_OPTIONS);
        if (_ui_sys_options) {
            lv_group_add_obj(top_level_group, _ui_sys_options->sys_options_btn_1);
            lv_group_add_obj(top_level_group, _ui_sys_options->sys_options_btn_2);
        }
        lv_indev_t *indev = lv_indev_get_next(NULL);
        if (indev != NULL) {
            lv_indev_set_group(indev, top_level_group);
        }
    }
}

void gui_hide_sys_options(void)
{
    lv_ui_sys_options *_ui_sys_options = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_OPTIONS);
    if (_ui_sys_options && _ui_sys_options->sys_options_del == false && lv_obj_is_valid(_ui_sys_options->sys_options)) {
        lv_obj_add_flag(_ui_sys_options->sys_options, LV_OBJ_FLAG_HIDDEN);
        lv_indev_t *indev = lv_indev_get_next(NULL);
        if (indev != NULL) {
            lv_indev_set_group(indev, lv_group_get_default());
        }

        if (top_level_group) {
            lv_group_del(top_level_group);
            top_level_group = NULL;
        }

    }
}



void gui_hide_sys_prompt(void)
{
    lv_ui_sys_prompt *_ui_sys_prompt = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
    if (_ui_sys_prompt && lv_obj_is_valid(_ui_sys_prompt->sys_prompt)) {
        lv_obj_add_flag(_ui_sys_prompt->sys_prompt, LV_OBJ_FLAG_HIDDEN);
    }
}

void gui_set_sys_prompt_lab(char *text)
{
    char *lab = lvgl_module_msg_get_ptr(GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB, strlen(text) + 1);
    strcpy(lab, text);
    lvgl_module_msg_send_ptr(lab, 0);
}

void gui_set_sys_options_lab(char *text)
{
    char *lab = lvgl_module_msg_get_ptr(GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB, strlen(text) + 1);
    strcpy(lab, text);
    lvgl_module_msg_send_ptr(lab, 0);
}

void gui_set_sys_options_yes_cb(void (*cb)(void))
{
    global_yes_options_callback = cb;

}

void gui_set_sys_options_no_cb(void (*cb)(void))
{
    global_no_options_callback = cb;

}

void gui_sys_options_run_yes_cb(void)
{
    if (global_yes_options_callback) {
        global_yes_options_callback();
        global_yes_options_callback = NULL;
    }

    lv_indev_t *indev = lv_indev_get_next(NULL);
    if (indev != NULL) {
        lv_indev_set_group(indev, lv_group_get_default());
    }

    if (top_level_group) {
        lv_group_del(top_level_group);
        top_level_group = NULL;
    }
}

void gui_sys_options_run_no_cb(void)
{
    if (global_no_options_callback) {
        global_no_options_callback();
        global_no_options_callback = NULL;
    }

    lv_indev_t *indev = lv_indev_get_next(NULL);
    if (indev != NULL) {
        lv_indev_set_group(indev, lv_group_get_default());
    }

    if (top_level_group) {
        lv_group_del(top_level_group);
        top_level_group = NULL;
    }
}

void post_home_msg_to_ui(const char *msg, int arg)
{
    if (!strcmp(msg, "back_home_page")) {
        lvgl_rpc_post_func(gui_load_home_page, 0);
    } else if (!strcmp(msg, "back_folder_sel_page")) {
        lvgl_rpc_post_func(gui_load_folder_sel_page, 0);
    } else if (!strcmp(msg, "back_dev_sel_page")) {
        lvgl_rpc_post_func(gui_load_dev_sel_page, 0);
    } else if (!strcmp(msg, "show_sys_prompt")) {
        char *text = (char *)arg;
        gui_set_sys_prompt_lab(text);
        lvgl_rpc_post_func(gui_show_sys_prompt, 0);
        lvgl_rpc_post_func(gui_hide_sys_options, 0);
    } else if (!strcmp(msg, "show_sys_options")) {
        char *text = (char *)arg;
        gui_set_sys_options_lab(text);
        lvgl_rpc_post_func(gui_show_sys_options, 0);
    } else {
        printf("Unknow Msg\n");
    }
}

static int gui_src_action_home(int action)
{
    struct intent it;
    struct application *app;

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        //TODO
        gui_bbm_file_reset_to_play_page();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_HOME)
.onchange = gui_src_action_home,
};
#endif





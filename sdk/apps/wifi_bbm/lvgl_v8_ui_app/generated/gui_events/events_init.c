/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"


void events_init(lv_ui *ui)
{
}

static void home_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_RT_STREAM);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void home_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_STATUS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void home_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_DEVICE_SELECT);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}
static void home_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_HOME, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_HOME, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_home(lv_ui *ui)
{
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    lv_obj_add_event_cb(ui_scr->home_imgbtn_2, home_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->home_imgbtn_1, home_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->home_imgbtn_3, home_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->home, home_screen_event_handler, LV_EVENT_ALL, ui);
}

static void pair_status_imglist_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void set_cur_pair_channel(uint8_t channel);
            set_cur_pair_channel(0);
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_status_imglist_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void set_cur_pair_channel(uint8_t channel);
            set_cur_pair_channel(1);
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_status_imglist_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void set_cur_pair_channel(uint8_t channel);
            set_cur_pair_channel(2);
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_status_imglist_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void set_cur_pair_channel(uint8_t channel);
            set_cur_pair_channel(3);
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_status_imglist_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void set_cur_pair_channel(uint8_t channel);
            set_cur_pair_channel(4);
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_status_imglist_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void set_cur_pair_channel(uint8_t channel);
            set_cur_pair_channel(5);
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_status_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_pair_status(lv_ui *ui)
{
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    lv_obj_add_event_cb(ui_scr->pair_status_imglist_1, pair_status_imglist_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_status_imglist_2, pair_status_imglist_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_status_imglist_3, pair_status_imglist_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_status_imglist_4, pair_status_imglist_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_status_imglist_5, pair_status_imglist_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_status_imglist_6, pair_status_imglist_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_status_imgbtn_1, pair_status_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void rt_stream_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_rt_stream *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RT_STREAM);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void rt_stream_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_rt_stream *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RT_STREAM);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern int gui_bbm_switch_camera(void);
            gui_bbm_switch_camera();
        }
    }
    break;
    default:
        break;
    }
}
static void rt_stream_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_RT_STREAM, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_RT_STREAM, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_rt_stream(lv_ui *ui)
{
    lv_ui_rt_stream *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RT_STREAM);
    lv_obj_add_event_cb(ui_scr->rt_stream, rt_stream_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->rt_stream_imgbtn_1, rt_stream_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->rt_stream, rt_stream_screen_event_handler, LV_EVENT_ALL, ui);
}

static void file_browser_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_DIR_SELECT);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_prev_page(void);
            gui_bbm_prev_page();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_next_page(void);
            gui_bbm_next_page();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_imgbtn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR

            extern int gui_bbm_file_del(void);
            gui_bbm_file_del();

#endif


        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_file_cont1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_file_to_play(int index);
            gui_bbm_file_to_play(0);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PLAY);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_cb_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (code == LV_EVENT_VALUE_CHANGED) {
                // 判断复选框是否被选中
                if (lv_obj_has_state(src, LV_STATE_CHECKED)) {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_add_del_file(int index);
                    gui_bbm_add_del_file(0);
#endif
                } else {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_remove_del_file(int index);
                    gui_bbm_remove_del_file(0);
#endif
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_file_cont2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_file_to_play(int index);
            gui_bbm_file_to_play(1);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PLAY);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_cb_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (code == LV_EVENT_VALUE_CHANGED) {
                // 判断复选框是否被选中
                if (lv_obj_has_state(src, LV_STATE_CHECKED)) {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_add_del_file(int index);
                    gui_bbm_add_del_file(1);
#endif
                } else {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_remove_del_file(int index);
                    gui_bbm_remove_del_file(1);
#endif
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_file_cont3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_file_to_play(int index);
            gui_bbm_file_to_play(2);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PLAY);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_cb_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (code == LV_EVENT_VALUE_CHANGED) {
                // 判断复选框是否被选中
                if (lv_obj_has_state(src, LV_STATE_CHECKED)) {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_add_del_file(int index);
                    gui_bbm_add_del_file(2);
#endif
                } else {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_remove_del_file(int index);
                    gui_bbm_remove_del_file(2);
#endif
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_file_cont4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_file_to_play(int index);
            gui_bbm_file_to_play(3);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PLAY);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_cb_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (code == LV_EVENT_VALUE_CHANGED) {
                // 判断复选框是否被选中
                if (lv_obj_has_state(src, LV_STATE_CHECKED)) {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_add_del_file(int index);
                    gui_bbm_add_del_file(3);
#endif
                } else {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_remove_del_file(int index);
                    gui_bbm_remove_del_file(3);
#endif
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_file_cont5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_file_to_play(int index);
            gui_bbm_file_to_play(4);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PLAY);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_cb_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (code == LV_EVENT_VALUE_CHANGED) {
                // 判断复选框是否被选中
                if (lv_obj_has_state(src, LV_STATE_CHECKED)) {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_add_del_file(int index);
                    gui_bbm_add_del_file(4);
#endif
                } else {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_remove_del_file(int index);
                    gui_bbm_remove_del_file(4);
#endif
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_file_cont6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_file_to_play(int index);
            gui_bbm_file_to_play(5);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_PLAY);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void file_browser_cb_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (code == LV_EVENT_VALUE_CHANGED) {
                // 判断复选框是否被选中
                if (lv_obj_has_state(src, LV_STATE_CHECKED)) {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_add_del_file(int index);
                    gui_bbm_add_del_file(5);
#endif
                } else {
#if !LV_USE_GUIBUILDER_SIMULATOR
                    extern void gui_bbm_remove_del_file(int index);
                    gui_bbm_remove_del_file(5);
#endif
                }
            }
        }
    }
    break;
    default:
        break;
    }
}
static void file_browser_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_FILE_BROWSER, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_FILE_BROWSER, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_file_browser(lv_ui *ui)
{
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    lv_obj_add_event_cb(ui_scr->file_browser_imgbtn_1, file_browser_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_imgbtn_2, file_browser_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_imgbtn_3, file_browser_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_imgbtn_4, file_browser_imgbtn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_file_cont1, file_browser_file_cont1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_cb_1, file_browser_cb_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_file_cont2, file_browser_file_cont2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_cb_2, file_browser_cb_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_file_cont3, file_browser_file_cont3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_cb_3, file_browser_cb_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_file_cont4, file_browser_file_cont4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_cb_4, file_browser_cb_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_file_cont5, file_browser_file_cont5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_cb_5, file_browser_cb_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_file_cont6, file_browser_file_cont6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser_cb_6, file_browser_cb_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->file_browser, file_browser_screen_event_handler, LV_EVENT_ALL, ui);
}

static void pair_options_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_OPTIONS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIRING);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_options_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_OPTIONS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_UNPAIR);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void pair_options_imgbtn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pair_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_OPTIONS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_STATUS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_pair_options(lv_ui *ui)
{
    lv_ui_pair_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_OPTIONS);
    lv_obj_add_event_cb(ui_scr->pair_options_imgbtn_1, pair_options_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_options_imgbtn_2, pair_options_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->pair_options_imgbtn_4, pair_options_imgbtn_4_event_handler, LV_EVENT_ALL, ui);
}

static void pairing_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_pairing *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIRING);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern int gui_set_bbm_exit_pairing(void);
            gui_set_bbm_exit_pairing();
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_pairing(lv_ui *ui)
{
    lv_ui_pairing *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIRING);
    lv_obj_add_event_cb(ui_scr->pairing, pairing_event_handler, LV_EVENT_ALL, ui);
}

static void unpair_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_unpair *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_UNPAIR);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_PAIR_OPTIONS);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_unpair(lv_ui *ui)
{
    lv_ui_unpair *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_UNPAIR);
    lv_obj_add_event_cb(ui_scr->unpair, unpair_event_handler, LV_EVENT_ALL, ui);
}

static void video_play_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_imglist_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_play_file_control(void);
            gui_bbm_play_file_control();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_play_file_next(void);
            gui_bbm_play_file_next();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void video_play_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            int gui_bbm_play_file_prev(void);
            gui_bbm_play_file_prev();
#endif
        }
    }
    break;
    default:
        break;
    }
}
static void video_play_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_PLAY, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_PLAY, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_play(lv_ui *ui)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_1, video_play_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imglist_1, video_play_imglist_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_3, video_play_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play_imgbtn_2, video_play_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->video_play, video_play_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_prompt_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_ui_sys_prompt *_ui_sys_prompt = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
        if (_ui_sys_prompt && _ui_sys_prompt->sys_prompt_del == false && lv_obj_is_valid(_ui_sys_prompt->sys_prompt)) {
            lv_obj_add_flag(_ui_sys_prompt->sys_prompt, LV_OBJ_FLAG_HIDDEN);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_sys_prompt(lv_ui *ui)
{
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
    lv_obj_add_event_cb(ui_scr->sys_prompt, sys_prompt_event_handler, LV_EVENT_ALL, ui);
}

static void dir_select_view_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            lv_obj_t *lab = lv_obj_get_child(guider_ui.dir_select->dir_select_view_1, 1);
            const char *text = lv_label_get_text(lab);
            while (*text && !isdigit(*text)) {  // 跳过非数字字符
                text++;
            }

            int ch = atoi(text);
            void gui_bbm_set_cur_dir_ch(int ch);
            gui_bbm_set_cur_dir_ch(ch);
#endif

        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void dir_select_view_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            lv_obj_t *lab = lv_obj_get_child(guider_ui.dir_select->dir_select_view_2, 1);
            const char *text = lv_label_get_text(lab);
            while (*text && !isdigit(*text)) {  // 跳过非数字字符
                text++;
            }

            int ch = atoi(text);
            void gui_bbm_set_cur_dir_ch(int ch);
            gui_bbm_set_cur_dir_ch(ch);
#endif

        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void dir_select_view_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            lv_obj_t *lab = lv_obj_get_child(guider_ui.dir_select->dir_select_view_3, 1);
            const char *text = lv_label_get_text(lab);
            while (*text && !isdigit(*text)) {  // 跳过非数字字符
                text++;
            }

            int ch = atoi(text);
            void gui_bbm_set_cur_dir_ch(int ch);
            gui_bbm_set_cur_dir_ch(ch);
#endif

        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void dir_select_view_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            lv_obj_t *lab = lv_obj_get_child(guider_ui.dir_select->dir_select_view_4, 1);
            const char *text = lv_label_get_text(lab);
            while (*text && !isdigit(*text)) {  // 跳过非数字字符
                text++;
            }

            int ch = atoi(text);
            void gui_bbm_set_cur_dir_ch(int ch);
            gui_bbm_set_cur_dir_ch(ch);
#endif

        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void dir_select_view_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            lv_obj_t *lab = lv_obj_get_child(guider_ui.dir_select->dir_select_view_5, 1);
            const char *text = lv_label_get_text(lab);
            while (*text && !isdigit(*text)) {  // 跳过非数字字符
                text++;
            }

            int ch = atoi(text);
            void gui_bbm_set_cur_dir_ch(int ch);
            gui_bbm_set_cur_dir_ch(ch);
#endif

        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void dir_select_view_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            lv_obj_t *lab = lv_obj_get_child(guider_ui.dir_select->dir_select_view_6, 1);
            const char *text = lv_label_get_text(lab);
            while (*text && !isdigit(*text)) {  // 跳过非数字字符
                text++;
            }

            int ch = atoi(text);
            void gui_bbm_set_cur_dir_ch(int ch);
            gui_bbm_set_cur_dir_ch(ch);
#endif

        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_FILE_BROWSER);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void dir_select_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_DEVICE_SELECT);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}
static void dir_select_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_DIR_SELECT, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_DIR_SELECT, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_dir_select(lv_ui *ui)
{
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    lv_obj_add_event_cb(ui_scr->dir_select_view_1, dir_select_view_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select_view_2, dir_select_view_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select_view_3, dir_select_view_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select_view_4, dir_select_view_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select_view_5, dir_select_view_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select_view_6, dir_select_view_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select_imgbtn_1, dir_select_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->dir_select, dir_select_screen_event_handler, LV_EVENT_ALL, ui);
}

static void device_select_view_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_device_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DEVICE_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            void gui_bbm_set_cur_dev_path(int dev);
            gui_bbm_set_cur_dev_path(0);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_DIR_SELECT);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void device_select_view_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_device_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DEVICE_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if !LV_USE_GUIBUILDER_SIMULATOR
            void gui_bbm_set_cur_dev_path(int dev);
            gui_bbm_set_cur_dev_path(1);
#endif
        }
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_DIR_SELECT);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void device_select_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_device_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DEVICE_SELECT);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME);
        if (screen != NULL) {
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}
static void device_select_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_DEVICE_SELECT, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_DEVICE_SELECT, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_device_select(lv_ui *ui)
{
    lv_ui_device_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DEVICE_SELECT);
    lv_obj_add_event_cb(ui_scr->device_select_view_1, device_select_view_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->device_select_view_2, device_select_view_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->device_select_imgbtn_1, device_select_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->device_select, device_select_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_options_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_ui_sys_options *_ui_sys_options = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
        if (_ui_sys_options && _ui_sys_options->sys_options_del == false && lv_obj_is_valid(_ui_sys_options->sys_options)) {
            lv_obj_add_flag(_ui_sys_options->sys_options, LV_OBJ_FLAG_HIDDEN);
        }
        //custom code sys_options
        {
            lv_ui_sys_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
            lv_obj_t *dest = ui_scr->sys_options;
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern void gui_sys_options_run_yes_cb(void);
            gui_sys_options_run_yes_cb();
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void sys_options_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_ui_sys_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        lv_ui_sys_options *_ui_sys_options = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
        if (_ui_sys_options && _ui_sys_options->sys_options_del == false && lv_obj_is_valid(_ui_sys_options->sys_options)) {
            lv_obj_add_flag(_ui_sys_options->sys_options, LV_OBJ_FLAG_HIDDEN);
        }
        //custom code sys_options
        {
            lv_ui_sys_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
            lv_obj_t *dest = ui_scr->sys_options;
#if !LV_USE_GUIBUILDER_SIMULATOR
            extern void gui_sys_options_run_no_cb(void);
            gui_sys_options_run_no_cb();
#endif
        }
    }
    break;
    default:
        break;
    }
}

void events_init_sys_options(lv_ui *ui)
{
    lv_ui_sys_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
    lv_obj_add_event_cb(ui_scr->sys_options_btn_1, sys_options_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_options_btn_2, sys_options_btn_2_event_handler, LV_EVENT_ALL, ui);
}

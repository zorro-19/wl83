/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_guider.h"
#include "./gui_timelines/gui_timelines.h"
#include "./gui_group/gui_group.h"
#include "./gui_events/events_init.h"

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck)
{
    if (screen == NULL) {
        return;
    }

    gui_scr_t *act_screen = gui_scr_get_act();
    if (act_screen == screen) {
        return;
    }

    gui_timelines_delete();
    gui_scr_set_act_anim(screen, ui, anim_type, time, delay, is_clean, auto_del);

    if (act_screen != NULL && gui_scr_get_act() == screen) {
        gui_msg_init_ui();
        gui_msg_init_events();

        if (is_push_satck) {
            gui_scr_stack_push(act_screen);
        }
    }
}

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck)
{
    gui_scr_t *screen = gui_scr_stack_pop();
    if (screen == NULL) {
        return;
    }

    ui_load_scr_anim(ui, screen, anim_type, time, delay, is_clean, auto_del, is_push_satck);
}

gui_scr_t *ui_get_scr(int32_t scr_id)
{
    gui_scr_t *screen = gui_scr_get(scr_id);
    if (screen != NULL) {
        return screen;
    }

    if (scr_id == GUI_SCREEN_HOME) {
        return gui_scr_create(GUI_SCREEN_HOME, "home", NULL, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
    }
    if (scr_id == GUI_SCREEN_PAIR_STATUS) {
        return gui_scr_create(GUI_SCREEN_PAIR_STATUS, "pair_status", NULL, (gui_scr_setup_cb_t)setup_scr_pair_status, (gui_scr_unload_cb_t)unload_scr_pair_status);
    }
    if (scr_id == GUI_SCREEN_RT_STREAM) {
        return gui_scr_create(GUI_SCREEN_RT_STREAM, "rt_stream", NULL, (gui_scr_setup_cb_t)setup_scr_rt_stream, (gui_scr_unload_cb_t)unload_scr_rt_stream);
    }
    if (scr_id == GUI_SCREEN_FILE_BROWSER) {
        return gui_scr_create(GUI_SCREEN_FILE_BROWSER, "file_browser", NULL, (gui_scr_setup_cb_t)setup_scr_file_browser, (gui_scr_unload_cb_t)unload_scr_file_browser);
    }
    if (scr_id == GUI_SCREEN_PAIR_OPTIONS) {
        return gui_scr_create(GUI_SCREEN_PAIR_OPTIONS, "pair_options", NULL, (gui_scr_setup_cb_t)setup_scr_pair_options, (gui_scr_unload_cb_t)unload_scr_pair_options);
    }
    if (scr_id == GUI_SCREEN_PAIRING) {
        return gui_scr_create(GUI_SCREEN_PAIRING, "pairing", NULL, (gui_scr_setup_cb_t)setup_scr_pairing, (gui_scr_unload_cb_t)unload_scr_pairing);
    }
    if (scr_id == GUI_SCREEN_UNPAIR) {
        return gui_scr_create(GUI_SCREEN_UNPAIR, "unpair", NULL, (gui_scr_setup_cb_t)setup_scr_unpair, (gui_scr_unload_cb_t)unload_scr_unpair);
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        return gui_scr_create(GUI_SCREEN_VIDEO_PLAY, "video_play", NULL, (gui_scr_setup_cb_t)setup_scr_video_play, (gui_scr_unload_cb_t)unload_scr_video_play);
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        return gui_scr_create(GUI_SCREEN_SYS_PROMPT, "sys_prompt", NULL, (gui_scr_setup_cb_t)setup_scr_sys_prompt, (gui_scr_unload_cb_t)unload_scr_sys_prompt);
    }
    if (scr_id == GUI_SCREEN_DIR_SELECT) {
        return gui_scr_create(GUI_SCREEN_DIR_SELECT, "dir_select", NULL, (gui_scr_setup_cb_t)setup_scr_dir_select, (gui_scr_unload_cb_t)unload_scr_dir_select);
    }
    if (scr_id == GUI_SCREEN_DEVICE_SELECT) {
        return gui_scr_create(GUI_SCREEN_DEVICE_SELECT, "device_select", NULL, (gui_scr_setup_cb_t)setup_scr_device_select, (gui_scr_unload_cb_t)unload_scr_device_select);
    }
    if (scr_id == GUI_SCREEN_SYS_OPTIONS) {
        return gui_scr_create(GUI_SCREEN_SYS_OPTIONS, "sys_options", NULL, (gui_scr_setup_cb_t)setup_scr_sys_options, (gui_scr_unload_cb_t)unload_scr_sys_options);
    }
    return NULL;
}

gui_scr_t *ui_get_setup_scr(int32_t scr_id)
{
    gui_scr_t *screen = ui_get_scr(scr_id);
    if (screen == NULL) {
        return NULL;
    }

    if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
        if (screen->setup_cb != NULL) {
            screen->scr = screen->setup_cb(&guider_ui);
            screen->is_del = false;
            if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
                screen->is_del = true;
                return NULL;
            }
        }
    }
    return screen;
}


void *ui_get_scr_ptr(lv_ui *ui, int32_t scr_id)
{
    if (ui == NULL) {
        return NULL;
    }

    if (scr_id == GUI_SCREEN_HOME) {
        return ui->home;
    }
    if (scr_id == GUI_SCREEN_PAIR_STATUS) {
        return ui->pair_status;
    }
    if (scr_id == GUI_SCREEN_RT_STREAM) {
        return ui->rt_stream;
    }
    if (scr_id == GUI_SCREEN_FILE_BROWSER) {
        return ui->file_browser;
    }
    if (scr_id == GUI_SCREEN_PAIR_OPTIONS) {
        return ui->pair_options;
    }
    if (scr_id == GUI_SCREEN_PAIRING) {
        return ui->pairing;
    }
    if (scr_id == GUI_SCREEN_UNPAIR) {
        return ui->unpair;
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        return ui->video_play;
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        return ui->sys_prompt;
    }
    if (scr_id == GUI_SCREEN_DIR_SELECT) {
        return ui->dir_select;
    }
    if (scr_id == GUI_SCREEN_DEVICE_SELECT) {
        return ui->device_select;
    }
    if (scr_id == GUI_SCREEN_SYS_OPTIONS) {
        return ui->sys_options;
    }
    return NULL;
}

void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id)
{
    if (ui == NULL) {
        return;
    }

    if (scr_id == GUI_SCREEN_HOME) {
        if (ui->home != NULL) {
            lv_mem_free(ui->home);
        }
        ui->home = NULL;
    }
    if (scr_id == GUI_SCREEN_PAIR_STATUS) {
        if (ui->pair_status != NULL) {
            lv_mem_free(ui->pair_status);
        }
        ui->pair_status = NULL;
    }
    if (scr_id == GUI_SCREEN_RT_STREAM) {
        if (ui->rt_stream != NULL) {
            lv_mem_free(ui->rt_stream);
        }
        ui->rt_stream = NULL;
    }
    if (scr_id == GUI_SCREEN_FILE_BROWSER) {
        if (ui->file_browser != NULL) {
            lv_mem_free(ui->file_browser);
        }
        ui->file_browser = NULL;
    }
    if (scr_id == GUI_SCREEN_PAIR_OPTIONS) {
        if (ui->pair_options != NULL) {
            lv_mem_free(ui->pair_options);
        }
        ui->pair_options = NULL;
    }
    if (scr_id == GUI_SCREEN_PAIRING) {
        if (ui->pairing != NULL) {
            lv_mem_free(ui->pairing);
        }
        ui->pairing = NULL;
    }
    if (scr_id == GUI_SCREEN_UNPAIR) {
        if (ui->unpair != NULL) {
            lv_mem_free(ui->unpair);
        }
        ui->unpair = NULL;
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        if (ui->video_play != NULL) {
            lv_mem_free(ui->video_play);
        }
        ui->video_play = NULL;
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        if (ui->sys_prompt != NULL) {
            lv_mem_free(ui->sys_prompt);
        }
        ui->sys_prompt = NULL;
    }
    if (scr_id == GUI_SCREEN_DIR_SELECT) {
        if (ui->dir_select != NULL) {
            lv_mem_free(ui->dir_select);
        }
        ui->dir_select = NULL;
    }
    if (scr_id == GUI_SCREEN_DEVICE_SELECT) {
        if (ui->device_select != NULL) {
            lv_mem_free(ui->device_select);
        }
        ui->device_select = NULL;
    }
    if (scr_id == GUI_SCREEN_SYS_OPTIONS) {
        if (ui->sys_options != NULL) {
            lv_mem_free(ui->sys_options);
        }
        ui->sys_options = NULL;
    }
}

void ui_init_style(lv_style_t *style)
{
    if (style->prop_cnt > 1) {
        lv_style_reset(style);
    } else {
        lv_style_init(style);
    }
}


void setup_ui(lv_ui *ui)
{
    init_gui_fonts();
    ui_style_init();
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_RT_STREAM);
    ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
    events_init(ui);
    gui_group_init();
    ui_scr_manager_init();
#if LV_USE_MSG
    gui_msg_init(ui);
#endif
    gui_timelines_init(ui);
}

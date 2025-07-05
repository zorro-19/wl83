#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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

    if (scr_id == GUI_SCREEN_USB_SLAVE) {
        return gui_scr_create(GUI_SCREEN_USB_SLAVE, "usb_slave", guider_ui.usb_slave, (gui_scr_setup_cb_t)setup_scr_usb_slave, (gui_scr_unload_cb_t)unload_scr_usb_slave);
    }
    if (scr_id == GUI_SCREEN_VIDEO_REC) {
        return gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", guider_ui.video_rec, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
    }
    if (scr_id == GUI_SCREEN_HOME_PAGE) {
        return gui_scr_create(GUI_SCREEN_HOME_PAGE, "home_page", guider_ui.home_page, (gui_scr_setup_cb_t)setup_scr_home_page, (gui_scr_unload_cb_t)unload_scr_home_page);
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        return gui_scr_create(GUI_SCREEN_SYS_PROMPT, "sys_prompt", guider_ui.sys_prompt, (gui_scr_setup_cb_t)setup_scr_sys_prompt, (gui_scr_unload_cb_t)unload_scr_sys_prompt);
    }
    if (scr_id == GUI_SCREEN_SYS_SETTING) {
        return gui_scr_create(GUI_SCREEN_SYS_SETTING, "sys_setting", guider_ui.sys_setting, (gui_scr_setup_cb_t)setup_scr_sys_setting, (gui_scr_unload_cb_t)unload_scr_sys_setting);
    }
    if (scr_id == GUI_SCREEN_VIDEO_PHOTO) {
        return gui_scr_create(GUI_SCREEN_VIDEO_PHOTO, "video_photo", guider_ui.video_photo, (gui_scr_setup_cb_t)setup_scr_video_photo, (gui_scr_unload_cb_t)unload_scr_video_photo);
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        return gui_scr_create(GUI_SCREEN_VIDEO_PLAY, "video_play", guider_ui.video_play, (gui_scr_setup_cb_t)setup_scr_video_play, (gui_scr_unload_cb_t)unload_scr_video_play);
    }
    if (scr_id == GUI_SCREEN_VIDEO_FILE) {
        return gui_scr_create(GUI_SCREEN_VIDEO_FILE, "video_file", guider_ui.video_file, (gui_scr_setup_cb_t)setup_scr_video_file, (gui_scr_unload_cb_t)unload_scr_video_file);
    }
    if (scr_id == GUI_SCREEN_VIDEO_DIR) {
        return gui_scr_create(GUI_SCREEN_VIDEO_DIR, "video_dir", guider_ui.video_dir, (gui_scr_setup_cb_t)setup_scr_video_dir, (gui_scr_unload_cb_t)unload_scr_video_dir);
    }
    if (scr_id == GUI_SCREEN_CAR_PARKING) {
        return gui_scr_create(GUI_SCREEN_CAR_PARKING, "car_parking", guider_ui.car_parking, (gui_scr_setup_cb_t)setup_scr_car_parking, (gui_scr_unload_cb_t)unload_scr_car_parking);
    }
    if (scr_id == GUI_SCREEN_LINE_DRIFT) {
        return gui_scr_create(GUI_SCREEN_LINE_DRIFT, "line_drift", guider_ui.line_drift, (gui_scr_setup_cb_t)setup_scr_line_drift, (gui_scr_unload_cb_t)unload_scr_line_drift);
    }
    if (scr_id == GUI_SCREEN_SYS_POPWIN) {
        return gui_scr_create(GUI_SCREEN_SYS_POPWIN, "sys_popwin", guider_ui.sys_popwin, (gui_scr_setup_cb_t)setup_scr_sys_popwin, (gui_scr_unload_cb_t)unload_scr_sys_popwin);
    }
    return NULL;
}

void ui_init_style(lv_style_t *style)
{
    if (style->prop_cnt > 1) {
        lv_style_reset(style);
    } else {
        lv_style_init(style);
    }
}

void init_scr_del_flag(lv_ui *ui)
{
    ui->usb_slave_del = true;
    ui->video_rec_del = true;
    ui->home_page_del = true;
    ui->sys_prompt_del = true;
    ui->sys_setting_del = true;
    ui->video_photo_del = true;
    ui->video_play_del = true;
    ui->video_file_del = true;
    ui->video_dir_del = true;
    ui->car_parking_del = true;
    ui->line_drift_del = true;
    ui->sys_popwin_del = true;
}

void setup_ui(lv_ui *ui)
{
    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale(lv_i18n_get_default_locale());
    init_gui_fonts();
    ui_style_init();
    init_scr_del_flag(ui);
    gui_scr_t *scr = gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", ui->video_rec, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
    ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
    events_init(ui);
    gui_group_init();
    ui_scr_manager_init();
#if LV_USE_MSG
    gui_msg_init(ui);
#endif
    gui_timelines_init(ui);
}
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec)
{
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0)) {
        days_in_month[1] = 29;
    }
    (*sec)++;
    if (*sec >= 60) {
        *sec = 0;
        (*min)++;
    }
    if (*min >= 60) {
        *min = 0;
        (*hour)++;
    }
    if (*hour >= 24) {
        *hour = 0;
        (*day)++;
    }
    if (*day > days_in_month[*month - 1]) {
        *day = 1;
        (*month)++;
        if (*month > 12) {
            *month = 1;
            (*year)++;
        }
    }
}

#endif

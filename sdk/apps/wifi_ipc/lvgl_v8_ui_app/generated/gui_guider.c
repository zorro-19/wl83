/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "gui_timelines.h"

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

    gui_scr_set_act_anim(screen, ui, anim_type, time, delay, is_clean, auto_del);

    if (act_screen != NULL && gui_scr_get_act() == screen) {
        gui_msg_init_ui();
        gui_msg_init_events();
        delete_gui_timelines();

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
    ui->start_del = true;
    ui->home_del = true;
    ui->menu_del = true;
    ui->language_del = true;
    ui->app_del = true;
    ui->syscfg_del = true;
    ui->sysinfo_del = true;
}

void setup_ui(lv_ui *ui)
{
    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale("zh_cn");
    init_gui_fonts();
    init_scr_del_flag(ui);
    gui_scr_t *scr = gui_scr_create(GUI_SCREEN_START, "start", ui->start, (gui_scr_setup_cb_t)setup_scr_start, (gui_scr_unload_cb_t)unload_scr_start);
    ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
#if LV_USE_MSG
    gui_msg_init(ui);
#endif
    init_gui_timelines(ui);
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

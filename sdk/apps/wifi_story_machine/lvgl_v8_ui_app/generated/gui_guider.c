/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include "./gui_guider.h"
#include "./gui_timelines/gui_timelines.h"
#include "./gui_group/gui_group.h"

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
    ui->audio_del = true;
    ui->camera_del = true;
    ui->boot_animation_del = true;
    ui->home_del = true;
    ui->key_del = true;
    ui->camera1_mipi_del = true;
    ui->audio_local_music_del = true;
    ui->audio_recorder_del = true;
    ui->audio_net_music_del = true;
    ui->wifi_del = true;
    ui->audio_bt_music_del = true;
    ui->bluetooth_del = true;
    ui->camera2_dvp_del = true;
    ui->camera3_dvp_del = true;
    ui->sdcard_del = true;
}

void setup_ui(lv_ui *ui)
{
    init_gui_fonts();
    init_scr_del_flag(ui);
    gui_scr_t *scr = gui_scr_create(GUI_SCREEN_BOOT_ANIMATION, "boot_animation", ui->boot_animation, (gui_scr_setup_cb_t)setup_scr_boot_animation, (gui_scr_unload_cb_t)unload_scr_boot_animation);
    ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
    gui_group_init();
#if LV_USE_MSG
    gui_msg_init(ui);
#endif
    init_gui_timelines(ui);
}

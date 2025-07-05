#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_sys_popwin(lv_ui *ui)
{
    if (lv_obj_is_valid(ui->sys_popwin)) {
        lv_obj_del(ui->sys_popwin);
    }
    //Write codes sys_popwin
    ui->sys_popwin = lv_obj_create(lv_layer_top());
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_popwin. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_popwin, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_popwin, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->sys_popwin, 800, 480);
    lv_obj_set_scrollbar_mode(ui->sys_popwin, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->sys_popwin, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_popwin_view_1
    ui->sys_popwin_view_1 = lv_obj_create(ui->sys_popwin);

    //Set style for sys_popwin_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_popwin_view_1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->sys_popwin_view_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_popwin_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_popwin_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_popwin_view_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_popwin_view_1, 199, 100);
    lv_obj_set_size(ui->sys_popwin_view_1, 390, 250);
    lv_obj_set_scrollbar_mode(ui->sys_popwin_view_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_popwin_lbl_1
    ui->sys_popwin_lbl_1 = lv_label_create(ui->sys_popwin_view_1);
    lv_label_set_long_mode(ui->sys_popwin_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_popwin_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_popwin_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_popwin_lbl_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_popwin_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_popwin_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_popwin_lbl_1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_popwin_lbl_1, 15, 0);
    lv_obj_set_size(ui->sys_popwin_lbl_1, 360, 165);
    lv_obj_set_scrollbar_mode(ui->sys_popwin_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_popwin_btn_1
    ui->sys_popwin_btn_1 = lv_btn_create(ui->sys_popwin_view_1);

    //Set style for sys_popwin_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_popwin_btn_1, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_popwin_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_popwin_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_popwin_btn_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_popwin_btn_1, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_popwin_btn_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_popwin_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->sys_popwin_btn_1, &gui_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->sys_popwin_btn_1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->sys_popwin_btn_1, 230, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->sys_popwin_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_pos(ui->sys_popwin_btn_1, 14, 132);
    lv_obj_set_size(ui->sys_popwin_btn_1, 181, 72);
    lv_obj_set_scrollbar_mode(ui->sys_popwin_btn_1, LV_SCROLLBAR_MODE_OFF);
    ui->sys_popwin_btn_1_label = lv_label_create(ui->sys_popwin_btn_1);
    lv_obj_set_style_pad_all(ui->sys_popwin_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_popwin_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_popwin_btn_2
    ui->sys_popwin_btn_2 = lv_btn_create(ui->sys_popwin_view_1);

    //Set style for sys_popwin_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_popwin_btn_2, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_popwin_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_popwin_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_popwin_btn_2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_popwin_btn_2, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_popwin_btn_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_popwin_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->sys_popwin_btn_2, &gui_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->sys_popwin_btn_2, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->sys_popwin_btn_2, 230, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->sys_popwin_btn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_pos(ui->sys_popwin_btn_2, 195, 132);
    lv_obj_set_size(ui->sys_popwin_btn_2, 181, 72);
    lv_obj_set_scrollbar_mode(ui->sys_popwin_btn_2, LV_SCROLLBAR_MODE_OFF);
    ui->sys_popwin_btn_2_label = lv_label_create(ui->sys_popwin_btn_2);
    lv_obj_set_style_pad_all(ui->sys_popwin_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_popwin_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->sys_popwin);
    ui->sys_popwin_del = false;
    i18n_refresh_texts("sys_popwin");

    //Init events for screen
    events_init_sys_popwin(ui);
    return ui->sys_popwin;
}
void unload_scr_sys_popwin(lv_ui *ui)
{
    ui->sys_popwin_del = true;
}

#endif

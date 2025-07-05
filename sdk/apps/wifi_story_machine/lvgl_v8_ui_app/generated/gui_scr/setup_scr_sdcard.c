/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_sdcard(lv_ui *ui)
{
    //Write codes sdcard
    ui->sdcard = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sdcard. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->sdcard, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->sdcard, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->sdcard, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->sdcard, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->sdcard, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes sdcard_title
    ui->sdcard_title = lv_label_create(ui->sdcard);
    lv_label_set_text(ui->sdcard_title, "SD Card");
    lv_label_set_long_mode(ui->sdcard_title, LV_LABEL_LONG_WRAP);

    //Set style for sdcard_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sdcard_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sdcard_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sdcard_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sdcard_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sdcard_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sdcard_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_title, 5, 4);
    lv_obj_set_size(ui->sdcard_title, 481, 85);
    lv_obj_set_scrollbar_mode(ui->sdcard_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes sdcard_back_btn
    ui->sdcard_back_btn = lv_btn_create(ui->sdcard);

    //Set style for sdcard_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sdcard_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sdcard_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sdcard_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->sdcard_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->sdcard_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sdcard_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->sdcard_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sdcard_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sdcard_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->sdcard_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sdcard_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_back_btn, 5, 10);
    lv_obj_set_size(ui->sdcard_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->sdcard_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->sdcard_back_btn_label = lv_label_create(ui->sdcard_back_btn);
    lv_label_set_text(ui->sdcard_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->sdcard_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sdcard_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sdcard_show_sdcard_state
    ui->sdcard_show_sdcard_state = lv_obj_create(ui->sdcard);

    //Set style for sdcard_show_sdcard_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_show_sdcard_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sdcard_show_sdcard_state, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard_show_sdcard_state, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sdcard_show_sdcard_state, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sdcard_show_sdcard_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_show_sdcard_state, 5, 100);
    lv_obj_set_size(ui->sdcard_show_sdcard_state, 475, 196);
    lv_obj_set_scrollbar_mode(ui->sdcard_show_sdcard_state, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sdcard_show_sdcard_state, LV_OBJ_FLAG_HIDDEN);
    //Write codes sdcard_capacity_bar
    ui->sdcard_capacity_bar = lv_bar_create(ui->sdcard_show_sdcard_state);

    //Set style for sdcard_capacity_bar. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_capacity_bar, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_capacity_bar, lv_color_make(0xD3, 0xED, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_capacity_bar, 61, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_capacity_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sdcard_capacity_bar. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_capacity_bar, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_capacity_bar, lv_color_make(0x13, 0x69, 0xD8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_capacity_bar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_capacity_bar, 21, 50);
    lv_obj_set_size(ui->sdcard_capacity_bar, 400, 41);
    lv_obj_set_scrollbar_mode(ui->sdcard_capacity_bar, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_anim_time(ui->sdcard_capacity_bar, 1000, 0);
    lv_bar_set_mode(ui->sdcard_capacity_bar, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->sdcard_capacity_bar, 0, 100);
    lv_bar_set_value(ui->sdcard_capacity_bar, 0, LV_ANIM_OFF);
    //Write codes sdcard_sdcard_path_label
    ui->sdcard_sdcard_path_label = lv_label_create(ui->sdcard_show_sdcard_state);
    lv_label_set_text(ui->sdcard_sdcard_path_label, "storage/sd0/C/");
    lv_label_set_long_mode(ui->sdcard_sdcard_path_label, LV_LABEL_LONG_WRAP);

    //Set style for sdcard_sdcard_path_label. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_sdcard_path_label, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sdcard_sdcard_path_label, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sdcard_sdcard_path_label, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->sdcard_sdcard_path_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sdcard_sdcard_path_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sdcard_sdcard_path_label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sdcard_sdcard_path_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_sdcard_path_label, 4, 0);
    lv_obj_set_size(ui->sdcard_sdcard_path_label, 249, 37);
    lv_obj_set_scrollbar_mode(ui->sdcard_sdcard_path_label, LV_SCROLLBAR_MODE_OFF);
    //Write codes sdcard_sdcard_total_label
    ui->sdcard_sdcard_total_label = lv_label_create(ui->sdcard_show_sdcard_state);
    lv_label_set_text(ui->sdcard_sdcard_total_label, "26000MB available, 30000MB total");
    lv_label_set_long_mode(ui->sdcard_sdcard_total_label, LV_LABEL_LONG_WRAP);

    //Set style for sdcard_sdcard_total_label. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_sdcard_total_label, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sdcard_sdcard_total_label, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sdcard_sdcard_total_label, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->sdcard_sdcard_total_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sdcard_sdcard_total_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sdcard_sdcard_total_label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sdcard_sdcard_total_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_sdcard_total_label, 10, 94);
    lv_obj_set_size(ui->sdcard_sdcard_total_label, 438, 64);
    lv_obj_set_scrollbar_mode(ui->sdcard_sdcard_total_label, LV_SCROLLBAR_MODE_OFF);
    //Write codes sdcard_not_found_label
    ui->sdcard_not_found_label = lv_label_create(ui->sdcard);
    lv_label_set_text(ui->sdcard_not_found_label, "SD card \nNot found!!!");
    lv_label_set_long_mode(ui->sdcard_not_found_label, LV_LABEL_LONG_WRAP);

    //Set style for sdcard_not_found_label. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sdcard_not_found_label, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sdcard_not_found_label, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sdcard_not_found_label, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->sdcard_not_found_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sdcard_not_found_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sdcard_not_found_label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sdcard_not_found_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sdcard_not_found_label, 88, 349);
    lv_obj_set_size(ui->sdcard_not_found_label, 312, 149);
    lv_obj_set_scrollbar_mode(ui->sdcard_not_found_label, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->sdcard);
    ui->sdcard_del = false;

    //Init events for screen
    events_init_sdcard(ui);
    return ui->sdcard;
}
void unload_scr_sdcard(lv_ui *ui)
{
    ui->sdcard_del = true;
}

/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_audio_local_music(lv_ui *ui)
{
    //Write codes audio_local_music
    ui->audio_local_music = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for audio_local_music. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->audio_local_music, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->audio_local_music, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->audio_local_music, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->audio_local_music, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->audio_local_music, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes audio_local_music_title
    ui->audio_local_music_title = lv_label_create(ui->audio_local_music);
    lv_label_set_text(ui->audio_local_music_title, "Local Music");
    lv_label_set_long_mode(ui->audio_local_music_title, LV_LABEL_LONG_WRAP);

    //Set style for audio_local_music_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_local_music_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_local_music_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->audio_local_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_title, 25, 0);
    lv_obj_set_size(ui->audio_local_music_title, 453, 85);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes audio_local_music_back_btn
    ui->audio_local_music_back_btn = lv_btn_create(ui->audio_local_music);

    //Set style for audio_local_music_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_local_music_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_local_music_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_local_music_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_local_music_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_local_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_local_music_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_local_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_back_btn, 0, 9);
    lv_obj_set_size(ui->audio_local_music_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_local_music_back_btn_label = lv_label_create(ui->audio_local_music_back_btn);
    lv_label_set_text(ui->audio_local_music_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->audio_local_music_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_local_music_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_local_music_switch_btn
    ui->audio_local_music_switch_btn = lv_btn_create(ui->audio_local_music);

    //Set style for audio_local_music_switch_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_switch_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_switch_btn, lv_color_make(0x6B, 0x78, 0x83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_switch_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_switch_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_local_music_switch_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_switch_btn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_local_music_switch_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_local_music_switch_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_local_music_switch_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_local_music_switch_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_local_music_switch_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_local_music_switch_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_switch_btn, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_switch_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_switch_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_switch_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_switch_btn, 156, 346);
    lv_obj_set_size(ui->audio_local_music_switch_btn, 176, 108);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_switch_btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->audio_local_music_switch_btn, LV_OBJ_FLAG_CHECKABLE);
    ui->audio_local_music_switch_btn_label = lv_label_create(ui->audio_local_music_switch_btn);
    lv_label_set_text(ui->audio_local_music_switch_btn_label, "Pause/Play");
    lv_obj_set_style_pad_all(ui->audio_local_music_switch_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_local_music_switch_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_local_music_prev_btn
    ui->audio_local_music_prev_btn = lv_btn_create(ui->audio_local_music);

    //Set style for audio_local_music_prev_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_prev_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_prev_btn, lv_color_make(0x6B, 0x78, 0x83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_prev_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_prev_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_local_music_prev_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_prev_btn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_local_music_prev_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_local_music_prev_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_local_music_prev_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_local_music_prev_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_local_music_prev_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_local_music_prev_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_prev_btn, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_prev_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_prev_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_prev_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_prev_btn, 25, 370);
    lv_obj_set_size(ui->audio_local_music_prev_btn, 98, 60);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_prev_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_local_music_prev_btn_label = lv_label_create(ui->audio_local_music_prev_btn);
    lv_label_set_text(ui->audio_local_music_prev_btn_label, "Prev");
    lv_obj_set_style_pad_all(ui->audio_local_music_prev_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_local_music_prev_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_local_music_next_btn
    ui->audio_local_music_next_btn = lv_btn_create(ui->audio_local_music);

    //Set style for audio_local_music_next_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_next_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_next_btn, lv_color_make(0x6B, 0x78, 0x83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_next_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_next_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_local_music_next_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_next_btn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_local_music_next_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_local_music_next_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_local_music_next_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_local_music_next_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_local_music_next_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_local_music_next_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_next_btn, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_next_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_next_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_next_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_next_btn, 361, 370);
    lv_obj_set_size(ui->audio_local_music_next_btn, 98, 60);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_next_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_local_music_next_btn_label = lv_label_create(ui->audio_local_music_next_btn);
    lv_label_set_text(ui->audio_local_music_next_btn_label, "Next");
    lv_obj_set_style_pad_all(ui->audio_local_music_next_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_local_music_next_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_local_music_volume_slider
    ui->audio_local_music_volume_slider = lv_slider_create(ui->audio_local_music);

    //Set style for audio_local_music_volume_slider. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_volume_slider, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_volume_slider, lv_color_make(0x6B, 0x78, 0x83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_volume_slider, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_volume_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_local_music_volume_slider, lv_color_make(0x6B, 0x78, 0x83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_local_music_volume_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_local_music_volume_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_local_music_volume_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for audio_local_music_volume_slider. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_volume_slider, 50, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_volume_slider, lv_color_make(0x6B, 0x78, 0x83), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_volume_slider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Set style for audio_local_music_volume_slider. Part: LV_PART_KNOB, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_volume_slider, 50, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_volume_slider, lv_color_make(0xDC, 0xDF, 0xE4), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_volume_slider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_volume_slider, 64, 491);
    lv_obj_set_size(ui->audio_local_music_volume_slider, 360, 29);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_volume_slider, LV_SCROLLBAR_MODE_OFF);
    lv_slider_set_range(ui->audio_local_music_volume_slider, 0, 100);
    lv_slider_set_mode(ui->audio_local_music_volume_slider, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->audio_local_music_volume_slider, 50, LV_ANIM_OFF);
    lv_slider_set_left_value(ui->audio_local_music_volume_slider, 0, LV_ANIM_OFF);
    //Write codes audio_local_music_lbl_1
    ui->audio_local_music_lbl_1 = lv_label_create(ui->audio_local_music);
    lv_label_set_text(ui->audio_local_music_lbl_1, "No Music Files Found");
    lv_label_set_long_mode(ui->audio_local_music_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for audio_local_music_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_lbl_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_lbl_1, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->audio_local_music_lbl_1, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->audio_local_music_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->audio_local_music_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_lbl_1, 0, 246);
    lv_obj_set_size(ui->audio_local_music_lbl_1, 480, 96);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes audio_local_music_music_time
    ui->audio_local_music_music_time = lv_bar_create(ui->audio_local_music);

    //Set style for audio_local_music_music_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_music_time, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_music_time, lv_color_make(0x6B, 0x78, 0x83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_music_time, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_music_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for audio_local_music_music_time. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_music_time, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_music_time, lv_color_make(0x6B, 0x78, 0x83), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_music_time, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_music_time, 80, 465);
    lv_obj_set_size(ui->audio_local_music_music_time, 320, 10);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_music_time, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_anim_time(ui->audio_local_music_music_time, 1000, 0);
    lv_bar_set_mode(ui->audio_local_music_music_time, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->audio_local_music_music_time, 0, 100);
    lv_bar_set_value(ui->audio_local_music_music_time, 0, LV_ANIM_OFF);
    lv_obj_update_layout(ui->audio_local_music);
    ui->audio_local_music_del = false;

    //Init events for screen
    events_init_audio_local_music(ui);
    return ui->audio_local_music;
}
void unload_scr_audio_local_music(lv_ui *ui)
{
    ui->audio_local_music_del = true;
}

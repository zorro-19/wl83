/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_audio(lv_ui *ui)
{
    //Write codes audio
    ui->audio = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for audio. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->audio, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->audio, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->audio, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->audio, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->audio, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes audio_title
    ui->audio_title = lv_label_create(ui->audio);
    lv_label_set_text(ui->audio_title, "Audio");
    lv_label_set_long_mode(ui->audio_title, LV_LABEL_LONG_WRAP);

    //Set style for audio_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->audio_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_title, 0, 0);
    lv_obj_set_size(ui->audio_title, 481, 85);
    lv_obj_set_scrollbar_mode(ui->audio_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes audio_back_btn
    ui->audio_back_btn = lv_btn_create(ui->audio);

    //Set style for audio_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_back_btn, 5, 9);
    lv_obj_set_size(ui->audio_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->audio_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_back_btn_label = lv_label_create(ui->audio_back_btn);
    lv_label_set_text(ui->audio_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->audio_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_local_music_btn
    ui->audio_local_music_btn = lv_btn_create(ui->audio);

    //Set style for audio_local_music_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_local_music_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_local_music_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_local_music_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_local_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_local_music_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_local_music_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_local_music_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_local_music_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_local_music_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_local_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_local_music_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_local_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_local_music_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_local_music_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_local_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_local_music_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_local_music_btn, 140, 160);
    lv_obj_set_size(ui->audio_local_music_btn, 200, 100);
    lv_obj_set_scrollbar_mode(ui->audio_local_music_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_local_music_btn_label = lv_label_create(ui->audio_local_music_btn);
    lv_label_set_text(ui->audio_local_music_btn_label, "local music");
    lv_obj_set_style_pad_all(ui->audio_local_music_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_local_music_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_recorder_btn
    ui->audio_recorder_btn = lv_btn_create(ui->audio);

    //Set style for audio_recorder_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_recorder_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_recorder_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_recorder_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_recorder_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_recorder_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_recorder_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_recorder_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_recorder_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_recorder_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_recorder_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_recorder_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_recorder_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_recorder_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_recorder_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_recorder_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_recorder_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_recorder_btn, 140, 310);
    lv_obj_set_size(ui->audio_recorder_btn, 200, 100);
    lv_obj_set_scrollbar_mode(ui->audio_recorder_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_recorder_btn_label = lv_label_create(ui->audio_recorder_btn);
    lv_label_set_text(ui->audio_recorder_btn_label, "recorder");
    lv_obj_set_style_pad_all(ui->audio_recorder_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_recorder_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_bt_music_btn
    ui->audio_bt_music_btn = lv_btn_create(ui->audio);

    //Set style for audio_bt_music_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_bt_music_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_bt_music_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_bt_music_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_bt_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_bt_music_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_bt_music_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_bt_music_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_bt_music_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_bt_music_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_bt_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_bt_music_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_bt_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_bt_music_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_bt_music_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_bt_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_bt_music_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_bt_music_btn, 140, 460);
    lv_obj_set_size(ui->audio_bt_music_btn, 200, 98);
    lv_obj_set_scrollbar_mode(ui->audio_bt_music_btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->audio_bt_music_btn, LV_OBJ_FLAG_HIDDEN);
    ui->audio_bt_music_btn_label = lv_label_create(ui->audio_bt_music_btn);
    lv_label_set_text(ui->audio_bt_music_btn_label, "bt music");
    lv_obj_set_style_pad_all(ui->audio_bt_music_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_bt_music_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes audio_net_music_btn
    ui->audio_net_music_btn = lv_btn_create(ui->audio);

    //Set style for audio_net_music_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_net_music_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_net_music_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_net_music_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_net_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_net_music_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_net_music_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_net_music_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_net_music_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_net_music_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_net_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_net_music_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_net_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_net_music_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_net_music_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_net_music_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_net_music_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_net_music_btn, 140, 610);
    lv_obj_set_size(ui->audio_net_music_btn, 200, 98);
    lv_obj_set_scrollbar_mode(ui->audio_net_music_btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->audio_net_music_btn, LV_OBJ_FLAG_HIDDEN);
    ui->audio_net_music_btn_label = lv_label_create(ui->audio_net_music_btn);
    lv_label_set_text(ui->audio_net_music_btn_label, "net music");
    lv_obj_set_style_pad_all(ui->audio_net_music_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_net_music_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->audio);
    ui->audio_del = false;

    //Init events for screen
    events_init_audio(ui);
    return ui->audio;
}
void unload_scr_audio(lv_ui *ui)
{
    ui->audio_del = true;
}

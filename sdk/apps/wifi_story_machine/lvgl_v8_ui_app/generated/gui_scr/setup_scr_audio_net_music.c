/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_audio_net_music(lv_ui *ui)
{
    //Write codes audio_net_music
    ui->audio_net_music = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for audio_net_music. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->audio_net_music, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->audio_net_music, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->audio_net_music, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_net_music, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_net_music, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->audio_net_music, LV_SCROLLBAR_MODE_OFF);
    //Write codes audio_net_music_title
    ui->audio_net_music_title = lv_label_create(ui->audio_net_music);
    lv_label_set_text(ui->audio_net_music_title, "Net Music");
    lv_label_set_long_mode(ui->audio_net_music_title, LV_LABEL_LONG_WRAP);

    //Set style for audio_net_music_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_net_music_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_net_music_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_net_music_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_net_music_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_net_music_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_net_music_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_net_music_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_net_music_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_net_music_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->audio_net_music_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_net_music_title, 46, 0);
    lv_obj_set_size(ui->audio_net_music_title, 414, 85);
    lv_obj_set_scrollbar_mode(ui->audio_net_music_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes audio_net_music_back_btn
    ui->audio_net_music_back_btn = lv_btn_create(ui->audio_net_music);

    //Set style for audio_net_music_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->audio_net_music_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->audio_net_music_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->audio_net_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->audio_net_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->audio_net_music_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->audio_net_music_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->audio_net_music_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->audio_net_music_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->audio_net_music_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->audio_net_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->audio_net_music_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->audio_net_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->audio_net_music_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->audio_net_music_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->audio_net_music_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->audio_net_music_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->audio_net_music_back_btn, 5, 10);
    lv_obj_set_size(ui->audio_net_music_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->audio_net_music_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->audio_net_music_back_btn_label = lv_label_create(ui->audio_net_music_back_btn);
    lv_label_set_text(ui->audio_net_music_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->audio_net_music_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->audio_net_music_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->audio_net_music);
    ui->audio_net_music_del = false;

    //Init events for screen
    events_init_audio_net_music(ui);
    return ui->audio_net_music;
}
void unload_scr_audio_net_music(lv_ui *ui)
{
    ui->audio_net_music_del = true;
}

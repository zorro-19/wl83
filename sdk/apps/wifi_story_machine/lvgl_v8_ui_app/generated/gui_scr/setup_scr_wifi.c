/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static void kb_wifi_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}
__attribute__((unused)) static void ta_wifi_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);
    }
}

lv_obj_t *setup_scr_wifi(lv_ui *ui)
{
    //Write codes wifi
    ui->wifi = lv_obj_create(NULL);

    //Create keyboard on wifi
    ui->g_kb_wifi = lv_keyboard_create(ui->wifi);
    lv_obj_add_event_cb(ui->g_kb_wifi, kb_wifi_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_wifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_wifi, &lv_font_Merge_fonts_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->g_kb_wifi, LV_PCT(100), LV_PCT(40));
    lv_keyboard_set_mode(ui->g_kb_wifi, LV_KEYBOARD_MODE_TEXT_LOWER);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for wifi. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->wifi, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->wifi, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->wifi, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->wifi, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes wifi_title
    ui->wifi_title = lv_label_create(ui->wifi);
    lv_label_set_text(ui->wifi_title, "WIFI\n");
    lv_label_set_long_mode(ui->wifi_title, LV_LABEL_LONG_WRAP);

    //Set style for wifi_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_title, -1, 1);
    lv_obj_set_size(ui->wifi_title, 481, 85);
    lv_obj_set_scrollbar_mode(ui->wifi_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_back_btn
    ui->wifi_back_btn = lv_btn_create(ui->wifi);

    //Set style for wifi_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_back_btn, 5, 10);
    lv_obj_set_size(ui->wifi_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->wifi_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->wifi_back_btn_label = lv_label_create(ui->wifi_back_btn);
    lv_label_set_text(ui->wifi_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->wifi_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->wifi_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes wifi_show_current_ssid
    ui->wifi_show_current_ssid = lv_textarea_create(ui->wifi);

    //Set style for wifi_show_current_ssid. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_show_current_ssid, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_show_current_ssid, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_show_current_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_show_current_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_show_current_ssid, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_show_current_ssid, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_show_current_ssid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_show_current_ssid, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_show_current_ssid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_show_current_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_show_current_ssid, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_show_current_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_show_current_ssid, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_show_current_ssid, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_show_current_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_show_current_ssid, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_show_current_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_show_current_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_show_current_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_show_current_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for wifi_show_current_ssid. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_show_current_ssid, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_show_current_ssid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_show_current_ssid, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_show_current_ssid, 36, 112);
    lv_obj_set_size(ui->wifi_show_current_ssid, 400, 132);
    lv_obj_set_scrollbar_mode(ui->wifi_show_current_ssid, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->wifi_show_current_ssid, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->wifi_show_current_ssid, LV_OBJ_FLAG_CHECKABLE);
    lv_textarea_set_text(ui->wifi_show_current_ssid, "WIFI Connect Fail SSID:");

    //use keyboard on wifi_show_current_ssid
    lv_obj_add_event_cb(ui->wifi_show_current_ssid, ta_wifi_event_cb, LV_EVENT_ALL, ui->g_kb_wifi);
    //Write codes wifi_login_wifi
    ui->wifi_login_wifi = lv_obj_create(ui->wifi);

    //Set style for wifi_login_wifi. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_login_wifi, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_login_wifi, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_login_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_login_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_login_wifi, lv_color_make(0x23, 0x3B, 0x50), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_login_wifi, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_login_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_login_wifi, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_login_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_login_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_login_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_login_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_login_wifi, 42, 250);
    lv_obj_set_size(ui->wifi_login_wifi, 394, 267);
    lv_obj_set_scrollbar_mode(ui->wifi_login_wifi, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_ssid_txt
    ui->wifi_ssid_txt = lv_textarea_create(ui->wifi_login_wifi);

    //Set style for wifi_ssid_txt. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_ssid_txt, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_ssid_txt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_ssid_txt, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_ssid_txt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_ssid_txt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_ssid_txt, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_ssid_txt, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_ssid_txt, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_ssid_txt, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_ssid_txt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_ssid_txt, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_ssid_txt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_ssid_txt, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_ssid_txt, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_ssid_txt, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_ssid_txt, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_ssid_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_ssid_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_ssid_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_ssid_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for wifi_ssid_txt. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_ssid_txt, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_ssid_txt, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_ssid_txt, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_ssid_txt, 117, 16);
    lv_obj_set_size(ui->wifi_ssid_txt, 220, 50);
    lv_obj_set_scrollbar_mode(ui->wifi_ssid_txt, LV_SCROLLBAR_MODE_OFF);

    //use keyboard on wifi_ssid_txt
    lv_obj_add_event_cb(ui->wifi_ssid_txt, ta_wifi_event_cb, LV_EVENT_ALL, ui->g_kb_wifi);
    //Write codes wifi_pwd_txt
    ui->wifi_pwd_txt = lv_textarea_create(ui->wifi_login_wifi);

    //Set style for wifi_pwd_txt. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_pwd_txt, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_pwd_txt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_pwd_txt, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_pwd_txt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_pwd_txt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_pwd_txt, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_pwd_txt, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_pwd_txt, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_pwd_txt, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_pwd_txt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_pwd_txt, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_pwd_txt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_pwd_txt, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_pwd_txt, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_pwd_txt, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_pwd_txt, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_pwd_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_pwd_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_pwd_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_pwd_txt, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for wifi_pwd_txt. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_pwd_txt, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_pwd_txt, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_pwd_txt, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_pwd_txt, 117, 78);
    lv_obj_set_size(ui->wifi_pwd_txt, 220, 50);
    lv_obj_set_scrollbar_mode(ui->wifi_pwd_txt, LV_SCROLLBAR_MODE_OFF);

    //use keyboard on wifi_pwd_txt
    lv_obj_add_event_cb(ui->wifi_pwd_txt, ta_wifi_event_cb, LV_EVENT_ALL, ui->g_kb_wifi);
    //Write codes wifi_connect_btn
    ui->wifi_connect_btn = lv_btn_create(ui->wifi_login_wifi);

    //Set style for wifi_connect_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_connect_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_connect_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_connect_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_connect_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_connect_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_connect_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_connect_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_btn, &lv_font_FontAwesome5_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_btn, 239, 150);
    lv_obj_set_size(ui->wifi_connect_btn, 98, 41);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_btn, LV_SCROLLBAR_MODE_OFF);
    ui->wifi_connect_btn_label = lv_label_create(ui->wifi_connect_btn);
    lv_label_set_text(ui->wifi_connect_btn_label, "connect");
    lv_obj_set_style_pad_all(ui->wifi_connect_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->wifi_connect_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes wifi_ssid_label
    ui->wifi_ssid_label = lv_label_create(ui->wifi_login_wifi);
    lv_label_set_text(ui->wifi_ssid_label, "ssid");
    lv_label_set_long_mode(ui->wifi_ssid_label, LV_LABEL_LONG_WRAP);

    //Set style for wifi_ssid_label. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_ssid_label, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_ssid_label, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_ssid_label, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_ssid_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_ssid_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_ssid_label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_ssid_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_ssid_label, 27, 17);
    lv_obj_set_size(ui->wifi_ssid_label, 80, 50);
    lv_obj_set_scrollbar_mode(ui->wifi_ssid_label, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_pwd_label
    ui->wifi_pwd_label = lv_label_create(ui->wifi_login_wifi);
    lv_label_set_text(ui->wifi_pwd_label, "pwd\n");
    lv_label_set_long_mode(ui->wifi_pwd_label, LV_LABEL_LONG_WRAP);

    //Set style for wifi_pwd_label. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_pwd_label, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_pwd_label, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_pwd_label, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_pwd_label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_pwd_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_pwd_label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_pwd_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_pwd_label, 28, 77);
    lv_obj_set_size(ui->wifi_pwd_label, 80, 50);
    lv_obj_set_scrollbar_mode(ui->wifi_pwd_label, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->wifi);
    ui->wifi_del = false;

    //Init events for screen
    events_init_wifi(ui);
    return ui->wifi;
}
void unload_scr_wifi(lv_ui *ui)
{
    ui->wifi_del = true;
}

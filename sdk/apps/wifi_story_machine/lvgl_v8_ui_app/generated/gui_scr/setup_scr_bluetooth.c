/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_bluetooth(lv_ui *ui)
{
    //Write codes bluetooth
    ui->bluetooth = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for bluetooth. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->bluetooth, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->bluetooth, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->bluetooth, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bluetooth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->bluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->bluetooth, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->bluetooth, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes bluetooth_title
    ui->bluetooth_title = lv_label_create(ui->bluetooth);
    lv_label_set_text(ui->bluetooth_title, "Bluetooth");
    lv_label_set_long_mode(ui->bluetooth_title, LV_LABEL_LONG_WRAP);

    //Set style for bluetooth_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->bluetooth_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->bluetooth_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bluetooth_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->bluetooth_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->bluetooth_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->bluetooth_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->bluetooth_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->bluetooth_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->bluetooth_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->bluetooth_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->bluetooth_title, 36, 0);
    lv_obj_set_size(ui->bluetooth_title, 431, 85);
    lv_obj_set_scrollbar_mode(ui->bluetooth_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes bluetooth_back_btn
    ui->bluetooth_back_btn = lv_btn_create(ui->bluetooth);

    //Set style for bluetooth_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->bluetooth_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->bluetooth_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bluetooth_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->bluetooth_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->bluetooth_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->bluetooth_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->bluetooth_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->bluetooth_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->bluetooth_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->bluetooth_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->bluetooth_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->bluetooth_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->bluetooth_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->bluetooth_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->bluetooth_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->bluetooth_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->bluetooth_back_btn, 5, 10);
    lv_obj_set_size(ui->bluetooth_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->bluetooth_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->bluetooth_back_btn_label = lv_label_create(ui->bluetooth_back_btn);
    lv_label_set_text(ui->bluetooth_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->bluetooth_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->bluetooth_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes bluetooth_show_bt_name
    ui->bluetooth_show_bt_name = lv_textarea_create(ui->bluetooth);

    //Set style for bluetooth_show_bt_name. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->bluetooth_show_bt_name, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->bluetooth_show_bt_name, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bluetooth_show_bt_name, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->bluetooth_show_bt_name, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->bluetooth_show_bt_name, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->bluetooth_show_bt_name, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->bluetooth_show_bt_name, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->bluetooth_show_bt_name, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->bluetooth_show_bt_name, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->bluetooth_show_bt_name, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->bluetooth_show_bt_name, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->bluetooth_show_bt_name, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->bluetooth_show_bt_name, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->bluetooth_show_bt_name, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->bluetooth_show_bt_name, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->bluetooth_show_bt_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->bluetooth_show_bt_name, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->bluetooth_show_bt_name, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->bluetooth_show_bt_name, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->bluetooth_show_bt_name, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for bluetooth_show_bt_name. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->bluetooth_show_bt_name, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->bluetooth_show_bt_name, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bluetooth_show_bt_name, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->bluetooth_show_bt_name, 61, 137);
    lv_obj_set_size(ui->bluetooth_show_bt_name, 358, 75);
    lv_obj_set_scrollbar_mode(ui->bluetooth_show_bt_name, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->bluetooth_show_bt_name, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui->bluetooth_show_bt_name, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_flag(ui->bluetooth_show_bt_name, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_textarea_set_text(ui->bluetooth_show_bt_name, "Bluetooth Name:");
    //Write codes bluetooth_bt_state
    ui->bluetooth_bt_state = lv_label_create(ui->bluetooth);
    lv_label_set_text(ui->bluetooth_bt_state, "Bluetooth\nDisconnect !!!!!!");
    lv_label_set_long_mode(ui->bluetooth_bt_state, LV_LABEL_LONG_WRAP);

    //Set style for bluetooth_bt_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->bluetooth_bt_state, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->bluetooth_bt_state, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->bluetooth_bt_state, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->bluetooth_bt_state, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->bluetooth_bt_state, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->bluetooth_bt_state, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->bluetooth_bt_state, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->bluetooth_bt_state, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->bluetooth_bt_state, 0, 245);
    lv_obj_set_size(ui->bluetooth_bt_state, 480, 130);
    lv_obj_set_scrollbar_mode(ui->bluetooth_bt_state, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->bluetooth);
    ui->bluetooth_del = false;

    //Init events for screen
    events_init_bluetooth(ui);
    return ui->bluetooth;
}
void unload_scr_bluetooth(lv_ui *ui)
{
    ui->bluetooth_del = true;
}

/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_home(lv_ui *ui)
{
    //Write codes home
    ui->home = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for home. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->home, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->home, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->home, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->home, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes home_list
    ui->home_list = lv_list_create(ui->home);

    //Set style for home_list. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_list, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_list, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_list, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_list, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_list, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_list, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_list. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_list, 5, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_list, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_list, 128, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_home_list_extra_btns_main_default
    static lv_style_t style_home_list_extra_btns_main_default;
    ui_init_style(&style_home_list_extra_btns_main_default);
    lv_style_set_radius(&style_home_list_extra_btns_main_default, 3);
    lv_style_set_bg_color(&style_home_list_extra_btns_main_default, lv_color_make(0xB9, 0xA5, 0xA5));
    lv_style_set_bg_opa(&style_home_list_extra_btns_main_default, 0);
    lv_style_set_border_color(&style_home_list_extra_btns_main_default, lv_color_make(0x1B, 0x18, 0x18));
    lv_style_set_border_width(&style_home_list_extra_btns_main_default, 2);
    lv_style_set_border_opa(&style_home_list_extra_btns_main_default, 204);
    lv_style_set_border_side(&style_home_list_extra_btns_main_default, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_text_color(&style_home_list_extra_btns_main_default, lv_color_make(0x0D, 0x30, 0x55));
    lv_style_set_text_font(&style_home_list_extra_btns_main_default, &lv_font_FontAwesome5_40);
    lv_style_set_text_letter_space(&style_home_list_extra_btns_main_default, 0);
    lv_style_set_pad_left(&style_home_list_extra_btns_main_default, 20);
    lv_style_set_pad_right(&style_home_list_extra_btns_main_default, 5);
    lv_style_set_pad_top(&style_home_list_extra_btns_main_default, 20);
    lv_style_set_pad_bottom(&style_home_list_extra_btns_main_default, 5);

    //Set style state: LV_STATE_DEFAULT for style_home_list_extra_texts_main_default
    static lv_style_t style_home_list_extra_texts_main_default;
    ui_init_style(&style_home_list_extra_texts_main_default);
    lv_style_set_radius(&style_home_list_extra_texts_main_default, 3);
    lv_style_set_bg_color(&style_home_list_extra_texts_main_default, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_opa(&style_home_list_extra_texts_main_default, 255);
    lv_style_set_border_width(&style_home_list_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_home_list_extra_texts_main_default, lv_color_make(0x0D, 0x30, 0x55));
    lv_style_set_text_font(&style_home_list_extra_texts_main_default, &lv_font_montserratMedium_40);
    lv_style_set_text_letter_space(&style_home_list_extra_texts_main_default, 0);
    lv_style_set_pad_left(&style_home_list_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_home_list_extra_texts_main_default, 5);
    lv_style_set_pad_top(&style_home_list_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_home_list_extra_texts_main_default, 5);
    lv_obj_set_pos(ui->home_list, 29, 202);
    lv_obj_set_size(ui->home_list, 420, 490);
    lv_obj_set_scrollbar_mode(ui->home_list, LV_SCROLLBAR_MODE_AUTO);

    lv_obj_t *home_list_item;
    home_list_item = lv_list_add_btn(ui->home_list, LV_SYMBOL_SETTINGS, "KEY");
    ui->home_list_item0 = home_list_item;
    lv_obj_add_style(home_list_item, &style_home_list_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    home_list_item = lv_list_add_btn(ui->home_list, LV_SYMBOL_VIDEO, "Camera ");
    ui->home_list_item1 = home_list_item;
    lv_obj_add_style(home_list_item, &style_home_list_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    home_list_item = lv_list_add_btn(ui->home_list, LV_SYMBOL_AUDIO, "AUDIO");
    ui->home_list_item2 = home_list_item;
    lv_obj_add_style(home_list_item, &style_home_list_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    home_list_item = lv_list_add_btn(ui->home_list, LV_SYMBOL_WIFI, "WIFI");
    ui->home_list_item3 = home_list_item;
    lv_obj_add_style(home_list_item, &style_home_list_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    home_list_item = lv_list_add_btn(ui->home_list, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    ui->home_list_item4 = home_list_item;
    lv_obj_add_style(home_list_item, &style_home_list_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    home_list_item = lv_list_add_btn(ui->home_list, LV_SYMBOL_FILE, "SD Card");
    ui->home_list_item5 = home_list_item;
    lv_obj_add_style(home_list_item, &style_home_list_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_title
    ui->home_title = lv_label_create(ui->home);
    lv_label_set_text(ui->home_title, "Board Hardware Verification");
    lv_label_set_long_mode(ui->home_title, LV_LABEL_LONG_WRAP);

    //Set style for home_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->home_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_title, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->home_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->home_title, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_title, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_title, 4, 0);
    lv_obj_set_size(ui->home_title, 472, 117);
    lv_obj_set_scrollbar_mode(ui->home_title, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->home);
    ui->home_del = false;

    //Init events for screen
    events_init_home(ui);
    return ui->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui->home_del = true;
}

/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"


lv_obj_t *setup_scr_language(lv_ui *ui)
{
    //Write codes language
    ui->language = lv_obj_create(NULL);

    //Set style for language. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->language, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->language, lv_color_make(0xFF, 0x6A, 0x6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->language, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->language, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->language, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->language, LV_SCROLLBAR_MODE_OFF);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes language_btn_return
    ui->language_btn_return = lv_btn_create(ui->language);

    const lv_font_t *language_btn_return_font = _font("return_language");
    if (language_btn_return_font == NULL) {
        language_btn_return_font = &lv_font_FangZhengKaiTiJianTi_1_32;
    }

    //Set style for language_btn_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->language_btn_return, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->language_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->language_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->language_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->language_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->language_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->language_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->language_btn_return, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->language_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->language_btn_return, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->language_btn_return, language_btn_return_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->language_btn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->language_btn_return, 11, 20);
    lv_obj_set_size(ui->language_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui->language_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->language_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->language_btn_return_label = lv_label_create(ui->language_btn_return);
    lv_label_set_text(ui->language_btn_return_label, _("return_language"));
    lv_obj_set_style_pad_all(ui->language_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->language_btn_return_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes language_list_language
    ui->language_list_language = lv_list_create(ui->language);

    //Set style for language_list_language. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->language_list_language, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->language_list_language, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->language_list_language, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->language_list_language, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->language_list_language, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->language_list_language, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->language_list_language, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->language_list_language, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->language_list_language, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for language_list_language. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->language_list_language, 10, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->language_list_language, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->language_list_language, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->language_list_language, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->language_list_language, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->language_list_language, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->language_list_language, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->language_list_language, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->language_list_language, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_left(ui->language_list_language, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_right(ui->language_list_language, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_top(ui->language_list_language, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_bottom(ui->language_list_language, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for language_list_language. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->language_list_language, 3, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->language_list_language, lv_color_make(0xff, 0xff, 0xff), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->language_list_language, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_language_list_language_extra_btns_main_default
    static lv_style_t style_language_list_language_extra_btns_main_default;
    ui_init_style(&style_language_list_language_extra_btns_main_default);
    lv_style_set_radius(&style_language_list_language_extra_btns_main_default, 4);
    lv_style_set_bg_color(&style_language_list_language_extra_btns_main_default, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_opa(&style_language_list_language_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_language_list_language_extra_btns_main_default, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_border_width(&style_language_list_language_extra_btns_main_default, 1);
    lv_style_set_border_opa(&style_language_list_language_extra_btns_main_default, 0);
    lv_style_set_border_side(&style_language_list_language_extra_btns_main_default, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_language_list_language_extra_btns_main_default, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_language_list_language_extra_btns_main_default, &lv_font_FangZhengKaiTiJianTi_1_22);
    lv_style_set_pad_left(&style_language_list_language_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_language_list_language_extra_btns_main_default, 5);
    lv_style_set_pad_top(&style_language_list_language_extra_btns_main_default, 20);
    lv_style_set_pad_bottom(&style_language_list_language_extra_btns_main_default, 20);

    //Set style state: LV_STATE_PRESSED for style_language_list_language_extra_btns_main_pressed
    static lv_style_t style_language_list_language_extra_btns_main_pressed;
    ui_init_style(&style_language_list_language_extra_btns_main_pressed);
    lv_style_set_radius(&style_language_list_language_extra_btns_main_pressed, 4);
    lv_style_set_bg_color(&style_language_list_language_extra_btns_main_pressed, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_bg_opa(&style_language_list_language_extra_btns_main_pressed, 26);
    lv_style_set_border_color(&style_language_list_language_extra_btns_main_pressed, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&style_language_list_language_extra_btns_main_pressed, 1);
    lv_style_set_border_opa(&style_language_list_language_extra_btns_main_pressed, 0);
    lv_style_set_border_side(&style_language_list_language_extra_btns_main_pressed, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_language_list_language_extra_btns_main_pressed, lv_color_make(0x1B, 0x72, 0xCF));
    lv_style_set_text_font(&style_language_list_language_extra_btns_main_pressed, &lv_font_simsun_22);
    lv_style_set_pad_left(&style_language_list_language_extra_btns_main_pressed, 5);
    lv_style_set_pad_right(&style_language_list_language_extra_btns_main_pressed, 5);
    lv_style_set_pad_top(&style_language_list_language_extra_btns_main_pressed, 20);
    lv_style_set_pad_bottom(&style_language_list_language_extra_btns_main_pressed, 20);

    //Set style state: LV_STATE_FOCUSED for style_language_list_language_extra_btns_main_focused
    static lv_style_t style_language_list_language_extra_btns_main_focused;
    ui_init_style(&style_language_list_language_extra_btns_main_focused);
    lv_style_set_radius(&style_language_list_language_extra_btns_main_focused, 4);
    lv_style_set_bg_color(&style_language_list_language_extra_btns_main_focused, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_bg_opa(&style_language_list_language_extra_btns_main_focused, 13);
    lv_style_set_border_color(&style_language_list_language_extra_btns_main_focused, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&style_language_list_language_extra_btns_main_focused, 1);
    lv_style_set_border_opa(&style_language_list_language_extra_btns_main_focused, 0);
    lv_style_set_border_side(&style_language_list_language_extra_btns_main_focused, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_language_list_language_extra_btns_main_focused, lv_color_make(0x1B, 0x72, 0xCF));
    lv_style_set_text_font(&style_language_list_language_extra_btns_main_focused, &lv_font_simsun_22);
    lv_style_set_pad_left(&style_language_list_language_extra_btns_main_focused, 5);
    lv_style_set_pad_right(&style_language_list_language_extra_btns_main_focused, 5);
    lv_style_set_pad_top(&style_language_list_language_extra_btns_main_focused, 20);
    lv_style_set_pad_bottom(&style_language_list_language_extra_btns_main_focused, 20);

    //Set style state: LV_STATE_DEFAULT for style_language_list_language_extra_texts_main_default
    static lv_style_t style_language_list_language_extra_texts_main_default;
    ui_init_style(&style_language_list_language_extra_texts_main_default);
    lv_style_set_radius(&style_language_list_language_extra_texts_main_default, 3);
    lv_style_set_bg_color(&style_language_list_language_extra_texts_main_default, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_bg_opa(&style_language_list_language_extra_texts_main_default, 255);
    lv_style_set_border_width(&style_language_list_language_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_language_list_language_extra_texts_main_default, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_language_list_language_extra_texts_main_default, &lv_font_FangZhengKaiTiJianTi_1_22);
    lv_style_set_pad_left(&style_language_list_language_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_language_list_language_extra_texts_main_default, 10);
    lv_style_set_pad_top(&style_language_list_language_extra_texts_main_default, 25);
    lv_style_set_pad_bottom(&style_language_list_language_extra_texts_main_default, 5);
    lv_obj_set_pos(ui->language_list_language, 6, 266);
    lv_obj_set_size(ui->language_list_language, 465, 210);
    lv_obj_set_scrollbar_mode(ui->language_list_language, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->language_list_language, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->language_list_language, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *language_list_language_item;
    language_list_language_item = lv_list_add_btn(ui->language_list_language, NULL, "   <  返回");
    ui->language_list_language_item0 = language_list_language_item;
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    language_list_language_item = lv_list_add_btn(ui->language_list_language, NULL, "     中文                                         设置");
    ui->language_list_language_item1 = language_list_language_item;
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    language_list_language_item = lv_list_add_btn(ui->language_list_language, NULL, "     英文                                         设置");
    ui->language_list_language_item2 = language_list_language_item;
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_update_layout(ui->language);
    ui->language_del = false;

    //Init events for screen
    events_init_language(ui);
    return ui->language;
}
void unload_scr_language(lv_ui *ui)
{
    ui->language_del = true;
}

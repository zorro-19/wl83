/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"


lv_obj_t *setup_scr_syscfg(lv_ui *ui)
{
    //Write codes syscfg
    ui->syscfg = lv_obj_create(NULL);

    //Set style for syscfg. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->syscfg, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->syscfg, lv_color_make(0xFF, 0x6A, 0x6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->syscfg, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->syscfg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->syscfg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->syscfg, LV_SCROLLBAR_MODE_OFF);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes syscfg_btn_return
    ui->syscfg_btn_return = lv_btn_create(ui->syscfg);

    const lv_font_t *syscfg_btn_return_font = _font("return_sysset");
    if (syscfg_btn_return_font == NULL) {
        syscfg_btn_return_font = &lv_font_FangZhengKaiTiJianTi_1_32;
    }

    //Set style for syscfg_btn_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->syscfg_btn_return, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->syscfg_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->syscfg_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->syscfg_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->syscfg_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->syscfg_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->syscfg_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->syscfg_btn_return, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->syscfg_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->syscfg_btn_return, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->syscfg_btn_return, syscfg_btn_return_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->syscfg_btn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->syscfg_btn_return, 11, 20);
    lv_obj_set_size(ui->syscfg_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui->syscfg_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->syscfg_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->syscfg_btn_return_label = lv_label_create(ui->syscfg_btn_return);
    lv_label_set_text(ui->syscfg_btn_return_label, _("return_sysset"));
    lv_obj_set_style_pad_all(ui->syscfg_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->syscfg_btn_return_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes syscfg_list_sysset
    ui->syscfg_list_sysset = lv_list_create(ui->syscfg);

    //Set style for syscfg_list_sysset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->syscfg_list_sysset, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->syscfg_list_sysset, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->syscfg_list_sysset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->syscfg_list_sysset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->syscfg_list_sysset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->syscfg_list_sysset, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->syscfg_list_sysset, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->syscfg_list_sysset, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->syscfg_list_sysset, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for syscfg_list_sysset. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->syscfg_list_sysset, 10, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->syscfg_list_sysset, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->syscfg_list_sysset, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->syscfg_list_sysset, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->syscfg_list_sysset, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->syscfg_list_sysset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->syscfg_list_sysset, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->syscfg_list_sysset, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->syscfg_list_sysset, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_left(ui->syscfg_list_sysset, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_right(ui->syscfg_list_sysset, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_top(ui->syscfg_list_sysset, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_bottom(ui->syscfg_list_sysset, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for syscfg_list_sysset. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->syscfg_list_sysset, 3, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->syscfg_list_sysset, lv_color_make(0xff, 0xff, 0xff), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->syscfg_list_sysset, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_syscfg_list_sysset_extra_btns_main_default
    static lv_style_t style_syscfg_list_sysset_extra_btns_main_default;
    ui_init_style(&style_syscfg_list_sysset_extra_btns_main_default);
    lv_style_set_radius(&style_syscfg_list_sysset_extra_btns_main_default, 4);
    lv_style_set_bg_color(&style_syscfg_list_sysset_extra_btns_main_default, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_opa(&style_syscfg_list_sysset_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_syscfg_list_sysset_extra_btns_main_default, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_border_width(&style_syscfg_list_sysset_extra_btns_main_default, 1);
    lv_style_set_border_opa(&style_syscfg_list_sysset_extra_btns_main_default, 0);
    lv_style_set_border_side(&style_syscfg_list_sysset_extra_btns_main_default, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_syscfg_list_sysset_extra_btns_main_default, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_syscfg_list_sysset_extra_btns_main_default, &lv_font_FangZhengKaiTiJianTi_1_22);
    lv_style_set_pad_left(&style_syscfg_list_sysset_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_syscfg_list_sysset_extra_btns_main_default, 5);
    lv_style_set_pad_top(&style_syscfg_list_sysset_extra_btns_main_default, 20);
    lv_style_set_pad_bottom(&style_syscfg_list_sysset_extra_btns_main_default, 20);

    //Set style state: LV_STATE_PRESSED for style_syscfg_list_sysset_extra_btns_main_pressed
    static lv_style_t style_syscfg_list_sysset_extra_btns_main_pressed;
    ui_init_style(&style_syscfg_list_sysset_extra_btns_main_pressed);
    lv_style_set_radius(&style_syscfg_list_sysset_extra_btns_main_pressed, 4);
    lv_style_set_bg_color(&style_syscfg_list_sysset_extra_btns_main_pressed, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_bg_opa(&style_syscfg_list_sysset_extra_btns_main_pressed, 26);
    lv_style_set_border_color(&style_syscfg_list_sysset_extra_btns_main_pressed, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&style_syscfg_list_sysset_extra_btns_main_pressed, 1);
    lv_style_set_border_opa(&style_syscfg_list_sysset_extra_btns_main_pressed, 0);
    lv_style_set_border_side(&style_syscfg_list_sysset_extra_btns_main_pressed, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_syscfg_list_sysset_extra_btns_main_pressed, lv_color_make(0x1B, 0x72, 0xCF));
    lv_style_set_text_font(&style_syscfg_list_sysset_extra_btns_main_pressed, &lv_font_simsun_22);
    lv_style_set_pad_left(&style_syscfg_list_sysset_extra_btns_main_pressed, 5);
    lv_style_set_pad_right(&style_syscfg_list_sysset_extra_btns_main_pressed, 5);
    lv_style_set_pad_top(&style_syscfg_list_sysset_extra_btns_main_pressed, 20);
    lv_style_set_pad_bottom(&style_syscfg_list_sysset_extra_btns_main_pressed, 20);

    //Set style state: LV_STATE_FOCUSED for style_syscfg_list_sysset_extra_btns_main_focused
    static lv_style_t style_syscfg_list_sysset_extra_btns_main_focused;
    ui_init_style(&style_syscfg_list_sysset_extra_btns_main_focused);
    lv_style_set_radius(&style_syscfg_list_sysset_extra_btns_main_focused, 4);
    lv_style_set_bg_color(&style_syscfg_list_sysset_extra_btns_main_focused, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_bg_opa(&style_syscfg_list_sysset_extra_btns_main_focused, 13);
    lv_style_set_border_color(&style_syscfg_list_sysset_extra_btns_main_focused, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&style_syscfg_list_sysset_extra_btns_main_focused, 1);
    lv_style_set_border_opa(&style_syscfg_list_sysset_extra_btns_main_focused, 0);
    lv_style_set_border_side(&style_syscfg_list_sysset_extra_btns_main_focused, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_syscfg_list_sysset_extra_btns_main_focused, lv_color_make(0x1B, 0x72, 0xCF));
    lv_style_set_text_font(&style_syscfg_list_sysset_extra_btns_main_focused, &lv_font_simsun_22);
    lv_style_set_pad_left(&style_syscfg_list_sysset_extra_btns_main_focused, 5);
    lv_style_set_pad_right(&style_syscfg_list_sysset_extra_btns_main_focused, 5);
    lv_style_set_pad_top(&style_syscfg_list_sysset_extra_btns_main_focused, 20);
    lv_style_set_pad_bottom(&style_syscfg_list_sysset_extra_btns_main_focused, 20);

    //Set style state: LV_STATE_DEFAULT for style_syscfg_list_sysset_extra_texts_main_default
    static lv_style_t style_syscfg_list_sysset_extra_texts_main_default;
    ui_init_style(&style_syscfg_list_sysset_extra_texts_main_default);
    lv_style_set_radius(&style_syscfg_list_sysset_extra_texts_main_default, 3);
    lv_style_set_bg_color(&style_syscfg_list_sysset_extra_texts_main_default, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_bg_opa(&style_syscfg_list_sysset_extra_texts_main_default, 255);
    lv_style_set_border_width(&style_syscfg_list_sysset_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_syscfg_list_sysset_extra_texts_main_default, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_syscfg_list_sysset_extra_texts_main_default, &lv_font_FangZhengKaiTiJianTi_1_22);
    lv_style_set_pad_left(&style_syscfg_list_sysset_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_syscfg_list_sysset_extra_texts_main_default, 10);
    lv_style_set_pad_top(&style_syscfg_list_sysset_extra_texts_main_default, 25);
    lv_style_set_pad_bottom(&style_syscfg_list_sysset_extra_texts_main_default, 5);
    lv_obj_set_pos(ui->syscfg_list_sysset, 7, 284);
    lv_obj_set_size(ui->syscfg_list_sysset, 466, 212);
    lv_obj_set_scrollbar_mode(ui->syscfg_list_sysset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->syscfg_list_sysset, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->syscfg_list_sysset, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *syscfg_list_sysset_item;
    syscfg_list_sysset_item = lv_list_add_btn(ui->syscfg_list_sysset, NULL, " <  返回");
    ui->syscfg_list_sysset_item0 = syscfg_list_sysset_item;
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    syscfg_list_sysset_item = lv_list_add_btn(ui->syscfg_list_sysset, NULL, "   休眠时长                                    永不");
    ui->syscfg_list_sysset_item1 = syscfg_list_sysset_item;
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    syscfg_list_sysset_item = lv_list_add_btn(ui->syscfg_list_sysset, NULL, "   天气显示                                     开");
    ui->syscfg_list_sysset_item2 = syscfg_list_sysset_item;
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_update_layout(ui->syscfg);
    ui->syscfg_del = false;

    //Init events for screen
    events_init_syscfg(ui);
    return ui->syscfg;
}
void unload_scr_syscfg(lv_ui *ui)
{
    ui->syscfg_del = true;
}

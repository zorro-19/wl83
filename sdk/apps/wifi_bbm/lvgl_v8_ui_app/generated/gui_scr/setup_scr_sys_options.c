/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_sys_options(lv_ui *ui)
{
    lv_ui_sys_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_sys_options));
        memset(ui_scr, 0, sizeof(lv_ui_sys_options));
        ui->sys_options = ui_scr;
    }
    if (lv_obj_is_valid(ui_scr->sys_options)) {
        lv_obj_del(ui_scr->sys_options);
    }
    //Write codes sys_options
    ui_scr->sys_options = lv_obj_create(lv_layer_top());
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_options. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_options, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_options, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_scr->sys_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_scr->sys_options, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->sys_options, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_options_view_1
    ui_scr->sys_options_view_1 = lv_obj_create(ui_scr->sys_options);

    //Set style for sys_options_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_options_view_1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_options_view_1, lv_color_make(0x33, 0x30, 0x30), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_options_view_1, 217, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->sys_options_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->sys_options_view_1, lv_color_make(0x02, 0x6C, 0xC0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->sys_options_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->sys_options_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->sys_options_view_1, 227, 114);
    lv_obj_set_size(ui_scr->sys_options_view_1, 345, 218);
    lv_obj_set_scrollbar_mode(ui_scr->sys_options_view_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_options_view_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_options_lbl_1
    ui_scr->sys_options_lbl_1 = lv_label_create(ui_scr->sys_options_view_1);
    lv_label_set_text(ui_scr->sys_options_lbl_1, "Are you sure you want to delete these files?");
    lv_label_set_long_mode(ui_scr->sys_options_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_options_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_options_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->sys_options_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->sys_options_lbl_1, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_scr->sys_options_lbl_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_scr->sys_options_lbl_1, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->sys_options_lbl_1, 0, 5);
    lv_obj_set_size(ui_scr->sys_options_lbl_1, 338, 136);
    lv_obj_set_scrollbar_mode(ui_scr->sys_options_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_options_lbl_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_options_btn_1
    ui_scr->sys_options_btn_1 = lv_btn_create(ui_scr->sys_options_view_1);

    //Set style for sys_options_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_options_btn_1, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_options_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->sys_options_btn_1, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->sys_options_btn_1, 28, 150);
    lv_obj_set_size(ui_scr->sys_options_btn_1, 80, 50);
    lv_obj_set_scrollbar_mode(ui_scr->sys_options_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_remove_obj(ui_scr->sys_options_btn_1);
    ui_scr->sys_options_btn_1_label = lv_label_create(ui_scr->sys_options_btn_1);
    lv_label_set_text(ui_scr->sys_options_btn_1_label, "Yes");
    lv_obj_set_style_pad_all(ui_scr->sys_options_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_options_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_options_btn_2
    ui_scr->sys_options_btn_2 = lv_btn_create(ui_scr->sys_options_view_1);

    //Set style for sys_options_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_options_btn_2, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_options_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->sys_options_btn_2, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->sys_options_btn_2, 233, 150);
    lv_obj_set_size(ui_scr->sys_options_btn_2, 80, 50);
    lv_obj_set_scrollbar_mode(ui_scr->sys_options_btn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_remove_obj(ui_scr->sys_options_btn_2);
    ui_scr->sys_options_btn_2_label = lv_label_create(ui_scr->sys_options_btn_2);
    lv_label_set_text(ui_scr->sys_options_btn_2_label, "No");
    lv_obj_set_style_pad_all(ui_scr->sys_options_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_options_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui_scr->sys_options);
    ui_scr->sys_options_del = false;

    //Init events for screen
    events_init_sys_options(ui);
    return ui_scr->sys_options;
}
void unload_scr_sys_options(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_SYS_OPTIONS);
}

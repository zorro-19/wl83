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


lv_obj_t *setup_scr_pair_options(lv_ui *ui)
{
    lv_ui_pair_options *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_OPTIONS);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_pair_options));
        memset(ui_scr, 0, sizeof(lv_ui_pair_options));
        ui->pair_options = ui_scr;
    }
    //Write codes pair_options
    ui_scr->pair_options = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for pair_options. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_options, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->pair_options, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->pair_options, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_options_imgbtn_1
    ui_scr->pair_options_imgbtn_1 = lv_imgbtn_create(ui_scr->pair_options);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_options_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->pair_options_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_options_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->pair_options_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_scr->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->pair_options_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->pair_options_imgbtn_1, 185, 173);
    lv_obj_set_size(ui_scr->pair_options_imgbtn_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_options_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->pair_options_imgbtn_1);
    lv_imgbtn_set_src(ui_scr->pair_options_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_PAIR_OPT_PAIR_PNG), NULL);
    lv_obj_add_flag(ui_scr->pair_options_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->pair_options_imgbtn_1_label = lv_label_create(ui_scr->pair_options_imgbtn_1);
    lv_label_set_text(ui_scr->pair_options_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->pair_options_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->pair_options_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes pair_options_imgbtn_2
    ui_scr->pair_options_imgbtn_2 = lv_imgbtn_create(ui_scr->pair_options);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_options_imgbtn_2, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->pair_options_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_options_imgbtn_2, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->pair_options_imgbtn_2, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_scr->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->pair_options_imgbtn_2, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->pair_options_imgbtn_2, 489, 173);
    lv_obj_set_size(ui_scr->pair_options_imgbtn_2, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_options_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->pair_options_imgbtn_2);
    lv_imgbtn_set_src(ui_scr->pair_options_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_PAIR_OPT_UNPAIR_PNG), NULL);
    lv_obj_add_flag(ui_scr->pair_options_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->pair_options_imgbtn_2_label = lv_label_create(ui_scr->pair_options_imgbtn_2);
    lv_label_set_text(ui_scr->pair_options_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->pair_options_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->pair_options_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes pair_options_lbl_1
    ui_scr->pair_options_lbl_1 = lv_label_create(ui_scr->pair_options);
    lv_label_set_text(ui_scr->pair_options_lbl_1, "Go to pairing");
    lv_label_set_long_mode(ui_scr->pair_options_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for pair_options_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_options_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_options_lbl_1, 170, 306);
    lv_obj_set_size(ui_scr->pair_options_lbl_1, 164, 38);
    lv_obj_set_scrollbar_mode(ui_scr->pair_options_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_options_lbl_2
    ui_scr->pair_options_lbl_2 = lv_label_create(ui_scr->pair_options);
    lv_label_set_text(ui_scr->pair_options_lbl_2, "Go to unpair");
    lv_label_set_long_mode(ui_scr->pair_options_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for pair_options_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_options_lbl_2, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_options_lbl_2, 489, 306);
    lv_obj_set_size(ui_scr->pair_options_lbl_2, 141, 27);
    lv_obj_set_scrollbar_mode(ui_scr->pair_options_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_options_imgbtn_4
    ui_scr->pair_options_imgbtn_4 = lv_imgbtn_create(ui_scr->pair_options);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_options_imgbtn_4, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_options_imgbtn_4, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->pair_options_imgbtn_4, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->pair_options_imgbtn_4, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->pair_options_imgbtn_4, 25, 22);
    lv_obj_set_size(ui_scr->pair_options_imgbtn_4, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->pair_options_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->pair_options_imgbtn_4);
    lv_imgbtn_set_src(ui_scr->pair_options_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->pair_options_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->pair_options_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->pair_options_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_obj_add_flag(ui_scr->pair_options_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->pair_options_imgbtn_4_label = lv_label_create(ui_scr->pair_options_imgbtn_4);
    lv_label_set_text(ui_scr->pair_options_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui_scr->pair_options_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->pair_options_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui_scr->pair_options);
    ui_scr->pair_options_del = false;

    //Init events for screen
    events_init_pair_options(ui);
    return ui_scr->pair_options;
}
void unload_scr_pair_options(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_PAIR_OPTIONS);
}

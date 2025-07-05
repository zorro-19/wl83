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


lv_obj_t *setup_scr_file_browser(lv_ui *ui)
{
    lv_ui_file_browser *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_file_browser));
        memset(ui_scr, 0, sizeof(lv_ui_file_browser));
        ui->file_browser = ui_scr;
    }
    //Write codes file_browser
    ui_scr->file_browser = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for file_browser. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_view_2
    ui_scr->file_browser_view_2 = lv_obj_create(ui_scr->file_browser);

    //Set style for file_browser_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_view_2, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_view_2, 20, 0);
    lv_obj_set_size(ui_scr->file_browser_view_2, 80, 480);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_view_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_imgbtn_1
    ui_scr->file_browser_imgbtn_1 = lv_imgbtn_create(ui_scr->file_browser_view_2);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->file_browser_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->file_browser_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->file_browser_imgbtn_1, 8, 30);
    lv_obj_set_size(ui_scr->file_browser_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_imgbtn_1);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_obj_add_flag(ui_scr->file_browser_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->file_browser_imgbtn_1_label = lv_label_create(ui_scr->file_browser_imgbtn_1);
    lv_label_set_text(ui_scr->file_browser_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->file_browser_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->file_browser_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_imgbtn_2
    ui_scr->file_browser_imgbtn_2 = lv_imgbtn_create(ui_scr->file_browser_view_2);

    //Set style for file_browser_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_imgbtn_2, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_imgbtn_2, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_imgbtn_2, 8, 140);
    lv_obj_set_size(ui_scr->file_browser_imgbtn_2, 64, 63);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_imgbtn_2);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_UP_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_UP_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_UP_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_UP_PNG), NULL);
    lv_obj_add_flag(ui_scr->file_browser_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->file_browser_imgbtn_2_label = lv_label_create(ui_scr->file_browser_imgbtn_2);
    lv_label_set_text(ui_scr->file_browser_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->file_browser_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->file_browser_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_imgbtn_3
    ui_scr->file_browser_imgbtn_3 = lv_imgbtn_create(ui_scr->file_browser_view_2);

    //Set style for file_browser_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_imgbtn_3, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_imgbtn_3, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_imgbtn_3, 8, 300);
    lv_obj_set_size(ui_scr->file_browser_imgbtn_3, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_imgbtn_3);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_DOWN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_DOWN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_DOWN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_DOWN_PNG), NULL);
    lv_obj_add_flag(ui_scr->file_browser_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->file_browser_imgbtn_3_label = lv_label_create(ui_scr->file_browser_imgbtn_3);
    lv_label_set_text(ui_scr->file_browser_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui_scr->file_browser_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->file_browser_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_lbl_1
    ui_scr->file_browser_lbl_1 = lv_label_create(ui_scr->file_browser_view_2);
    lv_label_set_text(ui_scr->file_browser_lbl_1, "50\n/\n1000");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->file_browser_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_lbl_1, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->file_browser_lbl_1, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_scr->file_browser_lbl_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_1, 8, 217);
    lv_obj_set_size(ui_scr->file_browser_lbl_1, 64, 80);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_imgbtn_4
    ui_scr->file_browser_imgbtn_4 = lv_imgbtn_create(ui_scr->file_browser_view_2);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_imgbtn_4, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->file_browser_imgbtn_4, &gui_imgbtn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_imgbtn_4, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->file_browser_imgbtn_4, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_pos(ui_scr->file_browser_imgbtn_4, 8, 390);
    lv_obj_set_size(ui_scr->file_browser_imgbtn_4, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_imgbtn_4);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_DELETE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_DELETE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_DELETE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->file_browser_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_DELETE_PNG), NULL);
    lv_obj_add_flag(ui_scr->file_browser_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->file_browser_imgbtn_4_label = lv_label_create(ui_scr->file_browser_imgbtn_4);
    lv_label_set_text(ui_scr->file_browser_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui_scr->file_browser_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->file_browser_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_browser_cont
    ui_scr->file_browser_browser_cont = lv_obj_create(ui_scr->file_browser);

    //Set style for file_browser_browser_cont. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_browser_cont, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->file_browser_browser_cont, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->file_browser_browser_cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_browser_cont, 104, 30);
    lv_obj_set_size(ui_scr->file_browser_browser_cont, 660, 435);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_browser_cont, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_file_cont1
    ui_scr->file_browser_file_cont1 = lv_obj_create(ui_scr->file_browser_browser_cont);

    //Set style for file_browser_file_cont1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_file_cont1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->file_browser_file_cont1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_file_cont1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_file_cont1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui_scr->file_browser_file_cont1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui_scr->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_file_cont1, 20, 10);
    lv_obj_set_size(ui_scr->file_browser_file_cont1, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_file_cont1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_file_cont1);
    //Write codes file_browser_img_1
    ui_scr->file_browser_img_1 = lv_img_create(ui_scr->file_browser_file_cont1);

    //Set style for file_browser_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_img_1, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->file_browser_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_img_1, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_img_1, 5, 0);
    lv_obj_set_size(ui_scr->file_browser_img_1, 192, 160);
    lv_obj_add_flag(ui_scr->file_browser_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_2
    ui_scr->file_browser_lbl_2 = lv_label_create(ui_scr->file_browser_file_cont1);
    lv_label_set_text(ui_scr->file_browser_lbl_2, "VID_0001.AVI");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_2, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_2, 4, 161);
    lv_obj_set_size(ui_scr->file_browser_lbl_2, 192, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_1
    ui_scr->file_browser_cb_1 = lv_checkbox_create(ui_scr->file_browser_file_cont1);
    lv_checkbox_set_text(ui_scr->file_browser_cb_1, "checkbox");

    //Set style for file_browser_cb_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_cb_1, &gui_cb_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_cb_1, &gui_cb_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_cb_1, 163, 4);
    lv_obj_set_size(ui_scr->file_browser_cb_1, 30, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_cb_1, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_1
    lv_obj_add_flag(ui_scr->file_browser_cb_1, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont2
    ui_scr->file_browser_file_cont2 = lv_obj_create(ui_scr->file_browser_browser_cont);

    //Set style for file_browser_file_cont2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_file_cont2, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->file_browser_file_cont2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_file_cont2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_file_cont2, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_radius(ui_scr->file_browser_file_cont2, -1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui_scr->file_browser_file_cont2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui_scr->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_file_cont2, 230, 10);
    lv_obj_set_size(ui_scr->file_browser_file_cont2, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_file_cont2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_file_cont2);
    //Write codes file_browser_img_2
    ui_scr->file_browser_img_2 = lv_img_create(ui_scr->file_browser_file_cont2);

    //Set style for file_browser_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_img_2, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->file_browser_img_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_img_2, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_img_2, 4, 0);
    lv_obj_set_size(ui_scr->file_browser_img_2, 192, 160);
    lv_obj_add_flag(ui_scr->file_browser_img_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_3
    ui_scr->file_browser_lbl_3 = lv_label_create(ui_scr->file_browser_file_cont2);
    lv_label_set_text(ui_scr->file_browser_lbl_3, "VID_0001.AVI");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_3, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_3, 4, 161);
    lv_obj_set_size(ui_scr->file_browser_lbl_3, 192, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_2
    ui_scr->file_browser_cb_2 = lv_checkbox_create(ui_scr->file_browser_file_cont2);
    lv_checkbox_set_text(ui_scr->file_browser_cb_2, "checkbox");

    //Set style for file_browser_cb_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_cb_2, &gui_cb_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_cb_2, &gui_cb_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_cb_2, 163, 4);
    lv_obj_set_size(ui_scr->file_browser_cb_2, 30, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_cb_2, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_2
    lv_obj_add_flag(ui_scr->file_browser_cb_2, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont3
    ui_scr->file_browser_file_cont3 = lv_obj_create(ui_scr->file_browser_browser_cont);

    //Set style for file_browser_file_cont3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_file_cont3, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->file_browser_file_cont3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_file_cont3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_file_cont3, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_file_cont3, 440, 10);
    lv_obj_set_size(ui_scr->file_browser_file_cont3, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_file_cont3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_file_cont3);
    //Write codes file_browser_img_3
    ui_scr->file_browser_img_3 = lv_img_create(ui_scr->file_browser_file_cont3);

    //Set style for file_browser_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_img_3, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->file_browser_img_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_img_3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_img_3, 4, 0);
    lv_obj_set_size(ui_scr->file_browser_img_3, 192, 160);
    lv_obj_add_flag(ui_scr->file_browser_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_4
    ui_scr->file_browser_lbl_4 = lv_label_create(ui_scr->file_browser_file_cont3);
    lv_label_set_text(ui_scr->file_browser_lbl_4, "VID_0001.AVI");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_4, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_4, 4, 161);
    lv_obj_set_size(ui_scr->file_browser_lbl_4, 192, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_3
    ui_scr->file_browser_cb_3 = lv_checkbox_create(ui_scr->file_browser_file_cont3);
    lv_checkbox_set_text(ui_scr->file_browser_cb_3, "checkbox");

    //Set style for file_browser_cb_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_cb_3, &gui_cb_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_cb_3, &gui_cb_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_cb_3, 163, 4);
    lv_obj_set_size(ui_scr->file_browser_cb_3, 30, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_cb_3, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_3
    lv_obj_add_flag(ui_scr->file_browser_cb_3, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont4
    ui_scr->file_browser_file_cont4 = lv_obj_create(ui_scr->file_browser_browser_cont);

    //Set style for file_browser_file_cont4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_file_cont4, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->file_browser_file_cont4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_file_cont4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_file_cont4, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_file_cont4, 20, 220);
    lv_obj_set_size(ui_scr->file_browser_file_cont4, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_file_cont4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_file_cont4);
    //Write codes file_browser_img_4
    ui_scr->file_browser_img_4 = lv_img_create(ui_scr->file_browser_file_cont4);

    //Set style for file_browser_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_img_4, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->file_browser_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_img_4, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_img_4, 4, 0);
    lv_obj_set_size(ui_scr->file_browser_img_4, 192, 160);
    lv_obj_add_flag(ui_scr->file_browser_img_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_5
    ui_scr->file_browser_lbl_5 = lv_label_create(ui_scr->file_browser_file_cont4);
    lv_label_set_text(ui_scr->file_browser_lbl_5, "VID_0001.AVI");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_5, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_5, 4, 161);
    lv_obj_set_size(ui_scr->file_browser_lbl_5, 192, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_4
    ui_scr->file_browser_cb_4 = lv_checkbox_create(ui_scr->file_browser_file_cont4);
    lv_checkbox_set_text(ui_scr->file_browser_cb_4, "checkbox");

    //Set style for file_browser_cb_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_cb_4, &gui_cb_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_cb_4, &gui_cb_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_cb_4, 163, 4);
    lv_obj_set_size(ui_scr->file_browser_cb_4, 30, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_cb_4, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_4
    lv_obj_add_flag(ui_scr->file_browser_cb_4, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont5
    ui_scr->file_browser_file_cont5 = lv_obj_create(ui_scr->file_browser_browser_cont);

    //Set style for file_browser_file_cont5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_file_cont5, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->file_browser_file_cont5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_file_cont5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_file_cont5, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_file_cont5, 230, 220);
    lv_obj_set_size(ui_scr->file_browser_file_cont5, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_file_cont5, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_file_cont5);
    //Write codes file_browser_img_5
    ui_scr->file_browser_img_5 = lv_img_create(ui_scr->file_browser_file_cont5);

    //Set style for file_browser_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_img_5, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->file_browser_img_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_img_5, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_img_5, 4, 0);
    lv_obj_set_size(ui_scr->file_browser_img_5, 192, 160);
    lv_obj_add_flag(ui_scr->file_browser_img_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_6
    ui_scr->file_browser_lbl_6 = lv_label_create(ui_scr->file_browser_file_cont5);
    lv_label_set_text(ui_scr->file_browser_lbl_6, "VID_0001.AVI");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_6, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_6, 4, 161);
    lv_obj_set_size(ui_scr->file_browser_lbl_6, 192, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_5
    ui_scr->file_browser_cb_5 = lv_checkbox_create(ui_scr->file_browser_file_cont5);
    lv_checkbox_set_text(ui_scr->file_browser_cb_5, "checkbox");

    //Set style for file_browser_cb_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_cb_5, &gui_cb_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_cb_5, &gui_cb_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_cb_5, 163, 4);
    lv_obj_set_size(ui_scr->file_browser_cb_5, 30, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_cb_5, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_5
    lv_obj_add_flag(ui_scr->file_browser_cb_5, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont6
    ui_scr->file_browser_file_cont6 = lv_obj_create(ui_scr->file_browser_browser_cont);

    //Set style for file_browser_file_cont6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_file_cont6, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->file_browser_file_cont6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_file_cont6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_file_cont6, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->file_browser_file_cont6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_file_cont6, 440, 220);
    lv_obj_set_size(ui_scr->file_browser_file_cont6, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_file_cont6, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->file_browser_file_cont6);
    //Write codes file_browser_img_6
    ui_scr->file_browser_img_6 = lv_img_create(ui_scr->file_browser_file_cont6);

    //Set style for file_browser_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_img_6, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->file_browser_img_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->file_browser_img_6, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_img_6, 4, 0);
    lv_obj_set_size(ui_scr->file_browser_img_6, 192, 160);
    lv_obj_add_flag(ui_scr->file_browser_img_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_7
    ui_scr->file_browser_lbl_7 = lv_label_create(ui_scr->file_browser_file_cont6);
    lv_label_set_text(ui_scr->file_browser_lbl_7, "VID_0001.AVI");
    lv_label_set_long_mode(ui_scr->file_browser_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_lbl_7, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->file_browser_lbl_7, 4, 161);
    lv_obj_set_size(ui_scr->file_browser_lbl_7, 192, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_lbl_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_6
    ui_scr->file_browser_cb_6 = lv_checkbox_create(ui_scr->file_browser_file_cont6);
    lv_checkbox_set_text(ui_scr->file_browser_cb_6, "checkbox");

    //Set style for file_browser_cb_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->file_browser_cb_6, &gui_cb_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->file_browser_cb_6, &gui_cb_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->file_browser_cb_6, 163, 4);
    lv_obj_set_size(ui_scr->file_browser_cb_6, 30, 30);
    lv_obj_set_scrollbar_mode(ui_scr->file_browser_cb_6, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_6
    lv_obj_add_flag(ui_scr->file_browser_cb_6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_update_layout(ui_scr->file_browser);
    ui_scr->file_browser_del = false;

    //Init events for screen
    events_init_file_browser(ui);
    return ui_scr->file_browser;
}
void unload_scr_file_browser(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_FILE_BROWSER);
}

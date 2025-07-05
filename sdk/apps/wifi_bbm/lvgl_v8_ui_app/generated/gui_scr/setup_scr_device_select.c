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


lv_obj_t *setup_scr_device_select(lv_ui *ui)
{
    lv_ui_device_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DEVICE_SELECT);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_device_select));
        memset(ui_scr, 0, sizeof(lv_ui_device_select));
        ui->device_select = ui_scr;
    }
    //Write codes device_select
    ui_scr->device_select = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for device_select. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->device_select, LV_SCROLLBAR_MODE_OFF);
    //Write codes device_select_view_1
    ui_scr->device_select_view_1 = lv_obj_create(ui_scr->device_select);

    //Set style for device_select_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_view_1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for device_select_view_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->device_select_view_1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->device_select_view_1, 80, 121);
    lv_obj_set_size(ui_scr->device_select_view_1, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->device_select_view_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->device_select_view_1, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->device_select_view_1);
    //Write codes device_select_img_1
    ui_scr->device_select_img_1 = lv_img_create(ui_scr->device_select_view_1);
    lv_img_set_src(ui_scr->device_select_img_1, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->device_select_img_1, 0, 0);
    lv_img_set_angle(ui_scr->device_select_img_1, 0);
    lv_img_set_zoom(ui_scr->device_select_img_1, 256);

    //Set style for device_select_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_img_1, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->device_select_img_1, 16, 0);
    lv_obj_set_size(ui_scr->device_select_img_1, 128, 128);
    lv_obj_add_flag(ui_scr->device_select_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->device_select_img_1, LV_OBJ_FLAG_CLICKABLE);
    //Write codes device_select_lbl_2
    ui_scr->device_select_lbl_2 = lv_label_create(ui_scr->device_select_view_1);
    lv_label_set_text(ui_scr->device_select_lbl_2, "Local");
    lv_label_set_long_mode(ui_scr->device_select_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for device_select_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_lbl_2, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->device_select_lbl_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->device_select_lbl_2, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->device_select_lbl_2, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_scr->device_select_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->device_select_lbl_2, -45, 125);
    lv_obj_set_size(ui_scr->device_select_lbl_2, 253, 52);
    lv_obj_set_scrollbar_mode(ui_scr->device_select_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes device_select_view_2
    ui_scr->device_select_view_2 = lv_obj_create(ui_scr->device_select);

    //Set style for device_select_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_view_2, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for device_select_view_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->device_select_view_2, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->device_select_view_2, 320, 120);
    lv_obj_set_size(ui_scr->device_select_view_2, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->device_select_view_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->device_select_view_2, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->device_select_view_2);
    //Write codes device_select_img_2
    ui_scr->device_select_img_2 = lv_img_create(ui_scr->device_select_view_2);
    lv_img_set_src(ui_scr->device_select_img_2, gui_get_res_path(GUI_RES_REMOTE_PNG));
    lv_img_set_pivot(ui_scr->device_select_img_2, 0, 0);
    lv_img_set_angle(ui_scr->device_select_img_2, 0);
    lv_img_set_zoom(ui_scr->device_select_img_2, 256);

    //Set style for device_select_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_img_2, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->device_select_img_2, 16, 0);
    lv_obj_set_size(ui_scr->device_select_img_2, 128, 128);
    lv_obj_add_flag(ui_scr->device_select_img_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->device_select_img_2, LV_OBJ_FLAG_CLICKABLE);
    //Write codes device_select_lbl_3
    ui_scr->device_select_lbl_3 = lv_label_create(ui_scr->device_select_view_2);
    lv_label_set_text(ui_scr->device_select_lbl_3, "Remote");
    lv_label_set_long_mode(ui_scr->device_select_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for device_select_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_lbl_3, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->device_select_lbl_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->device_select_lbl_3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->device_select_lbl_3, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_scr->device_select_lbl_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->device_select_lbl_3, -45, 125);
    lv_obj_set_size(ui_scr->device_select_lbl_3, 253, 52);
    lv_obj_set_scrollbar_mode(ui_scr->device_select_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes device_select_lbl_1
    ui_scr->device_select_lbl_1 = lv_label_create(ui_scr->device_select);
    lv_label_set_text(ui_scr->device_select_lbl_1, "Select the device to browser");
    lv_label_set_long_mode(ui_scr->device_select_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for device_select_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->device_select_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->device_select_lbl_1, &lv_font_montserratMedium_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->device_select_lbl_1, 120, 36);
    lv_obj_set_size(ui_scr->device_select_lbl_1, 559, 52);
    lv_obj_set_scrollbar_mode(ui_scr->device_select_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes device_select_imgbtn_1
    ui_scr->device_select_imgbtn_1 = lv_imgbtn_create(ui_scr->device_select);

    //Set style for device_select_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->device_select_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for device_select_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->device_select_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for device_select_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->device_select_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for device_select_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->device_select_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->device_select_imgbtn_1, 24, 30);
    lv_obj_set_size(ui_scr->device_select_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->device_select_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->device_select_imgbtn_1);
    lv_imgbtn_set_src(ui_scr->device_select_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->device_select_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->device_select_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->device_select_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_obj_add_flag(ui_scr->device_select_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->device_select_imgbtn_1_label = lv_label_create(ui_scr->device_select_imgbtn_1);
    lv_label_set_text(ui_scr->device_select_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->device_select_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->device_select_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui_scr->device_select);
    ui_scr->device_select_del = false;

    //Init events for screen
    events_init_device_select(ui);
    return ui_scr->device_select;
}
void unload_scr_device_select(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_DEVICE_SELECT);
}

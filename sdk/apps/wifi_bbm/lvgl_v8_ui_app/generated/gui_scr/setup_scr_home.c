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


lv_obj_t *setup_scr_home(lv_ui *ui)
{
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_home));
        memset(ui_scr, 0, sizeof(lv_ui_home));
        ui->home = ui_scr;
    }
    //Write codes home
    ui_scr->home = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for home. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->home, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_scr->home, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->home, LV_SCROLLBAR_MODE_OFF);
    //Write codes home_imgbtn_2
    ui_scr->home_imgbtn_2 = lv_imgbtn_create(ui_scr->home);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->home_imgbtn_2, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_scr->home_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->home_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->home_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->home_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->home_imgbtn_2, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->home_imgbtn_2, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_scr->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->home_imgbtn_2, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->home_imgbtn_2, 107, 175);
    lv_obj_set_size(ui_scr->home_imgbtn_2, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->home_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->home_imgbtn_2);
    lv_imgbtn_set_src(ui_scr->home_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_CAMERA_PNG), NULL);
    lv_obj_add_flag(ui_scr->home_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->home_imgbtn_2_label = lv_label_create(ui_scr->home_imgbtn_2);
    lv_label_set_text(ui_scr->home_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->home_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->home_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_imgbtn_1
    ui_scr->home_imgbtn_1 = lv_imgbtn_create(ui_scr->home);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->home_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_scr->home_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->home_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->home_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->home_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->home_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->home_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_scr->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->home_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->home_imgbtn_1, 336, 175);
    lv_obj_set_size(ui_scr->home_imgbtn_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->home_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->home_imgbtn_1);
    lv_imgbtn_set_src(ui_scr->home_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_LINK_PNG), NULL);
    lv_obj_add_flag(ui_scr->home_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->home_imgbtn_1_label = lv_label_create(ui_scr->home_imgbtn_1);
    lv_label_set_text(ui_scr->home_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->home_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->home_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_imgbtn_3
    ui_scr->home_imgbtn_3 = lv_imgbtn_create(ui_scr->home);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->home_imgbtn_3, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_scr->home_imgbtn_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->home_imgbtn_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->home_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->home_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->home_imgbtn_3, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->home_imgbtn_3, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_scr->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->home_imgbtn_3, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->home_imgbtn_3, 561, 175);
    lv_obj_set_size(ui_scr->home_imgbtn_3, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->home_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->home_imgbtn_3);
    lv_imgbtn_set_src(ui_scr->home_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_DIR_PNG), NULL);
    lv_obj_add_flag(ui_scr->home_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->home_imgbtn_3_label = lv_label_create(ui_scr->home_imgbtn_3);
    lv_label_set_text(ui_scr->home_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui_scr->home_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->home_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui_scr->home);
    ui_scr->home_del = false;

    //Init events for screen
    events_init_home(ui);
    return ui_scr->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_HOME);
}

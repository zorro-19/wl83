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


lv_obj_t *setup_scr_rt_stream(lv_ui *ui)
{
    lv_ui_rt_stream *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RT_STREAM);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_rt_stream));
        memset(ui_scr, 0, sizeof(lv_ui_rt_stream));
        ui->rt_stream = ui_scr;
    }
    //Write codes rt_stream
    ui_scr->rt_stream = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for rt_stream. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->rt_stream, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->rt_stream, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->rt_stream, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->rt_stream);
    //Write codes rt_stream_imgbtn_1
    ui_scr->rt_stream_imgbtn_1 = lv_imgbtn_create(ui_scr->rt_stream);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->rt_stream_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->rt_stream_imgbtn_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->rt_stream_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_opa(ui_scr->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->rt_stream_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->rt_stream_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_scr->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->rt_stream_imgbtn_1, 636, 70);
    lv_obj_set_size(ui_scr->rt_stream_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->rt_stream_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->rt_stream_imgbtn_1);

    //Hidden for widget rt_stream_imgbtn_1
    lv_obj_add_flag(ui_scr->rt_stream_imgbtn_1, LV_OBJ_FLAG_HIDDEN);
    lv_imgbtn_set_src(ui_scr->rt_stream_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->rt_stream_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->rt_stream_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->rt_stream_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_obj_add_flag(ui_scr->rt_stream_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->rt_stream_imgbtn_1_label = lv_label_create(ui_scr->rt_stream_imgbtn_1);
    lv_label_set_text(ui_scr->rt_stream_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->rt_stream_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->rt_stream_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes rt_stream_lbl_1
    ui_scr->rt_stream_lbl_1 = lv_label_create(ui_scr->rt_stream);
    lv_label_set_text(ui_scr->rt_stream_lbl_1, "");
    lv_label_set_long_mode(ui_scr->rt_stream_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for rt_stream_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->rt_stream_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->rt_stream_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->rt_stream_lbl_1, lv_color_make(0xE4, 0x18, 0x18), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->rt_stream_lbl_1, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->rt_stream_lbl_1, 0, 0);
    lv_obj_set_size(ui_scr->rt_stream_lbl_1, 800, 42);
    lv_obj_set_scrollbar_mode(ui_scr->rt_stream_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui_scr->rt_stream);
    ui_scr->rt_stream_del = false;

    //Init events for screen
    events_init_rt_stream(ui);
    return ui_scr->rt_stream;
}
void unload_scr_rt_stream(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_RT_STREAM);
}

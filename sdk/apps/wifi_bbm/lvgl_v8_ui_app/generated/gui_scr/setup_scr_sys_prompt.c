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


lv_obj_t *setup_scr_sys_prompt(lv_ui *ui)
{
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_sys_prompt));
        memset(ui_scr, 0, sizeof(lv_ui_sys_prompt));
        ui->sys_prompt = ui_scr;
    }
    if (lv_obj_is_valid(ui_scr->sys_prompt)) {
        lv_obj_del(ui_scr->sys_prompt);
    }
    //Write codes sys_prompt
    ui_scr->sys_prompt = lv_obj_create(lv_layer_top());
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_prompt. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_prompt, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_prompt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_scr->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_scr->sys_prompt, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->sys_prompt, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_prompt_view_1
    ui_scr->sys_prompt_view_1 = lv_obj_create(ui_scr->sys_prompt);

    //Set style for sys_prompt_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_prompt_view_1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_prompt_view_1, lv_color_make(0x33, 0x30, 0x30), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_prompt_view_1, 217, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->sys_prompt_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->sys_prompt_view_1, lv_color_make(0x02, 0x6C, 0xC0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->sys_prompt_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->sys_prompt_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->sys_prompt_view_1, 238, 137);
    lv_obj_set_size(ui_scr->sys_prompt_view_1, 345, 194);
    lv_obj_set_scrollbar_mode(ui_scr->sys_prompt_view_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_prompt_view_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_prompt_lbl_1
    ui_scr->sys_prompt_lbl_1 = lv_label_create(ui_scr->sys_prompt_view_1);
    lv_label_set_text(ui_scr->sys_prompt_lbl_1, "Connect Error !");
    lv_label_set_long_mode(ui_scr->sys_prompt_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_prompt_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_prompt_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->sys_prompt_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->sys_prompt_lbl_1, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->sys_prompt_lbl_1, 159, 51);
    lv_obj_set_size(ui_scr->sys_prompt_lbl_1, 187, 125);
    lv_obj_set_scrollbar_mode(ui_scr->sys_prompt_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_prompt_lbl_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_prompt_img_1
    ui_scr->sys_prompt_img_1 = lv_img_create(ui_scr->sys_prompt_view_1);
    lv_img_set_src(ui_scr->sys_prompt_img_1, gui_get_res_path(GUI_RES_WARN_PNG));
    lv_img_set_pivot(ui_scr->sys_prompt_img_1, 0, 0);
    lv_img_set_angle(ui_scr->sys_prompt_img_1, 0);
    lv_img_set_zoom(ui_scr->sys_prompt_img_1, 256);

    //Set style for sys_prompt_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->sys_prompt_img_1, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->sys_prompt_img_1, 16, 26);
    lv_obj_set_size(ui_scr->sys_prompt_img_1, 128, 128);
    lv_obj_add_flag(ui_scr->sys_prompt_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->sys_prompt_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_update_layout(ui_scr->sys_prompt);
    ui_scr->sys_prompt_del = false;

    //Init events for screen
    events_init_sys_prompt(ui);
    return ui_scr->sys_prompt;
}
void unload_scr_sys_prompt(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
}

#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_sys_prompt(lv_ui *ui)
{
    if (lv_obj_is_valid(ui->sys_prompt)) {
        lv_obj_del(ui->sys_prompt);
    }
    //Write codes sys_prompt
    ui->sys_prompt = lv_obj_create(lv_layer_top());
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_prompt. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_prompt, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_prompt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->sys_prompt, 800, 480);
    lv_obj_set_scrollbar_mode(ui->sys_prompt, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->sys_prompt, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_prompt_img_warn
    ui->sys_prompt_img_warn = lv_img_create(ui->sys_prompt);
    lv_img_set_src(ui->sys_prompt_img_warn, gui_get_res_path(GUI_RES_POP_UP_WINDOW_PNG));
    lv_img_set_pivot(ui->sys_prompt_img_warn, 0, 0);
    lv_img_set_angle(ui->sys_prompt_img_warn, 0);
    lv_img_set_zoom(ui->sys_prompt_img_warn, 256);

    //Set style for sys_prompt_img_warn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_prompt_img_warn, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_img_warn, 186, 122);
    lv_obj_set_size(ui->sys_prompt_img_warn, 390, 200);
    lv_obj_add_flag(ui->sys_prompt_img_warn, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_prompt_lbl_warn
    ui->sys_prompt_lbl_warn = lv_label_create(ui->sys_prompt);
    lv_label_set_long_mode(ui->sys_prompt_lbl_warn, LV_LABEL_LONG_WRAP);

    //Set style for sys_prompt_lbl_warn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_prompt_lbl_warn, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->sys_prompt_lbl_warn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_prompt_lbl_warn, lv_color_make(0x5B, 0x66, 0x6F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_prompt_lbl_warn, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_lbl_warn, 245, 197);
    lv_obj_set_size(ui->sys_prompt_lbl_warn, 394, 64);
    lv_obj_set_scrollbar_mode(ui->sys_prompt_lbl_warn, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_prompt_img_2
    ui->sys_prompt_img_2 = lv_img_create(ui->sys_prompt);
    lv_img_set_src(ui->sys_prompt_img_2, gui_get_res_path(GUI_RES_FLIG_ON_PNG));
    lv_img_set_pivot(ui->sys_prompt_img_2, 0, 0);
    lv_img_set_angle(ui->sys_prompt_img_2, 0);
    lv_img_set_zoom(ui->sys_prompt_img_2, 256);

    //Set style for sys_prompt_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_prompt_img_2, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_img_2, 284, 122);
    lv_obj_set_size(ui->sys_prompt_img_2, 200, 200);
    lv_obj_add_flag(ui->sys_prompt_img_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->sys_prompt_img_2, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_prompt_img_1
    ui->sys_prompt_img_1 = lv_img_create(ui->sys_prompt);
    lv_img_set_src(ui->sys_prompt_img_1, gui_get_res_path(GUI_RES_ASTERN_PNG));
    lv_img_set_pivot(ui->sys_prompt_img_1, 0, 0);
    lv_img_set_angle(ui->sys_prompt_img_1, 0);
    lv_img_set_zoom(ui->sys_prompt_img_1, 256);

    //Set style for sys_prompt_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_prompt_img_1, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_img_1, 106, 311);
    lv_obj_set_size(ui->sys_prompt_img_1, 550, 167);
    lv_obj_add_flag(ui->sys_prompt_img_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->sys_prompt_img_1, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_prompt_lbl_1
    ui->sys_prompt_lbl_1 = lv_label_create(ui->sys_prompt);
    lv_label_set_text(ui->sys_prompt_lbl_1, "准备好了吗~\n电量不足\n未插入卡\n没有文件\n摄像头掉线了\n");
    lv_label_set_long_mode(ui->sys_prompt_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_prompt_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_prompt_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_prompt_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_lbl_1, 282, 64);
    lv_obj_set_size(ui->sys_prompt_lbl_1, 202, 46);
    lv_obj_set_scrollbar_mode(ui->sys_prompt_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_prompt_lbl_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_update_layout(ui->sys_prompt);
    ui->sys_prompt_del = false;
    i18n_refresh_texts("sys_prompt");

    //Init events for screen
    events_init_sys_prompt(ui);
    return ui->sys_prompt;
}
void unload_scr_sys_prompt(lv_ui *ui)
{
    ui->sys_prompt_del = true;
}

#endif

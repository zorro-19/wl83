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


lv_obj_t *setup_scr_line_drift(lv_ui *ui)
{
    //Write codes line_drift
    ui->line_drift = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for line_drift. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->line_drift, LV_SCROLLBAR_MODE_OFF);
    //Write codes line_drift_lbl_3
    ui->line_drift_lbl_3 = lv_label_create(ui->line_drift);
    lv_label_set_text(ui->line_drift_lbl_3, "请移动至车头地平线");
    lv_label_set_long_mode(ui->line_drift_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for line_drift_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift_lbl_3, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->line_drift_lbl_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->line_drift_lbl_3, 50, 193);
    lv_obj_set_size(ui->line_drift_lbl_3, 190, 60);
    lv_obj_set_scrollbar_mode(ui->line_drift_lbl_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->line_drift_lbl_3, LV_OBJ_FLAG_HIDDEN);
    //Write codes line_drift_view_2
    ui->line_drift_view_2 = lv_obj_create(ui->line_drift);

    //Set style for line_drift_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift_view_2, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->line_drift_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->line_drift_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->line_drift_view_2, 42, 395);
    lv_obj_set_size(ui->line_drift_view_2, 700, 60);
    lv_obj_set_scrollbar_mode(ui->line_drift_view_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes line_drift_btn_horizon
    ui->line_drift_btn_horizon = lv_btn_create(ui->line_drift);

    //Set style for line_drift_btn_horizon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift_btn_horizon, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->line_drift_btn_horizon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->line_drift_btn_horizon, lv_color_make(0xD8, 0x3E, 0x74), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->line_drift_btn_horizon, 60, 23);
    lv_obj_set_size(ui->line_drift_btn_horizon, 700, 16);
    lv_obj_set_scrollbar_mode(ui->line_drift_btn_horizon, LV_SCROLLBAR_MODE_OFF);
    ui->line_drift_btn_horizon_label = lv_label_create(ui->line_drift_btn_horizon);
    lv_obj_set_style_pad_all(ui->line_drift_btn_horizon, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->line_drift_btn_horizon_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes line_drift_btn_carhead
    ui->line_drift_btn_carhead = lv_btn_create(ui->line_drift);

    //Set style for line_drift_btn_carhead. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift_btn_carhead, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->line_drift_btn_carhead, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->line_drift_btn_carhead, lv_color_make(0xD8, 0xC5, 0x3E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->line_drift_btn_carhead, 60, 395);
    lv_obj_set_size(ui->line_drift_btn_carhead, 700, 16);
    lv_obj_set_scrollbar_mode(ui->line_drift_btn_carhead, LV_SCROLLBAR_MODE_OFF);
    ui->line_drift_btn_carhead_label = lv_label_create(ui->line_drift_btn_carhead);
    lv_obj_set_style_pad_all(ui->line_drift_btn_carhead, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->line_drift_btn_carhead_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes line_drift_lbl_7
    ui->line_drift_lbl_7 = lv_label_create(ui->line_drift);
    lv_label_set_long_mode(ui->line_drift_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for line_drift_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift_lbl_7, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->line_drift_lbl_7, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->line_drift_lbl_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for line_drift_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->line_drift_lbl_7, &gui_label_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_pos(ui->line_drift_lbl_7, 734, 166);
    lv_obj_set_size(ui->line_drift_lbl_7, 55, 34);
    lv_obj_set_scrollbar_mode(ui->line_drift_lbl_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->line_drift_lbl_7, LV_OBJ_FLAG_CLICKABLE);
    //Write codes line_drift_lbl_6
    ui->line_drift_lbl_6 = lv_label_create(ui->line_drift);
    lv_label_set_long_mode(ui->line_drift_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for line_drift_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->line_drift_lbl_6, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->line_drift_lbl_6, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->line_drift_lbl_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for line_drift_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->line_drift_lbl_6, &gui_label_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_pos(ui->line_drift_lbl_6, 734, 229);
    lv_obj_set_size(ui->line_drift_lbl_6, 57, 35);
    lv_obj_set_scrollbar_mode(ui->line_drift_lbl_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->line_drift_lbl_6, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_update_layout(ui->line_drift);
    ui->line_drift_del = false;
    i18n_refresh_texts("line_drift");

    //Init events for screen
    events_init_line_drift(ui);
    return ui->line_drift;
}
void unload_scr_line_drift(lv_ui *ui)
{
    ui->line_drift_del = true;
}

#endif

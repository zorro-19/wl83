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

static lv_obj_t *sys_setting_datetext_subpage_calendar;
void sys_setting_datetext_subpage_calendar_event_handler(lv_event_t *e);
void sys_setting_datetext_subpage_init_calendar(lv_obj_t *parent);;
void sys_setting_datetext_subpage_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_FOCUSED) {
        if (sys_setting_datetext_subpage_calendar == NULL) {
            sys_setting_datetext_subpage_init_calendar(guider_ui.sys_setting_view_date);
        }
    }
}
void sys_setting_datetext_subpage_init_calendar(lv_obj_t *parent)
{
    if (sys_setting_datetext_subpage_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        sys_setting_datetext_subpage_calendar = lv_calendar_create(lv_layer_top());

        char *text = lv_label_get_text(guider_ui.sys_setting_datetext_subpage);
        char *temp = lv_mem_alloc(strlen(text) + 1);
        if (temp == NULL) {
            LV_LOG_WARN("Memory allocation failed");
            return;
        }
        strcpy(temp, text);
        char *year_str = strtok(temp, "/");
        char *month_str = strtok(NULL, "/");
        uint32_t year = 2022;
        uint32_t month = 5;
        if (year_str != NULL && month_str != NULL) {
            year = atoi(year_str);
            month = atoi(month_str);
        }
        lv_obj_set_size(sys_setting_datetext_subpage_calendar, 240, 240);
        lv_calendar_set_showed_date(sys_setting_datetext_subpage_calendar, year, month);
        lv_obj_align(sys_setting_datetext_subpage_calendar, LV_ALIGN_CENTER, 20, 20);

        lv_obj_add_event_cb(sys_setting_datetext_subpage_calendar, sys_setting_datetext_subpage_calendar_event_handler, LV_EVENT_ALL, NULL);
        lv_calendar_header_arrow_create(sys_setting_datetext_subpage_calendar);
        lv_obj_update_layout(parent);
        lv_mem_free(temp);
    }
}
void sys_setting_datetext_subpage_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj, &date);
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "%d/%02d/%02d", date.year, date.month, date.day);
        lv_label_set_text(guider_ui.sys_setting_datetext_subpage, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(sys_setting_datetext_subpage_calendar);
        sys_setting_datetext_subpage_calendar = NULL;
        lv_event_send(guider_ui.sys_setting_datetext_subpage, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

lv_obj_t *setup_scr_sys_setting(lv_ui *ui)
{
    //Write codes sys_setting
    ui->sys_setting = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_setting. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->sys_setting, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_menupage
    ui->sys_setting_view_menupage = lv_obj_create(ui->sys_setting);

    //Set style for sys_setting_view_menupage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_menupage, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_view_menupage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_view_menupage, 179, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_view_menupage, lv_color_make(0x72, 0x92, 0xAD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_view_menupage, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_menupage, 0, 0);
    lv_obj_set_size(ui->sys_setting_view_menupage, 436, 480);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_menupage, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_img_saver
    ui->sys_setting_img_saver = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_saver, gui_get_res_path(GUI_RES_LCD_OFF_PNG));
    lv_img_set_pivot(ui->sys_setting_img_saver, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_saver, 0);
    lv_img_set_zoom(ui->sys_setting_img_saver, 256);

    //Set style for sys_setting_img_saver. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_saver, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_saver. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_saver, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_saver, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_saver, 32, 36);
    lv_obj_set_size(ui->sys_setting_img_saver, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_saver, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_saver);
    lv_obj_add_flag(ui->sys_setting_img_saver, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_2
    ui->sys_setting_img_2 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_2, gui_get_res_path(GUI_RES_AUTO_OFF_PNG));
    lv_img_set_pivot(ui->sys_setting_img_2, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_2, 0);
    lv_img_set_zoom(ui->sys_setting_img_2, 256);

    //Set style for sys_setting_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_2, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_2, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_2, 133, 36);
    lv_obj_set_size(ui->sys_setting_img_2, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_2);
    lv_obj_add_flag(ui->sys_setting_img_2, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_3
    ui->sys_setting_img_3 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_3, gui_get_res_path(GUI_RES_FREQUENCY_PNG));
    lv_img_set_pivot(ui->sys_setting_img_3, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_3, 0);
    lv_img_set_zoom(ui->sys_setting_img_3, 256);

    //Set style for sys_setting_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_3, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_3, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_3, 234, 36);
    lv_obj_set_size(ui->sys_setting_img_3, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_3);
    lv_obj_add_flag(ui->sys_setting_img_3, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_4
    ui->sys_setting_img_4 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_4, gui_get_res_path(GUI_RES_VOICE_PNG));
    lv_img_set_pivot(ui->sys_setting_img_4, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_4, 0);
    lv_img_set_zoom(ui->sys_setting_img_4, 256);

    //Set style for sys_setting_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_4, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_4, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_4, 338, 36);
    lv_obj_set_size(ui->sys_setting_img_4, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_4);
    lv_obj_add_flag(ui->sys_setting_img_4, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_1
    ui->sys_setting_lbl_1 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_1, 35, 123);
    lv_obj_set_size(ui->sys_setting_lbl_1, 77, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_2
    ui->sys_setting_lbl_2 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_2, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_2, 133, 123);
    lv_obj_set_size(ui->sys_setting_lbl_2, 77, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_3
    ui->sys_setting_lbl_3 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_3, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_3, 235, 123);
    lv_obj_set_size(ui->sys_setting_lbl_3, 77, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_4
    ui->sys_setting_lbl_4 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_4, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_4, 341, 123);
    lv_obj_set_size(ui->sys_setting_lbl_4, 77, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_img_5
    ui->sys_setting_img_5 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_5, gui_get_res_path(GUI_RES_LANGUAGES_PNG));
    lv_img_set_pivot(ui->sys_setting_img_5, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_5, 0);
    lv_img_set_zoom(ui->sys_setting_img_5, 256);

    //Set style for sys_setting_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_5, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_5, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_5, 31, 183);
    lv_obj_set_size(ui->sys_setting_img_5, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_5);
    lv_obj_add_flag(ui->sys_setting_img_5, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_7
    ui->sys_setting_img_7 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_7, gui_get_res_path(GUI_RES_SOFTWARE_PNG));
    lv_img_set_pivot(ui->sys_setting_img_7, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_7, 0);
    lv_img_set_zoom(ui->sys_setting_img_7, 256);

    //Set style for sys_setting_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_7, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->sys_setting_img_7, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->sys_setting_img_7, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->sys_setting_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->sys_setting_img_7, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_7. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_7, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_radius(ui->sys_setting_img_7, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->sys_setting_img_7, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->sys_setting_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_7, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_7, 133, 184);
    lv_obj_set_size(ui->sys_setting_img_7, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_7, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_7);
    lv_obj_add_flag(ui->sys_setting_img_7, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_9
    ui->sys_setting_img_9 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_9, gui_get_res_path(GUI_RES_CAR_NUM_1_PNG));
    lv_img_set_pivot(ui->sys_setting_img_9, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_9, 0);
    lv_img_set_zoom(ui->sys_setting_img_9, 256);

    //Set style for sys_setting_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_9, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_9. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_9, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_9, 235, 182);
    lv_obj_set_size(ui->sys_setting_img_9, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_9, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_9);
    lv_obj_add_flag(ui->sys_setting_img_9, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_8
    ui->sys_setting_img_8 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_8, gui_get_res_path(GUI_RES_LANE_PNG));
    lv_img_set_pivot(ui->sys_setting_img_8, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_8, 0);
    lv_img_set_zoom(ui->sys_setting_img_8, 256);

    //Set style for sys_setting_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_8, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_8. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_8, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_8, 337, 183);
    lv_obj_set_size(ui->sys_setting_img_8, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_8, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_8);
    lv_obj_add_flag(ui->sys_setting_img_8, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_5
    ui->sys_setting_lbl_5 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_5, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_5, 22, 263);
    lv_obj_set_size(ui->sys_setting_lbl_5, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_6
    ui->sys_setting_lbl_6 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_6, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_6, 31, 414);
    lv_obj_set_size(ui->sys_setting_lbl_6, 77, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_img_6
    ui->sys_setting_img_6 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_6, gui_get_res_path(GUI_RES_FLIG_PNG));
    lv_img_set_pivot(ui->sys_setting_img_6, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_6, 0);
    lv_img_set_zoom(ui->sys_setting_img_6, 256);

    //Set style for sys_setting_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_6, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_6, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_6, 32, 330);
    lv_obj_set_size(ui->sys_setting_img_6, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_6);
    lv_obj_add_flag(ui->sys_setting_img_6, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_10
    ui->sys_setting_img_10 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_10, gui_get_res_path(GUI_RES_FORMAT_PNG));
    lv_img_set_pivot(ui->sys_setting_img_10, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_10, 0);
    lv_img_set_zoom(ui->sys_setting_img_10, 256);

    //Set style for sys_setting_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_10, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_10. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_10, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_10, 132, 330);
    lv_obj_set_size(ui->sys_setting_img_10, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_10, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_10);
    lv_obj_add_flag(ui->sys_setting_img_10, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_11
    ui->sys_setting_img_11 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_11, gui_get_res_path(GUI_RES_RESET_PNG));
    lv_img_set_pivot(ui->sys_setting_img_11, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_11, 0);
    lv_img_set_zoom(ui->sys_setting_img_11, 256);

    //Set style for sys_setting_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_11, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_11. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_11, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_11, 233, 330);
    lv_obj_set_size(ui->sys_setting_img_11, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_11, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_11);
    lv_obj_add_flag(ui->sys_setting_img_11, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_12
    ui->sys_setting_img_12 = lv_img_create(ui->sys_setting_view_menupage);
    lv_img_set_src(ui->sys_setting_img_12, gui_get_res_path(GUI_RES_DATE_1_PNG));
    lv_img_set_pivot(ui->sys_setting_img_12, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_12, 0);
    lv_img_set_zoom(ui->sys_setting_img_12, 256);

    //Set style for sys_setting_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_12, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_12. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_12, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_12, 337, 330);
    lv_obj_set_size(ui->sys_setting_img_12, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_12, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_img_12);
    lv_obj_add_flag(ui->sys_setting_img_12, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_7
    ui->sys_setting_lbl_7 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_7, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_7, 129, 263);
    lv_obj_set_size(ui->sys_setting_lbl_7, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_8
    ui->sys_setting_lbl_8 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_8, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_8, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_8, 230, 263);
    lv_obj_set_size(ui->sys_setting_lbl_8, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_8, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_9
    ui->sys_setting_lbl_9 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_9, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_9, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_9, 332, 263);
    lv_obj_set_size(ui->sys_setting_lbl_9, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_9, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_10
    ui->sys_setting_lbl_10 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_10, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_10, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_10, 128, 414);
    lv_obj_set_size(ui->sys_setting_lbl_10, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_10, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_11
    ui->sys_setting_lbl_11 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_11, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_11, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_11, 225, 414);
    lv_obj_set_size(ui->sys_setting_lbl_11, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_11, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_12
    ui->sys_setting_lbl_12 = lv_label_create(ui->sys_setting_view_menupage);
    lv_label_set_long_mode(ui->sys_setting_lbl_12, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_12, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_12, 332, 414);
    lv_obj_set_size(ui->sys_setting_lbl_12, 90, 51);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_12, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_subpage
    ui->sys_setting_view_subpage = lv_obj_create(ui->sys_setting);

    //Set style for sys_setting_view_subpage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_subpage, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_view_subpage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_view_subpage, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_view_subpage, lv_color_make(0xC1, 0xD2, 0xDF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_view_subpage, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_subpage, 436, 0);
    lv_obj_set_size(ui->sys_setting_view_subpage, 364, 480);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_subpage, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_img_icon
    ui->sys_setting_img_icon = lv_img_create(ui->sys_setting_view_subpage);
    lv_img_set_src(ui->sys_setting_img_icon, gui_get_res_path(GUI_RES_AUTO_OFF_PNG));
    lv_img_set_pivot(ui->sys_setting_img_icon, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_icon, 0);
    lv_img_set_zoom(ui->sys_setting_img_icon, 256);

    //Set style for sys_setting_img_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_icon, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_icon, 28, 7);
    lv_obj_set_size(ui->sys_setting_img_icon, 80, 80);
    lv_obj_add_flag(ui->sys_setting_img_icon, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_img_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_img_icon, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_menu_title
    ui->sys_setting_lbl_menu_title = lv_label_create(ui->sys_setting_view_subpage);
    lv_label_set_long_mode(ui->sys_setting_lbl_menu_title, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_menu_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_menu_title, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_menu_title, 117, 28);
    lv_obj_set_size(ui->sys_setting_lbl_menu_title, 232, 53);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_menu_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_3
    ui->sys_setting_view_3 = lv_obj_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_3, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_view_3, lv_color_make(0x86, 0x7E, 0x7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_view_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_view_3, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_3, 0, 414);
    lv_obj_set_size(ui->sys_setting_view_3, 364, 66);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_img_15
    ui->sys_setting_img_15 = lv_img_create(ui->sys_setting_view_3);
    lv_img_set_src(ui->sys_setting_img_15, gui_get_res_path(GUI_RES_VIDEO_2_PNG));
    lv_img_set_pivot(ui->sys_setting_img_15, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_15, 0);
    lv_img_set_zoom(ui->sys_setting_img_15, 256);

    //Set style for sys_setting_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_15, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_15. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->sys_setting_img_15, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->sys_setting_img_15, 2, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for sys_setting_img_15. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_15, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_15, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_15, 21, 6);
    lv_obj_set_size(ui->sys_setting_img_15, 48, 48);
    lv_group_add_obj(def_group, ui->sys_setting_img_15);
    lv_obj_add_flag(ui->sys_setting_img_15, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_14
    ui->sys_setting_img_14 = lv_img_create(ui->sys_setting_view_3);
    lv_img_set_src(ui->sys_setting_img_14, gui_get_res_path(GUI_RES_FILES_PNG));
    lv_img_set_pivot(ui->sys_setting_img_14, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_14, 0);
    lv_img_set_zoom(ui->sys_setting_img_14, 256);

    //Set style for sys_setting_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_14, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_14. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->sys_setting_img_14, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->sys_setting_img_14, 2, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for sys_setting_img_14. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_14, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_14, 149, 6);
    lv_obj_set_size(ui->sys_setting_img_14, 48, 48);
    lv_group_add_obj(def_group, ui->sys_setting_img_14);
    lv_obj_add_flag(ui->sys_setting_img_14, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_16
    ui->sys_setting_img_16 = lv_img_create(ui->sys_setting_view_3);
    lv_img_set_src(ui->sys_setting_img_16, gui_get_res_path(GUI_RES_HOME_PNG));
    lv_img_set_pivot(ui->sys_setting_img_16, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_16, 0);
    lv_img_set_zoom(ui->sys_setting_img_16, 256);

    //Set style for sys_setting_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_16, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_img_16. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->sys_setting_img_16, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->sys_setting_img_16, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for sys_setting_img_16. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_img_16, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_img_16, 284, 6);
    lv_obj_set_size(ui->sys_setting_img_16, 48, 48);
    lv_group_add_obj(def_group, ui->sys_setting_img_16);
    lv_obj_add_flag(ui->sys_setting_img_16, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_view_list
    ui->sys_setting_view_list = lv_obj_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_view_list. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_list, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_view_list, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_view_list, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_list, 6, 93);
    lv_obj_set_size(ui->sys_setting_view_list, 354, 239);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_list, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_funkey4
    ui->sys_setting_lbl_funkey4 = lv_label_create(ui->sys_setting_view_list);
    lv_label_set_long_mode(ui->sys_setting_lbl_funkey4, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey4, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_lbl_funkey4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_lbl_funkey4, 26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_lbl_funkey4, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_setting_lbl_funkey4, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_lbl_funkey4, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_setting_lbl_funkey4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_lbl_funkey4, 14, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
    lv_obj_add_style(ui->sys_setting_lbl_funkey4, &gui_label_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Set style for sys_setting_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey4, &gui_label_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey4, 4, 4);
    lv_obj_set_size(ui->sys_setting_lbl_funkey4, 346, 54);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey4, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->sys_setting_lbl_funkey4, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes sys_setting_lbl_funkey5
    ui->sys_setting_lbl_funkey5 = lv_label_create(ui->sys_setting_view_list);
    lv_label_set_long_mode(ui->sys_setting_lbl_funkey5, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_funkey5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey5, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_lbl_funkey5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_lbl_funkey5, 26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_lbl_funkey5, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_setting_lbl_funkey5, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_lbl_funkey5, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_setting_lbl_funkey5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_setting_lbl_funkey5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_lbl_funkey5, 14, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey5. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
    lv_obj_add_style(ui->sys_setting_lbl_funkey5, &gui_label_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Set style for sys_setting_lbl_funkey5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey5, &gui_label_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey5, 4, 62);
    lv_obj_set_size(ui->sys_setting_lbl_funkey5, 346, 54);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey5, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey5, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->sys_setting_lbl_funkey5, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes sys_setting_lbl_funkey6
    ui->sys_setting_lbl_funkey6 = lv_label_create(ui->sys_setting_view_list);
    lv_label_set_long_mode(ui->sys_setting_lbl_funkey6, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_funkey6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey6, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_lbl_funkey6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_lbl_funkey6, 26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_lbl_funkey6, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_setting_lbl_funkey6, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_lbl_funkey6, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_setting_lbl_funkey6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_lbl_funkey6, 14, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey6. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
    lv_obj_add_style(ui->sys_setting_lbl_funkey6, &gui_label_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Set style for sys_setting_lbl_funkey6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey6, &gui_label_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey6, 4, 122);
    lv_obj_set_size(ui->sys_setting_lbl_funkey6, 346, 54);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey6, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey6, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->sys_setting_lbl_funkey6, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes sys_setting_lbl_funkey7
    ui->sys_setting_lbl_funkey7 = lv_label_create(ui->sys_setting_view_list);
    lv_label_set_long_mode(ui->sys_setting_lbl_funkey7, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_funkey7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey7, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_lbl_funkey7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_lbl_funkey7, 26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_lbl_funkey7, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_setting_lbl_funkey7, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_setting_lbl_funkey7, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_setting_lbl_funkey7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_lbl_funkey7, 14, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey7. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
    lv_obj_add_style(ui->sys_setting_lbl_funkey7, &gui_label_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Set style for sys_setting_lbl_funkey7. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey7, &gui_label_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey7, 4, 180);
    lv_obj_set_size(ui->sys_setting_lbl_funkey7, 346, 54);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey7, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey7, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->sys_setting_lbl_funkey7, LV_OBJ_FLAG_SCROLLABLE);
    //Write codes sys_setting_lbl_subpage_warning
    ui->sys_setting_lbl_subpage_warning = lv_label_create(ui->sys_setting_view_subpage);
    lv_label_set_long_mode(ui->sys_setting_lbl_subpage_warning, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_subpage_warning. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_subpage_warning, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_lbl_subpage_warning, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_lbl_subpage_warning, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_subpage_warning, 6, 140);
    lv_obj_set_size(ui->sys_setting_lbl_subpage_warning, 352, 170);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_subpage_warning, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_date
    ui->sys_setting_view_date = lv_obj_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_view_date. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_date, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_view_date, 217, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_setting_view_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_date, 6, 93);
    lv_obj_set_size(ui->sys_setting_view_date, 349, 236);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_date, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_roller_hour
    ui->sys_setting_roller_hour = lv_roller_create(ui->sys_setting_view_date);

    //Set style for sys_setting_roller_hour. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_roller_hour, &gui_roller_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_roller_hour, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_roller_hour. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_roller_hour, &gui_roller_selected_default_style, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_roller_hour, 17, 93);
    lv_obj_set_size(ui->sys_setting_roller_hour, 145, 114);
    lv_obj_set_scrollbar_mode(ui->sys_setting_roller_hour, LV_SCROLLBAR_MODE_OFF);
    lv_roller_set_options(ui->sys_setting_roller_hour, "1\n2\n3\n4\n5", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui->sys_setting_roller_hour, 3);
    //Write codes sys_setting_roller_min
    ui->sys_setting_roller_min = lv_roller_create(ui->sys_setting_view_date);

    //Set style for sys_setting_roller_min. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_roller_min, &gui_roller_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_roller_min, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_roller_min. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_roller_min, &gui_roller_selected_default_style, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_roller_min, 193, 93);
    lv_obj_set_size(ui->sys_setting_roller_min, 145, 114);
    lv_obj_set_scrollbar_mode(ui->sys_setting_roller_min, LV_SCROLLBAR_MODE_OFF);
    lv_roller_set_options(ui->sys_setting_roller_min, "1\n2\n3\n4\n5", LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(ui->sys_setting_roller_min, 3);

    //Write datetext sys_setting_datetext_subpage
    ui->sys_setting_datetext_subpage = lv_label_create(ui->sys_setting_view_date);
    lv_label_set_text(ui->sys_setting_datetext_subpage, "2024/05/20");
    lv_obj_set_style_text_align(ui->sys_setting_datetext_subpage, LV_TEXT_ALIGN_CENTER, 0);

    //write datetext event
    lv_obj_add_flag(ui->sys_setting_datetext_subpage, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->sys_setting_datetext_subpage, sys_setting_datetext_subpage_event, LV_EVENT_ALL, NULL);

    //Set style for sys_setting_datetext_subpage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_datetext_subpage, &gui_datetext_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_datetext_subpage, 16, 18);
    lv_obj_set_size(ui->sys_setting_datetext_subpage, 310, 45);
    lv_group_add_obj(def_group, ui->sys_setting_datetext_subpage);
    //Write codes sys_setting_view_carmun
    ui->sys_setting_view_carmun = lv_obj_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_view_carmun. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_carmun, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_carmun, 4, 95);
    lv_obj_set_size(ui->sys_setting_view_carmun, 345, 234);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_carmun, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_1
    ui->sys_setting_ddlist_1 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_1, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_1, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_1, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_1, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_1, 0);

    //Set style for sys_setting_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_1, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_ddlist_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_ddlist_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_ddlist_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_1, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->sys_setting_ddlist_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_1_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_1_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_1_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_1), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_1), &style_sys_setting_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_1_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_1_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_1_extra_list_main_default);
    lv_style_set_max_height(&style_sys_setting_ddlist_1_extra_list_main_default, 210);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_1), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_1), &style_sys_setting_ddlist_1_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_1_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_1_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_1_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_1), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_1), &style_sys_setting_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_1, 18, 22);
    lv_obj_set_size(ui->sys_setting_ddlist_1, 109, 66);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_2
    ui->sys_setting_ddlist_2 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_2, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_2, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_2, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_2, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_2, 0);

    //Set style for sys_setting_ddlist_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_2, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_ddlist_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_ddlist_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_ddlist_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_2, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->sys_setting_ddlist_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_2_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_2_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_2_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_2), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_2), &style_sys_setting_ddlist_2_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_2_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_2_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_2_extra_list_main_default);
    lv_style_set_max_height(&style_sys_setting_ddlist_2_extra_list_main_default, 210);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_2), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_2), &style_sys_setting_ddlist_2_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_2_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_2_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_2_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_2), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_2), &style_sys_setting_ddlist_2_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_2, 227, 22);
    lv_obj_set_size(ui->sys_setting_ddlist_2, 100, 66);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_3
    ui->sys_setting_ddlist_3 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_3, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_3, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_3, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_3, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_3, 0);

    //Set style for sys_setting_ddlist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_3, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_3, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_3_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_3_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_3_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_3), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_3), &style_sys_setting_ddlist_3_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_3_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_3_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_3_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_3), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_3), &style_sys_setting_ddlist_3_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_3_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_3_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_3_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_3), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_3), &style_sys_setting_ddlist_3_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_3, 13, 120);
    lv_obj_set_size(ui->sys_setting_ddlist_3, 54, 60);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_4
    ui->sys_setting_ddlist_4 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_4, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_4, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_4, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_4, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_4, 0);

    //Set style for sys_setting_ddlist_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_4, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_4, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_4_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_4_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_4_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_4), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_4), &style_sys_setting_ddlist_4_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_4_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_4_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_4_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_4), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_4), &style_sys_setting_ddlist_4_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_4_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_4_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_4_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_4), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_4), &style_sys_setting_ddlist_4_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_4, 82, 120);
    lv_obj_set_size(ui->sys_setting_ddlist_4, 53, 60);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_5
    ui->sys_setting_ddlist_5 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_5, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_5, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_5, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_5, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_5, 0);

    //Set style for sys_setting_ddlist_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_5, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_5, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_5_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_5_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_5_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_5), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_5), &style_sys_setting_ddlist_5_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_5_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_5_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_5_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_5), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_5), &style_sys_setting_ddlist_5_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_5_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_5_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_5_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_5), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_5), &style_sys_setting_ddlist_5_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_5, 150, 120);
    lv_obj_set_size(ui->sys_setting_ddlist_5, 52, 60);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_6
    ui->sys_setting_ddlist_6 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_6, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_6, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_6, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_6, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_6, 0);

    //Set style for sys_setting_ddlist_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_6, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_6, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_6_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_6_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_6_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_6), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_6), &style_sys_setting_ddlist_6_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_6_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_6_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_6_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_6), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_6), &style_sys_setting_ddlist_6_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_6_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_6_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_6_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_6), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_6), &style_sys_setting_ddlist_6_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_6, 217, 120);
    lv_obj_set_size(ui->sys_setting_ddlist_6, 48, 60);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_7
    ui->sys_setting_ddlist_7 = lv_dropdown_create(ui->sys_setting_view_carmun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_7, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_7, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_7, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_7, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_7, 0);

    //Set style for sys_setting_ddlist_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_7, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_7. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_7, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_7_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_7_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_7_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_7), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_7), &style_sys_setting_ddlist_7_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_7_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_7_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_7_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_7), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_7), &style_sys_setting_ddlist_7_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_7_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_7_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_7_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_7), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_7), &style_sys_setting_ddlist_7_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_7, 280, 120);
    lv_obj_set_size(ui->sys_setting_ddlist_7, 48, 60);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_lbl_funkey1
    ui->sys_setting_lbl_funkey1 = lv_btn_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey1, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->sys_setting_lbl_funkey1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey1, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey1, 3, 351);
    lv_obj_set_size(ui->sys_setting_lbl_funkey1, 112, 55);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_lbl_funkey1_label = lv_label_create(ui->sys_setting_lbl_funkey1);
    lv_label_set_text(ui->sys_setting_lbl_funkey1_label, "button");
    lv_obj_set_style_pad_all(ui->sys_setting_lbl_funkey1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_lbl_funkey1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_setting_lbl_funkey2
    ui->sys_setting_lbl_funkey2 = lv_btn_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey2, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
    lv_obj_add_style(ui->sys_setting_lbl_funkey2, &gui_btn_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Set style for sys_setting_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey2, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey2, 126, 351);
    lv_obj_set_size(ui->sys_setting_lbl_funkey2, 112, 55);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_lbl_funkey2_label = lv_label_create(ui->sys_setting_lbl_funkey2);
    lv_obj_set_style_pad_all(ui->sys_setting_lbl_funkey2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_lbl_funkey2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_setting_lbl_funkey3
    ui->sys_setting_lbl_funkey3 = lv_btn_create(ui->sys_setting_view_subpage);

    //Set style for sys_setting_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_funkey3, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_lbl_funkey3, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_lbl_funkey3, 249, 351);
    lv_obj_set_size(ui->sys_setting_lbl_funkey3, 112, 55);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_funkey3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->sys_setting_lbl_funkey3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_lbl_funkey3_label = lv_label_create(ui->sys_setting_lbl_funkey3);
    lv_label_set_text(ui->sys_setting_lbl_funkey3_label, "button");
    lv_obj_set_style_pad_all(ui->sys_setting_lbl_funkey3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_lbl_funkey3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->sys_setting);
    ui->sys_setting_del = false;
    i18n_refresh_texts("sys_setting");

    //Init events for screen
    events_init_sys_setting(ui);
    return ui->sys_setting;
}
void unload_scr_sys_setting(lv_ui *ui)
{
    ui->sys_setting_del = true;
}

#endif

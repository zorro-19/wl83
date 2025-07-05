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

static const char *pair_status_imglist_1_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};
static const char *pair_status_imglist_2_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};
static const char *pair_status_imglist_3_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};
static const char *pair_status_imglist_4_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};
static const char *pair_status_imglist_5_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};
static const char *pair_status_imglist_6_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};
static void kb_pair_status_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}
__attribute__((unused)) static void ta_pair_status_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);
    }
}

lv_obj_t *setup_scr_pair_status(lv_ui *ui)
{
    lv_ui_pair_status *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_pair_status));
        memset(ui_scr, 0, sizeof(lv_ui_pair_status));
        ui->pair_status = ui_scr;
    }
    //Write codes pair_status
    ui_scr->pair_status = lv_obj_create(NULL);

    //Create keyboard on pair_status
    ui_scr->g_kb_pair_status = lv_keyboard_create(ui_scr->pair_status);
    lv_obj_add_event_cb(ui_scr->g_kb_pair_status, kb_pair_status_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_scr->g_kb_pair_status, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui_scr->g_kb_pair_status, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_scr->g_kb_pair_status, LV_PCT(70), LV_PCT(40));
    lv_keyboard_set_mode(ui_scr->g_kb_pair_status, LV_KEYBOARD_MODE_TEXT_LOWER);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for pair_status. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->pair_status, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_imglist_1
    ui_scr->pair_status_imglist_1 = lv_imglist_create(ui_scr->pair_status);

    //Set style for pair_status_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imglist_1, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imglist_1, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->pair_status_imglist_1, 86, 111);
    lv_obj_set_size(ui_scr->pair_status_imglist_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imglist_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->pair_status_imglist_1, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->pair_status_imglist_1);
    lv_imglist_set_src(ui_scr->pair_status_imglist_1, (const void **) pair_status_imglist_1_imgs, 2);
    lv_imglist_set_act(ui_scr->pair_status_imglist_1, 0);
    //Write codes pair_status_imglist_2
    ui_scr->pair_status_imglist_2 = lv_imglist_create(ui_scr->pair_status);

    //Set style for pair_status_imglist_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imglist_2, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imglist_2, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->pair_status_imglist_2, 337, 111);
    lv_obj_set_size(ui_scr->pair_status_imglist_2, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imglist_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->pair_status_imglist_2, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->pair_status_imglist_2);
    lv_imglist_set_src(ui_scr->pair_status_imglist_2, (const void **) pair_status_imglist_2_imgs, 2);
    lv_imglist_set_act(ui_scr->pair_status_imglist_2, 0);
    //Write codes pair_status_imglist_3
    ui_scr->pair_status_imglist_3 = lv_imglist_create(ui_scr->pair_status);

    //Set style for pair_status_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imglist_3, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imglist_3, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->pair_status_imglist_3, 590, 111);
    lv_obj_set_size(ui_scr->pair_status_imglist_3, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imglist_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->pair_status_imglist_3, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->pair_status_imglist_3);
    lv_imglist_set_src(ui_scr->pair_status_imglist_3, (const void **) pair_status_imglist_3_imgs, 2);
    lv_imglist_set_act(ui_scr->pair_status_imglist_3, 0);
    //Write codes pair_status_imglist_4
    ui_scr->pair_status_imglist_4 = lv_imglist_create(ui_scr->pair_status);

    //Set style for pair_status_imglist_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imglist_4, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imglist_4, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->pair_status_imglist_4, 82, 296);
    lv_obj_set_size(ui_scr->pair_status_imglist_4, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imglist_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->pair_status_imglist_4, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->pair_status_imglist_4);
    lv_imglist_set_src(ui_scr->pair_status_imglist_4, (const void **) pair_status_imglist_4_imgs, 2);
    lv_imglist_set_act(ui_scr->pair_status_imglist_4, 0);
    //Write codes pair_status_imglist_5
    ui_scr->pair_status_imglist_5 = lv_imglist_create(ui_scr->pair_status);

    //Set style for pair_status_imglist_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imglist_5, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imglist_5, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->pair_status_imglist_5, 337, 291);
    lv_obj_set_size(ui_scr->pair_status_imglist_5, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imglist_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->pair_status_imglist_5, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->pair_status_imglist_5);
    lv_imglist_set_src(ui_scr->pair_status_imglist_5, (const void **) pair_status_imglist_5_imgs, 2);
    lv_imglist_set_act(ui_scr->pair_status_imglist_5, 0);
    //Write codes pair_status_imglist_6
    ui_scr->pair_status_imglist_6 = lv_imglist_create(ui_scr->pair_status);

    //Set style for pair_status_imglist_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imglist_6, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imglist_6, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->pair_status_imglist_6, 590, 295);
    lv_obj_set_size(ui_scr->pair_status_imglist_6, 128, 128);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imglist_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->pair_status_imglist_6, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->pair_status_imglist_6);
    lv_imglist_set_src(ui_scr->pair_status_imglist_6, (const void **) pair_status_imglist_6_imgs, 2);
    lv_imglist_set_act(ui_scr->pair_status_imglist_6, 0);
    //Write codes pair_status_imgbtn_1
    ui_scr->pair_status_imgbtn_1 = lv_imgbtn_create(ui_scr->pair_status);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->pair_status_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->pair_status_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->pair_status_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->pair_status_imgbtn_1, 19, 14);
    lv_obj_set_size(ui_scr->pair_status_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->pair_status_imgbtn_1);
    lv_imgbtn_set_src(ui_scr->pair_status_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->pair_status_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->pair_status_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->pair_status_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_obj_add_flag(ui_scr->pair_status_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->pair_status_imgbtn_1_label = lv_label_create(ui_scr->pair_status_imgbtn_1);
    lv_label_set_text(ui_scr->pair_status_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->pair_status_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->pair_status_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes pair_status_lbl_1
    ui_scr->pair_status_lbl_1 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_1, "Device 0");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_1, 85, 240);
    lv_obj_set_size(ui_scr->pair_status_lbl_1, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_2
    ui_scr->pair_status_lbl_2 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_2, "Device 1");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_2, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_2, 335, 240);
    lv_obj_set_size(ui_scr->pair_status_lbl_2, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_3
    ui_scr->pair_status_lbl_3 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_3, "Device 2");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_3, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_3, 585, 240);
    lv_obj_set_size(ui_scr->pair_status_lbl_3, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_4
    ui_scr->pair_status_lbl_4 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_4, "Device 3");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_4, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_4, 85, 425);
    lv_obj_set_size(ui_scr->pair_status_lbl_4, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_5
    ui_scr->pair_status_lbl_5 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_5, "Device 4");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_5, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_5, 335, 425);
    lv_obj_set_size(ui_scr->pair_status_lbl_5, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_6
    ui_scr->pair_status_lbl_6 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_6, "Device 5");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_6, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_6, 585, 425);
    lv_obj_set_size(ui_scr->pair_status_lbl_6, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_ddlist_1
    ui_scr->pair_status_ddlist_1 = lv_dropdown_create(ui_scr->pair_status);
    lv_dropdown_set_options(ui_scr->pair_status_ddlist_1, "Channel-1\nChannel-6\nChannel-11\nChannel-13");
    lv_dropdown_set_dir(ui_scr->pair_status_ddlist_1, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->pair_status_ddlist_1, LV_SYMBOL_DOWN);
    lv_dropdown_set_selected(ui_scr->pair_status_ddlist_1, 0);

    //Set style for pair_status_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_ddlist_1, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->pair_status_ddlist_1, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_pair_status_ddlist_1_extra_list_selected_checked
    static lv_style_t style_pair_status_ddlist_1_extra_list_selected_checked;
    ui_init_style(&style_pair_status_ddlist_1_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->pair_status_ddlist_1), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->pair_status_ddlist_1), &style_pair_status_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_pair_status_ddlist_1_extra_list_main_default
    static lv_style_t style_pair_status_ddlist_1_extra_list_main_default;
    ui_init_style(&style_pair_status_ddlist_1_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->pair_status_ddlist_1), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->pair_status_ddlist_1), &style_pair_status_ddlist_1_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_pair_status_ddlist_1_extra_list_scrollbar_default
    static lv_style_t style_pair_status_ddlist_1_extra_list_scrollbar_default;
    ui_init_style(&style_pair_status_ddlist_1_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->pair_status_ddlist_1), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->pair_status_ddlist_1), &style_pair_status_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_ddlist_1, 590, 49);
    lv_obj_set_size(ui_scr->pair_status_ddlist_1, 150, 45);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_ddlist_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_7
    ui_scr->pair_status_lbl_7 = lv_label_create(ui_scr->pair_status);
    lv_label_set_text(ui_scr->pair_status_lbl_7, "WiFi-Channel");
    lv_label_set_long_mode(ui_scr->pair_status_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pair_status_lbl_7, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->pair_status_lbl_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->pair_status_lbl_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->pair_status_lbl_7, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->pair_status_lbl_7, lv_color_make(0x2A, 0x09, 0x23), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->pair_status_lbl_7, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pair_status_lbl_7, 520, 0);
    lv_obj_set_size(ui_scr->pair_status_lbl_7, 233, 38);
    lv_obj_set_scrollbar_mode(ui_scr->pair_status_lbl_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui_scr->pair_status);
    ui_scr->pair_status_del = false;

    //Init events for screen
    events_init_pair_status(ui);
    return ui_scr->pair_status;
}
void unload_scr_pair_status(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_PAIR_STATUS);
}

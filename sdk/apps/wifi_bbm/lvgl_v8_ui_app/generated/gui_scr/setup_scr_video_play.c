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

static const char *video_play_imglist_1_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\video_play.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\video_pause.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00000d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00000e.zip"
#endif
};

lv_obj_t *setup_scr_video_play(lv_ui *ui)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_play));
        memset(ui_scr, 0, sizeof(lv_ui_video_play));
        ui->video_play = ui_scr;
    }
    //Write codes video_play
    ui_scr->video_play = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for video_play. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->video_play, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_play_imgbtn_1
    ui_scr->video_play_imgbtn_1 = lv_imgbtn_create(ui_scr->video_play);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_imgbtn_1, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play_imgbtn_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->video_play_imgbtn_1, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_add_style(ui_scr->video_play_imgbtn_1, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_scr->video_play_imgbtn_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_add_style(ui_scr->video_play_imgbtn_1, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_1, 699, 107);
    lv_obj_set_size(ui_scr->video_play_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_1);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_WHITE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_WHITE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_WHITE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_WHITE_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_1_label = lv_label_create(ui_scr->video_play_imgbtn_1);
    lv_label_set_text(ui_scr->video_play_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_play_view_1
    ui_scr->video_play_view_1 = lv_obj_create(ui_scr->video_play);

    //Set style for video_play_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_view_1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play_view_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->video_play_view_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->video_play_view_1, 0, 401);
    lv_obj_set_size(ui_scr->video_play_view_1, 800, 80);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_view_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_play_imglist_1
    ui_scr->video_play_imglist_1 = lv_imglist_create(ui_scr->video_play_view_1);

    //Set style for video_play_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_imglist_1, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play_imglist_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->video_play_imglist_1, &gui_imglist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->video_play_imglist_1, 95, 22);
    lv_obj_set_size(ui_scr->video_play_imglist_1, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imglist_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_play_imglist_1, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->video_play_imglist_1);
    lv_imglist_set_src(ui_scr->video_play_imglist_1, (const void **) video_play_imglist_1_imgs, 2);
    lv_imglist_set_act(ui_scr->video_play_imglist_1, 0);
    //Write codes video_play_imgbtn_3
    ui_scr->video_play_imgbtn_3 = lv_imgbtn_create(ui_scr->video_play_view_1);

    //Set style for video_play_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_imgbtn_3, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play_imgbtn_3, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_play_imgbtn_3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->video_play_imgbtn_3, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_3, 172, 22);
    lv_obj_set_size(ui_scr->video_play_imgbtn_3, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_3);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_SKIP_NEXT_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_3_label = lv_label_create(ui_scr->video_play_imgbtn_3);
    lv_label_set_text(ui_scr->video_play_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_play_imgbtn_2
    ui_scr->video_play_imgbtn_2 = lv_imgbtn_create(ui_scr->video_play_view_1);

    //Set style for video_play_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_imgbtn_2, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play_imgbtn_2, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_play_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->video_play_imgbtn_2, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_2, 20, 22);
    lv_obj_set_size(ui_scr->video_play_imgbtn_2, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_2);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_SKIP_PREVIOUS_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_2_label = lv_label_create(ui_scr->video_play_imgbtn_2);
    lv_label_set_text(ui_scr->video_play_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_play_bar_1
    ui_scr->video_play_bar_1 = lv_bar_create(ui_scr->video_play_view_1);

    //Set style for video_play_bar_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_bar_1, &gui_bar_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_bar_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->video_play_bar_1, &gui_bar_indicator_default_style, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->video_play_bar_1, 0, 0);
    lv_obj_set_size(ui_scr->video_play_bar_1, 800, 12);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_bar_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_anim_time(ui_scr->video_play_bar_1, 1000, 0);
    lv_bar_set_mode(ui_scr->video_play_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui_scr->video_play_bar_1, 0, 100);
    lv_bar_set_value(ui_scr->video_play_bar_1, 0, LV_ANIM_OFF);
    lv_obj_update_layout(ui_scr->video_play);
    ui_scr->video_play_del = false;

    //Init events for screen
    events_init_video_play(ui);
    return ui_scr->video_play;
}
void unload_scr_video_play(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
}

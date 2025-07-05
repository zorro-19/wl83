/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"

static const char *home_imglist_bat_imgs[6] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_15.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_25.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_50.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_75.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_100.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000006.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000007.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000008.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000009.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600000a.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000005.rle"
#endif
};
static const char *home_imglist_wifi_imgs[5] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_00.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_01.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_2.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_03.png",
    "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600000b.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600000c.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600000d.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600000e.rle",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000000.rle"
#endif
};

lv_obj_t *setup_scr_home(lv_ui *ui)
{
    //Write codes home
    ui->home = lv_obj_create(NULL);

    //Set style for home. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->home, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->home, LV_SCROLLBAR_MODE_OFF);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes home_img_wifi
    ui->home_img_wifi = lv_img_create(ui->home);

    //Set style for home_img_wifi. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_wifi, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_wifi, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_wifi, lv_color_make(0xCF, 0xCB, 0xCB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_wifi, 41, 26);
    lv_obj_set_size(ui->home_img_wifi, 32, 32);
    lv_obj_set_scrollbar_mode(ui->home_img_wifi, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_wifi, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_img_wifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->home_img_wifi, LV_OBJ_FLAG_CLICKABLE);

    //Hidden for widget home_img_wifi
    lv_obj_add_flag(ui->home_img_wifi, LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_wifi, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png");
#else
    lv_img_set_src(ui->home_img_wifi, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000000.rle");
#endif
    lv_img_set_pivot(ui->home_img_wifi, 0, 0);
    lv_img_set_angle(ui->home_img_wifi, 0);
    lv_img_set_zoom(ui->home_img_wifi, 256);
    //Write codes home_lbl_bat
    ui->home_lbl_bat = lv_label_create(ui->home);
    lv_label_set_text(ui->home_lbl_bat, "100%");
    lv_label_set_long_mode(ui->home_lbl_bat, LV_LABEL_LONG_WRAP);

    //Set style for home_lbl_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_lbl_bat, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_lbl_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_lbl_bat, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_lbl_bat, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_lbl_bat, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_lbl_bat, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_lbl_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_lbl_bat, 384, 21);
    lv_obj_set_size(ui->home_lbl_bat, 70, 42);
    lv_obj_set_scrollbar_mode(ui->home_lbl_bat, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_lbl_bat, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes home_lbl_2
    ui->home_lbl_2 = lv_label_create(ui->home);
    lv_label_set_text(ui->home_lbl_2, "远程呼叫");
    lv_label_set_long_mode(ui->home_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for home_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_lbl_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_lbl_2, &lv_font_simsun_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_lbl_2, 27, 694);
    lv_obj_set_size(ui->home_lbl_2, 106, 41);
    lv_obj_set_scrollbar_mode(ui->home_lbl_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_lbl_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_lbl_2, LV_OBJ_FLAG_HIDDEN);

    //Hidden for widget home_lbl_2
    lv_obj_add_flag(ui->home_lbl_2, LV_OBJ_FLAG_HIDDEN);
    //Write codes home_lbl_4
    ui->home_lbl_4 = lv_label_create(ui->home);
    lv_label_set_text(ui->home_lbl_4, "门外对讲");
    lv_label_set_long_mode(ui->home_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for home_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_lbl_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_lbl_4, &lv_font_simsun_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_lbl_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_lbl_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_lbl_4, 180, 694);
    lv_obj_set_size(ui->home_lbl_4, 106, 41);
    lv_obj_set_scrollbar_mode(ui->home_lbl_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_lbl_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_lbl_4, LV_OBJ_FLAG_HIDDEN);

    //Hidden for widget home_lbl_4
    lv_obj_add_flag(ui->home_lbl_4, LV_OBJ_FLAG_HIDDEN);
    //Write codes home_lbl_5
    ui->home_lbl_5 = lv_label_create(ui->home);
    lv_label_set_text(ui->home_lbl_5, "便捷回复");
    lv_label_set_long_mode(ui->home_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for home_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_lbl_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_lbl_5, &lv_font_simsun_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_lbl_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_lbl_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_lbl_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_lbl_5, 342, 694);
    lv_obj_set_size(ui->home_lbl_5, 106, 41);
    lv_obj_set_scrollbar_mode(ui->home_lbl_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_lbl_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_lbl_5, LV_OBJ_FLAG_HIDDEN);

    //Hidden for widget home_lbl_5
    lv_obj_add_flag(ui->home_lbl_5, LV_OBJ_FLAG_HIDDEN);
    //Write codes home_img_funkey1
    ui->home_img_funkey1 = lv_img_create(ui->home);

    //Set style for home_img_funkey1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_funkey1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_funkey1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_funkey1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_funkey1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_funkey1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_funkey1, 28, 588);
    lv_obj_set_size(ui->home_img_funkey1, 98, 98);
    lv_obj_set_scrollbar_mode(ui->home_img_funkey1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_funkey1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->home_img_funkey1, LV_OBJ_FLAG_CLICKABLE);

    //Hidden for widget home_img_funkey1
    lv_obj_add_flag(ui->home_img_funkey1, LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_funkey1, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_call_out.png");
#else
    lv_img_set_src(ui->home_img_funkey1, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000001.rle");
#endif
    lv_img_set_pivot(ui->home_img_funkey1, 0, 0);
    lv_img_set_angle(ui->home_img_funkey1, 0);
    lv_img_set_zoom(ui->home_img_funkey1, 256);
    //Write codes home_img_funkey3
    ui->home_img_funkey3 = lv_img_create(ui->home);

    //Set style for home_img_funkey3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_funkey3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_funkey3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_funkey3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_funkey3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_funkey3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_funkey3, 345, 588);
    lv_obj_set_size(ui->home_img_funkey3, 98, 98);
    lv_obj_set_scrollbar_mode(ui->home_img_funkey3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_funkey3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_img_funkey3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->home_img_funkey3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->home_img_funkey3, LV_OBJ_FLAG_CLICKABLE);

    //Hidden for widget home_img_funkey3
    lv_obj_add_flag(ui->home_img_funkey3, LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_funkey3, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_recover.png");
#else
    lv_img_set_src(ui->home_img_funkey3, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000002.rle");
#endif
    lv_img_set_pivot(ui->home_img_funkey3, 0, 0);
    lv_img_set_angle(ui->home_img_funkey3, 0);
    lv_img_set_zoom(ui->home_img_funkey3, 256);
    //Write codes home_img_funkey2
    ui->home_img_funkey2 = lv_img_create(ui->home);

    //Set style for home_img_funkey2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_funkey2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_funkey2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_funkey2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_funkey2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_funkey2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_funkey2, 188, 589);
    lv_obj_set_size(ui->home_img_funkey2, 98, 98);
    lv_obj_set_scrollbar_mode(ui->home_img_funkey2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_funkey2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_img_funkey2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->home_img_funkey2, LV_OBJ_FLAG_CLICKABLE);

    //Hidden for widget home_img_funkey2
    lv_obj_add_flag(ui->home_img_funkey2, LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_funkey2, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_walkie_talkie.png");
#else
    lv_img_set_src(ui->home_img_funkey2, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000003.rle");
#endif
    lv_img_set_pivot(ui->home_img_funkey2, 0, 0);
    lv_img_set_angle(ui->home_img_funkey2, 0);
    lv_img_set_zoom(ui->home_img_funkey2, 256);
    static bool timer_home_digitclock_time_enabled = false;

    //Write codes home_digitclock_time
    ui->home_digitclock_time = lv_label_create(ui->home);
    lv_label_set_text_fmt(ui->home_digitclock_time, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui->home_digitclock_time, LV_TEXT_ALIGN_CENTER, 0);

    //Set style for home_digitclock_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_digitclock_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_digitclock_time, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digitclock_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digitclock_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_digitclock_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digitclock_time, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digitclock_time, &lv_font_montserratMedium_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digitclock_time, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digitclock_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digitclock_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digitclock_time, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_digitclock_time, 5, 94);
    lv_obj_set_size(ui->home_digitclock_time, 468, 52);
    //Write codes home_img_weather
    ui->home_img_weather = lv_img_create(ui->home);

    //Set style for home_img_weather. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_weather, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_weather, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_weather, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_weather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_weather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_weather, 146, 298);
    lv_obj_set_size(ui->home_img_weather, 200, 200);
    lv_obj_set_scrollbar_mode(ui->home_img_weather, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_weather, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_weather, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_013.png");
#else
    lv_img_set_src(ui->home_img_weather, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000004.rle");
#endif
    lv_img_set_pivot(ui->home_img_weather, 0, 0);
    lv_img_set_angle(ui->home_img_weather, 0);
    lv_img_set_zoom(ui->home_img_weather, 256);
    //Write codes home_img_bat
    ui->home_img_bat = lv_img_create(ui->home);

    //Set style for home_img_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_bat, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_bat, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_bat, 322, 17);
    lv_obj_set_size(ui->home_img_bat, 51, 51);
    lv_obj_set_scrollbar_mode(ui->home_img_bat, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_bat, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->home_img_bat, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_bat, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png");
#else
    lv_img_set_src(ui->home_img_bat, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000005.rle");
#endif
    lv_img_set_pivot(ui->home_img_bat, 0, 0);
    lv_img_set_angle(ui->home_img_bat, 0);
    lv_img_set_zoom(ui->home_img_bat, 256);
    //Write codes home_lbl_note
    ui->home_lbl_note = lv_label_create(ui->home);
    lv_label_set_text(ui->home_lbl_note, _("ScanCode"));
    lv_label_set_long_mode(ui->home_lbl_note, LV_LABEL_LONG_WRAP);

    const lv_font_t *home_lbl_note_font = _font("ScanCode");
    if (home_lbl_note_font == NULL) {
        home_lbl_note_font = &lv_font_FangZhengKaiTiJianTi_1_32;
    }

    //Set style for home_lbl_note. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_lbl_note, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_lbl_note, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_lbl_note, home_lbl_note_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_lbl_note, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_lbl_note, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_lbl_note, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_lbl_note, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_lbl_note, 17, 157);
    lv_obj_set_size(ui->home_lbl_note, 454, 140);
    lv_obj_set_scrollbar_mode(ui->home_lbl_note, LV_SCROLLBAR_MODE_OFF);
    //Write codes home_img_menu
    ui->home_img_menu = lv_img_create(ui->home);

    //Set style for home_img_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_img_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_img_menu, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_img_menu, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_img_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_img_menu, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_img_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_img_menu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_img_menu, 180, 676);
    lv_obj_set_size(ui->home_img_menu, 98, 98);
    lv_obj_set_scrollbar_mode(ui->home_img_menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_img_menu, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->home_img_menu, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_img_menu, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_recover.png");
#else
    lv_img_set_src(ui->home_img_menu, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000002.rle");
#endif
    lv_img_set_pivot(ui->home_img_menu, 0, 0);
    lv_img_set_angle(ui->home_img_menu, 0);
    lv_img_set_zoom(ui->home_img_menu, 256);
    //Write codes home_imglist_bat
    ui->home_imglist_bat = lv_imglist_create(ui->home);

    //Set style for home_imglist_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_imglist_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_imglist_bat, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_imglist_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_imglist_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_imglist_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_imglist_bat, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_imglist_bat, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_imglist_bat, 324, 17);
    lv_obj_set_size(ui->home_imglist_bat, 51, 51);
    lv_obj_set_scrollbar_mode(ui->home_imglist_bat, LV_SCROLLBAR_MODE_OFF);
    lv_imglist_set_src(ui->home_imglist_bat, (const void **) home_imglist_bat_imgs, 6);
    lv_imglist_set_act(ui->home_imglist_bat, 0);
    //Write codes home_imglist_wifi
    ui->home_imglist_wifi = lv_imglist_create(ui->home);

    //Set style for home_imglist_wifi. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_imglist_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_imglist_wifi, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_imglist_wifi, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_imglist_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_imglist_wifi, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_imglist_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_imglist_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_imglist_wifi, 39, 26);
    lv_obj_set_size(ui->home_imglist_wifi, 32, 32);
    lv_obj_set_scrollbar_mode(ui->home_imglist_wifi, LV_SCROLLBAR_MODE_OFF);
    lv_imglist_set_src(ui->home_imglist_wifi, (const void **) home_imglist_wifi_imgs, 5);
    lv_imglist_set_act(ui->home_imglist_wifi, 0);
    lv_obj_update_layout(ui->home);
    ui->home_del = false;

    //Init events for screen
    events_init_home(ui);
    return ui->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui->home_del = true;
}

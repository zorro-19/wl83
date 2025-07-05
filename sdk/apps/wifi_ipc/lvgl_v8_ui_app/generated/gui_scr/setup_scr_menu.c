/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"


lv_obj_t *setup_scr_menu(lv_ui *ui)
{
    //Write codes menu
    ui->menu = lv_obj_create(NULL);

    //Set style for menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->menu, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu, lv_color_make(0xFF, 0x6A, 0x6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui->menu, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes menu_edit_return
    ui->menu_edit_return = lv_textarea_create(ui->menu);

    const lv_font_t *menu_edit_return_font = _font("back");
    if (menu_edit_return_font == NULL) {
        menu_edit_return_font = &lv_font_FangZhengKaiTiJianTi_1_20;
    }

    //Set style for menu_edit_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_return, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_return, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu_edit_return, lv_color_make(0xFF, 0xA5, 0xA5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_edit_return, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_return, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_edit_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_edit_return, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_edit_return, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_edit_return, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_edit_return, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_edit_return, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_edit_return, menu_edit_return_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_edit_return, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_edit_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_edit_return, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_edit_return, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_edit_return, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_edit_return, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for menu_edit_return. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_return, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_return, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_edit_return, 62, 218);
    lv_obj_set_size(ui->menu_edit_return, 125, 42);
    lv_obj_set_scrollbar_mode(ui->menu_edit_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_edit_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->menu_edit_return);
    lv_textarea_set_text(ui->menu_edit_return, _("back"));
    //Write codes menu_edit_download
    ui->menu_edit_download = lv_textarea_create(ui->menu);

    const lv_font_t *menu_edit_download_font = _font("app");
    if (menu_edit_download_font == NULL) {
        menu_edit_download_font = &lv_font_FangZhengKaiTiJianTi_1_20;
    }

    //Set style for menu_edit_download. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_download, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_download, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu_edit_download, lv_color_make(0xFF, 0xA5, 0xA5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_edit_download, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_download, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_edit_download, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_edit_download, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_edit_download, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_edit_download, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_edit_download, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_edit_download, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_edit_download, menu_edit_download_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_edit_download, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_edit_download, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_edit_download, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_edit_download, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_edit_download, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_edit_download, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for menu_edit_download. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_download, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_download, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_download, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_edit_download, 299, 218);
    lv_obj_set_size(ui->menu_edit_download, 135, 42);
    lv_obj_set_scrollbar_mode(ui->menu_edit_download, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_edit_download, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->menu_edit_download);
    lv_textarea_set_text(ui->menu_edit_download, _("app"));
    //Write codes menu_edit_netcfg
    ui->menu_edit_netcfg = lv_textarea_create(ui->menu);

    const lv_font_t *menu_edit_netcfg_font = _font("netcfg");
    if (menu_edit_netcfg_font == NULL) {
        menu_edit_netcfg_font = &lv_font_FangZhengKaiTiJianTi_1_20;
    }

    //Set style for menu_edit_netcfg. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_netcfg, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_netcfg, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu_edit_netcfg, lv_color_make(0xFF, 0xA5, 0xA5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_edit_netcfg, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_netcfg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_edit_netcfg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_edit_netcfg, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_edit_netcfg, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_edit_netcfg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_edit_netcfg, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_edit_netcfg, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_edit_netcfg, menu_edit_netcfg_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_edit_netcfg, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_edit_netcfg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_edit_netcfg, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_edit_netcfg, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_edit_netcfg, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_edit_netcfg, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for menu_edit_netcfg. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_netcfg, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_netcfg, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_netcfg, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_edit_netcfg, 62, 452);
    lv_obj_set_size(ui->menu_edit_netcfg, 125, 42);
    lv_obj_set_scrollbar_mode(ui->menu_edit_netcfg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_edit_netcfg, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->menu_edit_netcfg);
    lv_textarea_set_text(ui->menu_edit_netcfg, _("netcfg"));
    //Write codes menu_edit_language
    ui->menu_edit_language = lv_textarea_create(ui->menu);

    const lv_font_t *menu_edit_language_font = _font("language");
    if (menu_edit_language_font == NULL) {
        menu_edit_language_font = &lv_font_FangZhengKaiTiJianTi_1_20;
    }

    //Set style for menu_edit_language. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_language, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_language, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu_edit_language, lv_color_make(0xFF, 0xA5, 0xA5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_edit_language, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_language, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_edit_language, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_edit_language, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_edit_language, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_edit_language, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_edit_language, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_edit_language, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_edit_language, menu_edit_language_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_edit_language, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_edit_language, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_edit_language, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_edit_language, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_edit_language, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_edit_language, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for menu_edit_language. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_language, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_language, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_language, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_edit_language, 302, 452);
    lv_obj_set_size(ui->menu_edit_language, 125, 42);
    lv_obj_set_scrollbar_mode(ui->menu_edit_language, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_edit_language, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->menu_edit_language);
    lv_textarea_set_text(ui->menu_edit_language, _("language"));
    //Write codes menu_edit_sysset
    ui->menu_edit_sysset = lv_textarea_create(ui->menu);

    const lv_font_t *menu_edit_sysset_font = _font("syscfg");
    if (menu_edit_sysset_font == NULL) {
        menu_edit_sysset_font = &lv_font_FangZhengKaiTiJianTi_1_20;
    }

    //Set style for menu_edit_sysset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_sysset, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_sysset, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu_edit_sysset, lv_color_make(0xFF, 0xA5, 0xA5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_edit_sysset, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_sysset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_edit_sysset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_edit_sysset, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_edit_sysset, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_edit_sysset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_edit_sysset, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_edit_sysset, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_edit_sysset, menu_edit_sysset_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_edit_sysset, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_edit_sysset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_edit_sysset, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_edit_sysset, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_edit_sysset, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_edit_sysset, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for menu_edit_sysset. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_sysset, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_sysset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_sysset, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_edit_sysset, 61, 680);
    lv_obj_set_size(ui->menu_edit_sysset, 125, 42);
    lv_obj_set_scrollbar_mode(ui->menu_edit_sysset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_edit_sysset, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->menu_edit_sysset);
    lv_textarea_set_text(ui->menu_edit_sysset, _("syscfg"));
    //Write codes menu_img_return
    ui->menu_img_return = lv_img_create(ui->menu);

    //Set style for menu_img_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_img_return, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_img_return, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_img_return, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_img_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->menu_img_return, lv_color_make(0xFF, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->menu_img_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_img_return, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_img_return, 61, 53);
    lv_obj_set_size(ui->menu_img_return, 120, 120);
    lv_obj_set_scrollbar_mode(ui->menu_img_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_img_return, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->menu_img_return, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_back.png");
#else
    lv_img_set_src(ui->menu_img_return, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600000f.rle");
#endif
    lv_img_set_pivot(ui->menu_img_return, 0, 0);
    lv_img_set_angle(ui->menu_img_return, 0);
    lv_img_set_zoom(ui->menu_img_return, 256);
    //Write codes menu_edit_sysinfo
    ui->menu_edit_sysinfo = lv_textarea_create(ui->menu);

    const lv_font_t *menu_edit_sysinfo_font = _font("sysinfo");
    if (menu_edit_sysinfo_font == NULL) {
        menu_edit_sysinfo_font = &lv_font_FangZhengKaiTiJianTi_1_18;
    }

    //Set style for menu_edit_sysinfo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_sysinfo, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_sysinfo, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->menu_edit_sysinfo, lv_color_make(0xFF, 0xA5, 0xA5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_edit_sysinfo, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_sysinfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_edit_sysinfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_edit_sysinfo, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_edit_sysinfo, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_edit_sysinfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_edit_sysinfo, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_edit_sysinfo, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_edit_sysinfo, menu_edit_sysinfo_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_edit_sysinfo, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_edit_sysinfo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_edit_sysinfo, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_edit_sysinfo, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_edit_sysinfo, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_edit_sysinfo, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for menu_edit_sysinfo. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_edit_sysinfo, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_edit_sysinfo, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_edit_sysinfo, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_edit_sysinfo, 299, 680);
    lv_obj_set_size(ui->menu_edit_sysinfo, 135, 42);
    lv_obj_set_scrollbar_mode(ui->menu_edit_sysinfo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_edit_sysinfo, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->menu_edit_sysinfo);
    lv_textarea_set_text(ui->menu_edit_sysinfo, _("sysinfo"));
    //Write codes menu_img_download
    ui->menu_img_download = lv_img_create(ui->menu);

    //Set style for menu_img_download. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_img_download, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_img_download, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_img_download, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_img_download, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->menu_img_download, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->menu_img_download, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_img_download, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_img_download, 302, 53);
    lv_obj_set_size(ui->menu_img_download, 120, 120);
    lv_obj_set_scrollbar_mode(ui->menu_img_download, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_img_download, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->menu_img_download, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_download.png");
#else
    lv_img_set_src(ui->menu_img_download, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000010.rle");
#endif
    lv_img_set_pivot(ui->menu_img_download, 0, 0);
    lv_img_set_angle(ui->menu_img_download, 0);
    lv_img_set_zoom(ui->menu_img_download, 256);
    //Write codes menu_img_netcfg
    ui->menu_img_netcfg = lv_img_create(ui->menu);

    //Set style for menu_img_netcfg. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_img_netcfg, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_img_netcfg, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_img_netcfg, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_img_netcfg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->menu_img_netcfg, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->menu_img_netcfg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_img_netcfg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_img_netcfg, 61, 307);
    lv_obj_set_size(ui->menu_img_netcfg, 120, 120);
    lv_obj_set_scrollbar_mode(ui->menu_img_netcfg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_img_netcfg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->menu_img_netcfg, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_confnet.png");
#else
    lv_img_set_src(ui->menu_img_netcfg, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000011.rle");
#endif
    lv_img_set_pivot(ui->menu_img_netcfg, 0, 0);
    lv_img_set_angle(ui->menu_img_netcfg, 0);
    lv_img_set_zoom(ui->menu_img_netcfg, 256);
    //Write codes menu_img_language
    ui->menu_img_language = lv_img_create(ui->menu);

    //Set style for menu_img_language. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_img_language, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_img_language, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_img_language, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_img_language, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->menu_img_language, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->menu_img_language, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_img_language, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_img_language, 302, 308);
    lv_obj_set_size(ui->menu_img_language, 120, 120);
    lv_obj_set_scrollbar_mode(ui->menu_img_language, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_img_language, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->menu_img_language, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_language.png");
#else
    lv_img_set_src(ui->menu_img_language, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000012.rle");
#endif
    lv_img_set_pivot(ui->menu_img_language, 0, 0);
    lv_img_set_angle(ui->menu_img_language, 0);
    lv_img_set_zoom(ui->menu_img_language, 256);
    //Write codes menu_img_sysset
    ui->menu_img_sysset = lv_img_create(ui->menu);

    //Set style for menu_img_sysset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_img_sysset, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_img_sysset, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_img_sysset, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_img_sysset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->menu_img_sysset, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->menu_img_sysset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_img_sysset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_img_sysset, 61, 532);
    lv_obj_set_size(ui->menu_img_sysset, 120, 120);
    lv_obj_set_scrollbar_mode(ui->menu_img_sysset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_img_sysset, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->menu_img_sysset, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_settle.png");
#else
    lv_img_set_src(ui->menu_img_sysset, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000013.rle");
#endif
    lv_img_set_pivot(ui->menu_img_sysset, 0, 0);
    lv_img_set_angle(ui->menu_img_sysset, 0);
    lv_img_set_zoom(ui->menu_img_sysset, 256);
    //Write codes menu_img_sysinfo
    ui->menu_img_sysinfo = lv_img_create(ui->menu);

    //Set style for menu_img_sysinfo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->menu_img_sysinfo, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_img_sysinfo, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_img_sysinfo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_img_sysinfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->menu_img_sysinfo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->menu_img_sysinfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_img_sysinfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->menu_img_sysinfo, 307, 532);
    lv_obj_set_size(ui->menu_img_sysinfo, 120, 120);
    lv_obj_set_scrollbar_mode(ui->menu_img_sysinfo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_img_sysinfo, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->menu_img_sysinfo, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_about.png");
#else
    lv_img_set_src(ui->menu_img_sysinfo, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000014.rle");
#endif
    lv_img_set_pivot(ui->menu_img_sysinfo, 0, 0);
    lv_img_set_angle(ui->menu_img_sysinfo, 0);
    lv_img_set_zoom(ui->menu_img_sysinfo, 256);
    lv_obj_update_layout(ui->menu);
    ui->menu_del = false;

    //Init events for screen
    events_init_menu(ui);
    return ui->menu;
}
void unload_scr_menu(lv_ui *ui)
{
    ui->menu_del = true;
}

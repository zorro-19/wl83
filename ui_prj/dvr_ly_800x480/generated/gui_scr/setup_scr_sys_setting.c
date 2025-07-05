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


lv_obj_t * setup_scr_sys_setting(lv_ui *ui)
{
	//Write codes sys_setting
	ui->sys_setting = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for sys_setting. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->sys_setting, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->sys_setting, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_menu_b
	ui->sys_setting_view_menu_b = lv_obj_create(ui->sys_setting);

	//Set style for sys_setting_view_menu_b. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_menu_b, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_view_menu_b, 0, 0);
	lv_obj_set_size(ui->sys_setting_view_menu_b, 800, 480);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_menu_b, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_menu
	ui->sys_setting_view_menu = lv_obj_create(ui->sys_setting_view_menu_b);

	//Set style for sys_setting_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_menu, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_view_menu, 0, 40);
	lv_obj_set_size(ui->sys_setting_view_menu, 800, 400);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_menu, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_pro
	ui->sys_setting_view_pro = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_pro. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_pro, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_pro. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_pro, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_pro, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_pro, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_pro, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_pro, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_pro, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_pro, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_pro, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_pro, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_pro, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_pro, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_pro, 0, 0);
	lv_obj_set_size(ui->sys_setting_view_pro, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_pro, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_pro, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_pro, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_pro);
	//Write codes sys_setting_img_1
	ui->sys_setting_img_1 = lv_img_create(ui->sys_setting_view_pro);
	lv_img_set_src(ui->sys_setting_img_1, gui_get_res_path(GUI_RES_LCD_AU_PNG));
	lv_img_set_pivot(ui->sys_setting_img_1, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_1, 0);
	lv_img_set_zoom(ui->sys_setting_img_1, 256);

	//Set style for sys_setting_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_1, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_1, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_1, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_1
	ui->sys_setting_lbl_1 = lv_label_create(ui->sys_setting_view_pro);
	lv_label_set_text(ui->sys_setting_lbl_1, _("lcdprotect"));
	lv_label_set_long_mode(ui->sys_setting_lbl_1, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_1_font = _font("lcdprotect");
	if(sys_setting_lbl_1_font == NULL) sys_setting_lbl_1_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_1, sys_setting_lbl_1_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_1, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_1, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_autof
	ui->sys_setting_view_autof = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_autof. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_autof, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_autof. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_autof, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_autof, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_autof, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_autof, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_autof, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_autof, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_autof, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_autof, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_autof, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_autof, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_autof, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_autof, 0, 45);
	lv_obj_set_size(ui->sys_setting_view_autof, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_autof, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_autof, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_autof, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_autof);
	//Write codes sys_setting_img_2
	ui->sys_setting_img_2 = lv_img_create(ui->sys_setting_view_autof);
	lv_img_set_src(ui->sys_setting_img_2, gui_get_res_path(GUI_RES_AUTO_OFF_PNG));
	lv_img_set_pivot(ui->sys_setting_img_2, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_2, 0);
	lv_img_set_zoom(ui->sys_setting_img_2, 256);

	//Set style for sys_setting_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_2, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_2, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_2, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_2
	ui->sys_setting_lbl_2 = lv_label_create(ui->sys_setting_view_autof);
	lv_label_set_text(ui->sys_setting_lbl_2, _("poweroff"));
	lv_label_set_long_mode(ui->sys_setting_lbl_2, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_2_font = _font("poweroff");
	if(sys_setting_lbl_2_font == NULL) sys_setting_lbl_2_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_2, sys_setting_lbl_2_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_2, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_2, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_2, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_hz
	ui->sys_setting_view_hz = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_hz. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_hz, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_hz. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_hz, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_hz, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_hz, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_hz, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_hz, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_hz, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_hz, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_hz, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_hz, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_hz, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_hz, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_hz, 0, 90);
	lv_obj_set_size(ui->sys_setting_view_hz, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_hz, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_hz, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_hz, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_hz);
	//Write codes sys_setting_img_3
	ui->sys_setting_img_3 = lv_img_create(ui->sys_setting_view_hz);
	lv_img_set_src(ui->sys_setting_img_3, gui_get_res_path(GUI_RES_HZ_PNG));
	lv_img_set_pivot(ui->sys_setting_img_3, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_3, 0);
	lv_img_set_zoom(ui->sys_setting_img_3, 256);

	//Set style for sys_setting_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_3, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_3, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_3, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_3
	ui->sys_setting_lbl_3 = lv_label_create(ui->sys_setting_view_hz);
	lv_label_set_text(ui->sys_setting_lbl_3, _("frequency"));
	lv_label_set_long_mode(ui->sys_setting_lbl_3, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_3_font = _font("frequency");
	if(sys_setting_lbl_3_font == NULL) sys_setting_lbl_3_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_3, sys_setting_lbl_3_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_3, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_3, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_3, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_kvo
	ui->sys_setting_view_kvo = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_kvo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_kvo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_kvo. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_kvo, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_kvo, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_kvo, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_kvo, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_kvo, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_kvo, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_kvo, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_kvo, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_kvo, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_kvo, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_kvo, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_kvo, 0, 135);
	lv_obj_set_size(ui->sys_setting_view_kvo, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_kvo, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_kvo, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_kvo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_kvo);
	//Write codes sys_setting_img_4
	ui->sys_setting_img_4 = lv_img_create(ui->sys_setting_view_kvo);
	lv_img_set_src(ui->sys_setting_img_4, gui_get_res_path(GUI_RES_KEY_V_PNG));
	lv_img_set_pivot(ui->sys_setting_img_4, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_4, 0);
	lv_img_set_zoom(ui->sys_setting_img_4, 256);

	//Set style for sys_setting_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_4, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_4, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_4, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_4
	ui->sys_setting_lbl_4 = lv_label_create(ui->sys_setting_view_kvo);
	lv_label_set_text(ui->sys_setting_lbl_4, _("speaker"));
	lv_label_set_long_mode(ui->sys_setting_lbl_4, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_4_font = _font("speaker");
	if(sys_setting_lbl_4_font == NULL) sys_setting_lbl_4_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_4, sys_setting_lbl_4_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_4, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_4, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_4, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_lag
	ui->sys_setting_view_lag = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_lag. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_lag, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_lag. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_lag, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_lag, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_lag, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_lag, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_lag, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_lag, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_lag, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_lag, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_lag, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_lag, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_lag, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_lag, 0, 180);
	lv_obj_set_size(ui->sys_setting_view_lag, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_lag, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_lag, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_lag, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_lag);
	//Write codes sys_setting_img_5
	ui->sys_setting_img_5 = lv_img_create(ui->sys_setting_view_lag);
	lv_img_set_src(ui->sys_setting_img_5, gui_get_res_path(GUI_RES_LANGUAGE_PNG));
	lv_img_set_pivot(ui->sys_setting_img_5, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_5, 0);
	lv_img_set_zoom(ui->sys_setting_img_5, 256);

	//Set style for sys_setting_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_5, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_5, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_5, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_5
	ui->sys_setting_lbl_5 = lv_label_create(ui->sys_setting_view_lag);
	lv_label_set_text(ui->sys_setting_lbl_5, _("language"));
	lv_label_set_long_mode(ui->sys_setting_lbl_5, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_5_font = _font("language");
	if(sys_setting_lbl_5_font == NULL) sys_setting_lbl_5_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_5, sys_setting_lbl_5_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_5, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_5, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_5, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_time
	ui->sys_setting_view_time = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_time, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_time. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_time, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_time, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_time, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_time, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_time, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_time, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_time, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_time, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_time, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_time, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_time, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_time, 0, 225);
	lv_obj_set_size(ui->sys_setting_view_time, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_time, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_time, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_time, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_time);
	//Write codes sys_setting_img_6
	ui->sys_setting_img_6 = lv_img_create(ui->sys_setting_view_time);
	lv_img_set_src(ui->sys_setting_img_6, gui_get_res_path(GUI_RES_TIME_PNG));
	lv_img_set_pivot(ui->sys_setting_img_6, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_6, 0);
	lv_img_set_zoom(ui->sys_setting_img_6, 256);

	//Set style for sys_setting_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_6, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_6, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_6, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_6
	ui->sys_setting_lbl_6 = lv_label_create(ui->sys_setting_view_time);
	lv_label_set_text(ui->sys_setting_lbl_6, _("date"));
	lv_label_set_long_mode(ui->sys_setting_lbl_6, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_6_font = _font("date");
	if(sys_setting_lbl_6_font == NULL) sys_setting_lbl_6_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_6, sys_setting_lbl_6_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_6, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_6, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_6, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_tv
	ui->sys_setting_view_tv = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_tv. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_tv, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_tv. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_tv, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_tv, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_tv, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_tv, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_tv, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_tv, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_tv, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_tv, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_tv, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_tv, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_tv, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_tv, 0, 270);
	lv_obj_set_size(ui->sys_setting_view_tv, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_tv, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_tv, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_tv, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_tv);
	//Write codes sys_setting_img_7
	ui->sys_setting_img_7 = lv_img_create(ui->sys_setting_view_tv);
	lv_img_set_src(ui->sys_setting_img_7, gui_get_res_path(GUI_RES_TV_PNG));
	lv_img_set_pivot(ui->sys_setting_img_7, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_7, 0);
	lv_img_set_zoom(ui->sys_setting_img_7, 256);

	//Set style for sys_setting_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_7, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_7, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_7, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_7
	ui->sys_setting_lbl_7 = lv_label_create(ui->sys_setting_view_tv);
	lv_label_set_text(ui->sys_setting_lbl_7, _("tv_mode"));
	lv_label_set_long_mode(ui->sys_setting_lbl_7, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_7_font = _font("tv_mode");
	if(sys_setting_lbl_7_font == NULL) sys_setting_lbl_7_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_7, sys_setting_lbl_7_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_7, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_7, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_7, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_format
	ui->sys_setting_view_format = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_format. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_format, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_format. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_format, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_format, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_format, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_format, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_format, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_format, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_format, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_format, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_format, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_format, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_format, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_format, 0, 315);
	lv_obj_set_size(ui->sys_setting_view_format, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_format, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_format, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_format, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_format);
	//Write codes sys_setting_img_8
	ui->sys_setting_img_8 = lv_img_create(ui->sys_setting_view_format);
	lv_img_set_src(ui->sys_setting_img_8, gui_get_res_path(GUI_RES_MDK_PNG));
	lv_img_set_pivot(ui->sys_setting_img_8, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_8, 0);
	lv_img_set_zoom(ui->sys_setting_img_8, 256);

	//Set style for sys_setting_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_8, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_8, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_8, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_8, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_8
	ui->sys_setting_lbl_8 = lv_label_create(ui->sys_setting_view_format);
	lv_label_set_text(ui->sys_setting_lbl_8, _("formatting"));
	lv_label_set_long_mode(ui->sys_setting_lbl_8, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_8_font = _font("formatting");
	if(sys_setting_lbl_8_font == NULL) sys_setting_lbl_8_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_8, sys_setting_lbl_8_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_8, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_8, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_8, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_reset
	ui->sys_setting_view_reset = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_reset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_reset, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_reset. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_reset, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_reset, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_reset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_reset, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_reset, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_reset, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_reset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_reset, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_reset, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_reset, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_reset, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_reset, 0, 360);
	lv_obj_set_size(ui->sys_setting_view_reset, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_reset, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_reset, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_reset, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_reset);
	//Write codes sys_setting_img_9
	ui->sys_setting_img_9 = lv_img_create(ui->sys_setting_view_reset);
	lv_img_set_src(ui->sys_setting_img_9, gui_get_res_path(GUI_RES_DEF_SET_PNG));
	lv_img_set_pivot(ui->sys_setting_img_9, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_9, 0);
	lv_img_set_zoom(ui->sys_setting_img_9, 256);

	//Set style for sys_setting_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_9, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_9, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_9, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_9, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_9
	ui->sys_setting_lbl_9 = lv_label_create(ui->sys_setting_view_reset);
	lv_label_set_text(ui->sys_setting_lbl_9, _("reset"));
	lv_label_set_long_mode(ui->sys_setting_lbl_9, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_9_font = _font("reset");
	if(sys_setting_lbl_9_font == NULL) sys_setting_lbl_9_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_9, sys_setting_lbl_9_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_9, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_9, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_9, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_view_ver
	ui->sys_setting_view_ver = lv_obj_create(ui->sys_setting_view_menu);

	//Set style for sys_setting_view_ver. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_ver, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_view_ver. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_view_ver, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_ver, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_view_ver, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_view_ver, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_view_ver, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_view_ver, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_view_ver, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_view_ver, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_view_ver, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_view_ver, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_ver, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_view_ver, 0, 405);
	lv_obj_set_size(ui->sys_setting_view_ver, 800, 43);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_ver, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_ver, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->sys_setting_view_ver, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->sys_setting_view_ver);
	//Write codes sys_setting_img_10
	ui->sys_setting_img_10 = lv_img_create(ui->sys_setting_view_ver);
	lv_img_set_src(ui->sys_setting_img_10, gui_get_res_path(GUI_RES_VERSION_PNG));
	lv_img_set_pivot(ui->sys_setting_img_10, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_10, 0);
	lv_img_set_zoom(ui->sys_setting_img_10, 256);

	//Set style for sys_setting_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_10, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_10, 8, 6);
	lv_obj_set_size(ui->sys_setting_img_10, 29, 29);
	lv_obj_add_flag(ui->sys_setting_img_10, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_lbl_10
	ui->sys_setting_lbl_10 = lv_label_create(ui->sys_setting_view_ver);
	lv_label_set_text(ui->sys_setting_lbl_10, _("ver"));
	lv_label_set_long_mode(ui->sys_setting_lbl_10, LV_LABEL_LONG_WRAP);

	const lv_font_t * sys_setting_lbl_10_font = _font("ver");
	if(sys_setting_lbl_10_font == NULL) sys_setting_lbl_10_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for sys_setting_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_10, sys_setting_lbl_10_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_10, 50, 6);
	lv_obj_set_size(ui->sys_setting_lbl_10, 200, 32);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_10, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_img_11
	ui->sys_setting_img_11 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_11, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->sys_setting_img_11, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_11, 0);
	lv_img_set_zoom(ui->sys_setting_img_11, 256);

	//Set style for sys_setting_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_11, 0, 0);
	lv_obj_set_size(ui->sys_setting_img_11, 800, 40);
	lv_obj_add_flag(ui->sys_setting_img_11, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_12
	ui->sys_setting_img_12 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_12, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->sys_setting_img_12, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_12, 0);
	lv_img_set_zoom(ui->sys_setting_img_12, 256);

	//Set style for sys_setting_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_12, 0, 440);
	lv_obj_set_size(ui->sys_setting_img_12, 800, 40);
	lv_obj_add_flag(ui->sys_setting_img_12, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_13
	ui->sys_setting_img_13 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_13, gui_get_res_path(GUI_RES_REC_PNG));
	lv_img_set_pivot(ui->sys_setting_img_13, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_13, 0);
	lv_img_set_zoom(ui->sys_setting_img_13, 256);

	//Set style for sys_setting_img_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_13, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_13, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_13, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_13, 9, 5);
	lv_obj_set_size(ui->sys_setting_img_13, 40, 30);
	lv_obj_add_flag(ui->sys_setting_img_13, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_14
	ui->sys_setting_img_14 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_14, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui->sys_setting_img_14, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_14, 0);
	lv_img_set_zoom(ui->sys_setting_img_14, 256);

	//Set style for sys_setting_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_14, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_img_14, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_img_14, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_14, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_14, 70, 1);
	lv_obj_set_size(ui->sys_setting_img_14, 37, 37);
	lv_obj_add_flag(ui->sys_setting_img_14, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_15
	ui->sys_setting_img_15 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_15, gui_get_res_path(GUI_RES_LEFT_PNG));
	lv_img_set_pivot(ui->sys_setting_img_15, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_15, 0);
	lv_img_set_zoom(ui->sys_setting_img_15, 256);

	//Set style for sys_setting_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_15, 200, 445);
	lv_obj_set_size(ui->sys_setting_img_15, 21, 29);
	lv_obj_add_flag(ui->sys_setting_img_15, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_16
	ui->sys_setting_img_16 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_16, gui_get_res_path(GUI_RES_UP_PNG));
	lv_img_set_pivot(ui->sys_setting_img_16, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_16, 0);
	lv_img_set_zoom(ui->sys_setting_img_16, 256);

	//Set style for sys_setting_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_16, 321, 448);
	lv_obj_set_size(ui->sys_setting_img_16, 29, 21);
	lv_obj_add_flag(ui->sys_setting_img_16, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_17
	ui->sys_setting_img_17 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_17, gui_get_res_path(GUI_RES_DOWN_PNG));
	lv_img_set_pivot(ui->sys_setting_img_17, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_17, 0);
	lv_img_set_zoom(ui->sys_setting_img_17, 256);

	//Set style for sys_setting_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_17, 450, 448);
	lv_obj_set_size(ui->sys_setting_img_17, 29, 21);
	lv_obj_add_flag(ui->sys_setting_img_17, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_18
	ui->sys_setting_img_18 = lv_img_create(ui->sys_setting_view_menu_b);
	lv_img_set_src(ui->sys_setting_img_18, gui_get_res_path(GUI_RES_RIGHT_PNG));
	lv_img_set_pivot(ui->sys_setting_img_18, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_18, 0);
	lv_img_set_zoom(ui->sys_setting_img_18, 256);

	//Set style for sys_setting_img_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_18, 579, 445);
	lv_obj_set_size(ui->sys_setting_img_18, 21, 29);
	lv_obj_add_flag(ui->sys_setting_img_18, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_view_submenu
	ui->sys_setting_view_submenu = lv_obj_create(ui->sys_setting);

	//Set style for sys_setting_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_submenu, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_view_submenu, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_submenu, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_view_submenu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_view_submenu, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_view_submenu, 111, 83);
	lv_obj_set_size(ui->sys_setting_view_submenu, 590, 314);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_submenu, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
	//Write codes sys_setting_submenu_btn_1
	ui->sys_setting_submenu_btn_1 = lv_btn_create(ui->sys_setting_view_submenu);

	//Set style for sys_setting_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_1, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_1, 203, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_1, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_submenu_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_1, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_1, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_1, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_1, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_submenu_btn_1, 83, 44);
	lv_obj_set_size(ui->sys_setting_submenu_btn_1, 438, 37);
	lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->sys_setting_submenu_btn_1_label = lv_label_create(ui->sys_setting_submenu_btn_1);
	lv_label_set_text(ui->sys_setting_submenu_btn_1_label, "button1");
	lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->sys_setting_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes sys_setting_submenu_btn_2
	ui->sys_setting_submenu_btn_2 = lv_btn_create(ui->sys_setting_view_submenu);

	//Set style for sys_setting_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_2, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_2, 215, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_2, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_submenu_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_2, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_2, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_2, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_submenu_btn_2, 83, 111);
	lv_obj_set_size(ui->sys_setting_submenu_btn_2, 438, 37);
	lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->sys_setting_submenu_btn_2_label = lv_label_create(ui->sys_setting_submenu_btn_2);
	lv_label_set_text(ui->sys_setting_submenu_btn_2_label, "button2");
	lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->sys_setting_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes sys_setting_submenu_btn_3
	ui->sys_setting_submenu_btn_3 = lv_btn_create(ui->sys_setting_view_submenu);

	//Set style for sys_setting_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_3, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_3, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_3, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_3, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_submenu_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_3, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_3, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_3, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_submenu_btn_3, 83, 171);
	lv_obj_set_size(ui->sys_setting_submenu_btn_3, 438, 37);
	lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->sys_setting_submenu_btn_3_label = lv_label_create(ui->sys_setting_submenu_btn_3);
	lv_label_set_text(ui->sys_setting_submenu_btn_3_label, "button3");
	lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->sys_setting_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes sys_setting_submenu_btn_4
	ui->sys_setting_submenu_btn_4 = lv_btn_create(ui->sys_setting_view_submenu);

	//Set style for sys_setting_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_4, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_4, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_4, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_4, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_submenu_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_submenu_btn_4, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_4, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_submenu_btn_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_submenu_btn_4, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_submenu_btn_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_submenu_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_submenu_btn_4, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->sys_setting_submenu_btn_4, 83, 233);
	lv_obj_set_size(ui->sys_setting_submenu_btn_4, 438, 37);
	lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->sys_setting_submenu_btn_4_label = lv_label_create(ui->sys_setting_submenu_btn_4);
	lv_label_set_text(ui->sys_setting_submenu_btn_4_label, "button4");
	lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->sys_setting_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes sys_setting_roller_mutifunc
	ui->sys_setting_roller_mutifunc = lv_roller_create(ui->sys_setting_view_submenu);

	//Set style for sys_setting_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_roller_mutifunc, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_roller_mutifunc, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_roller_mutifunc, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_roller_mutifunc, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_line_space(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_align(ui->sys_setting_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->sys_setting_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style for sys_setting_roller_mutifunc. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->sys_setting_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_roller_mutifunc, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_roller_mutifunc, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_roller_mutifunc, 0, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_roller_mutifunc, 198, 55);
	lv_obj_set_size(ui->sys_setting_roller_mutifunc, 198, 130);
	lv_obj_set_scrollbar_mode(ui->sys_setting_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_roller_mutifunc, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_roller_set_options(ui->sys_setting_roller_mutifunc,"1\n2\n3\n4\n5",LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->sys_setting_roller_mutifunc,3);
	//Write codes sys_setting_lbl_submenu_warning
	ui->sys_setting_lbl_submenu_warning = lv_label_create(ui->sys_setting_view_submenu);
	lv_label_set_text(ui->sys_setting_lbl_submenu_warning, "格式化\n删除所有数据\n恢复默认设置？");
	lv_label_set_long_mode(ui->sys_setting_lbl_submenu_warning, LV_LABEL_LONG_WRAP);

	//Set style for sys_setting_lbl_submenu_warning. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_lbl_submenu_warning, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_lbl_submenu_warning, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_lbl_submenu_warning, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_lbl_submenu_warning, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->sys_setting_lbl_submenu_warning, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_lbl_submenu_warning, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_lbl_submenu_warning, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_lbl_submenu_warning, 81, 40);
	lv_obj_set_size(ui->sys_setting_lbl_submenu_warning, 445, 112);
	lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_submenu_warning, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_lbl_submenu_warning, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_group_add_obj(def_group, ui->sys_setting_lbl_submenu_warning);
	//Write codes sys_setting_view_time_mun
	ui->sys_setting_view_time_mun = lv_obj_create(ui->sys_setting_view_submenu);

	//Set style for sys_setting_view_time_mun. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_view_time_mun, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->sys_setting_view_time_mun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_view_time_mun, 76, 44);
	lv_obj_set_size(ui->sys_setting_view_time_mun, 450, 164);
	lv_obj_set_scrollbar_mode(ui->sys_setting_view_time_mun, LV_SCROLLBAR_MODE_OFF);
	//Write codes sys_setting_ddlist_year
	ui->sys_setting_ddlist_year = lv_dropdown_create(ui->sys_setting_view_time_mun);
	lv_dropdown_set_options(ui->sys_setting_ddlist_year, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->sys_setting_ddlist_year, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_year, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_year, NULL);
	lv_dropdown_set_selected(ui->sys_setting_ddlist_year, 0);

	//Set style for sys_setting_ddlist_year. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_ddlist_year, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_year, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_year, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_year, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_year, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_year, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_year, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_year, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_year, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_year, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_year, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_year, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_year, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_year, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_ddlist_year. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_ddlist_year, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_year, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_year, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_year, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_year, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_year, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_year, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_year, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_year, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_year, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_year, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_year, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_year, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_year, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_year, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_year, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_year, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_year, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_year_extra_list_selected_checked
	static lv_style_t style_sys_setting_ddlist_year_extra_list_selected_checked;
	ui_init_style(&style_sys_setting_ddlist_year_extra_list_selected_checked);
	lv_style_set_radius(&style_sys_setting_ddlist_year_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_year_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_year_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_sys_setting_ddlist_year_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_year_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_year_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_year_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_year_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_sys_setting_ddlist_year_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_year_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &style_sys_setting_ddlist_year_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_year_extra_list_main_default
	static lv_style_t style_sys_setting_ddlist_year_extra_list_main_default;
	ui_init_style(&style_sys_setting_ddlist_year_extra_list_main_default);
	lv_style_set_radius(&style_sys_setting_ddlist_year_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_year_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_year_extra_list_main_default, 255);
	lv_style_set_border_color(&style_sys_setting_ddlist_year_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_year_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_year_extra_list_main_default, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_year_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_year_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_sys_setting_ddlist_year_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_year_extra_list_main_default, 0);
	lv_style_set_max_height(&style_sys_setting_ddlist_year_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &style_sys_setting_ddlist_year_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_year_extra_list_scrollbar_default
	static lv_style_t style_sys_setting_ddlist_year_extra_list_scrollbar_default;
	ui_init_style(&style_sys_setting_ddlist_year_extra_list_scrollbar_default);
	lv_style_set_radius(&style_sys_setting_ddlist_year_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_year_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_year_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &style_sys_setting_ddlist_year_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_ddlist_year, 38, 26);
	lv_obj_set_size(ui->sys_setting_ddlist_year, 87, 31);
	lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_year, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_ddlist_year, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes sys_setting_ddlist_month
	ui->sys_setting_ddlist_month = lv_dropdown_create(ui->sys_setting_view_time_mun);
	lv_dropdown_set_options(ui->sys_setting_ddlist_month, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->sys_setting_ddlist_month, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_month, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_month, NULL);
	lv_dropdown_set_selected(ui->sys_setting_ddlist_month, 0);

	//Set style for sys_setting_ddlist_month. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_ddlist_month, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_month, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_month, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_month, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_month, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_month, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_month, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_month, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_month, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_month, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_month, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_month, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_month, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_month, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_ddlist_month. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_ddlist_month, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_month, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_month, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_month, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_month, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_month, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_month, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_month, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_month, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_month, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_month, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_month, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_month, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_month, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_month, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_month, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_month, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_month, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_month_extra_list_selected_checked
	static lv_style_t style_sys_setting_ddlist_month_extra_list_selected_checked;
	ui_init_style(&style_sys_setting_ddlist_month_extra_list_selected_checked);
	lv_style_set_radius(&style_sys_setting_ddlist_month_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_month_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_month_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_sys_setting_ddlist_month_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_month_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_month_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_month_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_month_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_sys_setting_ddlist_month_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_month_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &style_sys_setting_ddlist_month_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_month_extra_list_main_default
	static lv_style_t style_sys_setting_ddlist_month_extra_list_main_default;
	ui_init_style(&style_sys_setting_ddlist_month_extra_list_main_default);
	lv_style_set_radius(&style_sys_setting_ddlist_month_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_month_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_month_extra_list_main_default, 255);
	lv_style_set_border_color(&style_sys_setting_ddlist_month_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_month_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_month_extra_list_main_default, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_month_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_month_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_sys_setting_ddlist_month_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_month_extra_list_main_default, 0);
	lv_style_set_max_height(&style_sys_setting_ddlist_month_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &style_sys_setting_ddlist_month_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_month_extra_list_scrollbar_default
	static lv_style_t style_sys_setting_ddlist_month_extra_list_scrollbar_default;
	ui_init_style(&style_sys_setting_ddlist_month_extra_list_scrollbar_default);
	lv_style_set_radius(&style_sys_setting_ddlist_month_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_month_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_month_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &style_sys_setting_ddlist_month_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_ddlist_month, 190, 26);
	lv_obj_set_size(ui->sys_setting_ddlist_month, 69, 31);
	lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_month, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_ddlist_month, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes sys_setting_ddlist_day
	ui->sys_setting_ddlist_day = lv_dropdown_create(ui->sys_setting_view_time_mun);
	lv_dropdown_set_options(ui->sys_setting_ddlist_day, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->sys_setting_ddlist_day, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_day, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_day, NULL);
	lv_dropdown_set_selected(ui->sys_setting_ddlist_day, 0);

	//Set style for sys_setting_ddlist_day. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_ddlist_day, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_day, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_day, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_day, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_day, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_day, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_day, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_day, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_day, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_day, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_day, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_day, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_ddlist_day. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_ddlist_day, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_day, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_day, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_day, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_day, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_day, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_day, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_day, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_day, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_day, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_day, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_day, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_day, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_day, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_day, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_day, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_day, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_day, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_day_extra_list_selected_checked
	static lv_style_t style_sys_setting_ddlist_day_extra_list_selected_checked;
	ui_init_style(&style_sys_setting_ddlist_day_extra_list_selected_checked);
	lv_style_set_radius(&style_sys_setting_ddlist_day_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_day_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_day_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_sys_setting_ddlist_day_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_day_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_day_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_day_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_day_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_sys_setting_ddlist_day_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_day_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &style_sys_setting_ddlist_day_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_day_extra_list_main_default
	static lv_style_t style_sys_setting_ddlist_day_extra_list_main_default;
	ui_init_style(&style_sys_setting_ddlist_day_extra_list_main_default);
	lv_style_set_radius(&style_sys_setting_ddlist_day_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_day_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_day_extra_list_main_default, 255);
	lv_style_set_border_color(&style_sys_setting_ddlist_day_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_day_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_day_extra_list_main_default, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_day_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_day_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_sys_setting_ddlist_day_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_day_extra_list_main_default, 0);
	lv_style_set_max_height(&style_sys_setting_ddlist_day_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &style_sys_setting_ddlist_day_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_day_extra_list_scrollbar_default
	static lv_style_t style_sys_setting_ddlist_day_extra_list_scrollbar_default;
	ui_init_style(&style_sys_setting_ddlist_day_extra_list_scrollbar_default);
	lv_style_set_radius(&style_sys_setting_ddlist_day_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_day_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_day_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &style_sys_setting_ddlist_day_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_ddlist_day, 328, 26);
	lv_obj_set_size(ui->sys_setting_ddlist_day, 69, 31);
	lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_day, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_ddlist_day, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes sys_setting_ddlist_hour
	ui->sys_setting_ddlist_hour = lv_dropdown_create(ui->sys_setting_view_time_mun);
	lv_dropdown_set_options(ui->sys_setting_ddlist_hour, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->sys_setting_ddlist_hour, LV_DIR_TOP);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_hour, LV_SYMBOL_UP);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_hour, NULL);
	lv_dropdown_set_selected(ui->sys_setting_ddlist_hour, 0);

	//Set style for sys_setting_ddlist_hour. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_ddlist_hour, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_hour, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_hour, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_hour, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_hour, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_hour, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_hour, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_hour, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_hour, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_hour, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_hour, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_hour, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_ddlist_hour. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_ddlist_hour, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_hour, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_hour, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_hour, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_hour, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_hour, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_hour, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_hour, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_hour, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_hour, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_hour, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_hour, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_hour, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_hour, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_hour, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_hour, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_hour, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_hour, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_hour_extra_list_selected_checked
	static lv_style_t style_sys_setting_ddlist_hour_extra_list_selected_checked;
	ui_init_style(&style_sys_setting_ddlist_hour_extra_list_selected_checked);
	lv_style_set_radius(&style_sys_setting_ddlist_hour_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_hour_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_hour_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_sys_setting_ddlist_hour_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_hour_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_hour_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_hour_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_hour_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_sys_setting_ddlist_hour_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_hour_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &style_sys_setting_ddlist_hour_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_hour_extra_list_main_default
	static lv_style_t style_sys_setting_ddlist_hour_extra_list_main_default;
	ui_init_style(&style_sys_setting_ddlist_hour_extra_list_main_default);
	lv_style_set_radius(&style_sys_setting_ddlist_hour_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_hour_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_hour_extra_list_main_default, 255);
	lv_style_set_border_color(&style_sys_setting_ddlist_hour_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_hour_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_hour_extra_list_main_default, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_hour_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_hour_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_sys_setting_ddlist_hour_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_hour_extra_list_main_default, 0);
	lv_style_set_max_height(&style_sys_setting_ddlist_hour_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &style_sys_setting_ddlist_hour_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_hour_extra_list_scrollbar_default
	static lv_style_t style_sys_setting_ddlist_hour_extra_list_scrollbar_default;
	ui_init_style(&style_sys_setting_ddlist_hour_extra_list_scrollbar_default);
	lv_style_set_radius(&style_sys_setting_ddlist_hour_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_hour_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_hour_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &style_sys_setting_ddlist_hour_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_ddlist_hour, 52, 102);
	lv_obj_set_size(ui->sys_setting_ddlist_hour, 69, 31);
	lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_hour, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_ddlist_hour, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes sys_setting_ddlist_min
	ui->sys_setting_ddlist_min = lv_dropdown_create(ui->sys_setting_view_time_mun);
	lv_dropdown_set_options(ui->sys_setting_ddlist_min, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->sys_setting_ddlist_min, LV_DIR_TOP);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_min, LV_SYMBOL_UP);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_min, NULL);
	lv_dropdown_set_selected(ui->sys_setting_ddlist_min, 0);

	//Set style for sys_setting_ddlist_min. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_ddlist_min, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_min, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_min, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_min, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_min, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_min, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_min, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_min, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_min, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_min, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_min, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_min, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_min, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_min, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_ddlist_min. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_ddlist_min, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_min, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_min, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_min, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_min, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_min, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_min, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_min, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_min, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_min, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_min, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_min, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_min, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_min, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_min, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_min, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_min, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_min, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_min_extra_list_selected_checked
	static lv_style_t style_sys_setting_ddlist_min_extra_list_selected_checked;
	ui_init_style(&style_sys_setting_ddlist_min_extra_list_selected_checked);
	lv_style_set_radius(&style_sys_setting_ddlist_min_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_min_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_min_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_sys_setting_ddlist_min_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_min_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_min_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_min_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_min_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_sys_setting_ddlist_min_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_min_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &style_sys_setting_ddlist_min_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_min_extra_list_main_default
	static lv_style_t style_sys_setting_ddlist_min_extra_list_main_default;
	ui_init_style(&style_sys_setting_ddlist_min_extra_list_main_default);
	lv_style_set_radius(&style_sys_setting_ddlist_min_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_min_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_min_extra_list_main_default, 255);
	lv_style_set_border_color(&style_sys_setting_ddlist_min_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_min_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_min_extra_list_main_default, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_min_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_min_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_sys_setting_ddlist_min_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_min_extra_list_main_default, 0);
	lv_style_set_max_height(&style_sys_setting_ddlist_min_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &style_sys_setting_ddlist_min_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_min_extra_list_scrollbar_default
	static lv_style_t style_sys_setting_ddlist_min_extra_list_scrollbar_default;
	ui_init_style(&style_sys_setting_ddlist_min_extra_list_scrollbar_default);
	lv_style_set_radius(&style_sys_setting_ddlist_min_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_min_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_min_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &style_sys_setting_ddlist_min_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_ddlist_min, 190, 102);
	lv_obj_set_size(ui->sys_setting_ddlist_min, 69, 31);
	lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_min, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_ddlist_min, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes sys_setting_ddlist_sec
	ui->sys_setting_ddlist_sec = lv_dropdown_create(ui->sys_setting_view_time_mun);
	lv_dropdown_set_options(ui->sys_setting_ddlist_sec, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->sys_setting_ddlist_sec, LV_DIR_TOP);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_sec, LV_SYMBOL_UP);
	lv_dropdown_set_symbol(ui->sys_setting_ddlist_sec, NULL);
	lv_dropdown_set_selected(ui->sys_setting_ddlist_sec, 0);

	//Set style for sys_setting_ddlist_sec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_ddlist_sec, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_sec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_sec, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_sec, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_sec, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_sec, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_sec, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_sec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_sec, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_sec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_sec, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_sec, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_sec, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_sec, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for sys_setting_ddlist_sec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->sys_setting_ddlist_sec, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->sys_setting_ddlist_sec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->sys_setting_ddlist_sec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->sys_setting_ddlist_sec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->sys_setting_ddlist_sec, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->sys_setting_ddlist_sec, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->sys_setting_ddlist_sec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->sys_setting_ddlist_sec, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->sys_setting_ddlist_sec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->sys_setting_ddlist_sec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->sys_setting_ddlist_sec, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->sys_setting_ddlist_sec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->sys_setting_ddlist_sec, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->sys_setting_ddlist_sec, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->sys_setting_ddlist_sec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->sys_setting_ddlist_sec, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->sys_setting_ddlist_sec, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->sys_setting_ddlist_sec, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_sec_extra_list_selected_checked
	static lv_style_t style_sys_setting_ddlist_sec_extra_list_selected_checked;
	ui_init_style(&style_sys_setting_ddlist_sec_extra_list_selected_checked);
	lv_style_set_radius(&style_sys_setting_ddlist_sec_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_sec_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_sec_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_sys_setting_ddlist_sec_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_sec_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_sec_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_sec_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_sec_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_sys_setting_ddlist_sec_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_sec_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &style_sys_setting_ddlist_sec_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_sec_extra_list_main_default
	static lv_style_t style_sys_setting_ddlist_sec_extra_list_main_default;
	ui_init_style(&style_sys_setting_ddlist_sec_extra_list_main_default);
	lv_style_set_radius(&style_sys_setting_ddlist_sec_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_sec_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_sec_extra_list_main_default, 255);
	lv_style_set_border_color(&style_sys_setting_ddlist_sec_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_sys_setting_ddlist_sec_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_sys_setting_ddlist_sec_extra_list_main_default, 255);
	lv_style_set_border_side(&style_sys_setting_ddlist_sec_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_sys_setting_ddlist_sec_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_sys_setting_ddlist_sec_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_sys_setting_ddlist_sec_extra_list_main_default, 0);
	lv_style_set_max_height(&style_sys_setting_ddlist_sec_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &style_sys_setting_ddlist_sec_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_sec_extra_list_scrollbar_default
	static lv_style_t style_sys_setting_ddlist_sec_extra_list_scrollbar_default;
	ui_init_style(&style_sys_setting_ddlist_sec_extra_list_scrollbar_default);
	lv_style_set_radius(&style_sys_setting_ddlist_sec_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_sys_setting_ddlist_sec_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_sys_setting_ddlist_sec_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &style_sys_setting_ddlist_sec_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_ddlist_sec, 328, 102);
	lv_obj_set_size(ui->sys_setting_ddlist_sec, 69, 31);
	lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_sec, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->sys_setting_ddlist_sec, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes sys_setting_img_19
	ui->sys_setting_img_19 = lv_img_create(ui->sys_setting_view_time_mun);
	lv_img_set_src(ui->sys_setting_img_19, gui_get_res_path(GUI_RES_NUM_L_PNG));
	lv_img_set_pivot(ui->sys_setting_img_19, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_19, 0);
	lv_img_set_zoom(ui->sys_setting_img_19, 256);

	//Set style for sys_setting_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_19, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_19, 151, 35);
	lv_obj_set_size(ui->sys_setting_img_19, 9, 13);
	lv_obj_add_flag(ui->sys_setting_img_19, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_20
	ui->sys_setting_img_20 = lv_img_create(ui->sys_setting_view_time_mun);
	lv_img_set_src(ui->sys_setting_img_20, gui_get_res_path(GUI_RES_NUM_L_PNG));
	lv_img_set_pivot(ui->sys_setting_img_20, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_20, 0);
	lv_img_set_zoom(ui->sys_setting_img_20, 256);

	//Set style for sys_setting_img_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_20, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_20, 283, 35);
	lv_obj_set_size(ui->sys_setting_img_20, 9, 13);
	lv_obj_add_flag(ui->sys_setting_img_20, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_21
	ui->sys_setting_img_21 = lv_img_create(ui->sys_setting_view_time_mun);
	lv_img_set_src(ui->sys_setting_img_21, gui_get_res_path(GUI_RES_NUM_D_PNG));
	lv_img_set_pivot(ui->sys_setting_img_21, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_21, 0);
	lv_img_set_zoom(ui->sys_setting_img_21, 256);

	//Set style for sys_setting_img_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_21, 149, 111);
	lv_obj_set_size(ui->sys_setting_img_21, 9, 13);
	lv_obj_add_flag(ui->sys_setting_img_21, LV_OBJ_FLAG_CLICKABLE);
	//Write codes sys_setting_img_22
	ui->sys_setting_img_22 = lv_img_create(ui->sys_setting_view_time_mun);
	lv_img_set_src(ui->sys_setting_img_22, gui_get_res_path(GUI_RES_NUM_D_PNG));
	lv_img_set_pivot(ui->sys_setting_img_22, 0, 0);
	lv_img_set_angle(ui->sys_setting_img_22, 0);
	lv_img_set_zoom(ui->sys_setting_img_22, 256);

	//Set style for sys_setting_img_22. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->sys_setting_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->sys_setting_img_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sys_setting_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->sys_setting_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->sys_setting_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->sys_setting_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->sys_setting_img_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->sys_setting_img_22, 287, 111);
	lv_obj_set_size(ui->sys_setting_img_22, 9, 13);
	lv_obj_add_flag(ui->sys_setting_img_22, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_update_layout(ui->sys_setting);
	ui->sys_setting_del = false;

	//Init events for screen
	events_init_sys_setting(ui);
	return ui->sys_setting;
}
void unload_scr_sys_setting(lv_ui *ui)
{
	ui->sys_setting_del = true;
}

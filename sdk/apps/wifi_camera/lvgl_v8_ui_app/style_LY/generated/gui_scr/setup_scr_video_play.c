#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
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


lv_obj_t * setup_scr_video_play(lv_ui *ui)
{
	//Write codes video_play
	ui->video_play = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for video_play. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_play, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->video_play, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_play_view_1
	ui->video_play_view_1 = lv_obj_create(ui->video_play);

	//Set style for video_play_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_view_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_play_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_play_view_1, 0, 367);
	lv_obj_set_size(ui->video_play_view_1, 799, 111);
	lv_obj_set_scrollbar_mode(ui->video_play_view_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_play_lbl_cur_time
	ui->video_play_lbl_cur_time = lv_label_create(ui->video_play_view_1);
	lv_label_set_text(ui->video_play_lbl_cur_time, "00:00");
	lv_label_set_long_mode(ui->video_play_lbl_cur_time, LV_LABEL_LONG_WRAP);

	//Set style for video_play_lbl_cur_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_lbl_cur_time, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_lbl_cur_time, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_lbl_cur_time, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_lbl_cur_time, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_play_lbl_cur_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_play_lbl_cur_time, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_play_lbl_cur_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_play_lbl_cur_time, 219, 52);
	lv_obj_set_size(ui->video_play_lbl_cur_time, 106, 47);
	lv_obj_set_scrollbar_mode(ui->video_play_lbl_cur_time, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_play_imgbtn_pause
	ui->video_play_imgbtn_pause = lv_imgbtn_create(ui->video_play_view_1);

	//Set style for video_play_imgbtn_pause. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_pause, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_pause, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_pause, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_pause, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_play_imgbtn_pause, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_pause, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_pause, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_imgbtn_pause. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_pause, true, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_pause, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_pause, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_pause, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_pause, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_pause, 255, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for video_play_imgbtn_pause. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_pause, true, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_pause, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_pause, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_pause, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_pause, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_pause, 255, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for video_play_imgbtn_pause. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_pause, true, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_pause, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_pause, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_play_imgbtn_pause, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_play_imgbtn_pause, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_play_imgbtn_pause, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_play_imgbtn_pause, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_pause, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_pause, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_align(ui->video_play_imgbtn_pause, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_pause, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_pause, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_pause, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_play_imgbtn_pause, 85, 48);
	lv_obj_set_size(ui->video_play_imgbtn_pause, 48, 48);
	lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_pause, LV_SCROLLBAR_MODE_OFF);
	lv_group_add_obj(def_group, ui->video_play_imgbtn_pause);
	lv_imgbtn_set_src(ui->video_play_imgbtn_pause, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_PLAY_PNG), NULL);
	lv_imgbtn_set_src(ui->video_play_imgbtn_pause, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_PAUSE_PNG), NULL);
	lv_obj_add_flag(ui->video_play_imgbtn_pause, LV_OBJ_FLAG_CHECKABLE);
	ui->video_play_imgbtn_pause_label = lv_label_create(ui->video_play_imgbtn_pause);
	lv_label_set_text(ui->video_play_imgbtn_pause_label, "");
	lv_obj_set_style_pad_all(ui->video_play_imgbtn_pause, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_play_imgbtn_pause_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_play_img_prev_file
	ui->video_play_img_prev_file = lv_img_create(ui->video_play_view_1);
	lv_img_set_src(ui->video_play_img_prev_file, gui_get_res_path(GUI_RES_SKIP_PREVIOUS_PNG));
	lv_img_set_pivot(ui->video_play_img_prev_file, 0, 0);
	lv_img_set_angle(ui->video_play_img_prev_file, 0);
	lv_img_set_zoom(ui->video_play_img_prev_file, 256);

	//Set style for video_play_img_prev_file. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_img_prev_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_play_img_prev_file, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_img_prev_file, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_img_prev_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_play_img_prev_file, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_play_img_prev_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_play_img_prev_file, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_img_prev_file. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_play_img_prev_file, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_clip_corner(ui->video_play_img_prev_file, true, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_play_img_prev_file, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_play_img_prev_file, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_play_img_prev_file, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_play_img_prev_file, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_play_img_prev_file, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_play_img_prev_file, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor(ui->video_play_img_prev_file, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor_opa(ui->video_play_img_prev_file, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_opa(ui->video_play_img_prev_file, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_play_img_prev_file, 24, 48);
	lv_obj_set_size(ui->video_play_img_prev_file, 57, 54);
	lv_group_add_obj(def_group, ui->video_play_img_prev_file);
	lv_obj_add_flag(ui->video_play_img_prev_file, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_play_img_next_file
	ui->video_play_img_next_file = lv_img_create(ui->video_play_view_1);
	lv_img_set_src(ui->video_play_img_next_file, gui_get_res_path(GUI_RES_SKIP_NEXT_PNG));
	lv_img_set_pivot(ui->video_play_img_next_file, 0, 0);
	lv_img_set_angle(ui->video_play_img_next_file, 0);
	lv_img_set_zoom(ui->video_play_img_next_file, 256);

	//Set style for video_play_img_next_file. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_img_next_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_play_img_next_file, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_img_next_file, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_img_next_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_play_img_next_file, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_play_img_next_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_play_img_next_file, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_img_next_file. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_play_img_next_file, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_clip_corner(ui->video_play_img_next_file, true, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_play_img_next_file, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_play_img_next_file, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_play_img_next_file, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_play_img_next_file, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_play_img_next_file, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_play_img_next_file, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor(ui->video_play_img_next_file, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor_opa(ui->video_play_img_next_file, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_opa(ui->video_play_img_next_file, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_play_img_next_file, 149, 48);
	lv_obj_set_size(ui->video_play_img_next_file, 57, 54);
	lv_group_add_obj(def_group, ui->video_play_img_next_file);
	lv_obj_add_flag(ui->video_play_img_next_file, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_play_imgbtn_loud
	ui->video_play_imgbtn_loud = lv_imgbtn_create(ui->video_play_view_1);

	//Set style for video_play_imgbtn_loud. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_loud, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_loud, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_loud, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_loud, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_play_imgbtn_loud, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_loud, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_loud, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_imgbtn_loud. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_loud, true, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_loud, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_loud, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_loud, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_loud, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_loud, 255, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for video_play_imgbtn_loud. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_loud, true, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_loud, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_loud, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_loud, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_loud, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_loud, 255, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for video_play_imgbtn_loud. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_loud, true, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_loud, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_loud, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_play_imgbtn_loud, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_play_imgbtn_loud, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_play_imgbtn_loud, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_play_imgbtn_loud, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_loud, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_loud, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_align(ui->video_play_imgbtn_loud, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_loud, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_loud, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_loud, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_play_imgbtn_loud, 600, 48);
	lv_obj_set_size(ui->video_play_imgbtn_loud, 48, 48);
	lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_loud, LV_SCROLLBAR_MODE_OFF);
	lv_group_add_obj(def_group, ui->video_play_imgbtn_loud);
	lv_imgbtn_set_src(ui->video_play_imgbtn_loud, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VOLUMELOUDER_SOLID_1_PNG), NULL);
	lv_imgbtn_set_src(ui->video_play_imgbtn_loud, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VOLUMEMUTE_SOLID_1_PNG), NULL);
	lv_obj_add_flag(ui->video_play_imgbtn_loud, LV_OBJ_FLAG_CHECKABLE);
	ui->video_play_imgbtn_loud_label = lv_label_create(ui->video_play_imgbtn_loud);
	lv_label_set_text(ui->video_play_imgbtn_loud_label, "");
	lv_obj_set_style_pad_all(ui->video_play_imgbtn_loud, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_play_imgbtn_loud_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_play_lbl_total_time
	ui->video_play_lbl_total_time = lv_label_create(ui->video_play_view_1);
	lv_label_set_text(ui->video_play_lbl_total_time, "/02:40");
	lv_label_set_long_mode(ui->video_play_lbl_total_time, LV_LABEL_LONG_WRAP);

	//Set style for video_play_lbl_total_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_lbl_total_time, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_lbl_total_time, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_lbl_total_time, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_lbl_total_time, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_play_lbl_total_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_play_lbl_total_time, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_play_lbl_total_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_play_lbl_total_time, 316, 52);
	lv_obj_set_size(ui->video_play_lbl_total_time, 106, 47);
	lv_obj_set_scrollbar_mode(ui->video_play_lbl_total_time, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_play_ddlist_multi_spped
	ui->video_play_ddlist_multi_spped = lv_dropdown_create(ui->video_play_view_1);
	lv_dropdown_set_options(ui->video_play_ddlist_multi_spped, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_play_ddlist_multi_spped, LV_DIR_TOP);
	lv_dropdown_set_symbol(ui->video_play_ddlist_multi_spped, LV_SYMBOL_UP);
	lv_dropdown_set_symbol(ui->video_play_ddlist_multi_spped, NULL);
	lv_dropdown_set_selected(ui->video_play_ddlist_multi_spped, 1);

	//Set style for video_play_ddlist_multi_spped. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_ddlist_multi_spped, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_ddlist_multi_spped, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_ddlist_multi_spped, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_ddlist_multi_spped, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_play_ddlist_multi_spped, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_play_ddlist_multi_spped, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_play_ddlist_multi_spped, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_play_ddlist_multi_spped, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_play_ddlist_multi_spped, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_play_ddlist_multi_spped, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_play_ddlist_multi_spped, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_play_ddlist_multi_spped, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_ddlist_multi_spped, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_ddlist_multi_spped, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_ddlist_multi_spped, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_play_ddlist_multi_spped, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_play_ddlist_multi_spped, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_play_ddlist_multi_spped, 12, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_ddlist_multi_spped. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_play_ddlist_multi_spped, 15, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_play_ddlist_multi_spped, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_play_ddlist_multi_spped, 153, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_play_ddlist_multi_spped, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_play_ddlist_multi_spped, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_play_ddlist_multi_spped, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_play_ddlist_multi_spped, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_play_ddlist_multi_spped, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_play_ddlist_multi_spped, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_play_ddlist_multi_spped, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_play_ddlist_multi_spped, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_play_ddlist_multi_spped, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_play_ddlist_multi_spped, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_play_ddlist_multi_spped, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_play_ddlist_multi_spped, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_play_ddlist_multi_spped, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_play_ddlist_multi_spped, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_play_ddlist_multi_spped, 12, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_play_ddlist_multi_spped_extra_list_selected_checked
	static lv_style_t style_video_play_ddlist_multi_spped_extra_list_selected_checked;
	ui_init_style(&style_video_play_ddlist_multi_spped_extra_list_selected_checked);
	lv_style_set_radius(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, 153);
	lv_style_set_border_width(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, 0);
	lv_style_set_text_color(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, &lv_font_montserratMedium_24);
	lv_style_set_text_letter_space(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_play_ddlist_multi_spped), &style_video_play_ddlist_multi_spped_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_play_ddlist_multi_spped_extra_list_main_default
	static lv_style_t style_video_play_ddlist_multi_spped_extra_list_main_default;
	ui_init_style(&style_video_play_ddlist_multi_spped_extra_list_main_default);
	lv_style_set_radius(&style_video_play_ddlist_multi_spped_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_play_ddlist_multi_spped_extra_list_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_play_ddlist_multi_spped_extra_list_main_default, 153);
	lv_style_set_border_color(&style_video_play_ddlist_multi_spped_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_play_ddlist_multi_spped_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_play_ddlist_multi_spped_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_play_ddlist_multi_spped_extra_list_main_default, LV_BORDER_SIDE_NONE);
	lv_style_set_text_color(&style_video_play_ddlist_multi_spped_extra_list_main_default, lv_color_make(0xFF, 0xFF, 0xFF));
	lv_style_set_text_font(&style_video_play_ddlist_multi_spped_extra_list_main_default, &lv_font_montserratMedium_24);
	lv_style_set_text_letter_space(&style_video_play_ddlist_multi_spped_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_play_ddlist_multi_spped_extra_list_main_default, 190);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_play_ddlist_multi_spped), &style_video_play_ddlist_multi_spped_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_play_ddlist_multi_spped_extra_list_scrollbar_default
	static lv_style_t style_video_play_ddlist_multi_spped_extra_list_scrollbar_default;
	ui_init_style(&style_video_play_ddlist_multi_spped_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_play_ddlist_multi_spped_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_play_ddlist_multi_spped_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_play_ddlist_multi_spped_extra_list_scrollbar_default, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_play_ddlist_multi_spped), &style_video_play_ddlist_multi_spped_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_play_ddlist_multi_spped, 674, 48);
	lv_obj_set_size(ui->video_play_ddlist_multi_spped, 101, 48);
	lv_obj_set_scrollbar_mode(ui->video_play_ddlist_multi_spped, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_play_bar_process
	ui->video_play_bar_process = lv_bar_create(ui->video_play_view_1);

	//Set style for video_play_bar_process. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_bar_process, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_bar_process, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_bar_process, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_bar_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_bar_process. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_bar_process, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_bar_process, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_bar_process, 128, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_play_bar_process, 0, 13);
	lv_obj_set_size(ui->video_play_bar_process, 800, 16);
	lv_obj_set_scrollbar_mode(ui->video_play_bar_process, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_anim_time(ui->video_play_bar_process, 1000, 0);
	lv_bar_set_mode(ui->video_play_bar_process, LV_BAR_MODE_NORMAL);
	lv_bar_set_range(ui->video_play_bar_process, 0, 100);
	lv_bar_set_value(ui->video_play_bar_process, 20.0004, LV_ANIM_ON);
	//Write codes video_play_imgbtn_1
	ui->video_play_imgbtn_1 = lv_imgbtn_create(ui->video_play);

	//Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_play_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_play_imgbtn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_play_imgbtn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_play_imgbtn_1, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_play_imgbtn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_align(ui->video_play_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_pos(ui->video_play_imgbtn_1, 724, 135);
	lv_obj_set_size(ui->video_play_imgbtn_1, 48, 48);
	lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_add_obj(def_group, ui->video_play_imgbtn_1);
	lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_PHOTO_1_PNG), NULL);
	lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_PHOTO_ON_PNG), NULL);
	lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_PHOTO_1_PNG), NULL);
	lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_PHOTO_ON_PNG), NULL);
	lv_obj_add_flag(ui->video_play_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
	ui->video_play_imgbtn_1_label = lv_label_create(ui->video_play_imgbtn_1);
	lv_label_set_text(ui->video_play_imgbtn_1_label, "");
	lv_obj_set_style_pad_all(ui->video_play_imgbtn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_play_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_play_lbl_msg
	ui->video_play_lbl_msg = lv_label_create(ui->video_play);
	lv_label_set_text(ui->video_play_lbl_msg, "正在播放 xxx.avi");
	lv_label_set_long_mode(ui->video_play_lbl_msg, LV_LABEL_LONG_WRAP);

	//Set style for video_play_lbl_msg. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_play_lbl_msg, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_play_lbl_msg, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_play_lbl_msg, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_play_lbl_msg, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_play_lbl_msg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_play_lbl_msg, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_play_lbl_msg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_play_lbl_msg, 159, 278);
	lv_obj_set_size(ui->video_play_lbl_msg, 527, 59);
	lv_obj_set_scrollbar_mode(ui->video_play_lbl_msg, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_play_lbl_msg, LV_OBJ_FLAG_HIDDEN);
	lv_obj_update_layout(ui->video_play);
	ui->video_play_del = false;

	//Init events for screen
	events_init_video_play(ui);
	return ui->video_play;
}
void unload_scr_video_play(lv_ui *ui)
{
	ui->video_play_del = true;
}

#endif

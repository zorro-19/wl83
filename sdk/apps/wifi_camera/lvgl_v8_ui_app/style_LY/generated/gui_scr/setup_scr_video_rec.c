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


lv_obj_t * setup_scr_video_rec(lv_ui *ui)
{
	//Write codes video_rec
	ui->video_rec = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for video_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_rec, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->video_rec, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_scan
	ui->video_rec_view_scan = lv_obj_create(ui->video_rec);

	//Set style for video_rec_view_scan. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_scan, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_view_scan, 0, 0);
	lv_obj_set_size(ui->video_rec_view_scan, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_scan, LV_SCROLLBAR_MODE_OFF);
	lv_group_add_obj(def_group, ui->video_rec_view_scan);
	//Write codes video_rec_img_1
	ui->video_rec_img_1 = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_1, gui_get_res_path(GUI_RES_I_REC_PNG));
	lv_img_set_pivot(ui->video_rec_img_1, 0, 0);
	lv_img_set_angle(ui->video_rec_img_1, 0);
	lv_img_set_zoom(ui->video_rec_img_1, 256);

	//Set style for video_rec_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_1, 12, 10);
	lv_obj_set_size(ui->video_rec_img_1, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_1, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_cyc_state
	ui->video_rec_img_cyc_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_cyc_state, gui_get_res_path(GUI_RES_CYCLIC_VIDEO_3_PNG));
	lv_img_set_pivot(ui->video_rec_img_cyc_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_cyc_state, 0);
	lv_img_set_zoom(ui->video_rec_img_cyc_state, 256);

	//Set style for video_rec_img_cyc_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_cyc_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_cyc_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_cyc_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_cyc_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_cyc_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_cyc_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_cyc_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_cyc_state, 13, 54);
	lv_obj_set_size(ui->video_rec_img_cyc_state, 29, 31);
	lv_obj_add_flag(ui->video_rec_img_cyc_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_exp_state
	ui->video_rec_img_exp_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_exp_state, gui_get_res_path(GUI_RES_EXP_A0_PNG));
	lv_img_set_pivot(ui->video_rec_img_exp_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_exp_state, 0);
	lv_img_set_zoom(ui->video_rec_img_exp_state, 256);

	//Set style for video_rec_img_exp_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_exp_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_exp_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_exp_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_exp_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_exp_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_exp_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_exp_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_exp_state, 12, 95);
	lv_obj_set_size(ui->video_rec_img_exp_state, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_exp_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_mot_state
	ui->video_rec_img_mot_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_mot_state, gui_get_res_path(GUI_RES_I_MOT_PNG));
	lv_img_set_pivot(ui->video_rec_img_mot_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_mot_state, 0);
	lv_img_set_zoom(ui->video_rec_img_mot_state, 256);

	//Set style for video_rec_img_mot_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_mot_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_mot_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_mot_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_mot_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_mot_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_mot_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_mot_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_mot_state, 14, 138);
	lv_obj_set_size(ui->video_rec_img_mot_state, 22, 25);
	lv_obj_add_flag(ui->video_rec_img_mot_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_gap_state
	ui->video_rec_img_gap_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_gap_state, gui_get_res_path(GUI_RES_I_TEAR_PNG));
	lv_img_set_pivot(ui->video_rec_img_gap_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_gap_state, 0);
	lv_img_set_zoom(ui->video_rec_img_gap_state, 256);

	//Set style for video_rec_img_gap_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_gap_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_gap_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_gap_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_gap_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_gap_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_gap_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_gap_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_gap_state, 13, 180);
	lv_obj_set_size(ui->video_rec_img_gap_state, 29, 31);
	lv_obj_add_flag(ui->video_rec_img_gap_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_mic_state
	ui->video_rec_img_mic_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_mic_state, gui_get_res_path(GUI_RES_MIC_ON_PNG));
	lv_img_set_pivot(ui->video_rec_img_mic_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_mic_state, 0);
	lv_img_set_zoom(ui->video_rec_img_mic_state, 256);

	//Set style for video_rec_img_mic_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_mic_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_mic_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_mic_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_mic_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_mic_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_mic_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_mic_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_mic_state, 12, 440);
	lv_obj_set_size(ui->video_rec_img_mic_state, 26, 29);
	lv_obj_add_flag(ui->video_rec_img_mic_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_hdr_state
	ui->video_rec_img_hdr_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_hdr_state, gui_get_res_path(GUI_RES_I_HDR_PNG));
	lv_img_set_pivot(ui->video_rec_img_hdr_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_hdr_state, 0);
	lv_img_set_zoom(ui->video_rec_img_hdr_state, 256);

	//Set style for video_rec_img_hdr_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_hdr_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_hdr_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_hdr_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_hdr_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_hdr_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_hdr_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_hdr_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_hdr_state, 177, 10);
	lv_obj_set_size(ui->video_rec_img_hdr_state, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_hdr_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_gra_state
	ui->video_rec_img_gra_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_gra_state, gui_get_res_path(GUI_RES_I_GRA_L_PNG));
	lv_img_set_pivot(ui->video_rec_img_gra_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_gra_state, 0);
	lv_img_set_zoom(ui->video_rec_img_gra_state, 256);

	//Set style for video_rec_img_gra_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_gra_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_gra_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_gra_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_gra_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_gra_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_gra_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_gra_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_gra_state, 226, 12);
	lv_obj_set_size(ui->video_rec_img_gra_state, 34, 31);
	lv_obj_add_flag(ui->video_rec_img_gra_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_par_state
	ui->video_rec_img_par_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_par_state, gui_get_res_path(GUI_RES_PARK_PNG));
	lv_img_set_pivot(ui->video_rec_img_par_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_par_state, 0);
	lv_img_set_zoom(ui->video_rec_img_par_state, 256);

	//Set style for video_rec_img_par_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_par_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_par_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_par_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_par_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_par_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_par_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_par_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_par_state, 762, 223);
	lv_obj_set_size(ui->video_rec_img_par_state, 27, 22);
	lv_obj_add_flag(ui->video_rec_img_par_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_reso
	ui->video_rec_lbl_reso = lv_label_create(ui->video_rec_view_scan);
	lv_label_set_text(ui->video_rec_lbl_reso, "720P");
	lv_label_set_long_mode(ui->video_rec_lbl_reso, LV_LABEL_LONG_WRAP);

	//Set style for video_rec_lbl_reso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_reso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_reso, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_reso, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_reso, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_reso, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_reso, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_reso, 478, 12);
	lv_obj_set_size(ui->video_rec_lbl_reso, 80, 35);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_reso, LV_SCROLLBAR_MODE_OFF);
	static bool timer_video_rec_digitclock_1_enabled = false;

	//Write codes video_rec_digitclock_1
	ui->video_rec_digitclock_1 = lv_label_create(ui->video_rec_view_scan);
	lv_label_set_text_fmt(ui->video_rec_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
	lv_obj_set_style_text_align(ui->video_rec_digitclock_1, LV_TEXT_ALIGN_CENTER, 0);

	//Set style for video_rec_digitclock_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_digitclock_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_digitclock_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_digitclock_1, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_digitclock_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_digitclock_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_digitclock_1, 50, 438);
	lv_obj_set_size(ui->video_rec_digitclock_1, 300, 35);
	//Write codes video_rec_img_bat
	ui->video_rec_img_bat = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_bat, gui_get_res_path(GUI_RES_BAT_FULL_PNG));
	lv_img_set_pivot(ui->video_rec_img_bat, 0, 0);
	lv_img_set_angle(ui->video_rec_img_bat, 0);
	lv_img_set_zoom(ui->video_rec_img_bat, 256);

	//Set style for video_rec_img_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_bat, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_bat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_bat, 762, 454);
	lv_obj_set_size(ui->video_rec_img_bat, 25, 15);
	lv_obj_add_flag(ui->video_rec_img_bat, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_sd
	ui->video_rec_img_sd = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_sd, gui_get_res_path(GUI_RES_CARD_ONLINE_PNG));
	lv_img_set_pivot(ui->video_rec_img_sd, 0, 0);
	lv_img_set_angle(ui->video_rec_img_sd, 0);
	lv_img_set_zoom(ui->video_rec_img_sd, 256);

	//Set style for video_rec_img_sd. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_sd, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_sd, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_sd, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_sd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_sd, 758, 410);
	lv_obj_set_size(ui->video_rec_img_sd, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_sd, LV_OBJ_FLAG_CLICKABLE);
	static bool timer_video_rec_digitclock_2_enabled = false;

	//Write codes video_rec_digitclock_2
	ui->video_rec_digitclock_2 = lv_label_create(ui->video_rec_view_scan);
	lv_label_set_text_fmt(ui->video_rec_digitclock_2, "%02d:%02d:%02d", 21 % 12, 25, 50);
	lv_obj_set_style_text_align(ui->video_rec_digitclock_2, LV_TEXT_ALIGN_CENTER, 0);

	//Set style for video_rec_digitclock_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_digitclock_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_digitclock_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_digitclock_2, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_digitclock_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_digitclock_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_digitclock_2. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->video_rec_digitclock_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->video_rec_digitclock_2, lv_color_make(0xF4, 0x43, 0x36), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->video_rec_digitclock_2, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->video_rec_digitclock_2, 2, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->video_rec_digitclock_2, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->video_rec_digitclock_2, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_pos(ui->video_rec_digitclock_2, 666, 10);
	lv_obj_set_size(ui->video_rec_digitclock_2, 120, 32);
	//Write codes video_rec_img_rec_state
	ui->video_rec_img_rec_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_rec_state, gui_get_res_path(GUI_RES_RED_CIRCLE_PNG));
	lv_img_set_pivot(ui->video_rec_img_rec_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_rec_state, 0);
	lv_img_set_zoom(ui->video_rec_img_rec_state, 256);

	//Set style for video_rec_img_rec_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_rec_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_rec_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_rec_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_rec_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_rec_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_rec_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_rec_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_rec_state, 65, 12);
	lv_obj_set_size(ui->video_rec_img_rec_state, 27, 27);
	lv_obj_add_flag(ui->video_rec_img_rec_state, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->video_rec_img_rec_state, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_num
	ui->video_rec_lbl_num = lv_label_create(ui->video_rec_view_scan);
	lv_label_set_text(ui->video_rec_lbl_num, "京 AAAAAA\n\n京津晋冀蒙辽吉黑苏浙皖闽赣鲁豫鄂湘粤桂琼川贵滇渝藏陕甘青宁新台港澳");
	lv_label_set_long_mode(ui->video_rec_lbl_num, LV_LABEL_LONG_WRAP);

	//Set style for video_rec_lbl_num. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_num, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_num, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_num, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_num, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_num, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_num, 93, 391);
	lv_obj_set_size(ui->video_rec_lbl_num, 180, 42);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_num, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_lbl_num, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_rec_img_headlight
	ui->video_rec_img_headlight = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_headlight, gui_get_res_path(GUI_RES_FLIG_ON_PNG));
	lv_img_set_pivot(ui->video_rec_img_headlight, 0, 0);
	lv_img_set_angle(ui->video_rec_img_headlight, 0);
	lv_img_set_zoom(ui->video_rec_img_headlight, 256);

	//Set style for video_rec_img_headlight. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_headlight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_headlight, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_headlight, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_headlight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_headlight, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_headlight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_headlight, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_headlight, 363, 203);
	lv_obj_set_size(ui->video_rec_img_headlight, 75, 75);
	lv_obj_add_flag(ui->video_rec_img_headlight, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->video_rec_img_headlight, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_key_state
	ui->video_rec_img_key_state = lv_img_create(ui->video_rec_view_scan);
	lv_img_set_src(ui->video_rec_img_key_state, gui_get_res_path(GUI_RES_KEY_PNG));
	lv_img_set_pivot(ui->video_rec_img_key_state, 0, 0);
	lv_img_set_angle(ui->video_rec_img_key_state, 0);
	lv_img_set_zoom(ui->video_rec_img_key_state, 256);

	//Set style for video_rec_img_key_state. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_key_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_key_state, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_key_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_key_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_key_state, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_key_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_key_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_key_state, 122, 12);
	lv_obj_set_size(ui->video_rec_img_key_state, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_key_state, LV_OBJ_FLAG_CLICKABLE);

	// Write Timer video_rec_timer_1
	if(ui->video_rec_timer_1 != NULL) lv_timer_del(ui->video_rec_timer_1);
	ui->video_rec_timer_1 = lv_timer_create(video_rec_timer_1_timer_cb, 1000, "");
	lv_timer_set_repeat_count(ui->video_rec_timer_1, -1);
	lv_timer_pause(ui->video_rec_timer_1);
	//Write codes video_rec_view_menu_b
	ui->video_rec_view_menu_b = lv_obj_create(ui->video_rec);

	//Set style for video_rec_view_menu_b. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_menu_b, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_view_menu_b, 0, 0);
	lv_obj_set_size(ui->video_rec_view_menu_b, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_menu_b, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_menu_b, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_rec_view_menu
	ui->video_rec_view_menu = lv_obj_create(ui->video_rec_view_menu_b);

	//Set style for video_rec_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_menu, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_view_menu, 0, 40);
	lv_obj_set_size(ui->video_rec_view_menu, 800, 400);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_menu, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_reso
	ui->video_rec_view_reso = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_reso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_reso, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_reso. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_reso, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_reso, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_reso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_reso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_reso, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_reso, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_reso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_reso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_reso, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_reso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_reso, 0, 0);
	lv_obj_set_size(ui->video_rec_view_reso, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_reso, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_reso, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_reso, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_reso);
	//Write codes video_rec_img_2
	ui->video_rec_img_2 = lv_img_create(ui->video_rec_view_reso);
	lv_img_set_src(ui->video_rec_img_2, gui_get_res_path(GUI_RES_M_SOLU_PNG));
	lv_img_set_pivot(ui->video_rec_img_2, 0, 0);
	lv_img_set_angle(ui->video_rec_img_2, 0);
	lv_img_set_zoom(ui->video_rec_img_2, 256);

	//Set style for video_rec_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_2, 8, 6);
	lv_obj_set_size(ui->video_rec_img_2, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_2, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_1
	ui->video_rec_lbl_1 = lv_label_create(ui->video_rec_view_reso);
	lv_label_set_text(ui->video_rec_lbl_1, _("resolution"));
	lv_label_set_long_mode(ui->video_rec_lbl_1, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_1_font = _font("resolution");
	if(video_rec_lbl_1_font == NULL) video_rec_lbl_1_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_1, video_rec_lbl_1_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_1, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_1, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_two_rec
	ui->video_rec_view_two_rec = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_two_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_two_rec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_two_rec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_two_rec, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_two_rec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_two_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_two_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_two_rec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_two_rec, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_two_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_two_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_two_rec, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_two_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_two_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_two_rec, 0, 45);
	lv_obj_set_size(ui->video_rec_view_two_rec, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_two_rec, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_two_rec, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_two_rec, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_two_rec);
	//Write codes video_rec_img_3
	ui->video_rec_img_3 = lv_img_create(ui->video_rec_view_two_rec);
	lv_img_set_src(ui->video_rec_img_3, gui_get_res_path(GUI_RES_M_TWO_REC_PNG));
	lv_img_set_pivot(ui->video_rec_img_3, 0, 0);
	lv_img_set_angle(ui->video_rec_img_3, 0);
	lv_img_set_zoom(ui->video_rec_img_3, 256);

	//Set style for video_rec_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_3, 8, 6);
	lv_obj_set_size(ui->video_rec_img_3, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_3, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_3
	ui->video_rec_lbl_3 = lv_label_create(ui->video_rec_view_two_rec);
	lv_label_set_text(ui->video_rec_lbl_3, _("doublerec"));
	lv_label_set_long_mode(ui->video_rec_lbl_3, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_3_font = _font("doublerec");
	if(video_rec_lbl_3_font == NULL) video_rec_lbl_3_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_3, video_rec_lbl_3_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_3, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_3, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_3, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_cyc_rec
	ui->video_rec_view_cyc_rec = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_cyc_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_cyc_rec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_cyc_rec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_cyc_rec, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_cyc_rec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_cyc_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_cyc_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_cyc_rec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_cyc_rec, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_cyc_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_cyc_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_cyc_rec, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_cyc_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_cyc_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_cyc_rec, 0, 90);
	lv_obj_set_size(ui->video_rec_view_cyc_rec, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_cyc_rec, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_cyc_rec, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_cyc_rec, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_cyc_rec);
	//Write codes video_rec_img_4
	ui->video_rec_img_4 = lv_img_create(ui->video_rec_view_cyc_rec);
	lv_img_set_src(ui->video_rec_img_4, gui_get_res_path(GUI_RES_M_CYC_PNG));
	lv_img_set_pivot(ui->video_rec_img_4, 0, 0);
	lv_img_set_angle(ui->video_rec_img_4, 0);
	lv_img_set_zoom(ui->video_rec_img_4, 256);

	//Set style for video_rec_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_4, 8, 6);
	lv_obj_set_size(ui->video_rec_img_4, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_4, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_4
	ui->video_rec_lbl_4 = lv_label_create(ui->video_rec_view_cyc_rec);
	lv_label_set_text(ui->video_rec_lbl_4, _("cycrec"));
	lv_label_set_long_mode(ui->video_rec_lbl_4, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_4_font = _font("cycrec");
	if(video_rec_lbl_4_font == NULL) video_rec_lbl_4_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_4, video_rec_lbl_4_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_4, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_4, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_4, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_gap
	ui->video_rec_view_gap = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_gap. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_gap, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_gap. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_gap, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_gap, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_gap, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_gap, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_gap, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_gap, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_gap, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_gap, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_gap, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_gap, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_gap, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_gap, 0, 135);
	lv_obj_set_size(ui->video_rec_view_gap, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_gap, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_gap, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_gap, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_gap);
	//Write codes video_rec_img_5
	ui->video_rec_img_5 = lv_img_create(ui->video_rec_view_gap);
	lv_img_set_src(ui->video_rec_img_5, gui_get_res_path(GUI_RES_REC_NOCYC_PNG));
	lv_img_set_pivot(ui->video_rec_img_5, 0, 0);
	lv_img_set_angle(ui->video_rec_img_5, 0);
	lv_img_set_zoom(ui->video_rec_img_5, 256);

	//Set style for video_rec_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_5, 8, 6);
	lv_obj_set_size(ui->video_rec_img_5, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_5, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_5
	ui->video_rec_lbl_5 = lv_label_create(ui->video_rec_view_gap);
	lv_label_set_text(ui->video_rec_lbl_5, _("gaprec"));
	lv_label_set_long_mode(ui->video_rec_lbl_5, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_5_font = _font("gaprec");
	if(video_rec_lbl_5_font == NULL) video_rec_lbl_5_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_5, video_rec_lbl_5_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_5, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_5, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_5, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_hdr
	ui->video_rec_view_hdr = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_hdr. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_hdr, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_hdr. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_hdr, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_hdr, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_hdr, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_hdr, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_hdr, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_hdr, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_hdr, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_hdr, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_hdr, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_hdr, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_hdr, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_hdr, 0, 180);
	lv_obj_set_size(ui->video_rec_view_hdr, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_hdr, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_hdr, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_hdr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_hdr);
	//Write codes video_rec_img_6
	ui->video_rec_img_6 = lv_img_create(ui->video_rec_view_hdr);
	lv_img_set_src(ui->video_rec_img_6, gui_get_res_path(GUI_RES_M_HDR_PNG));
	lv_img_set_pivot(ui->video_rec_img_6, 0, 0);
	lv_img_set_angle(ui->video_rec_img_6, 0);
	lv_img_set_zoom(ui->video_rec_img_6, 256);

	//Set style for video_rec_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_6, 8, 6);
	lv_obj_set_size(ui->video_rec_img_6, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_6, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_6
	ui->video_rec_lbl_6 = lv_label_create(ui->video_rec_view_hdr);
	lv_label_set_text(ui->video_rec_lbl_6, _("hdr"));
	lv_label_set_long_mode(ui->video_rec_lbl_6, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_6_font = _font("hdr");
	if(video_rec_lbl_6_font == NULL) video_rec_lbl_6_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_6, video_rec_lbl_6_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_6, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_6, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_6, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_exp
	ui->video_rec_view_exp = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_exp. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_exp, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_exp. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_exp, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_exp, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_exp, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_exp, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_exp, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_exp, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_exp, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_exp, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_exp, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_exp, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_exp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_exp, 0, 225);
	lv_obj_set_size(ui->video_rec_view_exp, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_exp, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_exp, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_exp, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_exp);
	//Write codes video_rec_img_7
	ui->video_rec_img_7 = lv_img_create(ui->video_rec_view_exp);
	lv_img_set_src(ui->video_rec_img_7, gui_get_res_path(GUI_RES_M_EXP_PNG));
	lv_img_set_pivot(ui->video_rec_img_7, 0, 0);
	lv_img_set_angle(ui->video_rec_img_7, 0);
	lv_img_set_zoom(ui->video_rec_img_7, 256);

	//Set style for video_rec_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_7, 8, 6);
	lv_obj_set_size(ui->video_rec_img_7, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_7, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_7
	ui->video_rec_lbl_7 = lv_label_create(ui->video_rec_view_exp);
	lv_label_set_text(ui->video_rec_lbl_7, _("exposure"));
	lv_label_set_long_mode(ui->video_rec_lbl_7, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_7_font = _font("exposure");
	if(video_rec_lbl_7_font == NULL) video_rec_lbl_7_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_7, video_rec_lbl_7_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_7, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_7, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_7, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_motd
	ui->video_rec_view_motd = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_motd. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_motd, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_motd. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_motd, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_motd, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_motd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_motd, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_motd, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_motd, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_motd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_motd, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_motd, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_motd, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_motd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_motd, 0, 270);
	lv_obj_set_size(ui->video_rec_view_motd, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_motd, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_motd, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_motd, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_motd);
	//Write codes video_rec_img_8
	ui->video_rec_img_8 = lv_img_create(ui->video_rec_view_motd);
	lv_img_set_src(ui->video_rec_img_8, gui_get_res_path(GUI_RES_M_MOT_PNG));
	lv_img_set_pivot(ui->video_rec_img_8, 0, 0);
	lv_img_set_angle(ui->video_rec_img_8, 0);
	lv_img_set_zoom(ui->video_rec_img_8, 256);

	//Set style for video_rec_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_8, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_8, 8, 6);
	lv_obj_set_size(ui->video_rec_img_8, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_8, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_8
	ui->video_rec_lbl_8 = lv_label_create(ui->video_rec_view_motd);
	lv_label_set_text(ui->video_rec_lbl_8, _("motion"));
	lv_label_set_long_mode(ui->video_rec_lbl_8, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_8_font = _font("motion");
	if(video_rec_lbl_8_font == NULL) video_rec_lbl_8_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_8, video_rec_lbl_8_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_8, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_8, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_8, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_mic
	ui->video_rec_view_mic = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_mic. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_mic, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_mic. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_mic, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_mic, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_mic, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_mic, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_mic, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_mic, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_mic, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_mic, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_mic, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_mic, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_mic, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_mic, 0, 315);
	lv_obj_set_size(ui->video_rec_view_mic, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_mic, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_mic, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_mic, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_mic);
	//Write codes video_rec_img_9
	ui->video_rec_img_9 = lv_img_create(ui->video_rec_view_mic);
	lv_img_set_src(ui->video_rec_img_9, gui_get_res_path(GUI_RES_M_AUD_PNG));
	lv_img_set_pivot(ui->video_rec_img_9, 0, 0);
	lv_img_set_angle(ui->video_rec_img_9, 0);
	lv_img_set_zoom(ui->video_rec_img_9, 256);

	//Set style for video_rec_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_9, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_9, 8, 6);
	lv_obj_set_size(ui->video_rec_img_9, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_9, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_9
	ui->video_rec_lbl_9 = lv_label_create(ui->video_rec_view_mic);
	lv_label_set_text(ui->video_rec_lbl_9, _("record"));
	lv_label_set_long_mode(ui->video_rec_lbl_9, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_9_font = _font("record");
	if(video_rec_lbl_9_font == NULL) video_rec_lbl_9_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_9, video_rec_lbl_9_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_9, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_9, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_9, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_date
	ui->video_rec_view_date = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_date. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_date, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_date. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_date, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_date, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_date, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_date, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_date, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_date, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_date, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_date, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_date, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_date, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_date, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_date, 0, 360);
	lv_obj_set_size(ui->video_rec_view_date, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_date, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_date, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_date, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_date);
	//Write codes video_rec_img_10
	ui->video_rec_img_10 = lv_img_create(ui->video_rec_view_date);
	lv_img_set_src(ui->video_rec_img_10, gui_get_res_path(GUI_RES_M_DAT_PNG));
	lv_img_set_pivot(ui->video_rec_img_10, 0, 0);
	lv_img_set_angle(ui->video_rec_img_10, 0);
	lv_img_set_zoom(ui->video_rec_img_10, 256);

	//Set style for video_rec_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_10, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_10, 8, 6);
	lv_obj_set_size(ui->video_rec_img_10, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_10, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_10
	ui->video_rec_lbl_10 = lv_label_create(ui->video_rec_view_date);
	lv_label_set_text(ui->video_rec_lbl_10, _("date"));
	lv_label_set_long_mode(ui->video_rec_lbl_10, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_10_font = _font("date");
	if(video_rec_lbl_10_font == NULL) video_rec_lbl_10_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_10, video_rec_lbl_10_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_10, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_10, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_10, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_gra
	ui->video_rec_view_gra = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_gra. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_gra, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_gra. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_gra, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_gra, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_gra, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_gra, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_gra, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_gra, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_gra, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_gra, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_gra, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_gra, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_gra, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_gra, 0, 405);
	lv_obj_set_size(ui->video_rec_view_gra, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_gra, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_gra, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_gra, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_gra);
	//Write codes video_rec_img_11
	ui->video_rec_img_11 = lv_img_create(ui->video_rec_view_gra);
	lv_img_set_src(ui->video_rec_img_11, gui_get_res_path(GUI_RES_M_GRA_PNG));
	lv_img_set_pivot(ui->video_rec_img_11, 0, 0);
	lv_img_set_angle(ui->video_rec_img_11, 0);
	lv_img_set_zoom(ui->video_rec_img_11, 256);

	//Set style for video_rec_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_11, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_11, 8, 6);
	lv_obj_set_size(ui->video_rec_img_11, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_11, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_11
	ui->video_rec_lbl_11 = lv_label_create(ui->video_rec_view_gra);
	lv_label_set_text(ui->video_rec_lbl_11, _("gsensor"));
	lv_label_set_long_mode(ui->video_rec_lbl_11, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_11_font = _font("gsensor");
	if(video_rec_lbl_11_font == NULL) video_rec_lbl_11_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_11, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_11, video_rec_lbl_11_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_11, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_11, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_11, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_par
	ui->video_rec_view_par = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_par. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_par, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_par. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_par, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_par, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_par, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_par, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_par, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_par, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_par, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_par, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_par, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_par, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_par, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_par, 0, 450);
	lv_obj_set_size(ui->video_rec_view_par, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_par, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_par, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_par, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_par);
	//Write codes video_rec_img_12
	ui->video_rec_img_12 = lv_img_create(ui->video_rec_view_par);
	lv_img_set_src(ui->video_rec_img_12, gui_get_res_path(GUI_RES_M_PARK_PNG));
	lv_img_set_pivot(ui->video_rec_img_12, 0, 0);
	lv_img_set_angle(ui->video_rec_img_12, 0);
	lv_img_set_zoom(ui->video_rec_img_12, 256);

	//Set style for video_rec_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_12, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_12, 8, 6);
	lv_obj_set_size(ui->video_rec_img_12, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_12, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_12
	ui->video_rec_lbl_12 = lv_label_create(ui->video_rec_view_par);
	lv_label_set_text(ui->video_rec_lbl_12, _("guard"));
	lv_label_set_long_mode(ui->video_rec_lbl_12, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_12_font = _font("guard");
	if(video_rec_lbl_12_font == NULL) video_rec_lbl_12_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_12, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_12, video_rec_lbl_12_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_12, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_12, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_12, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_num
	ui->video_rec_view_num = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_num. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_num, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_num. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_num, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_num, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_num, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_num, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_num, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_num, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_num, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_num, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_num, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_num, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_num, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_num, 0, 495);
	lv_obj_set_size(ui->video_rec_view_num, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_num, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_num, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_num, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_num);
	//Write codes video_rec_img_13
	ui->video_rec_img_13 = lv_img_create(ui->video_rec_view_num);
	lv_img_set_src(ui->video_rec_img_13, gui_get_res_path(GUI_RES_M_NUM_PNG));
	lv_img_set_pivot(ui->video_rec_img_13, 0, 0);
	lv_img_set_angle(ui->video_rec_img_13, 0);
	lv_img_set_zoom(ui->video_rec_img_13, 256);

	//Set style for video_rec_img_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_13, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_13, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_13, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_13, 8, 6);
	lv_obj_set_size(ui->video_rec_img_13, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_13, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_13
	ui->video_rec_lbl_13 = lv_label_create(ui->video_rec_view_num);
	lv_label_set_text(ui->video_rec_lbl_13, _("carnum"));
	lv_label_set_long_mode(ui->video_rec_lbl_13, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_13_font = _font("carnum");
	if(video_rec_lbl_13_font == NULL) video_rec_lbl_13_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_13, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_13, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_13, video_rec_lbl_13_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_13, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_13, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_13, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_13, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_13, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_view_hlw
	ui->video_rec_view_hlw = lv_obj_create(ui->video_rec_view_menu);

	//Set style for video_rec_view_hlw. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_hlw, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_view_hlw. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_view_hlw, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_view_hlw, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_view_hlw, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_view_hlw, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_view_hlw, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_view_hlw, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_view_hlw, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_view_hlw, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_view_hlw, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_view_hlw, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_hlw, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_view_hlw, 0, 540);
	lv_obj_set_size(ui->video_rec_view_hlw, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_hlw, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_hlw, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_rec_view_hlw, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_rec_view_hlw);
	//Write codes video_rec_img_14
	ui->video_rec_img_14 = lv_img_create(ui->video_rec_view_hlw);
	lv_img_set_src(ui->video_rec_img_14, gui_get_res_path(GUI_RES_M_FLIG_PNG));
	lv_img_set_pivot(ui->video_rec_img_14, 0, 0);
	lv_img_set_angle(ui->video_rec_img_14, 0);
	lv_img_set_zoom(ui->video_rec_img_14, 256);

	//Set style for video_rec_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_14, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_14, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_14, 8, 6);
	lv_obj_set_size(ui->video_rec_img_14, 29, 29);
	lv_obj_add_flag(ui->video_rec_img_14, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_lbl_14
	ui->video_rec_lbl_14 = lv_label_create(ui->video_rec_view_hlw);
	lv_label_set_text(ui->video_rec_lbl_14, _("lamp"));
	lv_label_set_long_mode(ui->video_rec_lbl_14, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_rec_lbl_14_font = _font("lamp");
	if(video_rec_lbl_14_font == NULL) video_rec_lbl_14_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_rec_lbl_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_lbl_14, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_lbl_14, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_lbl_14, video_rec_lbl_14_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_lbl_14, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_lbl_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_lbl_14, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_lbl_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_lbl_14, 50, 6);
	lv_obj_set_size(ui->video_rec_lbl_14, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_rec_lbl_14, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_img_15
	ui->video_rec_img_15 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_15, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->video_rec_img_15, 0, 0);
	lv_img_set_angle(ui->video_rec_img_15, 0);
	lv_img_set_zoom(ui->video_rec_img_15, 256);

	//Set style for video_rec_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_15, 0, 0);
	lv_obj_set_size(ui->video_rec_img_15, 800, 40);
	lv_obj_add_flag(ui->video_rec_img_15, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_16
	ui->video_rec_img_16 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_16, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->video_rec_img_16, 0, 0);
	lv_img_set_angle(ui->video_rec_img_16, 0);
	lv_img_set_zoom(ui->video_rec_img_16, 256);

	//Set style for video_rec_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_16, 0, 440);
	lv_obj_set_size(ui->video_rec_img_16, 800, 40);
	lv_obj_add_flag(ui->video_rec_img_16, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_17
	ui->video_rec_img_17 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_17, gui_get_res_path(GUI_RES_REC_PNG));
	lv_img_set_pivot(ui->video_rec_img_17, 0, 0);
	lv_img_set_angle(ui->video_rec_img_17, 0);
	lv_img_set_zoom(ui->video_rec_img_17, 256);

	//Set style for video_rec_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_img_17, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_img_17, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_17, 9, 5);
	lv_obj_set_size(ui->video_rec_img_17, 40, 30);
	lv_obj_add_flag(ui->video_rec_img_17, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_18
	ui->video_rec_img_18 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_18, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui->video_rec_img_18, 0, 0);
	lv_img_set_angle(ui->video_rec_img_18, 0);
	lv_img_set_zoom(ui->video_rec_img_18, 256);

	//Set style for video_rec_img_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_18, 70, 1);
	lv_obj_set_size(ui->video_rec_img_18, 37, 37);
	lv_obj_add_flag(ui->video_rec_img_18, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_19
	ui->video_rec_img_19 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_19, gui_get_res_path(GUI_RES_LEFT_PNG));
	lv_img_set_pivot(ui->video_rec_img_19, 0, 0);
	lv_img_set_angle(ui->video_rec_img_19, 0);
	lv_img_set_zoom(ui->video_rec_img_19, 256);

	//Set style for video_rec_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_19, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_19, 200, 445);
	lv_obj_set_size(ui->video_rec_img_19, 21, 29);
	lv_obj_add_flag(ui->video_rec_img_19, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_20
	ui->video_rec_img_20 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_20, gui_get_res_path(GUI_RES_UP_PNG));
	lv_img_set_pivot(ui->video_rec_img_20, 0, 0);
	lv_img_set_angle(ui->video_rec_img_20, 0);
	lv_img_set_zoom(ui->video_rec_img_20, 256);

	//Set style for video_rec_img_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_20, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_20, 321, 448);
	lv_obj_set_size(ui->video_rec_img_20, 29, 21);
	lv_obj_add_flag(ui->video_rec_img_20, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_21
	ui->video_rec_img_21 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_21, gui_get_res_path(GUI_RES_DOWN_PNG));
	lv_img_set_pivot(ui->video_rec_img_21, 0, 0);
	lv_img_set_angle(ui->video_rec_img_21, 0);
	lv_img_set_zoom(ui->video_rec_img_21, 256);

	//Set style for video_rec_img_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_21, 450, 448);
	lv_obj_set_size(ui->video_rec_img_21, 29, 21);
	lv_obj_add_flag(ui->video_rec_img_21, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_img_22
	ui->video_rec_img_22 = lv_img_create(ui->video_rec_view_menu_b);
	lv_img_set_src(ui->video_rec_img_22, gui_get_res_path(GUI_RES_RIGHT_PNG));
	lv_img_set_pivot(ui->video_rec_img_22, 0, 0);
	lv_img_set_angle(ui->video_rec_img_22, 0);
	lv_img_set_zoom(ui->video_rec_img_22, 256);

	//Set style for video_rec_img_22. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_rec_img_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_rec_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_rec_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_rec_img_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_img_22, 579, 445);
	lv_obj_set_size(ui->video_rec_img_22, 21, 29);
	lv_obj_add_flag(ui->video_rec_img_22, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_rec_view_submenu
	ui->video_rec_view_submenu = lv_obj_create(ui->video_rec);

	//Set style for video_rec_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_submenu, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_view_submenu, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_submenu, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_view_submenu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_view_submenu, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_view_submenu, 111, 83);
	lv_obj_set_size(ui->video_rec_view_submenu, 590, 314);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_submenu, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_rec_rec_submenu_btn_1
	ui->video_rec_rec_submenu_btn_1 = lv_btn_create(ui->video_rec_view_submenu);

	//Set style for video_rec_rec_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_1, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_1, 203, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_1, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_rec_submenu_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_rec_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_1, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_1, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_1, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_1, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_rec_submenu_btn_1, 83, 44);
	lv_obj_set_size(ui->video_rec_rec_submenu_btn_1, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_rec_rec_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_rec_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_rec_rec_submenu_btn_1_label = lv_label_create(ui->video_rec_rec_submenu_btn_1);
	lv_label_set_text(ui->video_rec_rec_submenu_btn_1_label, "button1");
	lv_obj_set_style_pad_all(ui->video_rec_rec_submenu_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_rec_rec_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_rec_rec_submenu_btn_2
	ui->video_rec_rec_submenu_btn_2 = lv_btn_create(ui->video_rec_view_submenu);

	//Set style for video_rec_rec_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_2, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_2, 215, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_2, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_rec_submenu_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_rec_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_2, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_2, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_2, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_rec_submenu_btn_2, 83, 111);
	lv_obj_set_size(ui->video_rec_rec_submenu_btn_2, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_rec_rec_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_rec_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_rec_rec_submenu_btn_2_label = lv_label_create(ui->video_rec_rec_submenu_btn_2);
	lv_label_set_text(ui->video_rec_rec_submenu_btn_2_label, "button2");
	lv_obj_set_style_pad_all(ui->video_rec_rec_submenu_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_rec_rec_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_rec_rec_submenu_btn_3
	ui->video_rec_rec_submenu_btn_3 = lv_btn_create(ui->video_rec_view_submenu);

	//Set style for video_rec_rec_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_3, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_3, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_3, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_3, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_rec_submenu_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_rec_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_3, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_3, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_3, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_rec_submenu_btn_3, 83, 171);
	lv_obj_set_size(ui->video_rec_rec_submenu_btn_3, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_rec_rec_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_rec_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_rec_rec_submenu_btn_3_label = lv_label_create(ui->video_rec_rec_submenu_btn_3);
	lv_label_set_text(ui->video_rec_rec_submenu_btn_3_label, "button3");
	lv_obj_set_style_pad_all(ui->video_rec_rec_submenu_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_rec_rec_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_rec_rec_submenu_btn_4
	ui->video_rec_rec_submenu_btn_4 = lv_btn_create(ui->video_rec_view_submenu);

	//Set style for video_rec_rec_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_4, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_4, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_4, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_4, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_rec_submenu_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_rec_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_rec_submenu_btn_4, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_rec_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_rec_submenu_btn_4, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_rec_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_rec_submenu_btn_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_rec_submenu_btn_4, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_rec_submenu_btn_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_rec_submenu_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_rec_submenu_btn_4, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_rec_rec_submenu_btn_4, 83, 233);
	lv_obj_set_size(ui->video_rec_rec_submenu_btn_4, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_rec_rec_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_rec_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_rec_rec_submenu_btn_4_label = lv_label_create(ui->video_rec_rec_submenu_btn_4);
	lv_label_set_text(ui->video_rec_rec_submenu_btn_4_label, "button4");
	lv_obj_set_style_pad_all(ui->video_rec_rec_submenu_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_rec_rec_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_rec_roller_mutifunc
	ui->video_rec_roller_mutifunc = lv_roller_create(ui->video_rec_view_submenu);

	//Set style for video_rec_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_roller_mutifunc, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_roller_mutifunc, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_roller_mutifunc, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_roller_mutifunc, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_line_space(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_align(ui->video_rec_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_rec_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style for video_rec_roller_mutifunc. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_rec_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_roller_mutifunc, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_roller_mutifunc, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_roller_mutifunc, 0, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_rec_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_roller_mutifunc, 223, 55);
	lv_obj_set_size(ui->video_rec_roller_mutifunc, 148, 214);
	lv_obj_set_scrollbar_mode(ui->video_rec_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_roller_mutifunc, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_roller_set_options(ui->video_rec_roller_mutifunc,"1\n2\n3\n4\n5",LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->video_rec_roller_mutifunc,5);
	//Write codes video_rec_view_carnum
	ui->video_rec_view_carnum = lv_obj_create(ui->video_rec_view_submenu);

	//Set style for video_rec_view_carnum. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_view_carnum, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_rec_view_carnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_view_carnum, 77, 42);
	lv_obj_set_size(ui->video_rec_view_carnum, 450, 164);
	lv_obj_set_scrollbar_mode(ui->video_rec_view_carnum, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_rec_ddlist_1
	ui->video_rec_ddlist_1 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_1, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_1, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_1, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_1, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_1, 0);

	//Set style for video_rec_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_1, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_1, &lv_font_FangZhengKaiTiJianTi_1_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_1, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_1, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_1, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_1, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_1, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_1, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_1, &lv_font_FangZhengKaiTiJianTi_1_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_1, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_1, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_1, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_1_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_1_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_1_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_1_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_1_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_1_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_1_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_1_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_1_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_1_extra_list_selected_checked, &lv_font_FangZhengKaiTiJianTi_1_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_1_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_1), &style_video_rec_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_1_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_1_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_1_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_1_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_1_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_1_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_1_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_1_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_1_extra_list_main_default, &lv_font_FangZhengKaiTiJianTi_1_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_1_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_1_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_1), &style_video_rec_ddlist_1_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_1_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_1_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_1_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_1_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_1_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_1_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_1), &style_video_rec_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_1, 102, 38);
	lv_obj_set_size(ui->video_rec_ddlist_1, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_1, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_rec_ddlist_2
	ui->video_rec_ddlist_2 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_2, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_2, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_2, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_2, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_2, 0);

	//Set style for video_rec_ddlist_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_2, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_2, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_2, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_2, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_2, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_2, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_2, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_2, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_2, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_2_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_2_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_2_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_2_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_2_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_2_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_2_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_2_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_2_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_2_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_2_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_2_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_2_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_2), &style_video_rec_ddlist_2_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_2_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_2_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_2_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_2_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_2_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_2_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_2_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_2_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_2_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_2_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_2_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_2_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_2_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_2_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_2), &style_video_rec_ddlist_2_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_2_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_2_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_2_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_2_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_2_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_2_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_2), &style_video_rec_ddlist_2_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_2, 288, 38);
	lv_obj_set_size(ui->video_rec_ddlist_2, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_2, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_rec_ddlist_3
	ui->video_rec_ddlist_3 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_3, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_3, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_3, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_3, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_3, 0);

	//Set style for video_rec_ddlist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_3, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_3, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_3, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_3, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_3, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_3, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_3, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_3, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_3, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_3, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_3_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_3_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_3_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_3_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_3_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_3_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_3_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_3_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_3_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_3_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_3_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_3_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_3_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_3), &style_video_rec_ddlist_3_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_3_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_3_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_3_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_3_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_3_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_3_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_3_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_3_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_3_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_3_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_3_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_3_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_3_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_3_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_3), &style_video_rec_ddlist_3_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_3_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_3_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_3_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_3_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_3_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_3_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_3), &style_video_rec_ddlist_3_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_3, 28, 102);
	lv_obj_set_size(ui->video_rec_ddlist_3, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_3, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_rec_ddlist_4
	ui->video_rec_ddlist_4 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_4, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_4, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_4, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_4, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_4, 0);

	//Set style for video_rec_ddlist_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_4, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_4, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_4, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_4, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_4, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_4, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_4, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_4, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_4, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_4, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_4, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_4, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_4, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_4, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_4, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_4_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_4_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_4_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_4_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_4_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_4_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_4_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_4_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_4_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_4_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_4_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_4_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_4_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_4), &style_video_rec_ddlist_4_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_4_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_4_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_4_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_4_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_4_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_4_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_4_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_4_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_4_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_4_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_4_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_4_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_4_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_4_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_4), &style_video_rec_ddlist_4_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_4_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_4_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_4_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_4_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_4_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_4_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_4), &style_video_rec_ddlist_4_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_4, 111, 102);
	lv_obj_set_size(ui->video_rec_ddlist_4, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_4, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_rec_ddlist_5
	ui->video_rec_ddlist_5 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_5, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_5, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_5, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_5, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_5, 0);

	//Set style for video_rec_ddlist_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_5, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_5, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_5, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_5, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_5, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_5, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_5, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_5, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_5, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_5, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_5, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_5, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_5, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_5, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_5, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_5, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_5, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_5, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_5_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_5_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_5_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_5_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_5_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_5_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_5_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_5_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_5_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_5_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_5_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_5_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_5_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_5), &style_video_rec_ddlist_5_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_5_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_5_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_5_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_5_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_5_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_5_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_5_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_5_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_5_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_5_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_5_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_5_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_5_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_5_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_5), &style_video_rec_ddlist_5_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_5_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_5_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_5_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_5_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_5_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_5_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_5), &style_video_rec_ddlist_5_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_5, 194, 102);
	lv_obj_set_size(ui->video_rec_ddlist_5, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_5, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_5, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_rec_ddlist_6
	ui->video_rec_ddlist_6 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_6, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_6, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_6, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_6, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_6, 0);

	//Set style for video_rec_ddlist_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_6, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_6, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_6, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_6, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_6, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_6, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_6, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_6, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_6, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_6, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_6, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_6, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_6, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_6, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_6, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_6, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_6, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_6, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_6, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_6, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_6, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_6_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_6_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_6_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_6_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_6_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_6_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_6_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_6_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_6_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_6_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_6_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_6_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_6_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_6), &style_video_rec_ddlist_6_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_6_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_6_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_6_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_6_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_6_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_6_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_6_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_6_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_6_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_6_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_6_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_6_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_6_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_6_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_6), &style_video_rec_ddlist_6_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_6_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_6_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_6_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_6_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_6_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_6_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_6), &style_video_rec_ddlist_6_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_6, 277, 102);
	lv_obj_set_size(ui->video_rec_ddlist_6, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_6, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_6, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_rec_ddlist_7
	ui->video_rec_ddlist_7 = lv_dropdown_create(ui->video_rec_view_carnum);
	lv_dropdown_set_options(ui->video_rec_ddlist_7, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui->video_rec_ddlist_7, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_7, LV_SYMBOL_DOWN);
	lv_dropdown_set_symbol(ui->video_rec_ddlist_7, NULL);
	lv_dropdown_set_selected(ui->video_rec_ddlist_7, 0);

	//Set style for video_rec_ddlist_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_rec_ddlist_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_7, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_7, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_7, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_7, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_7, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_rec_ddlist_7. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_rec_ddlist_7, 3, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_rec_ddlist_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_rec_ddlist_7, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_rec_ddlist_7, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_rec_ddlist_7, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_rec_ddlist_7, 1, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_rec_ddlist_7, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_rec_ddlist_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_rec_ddlist_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_rec_ddlist_7, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_rec_ddlist_7, 204, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_rec_ddlist_7, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_rec_ddlist_7, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_rec_ddlist_7, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_rec_ddlist_7, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_rec_ddlist_7, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_rec_ddlist_7, 6, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_rec_ddlist_7, 8, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_7_extra_list_selected_checked
	static lv_style_t style_video_rec_ddlist_7_extra_list_selected_checked;
	ui_init_style(&style_video_rec_ddlist_7_extra_list_selected_checked);
	lv_style_set_radius(&style_video_rec_ddlist_7_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_7_extra_list_selected_checked, lv_color_make(0x42, 0xA5, 0xF5));
	lv_style_set_bg_opa(&style_video_rec_ddlist_7_extra_list_selected_checked, 230);
	lv_style_set_border_color(&style_video_rec_ddlist_7_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_7_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_7_extra_list_selected_checked, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_7_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_7_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_video_rec_ddlist_7_extra_list_selected_checked, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_7_extra_list_selected_checked, 0);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_7), &style_video_rec_ddlist_7_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_7_extra_list_main_default
	static lv_style_t style_video_rec_ddlist_7_extra_list_main_default;
	ui_init_style(&style_video_rec_ddlist_7_extra_list_main_default);
	lv_style_set_radius(&style_video_rec_ddlist_7_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_7_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_video_rec_ddlist_7_extra_list_main_default, 255);
	lv_style_set_border_color(&style_video_rec_ddlist_7_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_video_rec_ddlist_7_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_video_rec_ddlist_7_extra_list_main_default, 255);
	lv_style_set_border_side(&style_video_rec_ddlist_7_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_video_rec_ddlist_7_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_video_rec_ddlist_7_extra_list_main_default, &lv_font_montserratMedium_18);
	lv_style_set_text_letter_space(&style_video_rec_ddlist_7_extra_list_main_default, 0);
	lv_style_set_max_height(&style_video_rec_ddlist_7_extra_list_main_default, 110);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_7), &style_video_rec_ddlist_7_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_7_extra_list_scrollbar_default
	static lv_style_t style_video_rec_ddlist_7_extra_list_scrollbar_default;
	ui_init_style(&style_video_rec_ddlist_7_extra_list_scrollbar_default);
	lv_style_set_radius(&style_video_rec_ddlist_7_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_video_rec_ddlist_7_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_opa(&style_video_rec_ddlist_7_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->video_rec_ddlist_7), &style_video_rec_ddlist_7_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_rec_ddlist_7, 361, 102);
	lv_obj_set_size(ui->video_rec_ddlist_7, 60, 31);
	lv_obj_set_scrollbar_mode(ui->video_rec_ddlist_7, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_rec_ddlist_7, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_update_layout(ui->video_rec);
	ui->video_rec_del = false;

	//Init events for screen
	events_init_video_rec(ui);
	return ui->video_rec;
}
void unload_scr_video_rec(lv_ui *ui)
{
	ui->video_rec_del = true;
}

#endif

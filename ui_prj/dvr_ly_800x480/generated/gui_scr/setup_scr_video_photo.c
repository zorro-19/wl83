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


lv_obj_t * setup_scr_video_photo(lv_ui *ui)
{
	//Write codes video_photo
	ui->video_photo = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for video_photo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_photo, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->video_photo, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_scan
	ui->video_photo_view_scan = lv_obj_create(ui->video_photo);

	//Set style for video_photo_view_scan. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_scan, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_view_scan, 0, 0);
	lv_obj_set_size(ui->video_photo_view_scan, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_scan, LV_SCROLLBAR_MODE_OFF);
	lv_group_add_obj(def_group, ui->video_photo_view_scan);
	//Write codes video_photo_img_taking_photo
	ui->video_photo_img_taking_photo = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_taking_photo, gui_get_res_path(GUI_RES_TP_3_PNG));
	lv_img_set_pivot(ui->video_photo_img_taking_photo, 0, 0);
	lv_img_set_angle(ui->video_photo_img_taking_photo, 0);
	lv_img_set_zoom(ui->video_photo_img_taking_photo, 256);

	//Set style for video_photo_img_taking_photo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_taking_photo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_taking_photo, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_taking_photo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_taking_photo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_taking_photo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_taking_photo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_taking_photo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_taking_photo, 12, 10);
	lv_obj_set_size(ui->video_photo_img_taking_photo, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_taking_photo, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_state(ui->video_photo_img_taking_photo, LV_STATE_FOCUS_KEY);
	lv_obj_add_flag(ui->video_photo_img_taking_photo, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_photo_icon
	ui->video_photo_img_photo_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_photo_icon, gui_get_res_path(GUI_RES_TP_PNG));
	lv_img_set_pivot(ui->video_photo_img_photo_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_photo_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_photo_icon, 256);

	//Set style for video_photo_img_photo_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_photo_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_photo_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_photo_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_photo_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_photo_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_photo_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_photo_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_photo_icon, 12, 10);
	lv_obj_set_size(ui->video_photo_img_photo_icon, 29, 29);
	lv_obj_add_state(ui->video_photo_img_photo_icon, LV_STATE_FOCUS_KEY);
	lv_obj_add_flag(ui->video_photo_img_photo_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_exp_icon
	ui->video_photo_img_exp_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_exp_icon, gui_get_res_path(GUI_RES_EXP_A0_PNG));
	lv_img_set_pivot(ui->video_photo_img_exp_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_exp_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_exp_icon, 256);

	//Set style for video_photo_img_exp_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_exp_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_exp_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_exp_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_exp_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_exp_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_exp_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_exp_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_exp_icon, 12, 54);
	lv_obj_set_size(ui->video_photo_img_exp_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_exp_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_awb_icon
	ui->video_photo_img_awb_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_awb_icon, gui_get_res_path(GUI_RES_AWB_AUTO_PNG));
	lv_img_set_pivot(ui->video_photo_img_awb_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_awb_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_awb_icon, 256);

	//Set style for video_photo_img_awb_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_awb_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_awb_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_awb_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_awb_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_awb_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_awb_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_awb_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_awb_icon, 12, 98);
	lv_obj_set_size(ui->video_photo_img_awb_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_awb_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_iso_icon
	ui->video_photo_img_iso_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_iso_icon, gui_get_res_path(GUI_RES_ISO_AUTO_PNG));
	lv_img_set_pivot(ui->video_photo_img_iso_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_iso_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_iso_icon, 256);

	//Set style for video_photo_img_iso_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_iso_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_iso_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_iso_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_iso_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_iso_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_iso_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_iso_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_iso_icon, 12, 144);
	lv_obj_set_size(ui->video_photo_img_iso_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_iso_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_qua_icon
	ui->video_photo_img_qua_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_qua_icon, gui_get_res_path(GUI_RES_Q1_PNG));
	lv_img_set_pivot(ui->video_photo_img_qua_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_qua_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_qua_icon, 256);

	//Set style for video_photo_img_qua_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_qua_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_qua_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_qua_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_qua_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_qua_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_qua_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_qua_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_qua_icon, 12, 192);
	lv_obj_set_size(ui->video_photo_img_qua_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_qua_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_delay_icon
	ui->video_photo_img_delay_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_delay_icon, gui_get_res_path(GUI_RES_DL2_PNG));
	lv_img_set_pivot(ui->video_photo_img_delay_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_delay_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_delay_icon, 256);

	//Set style for video_photo_img_delay_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_delay_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_delay_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_delay_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_delay_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_delay_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_delay_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_delay_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_delay_icon, 97, 10);
	lv_obj_set_size(ui->video_photo_img_delay_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_delay_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_shake_icon
	ui->video_photo_img_shake_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_shake_icon, gui_get_res_path(GUI_RES_SHAKE_OFF_PNG));
	lv_img_set_pivot(ui->video_photo_img_shake_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_shake_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_shake_icon, 256);

	//Set style for video_photo_img_shake_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_shake_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_shake_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_shake_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_shake_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_shake_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_shake_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_shake_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_shake_icon, 146, 10);
	lv_obj_set_size(ui->video_photo_img_shake_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_shake_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_repeat_icon
	ui->video_photo_img_repeat_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_repeat_icon, gui_get_res_path(GUI_RES_LIANP_PNG));
	lv_img_set_pivot(ui->video_photo_img_repeat_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_repeat_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_repeat_icon, 256);

	//Set style for video_photo_img_repeat_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_repeat_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_repeat_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_repeat_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_repeat_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_repeat_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_repeat_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_repeat_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_repeat_icon, 200, 10);
	lv_obj_set_size(ui->video_photo_img_repeat_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_repeat_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_sd_icon
	ui->video_photo_img_sd_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_sd_icon, gui_get_res_path(GUI_RES_CARD_ONLINE_PNG));
	lv_img_set_pivot(ui->video_photo_img_sd_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_sd_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_sd_icon, 256);

	//Set style for video_photo_img_sd_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_sd_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_sd_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_sd_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_sd_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_sd_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_sd_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_sd_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_sd_icon, 758, 410);
	lv_obj_set_size(ui->video_photo_img_sd_icon, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_sd_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_bat_icon
	ui->video_photo_img_bat_icon = lv_img_create(ui->video_photo_view_scan);
	lv_img_set_src(ui->video_photo_img_bat_icon, gui_get_res_path(GUI_RES_BAT_FULL_PNG));
	lv_img_set_pivot(ui->video_photo_img_bat_icon, 0, 0);
	lv_img_set_angle(ui->video_photo_img_bat_icon, 0);
	lv_img_set_zoom(ui->video_photo_img_bat_icon, 256);

	//Set style for video_photo_img_bat_icon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_bat_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_bat_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_bat_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_bat_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_bat_icon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_bat_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_bat_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_bat_icon, 762, 454);
	lv_obj_set_size(ui->video_photo_img_bat_icon, 25, 15);
	lv_obj_add_flag(ui->video_photo_img_bat_icon, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_photo_reso
	ui->video_photo_lbl_photo_reso = lv_label_create(ui->video_photo_view_scan);
	lv_label_set_text(ui->video_photo_lbl_photo_reso, "1M");
	lv_label_set_long_mode(ui->video_photo_lbl_photo_reso, LV_LABEL_LONG_WRAP);

	//Set style for video_photo_lbl_photo_reso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_photo_reso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_photo_reso, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_photo_reso, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_photo_reso, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_photo_reso, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_photo_reso, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_photo_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_photo_reso, 701, 10);
	lv_obj_set_size(ui->video_photo_lbl_photo_reso, 70, 35);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_photo_reso, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_lbl_remain_pnum
	ui->video_photo_lbl_remain_pnum = lv_label_create(ui->video_photo_view_scan);
	lv_label_set_text(ui->video_photo_lbl_remain_pnum, "99999");
	lv_label_set_long_mode(ui->video_photo_lbl_remain_pnum, LV_LABEL_LONG_WRAP);

	//Set style for video_photo_lbl_remain_pnum. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_remain_pnum, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_remain_pnum, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_remain_pnum, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_remain_pnum, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_remain_pnum, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_remain_pnum, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_remain_pnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_remain_pnum, 687, 42);
	lv_obj_set_size(ui->video_photo_lbl_remain_pnum, 100, 35);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_remain_pnum, LV_SCROLLBAR_MODE_OFF);
	static bool timer_video_photo_digitclock_1_enabled = false;

	//Write codes video_photo_digitclock_1
	ui->video_photo_digitclock_1 = lv_label_create(ui->video_photo_view_scan);
	lv_label_set_text_fmt(ui->video_photo_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
	lv_obj_set_style_text_align(ui->video_photo_digitclock_1, LV_TEXT_ALIGN_CENTER, 0);

	//Set style for video_photo_digitclock_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_digitclock_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_digitclock_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_digitclock_1, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_digitclock_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_digitclock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_digitclock_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_digitclock_1, 20, 439);
	lv_obj_set_size(ui->video_photo_digitclock_1, 300, 35);
	//Write codes video_photo_view_menu_b
	ui->video_photo_view_menu_b = lv_obj_create(ui->video_photo);

	//Set style for video_photo_view_menu_b. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_menu_b, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_menu_b, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_view_menu_b, 0, 0);
	lv_obj_set_size(ui->video_photo_view_menu_b, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_menu_b, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_menu_b, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_photo_view_menu
	ui->video_photo_view_menu = lv_obj_create(ui->video_photo_view_menu_b);

	//Set style for video_photo_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_menu, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_view_menu, 0, 40);
	lv_obj_set_size(ui->video_photo_view_menu, 800, 400);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_menu, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_phm
	ui->video_photo_view_phm = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_phm. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_phm, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_phm. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_phm, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_phm, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_phm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_phm, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_phm, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_phm, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_phm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_phm, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_phm, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_phm, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_phm, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_phm, 0, 0);
	lv_obj_set_size(ui->video_photo_view_phm, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_phm, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_phm, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_phm, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_phm);
	//Write codes video_photo_img_1
	ui->video_photo_img_1 = lv_img_create(ui->video_photo_view_phm);
	lv_img_set_src(ui->video_photo_img_1, gui_get_res_path(GUI_RES_PAIZ_PNG));
	lv_img_set_pivot(ui->video_photo_img_1, 0, 0);
	lv_img_set_angle(ui->video_photo_img_1, 0);
	lv_img_set_zoom(ui->video_photo_img_1, 256);

	//Set style for video_photo_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_1, 8, 6);
	lv_obj_set_size(ui->video_photo_img_1, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_1, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_1
	ui->video_photo_lbl_1 = lv_label_create(ui->video_photo_view_phm);
	lv_label_set_text(ui->video_photo_lbl_1, _("shoot"));
	lv_label_set_long_mode(ui->video_photo_lbl_1, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_1_font = _font("shoot");
	if(video_photo_lbl_1_font == NULL) video_photo_lbl_1_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_1, video_photo_lbl_1_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_1, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_1, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_reso
	ui->video_photo_view_reso = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_reso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_reso, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_reso. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_reso, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_reso, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_reso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_reso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_reso, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_reso, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_reso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_reso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_reso, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_reso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_reso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_reso, 0, 45);
	lv_obj_set_size(ui->video_photo_view_reso, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_reso, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_reso, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_reso, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_reso);
	//Write codes video_photo_img_2
	ui->video_photo_img_2 = lv_img_create(ui->video_photo_view_reso);
	lv_img_set_src(ui->video_photo_img_2, gui_get_res_path(GUI_RES_M_SOLU_PNG));
	lv_img_set_pivot(ui->video_photo_img_2, 0, 0);
	lv_img_set_angle(ui->video_photo_img_2, 0);
	lv_img_set_zoom(ui->video_photo_img_2, 256);

	//Set style for video_photo_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_2, 8, 6);
	lv_obj_set_size(ui->video_photo_img_2, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_2, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_2
	ui->video_photo_lbl_2 = lv_label_create(ui->video_photo_view_reso);
	lv_label_set_text(ui->video_photo_lbl_2, _("reso"));
	lv_label_set_long_mode(ui->video_photo_lbl_2, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_2_font = _font("reso");
	if(video_photo_lbl_2_font == NULL) video_photo_lbl_2_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_2, video_photo_lbl_2_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_2, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_2, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_2, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_cyt
	ui->video_photo_view_cyt = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_cyt. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_cyt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_cyt. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_cyt, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_cyt, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_cyt, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_cyt, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_cyt, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_cyt, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_cyt, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_cyt, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_cyt, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_cyt, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_cyt, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_cyt, 0, 90);
	lv_obj_set_size(ui->video_photo_view_cyt, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_cyt, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_cyt, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_cyt, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_cyt);
	//Write codes video_photo_img_3
	ui->video_photo_img_3 = lv_img_create(ui->video_photo_view_cyt);
	lv_img_set_src(ui->video_photo_img_3, gui_get_res_path(GUI_RES_LIANP_1_PNG));
	lv_img_set_pivot(ui->video_photo_img_3, 0, 0);
	lv_img_set_angle(ui->video_photo_img_3, 0);
	lv_img_set_zoom(ui->video_photo_img_3, 256);

	//Set style for video_photo_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_3, 8, 6);
	lv_obj_set_size(ui->video_photo_img_3, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_3, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_3
	ui->video_photo_lbl_3 = lv_label_create(ui->video_photo_view_cyt);
	lv_label_set_text(ui->video_photo_lbl_3, _("shots"));
	lv_label_set_long_mode(ui->video_photo_lbl_3, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_3_font = _font("shots");
	if(video_photo_lbl_3_font == NULL) video_photo_lbl_3_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_3, video_photo_lbl_3_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_3, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_3, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_3, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_qua
	ui->video_photo_view_qua = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_qua. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_qua, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_qua. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_qua, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_qua, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_qua, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_qua, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_qua, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_qua, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_qua, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_qua, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_qua, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_qua, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_qua, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_qua, 0, 135);
	lv_obj_set_size(ui->video_photo_view_qua, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_qua, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_qua, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_qua, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_qua);
	//Write codes video_photo_img_4
	ui->video_photo_img_4 = lv_img_create(ui->video_photo_view_qua);
	lv_img_set_src(ui->video_photo_img_4, gui_get_res_path(GUI_RES_IMG_Q_PNG));
	lv_img_set_pivot(ui->video_photo_img_4, 0, 0);
	lv_img_set_angle(ui->video_photo_img_4, 0);
	lv_img_set_zoom(ui->video_photo_img_4, 256);

	//Set style for video_photo_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_4, 8, 6);
	lv_obj_set_size(ui->video_photo_img_4, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_4, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_4
	ui->video_photo_lbl_4 = lv_label_create(ui->video_photo_view_qua);
	lv_label_set_text(ui->video_photo_lbl_4, _("quality"));
	lv_label_set_long_mode(ui->video_photo_lbl_4, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_4_font = _font("quality");
	if(video_photo_lbl_4_font == NULL) video_photo_lbl_4_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_4, video_photo_lbl_4_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_4, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_4, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_4, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_acu
	ui->video_photo_view_acu = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_acu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_acu, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_acu. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_acu, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_acu, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_acu, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_acu, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_acu, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_acu, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_acu, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_acu, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_acu, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_acu, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_acu, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_acu, 0, 180);
	lv_obj_set_size(ui->video_photo_view_acu, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_acu, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_acu, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_acu, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_acu);
	//Write codes video_photo_img_5
	ui->video_photo_img_5 = lv_img_create(ui->video_photo_view_acu);
	lv_img_set_src(ui->video_photo_img_5, gui_get_res_path(GUI_RES_RUIDU_PNG));
	lv_img_set_pivot(ui->video_photo_img_5, 0, 0);
	lv_img_set_angle(ui->video_photo_img_5, 0);
	lv_img_set_zoom(ui->video_photo_img_5, 256);

	//Set style for video_photo_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_5, 8, 6);
	lv_obj_set_size(ui->video_photo_img_5, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_5, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_5
	ui->video_photo_lbl_5 = lv_label_create(ui->video_photo_view_acu);
	lv_label_set_text(ui->video_photo_lbl_5, _("sharpness"));
	lv_label_set_long_mode(ui->video_photo_lbl_5, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_5_font = _font("sharpness");
	if(video_photo_lbl_5_font == NULL) video_photo_lbl_5_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_5, video_photo_lbl_5_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_5, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_5, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_5, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_wbl
	ui->video_photo_view_wbl = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_wbl. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_wbl, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_wbl. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_wbl, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_wbl, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_wbl, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_wbl, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_wbl, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_wbl, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_wbl, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_wbl, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_wbl, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_wbl, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_wbl, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_wbl, 0, 225);
	lv_obj_set_size(ui->video_photo_view_wbl, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_wbl, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_wbl, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_wbl, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_wbl);
	//Write codes video_photo_img_6
	ui->video_photo_img_6 = lv_img_create(ui->video_photo_view_wbl);
	lv_img_set_src(ui->video_photo_img_6, gui_get_res_path(GUI_RES_AWB_AUTO_PNG));
	lv_img_set_pivot(ui->video_photo_img_6, 0, 0);
	lv_img_set_angle(ui->video_photo_img_6, 0);
	lv_img_set_zoom(ui->video_photo_img_6, 256);

	//Set style for video_photo_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_6, 8, 6);
	lv_obj_set_size(ui->video_photo_img_6, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_6, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_6
	ui->video_photo_lbl_6 = lv_label_create(ui->video_photo_view_wbl);
	lv_label_set_text(ui->video_photo_lbl_6, _("awb"));
	lv_label_set_long_mode(ui->video_photo_lbl_6, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_6_font = _font("awb");
	if(video_photo_lbl_6_font == NULL) video_photo_lbl_6_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_6, video_photo_lbl_6_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_6, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_6, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_6, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_col
	ui->video_photo_view_col = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_col. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_col, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_col. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_col, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_col, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_col, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_col, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_col, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_col, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_col, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_col, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_col, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_col, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_col, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_col, 0, 270);
	lv_obj_set_size(ui->video_photo_view_col, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_col, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_col, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_col, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_col);
	//Write codes video_photo_img_7
	ui->video_photo_img_7 = lv_img_create(ui->video_photo_view_col);
	lv_img_set_src(ui->video_photo_img_7, gui_get_res_path(GUI_RES_COLOR_PNG));
	lv_img_set_pivot(ui->video_photo_img_7, 0, 0);
	lv_img_set_angle(ui->video_photo_img_7, 0);
	lv_img_set_zoom(ui->video_photo_img_7, 256);

	//Set style for video_photo_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_7, 8, 6);
	lv_obj_set_size(ui->video_photo_img_7, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_7, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_7
	ui->video_photo_lbl_7 = lv_label_create(ui->video_photo_view_col);
	lv_label_set_text(ui->video_photo_lbl_7, _("color"));
	lv_label_set_long_mode(ui->video_photo_lbl_7, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_7_font = _font("color");
	if(video_photo_lbl_7_font == NULL) video_photo_lbl_7_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_7, video_photo_lbl_7_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_7, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_7, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_7, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_iso
	ui->video_photo_view_iso = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_iso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_iso, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_iso. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_iso, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_iso, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_iso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_iso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_iso, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_iso, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_iso, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_iso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_iso, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_iso, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_iso, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_iso, 0, 315);
	lv_obj_set_size(ui->video_photo_view_iso, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_iso, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_iso, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_iso, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_iso);
	//Write codes video_photo_img_8
	ui->video_photo_img_8 = lv_img_create(ui->video_photo_view_iso);
	lv_img_set_src(ui->video_photo_img_8, gui_get_res_path(GUI_RES_ISO_PNG));
	lv_img_set_pivot(ui->video_photo_img_8, 0, 0);
	lv_img_set_angle(ui->video_photo_img_8, 0);
	lv_img_set_zoom(ui->video_photo_img_8, 256);

	//Set style for video_photo_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_8, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_8, 8, 6);
	lv_obj_set_size(ui->video_photo_img_8, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_8, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_8
	ui->video_photo_lbl_8 = lv_label_create(ui->video_photo_view_iso);
	lv_label_set_text(ui->video_photo_lbl_8, _("iso"));
	lv_label_set_long_mode(ui->video_photo_lbl_8, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_8_font = _font("iso");
	if(video_photo_lbl_8_font == NULL) video_photo_lbl_8_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_8, video_photo_lbl_8_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_8, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_8, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_8, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_pexp
	ui->video_photo_view_pexp = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_pexp. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_pexp, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_pexp. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_pexp, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_pexp, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_pexp, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_pexp, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_pexp, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_pexp, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_pexp, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_pexp, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_pexp, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_pexp, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_pexp, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_pexp, 0, 360);
	lv_obj_set_size(ui->video_photo_view_pexp, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_pexp, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_pexp, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_pexp, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_pexp);
	//Write codes video_photo_img_9
	ui->video_photo_img_9 = lv_img_create(ui->video_photo_view_pexp);
	lv_img_set_src(ui->video_photo_img_9, gui_get_res_path(GUI_RES_M_EXP_PNG));
	lv_img_set_pivot(ui->video_photo_img_9, 0, 0);
	lv_img_set_angle(ui->video_photo_img_9, 0);
	lv_img_set_zoom(ui->video_photo_img_9, 256);

	//Set style for video_photo_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_9, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_9, 8, 6);
	lv_obj_set_size(ui->video_photo_img_9, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_9, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_9
	ui->video_photo_lbl_9 = lv_label_create(ui->video_photo_view_pexp);
	lv_label_set_text(ui->video_photo_lbl_9, _("exposure"));
	lv_label_set_long_mode(ui->video_photo_lbl_9, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_9_font = _font("exposure");
	if(video_photo_lbl_9_font == NULL) video_photo_lbl_9_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_9, video_photo_lbl_9_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_9, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_9, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_9, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_sok
	ui->video_photo_view_sok = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_sok. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_sok, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_sok. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_sok, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_sok, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_sok, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_sok, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_sok, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_sok, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_sok, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_sok, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_sok, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_sok, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_sok, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_sok, 0, 405);
	lv_obj_set_size(ui->video_photo_view_sok, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_sok, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_sok, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_sok, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_sok);
	//Write codes video_photo_img_10
	ui->video_photo_img_10 = lv_img_create(ui->video_photo_view_sok);
	lv_img_set_src(ui->video_photo_img_10, gui_get_res_path(GUI_RES_SHAKE_PNG));
	lv_img_set_pivot(ui->video_photo_img_10, 0, 0);
	lv_img_set_angle(ui->video_photo_img_10, 0);
	lv_img_set_zoom(ui->video_photo_img_10, 256);

	//Set style for video_photo_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_10, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_10, 8, 6);
	lv_obj_set_size(ui->video_photo_img_10, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_10, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_10
	ui->video_photo_lbl_10 = lv_label_create(ui->video_photo_view_sok);
	lv_label_set_text(ui->video_photo_lbl_10, _("handshake"));
	lv_label_set_long_mode(ui->video_photo_lbl_10, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_10_font = _font("handshake");
	if(video_photo_lbl_10_font == NULL) video_photo_lbl_10_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_10, video_photo_lbl_10_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_10, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_10, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_10, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_sca
	ui->video_photo_view_sca = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_sca. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_sca, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_sca. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_sca, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_sca, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_sca, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_sca, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_sca, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_sca, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_sca, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_sca, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_sca, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_sca, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_sca, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_sca, 0, 450);
	lv_obj_set_size(ui->video_photo_view_sca, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_sca, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_sca, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_sca, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_sca);
	//Write codes video_photo_img_11
	ui->video_photo_img_11 = lv_img_create(ui->video_photo_view_sca);
	lv_img_set_src(ui->video_photo_img_11, gui_get_res_path(GUI_RES_SCAN_PNG));
	lv_img_set_pivot(ui->video_photo_img_11, 0, 0);
	lv_img_set_angle(ui->video_photo_img_11, 0);
	lv_img_set_zoom(ui->video_photo_img_11, 256);

	//Set style for video_photo_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_11, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_11, 8, 6);
	lv_obj_set_size(ui->video_photo_img_11, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_11, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_11
	ui->video_photo_lbl_11 = lv_label_create(ui->video_photo_view_sca);
	lv_label_set_text(ui->video_photo_lbl_11, _("preview"));
	lv_label_set_long_mode(ui->video_photo_lbl_11, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_11_font = _font("preview");
	if(video_photo_lbl_11_font == NULL) video_photo_lbl_11_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_11, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_11, video_photo_lbl_11_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_11, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_11, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_11, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_view_pdat
	ui->video_photo_view_pdat = lv_obj_create(ui->video_photo_view_menu);

	//Set style for video_photo_view_pdat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_pdat, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_view_pdat. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_view_pdat, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_view_pdat, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_view_pdat, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_view_pdat, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_view_pdat, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_view_pdat, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_view_pdat, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_view_pdat, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_view_pdat, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_view_pdat, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_pdat, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_view_pdat, 0, 495);
	lv_obj_set_size(ui->video_photo_view_pdat, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_pdat, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_pdat, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_photo_view_pdat, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_photo_view_pdat);
	//Write codes video_photo_img_12
	ui->video_photo_img_12 = lv_img_create(ui->video_photo_view_pdat);
	lv_img_set_src(ui->video_photo_img_12, gui_get_res_path(GUI_RES_M_DAT_PNG));
	lv_img_set_pivot(ui->video_photo_img_12, 0, 0);
	lv_img_set_angle(ui->video_photo_img_12, 0);
	lv_img_set_zoom(ui->video_photo_img_12, 256);

	//Set style for video_photo_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_12, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_12, 8, 6);
	lv_obj_set_size(ui->video_photo_img_12, 29, 29);
	lv_obj_add_flag(ui->video_photo_img_12, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_lbl_12
	ui->video_photo_lbl_12 = lv_label_create(ui->video_photo_view_pdat);
	lv_label_set_text(ui->video_photo_lbl_12, _("date_label"));
	lv_label_set_long_mode(ui->video_photo_lbl_12, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_photo_lbl_12_font = _font("date_label");
	if(video_photo_lbl_12_font == NULL) video_photo_lbl_12_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_photo_lbl_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_lbl_12, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_lbl_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_lbl_12, video_photo_lbl_12_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_lbl_12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_lbl_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_lbl_12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_lbl_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_lbl_12, 50, 6);
	lv_obj_set_size(ui->video_photo_lbl_12, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_photo_lbl_12, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_photo_img_14
	ui->video_photo_img_14 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_14, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->video_photo_img_14, 0, 0);
	lv_img_set_angle(ui->video_photo_img_14, 0);
	lv_img_set_zoom(ui->video_photo_img_14, 256);

	//Set style for video_photo_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_14, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_14, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_14, 0, 0);
	lv_obj_set_size(ui->video_photo_img_14, 800, 40);
	lv_obj_add_flag(ui->video_photo_img_14, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_15
	ui->video_photo_img_15 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_15, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->video_photo_img_15, 0, 0);
	lv_img_set_angle(ui->video_photo_img_15, 0);
	lv_img_set_zoom(ui->video_photo_img_15, 256);

	//Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_15, 0, 440);
	lv_obj_set_size(ui->video_photo_img_15, 800, 40);
	lv_obj_add_flag(ui->video_photo_img_15, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_16
	ui->video_photo_img_16 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_16, gui_get_res_path(GUI_RES_PHOTO_PNG));
	lv_img_set_pivot(ui->video_photo_img_16, 0, 0);
	lv_img_set_angle(ui->video_photo_img_16, 0);
	lv_img_set_zoom(ui->video_photo_img_16, 256);

	//Set style for video_photo_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_16, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_photo_img_16, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_photo_img_16, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_photo_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_photo_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_16, 9, 5);
	lv_obj_set_size(ui->video_photo_img_16, 40, 30);
	lv_obj_add_flag(ui->video_photo_img_16, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_17
	ui->video_photo_img_17 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_17, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui->video_photo_img_17, 0, 0);
	lv_img_set_angle(ui->video_photo_img_17, 0);
	lv_img_set_zoom(ui->video_photo_img_17, 256);

	//Set style for video_photo_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_17, 70, 1);
	lv_obj_set_size(ui->video_photo_img_17, 37, 37);
	lv_obj_add_flag(ui->video_photo_img_17, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_18
	ui->video_photo_img_18 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_18, gui_get_res_path(GUI_RES_LEFT_PNG));
	lv_img_set_pivot(ui->video_photo_img_18, 0, 0);
	lv_img_set_angle(ui->video_photo_img_18, 0);
	lv_img_set_zoom(ui->video_photo_img_18, 256);

	//Set style for video_photo_img_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_18, 200, 445);
	lv_obj_set_size(ui->video_photo_img_18, 21, 29);
	lv_obj_add_flag(ui->video_photo_img_18, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_19
	ui->video_photo_img_19 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_19, gui_get_res_path(GUI_RES_UP_PNG));
	lv_img_set_pivot(ui->video_photo_img_19, 0, 0);
	lv_img_set_angle(ui->video_photo_img_19, 0);
	lv_img_set_zoom(ui->video_photo_img_19, 256);

	//Set style for video_photo_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_19, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_19, 321, 448);
	lv_obj_set_size(ui->video_photo_img_19, 29, 21);
	lv_obj_add_flag(ui->video_photo_img_19, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_20
	ui->video_photo_img_20 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_20, gui_get_res_path(GUI_RES_DOWN_PNG));
	lv_img_set_pivot(ui->video_photo_img_20, 0, 0);
	lv_img_set_angle(ui->video_photo_img_20, 0);
	lv_img_set_zoom(ui->video_photo_img_20, 256);

	//Set style for video_photo_img_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_20, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_20, 450, 448);
	lv_obj_set_size(ui->video_photo_img_20, 29, 21);
	lv_obj_add_flag(ui->video_photo_img_20, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_img_21
	ui->video_photo_img_21 = lv_img_create(ui->video_photo_view_menu_b);
	lv_img_set_src(ui->video_photo_img_21, gui_get_res_path(GUI_RES_RIGHT_PNG));
	lv_img_set_pivot(ui->video_photo_img_21, 0, 0);
	lv_img_set_angle(ui->video_photo_img_21, 0);
	lv_img_set_zoom(ui->video_photo_img_21, 256);

	//Set style for video_photo_img_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_photo_img_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_photo_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_photo_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_photo_img_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_img_21, 579, 445);
	lv_obj_set_size(ui->video_photo_img_21, 21, 29);
	lv_obj_add_flag(ui->video_photo_img_21, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_photo_view_submenu
	ui->video_photo_view_submenu = lv_obj_create(ui->video_photo);

	//Set style for video_photo_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_view_submenu, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_photo_view_submenu, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_view_submenu, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_photo_view_submenu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_photo_view_submenu, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_view_submenu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_view_submenu, 111, 83);
	lv_obj_set_size(ui->video_photo_view_submenu, 590, 314);
	lv_obj_set_scrollbar_mode(ui->video_photo_view_submenu, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_photo_submenu_btn_1
	ui->video_photo_submenu_btn_1 = lv_btn_create(ui->video_photo_view_submenu);

	//Set style for video_photo_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_1, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_1, 203, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_1, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_submenu_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_1, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_1, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_1, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_1, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_submenu_btn_1, 83, 44);
	lv_obj_set_size(ui->video_photo_submenu_btn_1, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_photo_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_photo_submenu_btn_1_label = lv_label_create(ui->video_photo_submenu_btn_1);
	lv_label_set_text(ui->video_photo_submenu_btn_1_label, "button1");
	lv_obj_set_style_pad_all(ui->video_photo_submenu_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_photo_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_photo_submenu_btn_2
	ui->video_photo_submenu_btn_2 = lv_btn_create(ui->video_photo_view_submenu);

	//Set style for video_photo_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_2, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_2, 215, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_2, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_submenu_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_2, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_2, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_2, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_submenu_btn_2, 83, 111);
	lv_obj_set_size(ui->video_photo_submenu_btn_2, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_photo_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_photo_submenu_btn_2_label = lv_label_create(ui->video_photo_submenu_btn_2);
	lv_label_set_text(ui->video_photo_submenu_btn_2_label, "button2");
	lv_obj_set_style_pad_all(ui->video_photo_submenu_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_photo_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_photo_submenu_btn_3
	ui->video_photo_submenu_btn_3 = lv_btn_create(ui->video_photo_view_submenu);

	//Set style for video_photo_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_3, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_3, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_3, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_3, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_submenu_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_3, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_3, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_3, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_submenu_btn_3, 83, 171);
	lv_obj_set_size(ui->video_photo_submenu_btn_3, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_photo_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_photo_submenu_btn_3_label = lv_label_create(ui->video_photo_submenu_btn_3);
	lv_label_set_text(ui->video_photo_submenu_btn_3_label, "button3");
	lv_obj_set_style_pad_all(ui->video_photo_submenu_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_photo_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_photo_submenu_btn_4
	ui->video_photo_submenu_btn_4 = lv_btn_create(ui->video_photo_view_submenu);

	//Set style for video_photo_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_4, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_4, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_4, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_4, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_submenu_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_submenu_btn_4, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_submenu_btn_4, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_submenu_btn_4, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_submenu_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_submenu_btn_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_submenu_btn_4, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_submenu_btn_4, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_photo_submenu_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_photo_submenu_btn_4, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_photo_submenu_btn_4, 83, 233);
	lv_obj_set_size(ui->video_photo_submenu_btn_4, 438, 37);
	lv_obj_set_scrollbar_mode(ui->video_photo_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE);
	ui->video_photo_submenu_btn_4_label = lv_label_create(ui->video_photo_submenu_btn_4);
	lv_label_set_text(ui->video_photo_submenu_btn_4_label, "button4");
	lv_obj_set_style_pad_all(ui->video_photo_submenu_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_photo_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_photo_roller_mutifunc
	ui->video_photo_roller_mutifunc = lv_roller_create(ui->video_photo_view_submenu);

	//Set style for video_photo_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_photo_roller_mutifunc, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_photo_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_photo_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_photo_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_photo_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_photo_roller_mutifunc, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_photo_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_photo_roller_mutifunc, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_photo_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_photo_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_photo_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_photo_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_photo_roller_mutifunc, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->video_photo_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_letter_space(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_line_space(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_align(ui->video_photo_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	//Set style for video_photo_roller_mutifunc. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_photo_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_photo_roller_mutifunc, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_22, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_photo_roller_mutifunc, 0, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_photo_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_photo_roller_mutifunc, 223, 55);
	lv_obj_set_size(ui->video_photo_roller_mutifunc, 148, 174);
	lv_obj_set_scrollbar_mode(ui->video_photo_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_photo_roller_mutifunc, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_roller_set_options(ui->video_photo_roller_mutifunc,"1\n2\n3\n4\n5",LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->video_photo_roller_mutifunc,5);
	lv_obj_update_layout(ui->video_photo);
	ui->video_photo_del = false;

	//Init events for screen
	events_init_video_photo(ui);
	return ui->video_photo;
}
void unload_scr_video_photo(lv_ui *ui)
{
	ui->video_photo_del = true;
}

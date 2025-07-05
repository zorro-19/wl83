/*Generate Code, Do NOT Edit!*/
#include "./gui_group.h"

void add_children_to_group(lv_obj_t *obj, lv_group_t *group);
void set_default_group_cb();

void gui_group_init()
{
	if (guider_ui.default_group == NULL) {
		guider_ui.default_group = lv_group_get_default();
	}
}

void gui_group_set_default(lv_group_t *group)
{
	if (group == NULL) return;

	if (guider_ui.default_group == group) return set_default_group_cb();
}

void gui_group_add_obj(lv_group_t *group, lv_obj_t *obj, bool is_add)
{
	if (group == NULL || obj == NULL) return;

	bool is_group_def = lv_obj_is_group_def(obj);
	if (is_group_def && is_add) lv_group_add_obj(group, obj);

	if (lv_obj_check_type(obj, &lv_list_class) ||
		lv_obj_check_type(obj, &lv_calendar_class) ||
		lv_obj_check_type(obj, &lv_msgbox_class) ||
		lv_obj_check_type(obj, &lv_tabview_class) ||
		lv_obj_check_type(obj, &lv_calendar_header_arrow_class) ||
		lv_obj_check_type(obj, &lv_calendar_header_dropdown_class)) {
		add_children_to_group(obj, group);
	} else if (lv_obj_check_type(obj, &lv_win_class)) {
		lv_obj_t *header = lv_win_get_header(obj);
		add_children_to_group(header, group);
	}

	if (!is_group_def && is_add) lv_group_add_obj(group, obj);
}

void add_children_to_group(lv_obj_t *obj, lv_group_t *group)
{
	if (obj == NULL || group == NULL) return;

	int childCnt = lv_obj_get_child_cnt(obj);
	for (int i = 0; i < childCnt; i++) {
		lv_obj_t *child = lv_obj_get_child(obj, i);
		if (lv_obj_is_group_def(child)) {
			lv_group_add_obj(group, child);
		}
	}
}

void set_default_group_cb()
{
	if (guider_ui.default_group == NULL) return;

	lv_group_remove_all_objs(guider_ui.default_group);
	lv_obj_t *act_scr = lv_scr_act();

	if (act_scr == guider_ui.usb_slave) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.usb_slave_btn_usb_msd, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.usb_slave_btn_pc_cam, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.usb_slave_btn_video_rec, true);
	} else if (act_scr == guider_ui.video_rec) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_scan, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_reso, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_two_rec, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_cyc_rec, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_gap, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_hdr, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_exp, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_motd, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_mic, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_date, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_gra, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_par, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_num, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_view_hlw, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_rec_submenu_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_rec_submenu_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_rec_submenu_btn_3, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_rec_submenu_btn_4, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_roller_mutifunc, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_2, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_3, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_4, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_5, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_6, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_ddlist_7, true);
	} else if (act_scr == guider_ui.sys_setting) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_pro, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_autof, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_hz, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_kvo, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_lag, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_time, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_tv, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_format, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_reset, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_view_ver, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_submenu_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_submenu_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_submenu_btn_3, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_submenu_btn_4, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_roller_mutifunc, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_lbl_submenu_warning, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_year, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_month, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_day, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_hour, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_min, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_sec, true);
	} else if (act_scr == guider_ui.video_photo) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_scan, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_phm, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_reso, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_cyt, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_qua, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_acu, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_wbl, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_col, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_iso, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_pexp, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_sok, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_sca, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_view_pdat, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_submenu_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_submenu_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_submenu_btn_3, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_submenu_btn_4, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_roller_mutifunc, true);
	} else if (act_scr == guider_ui.video_play) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_pause, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_img_prev_file, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_img_next_file, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_loud, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_ddlist_multi_spped, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_1, true);
	} else if (act_scr == guider_ui.video_file) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_view_del, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_view_pro, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_submenu_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_submenu_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_submenu_btn_3, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_submenu_btn_4, true);
	} else if (act_scr == guider_ui.line_drift) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.line_drift_btn_horizon, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.line_drift_btn_carhead, true);
	} else if (act_scr == guider_ui.sys_popwin) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_popwin_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.sys_popwin_btn_2, true);
	} else if (act_scr == guider_ui.video_dec) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_dec_view_scan, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_dec_view_2, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_dec_view_3, true);
	} else if (act_scr == guider_ui.video_dec_options) {
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_dec_options_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, guider_ui.video_dec_options_btn_2, true);
	}
	lv_group_set_default(guider_ui.default_group);

	lv_indev_t *indev = NULL;
	while ((indev = lv_indev_get_next(indev)) != NULL) {
		lv_indev_set_group(indev, guider_ui.default_group);
	}
}

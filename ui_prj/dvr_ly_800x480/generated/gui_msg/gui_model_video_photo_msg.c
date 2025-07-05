/*Generate Code, Do NOT Edit!*/
#include "./gui_model_video_photo_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

void gui_model_video_photo_msg_video_photo_img_exp_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_awb_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_iso_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_qua_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_delay_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_shake_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char resolution_icon_init_var[] = "1M";
	static bool resolution_icon_is_init = false;
	static char * resolution_icon_var = NULL;
	if (resolution_icon_is_init == false) {
		resolution_icon_var = lv_mem_alloc(strlen(resolution_icon_init_var) + 1);
		strcpy(resolution_icon_var, resolution_icon_init_var);
		resolution_icon_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(resolution_icon_var);
		resolution_icon_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(resolution_icon_var, data->value_string);
	}
	data->value_string = resolution_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t awb_icon_var = RES_AWB_AUTO;
	if (access == GUI_MSG_ACCESS_SET) {
		awb_icon_var = data->value_int;
	}
	data->value_int = awb_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t quality_icon_var = RES_Q3;
	if (access == GUI_MSG_ACCESS_SET) {
		quality_icon_var = data->value_int;
	}
	data->value_int = quality_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_shot_mode_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t shot_mode_icon_var = RES_TIMING_PHOTO_2;
	if (access == GUI_MSG_ACCESS_SET) {
		shot_mode_icon_var = data->value_int;
	}
	data->value_int = shot_mode_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_handshake_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		show_handshake_var = data->value_int;
	}
	data->value_int = show_handshake_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_handshake_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_handshake_var = data->value_int;
	}
	data->value_int = hide_handshake_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_shots_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		show_shots_var = data->value_int;
	}
	data->value_int = show_shots_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_shots_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_shots_var = data->value_int;
	}
	data->value_int = hide_shots_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_shots_mode_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		show_shots_mode_var = data->value_int;
	}
	data->value_int = show_shots_mode_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_shots_mode_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_shots_mode_var = data->value_int;
	}
	data->value_int = hide_shots_mode_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char photo_remain_init_var[] = "99999999";
	static bool photo_remain_is_init = false;
	static char * photo_remain_var = NULL;
	if (photo_remain_is_init == false) {
		photo_remain_var = lv_mem_alloc(strlen(photo_remain_init_var) + 1);
		strcpy(photo_remain_var, photo_remain_init_var);
		photo_remain_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(photo_remain_var);
		photo_remain_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(photo_remain_var, data->value_string);
	}
	data->value_string = photo_remain_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_pexp_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t pexp_icon_var = RES_EXP_A0;
	if (access == GUI_MSG_ACCESS_SET) {
		pexp_icon_var = data->value_int;
	}
	data->value_int = pexp_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_iso_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t iso_icon_var = RES_ISO_AUTO;
	if (access == GUI_MSG_ACCESS_SET) {
		iso_icon_var = data->value_int;
	}
	data->value_int = iso_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_delay_sate_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool delay_sate_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		delay_sate_var = data->value_int;
	}
	data->value_int = delay_sate_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_delay_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t delay_icon_var = RES_DL2;
	if (access == GUI_MSG_ACCESS_SET) {
		delay_icon_var = data->value_int;
	}
	data->value_int = delay_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_handshake_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t handshake_icon_var = RES_SHAKE_OFF;
	if (access == GUI_MSG_ACCESS_SET) {
		handshake_icon_var = data->value_int;
	}
	data->value_int = handshake_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_shots_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool shots_icon_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		shots_icon_var = data->value_int;
	}
	data->value_int = shots_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_photo_reso_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char photo_reso_init_var[] = "VGA";
	static bool photo_reso_is_init = false;
	static char * photo_reso_var = NULL;
	if (photo_reso_is_init == false) {
		photo_reso_var = lv_mem_alloc(strlen(photo_reso_init_var) + 1);
		strcpy(photo_reso_var, photo_reso_init_var);
		photo_reso_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(photo_reso_var);
		photo_reso_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(photo_reso_var, data->value_string);
	}
	data->value_string = photo_reso_var;
	return 0;
}

void gui_model_video_photo_msg_init(lv_ui *ui)
{
	gui_msg_sub_t * sub;
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	gui_model_video_photo_msg_init_ui();
	gui_model_video_photo_msg_init_events();
}

void gui_model_video_photo_msg_init_ui()
{
}

void gui_model_video_photo_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[18] = {
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, 0, 0},
	};

	for (int i = 0; i < 18; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}

	lv_subject_t * subject_resolution_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON);
	lv_subject_t * subject_awb_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON);
	lv_subject_t * subject_quality_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON);
	lv_subject_t * subject_shot_mode_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON);
	lv_subject_t * subject_show_handshake = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE);
	lv_subject_t * subject_hide_handshake = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE);
	lv_subject_t * subject_show_shots = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS);
	lv_subject_t * subject_hide_shots = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS);
	lv_subject_t * subject_show_shots_mode = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE);
	lv_subject_t * subject_hide_shots_mode = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE);
	lv_subject_t * subject_photo_remain = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN);
	lv_subject_t * subject_pexp_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON);
	lv_subject_t * subject_iso_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON);
	lv_subject_t * subject_delay_sate = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE);
	lv_subject_t * subject_delay_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON);
	lv_subject_t * subject_handshake_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON);
	lv_subject_t * subject_shots_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON);
	lv_subject_t * subject_photo_reso = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO);
	if (!guider_ui.video_photo_del) {
		gui_model_video_photo_msg_shots_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_shots_icon, gui_msg_set_visible_by_bool_cb, guider_ui.video_photo_img_repeat_icon, &guider_msg_data);

		gui_model_video_photo_msg_iso_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_iso_icon, gui_model_video_photo_msg_video_photo_img_iso_icon_set_img_path_cb, guider_ui.video_photo_img_iso_icon, &guider_msg_data);

		gui_model_video_photo_msg_handshake_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_handshake_icon, gui_model_video_photo_msg_video_photo_img_shake_icon_set_img_path_cb, guider_ui.video_photo_img_shake_icon, &guider_msg_data);

		gui_model_video_photo_msg_pexp_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_pexp_icon, gui_model_video_photo_msg_video_photo_img_exp_icon_set_img_path_cb, guider_ui.video_photo_img_exp_icon, &guider_msg_data);

		gui_model_video_photo_msg_awb_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_awb_icon, gui_model_video_photo_msg_video_photo_img_awb_icon_set_img_path_cb, guider_ui.video_photo_img_awb_icon, &guider_msg_data);

		gui_model_video_photo_msg_quality_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_quality_icon, gui_model_video_photo_msg_video_photo_img_qua_icon_set_img_path_cb, guider_ui.video_photo_img_qua_icon, &guider_msg_data);

		gui_model_video_photo_msg_delay_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_delay_icon, gui_model_video_photo_msg_video_photo_img_delay_icon_set_img_path_cb, guider_ui.video_photo_img_delay_icon, &guider_msg_data);
		gui_model_video_photo_msg_delay_sate_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_delay_sate, gui_msg_set_visible_by_bool_cb, guider_ui.video_photo_img_delay_icon, &guider_msg_data);

		gui_model_video_photo_msg_photo_reso_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_photo_reso, gui_msg_set_label_text_by_string_cb, guider_ui.video_photo_lbl_photo_reso, &guider_msg_data);

		gui_model_video_photo_msg_photo_remain_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_photo_remain, gui_msg_set_label_text_by_string_cb, guider_ui.video_photo_lbl_remain_pnum, &guider_msg_data);


		for (int i = 0; i < 18; i++) {
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON) {
				status[i].is_subscribe = 1;
			}
		}
	}

	for (int i = 0; i < 18; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
}

void gui_model_video_photo_msg_unsubscribe()
{
	_gui_msg_status_t status[18] = {
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, 0, 0},
	};
	for (int i = 0; i < 18; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		lv_observer_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
		while (head != NULL) {
			lv_obj_t * obj = head->target;
			if (obj != NULL && lv_obj_is_valid(obj) == true) {
				lv_subject_remove_all_obj(subject, obj);
			}
			head = _lv_ll_get_head(&subject_ll);
		}
	}

	for (int i = 0; i < 18; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_data_t * gui_model_video_photo_msg_get(int32_t msg_id)
{
	switch (msg_id) {
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON: {
			gui_model_video_photo_msg_resolution_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON: {
			gui_model_video_photo_msg_awb_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON: {
			gui_model_video_photo_msg_quality_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON: {
			gui_model_video_photo_msg_shot_mode_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE: {
			gui_model_video_photo_msg_show_handshake_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE: {
			gui_model_video_photo_msg_hide_handshake_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS: {
			gui_model_video_photo_msg_show_shots_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS: {
			gui_model_video_photo_msg_hide_shots_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE: {
			gui_model_video_photo_msg_show_shots_mode_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE: {
			gui_model_video_photo_msg_hide_shots_mode_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN: {
			gui_model_video_photo_msg_photo_remain_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON: {
			gui_model_video_photo_msg_pexp_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON: {
			gui_model_video_photo_msg_iso_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE: {
			gui_model_video_photo_msg_delay_sate_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON: {
			gui_model_video_photo_msg_delay_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON: {
			gui_model_video_photo_msg_handshake_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON: {
			gui_model_video_photo_msg_shots_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO: {
			gui_model_video_photo_msg_photo_reso_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		default:
			return NULL;
	}
	return &guider_msg_data;
}

void gui_model_video_photo_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	switch (msg_id) {
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON: {
			gui_model_video_photo_msg_resolution_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON: {
			gui_model_video_photo_msg_awb_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON: {
			gui_model_video_photo_msg_quality_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON: {
			gui_model_video_photo_msg_shot_mode_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE: {
			gui_model_video_photo_msg_show_handshake_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE: {
			gui_model_video_photo_msg_hide_handshake_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS: {
			gui_model_video_photo_msg_show_shots_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS: {
			gui_model_video_photo_msg_hide_shots_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE: {
			gui_model_video_photo_msg_show_shots_mode_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE: {
			gui_model_video_photo_msg_hide_shots_mode_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN: {
			gui_model_video_photo_msg_photo_remain_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON: {
			gui_model_video_photo_msg_pexp_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON: {
			gui_model_video_photo_msg_iso_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE: {
			gui_model_video_photo_msg_delay_sate_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON: {
			gui_model_video_photo_msg_delay_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON: {
			gui_model_video_photo_msg_handshake_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON: {
			gui_model_video_photo_msg_shots_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO: {
			gui_model_video_photo_msg_photo_reso_cb(access, data, type);
			break;
		}
		default: {
				break;
		}
	}
}

gui_msg_status_t gui_model_video_photo_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			default: 
				break;
		}
		gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
		lv_subject_t * subject = gui_msg_get_subject(msg_id);
		if (subject == NULL) return GUI_MSG_STATUS_NO_SUBSCRIBE;
		lv_subject_set_pointer(subject, &guider_msg_data);
	}
	return GUI_MSG_STATUS_SUCCESS;
}

#endif

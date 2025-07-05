#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_video_rec_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

void gui_model_video_rec_msg_video_rec_img_cyc_state_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_exp_state_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_mic_state_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_gra_state_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_sd_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_digitclock_2_set_digit_clock_time_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	struct tm time = data->value_time;
	lv_label_set_text_fmt(obj, "%02d:%02d:%02d", time.tm_hour, time.tm_min, time.tm_sec);
}
void gui_model_video_rec_msg_video_photo_img_sd_icon_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_video_rec_msg_cycrec_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t cycrec_icon_var = RES_CYCLIC_VIDEO_3;
	if (access == GUI_MSG_ACCESS_SET) {
		cycrec_icon_var = data->value_int;
	}
	data->value_int = cycrec_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_delayrec_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t delayrec_icon_var = RES_INTERVAL_VIDEO_CLOSE;
	if (access == GUI_MSG_ACCESS_SET) {
		delayrec_icon_var = data->value_int;
	}
	data->value_int = delayrec_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_car_nunber_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char car_nunber_init_var[] = "京A11111";
	static bool car_nunber_is_init = false;
	static char * car_nunber_var = NULL;
	if (car_nunber_is_init == false) {
		car_nunber_var = lv_mem_alloc(strlen(car_nunber_init_var) + 1);
		strcpy(car_nunber_var, car_nunber_init_var);
		car_nunber_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(car_nunber_var);
		car_nunber_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(car_nunber_var, data->value_string);
	}
	data->value_string = car_nunber_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_reso_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char rec_reso_init_var[] = "720P";
	static bool rec_reso_is_init = false;
	static char * rec_reso_var = NULL;
	if (rec_reso_is_init == false) {
		rec_reso_var = lv_mem_alloc(strlen(rec_reso_init_var) + 1);
		strcpy(rec_reso_var, rec_reso_init_var);
		rec_reso_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(rec_reso_var);
		rec_reso_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(rec_reso_var, data->value_string);
	}
	data->value_string = rec_reso_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_btn_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_state_t rec_btn_var = LV_STATE_DEFAULT;
	if (access == GUI_MSG_ACCESS_SET) {
		rec_btn_var = data->value_int;
	}
	data->value_int = rec_btn_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_gsensor_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_gsensor_icon_var = data->value_int;
	}
	data->value_int = show_gsensor_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_gsensor_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_gsensor_icon_var = data->value_int;
	}
	data->value_int = hide_gsensor_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_guard_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_guard_icon_var = data->value_int;
	}
	data->value_int = show_guard_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_guard_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_guard_icon_var = data->value_int;
	}
	data->value_int = hide_guard_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_motion_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_motion_icon_var = data->value_int;
	}
	data->value_int = show_motion_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_motion_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_motion_icon_var = data->value_int;
	}
	data->value_int = hide_motion_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_hdr_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_hdr_icon_var = data->value_int;
	}
	data->value_int = show_hdr_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_hdr_icon_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_hdr_icon_var = data->value_int;
	}
	data->value_int = hide_hdr_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_remain_time_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static struct tm rec_remain_time_var = {
		.tm_year = 124,
		.tm_mon = 6,
		.tm_mday = 2,
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 0,
	};
	if (access == GUI_MSG_ACCESS_SET) {
		rec_remain_time_var = data->value_time;
	}
	data->value_time = rec_remain_time_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_time_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_state_t rec_time_state_var = LV_STATE_DEFAULT;
	if (access == GUI_MSG_ACCESS_SET) {
		rec_time_state_var = data->value_int;
	}
	data->value_int = rec_time_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_video_rec_menu_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool video_rec_menu_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		video_rec_menu_var = data->value_int;
	}
	data->value_int = video_rec_menu_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_mic_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t mic_icon_var = RES_MIC_ON;
	if (access == GUI_MSG_ACCESS_SET) {
		mic_icon_var = data->value_int;
	}
	data->value_int = mic_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t gsensor_icon_var = RES_I_GRA_L;
	if (access == GUI_MSG_ACCESS_SET) {
		gsensor_icon_var = data->value_int;
	}
	data->value_int = gsensor_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t sd_icon_var = RES_CARD_OFFLINE;
	if (access == GUI_MSG_ACCESS_SET) {
		sd_icon_var = data->value_int;
	}
	data->value_int = sd_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_guard_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool guard_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		guard_state_var = data->value_int;
	}
	data->value_int = guard_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_cyc_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool cyc_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		cyc_state_var = data->value_int;
	}
	data->value_int = cyc_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_motion_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool motion_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		motion_state_var = data->value_int;
	}
	data->value_int = motion_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_gap_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool gap_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		gap_state_var = data->value_int;
	}
	data->value_int = gap_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hdr_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool hdr_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		hdr_state_var = data->value_int;
	}
	data->value_int = hdr_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_gra_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool gra_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		gra_state_var = data->value_int;
	}
	data->value_int = gra_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_exp_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t exp_icon_var = RES_EXP_A0;
	if (access == GUI_MSG_ACCESS_SET) {
		exp_icon_var = data->value_int;
	}
	data->value_int = exp_icon_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_car_num_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool car_num_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		car_num_var = data->value_int;
	}
	data->value_int = car_num_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_flash_headlight_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool flash_headlight_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		flash_headlight_var = data->value_int;
	}
	data->value_int = flash_headlight_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_icon_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool rec_icon_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		rec_icon_state_var = data->value_int;
	}
	data->value_int = rec_icon_state_var;
	return 0;
}
GUI_WEAK int gui_model_video_rec_msg_key_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool key_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		key_state_var = data->value_int;
	}
	data->value_int = key_state_var;
	return 0;
}

void gui_model_video_rec_msg_init(lv_ui *ui)
{
	gui_msg_sub_t * sub;
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	gui_model_video_rec_msg_init_ui();
	gui_model_video_rec_msg_init_events();
}

void gui_model_video_rec_msg_init_ui()
{
}

void gui_model_video_rec_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[30] = {
		{GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, 0, 0},
	};

	for (int i = 0; i < 30; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}

	lv_subject_t * subject_cycrec_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON);
	lv_subject_t * subject_delayrec_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON);
	lv_subject_t * subject_car_nunber = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER);
	lv_subject_t * subject_rec_reso = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO);
	lv_subject_t * subject_rec_btn = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN);
	lv_subject_t * subject_show_gsensor_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON);
	lv_subject_t * subject_hide_gsensor_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON);
	lv_subject_t * subject_show_guard_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON);
	lv_subject_t * subject_hide_guard_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON);
	lv_subject_t * subject_show_motion_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON);
	lv_subject_t * subject_hide_motion_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON);
	lv_subject_t * subject_show_hdr_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON);
	lv_subject_t * subject_hide_hdr_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON);
	lv_subject_t * subject_rec_remain_time = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME);
	lv_subject_t * subject_rec_time_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE);
	lv_subject_t * subject_video_rec_menu = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU);
	lv_subject_t * subject_mic_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON);
	lv_subject_t * subject_gsensor_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON);
	lv_subject_t * subject_sd_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON);
	lv_subject_t * subject_guard_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE);
	lv_subject_t * subject_cyc_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE);
	lv_subject_t * subject_motion_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE);
	lv_subject_t * subject_gap_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE);
	lv_subject_t * subject_hdr_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE);
	lv_subject_t * subject_gra_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE);
	lv_subject_t * subject_exp_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON);
	lv_subject_t * subject_car_num = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM);
	lv_subject_t * subject_flash_headlight = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT);
	lv_subject_t * subject_rec_icon_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE);
	lv_subject_t * subject_key_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE);
	if (!guider_ui.video_rec_del) {
		gui_model_video_rec_msg_exp_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_exp_icon, gui_model_video_rec_msg_video_rec_img_exp_state_set_img_path_cb, guider_ui.video_rec_img_exp_state, &guider_msg_data);

		gui_model_video_rec_msg_rec_icon_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_rec_icon_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_rec_state, &guider_msg_data);

		gui_model_video_rec_msg_motion_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_motion_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_mot_state, &guider_msg_data);

		gui_model_video_rec_msg_guard_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_guard_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_par_state, &guider_msg_data);

		gui_model_video_rec_msg_sd_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_sd_icon, gui_model_video_rec_msg_video_rec_img_sd_set_img_path_cb, guider_ui.video_rec_img_sd, &guider_msg_data);

		gui_model_video_rec_msg_mic_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_mic_icon, gui_model_video_rec_msg_video_rec_img_mic_state_set_img_path_cb, guider_ui.video_rec_img_mic_state, &guider_msg_data);

		gui_model_video_rec_msg_car_nunber_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_car_nunber, gui_msg_set_label_text_by_string_cb, guider_ui.video_rec_lbl_num, &guider_msg_data);
		gui_model_video_rec_msg_car_num_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_car_num, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_lbl_num, &guider_msg_data);

		gui_model_video_rec_msg_gap_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_gap_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_gap_state, &guider_msg_data);

		gui_model_video_rec_msg_rec_reso_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_rec_reso, gui_msg_set_label_text_by_string_cb, guider_ui.video_rec_lbl_reso, &guider_msg_data);

		gui_model_video_rec_msg_cycrec_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_cycrec_icon, gui_model_video_rec_msg_video_rec_img_cyc_state_set_img_path_cb, guider_ui.video_rec_img_cyc_state, &guider_msg_data);
		gui_model_video_rec_msg_cyc_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_cyc_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_cyc_state, &guider_msg_data);

		gui_model_video_rec_msg_hdr_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_hdr_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_hdr_state, &guider_msg_data);

		gui_model_video_rec_msg_rec_remain_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
		lv_subject_add_observer_obj(subject_rec_remain_time, gui_model_video_rec_msg_video_rec_digitclock_2_set_digit_clock_time_cb, guider_ui.video_rec_digitclock_2, &guider_msg_data);
		gui_model_video_rec_msg_rec_time_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_rec_time_state, gui_msg_set_control_state_by_int32_cb, guider_ui.video_rec_digitclock_2, &guider_msg_data);

		gui_model_video_rec_msg_gsensor_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_gsensor_icon, gui_model_video_rec_msg_video_rec_img_gra_state_set_img_path_cb, guider_ui.video_rec_img_gra_state, &guider_msg_data);
		gui_model_video_rec_msg_gra_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_gra_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_gra_state, &guider_msg_data);

		gui_model_video_rec_msg_flash_headlight_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_flash_headlight, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_headlight, &guider_msg_data);

		gui_model_video_rec_msg_key_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_key_state, gui_msg_set_visible_by_bool_cb, guider_ui.video_rec_img_key_state, &guider_msg_data);


		for (int i = 0; i < 30; i++) {
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (!guider_ui.video_photo_del) {
		gui_model_video_rec_msg_sd_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_sd_icon, gui_model_video_rec_msg_video_photo_img_sd_icon_set_img_path_cb, guider_ui.video_photo_img_sd_icon, &guider_msg_data);


		for (int i = 0; i < 30; i++) {
			if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON) {
				status[i].is_subscribe = 1;
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
}

void gui_model_video_rec_msg_unsubscribe()
{
	_gui_msg_status_t status[30] = {
		{GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, 0, 0},
		{GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, 0, 0},
	};
	for (int i = 0; i < 30; i++) {
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

	for (int i = 0; i < 30; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_data_t * gui_model_video_rec_msg_get(int32_t msg_id)
{
	switch (msg_id) {
		case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON: {
			gui_model_video_rec_msg_cycrec_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON: {
			gui_model_video_rec_msg_delayrec_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER: {
			gui_model_video_rec_msg_car_nunber_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO: {
			gui_model_video_rec_msg_rec_reso_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN: {
			gui_model_video_rec_msg_rec_btn_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON: {
			gui_model_video_rec_msg_show_gsensor_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON: {
			gui_model_video_rec_msg_hide_gsensor_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON: {
			gui_model_video_rec_msg_show_guard_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON: {
			gui_model_video_rec_msg_hide_guard_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON: {
			gui_model_video_rec_msg_show_motion_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON: {
			gui_model_video_rec_msg_hide_motion_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON: {
			gui_model_video_rec_msg_show_hdr_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON: {
			gui_model_video_rec_msg_hide_hdr_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME: {
			gui_model_video_rec_msg_rec_remain_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE: {
			gui_model_video_rec_msg_rec_time_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU: {
			gui_model_video_rec_msg_video_rec_menu_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON: {
			gui_model_video_rec_msg_mic_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON: {
			gui_model_video_rec_msg_gsensor_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON: {
			gui_model_video_rec_msg_sd_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE: {
			gui_model_video_rec_msg_guard_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE: {
			gui_model_video_rec_msg_cyc_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE: {
			gui_model_video_rec_msg_motion_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE: {
			gui_model_video_rec_msg_gap_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE: {
			gui_model_video_rec_msg_hdr_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE: {
			gui_model_video_rec_msg_gra_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON: {
			gui_model_video_rec_msg_exp_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM: {
			gui_model_video_rec_msg_car_num_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT: {
			gui_model_video_rec_msg_flash_headlight_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE: {
			gui_model_video_rec_msg_rec_icon_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE: {
			gui_model_video_rec_msg_key_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		default:
			return NULL;
	}
	return &guider_msg_data;
}

void gui_model_video_rec_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	switch (msg_id) {
		case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON: {
			gui_model_video_rec_msg_cycrec_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON: {
			gui_model_video_rec_msg_delayrec_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER: {
			gui_model_video_rec_msg_car_nunber_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO: {
			gui_model_video_rec_msg_rec_reso_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN: {
			gui_model_video_rec_msg_rec_btn_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON: {
			gui_model_video_rec_msg_show_gsensor_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON: {
			gui_model_video_rec_msg_hide_gsensor_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON: {
			gui_model_video_rec_msg_show_guard_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON: {
			gui_model_video_rec_msg_hide_guard_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON: {
			gui_model_video_rec_msg_show_motion_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON: {
			gui_model_video_rec_msg_hide_motion_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON: {
			gui_model_video_rec_msg_show_hdr_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON: {
			gui_model_video_rec_msg_hide_hdr_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME: {
			gui_model_video_rec_msg_rec_remain_time_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE: {
			gui_model_video_rec_msg_rec_time_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU: {
			gui_model_video_rec_msg_video_rec_menu_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON: {
			gui_model_video_rec_msg_mic_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON: {
			gui_model_video_rec_msg_gsensor_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON: {
			gui_model_video_rec_msg_sd_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE: {
			gui_model_video_rec_msg_guard_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE: {
			gui_model_video_rec_msg_cyc_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE: {
			gui_model_video_rec_msg_motion_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE: {
			gui_model_video_rec_msg_gap_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE: {
			gui_model_video_rec_msg_hdr_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE: {
			gui_model_video_rec_msg_gra_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON: {
			gui_model_video_rec_msg_exp_icon_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM: {
			gui_model_video_rec_msg_car_num_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT: {
			gui_model_video_rec_msg_flash_headlight_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE: {
			gui_model_video_rec_msg_rec_icon_state_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE: {
			gui_model_video_rec_msg_key_state_cb(access, data, type);
			break;
		}
		default: {
				break;
		}
	}
}

gui_msg_status_t gui_model_video_rec_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_MODEL_VIDEO_REC_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME: {
				data_type = VALUE_TIME;
				if (value) guider_msg_data.value_time = *((struct tm *)value);
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE: {
				data_type = VALUE_BOOL;
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

#endif

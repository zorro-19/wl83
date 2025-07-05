#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_video_dec_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_model_video_dec_msg_file_type_img_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t file_type_img_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		file_type_img_var = data->value_int;
	}
	data->value_int = file_type_img_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_video_time_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char video_time_lab_init_var[] = "";
	static bool video_time_lab_is_init = false;
	static char * video_time_lab_var = NULL;
	if (video_time_lab_is_init == false) {
		video_time_lab_var = lv_mem_alloc(strlen(video_time_lab_init_var) + 1);
		strcpy(video_time_lab_var, video_time_lab_init_var);
		video_time_lab_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(video_time_lab_var);
		video_time_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(video_time_lab_var, data->value_string);
	}
	data->value_string = video_time_lab_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_file_name_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char file_name_lab_init_var[] = "";
	static bool file_name_lab_is_init = false;
	static char * file_name_lab_var = NULL;
	if (file_name_lab_is_init == false) {
		file_name_lab_var = lv_mem_alloc(strlen(file_name_lab_init_var) + 1);
		strcpy(file_name_lab_var, file_name_lab_init_var);
		file_name_lab_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(file_name_lab_var);
		file_name_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(file_name_lab_var, data->value_string);
	}
	data->value_string = file_name_lab_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_media_info_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char media_info_lab_init_var[] = "";
	static bool media_info_lab_is_init = false;
	static char * media_info_lab_var = NULL;
	if (media_info_lab_is_init == false) {
		media_info_lab_var = lv_mem_alloc(strlen(media_info_lab_init_var) + 1);
		strcpy(media_info_lab_var, media_info_lab_init_var);
		media_info_lab_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(media_info_lab_var);
		media_info_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(media_info_lab_var, data->value_string);
	}
	data->value_string = media_info_lab_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_sd_status_img_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t sd_status_img_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		sd_status_img_var = data->value_int;
	}
	data->value_int = sd_status_img_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_play_status_img_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t play_status_img_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		play_status_img_var = data->value_int;
	}
	data->value_int = play_status_img_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_video_cont_show_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool video_cont_show_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		video_cont_show_var = data->value_int;
	}
	data->value_int = video_cont_show_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_file_lock_show_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool file_lock_show_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		file_lock_show_var = data->value_int;
	}
	data->value_int = file_lock_show_var;
	return 0;
}
GUI_WEAK int gui_model_video_dec_msg_video_dec_options_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char video_dec_options_lab_init_var[] = "";
	static bool video_dec_options_lab_is_init = false;
	static char * video_dec_options_lab_var = NULL;
	if (video_dec_options_lab_is_init == false) {
		video_dec_options_lab_var = lv_mem_alloc(strlen(video_dec_options_lab_init_var) + 1);
		strcpy(video_dec_options_lab_var, video_dec_options_lab_init_var);
		video_dec_options_lab_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(video_dec_options_lab_var);
		video_dec_options_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(video_dec_options_lab_var, data->value_string);
	}
	data->value_string = video_dec_options_lab_var;
	return 0;
}

void gui_model_video_dec_msg_init(lv_ui *ui)
{
	gui_msg_sub_t * sub;
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	gui_model_video_dec_msg_init_ui();
	gui_model_video_dec_msg_init_events();
}

void gui_model_video_dec_msg_init_ui()
{
}

void gui_model_video_dec_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[9] = {
		{GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB, 0, 0},
	};

	for (int i = 0; i < 9; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}

	lv_subject_t * subject_file_type_img = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG);
	lv_subject_t * subject_video_time_lab = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB);
	lv_subject_t * subject_file_name_lab = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB);
	lv_subject_t * subject_media_info_lab = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB);
	lv_subject_t * subject_sd_status_img = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG);
	lv_subject_t * subject_play_status_img = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG);
	lv_subject_t * subject_video_cont_show = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW);
	lv_subject_t * subject_file_lock_show = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW);
	lv_subject_t * subject_video_dec_options_lab = gui_msg_get_subject(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB);
	if (!guider_ui.video_dec_options_del) {
		gui_model_video_dec_msg_video_dec_options_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_video_dec_options_lab, gui_msg_set_label_text_by_string_cb, guider_ui.video_dec_options_lbl_1, &guider_msg_data);


		for (int i = 0; i < 9; i++) {
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (!guider_ui.video_dec_del) {
		gui_model_video_dec_msg_video_cont_show_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_video_cont_show, gui_msg_set_visible_by_bool_cb, guider_ui.video_dec_view_1, &guider_msg_data);

		gui_model_video_dec_msg_file_type_img_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_file_type_img, gui_msg_set_imglist_selected_index_by_int32_cb, guider_ui.video_dec_imglist_1, &guider_msg_data);

		gui_model_video_dec_msg_file_lock_show_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
		lv_subject_add_observer_obj(subject_file_lock_show, gui_msg_set_visible_by_bool_cb, guider_ui.video_dec_img_1, &guider_msg_data);

		gui_model_video_dec_msg_sd_status_img_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_sd_status_img, gui_msg_set_imglist_selected_index_by_int32_cb, guider_ui.video_dec_imglist_2, &guider_msg_data);

		gui_model_video_dec_msg_video_time_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_video_time_lab, gui_msg_set_textarea_text_by_string_cb, guider_ui.video_dec_edit_1, &guider_msg_data);
		lv_obj_remove_event_cb(guider_ui.video_dec_edit_1, gui_msg_change_textarea_text_cb);
		lv_obj_add_event_cb(guider_ui.video_dec_edit_1, gui_msg_change_textarea_text_cb, LV_EVENT_VALUE_CHANGED, (void *)GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB);

		gui_model_video_dec_msg_file_name_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_file_name_lab, gui_msg_set_textarea_text_by_string_cb, guider_ui.video_dec_edit_2, &guider_msg_data);
		lv_obj_remove_event_cb(guider_ui.video_dec_edit_2, gui_msg_change_textarea_text_cb);
		lv_obj_add_event_cb(guider_ui.video_dec_edit_2, gui_msg_change_textarea_text_cb, LV_EVENT_VALUE_CHANGED, (void *)GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB);

		gui_model_video_dec_msg_media_info_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
		lv_subject_add_observer_obj(subject_media_info_lab, gui_msg_set_textarea_text_by_string_cb, guider_ui.video_dec_edit_3, &guider_msg_data);
		lv_obj_remove_event_cb(guider_ui.video_dec_edit_3, gui_msg_change_textarea_text_cb);
		lv_obj_add_event_cb(guider_ui.video_dec_edit_3, gui_msg_change_textarea_text_cb, LV_EVENT_VALUE_CHANGED, (void *)GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB);

		gui_model_video_dec_msg_play_status_img_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
		lv_subject_add_observer_obj(subject_play_status_img, gui_msg_set_imglist_selected_index_by_int32_cb, guider_ui.video_dec_imglist_3, &guider_msg_data);


		for (int i = 0; i < 9; i++) {
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB) {
				status[i].is_subscribe = 1;
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
}

void gui_model_video_dec_msg_unsubscribe()
{
	_gui_msg_status_t status[9] = {
		{GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW, 0, 0},
		{GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB, 0, 0},
	};
	for (int i = 0; i < 9; i++) {
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

	for (int i = 0; i < 9; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_data_t * gui_model_video_dec_msg_get(int32_t msg_id)
{
	switch (msg_id) {
		case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG: {
			gui_model_video_dec_msg_file_type_img_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB: {
			gui_model_video_dec_msg_video_time_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB: {
			gui_model_video_dec_msg_file_name_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB: {
			gui_model_video_dec_msg_media_info_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG: {
			gui_model_video_dec_msg_sd_status_img_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG: {
			gui_model_video_dec_msg_play_status_img_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW: {
			gui_model_video_dec_msg_video_cont_show_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW: {
			gui_model_video_dec_msg_file_lock_show_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB: {
			gui_model_video_dec_msg_video_dec_options_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		default:
			return NULL;
	}
	return &guider_msg_data;
}

void gui_model_video_dec_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	switch (msg_id) {
		case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG: {
			gui_model_video_dec_msg_file_type_img_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB: {
			gui_model_video_dec_msg_video_time_lab_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB: {
			gui_model_video_dec_msg_file_name_lab_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB: {
			gui_model_video_dec_msg_media_info_lab_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG: {
			gui_model_video_dec_msg_sd_status_img_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG: {
			gui_model_video_dec_msg_play_status_img_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW: {
			gui_model_video_dec_msg_video_cont_show_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW: {
			gui_model_video_dec_msg_file_lock_show_cb(access, data, type);
			break;
		}
		case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB: {
			gui_model_video_dec_msg_video_dec_options_lab_cb(access, data, type);
			break;
		}
		default: {
				break;
		}
	}
}

gui_msg_status_t gui_model_video_dec_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_MODEL_VIDEO_DEC_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW: {
				data_type = VALUE_BOOL;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB: {
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

#endif

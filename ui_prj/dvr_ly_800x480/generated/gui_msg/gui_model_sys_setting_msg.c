/*Generate Code, Do NOT Edit!*/
#include "./gui_model_sys_setting_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_model_sys_setting_msg_funkey4_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char funkey4_init_var[] = "关闭";
	static bool funkey4_is_init = false;
	static char * funkey4_var = NULL;
	if (funkey4_is_init == false) {
		funkey4_var = lv_mem_alloc(strlen(funkey4_init_var) + 1);
		strcpy(funkey4_var, funkey4_init_var);
		funkey4_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(funkey4_var);
		funkey4_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(funkey4_var, data->value_string);
	}
	data->value_string = funkey4_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_funkey5_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char funkey5_init_var[] = "30s";
	static bool funkey5_is_init = false;
	static char * funkey5_var = NULL;
	if (funkey5_is_init == false) {
		funkey5_var = lv_mem_alloc(strlen(funkey5_init_var) + 1);
		strcpy(funkey5_var, funkey5_init_var);
		funkey5_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(funkey5_var);
		funkey5_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(funkey5_var, data->value_string);
	}
	data->value_string = funkey5_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_funkey6_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char funkey6_init_var[] = "60s";
	static bool funkey6_is_init = false;
	static char * funkey6_var = NULL;
	if (funkey6_is_init == false) {
		funkey6_var = lv_mem_alloc(strlen(funkey6_init_var) + 1);
		strcpy(funkey6_var, funkey6_init_var);
		funkey6_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(funkey6_var);
		funkey6_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(funkey6_var, data->value_string);
	}
	data->value_string = funkey6_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_funkey7_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char funkey7_init_var[] = "120s";
	static bool funkey7_is_init = false;
	static char * funkey7_var = NULL;
	if (funkey7_is_init == false) {
		funkey7_var = lv_mem_alloc(strlen(funkey7_init_var) + 1);
		strcpy(funkey7_var, funkey7_init_var);
		funkey7_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(funkey7_var);
		funkey7_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(funkey7_var, data->value_string);
	}
	data->value_string = funkey7_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_subpage_warning_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char subpage_warning_init_var[] = "warning";
	static bool subpage_warning_is_init = false;
	static char * subpage_warning_var = NULL;
	if (subpage_warning_is_init == false) {
		subpage_warning_var = lv_mem_alloc(strlen(subpage_warning_init_var) + 1);
		strcpy(subpage_warning_var, subpage_warning_init_var);
		subpage_warning_is_init = true;
	}
	if (access == GUI_MSG_ACCESS_SET) {
		lv_mem_free(subpage_warning_var);
		subpage_warning_var = lv_mem_alloc(strlen(data->value_string) + 1);
		strcpy(subpage_warning_var, data->value_string);
	}
	data->value_string = subpage_warning_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_viewdate_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_viewdate_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_viewdate_var = data->value_int;
	}
	data->value_int = hide_viewdate_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_viewcarnum_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_viewcarnum_var = data->value_int;
	}
	data->value_int = hide_viewcarnum_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_viewlist_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_viewlist_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_viewlist_var = data->value_int;
	}
	data->value_int = hide_viewlist_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_subpagewarning_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_subpagewarning_var = data->value_int;
	}
	data->value_int = hide_subpagewarning_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_viewdate_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_viewdate_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_viewdate_var = data->value_int;
	}
	data->value_int = show_viewdate_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_viewcarnum_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_viewcarnum_var = data->value_int;
	}
	data->value_int = show_viewcarnum_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_viewlist_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_viewlist_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_viewlist_var = data->value_int;
	}
	data->value_int = show_viewlist_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_subpagewarning_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_subpagewarning_var = data->value_int;
	}
	data->value_int = show_subpagewarning_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey5_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_funkey5_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_funkey5_var = data->value_int;
	}
	data->value_int = hide_funkey5_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey6_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_funkey6_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_funkey6_var = data->value_int;
	}
	data->value_int = hide_funkey6_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey7_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_funkey7_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_funkey7_var = data->value_int;
	}
	data->value_int = hide_funkey7_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey4_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_funkey4_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_funkey4_var = data->value_int;
	}
	data->value_int = show_funkey4_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey5_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_funkey5_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_funkey5_var = data->value_int;
	}
	data->value_int = show_funkey5_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey6_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_funkey6_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_funkey6_var = data->value_int;
	}
	data->value_int = show_funkey6_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey7_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_funkey7_var = 0;
	if (access == GUI_MSG_ACCESS_SET) {
		show_funkey7_var = data->value_int;
	}
	data->value_int = show_funkey7_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey4_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_state_t state_funkey4_var = LV_STATE_DEFAULT;
	if (access == GUI_MSG_ACCESS_SET) {
		state_funkey4_var = data->value_int;
	}
	data->value_int = state_funkey4_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey5_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_state_t state_funkey5_var = LV_STATE_DEFAULT;
	if (access == GUI_MSG_ACCESS_SET) {
		state_funkey5_var = data->value_int;
	}
	data->value_int = state_funkey5_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey6_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_state_t state_funkey6_var = LV_STATE_DEFAULT;
	if (access == GUI_MSG_ACCESS_SET) {
		state_funkey6_var = data->value_int;
	}
	data->value_int = state_funkey6_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey7_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_state_t state_funkey7_var = LV_STATE_DEFAULT;
	if (access == GUI_MSG_ACCESS_SET) {
		state_funkey7_var = data->value_int;
	}
	data->value_int = state_funkey7_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey4_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_funkey4_var = LV_OBJ_FLAG_HIDDEN;
	if (access == GUI_MSG_ACCESS_SET) {
		hide_funkey4_var = data->value_int;
	}
	data->value_int = hide_funkey4_var;
	return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_subpage_warning_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool subpage_warning_state_var = false;
	if (access == GUI_MSG_ACCESS_SET) {
		subpage_warning_state_var = data->value_int;
	}
	data->value_int = subpage_warning_state_var;
	return 0;
}

void gui_model_sys_setting_msg_init(lv_ui *ui)
{
	gui_msg_sub_t * sub;
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	sub = gui_msg_create_sub(GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	gui_model_sys_setting_msg_init_ui();
	gui_model_sys_setting_msg_init_events();
}

void gui_model_sys_setting_msg_init_ui()
{
}

void gui_model_sys_setting_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[26] = {
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE, 0, 0},
	};

	for (int i = 0; i < 26; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}

	lv_subject_t * subject_funkey4 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4);
	lv_subject_t * subject_funkey5 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5);
	lv_subject_t * subject_funkey6 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6);
	lv_subject_t * subject_funkey7 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7);
	lv_subject_t * subject_subpage_warning = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING);
	lv_subject_t * subject_hide_viewdate = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE);
	lv_subject_t * subject_hide_viewcarnum = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM);
	lv_subject_t * subject_hide_viewlist = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST);
	lv_subject_t * subject_hide_subpagewarning = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING);
	lv_subject_t * subject_show_viewdate = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE);
	lv_subject_t * subject_show_viewcarnum = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM);
	lv_subject_t * subject_show_viewlist = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST);
	lv_subject_t * subject_show_subpagewarning = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING);
	lv_subject_t * subject_hide_funkey5 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5);
	lv_subject_t * subject_hide_funkey6 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6);
	lv_subject_t * subject_hide_funkey7 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7);
	lv_subject_t * subject_show_funkey4 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4);
	lv_subject_t * subject_show_funkey5 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5);
	lv_subject_t * subject_show_funkey6 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6);
	lv_subject_t * subject_show_funkey7 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7);
	lv_subject_t * subject_state_funkey4 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4);
	lv_subject_t * subject_state_funkey5 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5);
	lv_subject_t * subject_state_funkey6 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6);
	lv_subject_t * subject_state_funkey7 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7);
	lv_subject_t * subject_hide_funkey4 = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4);
	lv_subject_t * subject_subpage_warning_state = gui_msg_get_subject(GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE);

	for (int i = 0; i < 26; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
}

void gui_model_sys_setting_msg_unsubscribe()
{
	_gui_msg_status_t status[26] = {
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4, 0, 0},
		{GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE, 0, 0},
	};
	for (int i = 0; i < 26; i++) {
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

	for (int i = 0; i < 26; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_data_t * gui_model_sys_setting_msg_get(int32_t msg_id)
{
	switch (msg_id) {
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4: {
			gui_model_sys_setting_msg_funkey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5: {
			gui_model_sys_setting_msg_funkey5_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6: {
			gui_model_sys_setting_msg_funkey6_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7: {
			gui_model_sys_setting_msg_funkey7_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING: {
			gui_model_sys_setting_msg_subpage_warning_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE: {
			gui_model_sys_setting_msg_hide_viewdate_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM: {
			gui_model_sys_setting_msg_hide_viewcarnum_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST: {
			gui_model_sys_setting_msg_hide_viewlist_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING: {
			gui_model_sys_setting_msg_hide_subpagewarning_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE: {
			gui_model_sys_setting_msg_show_viewdate_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM: {
			gui_model_sys_setting_msg_show_viewcarnum_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST: {
			gui_model_sys_setting_msg_show_viewlist_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING: {
			gui_model_sys_setting_msg_show_subpagewarning_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5: {
			gui_model_sys_setting_msg_hide_funkey5_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6: {
			gui_model_sys_setting_msg_hide_funkey6_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7: {
			gui_model_sys_setting_msg_hide_funkey7_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4: {
			gui_model_sys_setting_msg_show_funkey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5: {
			gui_model_sys_setting_msg_show_funkey5_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6: {
			gui_model_sys_setting_msg_show_funkey6_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7: {
			gui_model_sys_setting_msg_show_funkey7_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4: {
			gui_model_sys_setting_msg_state_funkey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5: {
			gui_model_sys_setting_msg_state_funkey5_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6: {
			gui_model_sys_setting_msg_state_funkey6_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7: {
			gui_model_sys_setting_msg_state_funkey7_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4: {
			gui_model_sys_setting_msg_hide_funkey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE: {
			gui_model_sys_setting_msg_subpage_warning_state_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
			break;
		}
		default:
			return NULL;
	}
	return &guider_msg_data;
}

void gui_model_sys_setting_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	switch (msg_id) {
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4: {
			gui_model_sys_setting_msg_funkey4_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5: {
			gui_model_sys_setting_msg_funkey5_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6: {
			gui_model_sys_setting_msg_funkey6_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7: {
			gui_model_sys_setting_msg_funkey7_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING: {
			gui_model_sys_setting_msg_subpage_warning_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE: {
			gui_model_sys_setting_msg_hide_viewdate_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM: {
			gui_model_sys_setting_msg_hide_viewcarnum_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST: {
			gui_model_sys_setting_msg_hide_viewlist_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING: {
			gui_model_sys_setting_msg_hide_subpagewarning_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE: {
			gui_model_sys_setting_msg_show_viewdate_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM: {
			gui_model_sys_setting_msg_show_viewcarnum_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST: {
			gui_model_sys_setting_msg_show_viewlist_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING: {
			gui_model_sys_setting_msg_show_subpagewarning_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5: {
			gui_model_sys_setting_msg_hide_funkey5_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6: {
			gui_model_sys_setting_msg_hide_funkey6_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7: {
			gui_model_sys_setting_msg_hide_funkey7_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4: {
			gui_model_sys_setting_msg_show_funkey4_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5: {
			gui_model_sys_setting_msg_show_funkey5_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6: {
			gui_model_sys_setting_msg_show_funkey6_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7: {
			gui_model_sys_setting_msg_show_funkey7_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4: {
			gui_model_sys_setting_msg_state_funkey4_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5: {
			gui_model_sys_setting_msg_state_funkey5_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6: {
			gui_model_sys_setting_msg_state_funkey6_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7: {
			gui_model_sys_setting_msg_state_funkey7_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4: {
			gui_model_sys_setting_msg_hide_funkey4_cb(access, data, type);
			break;
		}
		case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE: {
			gui_model_sys_setting_msg_subpage_warning_state_cb(access, data, type);
			break;
		}
		default: {
				break;
		}
	}
}

gui_msg_status_t gui_model_sys_setting_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_MODEL_SYS_SETTING_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING: {
				data_type = VALUE_STRING;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4: {
				data_type = VALUE_INT;
				guider_msg_data.value_array.ptr = value;
				guider_msg_data.value_array.len = len;
				break;
			}
			case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE: {
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

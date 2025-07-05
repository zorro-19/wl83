/*Generate Code, Do NOT Edit!*/
#include "./gui_sys_model_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;
static lv_ll_t timer_ll;

typedef struct {
	lv_timer_t * timer;
} timer_dsc_t;
static void delete_all_timer()
{
	timer_dsc_t * head = _lv_ll_get_head(&timer_ll);
	while (head != NULL)
	{
		timer_dsc_t * next = _lv_ll_get_next(&timer_ll, head);
		if (head->timer != NULL) lv_timer_del(head->timer);
		_lv_ll_remove(&timer_ll, head);
		lv_mem_free(head);
		head = next;
	}
}
static timer_dsc_t * insert_timer(lv_ll_t * ll_p, lv_timer_t * timer)
{
	timer_dsc_t * tail = _lv_ll_ins_tail(ll_p);
	tail->timer = timer;
	return tail;
}
void gui_sys_model_msg_sys_time_timer_cb(lv_timer_t * timer)
{
	gui_msg_action_change(GUI_SYS_MODEL_MSG_ID_SYS_TIME, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
	lv_subject_t * subject = gui_msg_get_subject(GUI_SYS_MODEL_MSG_ID_SYS_TIME);
	if (subject == NULL) return;
	lv_subject_set_pointer(subject, &guider_msg_data);
}


GUI_WEAK int gui_sys_model_msg_sys_time_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static struct tm sys_time_var;
	if (access == GUI_MSG_ACCESS_SET) {
		sys_time_var = data->value_time;
	} else {
		time_t now = time(NULL);
		struct tm *tm = localtime(&now);
		if (tm != NULL) {
			sys_time_var = *tm;
		}
	}
	data->value_time = sys_time_var;
	return 0;
}

void gui_sys_model_msg_init(lv_ui *ui)
{
	gui_msg_sub_t * sub;
	sub = gui_msg_create_sub(GUI_SYS_MODEL_MSG_ID_SYS_TIME);
	if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	_lv_ll_init(&timer_ll, sizeof (timer_dsc_t));
	gui_sys_model_msg_init_ui();
	gui_sys_model_msg_init_events();
}

void gui_sys_model_msg_init_ui()
{
}

void gui_sys_model_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[1] = {
		{GUI_SYS_MODEL_MSG_ID_SYS_TIME, 0, 0},
	};
	lv_timer_t * timer = NULL;
	bool sys_time_timer_enable = false;
	delete_all_timer();

	for (int i = 0; i < 1; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}

	lv_subject_t * subject_sys_time = gui_msg_get_subject(GUI_SYS_MODEL_MSG_ID_SYS_TIME);

	for (int i = 0; i < 1; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
	if (sys_time_timer_enable) {
		timer = lv_timer_create(gui_sys_model_msg_sys_time_timer_cb, 1000, NULL);
		insert_timer(&timer_ll, timer);
	}
}

void gui_sys_model_msg_unsubscribe()
{
	_gui_msg_status_t status[1] = {
		{GUI_SYS_MODEL_MSG_ID_SYS_TIME, 0, 0},
	};
	for (int i = 0; i < 1; i++) {
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

	for (int i = 0; i < 1; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_data_t * gui_sys_model_msg_get(int32_t msg_id)
{
	switch (msg_id) {
		case GUI_SYS_MODEL_MSG_ID_SYS_TIME: {
			gui_sys_model_msg_sys_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
			break;
		}
		default:
			return NULL;
	}
	return &guider_msg_data;
}

void gui_sys_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	switch (msg_id) {
		case GUI_SYS_MODEL_MSG_ID_SYS_TIME: {
			gui_sys_model_msg_sys_time_cb(access, data, type);
			break;
		}
		default: {
				break;
		}
	}
}

gui_msg_status_t gui_sys_model_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_SYS_MODEL_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_SYS_MODEL_MSG_ID_SYS_TIME: {
				data_type = VALUE_TIME;
				if (value) guider_msg_data.value_time = *((struct tm *)value);
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

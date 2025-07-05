/*Generate Code, Do NOT Edit!*/
#include "./gui_msg.h"

gui_msg_data_t guider_msg_data = {0};
gui_msg_send_status_t gui_msg_send_status = GUI_MSG_SEND_DONE;
static lv_ll_t subs_ll;

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_OBSERVER
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_file_browser_msg_init(ui);
    gui_pair_msg_init(ui);
    gui_rt_stream_msg_init(ui);
    gui_sys_prompt_msg_init(ui);
    gui_video_play_msg_init(ui);
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_OBSERVER
    gui_file_browser_msg_init_ui();
    gui_pair_msg_init_ui();
    gui_rt_stream_msg_init_ui();
    gui_sys_prompt_msg_init_ui();
    gui_video_play_msg_init_ui();
#endif
}
void gui_msg_init_events()
{
#if LV_USE_OBSERVER
    gui_file_browser_msg_init_events();
    gui_pair_msg_init_events();
    gui_rt_stream_msg_init_events();
    gui_sys_prompt_msg_init_events();
    gui_video_play_msg_init_events();
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_OBSERVER
    gui_file_browser_msg_unsubscribe();
    gui_pair_msg_unsubscribe();
    gui_rt_stream_msg_unsubscribe();
    gui_sys_prompt_msg_unsubscribe();
    gui_video_play_msg_unsubscribe();
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_OBSERVER
    gui_msg_send_status = GUI_MSG_SENDING;
    gui_msg_status_t ret;
    switch (msg_id) {
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM:
    case GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX1:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX2:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX3:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX4:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX5:
        ret = gui_file_browser_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_PAIR_MSG_ID_PAIR_CH0:
    case GUI_PAIR_MSG_ID_PAIR_CH1:
    case GUI_PAIR_MSG_ID_PAIR_CH2:
    case GUI_PAIR_MSG_ID_PAIR_CH3:
    case GUI_PAIR_MSG_ID_PAIR_CH4:
    case GUI_PAIR_MSG_ID_PAIR_CH5:
    case GUI_PAIR_MSG_ID_PARING_LAB:
    case GUI_PAIR_MSG_ID_UNPAIR_LAB:
    case GUI_PAIR_MSG_ID_DDLIST_LAB:
    case GUI_PAIR_MSG_ID_WIFI_CH_SELECT:
        ret = gui_pair_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH:
    case GUI_RT_STREAM_MSG_ID_STREAM_INFO:
        ret = gui_rt_stream_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB:
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB:
        ret = gui_sys_prompt_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR:
    case GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL:
        ret = gui_video_play_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    default:
        break;
    }
    gui_msg_send_status = GUI_MSG_SEND_DONE;
    return GUI_MSG_STATUS_NO_FOUND_ID;
#else
    return GUI_MSG_STATUS_ERROR;
#endif
}
gui_msg_send_status_t gui_msg_get_send_status()
{
    return gui_msg_send_status;
}
GUI_WEAK gui_msg_data_t *gui_msg_get(int32_t msg_id)
{
    return gui_msg_get_guider(msg_id);
}
gui_msg_data_t *gui_msg_get_guider(int32_t msg_id)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_FILE_BROWSER_MSG_ID:
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM:
    case GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX1:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX2:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX3:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX4:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX5:
        return gui_file_browser_msg_get(msg_id);

    case GUI_PAIR_MSG_ID:
    case GUI_PAIR_MSG_ID_PAIR_CH0:
    case GUI_PAIR_MSG_ID_PAIR_CH1:
    case GUI_PAIR_MSG_ID_PAIR_CH2:
    case GUI_PAIR_MSG_ID_PAIR_CH3:
    case GUI_PAIR_MSG_ID_PAIR_CH4:
    case GUI_PAIR_MSG_ID_PAIR_CH5:
    case GUI_PAIR_MSG_ID_PARING_LAB:
    case GUI_PAIR_MSG_ID_UNPAIR_LAB:
    case GUI_PAIR_MSG_ID_DDLIST_LAB:
    case GUI_PAIR_MSG_ID_WIFI_CH_SELECT:
        return gui_pair_msg_get(msg_id);

    case GUI_RT_STREAM_MSG_ID:
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH:
    case GUI_RT_STREAM_MSG_ID_STREAM_INFO:
        return gui_rt_stream_msg_get(msg_id);

    case GUI_SYS_PROMPT_MSG_ID:
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB:
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB:
        return gui_sys_prompt_msg_get(msg_id);

    case GUI_VIDEO_PLAY_MSG_ID:
    case GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR:
    case GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL:
        return gui_video_play_msg_get(msg_id);

    default:
        break;
    }
#endif
    return NULL;
}
GUI_WEAK void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    gui_msg_action_change_guider(msg_id, access, data, type);
}
void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_FILE_BROWSER_MSG_ID:
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM:
    case GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX1:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX2:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX3:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX4:
    case GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX5:
        return gui_file_browser_msg_action_change(msg_id, access, data, type);

    case GUI_PAIR_MSG_ID:
    case GUI_PAIR_MSG_ID_PAIR_CH0:
    case GUI_PAIR_MSG_ID_PAIR_CH1:
    case GUI_PAIR_MSG_ID_PAIR_CH2:
    case GUI_PAIR_MSG_ID_PAIR_CH3:
    case GUI_PAIR_MSG_ID_PAIR_CH4:
    case GUI_PAIR_MSG_ID_PAIR_CH5:
    case GUI_PAIR_MSG_ID_PARING_LAB:
    case GUI_PAIR_MSG_ID_UNPAIR_LAB:
    case GUI_PAIR_MSG_ID_DDLIST_LAB:
    case GUI_PAIR_MSG_ID_WIFI_CH_SELECT:
        return gui_pair_msg_action_change(msg_id, access, data, type);

    case GUI_RT_STREAM_MSG_ID:
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH:
    case GUI_RT_STREAM_MSG_ID_STREAM_INFO:
        return gui_rt_stream_msg_action_change(msg_id, access, data, type);

    case GUI_SYS_PROMPT_MSG_ID:
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB:
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB:
        return gui_sys_prompt_msg_action_change(msg_id, access, data, type);

    case GUI_VIDEO_PLAY_MSG_ID:
    case GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR:
    case GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL:
        return gui_video_play_msg_action_change(msg_id, access, data, type);

    default:
        break;
    }
#endif
}
GUI_WEAK void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
    gui_msg_subscribe_change_guider(msg_id, sub_type);
}
void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
}
lv_subject_t *gui_msg_get_subject(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub != NULL) {
        return sub->subject;
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_get_sub(int32_t msg_id)
{
    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        if (head->msg_id == msg_id) {
            return head;
        }
        head = _lv_ll_get_next(&subs_ll, head);
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_create_sub(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub == NULL) {
        sub = _lv_ll_ins_tail(&subs_ll);
        sub->msg_id = msg_id;
        sub->subject = lv_mem_alloc(sizeof(lv_subject_t));
    }
    return sub;
}
gui_msg_data_t *gui_msg_get_data()
{
    return &guider_msg_data;
}
bool gui_msg_has_observer(lv_subject_t *subject, lv_observer_cb_t cb, lv_obj_t *obj, void *user_data)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return false;
    }
    lv_observer_t *observer = _lv_ll_get_head(&(subject->subs_ll));
    while (observer != NULL) {
        if (observer->cb == cb && observer->target == obj && observer->user_data == user_data) {
            return true;
        }
        observer = _lv_ll_get_next(&(subject->subs_ll), observer);
    }
    return false;
}
void gui_msg_setup_component(bool subscribe_enabled, bool event_enabled, lv_subject_t *subject, lv_obj_t *target_obj, gui_msg_data_t *msg_data, lv_observer_cb_t observer_cb, int32_t msg_id, gui_msg_action_t msg_action, gui_msg_data_type_t data_type, lv_event_cb_t event_cb)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return;
    }

    if (subscribe_enabled) {
        if (!gui_msg_has_observer(subject, observer_cb, target_obj, msg_data)) {
            gui_msg_action_change(msg_id, msg_action, msg_data, data_type);
            lv_subject_add_observer_obj(subject, observer_cb, target_obj, msg_data);
        }
    }

    if (event_enabled) {
        lv_obj_remove_event_cb(target_obj, event_cb);
        lv_obj_add_event_cb(target_obj, event_cb, LV_EVENT_VALUE_CHANGED, (void *)msg_id);
    }
}

void gui_msg_set_imglist_selected_index_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_imglist_set_act(obj, data->value_int);
}
void gui_msg_set_dropdown_list_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_dropdown_set_options(obj, (const char *)data->value_string);
}
void gui_msg_set_dropdown_selected_index_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_dropdown_set_selected(obj, data->value_int);
}
void gui_msg_change_dropdown_selected_index_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    int32_t msg_id = (int32_t)lv_event_get_user_data(e);
    int32_t var = lv_dropdown_get_selected(obj);
    gui_msg_send(msg_id, (void *)var, 1);
}
void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    if (data->value_bool) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}
void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_label_set_text(obj, data->value_string);
}
void gui_msg_set_checkbox_checked_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_obj_clear_state(obj, LV_STATE_ANY);
    lv_obj_add_state(obj, data->value_bool ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
}
void gui_msg_change_checkbox_checked_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    int32_t msg_id = (int32_t)lv_event_get_user_data(e);
    int32_t var = lv_obj_has_state(obj, LV_STATE_CHECKED);
    gui_msg_send(msg_id, (void *)var, 1);
}
void gui_msg_set_bar_bar_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_bar_set_value(obj, data->value_int, LV_ANIM_OFF);
}

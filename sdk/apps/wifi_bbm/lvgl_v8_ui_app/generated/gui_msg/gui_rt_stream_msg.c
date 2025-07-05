/*Generate Code, Do NOT Edit!*/
#include "./gui_rt_stream_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_rt_stream_msg_camera_switch_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool camera_switch_var = false;
    if (access == GUI_MSG_ACCESS_SET) {
        camera_switch_var = data->value_int;
    }
    data->value_int = camera_switch_var;
    return 0;
}
GUI_WEAK int gui_rt_stream_msg_stream_info_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char stream_info_init_var[] = "";
    static bool stream_info_is_init = false;
    static char *stream_info_var = NULL;
    if (stream_info_is_init == false) {
        stream_info_var = lv_mem_alloc(strlen(stream_info_init_var) + 1);
        strcpy(stream_info_var, stream_info_init_var);
        stream_info_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(stream_info_var);
        stream_info_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(stream_info_var, data->value_string);
    }
    data->value_string = stream_info_var;
    return 0;
}

void gui_rt_stream_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_RT_STREAM_MSG_ID_STREAM_INFO);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_rt_stream_msg_init_ui();
    gui_rt_stream_msg_init_events();
}

void gui_rt_stream_msg_init_ui()
{
}

void gui_rt_stream_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[2] = {
        {GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, 0, 0},
        {GUI_RT_STREAM_MSG_ID_STREAM_INFO, 0, 0},
    };

    for (int i = 0; i < 2; i++) {
        lv_subject_t *subject = gui_msg_get_subject(status[i].msg_id);
        if (subject == NULL) {
            continue;
        }
        lv_ll_t subject_ll = subject->subs_ll;
        gui_msg_sub_t *head = _lv_ll_get_head(&subject_ll);
        if (head != NULL) {
            status[i].is_unsubscribe = 1;
        }
    }

    lv_subject_t *subject_camera_switch = gui_msg_get_subject(GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH);
    lv_subject_t *subject_stream_info = gui_msg_get_subject(GUI_RT_STREAM_MSG_ID_STREAM_INFO);
    if (guider_ui.rt_stream) {
        lv_ui_rt_stream *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_RT_STREAM);
        gui_msg_setup_component(true, false, subject_stream_info, ui_scr->rt_stream_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_RT_STREAM_MSG_ID_STREAM_INFO, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_camera_switch, ui_scr->rt_stream_imgbtn_1, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);


        for (int i = 0; i < 2; i++) {
            if (status[i].msg_id == GUI_RT_STREAM_MSG_ID_STREAM_INFO) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_rt_stream_msg_unsubscribe()
{
    _gui_msg_status_t status[2] = {
        {GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, 0, 0},
        {GUI_RT_STREAM_MSG_ID_STREAM_INFO, 0, 0},
    };
    for (int i = 0; i < 2; i++) {
        lv_subject_t *subject = gui_msg_get_subject(status[i].msg_id);
        if (subject == NULL) {
            continue;
        }
        lv_ll_t subject_ll = subject->subs_ll;
        lv_observer_t *head = _lv_ll_get_head(&subject_ll);
        if (head != NULL) {
            status[i].is_unsubscribe = 1;
        }
        while (head != NULL) {
            lv_obj_t *obj = head->target;
            if (obj != NULL && lv_obj_is_valid(obj) == true) {
                lv_subject_remove_all_obj(subject, obj);
            }
            head = _lv_ll_get_head(&subject_ll);
        }
    }

    for (int i = 0; i < 2; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_rt_stream_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH: {
        gui_rt_stream_msg_camera_switch_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
        break;
    }
    case GUI_RT_STREAM_MSG_ID_STREAM_INFO: {
        gui_rt_stream_msg_stream_info_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_rt_stream_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH: {
        gui_rt_stream_msg_camera_switch_cb(access, data, type);
        break;
    }
    case GUI_RT_STREAM_MSG_ID_STREAM_INFO: {
        gui_rt_stream_msg_stream_info_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_rt_stream_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_RT_STREAM_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_RT_STREAM_MSG_ID_STREAM_INFO: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        default:
            break;
        }
        gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
        lv_subject_t *subject = gui_msg_get_subject(msg_id);
        if (subject == NULL) {
            return GUI_MSG_STATUS_NO_SUBSCRIBE;
        }
        lv_subject_set_pointer(subject, &guider_msg_data);
    }
    return GUI_MSG_STATUS_SUCCESS;
}

#endif

/*Generate Code, Do NOT Edit!*/
#include "./gui_local_music_volume_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_local_music_volume_msg_volume_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t volume_var = 50;
    if (access == GUI_MSG_ACCESS_SET) {
        volume_var = data->value_int;
    }
    data->value_int = volume_var;
    return 0;
}
GUI_WEAK int gui_local_music_volume_msg_play_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char play_name_init_var[] = "";
    static bool play_name_is_init = false;
    static char *play_name_var = NULL;
    if (play_name_is_init == false) {
        play_name_var = lv_mem_alloc(strlen(play_name_init_var) + 1);
        strcpy(play_name_var, play_name_init_var);
        play_name_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(play_name_var);
        play_name_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(play_name_var, data->value_string);
    }
    data->value_string = play_name_var;
    return 0;
}
GUI_WEAK int gui_local_music_volume_msg_play_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t play_time_var = 1;
    if (access == GUI_MSG_ACCESS_SET) {
        play_time_var = data->value_int;
    }
    data->value_int = play_time_var;
    return 0;
}

void gui_local_music_volume_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_local_music_volume_msg_init_ui();
    gui_local_music_volume_msg_init_events();
}

void gui_local_music_volume_msg_init_ui()
{
}

void gui_local_music_volume_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[3] = {
        {GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME, 0, 0},
        {GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME, 0, 0},
        {GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME, 0, 0},
    };

    for (int i = 0; i < 3; i++) {
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

    lv_subject_t *subject_volume = gui_msg_get_subject(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME);
    lv_subject_t *subject_play_name = gui_msg_get_subject(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME);
    lv_subject_t *subject_play_time = gui_msg_get_subject(GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME);
    if (!guider_ui.audio_recorder_del) {
        gui_local_music_volume_msg_volume_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        lv_subject_add_observer_obj(subject_volume, gui_msg_set_slider_starting_value_by_int32_cb, guider_ui.audio_recorder_volume_slider, &guider_msg_data);


        for (int i = 0; i < 3; i++) {
            if (status[i].msg_id == GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (!guider_ui.audio_local_music_del) {
        gui_local_music_volume_msg_volume_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        lv_subject_add_observer_obj(subject_volume, gui_msg_set_slider_starting_value_by_int32_cb, guider_ui.audio_local_music_volume_slider, &guider_msg_data);

        gui_local_music_volume_msg_play_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        lv_subject_add_observer_obj(subject_play_time, gui_msg_set_bar_bar_value_by_int32_cb, guider_ui.audio_local_music_music_time, &guider_msg_data);

        gui_local_music_volume_msg_play_name_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        lv_subject_add_observer_obj(subject_play_name, gui_msg_set_label_text_by_string_cb, guider_ui.audio_local_music_lbl_1, &guider_msg_data);


        for (int i = 0; i < 3; i++) {
            if (status[i].msg_id == GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_local_music_volume_msg_unsubscribe()
{
    _gui_msg_status_t status[3] = {
        {GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME, 0, 0},
        {GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME, 0, 0},
        {GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME, 0, 0},
    };
    for (int i = 0; i < 3; i++) {
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

    for (int i = 0; i < 3; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_local_music_volume_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME: {
        gui_local_music_volume_msg_volume_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME: {
        gui_local_music_volume_msg_play_name_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME: {
        gui_local_music_volume_msg_play_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_local_music_volume_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME: {
        gui_local_music_volume_msg_volume_cb(access, data, type);
        break;
    }
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME: {
        gui_local_music_volume_msg_play_name_cb(access, data, type);
        break;
    }
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME: {
        gui_local_music_volume_msg_play_time_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_local_music_volume_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_LOCAL_MUSIC_VOLUME_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME: {
            data_type = VALUE_INT;
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

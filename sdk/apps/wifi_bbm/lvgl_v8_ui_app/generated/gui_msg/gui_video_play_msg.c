/*Generate Code, Do NOT Edit!*/
#include "./gui_video_play_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_video_play_msg_progress_bar_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t progress_bar_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        progress_bar_var = data->value_int;
    }
    data->value_int = progress_bar_var;
    return 0;
}
GUI_WEAK int gui_video_play_msg_play_control_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t play_control_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        play_control_var = data->value_int;
    }
    data->value_int = play_control_var;
    return 0;
}

void gui_video_play_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_video_play_msg_init_ui();
    gui_video_play_msg_init_events();
}

void gui_video_play_msg_init_ui()
{
}

void gui_video_play_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[2] = {
        {GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR, 0, 0},
        {GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL, 0, 0},
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

    lv_subject_t *subject_progress_bar = gui_msg_get_subject(GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR);
    lv_subject_t *subject_play_control = gui_msg_get_subject(GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL);
    if (guider_ui.video_play) {
        lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
        gui_msg_setup_component(true, false, subject_play_control, ui_scr->video_play_imglist_1, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_progress_bar, ui_scr->video_play_bar_1, &guider_msg_data, gui_msg_set_bar_bar_value_by_int32_cb, GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 2; i++) {
            if (status[i].msg_id == GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR) {
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

void gui_video_play_msg_unsubscribe()
{
    _gui_msg_status_t status[2] = {
        {GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR, 0, 0},
        {GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL, 0, 0},
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

gui_msg_data_t *gui_video_play_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR: {
        gui_video_play_msg_progress_bar_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL: {
        gui_video_play_msg_play_control_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_video_play_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR: {
        gui_video_play_msg_progress_bar_cb(access, data, type);
        break;
    }
    case GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL: {
        gui_video_play_msg_play_control_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_video_play_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_VIDEO_PLAY_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_VIDEO_PLAY_MSG_ID_PROGRESS_BAR: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_VIDEO_PLAY_MSG_ID_PLAY_CONTROL: {
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

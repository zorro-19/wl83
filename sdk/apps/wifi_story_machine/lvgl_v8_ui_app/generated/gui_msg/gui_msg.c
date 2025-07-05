/*Generate Code, Do NOT Edit!*/
#include "./gui_msg.h"

gui_msg_data_t guider_msg_data = {0};
static lv_ll_t subs_ll;

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_OBSERVER
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_bluetooth_msg_init(ui);
    gui_key_msg_init(ui);
    gui_local_music_volume_msg_init(ui);
    gui_recorder_volume_msg_init(ui);
    gui_sd_card_msg_init(ui);
    gui_wifi_state_label_msg_init(ui);
    gui_blue_msg_init(ui);
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_OBSERVER
    gui_bluetooth_msg_init_ui();
    gui_key_msg_init_ui();
    gui_local_music_volume_msg_init_ui();
    gui_recorder_volume_msg_init_ui();
    gui_sd_card_msg_init_ui();
    gui_wifi_state_label_msg_init_ui();
    gui_blue_msg_init_ui();
#endif
}
void gui_msg_init_events()
{
#if LV_USE_OBSERVER
    gui_bluetooth_msg_init_events();
    gui_key_msg_init_events();
    gui_local_music_volume_msg_init_events();
    gui_recorder_volume_msg_init_events();
    gui_sd_card_msg_init_events();
    gui_wifi_state_label_msg_init_events();
    gui_blue_msg_init_events();
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_OBSERVER
    gui_bluetooth_msg_unsubscribe();
    gui_key_msg_unsubscribe();
    gui_local_music_volume_msg_unsubscribe();
    gui_recorder_volume_msg_unsubscribe();
    gui_sd_card_msg_unsubscribe();
    gui_wifi_state_label_msg_unsubscribe();
    gui_blue_msg_unsubscribe();
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_BLUETOOTH_MSG_ID_BT_NAME:
        return gui_bluetooth_msg_send(msg_id, value, len);

    case GUI_KEY_MSG_ID_KEY_TEXT:
        return gui_key_msg_send(msg_id, value, len);

    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME:
        return gui_local_music_volume_msg_send(msg_id, value, len);

    case GUI_RECORDER_VOLUME_MSG_ID_VOLUME:
        return gui_recorder_volume_msg_send(msg_id, value, len);

    case GUI_SD_CARD_MSG_ID_SDCARD:
        return gui_sd_card_msg_send(msg_id, value, len);

    case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID:
        return gui_wifi_state_label_msg_send(msg_id, value, len);

    case GUI_BLUE_MSG_ID_BT_STATE:
        return gui_blue_msg_send(msg_id, value, len);

    default:
        break;
    }
    return GUI_MSG_STATUS_NO_FOUND_ID;
#else
    return GUI_MSG_STATUS_ERROR;
#endif
}
GUI_WEAK gui_msg_data_t *gui_msg_get(int32_t msg_id)
{
    return gui_msg_get_guider(msg_id);
}
gui_msg_data_t *gui_msg_get_guider(int32_t msg_id)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_BLUETOOTH_MSG_ID:
    case GUI_BLUETOOTH_MSG_ID_BT_NAME:
        return gui_bluetooth_msg_get(msg_id);

    case GUI_KEY_MSG_ID:
    case GUI_KEY_MSG_ID_KEY_TEXT:
        return gui_key_msg_get(msg_id);

    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME:
        return gui_local_music_volume_msg_get(msg_id);

    case GUI_RECORDER_VOLUME_MSG_ID:
    case GUI_RECORDER_VOLUME_MSG_ID_VOLUME:
        return gui_recorder_volume_msg_get(msg_id);

    case GUI_SD_CARD_MSG_ID:
    case GUI_SD_CARD_MSG_ID_SDCARD:
        return gui_sd_card_msg_get(msg_id);

    case GUI_WIFI_STATE_LABEL_MSG_ID:
    case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID:
        return gui_wifi_state_label_msg_get(msg_id);

    case GUI_BLUE_MSG_ID:
    case GUI_BLUE_MSG_ID_BT_STATE:
        return gui_blue_msg_get(msg_id);

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
    case GUI_BLUETOOTH_MSG_ID:
    case GUI_BLUETOOTH_MSG_ID_BT_NAME:
        return gui_bluetooth_msg_action_change(msg_id, access, data, type);

    case GUI_KEY_MSG_ID:
    case GUI_KEY_MSG_ID_KEY_TEXT:
        return gui_key_msg_action_change(msg_id, access, data, type);

    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME:
        return gui_local_music_volume_msg_action_change(msg_id, access, data, type);

    case GUI_RECORDER_VOLUME_MSG_ID:
    case GUI_RECORDER_VOLUME_MSG_ID_VOLUME:
        return gui_recorder_volume_msg_action_change(msg_id, access, data, type);

    case GUI_SD_CARD_MSG_ID:
    case GUI_SD_CARD_MSG_ID_SDCARD:
        return gui_sd_card_msg_action_change(msg_id, access, data, type);

    case GUI_WIFI_STATE_LABEL_MSG_ID:
    case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID:
        return gui_wifi_state_label_msg_action_change(msg_id, access, data, type);

    case GUI_BLUE_MSG_ID:
    case GUI_BLUE_MSG_ID_BT_STATE:
        return gui_blue_msg_action_change(msg_id, access, data, type);

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

void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_label_set_text(obj, data->value_string);
}
void gui_msg_set_slider_starting_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_slider_set_value(obj, data->value_int, LV_ANIM_OFF);
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
void gui_msg_set_textarea_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    const char *old_text = lv_textarea_get_text(obj);
    if (strcmp(old_text, data->value_string) != 0) {
        lv_textarea_set_text(obj, data->value_string);
    }
}

/*Generate Code, Do NOT Edit!*/
#include "./gui_group.h"

void add_children_to_group(lv_obj_t *obj, lv_group_t *group);
void set_default_group_cb();

void gui_group_init()
{
    if (guider_ui.default_group == NULL) {
        guider_ui.default_group = lv_group_get_default();
    }
}

void gui_group_set_default(lv_group_t *group)
{
    if (group == NULL) {
        return;
    }

    if (guider_ui.default_group == group) {
        return set_default_group_cb();
    }
}

void gui_group_add_obj(lv_group_t *group, lv_obj_t *obj, bool is_add)
{
    if (group == NULL || obj == NULL) {
        return;
    }

    bool is_group_def = lv_obj_is_group_def(obj);
    if (is_group_def && is_add) {
        lv_group_add_obj(group, obj);
    }

    if (lv_obj_check_type(obj, &lv_list_class) ||
        lv_obj_check_type(obj, &lv_calendar_class) ||
        lv_obj_check_type(obj, &lv_msgbox_class) ||
        lv_obj_check_type(obj, &lv_tabview_class) ||
        lv_obj_check_type(obj, &lv_calendar_header_arrow_class) ||
        lv_obj_check_type(obj, &lv_calendar_header_dropdown_class)) {
        add_children_to_group(obj, group);
    } else if (lv_obj_check_type(obj, &lv_win_class)) {
        lv_obj_t *header = lv_win_get_header(obj);
        add_children_to_group(header, group);
    }

    if (!is_group_def && is_add) {
        lv_group_add_obj(group, obj);
    }
}

void add_children_to_group(lv_obj_t *obj, lv_group_t *group)
{
    if (obj == NULL || group == NULL) {
        return;
    }

    int childCnt = lv_obj_get_child_cnt(obj);
    for (int i = 0; i < childCnt; i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        if (lv_obj_is_group_def(child)) {
            lv_group_add_obj(group, child);
        }
    }
}

void set_default_group_cb()
{
    if (guider_ui.default_group == NULL) {
        return;
    }

    lv_group_remove_all_objs(guider_ui.default_group);
    lv_obj_t *act_scr = lv_scr_act();

    if (act_scr == guider_ui.audio) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_back_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_local_music_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_recorder_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_bt_music_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_net_music_btn, true);
    } else if (act_scr == guider_ui.camera) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.camera_back_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.camera_camera1_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.camera_camera2_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.camera_camera3_btn, true);
    } else if (act_scr == guider_ui.home) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.home_list, false);
    } else if (act_scr == guider_ui.key) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.key_back_btn, true);
    } else if (act_scr == guider_ui.audio_local_music) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_local_music_back_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_local_music_switch_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_local_music_prev_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_local_music_next_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_local_music_volume_slider, true);
    } else if (act_scr == guider_ui.audio_recorder) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_recorder_back_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_recorder_volume_slider, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_recorder_enc_gain_slider, true);
    } else if (act_scr == guider_ui.audio_net_music) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_net_music_back_btn, true);
    } else if (act_scr == guider_ui.wifi) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.wifi_back_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.wifi_show_current_ssid, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.wifi_ssid_txt, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.wifi_pwd_txt, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.wifi_connect_btn, true);
    } else if (act_scr == guider_ui.audio_bt_music) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.audio_bt_music_back_btn, true);
    } else if (act_scr == guider_ui.bluetooth) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.bluetooth_back_btn, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.bluetooth_show_bt_name, true);
    } else if (act_scr == guider_ui.sdcard) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.sdcard_back_btn, true);
    }
    lv_group_set_default(guider_ui.default_group);

    lv_indev_t *indev = NULL;
    while ((indev = lv_indev_get_next(indev)) != NULL) {
        lv_indev_set_group(indev, guider_ui.default_group);
    }
}

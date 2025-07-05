#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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

    if (act_scr == guider_ui.usb_slave) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.usb_slave_imgbtn_videorec, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.usb_slave_imgbtn_masstorage, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.usb_slave_imgbtn_pccam, true);
    } else if (act_scr == guider_ui.video_rec) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_video_set, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_15, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_home, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_imgbtn_lock_set, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_imgbtn_sw_window, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_resolution, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_19, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_20, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_21, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_10, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_17, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_18, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_22, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_23, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_img_24, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_lbl_funkey1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_lbl_funkey2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_lbl_funkey3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_lbl_funkey4, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_rec_roller_mutifunc, true);
    } else if (act_scr == guider_ui.home_page) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.home_page_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.home_page_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.home_page_imgbtn_3, true);
    } else if (act_scr == guider_ui.sys_setting) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_saver, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_4, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_5, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_7, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_9, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_8, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_6, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_10, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_11, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_12, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_15, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_14, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_img_16, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_roller_hour, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_roller_min, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_datetext_subpage, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_4, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_5, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_6, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_ddlist_7, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_lbl_funkey1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_lbl_funkey2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_setting_lbl_funkey3, true);
    } else if (act_scr == guider_ui.video_photo) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_video_set, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_15, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_home, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_resolution, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_19, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_20, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_21, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_10, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_17, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_18, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_22, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_23, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_img_24, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_roller_mutifunc, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_lbl_funkey1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_lbl_funkey2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_lbl_funkey3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_photo_lbl_funkey4, true);
    } else if (act_scr == guider_ui.video_play) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_pause, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_loud, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_ddlist_multi_spped, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_img_prev_file, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_play_img_next_file, true);
    } else if (act_scr == guider_ui.video_file) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_imgbtn_4, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_img_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_img_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_imgbtn_3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_imgbtn_5, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_file_view_3, true);
    } else if (act_scr == guider_ui.video_dir) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_dir_imgbtn_4, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_dir_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_dir_imgbtn_3, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_dir_imgbtn_5, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.video_dir_imgbtn_2, true);
    } else if (act_scr == guider_ui.line_drift) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.line_drift_btn_horizon, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.line_drift_btn_carhead, true);
    } else if (act_scr == guider_ui.sys_popwin) {
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_popwin_btn_1, true);
        gui_group_add_obj(guider_ui.default_group, guider_ui.sys_popwin_btn_2, true);
    }
    lv_group_set_default(guider_ui.default_group);

    lv_indev_t *indev = NULL;
    while ((indev = lv_indev_get_next(indev)) != NULL) {
        lv_indev_set_group(indev, guider_ui.default_group);
    }
}

#endif

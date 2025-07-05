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
    int32_t act_scr_id = gui_scr_get_id(gui_scr_get_act());

    if (act_scr_id == GUI_SCREEN_HOME) {
        lv_ui_home *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME);
        gui_group_add_obj(guider_ui.default_group, ui_scr->home_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->home_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->home_imgbtn_3, true);
    } else if (act_scr_id == GUI_SCREEN_PAIR_STATUS) {
        lv_ui_pair_status *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAIR_STATUS);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imglist_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imglist_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imglist_3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imglist_4, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imglist_5, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imglist_6, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_status_ddlist_1, true);
    } else if (act_scr_id == GUI_SCREEN_RT_STREAM) {
        lv_ui_rt_stream *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_RT_STREAM);
        gui_group_add_obj(guider_ui.default_group, ui_scr->rt_stream_imgbtn_1, true);
    } else if (act_scr_id == GUI_SCREEN_FILE_BROWSER) {
        lv_ui_file_browser *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_FILE_BROWSER);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_imgbtn_3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_imgbtn_4, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_file_cont1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_cb_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_file_cont2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_cb_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_file_cont3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_cb_3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_file_cont4, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_cb_4, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_file_cont5, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_cb_5, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_file_cont6, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->file_browser_cb_6, true);
    } else if (act_scr_id == GUI_SCREEN_PAIR_OPTIONS) {
        lv_ui_pair_options *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAIR_OPTIONS);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_options_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_options_imgbtn_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->pair_options_imgbtn_4, true);
    } else if (act_scr_id == GUI_SCREEN_VIDEO_PLAY) {
        lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
        gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imgbtn_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imglist_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imgbtn_3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imgbtn_2, true);
    } else if (act_scr_id == GUI_SCREEN_DIR_SELECT) {
        lv_ui_dir_select *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_DIR_SELECT);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_view_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_view_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_view_3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_view_4, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_view_5, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_view_6, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->dir_select_imgbtn_1, true);
    } else if (act_scr_id == GUI_SCREEN_DEVICE_SELECT) {
        lv_ui_device_select *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_DEVICE_SELECT);
        gui_group_add_obj(guider_ui.default_group, ui_scr->device_select_view_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->device_select_view_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->device_select_imgbtn_1, true);
    }
    lv_group_set_default(guider_ui.default_group);

    lv_indev_t *indev = NULL;
    while ((indev = lv_indev_get_next(indev)) != NULL) {
        lv_indev_set_group(indev, guider_ui.default_group);
    }
}

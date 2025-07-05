/*Generate Code, Do NOT Edit!*/
#include "./gui_pair_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_pair_msg_pair_ch0_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pair_ch0_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        pair_ch0_var = data->value_int;
    }
    data->value_int = pair_ch0_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_pair_ch1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pair_ch1_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        pair_ch1_var = data->value_int;
    }
    data->value_int = pair_ch1_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_pair_ch2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pair_ch2_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        pair_ch2_var = data->value_int;
    }
    data->value_int = pair_ch2_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_pair_ch3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pair_ch3_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        pair_ch3_var = data->value_int;
    }
    data->value_int = pair_ch3_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_pair_ch4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pair_ch4_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        pair_ch4_var = data->value_int;
    }
    data->value_int = pair_ch4_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_pair_ch5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pair_ch5_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        pair_ch5_var = data->value_int;
    }
    data->value_int = pair_ch5_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_paring_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char paring_lab_init_var[] = "";
    static bool paring_lab_is_init = false;
    static char *paring_lab_var = NULL;
    if (paring_lab_is_init == false) {
        paring_lab_var = lv_mem_alloc(strlen(paring_lab_init_var) + 1);
        strcpy(paring_lab_var, paring_lab_init_var);
        paring_lab_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(paring_lab_var);
        paring_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(paring_lab_var, data->value_string);
    }
    data->value_string = paring_lab_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_unpair_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char unpair_lab_init_var[] = "";
    static bool unpair_lab_is_init = false;
    static char *unpair_lab_var = NULL;
    if (unpair_lab_is_init == false) {
        unpair_lab_var = lv_mem_alloc(strlen(unpair_lab_init_var) + 1);
        strcpy(unpair_lab_var, unpair_lab_init_var);
        unpair_lab_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(unpair_lab_var);
        unpair_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(unpair_lab_var, data->value_string);
    }
    data->value_string = unpair_lab_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_ddlist_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char ddlist_lab_init_var[] = "";
    static bool ddlist_lab_is_init = false;
    static char *ddlist_lab_var = NULL;
    if (ddlist_lab_is_init == false) {
        ddlist_lab_var = lv_mem_alloc(strlen(ddlist_lab_init_var) + 1);
        strcpy(ddlist_lab_var, ddlist_lab_init_var);
        ddlist_lab_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(ddlist_lab_var);
        ddlist_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(ddlist_lab_var, data->value_string);
    }
    data->value_string = ddlist_lab_var;
    return 0;
}
GUI_WEAK int gui_pair_msg_wifi_ch_select_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t wifi_ch_select_var = 1;
    if (access == GUI_MSG_ACCESS_SET) {
        wifi_ch_select_var = data->value_int;
    }
    data->value_int = wifi_ch_select_var;
    return 0;
}

void gui_pair_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PAIR_CH0);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PAIR_CH1);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PAIR_CH2);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PAIR_CH3);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PAIR_CH4);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PAIR_CH5);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_PARING_LAB);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_UNPAIR_LAB);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_DDLIST_LAB);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_PAIR_MSG_ID_WIFI_CH_SELECT);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_pair_msg_init_ui();
    gui_pair_msg_init_events();
}

void gui_pair_msg_init_ui()
{
}

void gui_pair_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[10] = {
        {GUI_PAIR_MSG_ID_PAIR_CH0, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH1, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH2, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH3, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH4, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH5, 0, 0},
        {GUI_PAIR_MSG_ID_PARING_LAB, 0, 0},
        {GUI_PAIR_MSG_ID_UNPAIR_LAB, 0, 0},
        {GUI_PAIR_MSG_ID_DDLIST_LAB, 0, 0},
        {GUI_PAIR_MSG_ID_WIFI_CH_SELECT, 0, 0},
    };

    for (int i = 0; i < 10; i++) {
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

    lv_subject_t *subject_pair_ch0 = gui_msg_get_subject(GUI_PAIR_MSG_ID_PAIR_CH0);
    lv_subject_t *subject_pair_ch1 = gui_msg_get_subject(GUI_PAIR_MSG_ID_PAIR_CH1);
    lv_subject_t *subject_pair_ch2 = gui_msg_get_subject(GUI_PAIR_MSG_ID_PAIR_CH2);
    lv_subject_t *subject_pair_ch3 = gui_msg_get_subject(GUI_PAIR_MSG_ID_PAIR_CH3);
    lv_subject_t *subject_pair_ch4 = gui_msg_get_subject(GUI_PAIR_MSG_ID_PAIR_CH4);
    lv_subject_t *subject_pair_ch5 = gui_msg_get_subject(GUI_PAIR_MSG_ID_PAIR_CH5);
    lv_subject_t *subject_paring_lab = gui_msg_get_subject(GUI_PAIR_MSG_ID_PARING_LAB);
    lv_subject_t *subject_unpair_lab = gui_msg_get_subject(GUI_PAIR_MSG_ID_UNPAIR_LAB);
    lv_subject_t *subject_ddlist_lab = gui_msg_get_subject(GUI_PAIR_MSG_ID_DDLIST_LAB);
    lv_subject_t *subject_wifi_ch_select = gui_msg_get_subject(GUI_PAIR_MSG_ID_WIFI_CH_SELECT);
    if (guider_ui.pair_status) {
        lv_ui_pair_status *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAIR_STATUS);
        gui_msg_setup_component(true, false, subject_pair_ch5, ui_scr->pair_status_imglist_6, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_PAIR_CH5, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_pair_ch2, ui_scr->pair_status_imglist_3, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_PAIR_CH2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_pair_ch1, ui_scr->pair_status_imglist_2, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_PAIR_CH1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_pair_ch4, ui_scr->pair_status_imglist_5, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_PAIR_CH4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_pair_ch3, ui_scr->pair_status_imglist_4, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_PAIR_CH3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_ddlist_lab, ui_scr->pair_status_ddlist_1, &guider_msg_data, gui_msg_set_dropdown_list_by_string_cb, GUI_PAIR_MSG_ID_DDLIST_LAB, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, true, subject_wifi_ch_select, ui_scr->pair_status_ddlist_1, &guider_msg_data, gui_msg_set_dropdown_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_WIFI_CH_SELECT, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_dropdown_selected_index_cb);

        gui_msg_setup_component(true, false, subject_pair_ch0, ui_scr->pair_status_imglist_1, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_PAIR_MSG_ID_PAIR_CH0, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PAIR_CH5) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PAIR_CH0) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_DDLIST_LAB) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PAIR_CH3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PAIR_CH4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PAIR_CH1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PAIR_CH2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PAIR_MSG_ID_WIFI_CH_SELECT) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.pairing) {
        lv_ui_pairing *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAIRING);
        gui_msg_setup_component(true, false, subject_paring_lab, ui_scr->pairing_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_PAIR_MSG_ID_PARING_LAB, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_PAIR_MSG_ID_PARING_LAB) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.unpair) {
        lv_ui_unpair *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_UNPAIR);
        gui_msg_setup_component(true, false, subject_unpair_lab, ui_scr->unpair_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_PAIR_MSG_ID_UNPAIR_LAB, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_PAIR_MSG_ID_UNPAIR_LAB) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_pair_msg_unsubscribe()
{
    _gui_msg_status_t status[10] = {
        {GUI_PAIR_MSG_ID_PAIR_CH0, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH1, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH2, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH3, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH4, 0, 0},
        {GUI_PAIR_MSG_ID_PAIR_CH5, 0, 0},
        {GUI_PAIR_MSG_ID_PARING_LAB, 0, 0},
        {GUI_PAIR_MSG_ID_UNPAIR_LAB, 0, 0},
        {GUI_PAIR_MSG_ID_DDLIST_LAB, 0, 0},
        {GUI_PAIR_MSG_ID_WIFI_CH_SELECT, 0, 0},
    };
    for (int i = 0; i < 10; i++) {
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

    for (int i = 0; i < 10; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_pair_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_PAIR_MSG_ID_PAIR_CH0: {
        gui_pair_msg_pair_ch0_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH1: {
        gui_pair_msg_pair_ch1_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH2: {
        gui_pair_msg_pair_ch2_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH3: {
        gui_pair_msg_pair_ch3_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH4: {
        gui_pair_msg_pair_ch4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH5: {
        gui_pair_msg_pair_ch5_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_PAIR_MSG_ID_PARING_LAB: {
        gui_pair_msg_paring_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_PAIR_MSG_ID_UNPAIR_LAB: {
        gui_pair_msg_unpair_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_PAIR_MSG_ID_DDLIST_LAB: {
        gui_pair_msg_ddlist_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_PAIR_MSG_ID_WIFI_CH_SELECT: {
        gui_pair_msg_wifi_ch_select_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_pair_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_PAIR_MSG_ID_PAIR_CH0: {
        gui_pair_msg_pair_ch0_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH1: {
        gui_pair_msg_pair_ch1_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH2: {
        gui_pair_msg_pair_ch2_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH3: {
        gui_pair_msg_pair_ch3_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH4: {
        gui_pair_msg_pair_ch4_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_PAIR_CH5: {
        gui_pair_msg_pair_ch5_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_PARING_LAB: {
        gui_pair_msg_paring_lab_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_UNPAIR_LAB: {
        gui_pair_msg_unpair_lab_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_DDLIST_LAB: {
        gui_pair_msg_ddlist_lab_cb(access, data, type);
        break;
    }
    case GUI_PAIR_MSG_ID_WIFI_CH_SELECT: {
        gui_pair_msg_wifi_ch_select_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_pair_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_PAIR_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_PAIR_MSG_ID_PAIR_CH0: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_PAIR_CH1: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_PAIR_CH2: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_PAIR_CH3: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_PAIR_CH4: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_PAIR_CH5: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_PARING_LAB: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_UNPAIR_LAB: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_DDLIST_LAB: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_PAIR_MSG_ID_WIFI_CH_SELECT: {
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

/*Generate Code, Do NOT Edit!*/
#include "./gui_sys_prompt_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_sys_prompt_msg_prompt_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char prompt_lab_init_var[] = "Connect Error!";
    static bool prompt_lab_is_init = false;
    static char *prompt_lab_var = NULL;
    if (prompt_lab_is_init == false) {
        prompt_lab_var = lv_mem_alloc(strlen(prompt_lab_init_var) + 1);
        strcpy(prompt_lab_var, prompt_lab_init_var);
        prompt_lab_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(prompt_lab_var);
        prompt_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(prompt_lab_var, data->value_string);
    }
    data->value_string = prompt_lab_var;
    return 0;
}
GUI_WEAK int gui_sys_prompt_msg_prompt_opt_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char prompt_opt_lab_init_var[] = "";
    static bool prompt_opt_lab_is_init = false;
    static char *prompt_opt_lab_var = NULL;
    if (prompt_opt_lab_is_init == false) {
        prompt_opt_lab_var = lv_mem_alloc(strlen(prompt_opt_lab_init_var) + 1);
        strcpy(prompt_opt_lab_var, prompt_opt_lab_init_var);
        prompt_opt_lab_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(prompt_opt_lab_var);
        prompt_opt_lab_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(prompt_opt_lab_var, data->value_string);
    }
    data->value_string = prompt_opt_lab_var;
    return 0;
}

void gui_sys_prompt_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_sys_prompt_msg_init_ui();
    gui_sys_prompt_msg_init_events();
}

void gui_sys_prompt_msg_init_ui()
{
}

void gui_sys_prompt_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[2] = {
        {GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB, 0, 0},
        {GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB, 0, 0},
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

    lv_subject_t *subject_prompt_lab = gui_msg_get_subject(GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB);
    lv_subject_t *subject_prompt_opt_lab = gui_msg_get_subject(GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB);
    if (guider_ui.sys_prompt) {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        gui_msg_setup_component(true, false, subject_prompt_lab, ui_scr->sys_prompt_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 2; i++) {
            if (status[i].msg_id == GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.sys_options) {
        lv_ui_sys_options *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_OPTIONS);
        gui_msg_setup_component(true, false, subject_prompt_opt_lab, ui_scr->sys_options_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 2; i++) {
            if (status[i].msg_id == GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB) {
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

void gui_sys_prompt_msg_unsubscribe()
{
    _gui_msg_status_t status[2] = {
        {GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB, 0, 0},
        {GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB, 0, 0},
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

gui_msg_data_t *gui_sys_prompt_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB: {
        gui_sys_prompt_msg_prompt_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB: {
        gui_sys_prompt_msg_prompt_opt_lab_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_sys_prompt_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB: {
        gui_sys_prompt_msg_prompt_lab_cb(access, data, type);
        break;
    }
    case GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB: {
        gui_sys_prompt_msg_prompt_opt_lab_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_sys_prompt_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_SYS_PROMPT_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_SYS_PROMPT_MSG_ID_PROMPT_OPT_LAB: {
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

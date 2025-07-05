/*Generate Code, Do NOT Edit!*/
#include "gui_model_msg.h"
#if LV_USE_MSG

static lv_ll_t subs_ll;
static lv_ll_t timer_ll;

typedef struct {
    lv_timer_t *timer;
} timer_dsc_t;
static void delete_all_timer()
{
    timer_dsc_t *head = _lv_ll_get_head(&timer_ll);
    while (head != NULL) {
        timer_dsc_t *next = _lv_ll_get_next(&timer_ll, head);
        if (head->timer != NULL) {
            lv_timer_del(head->timer);
        }
        _lv_ll_remove(&timer_ll, head);
        lv_mem_free(head);
        head = next;
    }
}
static timer_dsc_t *insert_timer(lv_ll_t *ll_p, lv_timer_t *timer)
{
    timer_dsc_t *tail = _lv_ll_ins_tail(ll_p);
    tail->timer = timer;
    return tail;
}
void gui_model_msg_power_number_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_MODEL_MSG_ID_POWER_NUMBER, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
    lv_msg_send(GUI_MODEL_MSG_ID_POWER_NUMBER, NULL);
}
void gui_model_msg_systime_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_MODEL_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
    lv_msg_send(GUI_MODEL_MSG_ID_SYSTIME, NULL);
}

void gui_model_msg_home_img_wifi_set_img_path_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.home_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_MODEL_MSG_ID_SIGNAL) {
        return;
    }

    lv_img_set_src(obj, gui_get_res_path(guider_msg_data.value_int));
}
void gui_model_msg_home_lbl_bat_set_text_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.home_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_MODEL_MSG_ID_POWER_NUMBER) {
        return;
    }

    lv_label_set_text(obj, guider_msg_data.value_string);
}
void gui_model_msg_home_digitclock_time_set_digit_clock_time_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.home_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_MODEL_MSG_ID_SYSTIME) {
        return;
    }

    struct tm time = guider_msg_data.value_time;
    lv_label_set_text_fmt(obj, "%04d-%02d-%02d %02d:%02d:%02d", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}
void gui_model_msg_home_img_weather_set_img_path_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.home_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_MODEL_MSG_ID_WEATHER) {
        return;
    }

    lv_img_set_src(obj, gui_get_res_path(guider_msg_data.value_int));
}
void gui_model_msg_home_img_bat_set_img_path_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.home_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_MODEL_MSG_ID_POWER) {
        return;
    }

    lv_img_set_src(obj, gui_get_res_path(guider_msg_data.value_int));
}
void gui_model_msg_home_lbl_note_set_text_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.home_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_MODEL_MSG_ID_TIPS) {
        return;
    }

    lv_label_set_text(obj, guider_msg_data.value_string);
}

GUI_WEAK int gui_model_msg_power_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t power_var = RES_ICON_BATTERY_100;
    if (access == GUI_MSG_ACCESS_SET) {
        power_var = data->value_int;
    }
    data->value_int = power_var;
    return 0;
}
GUI_WEAK int gui_model_msg_signal_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t signal_var = RES_WIFI_00;
    if (access == GUI_MSG_ACCESS_SET) {
        signal_var = data->value_int;
    }
    data->value_int = signal_var;
    return 0;
}
GUI_WEAK int gui_model_msg_power_number_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char power_number_init_var[] = "100%";
    static bool power_number_is_init = false;
    static char *power_number_var = NULL;
    if (power_number_is_init == false) {
        power_number_var = lv_mem_alloc(strlen(power_number_init_var) + 1);
        strcpy(power_number_var, power_number_init_var);
        power_number_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(power_number_var);
        power_number_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(power_number_var, data->value_string);
    }
    data->value_string = power_number_var;
    return 0;
}
GUI_WEAK int gui_model_msg_keyfun1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t keyfun1_var = RES_ICON_CALL_OUT;
    if (access == GUI_MSG_ACCESS_SET) {
        keyfun1_var = data->value_int;
    }
    data->value_int = keyfun1_var;
    return 0;
}
GUI_WEAK int gui_model_msg_tips_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char tips_init_var[] = "";
    static bool tips_is_init = false;
    static char *tips_var = NULL;
    if (tips_is_init == false) {
        tips_var = lv_mem_alloc(strlen(tips_init_var) + 1);
        strcpy(tips_var, tips_init_var);
        tips_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(tips_var);
        tips_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(tips_var, data->value_string);
    }
    data->value_string = tips_var;
    return 0;
}
GUI_WEAK int gui_model_msg_calltime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm calltime_var = {
        .tm_year = 124,
        .tm_mon = 3,
        .tm_mday = 22,
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
    };
    if (access == GUI_MSG_ACCESS_SET) {
        calltime_var = data->value_time;
    }
    data->value_time = calltime_var;
    return 0;
}
GUI_WEAK int gui_model_msg_weather_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t weather_var = RES_WEATHER_010;
    if (access == GUI_MSG_ACCESS_SET) {
        weather_var = data->value_int;
    }
    data->value_int = weather_var;
    return 0;
}
GUI_WEAK int gui_model_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm systime_var = {
        .tm_year = 124,
        .tm_mon = 4,
        .tm_mday = 15,
        .tm_hour = 9,
        .tm_min = 39,
        .tm_sec = 15,
    };
    if (access == GUI_MSG_ACCESS_SET) {
        systime_var = data->value_time;
    }
    data->value_time = systime_var;
    return 0;
}
GUI_WEAK int gui_model_msg_keyfun2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t keyfun2_var = RES_ICON_WALKIE_TALKIE;
    if (access == GUI_MSG_ACCESS_SET) {
        keyfun2_var = data->value_int;
    }
    data->value_int = keyfun2_var;
    return 0;
}
GUI_WEAK int gui_model_msg_keyfun3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t keyfun3_var = RES_ICON_RECOVER;
    if (access == GUI_MSG_ACCESS_SET) {
        keyfun3_var = data->value_int;
    }
    data->value_int = keyfun3_var;
    return 0;
}
GUI_WEAK int gui_model_msg_menu_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char menu_title_init_var[] = "return_info";
    static bool menu_title_is_init = false;
    static char *menu_title_var = NULL;
    if (menu_title_is_init == false) {
        menu_title_var = lv_mem_alloc(strlen(menu_title_init_var) + 1);
        strcpy(menu_title_var, menu_title_init_var);
        menu_title_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(menu_title_var);
        menu_title_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(menu_title_var, data->value_string);
    }
    data->value_string = menu_title_var;
    return 0;
}

void gui_model_msg_init(lv_ui *ui)
{
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    _lv_ll_init(&timer_ll, sizeof(timer_dsc_t));
    gui_model_msg_init_ui();
    gui_model_msg_init_events();
}

void gui_model_msg_init_ui()
{
    if (!guider_ui.home_del) {
        gui_msg_action_change(GUI_MODEL_MSG_ID_POWER_NUMBER, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        lv_label_set_text(guider_ui.home_lbl_bat, guider_msg_data.value_string);

        gui_msg_action_change(GUI_MODEL_MSG_ID_WEATHER, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        lv_img_set_src(guider_ui.home_img_weather, gui_get_res_path(guider_msg_data.value_int));

        gui_msg_action_change(GUI_MODEL_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
        struct tm home_digitclock_time_time = guider_msg_data.value_time;
        lv_label_set_text_fmt(guider_ui.home_digitclock_time, "%04d-%02d-%02d %02d:%02d:%02d", home_digitclock_time_time.tm_year + 1900, home_digitclock_time_time.tm_mon + 1, home_digitclock_time_time.tm_mday, home_digitclock_time_time.tm_hour, home_digitclock_time_time.tm_min, home_digitclock_time_time.tm_sec);

        gui_msg_action_change(GUI_MODEL_MSG_ID_POWER, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        lv_img_set_src(guider_ui.home_img_bat, gui_get_res_path(guider_msg_data.value_int));

        gui_msg_action_change(GUI_MODEL_MSG_ID_SIGNAL, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        lv_img_set_src(guider_ui.home_img_wifi, gui_get_res_path(guider_msg_data.value_int));

        gui_msg_action_change(GUI_MODEL_MSG_ID_TIPS, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        lv_label_set_text(guider_ui.home_lbl_note, guider_msg_data.value_string);
    }
}

void gui_model_msg_init_events()
{
    void *res = NULL;
    char sub_ids[11] = {0};
    char unsub_ids[11] = {0};
    int32_t first_id = GUI_MODEL_MSG_ID_POWER;
    lv_timer_t *timer = NULL;
    bool power_number_timer_enable = false;
    bool systime_timer_enable = false;
    delete_all_timer();

    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        gui_msg_sub_t *next = _lv_ll_get_next(&subs_ll, head);
        if (head->data != NULL && lv_obj_is_valid((((gui_msg_sub_dsc_t *)head->data)->_priv_data))) {
            lv_msg_unsubscribe_obj(head->msg_id, ((gui_msg_sub_dsc_t *)head->data)->_priv_data);
        }
        unsub_ids[head->msg_id - first_id] = 1;
        _lv_ll_remove(&subs_ll, head);
        lv_mem_free(head);
        head = next;
    }

    if (!guider_ui.home_del) {
        lv_obj_remove_event_cb(guider_ui.home_lbl_note, gui_model_msg_home_lbl_note_set_text_cb);
        lv_obj_add_event_cb(guider_ui.home_lbl_note, gui_model_msg_home_lbl_note_set_text_cb, LV_EVENT_MSG_RECEIVED, NULL);

        lv_obj_remove_event_cb(guider_ui.home_img_weather, gui_model_msg_home_img_weather_set_img_path_cb);
        lv_obj_add_event_cb(guider_ui.home_img_weather, gui_model_msg_home_img_weather_set_img_path_cb, LV_EVENT_MSG_RECEIVED, NULL);

        lv_obj_remove_event_cb(guider_ui.home_digitclock_time, gui_model_msg_home_digitclock_time_set_digit_clock_time_cb);
        lv_obj_add_event_cb(guider_ui.home_digitclock_time, gui_model_msg_home_digitclock_time_set_digit_clock_time_cb, LV_EVENT_MSG_RECEIVED, NULL);

        lv_obj_remove_event_cb(guider_ui.home_img_bat, gui_model_msg_home_img_bat_set_img_path_cb);
        lv_obj_add_event_cb(guider_ui.home_img_bat, gui_model_msg_home_img_bat_set_img_path_cb, LV_EVENT_MSG_RECEIVED, NULL);

        lv_obj_remove_event_cb(guider_ui.home_img_wifi, gui_model_msg_home_img_wifi_set_img_path_cb);
        lv_obj_add_event_cb(guider_ui.home_img_wifi, gui_model_msg_home_img_wifi_set_img_path_cb, LV_EVENT_MSG_RECEIVED, NULL);

        lv_obj_remove_event_cb(guider_ui.home_lbl_bat, gui_model_msg_home_lbl_bat_set_text_cb);
        lv_obj_add_event_cb(guider_ui.home_lbl_bat, gui_model_msg_home_lbl_bat_set_text_cb, LV_EVENT_MSG_RECEIVED, NULL);

        res = lv_msg_subsribe_obj(GUI_MODEL_MSG_ID_TIPS, guider_ui.home_lbl_note, NULL);
        gui_msg_insert_list(&subs_ll, res);
        res = lv_msg_subsribe_obj(GUI_MODEL_MSG_ID_WEATHER, guider_ui.home_img_weather, NULL);
        gui_msg_insert_list(&subs_ll, res);
        res = lv_msg_subsribe_obj(GUI_MODEL_MSG_ID_SYSTIME, guider_ui.home_digitclock_time, NULL);
        gui_msg_insert_list(&subs_ll, res);
        res = lv_msg_subsribe_obj(GUI_MODEL_MSG_ID_POWER, guider_ui.home_img_bat, NULL);
        gui_msg_insert_list(&subs_ll, res);
        res = lv_msg_subsribe_obj(GUI_MODEL_MSG_ID_SIGNAL, guider_ui.home_img_wifi, NULL);
        gui_msg_insert_list(&subs_ll, res);
        res = lv_msg_subsribe_obj(GUI_MODEL_MSG_ID_POWER_NUMBER, guider_ui.home_lbl_bat, NULL);
        gui_msg_insert_list(&subs_ll, res);

        sub_ids[GUI_MODEL_MSG_ID_TIPS - first_id] = 1;
        sub_ids[GUI_MODEL_MSG_ID_WEATHER - first_id] = 1;
        sub_ids[GUI_MODEL_MSG_ID_SIGNAL - first_id] = 1;
        sub_ids[GUI_MODEL_MSG_ID_POWER - first_id] = 1;
        sub_ids[GUI_MODEL_MSG_ID_POWER_NUMBER - first_id] = 1;
        sub_ids[GUI_MODEL_MSG_ID_SYSTIME - first_id] = 1;

        power_number_timer_enable = true;
        systime_timer_enable = true;
    }

    for (int i = 0; i < 11; i++) {
        if (sub_ids[i] == 0 && unsub_ids[i] == 1) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_UNSUBSCRIBE);
        } else if (sub_ids[i] == 1 && unsub_ids[i] == 0) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_SUBSCRIBE);
        }
    }
    if (power_number_timer_enable) {
        timer = lv_timer_create(gui_model_msg_power_number_timer_cb, 6000, NULL);
        insert_timer(&timer_ll, timer);
    }
    if (systime_timer_enable) {
        timer = lv_timer_create(gui_model_msg_systime_timer_cb, 500, NULL);
        insert_timer(&timer_ll, timer);
    }
}

void gui_model_msg_unsubscribe()
{
    char msg_ids[11] = {0};
    int32_t first_id = GUI_MODEL_MSG_ID_POWER;
    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        gui_msg_sub_t *next = _lv_ll_get_next(&subs_ll, head);
        if (head->data != NULL && lv_obj_is_valid((((gui_msg_sub_dsc_t *)head->data)->_priv_data))) {
            lv_msg_unsubscribe_obj(head->msg_id, (((gui_msg_sub_dsc_t *)head->data)->_priv_data));
        }
        msg_ids[head->msg_id - first_id] = 1;
        _lv_ll_remove(&subs_ll, head);
        lv_mem_free(head);
        head = next;
    }
    for (int i = 0; i < 11; i++) {
        if (msg_ids[i] == 1) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

void gui_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_MODEL_MSG_ID_POWER: {
        gui_model_msg_power_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_SIGNAL: {
        gui_model_msg_signal_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_POWER_NUMBER: {
        gui_model_msg_power_number_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN1: {
        gui_model_msg_keyfun1_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_TIPS: {
        gui_model_msg_tips_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_CALLTIME: {
        gui_model_msg_calltime_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_WEATHER: {
        gui_model_msg_weather_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_SYSTIME: {
        gui_model_msg_systime_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN2: {
        gui_model_msg_keyfun2_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN3: {
        gui_model_msg_keyfun3_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_MENU_TITLE: {
        gui_model_msg_menu_title_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_model_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_MSG_ID) {
        lv_msg_send(GUI_MODEL_MSG_ID_POWER, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_SIGNAL, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_POWER_NUMBER, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_KEYFUN1, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_TIPS, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_CALLTIME, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_WEATHER, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_SYSTIME, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_KEYFUN2, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_KEYFUN3, NULL);
        lv_msg_send(GUI_MODEL_MSG_ID_MENU_TITLE, NULL);
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_MSG_ID_POWER: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_SIGNAL: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_POWER_NUMBER: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_KEYFUN1: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_TIPS: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_CALLTIME: {
            data_type = VALUE_TIME;
            if (value) {
                guider_msg_data.value_time = *((struct tm *)value);
            }
            break;
        }
        case GUI_MODEL_MSG_ID_WEATHER: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_SYSTIME: {
            data_type = VALUE_TIME;
            if (value) {
                guider_msg_data.value_time = *((struct tm *)value);
            }
            break;
        }
        case GUI_MODEL_MSG_ID_KEYFUN2: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_KEYFUN3: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_MENU_TITLE: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        default:
            break;
        }
        gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
        bool found = lv_msg_send(msg_id, NULL);
        return found ? GUI_MSG_STATUS_SUCCESS : GUI_MSG_STATUS_NO_SUBSCRIBE;
    }
    return GUI_MSG_STATUS_SUCCESS;
}

#endif

/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MSG_H_
#define GUI_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include "gui_guider.h"
#include "lvgl.h"
#include "custom.h"
#include "time.h"

typedef enum {
    GUI_MSG_ACCESS_GET = 0,
    GUI_MSG_ACCESS_SET,
} gui_msg_action_t;

typedef enum {
    GUI_MSG_SUBSCRIBE = 0,
    GUI_MSG_UNSUBSCRIBE,
} gui_msg_subscribe_t;

typedef enum {
    VALUE_INT = 1,
    VALUE_CHAR,
    VALUE_SHORT,
    VALUE_COORD,
    VALUE_BOOL,
    VALUE_STRING,
    VALUE_COLOR,
    VALUE_DATE,
    VALUE_POINT,
    VALUE_TIME,
    VALUE_ARRAY,
    VALUE_UNKNOWN = 0,
} gui_msg_data_type_t;

typedef enum {
    GUI_MSG_STATUS_SUCCESS = 0,
    GUI_MSG_STATUS_ERROR = -1,
    GUI_MSG_STATUS_NO_SUBSCRIBE = -2,
    GUI_MSG_STATUS_NO_FOUND_ID = -3,
} gui_msg_status_t;

typedef union {
    int32_t value_int;
    lv_coord_t value_coord;
    bool value_bool;
    char *value_string;
    lv_color_t value_color;
    lv_calendar_date_t value_date;
    lv_point_t value_point;
    struct tm value_time;
    struct {
        void *ptr;
        int32_t len;
    } value_array;
} gui_msg_data_t;

typedef enum {
    GUI_MODEL_MSG_ID = 0,
} gui_msg_id_t;

typedef struct {
    void *data;
    int32_t msg_id;
} gui_msg_sub_t;

#if LV_USE_MSG
typedef struct {
    uint32_t msg_id;
    lv_msg_subscribe_cb_t callback;
    void *user_data;
    void *_priv_data;       /*Internal: used only store 'obj' in lv_obj_subscribe*/
} gui_msg_sub_dsc_t;
#endif

extern void gui_msg_init(lv_ui *ui);
extern void gui_msg_init_ui();
extern void gui_msg_init_events();
extern void gui_msg_unsubscribe();
extern gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len);
extern GUI_WEAKREF void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern GUI_WEAKREF void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type);
extern void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type);
extern void *gui_msg_insert_list(lv_ll_t *ll_p, void *data);
extern bool gui_msg_id_is_in_list(lv_ll_t *ll_p, int32_t msg_id);
extern gui_msg_data_t *gui_msg_get_data();

#if LV_USE_MSG
#include "gui_model_msg.h"
#endif

extern gui_msg_data_t guider_msg_data;

#ifdef __cplusplus
}
#endif
#endif /* GUI_MSG_H_ */

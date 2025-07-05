/*Generate Code, Do NOT Edit!*/
#ifndef GUI_BLUE_MSG_H_
#define GUI_BLUE_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_BLUE_MSG_ID_BT_STATE = 0x10001,
} gui_blue_msg_id_t;

extern int gui_blue_msg_bt_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_blue_msg_init(lv_ui *ui);
extern void gui_blue_msg_init_ui();
extern void gui_blue_msg_init_events();
extern void gui_blue_msg_unsubscribe();
extern gui_msg_status_t gui_blue_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_blue_msg_get(int32_t msg_id);
extern void gui_blue_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_BLUE_MSG_H_ */

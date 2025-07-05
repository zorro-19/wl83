/*Generate Code, Do NOT Edit!*/
#ifndef GUI_KEY_MSG_H_
#define GUI_KEY_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_KEY_MSG_ID_KEY_TEXT = 0x0004,
} gui_key_msg_id_t;

extern int gui_key_msg_key_text_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_key_msg_init(lv_ui *ui);
extern void gui_key_msg_init_ui();
extern void gui_key_msg_init_events();
extern void gui_key_msg_unsubscribe();
extern gui_msg_status_t gui_key_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_key_msg_get(int32_t msg_id);
extern void gui_key_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_KEY_MSG_H_ */

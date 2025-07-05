/*Generate Code, Do NOT Edit!*/
#ifndef GUI_FILE_BROWSER_MSG_H_
#define GUI_FILE_BROWSER_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_FILE_BROWSER_MSG_ID_FILE_NUM = 0x000D,
    GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL = 0x0013,
    GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0 = 0x0014,
    GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX1 = 0x0015,
    GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX2 = 0x0016,
    GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX3 = 0x0017,
    GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX4 = 0x0018,
    GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX5 = 0x0019,
} gui_file_browser_msg_id_t;

extern int gui_file_browser_msg_file_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_check_box_del_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_sel_check_box0_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_sel_check_box1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_sel_check_box2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_sel_check_box3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_sel_check_box4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_file_browser_msg_sel_check_box5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_file_browser_msg_init(lv_ui *ui);
extern void gui_file_browser_msg_init_ui();
extern void gui_file_browser_msg_init_events();
extern void gui_file_browser_msg_unsubscribe();
extern gui_msg_status_t gui_file_browser_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_file_browser_msg_get(int32_t msg_id);
extern void gui_file_browser_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_FILE_BROWSER_MSG_H_ */

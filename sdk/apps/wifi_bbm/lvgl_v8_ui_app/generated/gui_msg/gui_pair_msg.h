/*Generate Code, Do NOT Edit!*/
#ifndef GUI_PAIR_MSG_H_
#define GUI_PAIR_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_PAIR_MSG_ID_PAIR_CH0 = 0x0002,
    GUI_PAIR_MSG_ID_PAIR_CH1 = 0x0003,
    GUI_PAIR_MSG_ID_PAIR_CH2 = 0x0004,
    GUI_PAIR_MSG_ID_PAIR_CH3 = 0x0005,
    GUI_PAIR_MSG_ID_PAIR_CH4 = 0x0006,
    GUI_PAIR_MSG_ID_PAIR_CH5 = 0x0007,
    GUI_PAIR_MSG_ID_PARING_LAB = 0x0008,
    GUI_PAIR_MSG_ID_UNPAIR_LAB = 0x0009,
    GUI_PAIR_MSG_ID_DDLIST_LAB = 0x001B,
    GUI_PAIR_MSG_ID_WIFI_CH_SELECT = 0x001C,
} gui_pair_msg_id_t;

extern int gui_pair_msg_pair_ch0_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_pair_ch1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_pair_ch2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_pair_ch3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_pair_ch4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_pair_ch5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_paring_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_unpair_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_ddlist_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_pair_msg_wifi_ch_select_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_pair_msg_init(lv_ui *ui);
extern void gui_pair_msg_init_ui();
extern void gui_pair_msg_init_events();
extern void gui_pair_msg_unsubscribe();
extern gui_msg_status_t gui_pair_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_pair_msg_get(int32_t msg_id);
extern void gui_pair_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_PAIR_MSG_H_ */

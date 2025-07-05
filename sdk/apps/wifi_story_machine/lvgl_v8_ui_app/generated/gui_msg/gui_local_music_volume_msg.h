/*Generate Code, Do NOT Edit!*/
#ifndef GUI_LOCAL_MUSIC_VOLUME_MSG_H_
#define GUI_LOCAL_MUSIC_VOLUME_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME = 0x0006,
    GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME = 0x0007,
    GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME = 0x0008,
} gui_local_music_volume_msg_id_t;

extern int gui_local_music_volume_msg_volume_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_local_music_volume_msg_play_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_local_music_volume_msg_play_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_local_music_volume_msg_init(lv_ui *ui);
extern void gui_local_music_volume_msg_init_ui();
extern void gui_local_music_volume_msg_init_events();
extern void gui_local_music_volume_msg_unsubscribe();
extern gui_msg_status_t gui_local_music_volume_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_local_music_volume_msg_get(int32_t msg_id);
extern void gui_local_music_volume_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_LOCAL_MUSIC_VOLUME_MSG_H_ */

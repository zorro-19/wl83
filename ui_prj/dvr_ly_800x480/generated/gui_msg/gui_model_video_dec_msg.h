/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_VIDEO_DEC_MSG_H_
#define GUI_MODEL_VIDEO_DEC_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
	GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG = 0x007D,
	GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB = 0x007E,
	GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB = 0x007F,
	GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB = 0x0080,
	GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG = 0x0081,
	GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG = 0x0082,
	GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW = 0x0083,
	GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW = 0x0084,
	GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB = 0x0085,
} gui_model_video_dec_msg_id_t;

extern int gui_model_video_dec_msg_file_type_img_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_video_time_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_file_name_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_media_info_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_sd_status_img_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_play_status_img_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_video_cont_show_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_file_lock_show_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_video_dec_options_lab_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);

extern void gui_model_video_dec_msg_init(lv_ui *ui);
extern void gui_model_video_dec_msg_init_ui();
extern void gui_model_video_dec_msg_init_events();
extern void gui_model_video_dec_msg_unsubscribe();
extern gui_msg_status_t gui_model_video_dec_msg_send(int32_t msg_id, void * value, int32_t len);
extern gui_msg_data_t * gui_model_video_dec_msg_get(int32_t msg_id);
extern void gui_model_video_dec_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_VIDEO_DEC_MSG_H_ */

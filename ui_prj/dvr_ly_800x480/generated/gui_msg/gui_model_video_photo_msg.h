/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_VIDEO_PHOTO_MSG_H_
#define GUI_MODEL_VIDEO_PHOTO_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON = 0x0047,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON = 0x0048,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON = 0x0049,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON = 0x004A,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE = 0x004B,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE = 0x004C,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS = 0x004D,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS = 0x004E,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE = 0x004F,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE = 0x0050,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN = 0x0051,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON = 0x0075,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON = 0x0046,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE = 0x0076,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON = 0x0077,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON = 0x0078,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON = 0x0079,
	GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO = 0x007A,
} gui_model_video_photo_msg_id_t;

extern int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_shot_mode_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_pexp_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_iso_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_delay_sate_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_delay_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_handshake_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_shots_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_photo_reso_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);

extern void gui_model_video_photo_msg_init(lv_ui *ui);
extern void gui_model_video_photo_msg_init_ui();
extern void gui_model_video_photo_msg_init_events();
extern void gui_model_video_photo_msg_unsubscribe();
extern gui_msg_status_t gui_model_video_photo_msg_send(int32_t msg_id, void * value, int32_t len);
extern gui_msg_data_t * gui_model_video_photo_msg_get(int32_t msg_id);
extern void gui_model_video_photo_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_VIDEO_PHOTO_MSG_H_ */

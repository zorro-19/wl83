/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_VIDEO_REC_MSG_H_
#define GUI_MODEL_VIDEO_REC_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
	GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON = 0x0053,
	GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON = 0x0055,
	GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER = 0x0057,
	GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO = 0x0058,
	GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN = 0x0059,
	GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON = 0x005A,
	GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON = 0x005B,
	GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON = 0x005C,
	GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON = 0x005D,
	GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON = 0x005E,
	GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON = 0x005F,
	GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON = 0x0060,
	GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON = 0x0061,
	GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME = 0x0062,
	GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE = 0x0063,
	GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU = 0x006C,
	GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON = 0x006D,
	GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON = 0x006E,
	GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON = 0x0054,
	GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE = 0x0056,
	GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE = 0x006F,
	GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE = 0x0070,
	GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE = 0x0071,
	GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE = 0x0072,
	GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE = 0x0073,
	GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON = 0x0074,
	GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM = 0x0023,
	GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT = 0x0024,
	GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE = 0x0066,
	GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE = 0x007B,
} gui_model_video_rec_msg_id_t;

extern int gui_model_video_rec_msg_cycrec_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_delayrec_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_car_nunber_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_reso_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_btn_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_remain_time_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_time_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_video_rec_menu_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_mic_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_guard_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_cyc_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_motion_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_gap_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hdr_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_gra_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_exp_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_car_num_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_flash_headlight_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_icon_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_key_state_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);

extern void gui_model_video_rec_msg_init(lv_ui *ui);
extern void gui_model_video_rec_msg_init_ui();
extern void gui_model_video_rec_msg_init_events();
extern void gui_model_video_rec_msg_unsubscribe();
extern gui_msg_status_t gui_model_video_rec_msg_send(int32_t msg_id, void * value, int32_t len);
extern gui_msg_data_t * gui_model_video_rec_msg_get(int32_t msg_id);
extern void gui_model_video_rec_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_VIDEO_REC_MSG_H_ */

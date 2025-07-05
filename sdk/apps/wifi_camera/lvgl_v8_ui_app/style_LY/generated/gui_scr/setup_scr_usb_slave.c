#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t * setup_scr_usb_slave(lv_ui *ui)
{
	//Write codes usb_slave
	ui->usb_slave = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for usb_slave. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->usb_slave, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->usb_slave, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->usb_slave, LV_SCROLLBAR_MODE_OFF);
	//Write codes usb_slave_img_icon_pccam
	ui->usb_slave_img_icon_pccam = lv_img_create(ui->usb_slave);
	lv_img_set_src(ui->usb_slave_img_icon_pccam, gui_get_res_path(GUI_RES_S_PC_PNG));
	lv_img_set_pivot(ui->usb_slave_img_icon_pccam, 0, 0);
	lv_img_set_angle(ui->usb_slave_img_icon_pccam, 0);
	lv_img_set_zoom(ui->usb_slave_img_icon_pccam, 256);

	//Set style for usb_slave_img_icon_pccam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->usb_slave_img_icon_pccam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->usb_slave_img_icon_pccam, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->usb_slave_img_icon_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave_img_icon_pccam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->usb_slave_img_icon_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->usb_slave_img_icon_pccam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->usb_slave_img_icon_pccam, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->usb_slave_img_icon_pccam, 298, 109);
	lv_obj_set_size(ui->usb_slave_img_icon_pccam, 200, 200);
	lv_obj_add_flag(ui->usb_slave_img_icon_pccam, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->usb_slave_img_icon_pccam, LV_OBJ_FLAG_CLICKABLE);
	//Write codes usb_slave_img_icon_masstorage
	ui->usb_slave_img_icon_masstorage = lv_img_create(ui->usb_slave);
	lv_img_set_src(ui->usb_slave_img_icon_masstorage, gui_get_res_path(GUI_RES_S_MASS_PNG));
	lv_img_set_pivot(ui->usb_slave_img_icon_masstorage, 0, 0);
	lv_img_set_angle(ui->usb_slave_img_icon_masstorage, 0);
	lv_img_set_zoom(ui->usb_slave_img_icon_masstorage, 256);

	//Set style for usb_slave_img_icon_masstorage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->usb_slave_img_icon_masstorage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->usb_slave_img_icon_masstorage, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->usb_slave_img_icon_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave_img_icon_masstorage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->usb_slave_img_icon_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->usb_slave_img_icon_masstorage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->usb_slave_img_icon_masstorage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->usb_slave_img_icon_masstorage, 298, 116);
	lv_obj_set_size(ui->usb_slave_img_icon_masstorage, 200, 200);
	lv_obj_add_flag(ui->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_CLICKABLE);
	//Write codes usb_slave_view_btnlist
	ui->usb_slave_view_btnlist = lv_obj_create(ui->usb_slave);

	//Set style for usb_slave_view_btnlist. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->usb_slave_view_btnlist, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->usb_slave_view_btnlist, 253, 99);
	lv_obj_set_size(ui->usb_slave_view_btnlist, 289, 234);
	lv_obj_set_scrollbar_mode(ui->usb_slave_view_btnlist, LV_SCROLLBAR_MODE_OFF);
	//Write codes usb_slave_btn_usb_msd
	ui->usb_slave_btn_usb_msd = lv_btn_create(ui->usb_slave_view_btnlist);

	const lv_font_t * usb_slave_btn_usb_msd_font = _font("msd");
	if(usb_slave_btn_usb_msd_font == NULL) usb_slave_btn_usb_msd_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for usb_slave_btn_usb_msd. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->usb_slave_btn_usb_msd, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->usb_slave_btn_usb_msd, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave_btn_usb_msd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->usb_slave_btn_usb_msd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->usb_slave_btn_usb_msd, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->usb_slave_btn_usb_msd, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->usb_slave_btn_usb_msd, usb_slave_btn_usb_msd_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->usb_slave_btn_usb_msd, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for usb_slave_btn_usb_msd. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->usb_slave_btn_usb_msd, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->usb_slave_btn_usb_msd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->usb_slave_btn_usb_msd, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->usb_slave_btn_usb_msd, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->usb_slave_btn_usb_msd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->usb_slave_btn_usb_msd, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->usb_slave_btn_usb_msd, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->usb_slave_btn_usb_msd, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->usb_slave_btn_usb_msd, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->usb_slave_btn_usb_msd, usb_slave_btn_usb_msd_font, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->usb_slave_btn_usb_msd, 27, 25);
	lv_obj_set_size(ui->usb_slave_btn_usb_msd, 236, 42);
	lv_obj_set_scrollbar_mode(ui->usb_slave_btn_usb_msd, LV_SCROLLBAR_MODE_OFF);
	ui->usb_slave_btn_usb_msd_label = lv_label_create(ui->usb_slave_btn_usb_msd);
	lv_label_set_text(ui->usb_slave_btn_usb_msd_label, _("msd"));
	lv_obj_set_style_pad_all(ui->usb_slave_btn_usb_msd, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->usb_slave_btn_usb_msd_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes usb_slave_btn_pc_cam
	ui->usb_slave_btn_pc_cam = lv_btn_create(ui->usb_slave_view_btnlist);

	const lv_font_t * usb_slave_btn_pc_cam_font = _font("pc_cam");
	if(usb_slave_btn_pc_cam_font == NULL) usb_slave_btn_pc_cam_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for usb_slave_btn_pc_cam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->usb_slave_btn_pc_cam, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->usb_slave_btn_pc_cam, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave_btn_pc_cam, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->usb_slave_btn_pc_cam, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->usb_slave_btn_pc_cam, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->usb_slave_btn_pc_cam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->usb_slave_btn_pc_cam, usb_slave_btn_pc_cam_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->usb_slave_btn_pc_cam, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for usb_slave_btn_pc_cam. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->usb_slave_btn_pc_cam, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->usb_slave_btn_pc_cam, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->usb_slave_btn_pc_cam, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->usb_slave_btn_pc_cam, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->usb_slave_btn_pc_cam, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->usb_slave_btn_pc_cam, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->usb_slave_btn_pc_cam, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->usb_slave_btn_pc_cam, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->usb_slave_btn_pc_cam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->usb_slave_btn_pc_cam, usb_slave_btn_pc_cam_font, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->usb_slave_btn_pc_cam, 26, 101);
	lv_obj_set_size(ui->usb_slave_btn_pc_cam, 236, 42);
	lv_obj_set_scrollbar_mode(ui->usb_slave_btn_pc_cam, LV_SCROLLBAR_MODE_OFF);
	ui->usb_slave_btn_pc_cam_label = lv_label_create(ui->usb_slave_btn_pc_cam);
	lv_label_set_text(ui->usb_slave_btn_pc_cam_label, _("pc_cam"));
	lv_obj_set_style_pad_all(ui->usb_slave_btn_pc_cam, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->usb_slave_btn_pc_cam_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes usb_slave_btn_video_rec
	ui->usb_slave_btn_video_rec = lv_btn_create(ui->usb_slave_view_btnlist);

	const lv_font_t * usb_slave_btn_video_rec_font = _font("video_rec");
	if(usb_slave_btn_video_rec_font == NULL) usb_slave_btn_video_rec_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for usb_slave_btn_video_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->usb_slave_btn_video_rec, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->usb_slave_btn_video_rec, lv_color_make(0xBD, 0xBD, 0xBD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->usb_slave_btn_video_rec, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->usb_slave_btn_video_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->usb_slave_btn_video_rec, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->usb_slave_btn_video_rec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->usb_slave_btn_video_rec, usb_slave_btn_video_rec_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->usb_slave_btn_video_rec, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for usb_slave_btn_video_rec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->usb_slave_btn_video_rec, 5, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->usb_slave_btn_video_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->usb_slave_btn_video_rec, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->usb_slave_btn_video_rec, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->usb_slave_btn_video_rec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->usb_slave_btn_video_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->usb_slave_btn_video_rec, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->usb_slave_btn_video_rec, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_color(ui->usb_slave_btn_video_rec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_text_font(ui->usb_slave_btn_video_rec, usb_slave_btn_video_rec_font, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->usb_slave_btn_video_rec, 26, 184);
	lv_obj_set_size(ui->usb_slave_btn_video_rec, 236, 42);
	lv_obj_set_scrollbar_mode(ui->usb_slave_btn_video_rec, LV_SCROLLBAR_MODE_OFF);
	ui->usb_slave_btn_video_rec_label = lv_label_create(ui->usb_slave_btn_video_rec);
	lv_label_set_text(ui->usb_slave_btn_video_rec_label, _("video_rec"));
	lv_obj_set_style_pad_all(ui->usb_slave_btn_video_rec, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->usb_slave_btn_video_rec_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_update_layout(ui->usb_slave);
	ui->usb_slave_del = false;

	//Init events for screen
	events_init_usb_slave(ui);
	return ui->usb_slave;
}
void unload_scr_usb_slave(lv_ui *ui)
{
	ui->usb_slave_del = true;
}

#endif

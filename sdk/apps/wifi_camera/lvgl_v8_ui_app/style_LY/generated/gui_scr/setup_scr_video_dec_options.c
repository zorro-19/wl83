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


lv_obj_t * setup_scr_video_dec_options(lv_ui *ui)
{
	if (lv_obj_is_valid(ui->video_dec_options)) {
		lv_obj_del(ui->video_dec_options);
	}
	//Write codes video_dec_options
	ui->video_dec_options = lv_obj_create(lv_layer_top());
	lv_group_t * def_group = lv_group_get_default();

	//Set style for video_dec_options. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_dec_options, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_options, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_options, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_size(ui->video_dec_options, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_dec_options, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui->video_dec_options, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_options_view_1
	ui->video_dec_options_view_1 = lv_obj_create(ui->video_dec_options);

	//Set style for video_dec_options_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_options_view_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_options_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_options_view_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_options_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_options_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_options_view_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_options_view_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_options_view_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_options_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_options_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_options_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_options_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_options_view_1, 199, 100);
	lv_obj_set_size(ui->video_dec_options_view_1, 390, 250);
	lv_obj_set_scrollbar_mode(ui->video_dec_options_view_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dec_options_lbl_1
	ui->video_dec_options_lbl_1 = lv_label_create(ui->video_dec_options_view_1);
	lv_label_set_text(ui->video_dec_options_lbl_1, _("del_file"));
	lv_label_set_long_mode(ui->video_dec_options_lbl_1, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_dec_options_lbl_1_font = _font("del_file");
	if(video_dec_options_lbl_1_font == NULL) video_dec_options_lbl_1_font = &lv_font_FangZhengKaiTiJianTi_1_16;

	//Set style for video_dec_options_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_options_lbl_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_options_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_options_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_options_lbl_1, video_dec_options_lbl_1_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_options_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_options_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_options_lbl_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_options_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_options_lbl_1, 15, 0);
	lv_obj_set_size(ui->video_dec_options_lbl_1, 360, 165);
	lv_obj_set_scrollbar_mode(ui->video_dec_options_lbl_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dec_options_btn_1
	ui->video_dec_options_btn_1 = lv_btn_create(ui->video_dec_options_view_1);

	const lv_font_t * video_dec_options_btn_1_font = _font("cancel");
	if(video_dec_options_btn_1_font == NULL) video_dec_options_btn_1_font = &lv_font_montserratMedium_16;

	//Set style for video_dec_options_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_options_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_options_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_options_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_options_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_options_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_options_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_options_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_options_btn_1, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_dec_options_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_dec_options_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_dec_options_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_dec_options_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_options_btn_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_options_btn_1, video_dec_options_btn_1_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_options_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_options_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_options_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->video_dec_options_btn_1, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->video_dec_options_btn_1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->video_dec_options_btn_1, 230, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->video_dec_options_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->video_dec_options_btn_1, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->video_dec_options_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->video_dec_options_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->video_dec_options_btn_1, 128, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->video_dec_options_btn_1, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->video_dec_options_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->video_dec_options_btn_1, video_dec_options_btn_1_font, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_pos(ui->video_dec_options_btn_1, 14, 132);
	lv_obj_set_size(ui->video_dec_options_btn_1, 181, 72);
	lv_obj_set_scrollbar_mode(ui->video_dec_options_btn_1, LV_SCROLLBAR_MODE_OFF);
	ui->video_dec_options_btn_1_label = lv_label_create(ui->video_dec_options_btn_1);
	lv_label_set_text(ui->video_dec_options_btn_1_label, _("cancel"));
	lv_obj_set_style_pad_all(ui->video_dec_options_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_dec_options_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes video_dec_options_btn_2
	ui->video_dec_options_btn_2 = lv_btn_create(ui->video_dec_options_view_1);

	const lv_font_t * video_dec_options_btn_2_font = _font("ensure");
	if(video_dec_options_btn_2_font == NULL) video_dec_options_btn_2_font = &lv_font_montserratMedium_16;

	//Set style for video_dec_options_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_options_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_options_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_options_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_options_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_options_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_options_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_options_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_options_btn_2, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_dec_options_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_dec_options_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_dec_options_btn_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_dec_options_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_options_btn_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_options_btn_2, video_dec_options_btn_2_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_options_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_options_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_options_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->video_dec_options_btn_2, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->video_dec_options_btn_2, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->video_dec_options_btn_2, 230, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->video_dec_options_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->video_dec_options_btn_2, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->video_dec_options_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->video_dec_options_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->video_dec_options_btn_2, 128, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->video_dec_options_btn_2, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->video_dec_options_btn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->video_dec_options_btn_2, video_dec_options_btn_2_font, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_pos(ui->video_dec_options_btn_2, 195, 132);
	lv_obj_set_size(ui->video_dec_options_btn_2, 181, 72);
	lv_obj_set_scrollbar_mode(ui->video_dec_options_btn_2, LV_SCROLLBAR_MODE_OFF);
	ui->video_dec_options_btn_2_label = lv_label_create(ui->video_dec_options_btn_2);
	lv_label_set_text(ui->video_dec_options_btn_2_label, _("ensure"));
	lv_obj_set_style_pad_all(ui->video_dec_options_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->video_dec_options_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_update_layout(ui->video_dec_options);
	ui->video_dec_options_del = false;

	//Init events for screen
	events_init_video_dec_options(ui);
	return ui->video_dec_options;
}
void unload_scr_video_dec_options(lv_ui *ui)
{
	ui->video_dec_options_del = true;
}

#endif

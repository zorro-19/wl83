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


lv_obj_t * setup_scr_line_drift(lv_ui *ui)
{
	//Write codes line_drift
	ui->line_drift = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for line_drift. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->line_drift, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->line_drift, LV_SCROLLBAR_MODE_OFF);
	//Write codes line_drift_lbl_3
	ui->line_drift_lbl_3 = lv_label_create(ui->line_drift);
	lv_label_set_text(ui->line_drift_lbl_3, "请移动至车头地平线");
	lv_label_set_long_mode(ui->line_drift_lbl_3, LV_LABEL_LONG_WRAP);

	//Set style for line_drift_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->line_drift_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift_lbl_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->line_drift_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->line_drift_lbl_3, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->line_drift_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->line_drift_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->line_drift_lbl_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->line_drift_lbl_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->line_drift_lbl_3, 50, 193);
	lv_obj_set_size(ui->line_drift_lbl_3, 190, 60);
	lv_obj_set_scrollbar_mode(ui->line_drift_lbl_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->line_drift_lbl_3, LV_OBJ_FLAG_HIDDEN);
	//Write codes line_drift_view_2
	ui->line_drift_view_2 = lv_obj_create(ui->line_drift);

	//Set style for line_drift_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->line_drift_view_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->line_drift_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->line_drift_view_2, 42, 395);
	lv_obj_set_size(ui->line_drift_view_2, 700, 60);
	lv_obj_set_scrollbar_mode(ui->line_drift_view_2, LV_SCROLLBAR_MODE_OFF);
	//Write codes line_drift_btn_horizon
	ui->line_drift_btn_horizon = lv_btn_create(ui->line_drift);

	const lv_font_t * line_drift_btn_horizon_font = _font("line_drift_horizon");
	if(line_drift_btn_horizon_font == NULL) line_drift_btn_horizon_font = &lv_font_FangZhengKaiTiJianTi_1_24;

	//Set style for line_drift_btn_horizon. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->line_drift_btn_horizon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->line_drift_btn_horizon, lv_color_make(0xD8, 0x3E, 0x74), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift_btn_horizon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->line_drift_btn_horizon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift_btn_horizon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->line_drift_btn_horizon, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->line_drift_btn_horizon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->line_drift_btn_horizon, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->line_drift_btn_horizon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->line_drift_btn_horizon, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->line_drift_btn_horizon, line_drift_btn_horizon_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->line_drift_btn_horizon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->line_drift_btn_horizon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->line_drift_btn_horizon, 60, 23);
	lv_obj_set_size(ui->line_drift_btn_horizon, 700, 16);
	lv_obj_set_scrollbar_mode(ui->line_drift_btn_horizon, LV_SCROLLBAR_MODE_OFF);
	ui->line_drift_btn_horizon_label = lv_label_create(ui->line_drift_btn_horizon);
	lv_label_set_text(ui->line_drift_btn_horizon_label, _("line_drift_horizon"));
	lv_obj_set_style_pad_all(ui->line_drift_btn_horizon, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->line_drift_btn_horizon_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes line_drift_btn_carhead
	ui->line_drift_btn_carhead = lv_btn_create(ui->line_drift);

	const lv_font_t * line_drift_btn_carhead_font = _font("line_drift_car");
	if(line_drift_btn_carhead_font == NULL) line_drift_btn_carhead_font = &lv_font_FangZhengKaiTiJianTi_1_24;

	//Set style for line_drift_btn_carhead. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->line_drift_btn_carhead, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->line_drift_btn_carhead, lv_color_make(0xD8, 0xC5, 0x3E), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift_btn_carhead, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->line_drift_btn_carhead, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift_btn_carhead, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->line_drift_btn_carhead, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->line_drift_btn_carhead, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->line_drift_btn_carhead, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->line_drift_btn_carhead, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->line_drift_btn_carhead, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->line_drift_btn_carhead, line_drift_btn_carhead_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->line_drift_btn_carhead, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->line_drift_btn_carhead, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->line_drift_btn_carhead, 60, 395);
	lv_obj_set_size(ui->line_drift_btn_carhead, 700, 16);
	lv_obj_set_scrollbar_mode(ui->line_drift_btn_carhead, LV_SCROLLBAR_MODE_OFF);
	ui->line_drift_btn_carhead_label = lv_label_create(ui->line_drift_btn_carhead);
	lv_label_set_text(ui->line_drift_btn_carhead_label, _("line_drift_car"));
	lv_obj_set_style_pad_all(ui->line_drift_btn_carhead, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->line_drift_btn_carhead_label, LV_ALIGN_CENTER, 0, 0);
	//Write codes line_drift_lbl_7
	ui->line_drift_lbl_7 = lv_label_create(ui->line_drift);
	lv_label_set_text(ui->line_drift_lbl_7, _("YES"));
	lv_label_set_long_mode(ui->line_drift_lbl_7, LV_LABEL_LONG_WRAP);

	const lv_font_t * line_drift_lbl_7_font = _font("YES");
	if(line_drift_lbl_7_font == NULL) line_drift_lbl_7_font = &lv_font_FangZhengKaiTiJianTi_1_16;

	//Set style for line_drift_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->line_drift_lbl_7, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->line_drift_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift_lbl_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->line_drift_lbl_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->line_drift_lbl_7, line_drift_lbl_7_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->line_drift_lbl_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->line_drift_lbl_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->line_drift_lbl_7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for line_drift_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->line_drift_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->line_drift_lbl_7, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->line_drift_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->line_drift_lbl_7, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->line_drift_lbl_7, 128, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->line_drift_lbl_7, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->line_drift_lbl_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->line_drift_lbl_7, line_drift_lbl_7_font, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_letter_space(ui->line_drift_lbl_7, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_line_space(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_align(ui->line_drift_lbl_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_left(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_right(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_top(ui->line_drift_lbl_7, 8, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_bottom(ui->line_drift_lbl_7, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_pos(ui->line_drift_lbl_7, 734, 166);
	lv_obj_set_size(ui->line_drift_lbl_7, 55, 34);
	lv_obj_set_scrollbar_mode(ui->line_drift_lbl_7, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->line_drift_lbl_7, LV_OBJ_FLAG_CLICKABLE);
	//Write codes line_drift_lbl_6
	ui->line_drift_lbl_6 = lv_label_create(ui->line_drift);
	lv_label_set_text(ui->line_drift_lbl_6, _("CANCEL"));
	lv_label_set_long_mode(ui->line_drift_lbl_6, LV_LABEL_LONG_WRAP);

	const lv_font_t * line_drift_lbl_6_font = _font("CANCEL");
	if(line_drift_lbl_6_font == NULL) line_drift_lbl_6_font = &lv_font_FangZhengKaiTiJianTi_1_16;

	//Set style for line_drift_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->line_drift_lbl_6, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->line_drift_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->line_drift_lbl_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->line_drift_lbl_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->line_drift_lbl_6, line_drift_lbl_6_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->line_drift_lbl_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->line_drift_lbl_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->line_drift_lbl_6, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for line_drift_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->line_drift_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->line_drift_lbl_6, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->line_drift_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->line_drift_lbl_6, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->line_drift_lbl_6, 128, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->line_drift_lbl_6, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->line_drift_lbl_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->line_drift_lbl_6, line_drift_lbl_6_font, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_letter_space(ui->line_drift_lbl_6, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_line_space(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_align(ui->line_drift_lbl_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_left(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_right(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_top(ui->line_drift_lbl_6, 8, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_bottom(ui->line_drift_lbl_6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_pos(ui->line_drift_lbl_6, 734, 229);
	lv_obj_set_size(ui->line_drift_lbl_6, 57, 35);
	lv_obj_set_scrollbar_mode(ui->line_drift_lbl_6, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->line_drift_lbl_6, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_update_layout(ui->line_drift);
	ui->line_drift_del = false;

	//Init events for screen
	events_init_line_drift(ui);
	return ui->line_drift;
}
void unload_scr_line_drift(lv_ui *ui)
{
	ui->line_drift_del = true;
}

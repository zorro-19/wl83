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


lv_obj_t * setup_scr_video_dir(lv_ui *ui)
{
	//Write codes video_dir
	ui->video_dir = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for video_dir. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_dir, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dir, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->video_dir, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dir_view_1
	ui->video_dir_view_1 = lv_obj_create(ui->video_dir);

	//Set style for video_dir_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dir_view_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dir_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dir_view_1, 0, 0);
	lv_obj_set_size(ui->video_dir_view_1, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_dir_view_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dir_lbl_path
	ui->video_dir_lbl_path = lv_label_create(ui->video_dir_view_1);
	lv_label_set_text(ui->video_dir_lbl_path, "storage/sd0/C/DCIM/");
	lv_label_set_long_mode(ui->video_dir_lbl_path, LV_LABEL_LONG_WRAP);

	//Set style for video_dir_lbl_path. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dir_lbl_path, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dir_lbl_path, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dir_lbl_path, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dir_lbl_path, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dir_lbl_path, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dir_lbl_path, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dir_lbl_path, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dir_lbl_path, 60, 10);
	lv_obj_set_size(ui->video_dir_lbl_path, 666, 38);
	lv_obj_set_scrollbar_mode(ui->video_dir_lbl_path, LV_SCROLLBAR_MODE_OFF);
	lv_obj_update_layout(ui->video_dir);
	ui->video_dir_del = false;

	//Init events for screen
	events_init_video_dir(ui);
	return ui->video_dir;
}
void unload_scr_video_dir(lv_ui *ui)
{
	ui->video_dir_del = true;
}

#endif

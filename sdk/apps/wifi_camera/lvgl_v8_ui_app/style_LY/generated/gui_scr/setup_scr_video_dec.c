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

static const char* video_dec_imglist_1_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
	"A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\import\\image\\LY_UI\\dec\\video.png",
	"A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\import\\image\\LY_UI\\dec\\photo.png"
#else
	"mnt/sdfile/EXT_RESERVED/uipackres/ui/55000051.zip",
	"mnt/sdfile/EXT_RESERVED/uipackres/ui/55000052.zip"
#endif
};
static const char* video_dec_imglist_2_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
	"A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png",
	"A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png"
#else
	"mnt/sdfile/EXT_RESERVED/uipackres/ui/55000053.zip",
	"mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000c.zip"
#endif
};
static const char* video_dec_imglist_3_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
	"A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\import\\image\\LY_UI\\dec\\play.png",
	"A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\import\\image\\LY_UI\\dec\\pause.png"
#else
	"mnt/sdfile/EXT_RESERVED/uipackres/ui/55000054.zip",
	"mnt/sdfile/EXT_RESERVED/uipackres/ui/55000055.zip"
#endif
};

lv_obj_t * setup_scr_video_dec(lv_ui *ui)
{
	//Write codes video_dec
	ui->video_dec = lv_obj_create(NULL);
	lv_group_t * def_group = lv_group_get_default();

	//Set style for video_dec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->video_dec, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->video_dec, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dec_view_scan
	ui->video_dec_view_scan = lv_obj_create(ui->video_dec);

	//Set style for video_dec_view_scan. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_view_scan, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_view_scan, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_view_scan, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_view_scan, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_scan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_view_scan, 0, 0);
	lv_obj_set_size(ui->video_dec_view_scan, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_dec_view_scan, LV_SCROLLBAR_MODE_OFF);
	lv_group_add_obj(def_group, ui->video_dec_view_scan);
	//Write codes video_dec_imglist_1
	ui->video_dec_imglist_1 = lv_imglist_create(ui->video_dec_view_scan);

	//Set style for video_dec_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_imglist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_imglist_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_imglist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_imglist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_imglist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_imglist_1, 12, 10);
	lv_obj_set_size(ui->video_dec_imglist_1, 30, 29);
	lv_obj_set_scrollbar_mode(ui->video_dec_imglist_1, LV_SCROLLBAR_MODE_OFF);
	lv_imglist_set_src(ui->video_dec_imglist_1, (const void **) video_dec_imglist_1_imgs, 2);
	lv_imglist_set_act(ui->video_dec_imglist_1, 0);
	//Write codes video_dec_edit_2
	ui->video_dec_edit_2 = lv_textarea_create(ui->video_dec_view_scan);

	//Set style for video_dec_edit_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_edit_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_edit_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_edit_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_edit_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_edit_2, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_edit_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_edit_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_edit_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_dec_edit_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_dec_edit_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_dec_edit_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_dec_edit_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_edit_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_edit_2, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_edit_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_edit_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_edit_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_edit_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_edit_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_edit_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_edit_2. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_edit_2, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_edit_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_edit_2, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_edit_2, 545, 24);
	lv_obj_set_size(ui->video_dec_edit_2, 282, 37);
	lv_obj_set_scrollbar_mode(ui->video_dec_edit_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_edit_2, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui->video_dec_edit_2, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_add_flag(ui->video_dec_edit_2, LV_OBJ_FLAG_CLICK_FOCUSABLE);
	lv_group_remove_obj(ui->video_dec_edit_2);
	lv_textarea_set_text(ui->video_dec_edit_2,"VID_0001.AVI");
	//Write codes video_dec_edit_3
	ui->video_dec_edit_3 = lv_textarea_create(ui->video_dec_view_scan);

	//Set style for video_dec_edit_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_edit_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_edit_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_edit_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_edit_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_edit_3, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_edit_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_edit_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_edit_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_dec_edit_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_dec_edit_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_dec_edit_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_dec_edit_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_edit_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_edit_3, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_edit_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_edit_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_edit_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_edit_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_edit_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_edit_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_edit_3. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_edit_3, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_edit_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_edit_3, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_edit_3, 545, 62);
	lv_obj_set_size(ui->video_dec_edit_3, 282, 36);
	lv_obj_set_scrollbar_mode(ui->video_dec_edit_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_edit_3, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_add_flag(ui->video_dec_edit_3, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui->video_dec_edit_3, LV_OBJ_FLAG_CLICK_FOCUSABLE);
	lv_group_remove_obj(ui->video_dec_edit_3);
	lv_textarea_set_text(ui->video_dec_edit_3,"720P");
	//Write codes video_dec_imglist_2
	ui->video_dec_imglist_2 = lv_imglist_create(ui->video_dec_view_scan);

	//Set style for video_dec_imglist_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_imglist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_imglist_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_imglist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_imglist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_imglist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_imglist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_imglist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_imglist_2, 738, 407);
	lv_obj_set_size(ui->video_dec_imglist_2, 29, 29);
	lv_obj_set_scrollbar_mode(ui->video_dec_imglist_2, LV_SCROLLBAR_MODE_OFF);
	lv_imglist_set_src(ui->video_dec_imglist_2, (const void **) video_dec_imglist_2_imgs, 2);
	lv_imglist_set_act(ui->video_dec_imglist_2, 0);
	//Write codes video_dec_view_1
	ui->video_dec_view_1 = lv_obj_create(ui->video_dec_view_scan);

	//Set style for video_dec_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_view_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_view_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_view_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_view_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_view_1, 1, 398);
	lv_obj_set_size(ui->video_dec_view_1, 468, 63);
	lv_obj_set_scrollbar_mode(ui->video_dec_view_1, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget video_dec_view_1
	lv_obj_add_flag(ui->video_dec_view_1, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_dec_imglist_3
	ui->video_dec_imglist_3 = lv_imglist_create(ui->video_dec_view_1);

	//Set style for video_dec_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_imglist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_imglist_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_imglist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_imglist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_imglist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_imglist_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_imglist_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_imglist_3, 93, 15);
	lv_obj_set_size(ui->video_dec_imglist_3, 24, 24);
	lv_obj_set_scrollbar_mode(ui->video_dec_imglist_3, LV_SCROLLBAR_MODE_OFF);
	lv_imglist_set_src(ui->video_dec_imglist_3, (const void **) video_dec_imglist_3_imgs, 2);
	lv_imglist_set_act(ui->video_dec_imglist_3, 0);
	//Write codes video_dec_edit_1
	ui->video_dec_edit_1 = lv_textarea_create(ui->video_dec_view_1);

	//Set style for video_dec_edit_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_edit_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_edit_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_edit_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_edit_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_edit_1, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_edit_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_edit_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_edit_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->video_dec_edit_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->video_dec_edit_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->video_dec_edit_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui->video_dec_edit_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_edit_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_edit_1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_edit_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_edit_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_edit_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_edit_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_edit_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_edit_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_edit_1. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_edit_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_edit_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_edit_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_edit_1, 124, 7);
	lv_obj_set_size(ui->video_dec_edit_1, 204, 40);
	lv_obj_set_scrollbar_mode(ui->video_dec_edit_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_edit_1, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_add_flag(ui->video_dec_edit_1, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui->video_dec_edit_1, LV_OBJ_FLAG_CLICK_FOCUSABLE);
	lv_group_remove_obj(ui->video_dec_edit_1);
	lv_textarea_set_text(ui->video_dec_edit_1,"00:00 / 03:00");
	//Write codes video_dec_img_1
	ui->video_dec_img_1 = lv_img_create(ui->video_dec_view_scan);
	lv_img_set_src(ui->video_dec_img_1, gui_get_res_path(GUI_RES_PROTECT_PNG));
	lv_img_set_pivot(ui->video_dec_img_1, 0, 0);
	lv_img_set_angle(ui->video_dec_img_1, 0);
	lv_img_set_zoom(ui->video_dec_img_1, 256);

	//Set style for video_dec_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_1, 74, 10);
	lv_obj_set_size(ui->video_dec_img_1, 29, 29);
	lv_obj_add_flag(ui->video_dec_img_1, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_dec_img_1
	lv_obj_add_flag(ui->video_dec_img_1, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_dec_view_5
	ui->video_dec_view_5 = lv_obj_create(ui->video_dec);

	//Set style for video_dec_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_view_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_view_5, 0, 0);
	lv_obj_set_size(ui->video_dec_view_5, 800, 480);
	lv_obj_set_scrollbar_mode(ui->video_dec_view_5, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_view_5, LV_OBJ_FLAG_HIDDEN);
	//Write codes video_dec_view_4
	ui->video_dec_view_4 = lv_obj_create(ui->video_dec_view_5);

	//Set style for video_dec_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_view_4, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_view_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->video_dec_view_4, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_view_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->video_dec_view_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_view_4, 0, 40);
	lv_obj_set_size(ui->video_dec_view_4, 800, 400);
	lv_obj_set_scrollbar_mode(ui->video_dec_view_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_view_4, LV_OBJ_FLAG_EVENT_BUBBLE);
	//Write codes video_dec_view_2
	ui->video_dec_view_2 = lv_obj_create(ui->video_dec_view_4);

	//Set style for video_dec_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_view_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_view_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_dec_view_2, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_dec_view_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_dec_view_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_dec_view_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_dec_view_2, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_dec_view_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_dec_view_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_dec_view_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_dec_view_2, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_dec_view_2, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_2, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_dec_view_2, 0, 0);
	lv_obj_set_size(ui->video_dec_view_2, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_dec_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_view_2, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_dec_view_2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_dec_view_2);
	//Write codes video_dec_img_2
	ui->video_dec_img_2 = lv_img_create(ui->video_dec_view_2);
	lv_img_set_src(ui->video_dec_img_2, gui_get_res_path(GUI_RES_DELET_PNG));
	lv_img_set_pivot(ui->video_dec_img_2, 0, 0);
	lv_img_set_angle(ui->video_dec_img_2, 0);
	lv_img_set_zoom(ui->video_dec_img_2, 256);

	//Set style for video_dec_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_2, 8, 6);
	lv_obj_set_size(ui->video_dec_img_2, 29, 29);
	lv_obj_add_flag(ui->video_dec_img_2, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_lbl_1
	ui->video_dec_lbl_1 = lv_label_create(ui->video_dec_view_2);
	lv_label_set_text(ui->video_dec_lbl_1, _("delete"));
	lv_label_set_long_mode(ui->video_dec_lbl_1, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_dec_lbl_1_font = _font("delete");
	if(video_dec_lbl_1_font == NULL) video_dec_lbl_1_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_dec_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_lbl_1, video_dec_lbl_1_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_lbl_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_lbl_1, 50, 6);
	lv_obj_set_size(ui->video_dec_lbl_1, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_dec_lbl_1, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dec_view_3
	ui->video_dec_view_3 = lv_obj_create(ui->video_dec_view_4);

	//Set style for video_dec_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for video_dec_view_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
	lv_obj_set_style_radius(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_color(ui->video_dec_view_3, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_bg_opa(ui->video_dec_view_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_shadow_width(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_color(ui->video_dec_view_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_width(ui->video_dec_view_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_opa(ui->video_dec_view_3, 255, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_border_side(ui->video_dec_view_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(ui->video_dec_view_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(ui->video_dec_view_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(ui->video_dec_view_3, 128, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(ui->video_dec_view_3, 2, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_left(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_right(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_top(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_style_pad_bottom(ui->video_dec_view_3, 0, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_obj_set_pos(ui->video_dec_view_3, 0, 45);
	lv_obj_set_size(ui->video_dec_view_3, 800, 43);
	lv_obj_set_scrollbar_mode(ui->video_dec_view_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->video_dec_view_3, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_add_flag(ui->video_dec_view_3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_group_add_obj(def_group, ui->video_dec_view_3);
	//Write codes video_dec_img_3
	ui->video_dec_img_3 = lv_img_create(ui->video_dec_view_3);
	lv_img_set_src(ui->video_dec_img_3, gui_get_res_path(GUI_RES_PROTECT_PNG));
	lv_img_set_pivot(ui->video_dec_img_3, 0, 0);
	lv_img_set_angle(ui->video_dec_img_3, 0);
	lv_img_set_zoom(ui->video_dec_img_3, 256);

	//Set style for video_dec_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_3, 8, 6);
	lv_obj_set_size(ui->video_dec_img_3, 29, 29);
	lv_obj_add_flag(ui->video_dec_img_3, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_lbl_2
	ui->video_dec_lbl_2 = lv_label_create(ui->video_dec_view_3);
	lv_label_set_text(ui->video_dec_lbl_2, _("protection"));
	lv_label_set_long_mode(ui->video_dec_lbl_2, LV_LABEL_LONG_WRAP);

	const lv_font_t * video_dec_lbl_2_font = _font("protection");
	if(video_dec_lbl_2_font == NULL) video_dec_lbl_2_font = &lv_font_FangZhengKaiTiJianTi_1_22;

	//Set style for video_dec_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->video_dec_lbl_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->video_dec_lbl_2, video_dec_lbl_2_font, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->video_dec_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->video_dec_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->video_dec_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->video_dec_lbl_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_lbl_2, 50, 6);
	lv_obj_set_size(ui->video_dec_lbl_2, 200, 32);
	lv_obj_set_scrollbar_mode(ui->video_dec_lbl_2, LV_SCROLLBAR_MODE_OFF);
	//Write codes video_dec_img_4
	ui->video_dec_img_4 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_4, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->video_dec_img_4, 0, 0);
	lv_img_set_angle(ui->video_dec_img_4, 0);
	lv_img_set_zoom(ui->video_dec_img_4, 256);

	//Set style for video_dec_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_4, 0, 0);
	lv_obj_set_size(ui->video_dec_img_4, 800, 40);
	lv_obj_add_flag(ui->video_dec_img_4, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_5
	ui->video_dec_img_5 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_5, gui_get_res_path(GUI_RES_MENU_STA_PNG));
	lv_img_set_pivot(ui->video_dec_img_5, 0, 0);
	lv_img_set_angle(ui->video_dec_img_5, 0);
	lv_img_set_zoom(ui->video_dec_img_5, 256);

	//Set style for video_dec_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_5, 0, 440);
	lv_obj_set_size(ui->video_dec_img_5, 800, 40);
	lv_obj_add_flag(ui->video_dec_img_5, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_6
	ui->video_dec_img_6 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_6, gui_get_res_path(GUI_RES_PLAY_PNG));
	lv_img_set_pivot(ui->video_dec_img_6, 0, 0);
	lv_img_set_angle(ui->video_dec_img_6, 0);
	lv_img_set_zoom(ui->video_dec_img_6, 256);

	//Set style for video_dec_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_6, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_6, 9, 0);
	lv_obj_set_size(ui->video_dec_img_6, 39, 39);
	lv_obj_add_flag(ui->video_dec_img_6, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_7
	ui->video_dec_img_7 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_7, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui->video_dec_img_7, 0, 0);
	lv_img_set_angle(ui->video_dec_img_7, 0);
	lv_img_set_zoom(ui->video_dec_img_7, 256);

	//Set style for video_dec_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_7, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_7, 70, 1);
	lv_obj_set_size(ui->video_dec_img_7, 37, 37);
	lv_obj_add_flag(ui->video_dec_img_7, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_8
	ui->video_dec_img_8 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_8, gui_get_res_path(GUI_RES_LEFT_PNG));
	lv_img_set_pivot(ui->video_dec_img_8, 0, 0);
	lv_img_set_angle(ui->video_dec_img_8, 0);
	lv_img_set_zoom(ui->video_dec_img_8, 256);

	//Set style for video_dec_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_8, 200, 445);
	lv_obj_set_size(ui->video_dec_img_8, 21, 29);
	lv_obj_add_flag(ui->video_dec_img_8, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_9
	ui->video_dec_img_9 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_9, gui_get_res_path(GUI_RES_UP_PNG));
	lv_img_set_pivot(ui->video_dec_img_9, 0, 0);
	lv_img_set_angle(ui->video_dec_img_9, 0);
	lv_img_set_zoom(ui->video_dec_img_9, 256);

	//Set style for video_dec_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_9, 321, 448);
	lv_obj_set_size(ui->video_dec_img_9, 29, 21);
	lv_obj_add_flag(ui->video_dec_img_9, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_10
	ui->video_dec_img_10 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_10, gui_get_res_path(GUI_RES_DOWN_PNG));
	lv_img_set_pivot(ui->video_dec_img_10, 0, 0);
	lv_img_set_angle(ui->video_dec_img_10, 0);
	lv_img_set_zoom(ui->video_dec_img_10, 256);

	//Set style for video_dec_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_10, 450, 448);
	lv_obj_set_size(ui->video_dec_img_10, 29, 21);
	lv_obj_add_flag(ui->video_dec_img_10, LV_OBJ_FLAG_CLICKABLE);
	//Write codes video_dec_img_11
	ui->video_dec_img_11 = lv_img_create(ui->video_dec_view_5);
	lv_img_set_src(ui->video_dec_img_11, gui_get_res_path(GUI_RES_RIGHT_PNG));
	lv_img_set_pivot(ui->video_dec_img_11, 0, 0);
	lv_img_set_angle(ui->video_dec_img_11, 0);
	lv_img_set_zoom(ui->video_dec_img_11, 256);

	//Set style for video_dec_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->video_dec_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->video_dec_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->video_dec_img_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->video_dec_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->video_dec_img_11, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->video_dec_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->video_dec_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->video_dec_img_11, 579, 445);
	lv_obj_set_size(ui->video_dec_img_11, 21, 29);
	lv_obj_add_flag(ui->video_dec_img_11, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_update_layout(ui->video_dec);
	ui->video_dec_del = false;

	//Init events for screen
	events_init_video_dec(ui);
	return ui->video_dec;
}
void unload_scr_video_dec(lv_ui *ui)
{
	ui->video_dec_del = true;
}

#endif

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


lv_obj_t * setup_scr_car_parking(lv_ui *ui)
{
	if (lv_obj_is_valid(ui->car_parking)) {
		lv_obj_del(ui->car_parking);
	}
	//Write codes car_parking
	ui->car_parking = lv_obj_create(lv_layer_top());
	lv_group_t * def_group = lv_group_get_default();

	//Set style for car_parking. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->car_parking, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->car_parking, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->car_parking, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_size(ui->car_parking, 800, 480);
	lv_obj_set_scrollbar_mode(ui->car_parking, LV_SCROLLBAR_MODE_OFF);
	//Write codes car_parking_img_1
	ui->car_parking_img_1 = lv_img_create(ui->car_parking);
	lv_img_set_src(ui->car_parking_img_1, gui_get_res_path(GUI_RES_ASTERN_PNG));
	lv_img_set_pivot(ui->car_parking_img_1, 0, 0);
	lv_img_set_angle(ui->car_parking_img_1, 0);
	lv_img_set_zoom(ui->car_parking_img_1, 256);

	//Set style for car_parking_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->car_parking_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_clip_corner(ui->car_parking_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->car_parking_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->car_parking_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->car_parking_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->car_parking_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->car_parking_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->car_parking_img_1, 109, 309);
	lv_obj_set_size(ui->car_parking_img_1, 550, 167);
	lv_obj_add_flag(ui->car_parking_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_update_layout(ui->car_parking);
	ui->car_parking_del = false;
	return ui->car_parking;
}
void unload_scr_car_parking(lv_ui *ui)
{
	ui->car_parking_del = true;
}

#endif

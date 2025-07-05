/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_camera(lv_ui *ui)
{
    //Write codes camera
    ui->camera = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for camera. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->camera, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->camera, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->camera, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->camera, LV_SCROLLBAR_MODE_OFF);
    //Write codes camera_title
    ui->camera_title = lv_label_create(ui->camera);
    lv_label_set_text(ui->camera_title, "Camera");
    lv_label_set_long_mode(ui->camera_title, LV_LABEL_LONG_WRAP);

    //Set style for camera_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->camera_title, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera_title, lv_color_make(0xF0, 0x92, 0xB5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_title, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->camera_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera_title, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->camera_title, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_title, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_title, &lv_font_montserratMedium_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->camera_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera_title, 0, 0);
    lv_obj_set_size(ui->camera_title, 481, 85);
    lv_obj_set_scrollbar_mode(ui->camera_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes camera_back_btn
    ui->camera_back_btn = lv_btn_create(ui->camera);

    //Set style for camera_back_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->camera_back_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->camera_back_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera_back_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->camera_back_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->camera_back_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->camera_back_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->camera_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->camera_back_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->camera_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_back_btn, lv_color_make(0x0A, 0x0A, 0x0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_back_btn, &lv_font_FontAwesome5_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_back_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera_back_btn, 5, 10);
    lv_obj_set_size(ui->camera_back_btn, 101, 43);
    lv_obj_set_scrollbar_mode(ui->camera_back_btn, LV_SCROLLBAR_MODE_OFF);
    ui->camera_back_btn_label = lv_label_create(ui->camera_back_btn);
    lv_label_set_text(ui->camera_back_btn_label, "BACK ");
    lv_obj_set_style_pad_all(ui->camera_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->camera_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes camera_camera1_btn
    ui->camera_camera1_btn = lv_btn_create(ui->camera);

    //Set style for camera_camera1_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->camera_camera1_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera_camera1_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_camera1_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_camera1_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->camera_camera1_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera_camera1_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->camera_camera1_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->camera_camera1_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->camera_camera1_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->camera_camera1_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->camera_camera1_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->camera_camera1_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_camera1_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_camera1_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_camera1_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_camera1_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera_camera1_btn, 140, 159);
    lv_obj_set_size(ui->camera_camera1_btn, 200, 100);
    lv_obj_set_scrollbar_mode(ui->camera_camera1_btn, LV_SCROLLBAR_MODE_OFF);
    ui->camera_camera1_btn_label = lv_label_create(ui->camera_camera1_btn);
    lv_label_set_text(ui->camera_camera1_btn_label, "Camera1(MIPI)");
    lv_obj_set_style_pad_all(ui->camera_camera1_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->camera_camera1_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes camera_camera2_btn
    ui->camera_camera2_btn = lv_btn_create(ui->camera);

    //Set style for camera_camera2_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->camera_camera2_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera_camera2_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_camera2_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_camera2_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->camera_camera2_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera_camera2_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->camera_camera2_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->camera_camera2_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->camera_camera2_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->camera_camera2_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->camera_camera2_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->camera_camera2_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_camera2_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_camera2_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_camera2_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_camera2_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera_camera2_btn, 140, 312);
    lv_obj_set_size(ui->camera_camera2_btn, 200, 100);
    lv_obj_set_scrollbar_mode(ui->camera_camera2_btn, LV_SCROLLBAR_MODE_OFF);
    ui->camera_camera2_btn_label = lv_label_create(ui->camera_camera2_btn);
    lv_label_set_text(ui->camera_camera2_btn_label, "Camera2(DVP)");
    lv_obj_set_style_pad_all(ui->camera_camera2_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->camera_camera2_btn_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes camera_camera3_btn
    ui->camera_camera3_btn = lv_btn_create(ui->camera);

    //Set style for camera_camera3_btn. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->camera_camera3_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera_camera3_btn, lv_color_make(0x1E, 0x83, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_camera3_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_camera3_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->camera_camera3_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera_camera3_btn, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->camera_camera3_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->camera_camera3_btn, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->camera_camera3_btn, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->camera_camera3_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->camera_camera3_btn, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->camera_camera3_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_camera3_btn, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_camera3_btn, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_camera3_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_camera3_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera_camera3_btn, 140, 460);
    lv_obj_set_size(ui->camera_camera3_btn, 200, 98);
    lv_obj_set_scrollbar_mode(ui->camera_camera3_btn, LV_SCROLLBAR_MODE_OFF);
    ui->camera_camera3_btn_label = lv_label_create(ui->camera_camera3_btn);
    lv_label_set_text(ui->camera_camera3_btn_label, "Camera3(DVP)");
    lv_obj_set_style_pad_all(ui->camera_camera3_btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->camera_camera3_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->camera);
    ui->camera_del = false;

    //Init events for screen
    events_init_camera(ui);
    return ui->camera;
}
void unload_scr_camera(lv_ui *ui)
{
    ui->camera_del = true;
}

/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_camera1_mipi(lv_ui *ui)
{
    //Write codes camera1_mipi
    ui->camera1_mipi = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for camera1_mipi. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->camera1_mipi, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera1_mipi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera1_mipi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->camera1_mipi, LV_SCROLLBAR_MODE_OFF);
    //Write codes camera1_mipi_title
    ui->camera1_mipi_title = lv_label_create(ui->camera1_mipi);
    lv_label_set_text(ui->camera1_mipi_title, "CAM1(MIPI)\n\nClick the screen to exit");
    lv_label_set_long_mode(ui->camera1_mipi_title, LV_LABEL_LONG_WRAP);

    //Set style for camera1_mipi_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera1_mipi_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera1_mipi_title, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera1_mipi_title, &lv_font_montserratMedium_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera1_mipi_title, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera1_mipi_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->camera1_mipi_title, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->camera1_mipi_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera1_mipi_title, 35, 0);
    lv_obj_set_size(ui->camera1_mipi_title, 411, 182);
    lv_obj_set_scrollbar_mode(ui->camera1_mipi_title, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->camera1_mipi);
    ui->camera1_mipi_del = false;

    //Init events for screen
    events_init_camera1_mipi(ui);
    return ui->camera1_mipi;
}
void unload_scr_camera1_mipi(lv_ui *ui)
{
    ui->camera1_mipi_del = true;
}

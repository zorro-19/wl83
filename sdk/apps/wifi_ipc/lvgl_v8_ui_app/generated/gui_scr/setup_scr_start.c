/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"


lv_obj_t *setup_scr_start(lv_ui *ui)
{
    //Write codes start
    ui->start = lv_obj_create(NULL);

    //Set style for start. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->start, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->start, lv_color_make(0xFF, 0x6A, 0x6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->start, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->start, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->start, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->start, LV_SCROLLBAR_MODE_OFF);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes start_img_logo
    ui->start_img_logo = lv_img_create(ui->start);

    //Set style for start_img_logo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->start_img_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->start_img_logo, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->start_img_logo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->start_img_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->start_img_logo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->start_img_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->start_img_logo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->start_img_logo, 74, 312);
    lv_obj_set_size(ui->start_img_logo, 332, 82);
    lv_obj_set_scrollbar_mode(ui->start_img_logo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->start_img_logo, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->start_img_logo, LV_OBJ_FLAG_CLICKABLE);
    //Effect fadeIn fade_in_up
    lv_anim_effect_args_t start_img_logo_effect_args;
    start_img_logo_effect_args.delay = 0;
    start_img_logo_effect_args.duration = 2000;
    lv_anim_effect_fade_in_up(ui->start_img_logo, &start_img_logo_effect_args);
    lv_img_set_src(ui->start_img_logo, &_img_logo_alpha_332x82);
    lv_img_set_pivot(ui->start_img_logo, 0, 0);
    lv_img_set_angle(ui->start_img_logo, 0);
    lv_img_set_zoom(ui->start_img_logo, 256);
    lv_obj_update_layout(ui->start);
    ui->start_del = false;

    //Init events for screen
    events_init_start(ui);
    return ui->start;
}
void unload_scr_start(lv_ui *ui)
{
    ui->start_del = true;
}

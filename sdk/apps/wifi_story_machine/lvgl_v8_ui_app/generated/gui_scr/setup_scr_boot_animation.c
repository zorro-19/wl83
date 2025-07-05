/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_boot_animation(lv_ui *ui)
{
    //Write codes boot_animation
    ui->boot_animation = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for boot_animation. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->boot_animation, lv_color_make(0xF7, 0x98, 0xB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->boot_animation, lv_color_make(0xD6, 0x78, 0x78), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->boot_animation, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->boot_animation, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->boot_animation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->boot_animation, LV_SCROLLBAR_MODE_OFF);
    //Write codes boot_animation_jl_logo
    ui->boot_animation_jl_logo = lv_img_create(ui->boot_animation);

    //Set style for boot_animation_jl_logo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->boot_animation_jl_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->boot_animation_jl_logo, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->boot_animation_jl_logo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->boot_animation_jl_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->boot_animation_jl_logo, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->boot_animation_jl_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->boot_animation_jl_logo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->boot_animation_jl_logo, 75, 361);
    lv_obj_set_size(ui->boot_animation_jl_logo, 332, 82);
    lv_obj_set_scrollbar_mode(ui->boot_animation_jl_logo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->boot_animation_jl_logo, LV_OBJ_FLAG_CLICKABLE);
    //Effect fadeIn fade_in_up
    lv_anim_effect_args_t boot_animation_jl_logo_effect_args;
    boot_animation_jl_logo_effect_args.delay = 0;
    boot_animation_jl_logo_effect_args.duration = 1000;
    lv_anim_effect_fade_in_up(ui->boot_animation_jl_logo, &boot_animation_jl_logo_effect_args);
    lv_img_set_src(ui->boot_animation_jl_logo, &_img_logo_alpha332x82);
    lv_img_set_pivot(ui->boot_animation_jl_logo, 0, 0);
    lv_img_set_angle(ui->boot_animation_jl_logo, 0);
    lv_img_set_zoom(ui->boot_animation_jl_logo, 256);
    lv_obj_update_layout(ui->boot_animation);
    ui->boot_animation_del = false;

    //Init events for screen
    events_init_boot_animation(ui);
    return ui->boot_animation;
}
void unload_scr_boot_animation(lv_ui *ui)
{
    ui->boot_animation_del = true;
}

/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"


lv_obj_t *setup_scr_app(lv_ui *ui)
{
    //Write codes app
    ui->app = lv_obj_create(NULL);

    //Set style for app. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->app, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->app, lv_color_make(0xFF, 0x6A, 0x6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->app, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->app, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->app, LV_SCROLLBAR_MODE_OFF);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes app_btn_return
    ui->app_btn_return = lv_btn_create(ui->app);

    const lv_font_t *app_btn_return_font = _font("return_app");
    if (app_btn_return_font == NULL) {
        app_btn_return_font = &lv_font_FangZhengKaiTiJianTi_1_32;
    }

    //Set style for app_btn_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->app_btn_return, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->app_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->app_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->app_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->app_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->app_btn_return, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->app_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_btn_return, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_btn_return, app_btn_return_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_btn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_btn_return, 11, 20);
    lv_obj_set_size(ui->app_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui->app_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->app_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->app_btn_return_label = lv_label_create(ui->app_btn_return);
    lv_label_set_text(ui->app_btn_return_label, _("return_app"));
    lv_obj_set_style_pad_all(ui->app_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->app_btn_return_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes app_img_qrcode
    ui->app_img_qrcode = lv_img_create(ui->app);

    //Set style for app_img_qrcode. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->app_img_qrcode, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_img_qrcode, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->app_img_qrcode, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_img_qrcode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->app_img_qrcode, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->app_img_qrcode, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->app_img_qrcode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_img_qrcode, 108, 282);
    lv_obj_set_size(ui->app_img_qrcode, 264, 267);
    lv_obj_set_scrollbar_mode(ui->app_img_qrcode, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->app_img_qrcode, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->app_img_qrcode, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_code.png");
#else
    lv_img_set_src(ui->app_img_qrcode, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000015.rle");
#endif
    lv_img_set_pivot(ui->app_img_qrcode, 0, 0);
    lv_img_set_angle(ui->app_img_qrcode, 0);
    lv_img_set_zoom(ui->app_img_qrcode, 256);
    lv_obj_update_layout(ui->app);
    ui->app_del = false;

    //Init events for screen
    events_init_app(ui);
    return ui->app;
}
void unload_scr_app(lv_ui *ui)
{
    ui->app_del = true;
}

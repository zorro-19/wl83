/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "callback_handler.h"
#include "gui_timelines.h"
#include "custom.h"


lv_obj_t *setup_scr_sysinfo(lv_ui *ui)
{
    //Write codes sysinfo
    ui->sysinfo = lv_obj_create(NULL);

    //Set style for sysinfo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->sysinfo, lv_color_make(0x02, 0x9A, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->sysinfo, lv_color_make(0xFF, 0x6A, 0x6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->sysinfo, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sysinfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sysinfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->sysinfo, LV_SCROLLBAR_MODE_OFF);
    lv_group_t *def_group = lv_group_get_default();
    //Write codes sysinfo_img_info
    ui->sysinfo_img_info = lv_img_create(ui->sysinfo);

    //Set style for sysinfo_img_info. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sysinfo_img_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->sysinfo_img_info, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sysinfo_img_info, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sysinfo_img_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->sysinfo_img_info, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->sysinfo_img_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->sysinfo_img_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sysinfo_img_info, 114, 218);
    lv_obj_set_size(ui->sysinfo_img_info, 258, 258);
    lv_obj_set_scrollbar_mode(ui->sysinfo_img_info, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sysinfo_img_info, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->sysinfo_img_info, "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\qrcode.png");
#else
    lv_img_set_src(ui->sysinfo_img_info, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000016.rle");
#endif
    lv_img_set_pivot(ui->sysinfo_img_info, 0, 0);
    lv_img_set_angle(ui->sysinfo_img_info, 0);
    lv_img_set_zoom(ui->sysinfo_img_info, 256);
    //Write codes sysinfo_btn_return
    ui->sysinfo_btn_return = lv_btn_create(ui->sysinfo);

    const lv_font_t *sysinfo_btn_return_font = _font("return_sysinfo");
    if (sysinfo_btn_return_font == NULL) {
        sysinfo_btn_return_font = &lv_font_FangZhengKaiTiJianTi_1_32;
    }

    //Set style for sysinfo_btn_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sysinfo_btn_return, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sysinfo_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sysinfo_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sysinfo_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sysinfo_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->sysinfo_btn_return, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->sysinfo_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sysinfo_btn_return, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->sysinfo_btn_return, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sysinfo_btn_return, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sysinfo_btn_return, sysinfo_btn_return_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sysinfo_btn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sysinfo_btn_return, 11, 20);
    lv_obj_set_size(ui->sysinfo_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui->sysinfo_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sysinfo_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sysinfo_btn_return_label = lv_label_create(ui->sysinfo_btn_return);
    lv_label_set_text(ui->sysinfo_btn_return_label, _("return_sysinfo"));
    lv_obj_set_style_pad_all(ui->sysinfo_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sysinfo_btn_return_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->sysinfo);
    ui->sysinfo_del = false;

    //Init events for screen
    events_init_sysinfo(ui);
    return ui->sysinfo;
}
void unload_scr_sysinfo(lv_ui *ui)
{
    ui->sysinfo_del = true;
}

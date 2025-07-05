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


lv_obj_t *setup_scr_pairing(lv_ui *ui)
{
    lv_ui_pairing *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAIRING);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_pairing));
        memset(ui_scr, 0, sizeof(lv_ui_pairing));
        ui->pairing = ui_scr;
    }
    //Write codes pairing
    ui_scr->pairing = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for pairing. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pairing, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->pairing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->pairing, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->pairing);
    //Write codes pairing_lbl_1
    ui_scr->pairing_lbl_1 = lv_label_create(ui_scr->pairing);
    lv_label_set_text(ui_scr->pairing_lbl_1, "Pairing...\n\nPlease press the pairing button of the camera and Make sure the camera is within 30cm");
    lv_label_set_long_mode(ui_scr->pairing_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for pairing_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->pairing_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->pairing_lbl_1, &lv_font_montserratMedium_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_scr->pairing_lbl_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->pairing_lbl_1, 4, 150);
    lv_obj_set_size(ui_scr->pairing_lbl_1, 788, 269);
    lv_obj_set_scrollbar_mode(ui_scr->pairing_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui_scr->pairing);
    ui_scr->pairing_del = false;

    //Init events for screen
    events_init_pairing(ui);
    return ui_scr->pairing;
}
void unload_scr_pairing(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_PAIRING);
}

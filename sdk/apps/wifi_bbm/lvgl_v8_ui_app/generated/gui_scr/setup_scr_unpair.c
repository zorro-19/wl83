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


lv_obj_t *setup_scr_unpair(lv_ui *ui)
{
    lv_ui_unpair *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_UNPAIR);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_unpair));
        memset(ui_scr, 0, sizeof(lv_ui_unpair));
        ui->unpair = ui_scr;
    }
    //Write codes unpair
    ui_scr->unpair = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for unpair. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->unpair, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->unpair, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui_scr->unpair, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->unpair);
    //Write codes unpair_lbl_1
    ui_scr->unpair_lbl_1 = lv_label_create(ui_scr->unpair);
    lv_label_set_text(ui_scr->unpair_lbl_1, "Unpair success ! \n\nPlease click to return");
    lv_label_set_long_mode(ui_scr->unpair_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for unpair_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui_scr->unpair_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->unpair_lbl_1, &lv_font_montserratMedium_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_scr->unpair_lbl_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->unpair_lbl_1, 6, 150);
    lv_obj_set_size(ui_scr->unpair_lbl_1, 788, 269);
    lv_obj_set_scrollbar_mode(ui_scr->unpair_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui_scr->unpair);
    ui_scr->unpair_del = false;

    //Init events for screen
    events_init_unpair(ui);
    return ui_scr->unpair;
}
void unload_scr_unpair(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_UNPAIR);
}

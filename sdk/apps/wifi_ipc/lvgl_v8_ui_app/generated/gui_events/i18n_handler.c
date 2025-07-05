/*Generate Code, Do NOT Edit!*/
#include "i18n_handler.h"

void i18n_refresh_texts(const char *page_name)
{
    if (page_name == NULL) {
        return;
    }

    if (strcmp(page_name, "start") == 0 && !guider_ui.start_del) {

    }

    if (strcmp(page_name, "home") == 0 && !guider_ui.home_del) {
        if (guider_ui.home_lbl_note != NULL && lv_obj_is_valid(guider_ui.home_lbl_note)) {
            lv_label_set_text(guider_ui.home_lbl_note, _("ScanCode"));
            const lv_font_t *font = _font("ScanCode");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.home_lbl_note, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (strcmp(page_name, "menu") == 0 && !guider_ui.menu_del) {
        if (guider_ui.menu_edit_return != NULL && lv_obj_is_valid(guider_ui.menu_edit_return)) {
            lv_textarea_set_text(guider_ui.menu_edit_return, _("back"));
            const lv_font_t *font = _font("back");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_return, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_download != NULL && lv_obj_is_valid(guider_ui.menu_edit_download)) {
            lv_textarea_set_text(guider_ui.menu_edit_download, _("app"));
            const lv_font_t *font = _font("app");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_download, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_netcfg != NULL && lv_obj_is_valid(guider_ui.menu_edit_netcfg)) {
            lv_textarea_set_text(guider_ui.menu_edit_netcfg, _("netcfg"));
            const lv_font_t *font = _font("netcfg");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_netcfg, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_language != NULL && lv_obj_is_valid(guider_ui.menu_edit_language)) {
            lv_textarea_set_text(guider_ui.menu_edit_language, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_language, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_sysset != NULL && lv_obj_is_valid(guider_ui.menu_edit_sysset)) {
            lv_textarea_set_text(guider_ui.menu_edit_sysset, _("syscfg"));
            const lv_font_t *font = _font("syscfg");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_sysset, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_sysinfo != NULL && lv_obj_is_valid(guider_ui.menu_edit_sysinfo)) {
            lv_textarea_set_text(guider_ui.menu_edit_sysinfo, _("sysinfo"));
            const lv_font_t *font = _font("sysinfo");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_sysinfo, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (strcmp(page_name, "language") == 0 && !guider_ui.language_del) {
        if (guider_ui.language_btn_return_label != NULL && lv_obj_is_valid(guider_ui.language_btn_return_label)) {
            lv_label_set_text(guider_ui.language_btn_return_label, _("return_language"));
            const lv_font_t *font = _font("return_language");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.language_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (strcmp(page_name, "app") == 0 && !guider_ui.app_del) {
        if (guider_ui.app_btn_return_label != NULL && lv_obj_is_valid(guider_ui.app_btn_return_label)) {
            lv_label_set_text(guider_ui.app_btn_return_label, _("return_app"));
            const lv_font_t *font = _font("return_app");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.app_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (strcmp(page_name, "syscfg") == 0 && !guider_ui.syscfg_del) {
        if (guider_ui.syscfg_btn_return_label != NULL && lv_obj_is_valid(guider_ui.syscfg_btn_return_label)) {
            lv_label_set_text(guider_ui.syscfg_btn_return_label, _("return_sysset"));
            const lv_font_t *font = _font("return_sysset");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.syscfg_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (strcmp(page_name, "sysinfo") == 0 && !guider_ui.sysinfo_del) {
        if (guider_ui.sysinfo_btn_return_label != NULL && lv_obj_is_valid(guider_ui.sysinfo_btn_return_label)) {
            lv_label_set_text(guider_ui.sysinfo_btn_return_label, _("return_sysinfo"));
            const lv_font_t *font = _font("return_sysinfo");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.sysinfo_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }
}

void i18n_refresh_all_texts()
{
    if (!guider_ui.start_del) {

    }

    if (!guider_ui.home_del) {
        if (guider_ui.home_lbl_note != NULL && lv_obj_is_valid(guider_ui.home_lbl_note)) {
            lv_label_set_text(guider_ui.home_lbl_note, _("ScanCode"));
            const lv_font_t *font = _font("ScanCode");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.home_lbl_note, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (!guider_ui.menu_del) {
        if (guider_ui.menu_edit_return != NULL && lv_obj_is_valid(guider_ui.menu_edit_return)) {
            lv_textarea_set_text(guider_ui.menu_edit_return, _("back"));
            const lv_font_t *font = _font("back");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_return, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_download != NULL && lv_obj_is_valid(guider_ui.menu_edit_download)) {
            lv_textarea_set_text(guider_ui.menu_edit_download, _("app"));
            const lv_font_t *font = _font("app");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_download, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_netcfg != NULL && lv_obj_is_valid(guider_ui.menu_edit_netcfg)) {
            lv_textarea_set_text(guider_ui.menu_edit_netcfg, _("netcfg"));
            const lv_font_t *font = _font("netcfg");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_netcfg, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_language != NULL && lv_obj_is_valid(guider_ui.menu_edit_language)) {
            lv_textarea_set_text(guider_ui.menu_edit_language, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_language, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_sysset != NULL && lv_obj_is_valid(guider_ui.menu_edit_sysset)) {
            lv_textarea_set_text(guider_ui.menu_edit_sysset, _("syscfg"));
            const lv_font_t *font = _font("syscfg");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_sysset, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (guider_ui.menu_edit_sysinfo != NULL && lv_obj_is_valid(guider_ui.menu_edit_sysinfo)) {
            lv_textarea_set_text(guider_ui.menu_edit_sysinfo, _("sysinfo"));
            const lv_font_t *font = _font("sysinfo");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.menu_edit_sysinfo, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (!guider_ui.language_del) {
        if (guider_ui.language_btn_return_label != NULL && lv_obj_is_valid(guider_ui.language_btn_return_label)) {
            lv_label_set_text(guider_ui.language_btn_return_label, _("return_language"));
            const lv_font_t *font = _font("return_language");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.language_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (!guider_ui.app_del) {
        if (guider_ui.app_btn_return_label != NULL && lv_obj_is_valid(guider_ui.app_btn_return_label)) {
            lv_label_set_text(guider_ui.app_btn_return_label, _("return_app"));
            const lv_font_t *font = _font("return_app");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.app_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (!guider_ui.syscfg_del) {
        if (guider_ui.syscfg_btn_return_label != NULL && lv_obj_is_valid(guider_ui.syscfg_btn_return_label)) {
            lv_label_set_text(guider_ui.syscfg_btn_return_label, _("return_sysset"));
            const lv_font_t *font = _font("return_sysset");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.syscfg_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }

    if (!guider_ui.sysinfo_del) {
        if (guider_ui.sysinfo_btn_return_label != NULL && lv_obj_is_valid(guider_ui.sysinfo_btn_return_label)) {
            lv_label_set_text(guider_ui.sysinfo_btn_return_label, _("return_sysinfo"));
            const lv_font_t *font = _font("return_sysinfo");
            if (font != NULL) {
                lv_obj_set_style_text_font(guider_ui.sysinfo_btn_return_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }
}

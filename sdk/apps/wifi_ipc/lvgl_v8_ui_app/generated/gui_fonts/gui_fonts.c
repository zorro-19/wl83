#include "lvgl.h"
#include <stdio.h>
#include "gui_fonts.h"

lv_font_t lv_font_montserratMedium_22;
void lv_font_montserratMedium_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000000.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
    }
}
lv_font_t lv_font_simsun_22;
void lv_font_simsun_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000001.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_simsun_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_32;
void lv_font_montserratMedium_32_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000002.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_32 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
void lv_font_FangZhengKaiTiJianTi_1_32_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000003.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_32 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_20;
void lv_font_FangZhengKaiTiJianTi_1_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000004.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
void lv_font_FangZhengKaiTiJianTi_1_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000005.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
void lv_font_FangZhengKaiTiJianTi_1_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000006.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
    }
}

void init_gui_fonts()
{
    lv_font_montserratMedium_22_file();
    lv_font_simsun_22_file();
    lv_font_montserratMedium_32_file();
    lv_font_FangZhengKaiTiJianTi_1_32_file();
    lv_font_FangZhengKaiTiJianTi_1_20_file();
    lv_font_FangZhengKaiTiJianTi_1_18_file();
    lv_font_FangZhengKaiTiJianTi_1_22_file();
}
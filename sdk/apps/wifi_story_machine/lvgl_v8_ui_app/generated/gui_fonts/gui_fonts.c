#include "lvgl.h"
#include <stdio.h>
#include "./gui_fonts.h"

lv_font_t lv_font_montserratMedium_48;
void lv_font_montserratMedium_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000000.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
    }
}
lv_font_t lv_font_FontAwesome5_24;
void lv_font_FontAwesome5_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000001.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FontAwesome5_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_24;
void lv_font_montserratMedium_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000002.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
    }
}
lv_font_t lv_font_FontAwesome5_40;
void lv_font_FontAwesome5_40_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000003.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FontAwesome5_40 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_40;
void lv_font_montserratMedium_40_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000004.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_40 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_30;
void lv_font_montserratMedium_30_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000005.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_30 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_12;
void lv_font_montserratMedium_12_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000006.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_12 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
    }
}
lv_font_t lv_font_FontAwesome5_18;
void lv_font_FontAwesome5_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000007.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000007.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FontAwesome5_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000007.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000007.rle");
#endif
    }
}
lv_font_t lv_font_Merge_fonts_24;
void lv_font_Merge_fonts_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000008.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000008.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_Merge_fonts_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000008.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000008.rle");
#endif
    }
}

void init_gui_fonts()
{
    lv_font_montserratMedium_48_file();
    lv_font_FontAwesome5_24_file();
    lv_font_montserratMedium_24_file();
    lv_font_FontAwesome5_40_file();
    lv_font_montserratMedium_40_file();
    lv_font_montserratMedium_30_file();
    lv_font_montserratMedium_12_file();
    lv_font_FontAwesome5_18_file();
    lv_font_Merge_fonts_24_file();
}
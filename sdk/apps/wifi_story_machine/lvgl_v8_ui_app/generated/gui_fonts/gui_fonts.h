#ifndef GUIDER_FONTS_H
#define GUIDER_FONTS_H
#ifdef __cplusplus
extern "C" {
#endif

#if LVGL_VERSION_MAJOR == 7
#include "lv_font/lv_font.h"
#else
#include "src/font/lv_font.h"
#endif

extern lv_font_t lv_font_montserratMedium_48;
extern lv_font_t lv_font_FontAwesome5_24;
extern lv_font_t lv_font_montserratMedium_24;
extern lv_font_t lv_font_FontAwesome5_40;
extern lv_font_t lv_font_montserratMedium_40;
extern lv_font_t lv_font_montserratMedium_30;
extern lv_font_t lv_font_montserratMedium_12;
extern lv_font_t lv_font_FontAwesome5_18;
extern lv_font_t lv_font_Merge_fonts_24;

void init_gui_fonts();

#ifdef __cplusplus
}
#endif
#endif
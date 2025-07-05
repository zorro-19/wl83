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

LV_FONT_DECLARE(lv_font_montserratMedium_12);
LV_FONT_DECLARE(lv_font_montserratMedium_16);
LV_FONT_DECLARE(lv_font_montserratMedium_20);
LV_FONT_DECLARE(lv_font_montserratMedium_24);
LV_FONT_DECLARE(lv_font_montserratMedium_36);
LV_FONT_DECLARE(lv_font_montserratMedium_32);

void init_gui_fonts();

#ifdef __cplusplus
}
#endif
#endif
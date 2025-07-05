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

extern lv_font_t lv_font_montserratMedium_22;
extern lv_font_t lv_font_simsun_22;
extern lv_font_t lv_font_montserratMedium_32;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_20;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;

void init_gui_fonts();

#ifdef __cplusplus
}
#endif
#endif
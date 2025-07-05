#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"

lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
void lv_font_FangZhengKaiTiJianTi_1_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000000.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_22 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000000.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
void lv_font_FangZhengKaiTiJianTi_1_26_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000001.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_26 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000001.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
void lv_font_FangZhengKaiTiJianTi_1_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000002.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_18 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000002.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
  }
}
lv_font_t lv_font_montserratMedium_18;
void lv_font_montserratMedium_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000003.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_montserratMedium_18 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000003.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
void lv_font_FangZhengKaiTiJianTi_1_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000004.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_48 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000004.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
  }
}
lv_font_t lv_font_montserratMedium_24;
void lv_font_montserratMedium_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000005.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_montserratMedium_24 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000005.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
  }
}
lv_font_t lv_font_montserratMedium_12;
void lv_font_montserratMedium_12_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000006.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_montserratMedium_12 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000006.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
  }
}
lv_font_t lv_font_montserratMedium_22;
void lv_font_montserratMedium_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000007.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000007.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_montserratMedium_22 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000007.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000007.rle");
#endif
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
void lv_font_FangZhengKaiTiJianTi_1_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000008.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000008.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_24 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000008.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000008.rle");
#endif
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
void lv_font_FangZhengKaiTiJianTi_1_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000009.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000009.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_16 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\10000009.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000009.rle");
#endif
  }
}
lv_font_t lv_font_montserratMedium_16;
void lv_font_montserratMedium_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\1000000a.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000a.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_montserratMedium_16 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\1000000a.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000a.rle");
#endif
  }
}
lv_font_t lv_font_montserratMedium_20;
void lv_font_montserratMedium_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_t * fnt_font = lv_font_load_bin("A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\1000000b.rle");
#else
  lv_font_t * fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000b.rle");
#endif
  if (fnt_font != NULL) {
    lv_font_montserratMedium_20 = *fnt_font;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\WL83\\jxc\\2.2.2\\fw-AC792_SDK\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\rle\\font\\1000000b.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000b.rle");
#endif
  }
}

void init_gui_fonts()
{
  lv_font_FangZhengKaiTiJianTi_1_22_file();
  lv_font_FangZhengKaiTiJianTi_1_26_file();
  lv_font_FangZhengKaiTiJianTi_1_18_file();
  lv_font_montserratMedium_18_file();
  lv_font_FangZhengKaiTiJianTi_1_48_file();
  lv_font_montserratMedium_24_file();
  lv_font_montserratMedium_12_file();
  lv_font_montserratMedium_22_file();
  lv_font_FangZhengKaiTiJianTi_1_24_file();
  lv_font_FangZhengKaiTiJianTi_1_16_file();
  lv_font_montserratMedium_16_file();
  lv_font_montserratMedium_20_file();
}
/*Generate Code, Do NOT Edit!*/
#ifndef __RES_COMMON_H__
#define __RES_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_USE_GUIBUILDER_SIMULATOR
#define GUI_WEAKREF __attribute__((weakref))
#define GUI_WEAK __attribute__((weak))
#else
#define GUI_WEAKREF
#define GUI_WEAK __attribute__((weak))
#endif

typedef enum {
    GUI_RES_MONTSERRATMEDIUM_48_TTF = 0x10000000,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000000.rle
    GUI_RES_FONTAWESOME5_24_TTF = 0x10000001,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000001.rle
    GUI_RES_MONTSERRATMEDIUM_24_TTF = 0x10000002,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000002.rle
    GUI_RES_FONTAWESOME5_40_TTF = 0x10000003,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000003.rle
    GUI_RES_MONTSERRATMEDIUM_40_TTF = 0x10000004,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000004.rle
    GUI_RES_MONTSERRATMEDIUM_30_TTF = 0x10000005,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000005.rle
    GUI_RES_MONTSERRATMEDIUM_12_TTF = 0x10000006,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000006.rle
    GUI_RES_FONTAWESOME5_18_TTF = 0x10000007,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000007.rle
    GUI_RES_MERGE_FONTS_24_TTF = 0x10000008,   //F:\WL83\ui_prj\wifi_story_machine_480x800\ui_res\rle\font\10000008.rle
} GUI_RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

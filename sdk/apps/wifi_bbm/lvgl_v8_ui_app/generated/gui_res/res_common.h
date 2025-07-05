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

#define CONV_RES_ID(id) (((id) >> 24) | ((id) & 0x00FFFFFF) << 8)
typedef enum {
    GUI_RES_CAMERA_PNG = 0x4B000000,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\camera.png
    GUI_RES_LINK_PNG = 0x4B000001,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\link.png
    GUI_RES_DIR_PNG = 0x4B000002,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\dir.png
    GUI_RES_UNPAIR_PNG = 0x4B000003,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\unpair.png
    GUI_RES_PAIRED_PNG = 0x4B000004,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\paired.png
    GUI_RES_BACK_PNG = 0x4B000005,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\back.png
    GUI_RES_SWITCH_PNG = 0x4B000006,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\switch.png
    GUI_RES_UP_PNG = 0x4B000007,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\up.png
    GUI_RES_DOWN_PNG = 0x4B000008,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\down.png
    GUI_RES_DELETE_PNG = 0x4B000009,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\delete.png
    GUI_RES_PAIR_OPT_PAIR_PNG = 0x4B00000A,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\pair_opt_pair.png
    GUI_RES_PAIR_OPT_UNPAIR_PNG = 0x4B00000B,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\pair_opt_unpair.png
    GUI_RES_BACK_WHITE_PNG = 0x4B00000C,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\back_white.png
    GUI_RES_VIDEO_PLAY_PNG = 0x4B00000D,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\video_play.png
    GUI_RES_VIDEO_PAUSE_PNG = 0x4B00000E,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\video_pause.png
    GUI_RES_SKIP_NEXT_PNG = 0x4B00000F,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\skip_next.png
    GUI_RES_SKIP_PREVIOUS_PNG = 0x4B000010,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\skip_previous.png
    GUI_RES_WARN_PNG = 0x4B000011,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\warn.png
    GUI_RES_REMOTE_PNG = 0x4B000012,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_800x480\import\image\remote.png
} GUI_RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

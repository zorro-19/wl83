/*Generate Code, Do NOT Edit!*/
#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "./gui_res/res_common.h"

#define GUI_UIT_VERSION_MAJOR 1
#define GUI_UIT_VERSION_MINOR 0
#define GUI_UIT_VERSION_PATCH 0
#define GUI_UIT_VERSION_INFO "20241111"

#define GUI_CORE_VERSION_MAJOR 2
#define GUI_CORE_VERSION_MINOR 1
#define GUI_CORE_VERSION_PATCH 0
#define GUI_CORE_VERSION_INFO "GENERIC(with tools)"

typedef enum {
    GUI_SCREEN_ACTION_LOAD = 0,
    GUI_SCREEN_ACTION_UNLOAD
} gui_screen_action_t;

typedef enum {
    GUI_SCREEN_AUDIO = 0,
    GUI_SCREEN_CAMERA,
    GUI_SCREEN_BOOT_ANIMATION,
    GUI_SCREEN_HOME,
    GUI_SCREEN_KEY,
    GUI_SCREEN_CAMERA1_MIPI,
    GUI_SCREEN_AUDIO_LOCAL_MUSIC,
    GUI_SCREEN_AUDIO_RECORDER,
    GUI_SCREEN_AUDIO_NET_MUSIC,
    GUI_SCREEN_WIFI,
    GUI_SCREEN_AUDIO_BT_MUSIC,
    GUI_SCREEN_BLUETOOTH,
    GUI_SCREEN_CAMERA2_DVP,
    GUI_SCREEN_CAMERA3_DVP,
    GUI_SCREEN_SDCARD,
} gui_screen_id_t;

#define GUI_KEY_KEY222 222

#ifdef __cplusplus
}
#endif
#endif

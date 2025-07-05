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
#define GUI_UIT_VERSION_INFO "20250331"

#define GUI_CORE_VERSION_MAJOR 2
#define GUI_CORE_VERSION_MINOR 2
#define GUI_CORE_VERSION_PATCH 4
#define GUI_CORE_VERSION_INFO "GENERIC(with tools)"

#define GUI_TEMPLATE_VERSION_MAJOR 0
#define GUI_TEMPLATE_VERSION_MINOR 0
#define GUI_TEMPLATE_VERSION_PATCH 1
#define GUI_TEMPLATE_VERSION_INFO "empty480x800"

typedef enum {
    GUI_SCREEN_ACTION_LOAD = 0,
    GUI_SCREEN_ACTION_UNLOAD
} gui_screen_action_t;

typedef enum {
    GUI_SCREEN_HOME = 0,
    GUI_SCREEN_PAIR_STATUS,
    GUI_SCREEN_RT_STREAM,
    GUI_SCREEN_FILE_BROWSER,
    GUI_SCREEN_PAIR_OPTIONS,
    GUI_SCREEN_PAIRING,
    GUI_SCREEN_UNPAIR,
    GUI_SCREEN_VIDEO_PLAY,
    GUI_SCREEN_SYS_PROMPT,
    GUI_SCREEN_DIR_SELECT,
    GUI_SCREEN_DEVICE_SELECT,
    GUI_SCREEN_SYS_OPTIONS,
} gui_screen_id_t;


#ifdef __cplusplus
}
#endif
#endif

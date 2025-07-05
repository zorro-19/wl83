/*Generate Code, Do NOT Edit!*/
#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "res_common.h"

#define GUI_UIT_VERSION_MAJOR 1
#define GUI_UIT_VERSION_MINOR 0
#define GUI_UIT_VERSION_PATCH 0
#define GUI_UIT_VERSION_INFO "20240708"

#define GUI_CORE_VERSION_MAJOR 1
#define GUI_CORE_VERSION_MINOR 1
#define GUI_CORE_VERSION_PATCH 2
#define GUI_CORE_VERSION_INFO "GENERIC(with tools)"

typedef enum {
    GUI_SCREEN_ACTION_LOAD = 0,
    GUI_SCREEN_ACTION_UNLOAD
} gui_screen_action_t;

typedef enum {
    GUI_SCREEN_START = 0,
    GUI_SCREEN_HOME,
    GUI_SCREEN_MENU,
    GUI_SCREEN_LANGUAGE,
    GUI_SCREEN_APP,
    GUI_SCREEN_SYSCFG,
    GUI_SCREEN_SYSINFO,
} gui_screen_id_t;

#define GUI_KEY_Call 201
#define GUI_KEY_MicroPhone 202
#define GUI_KEY_Text 203
#define GUI_KEY_CallDown 204
#define GUI_KEY_Mute 205
#define GUI_KEY_LoudSpeak 206
#define GUI_KEY_PreItem 207
#define GUI_KEY_NextItem 208
#define GUI_KEY_Select 209

#ifdef __cplusplus
}
#endif
#endif

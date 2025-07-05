#ifndef _TUYA_AUDIO__H
#define _TUYA_AUDIO__H

#include "tuya_cloud_types.h"
#include "system/includes.h"
#include "server/audio_server.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    APP_LOCAL_PROMPT_NULL = 0,
    /*01*/    APP_LOCAL_PROMPT_DOOR_CALL = 1,           //敲门声
    /****/    APP_LOCAL_PROMPT_NUMM,
} APP_LOCAL_PROMPT_TYPE_E;

struct music_dec_ops {
    int (*switch_dir)(int fsel_mode);
    int (*switch_file)(int fsel_mode);
    int (*dec_file)(void *file, int, void *, int);
    int (*dec_play_pause)(char notify);
    int (*dec_breakpoint)(int);
    int (*dec_stop)(int);
    int (*dec_volume)(int);
    int (*dec_progress)(int);
    int (*dec_seek)(int);
    int (*dec_status)(int);
};

typedef struct  {

    UCHAR_T mode;
    UCHAR_T last_mode;
    UCHAR_T play_voice_prompt;
    APP_LOCAL_PROMPT_TYPE_E  prompt_type;
    CHAR_T volume;
    FILE *file;
    struct server *dec_server;
    const struct music_dec_ops *dec_ops;
} TY_HW_LOCAL_HDL;

#ifdef __cplusplus
}
#endif

#endif
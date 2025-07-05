#include "app_config.h"
#include "gui_guider.h"
#include "server/audio_server.h"
#include "server/server_core.h"
#include "syscfg/syscfg_id.h"
#include "system/app_core.h"
#include "event/key_event.h"
#include "fs/fs.h"

#define LOG_TAG             "[AUDIO_MODE]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"
lv_ui guider_ui;
void jl_gui_init(void)
{
    setup_ui(&guider_ui);
    events_init(&guider_ui);
}


static void dec_server_event_handler(void *priv, int argc, int *argv)
{
    union audio_req r = {0};

    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
        log_info("tone: AUDIO_SERVER_EVENT_ERR");
    case AUDIO_SERVER_EVENT_END:
        log_info("tone: AUDIO_SERVER_EVENT_END");
        r.dec.cmd = AUDIO_DEC_STOP;
        server_request(priv, AUDIO_REQ_DEC, &r);
        server_close(priv); //priv是server_register_event_handler_to_task的priv参数
        fclose((FILE *)argv[1]); //argv[1]是解码开始时传递进去的文件句柄
        key_event_enable();
        break;
    case AUDIO_SERVER_EVENT_CURR_TIME:
        log_info("play_time: %d", argv[1]);
        break;
    default:
        break;
    }
}


//播放提示音
int app_play_tone_file(const char *tonename)
{
    int err = 0;
    union audio_req req = {0};
    char path[64];

    sprintf(path, "%s%s", CONFIG_VOICE_PROMPT_FILE_PATH, tonename);
    log_info("play tone file : %s", path);

    key_event_disable();


    FILE *file = fopen(path, "r");
    if (!file) {
        printf("[chili] %s %d   \n",  __func__, __LINE__);
        return -1;
    }

    void *dec_server = server_open("audio_server", "dec");
    if (!dec_server) {
        goto __err;
    }
    server_register_event_handler_to_task(dec_server, dec_server, dec_server_event_handler, "app_core");

    req.dec.cmd             = AUDIO_DEC_OPEN;

    req.dec.output_buf_len  = 4 * 1024;
    req.dec.file            = file;
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;

    syscfg_read(CFG_MUSIC_VOL, &req.dec.volume, sizeof(req.dec.volume));
    printf("[chili] %s %d  req.dec.volume:%d \n",  __func__, __LINE__, req.dec.volume);
    req.dec.volume          = 100;
    err = server_request(dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;

    err = server_request(dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }



    return 0;

__err:

    if (dec_server) {
        server_close(dec_server);
    }
    if (file) {
        fclose(file);
    }

    return err;
}


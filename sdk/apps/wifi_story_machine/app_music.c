#include "app_music.h"
#include "system/includes.h"
#include "server/audio_server.h"
#include "server/server_core.h"
#include "app_config.h"
#include "action.h"
#include "storage_device.h"
#include "reverb_deal.h"
#include "fm/fm_manage.h"
#include "app_power_manage.h"
#include "syscfg/syscfg_id.h"
#include "character_coding.h"
#include "asm/rf_coexistence_config.h"
#include "generic/circular_buf.h"
#include "media/audio_effect.h"

#if (!defined CONFIG_DUI_SDK_ENABLE) && (!defined CONFIG_TVS_SDK_ENABLE)

#ifdef CONFIG_NET_ENABLE
#include "network_download/net_download.h"
#include "server/ai_server.h"
#include "lwip/netdb.h"
#include "net/assign_macaddr.h"
#include "net/config_network.h"
#endif

#include "event/key_event.h"
#include "event/net_event.h"
#include "event/bt_event.h"
#include "event/device_event.h"
#include "database.h"
#include "asm/eq.h"
#include "syscfg/syscfg_id.h"
#ifdef CONFIG_BT_ENABLE
#include "btstack/avctp_user.h"
#include "btctrler/btctrler_task.h"
#include "classic/hci_lmp.h"
#include "bt_ble/bt_emitter.h"

extern const struct music_dec_ops *get_bt_music_dec_ops(void);
extern void bt_connection_disable(void);
extern void bt_connection_enable(void);
extern void bt_delete_power_off_timer(void);
extern int get_a2dp_drop_frame_timer(void);
extern int app_music_bt_event_handler(struct sys_event *event);
extern void low_power_hw_unsleep_lock(void);
extern void low_power_hw_unsleep_unlock(void);
#endif

enum {
    LISTEN_STATE_STOP = 0,
    LISTEN_STATE_STOPPING,
    LISTEN_STATE_START,
    LISTEN_STATE_WAKEUP,
};

struct __wechat_url {
    struct list_head entry;
    void *url;
};

/* #define CONFIG_HOLD_SEND_VOICE */
#define CONFIG_PLAY_PROMPT_DISABLE_KEY	1 //播放提示音时屏蔽按键
#define CONFIG_STORE_VOLUME
#define VOLUME_STEP 5
#define MIN_VOLUME_VALUE	5
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE   60

#if defined CONFIG_NO_SDRAM_ENABLE
#define DEC_BUF_LEN      6 * 1024
#else
#define DEC_BUF_LEN      12 * 1024
#endif


#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
extern void lfs_sdram_prompt_init();
extern void lfs_sdram_prompt_load(char *path, char *name);
extern int lfs_sdram_prompt_check(char *fname);
extern void *lfs_sdram_prompt_open(char *fname);
extern void lfs_sdram_prompt_close(void *lfs_file);
void sdram_prompt_load(char *fname);
#endif


static struct app_music_hdl music_handler;

#define __this 	(&music_handler)

static void app_music_play_mode_switch_notify(void);
static int app_music_switch_local_device(const char *path);
static int app_music_play_voice_prompt(const char *fname, void *dec_end_handler);
extern int fs_update_check(const char *path);
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
extern void set_user_virtual_play_hdl(void *virtual);
extern void *get_user_virtual_audio_server(void);
extern int check_user_virtual_audio_if_running(void);
#endif

static const struct music_dec_ops local_music_dec_ops;

static const struct {
    APP_LOCAL_PROMPT_TYPE_E prompt_type;
    const char *file_name;
} local_prompt_table[] = {
    {APP_LOCAL_PROMPT_POWER_ON,                "PowerOn.mp3"},
    {APP_LOCAL_PROMPT_POWER_OFF,               "PowerOff.mp3"},
    {APP_LOCAL_PROMPT_PLAY_DOMAIN_MUSIC,       "004.mp3"},
    {APP_LOCAL_PROMPT_PLAY_DOMAIN_STORY,       "005.mp3"},
    {APP_LOCAL_PROMPT_PLAY_DOMAIN_SINOLOGY,    "006.mp3"},
    {APP_LOCAL_PROMPT_PLAY_DOMAIN_ENGLISH,     "007.mp3"},
    {APP_LOCAL_PROMPT_BT_OPEN,                 "BtOpen.mp3"},
    {APP_LOCAL_PROMPT_BT_CLOSE,                "BtClose.mp3"},
    {APP_LOCAL_PROMPT_BT_CONNECTED,            "BtSucceed.mp3"},
    {APP_LOCAL_PROMPT_BT_DISCONNECT,           "BtDisc.mp3"},
    {APP_LOCAL_PROMPT_WIFI_CONNECTING,         "NetConnting.mp3"},
    {APP_LOCAL_PROMPT_WIFI_CONNECT_SUCCESS,    "NetCfgSucc.mp3"},
    {APP_LOCAL_PROMPT_WIFI_CONNECT_FAIL,       "NetCfgFail.mp3"},
    {APP_LOCAL_PROMPT_WIFI_DISCONNECT,         "NetDisc.mp3"},
    {APP_LOCAL_PROMPT_WIFI_CONFIG_START,       "NetCfgEnter.mp3"},
    {APP_LOCAL_PROMPT_WIFI_CONFIG_INFO_RECV,   "SsidRecv.mp3"},
    {APP_LOCAL_PROMPT_WIFI_FIRST_CONFIG,       "NetEmpty.mp3"},
    {APP_LOCAL_PROMPT_WIFI_CONFIG_TIMEOUT,     "NetCfgTo.mp3"},
    {APP_LOCAL_PROMPT_LIGHT_OPEN,              "LightOpen.mp3"},
    {APP_LOCAL_PROMPT_LIGHT_CLOSE,             "LightClose.mp3"},
    {APP_LOCAL_PROMPT_AI_ASR_FAIL,             "AiAsrFail.mp3"},
    {APP_LOCAL_PROMPT_AI_TRANSLATE_FAIL,       "AiTransFail.mp3"},
    {APP_LOCAL_PROMPT_AI_PICTURE_FAIL,         "AiPicFail.mp3"},
    {APP_LOCAL_PROMPT_SEND_MESSAGE_FAIL,       "SendMsgFail.mp3"},
    {APP_LOCAL_PROMPT_RECV_NEW_MESSAGE,        "RecvNewMsg.mp3"},
    {APP_LOCAL_PROMPT_MESSAGE_TOO_SHORT,       "MsgTooShort.mp3"},
    {APP_LOCAL_PROMPT_MESSAGE_EMPTY,           "MsgEmpty.mp3"},
    {APP_LOCAL_PROMPT_LOW_BATTERY_LEVEL,       "LowBatLevel.mp3"},
    {APP_LOCAL_PROMPT_LOW_BATTERY_SHUTDOWN,    "LowBatOff.mp3"},
    {APP_LOCAL_PROMPT_ENTER_AI_TRANSLATE_MODE, "AiTransMode.mp3"},
    {APP_LOCAL_PROMPT_ENTER_AI_ASR_MODE,       "AiAsrMode.mp3"},
    {APP_LOCAL_PROMPT_ENTER_AI_PICTURE_MODE,   "PicModeIn.mp3"},
    {APP_LOCAL_PROMPT_EXIT_AI_PICTURE_MODE,    "PicModeOut.mp3"},
    {APP_LOCAL_PROMPT_PICTURE_RECOGNIZE_FAIL,  "PicRecgFail.mp3"},
    {APP_LOCAL_PROMPT_SERVER_CONNECTED,        "SerConnect.mp3"},
    {APP_LOCAL_PROMPT_SERVER_DISCONNECT,       "SerDiscon.mp3"},
    {APP_LOCAL_PROMPT_ASR_EMPTY,               "AsrEmpty.mp3"},
    {APP_LOCAL_PROMPT_KWS_ENABLE,              "KwsEnable.mp3"},
    {APP_LOCAL_PROMPT_KWS_DISABLE,             "KwsDisable.mp3"},
    {APP_LOCAL_PROMPT_REVERB_ENABLE,           "ReverbEnter.mp3"},
    {APP_LOCAL_PROMPT_REVERB_DISABLE,          "ReverbExit.mp3"},
    {APP_LOCAL_PROMPT_ENTER_NETWORK_MODE,      "NetMusic.mp3"},
    {APP_LOCAL_PROMPT_ENTER_FLASH_MUSIC_MODE,  "FlashMusic.mp3"},
    {APP_LOCAL_PROMPT_ENTER_SDCARD_MUSIC_MODE, "SDcardMusic.mp3"},
    {APP_LOCAL_PROMPT_ENTER_UDISK_MUSIC_MODE,  "UdiskMusic.mp3"},
    {APP_LOCAL_PROMPT_ENTER_FM_MUSIC_MODE,     "FMMusic.mp3"},
    {APP_LOCAL_PROMPT_PHONE_RING,              "ring.mp3"},
    {APP_LOCAL_PROMPT_AI_LISTEN_START,         "rec.mp3"},
    {APP_LOCAL_PROMPT_AI_LISTEN_STOP,          "send.mp3"},
    {APP_LOCAL_PROMPT_VOLUME_SET,              "Volume.mp3"},
    {APP_LOCAL_PROMPT_VOLUME_FULL,             "VolumeFull.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_BIND_SUCCESS,     "BindSucc.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_BIND_FAIL,        "BindFail.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_UNBIND_DEFAULT,   "UnbindDef.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_UNBIND_SUCCESS,   "UnbindSucc.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_UNBIND_FAIL,      "UnbindFail.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_INFO_RESTORE,     "Restore.mp3"},
    {APP_LOCAL_PROMPT_DEVICE_RESTART,          "Restart.mp3"},
    {APP_LOCAL_PROMPT_OTA_UPGRADE_START,       "OtaInUpdate.mp3"},
    {APP_LOCAL_PROMPT_OTA_UPGRADE_SUCCESS,     "OtaSuccess.mp3"},
    {APP_LOCAL_PROMPT_OTA_UPGRADE_FAIL,        "OtaFailed.mp3"},
    {APP_LOCAL_PROMPT_ALARM,                   "reminder.mp3"},
    {APP_LOCAL_PROMPT_SCHEDULE,                "schedule.mp3"},
    {APP_LOCAL_PROMPT_ENTER_AUX_MUSIC_MODE,    "LineinMusic.mp3"},
    {APP_LOCAL_PROMPT_ENTER_BT_EMITTER_MODE,   "EmitterOn.mp3"},
    {APP_LOCAL_PROMPT_EXIT_BT_EMITTER_MODE,    "EmitterOff.mp3"},
};

static const u8 dir_name_chars[][8] = {
    { 0x3F, 0x51, 0x4C, 0x6B, 0x00, 0x00 },   //儿歌
    { 0x45, 0x65, 0x8B, 0x4E, 0x00, 0x00 },   //故事
    { 0xFD, 0x56, 0x66, 0x5B, 0x00, 0x00 },   //国学
    { 0xF1, 0x82, 0xED, 0x8B, 0x00, 0x00 },   //英语
};

static const char *dir_name_chars_english[] = {
    "CHILD",  //儿歌
    "STORY",     //故事
    "CHINESE",   //国学
    "ENGLISH",   //英语
};

static const char *voice_prompt_file[] = {
    "004.mp3",      //儿歌
    "005.mp3",      //故事
    "006.mp3",      //国学
    "007.mp3",      //英语
};

#ifdef CONFIG_ASR_ALGORITHM
extern int aisp_open(u16 sample_rate);
extern void aisp_suspend(void);
extern void aisp_resume(void);
#endif

static const char *find_local_prompt_filename(APP_LOCAL_PROMPT_TYPE_E prompt_type)
{
    for (int i = 0; i < ARRAY_SIZE(local_prompt_table); ++i) {
        if (local_prompt_table[i].prompt_type == prompt_type) {
            return local_prompt_table[i].file_name;
        }
    }

    return NULL;
}

static int app_music_shutdown(int priv)
{
    sys_power_poweroff();
    return 0;
}

static void led_ui_post_msg(const char *msg, ...)
{
#ifdef CONFIG_LED_UI_ENABLE
    union led_uireq req;
    va_list argptr;

    if (__this->play_voice_prompt) {
        return;
    }

    va_start(argptr, msg);

    if (__this->led_ui) {
        req.msg.receiver = "gr202_led";
        req.msg.msg = msg;
        req.msg.exdata = argptr;

        server_request(__this->led_ui, LED_UI_REQ_MSG, &req);
    }

    va_end(argptr);
#endif
}

static void set_dec_end_handler(void *file, void *handler, int arg0, int arg1)
{
    __this->dec_end_file = file;
    __this->dec_end_args[0] = arg0;
    __this->dec_end_args[1] = arg1;
    __this->dec_end_handler = handler;
}

static void do_dec_end_handler(void *file)
{
    if (file == __this->dec_end_file) {
        __this->dec_end_file = NULL;
        if (__this->dec_end_handler) {
            if (__this->dec_end_args[1] == -1) {
                ((int (*)(int))__this->dec_end_handler)(__this->dec_end_args[0]);
            } else {
                ((int (*)(int, int))__this->dec_end_handler)(__this->dec_end_args[0],
                        __this->dec_end_args[1]);
            }
        }
    }
}

static const char *__get_dirname_file(const char *name, int len)
{
    for (int i = 0; i < ARRAY_SIZE(dir_name_chars); i++) {
        if (name[0] == '\\' && name[1] == 'U') {
            if (!memcmp(dir_name_chars[i], name + 2, len - 2)) {
                return voice_prompt_file[i];
            }
        } else {
            if (!memcmp(dir_name_chars[i], name, len)) {
                return voice_prompt_file[i];
            }
        }
    }
    for (int i = 0; i < ARRAY_SIZE(dir_name_chars_english); i++) {
        if (!strncmp(dir_name_chars_english[i], name, len)) {
            return voice_prompt_file[i];
        }
    }
    for (int i = 0; i < ARRAY_SIZE(voice_prompt_file); i++) {
        if (!memcmp(name, voice_prompt_file[i], 3)) {
            return voice_prompt_file[i];
        }
    }

    return NULL;
}

static void mix_dec_server_event_handler(void *priv, int argc, int *argv)
{
    union audio_req r = {0};

    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
        puts("mix_music: AUDIO_SERVER_EVENT_ERR\n");
    case AUDIO_SERVER_EVENT_END:
        puts("mix_music: AUDIO_SERVER_EVENT_END\n");
        r.dec.cmd = AUDIO_DEC_STOP;
        server_request(priv, AUDIO_REQ_DEC, &r);
        server_close(priv);
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(argv[1]);
        } else
#endif
        {
            fclose((FILE *)argv[1]);
        }
        break;
    default:
        break;
    }
}

static int app_music_play_mix_file(const char *path)
{
    int err = 0;
    union audio_req req = {0};

#if defined CONFIG_NO_SDRAM_ENABLE || !defined CONFIG_AUDIO_MIX_ENABLE
    return 0;
#endif

#if TCFG_USER_EMITTER_ENABLE
    if (get_bt_emitter_audio_server() && __this->dec_server) {
        return 0;
    }
#endif
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    if (check_user_virtual_audio_if_running() && __this->dec_server) {
        return 0;
    }
#endif

    log_d("play_mix_file : %s\n", path);

    FILE *file = fopen(path, "r");
    if (!file) {
        return -ENOENT;
    }

    void *dec_server = server_open("audio_server", "dec");
    if (!dec_server) {
        goto __err;
    }
    server_register_event_handler_to_task(dec_server, dec_server, mix_dec_server_event_handler, "app_core");

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.output_buf_len  = DEC_BUF_LEN;
    req.dec.file            = file;
#if defined CONFIG_AUDIO_DEC_PLAY_SOURCE
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;
#else
    req.dec.sample_source   = "dac";
#endif

    err = server_request(dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;

    err = server_request(dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    puts("play_mix_music_file: suss\n");

    return 0;

__err:

    if (dec_server) {
        server_close(dec_server);
    }
    if (file) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(file);
        } else
#endif
        {
            fclose(file);
        }
    }

    printf("play_mix_music_file: fail : %d\n", err);

    return err;
}

static int __get_dec_breakpoint(struct audio_dec_breakpoint *bp, int resume_play)
{
    int err;
    union audio_req r = {0};

    bp->len = 0;
    r.dec.bp = bp;
    r.dec.cmd = AUDIO_DEC_GET_BREAKPOINT;

    if (bp->data) {
        free(bp->data);
        bp->data = NULL;
    }

    if (!__this->dec_server) {
        return -EFAULT;
    }

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    if (err) {
        return err;
    }

    if (resume_play && r.dec.dec_type && !strcmp(r.dec.dec_type, "m4a") && bp->len > 512) {
        bp->len -= 512;
    }

    if (!resume_play && r.dec.status == AUDIO_DEC_STOP) {
        bp->len = 0;
        free(bp->data);
        bp->data = NULL;
        return -EFAULT;
    }
    /* put_buf(bp->data, bp->len); */

    return 0;
}

static int __set_dec_volume(int step)
{
    union audio_req req = {0};

    int volume = __this->volume + step;
    if (volume < MIN_VOLUME_VALUE) {
        volume = MIN_VOLUME_VALUE;
    } else if (volume > MAX_VOLUME_VALUE) {
#ifdef CONFIG_VOICE_PROMPT_FILE_PATH
        app_music_play_mix_file(CONFIG_VOICE_PROMPT_FILE_PATH"VolumeFull.mp3");
#endif
        volume = MAX_VOLUME_VALUE;
    }
    if (volume == __this->volume) {
        return -EINVAL;
    }
    __this->volume = volume;

    log_d("set_dec_volume: %d\n", volume);

#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
#if TCFG_USER_EMITTER_ENABLE
    if (get_bt_emitter_audio_server() && __this->digital_vol_hdl && __this->dec_server) {
        return user_audio_digital_volume_set(__this->digital_vol_hdl, volume, 1);
    }
#endif
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    if (check_user_virtual_audio_if_running() && __this->digital_vol_hdl && __this->dec_server) {
        return user_audio_digital_volume_set(__this->digital_vol_hdl, volume, 1);
    }
#endif
#endif

#ifdef CONFIG_VOICE_PROMPT_FILE_PATH
    if (volume == MAX_VOLUME_VALUE) {
        app_music_play_mix_file(CONFIG_VOICE_PROMPT_FILE_PATH"VolumeFull.mp3");
    } else {
        app_music_play_mix_file(CONFIG_VOICE_PROMPT_FILE_PATH"Volume.mp3");
    }
#endif

    if (!__this->dec_server) {
        return -EFAULT;
    }

    req.dec.cmd     = AUDIO_DEC_SET_VOLUME;
    req.dec.volume  = volume;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    return 0;
}

static int __get_dec_status(int priv)
{
    union audio_req req = {0};

    if (!__this->dec_server) {
        return -EFAULT;
    }

    req.dec.cmd     = AUDIO_DEC_GET_STATUS;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    return req.dec.status;
}

//打断提示音的播放
static void app_music_stop_voice_prompt(void)
{
    if (__this->play_voice_prompt) {
        local_music_dec_ops.dec_stop(0);
        __this->play_voice_prompt = 0;
        if (!__this->key_disable) {
            key_event_enable();
        }
    }
}

/*
 * ****************************本地播放*************************************
 */
static int local_music_dec_play_pause(u8 notify)
{
    union audio_req r = {0};

    if (!__this->dec_server) {
        return -EFAULT;
    }

#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
#if TCFG_USER_EMITTER_ENABLE
    if (get_bt_emitter_audio_server() && __this->digital_vol_hdl && __this->dec_server) {
        if (AUDIO_DEC_START == __get_dec_status(0)) {
            user_audio_digital_volume_set(__this->digital_vol_hdl, 0, 1);
            user_audio_digital_volume_wait_fade_complete(__this->digital_vol_hdl, (12 + 32) * 1024);
        } else if (AUDIO_DEC_PAUSE == __get_dec_status(0)) {
            user_audio_digital_volume_set(__this->digital_vol_hdl, __this->volume, 1);
        }
    }
#endif
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    if (check_user_virtual_audio_if_running() && __this->digital_vol_hdl && __this->dec_server) {
        if (AUDIO_DEC_START == __get_dec_status(0)) {
            user_audio_digital_volume_set(__this->digital_vol_hdl, 0, 1);
            user_audio_digital_volume_wait_fade_complete(__this->digital_vol_hdl, (12 + 32) * 1024);
        } else if (AUDIO_DEC_PAUSE == __get_dec_status(0)) {
            user_audio_digital_volume_set(__this->digital_vol_hdl, __this->volume, 1);
        }
    }
#endif
#endif

#if TCFG_USER_EMITTER_ENABLE
    void *emitter = get_bt_emitter_audio_server();
    if (emitter && AUDIO_DEC_START == __get_dec_status(0)) {
        set_bt_emitter_virtual_hdl(NULL);
        memset(&r, 0, sizeof(r));
        r.enc.cmd = AUDIO_ENC_PAUSE;
        server_request(emitter, AUDIO_REQ_ENC, &r);
    }
#endif

    memset(&r, 0, sizeof(r));

#ifdef CONFIG_DEC_ANALOG_VOLUME_ENABLE
    r.dec.attr = AUDIO_ATTR_FADE_INOUT;
#endif
    r.dec.cmd = AUDIO_DEC_PP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    if (r.dec.status == AUDIO_DEC_START) {
        led_ui_post_msg("dec_start");
#if TCFG_USER_EMITTER_ENABLE
        if (emitter && __this->virtual_audio) {
            set_bt_emitter_virtual_hdl(__this->virtual_audio);
            memset(&r, 0, sizeof(r));
            r.enc.cmd = AUDIO_ENC_START;
            server_request(emitter, AUDIO_REQ_ENC, &r);
        }
#endif
    } else {
        led_ui_post_msg("dec_pause");
    }

    return 0;
}

static int local_music_dec_stop(int save_breakpoint)
{
    int err = 0;
    union audio_req req;
#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
    int resume_play = 1;
#else
    int resume_play = 0;
#endif

    if (!__this->file) {
        return 0;
    }

    puts("local_music_dec_stop\n");

    led_ui_post_msg("dec_stop");

    if (save_breakpoint) {
        err = __get_dec_breakpoint(&__this->lbp.local_bp, resume_play);
        if (!err) {
            if (__this->local_bp_file && __this->local_bp_file != __this->file) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
                if (__this->last_sdram_prompt_flag) {
                    __this->last_sdram_prompt_flag = 0;
                    lfs_sdram_prompt_close(__this->local_bp_file);
                } else
#endif
                {
                    fclose(__this->local_bp_file);
                }
            }
            __this->local_bp_file = __this->file;
#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
            struct vfs_attr attr = {0};
            fget_attrs(__this->local_bp_file, &attr);
            __this->lbp.sclust = attr.sclust;
            __this->lbp.fsize = attr.fsize;
            memcpy(__this->lbp.data, __this->lbp.local_bp.data, __this->lbp.local_bp.len);
#endif
        }
    }

#if TCFG_USER_EMITTER_ENABLE
    void *emitter = get_bt_emitter_audio_server();
    if (emitter) {
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
        if (__this->digital_vol_hdl) {
            if (AUDIO_DEC_START == __get_dec_status(0)) {
                user_audio_digital_volume_set(__this->digital_vol_hdl, 0, 1);
                user_audio_digital_volume_wait_fade_complete(__this->digital_vol_hdl, (12 + 32) * 1024);
            }
        }
#endif
        memset(&req, 0, sizeof(req));
        set_bt_emitter_virtual_hdl(NULL);
        req.enc.cmd = AUDIO_ENC_PAUSE;
        server_request(emitter, AUDIO_REQ_ENC, &req);
        memset(&req, 0, sizeof(req));
    } else {
        set_bt_emitter_virtual_hdl(NULL);
    }
#endif

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
    if (check_user_virtual_audio_if_running() && __this->digital_vol_hdl) {
        if (AUDIO_DEC_START == __get_dec_status(0)) {
            user_audio_digital_volume_set(__this->digital_vol_hdl, 0, 1);
            user_audio_digital_volume_wait_fade_complete(__this->digital_vol_hdl, (12 + 32) * 1024);
        }
    }
#endif
    void *virtual = get_user_virtual_audio_server();
    if (virtual) {
        memset(&req, 0, sizeof(req));
        set_user_virtual_play_hdl(NULL);
        req.enc.cmd = AUDIO_ENC_PAUSE;
        server_request(virtual, AUDIO_REQ_ENC, &req);
        memset(&req, 0, sizeof(req));
    } else {
        set_user_virtual_play_hdl(NULL);
    }
#endif

    __this->spectrum_fft_hdl = NULL;
    __this->digital_vol_hdl = NULL;
    __this->virtual_audio = NULL;

    if (__this->dec_server) {
#ifdef CONFIG_DEC_ANALOG_VOLUME_ENABLE
        req.dec.attr |= AUDIO_ATTR_FADE_INOUT;
#endif
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    }

#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
    if (!err && save_breakpoint) {
        syscfg_write(VM_FLASH_BREAKPOINT_INDEX + __this->mode - LOCAL_MUSIC_MODE, &__this->lbp, sizeof(__this->lbp));
    }
#endif

    int argv[2];
    argv[0] = AUDIO_SERVER_EVENT_END;
    argv[1] = (int)__this->file;
    server_event_handler_del(__this->dec_server, 2, argv);

    if (!save_breakpoint || err) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(__this->file);
        } else
#endif
        {
            fclose(__this->file);
        }
        if (__this->local_bp_file == __this->file) {
            __this->local_bp_file = NULL;
        }
    }
    __this->file = NULL;

    return 0;
}

/*
 * 选择文件并播放, mode为选择方式，如FSEL_NEXT_FILE
 */
static int local_music_dec_file(void *file, int breakpoint, void *handler, int arg)
{
    int err;
    union audio_req req = {0};

    puts("app_music_dec_local_file\n");

    __this->dec_ops->dec_stop(0);

    if (!file) {
        return -1;
    }

    set_dec_end_handler(file, handler, arg, -1);

    if (breakpoint) {
        req.dec.bp = &__this->lbp.local_bp;
    }

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.digital_volume  = 100;	//数字音量初始值
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = DEC_BUF_LEN;
    req.dec.file            = (FILE *)file;
    req.dec.channel         = 0;
    req.dec.sample_rate     = 0;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = NULL;
#if defined CONFIG_AUDIO_DEC_PLAY_SOURCE
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;
#else
    req.dec.sample_source   = "dac";
#endif
#if 0	//变声变调功能
    req.dec.speedV = 80; // >80是变快，<80是变慢，建议范围：30到130
    req.dec.pitchV = 32768; // >32768是音调变高，<32768音调变低，建议范围20000到50000
    req.dec.attr = AUDIO_ATTR_PS_EN;
#endif
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
    if (__this->sdram_prompt_flag) {
        printf("---%s---%s---%d\n\r", __FILE__, __func__, __LINE__);
        req.dec.attr  |= AUDIO_ATTR_SDRAM_PROMPT;
        extern const struct audio_vfs_ops *get_load_sdram_ops(void);
        req.dec.vfs_ops         = get_load_sdram_ops();
        req.dec.dec_type		= __this->sdram_save_dec_type;
        __this->last_sdram_prompt_flag = 1;
        __this->sdram_prompt_flag = 0;
    }
#endif

#if TCFG_EQ_ENABLE
    req.dec.attr |= AUDIO_ATTR_EQ_EN;
#if TCFG_LIMITER_ENABLE
    req.dec.attr |= AUDIO_ATTR_EQ32BIT_EN;
#endif
#if TCFG_DRC_ENABLE
    req.dec.attr |= AUDIO_ATTR_DRC_EN;
#endif
#endif

#if CONFIG_DEC_DECRYPT_ENABLE
    if (!__this->play_voice_prompt) {
        extern const struct audio_vfs_ops *get_decrypt_vfs_ops(void);
        req.dec.vfs_ops = get_decrypt_vfs_ops();
        req.dec.attr |= AUDIO_ATTR_DECRYPT_DEC;
    }
#endif

#if TCFG_USER_EMITTER_ENABLE
    void *emitter = get_bt_emitter_audio_server();
    if (!emitter) {
        if (bt_emitter_role_get() == BT_EMITTER_EN && bt_get_total_connect_dev() > 0 && (bt_emitter_get_curr_channel_state() & A2DP_SRC_CH)) {
            bt_emitter_pp(1);
            os_time_dly(50);
        }
    }
    emitter = get_bt_emitter_audio_server();
    if (emitter) {
        req.dec.force_sr = 44100;
        req.dec.sample_source = "virtual";
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
        req.dec.digital_volume = req.dec.volume;
        req.dec.attr |= AUDIO_ATTR_DIGITAL_FADE_INOUT;;
#endif
    }
#endif

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    //此处可加上检查PC端是否已经打开文件
    if (!__this->play_voice_prompt && check_user_virtual_audio_if_running()) {
        req.dec.force_sr = TCFG_USER_VIRTUAL_PLAY_SAMPLERATE;
        req.dec.sample_source = "virtual";
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
        req.dec.digital_volume = req.dec.volume;
        req.dec.attr |= AUDIO_ATTR_DIGITAL_FADE_INOUT;;
#endif
    }
#endif

#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
    req.dec.effect |= AUDIO_EFFECT_DIGITAL_VOL;
#endif

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    req.dec.effect |= AUDIO_EFFECT_SPECTRUM_FFT;
#endif

#ifdef CONFIG_VIRTUAL_BASS_ENABLE
    req.dec.effect |= AUDIO_EFFECT_VIRTUAL_BASS;
#endif

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        log_e("audio_dec_open: err = %d\n", err);
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(__this->file);
        } else
#endif
        {
            fclose((FILE *)file);
        }
        return err;
    }

    __this->play_time = req.dec.play_time;
    __this->total_time = req.dec.total_time;
    __this->virtual_audio = req.dec.virtual_audio;

    if (breakpoint) {
        __this->lbp.local_bp.len = 0;
    }

#if TCFG_USER_EMITTER_ENABLE
    if (emitter && req.dec.virtual_audio) {
        set_bt_emitter_virtual_hdl(req.dec.virtual_audio);
        memset(&req, 0, sizeof(req));
        req.enc.cmd = AUDIO_ENC_START;
        server_request(emitter, AUDIO_REQ_ENC, &req);
        memset(&req, 0, sizeof(req));
    }
#endif

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    if (req.dec.virtual_audio) {
        set_user_virtual_play_hdl(req.dec.virtual_audio);
        void *virtual = get_user_virtual_audio_server();
        if (virtual) {
            memset(&req, 0, sizeof(req));
            req.enc.cmd = AUDIO_ENC_START;
            server_request(virtual, AUDIO_REQ_ENC, &req);
            memset(&req, 0, sizeof(req));
        }
    }
#endif

    if (__this->seek_step && !__this->play_voice_prompt) {
        __this->dec_ops->dec_seek(__this->seek_step);
        __this->seek_step = 0;
    }

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    memset(&req, 0, sizeof(req));
    req.dec.cmd = AUDIO_DEC_GET_EFFECT_HANDLE;
    req.dec.effect = AUDIO_EFFECT_SPECTRUM_FFT;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    __this->spectrum_fft_hdl = req.dec.get_hdl;
#endif

#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
    memset(&req, 0, sizeof(req));
    req.dec.cmd = AUDIO_DEC_GET_EFFECT_HANDLE;
    req.dec.effect = AUDIO_EFFECT_DIGITAL_VOL;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    __this->digital_vol_hdl = req.dec.get_hdl;
#endif

#ifdef CONFIG_VIRTUAL_BASS_ENABLE
    memset(&req, 0, sizeof(req));
    req.dec.cmd = AUDIO_DEC_GET_EFFECT_HANDLE;
    req.dec.effect = AUDIO_EFFECT_VIRTUAL_BASS;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    __this->virtual_bass = req.dec.get_hdl;
#endif

#ifdef CONFIG_DEC_ANALOG_VOLUME_ENABLE
    req.dec.attr |= AUDIO_ATTR_FADE_INOUT;
#endif

    req.dec.cmd = AUDIO_DEC_START;

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        log_e("audio_dec_start: err = %d\n", err);
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(__this->file);
        } else
#endif
        {
            fclose((FILE *)file);
        }
        return err;
    }
    __this->file = (FILE *)file;
    __this->cmp_file = (void *)file;

    if (!__this->play_voice_prompt) {
        __this->dec_ops = &local_music_dec_ops;
    }

    led_ui_post_msg("dec_start");
    puts("play_music_file: suss\n");

    return 0;
}

static int local_music_dec_switch_file(int fsel_mode)
{
    int i = 0;
    FILE *file = NULL;
    int len = 0;
    char name[64] = {0};
    char vm_name[64] = {0};
    u8 resume_file = fsel_mode == FSEL_FIRST_FILE && __this->local_play_all ? 1 : 0;

    puts("app_music_dec_switch_file\n");

    if (!__this->fscan || !__this->fscan->file_number) {
        return -ENOENT;
    }

    app_music_stop_voice_prompt();

    __this->fscan->cycle_mode = FCYCLE_ALL;

    if (!resume_file && __this->local_play_all) {
        /* __this->fscan->cycle_mode = FCYCLE_FOLDER; */
    }

    if (!resume_file && __this->local_play_mode == SINGLE_PLAY_MODE && fsel_mode != FSEL_FIRST_FILE && !__this->force_switch_file) {
        __this->fscan->cycle_mode = FCYCLE_ONE;
        fsel_mode = FSEL_AUTO_FILE;
    }

    if (!resume_file && __this->local_play_mode == RANDOM_PLAY_MODE) {
        __this->fscan->cycle_mode = FCYCLE_RANDOM;
    }

__retry:
    do {
        file = fselect(__this->fscan, fsel_mode, 0);
        if (file) {
            memset(name, 0, sizeof(name));
            len = fget_name(file, (u8 *)name, sizeof(name));
            if (len > 0) {
                printf("play file name : %s\n", name);
            }
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
            if (__this->sdram_prompt_dir) {
                fclose(file);
                file = NULL;
                if (lfs_sdram_prompt_check(name)) {
                    //是否全部装载, 还是只装载一个
                    sdram_prompt_load(name);
                }
                file = lfs_sdram_prompt_open(name);
                if (!file) {
                    goto __retry;
                }
                memset(__this->sdram_save_dec_type, 0, sizeof(__this->sdram_save_dec_type));
                strcpy(__this->sdram_save_dec_type, strstr(name, ".") + 1);
                __this->sdram_prompt_flag = 1;
            }
#endif
            ++i;
            break;
        }
    } while (i++ < __this->fscan->file_number);

    if (!file) {
        return -ENOENT;
    }

#if TCFG_UDISK_ENABLE
    if (__this->mode == UDISK0_MUSIC_MODE && __this->local_path == CONFIG_MUSIC_PATH_UDISK0 && !udisk_storage_device_ready(0)) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->sdram_prompt_flag) {
            __this->sdram_prompt_flag = 0;
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(file);
        } else
#endif
        {
            fclose(file);
        }
        return -1;
    }
    if (__this->mode == UDISK1_MUSIC_MODE && __this->local_path == CONFIG_MUSIC_PATH_UDISK1 && !udisk_storage_device_ready(1)) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->sdram_prompt_flag) {
            __this->sdram_prompt_flag = 0;
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(file);
        } else
#endif
        {
            fclose(file);
        }
        return -1;
    }
#endif

    if (0 != local_music_dec_file(file, 0, local_music_dec_switch_file, FSEL_NEXT_FILE)) {
        if (fsel_mode == FSEL_FIRST_FILE) {
            fsel_mode = FSEL_NEXT_FILE;
        } else if (fsel_mode == FSEL_LAST_FILE) {
            fsel_mode = FSEL_PREV_FILE;
        }
        if (i < __this->fscan->file_number) {
            goto __retry;
        }
    }

    return 0;
}

static void local_music_create_new_dir(void)
{
    if (__this->local_path && strcmp(__this->local_path, CONFIG_MUSIC_PATH_FLASH)) {
        char path[64] = {0};
        char dir[8] = {'\\', 'U', 0, 0, 0, 0, '/'};
        for (u8 i = 0; i < 4; ++i) {
            memcpy(&dir[2], dir_name_chars[i], 4);
            strcpy(path, __this->local_path);
            memcpy(path + strlen(path), dir, sizeof(dir));
            FILE *fp = fopen(path, "w+");
            if (fp) {
                fclose(fp);
            }
        }
    }
}

static int local_music_dec_switch_dir(int fsel_mode)
{
    int len = 0;
    int i = 0;
    char name[16] = {0};
    char path[128] = {0};
    FILE *dir = NULL;
    FILE *file = NULL;

    puts("app_music_dec_switch_dir\n");

    if (!__this->local_path) {
        return app_music_switch_local_device("unknown");
    }

    if (__this->local_play_all) {
        if (__this->fscan) {
            fscan_release(__this->fscan);
        }
#if CONFIG_DEC_DECRYPT_ENABLE
        __this->fscan = fscan(__this->local_path, "-r -tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADPSMP -sn", 9);
#else
        __this->fscan = fscan(__this->local_path, "-r -tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADP -sn", 9);
#endif
        if (!__this->fscan) {
            return -ENOENT;
        }
        if (fsel_mode == FSEL_BY_SCLUST) {
            return 0;
        }
        return local_music_dec_switch_file(FSEL_FIRST_FILE);
    }

    //搜索文件夹
    if (!__this->dir_list) {
        __this->dir_list = fscan(__this->local_path, "-d -sn", 1);
        if (!__this->dir_list || __this->dir_list->file_number == 0) {
            puts("no_music_dir_find\n");
            local_music_create_new_dir();
            return -ENOENT;
        }
    }

    //选择文件夹
__again:
    do {
        dir = fselect(__this->dir_list, fsel_mode, 0);
        if (dir) {
            i++;
            break;
        }
        if (fsel_mode == FSEL_NEXT_FILE) {
            fsel_mode = FSEL_FIRST_FILE;
        } else if (fsel_mode == FSEL_PREV_FILE) {
            fsel_mode = FSEL_LAST_FILE;
        } else {
            puts("fselect_dir_faild, create dir\n");
            return -ENOENT;
        }
    } while (i++ < __this->dir_list->file_number);

    if (!dir) {
        return -ENOENT;
    }

    len = fget_name(dir, (u8 *)name, sizeof(name) - 1);
    if (0 == len) {
        fclose(dir);
        if (fsel_mode == FSEL_FIRST_FILE) {
            fsel_mode = FSEL_NEXT_FILE;
        } else if (fsel_mode == FSEL_LAST_FILE) {
            fsel_mode = FSEL_PREV_FILE;
        }
        goto __again;
    }

#if 0 //根据文件夹名打开提示音文件，不需要可屏蔽
    int __len = 0;
    char __name[64] = {0};

#ifdef CONFIG_JLFAT_ENABLE
    __len = fget_name(dir, (u8 *)__name, sizeof(__name) - 1);
#else
    __len = strlen(__name) - 1;
#endif

    const char *note = __get_dirname_file(__name, __len);
#ifdef CONFIG_VOICE_PROMPT_FILE_PATH
    if (note) {
        fname_to_path(path, CONFIG_VOICE_PROMPT_FILE_PATH, note, strlen(note) + 1, 0, 0);
    } else {
        fname_to_path(path, CONFIG_VOICE_PROMPT_FILE_PATH, __name, strlen(__name) + 1, 0, 0);
    }
#endif

    file = fopen(path, "r");
    if (!file) {
        if (i >= __this->dir_list->file_number) {
            fclose(dir);
            puts("fselect_no_purpose_dir, create dir\n");
            local_music_create_new_dir();
            return -ENOENT;
        }
        if (fsel_mode == FSEL_FIRST_FILE) {
            fsel_mode = FSEL_NEXT_FILE;
        } else if (fsel_mode == FSEL_LAST_FILE) {
            fsel_mode = FSEL_PREV_FILE;
        }
        fclose(dir);
        goto __again;
    }
    if (note) {
        fclose(file);
        app_music_play_voice_prompt(note, local_music_dec_switch_file);
    } else {
        __this->play_voice_prompt = 1;
#if CONFIG_PLAY_PROMPT_DISABLE_KEY
        key_event_disable();
#endif
        local_music_dec_file(file, 0, local_music_dec_switch_file, FSEL_FIRST_FILE);
    }
#endif

    fclose(dir);

    if (__this->fscan) {
        fscan_release(__this->fscan);
    }

    /*
     * 搜索文件夹下的文件，按序号排序
     */
    fname_to_path(path, __this->local_path, name, len, 1, 0);

#if 0	//此处播放指定目录，用户填写的目录路径要注意中文编码问题，具体例子见local_music_create_new_dir函数，看不懂就直接用16进制把路径打印出来
    const char *user_dir = "";
    if (!file && strcmp(path, user_dir)) {
        printf("dir name : %s\n", path);
        if (fsel_mode == FSEL_FIRST_FILE) {
            fsel_mode = FSEL_NEXT_FILE;
        } else if (fsel_mode == FSEL_LAST_FILE) {
            fsel_mode = FSEL_PREV_FILE;
        }
        goto __again;
    }
#endif

    printf("fscan path : %s\n", path);
#if CONFIG_DEC_DECRYPT_ENABLE
    __this->fscan = fscan(path, "-tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADPSMP -sn", 1);
#else
    __this->fscan = fscan(path, "-tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADP -sn", 1);
#endif

#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
    if (strcmp(path, CONFIG_VOICE_PROMPT_FILE_PATH) == 0) {
        __this->sdram_prompt_dir = 1;
    } else {
        __this->sdram_prompt_dir = 0;
    }
#endif

    if (!file) {
        if (!__this->fscan || !__this->fscan->file_number) {
            if (fsel_mode == FSEL_FIRST_FILE) {
                fsel_mode = FSEL_NEXT_FILE;
            } else if (fsel_mode == FSEL_LAST_FILE) {
                fsel_mode = FSEL_PREV_FILE;
            }
            goto __again;
        }
        local_music_dec_switch_file(FSEL_FIRST_FILE);
    }

    return 0;
}

static int local_music_dec_breakpoint(int priv)
{
    if (!__this->fscan) {
        return -ENOENT;
    }

    if (__this->lbp.local_bp.len == 0) {
        return -ENOENT;
    }

    return local_music_dec_file(__this->local_bp_file, 1,
                                local_music_dec_switch_file, FSEL_NEXT_FILE);
}

#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
static int local_music_dec_vm_breakpoint(int priv)
{
    if (__this->lbp.local_bp.data) {
        free(__this->lbp.local_bp.data);
        __this->lbp.local_bp.data = NULL;
        __this->lbp.local_bp.len = 0;
    }

    if (__this->local_path == CONFIG_MUSIC_PATH_SD0) {
        if (!sdcard_storage_device_ready("sd0")) {
            return -1;
        }
    } else if (__this->local_path == CONFIG_MUSIC_PATH_SD1) {
        if (!sdcard_storage_device_ready("sd1")) {
            return -1;
        }
    } else if (__this->local_path == CONFIG_MUSIC_PATH_UDISK0) {
#if TCFG_UDISK_ENABLE
        if (!udisk_storage_device_ready(0)) {
            return -1;
        }
#endif
    } else if (__this->local_path == CONFIG_MUSIC_PATH_UDISK1) {
#if TCFG_UDISK_ENABLE
        if (!udisk_storage_device_ready(1)) {
            return -1;
        }
#endif
    }

    if (syscfg_read(VM_FLASH_BREAKPOINT_INDEX + __this->mode - LOCAL_MUSIC_MODE, &__this->lbp, sizeof(__this->lbp)) == sizeof(__this->lbp)) {
        __this->lbp.local_bp.data = malloc(__this->lbp.local_bp.len);
        if (!__this->lbp.local_bp.data) {
            return -1;
        }

        memcpy(__this->lbp.local_bp.data, __this->lbp.data, __this->lbp.local_bp.len);

        if (__this->dir_list) {
            fscan_release(__this->dir_list);
            __this->dir_list = NULL;
        }
        if (__this->fscan) {
            fscan_release(__this->fscan);
            __this->fscan = NULL;
        }

        if (0 == local_music_dec_switch_dir(FSEL_BY_SCLUST)) {
            __this->local_bp_file = fselect(__this->fscan, FSEL_BY_SCLUST, __this->lbp.sclust);
            if (!__this->local_bp_file) {
                __this->lbp.local_bp.len = 0;
                return -1;
            }

            struct vfs_attr attr = {0};
            fget_attrs(__this->local_bp_file, &attr);
            if (__this->lbp.fsize != attr.fsize) {
                __this->lbp.local_bp.len = 0;
            }
        }
    }

    if (__this->lbp.local_bp.len == 0) {
        return -1;
    }

    return local_music_dec_file(__this->local_bp_file, 1,
                                local_music_dec_switch_file, FSEL_NEXT_FILE);
}
#endif

static int local_music_dec_progress(int time)
{
    return 0;
}

static int local_music_dec_volume(int step)
{
    return 0;
}

static int local_music_dec_seek(int seek_step)
{
    int err;
    union audio_req r = {0};

    if (0 == seek_step) {
        return 0;
    }

    if (__this->total_time != 0 && __this->total_time != -1) {
        if (__this->play_time + seek_step <= 0 || __this->play_time + seek_step >= __this->total_time) {
            log_e("local music seek out of range\n");
            return -1;
        }
    }

    if (seek_step > 0) {
        r.dec.cmd = AUDIO_DEC_FF;
        r.dec.ff_fr_step = seek_step;
    } else {
        r.dec.cmd = AUDIO_DEC_FR;
        r.dec.ff_fr_step = -seek_step;
    }

    log_i("local music seek step : %d\n", seek_step);

    if (!__this->dec_server) {
        return -EFAULT;
    }

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    if (!err && r.dec.status == AUDIO_DEC_START) {
        led_ui_post_msg("dec_start");
    }

    return 0;
}

static void sdram_prompt_load(char *fname)
{
    int i = 0;
    FILE *file = NULL;
    int len;
    u8 fscan_exit = 0;
    char name[64] = {0};
#if defined CONFIG_LOAD_SDRAM_PROMPT_PLAY && (CONFIG_LOAD_SDRAM_PROMPT_PLAY == 0)
    if (!__this->local_path || (__this->local_path && strcmp(__this->local_path, CONFIG_VOICE_PROMPT_FILE_PATH) != 0)) {
        if (__this->fscan) {
            fscan_release(__this->fscan);
            __this->fscan = NULL;
            fscan_exit = 1;
        }
        char *path = CONFIG_VOICE_PROMPT_FILE_PATH;
#if CONFIG_DEC_DECRYPT_ENABLE
        __this->fscan = fscan(path, "-tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADPSMP -sn", 1);
#else
        __this->fscan = fscan(path, "-tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADP -sn", 1);
#endif
    }
    /* __this->fscan->cycle_mode = FCYCLE_ALL; */

    do {
        file = fselect(__this->fscan, i == 0 ? FSEL_FIRST_FILE : FSEL_NEXT_FILE, 0);
        if (file) {
            memset(name, 0, sizeof(name));
            len = fget_name(file, (u8 *)name, sizeof(name));
            if (len > 0) {
                printf("file name : %s\n\r", name);
            }
            fclose(file);
            lfs_sdram_prompt_load(CONFIG_VOICE_PROMPT_FILE_PATH, name);
        }
    } while (i++ < __this->fscan->file_number);
    if (__this->fscan) {
        fscan_release(__this->fscan);
        __this->fscan = NULL;
    }
    if (__this->local_path && strcmp(__this->local_path, CONFIG_VOICE_PROMPT_FILE_PATH) != 0) {
        if (__this->fscan) {
            fscan_release(__this->fscan);
            __this->fscan = NULL;
        }
        if (fscan_exit) {
#if CONFIG_DEC_DECRYPT_ENABLE
            __this->fscan = fscan(__this->lcoal_path, "-tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADPSMP -sn", 1);
#else
            __this->fscan = fscan(__this->local_path, "-tOGGMP3MP2MP1WMAWAVM4AAMRAPEFLAAACSPXOPUDTSADP -sn", 1);
#endif

        }
    }
#elif defined CONFIG_LOAD_SDRAM_PROMPT_PLAY && (CONFIG_LOAD_SDRAM_PROMPT_PLAY == 1)
    printf("file name : %s\n\r", fname);
    lfs_sdram_prompt_load(CONFIG_VOICE_PROMPT_FILE_PATH, fname);
#endif
    return;
}




static const struct music_dec_ops local_music_dec_ops = {
    .switch_dir     = local_music_dec_switch_dir,
    .switch_file    = local_music_dec_switch_file,
    .dec_file       = local_music_dec_file,
    .dec_breakpoint = local_music_dec_breakpoint,
    .dec_play_pause = local_music_dec_play_pause,
    .dec_volume     = local_music_dec_volume,
    .dec_progress   = local_music_dec_progress,
    .dec_stop       = local_music_dec_stop,
    .dec_seek       = local_music_dec_seek,
    .dec_status     = __get_dec_status,
};

/*
 * SD卡插入升级检测
 */
static int upgrade_detect(const char *upgrade_path)
{
    return fs_update_check(upgrade_path);
}

static int sdcard_upgrade(const char *upgrade_path)
{
    FILE *fsdc = fopen(upgrade_path, "r");
    if (fsdc) {
        fclose(fsdc);
        if (0 == app_music_play_voice_prompt("OtaInUpdate.mp3", upgrade_detect)) {
            __this->dec_end_args[0] = (int)upgrade_path;
            __this->dec_end_args[1] = -1;
            return 0;
        }
    }

    return -1;
}

/*
 * flash、sd卡和U盘之间的切换
 */
static int app_music_switch_local_device(const char *path)
{
    puts("app_music_switch_local_device\n");

    if (__this->dir_list) {
        fscan_release(__this->dir_list);
        __this->dir_list = NULL;
    }
    if (__this->fscan) {
        fscan_release(__this->fscan);
        __this->fscan = NULL;
    }
    if (__this->local_bp_file && __this->local_bp_file != __this->file) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(__this->local_bp_file);
        } else
#endif
        {
            fclose(__this->local_bp_file);
        }
        __this->local_bp_file = NULL;
        __this->lbp.local_bp.len = 0;
    }
    if (__this->mode != SDCARD0_MUSIC_MODE && __this->wait_sd) {
        wait_completion_del(__this->wait_sd);
        __this->wait_sd = 0;
    }
    if (__this->mode != SDCARD1_MUSIC_MODE && __this->wait_sd1) {
        wait_completion_del(__this->wait_sd1);
        __this->wait_sd1 = 0;
    }
    if (__this->mode != UDISK0_MUSIC_MODE && __this->wait_udisk) {
        wait_completion_del(__this->wait_udisk);
        __this->wait_udisk = 0;
    }
    if (__this->mode != UDISK1_MUSIC_MODE && __this->wait_udisk1) {
        wait_completion_del(__this->wait_udisk1);
        __this->wait_udisk1 = 0;
    }

    if (path == CONFIG_MUSIC_PATH_SD0 && sdcard_storage_device_ready("sd0") && 0 == sdcard_upgrade(CONFIG_SD0_UPGRADE_PATH)) {
        __this->wait_sd = 0;
        return 0;
    }
    if (path == CONFIG_MUSIC_PATH_SD1 && sdcard_storage_device_ready("sd1") && 0 == sdcard_upgrade(CONFIG_SD1_UPGRADE_PATH)) {
        __this->wait_sd1 = 0;
        return 0;
    }

    if ((path && !strcmp(path, "unknown")) || !__this->local_path) {
        return 0;
    } else if (path == CONFIG_MUSIC_PATH_SD0 || __this->local_path == CONFIG_MUSIC_PATH_SD0) {
        if (!sdcard_storage_device_ready("sd0")) {
            return -1;
        }
        __this->wait_sd = 0;
    } else if (path == CONFIG_MUSIC_PATH_SD1 || __this->local_path == CONFIG_MUSIC_PATH_SD1) {
        if (!sdcard_storage_device_ready("sd1")) {
            return -1;
        }
        __this->wait_sd1 = 0;
    } else if (path == CONFIG_MUSIC_PATH_UDISK0 || __this->local_path == CONFIG_MUSIC_PATH_UDISK0) {
#if TCFG_UDISK_ENABLE
        if (!udisk_storage_device_ready(0)) {
            return -1;
        }
        __this->wait_udisk = 0;
#endif
    } else if (path == CONFIG_MUSIC_PATH_UDISK1 || __this->local_path == CONFIG_MUSIC_PATH_UDISK1) {
#if TCFG_UDISK_ENABLE
        if (!udisk_storage_device_ready(1)) {
            return -1;
        }
        __this->wait_udisk1 = 0;
#endif
    }

    if (path) {
        __this->local_path = path;
    }

    local_music_dec_switch_dir(FSEL_FIRST_FILE);

    return 0;
}


/*
 * ******************************FM电台*************************************
 */
#if TCFG_FM_DEV_ENABLE

static const struct music_dec_ops fm_music_dec_ops;

static int fm_music_dec_switch_dir(int fsel_mode)
{
    return fm_server_msg_post(fsel_mode == FSEL_NEXT_FILE ? FM_SCAN_ALL_DOWN : FM_SCAN_ALL_UP);
}

static int fm_music_dec_switch_file(int fsel_mode)
{
    return fm_server_msg_post(fsel_mode == FSEL_NEXT_FILE ? FM_NEXT_STATION : FM_PREV_STATION);
}

static int fm_music_dec_file(void *priv, int breakpoint, void *handler, int arg)
{
    if (0 != fm_server_init()) {
        return -1;
    }

    set_dec_end_handler(priv, handler, arg, -1);
    __this->dec_ops = &fm_music_dec_ops;
    return 0;
}

static int fm_music_dec_play_pause(u8 notify)
{
    return fm_server_msg_post(FM_MUSIC_PP);
}

static int fm_music_dec_volume(int step)
{
    return fm_server_msg_post(step > 0 ? FM_VOLUME_DOWN : FM_VOLUME_UP);
}

static int fm_music_dec_stop(int save_breakpoint)
{
    if (1 == save_breakpoint) {
        return fm_server_msg_post(FM_DEC_OFF);
    } else {
        fm_sever_kill();
    }

    return 0;
}

static int fm_music_dec_breakpoint(int priv)
{
    return fm_server_msg_post(FM_DEC_ON);
}

static const struct music_dec_ops fm_music_dec_ops = {
    .switch_dir     = fm_music_dec_switch_dir,
    .switch_file    = fm_music_dec_switch_file,
    .dec_file       = fm_music_dec_file,
    .dec_breakpoint = fm_music_dec_breakpoint,
    .dec_play_pause = fm_music_dec_play_pause,
    .dec_volume     = fm_music_dec_volume,
    .dec_stop       = fm_music_dec_stop,
    .dec_status     = __get_dec_status,
};

#endif


#ifdef CONFIG_AUDIO_ENABLE

/*
 * ****************************AUX/LINEIN*************************************
 */
//编码器输出PCM数据
static int aux_vfs_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    if (0 == cbuf_write(cbuf, data, len)) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        cbuf_clear(cbuf);
    }
    os_sem_set(&__this->r_sem, 0);
    os_sem_post(&__this->r_sem);
    //此回调返回0linein就会自动停止
    return len;
}

//解码器读取PCM数据
static int aux_vfs_fread(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    u32 rlen;

    do {
        rlen = cbuf_get_data_size(cbuf);
        rlen = rlen > len ? len : rlen;
        if (cbuf_read(cbuf, data, rlen) > 0) {
            len = rlen;
            break;
        }
        //此处等待信号量是为了防止解码器因为读不到数而一直空转
        os_sem_pend(&__this->r_sem, 0);
        if (!__this->run_flag) {
            return 0;
        }
    } while (__this->run_flag);

    //返回成功读取的字节数
    return len;
}

static int aux_vfs_fclose(void *file)
{
    return 0;
}

static int aux_vfs_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops recorder_vfs_ops = {
    .fwrite = aux_vfs_fwrite,
    .fread  = aux_vfs_fread,
    .fclose = aux_vfs_fclose,
    .flen   = aux_vfs_flen,
};

static int aux_music_dec_stop(int save_breakpoint)
{
    union audio_req req = {0};

    if (!__this->run_flag) {
        return 0;
    }

    log_d("----------aux close----------\n");

    __this->run_flag = 0;

    os_sem_post(&__this->w_sem);
    os_sem_post(&__this->r_sem);

    if (__this->enc_server) {
        req.enc.cmd = AUDIO_ENC_STOP;
        server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
    }

    if (__this->dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    }

    server_close(__this->enc_server);
    __this->enc_server = NULL;

    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
    }

    return 0;
}

static int aux_music_dec_file(void *priv, int breakpoint, void *handler, int arg)
{
    int err;
    int sample_rate = CONFIG_AUDIO_LINEIN_SAMPLERATE;
    u8 channel = CONFIG_AUDIO_LINEIN_CHANNEL;

    printf("----------aux_play_to_dac----------\n");

#ifdef CONFIG_ASR_ALGORITHM
    if (__this->wakeup_support) {
        sample_rate = 16000;
    }
#endif

    __this->enc_server = server_open("audio_server", "enc");

    if (channel > 2) {
        channel = 2;
    }
    __this->cache_buf = malloc(sample_rate * channel); //上层缓冲buf缓冲0.5秒的数据，缓冲太大听感上会有延迟
    if (__this->cache_buf == NULL) {
        return -1;
    }
    cbuf_init(&__this->save_cbuf, __this->cache_buf, sample_rate * channel);

    os_sem_create(&__this->w_sem, 0);
    os_sem_create(&__this->r_sem, 0);

    __this->run_flag = 1;

    union audio_req req = {0};
    /****************打开解码DAC器*******************/
    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.output_buf_len  = 4 * 1024;
    req.dec.channel         = channel;
    req.dec.sample_rate     = sample_rate;
    req.dec.vfs_ops         = &recorder_vfs_ops;
    req.dec.dec_type 		= "pcm";
#if defined CONFIG_AUDIO_DEC_PLAY_SOURCE
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;
#else
    req.dec.sample_source   = "dac";
#endif
    req.dec.file            = (FILE *)&__this->save_cbuf;
    /* req.dec.attr            = AUDIO_ATTR_LR_ADD; */          //左右声道数据合在一起,封装只有DACL但需要测试两个MIC时可以打开此功能

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    /****************打开编码器*******************/
    memset(&req, 0, sizeof(union audio_req));

    /* BIT(x)用来区分上层需要获取哪个通道的数据 */
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    req.enc.channel_bit_map = BIT(CONFIG_AUDIO_LINEIN_CHANNEL_MAP);
#endif
    req.enc.frame_size = sample_rate / 100 * 4 * channel;	//收集够多少字节PCM数据就回调一次fwrite
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = channel;
    req.enc.volume = CONFIG_AUDIO_LINEIN_ADC_GAIN;
    req.enc.sample_rate = sample_rate;
    req.enc.format = "pcm";
    req.enc.sample_source = "linein";
    req.enc.vfs_ops = &recorder_vfs_ops;
    req.enc.file = (FILE *)&__this->save_cbuf;

    err = server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
    if (err) {
        goto __err1;
    }

    req.dec.cmd = AUDIO_DEC_START;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    return 0;

__err1:
    req.dec.cmd = AUDIO_DEC_STOP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

__err:
    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
    }

    __this->run_flag = 0;

    return -1;
}

static int aux_music_dec_play_pause(u8 notify)
{
    union audio_req req = {0};

    req.dec.cmd = AUDIO_DEC_PP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    req.enc.cmd = AUDIO_ENC_PP;
    server_request(__this->enc_server, AUDIO_REQ_ENC, &req);

    if (__this->cache_buf) {
        cbuf_clear(&__this->save_cbuf);
    }

    return 0;
}

static int aux_music_dec_volume(int step)
{
    return 0;
}

static int aux_music_dec_breakpoint(int priv)
{
    return aux_music_dec_file(NULL, 0, NULL, 0);
}

static const struct music_dec_ops aux_music_dec_ops = {
    .dec_file       = aux_music_dec_file,
    .dec_play_pause = aux_music_dec_play_pause,
    .dec_volume     = aux_music_dec_volume,
    .dec_breakpoint = aux_music_dec_breakpoint,
    .dec_stop       = aux_music_dec_stop,
    .dec_status     = __get_dec_status,
};

#endif

/*
 * ****************************网络播歌*************************************
 */
#ifdef CONFIG_NET_ENABLE

static const struct music_dec_ops net_music_dec_ops;

static const struct audio_vfs_ops net_audio_dec_vfs_ops = {
    .fread = net_download_read,
    .fseek = net_download_seek,
    .flen  = net_download_get_file_len,
};

static int __net_download_ready()
{
    __this->download_ready = net_download_check_ready(__this->net_file);
    if (__this->download_ready) {
        return 1;
    }
    return 0;
}

static int net_music_dec_play_pause(u8 notify)
{
    union audio_req r;
    union ai_req req  = {0};

    if (!__this->dec_server) {
        return -EFAULT;
    }

#if TCFG_USER_EMITTER_ENABLE
    void *emitter = get_bt_emitter_audio_server();
    if (emitter && AUDIO_DEC_START == __get_dec_status(0)) {
        set_bt_emitter_virtual_hdl(NULL);
        memset(&r, 0, sizeof(r));
        r.enc.cmd = AUDIO_ENC_PAUSE;
        server_request(emitter, AUDIO_REQ_ENC, &r);
    }
#endif

    memset(&r, 0, sizeof(r));

#ifdef CONFIG_DEC_ANALOG_VOLUME_ENABLE
    r.dec.attr = AUDIO_ATTR_FADE_INOUT;
#endif
    r.dec.cmd = AUDIO_DEC_PP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    if (r.dec.status == AUDIO_DEC_START) {
        /* 播放状态 */
        net_download_set_pp(__this->net_file, 0);
        led_ui_post_msg("dec_start");
#if TCFG_USER_EMITTER_ENABLE
        if (emitter && __this->virtual_audio) {
            set_bt_emitter_virtual_hdl(__this->virtual_audio);
            memset(&r, 0, sizeof(r));
            r.enc.cmd = AUDIO_ENC_START;
            server_request(emitter, AUDIO_REQ_ENC, &r);
        }
#endif
    } else if (r.dec.status == AUDIO_DEC_PAUSE) {
        if (__this->play_tts) {
            __this->dec_ops->dec_stop(0);
        } else {
            /* 暂停状态 */
            net_download_set_pp(__this->net_file, 1);
            led_ui_post_msg("dec_pause");
        }
    } else if (r.dec.status == AUDIO_DEC_STOP) {
        if (0 == __this->dec_ops->dec_breakpoint(0)) {
            r.dec.status = AUDIO_DEC_START;
        }
    }

    if (notify && __this->ai_server && r.dec.status != AUDIO_DEC_STOP) {
        req.evt.event   = AI_EVENT_PLAY_PAUSE;
        req.evt.ai_name = __this->ai_name;
        if (r.dec.status == AUDIO_DEC_PAUSE) {
            req.evt.arg = 1;
        }
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }

    return 0;
}

static int net_music_dec_stop(int save_breakpoint)
{
    int err;
    union audio_req r = {0};
    union ai_req req = {0};

    //如果是语音链接不应该保存断点
    if (__this->play_tts) {
        save_breakpoint = 0;
    }

    printf("net_music_dec_stop: %d\n", save_breakpoint);

    if (!__this->net_file) {
        return 0;
    }

    led_ui_post_msg("dec_stop");

    net_download_buf_inactive(__this->net_file);

    if (__this->wait_download) {
        /*
         * 歌曲还未播放，删除wait
         */
        /* sys_timer_del(__this->wait_download); */
        wait_completion_del(__this->wait_download);
        __this->wait_download = 0;
        __this->wait_download_suspend = 1;
    } else {
        if (save_breakpoint) {
            int url_len = strlen(__this->url) + 1;
            if (url_len > __this->net_bp.url_len) {
                if (__this->net_bp.url) {
                    free(__this->net_bp.url);
                }
                __this->net_bp.url = malloc(url_len);
                if (!__this->net_bp.url) {
                    __this->net_bp.url_len = 0;
                } else {
                    __this->net_bp.url_len = url_len;
                }
            }
            if (__this->net_bp.url) {
                err = __get_dec_breakpoint(&__this->net_bp.dec_bp, 0);
                if (!err) {
                    __this->net_bp.ai_name = __this->ai_name;
                    strcpy(__this->net_bp.url, __this->url);
                    __this->net_bp.fptr = __this->net_bp.dec_bp.fptr;
                    if (net_download_check_if_is_m3u8_url(__this->net_file)) {
                        __this->net_bp.fptr = 0;
                        free(__this->net_bp.dec_bp.data);
                        __this->net_bp.dec_bp.data = NULL;
                    }
                    log_d("save_breakpoint: fptr=%x\n", __this->net_bp.fptr);
                } else if (1 == err && __this->ai_server) {		//解决暂停时的断点问题
                    req.evt.event   = AI_EVENT_MEDIA_STOP;
                    req.evt.arg     = __this->play_time;
                    req.evt.ai_name = __this->ai_name;
                    ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
                }
            }
        }

#if TCFG_USER_EMITTER_ENABLE
        void *emitter = get_bt_emitter_audio_server();
        if (emitter) {
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
            if (__this->digital_vol_hdl) {
                if (AUDIO_DEC_START == __get_dec_status(0)) {
                    user_audio_digital_volume_set(__this->digital_vol_hdl, 0, 1);
                    user_audio_digital_volume_wait_fade_complete(__this->digital_vol_hdl, (12 + 32) * 1024);
                }
            }
#endif
            memset(&r, 0, sizeof(r));
            set_bt_emitter_virtual_hdl(NULL);
            r.enc.cmd = AUDIO_ENC_PAUSE;
            server_request(emitter, AUDIO_REQ_ENC, &r);
            memset(&r, 0, sizeof(r));
        } else {
            set_bt_emitter_virtual_hdl(NULL);
        }
#endif

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
        if (check_user_virtual_audio_if_running() && __this->digital_vol_hdl) {
            if (AUDIO_DEC_START == __get_dec_status(0)) {
                user_audio_digital_volume_set(__this->digital_vol_hdl, 0, 1);
                user_audio_digital_volume_wait_fade_complete(__this->digital_vol_hdl, (12 + 32) * 1024);
            }
        }
#endif
        void *virtual = get_user_virtual_audio_server();
        if (virtual) {
            memset(&r, 0, sizeof(r));
            set_user_virtual_play_hdl(NULL);
            r.enc.cmd = AUDIO_ENC_PAUSE;
            server_request(virtual, AUDIO_REQ_ENC, &r);
            memset(&r, 0, sizeof(r));
        } else {
            set_user_virtual_play_hdl(NULL);
        }
#endif

        __this->spectrum_fft_hdl = NULL;
        __this->digital_vol_hdl = NULL;
        __this->virtual_audio = NULL;

        if (__this->dec_server) {
#ifdef CONFIG_DEC_ANALOG_VOLUME_ENABLE
            r.dec.attr |= AUDIO_ATTR_FADE_INOUT;
#endif
            r.dec.cmd = AUDIO_DEC_STOP;
            server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
        }

        int argv[2];
        argv[0] = AUDIO_SERVER_EVENT_END;
        argv[1] = (int)__this->net_file;
        server_event_handler_del(__this->dec_server, 2, argv);
    }

    canceladdrinfo();
    net_download_close(__this->net_file);
    __this->net_file = NULL;
    __this->seek_step = 0;

    return 0;
}

static int net_music_dec_end(int save_bp)
{
    union ai_req req = {0};

    puts("net_music_dec_end\n");

    net_music_dec_stop(save_bp);

    if (!__this->ai_server) {
        return 0;
    }

    /*
     * 歌曲播放完成，发送此命令后ai平台会发送新的URL
     */
    req.evt.event   = __this->play_tts ? AI_EVENT_SPEAK_END : AI_EVENT_MEDIA_END;
    req.evt.ai_name     = __this->ai_name;
    return ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
}

static int __net_music_dec_file(int breakpoint)
{
    int err;
    union ai_req r = {0};
    union audio_req req = {0};

    __this->wait_download = 0;
    __this->wait_download_suspend = 0;

    if (__this->download_ready < 0) {
        /* 网络下载失败 */
        goto __err;
    }
    if (__this->wait_switch_file) {
        puts("del_wait_switch_file\n");
        sys_timeout_del(__this->wait_switch_file);
        __this->wait_switch_file = 0;
    }
    if (__this->play_voice_prompt) {
        set_dec_end_handler(__this->file, __net_music_dec_file, breakpoint, -1);
        return 0;
    }

    req.dec.dec_type = net_download_get_media_type(__this->net_file);
    if (req.dec.dec_type == NULL) {
        goto __err;
    }
    printf("url_file_type: %s\n", req.dec.dec_type);

    if (breakpoint == 1) {
        __this->ai_name = __this->net_bp.ai_name;
        req.dec.bp = &__this->net_bp.dec_bp;
    }

    net_download_set_read_timeout(__this->net_file, 5000);

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.digital_volume  = 100;	//数字音量初始值
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = DEC_BUF_LEN;
    req.dec.file            = (FILE *)__this->net_file;
    req.dec.channel         = 0;
    req.dec.sample_rate     = 0;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &net_audio_dec_vfs_ops;
#if defined CONFIG_AUDIO_DEC_PLAY_SOURCE
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;
#else
    req.dec.sample_source   = "dac";
#endif

#if 0	//变声变调功能
    req.dec.speedV = 80; // >80是变快，<80是变慢，建议范围：30到130
    req.dec.pitchV = 32768; // >32768是音调变高，<32768音调变低，建议范围20000到50000
    req.dec.attr = AUDIO_ATTR_PS_EN;
#endif

#if TCFG_EQ_ENABLE
    req.dec.attr |= AUDIO_ATTR_EQ_EN;
#if TCFG_LIMITER_ENABLE
    req.dec.attr |= AUDIO_ATTR_EQ32BIT_EN;
#endif
#if TCFG_DRC_ENABLE
    req.dec.attr |= AUDIO_ATTR_DRC_EN;
#endif
#endif

#if TCFG_USER_EMITTER_ENABLE
    void *emitter = get_bt_emitter_audio_server();
    if (!emitter) {
        if (bt_emitter_role_get() == BT_EMITTER_EN && bt_get_total_connect_dev() > 0 && (bt_emitter_get_curr_channel_state() & A2DP_SRC_CH)) {
            bt_emitter_pp(1);
            os_time_dly(50);
        }
    }
    emitter = get_bt_emitter_audio_server();
    if (emitter) {
        req.dec.force_sr = 44100;
        req.dec.sample_source = "virtual";
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
        req.dec.digital_volume = req.dec.volume;
        req.dec.attr |= AUDIO_ATTR_DIGITAL_FADE_INOUT;;
#endif
    }
#endif

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    //此处可加上检查PC端是否已经打开文件
    if (check_user_virtual_audio_if_running()) {
        req.dec.force_sr = TCFG_USER_VIRTUAL_PLAY_SAMPLERATE;
        req.dec.sample_source = "virtual";
#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
        req.dec.digital_volume = req.dec.volume;
        req.dec.attr |= AUDIO_ATTR_DIGITAL_FADE_INOUT;;
#endif
    }
#endif

#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
    req.dec.effect |= AUDIO_EFFECT_DIGITAL_VOL;
#endif

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    req.dec.effect |= AUDIO_EFFECT_SPECTRUM_FFT;
#endif

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    __this->cmp_file = __this->net_file;
    __this->play_time = req.dec.play_time;
    __this->total_time = req.dec.total_time;
    __this->virtual_audio = req.dec.virtual_audio;

    if (breakpoint == 1) {
        __this->net_bp.dec_bp.len = 0;
    }

#if TCFG_USER_EMITTER_ENABLE
    if (emitter && req.dec.virtual_audio) {
        set_bt_emitter_virtual_hdl(req.dec.virtual_audio);
        memset(&req, 0, sizeof(req));
        req.enc.cmd = AUDIO_ENC_START;
        server_request(emitter, AUDIO_REQ_ENC, &req);
        memset(&req, 0, sizeof(req));
    }
#endif

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
    if (req.dec.virtual_audio) {
        set_user_virtual_play_hdl(req.dec.virtual_audio);
        void *virtual = get_user_virtual_audio_server();
        if (virtual) {
            memset(&req, 0, sizeof(req));
            req.enc.cmd = AUDIO_ENC_START;
            server_request(virtual, AUDIO_REQ_ENC, &req);
            memset(&req, 0, sizeof(req));
        }
    }
#endif

    net_download_set_read_timeout(__this->net_file, 0);

    if (__this->seek_step) {
        __this->dec_ops->dec_seek(__this->seek_step);
        __this->seek_step = 0;
        net_download_set_read_timeout(__this->net_file, 0);
    }

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    memset(&req, 0, sizeof(req));
    req.dec.cmd = AUDIO_DEC_GET_EFFECT_HANDLE;
    req.dec.effect |= AUDIO_EFFECT_SPECTRUM_FFT;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    __this->spectrum_fft_hdl = req.dec.get_hdl;
#endif

#ifdef CONFIG_DEC_DIGITAL_VOLUME_ENABLE
    memset(&req, 0, sizeof(req));
    req.dec.cmd = AUDIO_DEC_GET_EFFECT_HANDLE;
    req.dec.effect = AUDIO_EFFECT_DIGITAL_VOL;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    __this->digital_vol_hdl = req.dec.get_hdl;
#endif

#ifdef CONFIG_DEC_ANALOG_VOLUME_ENABLE
    req.dec.attr |= AUDIO_ATTR_FADE_INOUT;
#endif

    req.dec.cmd = AUDIO_DEC_START;

    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    net_download_set_pp(__this->net_file, 0);

#ifdef CONFIG_NO_SDRAM_ENABLE
    net_download_set_tmp_data_threshold(__this->net_file, 10 * 1024);
#else
    net_download_set_tmp_data_threshold(__this->net_file, 80 * 1024);
#endif

    led_ui_post_msg("dec_start");

    if (__this->ai_server) {
        r.evt.event   = __this->play_tts ? AI_EVENT_SPEAK_START : AI_EVENT_MEDIA_START;
        r.evt.ai_name = __this->ai_name;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &r);
    }

    return 0;

__err:
    puts("play_net_music_faild\n");

    net_download_buf_inactive(__this->net_file);

    if (__this->dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    }

    net_download_close(__this->net_file);
    __this->net_file = NULL;

    if (__this->ai_server) {
        r.evt.event   = __this->play_tts ? AI_EVENT_SPEAK_END : AI_EVENT_MEDIA_END;
        r.evt.ai_name   = __this->ai_name;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &r);
    }

    return -EFAULT;
}

static void check_net_download_ready_timer(void *priv)
{
    if (!__this->wait_download || !__this->net_file) {
        return;
    }
    __this->download_ready = net_download_check_ready(__this->net_file);
    if (__this->download_ready) {
        sys_timer_del(__this->wait_download);
        __this->wait_download = 0;
        __net_music_dec_file((int)priv);
    }
}

static int net_music_dec_file(void *_url, int breakpoint, void *handler, int arg)
{
    int err;
    struct net_download_parm parm;

    if (__this->dec_ops) {
        __this->dec_ops->dec_stop(0);
    }

    puts("net_download_open\n");

    if (!_url) {
        return -1;
    }

    memset(&parm, 0, sizeof(struct net_download_parm));
    parm.url                = (const char *)_url;
    parm.prio               = 0;
#ifdef CONFIG_NO_SDRAM_ENABLE
    parm.cbuf_size          = 40 * 1024;
#else
    parm.cbuf_size          = 200 * 1024;
#endif
    parm.timeout_millsec    = 10000;
    parm.seek_high_range    = 0;
    parm.seek_low_range     = breakpoint ? __this->net_bp.fptr : 0;
#ifdef CONFIG_DOWNLOAD_SAVE_FILE
    if (!__this->play_tts && storage_device_ready()) {
        char path[128] = {0};
        char file_name[64] = {0};
        time_t tNow = time(NULL);
        struct tm tmNow = { 0 };
        localtime_r(&tNow, &tmNow);
        parm.dir_len = snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"download/%04d-%02d-%02dT%02d-%02d-%02d.%s",
                                tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday,
                                tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec,
                                "mp3");
#ifdef CONFIG_JLFAT_ENABLE
        parm.dir_len			= long_file_name_encode(file_name, (u8 *)path, sizeof(path));
        parm.file_dir			= path;
        /* put_buf(path, parm.dir_len); */
#else
        parm.file_dir			= file_name;
#endif
        parm.save_file			= 1;
    }
#endif
    parm.seek_threshold     = 1024 * 200;	//用户可适当调整
    /* parm.no_wait_close      = 1; */
    /* parm.start_play_threshold = 1024 * 4; */

    err = net_download_open(&__this->net_file, &parm);
    if (err) {
        log_e("net_download_open: err = %d\n", err);
        return err;
    }
    __this->url = (const char *)_url;

    set_dec_end_handler(__this->net_file, handler, arg, -1);

    /*
     * 异步等待网络下载ready，防止网络阻塞导致app卡住
     */
    __this->wait_download_suspend = 0;
#if 1
    __this->wait_download = wait_completion(__net_download_ready,
                                            (int (*)(void *))__net_music_dec_file, (void *)breakpoint, NULL);
#else
    __this->wait_download = sys_timer_add((void *)breakpoint, check_net_download_ready_timer, 20);
#endif

    __this->dec_ops = &net_music_dec_ops;

    return 0;
}

static int net_music_dec_switch_file(int fsel_mode)
{
    union ai_req req = {0};

    puts("net_music_dec_switch_file\n");

    if (!strcmp(__this->ai_name, "dlna")) {
        return 0;
    }

    net_music_dec_stop(0);

    if (fsel_mode == FSEL_NEXT_FILE) {
        req.evt.event = AI_EVENT_NEXT_SONG;
    } else if (fsel_mode == FSEL_PREV_FILE) {
        req.evt.event = AI_EVENT_PREVIOUS_SONG;
    } else {
        return 0;
    }

    if (!__this->ai_server) {
        return 0;
    }

    req.evt.ai_name = __this->ai_name;
    return ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
}

static int net_music_dec_switch_dir(int fsel_mode)
{
    return 0;
}

static int net_music_dec_breakpoint(int priv)
{
    puts("net_music_dec_breakpoint\n");

    if (__this->play_tts) {
        __this->play_tts = 0;
    }
    if (__this->wait_download_suspend) {
        if (__this->net_bp.dec_bp.len > 0 && !strcmp(__this->url, __this->net_bp.url)) {
            return net_music_dec_file(__this->net_bp.url, 1, net_music_dec_end, 0);
        } else {
            return net_music_dec_file((void *)__this->url, 0, net_music_dec_end, 0);
        }
    }
    if (__this->net_bp.dec_bp.len == 0) {
        return -ENOENT;
    }
    return net_music_dec_file(__this->net_bp.url, 1, net_music_dec_end, 0);
}

static int net_music_dec_progress(int sec)
{
    union ai_req req = {0};

    req.evt.event       = AI_EVENT_PLAY_TIME;
    req.evt.arg         = sec;
    req.evt.ai_name     = __this->ai_name;
    return ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
}

static int net_music_dec_volume(int step)
{
    union ai_req req = {0};

    if (__this->ai_server) {
        req.evt.event       = AI_EVENT_VOLUME_CHANGE;
        req.evt.arg         = __this->volume;
        req.evt.ai_name     = __this->ai_name;
        return ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }

    return 0;
}

static int net_music_dec_seek(int seek_step)
{
    int err;
    union audio_req r = {0};

    if (0 == seek_step) {
        return 0;
    }

    if (__this->total_time != 0 && __this->total_time != -1) {
        if (__this->play_time + seek_step <= 0 || __this->play_time + seek_step >= __this->total_time) {
            log_e("local music seek out of range\n");
            return -1;
        }
    }

    if (seek_step > 0) {
        r.dec.cmd = AUDIO_DEC_FF;
        r.dec.ff_fr_step = seek_step;
    } else {
        r.dec.cmd = AUDIO_DEC_FR;
        r.dec.ff_fr_step = -seek_step;
    }

    log_i("net music seek step : %d\n", seek_step);

    if (!__this->dec_server) {
        return -EFAULT;
    }

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    if (!err && r.dec.status == AUDIO_DEC_START) {
        led_ui_post_msg("dec_start");
    }

    return 0;
}

static const struct music_dec_ops net_music_dec_ops = {
    .switch_dir     = net_music_dec_switch_dir,
    .switch_file    = net_music_dec_switch_file,
    .dec_file       = net_music_dec_file,
    .dec_breakpoint = net_music_dec_breakpoint,
    .dec_play_pause = net_music_dec_play_pause,
    .dec_volume     = net_music_dec_volume,
    .dec_progress   = net_music_dec_progress,
    .dec_stop       = net_music_dec_stop,
    .dec_seek       = net_music_dec_seek,
    .dec_status     = __get_dec_status,
};

static void ai_server_media_stop_notify(void)
{
    union ai_req req = {0};

    if (__this->ai_server) {
        req.evt.event   = AI_EVENT_MEDIA_STOP;
        req.evt.arg     = __this->play_time;
        req.evt.ai_name = __this->ai_name;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
}

static int __play_net_music(const char *url)
{
    return net_music_dec_file((void *)url, 0, net_music_dec_end, 0);
}

static int app_music_play_net_music(void *url)
{
    if (__this->play_voice_prompt) {
        if (__this->dec_end_handler != (void *)app_music_shutdown) {
            set_dec_end_handler(__this->dec_end_file, __play_net_music, (int)url, -1);
        }
        return 0;
    }
    if (__this->net_bp.url && __this->net_bp.dec_bp.len > 0 && !strcmp((const char *)url, __this->net_bp.url)) {
        return net_music_dec_file(url, 1, net_music_dec_end, 0);
    }

    return net_music_dec_file(url, 0, net_music_dec_end, 0);
}

static int app_music_ai_listen_start(u8 voice_mode, u8 enable_vad);

//第三方平台的事件通知回调
static void ai_server_event_handler(void *priv, int argc, int *argv)
{
    int err = 0;

    if (!__this->ai_server) {
        switch (argv[0]) {
        case AI_SERVER_EVENT_URL:
        case AI_SERVER_EVENT_RECV_CHAT:
            free((void *)argv[1]);
            break;
        default:
            break;
        }
        return;
    }

    switch (argv[0]) {
    case AI_SERVER_EVENT_CONNECTED:
        if (!strcmp((const char *)argv[1], "dlna") || !strcmp((const char *)argv[1], "page_turning")) {
            break;
        }
        if (!__this->ai_connected) {
            __this->ai_connected = 1;
            if (__this->dec_end_handler != (void *)__play_net_music) {
                /* app_music_play_voice_prompt("SerConnect.mp3", __this->dec_ops->dec_breakpoint); */
            }
        }
        break;
    case AI_SERVER_EVENT_DISCONNECTED:
        if (!strcmp((const char *)argv[1], "dlna") || !strcmp((const char *)argv[1], "page_turning")) {
            break;
        }
        if (__this->ai_connected) {
            __this->ai_connected = 0;
            if (__this->mode == NET_MUSIC_MODE) {
                app_music_play_voice_prompt("SerDiscon.mp3", __this->dec_ops->dec_breakpoint);
            }
        }
        break;
    case AI_SERVER_EVENT_URL:
    case AI_SERVER_EVENT_URL_TTS:
    case AI_SERVER_EVENT_URL_MEDIA:
        if (__this->listening == LISTEN_STATE_START || __this->listening == LISTEN_STATE_WAKEUP
            || __this->upgrading || __this->call_flag || __this->mute) {
            free((void *)argv[1]);
            return;
        }
        __this->play_tts = argv[0] == AI_SERVER_EVENT_URL_TTS ? 1 : 0;
        __this->total_time = 0;	//清空上一首歌的信息
        if (strcmp((const char *)argv[2], __this->ai_name)) {
            ai_server_media_stop_notify();
        }
        __this->ai_name = (const char *)argv[2];
        free(__this->save_url);
        __this->save_url = (void *)argv[1];
        if (__this->mode != NET_MUSIC_MODE) {
            app_music_play_mode_switch_notify();
            __this->mode = NET_MUSIC_MODE;
        }
        app_music_play_net_music((void *)argv[1]);
        break;
    case AI_SERVER_EVENT_CONTINUE:
        if (__this->dec_ops == &net_music_dec_ops && !strcmp((const char *)argv[2], __this->ai_name)) {
            if (__this->play_voice_prompt) {
                if (__this->net_bp.dec_bp.len > 0) {
                    app_music_stop_voice_prompt();
                    __this->dec_ops->dec_play_pause(0);
                }
            } else if (!__this->play_tts && AUDIO_DEC_START != __this->dec_ops->dec_status(0)) {
                __this->dec_ops->dec_play_pause(0);
            }
        }
        break;
    case AI_SERVER_EVENT_PAUSE:
        if (__this->dec_ops == &net_music_dec_ops && !strcmp((const char *)argv[2], __this->ai_name)) {
            if (__this->play_voice_prompt) {
                if (__this->dec_end_handler == net_music_dec_ops.dec_breakpoint) {
                    __this->dec_end_handler = NULL;
                }
            } else if (!__this->play_tts && AUDIO_DEC_START == __this->dec_ops->dec_status(0)) {
                __this->dec_ops->dec_play_pause(0);
            }
        }
        break;
    case AI_SERVER_EVENT_STOP:
        if (__this->dec_ops == &net_music_dec_ops && !strcmp((const char *)argv[2], __this->ai_name)) {
            __this->dec_ops->dec_stop(0);
            __this->net_bp.dec_bp.len = 0;
        }
        break;
    case AI_SERVER_EVENT_RESUME_PLAY:
        if (AUDIO_DEC_STOP == __this->dec_ops->dec_status(0)) {
            __this->dec_ops = &net_music_dec_ops;
            __this->dec_ops->dec_breakpoint(0);
        }
        break;
    case AI_SERVER_EVENT_SEEK:
        if (__this->dec_ops == &net_music_dec_ops) {
            if (AUDIO_DEC_STOP == __this->dec_ops->dec_status(0)) {
                __this->seek_step = argv[1];
                if (0 != __this->dec_ops->dec_breakpoint(0)) {
                    __this->seek_step = 0;
                }
            } else {
                __this->dec_ops->dec_seek(argv[1] - __this->play_time);
            }
        }
        break;
    case AI_SERVER_EVENT_UPGRADE:
        sys_power_auto_shutdown_pause();
        __this->key_disable |= BIT(1);
        __this->upgrading = 1;
        ai_server_media_stop_notify();
        app_music_play_voice_prompt("OtaInUpdate.mp3", NULL);
#ifdef CONFIG_LOW_POWER_ENABLE
        low_power_hw_unsleep_lock();
#endif
        break;
    case AI_SERVER_EVENT_UPGRADE_SUCC:
        if (argv[1] && strlen((const char *)argv[1]) < 16) {
            char version[16];
            memset(version, 0, sizeof(version));
            version[0] = 0;	//升级类型
            memcpy(version + 1, (const char *)argv[1], strlen((const char *)argv[1]));
            syscfg_write(VM_VERSION_INDEX, version, 16);
        }
        free((void *)argv[1]);
        /* db_update("upg", 1); */
        system_soft_reset();
        break;
    case AI_SERVER_EVENT_UPGRADE_FAIL:
        __this->key_disable &= ~BIT(1);
        __this->upgrading = 0;
        if (!__this->play_voice_prompt && !__this->key_disable) {
            key_event_enable();
        }
        app_music_play_voice_prompt("OtaFailed.mp3", NULL);
        sys_power_auto_shutdown_resume();
#ifdef CONFIG_LOW_POWER_ENABLE
        low_power_hw_unsleep_unlock();
#endif
        break;
    case AI_SERVER_EVENT_MIC_OPEN:
        if (__this->listening == LISTEN_STATE_STOP) {
            __this->listening = LISTEN_STATE_WAKEUP;
            app_music_play_voice_prompt("rec.mp3", NULL);
        }
        if (argv[1]) {
            os_sem_post((OS_SEM *)argv[1]);
        }
        break;
    case AI_SERVER_EVENT_MIC_CLOSE:
        if (__this->listening == LISTEN_STATE_WAKEUP) {
            __this->listening = LISTEN_STATE_STOP;
        } else if (__this->listening == LISTEN_STATE_START) {
            __this->listening = LISTEN_STATE_STOPPING;
        }
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
        extern void adc_multiplex_set_gain(const char *source, u8 channel_bit_map, u8 gain);
        adc_multiplex_set_gain("mic", BIT(CONFIG_ASR_CLOUD_ADC_CHANNEL), CONFIG_AISP_MIC_ADC_GAIN);
#endif
        if (__this->wechat_flag && !__this->rec_again) {
            app_music_play_voice_prompt("send.mp3", __this->dec_ops->dec_breakpoint);
            break;
        }
        if (__this->rec_again && 0 == app_music_ai_listen_start(__this->voice_mode, 1)) {
            __this->listening = LISTEN_STATE_WAKEUP;
        } else {
            app_music_play_voice_prompt("send.mp3", NULL);
        }
        break;
    case AI_SERVER_EVENT_REC_TOO_SHORT:
        app_music_play_voice_prompt("MsgTooShort.mp3", __this->dec_ops->dec_breakpoint);
        break;
    case AI_SERVER_EVENT_PLAY_BEEP:
        if (__this->listening == LISTEN_STATE_STOP && !__this->upgrading && __this->mode == NET_MUSIC_MODE) {
            app_music_play_voice_prompt((const char *)argv[1],  __this->dec_ops->dec_breakpoint);
        }
        break;
    case AI_SERVER_EVENT_RECV_CHAT:
        if (argv[1]) {
            if (__this->wechat_url_num < 30) {
                struct __wechat_url *wechat = (struct __wechat_url *)malloc(sizeof(struct __wechat_url));
                if (wechat) {
                    wechat->url = (void *)argv[1];
                    list_add_tail(&wechat->entry, &__this->wechat_list);
                    ++__this->wechat_url_num;
                    if (__this->listening == LISTEN_STATE_STOP && !__this->upgrading && __this->mode == NET_MUSIC_MODE) {
                        app_music_play_voice_prompt("RecvNewMsg.mp3", __this->dec_ops->dec_breakpoint);
                    }
                    break;
                }
            }
            free((void *)argv[1]);
        }
        break;
    case AI_SERVER_EVENT_VOLUME_CHANGE:
        if (0 == __set_dec_volume(argv[1] - __this->volume)) {
#ifdef CONFIG_STORE_VOLUME
            syscfg_write(CFG_MUSIC_VOL, &__this->volume, sizeof(__this->volume));
#endif
        }
        break;
    case AI_SERVER_EVENT_SET_PLAY_TIME:
        __this->play_time = argv[1];
        break;
    case AI_SERVER_EVENT_CHILD_LOCK_CHANGE:
        if (argv[1]) {
            __this->key_disable |= BIT(0);
            key_event_disable();
        } else {
            __this->key_disable &= ~BIT(0);
            if (!__this->play_voice_prompt && !__this->key_disable) {
                key_event_enable();
            }
        }
        break;
    case AI_SERVER_EVENT_LIGHT_CHANGE:
        if (__this->light_intensity != argv[1]) {
            __this->light_intensity = argv[1];
            if ((__this->light_intensity == 0 && argv[1] == 100) || (__this->light_intensity == 100 && argv[1] == 0)) {

            }
        }
        break;
    case AI_SERVER_EVENT_REC_ERR:
        app_music_play_voice_prompt("AsrEmpty.mp3", __this->dec_ops->dec_breakpoint);
        break;
#ifdef CONFIG_BT_ENABLE
    case AI_SERVER_EVENT_BT_CLOSE:
        app_music_play_voice_prompt("BtClose.mp3", __this->dec_ops->dec_breakpoint);    //关闭蓝牙
        if (__this->bt_music_enable) {
            __this->bt_music_enable = 0;
            __this->bt_emitter_enable = 0;
            bt_connection_disable();
        }
        break;
    case AI_SERVER_EVENT_BT_OPEN:
        app_music_play_voice_prompt("BtOpen.mp3", __this->dec_ops->dec_breakpoint);    //打开蓝牙
        if (!__this->bt_music_enable) {
            __this->bt_music_enable = 1;
            bt_connection_enable();
        }
        break;
#endif
    default:
        break;
    }
}

static int app_music_ai_listen_start(u8 voice_mode, u8 enable_vad)
{
    int err;
    union ai_req req = {0};

    __this->rec_again = 0;
    __this->wechat_flag = 0;

    if (__this->listening != LISTEN_STATE_STOP) {
        return -1;
    }

    if (!__this->ai_connected || !__this->net_connected) {
        if (WECHAT_MODE == voice_mode) {
            app_music_play_voice_prompt("SendMsgFail.mp3", __this->dec_ops->dec_breakpoint);
        } else if (AI_MODE == voice_mode) {
            app_music_play_voice_prompt("AiAsrFail.mp3", __this->dec_ops->dec_breakpoint);
        } else if (TRANSLATE_MODE == voice_mode) {
            app_music_play_voice_prompt("AiTransFail.mp3", __this->dec_ops->dec_breakpoint);
        }
        return -1;
    }

    if (__this->mode == BT_MUSIC_MODE) {
        __this->dec_ops->dec_stop(-1);
    } else {
        __this->dec_ops->dec_stop(1);
    }

    app_music_play_voice_prompt("rec.mp3", NULL);

    os_time_dly(30);

    if (enable_vad && voice_mode != WECHAT_MODE) {
        voice_mode |= VAD_ENABLE;	//enable local vad
    }

    //voice_mode:(bit0_bit1) 交互模式   0:智能聊天   1:中英翻译    2:微聊   3:口语评测
    //voice_mode:(bit3_bit6) 采样源选择 0:AUDIO_ADC不是四路全开时使用0   1-4:AUDIO_ADC四路全开时代表具体使用的ADC通道
    //voice_mode:(bit3_bit6) 采样源选择 5:plnk0    6:plnk1    7:iis0     8:iis1
    //voice_mode:(bit7)                 0:关闭VAD    1:打开VAD
#if CONFIG_AUDIO_ENC_SAMPLE_SOURCE != AUDIO_ENC_SAMPLE_SOURCE_MIC
    req.lis.arg = voice_mode | ((CONFIG_AUDIO_ENC_SAMPLE_SOURCE + 4) << 3);
#else
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    req.lis.arg = voice_mode | ((CONFIG_ASR_CLOUD_ADC_CHANNEL + 1) << 3);
#else
    req.lis.arg = voice_mode;
#endif
#endif
    req.lis.cmd = AI_LISTEN_START;
    err = ai_server_request(__this->ai_server, AI_REQ_LISTEN, &req);
    if (err == 0) {
        __this->listening = LISTEN_STATE_START;
        if (voice_mode == WECHAT_MODE) {
            __this->wechat_flag = 1;
        }
        os_time_dly(30);
    }

    return 0;
}

static void app_music_ai_listen_stop(void)
{
    union ai_req req = {0};

    if (__this->listening == LISTEN_STATE_STOP) {
        return;
    }

    if (__this->listening != LISTEN_STATE_STOPPING) {
        if (__this->ai_server) {
            req.lis.cmd = AI_LISTEN_STOP;
            ai_server_request(__this->ai_server, AI_REQ_LISTEN, &req);
        }
    }

    __this->listening = LISTEN_STATE_STOP;
}

static void app_music_ai_listen_break(void)
{
    union ai_req req = {0};

    if (__this->listening == LISTEN_STATE_STOP) {
        return;
    }

    if (__this->listening != LISTEN_STATE_STOPPING) {
        req.evt.event = AI_EVENT_RECORD_BREAK;
#if defined CONFIG_TURING_SDK_ENABLE
        req.evt.ai_name = "turing";
#else
        req.evt.ai_name = __this->ai_name;
#endif
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
}

static void app_music_event_net_connected()
{
    union ai_req req = {0};

    /*
     * 网络连接成功,开始连接ai服务器
     */
    if (__this->ai_server) {
        return;
    }

    __this->ai_server = server_open("ai_server", NULL);
    if (__this->ai_server) {
        server_register_event_handler(__this->ai_server, NULL, ai_server_event_handler);
        ai_server_request(__this->ai_server, AI_REQ_CONNECT, &req);
    }
}


/***************************************************************/
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
extern void dev_profile_init(void);
extern void dev_profile_uninit(void);
#endif
extern void wifi_return_sta_mode(void);
extern void turing_ble_cfg_net_result_notify(int succeeded, const char *mac, const char *api_key, const char *deviceid);
extern void ble_cfg_net_result_notify(int event);

static void switch_rf_coexistence_timer(void *p)
{
    __this->coexistence_timer = 0;

    switch_rf_coexistence_config_unlock();

#if defined CONFIG_BT_ENABLE && !TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
    if (!is_in_config_network_state())
#endif
    {
        switch_rf_coexistence_config_table(0);
    }
}

static void cancel_dns_timer(void *p)
{
    canceladdrinfo();
}

static void app_music_net_config(void)
{
#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
    if (__this->mode != BT_MUSIC_MODE)
#endif
    {
        __this->mode = NET_MUSIC_MODE;
    }
    __this->net_bp.dec_bp.len = 0;
    __this->reconnecting = 0;

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
    cancel_server_assign_macaddr();
#endif

#ifdef CONFIG_VIDEO_ENABLE
    if (__this->picture_det_mode == PICTURE_DET_ENTER_MODE) {
        __this->picture_det_mode = PICTURE_DET_EXIT_MODE;
#if defined CONFIG_PAGE_TURNING_DET_ENABLE || defined CONFIG_TURING_PAGE_TURNING_DET_ENABLE
        extern int page_turning_det_uninit(void);
        page_turning_det_uninit();
#if defined CONFIG_PAGE_TURNING_DET_ENABLE
        extern int user_video_rec0_close(void);
        user_video_rec0_close();
#endif
#endif
    }
#endif

    app_music_stop_voice_prompt();

    app_music_switch_local_device("unknown");
    __this->local_path = NULL;

    if (!is_in_config_network_state()) {
        sys_power_auto_shutdown_pause();

        if (__this->coexistence_timer) {
            sys_timeout_del(__this->coexistence_timer);
            __this->coexistence_timer = 0;
            switch_rf_coexistence_config_unlock();
        }
#ifdef CONFIG_REVERB_MODE_ENABLE
        if (__this->reverb_enable) {
            echo_reverb_uninit();
            __this->reverb_enable = 0;
        }
#endif
#if defined CONFIG_BT_ENABLE && !TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
        if (__this->bt_music_enable) {
            __this->bt_emitter_enable = 0;
            bt_connection_disable();
        }
#endif
        __this->net_connected = 0;
        if (__this->ai_server) {
            __this->cancel_dns_timer = sys_timer_add_to_task("sys_timer", NULL, cancel_dns_timer, 1000);
        }
#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
        if (get_bt_music_dec_ops()->dec_status(0) == AUDIO_DEC_START) {
            app_music_play_voice_prompt("NetCfgEnter.mp3", __this->dec_ops->dec_breakpoint);
        } else
#endif
        {
            app_music_play_voice_prompt("NetCfgEnter.mp3", NULL);
        }
        if (__this->ai_server) {
            server_close(__this->ai_server);
            __this->ai_server = NULL;
            __this->ai_connected = 0;
            sys_timer_del(__this->cancel_dns_timer);
            __this->cancel_dns_timer = 0;
        }
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
        dev_profile_uninit();
#endif
#ifdef CONFIG_ASR_ALGORITHM
        if (__this->wakeup_support) {
            aisp_suspend();
        }
#endif
        config_network_start();
    } else {
#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
        if (get_bt_music_dec_ops()->dec_status(0) == AUDIO_DEC_START) {
            app_music_play_voice_prompt("NetConnting.mp3", __this->dec_ops->dec_breakpoint);
        } else
#endif
        {
            app_music_play_voice_prompt("NetConnting.mp3", NULL);
        }

        config_network_stop();
        wifi_return_sta_mode();
#ifdef CONFIG_ASR_ALGORITHM
        if (__this->wakeup_support) {
            aisp_resume();
        }
#endif
#if defined CONFIG_BT_ENABLE && !TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
        //避免打开蓝牙自动回连设备时挡住wifi连接
        switch_rf_coexistence_config_table(3);
        switch_rf_coexistence_config_lock();
        __this->coexistence_timer = sys_timeout_add(NULL, switch_rf_coexistence_timer, 15000);
        if (__this->bt_music_enable) {
            bt_connection_enable();
        }
#endif
        sys_power_auto_shutdown_resume();
    }

#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
    if (__this->dec_ops != get_bt_music_dec_ops())
#endif
    {
        __this->dec_ops = &net_music_dec_ops;
    }
}

#endif

#if defined CONFIG_BT_ENABLE && TCFG_USER_EMITTER_ENABLE
static int bt_emitter_enable(int priv)
{
    __this->bt_emitter_enable = 1;
    bt_delete_power_off_timer();
#if TCFG_BT_SNIFF_ENABLE
    lmp_set_sniff_establish_by_remote(1);
#endif
#ifdef CONFIG_LOW_POWER_ENABLE
    low_power_hw_unsleep_lock();
    btctrler_task_init_bredr();
    low_power_hw_unsleep_unlock();
#endif
    emitter_or_receiver_switch(BT_EMITTER_EN);
    __this->dec_ops->dec_breakpoint(0);
    return 0;
}

static int bt_emitter_disable(int priv)
{
    __this->bt_emitter_enable = 0;
    bt_connection_disable();
    __this->dec_ops->dec_breakpoint(0);
    return 0;
}

static int bt_emitter_switch_to_receiver(int priv)
{
    os_time_dly(50);
    __this->bt_emitter_enable = 0;
#if TCFG_BT_SNIFF_ENABLE
    lmp_set_sniff_establish_by_remote(0);
#endif
    emitter_or_receiver_switch(BT_RECEIVER_EN);
#ifdef CONFIG_NET_ENABLE
    switch_rf_coexistence_config_table(0);
#endif
    bt_connection_enable();
    __this->dec_ops->dec_breakpoint(0);
    return 0;
}

void resume_bt_emitter_dec_play(void)
{
    if (__this->virtual_audio && AUDIO_DEC_START == __get_dec_status(0)) {
        set_bt_emitter_virtual_hdl(__this->virtual_audio);
    }
}
#endif

/*
 * ****************************提示音*************************************
 */
static void dec_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
        puts("app_music: AUDIO_SERVER_EVENT_ERR\n");
    case AUDIO_SERVER_EVENT_END:
        puts("app_music: AUDIO_SERVER_EVENT_END\n");
        if (__this->cmp_file != (void *)argv[1]) {
            printf("not the same file, may be closed!\n");
            break;
        }
        /* os_time_dly(3); */
        union audio_req r = {0};
        r.dec.cmd = AUDIO_DEC_PAUSE;
        if (__this->dec_server) {
            server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
        }
        led_ui_post_msg("dec_end");
        if (!__this->key_disable) {
            key_event_enable();
        }
        if (__this->play_voice_prompt) {
            local_music_dec_ops.dec_stop(0);
            __this->play_voice_prompt = 0;
        }
#ifdef CONFIG_BT_ENABLE
#if TCFG_BT_SUPPORT_RECEIVER_AUTO_A2DP_START
        if (__this->bt_connecting && !__this->bt_emitter_enable) {
            if (get_a2dp_drop_frame_timer() == 0 && bt_get_total_connect_dev() == 1 && get_bt_music_dec_ops()->dec_status(0) != AUDIO_DEC_START) {
                bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
            }
        }
#if TCFG_BT_DUAL_CONN_ENABLE
        if (__this->bt_auto_play_another_dev && !__this->bt_emitter_enable) {
            if (get_a2dp_drop_frame_timer() == 0 && bt_get_total_connect_dev() == 1 && get_bt_music_dec_ops()->dec_status(0) != AUDIO_DEC_START) {
                bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
            }
        }
#endif
#endif
#endif
        __this->bt_auto_play_another_dev = 0;
        __this->bt_connecting = 0;
        do_dec_end_handler((void *)argv[1]);
        /* __this->play_time = 0; */
        break;
    case AUDIO_SERVER_EVENT_CURR_TIME:
        log_d("play_time: %d\n", argv[1]);
        __this->play_time = argv[1];

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
        if (__this->spectrum_fft_hdl) {
            short *db_data = audio_spectrum_fft_get_val(__this->spectrum_fft_hdl);//获取存储频谱值得地址
            if (db_data) {
                for (int i = 0; i < audio_spectrum_fft_get_num(__this->spectrum_fft_hdl); i++) {
                    //输出db_num个 db值
                    /* printf("db_data db[%d] %d\n", i, db_data[i]); */
                }
            }
        }
#endif

        sys_power_auto_shutdown_clear();

#ifdef CONFIG_JL_CLOUD_SDK_ENABLE
        if (__this->ai_server && !__this->play_tts) {
            union ai_req r = {0};
            r.evt.event   =  AI_EVENT_MEDIA_PLAY_TIME;
            r.evt.ai_name = __this->ai_name;
            ai_server_request(__this->ai_server, AI_REQ_EVENT, &r);
        }
#endif
        /* __this->dec_ops->dec_progress(argv[1]); */
        break;
    }
}

static int __play_voice_prompt(const char *fname, void *dec_end_handler, int save_bp)
{
    int err;
    char path[64] = {0};

    if ((u32)fname < APP_LOCAL_PROMPT_NUMM) {
        fname = find_local_prompt_filename((APP_LOCAL_PROMPT_TYPE_E)fname);
        if (!fname) {
            return -1;
        }
    }

    log_d("play_voice_prompt: %s\n", fname);
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
    if (lfs_sdram_prompt_check(fname)) {
        //是否全部装载, 还是只装载一个
        sdram_prompt_load(fname);
    }
    void *file = lfs_sdram_prompt_open(fname);
    if (!file) {
        return -ENOENT;
    }
    memset(__this->sdram_save_dec_type, 0, sizeof(__this->sdram_save_dec_type));
    strcpy(__this->sdram_save_dec_type, strstr(fname, ".") + 1);
    __this->sdram_prompt_flag = 1;
#else
#ifdef CONFIG_VOICE_PROMPT_FILE_PATH
    sprintf(path, "%s%s", CONFIG_VOICE_PROMPT_FILE_PATH, fname);
#endif

    FILE *file = fopen(path, "r");
    if (!file) {
        return -ENOENT;
    }
#endif
    if (__this->play_voice_prompt) {
        local_music_dec_ops.dec_stop(0);
    } else {
        __this->dec_ops->dec_stop(save_bp);
    }

    __this->play_voice_prompt = 1;

#if CONFIG_PLAY_PROMPT_DISABLE_KEY
    key_event_disable();
#endif

    if (__this->dec_end_args[2]) {
        err = local_music_dec_file(file, 0, dec_end_handler, __this->dec_end_args[2]);
        __this->dec_end_args[2] = 0;
    } else {
        err = local_music_dec_file(file, 0, dec_end_handler, 0);
    }
    if (err) {
        __this->play_voice_prompt = 0;
        if (!__this->key_disable) {
            key_event_enable();
        }
    }

    return err;
}

static int _play_voice_prompt(const char *fname, void *dec_end_handler)
{
    return __play_voice_prompt(fname, dec_end_handler, 0);
}

/*
 * 播放提示音
 */
static int app_music_play_voice_prompt(const char *fname, void *dec_end_handler)
{
#ifndef CONFIG_AUDIO_ENABLE
    if (dec_end_handler) {
        return ((int (*)(int))dec_end_handler)(0);
    }

    return 0;
#endif

    if (__this->call_flag && strcmp(fname, "ring.mp3")) {
        return 0;
    }

    if (dec_end_handler == (void *)app_music_shutdown) {
        return _play_voice_prompt(fname, dec_end_handler);
    }

    if (__this->play_voice_prompt) {
#if defined CONFIG_BT_ENABLE && TCFG_USER_EMITTER_ENABLE
        if (__this->dec_end_handler == (void *)bt_emitter_enable ||
            __this->dec_end_handler == (void *)bt_emitter_switch_to_receiver ||
            __this->dec_end_handler == (void *)bt_emitter_disable) {
            return 0;
        }
#endif
        if (__this->dec_end_handler != (void *)app_music_shutdown) {
            set_dec_end_handler(__this->dec_end_file, _play_voice_prompt,
                                (int)fname, (int)dec_end_handler);
        }
        return 0;
    }

#ifdef CONFIG_NET_ENABLE
    if (AUDIO_DEC_START != __get_dec_status(0) && !__this->wait_download && !__this->reconnecting) {
        if (dec_end_handler == local_music_dec_ops.dec_breakpoint
            || dec_end_handler == net_music_dec_ops.dec_breakpoint
           ) {
            //避免本来已经暂停了又恢复播放
            dec_end_handler = NULL;
        }
    }
#endif

    return __play_voice_prompt(fname, dec_end_handler, 1);
}

/*
 * ****************************绘本识别*************************************
 */
#if defined CONFIG_VIDEO_ENABLE && defined CONFIG_NET_ENABLE

static void app_music_enter_picture_mode(void)
{
#ifdef CONFIG_PAGE_TURNING_DET_ENABLE
    extern int user_video_rec0_open(int dev);
    user_video_rec0_open(0);
    extern int page_turning_det_init(void);
    page_turning_det_init();
#endif

#ifdef CONFIG_TURING_PAGE_TURNING_DET_ENABLE
    extern int page_turning_det_init(void);
    page_turning_det_init();
#endif

#ifdef CONFIG_SCAN_PEN_ENABLE
    printf(">>>>>>>>>>>>run spi_video_task_create OKOKOK");
    extern void scan_pen_task_init(void);
    scan_pen_task_init();// 该线程用于初始化拼接算法 接收线程中处理好的摄像头数据
#endif

#ifdef CONFIG_WT_SDK_ENABLE
    union ai_req req = {0};
    if (__this->ai_server) {
        req.evt.event   = AI_EVENT_RUN_START;
        req.evt.ai_name = "wt";
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
#endif

#if defined CONFIG_VIDEO_DISPLAY_ENABLE && defined CONFIG_VIDEO_ENABLE
    extern void video0_display_start(void);
    video0_display_start();
#endif
}

static void app_music_exit_picture_mode(void)
{
#ifdef CONFIG_PAGE_TURNING_DET_ENABLE
    extern int page_turning_det_uninit(void);
    page_turning_det_uninit();
    extern int user_video_rec0_close(void);
    user_video_rec0_close();
#endif

#ifdef CONFIG_TURING_PAGE_TURNING_DET_ENABLE
    extern int page_turning_det_uninit(void);
    page_turning_det_uninit();
#endif

#ifdef CONFIG_SCAN_PEN_ENABLE
    extern void scan_pen_task_uninit(void);
    scan_pen_task_uninit();
#endif

#ifdef CONFIG_WT_SDK_ENABLE
    union ai_req req = {0};
    if (__this->ai_server) {
        req.evt.event   = AI_EVENT_RUN_STOP;
        req.evt.ai_name = "wt";
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
#endif

#if defined CONFIG_VIDEO_DISPLAY_ENABLE && defined CONFIG_VIDEO_ENABLE
    extern void video0_display_stop(void);
    video0_display_stop();
#endif
}

u8 page_turning_get_mode(void)
{
    if (!__this->net_connected) {
        return PICTURE_DET_EXIT_MODE;
    }
    return __this->picture_det_mode;
}

#endif

int get_app_music_prompt_dec_status(void)
{
    return __this->play_voice_prompt;
}

int get_app_music_net_dec_status(void)
{
#ifdef CONFIG_NET_ENABLE
    if (__this->dec_ops == &net_music_dec_ops) {
        return __this->dec_ops->dec_status(0);
    }
#endif

    return AUDIO_DEC_STOP;
}

int is_net_music_mode(void)
{
    return __this->last_mode == NET_MUSIC_MODE;
}

int get_app_music_volume(void)
{
    return __this->volume;
}

void set_app_music_volume(int volume, u8 mode)
{
    if (__this->mode == mode) {	//避免蓝牙模式和网络模式音量不同步
        __this->volume = volume;
    }
}

int get_app_music_playtime(void)
{
    return __this->play_time;
}

int get_app_music_total_time(void)
{
    return __this->total_time;
}

int get_app_music_light_intensity(void)
{
    return __this->light_intensity;
}

int get_app_music_battery_power(void)
{
    return __this->battery_per;
}

void play_voice_prompt_for_app(char *name)
{
    struct intent it = {0};
    it.name = "app_music";
    it.action = ACTION_MUSIC_PLAY_VOICE_PROMPT;
    it.data = name;
    it.exdata = 1;
    start_app(&it);
}

static void app_music_play_mode_switch_notify(void)
{
    if (__this->mode == NET_MUSIC_MODE) {
#ifdef CONFIG_NET_ENABLE
        ai_server_media_stop_notify();
#endif
    } else if (__this->mode >= LOCAL_MUSIC_MODE && __this->mode <= UDISK1_MUSIC_MODE) {
        app_music_switch_local_device("unknown");
        __this->local_path = NULL;
    } else if (__this->mode == BT_MUSIC_MODE) {
        __this->dec_ops->dec_stop(-1);
    }
}

static int app_music_resume_local_music_mode(int priv)
{
#ifndef CONFIG_AUDIO_ENABLE
    return 0;
#endif
#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
    if (local_music_dec_vm_breakpoint(0) < 0)
#endif
    {
        return app_music_switch_local_device(priv ? (const char *)priv : __this->local_path);
    }

    return 0;
}

static int app_music_resume_net_music_mode(int priv)
{
    app_music_switch_local_device(NULL);
#ifdef CONFIG_NET_ENABLE
    //这里是否需要恢复之前的网络播放
    net_music_dec_breakpoint(0);
    __this->dec_ops = &net_music_dec_ops;
#endif
    return 0;
}

#if TCFG_FM_DEV_ENABLE
static int app_music_start_fm_music_mode(int priv)
{
    app_music_switch_local_device(NULL);
    __this->dec_ops = &fm_music_dec_ops;
    return __this->dec_ops->dec_file(NULL, 0, NULL, 0);
}
#endif

static void local_music_play_mode_switch(void)
{
    app_music_stop_voice_prompt();
#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
    if (__this->mode == NET_MUSIC_MODE || (__this->mode >= LOCAL_MUSIC_MODE && __this->mode <= UDISK1_MUSIC_MODE))
#else
    if (__this->mode == NET_MUSIC_MODE)
#endif
    {
        __this->dec_ops->dec_stop(1);
    } else {
        __this->dec_ops->dec_stop(0);
    }

#ifdef CONFIG_AUDIO_ENABLE
    if (__this->mode < LOCAL_MUSIC_MODE) {
        app_music_play_mode_switch_notify();
        __this->dec_ops = &local_music_dec_ops;
        __this->mode = LOCAL_MUSIC_MODE;
        app_music_play_voice_prompt("FlashMusic.mp3", app_music_resume_local_music_mode);
        __this->local_path = CONFIG_MUSIC_PATH_FLASH;
    } else if (__this->mode == LOCAL_MUSIC_MODE) {
        __this->dec_ops = &local_music_dec_ops;
        __this->mode = SDCARD0_MUSIC_MODE;
        app_music_play_voice_prompt("SDcardMusic.mp3", app_music_resume_local_music_mode);
        __this->local_path = CONFIG_MUSIC_PATH_SD0;
    } else if (__this->mode == SDCARD0_MUSIC_MODE) {
        __this->dec_ops = &local_music_dec_ops;
        __this->mode = SDCARD1_MUSIC_MODE;
        app_music_play_voice_prompt("SDcardMusic.mp3", app_music_resume_local_music_mode);
        __this->local_path = CONFIG_MUSIC_PATH_SD1;
    } else if (__this->mode == SDCARD1_MUSIC_MODE) {
        __this->dec_ops = &local_music_dec_ops;
        __this->mode = UDISK0_MUSIC_MODE;
        app_music_play_voice_prompt("UdiskMusic.mp3", app_music_resume_local_music_mode);
        __this->local_path = CONFIG_MUSIC_PATH_UDISK0;
    } else if (__this->mode == UDISK0_MUSIC_MODE) {
        __this->dec_ops = &local_music_dec_ops;
        __this->mode = UDISK1_MUSIC_MODE;
        app_music_play_voice_prompt("UdiskMusic.mp3", app_music_resume_local_music_mode);
        __this->local_path = CONFIG_MUSIC_PATH_UDISK1;
    } else if (__this->mode == UDISK1_MUSIC_MODE) {
        __this->dec_ops = &aux_music_dec_ops;
        __this->mode = AUX_MUSIC_MODE;
        app_music_play_voice_prompt("LineinMusic.mp3", aux_music_dec_file);
    } else if (__this->mode == AUX_MUSIC_MODE) {
        __this->local_path = NULL;
#if TCFG_FM_DEV_ENABLE
        __this->mode = FM_MUSIC_MODE;
        app_music_play_voice_prompt("FMMusic.mp3", app_music_start_fm_music_mode);
    } else if (__this->mode == FM_MUSIC_MODE) {
#endif
        __this->mode = NET_MUSIC_MODE;
        app_music_play_voice_prompt("NetMusic.mp3", app_music_resume_net_music_mode);
    }
#endif

}

#if TCFG_UDISK_ENABLE
//U盘插入升级检测
static void udisk_upgrade(void *p)
{
    if (p) {
        __this->udisk1_upgrade_timer = 0;
    } else {
        __this->udisk_upgrade_timer = 0;
    }

    if (udisk_storage_device_ready((int)p)) {
        FILE *fsdc = fopen(p ? CONFIG_UDISK1_UPGRADE_PATH : CONFIG_UDISK0_UPGRADE_PATH, "r");
        if (fsdc) {
            fclose(fsdc);
            __this->dec_ops->dec_stop(1);

            __this->dec_end_args[0] = p ? (int)CONFIG_UDISK1_UPGRADE_PATH : (int)CONFIG_UDISK0_UPGRADE_PATH;
            __this->dec_end_args[1] = -1;
            app_music_play_voice_prompt("OtaInUpdate.mp3", upgrade_detect);
        }
    }
}
#endif

static int app_music_main()
{
    int err = 0;
    puts("action_music_play_main\n");

#ifdef CONFIG_STORE_VOLUME
    if (syscfg_read(CFG_MUSIC_VOL, &__this->volume, sizeof(__this->volume)) < 0 ||
        __this->volume < MIN_VOLUME_VALUE || __this->volume > MAX_VOLUME_VALUE) {
        __this->volume = INIT_VOLUME_VALUE;
    }
#else
    __this->volume = INIT_VOLUME_VALUE;
#endif
    if (__this->volume < 0 || __this->volume > MAX_VOLUME_VALUE) {
        __this->volume = INIT_VOLUME_VALUE;
    }

    led_ui_post_msg("init");

#ifdef CONFIG_AUDIO_ENABLE
    __this->dec_server = server_open("audio_server", "dec");
    if (!__this->dec_server) {
        puts("play_music open audio_server fail!\n");
        return -EPERM;
    }
    server_register_event_handler(__this->dec_server, NULL, dec_server_event_handler);
#endif

#if CONFIG_VOLUME_TAB_TEST_ENABLE
    return 0;
#endif

#ifdef CONFIG_ASR_ALGORITHM
    aisp_open(16000);
#endif
    /*
     * 播放开机提示音
     */
#ifdef CONFIG_SCAN_PEN_ENABLE
    extern void spi_video_init(void);
    spi_video_init();
#endif

#ifdef CONFIG_AUDIO_ENABLE

    if (__this->mode == LOCAL_MUSIC_MODE) {
        __this->dec_end_args[2] = (int)CONFIG_MUSIC_PATH_FLASH;
        __play_voice_prompt("PowerOn.mp3", app_music_switch_local_device, 0);
        __this->local_path = CONFIG_MUSIC_PATH_FLASH;
    } else {
        __play_voice_prompt("PowerOn.mp3", NULL, 0);
    }
    if (err) {
        key_event_enable();
        __this->play_voice_prompt = 0;
    }
#endif

    return err;
}

static void app_music_exit(void)
{
    key_event_enable();
    sys_power_auto_shutdown_pause();

#ifdef CONFIG_NET_ENABLE
    if (__this->ai_server) {
        server_close(__this->ai_server);
        __this->ai_server = NULL;
        __this->ai_connected = 0;
    }
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
    dev_profile_uninit();
#endif
    free(__this->net_bp.url);
    free(__this->save_url);
    __this->net_bp.url = NULL;
#endif

    if (__this->dec_server) {
        app_music_stop_voice_prompt();
        if (__this->dec_ops) {
            __this->dec_ops->dec_stop(0);
        }
        server_close(__this->dec_server);
        __this->dec_server = NULL;
    }

    if (__this->wait_switch_file) {
        sys_timeout_del(__this->wait_switch_file);
        __this->wait_switch_file = 0;
    }
    if (__this->wait_sd) {
        wait_completion_del(__this->wait_sd);
        __this->wait_sd = 0;
    }
    if (__this->wait_sd1) {
        wait_completion_del(__this->wait_sd1);
        __this->wait_sd1 = 0;
    }
    if (__this->wait_udisk) {
        wait_completion_del(__this->wait_udisk);
        __this->wait_udisk = 0;
    }
    if (__this->wait_udisk1) {
        wait_completion_del(__this->wait_udisk1);
        __this->wait_udisk1 = 0;
    }
    if (__this->udisk_upgrade_timer) {
        sys_timeout_del(__this->udisk_upgrade_timer);
        __this->udisk_upgrade_timer = 0;
    }
    if (__this->udisk1_upgrade_timer) {
        sys_timeout_del(__this->udisk1_upgrade_timer);
        __this->udisk1_upgrade_timer = 0;
    }
    if (__this->fscan) {
        fscan_release(__this->fscan);
        __this->fscan = NULL;
    }
    if (__this->dir_list) {
        fscan_release(__this->dir_list);
        __this->dir_list = NULL;
    }
    if (__this->local_bp_file) {
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        if (__this->last_sdram_prompt_flag) {
            __this->last_sdram_prompt_flag = 0;
            lfs_sdram_prompt_close(__this->local_bp_file);
        } else
#endif
        {
            fclose(__this->local_bp_file);
        }
        __this->local_bp_file = NULL;
        __this->lbp.local_bp.len = 0;
    }
    if (__this->lbp.local_bp.data) {
        free(__this->lbp.local_bp.data);
        __this->lbp.local_bp.data = NULL;
    }
    if (__this->led_ui) {
        server_close(__this->led_ui);
        __this->led_ui = NULL;
    }
#ifdef CONFIG_NET_ENABLE
    while (!list_empty(&__this->wechat_list)) {
        struct __wechat_url *first = list_first_entry(&__this->wechat_list, struct __wechat_url, entry);
        list_del(&first->entry);
        free(first->url);
        free(first);
        --__this->wechat_url_num;
    }
    if (__this->net_bp.dec_bp.data) {
        free(__this->net_bp.dec_bp.data);
        __this->net_bp.dec_bp.data = NULL;
    }
    if (__this->coexistence_timer) {
        sys_timeout_del(__this->coexistence_timer);
        __this->coexistence_timer = 0;
    }
#endif
}

/*
 *按键响应函数
 */
static int app_music_key_click(struct key_event *key)
{
    switch (key->value) {
    case KEY_MUTE:
        if (__this->wakeup_support) {
            __this->mute = 1;
            if (__this->play_voice_prompt) {
                app_music_stop_voice_prompt();
            } else {
                __this->dec_ops->dec_stop(1);
            }
            __this->wakeup_support = 0;
#if defined CONFIG_ASR_ALGORITHM
            aisp_suspend();
#endif
        } else {
            __this->mute = 0;
            __this->wakeup_support = 1;
            app_music_play_voice_prompt("KwsEnable.mp3", __this->dec_ops->dec_breakpoint);
#if defined CONFIG_ASR_ALGORITHM
            aisp_resume();
#endif
        }
        break;
    case KEY_OK:
        if (__this->play_voice_prompt) {
            app_music_stop_voice_prompt();
        } else {
            __this->dec_ops->dec_play_pause(1);
        }
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
        if (0 == __set_dec_volume(-VOLUME_STEP) && 0 == __this->dec_ops->dec_volume(-VOLUME_STEP)) {
#ifdef CONFIG_STORE_VOLUME
            syscfg_write(CFG_MUSIC_VOL, &__this->volume, sizeof(__this->volume));
#endif
#if TCFG_USER_EMITTER_ENABLE && TCFG_BT_SUPPORT_MUSIC_VOL_SYNC
#if TCFG_POWER_ON_ENABLE_EMITTER
            bt_emitter_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL);
#else
            if (__this->bt_emitter_enable) {
                bt_emitter_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL);
            }
#endif
#endif
        }
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
        if (0 == __set_dec_volume(VOLUME_STEP) && 0 == __this->dec_ops->dec_volume(VOLUME_STEP)) {
#ifdef CONFIG_STORE_VOLUME
            syscfg_write(CFG_MUSIC_VOL, &__this->volume, sizeof(__this->volume));
#endif
#if TCFG_USER_EMITTER_ENABLE && TCFG_BT_SUPPORT_MUSIC_VOL_SYNC
#if TCFG_POWER_ON_ENABLE_EMITTER
            bt_emitter_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL);
#else
            if (__this->bt_emitter_enable) {
                bt_emitter_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL);
            }
#endif
#endif
        }
        break;
#ifdef CONFIG_NET_ENABLE
#ifdef CONFIG_HOLD_SEND_VOICE
    case KEY_ENC:
        if (!__this->ai_connected || !__this->net_connected) {
            app_music_play_voice_prompt("AiAsrFail.mp3", __this->dec_ops->dec_breakpoint);
        } else {
            if (__this->voice_mode == AI_MODE) {
                __this->voice_mode = TRANSLATE_MODE;
                app_music_play_voice_prompt("AiTransMode.mp3", __this->dec_ops->dec_breakpoint);
            } else {
                __this->voice_mode = AI_MODE;
                app_music_play_voice_prompt("AiAsrMode.mp3", __this->dec_ops->dec_breakpoint);
            }
        }
        break;
    case KEY_F1:
        if (!__this->ai_connected || !__this->net_connected) {
            app_music_play_voice_prompt("SendMsgFail.mp3", __this->dec_ops->dec_breakpoint);
        } else {
#if defined CONFIG_ALI_SDK_ENABLE
            union ai_req req = {0};
            req.evt.event   = AI_EVENT_CUSTOM_FUN;
            req.evt.ai_name = "ali";
            req.evt.arg = 0;
            ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
            break;
#endif
            if (!list_empty(&__this->wechat_list)) {
                struct __wechat_url *wechat = list_first_entry(&__this->wechat_list, struct __wechat_url, entry);
                __this->dec_ops->dec_stop(1);
                if (AUDIO_DEC_START != __get_dec_status(0) && !__this->wait_download && !__this->reconnecting) {
                    net_music_dec_file(wechat->url, 0, NULL, 0);
                } else {
                    net_music_dec_file(wechat->url, 0, __this->dec_ops->dec_breakpoint, 0);
                }
                list_del(&wechat->entry);
                free(wechat->url);
                free(wechat);
                --__this->wechat_url_num;
            } else {
                app_music_play_voice_prompt("MsgEmpty.mp3", __this->dec_ops->dec_breakpoint);
            }
        }
        break;
#else
    case KEY_ENC:
#ifdef CONFIG_BT_ENABLE
        if (bt_get_total_connect_dev() > 0) {
#if TCFG_USER_EMITTER_ENABLE
            if (bt_emitter_role_get() == BT_EMITTER_EN) {
                if (bt_get_call_status() == BT_CALL_HANGUP) {
                    bt_emitter_esco_pp(1);
                } else {
                    bt_emitter_esco_pp(0);
                }
                break;
            } else
#endif
            {
                if (bt_get_call_status() == BT_CALL_INCOMING) {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
                } else if (bt_get_call_status() == BT_CALL_ACTIVE || bt_get_call_status() == BT_CALL_OUTGOING) {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO, 0, NULL);
                }
                break;
            }
        }
#endif
        if (0 == app_music_ai_listen_start(__this->voice_mode, 1)) {
            __this->listening = LISTEN_STATE_WAKEUP;
        }
        break;
    case KEY_F1:  //wechat
        if (0 == app_music_ai_listen_start(WECHAT_MODE, 0)) {
            __this->listening = LISTEN_STATE_WAKEUP;
        }
        break;
#endif
#endif
    case KEY_CANCLE:
    case KEY_POWER:
        local_music_play_mode_switch();
        break;
    case KEY_COLLECT:
#ifdef CONFIG_NET_ENABLE
        if (__this->ai_connected && __this->net_connected && __this->mode == NET_MUSIC_MODE) {
            union ai_req req = {0};
            req.evt.event   = AI_EVENT_COLLECT_RES;
            req.evt.ai_name = __this->ai_name;
            req.evt.arg = 0;
            ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
        }
#endif
        break;
    case KEY_MODE:
#ifdef CONFIG_BT_ENABLE
        if (__this->bt_music_enable) {
            __this->bt_music_enable = 0;
            if (__this->bt_emitter_enable) {
#if TCFG_USER_EMITTER_ENABLE
                app_music_play_voice_prompt("BtClose.mp3", bt_emitter_disable);	//关闭蓝牙
#endif
            } else {
                app_music_play_voice_prompt("BtClose.mp3", __this->dec_ops->dec_breakpoint);	//关闭蓝牙
                bt_connection_disable();
            }
        } else {
            app_music_play_voice_prompt("BtOpen.mp3", __this->dec_ops->dec_breakpoint);	//打开蓝牙
            __this->bt_music_enable = 1;
            bt_connection_enable();
        }
#endif
        break;
    case KEY_MENU:
#ifdef CONFIG_ASR_ALGORITHM
        if (__this->wakeup_support) {
            __this->wakeup_support = 0;
            app_music_play_voice_prompt("KwsDisable.mp3", __this->dec_ops->dec_breakpoint);
            aisp_suspend();
        } else {
            __this->wakeup_support = 1;
            app_music_play_voice_prompt("KwsEnable.mp3", __this->dec_ops->dec_breakpoint);
            aisp_resume();
        }
#endif
        break;
    case KEY_PHOTO:
#if defined CONFIG_VIDEO_ENABLE && defined CONFIG_NET_ENABLE
#if defined CONFIG_VIDEO_DISPLAY_ENABLE
        if (0) {
#else
        if (!__this->net_connected) {
#endif
            app_music_play_voice_prompt("AiPicFail.mp3", __this->dec_ops->dec_breakpoint);
        } else {
            /* 进入绘本朗读模式 */
            if (__this->picture_det_mode == PICTURE_DET_EXIT_MODE) {
                app_music_play_voice_prompt("PicModeIn.mp3", __this->dec_ops->dec_breakpoint);
                app_music_enter_picture_mode();
                __this->picture_det_mode = PICTURE_DET_ENTER_MODE;
            } else if (__this->picture_det_mode == PICTURE_DET_ENTER_MODE) {
                /* 退出绘本朗读模式 */
                __this->picture_det_mode = PICTURE_DET_EXIT_MODE;
                app_music_play_voice_prompt("PicModeOut.mp3", __this->dec_ops->dec_breakpoint);
                app_music_exit_picture_mode();
            }
        }
#endif
        break;
    default:
        break;
    }
    return false;
}

static int app_music_key_hold(struct key_event *key)
{
    switch (key->value) {
#ifdef CONFIG_NET_ENABLE
#ifdef CONFIG_HOLD_SEND_VOICE
    case KEY_ENC:
        app_music_ai_listen_start(__this->voice_mode, 0);
        break;
    case KEY_F1:  //wechat
        app_music_ai_listen_start(WECHAT_MODE, 0);
        break;
#endif
#endif
    case KEY_RIGHT:
        ++__this->seek_step;
        break;
    case KEY_LEFT:
        --__this->seek_step;
        break;
    case KEY_LOCAL:
        if (AUDIO_DEC_START == __this->dec_ops->dec_status(0)) {
            if (__this->play_voice_prompt) {
                app_music_stop_voice_prompt();
            } else {
                __this->dec_ops->dec_play_pause(1);
            }
        }
        break;
    default:
        break;
    }

    return false;
}

static int app_music_key_up(struct key_event *key)
{
    switch (key->value) {
#ifdef CONFIG_NET_ENABLE
#ifdef CONFIG_HOLD_SEND_VOICE
    case KEY_ENC:
        app_music_ai_listen_stop();
        break;
    case KEY_F1:
        app_music_ai_listen_stop();
        break;
#endif
#endif
    case KEY_LEFT:
    case KEY_RIGHT:
        if (__this->dec_ops->dec_seek) {
            __this->dec_ops->dec_seek(__this->seek_step);
        }
        __this->seek_step = 0;
        break;
    case KEY_LOCAL:
        if (AUDIO_DEC_PAUSE == __this->dec_ops->dec_status(0)) {
            if (__this->play_voice_prompt) {
                app_music_stop_voice_prompt();
            }
            __this->dec_ops->dec_play_pause(1);
        }
        break;
    default:
        break;
    }

    return false;
}

static int app_music_key_long(struct key_event *key)
{
    switch (key->value) {
    case KEY_OK:
#if TCFG_USER_EMITTER_ENABLE
        if (__this->bt_music_enable) {
            if (__this->bt_emitter_enable) {
                app_music_play_voice_prompt("EmitterOff.mp3", bt_emitter_switch_to_receiver);
            } else {
                app_music_play_voice_prompt("EmitterOn.mp3", bt_emitter_enable);
                bt_connection_disable();
            }
        }
#endif
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
        puts("music key up\n");
        __this->force_switch_file = 1;
        if (__this->dec_ops->switch_file) {
            __this->dec_ops->switch_file(FSEL_PREV_FILE);
        }
        __this->force_switch_file = 0;
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
        puts("music key down\n");
        __this->force_switch_file = 1;
        if (__this->dec_ops->switch_file) {
            __this->dec_ops->switch_file(FSEL_NEXT_FILE);
        }
        __this->force_switch_file = 0;
        break;
    case KEY_MODE:
#ifdef CONFIG_NET_ENABLE
        puts("switch_net_config\n");
        app_music_net_config();
#endif
        break;
    case KEY_POWER:
        app_music_shutdown(0);
        break;
    case KEY_MENU:
#if (defined PAYMENT_AUDIO_SDK_ENABLE)
        puts("payment_device_unbind\n");
        extern int payment_jl_cloud_device_unbind(void);
        int ret = payment_jl_cloud_device_unbind();
        if (ret == 0) {
            app_music_play_voice_prompt("UnbindSucc.mp3", NULL);
        } else if (ret == -2) {
            app_music_play_voice_prompt("NetEmpty.mp3", NULL);
        } else if (ret == 1) {
            app_music_play_voice_prompt("UnbindDef.mp3", NULL);
        } else {
            app_music_play_voice_prompt("UnbindFail.mp3", NULL);
        }
#endif
        break;
    case KEY_CANCLE:
        if (__this->mode >= LOCAL_MUSIC_MODE && __this->mode <= UDISK1_MUSIC_MODE && !__this->local_play_all) {
            puts("switch_next_dir\n");
            local_music_dec_switch_dir(FSEL_NEXT_FILE);
        }
        if (__this->mode == FM_MUSIC_MODE) {
            __this->dec_ops->switch_dir(FSEL_NEXT_FILE);
        }
        break;
    case KEY_COLLECT:
#ifdef CONFIG_NET_ENABLE
        if (__this->ai_connected && __this->net_connected) {
            union ai_req req = {0};
            req.evt.event   = AI_EVENT_COLLECT_RES;
#if defined CONFIG_TURING_SDK_ENABLE
            req.evt.ai_name = "wechat";
#elif defined CONFIG_ECHO_CLOUD_SDK_ENABLE
            req.evt.ai_name = "echo_cloud";
#elif defined CONFIG_DUER_SDK_ENABLE
            req.evt.ai_name = "duer";
#elif defined CONFIG_ALI_SDK_ENABLE
            req.evt.ai_name = "ali";
#else
            req.evt.ai_name = __this->ai_name;
#endif
            req.evt.arg = 1;
            ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
        }
#endif
        break;
    case KEY_PHOTO:
#ifdef CONFIG_REVERB_MODE_ENABLE
        if (__this->reverb_enable) {
#ifdef CONFIG_BT_ENABLE
            if (__this->dec_ops == get_bt_music_dec_ops()) {
                __this->dec_ops->dec_stop(0);	//让变采样过渡平滑
            }
#endif
            echo_reverb_uninit();
            __this->reverb_enable = 0;
            app_music_play_voice_prompt("ReverbExit.mp3", __this->dec_ops->dec_breakpoint);
        } else {
            const struct __HOWLING_PARM_ howling_parm = {13, 20, 20, 300, 5, -50000/*-25000*/, 0, 16000, 1};
#if CONFIG_AUDIO_ENC_SAMPLE_SOURCE != AUDIO_ENC_SAMPLE_SOURCE_MIC
            echo_reverb_init(48000, 16000, BIT(CONFIG_AUDIO_ENC_SAMPLE_SOURCE + 3), 100, __this->volume, NULL, NULL, (void *)&howling_parm, NULL);
#else
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
            echo_reverb_init(48000, 16000, BIT(CONFIG_REVERB_ADC_CHANNEL), 100, __this->volume, NULL, NULL, (void *)&howling_parm, NULL);
#else
            echo_reverb_init(48000, 16000, 0, 100, __this->volume, NULL, NULL, (void *)&howling_parm, NULL);
#endif
#endif
            app_music_play_voice_prompt("ReverbEnter.mp3", __this->dec_ops->dec_breakpoint);
            __this->reverb_enable = 1;
        }
#endif
        break;
    case KEY_ENC:
#ifdef CONFIG_BT_ENABLE
        if (bt_get_total_connect_dev() > 0) {
            if (bt_get_call_status() == BT_CALL_INCOMING) {
#if TCFG_USER_EMITTER_ENABLE
                if (bt_emitter_role_get() == BT_EMITTER_EN) {
                    bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
                } else
#endif
                {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
                }
                break;
            }
        }
#endif
#if defined CONFIG_NET_ENABLE && !defined CONFIG_HOLD_SEND_VOICE
        if (!__this->ai_connected || !__this->net_connected) {
            app_music_play_voice_prompt("AiAsrFail.mp3", __this->dec_ops->dec_breakpoint);
        } else {
            if (__this->voice_mode == AI_MODE) {
                __this->voice_mode = TRANSLATE_MODE;
                app_music_play_voice_prompt("AiTransMode.mp3", __this->dec_ops->dec_breakpoint);
#if defined CONFIG_TURING_SDK_ENABLE
            } else if (__this->voice_mode == TRANSLATE_MODE) {
                __this->voice_mode = ORAL_MODE;
                app_music_play_voice_prompt("052.mp3", __this->dec_ops->dec_breakpoint);
#endif
            } else {
                __this->voice_mode = AI_MODE;
                app_music_play_voice_prompt("AiAsrMode.mp3", __this->dec_ops->dec_breakpoint);
            }
        }
#endif
        break;
#if defined CONFIG_NET_ENABLE && !defined CONFIG_HOLD_SEND_VOICE
    case KEY_F1:
        if (!__this->ai_connected || !__this->net_connected) {
            app_music_play_voice_prompt("SendMsgFail.mp3", __this->dec_ops->dec_breakpoint);
        } else {
            if (!list_empty(&__this->wechat_list)) {
                struct __wechat_url *wechat = list_first_entry(&__this->wechat_list, struct __wechat_url, entry);
                __this->dec_ops->dec_stop(1);
                net_music_dec_file(wechat->url, 0, __this->dec_ops->dec_breakpoint, 0);
                list_del(&wechat->entry);
                free(wechat->url);
                free(wechat);
                --__this->wechat_url_num;
            } else {
                app_music_play_voice_prompt("MsgEmpty.mp3", __this->dec_ops->dec_breakpoint);
            }
        }
        break;
#endif
    default:
        break;
    }

    return false;
}

static int app_music_key_event_handler(struct key_event *key)
{
    int ret = false;

    if (__this->call_flag && (key->value != KEY_UP && key->value != KEY_DOWN && key->value != KEY_VOLUME_DEC && key->value != KEY_VOLUME_INC && key->value != KEY_OK && key->value != KEY_ENC)) {
        return true;	//通话模式下只有音量键和暂停键能起作用
    }

#ifdef CONFIG_NET_ENABLE
    if (__this->upgrading) {
        return true;	//升级过程中所有按键失效
    }

#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
    if (is_in_config_network_state() && key->value != KEY_MODE) {
#else
    if (is_in_config_network_state() && (key->action != KEY_EVENT_LONG || key->value != KEY_MODE)) {
#endif
        return true;	//配网模式下只有配网键能起作用
    }

#ifndef CONFIG_HOLD_SEND_VOICE
    if (__this->listening != LISTEN_STATE_STOP) {	//云端识别过程中过滤其它按键
        if (key->action != KEY_EVENT_CLICK || (key->value != KEY_ENC && key->value != KEY_F1)) {
            return ret;
        }
#ifdef CONFIG_ASR_ALGORITHM
        if (key->value == KEY_ENC) {
            __this->rec_again = 1;
            app_music_ai_listen_break();
        }
#endif
        app_music_ai_listen_stop();
        return ret;
    }
#endif
#endif

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = app_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = app_music_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        ret = app_music_key_hold(key);
        break;
    case KEY_EVENT_UP:
        ret = app_music_key_up(key);
        break;
    default:
        break;
    }

    return ret;
}

/*
 *设备响应函数
 */
static int app_music_device_event_handler(struct sys_event *sys_eve)
{
    struct device_event *device_eve = (struct device_event *)sys_eve->payload;
    int dev_id = 0;
    /*
     * SD卡插拔处理
     */
    if (sys_eve->from == DEVICE_EVENT_FROM_SD) {
        dev_id = ((const char *)device_eve->arg)[2] - '0';

        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            if (__this->mode == SDCARD0_MUSIC_MODE && dev_id == 0) {
                __this->wait_sd = wait_completion((int (*)(void *))sdcard_storage_device_ready,
                                                  (int (*)(void *))app_music_resume_local_music_mode,
                                                  CONFIG_MUSIC_PATH_SD0, device_eve->arg);
            }
            if (__this->mode == SDCARD1_MUSIC_MODE && dev_id == 1) {
                __this->wait_sd1 = wait_completion((int (*)(void *))sdcard_storage_device_ready,
                                                   (int (*)(void *))app_music_resume_local_music_mode,
                                                   CONFIG_MUSIC_PATH_SD1, device_eve->arg);
            }
            break;
        case DEVICE_EVENT_OUT:
            if ((__this->mode == SDCARD0_MUSIC_MODE && dev_id == 0) || (__this->mode == SDCARD1_MUSIC_MODE && dev_id == 1)) {
                if (__this->dec_ops == &local_music_dec_ops && !__this->play_voice_prompt) {
#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
                    __this->dec_ops->dec_stop(1);
#else
                    __this->dec_ops->dec_stop(0);
#endif
                } else {
                    __this->lbp.local_bp.len = 0;
                }

                app_music_switch_local_device("unknown");

                if (!dev_id && __this->wait_sd) {
                    wait_completion_del(__this->wait_sd);
                    __this->wait_sd = 0;
                }
                if (dev_id && __this->wait_sd1) {
                    wait_completion_del(__this->wait_sd1);
                    __this->wait_sd1 = 0;
                }
            }
            break;
        }
    } else if (sys_eve->from == DEVICE_EVENT_FROM_POWER) {
        if (device_eve->event == POWER_EVENT_POWER_CHANGE) {
            __this->battery_per = sys_power_get_battery_persent();
        } else if (device_eve->event == POWER_EVENT_POWER_WARNING) {
            app_music_play_voice_prompt("LowBatLevel.mp3", __this->dec_ops->dec_breakpoint);
        } else if (device_eve->event == POWER_EVENT_POWER_LOW) {
            log_d("low_power_shutdown\n");
            app_music_play_voice_prompt("LowBatOff.mp3", app_music_shutdown);
        } else if (device_eve->event == POWER_EVENT_POWER_AUTOOFF) {
            app_music_play_voice_prompt("PowerOff.mp3", app_music_shutdown);
        } else if (device_eve->event == POWER_EVENT_POWER_CHARGE) {

        }
#if TCFG_UDISK_ENABLE
    } else if (sys_eve->from == DEVICE_EVENT_FROM_USB_HOST && !strncmp((const char *)device_eve->value, "udisk", 5)) {
        dev_id = ((const char *)device_eve->value)[5] - '0';

        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            if (__this->mode == UDISK0_MUSIC_MODE && dev_id == 0) {
                __this->wait_udisk = wait_completion((int (*)(void *))udisk_storage_device_ready,
                                                     (int (*)(void *))app_music_resume_local_music_mode,
                                                     CONFIG_MUSIC_PATH_UDISK0, (void *)dev_id);
                __this->udisk_upgrade_timer = sys_timeout_add((void *)dev_id, udisk_upgrade, 3000);
            }
            if (__this->mode == UDISK1_MUSIC_MODE && dev_id == 1) {
                __this->wait_udisk1 = wait_completion((int (*)(void *))udisk_storage_device_ready,
                                                      (int (*)(void *))app_music_resume_local_music_mode,
                                                      CONFIG_MUSIC_PATH_UDISK1, (void *)dev_id);
                __this->udisk1_upgrade_timer = sys_timeout_add((void *)dev_id, udisk_upgrade, 3000);
            }
            break;
        case DEVICE_EVENT_OUT:
            if ((__this->mode == UDISK0_MUSIC_MODE && dev_id == 0) || (__this->mode == UDISK1_MUSIC_MODE && dev_id == 1)) {
                if (__this->dec_ops == &local_music_dec_ops && !__this->play_voice_prompt) {
#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
                    __this->dec_ops->dec_stop(1);
#else
                    __this->dec_ops->dec_stop(0);
#endif
                } else {
                    __this->lbp.local_bp.len = 0;
                }

                app_music_switch_local_device("unknown");

                if (!dev_id && __this->wait_udisk) {
                    wait_completion_del(__this->wait_udisk);
                    __this->wait_udisk = 0;
                }
                if (dev_id && __this->wait_udisk1) {
                    wait_completion_del(__this->wait_udisk1);
                    __this->wait_udisk1 = 0;
                }
            }
            if (__this->udisk_upgrade_timer && dev_id == 0) {
                sys_timeout_del(__this->udisk_upgrade_timer);
                __this->udisk_upgrade_timer = 0;
            }
            if (__this->udisk1_upgrade_timer && dev_id == 1) {
                sys_timeout_del(__this->udisk1_upgrade_timer);
                __this->udisk1_upgrade_timer = 0;
            }
            break;
        }
#endif
    }

    return false;
}

#ifdef CONFIG_NET_ENABLE
#include <time.h>
extern char get_MassProduction(void);

int net_dhcp_ready(void)
{
#ifdef CONFIG_MASS_PRODUCTION_ENABLE
    if (get_MassProduction()) {
        return 0;
    }
#endif
    return __this->_net_dhcp_ready;
}

static int app_music_net_event_handler(struct net_event *event)
{
    if (!ASCII_StrCmp(event->arg, "net", 4)) {
        switch (event->event) {
        case NET_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        case NET_CONNECT_ASSOCIAT_FAIL:
            if (__this->mode == NET_MUSIC_MODE) {
                app_music_play_voice_prompt("NetCfgFail.mp3", NULL);
#if defined CONFIG_TURING_SDK_ENABLE && TCFG_BT_NET_CFG_TURING_EN
                turing_ble_cfg_net_result_notify(0, NULL, NULL, NULL);
#elif TCFG_BT_NET_CFG_EN
                ble_cfg_net_result_notify(event->event);
#endif
            }
            break;
        case NET_EVENT_SMP_CFG_FIRST:
            if (__this->mode == NET_MUSIC_MODE) {
                app_music_play_voice_prompt("NetEmpty.mp3", NULL);
            }
            break;
        case NET_EVENT_SMP_CFG_FINISH:
            if (is_in_config_network_state()) {
#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
                if (get_bt_music_dec_ops()->dec_status(0) == AUDIO_DEC_START) {
                    app_music_play_voice_prompt("SsidRecv.mp3", __this->dec_ops->dec_breakpoint);
                } else
#endif
                {
                    app_music_play_voice_prompt("SsidRecv.mp3", NULL);
                }
                config_network_stop();
                config_network_connect();
#ifdef CONFIG_ASR_ALGORITHM
                if (__this->wakeup_support) {
                    aisp_resume();
                }
#endif
#if defined CONFIG_BT_ENABLE && !TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
                //避免打开蓝牙自动回连设备时挡住wifi连接
                switch_rf_coexistence_config_table(3);
                switch_rf_coexistence_config_lock();
                __this->coexistence_timer = sys_timeout_add(NULL, switch_rf_coexistence_timer, 15000);
                if (__this->bt_music_enable) {
                    bt_connection_enable();
                }
#endif
                sys_power_auto_shutdown_resume();
#if TCFG_USER_BLE_ENABLE && (TCFG_BT_NET_CFG_EN || TCFG_BT_NET_CFG_DUI_EN) && TCFG_POWER_ON_ENABLE_BLE || (defined PAYMENT_AUDIO_SDK_ENABLE)
            } else {
#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
                if (get_bt_music_dec_ops()->dec_status(0) == AUDIO_DEC_START) {
                    app_music_play_voice_prompt("SsidRecv.mp3", __this->dec_ops->dec_breakpoint);
                } else
#endif
                {
                    app_music_play_voice_prompt("SsidRecv.mp3", NULL);
                }
                config_network_connect();
                __this->reconnecting = 1;
#endif
            }
            break;
        case NET_EVENT_CONNECTED:
            puts("NET_EVENT_CONNECTED\n");

            __this->_net_dhcp_ready = 1;

#ifdef CONFIG_SCAN_PEN_ENABLE
#ifdef CONFIG_UI_ENABLE
            user_ui_lcd_init();
            static char str2[] = "连接成功";
            ui_text_set_textu_by_id(BASEFORM_5, str2, strlen(str2), FONT_DEFAULT | FONT_SHOW_MULTI_LINE);
            os_time_dly(100);
            static char str3[] = "扫描笔测试开始";
            ui_text_set_textu_by_id(BASEFORM_5, str3, strlen(str3), FONT_DEFAULT | FONT_SHOW_MULTI_LINE);
#else
            printf("please enable CONFIG_UI_ENABLE");
#endif
#endif

#ifdef CONFIG_ELINK_QLINK_NET_CFG
            extern unsigned int elink_connect_ok(void);
            if (elink_connect_ok()) {
                extern int elink_dev_connet_wifi_success(void);
                elink_dev_connet_wifi_success();
            }
#endif

#ifdef WIFI_PCM_STREAN_SOCKET_ENABLE
            extern void wifi_pcm_stream_task_init(void);
            wifi_pcm_stream_task_init();
#endif

            if (!is_in_config_network_state()) {
#if TCFG_BT_NET_CFG_EN
                ble_cfg_net_result_notify(event->event);
#endif
                app_music_play_voice_prompt("NetCfgSucc.mp3", __this->dec_ops->dec_breakpoint);
                __this->reconnecting = 0;
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
                dev_profile_init();
#endif
                app_music_event_net_connected();
            }
            __this->net_connected = 1;
            if (__this->coexistence_timer) {
                sys_timeout_del(__this->coexistence_timer);
                __this->coexistence_timer = 0;
                switch_rf_coexistence_config_unlock();
                switch_rf_coexistence_config_table(0);
            }
            break;
        case NET_EVENT_DISCONNECTED:
            puts("NET_EVENT_DISCONNECTED\n");
            if (!__this->_net_dhcp_ready) {
                break;
            }
            canceladdrinfo();
            __this->_net_dhcp_ready = 0;

            if (__this->net_connected && !is_in_config_network_state() && !__this->reconnecting && __this->mode == NET_MUSIC_MODE) {
                app_music_play_voice_prompt("NetDisc.mp3", NULL);
            }
            __this->net_connected = 0;
            return false;
        case NET_EVENT_SMP_CFG_TIMEOUT:
            if (is_in_config_network_state()) {
#if defined CONFIG_BT_ENABLE && TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
                if (get_bt_music_dec_ops()->dec_status(0) == AUDIO_DEC_START) {
                    app_music_play_voice_prompt("NetCfgTo.mp3", __this->dec_ops->dec_breakpoint);
                } else
#endif
                {
                    app_music_play_voice_prompt("NetCfgTo.mp3", NULL);
                }
            }
            break;

        case NET_SMP_CFG_COMPLETED:
#ifdef CONFIG_AIRKISS_NET_CFG
            wifi_smp_set_ssid_pwd();
#endif
            break;
        case NET_EVENT_DISCONNECTED_AND_REQ_CONNECT:
            wifi_return_sta_mode();
            break;
        case NET_NTP_GET_TIME_SUCC:	//NTP获取成功事件返回
            break;
        default:
            break;
        }
    }

    return false;
}
#endif

#ifdef CONFIG_BT_ENABLE
void set_bt_dec_end_handler(void *handler)
{
    __this->dec_end_handler = handler;
}

u8 get_bt_connecting_flag(void)
{
    return __this->bt_connecting;
}

void set_app_music_dec_ops(const struct music_dec_ops *ops)
{
    if (!__this->bt_connecting) {
        app_music_stop_voice_prompt();
    }
    if (__this->mode == NET_MUSIC_MODE) {
        app_music_play_mode_switch_notify();
        __this->dec_ops->dec_stop(1);
    } else if (__this->mode != BT_MUSIC_MODE) {
        __this->dec_ops->dec_stop(0);
        app_music_play_mode_switch_notify();
    }
    __this->mode = BT_MUSIC_MODE;
    __this->dec_ops = get_bt_music_dec_ops();
}

static int app_music_bt_event_handler_pretreatment(struct bt_event *event)
{
#if 0//CONFIG_POWER_ON_ENABLE_BT && defined CONFIG_NET_ENABLE
    if (BT_STATUS_INIT_OK == event->event) {
        //避免打开蓝牙自动回连设备时挡住wifi连接
        switch_rf_coexistence_config_table(3);
        switch_rf_coexistence_config_lock();
        __this->coexistence_timer = sys_timeout_add(NULL, switch_rf_coexistence_timer, 15000);
    }
#endif

    if (BT_STATUS_A2DP_MEDIA_START == event->event || BT_STATUS_SCO_STATUS_CHANGE == event->event) {
        set_app_music_dec_ops(NULL);

        if (BT_STATUS_SCO_STATUS_CHANGE == event->event) {
            __this->call_flag = event->value == 0xff ? 0 : 1;
#ifdef CONFIG_REVERB_MODE_ENABLE
            if (__this->reverb_enable) {
                if (__this->call_flag) {
                    echo_deal_pause();
                } else {
                    echo_deal_start();
                }
            }
#endif
#ifdef CONFIG_ASR_ALGORITHM
            if (__this->wakeup_support) {
                if (__this->call_flag) {
                    aisp_suspend();
                } else {
                    aisp_resume();
                }
            }
#endif
        }
    }

    return 0;
}
#endif

static int app_music_event_handler(struct application *app, struct sys_event *event)
{
#ifdef CONFIG_WIFIBOX_ENABLE
    u8 get_wbcp_connect_status(void);
    if (get_wbcp_connect_status()) {
#ifdef CONFIG_BT_ENABLE
        if (event->type == SYS_BT_EVENT) {
            app_music_bt_event_handler_pretreatment((struct bt_event *)event->payload);
            return app_music_bt_event_handler(event);
        }
        return false;
#endif
    }
#endif

    switch (event->type) {
    case SYS_KEY_EVENT:
        return app_music_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return app_music_device_event_handler(event);
#ifdef CONFIG_NET_ENABLE
    case SYS_NET_EVENT:
        return app_music_net_event_handler((struct net_event *)event->payload);
#endif
#ifdef CONFIG_BT_ENABLE
    case SYS_BT_EVENT:
        if (event->from == BT_EVENT_FROM_CON) {
            app_music_bt_event_handler_pretreatment((struct bt_event *)event->payload);
        }
        return app_music_bt_event_handler(event);
#endif
    default:
        return false;
    }
}

static int app_music_state_machine(struct application *app, enum app_state state,
                                   struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        memset(__this, 0, sizeof(struct app_music_hdl));
#ifdef CONFIG_NET_ENABLE
        __this->ai_name = "unknown";
        __this->net_bp.url = malloc(512);
        __this->net_bp.url_len = 512;
        INIT_LIST_HEAD(&__this->wechat_list);
        __this->mode = NET_MUSIC_MODE;	//开机默认网络模式
        __this->dec_ops = &net_music_dec_ops;
#else
#ifdef CONFIG_BT_ENABLE
        __this->mode = BT_MUSIC_MODE;
        __this->dec_ops = get_bt_music_dec_ops();
#else
        __this->mode = LOCAL_MUSIC_MODE;
        __this->dec_ops = &local_music_dec_ops;
#endif
#endif

#ifdef CONFIG_RESUME_LOCAL_PLAY_FILE
        __this->local_play_all = 1;
#endif
        __this->local_play_mode = LOOP_PLAY_MODE;
#ifdef CONFIG_ASR_ALGORITHM
        __this->wakeup_support = 1;
#endif
#ifdef CONFIG_BT_ENABLE
#if TCFG_POWER_ON_ENABLE_BT
        __this->bt_music_enable = 1;
#else
        __this->bt_music_enable = 0;
#endif
#endif
#ifdef CONFIG_LED_UI_ENABLE
        __this->light_intensity = 100;
        __this->led_ui = server_open("led_ui_server", NULL);
        if (!__this->led_ui) {
            log_e("led_ui open server err!\n");
            return -EINVAL;
        }
#endif
        __this->battery_per = 100;
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
#ifdef CONFIG_LOAD_SDRAM_PROMPT_PLAY
        lfs_sdram_prompt_init();
#endif
        switch (it->action) {
        case ACTION_MUSIC_PLAY_MAIN:
            app_music_main();
            break;
        case ACTION_MUSIC_PLAY_VOICE_PROMPT:
#ifdef CONFIG_NET_ENABLE
#if TCFG_POWER_ON_ENABLE_EMITTER
            if (is_in_config_network_state() && !strcmp((const char *)it->data, "BtDisc.mp3")) {
#elif TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE
            if (!__this->bt_music_enable && !strcmp((const char *)it->data, "BtDisc.mp3")) {
#else
            if ((!__this->bt_music_enable || is_in_config_network_state()) && !strcmp((const char *)it->data, "BtDisc.mp3")) {
#endif
                break;	//蓝牙关闭后不需要蓝牙断开提示音
            }
#endif
            if (!strcmp((const char *)it->data, "BtSucceed.mp3") && __this->dec_end_handler != (void *)app_music_shutdown) {
                if (__this->play_voice_prompt) {
                    local_music_dec_ops.dec_stop(0);
                    __this->play_voice_prompt = 0;
                }
                __this->bt_connecting = 1;
            }
#ifdef CONFIG_BT_ENABLE
#if TCFG_BT_DUAL_CONN_ENABLE
            if (!strcmp((const char *)it->data, "BtDisc.mp3") && bt_get_total_connect_dev() > 0) {
                __this->bt_auto_play_another_dev = 1;
            }
#endif
            if (__this->dec_ops == get_bt_music_dec_ops() && !strcmp((const char *)it->data, "ring.mp3")) {
                it->exdata = 1;          //蓝牙通话进来时被mute掉需要恢复断点
            }
#endif
            if (it->exdata) {
                app_music_play_voice_prompt(it->data, __this->dec_ops->dec_breakpoint);
            } else {
                app_music_play_voice_prompt(it->data, NULL);
            }
#ifdef CONFIG_BT_ENABLE
            if (!strcmp((const char *)it->data, "ring.mp3")) {
                /* set_app_music_dec_ops(NULL); */
            }
#endif
            break;
        case ACTION_MUSIC_PLAY_FILE:
            if (it->data) {
                FILE *file = fopen(it->data, "r");
                if (file) {
                    local_music_dec_file(file, 0, NULL, 0);
                }
            }
            break;
        }
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        app_music_exit();
        break;
    }

    return 0;
}

static const struct application_operation app_music_ops = {
    .state_machine  = app_music_state_machine,
    .event_handler 	= app_music_event_handler,
};

#if !TCFG_RF_FCC_TEST_ENABLE
REGISTER_APPLICATION(app_music) = {
    .name 	= "app_music",
    .ops 	= &app_music_ops,
    .state  = APP_STA_DESTROY,
};
#endif

#endif

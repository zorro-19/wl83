#include "app_config.h"

#ifdef CONFIG_TUYA_SDK_ENABLE
#include "system/includes.h"
#include "device/device.h"
#include "event/device_event.h"
#include "usb/host/usb_host.h"
#include "usb/host/audio.h"
#include "server/audio_server.h"
#include "server/server_core.h"
#include "generic/circular_buf.h"

#include "tuya_hal_system.h"
#include "uni_log.h"
#include "tuya_os_adapter.h"
#include "uni_thread.h"
#include "uni_msg_queue.h"
#include "tuya_hal_semaphore.h"
#include "tuya_cloud_types.h"
#include "uni_pointer.h"
#include "sys_timer.h"
#include "tuya_device.h"
#include "tuya_video.h"
#include "tuya_audio.h"
#include "tal_memory.h"
#include "tkl_queue.h"


#ifndef TY_HOST_UAC_WITH_HW_AUDIO
#define TY_HOST_UAC_WITH_HW_AUDIO             1
#endif


#define TY_AUDIO_TEST   0//仅供测试使用  设置1时 启动后mic收音直接通过喇叭发出来，测试麦克风和喇叭是否正常
#define MSG_START_NET_AUDIO_PLAY   1
#define MSG_START_LOCAL_AUDIO_PLAY   2
#define MSG_STOP_NET_AUDIO_PLAY   3
#define MSG_STOP_LOCAL_AUDIO_PLAY   4
#define MSG_START_AUDIO_RECORDER   5
#define MSG_STOP_AUDIO_RECORDER   6
#define MSG_START_AUDIO_TEST   7
#define MSG_STOP_AUDIO_TEST  8
#define MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST   9
#define MSG_STOP_AUDIO_RECORDER_AND_START_PLAY_TEST   10
#define MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_STOP_PLAY_TEST   11

#if TY_HOST_UAC_WITH_HW_AUDIO
#define MSG_HW_START_LOCAL_AUDIO_PLAY  20
#define MSG_HW_STOP_LOCAL_AUDIO_PLAY   21
#endif


#define AUDIO_PLAY_VOICE_VOLUME   100
#define AUDIO_RECORD_VOICE_VOLUME 100
#define AUDIO_RECORD_VOICE_UPLORD_LEN (1280)
#define TY_AUDIO_TASK_NAME    "audio_task"
#define TY_AUDIO_WAIT_TIMEOUT    500
#define TY_AUDIO_UAC_TRY_TIMES    10

#define MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_STOP   0
#define MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_START   1
#define MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_RECORDER_START   2
#define MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_PLAY_START   3

typedef struct {
    CHAR_T *play_src;
    INT_T   play_src_len;
    INT_T   play_len;
} TY_AUDIO_LOCAL_MSG;

typedef unsigned short WORD;

typedef struct {
    cbuffer_t pcm_cbuff_w;
    cbuffer_t pcm_cbuff_r;
    struct server *enc_server;
    struct server *dec_server;
    UCHAR_T   status;
    BOOL_T is_audio_play_open;
    BOOL_T is_audio_record_open;
#if TY_HOST_UAC_WITH_HW_AUDIO
    TY_HW_LOCAL_HDL local_hw_handler;
#endif
} TY_AUDIO_HANDLE;

typedef struct {
    SEM_HANDLE    r_sem;
    OS_QUEUE msg_que;
    BOOL_T pcm_wait_sem;
    THRD_HANDLE task_handle;
} TY_AUDIO_CTRL;

typedef struct {
    UINT_T              cmd;
    UCHAR_T             *data;
    UINT_T              data_len;
} TY_AUDIO_CTRL_MSG;

STATIC TY_AUDIO_CTRL g_audio_ctrl = {0};
STATIC TY_AUDIO_HANDLE g_audio_hdl = {0};
STATIC TY_AUDIO_LOCAL_MSG  g_local_file = {0};
STATIC UINT_T PCM_SAMPLE_RATE = 8000;//48000;//8000;
STATIC UINT_T PCM_CHANNEL     = 1;
STATIC UINT_T PCM_BIT_DEP     = 16;
STATIC CHAR_T audio_data[AUDIO_RECORD_VOICE_UPLORD_LEN] = {0};
STATIC UINT_T voice_buf_size = AUDIO_RECORD_VOICE_UPLORD_LEN;
STATIC INT_T audio_power_off = 0;
STATIC INT_T audio_uac_retry_times = 0;
STATIC UINT_T audio_test_recorder_first_play_next = 0;
STATIC UINT_T audio_test_recorder_first_play_times = 0;
STATIC TIMER_ID  audio_test_timer_id = 0;


FILE *fp = NULL;
/***************************************audio*********************************************/

#if 0
VOID audio_power_en(BOOL_T status)
{
#if defined(TY_OLD_BORD) && (TY_OLD_BORD == 1)

    if (status) {
        tuya_jl_gpio_inout_set(POWER_AUDIO_GPIO_PH7, FALSE);
        tuya_jl_gpio_write(POWER_AUDIO_GPIO_PH7, TRUE);
    } else {
        tuya_jl_gpio_inout_set(POWER_AUDIO_GPIO_PH7, FALSE);
        tuya_jl_gpio_write(POWER_AUDIO_GPIO_PH7, FALSE);
    }
#else
    if (status) {
        tuya_jl_gpio_inout_set(POWER_AUDIO_GPIO_PH4, FALSE);
        tuya_jl_gpio_write(POWER_AUDIO_GPIO_PH4, TRUE);
    } else {
        tuya_jl_gpio_inout_set(POWER_AUDIO_GPIO_PH4, FALSE);
        tuya_jl_gpio_write(POWER_AUDIO_GPIO_PH4, FALSE);
    }
#endif
}
#endif // 0

STATIC OPERATE_RET tuya_send_audio_msg(IN CONST UINT_T msgid, IN CONST VOID *data, IN CONST UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T msg_num = 0;
    if (!&g_audio_ctrl.msg_que) {
        return OPRT_MSG_OUT_OF_LMT;
    }

    TY_AUDIO_CTRL_MSG *msg_data;
    msg_data = Malloc(sizeof(TY_AUDIO_CTRL_MSG) + 1);
    if (!msg_data) {
        return OPRT_MALLOC_FAILED;
    }
    memset(msg_data, 0, SIZEOF(TY_AUDIO_CTRL_MSG) + 1);
    msg_data->cmd = msgid;

    if (data && len) {
        msg_data->data = Malloc(len + 1);
        if (!msg_data->data) {
            if (msg_data) {
                Free(msg_data);
            }
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data->data, 0, len + 1);
        memcpy(msg_data->data, data, len);
        msg_data->data_len = len;
    } else {
        msg_data->data = NULL;
    }

    op_ret = os_q_post(&g_audio_ctrl.msg_que, msg_data);
    if (OPRT_OK != op_ret) {
        if (msg_data->data) {
            Free(msg_data->data);
        }
        if (msg_data) {
            Free(msg_data);
        }
        return op_ret;
    }

    return OPRT_OK;
}

STATIC VOID tuya_audio_test_timer_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    PR_NOTICE("tuya_audio_test_timer_cb step=%d ", audio_test_recorder_first_play_next);
    if (MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_RECORDER_START == audio_test_recorder_first_play_next) {
        tuya_send_audio_msg(MSG_STOP_AUDIO_RECORDER_AND_START_PLAY_TEST, NULL, 0);
    } else if (MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_PLAY_START == audio_test_recorder_first_play_next) {
        tuya_send_audio_msg(MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_STOP_PLAY_TEST, NULL, 0);
    }

}

STATIC OPERATE_RET tuya_audio_test_timer_init_and_start(UINT_T interval)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T heap_size = 0;
    if (0 == audio_test_timer_id) {
        op_ret = sys_add_timer(tuya_audio_test_timer_cb, NULL, &audio_test_timer_id);
        if (OPRT_OK != op_ret) {
            PR_ERR("sys_add_timer tuya_audio_test_timer_cb err:%d", op_ret);
            return op_ret;
        }
    }
    PR_NOTICE("tuya_audio_test_timer_init_and_start interval=%d ", interval);
    op_ret = sys_start_timer(audio_test_timer_id, interval, TIMER_ONCE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_start_timer err:%d", op_ret);
        return op_ret;
    }

    return op_ret;
}

INT_T ty_device_get_voice_data(VOID *data, UINT_T max_len)
{
    cbuffer_t *cbuf = (cbuffer_t *)&g_audio_hdl.pcm_cbuff_w;
    UINT_T rlen;
    rlen = cbuf_get_data_size(cbuf);
    if (rlen == 0) {
        PR_DEBUG("ty_device_get_voice_data no data");
        return 0;
    } else {
        // PR_DEBUG("ty_device_get_voice_data %d",rlen);
    }
    rlen = rlen > max_len ? max_len : rlen;
    cbuf_read(cbuf, data, rlen);
    return rlen;
}


INT_T ty_device_write_net_voice_data(VOID *data, UINT_T len)
{
    cbuffer_t *cbuf = (cbuffer_t *)&g_audio_hdl.pcm_cbuff_r;
    INT_T  i = 0;
//    printf("put audio data!");
//    put_buf(data,len);
    UINT_T wite_len = cbuf_write(cbuf, data, len);
    /* PR_DEBUG("len=%d wite_len=%d", len, wite_len); */
    if (0 == wite_len) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        cbuf_clear(cbuf);
        //user_printf("cbuf_write full");
    } else if (wite_len != len) {
        UINT_T rlen = cbuf_get_data_size(cbuf);
        PR_DEBUG("wite_len %d len %d rlen %d", wite_len, len, rlen);
    }
    if (g_audio_ctrl.pcm_wait_sem) {
        tuya_hal_semaphore_post(g_audio_ctrl.r_sem);
    }
    //此回调返回0录音就会自动停止
    return len;
}

#if TY_HOST_UAC_WITH_HW_AUDIO

#define INIT_VOLUME_VALUE   100
#define DEC_BUF_LEN      12 * 1024
#define __this 	(&(g_audio_hdl.local_hw_handler))

static const struct music_dec_ops local_music_dec_ops;

static const struct {
    APP_LOCAL_PROMPT_TYPE_E prompt_type;
    const char *file_name;
} local_prompt_table[] = {
    {APP_LOCAL_PROMPT_DOOR_CALL,                "doorcall.mp3"},
};


static const char *find_local_prompt_filename(APP_LOCAL_PROMPT_TYPE_E prompt_type)
{
    for (int i = 0; i < ARRAY_SIZE(local_prompt_table); ++i) {
        if (local_prompt_table[i].prompt_type == prompt_type) {
            return local_prompt_table[i].file_name;
        }
    }
    return NULL;
}




static int __get_dec_breakpoint(struct audio_dec_breakpoint *bp)
{
    int err;
    union audio_req r = {0};
    PR_NOTICE("__get_dec_breakpoint");
    bp->len = 0;
    r.dec.bp = bp;
    r.dec.cmd = AUDIO_DEC_GET_BREAKPOINT;

    if (bp->data) {
        free(bp->data);
        bp->data = NULL;
    }

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    if (err) {
        return err;
    }

    if (r.dec.status == AUDIO_DEC_STOP) {
        bp->len = 0;
        free(bp->data);
        bp->data = NULL;
        return -EFAULT;
    }
    /* put_buf(bp->data, bp->len); */

    return 0;
}

static int __get_dec_status(int priv)
{
    union audio_req req = {0};
    PR_NOTICE("__get_dec_status");
    req.dec.cmd     = AUDIO_DEC_GET_STATUS;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    return req.dec.status;
}


static void app_music_stop_voice_prompt(void)
{
    if (__this->play_voice_prompt) {
        local_music_dec_ops.dec_stop(0);
        __this->play_voice_prompt = 0;
        __this->prompt_type = APP_LOCAL_PROMPT_NULL;
    }
}

static int local_music_dec_play_pause(u8 notify)
{
    union audio_req r = {0};
    PR_NOTICE("local_music_dec_play_pause");
    r.dec.cmd = AUDIO_DEC_PP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &r);
    return 0;
}

static int local_music_dec_stop(int save_breakpoint)
{
    int err = 0;
    union audio_req req;

    if (!__this->file) {
        return 0;
    }

    PR_NOTICE("local_music_dec_stop");

    req.dec.cmd = AUDIO_DEC_STOP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    int argv[2];
    argv[0] = AUDIO_SERVER_EVENT_END;
    argv[1] = (int)__this->file;
    server_event_handler_del(__this->dec_server, 2, argv);

    fclose(__this->file);
    __this->file = NULL;

    return 0;
}

static int audio_dec_data_callback(u8 *buf, u32 len, u32 sample_rate, u8 ch_num)
{
    static int total_num = 0;
    total_num += len;
    //PR_NOTICE("channel=%d sample_rate=%d len=%d total_num=%d",ch_num,sample_rate,len,total_num);
    return len;
}
//解码器读取PCM数据
STATIC INT_T audio_play_hw_vfs_fread(VOID *file, VOID *data, UINT_T len)
{
    INT_T rlen = 0;
    rlen = fread_fast(data, 1, len, file);
    //PR_NOTICE("audio_play_hw_vfs_fread len %d rlen %d",len,rlen);
    return rlen;
}
STATIC INT_T audio_play_hw_vfs_fseek(VOID *file, UINT_T offset, INT_T seek_mode)
{
    //PR_NOTICE("audio_play_hw_vfs_fseek offset =%d seek_mode=%d",offset,seek_mode);
    return fseek_fast(file, offset, seek_mode);
}

STATIC INT_T audio_play_hw_vfs_flen(VOID *file)
{
    INT_T len;
    len = flen(file);
    //PR_NOTICE("audio_play_hw_vfs_flen=%d",len);
    return len;
}

STATIC INT_T audio_play_hw_vfs_fclose(VOID *file)
{
    //PR_NOTICE("audio_play_hw_vfs_fclose");
    return 0;
}
STATIC CONST struct audio_vfs_ops audio_play_hw_vfs_ops = {
    .fread  = audio_play_hw_vfs_fread,
    .fseek   = audio_play_hw_vfs_fseek,
    .fclose = audio_play_hw_vfs_fclose,
    .flen   = audio_play_hw_vfs_flen,
};

/*
 * 选择文件并播放, mode为选择方式，如FSEL_NEXT_FILE
 */

static int local_music_dec_file(void *file, int breakpoint, void *handler, int arg)
{
    int err;
    union audio_req req = {0};
    PR_NOTICE("app_music_dec_local_file");
    __this->dec_ops->dec_stop(0);
    if (!file) {
        return -1;
    }

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = DEC_BUF_LEN;
    req.dec.file            = (FILE *)file;
    req.dec.channel         = 0;
    req.dec.sample_rate     = 0;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &audio_play_hw_vfs_ops;
    req.dec.sample_source   = "dac";
    req.dec.dec_type = "mp3";
    //req.dec.dec_callback = audio_dec_data_callback;
    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        PR_ERR("audio_dec_open: err = %d", err);
        fclose((FILE *)file);
        return err;
    }

    //PR_NOTICE("play_time=%d total_time=%d channel=%d sample_rate=%d",req.dec.play_time,req.dec.total_time,req.dec.channel,req.dec.sample_rate);

    req.dec.cmd = AUDIO_DEC_START;

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        PR_ERR("audio_dec_start: err = %d", err);
        fclose((FILE *)file);
        return err;
    }
    __this->file = (FILE *)file;

    PR_NOTICE("play_music_file: suss");


    return 0;
}

static int local_music_dec_switch_file(int fsel_mode)
{
    PR_NOTICE("local_music_dec_switch_file");
    return 0;
}

static int local_music_dec_switch_dir(int fsel_mode)
{
    PR_NOTICE("local_music_dec_switch_dir");
    return 0;
}

static int local_music_dec_breakpoint(int priv)
{
    return 0;
}

static int local_musci_dec_progress(int time)
{
    PR_NOTICE("local_musci_dec_progress");
    return 0;
}

static int local_music_dec_volume(int step)
{
    PR_NOTICE("local_music_dec_volume");
    return 0;
}

static int local_music_dec_seek(int seek_step)
{
    PR_NOTICE("local_music_dec_seek");
    return 0;
}

static const struct music_dec_ops local_music_dec_ops = {
    .switch_dir     = local_music_dec_switch_dir,
    .switch_file    = local_music_dec_switch_file,
    .dec_file       = local_music_dec_file,
    .dec_breakpoint = local_music_dec_breakpoint,
    .dec_play_pause = local_music_dec_play_pause,
    .dec_volume     = local_music_dec_volume,
    .dec_progress   = local_musci_dec_progress,
    .dec_stop       = local_music_dec_stop,
    .dec_seek       = local_music_dec_seek,
    .dec_status     = __get_dec_status,
};


static void dec_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
    //PR_ERR("app_music: AUDIO_SERVER_EVENT_ERR");
    case AUDIO_SERVER_EVENT_END:
        //PR_NOTICE("app_music: AUDIO_SERVER_EVENT_END");
        if (__this->play_voice_prompt) {
            local_music_dec_ops.dec_stop(0);
            __this->play_voice_prompt = 0;
            __this->prompt_type = APP_LOCAL_PROMPT_NULL;
        }
        break;
    case AUDIO_SERVER_EVENT_CURR_TIME:
        // PR_NOTICE("play_time: %d", argv[1]);
        break;
    }
}

static int __play_voice_prompt(APP_LOCAL_PROMPT_TYPE_E name, void *dec_end_handler, int save_bp)
{
    int err;
    char path[64];
    char *fname = NULL;
    if (__this->prompt_type == name) {
        return -1;
    }
    if (name < APP_LOCAL_PROMPT_NUMM) {
        fname = find_local_prompt_filename(name);
        if (!fname) {
            return -1;
        }
    } else {
        return -1;
    }

    sprintf(path, "%s%s", CONFIG_VOICE_PROMPT_FILE_PATH, fname);

    //PR_NOTICE("play_voice_prompt: %s path=%s", fname,path);

    FILE *file = fopen(path, "r");
    if (!file) {
        return -ENOENT;
    }

    PR_NOTICE("play_voice_prompt: %s path=%s filelen=%d", fname, path, flen(file));

    if (__this->play_voice_prompt) {
        local_music_dec_ops.dec_stop(0);
    }
    __this->play_voice_prompt = 1;
    __this->prompt_type = name;

    err = local_music_dec_file(file, 0, dec_end_handler, 0);
    if (err) {
        __this->play_voice_prompt = 0;
        __this->prompt_type = APP_LOCAL_PROMPT_NULL;
    }

    return err;
}

/*
 * 播放提示音
 */
static int app_music_play_voice_prompt(APP_LOCAL_PROMPT_TYPE_E fname, void *dec_end_handler)
{
    return __play_voice_prompt(fname, dec_end_handler, 0);
}



#endif




#if (TCFG_HOST_AUDIO_ENABLE==0)

static FILE *record_file = NULL;
//编码器输出PCM数据
STATIC INT_T recorder_vfs_fwrite(VOID *file, VOID *data, UINT_T len)
{
    static int cnt;
    int ret;
    cbuffer_t *cbuf = (cbuffer_t *)file;

    if (FALSE == ty_stream_is_support()) {
        PR_DEBUG("ty stream is not support!");
        if (0 == cbuf_write(cbuf, data, len)) {
            //上层buf写不进去时清空一下，避免出现声音滞后的情况
            UINT_T rlen;
            rlen = cbuf_get_data_size(cbuf);
            cbuf_clear(cbuf);
            PR_DEBUG("recorder_vfs_fwrite size=%d full", len);
        } else {
            PR_DEBUG("cbuf_write %d", len);
        }
    } else {
        // cbuf_write(cbuf, data, len);

        /* while(!storage_device_ready()); */
        /* if (!record_file) { */
        /* record_file = fopen("storage/sd0/C/record00.pcm", "w+"); */
        /* cnt = 0; */
        /* if (!record_file) { */
        /* PR_ERR("fopen play file faild!\n"); */
        /* return -1; */
        /* } */
        /* } */
        /* printf("audio len :%d", len); */
        /* ret = fwrite(data, len, 1, record_file); */
        /* if (ret != len) { */
        /* PR_ERR(" file write buf err %d\n", ret); */
        /* fclose(record_file); */
        /* record_file = NULL; */
        /* return -1; */
        /* } */

        /* if (cnt++ >= 1000) { */
        /* cnt = 0; */
        /* PR_DEBUG("stop record....\n"); */
        /* fclose(record_file); */
        /* record_file = NULL; */
        /* }  */

        // cbuf_write(cbuf, data, len);
        if (0 == cbuf_write(cbuf, data, len)) {
            // 上层buf写不进去时清空一下，避免出现声音滞后的情况
            cbuf_clear(cbuf);
        }
        if (voice_buf_size <= cbuf_get_data_size(cbuf)) {
            cbuf_read(cbuf, audio_data, voice_buf_size);
            PR_DEBUG("put audio data to queue len:%d", voice_buf_size);
            ty_audio_stream_in_queue(audio_data, voice_buf_size);
        }

    }

    return len;
}

STATIC CONST struct audio_vfs_ops recorder_vfs_ops = {
    .fwrite = recorder_vfs_fwrite,
    .fopen = 0,
    .fread = 0,
    .fseek = 0,
    .ftell = 0,
    .flen = 0,
    .fclose = 0,
};


/**
 * @berief: 初始化录音功能,录取PCM的数据,存储到PCM buff中
 * @param   INT_T
 * @return: none
 * @retval: none
 */


STATIC VOID audio_recoder_init()
{
    PR_DEBUG("audio recoder init ");
    INT_T err;
    STATIC BOOL_T flag = FALSE;
    union audio_req req = {0};

    /* req.enc.channel_bit_map = BIT(1); */

    flag = TRUE;
    req.enc.frame_size = PCM_SAMPLE_RATE / 100 * 4 * PCM_CHANNEL;        //收集够多少字节PCM数据就回调一次fwrite
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = PCM_CHANNEL;
    req.enc.volume = AUDIO_RECORD_VOICE_VOLUME;
    req.enc.sample_rate = PCM_SAMPLE_RATE;
    req.enc.format = "pcm";
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &recorder_vfs_ops;
    req.enc.file = (FILE *)&g_audio_hdl.pcm_cbuff_w;

    req.enc.use_vad = 1; //打开VAD断句功能
    req.enc.dns_enable = 1; //打开降噪功能
    req.enc.vad_auto_refresh = 1; //VAD自动刷新


#if 0  //回声消除
#define AEC_EN              BIT(0)
#define NLP_EN              BIT(1)
#define ANS_EN              BIT(2)
#define DNS_EN              BIT(5)

    req.enc.use_vad = 1; //打开VAD断句功能
    req.enc.dns_enable = 1; //打开降噪功能
    req.enc.vad_auto_refresh = 1; //VAD自动刷新
#if 0
    struct aec_s_attr aec_param = {0};
    req.enc.aec_attr = &aec_param;
    req.enc.aec_enable = 1;

    extern VOID get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);
    aec_param.output_way = 0;
    aec_param.agc_en = 0;
#ifdef CONFIG_DNS_ENC_ENABLE
    aec_param.EnableBit = (AEC_EN | NLP_EN | ANS_EN | DNS_EN);
#else
    aec_param.EnableBit = (AEC_EN | NLP_EN | ANS_EN);
#endif
    // aec_param.mic_again = ;
    // aec_param.dac_again = ;

    if (aec_param.EnableBit == 0) {
        req.enc.aec_enable = 0;
        req.enc.aec_attr = NULL;
    }

    if (aec_param.output_way) {
        req.enc.channel_bit_map |= BIT(3);  //回踩电路通道
        //req.enc.ch_data_exchange = 1; //回踩电路比收音通道低的话需要设置这个

    }
    PR_NOTICE("output_way=%d channel_bit_map=0x%x EnableBit=0x%x agc=%d", aec_param.output_way, req.enc.channel_bit_map, aec_param.EnableBit, aec_param.agc_en);
    aec_param.AGC_echo_look_ahead = 100;
    aec_param.AGC_echo_hold = 400;
    aec_param.ES_Unconverge_OverDrive = aec_param.ES_MinSuppress;

    if (req.enc.sample_rate == 16000) {
        aec_param.wideband = 1;
        aec_param.hw_delay_offset = 50;
    } else {
        aec_param.wideband = 0;
        aec_param.hw_delay_offset = 75;//75
    }
#endif // 0
#endif

    err = server_request(g_audio_hdl.enc_server, AUDIO_REQ_ENC, &req);
}


STATIC INT_T recorder_test_vfs_fwrite(VOID *file, VOID *data, UINT_T len)
{

    cbuffer_t *cbuf = (cbuffer_t *)file;
    if (0 == cbuf_write(cbuf, data, len)) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        cbuf_clear(cbuf);
    }
    PR_NOTICE("cbuf_write %d", len);
//    user_printf("w");
    tuya_hal_semaphore_post(g_audio_ctrl.r_sem);
    return len;
}
STATIC CONST struct audio_vfs_ops recorder_test_vfs_ops = {
    .fwrite = recorder_test_vfs_fwrite,
    .fopen = 0,
    .fread = 0,
    .fseek = 0,
    .ftell = 0,
    .flen = 0,
    .fclose = 0,
};
STATIC VOID audio_recoder_test_init()
{
    INT_T err;
    union audio_req req = {0};
    /* req.enc.channel_bit_map = BIT(1); */

    req.enc.frame_size = PCM_SAMPLE_RATE / 100 * 4 * PCM_CHANNEL;	//收集够多少字节PCM数据就回调一次fwrite
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = PCM_CHANNEL;
    req.enc.volume = AUDIO_RECORD_VOICE_VOLUME;
    req.enc.sample_rate = PCM_SAMPLE_RATE;
    req.enc.format = "pcm";
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &recorder_test_vfs_ops;
    req.enc.file = (FILE *)&g_audio_hdl.pcm_cbuff_r;
    req.enc.use_vad = 1; //打开VAD断句功能
    req.enc.dns_enable = 1; //打开降噪功能
    req.enc.vad_auto_refresh = 1; //VAD自动刷新
#if 0  //回声消除
#define AEC_EN              BIT(0)
#define NLP_EN              BIT(1)
#define ANS_EN              BIT(2)
#define DNS_EN              BIT(5)

    struct aec_s_attr aec_param = {0};
    req.enc.aec_attr = &aec_param;
    req.enc.aec_enable = 1;

    extern VOID get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);
    aec_param.output_way = 0;
    aec_param.agc_en = 0;
#ifdef CONFIG_DNS_ENC_ENABLE
    aec_param.EnableBit = (AEC_EN | NLP_EN | ANS_EN | DNS_EN);
#else
    aec_param.EnableBit = (AEC_EN | NLP_EN | ANS_EN);
#endif
    // aec_param.mic_again = ;
    // aec_param.dac_again = ;

    if (aec_param.EnableBit == 0) {
        req.enc.aec_enable = 0;
        req.enc.aec_attr = NULL;
    }
    if (aec_param.output_way) {
        req.enc.channel_bit_map |= BIT(3);  //回踩电路通道
        //req.enc.ch_data_exchange = 1; //回踩电路比收音通道低的话需要设置这个
    }
    PR_NOTICE("output_way=%d channel_bit_map=0x%x EnableBit=0x%x agc=%d", aec_param.output_way, req.enc.channel_bit_map, aec_param.EnableBit, aec_param.agc_en);
    aec_param.AGC_echo_look_ahead = 100;
    aec_param.AGC_echo_hold = 400;
    aec_param.ES_Unconverge_OverDrive = aec_param.ES_MinSuppress;

    if (req.enc.sample_rate == 16000) {
        aec_param.wideband = 1;
        aec_param.hw_delay_offset = 50;
    } else {
        aec_param.wideband = 0;
        aec_param.hw_delay_offset = 75;//75
    }
#endif
    err = server_request(g_audio_hdl.enc_server, AUDIO_REQ_ENC, &req);

}

STATIC INT_T recorder_test_new_vfs_fwrite(VOID *file, VOID *data, UINT_T len)
{
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T count = 0;
    STATIC INT_T fps = 0;
    INT_T now_time_ms = 0;
    cbuffer_t *cbuf = (cbuffer_t *)file;
    if (0 == cbuf_write(cbuf, data, len)) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        //cbuf_clear(cbuf);
    } else {
        //PR_DEBUG("w %d",len);
        fps++;
        count += len;
        now_time_ms = tuya_hal_get_systemtickcount();
        if (now_time_ms - 100 > last_time_ms) {
            PR_NOTICE("recorder_test_new_vfs_fwrite fps %d size=%d  len =%d", fps, len, count);
            last_time_ms = tuya_hal_get_systemtickcount();
            fps = 0;
            count = 0;
        }
    }

    return len;
}
STATIC CONST struct audio_vfs_ops recorder_test_new_vfs_ops = {
    .fwrite = recorder_test_new_vfs_fwrite,
    .fopen = 0,
    .fread = 0,
    .fseek = 0,
    .ftell = 0,
    .flen = 0,
    .fclose = 0,
};
STATIC VOID audio_recoder_test_new_init()
{
    INT_T err;
    union audio_req req = {0};
    req.enc.channel_bit_map = BIT(1);

    req.enc.frame_size = PCM_SAMPLE_RATE / 100 * 4 * PCM_CHANNEL;	//收集够多少字节PCM数据就回调一次fwrite
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = PCM_CHANNEL;
    req.enc.volume = AUDIO_RECORD_VOICE_VOLUME;
    req.enc.sample_rate = PCM_SAMPLE_RATE;
    req.enc.format = "pcm";
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &recorder_test_new_vfs_ops;
    req.enc.file = (FILE *)&g_audio_hdl.pcm_cbuff_r;
#if 1  //回声消除
#define AEC_EN              BIT(0)
#define NLP_EN              BIT(1)
#define ANS_EN              BIT(2)
#define DNS_EN              BIT(5)

    struct aec_s_attr aec_param = {0};
    req.enc.aec_attr = &aec_param;
    req.enc.aec_enable = 1;

    extern VOID get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);
    aec_param.output_way = 0;
    aec_param.agc_en = 0;
#ifdef CONFIG_DNS_ENC_ENABLE
    aec_param.EnableBit = (AEC_EN | NLP_EN | ANS_EN | DNS_EN);
#else
    aec_param.EnableBit = (AEC_EN | NLP_EN | ANS_EN);
#endif
    // aec_param.mic_again = ;
    // aec_param.dac_again = ;

    if (aec_param.EnableBit == 0) {
        req.enc.aec_enable = 0;
        req.enc.aec_attr = NULL;
    }
    if (aec_param.output_way) {
        req.enc.channel_bit_map |= BIT(3);  //回踩电路通道
        //req.enc.ch_data_exchange = 1; //回踩电路比收音通道低的话需要设置这个
    }
    PR_NOTICE("output_way=%d channel_bit_map=0x%x EnableBit=0x%x agc=%d", aec_param.output_way, req.enc.channel_bit_map, aec_param.EnableBit, aec_param.agc_en);
    aec_param.AGC_echo_look_ahead = 100;
    aec_param.AGC_echo_hold = 400;
    aec_param.ES_Unconverge_OverDrive = aec_param.ES_MinSuppress;

    if (req.enc.sample_rate == 16000) {
        aec_param.wideband = 1;
        aec_param.hw_delay_offset = 50;
    } else {
        aec_param.wideband = 0;
        aec_param.hw_delay_offset = 75;//75
    }
#endif
    err = server_request(g_audio_hdl.enc_server, AUDIO_REQ_ENC, &req);

}


STATIC VOID tuya_audio_recoder_stop()
{
    INT_T err;
    union audio_req req = {0};
    req.enc.cmd             = AUDIO_ENC_STOP;
    err = server_request(g_audio_hdl.enc_server, AUDIO_REQ_ENC, &req);
    PR_DEBUG("tuya_audio_recoder_stop err=%d", err);

}


//解码器读取PCM数据
STATIC INT_T audio_play_net_vfs_fread(VOID *file, VOID *data, UINT_T len)
{

    cbuffer_t *cbuf = NULL;
    UINT_T cbuf_len = 0;
    UINT_T rlen = 0;
    UINT_T c_rlen = 0;
    cbuf = (cbuffer_t *)file;
    do {
        cbuf_len = cbuf_get_data_size(cbuf);
        rlen = cbuf_len > len ? len : cbuf_len;
        c_rlen = cbuf_read(cbuf, data, rlen);
        if (c_rlen > 0) {
            //PR_DEBUG("c_rlen=%d rlen=%d cbuf_len=%d len=%d",c_rlen,rlen,cbuf_len,len);
            break;
        }
        //PR_DEBUG("os_sem_pend");
        //此处等待信号量是为了防止解码器因为读不到数而一直空转
        if (FALSE == g_audio_hdl.is_audio_play_open) {
            rlen = 0;
            break;
        }
        g_audio_ctrl.pcm_wait_sem = 1;
        tuya_hal_semaphore_waittimeout(g_audio_ctrl.r_sem, TY_AUDIO_WAIT_TIMEOUT);
        g_audio_ctrl.pcm_wait_sem = 0;

    } while (1);



    //返回成功读取的字节数
    return rlen;
}

STATIC CONST struct audio_vfs_ops audio_play_net_vfs_ops = {
    .fread  = audio_play_net_vfs_fread,
    .fwrite = 0,
    .fopen = 0,
    .fseek = 0,
    .ftell = 0,
    .flen = 0,
    .fclose = 0,
};

/**
 * @berief: 初始化播放功能,播放PCM的数据,从pcm_buff中读取数据播放
 * @param   INT_T
 * @return: none
 * @retval: none
 */
STATIC VOID audio_player_net_init()
{
    STATIC BOOL_T flag = FALSE;
    INT_T err;
    union audio_req req = {0};
    if (flag) {
        return;
    }
    flag = TRUE;

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = AUDIO_PLAY_VOICE_VOLUME;
    req.dec.output_buf_len  = 8 * 1024;
    req.dec.priority        = 1;
    req.dec.channel         = PCM_CHANNEL;  /*dac 差分输出 单路*/
    req.dec.sample_rate     = PCM_SAMPLE_RATE;
    req.dec.vfs_ops         = &audio_play_net_vfs_ops;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";
    // req.dec.speedV = 80; // >80是变快，<80是变慢，建议范围：30到130
    // req.dec.pitchV = 32768; // >32768是音调变高，<32768音调变低，建议范围20000到50000k

    req.dec.file            = (FILE *)&g_audio_hdl.pcm_cbuff_r;
    /* req.dec.attr            = AUDIO_ATTR_LR_ADD; */          //左右声道数据合在一起,封装只有DACL但需要测试两个MIC时可以打开此功能
    PR_DEBUG("audio_player_net_init ");
    err = server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        PR_ERR("server_request dec_server AUDIO_DEC_OPEN err %d", err);
        goto __err;
    }
    req.dec.cmd = AUDIO_DEC_START;
    server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);
    return;
__err :

    return;

}


//解码器读取PCM数据
STATIC INT_T audio_play_test_new_vfs_fread(VOID *file, VOID *data, UINT_T len)
{

    cbuffer_t *cbuf = NULL;
    UINT_T cbuf_len = 0;
    UINT_T rlen = 0;
    UINT_T c_rlen = 0;
    cbuf = (cbuffer_t *)file;
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T count = 0;
    STATIC INT_T fps = 0;
    INT_T now_time_ms = 0;

    if (FALSE == g_audio_hdl.is_audio_play_open) {
        rlen = 0;
        return rlen;
    }
    cbuf_len = cbuf_get_data_size(cbuf);
    rlen = cbuf_len > len ? len : cbuf_len;
    c_rlen = cbuf_read(cbuf, data, rlen);
    if (c_rlen > 0) {
        fps++;
        count += len;
        now_time_ms = tuya_hal_get_systemtickcount();
        if (now_time_ms - 100 > last_time_ms) {
            PR_NOTICE("audio_play_test_new_vfs_fread fps %d size=%d  len =%d", fps, len, count);
            last_time_ms = tuya_hal_get_systemtickcount();
            fps = 0;
            count = 0;
        }
    } else {
        rlen = 0;
    }
    //返回成功读取的字节数
    return rlen;
}

STATIC CONST struct audio_vfs_ops audio_play_test_new_vfs_ops = {
    .fread  = audio_play_test_new_vfs_fread,
    .fwrite = 0,
    .fopen = 0,
    .fseek = 0,
    .ftell = 0,
    .flen = 0,
    .fclose = 0,
};

/**
 * @berief: 初始化播放功能,播放PCM的数据,从pcm_buff中读取数据播放
 * @param   INT_T
 * @return: none
 * @retval: none
 */
STATIC VOID audio_player_test_new_init()
{
    STATIC BOOL_T flag = FALSE;
    INT_T err;
    union audio_req req = {0};
    // if(flag) {
    //    return;
    // }
    flag = TRUE;

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = AUDIO_PLAY_VOICE_VOLUME;
    req.dec.output_buf_len  = 8 * 1024;
    req.dec.priority        = 1;
    req.dec.channel         = PCM_CHANNEL;  /*dac 差分输出 单路*/
    req.dec.sample_rate     = PCM_SAMPLE_RATE;
    req.dec.vfs_ops         = &audio_play_test_new_vfs_ops;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";

    req.dec.file            = (FILE *)&g_audio_hdl.pcm_cbuff_r;
    /* req.dec.attr            = AUDIO_ATTR_LR_ADD; */          //左右声道数据合在一起,封装只有DACL但需要测试两个MIC时可以打开此功能
    PR_DEBUG("audio_player_net_init ");
    err = server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        PR_ERR("server_request dec_server AUDIO_DEC_OPEN err %d", err);
        goto __err;
    }
    req.dec.cmd = AUDIO_DEC_START;
    server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);
    return;
__err :

    return;

}

STATIC VOID tuya_audio_player_stop()
{
    INT_T err;
    union audio_req req = {0};
    req.dec.cmd             = AUDIO_DEC_STOP;
    err = server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);
    PR_DEBUG("tuya_audio_player_stop err=%d", err);

}


VOID ty_device_local_audio_play(CHAR_T *src, INT_T src_len)
{
    TY_AUDIO_LOCAL_MSG local_file;
    local_file.play_src =   src;
    local_file.play_src_len = src_len;
    local_file.play_len = 0;
    tuya_send_audio_msg(MSG_START_LOCAL_AUDIO_PLAY, &local_file, SIZEOF(TY_AUDIO_LOCAL_MSG));
}

VOID ty_device_local_audio_play_stop()
{
    tuya_send_audio_msg(MSG_STOP_LOCAL_AUDIO_PLAY, NULL, 0);
}

STATIC INT_T audio_play_local_vfs_fread(VOID *file, VOID *data, UINT_T len)
{
    TY_AUDIO_LOCAL_MSG *local_file = (TY_AUDIO_LOCAL_MSG *)file;
    CHAR_T *play_buf = local_file->play_src;
    INT_T rlen = 0;
    do {
        //需要最先判断
        if (FALSE == g_audio_hdl.is_audio_play_open) {
            rlen = 0;
            break;
        }
        if (local_file->play_src_len >= local_file->play_len + len) {
            memcpy(data, play_buf + local_file->play_len, len);
            local_file->play_len += len;
            rlen = len;
            PR_DEBUG("src_len=%d play_len=%d rlen=%d", local_file->play_src_len, local_file->play_len, rlen);
            break;
        } else if (local_file->play_src_len > local_file->play_len) {
            memcpy(data, play_buf + local_file->play_len, local_file->play_src_len - local_file->play_len);
            rlen = local_file->play_src_len - local_file->play_len;
            PR_DEBUG("src_len=%d play_len=%d rlen=%d", local_file->play_src_len, local_file->play_len, rlen);
            local_file->play_len += local_file->play_src_len - local_file->play_len;

            break;
        } else if (local_file->play_src_len == local_file->play_len) {
            ty_device_local_audio_play_stop();
            rlen = 0;
            PR_DEBUG("local_file->play_src_len == local_file->play_len %d", local_file->play_src_len);
            break;
        }
    } while (1);

    //返回成功读取的字节数
    return rlen;
}

STATIC CONST struct audio_vfs_ops audio_play_local_vfs_ops = {
    .fread  = audio_play_local_vfs_fread,
    .fwrite = 0,
    .fopen = 0,
    .fseek = 0,
    .ftell = 0,
    .flen = 0,
    .fclose = 0,
};

/**
 * @berief: 初始化播放功能,播放PCM的数据,从pcm_buff中读取数据播放
 * @param   INT_T
 * @return: none
 * @retval: none
 */
STATIC VOID audio_player_local_init(VOID_T *arg)
{
    INT_T err;
    union audio_req req = {0};

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = AUDIO_PLAY_VOICE_VOLUME;
    req.dec.output_buf_len  = 8 * 1024;
    req.dec.priority        = 1;
    req.dec.channel         = PCM_CHANNEL;  /*dac 差分输出 单路*/
    req.dec.sample_rate     = PCM_SAMPLE_RATE;
    req.dec.vfs_ops         = &audio_play_local_vfs_ops;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";
    memcpy(&g_local_file, arg, SIZEOF(TY_AUDIO_LOCAL_MSG));
    req.dec.file            = (FILE *)&g_local_file;
    /* req.dec.attr            = AUDIO_ATTR_LR_ADD; */          //左右声道数据合在一起,封装只有DACL但需要测试两个MIC时可以打开此功能

    err = server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);

    req.dec.cmd = AUDIO_DEC_START;
    server_request(g_audio_hdl.dec_server, AUDIO_REQ_DEC, &req);
}


STATIC VOID enc_server_event_handler(VOID *priv, INT_T argc, INT_T *argv)
{

    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
    case AUDIO_SERVER_EVENT_END:
        break;
    case AUDIO_SERVER_EVENT_SPEAK_START:
        break;
    case AUDIO_SERVER_EVENT_SPEAK_STOP:
        break;
    default:
        break;
    }
}


VOID ty_device_net_audio(BOOL_T flag)
{
    PR_NOTICE("ty_device_net_audio %d", flag);
    if (flag) {
        //音频播放功放
        tuya_send_audio_msg(MSG_START_NET_AUDIO_PLAY, 0, NULL);
        tuya_send_audio_msg(MSG_START_AUDIO_RECORDER, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_NET_AUDIO_PLAY, 0, NULL);
        tuya_send_audio_msg(MSG_STOP_AUDIO_RECORDER, 0, NULL);
    }

}
VOID ty_device_net_audio_play(BOOL_T flag)
{
    PR_NOTICE("ty_device_net_audio_play %d", flag);
    if (flag) {
        //音频播放功放
        tuya_send_audio_msg(MSG_START_NET_AUDIO_PLAY, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_NET_AUDIO_PLAY, 0, NULL);
    }

}

VOID ty_device_net_audio_recorder(BOOL_T flag)
{
    PR_NOTICE("ty_device_net_audio_recorder %d", flag);
    if (flag) {
        //音频播放功放
        tuya_send_audio_msg(MSG_START_AUDIO_RECORDER, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_AUDIO_RECORDER, 0, NULL);
    }

}

INT_T ty_device_audio_test(BOOL_T flag)
{
    if (flag) {
        tuya_send_audio_msg(MSG_START_AUDIO_TEST, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_AUDIO_TEST, 0, NULL);
    }
    return 0;
}
BOOL_T is_audio_play_open(VOID)
{
    return g_audio_hdl.is_audio_play_open;
}




STATIC VOID __audio_task(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    TY_AUDIO_CTRL_MSG *msg_data;
    int msg[16] = {0,};
    while (1) {
        //阻塞等待消息
        op_ret = os_q_pend(&g_audio_ctrl.msg_que, 0, msg);
        if (op_ret != OPRT_OK) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("tal_queue_fetch op_ret:%d", op_ret);
            }
            continue;
        }
        msg_data = (TY_AUDIO_CTRL_MSG *)msg[0];
        switch (msg_data->cmd) {
        case MSG_START_NET_AUDIO_PLAY: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            if (g_audio_hdl.is_audio_play_open) {
                tuya_audio_player_stop();
            }

            g_audio_hdl.is_audio_play_open = TRUE;
            audio_player_net_init();

        }
        break;
        case MSG_START_LOCAL_AUDIO_PLAY: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            if (g_audio_hdl.is_audio_play_open) {
                tuya_audio_player_stop();
            }

            TY_AUDIO_LOCAL_MSG *p = (TY_AUDIO_LOCAL_MSG *)(msg_data->data);
            if (p) {
                //PR_NOTICE("local play src=0x%x len=%d",p->play_src,p->play_src_len);
                g_audio_hdl.is_audio_play_open = true;
                audio_player_local_init((VOID_T *)p);
            }
        }
        break;
        case MSG_STOP_NET_AUDIO_PLAY: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_audio_player_stop();
        }
        break;
        case MSG_STOP_LOCAL_AUDIO_PLAY: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_audio_player_stop();

        }
        break;
        case MSG_START_AUDIO_RECORDER: {

            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            if (g_audio_hdl.is_audio_record_open) {
                tuya_audio_recoder_stop();
            }
            g_audio_hdl.is_audio_record_open = true;
            audio_recoder_init();

        }
        break;
        case MSG_STOP_AUDIO_RECORDER: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_audio_recoder_stop();
        }
        break;

        case MSG_START_AUDIO_TEST: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            if (g_audio_hdl.is_audio_play_open) {
                tuya_audio_player_stop();
            }

            g_audio_hdl.is_audio_play_open = true;
            audio_player_net_init();

            if (g_audio_hdl.is_audio_record_open) {
                tuya_audio_recoder_stop();
            }
            g_audio_hdl.is_audio_record_open = true;
            audio_recoder_test_init();

        }
        break;

        case MSG_STOP_AUDIO_TEST: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_audio_recoder_stop();
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_audio_player_stop();

        }
        break;

        case MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST: {

            if (g_audio_hdl.is_audio_record_open) {
                tuya_audio_recoder_stop();
            }
            g_audio_hdl.is_audio_record_open = true;
            audio_recoder_test_new_init();
            audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_RECORDER_START;
            tuya_audio_test_timer_init_and_start(audio_test_recorder_first_play_times);
        }
        break;
        case MSG_STOP_AUDIO_RECORDER_AND_START_PLAY_TEST: {

            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_audio_recoder_stop();
            g_audio_hdl.is_audio_play_open = TRUE;
            audio_player_test_new_init();
            audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_PLAY_START;
            tuya_audio_test_timer_init_and_start(audio_test_recorder_first_play_times);
        }
        break;

        case MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_STOP_PLAY_TEST: {
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_audio_player_stop();
            audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_STOP;
        }
        break;

        }
        if (msg_data) {
            if (msg_data->data) {
                tal_free(msg_data->data);
            }
            tal_free(msg_data);
            msg_data = NULL;
        }
    }
}



#else

typedef enum {
    TYPE_NULL = 0,
    TYPE_NET = 1,
    TYPE_LOCAL = 2,
    TYPE_TEST = 3,
    TYPE_TEST_NEW = 4,
} TY_AUDIO_TYPE;

STATIC TY_AUDIO_TYPE ty_audio_type = TYPE_NULL;

void usb_audio_get_cfg(u8 *channel, u8 *bit_reso, UINT_T *sample_rate)
{
    *channel     = PCM_CHANNEL;
    *bit_reso    = PCM_BIT_DEP;
    *sample_rate = PCM_SAMPLE_RATE;
}

void ty_usb_audio_get_cfg(u8 *channel, u8 *bit_reso, UINT_T *sample_rate)
{
    usb_audio_get_cfg(channel, bit_reso, sample_rate);
}

void usb_audio_set_cfg(u8 channel, u8 bit_reso, UINT_T sample_rate)
{
    PCM_SAMPLE_RATE = sample_rate;
    PCM_CHANNEL     = channel;
    PCM_BIT_DEP     = bit_reso;
}


STATIC VOID audio_player_local_init(VOID_T *arg)
{
    memcpy(&g_local_file, arg, SIZEOF(TY_AUDIO_LOCAL_MSG));
}


VOID tuya_usb_audio_start_play(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }

    // if(!audio_power_off) {
    usb_audio_resume_recorder(audio_id);
    // }
    PR_NOTICE("tuya_usb_audio_start_play");
}

VOID tuya_usb_audio_stop_play(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }
    // if(!audio_power_off) {
    usb_audio_pause_recorder(audio_id);
    // }
    PR_NOTICE("tuya_usb_audio_stop_play");
}

VOID tuya_usb_audio_start_record(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }
    // if(!audio_power_off) {
    /* usb_audio_resume_player(audio_id); */
    // }
    PR_NOTICE("tuya_usb_audio_start_record");
}

VOID tuya_usb_audio_stop_record(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }
    // if(!audio_power_off) {
    /* usb_audio_pause_player(audio_id); */
    // }

    PR_NOTICE("tuya_usb_audio_stop_record");
}

VOID tuya_usb_audio_start_play_test(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }

    /* if (!audio_power_off) { */
    /* usb_audio_resume_recorder(audio_id); */
    /* } */

}

VOID tuya_usb_audio_stop_play_test(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }
    /* if (!audio_power_off) { */
    /* usb_audio_pause_recorder(audio_id); */
    /* } */

}

VOID tuya_usb_audio_start_record_test(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }
    /* if (!audio_power_off) { */
    /* usb_audio_resume_player(audio_id); */
    /* } */
}

VOID tuya_usb_audio_stop_record_test(VOID)
{
    CHAR_T audio_id = get_audio_id();
    if (audio_id < 0) {
        PR_ERR("audio not online!");
        return;
    }
    /* if (!audio_power_off) { */
    /* usb_audio_pause_player(audio_id); */
    /* } */
}
STATIC VOID __audio_task(PVOID_T pArg)
{
    CHAR_T audio_id;
    OPERATE_RET op_ret = OPRT_OK;
//    P_MSG_LIST msgListNode;
    TY_AUDIO_CTRL_MSG *msg_data;
    int msg[16] = {0,};
    while (1) {
        //阻塞等待消息
//        op_ret = WaitMessage(g_audio_ctrl.msg_que,&msgListNode);
//        op_ret = tal_queue_fetch(g_audio_ctrl.msg_que, &msg_data, TKL_QUEUE_WAIT_FROEVER);
        op_ret = os_q_pend(&g_audio_ctrl.msg_que, 0, msg);
        if (op_ret != OPRT_OK) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("tal_queue_fetch op_ret:%d", op_ret);
            }
            continue;
        }
        msg_data = (TY_AUDIO_CTRL_MSG *)msg[0];
        audio_id = get_audio_id();
        if (-1 == audio_id) {
#if TY_HOST_UAC_WITH_HW_AUDIO
            if (msg_data->cmd != MSG_HW_START_LOCAL_AUDIO_PLAY && msg_data->cmd != MSG_HW_STOP_LOCAL_AUDIO_PLAY) {
#endif
                if (audio_uac_retry_times >= TY_AUDIO_UAC_TRY_TIMES) {
                    audio_uac_retry_times = 0;
                    PR_NOTICE("usb audio fail,retry post stop,please check your camera");
                    goto END;
                }
                PR_NOTICE("usb audio fail,retry post msgID %d", msg_data->cmd);
                if (MSG_START_LOCAL_AUDIO_PLAY == msg_data->cmd) {
                    tuya_send_audio_msg(msg_data->cmd, msg_data->data, msg_data->data_len);
                } else  {
                    tuya_send_audio_msg(msg_data->cmd, NULL, 0);
                }
                os_time_dly(50);
                audio_uac_retry_times++;
                goto END;
#if TY_HOST_UAC_WITH_HW_AUDIO
            }
#endif

        }
        audio_uac_retry_times = 0;
        switch (msg_data->cmd) {
        case MSG_START_NET_AUDIO_PLAY: {
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            ty_audio_type = TYPE_NET;
            if (g_audio_hdl.is_audio_play_open) {
                break;
            }

            g_audio_hdl.is_audio_play_open = TRUE;
            tuya_usb_audio_start_play();
            // audio_player_net_init();
        }
        break;
        case MSG_START_LOCAL_AUDIO_PLAY: {
            ty_audio_type = TYPE_LOCAL;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            if (g_audio_hdl.is_audio_play_open) {
                break;
            }
            TY_AUDIO_LOCAL_MSG *p = (TY_AUDIO_LOCAL_MSG *)(msg_data->data);
            if (p) {
                PR_NOTICE("local play src=0x%x len=%d", p->play_src, p->play_src_len);
                g_audio_hdl.is_audio_play_open = TRUE;
                audio_player_local_init((VOID *)p);
                tuya_usb_audio_start_play();
            }
        }
        break;
        case MSG_STOP_NET_AUDIO_PLAY: {
            ty_audio_type = TYPE_NET;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_usb_audio_stop_play();
            // tuya_audio_player_stop();
        }
        break;
        case MSG_STOP_LOCAL_AUDIO_PLAY: {
            ty_audio_type = TYPE_LOCAL;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_usb_audio_stop_play();

        }
        break;
        case MSG_START_AUDIO_RECORDER: {
            ty_audio_type = TYPE_NET;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            if (g_audio_hdl.is_audio_record_open) {
                break;
            }
            g_audio_hdl.is_audio_record_open = TRUE;
            tuya_usb_audio_start_record();

        }
        break;
        case MSG_STOP_AUDIO_RECORDER: {
            ty_audio_type = TYPE_NET;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_usb_audio_stop_record();

        }
        break;

        case MSG_START_AUDIO_TEST: {
            ty_audio_type = TYPE_TEST;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            if (g_audio_hdl.is_audio_play_open) {
                break;
            }
            g_audio_hdl.is_audio_play_open = TRUE;
            tuya_usb_audio_start_play_test();

            if (g_audio_hdl.is_audio_record_open) {
                break;
            }
            g_audio_hdl.is_audio_record_open = TRUE;
            tuya_usb_audio_start_record_test();

        }
        break;

        case MSG_STOP_AUDIO_TEST: {
            ty_audio_type = TYPE_TEST;
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            cbuf_clear(&g_audio_hdl.pcm_cbuff_w);
            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_usb_audio_stop_record_test();
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_usb_audio_stop_play_test();

        }
        break;

        case MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST: {
            ty_audio_type = TYPE_TEST_NEW;
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_usb_audio_stop_play();
            cbuf_clear(&g_audio_hdl.pcm_cbuff_r);
            g_audio_hdl.is_audio_record_open = TRUE;
            tuya_usb_audio_start_record();
            audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_RECORDER_START;
            tuya_audio_test_timer_init_and_start(audio_test_recorder_first_play_times);
            PR_NOTICE("MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST %d %d", g_audio_hdl.is_audio_play_open, g_audio_hdl.is_audio_record_open);
        }
        break;
        case MSG_STOP_AUDIO_RECORDER_AND_START_PLAY_TEST: {
            ty_audio_type = TYPE_TEST_NEW;
            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_usb_audio_stop_record();
            g_audio_hdl.is_audio_play_open = TRUE;
            tuya_usb_audio_start_play();
            audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_PLAY_START;
            tuya_audio_test_timer_init_and_start(audio_test_recorder_first_play_times);
            PR_NOTICE("MSG_STOP_AUDIO_RECORDER_AND_START_PLAY_TEST %d %d", g_audio_hdl.is_audio_play_open, g_audio_hdl.is_audio_record_open);
        }
        break;

        case MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_STOP_PLAY_TEST: {
            ty_audio_type = TYPE_TEST_NEW;
            g_audio_hdl.is_audio_record_open = FALSE;
            tuya_usb_audio_stop_record();
            g_audio_hdl.is_audio_play_open = FALSE;
            tuya_usb_audio_stop_play();
            audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_STOP;
            PR_NOTICE("MSG_STOP_AUDIO_RECORDER_AND_START_PLAY_TEST %d %d", g_audio_hdl.is_audio_play_open, g_audio_hdl.is_audio_record_open);
        }
        break;



#if TY_HOST_UAC_WITH_HW_AUDIO

        case MSG_HW_START_LOCAL_AUDIO_PLAY: {
            UINT_T *p = (UINT_T *)(msg_data->data);
//                audio_power_en(TRUE);
            app_music_play_voice_prompt(*p, NULL);
        }
        break;

        case MSG_HW_STOP_LOCAL_AUDIO_PLAY: {
            app_music_stop_voice_prompt();
//                audio_power_en(FALSE);
        }
        break;

#endif

        }
END:
//        if(msgListNode->msg.pMsgData) {
//            Free(msgListNode->msg.pMsgData);
//        }
//        DelAndFreeMsgNodeFromQueue(g_audio_ctrl.msg_que,msgListNode);
        if (msg_data) {
            if (msg_data->data) {
                tal_free(msg_data->data);
            }
            tal_free(msg_data);
            msg_data = NULL;
        }
    }
}

VOID ty_device_local_audio_play(CHAR_T *src, INT_T src_len)
{
    TY_AUDIO_LOCAL_MSG local_file;
    local_file.play_src =   src;
    local_file.play_src_len = src_len;
    local_file.play_len = 0;
    tuya_send_audio_msg(MSG_START_LOCAL_AUDIO_PLAY, &local_file, SIZEOF(TY_AUDIO_LOCAL_MSG));
}

VOID ty_device_local_audio_play_stop()
{
    tuya_send_audio_msg(MSG_STOP_LOCAL_AUDIO_PLAY, NULL, 0);
}

VOID ty_device_net_audio(BOOL_T flag)
{
    PR_NOTICE("ty_device_net_audio %d", flag);
    if (flag) {
        //音频播放功放
        tuya_send_audio_msg(MSG_START_NET_AUDIO_PLAY, 0, NULL);
        tuya_send_audio_msg(MSG_START_AUDIO_RECORDER, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_NET_AUDIO_PLAY, 0, NULL);
        tuya_send_audio_msg(MSG_STOP_AUDIO_RECORDER, 0, NULL);
    }

}
VOID ty_device_net_audio_play(BOOL_T flag)
{
    PR_NOTICE("ty_device_net_audio_play %d", flag);
    if (flag) {
        //音频播放功放
        tuya_send_audio_msg(MSG_START_NET_AUDIO_PLAY, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_NET_AUDIO_PLAY, 0, NULL);
    }

}

VOID ty_device_net_audio_recorder(BOOL_T flag)
{
    PR_NOTICE("ty_device_net_audio_recorder %d", flag);
    if (flag) {
        //音频播放功放
        tuya_send_audio_msg(MSG_START_AUDIO_RECORDER, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_AUDIO_RECORDER, 0, NULL);
    }

}

INT_T ty_device_audio_test(BOOL_T flag)
{
    if (flag) {
        tuya_send_audio_msg(MSG_START_AUDIO_TEST, 0, NULL);
    } else {
        tuya_send_audio_msg(MSG_STOP_AUDIO_TEST, 0, NULL);
    }
    return 0;
}
BOOL_T is_audio_play_open(VOID)
{
    return g_audio_hdl.is_audio_play_open;
}

INT_T ty_usb_audio_play_put_buf_test(VOID *ptr, UINT_T len)
{
    cbuffer_t *cbuf = &g_audio_hdl.pcm_cbuff_r;
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T count = 0;
    STATIC INT_T fps = 0;
    INT_T now_time_ms = 0;
    if (FALSE == g_audio_hdl.is_audio_record_open) {
        return len;
    }
    if (0 == cbuf_write(cbuf, ptr, len)) {
        //PR_NOTICE("cbuf_write size=%d full",len);
    } else {
        PR_DEBUG("w %d", len);
        fps++;
        count += len;
        now_time_ms = tuya_hal_get_systemtickcount();
        if (now_time_ms - 100 > last_time_ms) {
            //PR_NOTICE("recorder fps %d size=%d  len =%d",fps,len,count);
            last_time_ms = tuya_hal_get_systemtickcount();
            fps = 0;
            count = 0;
        }
    }
    tuya_hal_semaphore_post(g_audio_ctrl.r_sem);
    return len;
}
INT_T ty_usb_audio_play_put_buf_test_new(VOID *ptr, UINT_T len)
{
    cbuffer_t *cbuf = &g_audio_hdl.pcm_cbuff_r;
    UINT_T cbuf_len = 0;
    UINT_T rlen = 0;
    UINT_T c_rlen = 0;
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T count = 0;
    STATIC INT_T fps = 0;
    INT_T now_time_ms = 0;

    if (FALSE == g_audio_hdl.is_audio_play_open) {
        rlen = 0;
        return rlen;
    }
    cbuf_len = cbuf_get_data_size(cbuf);
    rlen = cbuf_len > len ? len : cbuf_len;
    c_rlen = cbuf_read(cbuf, ptr, rlen);
    if (c_rlen <= 0) {
        rlen = 0 ;
    } else {
        fps++;
        count += len;
        now_time_ms = tuya_hal_get_systemtickcount();
        if (now_time_ms - 100 > last_time_ms) {
            PR_NOTICE("cbuf_read fps %d size=%d  len =%d", fps, len, count);
            last_time_ms = tuya_hal_get_systemtickcount();
            fps = 0;
            count = 0;
        }
    }
    return rlen;
}
INT_T ty_usb_audio_record_get_buf_test(VOID *ptr, UINT_T len)
{
    cbuffer_t *cbuf = &g_audio_hdl.pcm_cbuff_r;
    UINT_T cbuf_len = 0;
    UINT_T rlen = 0;
    UINT_T c_rlen = 0;

    do {
        if (FALSE == g_audio_hdl.is_audio_play_open) {
            rlen = 0;
            break;
        }
        cbuf_len = cbuf_get_data_size(cbuf);
        rlen = cbuf_len > len ? len : cbuf_len;
        c_rlen = cbuf_read(cbuf, ptr, rlen);
        if (c_rlen > 0) {
            //user_printf("c_rlen=%d rlen=%d cbuf_len=%d len=%d",c_rlen,rlen,cbuf_len,len);
            break;
        }
        tuya_hal_semaphore_waittimeout(g_audio_ctrl.r_sem, TY_AUDIO_WAIT_TIMEOUT);
    } while (1);

    return len;
}

INT_T ty_usb_audio_record_get_buf_test_new(VOID *ptr, UINT_T len)
{
    cbuffer_t *cbuf = &g_audio_hdl.pcm_cbuff_r;
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T count = 0;
    STATIC INT_T fps = 0;
    INT_T now_time_ms = 0;
    if (FALSE == g_audio_hdl.is_audio_record_open) {
        return len;
    }
    if (0 == cbuf_write(cbuf, ptr, len)) {
        PR_DEBUG("cbuf_write size=%d full", len);
    } else {
        //user_printf("w %d",len);
        fps++;
        count += len;
        now_time_ms = tuya_hal_get_systemtickcount();
        if (now_time_ms - 100 > last_time_ms) {
            PR_NOTICE("recorder fps %d size=%d  len =%d", fps, len, count);
            last_time_ms = tuya_hal_get_systemtickcount();
            fps = 0;
            count = 0;
        }
    }
    return len;
}


/* STATIC INT_T ty_usb_audio_play_put_buf_net(VOID *data, UINT_T len) */
INT_T ty_usb_audio_play_put_buf_net(VOID *data, UINT_T len)
{

    cbuffer_t *cbuf = &g_audio_hdl.pcm_cbuff_w;
    if (FALSE == g_audio_hdl.is_audio_record_open) {
        return len;
    }
    if (FALSE == ty_stream_is_support()) {
        if (0 == cbuf_write(cbuf, data, len)) {
            //上层buf写不进去时清空一下，避免出现声音滞后的情况
            UINT_T rlen;
            rlen = cbuf_get_data_size(cbuf);
            cbuf_clear(cbuf);
            //PR_DEBUG("recorder_vfs_fwrite size=%d full",len);
        } else {
            // PR_DEBUG("cbuf_write %d",len);
        }
    } else {
        // cbuf_write(cbuf, data, len);
        /* PR_DEBUG("data_len:%d", len); */
        if (0 == cbuf_write(cbuf, data, len)) {
            //上层buf写不进去时清空一下，避免出现声音滞后的情况
            cbuf_clear(cbuf);
        }
        if (voice_buf_size <= cbuf_get_data_size(cbuf)) {
            cbuf_read(cbuf, audio_data, voice_buf_size);
            /* PR_DEBUG("voicebuf_len:%d", voice_buf_size); */
            ty_audio_stream_in_queue(audio_data, voice_buf_size);
        }
    }
    return len;

}

INT_T ty_usb_audio_record_get_buf_net(VOID *data, UINT_T len)
{
    cbuffer_t *cbuf = NULL;
    UINT_T cbuf_len = 0;
    UINT_T rlen = 0;
    UINT_T c_rlen = 0;
    cbuf = &g_audio_hdl.pcm_cbuff_r;
    do {
        if (FALSE == g_audio_hdl.is_audio_play_open) {
            rlen = 0;
            break;
        }
        cbuf_len = cbuf_get_data_size(cbuf);
        if (cbuf_len == 0) {
            // user_printf("1");
            rlen = 0;
            break;
        }
        rlen = cbuf_len > len ? len : cbuf_len;
        if (rlen == 0) {
            // user_printf("2");
            break;
        }
        c_rlen = cbuf_read(cbuf, data, rlen);
        if (c_rlen > 0) {
            PR_NOTICE("c_rlen=%d rlen=%d cbuf_len=%d len=%d", c_rlen, rlen, cbuf_len, len);
            break;
        } else {
            break;
        }
    } while (1);
    // 返回成功读取的字节数
    return rlen;

}


STATIC INT_T ty_usb_audio_play_put_buf_local(VOID *data, UINT_T len)
{
    TY_AUDIO_LOCAL_MSG *local_file = (TY_AUDIO_LOCAL_MSG *)&g_local_file;
    CHAR_T *play_buf = local_file->play_src;
    INT_T rlen = 0;
    do {
        //需要最先判断
        if (FALSE == g_audio_hdl.is_audio_play_open) {
            rlen = 0;
            break;
        }
        if (local_file->play_src_len >= local_file->play_len + len) {
            memcpy(data, play_buf + local_file->play_len, len);
            local_file->play_len += len;
            rlen = len;
            PR_DEBUG("src_len=%d play_len=%d rlen=%d", local_file->play_src_len, local_file->play_len, rlen);
            break;
        } else if (local_file->play_src_len > local_file->play_len) {
            memcpy(data, play_buf + local_file->play_len, local_file->play_src_len - local_file->play_len);
            rlen = local_file->play_src_len - local_file->play_len;
            PR_DEBUG("src_len=%d play_len=%d rlen=%d", local_file->play_src_len, local_file->play_len, rlen);
            local_file->play_len += local_file->play_src_len - local_file->play_len;

            break;
        } else if (local_file->play_src_len == local_file->play_len) {
            ty_device_local_audio_play_stop();
            rlen = 0;
            PR_DEBUG("local_file->play_src_len == local_file->play_len %d", local_file->play_src_len);
            break;
        }
    } while (1);

    //返回成功读取的字节数
    return rlen;
}
STATIC INT_T usb_host_audio_play_put_buf_test(CONST usb_dev usb_id, VOID *ptr, UINT_T len, u8 channel, UINT_T sample_rate)
{
    INT_T send_len = 0;
    if (len == 0 || (FALSE == g_audio_hdl.is_audio_play_open)) {
        return send_len;
    }
    switch (ty_audio_type) {
    // PR_DEBUG("play channel:%d, sample_rate:%d", channel, sample_rate);
    case TYPE_NET: {
        send_len = ty_usb_audio_play_put_buf_net(ptr, len);
    }
    break;
    case TYPE_LOCAL: {
        send_len = ty_usb_audio_play_put_buf_local(ptr, len);
    }
    break;
    case TYPE_TEST: {
        send_len = ty_usb_audio_play_put_buf_test(ptr, len);
    }
    break;
    case TYPE_TEST_NEW: {
        send_len = ty_usb_audio_play_put_buf_test_new(ptr, len);
    }
    break;
    }
    return send_len;
}

INT_T usb_host_audio_record_get_buf_test(CONST usb_dev usb_id, VOID *ptr, UINT_T len, u8 channel, UINT_T sample_rate)
{
    INT_T send_len = len;
    usb_audio_set_cfg(channel, 16, sample_rate);
    if (len == 0 || (FALSE == g_audio_hdl.is_audio_record_open)) {
        return send_len;
    }
    // PR_DEBUG("record channel:%d, sample_rate:%d", channel, sample_rate);
    switch (ty_audio_type) {
    case TYPE_NET: {
        send_len = ty_usb_audio_record_get_buf_net(ptr, len);
    }
    break;
    case TYPE_TEST: {
        send_len = ty_usb_audio_record_get_buf_test(ptr, len);
    }
    break;
    case TYPE_TEST_NEW: {
        send_len = ty_usb_audio_record_get_buf_test_new(ptr, len);
    }
    break;
    }
    return send_len;
}

STATIC INT_T usb_host_audio_test_init(VOID)
{
    usb_host_audio_init(0, usb_host_audio_play_put_buf_test, usb_host_audio_record_get_buf_test);
#if USB_MAX_HW_NUM > 1
    usb_host_audio_init(1, usb_host_audio_play_put_buf_test, usb_host_audio_record_get_buf_test);
#endif

    return 0;
}
/* late_initcall(usb_host_audio_test_init); */

#endif


OPERATE_RET audio_cfg_init(TY_AUDIO_PARAM *audio_param)
{
    PR_DEBUG("into audio cfg init");
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    if (audio_param->sample_rate > 8000) {
        voice_buf_size = AUDIO_RECORD_VOICE_UPLORD_LEN;
    }
    PR_NOTICE("audio param:%d %d %d %d", audio_param->sample_rate, audio_param->bit_dept, audio_param->channel_num, audio_param->audio_power_off);
    ty_set_audio_cfg(audio_param->channel_num, audio_param->bit_dept, audio_param->sample_rate);
// #if TCFG_HOST_AUDIO_ENABLE
    // usb_audio_set_cfg((UCHAR_T)audio_param->channel_num, (UCHAR_T)audio_param->bit_dept, (UINT_T)audio_param->sample_rate);
// #endif
    PCM_SAMPLE_RATE = audio_param->sample_rate;
    PCM_CHANNEL = audio_param->channel_num;
    PCM_BIT_DEP = audio_param->bit_dept;
    audio_power_off = audio_param->audio_power_off;
    return OPRT_OK;
}

STATIC OPERATE_RET tuya_audio_soft_init(VOID)
{
    OPERATE_RET op_ret;
    u8 *pcm_buff_w = NULL;
    u8 *pcm_buff_r = NULL;
    PR_DEBUG("into tuya audio soft init");
    pcm_buff_w = Malloc(PCM_SAMPLE_RATE * PCM_CHANNEL * 20);
    cbuf_init(&g_audio_hdl.pcm_cbuff_w, pcm_buff_w, PCM_SAMPLE_RATE * PCM_CHANNEL * 20);
    pcm_buff_r = Malloc(PCM_SAMPLE_RATE * PCM_CHANNEL * 20);
    cbuf_init(&g_audio_hdl.pcm_cbuff_r, pcm_buff_r, PCM_SAMPLE_RATE * PCM_CHANNEL * 20);


#if (TCFG_HOST_AUDIO_ENABLE==0)
#if 1
    if (!g_audio_hdl.enc_server) {
        g_audio_hdl.enc_server = server_open("audio_server", "enc");
        if (!g_audio_hdl.enc_server) {
            op_ret = OPRT_COM_ERROR;
            PR_ERR("server_open err:%d", op_ret);
            return op_ret;
        }
        PR_DEBUG("enc server_open succ!");
        // server_register_event_handler_to_task(g_audio_hdl.enc_server, NULL, enc_server_event_handler,"app_core");
    }
#endif
    if (!g_audio_hdl.dec_server) {
        g_audio_hdl.dec_server = server_open("audio_server", "dec");
        if (!g_audio_hdl.dec_server) {
            op_ret = OPRT_COM_ERROR;
            PR_ERR("server_open err:%d", op_ret);
            return op_ret;
        }
        PR_DEBUG("dec server_open succ!");
        PR_DEBUG("enc_server 0x%x dec_server 0x%x", g_audio_hdl.enc_server, g_audio_hdl.dec_server);
    }
#else
#if TY_HOST_UAC_WITH_HW_AUDIO
    if (!g_audio_hdl.dec_server) {
        g_audio_hdl.dec_server = server_open("audio_server", "dec");
        if (!g_audio_hdl.dec_server) {
            op_ret = OPRT_COM_ERROR;
            PR_ERR("server_open err:%d", op_ret);
            return op_ret;
        }
        /* server_register_event_handler_to_task(g_audio_hdl.dec_server, NULL, dec_server_event_handler, "app_core"); */
        if (g_audio_hdl.dec_server) {
            __this->dec_server = g_audio_hdl.dec_server;
            __this->volume = INIT_VOLUME_VALUE;
            __this->dec_ops = &local_music_dec_ops;
            //PR_NOTICE("enc_server 0x%x dec_server 0x%x",g_audio_hdl.enc_server,g_audio_hdl.dec_server);
        }
    }
#endif
#endif

    op_ret = tuya_hal_semaphore_create_init(&g_audio_ctrl.r_sem, 0, 1);
    if (op_ret != OPRT_OK) {
        PR_ERR("tuya_hal_semaphore_create_init create semphore err:%d", op_ret);
        return op_ret;
    }

//    CreateMsgQueAndInit(&g_audio_ctrl.msg_que);
//    op_ret = tal_queue_create_init(&g_audio_ctrl.msg_que, sizeof(TY_AUDIO_CTRL_MSG*), 20);
    QS queue_size = (SIZEOF(TY_AUDIO_CTRL_MSG *) * 20 + sizeof(WORD) - 1) / sizeof(WORD);
    op_ret = os_q_create(&g_audio_ctrl.msg_que, queue_size);
    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_1;
    thrd_param.stackDepth = 1024 * 2;
    thrd_param.thrdname = TY_AUDIO_TASK_NAME;
    op_ret = CreateAndStart(&g_audio_ctrl.task_handle, NULL, NULL, __audio_task, NULL, &thrd_param);

    PR_DEBUG("ty_audio_task create");
    return op_ret;
}

VOID tuya_audio_init(TY_AUDIO_PARAM *audio_param)
{
    PR_DEBUG("into tuya audio inti!");
    STATIC UCHAR_T init = 0;

    audio_cfg_init(audio_param);
    if (!init) {
        tuya_audio_soft_init();
    }

#if defined(TY_AUDIO_TEST) && (TY_AUDIO_TEST == 1)
    if (!init) {
        ty_device_audio_test(TRUE);
    }
#endif

    init = 1;
}

OPERATE_RET tuya_audio_hw_local_play(UINT_T audio)
{
#if TY_HOST_UAC_WITH_HW_AUDIO
    return tuya_send_audio_msg(MSG_HW_START_LOCAL_AUDIO_PLAY, &audio, SIZEOF(UINT_T));
#else
    return OPRT_OK;
#endif

}

OPERATE_RET tuya_audio_hw_local_stop(VOID)
{
#if TY_HOST_UAC_WITH_HW_AUDIO
    return tuya_send_audio_msg(MSG_HW_STOP_LOCAL_AUDIO_PLAY, NULL, 0);
#else
    return OPRT_OK;
#endif

}

OPERATE_RET ty_device_first_recorder_next_paly_test(UINT_T record_time_s)
{
    audio_test_recorder_first_play_times = record_time_s * 1000;
    if (audio_test_recorder_first_play_next) {
        return OPRT_COM_ERROR;
    }
    PR_NOTICE("audio_test_recorder_first_play_next %d", audio_test_recorder_first_play_times);
    audio_test_recorder_first_play_next = MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST_START;
    return tuya_send_audio_msg(MSG_AUDIO_RECORDER_FIRST_PLAY_NEXT_TEST, NULL, 0);
}
#endif

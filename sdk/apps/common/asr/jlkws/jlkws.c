#include "server/audio_server.h"
#include "server/server_core.h"
#include "generic/circular_buf.h"
#include "os/os_api.h"
#include "event.h"
#include "app_config.h"
#include "jlsp_far_keyword.h"
#include "event/key_event.h"
/* #include "jlsp_kws_aec.h" */

#if (defined CONFIG_ASR_ALGORITHM) && (CONFIG_ASR_ALGORITHM == JLKWS_ALGORITHM)

#define LOG_TAG             "[JLKWS]"
#define LOG_ERROR_ENABLE
#define LOG_WARN_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


const int CONFIG_KWS_RAM_USE_ENABLE = 1;

extern void aisp_resume(void);

#define ONCE_SR_POINTS	160//256

#define AISP_BUF_SIZE	(ONCE_SR_POINTS * 2 * 2)	//跑不过来时适当加大倍数
#define MIC_SR_LEN		(ONCE_SR_POINTS * 2)

#ifdef CONFIG_AEC_ENC_ENABLE

/*aec module enable bit define*/
#define AEC_EN              BIT(0)
#define NLP_EN              BIT(1)
#define ANS_EN              BIT(2)

#define AEC_MODE_ADVANCE	(AEC_EN | NLP_EN | ANS_EN)
#define AEC_MODE_REDUCE		(NLP_EN | ANS_EN)
#define AEC_MODE_SIMPLEX	(ANS_EN)

#endif

#define AEC_DATA_TO_SD 0 //将唤醒前的mic/dac/aec数据写卡进行查看,3channel(mic,dac,aec)

static struct {
    int pid;
    u16 sample_rate;
    u8 volatile exit_flag;
    int volatile run_flag;
    OS_SEM sem;
    s16 mic_buf[AISP_BUF_SIZE * 2];
    void *mic_enc;
    cbuffer_t mic_cbuf;
} aisp_server;

#define __this (&aisp_server)

static const float confidence[8] = {
    0.5, 0.5, 0.5, 0.5, //小杰小杰，小杰同学，播放音乐，暂停播放
    0.5, 0.5, 0.5, 0.5, //增大音量，减小音量，上一首, 下一首
};

enum {
    PLAY_MUSIC_EVENT = 4,
    STOP_MUSIC_EVENT,
    VOLUME_INC_EVENT = 7,
    VOLUME_DEC_EVENT,
    SONG_PREVIOUS_EVENT,
    SONG_NEXT_EVENT,
};

static void aisp_task(void *priv)
{
    u32 mic_len, linein_len;
    u32 time = 0, time_cnt = 0, cnt = 0;
    int ret;
    int model = 0;
    int model_size, private_heap_size, share_heap_size;
    void *kws = NULL;
    u8 *private_heap = NULL, *share_heap = NULL;
    int online = 0;

    jl_far_kws_model_get_heap_size(model, &model_size, &private_heap_size, &share_heap_size);

    private_heap = zalloc(private_heap_size);
    if (!private_heap) {
        goto __exit;
    }

    share_heap	 = zalloc(share_heap_size);
    if (!share_heap) {
        goto __exit;
    }

    kws = jl_far_kws_model_init(model, private_heap, private_heap_size, share_heap, share_heap_size, model_size, confidence, online);
    if (!kws) {
        goto __exit;
    }

#if AEC_DATA_TO_SD
    aec_data_to_sd_open();
#endif

    aisp_resume();

    while (1) {
        if (__this->exit_flag) {
            break;
        }

        if (!__this->run_flag) {
            os_sem_pend(&__this->sem, 0);
            continue;
        }

        if (__this->exit_flag) {
            break;
        }

        if ((cbuf_get_data_size(&__this->mic_cbuf) < ONCE_SR_POINTS * 2)) {
            os_sem_pend(&__this->sem, 0);
            continue;
        }
        short near_data_buf[ONCE_SR_POINTS];
        mic_len = cbuf_read(&__this->mic_cbuf, near_data_buf, ONCE_SR_POINTS * 2);
        if (!mic_len) {
            continue;
        }

        time = timer_get_ms();
        ret = jl_far_kws_model_process(kws, model, (u8 *)near_data_buf, sizeof(near_data_buf));
        if (ret > 1) {
            log_info("jlkws wakeup event : %d", ret);
#if AEC_DATA_TO_SD
            if (__this->mic_enc) {
                union audio_req req = {0};
                req.enc.cmd = AUDIO_ENC_STOP;
                server_request(__this->mic_enc, AUDIO_REQ_ENC, &req);
                server_close(__this->mic_enc);
                __this->mic_enc = NULL;

                aec_data_to_sd_close();

            }
#endif

            //add your button event according to ret
            struct key_event key = {0};

            if (ret == PLAY_MUSIC_EVENT) {
                key.action = KEY_EVENT_UP;
                key.value = KEY_LOCAL;
            } else if (ret == STOP_MUSIC_EVENT) {
                key.action = KEY_EVENT_HOLD;
                key.value = KEY_LOCAL;
            } else if (ret == VOLUME_INC_EVENT) {
                key.action = KEY_EVENT_CLICK;
                key.value = KEY_VOLUME_INC;
            } else if (ret == VOLUME_DEC_EVENT) {
                key.action = KEY_EVENT_CLICK;
                key.value = KEY_VOLUME_DEC;
            } else if (ret == SONG_PREVIOUS_EVENT) {
                key.action = KEY_EVENT_LONG;
                key.value = KEY_UP;
            } else if (ret == SONG_NEXT_EVENT) {
                key.action = KEY_EVENT_LONG;
                key.value = KEY_DOWN;
            } else {
                key.action = KEY_EVENT_CLICK;
                key.value = KEY_ENC;
            }

            key.type = KEY_EVENT_USER;
            key_event_notify(KEY_EVENT_FROM_USER, &key);

            jl_far_kws_model_reset(kws);
        }

        time_cnt += timer_get_ms() - time;
        if (++cnt == 100) {
            /* printf("aec time :%d \n", time_cnt); */
            time_cnt = cnt = 0;
        }
    }

__exit:

    if (kws) {
        jl_far_kws_model_free(kws);
    }
    if (private_heap) {
        free(private_heap);
    }
    if (share_heap) {
        free(share_heap);
    }

    __this->run_flag = 0;

}

static void enc_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
    case AUDIO_SERVER_EVENT_END:
        break;
    default:
        break;
    }
}

static int aisp_vfs_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;

    u32 wlen = cbuf_write(cbuf, data, len);
    if (wlen != len) {
        cbuf_clear(&__this->mic_cbuf);
        log_warn("jlkws busy!");
    }
    os_sem_set(&__this->sem, 0);
    os_sem_post(&__this->sem);

    return len;
}

static int aisp_vfs_fclose(void *file)
{
    return 0;
}

static const struct audio_vfs_ops aisp_vfs_ops = {
    .fwrite = aisp_vfs_fwrite,
    .fclose = aisp_vfs_fclose,
};

int aisp_open(u16 sample_rate)
{
    __this->exit_flag = 0;
    __this->mic_enc = server_open("audio_server", "enc");
    server_register_event_handler(__this->mic_enc, NULL, enc_server_event_handler);
    cbuf_init(&__this->mic_cbuf, __this->mic_buf, sizeof(__this->mic_buf));
    os_sem_create(&__this->sem, 0);
    __this->sample_rate = sample_rate;

    return thread_fork("aisp", 3, 1024, 0, &__this->pid, aisp_task, __this);
}

void aisp_suspend(void)
{
    union audio_req req = {0};

    if (!__this->run_flag) {
        return;
    }

    __this->run_flag = 0;

    req.enc.cmd = AUDIO_ENC_STOP;
    server_request(__this->mic_enc, AUDIO_REQ_ENC, &req);
    cbuf_clear(&__this->mic_cbuf);
}

void aisp_resume(void)
{
    union audio_req req = {0};

    if (__this->run_flag) {
        return;
    }
    __this->run_flag = 1;
    os_sem_set(&__this->sem, 0);
    os_sem_post(&__this->sem);

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    req.enc.channel_bit_map = BIT(CONFIG_AISP_MIC0_ADC_CHANNEL);
#endif
    req.enc.frame_size = ONCE_SR_POINTS * 2 * req.enc.channel;
    req.enc.volume = CONFIG_AISP_MIC_ADC_GAIN;
    req.enc.sample_rate = __this->sample_rate;
    req.enc.format = "pcm";
#if CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_PLNK0
    req.enc.sample_source = "plnk0";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_PLNK1
    req.enc.sample_source = "plnk1";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_IIS0
    req.enc.sample_source = "iis0";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_IIS1
    req.enc.sample_source = "iis1";
#else
    req.enc.sample_source = "mic";
#endif
    req.enc.vfs_ops = &aisp_vfs_ops;
    req.enc.output_buf_len = req.enc.frame_size * 5;
    req.enc.file = (FILE *)&__this->mic_cbuf;
#ifdef CONFIG_AEC_ENC_ENABLE
    struct aec_s_attr aec_param = {0};
    aec_param.EnableBit = AEC_MODE_ADVANCE;
    req.enc.aec_attr = &aec_param;
    req.enc.aec_enable = 1;

    extern void get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);

    if (aec_param.EnableBit == 0) {
        req.enc.aec_enable = 0;
        req.enc.aec_attr = NULL;
    }
    if (aec_param.EnableBit != AEC_MODE_ADVANCE) {
        aec_param.output_way = 0;
    }

#if defined TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN && defined CONFIG_AISP_LINEIN_ADC_CHANNEL && defined CONFIG_AEC_HW_REC_LINEIN_ENABLE
    if (req.enc.aec_enable) {
        aec_param.output_way = 1;	 //1:使用硬件回采 0:使用软件回采
        req.enc.rec_linein_channel_bit_map = BIT(CONFIG_AISP_LINEIN_ADC_CHANNEL); //设置linein的回采通道
        req.enc.channel_bit_map |= BIT(CONFIG_AISP_LINEIN_ADC_CHANNEL);	 //配置回采硬件通道
        if (CONFIG_AISP_LINEIN_ADC_CHANNEL < CONFIG_PHONE_CALL_ADC_CHANNEL) {
            req.enc.ch_data_exchange = 1;	 //如果回采通道使用的硬件channel比MIC通道使用的硬件channel靠前的话处理数据时需要交换一下顺序
        }
    }
#endif

    if (req.enc.sample_rate == 16000) {
        aec_param.wideband = 1;
#ifdef CONFIG_AEC_USE_PLAY_MUSIC_ENABLE
        aec_param.hw_delay_offset = 640;
#else
        aec_param.hw_delay_offset = 30;
#endif
    } else {
        aec_param.wideband = 0;
        aec_param.hw_delay_offset = 75;
    }

#ifdef CONFIG_AEC_USE_PLAY_MUSIC_ENABLE
    if (aec_param.output_way == 0) {
        aec_param.dac_ref_sr = 48000; //aec软件回采dac参考采样率
    }
#endif

#endif

    server_request(__this->mic_enc, AUDIO_REQ_ENC, &req);

#if defined CONFIG_AEC_ENC_ENABLE && !defined CONFIG_FPGA_ENABLE
    if (aec_param.output_way) {
#ifdef TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
        extern void adc_multiplex_set_gain(const char *source, u8 channel_bit_map, u8 gain);
        adc_multiplex_set_gain("linein", BIT(CONFIG_AISP_LINEIN_ADC_CHANNEL), CONFIG_AISP_LINEIN_ADC_GAIN * 2);
#endif
    }
#endif

}

void aisp_close(void)
{
    if (__this->exit_flag) {
        return;
    }

    aisp_suspend();

    __this->exit_flag = 1;

    os_sem_post(&__this->sem);

    if (__this->mic_enc) {
        server_close(__this->mic_enc);
        __this->mic_enc = NULL;
    }
    thread_kill(&__this->pid, KILL_WAIT);
}

#endif


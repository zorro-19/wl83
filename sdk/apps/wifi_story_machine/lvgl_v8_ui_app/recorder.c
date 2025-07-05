#include "app_config.h"

#ifdef CONFIG_AUDIO_ENABLE
#include "server/audio_server.h"
#include "server/server_core.h"
#include "system/app_core.h"
#include "generic/circular_buf.h"
#include "os/os_api.h"
#include "syscfg/syscfg_id.h"
#include "event/key_event.h"
#include "storage_device.h"
#include "fs/fs.h"
#include <time.h>
#include "system/timer.h"
#include "media/spectrum/SpectrumShow_api.h"
#include "network_download/net_audio_buf.h"

#define CONFIG_STORE_VOLUME
#define MIN_VOLUME_VALUE	0
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE   50
//*********************************************************************************//
//                            AUDIO_ADC应用的通道配置                              //
//*********************************************************************************//
#define AUDIO_ENC_SAMPLE_SOURCE_MIC         0  //录音输入源：MIC
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK0       1  //录音输入源：数字麦PLNK0
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK1       2  //录音输入源：数字麦PLNK1
#define AUDIO_ENC_SAMPLE_SOURCE_IIS0        3  //录音输入源：IIS0
#define AUDIO_ENC_SAMPLE_SOURCE_IIS1        4  //录音输入源：IIS1
#define AUDIO_ENC_SAMPLE_SOURCE_LINEIN      5  //录音输入源：LINEIN

#define CONFIG_AUDIO_ENC_SAMPLE_SOURCE      AUDIO_ENC_SAMPLE_SOURCE_MIC    //录音输入源选择
#define CONFIG_AUDIO_DEC_PLAY_SOURCE        "dac"                          //播放输出源选择
#define CONFIG_AUDIO_RECORDER_SAMPLERATE    16000                          //录音采样率
#define CONFIG_AUDIO_RECORDER_CHANNEL       1                              //录音通道数
#define CONFIG_AUDIO_RECORDER_DURATION      (30 * 1000)                    //录音时长ms
#define CONFIG_AUDIO_RECORDER_SAVE_FORMAT   "wav"                          //录音文件保存格式
#define CONFIG_AUDIO_RECORDER_PLAY_FORMAT   "pcm"                          //自编自解格式仅支持pcm/mp3/aac/jla/amr/opus/ogg/speex格式

#define CONFIG_AUDIO_ADC_CHANNEL_L          1        //左mic/aux通道
#define CONFIG_AUDIO_ADC_CHANNEL_R          0        //右mic/aux通道
#define CONFIG_UAC_MIC_ADC_CHANNEL          0        //UAC mic通道
#define CONFIG_AUDIO_ADC_GAIN               100      //mic/aux增益

#define CONFIG_AISP_MIC0_ADC_CHANNEL        0		//本地唤醒左mic通道
#define CONFIG_AISP_MIC1_ADC_CHANNEL        1		//本地唤醒右mic通道
#define CONFIG_AISP_LINEIN_ADC_CHANNEL      1		//本地唤醒LINEIN回采DAC通道
#define CONFIG_AISP_MIC_ADC_GAIN            80		//本地唤醒mic增益
#define CONFIG_AISP_LINEIN_ADC_GAIN         60		//本地唤醒LINEIN增益

#define LOG_TAG             "[RECORDER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"


struct recorder_hdl {
    FILE *fp;
    struct server *enc_server;
    struct server *dec_server;
    void *cache_buf;
    void *net_buf;
    cbuffer_t save_cbuf;
    OS_SEM w_sem;
    OS_SEM r_sem;
    volatile u8 run_flag;
    u8 volume;
    u8 gain;
    u8 channel;
    u8 direct;
    const char *sample_source;
    int sample_rate;
#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    void *work_buf;
    s16 *out_buf;
    u32 out_buf_size;
    u32 offset;
    u16 show_timer_id;
#endif
};

static struct recorder_hdl recorder_handler;

#define __this (&recorder_handler)

//AUDIO ADC支持的采样率
static const u16 sample_rate_table[] = {
    8000,
    11025,
    12000,
    16000,
    22050,
    24000,
    32000,
    44100,
    48000,
};

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
static void recorder_spectrum_fft_show(void *p)
{
    if (__this->work_buf) {
        short *db_data = getSpectrumValue(__this->work_buf);
        int num = getSpectrumNum(__this->work_buf);
        if (db_data && num > 0) {
            for (int i = 0; i < num; i++) {
                //输出db_num个 db值
                log_info("db_data db[%d] %d", i, db_data[i]);
            }
        }
    }
}
#endif

//编码器输出PCM数据
static int recorder_vfs_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    if (0 == cbuf_write(cbuf, data, len)) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        cbuf_clear(cbuf);
    }
    os_sem_set(&__this->r_sem, 0);
    os_sem_post(&__this->r_sem);

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    u32 in_remain = len, tlen;

    while (in_remain) {
        if (__this->offset < __this->out_buf_size) {
            tlen = __this->out_buf_size - __this->offset;
            if (tlen > in_remain) {
                tlen = in_remain;
            }
            memcpy((u8 *)__this->out_buf + __this->offset, (u8 *)data + (len - in_remain), tlen);
            __this->offset += tlen;
            in_remain -= tlen;
            if (in_remain && (__this->offset != __this->out_buf_size)) {
                continue;
            }
        }
        if (__this->offset == __this->out_buf_size) {
            __this->offset = 0;
            SpectrumShowRun(__this->work_buf, __this->out_buf, 512);
        }
    }
#endif

    //此回调返回0录音就会自动停止
    return len;
}

//解码器读取PCM数据
static int recorder_vfs_fread(void *file, void *data, u32 len)
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

static int recorder_vfs_fclose(void *file)
{
    return 0;
}

static int recorder_vfs_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops recorder_vfs_ops = {
    .fwrite = recorder_vfs_fwrite,
    .fread  = recorder_vfs_fread,
    .fclose = recorder_vfs_fclose,
    .flen   = recorder_vfs_flen,
};

#ifdef CONFIG_NET_ENABLE
//编码器输出带格式的数据，除了PCM格式以外，其他格式都要必须实现fseek接口
static int recorder_vfs_with_format_fwrite(void *file, void *data, u32 len)
{
    return net_buf_write((u8 *)data, len, file);
}

//解码器读取带格式的数据
static int recorder_vfs_with_format_fread(void *file, void *data, u32 len)
{
    return net_buf_read(data, len, file);
}

static int recorder_vfs_with_format_seek(void *file, u32 offset, int orig)
{
    return net_buf_seek(offset, orig, file);
}

static int recorder_vfs_with_format_fclose(void *file)
{
    return 0;
}

static int recorder_vfs_with_format_flen(void *file)
{
    return -1;
}

static const struct audio_vfs_ops recorder_vfs_with_format_ops = {
    .fwrite = recorder_vfs_with_format_fwrite,
    .fread  = recorder_vfs_with_format_fread,
    .fseek  = recorder_vfs_with_format_seek,
    .fclose = recorder_vfs_with_format_fclose,
    .flen   = recorder_vfs_with_format_flen,
};

#endif

static int recorder_close(void)
{
    union audio_req req = {0};

    if (!__this->run_flag) {
        return 0;
    }

    log_info("----------recorder close----------");

    __this->run_flag = 0;

    if (__this->cache_buf) {
        os_sem_post(&__this->w_sem);
        os_sem_post(&__this->r_sem);
    }

    if (__this->enc_server) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
    }

#ifdef CONFIG_NET_ENABLE
    if (__this->net_buf) {
        net_buf_set_file_end(__this->net_buf);
        /* net_buf_inactive(__this->net_buf); */
    }
#endif

    if (__this->dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    }

    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
        os_sem_del(&__this->w_sem, OS_DEL_ALWAYS);
        os_sem_del(&__this->r_sem, OS_DEL_ALWAYS);
    }

#ifdef CONFIG_NET_ENABLE
    if (__this->net_buf) {
        net_buf_uninit(__this->net_buf);
        __this->net_buf = NULL;
    }
#endif

    if (__this->fp) {
        fclose(__this->fp);
        __this->fp = NULL;
    }

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    if (__this->work_buf) {
        free(__this->work_buf);
        __this->work_buf = NULL;
    }
    if (__this->out_buf) {
        free(__this->out_buf);
        __this->out_buf = NULL;
    }
    if (__this->show_timer_id) {
        sys_timeout_del(__this->show_timer_id);
        __this->show_timer_id = 0;
    }
#endif

    return 0;
}

static void enc_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
    case AUDIO_SERVER_EVENT_END:
        recorder_close();
        break;
    case AUDIO_SERVER_EVENT_SPEAK_START:
        log_info("speak start !");
        break;
    case AUDIO_SERVER_EVENT_SPEAK_STOP:
        log_info("speak stop !");
        break;
    default:
        break;
    }
}

//将MIC的数字信号采集后推到DAC播放
//注意：如果需要播放两路MIC，DAC分别对应的是DACL和DACR，要留意芯片封装是否有DACR引脚出来，
//      而且要使能DAC的双通道输出，DAC如果采用差分输出方式也只会听到第一路MIC的声音
static int recorder_play_to_dac(int sample_rate, u8 channel, const char *format)
{
    int err;
    union audio_req req = {0};

    log_info("----------recorder_play_to_dac----------");

    if (channel > 2) {
        channel = 2;
    }

#ifdef CONFIG_NET_ENABLE
    if (!strcmp(format, "pcm")) {
        goto __pcm;
    }

    //带格式的自编自解
    u32 bufsize = 32 * 1024;
    __this->net_buf = net_buf_init(&bufsize, NULL);
    if (!__this->net_buf) {
        return -1;
    }
    net_buf_active(__this->net_buf);
    net_buf_set_time_out(0, __this->net_buf);

    //BIT(x)用来区分上层需要获取哪个通道的数据
    if (channel == 2) {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L) | BIT(CONFIG_AUDIO_ADC_CHANNEL_R);
    } else {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L);
    }
    req.enc.frame_size = sample_rate / 100 * 4 * channel;	//收集够多少字节PCM数据就回调一次fwrite
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = channel;
    req.enc.volume = __this->gain;
    req.enc.sample_rate = sample_rate;
    req.enc.format = format;
    req.enc.sample_source = __this->sample_source;
    req.enc.vfs_ops = &recorder_vfs_with_format_ops;
    req.enc.file = (FILE *)__this->net_buf;
    if (channel == 1 && !strcmp(__this->sample_source, "mic") && (sample_rate == 8000 || sample_rate == 16000)) {
        req.enc.use_vad = 1; //打开VAD断句功能
        req.enc.dns_enable = 1; //打开降噪功能
        req.enc.vad_auto_refresh = 1; //VAD自动刷新
    }
    if (!strcmp(format, "mp3")) {
        req.enc.bitrate = sample_rate * 2;
    } else if (!strcmp(format, "aac")) {
        req.enc.bitrate = sample_rate * 4;
        req.enc.no_header = 1;
    } else if (!strcmp(format, "jla")) {
        req.enc.bitrate = sample_rate * 4;
    } else if (!strcmp(format, "speex")) {
        req.enc.bitrate = 5;    //1-9
    }

    err = server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
    if (err) {
        goto __err;
    }

    memset(&req, 0, sizeof(union audio_req));

    /****************打开解码器*******************/
    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.output_buf_len  = 4 * 1024;
    req.dec.vfs_ops         = &recorder_vfs_with_format_ops;
    req.dec.dec_type        = format;
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;
    req.dec.file            = (FILE *)__this->net_buf;
    /* req.dec.attr            = AUDIO_ATTR_LR_ADD; */          //左右声道数据合在一起,封装只有DACL但需要测试两个MIC时可以打开此功能
    if (!strcmp(format, "jla")) {
        //头部信息没有采样率和通道数的格式需要手动设置以下信息
        req.dec.sample_rate = sample_rate;
        req.dec.channel     = channel;
    }

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    req.dec.attr = AUDIO_ATTR_NO_WAIT_READY;
    return server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

__pcm:
#endif
    //不带格式的自编自解
    __this->cache_buf = malloc(sample_rate * channel); //上层缓冲buf缓冲0.5秒的数据，缓冲太大听感上会有延迟
    if (__this->cache_buf == NULL) {
        return -1;
    }
    cbuf_init(&__this->save_cbuf, __this->cache_buf, sample_rate * channel);

    os_sem_create(&__this->w_sem, 0);
    os_sem_create(&__this->r_sem, 0);

    __this->run_flag = 1;

    /****************打开解码器*******************/
    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = __this->volume;
    req.dec.output_buf_len  = 4 * 1024;
    req.dec.channel         = channel;
    req.dec.sample_rate     = sample_rate;
    req.dec.vfs_ops         = &recorder_vfs_ops;
    req.dec.dec_type        = "pcm";
    req.dec.sample_source   = CONFIG_AUDIO_DEC_PLAY_SOURCE;
    req.dec.file            = (FILE *)&__this->save_cbuf;
    /* req.dec.attr            = AUDIO_ATTR_LR_ADD; */          //左右声道数据合在一起,封装只有DACL但需要测试两个MIC时可以打开此功能

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    req.dec.attr = AUDIO_ATTR_NO_WAIT_READY;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

#ifdef CONFIG_SPECTRUM_FFT_EFFECT_ENABLE
    __this->work_buf = zalloc(getSpectrumShowBuf());
    if (!__this->work_buf) {
        goto __err1;
    }
    __this->offset = 0;
    __this->out_buf_size = 512 * 2 * channel;
    __this->out_buf = zalloc(__this->out_buf_size);
    if (!__this->out_buf) {
        free(__this->work_buf);
        __this->work_buf = NULL;
        goto __err1;
    }

    SpectrumShowInit(__this->work_buf, 0.9, 0.9,
                     sample_rate, channel, channel > 1 ? 2 : 0, JL_FFT_BASE);

    __this->show_timer_id = sys_timer_add(NULL, recorder_spectrum_fft_show, 1000);
#endif

    /****************打开编码器*******************/
    memset(&req, 0, sizeof(union audio_req));

    //BIT(x)用来区分上层需要获取哪个通道的数据
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    if (channel == 2) {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L) | BIT(CONFIG_AUDIO_ADC_CHANNEL_R);
    } else {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L);
    }
#endif
    req.enc.frame_size = sample_rate / 100 * 4 * channel;	//收集够多少字节PCM数据就回调一次fwrite
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = channel;
    req.enc.volume = __this->gain;
    req.enc.sample_rate = sample_rate;
    req.enc.format = "pcm";
    req.enc.sample_source = __this->sample_source;
    req.enc.vfs_ops = &recorder_vfs_ops;
    req.enc.file = (FILE *)&__this->save_cbuf;
    if (channel == 1 && !strcmp(__this->sample_source, "mic") && (sample_rate == 8000 || sample_rate == 16000)) {
        req.enc.use_vad = 1; //打开VAD断句功能
        req.enc.dns_enable = 1; //打开降噪功能
        req.enc.vad_auto_refresh = 1; //VAD自动刷新
    }

    err = server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
    if (err) {
        goto __err1;
    }

    return 0;

__err1:
    req.dec.cmd = AUDIO_DEC_STOP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

__err:
    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
    }
#ifdef CONFIG_NET_ENABLE
    if (__this->net_buf) {
        net_buf_inactive(__this->net_buf);
        net_buf_uninit(__this->net_buf);
        __this->net_buf = NULL;
    }
#endif

    __this->run_flag = 0;

    return -1;
}

//MIC或者LINEIN模拟直通到DAC，不需要软件参与，AC792芯片不支持模拟直通
static int audio_adc_analog_direct_to_dac(int sample_rate, u8 channel)
{
    union audio_req req = {0};

    log_info("----------audio_adc_analog_direct_to_dac----------");

    __this->run_flag = 1;

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = channel;
    req.enc.volume = __this->gain;
    req.enc.format = "pcm";
    req.enc.sample_source = __this->sample_source;
    req.enc.sample_rate = sample_rate;
    req.enc.direct2dac = 1;
    req.enc.high_gain = 1;
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    if (channel == 4) {
        req.enc.channel_bit_map = 0x0f;
    } else if (channel == 2) {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L) | BIT(CONFIG_AUDIO_ADC_CHANNEL_R);
    } else {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L);
    }
#endif

    return server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
}

//录音文件到SD卡
static int recorder_to_file(int sample_rate, u8 channel, const char *format)
{
    union audio_req req = {0};

    __this->run_flag = 1;
    __this->direct = 0;

    char time_str[64] = {0};
    char file_name[100] = {0};
    u8 dir_len = 0;
    struct tm timeinfo = {0};
    time_t timestamp = time(NULL);
    localtime_r(&timestamp, &timeinfo);
    strcpy(time_str, CONFIG_ROOT_PATH"RECORDER/\\U");
    dir_len = strlen(time_str);
    strftime(time_str + dir_len, sizeof(time_str) - dir_len, "%Y-%m-%dT%H-%M-%S.", &timeinfo);
    strcat(time_str, format);
    log_info("recorder file name : %s", time_str);

    memcpy(file_name, time_str, dir_len);

    for (u8 i = 0; i < strlen(time_str) - dir_len; ++i) {
        file_name[dir_len + i * 2] = time_str[dir_len + i];
    }

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = channel;
    req.enc.volume = __this->gain;
    req.enc.frame_size = 8192;
    req.enc.output_buf_len = req.enc.frame_size * 10;
    req.enc.sample_rate = sample_rate;
    req.enc.format = format;
    req.enc.sample_source = __this->sample_source;
    req.enc.msec = CONFIG_AUDIO_RECORDER_DURATION;
    req.enc.file = __this->fp = fopen(file_name, "w+");
    if (!strcmp(req.enc.format, "aac")) {
        req.enc.bitrate = sample_rate * 4;
        req.enc.no_header = 1;
    }
    /* req.enc.sample_depth = 24; //IIS支持采集24bit深度 */
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    if (channel == 4) {
        req.enc.channel_bit_map = 0x0f;
    } else if (channel == 2) {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L) | BIT(CONFIG_AUDIO_ADC_CHANNEL_R);
    } else {
        req.enc.channel_bit_map = BIT(CONFIG_AUDIO_ADC_CHANNEL_L);
    }
#endif

    return server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
}

static void recorder_play_pause(void)
{
    union audio_req req = {0};

    req.dec.cmd = AUDIO_DEC_PP;
    server_request(__this->dec_server, AUDIO_REQ_DEC, &req);

    req.enc.cmd = AUDIO_ENC_PP;
    server_request(__this->enc_server, AUDIO_REQ_ENC, &req);

    if (__this->cache_buf) {
        cbuf_clear(&__this->save_cbuf);
    }
}

//调整ADC的模拟增益
int recorder_enc_gain_change(int value)
{
    union audio_req req = {0};

    int gain = value;
    if (gain < 0) {
        gain = 0;
    } else if (gain > 100) {
        gain = 100;
    }
    if (gain == __this->gain) {
        return -1;
    }
    __this->gain = gain;

    if (!__this->enc_server) {
        return -1;
    }

    log_info("set_enc_gain: %d", gain);

    req.enc.cmd     = AUDIO_ENC_SET_VOLUME;
    req.enc.volume  = gain;
    return server_request(__this->enc_server, AUDIO_REQ_ENC, &req);
}

//调整DAC的数字音量和模拟音量
int recorder_dec_volume_change(int value)
{
    union audio_req req = {0};

    int volume = value;
    if (volume < MIN_VOLUME_VALUE) {
        volume = MIN_VOLUME_VALUE;
    } else if (volume > MAX_VOLUME_VALUE) {
        volume = MAX_VOLUME_VALUE;
    }
    if (volume == __this->volume) {
        return -1;
    }
    __this->volume = volume;

    if (!__this->dec_server) {
        return -1;
    }

    log_info("set_dec_volume: %d", volume);

#ifdef CONFIG_STORE_VOLUME
    syscfg_write(CFG_MUSIC_VOL, &__this->volume, sizeof(__this->volume));
#endif

    req.dec.cmd     = AUDIO_DEC_SET_VOLUME;
    req.dec.volume  = volume;
    return server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
}

int recorder_mode_init(void)
{
    log_info("recorder_play_main");

    memset(__this, 0, sizeof(struct recorder_hdl));

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

#if CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_PLNK0
    __this->sample_source = "plnk0";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_PLNK1
    __this->sample_source = "plnk1";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_IIS0
    __this->sample_source = "iis0";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_IIS1
    __this->sample_source = "iis1";
#elif CONFIG_AUDIO_ENC_SAMPLE_SOURCE == AUDIO_ENC_SAMPLE_SOURCE_LINEIN
    __this->sample_source = "linein";
#else
    __this->sample_source = "mic";
#endif

    __this->channel = CONFIG_AUDIO_RECORDER_CHANNEL;
    __this->gain = CONFIG_AUDIO_ADC_GAIN;
    __this->sample_rate = CONFIG_AUDIO_RECORDER_SAMPLERATE;

    __this->enc_server = server_open("audio_server", "enc");
    server_register_event_handler_to_task(__this->enc_server, NULL, enc_server_event_handler, "app_core");

    __this->dec_server = server_open("audio_server", "dec");

    return recorder_play_to_dac(__this->sample_rate, __this->channel, CONFIG_AUDIO_RECORDER_PLAY_FORMAT);
}

void recorder_mode_exit(void)
{
    recorder_close();
    server_close(__this->dec_server);
    __this->dec_server = NULL;
    server_close(__this->enc_server);
    __this->enc_server = NULL;
}

#endif

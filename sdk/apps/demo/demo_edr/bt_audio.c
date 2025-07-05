#include "server/audio_server.h"
#include "server/server_core.h"
#include "btstack/avctp_user.h"
#include "btstack/a2dp_media_codec.h"
#include "classic/hci_lmp.h"
#include "app_config.h"
#include "asm/sbc.h"
#include "asm/clock.h"
#include "system/timer.h"

#ifdef CONFIG_BT_ENABLE

#define LOG_TAG             "[BT_AUDIO]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

#define BT_MUSIC_DECODE
#define BT_PHONE_DECODE
#if TCFG_USER_EMITTER_ENABLE
#define BT_EMITTER_ENABLE
#endif

#ifdef BT_MUSIC_DECODE

#define BT_AUDIO_FORMAT_SBC     1
#define BT_AUDIO_FORMAT_AAC     2
#define BT_AUDIO_FORMAT_APTX    3
#define BT_AUDIO_FORMAT_LADC    4
#define BT_AUDIO_FORMAT_CVSD    5
#define BT_AUDIO_FORMAT_MSBC    6


struct bt_media_vfs_handle {
    u8    format;
    u8    a2dp_open;
    u16   seqn;
    void *file;
    void *p_addr;
    int   p_len;
    int   p_pos;
    void *audio_dec;
    OS_SEM sem;
};

static struct bt_media_vfs_handle bt_media_vfs_handle;
#define mfs      (&bt_media_vfs_handle)

u8 get_a2dp_decoder_status(void);

static void sbc_dec_event_handler(void *priv, int argc, int *argv)
{
    union audio_req req = {0};
    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_END:
        break;
    default:
        break;
    }
}

#define RB16(b)    (u16)(((u8 *)b)[0] << 8 | (((u8 *)b))[1])

static int get_rtp_header_len(u8 *buf, int len)
{
    int ext, csrc;
    int byte_len;
    int header_len = 0;
    u8 *data = buf;

    if (RB16(buf + 2) != (u16)(mfs->seqn + 1) && mfs->seqn) {
        putchar('K');
    }
    mfs->seqn = RB16(buf + 2);

    csrc = buf[0] & 0x0f;
    ext  = buf[0] & 0x10;

    byte_len = 12 + 4 * csrc;
    buf += byte_len;
    if (ext) {
        ext = (RB16(buf + 2) + 1) << 2;
    }

    header_len = byte_len + ext + 1;
    if (mfs->format == BT_AUDIO_FORMAT_SBC) {
        /*sbc兼容性处理*/
        while (data[header_len] != 0x9c) {
            if (++header_len > len) {
                log_w("sbc warn\n");
                return len;
            }
        }
    }

    if (header_len != byte_len + ext + 1) {
        /* log_w("sbc warn!!!\n"); */
        /* put_buf(data, len); */
    }

    return header_len;
}

static void media_stream_free(void)
{
    if (mfs->p_addr) {
        a2dp_media_free_packet(mfs->file, mfs->p_addr);
        mfs->p_addr = NULL;
        mfs->p_pos = 0;
        mfs->p_len = 0;
    }
}

static void a2dp_source_wake_decode(void *priv)
{
    os_sem_set(&mfs->sem, 0);
    os_sem_post(&mfs->sem);
}

static int bt_sbc_file_read(void *priv, void *buf, u32 len)
{
    struct a2dp_media_frame frame;
    u32 r_len = 0;
    u32 offset = 0;

    do {
        if (!mfs->p_addr) {
            frame.packet = NULL;
            mfs->p_len = a2dp_media_get_packet(mfs->file, &frame);
            if (!frame.packet) {
                if (!mfs->a2dp_open) {
                    return 0;
                }
                os_sem_pend(&mfs->sem, 0);
                continue;
            }
            mfs->p_addr = frame.packet;
            mfs->p_pos = get_rtp_header_len(mfs->p_addr, mfs->p_len);
            if (mfs->p_pos >= len) {
                return 0;
            }
        }

        if (len == (u32) - 1) {	//第一包
            if (0x800 > mfs->p_len && mfs->format == BT_AUDIO_FORMAT_SBC) {
                memcpy(buf, (u8 *)mfs->p_addr, mfs->p_len);
                offset = mfs->p_len;
                media_stream_free();
                break;
            } else {
                if (mfs->format == BT_AUDIO_FORMAT_SBC) {
                    memcpy(buf, (u8 *)mfs->p_addr, 0x20);
                } else {
                    memcpy(buf, (u8 *)mfs->p_addr + mfs->p_pos, 0x20);
                }
                offset = 0x20;
                media_stream_free();
                break;
            }
        }

        r_len = mfs->p_len - mfs->p_pos;
        if (r_len > (len - offset)) {
            r_len = len - offset;
        }

        memcpy((u8 *)buf + offset, (u8 *)mfs->p_addr + mfs->p_pos, r_len);
        mfs->p_pos += r_len;
        offset += r_len;

        if (mfs->p_pos >= mfs->p_len) {
            media_stream_free();
            if (mfs->format == BT_AUDIO_FORMAT_SBC) {
                break;
            }
        }
    } while (offset < len);

    return offset;
}

static int bt_sbc_file_seek(void *priv, u32 offset, int orig)
{
    return 0;
}

static const struct audio_vfs_ops bt_sbc_audio_dec_vfs_ops = {
    .fread = bt_sbc_file_read,
    .fseek = bt_sbc_file_seek,
};

void *earphone_a2dp_audio_codec_open(int media_type, u8 volume, u8 *bt_addr)
{
    union audio_req req = {0};
    int err = 0;

    mfs->file = a2dp_open_media_file(bt_addr);
    if (!mfs->file) {
        return NULL;
    }

    os_sem_create(&mfs->sem, 0);
    a2dp_media_set_rx_notify(mfs->file, mfs, a2dp_source_wake_decode);
    a2dp_media_start_play(mfs->file);

    while (a2dp_media_get_remain_play_time(mfs->file, 0) <= 0) {
        if (get_a2dp_decoder_status() == 0) {
            return NULL;
        }
        msleep(10);
    }

    mfs->audio_dec = server_open("audio_server", "dec");
    if (!mfs->audio_dec) {
        return NULL;
    }

    /*播放事件注册(这个可以先不用加,根据需要添加)*/
    server_register_event_handler(mfs->audio_dec, mfs, sbc_dec_event_handler);

    switch (media_type) {
    case A2DP_CODEC_SBC:
        req.dec.dec_type = "sbc";
        mfs->format = BT_AUDIO_FORMAT_SBC;
        break;
    case A2DP_CODEC_MPEG24:
        req.dec.dec_type = "aac";
        mfs->format = BT_AUDIO_FORMAT_AAC;
        break;
    }

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = volume;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = 2 * 1024;
    req.dec.channel         = 0;
    req.dec.sample_rate     = 0;
    req.dec.vfs_ops         = &bt_sbc_audio_dec_vfs_ops;
    req.dec.sample_source   = "dac";

    if (media_type == A2DP_CODEC_MPEG24) {
        req.dec.attr        |= AUDIO_ATTR_BT_AAC_EN;
    }

    mfs->a2dp_open = 1;

    err = server_request(mfs->audio_dec, AUDIO_REQ_DEC, &req);
    if (err) {
        mfs->a2dp_open = 0;
        server_close(mfs->audio_dec);
        mfs->audio_dec = NULL;
        return NULL;
    }

    mfs->seqn = 0;

    req.dec.cmd = AUDIO_DEC_START;
    server_request(mfs->audio_dec, AUDIO_REQ_DEC, &req);

    return mfs->audio_dec;
}

void earphone_a2dp_audio_codec_close(u8 *bt_addr)
{
    union audio_req req = {0};

    mfs->a2dp_open = 0;

    if (mfs->file) {
        os_sem_post(&mfs->sem);
        a2dp_media_stop_play(mfs->file);
        a2dp_media_set_rx_notify(mfs->file, NULL, NULL);
    }

    if (mfs->audio_dec) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(mfs->audio_dec, AUDIO_REQ_DEC, &req);
        server_close(mfs->audio_dec);
        mfs->audio_dec = NULL;
    }

    if (mfs->file) {
        a2dp_close_media_file(mfs->file);
        a2dp_media_close(bt_addr);
        mfs->file = NULL;
        os_sem_del(&mfs->sem, OS_DEL_ALWAYS);
    }

    media_stream_free();
}

#endif


#ifdef BT_PHONE_DECODE

void phone_call_end(void);

struct bt_phone_vfs_handle {
    u8    format;
    u8    mute;
    u8    lmp_open;
    u8    offset;
    u8   *buffer;
    void *p_addr;
    int   p_len;
    int   p_pos;
    u16   frame_offset;
    u16   frame_len;
    void *audio_dec;
    void *audio_enc;
};

static struct bt_phone_vfs_handle bt_phone_vfs_handle;
#define pfs      (&bt_phone_vfs_handle)


static u8 headcheck(u8 *buf)
{
    int sync_word = buf[0] | ((buf[1] & 0x0f) << 8);
    return (sync_word == 0x801) && (buf[2] == 0xAD);
}

static const u8 msbc_mute_data[] = {
    0xAD, 0x00, 0x00, 0xC5, 0x00, 0x00, 0x00, 0x00, 0x77, 0x6D, 0xB6, 0xDD, 0xDB, 0x6D, 0xB7, 0x76,
    0xDB, 0x6D, 0xDD, 0xB6, 0xDB, 0x77, 0x6D, 0xB6, 0xDD, 0xDB, 0x6D, 0xB7, 0x76, 0xDB, 0x6D, 0xDD,
    0xB6, 0xDB, 0x77, 0x6D, 0xB6, 0xDD, 0xDB, 0x6D, 0xB7, 0x76, 0xDB, 0x6D, 0xDD, 0xB6, 0xDB, 0x77,
    0x6D, 0xB6, 0xDD, 0xDB, 0x6D, 0xB7, 0x76, 0xDB, 0x6C, 0x00,
};

static const u8 msbc_err_data[] = {
    0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
};

static void phone_stream_free(void)
{
    if (pfs->p_addr) {
        lmp_private_free_esco_packet(pfs->p_addr);
        pfs->p_addr = NULL;
        pfs->p_pos = 0;
        pfs->p_len = 0;
    }
}

static int bt_phone_file_read(void *priv, void *buf, u32 len)
{
    u32 r_len = 0;
    u32 offset = 0;
    u32 hash = 0;

    do {
        if (!pfs->lmp_open) {
            log_info("lmp file close");
            return 0;
        }
        if (!pfs->p_addr) {
            if (pfs->mute && pfs->format == BT_AUDIO_FORMAT_MSBC) {
                //不从协议栈获取数据包，直接返回
                memcpy((u8 *)buf, msbc_mute_data, len);
                return len;
            }
            pfs->p_addr = (u8 *)lmp_private_get_esco_packet(&pfs->p_len, &hash);
            if (pfs->p_addr) {
                if (((u8 *)pfs->p_addr)[0] == 0x55 && ((u8 *)pfs->p_addr)[1] == 0x55 && ((u8 *)pfs->p_addr)[2] == 0xAA && ((u8 *)pfs->p_addr)[3] == 0xAA) {
                    phone_stream_free();
                    if (offset && pfs->format == BT_AUDIO_FORMAT_MSBC) {
                        pfs->offset = offset;
                        memcpy((u8 *)pfs->buffer, buf, pfs->frame_len);
                    }
                    //错包返回-2
                    return -2;
                }
            } else {
                if (!pfs->lmp_open) {
                    log_info("lmp file close");
                    return 0;
                }
                if (offset && pfs->format == BT_AUDIO_FORMAT_MSBC) {
                    pfs->offset = offset;
                    memcpy((u8 *)pfs->buffer, buf, pfs->frame_len);
                }
                //没有数据
                return -1;
            }
        }

        if (pfs->frame_offset == 0) {
            if (pfs->format == BT_AUDIO_FORMAT_MSBC) {
                u32 head_offset = 0;
                u8 *ptr = (u8 *)pfs->p_addr + pfs->p_pos;
                int check_len = pfs->p_len - pfs->p_pos;
                while (head_offset < check_len) {
                    if (ptr[head_offset] == 0xAD) {
                        if (head_offset >= 2) {
                            if (!headcheck(ptr + head_offset - 2)) {
                                /* put_buf(pfs->p_addr, pfs->p_len); */
                                head_offset++;
                                continue;
                            }
                        }
                        break;
                    }
                    head_offset++;
                }

                if (head_offset >= pfs->frame_len + 2) {
                    phone_stream_free();
                    continue;
                }

                pfs->p_pos += head_offset;
            } else if (pfs->format == BT_AUDIO_FORMAT_CVSD) {
                pfs->frame_len = pfs->p_len;
            }
        }

        r_len = pfs->frame_len - pfs->frame_offset;

        if (pfs->offset) {
            memcpy(buf, pfs->buffer, pfs->frame_len);
            offset = pfs->offset;
            pfs->offset = 0;
        }

        if (r_len > (len - offset)) {
            r_len = len - offset;
        }

        if (r_len > (pfs->p_len - pfs->p_pos)) {
            r_len = pfs->p_len - pfs->p_pos;
        }

        memcpy((u8 *)buf + offset, (u8 *)pfs->p_addr + pfs->p_pos, r_len);

        offset += r_len;
        pfs->p_pos += r_len;

        pfs->frame_offset += r_len;
        if (pfs->frame_offset >= pfs->frame_len) {
            pfs->frame_offset = 0;
        }

        if (pfs->p_pos >= pfs->p_len) {
            phone_stream_free();
        }
    } while (offset < len);

    return offset;
}

static int bt_phone_file_write(void *priv, void *buf, u32 len)
{
    if (!pfs->lmp_open) {
        return 0;
    }
    lmp_private_send_esco_packet(NULL, buf, len);
    return len;
}

static int bt_phone_file_seek(void *priv, u32 offset, int orig)
{
    return 0;
}

static int bt_phone_file_len(void *priv)
{
    return -1;
}

static const struct audio_vfs_ops bt_phone_audio_dec_vfs_ops = {
    .fread = bt_phone_file_read,
    .fwrite = bt_phone_file_write,
    .fseek = bt_phone_file_seek,
    .flen  = bt_phone_file_len,
};


static void phone_call_dec_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    /* case AUDIO_SERVER_EVENT_ERR: */
    case AUDIO_SERVER_EVENT_END:
        phone_call_end();
        break;
    default:
        break;
    }
}

static void *phone_decode_start(int format, u8 volume)
{
    union audio_req req = {0};

    pfs->audio_dec = server_open("audio_server", "dec");
    if (!pfs->audio_dec) {
        return NULL;
    }

    server_register_event_handler(pfs->audio_dec, NULL, phone_call_dec_event_handler);

    pfs->format = format;
    pfs->frame_offset = 0;

    if (format == BT_AUDIO_FORMAT_MSBC) {
        req.dec.dec_type = "msbc";
        req.dec.sample_rate = 16000;
        pfs->frame_len = MSBC_FRAME_LEN;
        pfs->buffer = zalloc(MSBC_FRAME_LEN);
        ASSERT(pfs->buffer, "pfs buffer malloc fail");
    } else if (format == BT_AUDIO_FORMAT_CVSD) {
        req.dec.dec_type = "cvsd";
        req.dec.sample_rate = 8000;
    }

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = volume;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = 1024 * 4;
    req.dec.channel         = 2;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &bt_phone_audio_dec_vfs_ops;
    req.dec.sample_source   = "dac";

    server_request(pfs->audio_dec, AUDIO_REQ_DEC, &req);

    req.dec.cmd = AUDIO_DEC_START;
    //req.dec.attr = AUDIO_ATTR_NO_WAIT_READY;
    server_request(pfs->audio_dec, AUDIO_REQ_DEC, &req);

    return pfs->audio_dec;
}

static void phone_decode_close(void)
{
    union audio_req req = {0};

    if (!pfs->audio_dec) {
        return;
    }

    req.dec.cmd = AUDIO_DEC_STOP;
    server_request(pfs->audio_dec, AUDIO_REQ_DEC, &req);

    server_close(pfs->audio_dec);

    phone_stream_free();

    pfs->audio_dec = NULL;
    pfs->offset = 0;
    free(pfs->buffer);
    pfs->buffer = NULL;
}

static int phone_speak_start(int format, int packet_len)
{
    int err = 0;
    union audio_req req = {0};

    pfs->audio_enc = server_open("audio_server", "enc");
    if (!pfs->audio_enc) {
        return -1;
    }

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
    req.enc.volume = 100;
    req.enc.output_buf = NULL;
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &bt_phone_audio_dec_vfs_ops;
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
    req.enc.channel_bit_map = BIT(TCFG_PHONE_CALL_ADC_CHANNEL);
#endif

    if (format == BT_AUDIO_FORMAT_MSBC) {
        req.enc.format = "msbc";
        req.enc.sample_rate = 16000;
        req.enc.output_buf_len = 512;
    } else if (format == BT_AUDIO_FORMAT_CVSD) {
        req.enc.format = "cvsd";
        req.enc.sample_rate = 8000;
        req.enc.frame_size = packet_len * 2;
        req.enc.output_buf_len = packet_len * 2 * 10;
    }

#if defined CONFIG_AEC_ENC_ENABLE

#define AEC_EN              BIT(0)
#define NLP_EN              BIT(1)
#define ANS_EN              BIT(2)

    /*aec module enable bit define*/
#define AEC_MODE_ADVANCE	(AEC_EN | NLP_EN | ANS_EN)
#define AEC_MODE_REDUCE		(NLP_EN | ANS_EN)
#define AEC_MODE_SIMPLEX	(ANS_EN)

    struct aec_s_attr aec_param = {0};
    aec_param.EnableBit = AEC_MODE_ADVANCE;
    /* aec_param.agc_en = 1; */
    req.enc.aec_attr = &aec_param;
    req.enc.aec_enable = 1;

    extern void get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);

#if 0
    aec_param.ANS_NoiseLevel =	2.2e3f;	//初始噪声水平,用来加速降噪收敛,跟 mic 信号的信噪比有关。 Mic 信号信噪比高， 该值可以小一点， 反之则需要稍微大一点。default: 2.2e3f(0 ~ 32767)
#endif

    if (aec_param.EnableBit == 0) {
        req.enc.aec_enable = 0;
        req.enc.aec_attr = NULL;
    }
    if (aec_param.EnableBit != AEC_MODE_ADVANCE) {
        aec_param.output_way = 0;
    }

#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN && defined TCFG_AEC_ADC_CHANNEL
    if (req.enc.aec_enable) {
        aec_param.output_way = 1;	 //1:使用硬件回采 0:使用软件回采
        req.enc.rec_linein_channel_bit_map = BIT(TCFG_AEC_ADC_CHANNEL); //设置linein的回采通道
        req.enc.channel_bit_map |= BIT(TCFG_AEC_ADC_CHANNEL);	 //配置回采硬件通道
        if (TCFG_AEC_ADC_CHANNEL < TCFG_PHONE_CALL_ADC_CHANNEL) {
            req.enc.ch_data_exchange = 1;	 //如果回采通道使用的硬件channel比MIC通道使用的硬件channel靠前的话处理数据时需要交换一下顺序
        }
    }
#endif

    if (req.enc.sample_rate == 16000) {
        aec_param.wideband = 1;
        aec_param.hw_delay_offset = 50;
    } else {
        aec_param.wideband = 0;
        aec_param.hw_delay_offset = 75;
    }

#if CONFIG_AEC_SIMPLEX_ENABLE
#define AEC_SIMPLEX_TAIL 15 /*单工连续清0的帧数*/
    /*远端数据大于CONST_AEC_SIMPLEX_THR,即清零近端数据越小，回音限制得越好，同时也就越容易卡*/
#define AEC_SIMPLEX_THR		100000	/*default:260000*/

    aec_param.wn_en = 1;
    aec_param.simplex = 1;
    aec_param.dly_est = 1;
    aec_param.wn_gain = 331;
    aec_param.dst_delay = 50;
    aec_param.EnableBit = AEC_MODE_SIMPLEX;
    aec_param.SimplexTail = req.enc.sample_rate == 8000 ? AEC_SIMPLEX_TAIL / 2 : AEC_SIMPLEX_TAIL;
    aec_param.SimplexThr = AEC_SIMPLEX_THR;
#endif/*TCFG_AEC_SIMPLEX*/

#endif

    err = server_request(pfs->audio_enc, AUDIO_REQ_ENC, &req);

#if defined CONFIG_AEC_ENC_ENABLE
    if (aec_param.output_way) {
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
        extern void adc_multiplex_set_gain(const char *source, u8 channel_bit_map, u8 gain);
        adc_multiplex_set_gain("linein", BIT(TCFG_AEC_ADC_CHANNEL), TCFG_AEC_ADC_GAIN);
#endif
    }
#endif

    return err;
}

static int phone_speak_close(void)
{
    union audio_req req = {0};

    if (pfs->audio_enc) {
        req.enc.cmd = AUDIO_ENC_STOP;
        server_request(pfs->audio_enc, AUDIO_REQ_ENC, &req);
        server_close(pfs->audio_enc);
        pfs->audio_enc = NULL;
    }

    return 0;
}

void *phone_call_begin(int call_format, u8 volume)
{
    int err = 0;
    int esco_len = call_format >> 16;
    int codec_type = call_format & 0x000000ff;

    if (codec_type == 3) {
        log_info(">>sco_format:msbc");
        codec_type = BT_AUDIO_FORMAT_MSBC;
    } else if (codec_type == 2) {
        log_info(">>sco_format:cvsd");
        codec_type = BT_AUDIO_FORMAT_CVSD;
    } else {
        log_info("sco_format:error->please check %d", codec_type);
        return NULL;
    }

    pfs->lmp_open = 1;

    err = phone_speak_start(codec_type, esco_len);
    if (err) {
        goto __err;
    }

    return phone_decode_start(codec_type, volume);

__err:
    phone_call_end();
    return NULL;
}

void phone_call_end(void)
{
    pfs->lmp_open = 0;
    phone_speak_close();
    phone_decode_close();
}

#endif


#ifdef BT_EMITTER_ENABLE

#define BT_EMITTER_CBUF_SIZE	(512 * 6)

typedef struct sbc_param_str {
    unsigned int flags;

    u8 frequency;
    u8 blocks;
    u8 subbands;
    u8 mode;
    u8 allocation;
    u8 bitpool;
    u8 endian;
    void *priv;
    void *priv_alloc_base;
} sbc_t;

struct bt_emitter_vfs_handle {
    u8 open;
    u8 gain;
    u8 suspend;
    u16 frame_size;
    void *audio_enc;
    cbuffer_t cbuf;
    void *buf;
};

static struct bt_emitter_vfs_handle bt_emitter_vfs_handle = {.gain = 100};
#define efs      (&bt_emitter_vfs_handle)

static int bt_emitter_vfs_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;

    efs->frame_size = len;

    if (cbuf_write(cbuf, data, len) != len) {
        log_info("bt emitter cbuf write full");
        cbuf_clear(cbuf);
    } else if (efs->suspend) {
        efs->suspend = 0;
        extern void stack_run_loop_resume();
        stack_run_loop_resume();
    }

    return len;
}

static const struct audio_vfs_ops bt_emitter_vfs_ops = {
    .fwrite = bt_emitter_vfs_fwrite,
};

int a2dp_sbc_encoder_init(void *sbc_struct)
{
    int ret = 0;
    union audio_req req = {0};
    sbc_t *sbc = (sbc_t *)sbc_struct;

    if (sbc) {
        log_info("audio emitter server open");

        efs->buf = malloc(BT_EMITTER_CBUF_SIZE);
        if (!efs->buf) {
            return -1;
        }

        efs->audio_enc = server_open("audio_server", "enc");
        if (!efs->audio_enc) {
            free(efs->buf);
            efs->buf = NULL;
            return -1;
        }

        cbuf_init(&efs->cbuf, efs->buf, BT_EMITTER_CBUF_SIZE);

        req.enc.cmd = AUDIO_ENC_OPEN;
        req.enc.channel = sbc->mode > 0 ? 2 : 1;
        req.enc.volume = efs->gain;
        req.enc.frame_size = (sbc->subbands ? 8 : 4) * (4 + (sbc->blocks * 4)) * req.enc.channel * 2;
        req.enc.output_buf_len = 4 * req.enc.frame_size;
        req.enc.format = "sbc";
        req.enc.sample_source = "mic";
        req.enc.vfs_ops = &bt_emitter_vfs_ops;
        req.enc.file = (FILE *)&efs->cbuf;
        req.enc.bitrate = ((3 - sbc->blocks) << 28) & sbc->bitpool;
        if (sbc->endian) {
            req.enc.bitrate |= BIT(31);
        }
        if (!sbc->subbands) {
            req.enc.bitrate |= BIT(30);
        }
        if (sbc->frequency == SBC_FREQ_48000) {
            req.enc.sample_rate = 48000;
        } else if (sbc->frequency == SBC_FREQ_44100) {
            req.enc.sample_rate = 44100;
        } else if (sbc->frequency == SBC_FREQ_32000) {
            req.enc.sample_rate = 32000;
        } else {
            req.enc.sample_rate = 16000;
        }
#if TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN
        if (req.enc.channel == 2) {
            req.enc.channel_bit_map = BIT(TCFG_MIC_ADC_CHANNEL_L) | BIT(TCFG_MIC_ADC_CHANNEL_R);
        } else {
            req.enc.channel_bit_map = BIT(TCFG_MIC_ADC_CHANNEL_L);
        }
#endif

        ret = server_request(efs->audio_enc, AUDIO_REQ_ENC, &req);
        if (!ret) {
            efs->open = 1;
        }

        return ret;
    } else {
        log_info("audio emitter server close");

        efs->open = 0;

        if (efs->audio_enc) {
            req.enc.cmd = AUDIO_ENC_CLOSE;
            server_request(efs->audio_enc, AUDIO_REQ_ENC, &req);
            server_close(efs->audio_enc);
            efs->audio_enc = NULL;
        }
        if (efs->buf) {
            cbuf_clear(&efs->cbuf);
            free(efs->buf);
            efs->buf = NULL;
        }

        efs->frame_size = 0;
        efs->suspend = 0;

        return 0;
    }
}

int a2dp_sbc_encoder_get_data(u8 *packet, u16 buf_len, int *frame_size)
{
    int number = 0;
    u32 data_size = 0;

    while (efs->open) {
        data_size = cbuf_get_data_size(&efs->cbuf);
        if (!data_size) {
            efs->suspend = 1;
            return 0;
        }
        if (buf_len < data_size) {
            data_size = buf_len;
        }
        number = data_size / efs->frame_size;  /*取整数包*/
        *frame_size = efs->frame_size;
        data_size = cbuf_read(&efs->cbuf, packet, *frame_size * number);
        if (data_size > 0) {
            return data_size;
        }
    }

    return 0;
}

u8 bt_emitter_stu_get(void)
{
    return efs->open;
}

int bt_emitter_enc_gain_set(int step)
{
    if (efs->audio_enc) {
        union audio_req req = {0};

        int gain = efs->gain + step;
        if (gain < 0) {
            gain = 0;
        } else if (gain > 100) {
            gain = 100;
        }
        if (gain == efs->gain) {
            return -1;
        }
        efs->gain = gain;

        log_info("set_enc_gain: %d", gain);

        req.enc.cmd     = AUDIO_ENC_SET_VOLUME;
        req.enc.volume  = gain;
        return server_request(efs->audio_enc, AUDIO_REQ_ENC, &req);
    }

    return -1;
}

void *get_bt_emitter_audio_server(void)
{
    return efs->audio_enc;
}

#endif

#endif

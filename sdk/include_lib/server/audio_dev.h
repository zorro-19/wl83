#ifndef AUDIO_DEV_H
#define AUDIO_DEV_H

#include "generic/list.h"
#include "typedef.h"
#include "device/device.h"
#include "generic/circular_buf.h"
#include "os/os_api.h"
#include "generic/ioctl.h"

#define AUDIOC_QUERYCAP         _IOR('A', 0, struct audio_capability)
#define AUDIOC_GET_FMT          _IOR('A', 1, struct audio_format)
#define AUDIOC_SET_FMT          _IOW('A', 1, struct audio_format)
#define AUDIOC_REQBUFS          _IOW('A', 2, struct video_reqbufs)
#define AUDIOC_DQBUF            _IOR('A', 3, struct video_buffer)
#define AUDIOC_QBUF             _IOW('A', 4, struct video_buffer)
#define AUDIOC_STREAM_ON        _IOW('A', 5, u32)
#define AUDIOC_STREAM_OFF       _IOW('A', 6, u32)
#define AUDIOC_FADE_INOUT_SET   _IOW('A', 7, u8)
#define AUDIOC_GET_HEAD_INFO    _IOR('A', 8, u32 (*)[2])
#define AUDIOC_SET_VOLUME       _IOW('A', 9, u32)
#define AUDIOC_SET_REFRESH_VAD  _IO('A', 10)
#define AUDIOC_FLUSH            _IO('A', 11)
#define AUDIOC_REGISTER_IRQ_HANDLER  _IOW('A', 12, struct audio_irq_handler)


#define AUD_SUBDEV_REQ_PUT_PCM_DATA      0
#define AUD_SUBDEV_REQ_GET_PCM_DATA      1
#define AUD_SUBDEV_VIRTUAL_END_POST_SEM  2


#define AUDIO_TYPE_DEC                  0x01
#define AUDIO_TYPE_ENC                  0x02
#define AUDIO_TYPE_ENC_MIC              (BIT(2) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_LINEIN           (BIT(3) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_PLNK0            (BIT(4) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_PLNK1            (BIT(5) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_IIS0             (BIT(6) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_IIS1             (BIT(7) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_SPDIF            (BIT(8) | AUDIO_TYPE_ENC)
#define AUDIO_TYPE_ENC_SHARE            BIT(31)

struct audio_irq_handler {
    void (*irq_handler)(void *, void *, int);
    void *priv;
};

struct audio_req_data {
    u8 channel;
    u8 wait_en;
    u8 source;
    u8 *data;
    int len;
    int sample_rate;
    u8 *ch0_data;
    u8 *ch1_data;
};

struct audio_endpoint;

struct aec_s_attr;

struct audio_platform_data {
    u8 type;
    void *private_data;
};

struct audio_capability {
    u32 capabilities;
};


#define AUDIO_FMT_PCM          0x01
#define AUDIO_FMT_SPEEX        0x02
#define AUDIO_FMT_AMR          0x03
#define AUDIO_FMT_AAC          0x04
#define AUDIO_FMT_OPUS         0x05
#define AUDIO_FMT_CVSD         0x06
#define AUDIO_FMT_MSBC         0x07
#define AUDIO_FMT_ADPCM        0x08
#define AUDIO_FMT_SBC          0x09
#define AUDIO_FMT_MP2          0x0a
#define AUDIO_FMT_MP3          0x0b
#define AUDIO_FMT_JLA          0x0c
#define AUDIO_FMT_OGG          0x0d

#define AUDIO_FMT_DNS          0xfd
#define AUDIO_FMT_AEC          0xfe
#define AUDIO_FMT_VAD          0xff

struct audio_format {
    u8 index;
    u8 volume;
    u8 channel;
    u8 channel_bit_map;
    u8 rec_linein_channel_bit_map;
    u8 priority;
    volatile u8 vad_status;
    u8 use_vad : 2;
    u8 vad_auto_refresh : 1;
    u8 direct2dac : 1;
    u8 high_gain : 1;
    u8 amr_src : 1;
    u8 vir_data_wait : 1;
    u8 ch_detached : 1;

    u8 aec_enable : 1;
    u8 ch_data_exchange : 1;
    u8 no_header : 1;
    u8 sample_depth : 3;
    u8 dns_enable : 1;
    u8 wait_sem : 1;

    u8 read_end;

    u16 vad_start_threshold;
    u16 vad_stop_threshold;
    u16 frame_len;
    u16 frame_head_reserve_len;
    int sample_rate;
    u32 bitrate;
    u32 delay_ms;
    const char *format;
    const char *sample_source;
    int(*read_input)(u8 *buf, u32 len);
    struct aec_s_attr *aec_attr;
    OS_SEM *sem;
};

struct audio_subdevice_ops {
    int (*init)(struct audio_platform_data *);

    int (*querycap)(struct audio_capability *cap);

    int (*get_format)(struct audio_format *);
    int (*set_format)(struct audio_format *);

    struct audio_endpoint *(*open)(struct audio_format *);

    int (*streamon)(struct audio_endpoint *);

    int (*streamoff)(struct audio_endpoint *);

    int (*response)(struct audio_endpoint *, int cmd, void *);

    int (*write)(struct audio_endpoint *, void *buf, u32 len);

    int (*close)(struct audio_endpoint *);

    int (*ioctl)(struct audio_endpoint *, u32 cmd, u32 arg);
};

struct audio_subdevice {
    u8 id;
    /*u8 inused;*/
    u8 type;
    u32 format;
    /*struct audio_subdevice *next;*/
    /*void *parent;*/
    /*void *private_data;*/
    const struct audio_subdevice_ops *ops;
};

struct audio_endpoint {
    struct list_head entry;
    const struct audio_subdevice *dev;
    volatile int inused;
    void *parent;
    void *private_data;
    struct list_head parent_list;
};

struct aec_s_attr {
    u8 agc_en : 1;
    u8 ul_eq_en : 1;
    u8 wideband : 1;
    u8 toggle : 1;
    u8 wn_en : 1;
    u8 dly_est : 1;
    u8 output_way : 1;    // 0:dac  1:fm
    u8 simplex : 1;

    u8 dst_delay;/*延时估计目标延时*/
    u8 EnableBit;
    u8 SimplexTail;

    int SimplexThr;
    u16 hw_delay_offset;            /*dac hardware delay offset*/
    u16 wn_gain;                    /*white_noise gain*/
    u16 dac_ref_sr;                 //dac参考采样率,要是编码时AEC采样率(8k或16k)的整数倍

    float AGC_NDT_fade_in_step; 	//in dB
    float AGC_NDT_fade_out_step; 	//in dB
    float AGC_NDT_max_gain;     	//in dB
    float AGC_NDT_min_gain;     	//in dB
    float AGC_NDT_speech_thr;   	//in dB
    float AGC_DT_fade_in_step;  	//in dB
    float AGC_DT_fade_out_step; 	//in dB
    float AGC_DT_max_gain;      	//in dB
    float AGC_DT_min_gain;      	//in dB
    float AGC_DT_speech_thr;    	//in dB
    float AGC_echo_present_thr; 	//In dB
    int AGC_echo_look_ahead;    	//in ms
    int AGC_echo_hold;          	//in ms
    float ES_AggressFactor;
    float ES_MinSuppress;
    float ES_Unconverge_OverDrive;
    float ANS_AggressFactor;
    float ANS_MinSuppress;
    float ANS_NoiseLevel;
    int (*aec_probe)(s16 *dat, u16 len);
    int (*aec_post)(s16 *dat, u16 len);
    int (*output_handle)(u8 *dat, u16 len);

    float AEC_RefEngThr;
    float AEC_DT_AggressiveFactor;
    //float AES_AggressFactor;
    //float AES_RefEngThr;
    float DNS_gain_floor;	//增益的最小值控制,范围0~1,建议值(0~0.2)之间, default:双麦 0.05f ,单麦 0.1f
    float DNS_over_drive;	//控制降噪强度: 0 < over_drive < 1，越小降噪强度越轻，太小噪声会很大；over_drive = 1,正常降噪; over_drive > 1,降噪强度加强，越大降噪强度越强，太大会吃音. 建议调节范围0.3~3之间来控制降噪强度的强弱, default: 1.0f
    float DNS_loudness;
};

void dac_digital_lr_add(s16 *buff, u32 len);

void dac_digital_lr_sub(s16 *buff, u32 len);

int audio_channel_buf_data_separate(s16 *output, s16 *input, u8 channel_bit_map, u8 channel, u32 output_len);

int audio_channel_cbuf_data_separate(cbuffer_t *cbuf, s16 *input, u8 channel_bit_map, u8 channel, u32 output_len);

int audio_channel_cbuf_data_merge(cbuffer_t *cbuf, s16 *ch0_data, s16 *ch1_data, u32 output_len);

int audio_channel_buf_data_merge(s16 *output, s16 *ch0_data, s16 *ch1_data, u32 output_len);

int audio_subdevice_request(struct audio_endpoint *ep, int req, void *arg);

void *audio_buf_malloc(struct audio_endpoint *ep, u32 size);

void *audio_buf_realloc(struct audio_endpoint *ep, void *buf, int size);

void audio_buf_stream_finish(struct audio_endpoint *ep, void *buf);

void audio_buf_free(struct audio_endpoint *ep, void *buf);

void audio_buf_set_time(struct audio_endpoint *ep, void *buf, u32 msec);

int audio_encoder_thread_create(void (*func)(void *), void *priv, int *pid, const char *name);

extern const struct audio_subdevice audio_subdev_begin[];
extern const struct audio_subdevice audio_subdev_end[];

//cppcheck-suppress preprocessorErrorDirective
#define REGISTER_AUDIO_SUBDEVICE(dev, _id) \
	const struct audio_subdevice dev SEC_USED(.audio_subdev.##_id) = { \
		.id = _id, \

#define CHECK_AUDIO_ENDPOINT_IF_IS_STOPPED(ep) \
	do { \
		if (!ep->inused) { \
			return 0; \
		} \
	}while(0)

extern const struct device_operations audio_dev_ops;


typedef void (*audio_output_handler_t)(s16 *data, int len, int sample, u8 channel, const char *source);

#define REGISTER_AUDIO_OUTPUT_DATA_HANDLER(fn) \
	static const audio_output_handler_t __audio_output_##fn SEC_USED(.audio_output_handler) = fn

#define do_audio_output_data_handler(data, len, sample, channel, source) \
	do { \
		audio_output_handler_t *handler; \
		extern audio_output_handler_t audio_output_handler_begin[];\
        extern audio_output_handler_t audio_output_handler_end[]; \
		for (handler = audio_output_handler_begin; handler < audio_output_handler_end; \
                handler++) { \
			(*handler)(data, len, sample, channel, source);	\
		} \
	}while(0)


typedef void (*audio_input_handler_t)(s16 *data, int len, int sample, s16 **out_data, const char *source);

#define REGISTER_AUDIO_INPUT_DATA_HANDLER(fn) \
	static const audio_input_handler_t __audio_intput_##fn SEC_USED(.audio_input_handler) = fn

#define do_audio_input_data_handler(data, len, sample, out_data, source) \
	do { \
		audio_input_handler_t *handler; \
		extern audio_input_handler_t audio_input_handler_begin[];\
        extern audio_input_handler_t audio_input_handler_end[]; \
		for (handler = audio_input_handler_begin; handler < audio_input_handler_end; \
                handler++) { \
			(*handler)(data, len, sample, out_data, source);	\
		} \
	}while(0)


#endif

#ifndef _TUYA_IPC_MEDIA_H_
#define _TUYA_IPC_MEDIA_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "tuya_cloud_types.h"

typedef UINT_T CHANNEL_E;
#define     E_CHANNEL_VIDEO_MAIN    0
#define     E_CHANNEL_VIDEO_SUB     1
#define     E_CHANNEL_VIDEO_3RD     2
#define     E_CHANNEL_VIDEO_4TH     3
#define     E_CHANNEL_VIDEO_MAX     8    //max video streams

#define     E_CHANNEL_AUDIO         9
#define     E_CHANNEL_AUDIO_2RD     10
#define     E_CHANNEL_AUDIO_3RD     11
#define     E_CHANNEL_AUDIO_4TH     12
#define     E_CHANNEL_MAX           16


typedef UINT_T MEDIA_FRAME_TYPE_E;
#define     E_VIDEO_PB_FRAME        0
#define     E_VIDEO_I_FRAME         1
#define     E_VIDEO_TS_FRAME        2
#define     E_AUDIO_FRAME           3
#define     E_CMD_FRAME             4
#define     E_MEDIA_FRAME_TYPE_MAX  5

//enum for codec, sync with tuya cloud and APP, should NOT be changed
typedef UINT_T TUYA_CODEC_ID;

#define     TUYA_CODEC_VIDEO_MPEG4      0
#define     TUYA_CODEC_VIDEO_H263       1
#define     TUYA_CODEC_VIDEO_H264       2
#define     TUYA_CODEC_VIDEO_MJPEG      3
#define     TUYA_CODEC_VIDEO_H265       4
#define     TUYA_CODEC_VIDEO_YUV420     5
#define     TUYA_CODEC_VIDEO_YUV422     6
#define     TUYA_CODEC_VIDEO_MAX        99

#define     TUYA_CODEC_AUDIO_ADPCM      100
#define     TUYA_CODEC_AUDIO_PCM        101
#define     TUYA_CODEC_AUDIO_AAC_RAW    102
#define     TUYA_CODEC_AUDIO_AAC_ADTS   103
#define     TUYA_CODEC_AUDIO_AAC_LATM   104
#define     TUYA_CODEC_AUDIO_G711U      105
#define     TUYA_CODEC_AUDIO_G711A      106
#define     TUYA_CODEC_AUDIO_G726       107
#define     TUYA_CODEC_AUDIO_SPEEX      108
#define     TUYA_CODEC_AUDIO_MP3        109
#define     TUYA_CODEC_AUDIO_MAX        199

#define     TUYA_CODEC_INVALID          200

typedef UINT_T TUYA_AUDIO_SAMPLE_E;
#define     TUYA_AUDIO_SAMPLE_8K        8000
#define     TUYA_AUDIO_SAMPLE_11K       11000
#define     TUYA_AUDIO_SAMPLE_12K       12000
#define     TUYA_AUDIO_SAMPLE_16K       16000
#define     TUYA_AUDIO_SAMPLE_22K       22000
#define     TUYA_AUDIO_SAMPLE_24K       24000
#define     TUYA_AUDIO_SAMPLE_32K       32000
#define     TUYA_AUDIO_SAMPLE_44K       44000
#define     TUYA_AUDIO_SAMPLE_48K       48000
#define     TUYA_AUDIO_SAMPLE_MAX       0xFFFFFFFF

typedef UINT_T TUYA_VIDEO_BITRATE_E;
#define     TUYA_VIDEO_BITRATE_64K      64
#define     TUYA_VIDEO_BITRATE_128K     128
#define     TUYA_VIDEO_BITRATE_256K     256
#define     TUYA_VIDEO_BITRATE_512K     512
#define     TUYA_VIDEO_BITRATE_768K     768
#define     TUYA_VIDEO_BITRATE_1M       1024
#define     TUYA_VIDEO_BITRATE_1_5M     1536
#define     TUYA_VIDEO_BITRATE_2M       2048   //maximum 2Mbps stream is supported, as consideration of cloud storage order price

typedef UINT_T TUYA_AUDIO_DATABITS_E;
#define     TUYA_AUDIO_DATABITS_8       8
#define     TUYA_AUDIO_DATABITS_16      16
#define     TUYA_AUDIO_DATABITS_MAX     0xFF

typedef UINT_T TUYA_AUDIO_CHANNEL_E;
#define     TUYA_AUDIO_CHANNEL_MONO     0
#define     TUYA_AUDIO_CHANNEL_STERO    1

typedef struct {
    BOOL_T channel_enable[E_CHANNEL_MAX];

    UINT_T video_fps[E_CHANNEL_VIDEO_MAX];
    UINT_T video_gop[E_CHANNEL_VIDEO_MAX];
    TUYA_VIDEO_BITRATE_E video_bitrate[E_CHANNEL_VIDEO_MAX];
    UINT_T video_width[E_CHANNEL_VIDEO_MAX];
    UINT_T video_height[E_CHANNEL_VIDEO_MAX];
    UINT_T video_freq[E_CHANNEL_VIDEO_MAX];
    TUYA_CODEC_ID video_codec[E_CHANNEL_VIDEO_MAX];

    TUYA_CODEC_ID audio_codec[E_CHANNEL_MAX];
    UINT_T audio_fps[E_CHANNEL_MAX];
    TUYA_AUDIO_SAMPLE_E audio_sample[E_CHANNEL_MAX];
    TUYA_AUDIO_DATABITS_E audio_databits[E_CHANNEL_MAX];
    TUYA_AUDIO_CHANNEL_E audio_channel[E_CHANNEL_MAX];
} IPC_MEDIA_INFO_S;


typedef struct {
    UINT_T    type;
    UINT_T    size;
    UINT64_T  timestamp;
    UINT64_T  pts;
} STORAGE_FRAME_HEAD_S;

typedef struct {
    MEDIA_FRAME_TYPE_E type;
    BYTE_T    *p_buf;
    UINT_T    size;
    UINT64_T  pts;
    UINT64_T  timestamp;
} MEDIA_FRAME_S;

#ifdef __cplusplus
}
#endif

#endif /*_TUYA_IPC_MEDIA_H_*/

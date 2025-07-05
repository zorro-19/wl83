#ifndef _TUYA_PACKAGER_H_
#define _TUYA_PACKAGER_H_
#include "tuya_cloud_types.h"
#include "tuya_ipc_media.h"

#define SESSION_ID_LEN 32
#define MAX_STREAM_NUM 4


typedef UINT_T CMD_ID_E;
#define     E_CMD_REQUEST       0
#define     E_CMD_RESPONSE      1
#define     E_CMD_ACK           2
#define     E_CMD_COMPLETE      3
#define     E_CMD_DISCONNECT    4
#define     E_CMD_SET_CONFIG    5
#define     E_CMD_AUDIO_CTRL    6
#define     E_CMD_MAX           7
#define     E_CMD_STREAM_END    0x01000010

typedef UINT_T STREAM_TYPE_E;
#define     E_STREAM_AUDIO          1
#define     E_STREAM_VIDEO_MAIN     2
#define     E_STREAM_VIDEO_AUDIO    3
#define     E_STREAM_VIDEO_SUB      4
#define     E_STREAM_VIDEO_3RD      8
#define     E_STREAM_MAX            0xFF

#define STREAMING_FRAG_E UCHAR_T
#define STREAMING_FRAG_DISABLE 0
#define STREAMING_FRAG_START 1
#define STREAMING_FRAG_INSIDE 2
#define STREAMING_FRAG_END 3

typedef struct {
    STREAM_TYPE_E streamType;
    UINT_T  seqNum;     //帧序列号
    TUYA_AUDIO_DATABITS_E  data_bit; //位宽
    TUYA_AUDIO_SAMPLE_E    sample;   //采样率
    TUYA_CODEC_ID          codec;    //编码格式
    TUYA_AUDIO_CHANNEL_E   channel_num; //声道数
    UINT64_T timestamp;             //精确到毫秒的时间戳，UTC时间绝对值
    UINT64_T pts;                   //编码时间戳，相对时间
} __attribute__((packed))AUDIO_FRAME_S;

typedef struct {
    STREAM_TYPE_E streamType;
    UINT_T  seqNum;     //帧序列号
    MEDIA_FRAME_TYPE_E  type;       //视频帧类型 I/P/B
    TUYA_CODEC_ID       codec;      //编码格式
    UINT_T  width;      //分辨率宽
    UINT_T  height;     //分辨率高
    UINT_T  fps;        //当前帧的帧率
    UINT64_T timestamp;             //精确到毫秒的时间戳，UTC时间绝对值
    UINT64_T pts;                   //编码时间戳，相对时间
} __attribute__((packed))VIDEO_FRAME_S;

typedef struct {
    UINT_T  type;       //图片类型  JPEG/PNG/...
} __attribute__((packed))PIC_FRAME_S;

typedef struct {
    CMD_ID_E  cmdID;     //控制帧ID
    BYTE_T  sessionID[SESSION_ID_LEN]; //mqtt下发的sessionid，用于服务端确认密钥
} __attribute__((packed))CMD_FRAME_S;

typedef struct {
    UINT_T version;                 //版本，1开始
    STREAMING_FRAG_E fragStatus;     //分片标志
    UCHAR_T fragNo;
    USHORT_T type;        //数据帧类型
    UINT_T  size;                   //除了总帧头之外的大小
    BYTE_T iv[16];                  //16字节随机向量
} __attribute__((packed))STREAMING_FRAME_S;

typedef enum {
    E_PACK_RAW = 0,
    E_PACK_RTP,
    E_PACK_TLS,
    E_PACK_INVALID
} PACK_TYPE_E;

typedef struct {
    BOOL_T inited;
    PACK_TYPE_E sourceType;
    PACK_TYPE_E targetType;
    BOOL_T encryptNeeded;

    OPERATE_RET(*Pack)(IN STREAMING_FRAME_S *frameHead, IN BYTE_T *data, IN UINT_T size, OUT CHAR_T **packedData, OUT UINT_T *packedSize);
} PACKAGER_S;

PACKAGER_S *GetPackagerInstance(PACK_TYPE_E sourceType, PACK_TYPE_E targetType);

int tuya_ipc_packager_init();

#endif

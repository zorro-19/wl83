#ifndef _TUYA_STREAMER_H_
#define _TUYA_STREAMER_H_

#include "tuya_cloud_types.h"
#include "uni_thread.h"
#include "tuya_ipc_media.h"
#include "tuya_ipc_packager.h"
#include "tuya_ipc_encrypt.h"
#include "uni_md5.h"

#define MAX_URL_LEN         256
#define AUTH_STRING_LEN     64

#define USERNAME_LEN 32
#define PASSWORD_LEN 32

#define MOTO_ID_LEN 16
#define TOPIC_LEN 64

#define MD5_VALUE_LEN     (2*MD5_DECRYPT_LEN)

#define PUBLIC
#define PRIVATE

typedef enum {
    E_STREAMING_DISCONNECT = 0,
    E_STREAMING_START,
    E_STREAMING_STOP,
    E_STREAMING_AUTH_REQUEST,
    E_STREAMING_AUTH_ACK,
    E_STREAMING_AUTH_WAIT,
    E_STREAMING_ONGOING,
    E_STREAMING_END,
    E_STREAMING_MAX
} STREAMING_STATUS_E;

typedef enum {
    E_STREAMING_REQUEST_NULL = 0,
    E_STREAMING_REQUEST_START,
    E_STREAMING_REQUEST_STOP,
} E_STREAMING_REQUEST_TYPE_E;

typedef struct {
    USHORT_T type;
    UCHAR_T *data;
    UINT_T size;
    UINT64_T pts;
    UINT64_T timestamp;
    UINT_T seqNo;
    UCHAR_T fragStatus;                     //分片标志，0-不分片，1-分片开始，2-分片内容，3-分片结束
    UCHAR_T fragNo;                         //分片序号，从0开始
} FRAME_INFO_S;

typedef struct {
    TUYA_CODEC_ID audio_codec;
    TUYA_AUDIO_SAMPLE_E audio_sample;
    TUYA_AUDIO_DATABITS_E audio_databits;
    TUYA_AUDIO_CHANNEL_E audio_channel;
    BYTE_T *p_audio_buf;
    UINT_T buf_len;
    UINT64_T pts;
    UINT64_T timestamp;//in milliseconds
    VOID *p_reserved;
} TRANSFER_AUDIO_FRAME_S;


typedef enum {
    TRANS_LIVE_VIDEO_START = 0,
    TRANS_LIVE_VIDEO_STOP,
    TRANS_LIVE_AUDIO_START,
    TRANS_LIVE_AUDIO_STOP,
    TRANS_LIVE_VIDEO_CLARITY_SET,           /* set clarity from APP */
    TRANS_LIVE_VIDEO_CLARITY_QUERY,         /* query clarity informations*/
    TRANS_LIVE_LOAD_ADJUST,
    TRANS_PLAYBACK_LOAD_ADJUST,
    TRANS_PLAYBACK_QUERY_MONTH_SIMPLIFY,    /* query storage info of month  */
    TRANS_PLAYBACK_QUERY_DAY_TS,            /* query storage info of day */

    TRANS_PLAYBACK_START_TS,                /* start playback */
    TRANS_PLAYBACK_PAUSE,                   /* pause playback */
    TRANS_PLAYBACK_RESUME,                  /* resume playback */
    TRANS_PLAYBACK_MUTE,                    /* mute playback */
    TRANS_PLAYBACK_UNMUTE,                  /* unmute playback */
    TRANS_PLAYBACK_STOP,                    /* stop playback */
    TRANS_PLAYBACK_SET_SPEED,               /*set playback speed*/


    TRANS_SPEAKER_START,                    /* start APP-to-IPC speak */
    TRANS_SPEAKER_STOP,                     /* stop APP-to-IPC speak */
    TRANS_ABILITY_QUERY,                    /* query the alibity of audion video strraming */

    TRANS_DOWNLOAD_START,                   /* start to download */
    TRANS_DOWNLOAD_STOP,                    /* abondoned */
    TRANS_DOWNLOAD_PAUSE,
    TRANS_DOWNLOAD_RESUME,
    TRANS_DOWNLOAD_CANCLE,

    TRANS_STREAMING_VIDEO_START = 100,
    TRANS_STREAMING_VIDEO_STOP = 101,

    TRANS_DOWNLOAD_IMAGE = 201,             /* download image */
    TRANS_PLAYBACK_DELETE = 202,            /* delete video */
} TRANSFER_EVENT_E;

typedef INT_T(*GET_FRAME_CB)(IN INT_T get_latest_frame, IN STREAM_TYPE_E stream_type, IN INT_T retry, OUT FRAME_INFO_S *frame_info);
typedef INT_T(*TRANSFER_EVENT_CB)(IN CONST TRANSFER_EVENT_E event);
typedef VOID (*TRANSFER_REV_AUDIO_CB)(IN CONST TRANSFER_AUDIO_FRAME_S *p_audio_frame);
typedef VOID (*TRANSFER_DATA_FINISH_CB)(IN FRAME_INFO_S *frame_info, BOOL_T is_success);
typedef VOID (*TRANSFER_REV_CONFIG_CB)(INT_T streamType);
typedef BOOL_T(*STREAM_RECV_CB)(cJSON *jsonRoot);
typedef INT_T(*START_SERSOR_CB)(VOID);

typedef struct {
    CHAR_T userName[USERNAME_LEN];
    CHAR_T passWord[PASSWORD_LEN];
    CHAR_T sessionID[SESSION_ID_LEN];
    CHAR_T devRandom[AUTH_STRING_LEN];
    CHAR_T serverRandom[AUTH_STRING_LEN];
    CHAR_T signature[68];
    STREAM_TYPE_E  streamType;
    INT_T  fd;
} SESSION_INFO_S;

typedef struct {
    CHAR_T  address[MAX_URL_LEN];
    UINT_T  port;
} SERVER_INFO_S;

typedef struct {
    PRIVATE
    BOOL_T      inited;
    BOOL_T      paused;
    BOOL_T      supportAudio;
    UINT_T      interval_ms;
    THRD_HANDLE threadHandle;
    STREAMING_STATUS_E    status;
    CHAR_T      devId[GW_ID_LEN + 1];
    CHAR_T      localKey[LOCAL_KEY_LEN + 1];
    BYTE_T      cloudKeyMd5[MD5_VALUE_LEN + 1];

    CHAR_T      motoId[MOTO_ID_LEN];
    CHAR_T      bookTopic[TOPIC_LEN];
    CHAR_T      sendTopic[TOPIC_LEN];

    SERVER_INFO_S   serverInfo;
    SESSION_INFO_S  sessionInfo;

    CHAR_T      *pSendBuffer;
    CHAR_T      *pSendBufferInternal;
    INT_T       sendBufferLen;
    CHAR_T      *pReceiveBuffer;
    INT_T       recvBufferLen;

    ENCRYPTOR_S     *pEncryptor;
    PACKAGER_S      *pPackager;
//  MOTO_MQTT_T     *pMotoMqtt;
    TRANSFER_EVENT_CB        eventCb;
    TRANSFER_REV_AUDIO_CB    audioDataCb;
    GET_FRAME_CB    getFrameCb;
    TRANSFER_DATA_FINISH_CB    tranfer_finish_cb;
    E_STREAMING_REQUEST_TYPE_E requestPending;
    START_SERSOR_CB            start_sensor_cb;

    //宠物视频
    TRANSFER_REV_CONFIG_CB recv_conig_cb;
    STREAM_RECV_CB stream_recv_cb;

    PUBLIC
    OPERATE_RET(*SetMediaSetting)(IPC_MEDIA_INFO_S *media_setting);
    OPERATE_RET(*SupportAudio)(BOOL_T status);
    OPERATE_RET(*SetFrameInterval)(UINT_T interval_ms);
    OPERATE_RET(*FillSkills)(CHAR_T *skillInfo, INT_T len);
    OPERATE_RET(*SetServerAddr)(CHAR_T *address, UINT_T port);
    OPERATE_RET(*Start)(VOID);
    OPERATE_RET(*Stop)(VOID);
    OPERATE_RET(*Pause)(VOID);
    OPERATE_RET(*Resume)(VOID);
    OPERATE_RET(*RegisterCb)(TRANSFER_EVENT_CB eventCallback, TRANSFER_REV_AUDIO_CB audioCallback, GET_FRAME_CB getFrameCallback);
    OPERATE_RET(*RegisterFinishCb)(TRANSFER_DATA_FINISH_CB tranferFinishCb);
    OPERATE_RET(*SendMqttMsg)(BYTE_T *p_data);
} TSTREAMER_S;

TSTREAMER_S *GetTStreamerInstance(VOID);

INT_T tuya_ipc_streamer_init();
//must call before GetTStreamerInstance
INT_T tuya_ipc_streamer_set_max_frame_size(IN INT_T max_frame_size);
//must call before GetTStreamerInstance
OPERATE_RET tuya_ipc_streamer_set_memory_save_mode(VOID);

OPERATE_RET StopStreaming(VOID);
OPERATE_RET PushStreamingStatus(OUT INT_T *stream_flag);
OPERATE_RET http_device_update_skill(IN CONST CHAR_T *dev_id, IN CONST CHAR_T *skill);


#endif


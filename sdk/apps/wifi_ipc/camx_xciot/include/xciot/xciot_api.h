/*****************************************************************************
 * xciot_api.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef XCIOT_API_H_INCLUDE
#define XCIOT_API_H_INCLUDE
/*****************************************************************************
 * @addtogroup xciot_api
 * @{
 */
/*****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
//#include <stdbool.h>
#include <typedef.h> //bool

#include "xciot_type.h"
#include "xciot_cmd_common.h"
#include "xciot_cmd_ipc.h"
#include "xc_cs_type.h"

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/*****************************************************************************
 * Public Data
 ****************************************************************************/

/*****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * @brief 查询avsdk的版本号.
 *
 * @return  返回avsdk的版本号.
 */
char *avsdk_get_sdk_ver(void);

/**
 * @brief 设置SDK日志等级.
 *
 * @param[in]  level - 日志等级 see @ref iot_log_level_t.
 *
 * @return status code that indicates the execution status of the function.
 */
void avsdk_set_loglevel(iot_log_level_t level);

/**
 * @brief 注册SDK日志底层输出函数.
 *
 * @param[in]  domain     - 目前未使用该字段，填NULL.
 * @param[in]  log_output - 用户log输出函数.
 *
 * @return 无.
 */
typedef int (*log_output)(const char *fmt, ...);
void avsdk_log_lowPrintf(char *domain, log_output user_printf);


/**
 * @brief 上传日志到平台，web开启一次日志功能，2小时内有效，设备重启需要重新使能。
 *
 * @param[in]  level     - 日志等级: 1, debug; 2, info; 3, warn; 4, error; 5, crash.
 * @param[in]  payload   - 日志正文,长度需要控制在900以内，否则会被截断.
 *
 * @return 小于0，上传失败； 返回-6表示未在web后台，开启日志上传.
 */
int  avsdk_app_log_append(int32_t level, char *payload);

/**
 * @brief 上传日志文件到平台，仅支持linux系统！！！！！
 *        web开启一次日志功能，2小时内有效，设备重启需要重新使能。
 *
 * @param[in]  file_name   - 文件上传后显示的名字.
 * @param[in]  file_path   - 日志文件所在的路径.
 *
 * @return 小于0，上传失败； 返回-3传入的参数不完整,-6表示未在web后台，开启日志上传.
 */
int avsdk_log_put_file(char *file_name,
                       char *file_path);
/**
 * @brief SDK 初始化.
 *
 * @param[in]  init_params - 初始化参数. 其中版本号填“”，则需要调用avsdk_report_version主动上报版本号
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_init(avsdk_init_params_t *init_params);

/**
 * @brief SDK 反初始化清除.
 */
void avsdk_fini(void);

/**
 * @brief SDK 启动.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_start(void);

/**
 * @brief SDK 断开和平台的连接.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_stop(void);

/**
 * @brief SDK 休眠.
 *
 * @param[out] sleep - 休眠参数 @ref iot_sleep_t.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_sleep(iot_sleep_t *sleep);

/**
 * @brief 查询sdk是否处于休眠模式.
 *
 *
 * @return true,表示再休眠； false表示正常模式（非低功耗）.
 */
bool avsdk_ppmq_in_sleep(void);

/**
 * @brief 将sdk设置为正常的心跳，适用于单芯片的保活方案.
 *
 * @return true,表示再休眠； false表示正常模式（非低功耗）.
 */
void avsdk_ppmq_set_normal(void);

/**
 * @brief 查询连接平台是否成功.
 *
 * @return true 连接平台成功， false失败.
 */
bool avsdk_poll_conn_platfrom(void);

/**
 * @brief SDK 休眠参数序列化.
 *
 * @param[in]  sleep  - 休眠参数,通过avsdk_sleep获取.
 *
 * @param[out] outArr - 序列化后的数据，建议512B的大小数组.
 *
 * @param[out] arrlen - 序列化后的长度.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_tools_sleep2byte(iot_sleep_t *sleep,
                           uint8_t     *outArr,
                           uint16_t    *arrlen);

/**
 * @brief SDK 快速初始化.
 *
 * @param[in] faststart_data    - 快速初始化参数内容.
 *
 * @param[in] faststart_datalen - 快速初始化参数内容长度.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_faststart(const uint8_t *faststart_data, size_t faststart_datalen);

/**
 * @brief SDK 周期性循环.
 */
void avsdk_loop(void);

/**
 * @brief 解除设备的绑定关系.
 */
int avsdk_unbind(void);

/**
 * @brief 获取天气
 *
 * @param[out] p   - 返回天气信息。
 *
 * @return 返回值小于0错误.
 */
int avsdk_get_weather(iot_weatherInfo_t *p);

/**
 * @brief SDK 外部接管ppmq_handle
 *
 * @param[in] hdl   - 为avsdk_set_on_ppmq_handle返回的值。
 *
 * @return 返回值小于0，不再调用avsdk_ppmq_handle；
 *         大于0为多少秒后再次调用avsdk_ppmq_handle.
 */
int avsdk_ppmq_handle(void *hdl);

/**
 * @brief 返回当前用户连接数.
 *
 * @return 返回当前连接数
 */
int avsdk_poll_current_conn_num(void);

/**
 * @brief SDK errno 转化为字符串.
 */
const char *avsdk_strerror(int errnum);


/**
 * @brief 如果有运行数据需要更新，将触发该回调（目前只有ipc和屏绑定的数据）
 *
 * @param[in] cb   - 为avsdk_set_on_ppmq_handle返回的值。
 *
 * @return 0成功
 */
void avsdk_set_on_backup(iot_on_backup_t cb);

/**
 * @brief 导入保存的运行备份数据，须在avsdk_init之后，avsdk_start之前调用
 *
 * @param[in] data   - 导入avsdk_set_on_backup保存的数据
 * @param[in] len    - 数据长度
 *
 * @return 0 成功；
 */
int avsdk_import_backup(uint8_t *data, uint32_t len);

/**
 * @brief 获取设备关联绑定设备的信息（与屏绑定的ipc、门锁）
 *
 *
 * @return 成功，返回关联设备的信息，失败NULL；
 * eg:
 *   {
 *       bind_dev_t *bind = avsdk_bind_list();
 *       T_I("bind count=%d", bind->count);
 *       for(int i=0; i<bind->count; i++) {
 *           discovery_info_t *info = &bind->info[i].base;
 *           T_I("[%d],did=%s,ip=%s,utcms=%llu", i, info->did, info->ipaddr, info->utcms);
 *           T_IH_HEX("skill", bind->info[i].skill.bytes, bind->info[i].skill.size);
 *       }
 *   }
 */
bind_dev_t *avsdk_bind_list(void);


/**
 * @brief 往连接写入流媒体数据.
 *
 * @param[in] conn_id         - 连接ID.
 *
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 *
 * @param[in] iskeyframe      - 是不是关键帧(i frame set true or false).
 *
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码. .
 *
 * @param[in] enctype         - 加密类型 @ref iot_encrypt_type_t.
 *
 * @param[in] timestamp       - ms级时间戳.
 *
 * @param[in] enclength       - 加密长度，默认 0.
 *
 * @param[in] mediadata       - 媒体数据.
 *
 * @param[in] mediadatalength - 媒体数据长度.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_write_media_v1(int32_t                conn_id,
                         iot_mediastream_type_t streamtype,
                         bool                   iskeyframe,
                         uint64_t               avchannel,
                         iot_encrypt_type_t     enctype,
                         uint64_t               timestamp,
                         uint64_t               enclength,
                         const uint8_t         *mediadata,
                         size_t                 mediadatalength);

/**
 * @brief 往连接写入流媒体数据V2.
 *
 * @param[in] conn_id         - 连接ID.
 *
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 *
 * @param[in] iskeyframe      - 是不是关键帧(i frame set true or false).
 *
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 *
 * @param[in] enctype         - 加密类型 @ref iot_encrypt_type_t.
 *
 * @param[in] timestamp       - ms级时间戳.
 *
 * @param[in] enclength       - 加密长度默认填0
 *
 * @param[in] source		  - 媒体数据来源 @ref iot_mediasource_type_t.
 *
 * @param[in] file_id		  - 文件id.
 *
 * @param[in] exdata		  - Default NULL.
 *
 * @param[in] exdatalength    - Default 0.
 *
 * @param[in] mediadata       - 媒体数据.
 *
 * @param[in] mediadatalength - 媒体数据长度.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_write_media_v2(int32_t                conn_id,
                         iot_mediastream_type_t streamtype,
                         bool                   iskeyframe,
                         uint64_t               avchannel,
                         iot_encrypt_type_t     enctype,
                         uint64_t               timestamp,
                         uint64_t               enclength,
                         iot_mediasource_type_t source,
                         uint64_t               file_id,
                         const uint8_t         *exdata,
                         uint64_t               exdatalength,
                         const uint8_t         *mediadata,
                         size_t                 mediadatalength);

/**
 * @brief 往连接写入文件数据.
 *
 * @param[in] conn_id        - 连接ID.
 *
 * @param[in] fileid         - 文件id.
 *
 * @param[in] offset         - 文件传输偏移.
 *
 * @param[in] enctype        - 加密类型 @ref iot_encrypt_type_t,,默认E_IOT_ENCRYPT_TYPE_AES256CBC.
 *
 * @param[in] enclength      - 加密长度默认填0
 *
 * @param[in] data           - 文件数据.
 *
 * @param[in] datalength     - 数据长度.
 *
 * @return 0成功，-8表示发送队列满了，需要调用者重发，否则文件不完整.
 */
int avsdk_write_file(int32_t            conn_id,
                     uint64_t           fileid,
                     uint64_t           offset,
                     iot_encrypt_type_t enctype,
                     uint64_t           enclength,
                     const uint8_t     *data,
                     size_t             datalength);
/**
 * @brief 向连接发送自定义命令.
 *
 * @param[in] conn_id        - 连接ID.
 *
 * @param[in] req            - 命令请求.
 *
 * @param[in] rsp            - 命令回应.
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_custom_cmd(int32_t             conn_id,
                     ipc_CustomCmd_Req *req,
                     ipc_CustomCmd_Resp *rsp);

/**
 * 推荐使用 avsdk_firmware_rate_v2
 *
 * @brief 向连接发送固件升级进度（不能在回调中直接调用，需要异步调用）.
 *
 * @param[in] conn_id         - 连接ID.
 *
 * @param[in] channel         - 通道编号，如果是IPC，该值为0.
 *
 * @param[in] rate            - 升级进度: 0-100. -1表示失败
 *
 * @return status code that indicates the execution status of the function.
 */
int avsdk_firmware_rate(int32_t conn_id, int32_t channel, int32_t rate);

/**
 * @brief 向所有连接和平台发送固件升级进度（不能在回调中直接调用，需要异步调用）.
 *
 * @param[in] channel         - 通道编号，如果是IPC，该值为0.
 *
 * @param[in] rate            - 升级进度: 0-100. -1表示失败
 *
 * @return 无.
 */
void avsdk_firmware_rate_v2(int32_t channel, int32_t rate);

/**
 * @brief 向连接发送存储格式化进度（不能在回调中直接调用，需要异步调用）.
 *
 * @param[in] conn_id         - 连接ID.
 *
 * @param[in] channel         - 通道编号，如果是IPC，该值为0.
 *
 * @param[in] rate            - 格式化进度: 0-100; -1 格式化失败.
 *
 * @return status code that indicates the execution status of the function.
 */

int avsdk_storage_format_rate(int32_t conn_id, int32_t channel, int32_t rate);

/**
 * @brief 防撬上报，当防撬状态变化时，触发.
 *
 * @param[in] status - 设备当前防撬状态.
 */
int avsdk_report_tamper_status(iot_tamper_status_t status);

/**
 * @brief 平台第一次连接通知,可以用于状态上报等；注意：该回调只会调用一次.
 *
 * @param[in] cb - 平台连接通知回调函数.
 */
void avsdk_set_on_connect_platform(iot_on_connect_platform_t cb);

/**
 * @brief 平台重新连接通知回调注册,可以用于联网状态灯维护等，平台后续连接状态变化都会触发该回调.
 *
 * @param[in] cb - 平台连接通知回调函数.
 */
void avsdk_set_on_reconnect_platform(iot_on_connect_platform_t cb);

/**
 * @brief 通知用户设备被云端唤醒，sdk内部会自动退出休眠模式，
 *        适用于wifi作为主控的情况，调用avsdk_sleep且way填0，才会触发该回调.
 *
 * @param[in] cb - 连接平台utc回调函数.
 */
void avsdk_set_on_wakeup(iot_on_wakeup_t cb);

/**
 * @brief 通知用户ppmq_handle入参的值.
 *
 * @param[in] cb - 连接平台utc回调函数.
 */
void avsdk_set_on_ppmq_handle(iot_on_ppmq_handle_t cb);

/**
 * @brief 平台连接UTC回调注册.
 *
 * @param[in] cb - 连接平台utc回调函数.
 */
void avsdk_set_on_platform_utc(iot_on_platform_utc_t cb);

/**
 * @brief 用户连接通知回调注册.
 *
 * @param[in] on_connect - 用户连接通知回调函数.
 */
void avsdk_set_on_connect(iot_on_connect_t on_connect);

/**
 * @brief 流媒体数据数据回调注册.
 *
 * @param[in] on_media - 用户流媒体数据回调函数.
 */
void avsdk_set_on_media(iot_on_media_t on_media);

/**
 * @brief 文件数据回调注册.
 *
 * @param[in] on_RecvFile - 用户文件数据回调函数.
 */
void avsdk_set_on_RecvFile(iot_on_RecvFile_t on_RecvFile);

/**
 * @brief 音视频丢包回调注册.
 *
 * @param[in] cb - 回调函数.
 */
void avsdk_set_on_PacketDropout(iot_on_PacketDropout_t cb);

/**
 * @brief 添加到视频播放组.
 *
 * @param[in] conn_id         - 连接id.
 *
 * @param[in] ch              - 添加哪一个通道.
 *
 * @return 无.
 */
void avsdk_video_add_conn(int conn_id, int ch);

/**
 * @brief 从视频播放组删除.
 *
 * @param[in] conn_id         - 连接id.
 *
 * @param[in] ch              - 删除哪一个通道，-1表示全部删除.
 *
 * @return 无.
 */
void avsdk_video_del_conn(int conn_id, int ch);
/**
 * @brief 添加到音频播放组.
 *
 * @param[in] conn_id         - 连接id.
 *
 * @return 无.
 */
void avsdk_audio_add_conn(int conn_id);

/**
 * @brief 从音频播放组删除.
 *
 * @param[in] conn_id         - 连接id.
 *
 * @return 无.
 */
void avsdk_audio_del_conn(int conn_id);

/**
 * @brief 添加到自定义命名用户组.
 *
 * @param[in] conn_id         - 连接id.
 *
 * @return 无.
 */
void avsdk_custom_add_conn(int conn_id);

/**
 * @brief 从自定义命名用户组删除.
 *
 * @param[in] conn_id         - 连接id.
 *
 * @return 无.
 */
void avsdk_custom_del_conn(int conn_id);

/**
 * @brief AI描述信息序列化，填充到流数据exdata段
 *
 * @param[in] ai	    - 对象描述信息 @ref ai_desc_t.
 * @param[out] len		- 序列化后，数据大小
 *
 * @return 成功返回序列化后的数据，失败返回NULL；返回非NULL需要Free内存.
 */
uint8_t *avsdk_ai_desc_encode(ai_desc_t *ai, uint32_t *len);

/**
 * @brief 发送音频媒体数据，连接内部管理（推荐使用）.
 *
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码. .
 * @param[in] timestamp       - ms级时间戳.
 * @param[in] ai    		  - 对数据流的描述具体参考ai_desc_t定义，没有填NULL.
 * @param[in] payload_ptr     - 媒体数据.
 * @param[in] payload_len	  - 媒体数据长度.
 *
 * @return 无.
 */
void avsdk_write_audio(iot_mediastream_type_t stream_type,
                       uint64_t               avchannel,
                       uint64_t               timestamp_ms,
                       ai_desc_t             *ai,
                       const uint8_t         *payload_ptr,
                       uint32_t               payload_len);

/**
 * @brief 发送音频媒体数据，连接内部管理.
 *
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码. .
 * @param[in] enctype         - 加密类型 @ref iot_encrypt_type_t,默认E_IOT_ENCRYPT_TYPE_AES256CBC.
 * @param[in] timestamp       - ms级时间戳.
 * @param[in] enclength       - 加密长度，默认 0.
 * @param[in] exdata		  - 额外数据，对数据流的描述，没有填NULL.
 * @param[in] exdatalength	  - 额外数据长度,没有填0.
 * @param[in] payload_ptr     - 媒体数据.
 * @param[in] payload_len	  - 媒体数据长度.
 *
 * @return 无.
 */

void avsdk_write_audio_data(iot_mediastream_type_t stream_type,
                            uint64_t               avchannel,
                            iot_encrypt_type_t     encrypt_type,
                            uint64_t               timestamp_ms,
                            uint64_t               encrypt_length,
                            const uint8_t         *exdata,
                            uint64_t               exdatalength,
                            const uint8_t         *payload_ptr,
                            uint32_t               payload_len);

/**
 * @brief 发送视频媒体数据.（推荐使用）
 *
 * @param[in] streamtype		- 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] iskeyframe		- 是不是关键帧(i frame set true or false).
 * @param[in] avchannel			- 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] timestamp			- ms级时间戳.
 * @param[in] ai    		  	- 对数据流的描述具体参考ai_desc_t定义，没有填NULL.
 * @param[in] payload_ptr 		- 媒体数据.
 * @param[in] payload_len 		- 媒体数据长度.
 *
 * @return 无.
 */
void avsdk_write_video(iot_mediastream_type_t stream_type,
                       bool                   is_key_frame,
                       uint64_t               avchannel,
                       uint64_t               timestamp_ms,
                       ai_desc_t             *ai,
                       const uint8_t         *payload_ptr,
                       uint32_t               payload_len);

/**
 * @brief 发送视频媒体数据.
 *
 * @param[in] streamtype		- 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] iskeyframe		- 是不是关键帧(i frame set true or false).
 * @param[in] avchannel			- 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] enctype			- 加密类型 @ref iot_encrypt_type_t,默认E_IOT_ENCRYPT_TYPE_AES256CBC.
 * @param[in] timestamp			- ms级时间戳.
 * @param[in] enclength			- 加密长度，默认 0.
 * @param[in] exdata		  	- 额外数据，对数据流的描述，没有填NULL.
 * @param[in] exdatalength	  	- 额外数据长度,没有填0.
 * @param[in] payload_ptr 		- 媒体数据.
 * @param[in] payload_len 		- 媒体数据长度.
 *
 * @return 无.
 */
void avsdk_write_video_data(iot_mediastream_type_t stream_type,
                            bool                   is_key_frame,
                            uint64_t               avchannel,
                            iot_encrypt_type_t     encrypt_type,
                            uint64_t               timestamp_ms,
                            uint64_t               encrypt_length,
                            const uint8_t         *exdata,
                            uint64_t               exdatalength,
                            const uint8_t         *payload_ptr,
                            uint32_t               payload_len);


/**
 * @brief 发送视频媒体数据，使用切片的方式，适合内存很小(512k)的设备.
 *
 * @param[in] streamtype		- 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] iskeyframe		- 是不是关键帧(i frame set true or false).
 * @param[in] avchannel			- 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] timestamp			- ms级时间戳.
 * @param[in] slice_seq		  	- 分⽚序号: 0, 不分⽚; 1-250, 分配序号; 255, 表⽰分⽚结束
 * @param[in] ai    		    - 对数据流的描述具体参考ai_desc_t定义，没有填NULL.
 * @param[in] payload_ptr 		- 媒体数据.
 * @param[in] payload_len 		- 媒体数据长度.
 * @param[in] timeoutms 		- 发送最长超时时间，一般300-700ms.
 *
 * @return 无.
 */
int avsdk_write_video_slice(iot_mediastream_type_t stream_type,
                            bool                   is_key_frame,
                            uint64_t               avchannel,
                            uint64_t               timestamp_ms,
                            uint8_t                slice_seq,
                            ai_desc_t             *ai,
                            const uint8_t         *payload_ptr,
                            uint32_t               payload_len,
                            int                    timeoutms);

/**
 * @brief 发送历史视频媒体数据，使用切片的方式，适合内存很小(512k)的设备.
 *
 * @param[in] conn_id           - 连接ID.
 * @param[in] streamtype		- 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] iskeyframe		- 是不是关键帧(i frame set true or false).
 * @param[in] avchannel			- 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] timestamp_ms  	- ms级时间戳.
 * @param[in] file_id		    - 文件id.
 * @param[in] slice_seq		  	- 分⽚序号: 0, 不分⽚; 1-250, 分配序号; 255, 表⽰分⽚结束
 * @param[in] ai    		    - 对数据流的描述具体参考ai_desc_t定义，没有填NULL.
 * @param[in] payload_ptr 		- 媒体数据.
 * @param[in] payload_len 		- 媒体数据长度.
 * @param[in] timeoutms 		- 发送最长超时时间，一般300-700ms.
 *
 * @return 无.
 */
int avsdk_write_history_video_slice(int32_t                conn_id,
                                    iot_mediastream_type_t stream_type,
                                    bool                   is_key_frame,
                                    uint64_t               avchannel,
                                    uint64_t               timestamp_ms,
                                    uint64_t               file_id,
                                    uint8_t                slice_seq,
                                    ai_desc_t             *ai,
                                    const uint8_t         *payload_ptr,
                                    uint32_t               payload_len,
                                    int                    timeoutms);

/**
 * @brief 往连接写入历史音频数据.（推荐使用）
 *
 * @param[in] conn_id         - 连接ID.
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] timestamp       - ms级时间戳.
 * @param[in] file_id		  - 文件id.
 * @param[in] ai    		  - 对数据流的描述具体参考ai_desc_t定义，没有填NULL.
 * @param[in] payload_ptr     - 媒体数据.
 * @param[in] payload_len 	  - 媒体数据长度.
 *
 * @return 0成功，-9 conn_id已断开，需要退出sd发送，其他返回值可以暂时不处理.
 */
int avsdk_write_history_audio(int32_t                conn_id,
                              iot_mediastream_type_t stream_type,
                              uint64_t               avchannel,
                              uint64_t               timestamp_ms,
                              uint64_t               file_id,
                              ai_desc_t             *ai,
                              const uint8_t         *payload_ptr,
                              uint32_t               payload_len);

/**
 * @brief 往连接写入历史音频数据.
 *
 * @param[in] conn_id         - 连接ID.
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] enctype         - 加密类型 @ref iot_encrypt_type_t,默认E_IOT_ENCRYPT_TYPE_AES256CBC.
 * @param[in] timestamp_ms    - ms级时间戳.
 * @param[in] enclength       - 加密长度默认填0
 * @param[in] file_id		  - 文件id.
 * @param[in] exdata		  - 额外数据，对数据流的描述，没有填NULL.
 * @param[in] exdatalength	  - 额外数据长度,没有填0.
 * @param[in] payload_ptr     - 媒体数据.
 * @param[in] payload_len 	  - 媒体数据长度.
 *
 * @return 0成功，-9 conn_id已断开，需要退出sd发送，其他返回值可以暂时不处理.
 */
int avsdk_write_history_audio_data(int32_t                conn_id,
                                   iot_mediastream_type_t stream_type,
                                   uint64_t               avchannel,
                                   iot_encrypt_type_t     encrypt_type,
                                   uint64_t               timestamp_ms,
                                   uint64_t               encrypt_length,
                                   uint64_t               file_id,
                                   const uint8_t         *exdata,
                                   uint64_t               exdatalength,
                                   const uint8_t         *payload_ptr,
                                   uint32_t               payload_len);

/**
 * @brief 往连接写入历史视频数据.（推荐使用）
 *
 * @param[in] conn_id         - 连接ID.
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] iskeyframe      - 是不是关键帧(i frame set true or false).
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] timestamp       - ms级时间戳.
 * @param[in] file_id		  - 文件id.
 * @param[in] ai    		  - 对数据流的描述具体参考ai_desc_t定义，没有填NULL.
 * @param[in] payload_ptr     - 媒体数据.
 * @param[in] payload_len 	  - 媒体数据长度.
 *
 * @return 0成功，-9 conn_id已断开，需要退出sd发送，其他返回值可以暂时不处理.
 */
int avsdk_write_history_video(int32_t                conn_id,
                              iot_mediastream_type_t stream_type,
                              bool                   is_key_frame,
                              uint64_t               avchannel,
                              uint64_t               timestamp_ms,
                              uint64_t               file_id,
                              ai_desc_t             *ai,
                              const uint8_t         *payload_ptr,
                              uint32_t               payload_len);

/**
 * @brief 往连接写入历史视频数据.
 *
 * @param[in] conn_id         - 连接ID.
 * @param[in] streamtype      - 音视频数据类型 @ref iot_mediastream_type_t.
 * @param[in] iskeyframe      - 是不是关键帧(i frame set true or false).
 * @param[in] avchannel       - 0, 表示设备本身；单通道都为0；如果是多通道，第1路从1开始编码.
 * @param[in] enctype         - 加密类型 @ref iot_encrypt_type_t,默认E_IOT_ENCRYPT_TYPE_AES256CBC.
 * @param[in] timestamp       - ms级时间戳.
 * @param[in] enclength       - 加密长度默认填0
 * @param[in] file_id		  - 文件id.
 * @param[in] exdata		  - 额外数据，对数据流的描述，没有填NULL.
 * @param[in] exdatalength	  - 额外数据长度,没有填0.
 * @param[in] payload_ptr     - 媒体数据.
 * @param[in] payload_len 	  - 媒体数据长度.
 *
 * @return 0成功，-9 conn_id已断开，需要退出sd发送，其他返回值可以暂时不处理.
 */
int avsdk_write_history_video_data(int32_t                conn_id,
                                   iot_mediastream_type_t stream_type,
                                   bool                   is_key_frame,
                                   uint64_t               avchannel,
                                   iot_encrypt_type_t     encrypt_type,
                                   uint64_t               timestamp_ms,
                                   uint64_t               encrypt_length,
                                   uint64_t               file_id,
                                   const uint8_t         *exdata,
                                   uint64_t               exdatalength,
                                   const uint8_t         *payload_ptr,
                                   uint32_t               payload_len);
/**
 * @brief 用户自定义命令.
 *
 * @param[in] ipc_CustomCmd_Req           - 用户自定义请求.
 *
 * @param[out] ipc_CustomCmd_Resp         - 用户自定义返回.
 *
 * @return 0成功，负数失败.
 */
int avsdk_custom_cmd_send(ipc_CustomCmd_Req *req, ipc_CustomCmd_Resp *rsp);

/**
 * @brief 文件接收进度上报.
 *
 * @param[in] req          - 进度上报请求.
 *
 * @param[out] rsp         - 进度上报回应.
 *
 * @return 0成功.
 */
int avsdk_report_FileRecvRate(int32_t                conn_id,
                              ipc_FileRecvRate_Req *req,
                              ipc_FileRecvRate_Resp *rsp);

/**
 * @brief 打印PpiotCmd所有的参数.
 *
 * @param[in] perfix    - 打印前缀.
 *
 * @param[in] p         - 需要打印的结构体的指针.
 *
 * @return 0成功.
 */
void avsdk_dump_PpiotCmd(char *perfix, iot_PpiotCmd_t *p);

/**
 * @brief 异常事件上报(66).
 *
 * @param[in] event  - 异常事件.
 *
 * @return 返回值：为负数表示错误; 等于0事件上报成功，但是设备没开通云存; 大于0表示上报成功且设备开通了云存.
 */
int64_t avsdk_push_event(iot_event_opt_t *event);


/**
 * @brief 设备状态上报(67).
 *
 * @param[in] status_id         - 设备状态id@iot_status_id_t.
 *
 * @param[in] timestamp         - 发生时间的时间戳ms.
 *
 * @param[in] peopleID         - 人脸识别id,没有该功能填NULL.
 *
 * @return 0正确.
 */
int avsdk_status_pulish(int64_t         status_id,
                        uint64_t        timestamp,
                        ipc_PeopleID_t *peopleID);

/**
 * @brief 获取绑定设备的用户列表.
 *
 * @param[in] user_type   - 用户类型: 0，all; 1: owner; 2: share user; 3, home user; 4, admin user;.
 * @param[in] p           - 用户信息,其中用户个数不为0，即可认为设备被绑定.
 *
 * @return 0正确.
 */
int avsdk_get_user_list(int32_t user_type, user_list_t *p);

/**
 * @brief 查询云端发给设备的消息.
 *
 * @param[in] req   - 获取列表的请求参数；如需查询app给设备的留言消息event_id填E_IOT_EVENT_LEAVE_MESSAGE_APP
 * @param[in] rsp   - 获取到消息的列表.
 *
 * @return 0正确.
 */
int avsdk_alert_get_list(alert_list_req_t *req, alert_list_resp_t *rsp);

/**
 * @brief 将云端发送的消息设为已读.
 *
 * @param[in] p   - 需要设置事件的时间，由avsdk_alert_get_list中rsp取得。
 *
 * @return 0正确.
 */
int avsdk_alert_set_read(alert_arr_t *p);

/**
 * @brief 主动呼叫用户(app)；
 * @注意： 1.内部调用avsdk_push_event实现，如果要产生云存，不再调用avsdk_push_event.
 *        2.app接听或者拒绝将会通过avsdk_set_on_StateChangeByApp回调通知
 *
 * @param[in] uid   - 用户id,由avsdk_get_user_list获取；如果为NULL,表示普通推送，非NULL表示指定用户推送；
 *
 * @return 返回值：为负数表示错误; 等于0成功，但是设备没开通云存; 大于0表示成功且设备开通了云存.
 */
int64_t avsdk_call_user_start(char *uid);

/**
 * @brief 挂断呼叫用户；
 *
 * @param[in] uid   - 用户id;跟avsdk_call_user_start中填的uid保持一直；
 *
 * @return 返回值：为负数表示错误; 等于0成功.
 */
int64_t avsdk_call_user_end(char *uid);


/**
 * @brief 挂断app发起的视频通话；
 *
 * @param[in] conn_id   - 连接id，由回调avsdk_set_on_VideoCall入参取得；
 * @param[in] ch        - 通道id,0为ipc本身，；
 *
 * @return 返回值：为负数表示错误; 等于0成功.
 */
int avsdk_video_pause(int conn_id, int ch);


/**
 * @brief 上报基本信息(平台和连接都会发送) (70)
 *
 * @param[in]   p  - 设备基本信息（包括初始化传入的版本号）
 *
 * @return  0成功.
 */
int avsdk_push_info(dev_base_info_t *p);

/**
 * @brief 设备时区变更上报.
 *
 * @param[in] timeZone 		- 标准时区字符串.
 *
 * @return 0正确.
 */
int avsdk_report_TimeZone(char *timeZone);

/**
 * @brief 运营网络参数上报.
 *
 * @param[in] ICCID 		- ICCID.
 *
 * @param[in] IMEI 			- IMEI.
 *
 * @param[in] IMSI		   	- IMSI.
 *
 * @return 0正确.
 */
int avsdk_report_NetworkParams(char *ICCID, char *IMEI, char *IMSI);

/**
 * @brief 网络信号质量上报.
 *
 * @param[in] QOS 		- 网络质量: 1-6数字越大网络质量越好，
 *                        0 - 不支持，1 - 无信号
 *
 * @return 0正确.
 */
int avsdk_report_NetworkQuality(uint8_t QOS);

/**
 * @brief 电池电量上报(变化5%或者低电量触发).
 *
 * @param[in] quantity 		- 当前电量: 1-100，百分比，0表示没有电池。
 *
 * @param[in] status 		- 当前是否在充电，@iot_status_power_t。
 *
 * @param[in] voltage 		- 当前电压(mv); 0：不支持电压检测。
 *
 * @param[in] use_time 		- 可用时间(单位秒): 0:不支持。
 *
 * @return 0正确.
 */
int avsdk_report_Battary_v2(uint8_t            quantity,
                            iot_status_power_t status,
                            uint32_t           voltage,
                            uint32_t           use_time);

/**
 * @brief 电池电量上报(变化5%或者低电量触发).
 *
 * @param[in] quantity 		- 当前电量: 1-100，百分比，0表示没有电池。
 *
 * @param[in] status 		- 当前是否在充电，@iot_status_power_t。
 *
 * @return 0正确.
 */
int avsdk_report_Battary(uint8_t quantity, iot_status_power_t status);

/**
 * @brief 上报版本号，如果avsdk_init的时候rom_ver填NULL,
 *         那么sdk不会自动上报版本号，需要用户调用次接口主动上报版本号
 *
 * @param[in] rom_ver    - 设备的软件版本号，格式必须为“1.01.01.03_190618”，否则上报失败
 *
 * @param[in] hdw_ver    - 设备的硬件版本号
 *
 * @return 0正确.
 */
int avsdk_report_version(char *rom_ver, char *hdw_ver);

/**
 * @brief 上报子模块版本号
 *
 * @param[in] ch    	 - 通道，从1开始
 *
 * @param[in] rom_ver    - 子设备的软件版本号，格式必须为“1.01.01.03_190618”，否则上报失败
 *
 * @return 0正确.
 */
int avsdk_report_version_ch(int ch, char *rom_ver);

/**
 * @brief 设置配网获取到的国别信息
 *
 * @param[in] country_code    	 - 国别
 *
 * @return 0正确.
 */
int avsdk_update_country(char *country_code);

/**
 * @brief 二维码配网，二维码解析成字符串后，调用该函数解析wifi信息
 *
 * @param[in] data    	 - 二维码解析出来的字符串
 * @param[in] len        - 字符串长度
 * @param[out] wifi      - WiFi信息，其中vcode,需要连上平台调用avsdk_report_vcode上报
 *
 * @return 0正确.
 */
int avsdk_qr_netcfg_decode(uint8_t *data, size_t len, ipc_netcfg_t *wifi);

/**
 * @brief 上报获取的安全码,只需要配网的时候上报一次.(扫描配网)
 *
 * @param[in] vcode    - 获取到的安全码
 *
 * @return 0正确.
 */
int avsdk_report_vcode(char *vcode);

/**
 * @brief 上报扩展字段（设备特有配置）
 *
 * @param[in] data   - 数据
 *
 * @param[in] len    - 数据长度
 *
 * @return 0正确.
 */
int avsdk_report_ExtendConfig(uint8_t *data, uint16_t len);

/**
 * @brief 设备固件版本查询.
 *
 * @param[out] ipc_FirmwareCheckByDevice_Resp    -固件信息
 *
 * @return 0正确.
 */
int avsdk_firmware_poll(ipc_FirmwareCheckByDevice_Resp *rsp);

/**
 * @brief 子模块固件版本查询.
 *
 * @param[in ] ipc_FirmwareChanCheckByDevice_Req    -子组版本信息
 * @param[out] ipc_FirmwareCheckByDevice_Resp       -子组模块待升级的固件信息
 *
 * @return 0正确.
 */
int avsdk_firmware_poll_chan(ipc_FirmwareChanCheckByDevice_Req              *req,
                             ipc_FirmwareChanCheckByDevice_Resp *rsp);


/**
 * @brief uint32形式的ipaddr转字符串的ip地址.
 *
 * @param[in]  ipaddr    - uint32形式的ipaddr
 *
 * @param[out] ip        - 字符串形式的ip地址
 *
 * @return ip.
 */
char *avsdk_ntoa(uint32_t ipaddr, char *ip);

/**
 * @brief 字符串的ip地址转uint32形式的ipaddr.
 *
 * @param[in]  ip        - 字符串形式的ip地址
 *
 * @param[out] ipaddr    - uint32形式的ipaddr
 *
 * @return 0正确.
 */
int avsdk_aton(char *ip, uint8_t ipaddr[4]);

/**
 * @brief 获取白名单IP（4G热点）.
 *
 * @param[out] rsp    - IP白名单，ipv4使用avsdk_ntoa转换
 *
 * @return 0正确.
 */
int avsdk_ScpeGetWhitelist(ipc_ScpeGetWhitelist_Resp *rsp);

/**
 * @brief 设备发送GPS数据到iotdata微服务.
 *
 * @param[in]   longitude     - 经度: 经度每隔0.00001度，距离相差约1米（-90 到 +90）;经度 = 真实经度 * 100000 取整的值
 *
 * @param[in]   latitude      - 纬度: 纬度每隔0.00001度，距离相差约1.1米 （-180 到 +180）;纬度 = 真实纬度 * 100000 取整的值
 *
 * @param[in]   speed         - 速度(m/s);速度 = 真实速度 * 10 取整的值
 *
 * @param[in]   angle         - 方向范围0-360，整形，以正北为0度，顺时针增加;如果值为166600，表示不支持方向功能。(保留小数点后面2位，存放数据扩大100倍变为整数)
 *
 * @param[in]   acceleration  - 加速度: 0 不支持，或者没有急加/减速; 1 急加速; 2 急减速
 *
 * @param[in]   utcms         - UTC时间戳，单位ms
 *
 * @return 0正确.
 */
int avsdk_put_iotdata_gps(int64_t   longitude,
                          int64_t   latitude,
                          int64_t   speed,
                          int64_t   angle,
                          int64_t   acceleration,
                          uint64_t  utcms);

/**
 * @brief 设备发送批量GPS数据到iotdata微服务.
 *
 * @param[in]   data     - gps数据
 *
 * @return 0正确.
 */
int avsdk_put_iotdata_gps_v2(gps_t *data);

/**
 * @brief 设备发送数据到iotdata微服务.
 *
 * @param[in]   p                 - 数据
 *
 * @return 0正确.
 */
int avsdk_put_iotdata(iot_PpiotCmd_t *p);

/**
 * @brief 设备上报清扫记录.
 *
 * @param[in]   p - 数据
 *
 * @return 0正确.
 */
int avsdk_report_SSWPMapClean(iot_SSWPMapCleanReport_t *p);

/**
 * @brief 设备上报地图.
 *
 * @param[in]   p - 数据
 *
 * @return 0正确.
 */
int avsdk_report_MapAdd(iot_SSWPMapAddByDevice_t *p);

/**
 * @brief 设备发送数据到app.
 *
 * @param[in]   req                 - 发送的数据
 *
 * @param[in]   rsp                 - 应答的数据
 *
 * @return 0正确.
 */
int avsdk_push_ppiotcmd(int32_t             conn_id,
                        iot_PpiotCmd_t     *req,
                        iot_PpiotCmd_t     *rsp);

/**
 * @brief 设备发送数据到app(所有的连接都会发送一份).
 *
 * @param[in]   req                 - 发送的数据
 *
 * @return 0正确.
 */
int avsdk_push_ppiotcmd2(ipc_ExecIOTCMD_Req *req);

/**
 * @brief 设备发送大数据到app(所有的连接都会发送一份).
 *
 * @param[in]   req                 - 发送的数据
 *
 * @return 0正确.
 */
int avsdk_push_bigPpiotcmd(ipc_ExecBigIOTCMD_Req *req);
/**
 * @brief 查询当前设备云存支持的服务类型.
 *
 * @return 枚举服务类型 0,无服务 1.事件云存储; 2.人脸识别; 3.短信服务; 4. 事件图片(jpg); 200全天云存.
 */
cs_service_type_t avsdk_cs_get_service_type(void);

/**
 * @brief 查询当前设备云存支持的服务类型以及支持云存的事件id.
 *
 * @param[out]   type       - 0,无服务 1.事件云存储; 2.人脸识别; 3.短信服务; 4. 事件图片(jpg); 200全天云存.
 * @param[out]   event_arr  - 需要上报云存的事件列表，长度最大100Byte
 *
 * @return 0,成功
 */
int avsdk_cs_info(cs_service_type_t *type, char *event_arr);

/**
* @brief 设置云存能传输的最大图片.
*
* @param[in] maxsize     -设置最大能上传图片的大小，sdk内部默认512*1024,单位Byte
*
* @return 0正确; -1 maxsieze值大于1M.
*/
int avsdk_cs_set_picture_maxsize(uint32_t maxsize);

/**
 * @brief 云存图片(jpg)传输.
 *
 * @param[in] event_id		-异常事件id,@iot_event_id_t
 *
 * @param[in] channel		-通道，IPC为0
 *
 * @param[in] data          -需要上传的图片数据
 *
 * @param[in] data_len      -图片数据长度
 *
 * @param[in] peopleID      -人脸识别id,没有该功能填NULL.
 *
 * @param[in] xy            -识别到物体的坐标,没有该功能，应使用memset清零.
 *
 * @return 0正确.
 */
int avsdk_cs_picture_pulish(iot_event_id_t  event_id,
                            int64_t         channel,
                            uint8_t        *data,
                            uint32_t        data_len,
                            ipc_PeopleID_t *peopleID,
                            struct coord   *xy);

/**
 * @brief 云存图片(jpg)多张传输.
 *
 * @param[in] event_id		-异常事件id,@iot_event_id_t
 * @param[in] channel		-通道，IPC为0
 * @param[in] utcms 		-事件产生的时间，单位ms；填0，表示当前的时间
 * @param[in] picture       -需要上传的图片数据
 * @param[in] peopleID      -人脸识别id,没有该功能填NULL.
 *
 * @return 0正确.
 */
int avsdk_cs_picture_pulish_v2(iot_event_id_t  event_id,
                               int64_t         channel,
                               int64_t         utcms,
                               ipc_picture_t  *picture,
                               ipc_PeopleID_t *peopleID);

/**
 * @brief 云存图片(jpg)多张传输，支持补传(推荐使用).
 *
 * @param[in] event_id		-异常事件id,@iot_event_id_t
 * @param[in] channel		-通道，IPC为0
 * @param[in] utcms 		-事件产生的时间，单位ms；填0，表示当前的时间
 * @param[in] isretry 		-是否是补传（重传）的图片，
 * @param[in] picture       -需要上传的图片数据
 * @param[in] peopleID      -人脸识别id,没有该功能填NULL.
 *
 * @return 0正确.
 */
int avsdk_cs_push_picture(iot_event_id_t  event_id,
                          int64_t         channel,
                          int64_t         utcms,
                          bool            isretry,
                          ipc_picture_t  *picture,
                          ipc_PeopleID_t *peopleID);
/**
 * @brief 云存图片(小图片)传输，适合内存很小的设备.
 *
 * @param[in] event_id      -异常事件id,@iot_event_id_t
 *
 * @param[in] channel       -通道，IPC为0
 *
 * @param[in] obj_ext       -没有该功能填NULL，坐标的JSON数组;obj_id数组个数x4, 目标坐标 4个数字,左下为(0,0)开始计数; 左下(x,y),右上(x,y); x,y 为像素编号; 一张图多个目标则为多个坐标
 *
 * @param[in] data          -需要上传的图片数据
 *
 * @param[in] data_len      -图片数据长度
 *
 * @return 0正确.
 */
int avsdk_cs_picture_pulish_v3(iot_event_id_t  event_id,
                               int64_t         channel,
                               char           *obj_ext,
                               uint8_t        *data,
                               uint32_t        data_len);


/**
 * @brief 设置云存日志等级
 *
 * @param[in]   level        -#define LOG_LEVEL_NONE  1
 *                            #define LOG_LEVEL_ERROR 2
 *                            #define LOG_LEVEL_WARN  3
 *                            #define LOG_LEVEL_INFO  4
 *                            #define LOG_LEVEL_DEBUG 5
 *                            #define LOG_LEVEL_TRACE 6
 *
 *
 * @return  设置日志等级
 */
void avsdk_cs_set_log_level(int level);

/**
 * @brief  云存开始
 *
 * @param[out]  cs_hdl      - 操作句柄
 * @param[in]   opt         - 云存配置文件
 *
 * @return  成功返回0
 */
int avsdk_cs_start(cs_hdl_ref_t       *cs_hdl,
                   cs_start_opt_t     *opt);


#if 1 //云存v2接口

/**
 * @brief 设置存入的音视频格式v2
 *
 * @param[in]   encrypt        		- 文件加密方式,none或者e_cs_encrypt_aes_256_cbc
 *
 * @param[in]   video_format        - 视频格式
 *
 * @param[in]   fps                 - 帧率
 *
 * @param[in]   audio_format        - 音频格式
 *
 * @param[in]   sound_frequency     - 声音采样频率
 *
 * @param[in]   sound_depth         - 声音采样深度
 *
 * @param[in]   sound_channel       - 声音声道
 *
 * @param[in]   picture_num         - 0无图片，有几张图片调用几次avsdk_cs_append_thumbnail_v2
 *
 * @param[in]   picture_type        - 图片类型，参考e_cs_picture_type_t
 *
 * @return  返回0成功，返回-1表示已经设置过音视频格式
 */
int avsdk_cs_set_format_v2(cs_hdl_ref_t           cs_hdl,
                           e_cs_encrypt_type_t    encrypt,
                           e_cs_stream_type_t     video_format,
                           uint8_t                fps,
                           e_cs_stream_type_t     audio_format,
                           e_cs_sound_frequency_t sound_frequency,
                           e_cs_sound_depth_t     sound_depth,
                           e_cs_sound_channel_t   sound_channel,
                           uint8_t                picture_num,
                           e_cs_picture_type_t    picture_type);

/**
 * @brief 存入缩略图v2
 *
 * @param[in]   payload        - 缩略图的内容
 *
 * @param[in]   payload_len    - 内容的长度
 *
 * @param[in]   xy             - 图片中对象的坐标，没有填NULL
 *
 * @return  返回0成功，返回 -1表示没有写入音视频格式
 */
int avsdk_cs_append_thumbnail_v2(cs_hdl_ref_t  cs_hdl,
                                 uint8_t      *payload,
                                 uint32_t      payload_len,
                                 struct coord *xy);

/**
 * @brief 存入video数据v2
 *
 * @param[in]   ch                  - AV通道，ipc只支持一个通道填0；如果配置了多路视频通道，那么从1开始编号；例如：设备配置的两个视频通道，视频通道ch只能是1或者2;
 *
 * @param[in]   is_key_frame        - 关键帧填1，其他填0
 *
 * @param[in]   frame_features      - 帧特征@e_frame_features_t
 *
 * @param[in]   timestamp_ms        - 相对于第一个视频帧时间的间隔ms
 *
 * @param[in]   xy                 	- 物体的坐标，参考struct coord
 *
 * @param[in]   payload_ptr         - 视频内容
 *
 * @param[in]   payload_len                 - 视频内容长度
 *
 * @return  返回0成功，返回-1表示没有写入音视频格式，如果返回 -4 表示文件大小超过16M.
 */
int avsdk_cs_append_video_v2(cs_hdl_ref_t          cs_hdl,
                             uint8_t               ch,
                             char                  is_key_frame,
                             e_cs_frame_features_t frame_features,
                             uint32_t              timestamp_ms,
                             struct coord         *xy,
                             uint8_t              *payload_ptr,
                             uint32_t              payload_len);

/**
 * @brief 存入audio数据v2
 *
 * @param[in]   ch                  - AV通道，ipc只支持一个通道填0；如果配置了多路视频通道，那么从1开始编号
 *
 * @param[in]   frame_features      - 帧特征@e_cs_frame_features_t
 *
 * @param[in]   timestamp_ms        - 相对于第一个视频帧时间的间隔ms
 *
 * @param[in]   payload_ptr         - 视频内容
 *
 * @param[in]   payload_len         - 视频内容长度
 *
 * @return  返回0成功，返回-1表示没有写入音视频格式，如果返回 -4 表示文件大小超过16M.
 */
int avsdk_cs_append_audio_v2(cs_hdl_ref_t          cs_hdl,
                             uint8_t               ch,
                             e_cs_frame_features_t frame_features,
                             uint32_t              timestamp_ms,
                             uint8_t              *payload_ptr,
                             uint32_t              payload_len);
#endif

/**
 * @brief  获取云文件的大小（流）
 *
 * @return  成功返回0
 */
uint32_t avsdk_cs_get_file_size(cs_hdl_ref_t cs_hdl);

/**
 * @brief 云存结束.
 *
 * @param[in] peopleID         - 人脸识别id,没有该功能填NULL.
 *
 * @return 0正确.*/
int avsdk_cs_end(cs_hdl_ref_t *cs_hdl, ipc_PeopleID_t *peopleID);



#if 1 //v1版接口后期停止新功能开发，请优先使用v2接口
/**
 * @brief 设置存入的音视频格式（v1版接口，请优先使用v2接口）
 *
 * @param[in]   encrypt        		- 文件加密方式,none或者e_cs_encrypt_aes_256_cbc
 *
 * @param[in]   video_format        - 视频格式
 *
 * @param[in]   fps                 - 帧率
 *
 * @param[in]   audio_format        - 音频格式
 *
 * @param[in]   sound_frequency     - 声音采样频率
 *
 * @param[in]   sound_depth         - 声音采样深度
 *
 * @param[in]   sound_channel       - 声音声道
 *
 * @param[in]   is_have_thumbnail   - 0无图片，1缩略图，2图片
 *
 *
 * @return  返回0成功，返回-1表示已经设置过音视频格式
 */
int avsdk_cs_set_format(cs_hdl_ref_t           cs_hdl,
                        e_cs_encrypt_type_t    encrypt,
                        e_cs_stream_type_t     video_format,
                        uint8_t                fps,
                        e_cs_stream_type_t     audio_format,
                        e_cs_sound_frequency_t sound_frequency,
                        e_cs_sound_depth_t     sound_depth,
                        e_cs_sound_channel_t   sound_channel,
                        char                   is_have_thumbnail);

/**
 * @brief 存入缩略图(v1版接口，请优先使用v2接口)
 *
 * @param[in]   payload             - 缩略图的内容
 *
 * @param[in]   payload_len         - 内容的长度
 *
 * @param[in]   xy                  - 物体的坐标，参考struct coord
 *
 * @return  返回0成功，返回 -1表示没有写入音视频格式
 */
int avsdk_cs_append_thumbnail(cs_hdl_ref_t  cs_hdl,
                              uint8_t      *payload,
                              uint32_t      payload_len,
                              struct coord *xy);

/**
 * @brief 存入video数据（v1版接口，请优先使用v2接口）
 *
 * @param[in]   is_key_frame                - 关键帧填1，其他填0
 *
 * @param[in]   frame_features              - 帧特征@e_frame_features_t
 *
 * @param[in]   timestamp_ms                - 相对于第一个视频帧时间的间隔ms
 *
 * @param[in]   xy                 			- 物体的坐标，参考struct coord
 *
 * @param[in]   payload_ptr                 - 视频内容
 *
 * @param[in]   payload_len                 - 视频内容长度
 *
 * @return  返回0成功，返回-1表示没有写入音视频格式，如果返回 -4 表示文件大小超过16M;-9本次cs已退出或者未初始化.
 */
int avsdk_cs_append_video(cs_hdl_ref_t          cs_hdl,
                          char                  is_key_frame,
                          e_cs_frame_features_t frame_features,
                          uint32_t              timestamp_ms,
                          struct coord         *xy,
                          uint8_t              *payload_ptr,
                          uint32_t              payload_len);

/**
 * @brief 存入audio数据（v1版接口，请优先使用v2接口）
 *
 * @param[in]   frame_features              - 帧特征@e_cs_frame_features_t
 *
 * @param[in]   timestamp_ms                - 相对于第一个视频帧时间的间隔ms
 *
 * @param[in]   payload_ptr                 - 视频内容
 *
 * @param[in]   payload_len                 - 视频内容长度
 *
 * @return  返回0成功，返回-1表示没有写入音视频格式，如果返回 -4 表示文件大小超过16M;-9本次cs已退出或者未初始化.
 */
int avsdk_cs_append_audio(cs_hdl_ref_t          cs_hdl,
                          e_cs_frame_features_t frame_features,
                          uint32_t              timestamp_ms,
                          uint8_t              *payload_ptr,
                          uint32_t              payload_len);
#endif

/**
 * @brief  私有云存开始
 *
 * @param[out]  cs_hdl      - 操作句柄
 * @param[in]   opt         - 云存配置文件
 *
 * @return  成功返回0
 */
int avsdk_xcs_start(cs_start_opt_t     *opt,
                    cs_avfmt_t         *avfmt);

int avsdk_xcs_end(uint64_t startTime);

int avsdk_xcs_append_slice(iot_mediastream_type_t stream_type,
                           bool                   is_key_frame,
                           uint64_t               avchannel,
                           uint64_t               timestamp_ms,
                           uint8_t                slice_seq,
                           const uint8_t         *payload_ptr,
                           uint32_t               payload_len,
                           int                    timeoutms);
/**
 * @brief 指定云存上报的格式；格式无变化调用一次即可；
 * 一般用户不需要关注此接口.
 *
 * @param[in] format         - 0使用服务器下发的普通格式；101.需要易瞳校准SDK;5,热成像
 *
 * @return 无.*/
void avsdk_cs_extend_format(int format);

/**
 * @brief 尝试立马连接服务器,适用于配网后，加速连接平台.
 *
 * @return 无.
 */
void avsdk_try_connect_now(void);

/**
 * @brief 获取wifi热点的ssid和password,需要sdk初始化后调用.
 *
 * @param[out]   ssid                 - wifi热点ssid
 *
 * @param[out]   pass                 - wifi热点password
 *
 * @return 无.
 */
void avsdk_get_wifi_conf(char *ssid, char *pass);

/**
 * @brief 获取wifi热点的ssid和password，可随时调用.
 *
 * @param[in]    did                  - 配置文件中的did
 *
 * @param[out]   ssid                 - wifi热点ssid
 *
 * @param[out]   pass                 - wifi热点password
 *
 * @return 无.
 */

void avsdk_get_wifi_info(char *did, char *ssid, char *pass);

/**
 * @brief 设备发送iot命令到平台.
 *
 * @param[in]   topic             - 发送的topic，从文档获取
 *
 * @param[in]   p                 - iot命令
 *
 * @return 无.
 */
int avsdk_send_iotcmd(char *topic, iot_PpiotCmd_t *p);

/**
 * @brief 应答平台下发文档标注用217应答的命令
 *
 * @param[in]	sdid	    - 子设备id, 下发req中的带的sdid，不支持，填NULL
 * @param[in]	ch	        - 通道，不支持ch的命令,填0;
 * @param[in]	cid	        - 应答下发req的cid
 * @param[in]	rate	    - 0-100表示命令执行的进度；最总100成功， 101失败
 * @param[in]	error	    - 失败的原因，rate=101时有效；0不支持具体原因；不同设备的命令错误代码定义参见错误代码定义
 *
 * @return	返回0成功，否则失败.
 */
int avsdk_ack_cmd_217(int ch, int cid, int rate, int error, int64_t utcms);

/**
 * @brief 与平台断开时，重连平台模式，一般不需要调用.
 *
 * @param[in]   mode  - 平台重连运行模式，默认快速模式
 *
 * @return 无.
 */
void avsdk_set_platform_mode(iot_reconnect_mode_t mode);

/**
 * @brief 设置kcp窗口，一般不需要调用.
 *
 * @param[in]   snd_wnd             - 发送窗口
 *
 * @param[in]   rcv_wnd             - 接收窗口
 *
 * @return 无.
 */
void avsdk_set_wnd(int32_t snd_wnd, int32_t rcv_wnd);

/**
 * @brief 设置发送队列容量，一般不需要调用.
 *
 * @param[in]   cmd_cap             - 命令深度
 * @param[in]   file_cap            - 文件深度
 * @param[in]   audio_cap           - 音频深度
 * @param[in]   video_cap           - 视频深度
 *
 * @return 无.
 */
void avsdk_set_sendcap(uint16_t cmd_cap,
                       uint16_t file_cap,
                       uint16_t audio_cap,
                       uint16_t video_cap);
#if 1
int avsdk_export_apigw(iot_server_t *server);
char *avsdk_cfg_lslat(void);
char *avsdk_cfg_did(void);
char *avsdk_cfg_dkey(void);
void avsdk_get_signKey(char *deviceId, char *deviceKey, char *signKey);
void avsdk_get_localSignKey(char *deviceId, char *deviceKey, char *signKey);
#endif

#if 1 //for 蓝牙配网加解密
/*********************************************************************************************************************
蓝牙配网需要使用指定的128位UUID,入下：

#define DEV_BLE_SERVER_UUID     "865300b1-43e6-47b7-9cb0-5fc21d4ae340"
#define DEV_BLE_RX_UUID         "865300b3-43e6-47b7-9cb0-5fc21d4ae340" //read 从app收数据
#define DEV_BLE_TX_NTF_UUID     "865300b2-43e6-47b7-9cb0-5fc21d4ae340" //send ntf发数据给app
#define DEV_BLE_TX_IND_UUID     "865300b4-43e6-47b7-9cb0-5fc21d4ae340" //send ind发数据给app

#define BLE_SERVER_UUID       {0x40,0xE3,0x4A,0x1D,0xC2,0x5F,0xB0,0x9C,0xB7,0x47,0xE6,0x43,0xB1,0x00,0x53,0x86}
#define BLE_TX_NTF_UUID       {0x40,0xE3,0x4A,0x1D,0xC2,0x5F,0xB0,0x9C,0xB7,0x47,0xE6,0x43,0xB2,0x00,0x53,0x86}
#define BLE_RX_UUID           {0x40,0xE3,0x4A,0x1D,0xC2,0x5F,0xB0,0x9C,0xB7,0x47,0xE6,0x43,0xB3,0x00,0x53,0x86}
#define BLE_TX_IND_UUID       {0x40,0xE3,0x4A,0x1D,0xC2,0x5F,0xB0,0x9C,0xB7,0x47,0xE6,0x43,0xB4,0x00,0x53,0x86}
*********************************************************************************************************************/
/*
 * @brief:  蓝牙配网初始化
 *
 * @param[out]: hdl     -   句柄
 * @param[in]:  write   -   写数据回调
 * @param[in]： cfg     -    配置WiFi回调
 *
 * @return: 0成功
 **/
int avsdk_bdn_init(iot_bdn_ref_t *hdl,
                   int (*ble_send)(uint8_t *data, uint16_t len),
                   int (*wifi_set)(char *ssid, char *pwd));

/*
 * @brief:  蓝牙配网反初始化，资源释放
 *
 * @param[in]:  hdl     -   句柄,由avsdk_bdn_init获取
 *
 * @return: 0成功
 **/
int avsdk_bdn_fini(iot_bdn_ref_t *hdl);

/*
 * @brief:  蓝牙数据接收
 *
 * @param[out]: hdl     -   句柄,由avsdk_bdn_init获取
 * @param[in]:  data    -   待处理数据指针
 * @param[in]:  len     -   待处理数据长度
 *
 * @return:
 **/
void avsdk_bdn_recv(iot_bdn_ref_t hdl, uint8_t *data, uint16_t len);

int avsdk_local_decode(uint8_t *payload, size_t len, iot_PpiotCmd_t *cmd);
int avsdk_local_encode(iot_PpiotCmd_t *cmd, uint8_t *payload, size_t *len);
#endif

#if 1//dp
int64_t dp_get_int(const uint8_t *src, int len);
int dp_put_int(uint8_t *dst, int64_t var);
/**
 * @brief 通知用户设备被收到了dp点.
 *  注意：如果total大于1，则表示下发了一组有关联关系的dp操作，
 *       用户需要收到所有的dp回调后，即total=offset，才能执行命令；
 *
 * @param[in] total     - 收到dp点的总个数.
 * @param[in] offset    - 当前dp点数组中的第几个数据点.
 * @param[in] dp        - dp点的信息.
 *
 * @return 0正确.
 */
typedef int (*iot_on_datapoint_t)(int total, int offset, datapoint_t *dp);
int avsdk_set_on_datapoint(iot_on_datapoint_t cb);


/**
 * @brief 通知设备定时任务发生变更（全量）.
 *
 * @param[in] count     - 收到定时任务的总个数.
 * @param[in] p         - dp_ttCmd_t的数组.
 *
 * @return 0正确.
 */
typedef int (*iot_on_dp_ttcmd_t)(dp_ttCmds_t *p);

/**
 * @brief 通知设备保存定时任务
 *
 * @param[in] cb     - 回调.
 *
 * @return 0正确.
 */
int avsdk_set_on_dp_ttcmdSet(iot_on_dp_ttcmd_t cb);

/**
 * @brief 获取设备保存的定时任务
 *   注意：一般是设备能自己修改定时任务后，才会触发该回调，即如果设备没有修改定时任务的功能，该回调不会被触发；
 *
 * @param[in] cb     - 回调.
 *
 * @return 0正确.
 */
int avsdk_set_on_dp_ttcmdGet(iot_on_dp_ttcmd_t cb);

/**
 * @brief 上报设备端定时任务的时间；
 *   注意：1.如果设备不能自己修改定时任务，该值就是avsdk_set_on_dp_ttcmdSet收到的timestamp；
 *        2.如果设备自己修改了定时任务，该值填当时修改的时间。
 *        3.如果支持定时任务，每次连上平台都需要上报一次；尝试同步定时任务。
 *
 * @param[in] timestamp     - 时间戳.单位毫秒
 *
 * @return 0正确.
 */
int avsdk_dp_update_ttcmd_timestamp(uint64_t timestamp);

/**
 * @brief 解析定时任务中的pbs.
 *  注意：如果total大于1，则表示下发了一组有关联关系的dp操作，
 *       用户需要收到所有的dp回调后，即total=offset，才能执行命令；
 *
 * @param[in] dp_count     - dp_ttCmd_t中dp_count
 * @param[in] pbs          - dp_ttCmd_t中pbs
 * @param[in] pbs_len      - dp_ttCmd_t中pbs_len
 *
 * @return 0正确.
 */
int avsdk_dp_timetask_parse(int dp_count, uint8_t *pbs, int pbs_len, iot_on_datapoint_t on_datapoint);

/**
 * @brief 设备端更新数据点状态.
 *  注意：
 *  1.开机的时候，有很多dp点需要上报给平台，用户一定要将update_now设为0，
 *      在最后一条dp点设置1，以减少上报平台的次数！！！
 *  2.需要及时同步到平台的dp点，如运行中开关发生变化，update_now要设为1.
 *
 * @param[in] update_now    - 0，先缓存到ram，后面sdk周期同步到平台；1.立马同步到平台；
 * @param[in] isDefault     - 0，设备的实时值；1.设置设备的出厂默认值(添加绑定后上报一次即可)；
 * @param[in] dp            - 需要更新的dp点.
 *
 * @return 0正确.
 */
int avsdk_update_datapoint(int update_now, int isDefault, datapoint_t *dp);

/**
 * @brief dp事件上报，如果需要同时报多个事件，只能使用该api.
 *
 * @param[in] isCS          - 0，只需要传一个事件；1.需要传一个云存；
 * @param[in] evt_list      - 事件信息
 *
 * @return 0正确.
 */
int64_t avsdk_dp_event(int isCS, dp_event_list_t *evt_list);
#endif //dp

#if 1
/*
 * @brief:  启动本地udp服务器，可用于ap配网，只有资源紧张，默认没开启udp服务的设备才需要调用，常规sdk都不需要调用
 *
 *
 * @return: 0成功，-4已经有服务运行。
 **/
int avsdk_localsrv_udp_start(void);

/*
 * @brief:  关闭本地udp服务器，节约资源；一般不需要调用
 *
 *
 * @return: 无
 **/
void avsdk_localsrv_udp_stop(void);

#endif

/*
 * @brief:  发现局域网内的设备
 *
 *
 * @return: 设备信息
 **/
discovery_t *avsdk_broadcast_discovery(void);

#if 1 //设备拉流

/*
 * @brief: 连接指定设备
 *
 * @param[in]:   did     - avsdk_bind_list返回在线的设备中的一个
 *
 * @return: 小于0失败，大于0表示conn_id,用于其他命令发送
 **/
int avsdk_user_conn(char *did);

/*
 * @brief: 断开连接(本地拉流)
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @return: 0成功
 **/
int avsdk_user_disconn(int conn_id);

/*
 * @brief: 播放视频
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回视频的参数
 *
 * @return: 0成功
 **/
int avsdk_user_VideoPlay(int conn_id, ipc_VideoPlay_Req *req, ipc_VideoPlay_Resp *rsp);

/*
 * @brief: 停止播放视频
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回音频的参数
 *
 * @return: 0成功
 **/
int avsdk_user_VideoPause(int conn_id, ipc_VideoPause_Req *req, ipc_VideoPause_Resp *rsp);

/*
 * @brief: 播放音频
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回音频的参数
 *
 * @return: 0成功
 **/
int avsdk_user_AudioPlay(int conn_id, ipc_AudioPlay_Req *req, ipc_AudioPlay_Resp *rsp);

/*
 * @brief: 停止播放音频
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回音频的参数
 *
 * @return: 0成功
 **/

int avsdk_user_AudioPause(int conn_id, ipc_AudioPause_Req *req, ipc_AudioPause_Resp *rsp);

/*
 * @brief: 发起对讲
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回设备支持播放的音频参数
 *
 * @return: 0成功
 **/

int avsdk_user_TalkbackPlay(int conn_id, ipc_TalkbackPlay_Req *req, ipc_TalkbackPlay_Resp *rsp);

/*
 * @brief: 停止对讲
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回音频的参数
 *
 * @return: 0成功
 **/

int avsdk_user_TalkbackPause(int conn_id, ipc_TalkbackPause_Req *req, ipc_TalkbackPause_Resp *rsp);

/*
 * @brief: 获取一张缩略图
 *
 * @param[in]:   conn_id - 由avsdk_user_conn_dev获得
 *
 * @param[in]:   req     - 请求参数
 *
 * @param[out]:  rsp     - 返回缩略图
 *
 * @return: 0成功
 **/
int avsdk_user_Screenshot(int conn_id, ipc_Screenshot_Req *req, ipc_Screenshot_Resp *rsp);


#endif

#if 1 //不更新的接口,不推荐使用

/**
 * @brief 异常事件上报,建议使用avsdk_push_event
 *
 * @param[in] event_id  - 异常事件id.
 *
 * @param[in] avchannel - IPC都为0；如果是NVR，表示第几路摄像头
 *
 * @param[in] hw_errno  - 硬件错误码，event_id为E_IOT_EVENT_HARDWARE_FAULT和E_IOT_EVENT_FIRMWARE_UPDATE有效.
 *
 * @param[in] peopleID  - 人脸识别id,没有该功能填NULL.
 *
 * @param[in] isCS      - 该事件是否带云存,true表示带有云存类型的事件(与开通云存状态没关系);false表示只产生一条消息.
 *
 * @return 返回值：为负数表示错误; 等于0事件上报成功，但是设备没开通云存; 大于0表示上报成功且设备开通了云存.
 */
int64_t avsdk_event_pulish(iot_event_id_t  event_id,
                           int64_t         avchannel,
                           int64_t         hw_errno,
                           ipc_PeopleID_t *peopleID,
                           bool            isCS);

#endif //不更新的接口

#if 1
/* 注册回调函数 */
void avsdk_set_on_ipc_PirSet(on_ipc_PirSet_t cb);
void avsdk_set_on_ipc_PirGet(on_ipc_PirGet_t cb);
void avsdk_set_on_ipc_ChanState(on_ipc_ChanState_t cb);
void avsdk_set_on_ipc_VideoChanChange(on_ipc_VideoChanChange_t cb);
void avsdk_set_on_ipc_Discovery(on_ipc_Discovery_t cb);
void avsdk_set_on_ipc_WifiAPGet(on_ipc_WifiAPGet_t cb);
void avsdk_set_on_ipc_WifiSet(on_ipc_WifiSet_t cb);
void avsdk_set_on_ipc_WifiGet(on_ipc_WifiGet_t cb);
void avsdk_set_on_ipc_OsdSet(on_ipc_OsdSet_t cb);
void avsdk_set_on_ipc_OsdGet(on_ipc_OsdGet_t cb);
void avsdk_set_on_ipc_VideoPlay(on_ipc_VideoPlay_t cb);
void avsdk_set_on_ipc_VideoPause(on_ipc_VideoPause_t cb);
void avsdk_set_on_ipc_VideoQosSet(on_ipc_VideoQosSet_t cb);
void avsdk_set_on_ipc_FlipSet(on_ipc_FlipSet_t cb);
void avsdk_set_on_ipc_AudioPlay(on_ipc_AudioPlay_t cb);
void avsdk_set_on_ipc_AudioPause(on_ipc_AudioPause_t cb);
void avsdk_set_on_ipc_TalkbackPlay(on_ipc_TalkbackPlay_t cb);
void avsdk_set_on_ipc_TalkbackPause(on_ipc_TalkbackPause_t cb);
void avsdk_set_on_ipc_HistoryPlanSet(on_ipc_HistoryPlanSet_t cb);
void avsdk_set_on_ipc_HistoryPlanGet(on_ipc_HistoryPlanGet_t cb);
void avsdk_set_on_ipc_HistoryDays(on_ipc_HistoryDays_t cb);
void avsdk_set_on_ipc_HistoryDayList(on_ipc_HistoryDayList_t cb);
void avsdk_set_on_ipc_HistoryPlay(on_ipc_HistoryPlay_t cb);
void avsdk_set_on_ipc_HistoryPause(on_ipc_HistoryPause_t cb);
void avsdk_set_on_ipc_HistoryThumGet(on_ipc_HistoryThumGet_t cb);
void avsdk_set_on_ipc_HistoryDel(on_ipc_HistoryDel_t cb);
void avsdk_set_on_ipc_ConfigGet(on_ipc_ConfigGet_t cb);
void avsdk_set_on_ipc_TimeSet(on_ipc_TimeSet_t cb);
void avsdk_set_on_ipc_TimeGet(on_ipc_TimeGet_t cb);
void avsdk_set_on_ipc_LedSet(on_ipc_LedSet_t cb);
void avsdk_set_on_ipc_LedGet(on_ipc_LedGet_t cb);
void avsdk_set_on_ipc_LedModeSet(on_ipc_LedModeSet_t cb);
void avsdk_set_on_ipc_LedModeGet(on_ipc_LedModeGet_t cb);
void avsdk_set_on_ipc_IRCutSet(on_ipc_IRCutSet_t cb);
void avsdk_set_on_ipc_IRCutGet(on_ipc_IRCutGet_t cb);
void avsdk_set_on_ipc_SecretSet(on_ipc_SecretSet_t cb);
void avsdk_set_on_ipc_SecretGet(on_ipc_SecretGet_t cb);
void avsdk_set_on_ipc_NotifySet(on_ipc_NotifySet_t cb);
void avsdk_set_on_ipc_NotifyGet(on_ipc_NotifyGet_t cb);
void avsdk_set_on_ipc_MotionzoneSet(on_ipc_MotionzoneSet_t cb);
void avsdk_set_on_ipc_MotionzoneGet(on_ipc_MotionzoneGet_t cb);
void avsdk_set_on_ipc_PspAdd(on_ipc_PspAdd_t cb);
void avsdk_set_on_ipc_PspDel(on_ipc_PspDel_t cb);
void avsdk_set_on_ipc_PspList(on_ipc_PspList_t cb);
void avsdk_set_on_ipc_PspCall(on_ipc_PspCall_t cb);
void avsdk_set_on_ipc_Reboot(on_ipc_Reboot_t cb);
void avsdk_set_on_ipc_Reset(on_ipc_Reset_t cb);
void avsdk_set_on_ipc_FlipGet(on_ipc_FlipGet_t cb);
void avsdk_set_on_ipc_LanAuth(on_ipc_LanAuth_t cb);
void avsdk_set_on_ipc_TimedcruiseSet(on_ipc_TimedcruiseSet_t cb);
void avsdk_set_on_ipc_TimedcruiseGet(on_ipc_TimedcruiseGet_t cb);
void avsdk_set_on_ipc_StorageInfo(on_ipc_StorageInfo_t cb);
void avsdk_set_on_ipc_StorageFormat(on_ipc_StorageFormat_t cb);
void avsdk_set_on_ipc_StorageFormatRate(on_ipc_StorageFormatRate_t cb);
void avsdk_set_on_ipc_LogSet(on_ipc_LogSet_t cb);
void avsdk_set_on_ipc_VolumeSet(on_ipc_VolumeSet_t cb);
void avsdk_set_on_ipc_PowerFreqSet(on_ipc_PowerFreqSet_t cb);
void avsdk_set_on_ipc_PowerFreqGet(on_ipc_PowerFreqGet_t cb);
void avsdk_set_on_ipc_VolumeGet(on_ipc_VolumeGet_t cb);
void avsdk_set_on_ipc_AlarmSet(on_ipc_AlarmSet_t cb);
void avsdk_set_on_ipc_AlarmGet(on_ipc_AlarmGet_t cb);
void avsdk_set_on_ipc_Screenshot(on_ipc_Screenshot_t cb);
void avsdk_set_on_ipc_PtzCtrl(on_ipc_PtzCtrl_t cb);
void avsdk_set_on_ipc_FirmwareNotify(on_ipc_FirmwareNotify_t cb);
void avsdk_set_on_ipc_FirmwareRate(on_ipc_FirmwareRate_t cb);
void avsdk_set_on_ipc_EventRecordGet(on_ipc_EventRecordGet_t cb);
void avsdk_set_on_ipc_EventRecordSet(on_ipc_EventRecordSet_t cb);
void avsdk_set_on_ipc_GetNetworkInfo(on_ipc_GetNetworkInfo_t cb);
void avsdk_set_on_ipc_FileStart(on_ipc_FileStart_t cb);
void avsdk_set_on_ipc_FileStop(on_ipc_FileStop_t cb);
void avsdk_set_on_ipc_CustomCmd(on_ipc_CustomCmd_t cb);
void avsdk_set_on_ipc_DirCreate(on_ipc_DirCreate_t cb);
void avsdk_set_on_ipc_DirDel(on_ipc_DirDel_t cb);
void avsdk_set_on_ipc_DirEdit(on_ipc_DirEdit_t cb);
void avsdk_set_on_ipc_DirList(on_ipc_DirList_t cb);
void avsdk_set_on_ipc_FileAdd(on_ipc_FileAdd_t cb);
void avsdk_set_on_ipc_FileDel(on_ipc_FileDel_t cb);
void avsdk_set_on_ipc_FileEdit(on_ipc_FileEdit_t cb);
void avsdk_set_on_ipc_FileRecvRate(on_ipc_FileRecvRate_t cb);
void avsdk_set_on_ipc_FileThumList(on_ipc_FileThumList_t cb);
void avsdk_set_on_ipc_FileAttrSet(on_ipc_FileAttrSet_t cb);
void avsdk_set_on_ipc_ExecIOTCMD(on_ipc_ExecIOTCMD_t cb);
void avsdk_set_on_ipc_ExecTimetask(on_ipc_ExecTimetask_t cb);
void avsdk_set_on_ipc_TamperSet(on_ipc_TamperSet_t cb);
void avsdk_set_on_ipc_SetAutoTrack(on_ipc_SetAutoTrack_t cb);
void avsdk_set_on_ipc_GetAutoTrack(on_ipc_GetAutoTrack_t cb);
void avsdk_set_on_ipc_ForceIFrame(on_ipc_ForceIFrame_t cb);
void avsdk_set_on_ipc_SetLowPower(on_ipc_SetLowPower_t cb);
void avsdk_set_on_ipc_GetLowPower(on_ipc_GetLowPower_t cb);
void avsdk_set_on_leaveMessage(on_ipc_LeaveMessage_t cb); //留言
void avsdk_set_on_StateChangeByApp(on_ipc_StateChangeByApp_t cb);//app操作导致设备状态发生改变（cid=220）
void avsdk_set_on_VideoCall(on_ipc_VideoCall_t cb);//app发起视频对接(561)
void avsdk_set_on_PauseAllAv(on_ipc_PauseAllAv_t cb);//退出所有的音视频包括视频对讲(563)
#endif

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************
 * @} (end addtogroup xciot_api)
 */
/****************************************************************************/
#endif /* XCIOT_API_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/


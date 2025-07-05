/****************************************************************************/
/* iot_xdbsp.h
 *
 ****************************************************************************/
#ifndef IOT_XDBSP_H_INCLUDE
#define IOT_XDBSP_H_INCLUDE
/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/
#include <stdint.h>
#include <string.h>
/****************************************************************************/
/* Configure Definitions                                                    */
/****************************************************************************/

/* tx/rx dump */
#define XDBSP_TX_DUMP_ENABLE 1
#define XDBSP_RX_DUMP_ENABLE 1

/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/* 事件类型 */
#define XDBSP_EVENT_TYPE_DOOR_LOCKED   0x00 ///< 已上锁
#define XDBSP_EVENT_TYPE_DOOR_UNLOCKED 0x01 ///< 已打开
#define XDBSP_EVENT_TYPE_ALARM         0x02 ///< 报警
#define XDBSP_EVENT_TYPE_RMTUNLOCK     0x03 ///< 远程开锁请求
#define XDBSP_EVENT_TYPE_TIPS          0X04 ///< 提醒

/* 事件信息 { */
/****************/
// 已上锁/已打开
/****************/
#define XDBSP_EVENT_INFO_DOOR_OUTSIDE 0x00 ///< 外门
#define XDBSP_EVENT_INFO_DOOR_INSIDE  0x01 ///< 内门

/****************/
// 报警
/****************/
#define XDBSP_EVENT_INFO_ALARM_00 0x00 ///< 智能锁被撬
#define XDBSP_EVENT_INFO_ALARM_01 0x01 ///< 强行开门
#define XDBSP_EVENT_INFO_ALARM_02 0x02 ///< 指纹尝试开锁被冻结
#define XDBSP_EVENT_INFO_ALARM_03 0x03 ///< 密码尝试开锁被冻结
#define XDBSP_EVENT_INFO_ALARM_04 0x04 ///< IC卡尝试开锁被冻结
#define XDBSP_EVENT_INFO_ALARM_05 0x05 ///< 钥匙尝试开锁被冻结
#define XDBSP_EVENT_INFO_ALARM_06 0x06 ///< 遥控尝试开锁被冻结
#define XDBSP_EVENT_INFO_ALARM_RU 0x07 ///< 保留
#define XDBSP_EVENT_INFO_ALARM_08 0x08 ///< 胁迫开锁报警
#define XDBSP_EVENT_INFO_ALARM_09 0x09 ///< 特斯拉开锁报警
#define XDBSP_EVENT_INFO_ALARM_0A 0x0A ///< 任意开锁被冻结
#define XDBSP_EVENT_INFO_ALARM_0B 0x0B ///< 人脸尝试开锁报警
#define XDBSP_EVENT_INFO_ALARM_0C 0x0C ///< 掌纹尝试开锁报警
#define XDBSP_EVENT_INFO_ALARM_0D 0x0D ///< 陌生人逗留报警
#define XDBSP_EVENT_INFO_ALARM_0E 0x0E ///< 火灾报警
#define XDBSP_EVENT_INFO_ALARM_0F 0x0F ///< 门口有陌生人
#define XDBSP_EVENT_INFO_ALARM_10 0x10 ///< 非活体人脸
#define XDBSP_EVENT_INFO_ALARM_11 0x11 ///< 被人劫持
#define XDBSP_EVENT_INFO_ALARM_12 0x12 ///< 被人尾随
#define XDBSP_EVENT_INFO_ALARM_13 0x13 ///< 门口有人徘徊
#define XDBSP_EVENT_INFO_ALARM_14 0x14 ///< 指纹尝试开锁报警
#define XDBSP_EVENT_INFO_ALARM_15 0x15 ///< 密码尝试开锁报警
#define XDBSP_EVENT_INFO_ALARM_16 0x16 ///< 卡尝试开锁报警
#define XDBSP_EVENT_INFO_ALARM_17 0x17 ///< 系统锁定报警
/****************/
// 远程开锁请求
/****************/
#define XDBSP_EVENT_INFO_RMTUNLOCK 0x00 ///< 固定0x00

/****************/
// 提醒
/****************/
#define XDBSP_EVENT_INFO_TIPS_00 0x00 ///< 忘拔钥匙(0x00)
#define XDBSP_EVENT_INFO_TIPS_01 0x01 ///< 锁门提醒(0x01)
#define XDBSP_EVENT_INFO_TIPS_02 0x02 ///< 敲门提醒(0x02)
#define XDBSP_EVENT_INFO_TIPS_03 0x03 ///< SOS求救提醒(0x03)
#define XDBSP_EVENT_INFO_TIPS_04 0x04 ///< 门没关好(0x04)
#define XDBSP_EVENT_INFO_TIPS_05 0x05 ///< 门已反锁(0x05)
#define XDBSP_EVENT_INFO_TIPS_06 0x06 ///< 门已解锁(0x06)
#define XDBSP_EVENT_INFO_TIPS_07 0x07 ///< 常开已开启(0x07)
#define XDBSP_EVENT_INFO_TIPS_08 0x08 ///< 电量低压提醒(0x08)
#define XDBSP_EVENT_INFO_TIPS_09 0x09 ///< 添加用户(0x09)
#define XDBSP_EVENT_INFO_TIPS_0A 0x0A ///< 删除用户(0x0A)
#define XDBSP_EVENT_INFO_TIPS_0B 0x0B ///< 用户初始化(0x0B)
#define XDBSP_EVENT_INFO_TIPS_0C 0x0C ///< 门铃提醒(0x0C)
#define XDBSP_EVENT_INFO_TIPS_0D 0x0D ///< 删除全部用户(0x0D)
#define XDBSP_EVENT_INFO_TIPS_0E 0x0E ///< 定时上锁提醒(0x0E)
#define XDBSP_EVENT_INFO_TIPS_0F 0x0F ///< 主动查看提醒(0x0F)
#define XDBSP_EVENT_INFO_TIPS_10 0x10 ///< 门内按键开锁(0x10)
#define XDBSP_EVENT_INFO_TIPS_11 0x11 ///< 门内把手开锁(0x11)
/* 事件信息 } */

/* 用户类型 */
#define XDBSP_USER_TYPE_DEFAULT      0x00 ///< 默认用户
#define XDBSP_USER_TYPE_FINGER_PRINT 0x01 ///< 指纹用户
#define XDBSP_USER_TYPE_PASSWORD     0x02 ///< 密码用户
#define XDBSP_USER_TYPE_IC           0x03 ///< IC卡用户
#define XDBSP_USER_TYPE_KEY          0x04 ///< 钥匙用户
#define XDBSP_USER_TYPE_MOBAPP       0x05 ///< 手机用户
#define XDBSP_USER_TYPE_FACE         0x06 ///< 人脸用户
#define XDBSP_USER_TYPE_PALMAR_PRINT 0x07 ///< 掌纹用户
#define XDBSP_USER_TYPE_IRIS         0x08 ///< 虹膜用户
#define XDBSP_USER_TYPE_TEMP         0x09 ///< 临时用户
#define XDBSP_USER_TYPE_FINGER_VEIN  0x0A ///< 指静脉用户
#define XDBSP_USER_TYPE_PALMAR_VEIN  0x0B ///< 掌静脉用户

/* 用户编号 */
#define XDBSP_USER_ID_IS_YUN(id_)   ((id_) >= 1024 && (id_) <= 2048)
#define XDBSP_USER_ID_IS_LOCAL(id_) ((id_) >= 0 && (id_) <= 1024)

/* 模块产测 */
#define XDBSP_PDTEST_ERRCODE_FAIL    0x01 ///< 测试失败
#define XDBSP_PDTEST_ERRCODE_IOTCFG  0x02 ///< 云端信息错误
#define XDBSP_PDTEST_ERRCODE_NETLOST 0x03 ///< 路由器连接失败
#define XDBSP_PDTEST_ERRCODE_YUNLOST 0x04 ///< 服务器连接失败
#define XDBSP_PDTEST_ERRCODE_NOVIDEO 0x05 ///< 没有图片
#define XDBSP_PDTEST_ERRCODE_NOAUDIO 0x06 ///< 没有声音

/* 用户验证 @{ */
/****************/
// 用户验证结果
/****************/
#define XDBSP_AUTH_RESULT_SUCCESS  0x00 ///< 验证通过(0x00)
#define XDBSP_AUTH_RESULT_FAILED   0x01 ///< 验证失败(0x01)
#define XDBSP_AUTH_RESULT_NOTEXIST 0x02 ///< 用户不存在(0x02)

/****************/
// 用户权限
/****************/
#define XDBSP_AUTH_TYPE_ADMIN    0x00 ///< 管理员(0x00)
#define XDBSP_AUTH_TYPE_ORDINARY 0x01 ///< 普通用户(0x01)
#define XDBSP_AUTH_TYPE_TEMP     0x02 ///< 临时用户(0x02)
#define XDBSP_AUTH_TYPE_INDANGER 0x03 ///< 胁迫用户(0x03)
/* 事件信息 @} */

/* 联网状态 */
#define XDBSP_NETSTA_NOCFG             0x01 ///< 未配置网络(0x01)
#define XDBSP_NETSTA_ROUTER_CONNECTING 0x02 ///< 正在连接路由器或基站(0x02)
#define XDBSP_NETSTA_ROUTER_CONNECTED  0x03 ///< 已连接路由器或基站(0x03)
#define XDBSP_NETSTA_YUN_CONNECTED     0x04 ///< 已连接云服务器(0x04)

/* 串口波特率 */
#define XDBSP_BAUDRATE_115200_X1  1
#define XDBSP_BAUDRATE_115200_X2  2
#define XDBSP_BAUDRATE_115200_X3  3
#define XDBSP_BAUDRATE_115200_X4  4
#define XDBSP_BAUDRATE_115200_X5  5
#define XDBSP_BAUDRATE_115200_X6  6
#define XDBSP_BAUDRATE_115200_X7  7
#define XDBSP_BAUDRATE_115200_X8  8
#define XDBSP_BAUDRATE_115200_X9  9
#define XDBSP_BAUDRATE_115200_X10 10

/* 串口图传开启 */
#define XDBSP_SERJPG_ERRCODE_SUCCESS     0x00 ///< 开启成功(0x00)
#define XDBSP_SERJPG_ERRCODE_IS_EXIST    0x01 ///< 已存在相同图片(0x01)
#define XDBSP_SERJPG_ERRCODE_NOT_SUPPORT 0x02 ///< 不支持图传功能(0x02)
#define XDBSP_SERJPG_ERRCODE_TOO_BIG     0x03 ///< 图片大小超过限制(0x03)
#define XDBSP_SERJPG_ERRCODE_MEM_FAILED  0x04 ///< 图片内存申请失败(0x04)
#define XDBSP_SERJPG_ERRCODE_DISABLE     0x05 ///< 临时禁用图传功能(0x05)

/* 串口图传结果 */
#define XDBSP_SERJPG_RESULT_SUCCESS    0x00 ///< 图传成功(0x00)
#define XDBSP_SERJPG_RESULT_ERRCHKSUM  0x01 ///< 校验失败(0x01)
#define XDBSP_SERJPG_RESULT_REVTIMEOUT 0x02 ///< 接收超时(0x02)

/* 视频状态 */
#define XDBSP_AVSTAT_NOT_SUPPORT 0x00 ///< 不支持(0x00)
#define XDBSP_AVSTAT_STOPED      0x01 ///< 视频结束(0x01)
#define XDBSP_AVSTAT_STARTED     0x02 ///< 视频开始(0x02)

/* 配置 */
#define XDBSP_UI_MODE_NORMAL 0x00 ///< UI 普通模式
#define XDBSP_UI_MODE_MGMT   0x01 ///< UI 管理模式

#define XDBSP_LANG_DEFAULT 0x00 ///< 默认(0x00)
#define XDBSP_LANG_CH      0x01 ///< 中文(0x01)
#define XDBSP_LANG_EN      0x02 ///< 英文(0x02)

/****************************************************************************/
/* Public Types                                                             */
/****************************************************************************/
/**
 * @brief xdbsp cmd id enum.
 *
 * H2M: host(doorbell mcu) -> module(wifi)
 * M2H: module(wifi)       -> host(doorbell mcu)
 */
typedef uint8_t xdbsp_cmd_id_e;
enum {
    /* 通用命令处理结果回复 (WIFI->MCU) */
    E_XDBSP_COMMON_RSP_M2H = 0x02,

    /* 配网模式(MCU->WIFI) */
    E_XDBSP_NETCFG_REQ_H2M = 0x01,
    E_XDBSP_NETCFG_RSP_M2H = 0x02,

    /* 消息上传(MCU->WIFI) */
    E_XDBSP_SNDMSG_REQ_H2M = 0x03,
    E_XDBSP_SNDMSG_RSP_M2H = 0x02,

    /* 断电通知(MCU->WIFI) */
    E_XDBSP_PWROFF_REQ_H2M = 0x04,
    E_XDBSP_PWROFF_RSP_M2H = 0x02,

    /* 清除数据(MCU->WIFI) */
    E_XDBSP_CLRDAT_REQ_H2M = 0x05,
    E_XDBSP_CLRDAT_RSP_M2H = 0x02,

    /* 设备信息(MCU->WIFI) */
    E_XDBSP_DEVINF_REQ_H2M = 0x06,
    E_XDBSP_DEVINF_RSP_M2H = 0x07,

    /* 升级固件(MCU->WIFI) */
    E_XDBSP_FW1UPG_REQ_H2M = 0x0A,
    E_XDBSP_FW1UPG_RSP_M2H = 0x0B,

    /* 模块产测(MCU->WIFI) */
    E_XDBSP_PDTEST_REQ_H2M = 0x0C,
    E_XDBSP_PDTEST_RSP_M2H = 0x0D,

    /* 网络时间(MCU->WIFI) */
    E_XDBSP_GETUTC_REQ_H2M = 0x10,
    E_XDBSP_GETUTC_RSP_M2H = 0x11,

    /* 远程开锁(WIFI->MCU) */
    E_XDBSP_REMULK_REQ_M2H = 0x13,
    E_XDBSP_REMULK_RSP_H2M = 0x12,

    /* 图传开启(MCU->WIFI) */
    E_XDBSP_OPENAV_REQ_H2M = 0x1C,
    E_XDBSP_OPENAV_RSP_M2H = 0x1D,

    /* 用户验证(MCU->WIFI) */
    E_XDBSP_URAUTH_REQ_H2M = 0x20,
    E_XDBSP_URAUTH_RSP_M2H = 0x21,

    /* 联网通知(WIFI->MCU) */
    /* 状态改变主动下发(WIFI->MCU) */
    E_XDBSP_NETSTA_EVT_M2H = 0x23,

    /* 串口图传开启(MCU->WIFI) */
    E_XDBSP_SERJPG_REQ_H2M = 0x24,
    E_XDBSP_SERJPG_RSP_M2H = 0x25,

    /* 串口图传结果(WIFI->MCU) */
    E_XDBSP_SERJPG_EVT_M2H = 0x27,

    /* 视频状态查询(MCU->WIFI) */
    E_XDBSP_AVSTAT_REQ_H2M = 0x3A,
    E_XDBSP_AVSTAT_RSP_M2H = 0x3B,
    /* 状态改变主动下发(WIFI->MCU) */
    E_XDBSP_AVSTAT_EVT_M2H = 0x3B,

    /* 视频参数设置(MCU->WIFI) */
    E_XDBSP_SETDAV_REQ_H2M = 0x3C,
    E_XDBSP_SETDAV_RSP_M2H = 0x3D,
};

/**
 * @brief xdbsp context.
 */
typedef struct xdbsp_ctx xdbsp_ctx_t;

/**
 * @brief xdbsp on cmd callback type.
 */
typedef void (*xdbsp_on_cmd_fn)(xdbsp_cmd_id_e id, void *ptrval, void *ud);

/**
 * @brief xdbsp on tick callback type.
 */
typedef void (*xdbsp_on_tick_fn)(void *ud);

//return write len
typedef int (*xdbsp_write)(uint8_t *buffer, int len);

//return read len
typedef int (*xdbsp_read)(uint8_t *buffer, int len, int timeout);

/**
 * @brief xdbsp context.
 */
struct xdbsp_ctx {
    union {
        int   p_fd;
        void *d_id;
    } id;
    uint32_t         shutdown : 1;
    uint32_t         tx_dump : 1;
    uint32_t         rx_dump : 1;
    xdbsp_on_cmd_fn  on_cmd;
    xdbsp_on_tick_fn on_tick;
    xdbsp_write      uesr_write;
    xdbsp_read       uesr_read;
    void            *ud;
};

/* E_XDBSP_NETCFG_REQ_H2M */
typedef struct xdbsp_netcfg_req_h2m {
    uint8_t ui_mode;    ///< 0x00: 普通UI, 0x01：管理UI
    uint8_t nwk_notify; ///< 0x00: 关闭, 0x01: 开启
} xdbsp_netcfg_req_h2m_t;

/* E_XDBSP_NETCFG_RSP_M2H */
typedef struct xdbsp_netcfg_rsp_m2h {
    uint8_t retcode; ///< 0x00: 执行成功, 0x02: 执行失败
} xdbsp_netcfg_rsp_m2h_t;

/* E_XDBSP_SNDMSG_REQ_H2M */
typedef struct xdbsp_sndmsg_req_h2m {
    uint8_t event_type; ///< 事件类型 XDBSP_EVENT_TYPE_DOOR_LOCKED
    uint8_t event_info; ///< 事件信息 XDBSP_EVENT_INFO_DOOR_OUTSIDE
    uint8_t user_type;  ///< 用户类型 XDBSP_USER_TYPE_PASSWORD
    uint16_t user_id; ///< 用户id, 主板范围: 0-1024, 云用户范围: 1024-2048
} xdbsp_sndmsg_req_h2m_t;

/* E_XDBSP_SNDMSG_RSP_M2H */
typedef struct xdbsp_sndmsg_rsp_m2h {
    uint8_t retcode; ///< 0x00: 执行成功, 0x02: 执行失败
} xdbsp_sndmsg_rsp_m2h_t;

/* E_XDBSP_PWROFF_REQ_H2M */
typedef struct xdbsp_pwroff_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_pwroff_req_h2m_t;

/* E_XDBSP_PWROFF_RSP_M2H */
typedef struct xdbsp_pwroff_rsp_m2h {
    uint8_t retcode; ///< 0x00: 执行成功, 0x02: 执行失败
} xdbsp_pwroff_rsp_m2h_t;

/* E_XDBSP_CLRDAT_REQ_H2M */
typedef struct xdbsp_clrdat_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_clrdat_req_h2m_t;

/* E_XDBSP_CLRDAT_RSP_M2H */
typedef struct xdbsp_clrdat_rsp_m2h {
    uint8_t retcode; ///< 0x00: 执行成功, 0x02: 执行失败
} xdbsp_clrdat_rsp_m2h_t;

/* E_XDBSP_DEVINF_REQ_H2M */
typedef struct xdbsp_devinf_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_devinf_req_h2m_t;

/* E_XDBSP_DEVINF_RSP_M2H */
typedef struct xdbsp_devinf_rsp_m2h {
    uint8_t did[12];    ///< 设备id
    uint8_t macaddr[6]; ///< MAC地址
} xdbsp_devinf_rsp_m2h_t;

/* E_XDBSP_FW1UPG_REQ_H2M */
typedef struct xdbsp_fw1upg_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_fw1upg_req_h2m_t;

/* E_XDBSP_FW1UPG_RSP_M2H */
typedef struct xdbsp_fw1upg_rsp_m2h {
    uint8_t upg_status; ///< 0x00:失败, 0x01:成功, 0x02: 固件已经最新
} xdbsp_fw1upg_rsp_m2h_t;

/* E_XDBSP_PDTEST_REQ_H2M */
typedef struct xdbsp_pdtest_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_pdtest_req_h2m_t;

/* E_XDBSP_PDTEST_RSP_M2H */
typedef struct xdbsp_pdtest_rsp_m2h {
    uint8_t retcode; ///< 0x00: 执行成功, 0x01: 执行失败
    uint8_t errcode; ///< 0x00: 成功, XDBSP_PDTEST_ERRCODE_FAIL
} xdbsp_pdtest_rsp_m2h_t;

/* E_XDBSP_GETUTC_REQ_H2M */
typedef struct xdbsp_getutc_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_getutc_req_h2m_t;

/* E_XDBSP_GETUTC_RSP_M2H */
typedef struct xdbsp_getutc_rsp_m2h {
    uint32_t utc; ///< UTC时间秒数
    int8_t   tz; ///< 数值范围为-128 到 127, 时区值=小时x10+刻，一刻=15分钟
} xdbsp_getutc_rsp_m2h_t;

/* E_XDBSP_REMULK_REQ_M2H */
typedef struct xdbsp_remulk_req_m2h {
    uint8_t user_type; ///< 用户类型 XDBSP_USER_TYPE_MOBAPP(只能是手机用户)
    uint16_t user_id; ///< 用户id, 主板范围: 0-1024, 云用户范围: 1024-2048
} xdbsp_remulk_req_m2h_t;

/* E_XDBSP_REMULK_RSP_H2M */
typedef struct xdbsp_remulk_rsp_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_remulk_rsp_h2m_t;

/* E_XDBSP_OPENAV_REQ_H2M */
typedef struct xdbsp_openav_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_openav_req_h2m_t;

/* E_XDBSP_OPENAV_RSP_M2H */
typedef struct xdbsp_openav_rsp_m2h {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_openav_rsp_m2h_t;

/* E_XDBSP_URAUTH_REQ_H2M */
typedef struct xdbsp_urauth_req_h2m {
    uint32_t utc;  ///< 锁板UTC时间
    uint8_t  tz;   ///< 时区 - 固定为0x50
    uint8_t  type; ///< 特征类型 - 固定密码(0x02)
    ///< 密码为BCD编码方式，如0x12表示数字1和2，
    ///< 遇到非数字值时结束。
    ///< 如密码字段为0x12,0x34,0x5f，表示密码12345。支持虚位密码
    uint8_t passwd[128];
    uint8_t passwd_len;
} xdbsp_urauth_req_h2m_t;

/* E_XDBSP_URAUTH_RSP_M2H */
typedef struct xdbsp_urauth_rsp_m2h {
    uint8_t  auth_result; ///< XDBSP_AUTH_RESULT_SUCCESS
    uint8_t  auth_type;   ///< XDBSP_AUTH_TYPE_ADMIN
    uint8_t  user_type;   ///< 事件类型 XDBSP_USER_TYPE_PASSWORD
    uint16_t user_id; ///< 主板范围: 0-1024, 云用户范围: 1024-2048
} xdbsp_urauth_rsp_m2h_t;

/* E_XDBSP_NETSTA_EVT_M2H */
typedef struct xdbsp_netsta_evt_m2h {
    uint8_t  status; ///< 联网状态 XDBSP_NETSTA_YUN_CONNECTED
    uint32_t utc;    ///< 只有联网状态为已连接云服务器才有效
    uint8_t  tz;     ///< 与获取网络时间接口一致
} xdbsp_netsta_evt_m2h_t;

/* E_XDBSP_SERJPG_REQ_H2M */
typedef struct xdbsp_serjpg_req_h2m {
    uint8_t baudrate; ///< 单位115200bps, XDBSP_BAUDRATE_115200_X1
    uint16_t picsize; ///< 要最大不能超过30KB, 小端字节序，低字节在前
    uint16_t checksum; ///< 图片原始数据的累加和, 取低16位。小端字节序
} xdbsp_serjpg_req_h2m_t;

/* E_XDBSP_SERJPG_RSP_M2H */
typedef struct xdbsp_serjpg_rsp_m2h {
    uint8_t errcode;  ///< XDBSP_SERJPG_ERRCODE_SUCCESS
    uint8_t baudrate; ///< 单位115200bps
} xdbsp_serjpg_rsp_m2h_t;

/* E_XDBSP_SERJPG_EVT_M2H */
typedef struct xdbsp_serjpg_evt_m2h {
    uint8_t  result;   ///< 图传结果 XDBSP_SERJPG_RESULT_SUCCESS
    uint16_t picsize;  ///< 已接收到的图片数据大小
    uint16_t checksum; ///< 已接收到的图片数据校验和
} xdbsp_serjpg_evt_m2h_t;

/* E_XDBSP_AVSTAT_REQ_H2M */
typedef struct xdbsp_avstat_req_h2m {
    uint8_t dummy[6]; ///< zero dummy
} xdbsp_avstat_req_h2m_t;

/* E_XDBSP_AVSTAT_RSP_M2H */
typedef struct xdbsp_avstat_rsp_m2h {
    uint8_t avstat; ///< XDBSP_AVSTAT_STARTED
} xdbsp_avstat_rsp_m2h_t;

/* E_XDBSP_AVSTAT_EVT_M2H */
typedef struct xdbsp_avstat_rsp_m2h xdbsp_avstat_evt_m2h_t;

/* E_XDBSP_SETDAV_REQ_H2M */
typedef struct xdbsp_setdav_req_h2m {
    uint8_t language;       ///< 语音, XDBSP_LANG_CH
    uint8_t spk_vol;        ///< SPK音量 0~31
    uint8_t video_rotation; ///< 无旋转(0x00), 顺时针旋转180°(0x02)
} xdbsp_setdav_req_h2m_t;

/* E_XDBSP_SETDAV_RSP_M2H */
typedef struct xdbsp_setdav_rsp_m2h {
    uint8_t retcode; ///< 0x00: 执行成功, 0x01: 参数错误
} xdbsp_setdav_rsp_m2h_t;

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************/
/* Public Function Prototypes                                               */
/****************************************************************************/

/**
 * @brief Init serial port protocol of doorlock.
 *
 * @param[in] ctx        - The xdbsp context.
 * @param[in] on_cmd     - The cmd receive callback.
 * @param[in] on_tick    - The xdbsp loop tick callback.
 * @param[in] uesr_write - The uart write.
 * @param[in] uesr_read  - The uart read.
 * @param[in] ud         - The xdbsp callback userdata.
 *
 * @return status code that indicates the execution status of the function.
 */
int xdbsp_init(xdbsp_ctx_t     *ctx,
               xdbsp_on_cmd_fn  on_cmd,
               xdbsp_on_tick_fn on_tick,
               xdbsp_write      uesr_write,
               xdbsp_read       uesr_read,
               void            *ud);

/**
 * @brief Deinit serial port protocol of doorlock.
 *
 * @param[in] ctx - The xdbsp context obtained by @ref xdbsp_init.
 */
void xdbsp_fini(xdbsp_ctx_t *ctx);

/**
 * @brief Send dbsp cmd to doorlock.
 *
 * @param[in] ctx    - The xdbsp context.
 * @param[in] id     - The xdbsp cmd id.
 * @param[in] ptrval - The pointer of xdbsp command value.
 *
 * @return status code that indicates the execution status of the function.
 */
int xdbsp_send_cmd(xdbsp_ctx_t *ctx, xdbsp_cmd_id_e id, void *ptrval);

/**
 * @brief The dbsp cmd name.
 *
 * @param[in] id - The xdbsp command id, e.g. E_XDBSP_COMMON_RSP_M2H.
 *
 * @return The cmd name.
 */
const char *xdbsp_cmd_name(xdbsp_cmd_id_e id);

/**
 * @brief The dbsp sendmsg event type name.
 *
 * @param[in] event_type - The event type, e.g. XDBSP_EVENT_TYPE_DOOR_LOCKED
 *
 * @return The event type name.
 */
const char *xdbsp_event_type_name(uint8_t event_type);

/**
 * @brief The dbsp sendmsg event info name of doorlocked.
 *
 * @param[in] event_info - The event type, e.g. XDBSP_EVENT_INFO_DOOR_OUTSIDE
 *
 * @return The event info name.
 */
const char *xdbsp_event_info_name_of_door_locked(uint8_t event_info);

/**
 * @brief The dbsp sendmsg event info name of doorunlocked.
 *
 * @param[in] event_info - The event type, e.g. XDBSP_EVENT_INFO_DOOR_OUTSIDE
 *
 * @return The event info name.
 */
const char *xdbsp_event_info_name_of_door_unlocked(uint8_t event_info);

/**
 * @brief The dbsp sendmsg event info name of alarm.
 *
 * @param[in] event_info - The event info id, e.g. XDBSP_EVENT_INFO_ALARM_00.
 *
 * @return The event info name.
 */
const char *xdbsp_event_info_name_of_alarm(uint8_t event_info);

/**
 * @brief The dbsp sendmsg event info name of rmtunlock.
 *
 * @param[in] event_info - The event info id, e.g. XDBSP_EVENT_INFO_RMTUNLOCK.
 *
 * @return The event info name.
 */
const char *xdbsp_event_info_name_of_rmtunlock(uint8_t event_info);

/**
 * @brief The dbsp sendmsg event info name of tips.
 *
 * @param[in] event_info - The event info id, e.g. XDBSP_EVENT_INFO_TIPS_00.
 *
 * @return The event info name.
 */
const char *xdbsp_event_info_name_of_tips(uint8_t event_info);

/**
 * @brief The dbsp sendmsg event info name.
 *
 * @param[in] event_type - The event type, e.g. XDBSP_EVENT_TYPE_DOOR_LOCKED.
 * @param[in] event_info - The event info id, e.g. XDBSP_EVENT_INFO_DOOR_OUTSIDE.
 *
 * @return The event info name.
 */
const char *xdbsp_event_info_name(uint8_t event_type, uint8_t event_info);

/**
 * @brief The dbsp user type name.
 *
 * @param[in] evt - The event type, e.g. XDBSP_USER_TYPE_DEFAULT
 *
 * @return The user type name.
 */
const char *xdbsp_user_type_name(uint8_t usertype);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* CAMX_XDBSP_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

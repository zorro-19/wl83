/**
 * @file tbl_common_cmd_def.h
 * @author  www.tuya.com
 * @brief 通用对接协议命令定义文件
 * @version 1.0
 * @date 2022-05-12
 * @copyright Copyright 2022-2032 Tuya Inc. All Rights Reserved.
 *
 */

#ifndef _TBL_KIWI_CMD_DEF_H_
#define _TBL_KIWI_CMD_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 ** INCLUDE                                                           **
 **********************************************************************/
#include "tal_queue.h"
#include "tfm_cmd_list.h"


/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/
/**
 * @brief 通用对接使用到的event info定义
 */


/**
 * @brief 通用对接协议命令字定义
 */
typedef enum {
    CMD_KIWI_START_WIFI = 0x01,
    CMD_KIWI_COMMON_ACK = 0x02,
    CMD_KIWI_UPDATE_INFO = 0x03,
    CMD_KIWI_CLOSE_POWER = 0x04,

    CMD_KIWI_CLEAR_DATA = 0x05,
    CMD_KIWI_GET_MODULE_INFO = 0x06,
    CMD_KIWI_SEND_MODULE_INFO = 0x07,
    CMD_KIWI_PRODUCT_TEST = 0x0C,
    CMD_KIWI_PRODUCT_TEST_RESULT = 0x0D,

    CMD_KIWI_GET_GMT_TIME = 0x10,
    CMD_KIWI_SEND_GMT_TIME = 0x11,
    CMD_KIWI_REMOTE_UNLOCK_ACK = 0x12,
    CMD_KIWI_REMOTE_UNLOCK = 0x13,

    CMD_KIWI_STOP_WIFI = 0x1A,
    CMD_KIWI_STOP_WIFI_ACK = 0x1B,
    CMD_KIWI_START_SNAP_PIC = 0x1C,
    CMD_KIWI_START_SNAP_PIC_ACK = 0x1D,

    CMD_KIWI_GET_CHECK_USER_INFO_RESULT = 0x20,
    CMD_KIWI_SEND_CHECK_USER_INFO_RESULT = 0x21,
    CMD_KIWI_WF_STATE = 0x23,

    CMD_KIWI_GET_VIDEO_STATUS = 0x3A,
    CMD_KIWI_SEND_VIDEO_STATUS = 0x3B,

    CMD_KIWI_UPDATE_MCU_STATE = 0x42,
    CMD_KIWI_UPDATE_MCU_STATE_ACK = 0x43,
    CMD_KIWI_UPDATE_CACHE_INFO = 0x44,
    CMD_KIWI_UPDATE_CACHE_INFO_ACK = 0x45,
    CMD_KIWI_GET_DEV_CAP = 0x46,
    CMD_KIWI_GET_DEV_CAP_ACK = 0x47,
    CMD_KIWI_PROACTIVE_VIEW = 0x48,
    CMD_KIWI_PROACTIVE_VIEW_ACK = 0x49,

    CMD_KIWI_GET_VERSION = 0x4A,
    CMD_KIWI_SEND_VERSION = 0x4B,

    CMD_KIWI_USER_CONTROL_ACK = 0x52,
    CMD_KIWI_USER_CONTROL = 0x53,
    CMD_KIWI_USER_CONTROL_FEED_BACK = 0x54,
    CMD_KIWI_USER_CONTROL_FEED_BACK_ACK = 0x55,

    CMD_KIWI_SET_PID = 0xFC,
    CMD_KIWI_GET_PID = 0xFD,
    CMD_KIWI_GET_PID_ACK = 0xFE,

} KW_WF_CMD_E;


#pragma pack(1)

typedef struct {
    UCHAR_T      device[12];
    UCHAR_T      mac[6];
    UCHAR_T      res[6];
} tKIWI_MODULE_INFO;

typedef struct {
    UCHAR_T      protocol_ver;
    UCHAR_T      res;
    USHORT_T     soft_ver;
    USHORT_T     hard_ver;
} tKIWI_VERSION_INFO;



typedef struct {
    UCHAR_T      result;
    UCHAR_T      res[5];
} tKIWI_PROACTIVE_VIEW;


typedef struct {
    UCHAR_T      function;
    UCHAR_T      wifi_style;
    UCHAR_T      res[4];
} tKIWI_DEV_CAP;




typedef struct {
    UCHAR_T    is_effect;
    USHORT_T   member_id;
    TIME_T     effect_tm;
    TIME_T     lose_effect_tm;
    USHORT_T   secret_key_used_time;
    UCHAR_T    secret_key_value[8];
} tDP_SECRET_KEY;


typedef struct {
    UCHAR_T    status;
    USHORT_T   member_id;
    UCHAR_T    secret_key_value[8];
    USHORT_T   unlock_type;
} tDP_CHECK_SECRET_KEY;

typedef struct {
    UCHAR_T      user_type;
    USHORT_T     user_num;
    UCHAR_T      rever[3];
} tKIWI_REMOTE_UNLOCK;

typedef struct {
    USHORT_T     mcu_state_type;
    UINT_T       mcu_state_value;
} tKIWI_MCU_STATE;

typedef struct {
    UCHAR_T      event_type;
    UCHAR_T      event_info;
    UCHAR_T      user_type;
    USHORT_T     user_num;
    UCHAR_T      rever;
} tKIWI_MCU_INFO;

typedef struct {
    UCHAR_T      lenth;
    TIME_T       utc;
    UCHAR_T      time_zone;
    UCHAR_T      feature_type;
    UCHAR_T      feature_value[0];
} tKIWI_CHECK_USER_INFO;


typedef struct {
    UCHAR_T      lenth;
    TIME_T       utc;
    UCHAR_T      event_type;
    UCHAR_T      event_info;
    UCHAR_T      user_type;
    USHORT_T     user_num;
} tKIWI_MCU_CACHE_INFO;


typedef struct {
    THREAD_HANDLE    hand;
    SEM_HANDLE       send_sem;
    QUEUE_HANDLE     send_queue;
} tSEND_KIWI_RECORD;


typedef struct {
    TIME_T      timestamp;
    TY_CMD_S    record_info;
} KIWI_RECORD_QUEUE_MSG_T;


typedef struct {
    UCHAR_T      len;
    UCHAR_T      result;
    UCHAR_T      user_power;
    UCHAR_T      user_type;
    USHORT_T     user_num;
} tKIWI_CHECK_PASS_RESULT;


typedef struct {
    UCHAR_T                    lenth;            // 要添加的解锁方式类型
    UCHAR_T                    opera_type;       // 操作类型
    UCHAR_T                    user_type;        // 用户类型
    USHORT_T                   member_id;        // 成员id
    UCHAR_T                    data[0];          // 包含限制信息和特征数据
} tKIWI_USER_CONTROL_INFO;


typedef struct {
    UCHAR_T                    erro_code;        // 错误码
    UCHAR_T                    opera_type;       // 操作类型
    UCHAR_T                    user_type;        // 用户类型
    USHORT_T                   member_id;        // 成员id
    UCHAR_T                    rsv;
} tKIWI_USER_CONTROL_FEED_BACK;

typedef struct {
    UCHAR_T                   operator_type;     // 执行人员类型
    USHORT_T                  operator_id;       // 执行人员id
    UCHAR_T                   operation_class;   // 操作分类
    UCHAR_T                   opera_type;        // 操作类型
    UCHAR_T                   data_len;          // 数据长度
    USHORT_T                  operation_info;    // 操作信息
    UCHAR_T                   operated_type;     // 被执行人员类型
    USHORT_T                  operated_id;       // 被执行人员id
} tKIWI_LOCAL_RECORD;


typedef struct {
    UCHAR_T      lenth;
    UCHAR_T      pid[0];          // pid数据
} tKIWI_MCU_PID_INFO;


typedef struct {
    UCHAR_T      lenth;
    UCHAR_T      result;
    UCHAR_T      pid[PRODUCT_KEY_LEN];          // pid数据
} tKIWI_MCU_GET_PID_INFO;


#pragma pack()

/***********************************************************************
 ** 几维相关弘定义                                                           **
 **********************************************************************/
#define DATA_COM_LEN_KIWI                    6
#define KIWI_DYN_PASS_LEN                    8u
#define KIWI_RECORD_SEND_QUEUE_SIZE         (16)
#define KIWI_RECORD_RESERVE_MAX_TIME        15000

#define UART_RECV_KIWI_MIN_NUM              (10)  /* 最小接收数据长度 */
#define UART_PROTOCOL_KIWI_HEAD_ONE         (0xAA)     /* 几维协议头0 */
#define UART_PROTOCOL_KIWI_HEAD_TWO         (0x55)     /* 几维协议头1 */
#define KIWI_REFERENCE_TIME                 1599916255    //2020-09-12 21:10:55

#define KIWI_PROTOCOL_VER           0x02
#define KIWI_SOFT_VER               0x0013
#define KIWI_HARD_VER               0x0002




typedef enum {
    SELECT_TYPE_APP,
    SELECT_TYPE_KEY,
} VIDEO_SELECT_TYPE_E;




typedef UCHAR_T UART_KIWI_WF_STATE_E;

#define WF_ST_KIWI_NO_CONFIG                  0x01
#define WF_ST_KIWI_START_CONNECT_ROUTER       0x02
#define WF_ST_KIWI_CONNECT_ROUTER             0x03
#define WF_ST_KIWI_CONNECT_CLOUDE             0x04
#define WF_ST_KIWI_BLE_START                  0x05
#define WF_ST_KIWI_BLE_TIMEOUT                0x06


/***********************************************************************
 ** 涂鸦dp点相关弘定义                                                           **
 **********************************************************************/

#define DPID_RAW_TEM_PASSWORD_ADD                 4
#define DPID_RAW_TEM_PASSWORD_DEL                 5
#define DPID_RAW_TEM_PASSWORD_MODIFY              6


#define DPID_RAW_UNLOCK_METHOD_ADD_BIG            13
#define DPID_RAW_UNLOCK_METHOD_DEL_BIG            14
#define DPID_RAW_UNLOCK_METHOD_MODIFY_BIG         15


#define DPID_RAW_TEM_PASSWORD_ADD_BIG             16
#define DPID_RAW_TEM_PASSWORD_DEL_BIG             17
#define DPID_RAW_TEM_PASSWORD_MODIFY_BIG          18



#define DPID_RAW_SET_SECRET_KEY                   9
#define DPID_RAW_CHECK_SECRET_KEY                 10


#define DPID_ENUM_DOOR_OPEN_CLOSE_STATUS          51

#define DPID_BOOL_DOOR_BELL_FOR_WECHAT            53
#define DPID_DEV_INFO_REPORT                      54


#define DPID_VIDEO_CHANNEL_SELECT_DP              43


#define DPID_VALUE_BATTERY_DRY                    45
#define DPID_VALUE_LITHIUM_BATTERY_DRY            46


#define DPID_BOOL_LOCK_OPEN_CLOSE_STATUS          47



#define DPID_ENUM_ALARM_RECORD                    60

#define DPID_RAW_LOCAL_RECORD_DP                  58
#define DPID_VALUE_ALARM_AND_REMIND               59
#define DPID_VALUE_PASSWORD_UNLOCK                61
#define DPID_RAW_LOCK_STATUS_DP                   62

#define DPID_VALUE_FINGER_PRINT_UNLOCK            63
#define DPID_VALUE_IC_CARD_UNLOCK                 64
#define DPID_VALUE_FACE_UNLOCK                    65
#define DPID_VALUE_PALM_PRINT_UNLOCK              66
#define DPID_VALUE_FINGER_VEIN_UNLOCK             67
#define DPID_VALUE_IRIS_UNLOCK                    68
#define DPID_VALUE_TEMPORARY_UNLOCK               69

#define DPID_VALUE_KEY_UNLOCK                     71
#define DPID_VALUE_MOBILE_PHONE_UNLOCK            72

/***********************************************************************
 ** 状态相关宏定义                                                    **
 **********************************************************************/

typedef UCHAR_T UART_KIWI_USER_CONTROL_ADD_STATE_E;
#define USER_CONTROL_ADD_STATE_START              0x00
#define USER_CONTROL_ADD_STATE_ENTERING           0xFC
#define USER_CONTROL_ADD_STATE_FAILED             0xFD
#define USER_CONTROL_ADD_STATE_CANCEL             0xFE
#define USER_CONTROL_ADD_STATE_SUCCESS            0xFF


typedef UCHAR_T UART_KIWI_USER_CONTROL_RESULT_E;

#define USER_CONTROL_RESULT_SUCCESS             0x00
#define USER_CONTROL_RESULT_FAILED              0x01
#define USER_CONTROL_RESULT_USER_FULL           0x02
#define USER_CONTROL_RESULT_USER_CANCEL         0x03
#define USER_CONTROL_RESULT_TIME_OUT            0x04
#define USER_CONTROL_RESULT_USER_INPUT_FAILED   0x05
#define USER_CONTROL_RESULT_NO_USER             0x06
#define USER_CONTROL_RESULT_USER_EXISTED        0x07
#define USER_CONTROL_RESULT_USER_CANNOT_DELETE  0x08

typedef UCHAR_T UART_KIWI_USER_CONTROL_ADD_FAILED_REASON_E;
#define USER_CONTROL_ADD_FAILED_REASON_TIME_OUT              0x00
#define USER_CONTROL_ADD_FAILED_REASON_INPUT_FAILED          0x01
#define USER_CONTROL_ADD_FAILED_REASON_INPUT_REPEAT          0x02
#define USER_CONTROL_ADD_FAILED_REASON_USER_FULL             0x03
#define USER_CONTROL_ADD_FAILED_REASON_PASSWORD_ERR          0x04
#define USER_CONTROL_ADD_FAILED_REASON_PASSWORD_LEN_ERR      0x05
#define USER_CONTROL_ADD_FAILED_REASON_NOT_SUPPORT           0x06
#define USER_CONTROL_ADD_FAILED_REASON_ENTER_FINGERPRINTS    0x07
#define USER_CONTROL_ADD_FAILED_REASON_BIND_DOOR_CARD        0x08
#define USER_CONTROL_ADD_FAILED_REASON_BIND_FACE             0x09
#define USER_CONTROL_ADD_FAILED_REASON_SIMPLE_PASSWORD       0x0A
#define USER_CONTROL_ADD_FAILED_REASON_RESULT_FAILED         0x0B
#define USER_CONTROL_ADD_FAILED_REASON_USER_CANCEL           0x0C
#define USER_CONTROL_ADD_FAILED_REASON_NO_USER               0x0D
#define USER_CONTROL_ADD_FAILED_REASON_CANNOT_DELETE         0x0E

#define USER_CONTROL_ADD_FAILED_REASON_PARAM_ERROR           0xFE

typedef UCHAR_T UART_KIWI_USER_CONTROL_DEL_E;
#define UART_KIWI_USER_CONTROL_DEL_FAILED                   0x00
#define UART_KIWI_USER_CONTROL_DEL_SUCCESS                  0xFF
#define UART_KIWI_USER_CONTROL_DEL_NO_USER                  0x01
#define UART_KIWI_USER_CONTROL_DEL_CANNOT_DELETE            0x02





typedef UCHAR_T UART_KIWI_UNLOCK_METHOD_ADD_TYPE_E;
#define UNLOCK_METHOD_ADD_TYPE_PASSWORD               0x01
#define UNLOCK_METHOD_ADD_TYPE_DOOR_CARD              0x02
#define UNLOCK_METHOD_ADD_TYPE_FINGER_PRINT           0x03
#define UNLOCK_METHOD_ADD_TYPE_FACE                   0x04
#define UNLOCK_METHOD_ADD_TYPE_PALM_PRINT             0x05
#define UNLOCK_METHOD_ADD_TYPE_FINGER_VEIN            0x06


typedef UCHAR_T UART_KIWI_VIDEO_STATE_E;
#define MCU_STATE_TYPE_VIDEO_START              0x02
#define MCU_STATE_TYPE_VIDEO_END                0x01


typedef UCHAR_T REMOTE_UNLOCK_STAT_ENUM_TYPE_E;
#define      REMOTE_UNLOCK_STAT_SUCCESS           0x00
#define      REMOTE_UNLOCK_STAT_FAILED            0x01
#define      REMOTE_UNLOCK_STAT_ERROR             0x05

typedef USHORT_T UART_KIWI_MCU_STATE_TYPE_E;
#define MCU_STATE_TYPE_BATTERY_MCU              0x1006
#define MCU_STATE_TYPE_BATTERY_CAT              0x100A
#define MCU_STATE_TYPE_SENSOR_FAULT             0x1208
#define MCU_STATE_TYPE_BATTERY_ATTR             0x1209
#define MCU_STATE_TYPE_SHIELD                   0x110F


typedef UCHAR_T UART_KIWI_MCU_INFO_EVENT_TYPE_E;
#define MCU_KIWI_INFO_DOOR_LOCK                         0x00
#define MCU_KIWI_INFO_DOOR_UNLOCK                       0x01
#define MCU_KIWI_INFO_ALARM                             0x02
#define MCU_KIWI_INFO_UNLOCK_REQ                        0x03
#define MCU_KIWI_INFO_REMIND                            0x04


typedef UCHAR_T UART_KIWI_MCU_INFO_USER_TYPE_E;
#define MCU_KIWI_INFO_USER_DEFAULT                      0x00
#define MCU_KIWI_INFO_USER_FINGER_PRINT                 0x01
#define MCU_KIWI_INFO_USER_PASSWORD                     0x02
#define MCU_KIWI_INFO_USER_IC_CARD                      0x03
#define MCU_KIWI_INFO_USER_KEY                          0x04
#define MCU_KIWI_INFO_USER_MOBILE_PHONE                 0x05
#define MCU_KIWI_INFO_USER_FACE                         0x06
#define MCU_KIWI_INFO_PALM_PRINT                        0x07
#define MCU_KIWI_INFO_IRIS                              0x08
#define MCU_KIWI_INFO_TEMPORARY                         0x09
#define MCU_KIWI_INFO_FINGER_VEIN                       0x0A
#define MCU_KIWI_INFO_PALM_VEIN                         0x0B

typedef UCHAR_T UART_KIWI_MCU_INFO_EVENT_INFO_E;
#define MCU_KIWI_EVENT_INFO_LOCK_DAMAGGED_ALARM         0x00
#define MCU_KIWI_EVENT_INFO_FORCE_OPEN_DOOR_ALARM       0x01
#define MCU_KIWI_EVENT_INFO_FINGER_PRINT_TRY_FREEZE     0x02
#define MCU_KIWI_EVENT_INFO_PASSWORD_TRY_FREEZE         0x03
#define MCU_KIWI_EVENT_INFO_IC_CARD_TRY_FREEZE          0x04
#define MCU_KIWI_EVENT_INFO_KEY_TRY_FREEZE              0x05
#define MCU_KIWI_EVENT_INFO_REMOTE_TRY_FREEZE           0x06


#define MCU_KIWI_EVENT_INFO_STRESS_UNLOCK_ALARM         0x08
#define MCU_KIWI_EVENT_INFO_TESLA_UNLOCK_ALARM          0x09
#define MCU_KIWI_EVENT_INFO_WANTONLY_UNLOCK_FREEZE      0x0A
#define MCU_KIWI_EVENT_INFO_FACE_TRY_ALARM              0x0B
#define MCU_KIWI_EVENT_INFO_PALM_PRINT_TRY_ALARM        0x0C
#define MCU_KIWI_EVENT_INFO_STAY_ALARM                  0x0D
#define MCU_KIWI_EVENT_INFO_FIRE_ALARM                  0x0E
#define MCU_KIWI_EVENT_INFO_STRANGER_ALARM              0x0F
#define MCU_KIWI_EVENT_INFO_NO_LIVING_FACE_ALARM        0x10
#define MCU_KIWI_EVENT_INFO_HOLD_ALARM                  0x11

#define MCU_KIWI_EVENT_INFO_TAILGATING_ALARM            0x12
#define MCU_KIWI_EVENT_INFO_SOMEONE_WANDERINFG_ARALM    0x13
#define MCU_KIWI_EVENT_INFO_FINGER_PRINT_TRY_ALARM      0x14
#define MCU_KIWI_EVENT_INFO_PASSWORD_TRY_ALARM          0x15
#define MCU_KIWI_EVENT_INFO_IC_CARD_TRY_ALARM           0x16
#define MCU_KIWI_EVENT_INFO_SYSTEM_LOCK_ALARM           0x17
#define MCU_KIWI_EVENT_INFO_DEVICE_ABNORMAL_ALARM       0x18
#define MCU_KIWI_EVENT_INFO_FACE_TRY_FREEZE             0x19
#define MCU_KIWI_EVENT_INFO_PALM_PRINT_TRY_FREEZE       0x1A
#define MCU_KIWI_EVENT_INFO_IRIS_TRY_FREEZE             0x1B
#define MCU_KIWI_EVENT_INFO_FINGER_VEIN_TRY_FREEZE      0x1C
#define MCU_KIWI_EVENT_INFO_PALM_VEIN_TRY_FREEZE        0x1D
#define MCU_KIWI_EVENT_INFO_IRIS_TRY_ALARM              0x1E
#define MCU_KIWI_EVENT_INFO_FINGER_VEIN_TRY_ALARM       0x1F
#define MCU_KIWI_EVENT_INFO_PALM_VEIN_TRY_ALARM         0x20
#define MCU_KIWI_EVENT_INFO_HIGH_TEMP_ALARM             0x21
#define MCU_KIWI_EVENT_INFO_SMOKE_ALARM                 0x22

typedef UCHAR_T UART_KIWI_EVENT_REMIND_INFO_E;
#define MCU_KIWI_REMIND_INFO_FORGOT_KEY                 0x00
#define MCU_KIWI_REMIND_INFO_LOCK_DOOR                  0x01
#define MCU_KIWI_REMIND_INFO_KNOCK_DOOR                 0x02
#define MCU_KIWI_REMIND_INFO_SOS                        0x03
#define MCU_KIWI_REMIND_INFO_NOT_CLOSE_DOOR             0x04
#define MCU_KIWI_REMIND_INFO_DOOR_LOCKED                0x05
#define MCU_KIWI_REMIND_INFO_DOOR_UNLOCKED              0x06
#define MCU_KIWI_REMIND_INFO_NORMALLY_OPEN              0x07
#define MCU_KIWI_REMIND_INFO_LOW_BATTERY                0x08
#define MCU_KIWI_REMIND_INFO_ADD_USER                   0x09
#define MCU_KIWI_REMIND_INFO_DEL_USER                   0x0A
#define MCU_KIWI_REMIND_INFO_INIT_USER                  0x0B
#define MCU_KIWI_REMIND_INFO_DOOR_BELL                  0x0C
#define MCU_KIWI_REMIND_INFO_DEL_ALL_USER               0x0D
#define MCU_KIWI_REMIND_INFO_TIMED_LOCK                 0x0E
#define MCU_KIWI_REMIND_INFO_PROACT_VIEW                0x0F
#define MCU_KIWI_REMIND_INFO_BUTTON_UNLOCK              0x10
#define MCU_KIWI_REMIND_INFO_HANDLE_UNLOCK              0x11
#define MCU_KIWI_REMIND_INFO_BUTTON_LOCK                0x12
#define MCU_KIWI_REMIND_INFO_HANDLE_LOCK                0x13
#define MCU_KIWI_REMIND_INFO_NORMALLY_CLOSE             0x14
#define MCU_KIWI_REMIND_INFO_COVER_OPENED               0x15
#define MCU_KIWI_REMIND_INFO_COVER_CLOSED               0x16
#define MCU_KIWI_REMIND_INFO_DOOR_NOT_CLOSED            0x17
#define MCU_KIWI_REMIND_INFO_LAMP_OPENED                0x18
#define MCU_KIWI_REMIND_INFO_LAMP_CLOSED                0x19
#define MCU_KIWI_REMIND_INFO_TONGGUE_BLOCKED            0x1A
#define MCU_KIWI_REMIND_INFO_TONGGUE_RETRACT_FAILED     0x1B
#define MCU_KIWI_REMIND_INFO_EMERGEM_UNLOCK             0x1C

typedef UCHAR_T KIWI_TRIGGER_TYPE_E;
#define KIWI_TRIGGER_TYPE_NONE           0x00
#define KIWI_TRIGGER_TYPE_PHOTO          0x01
#define KIWI_TRIGGER_TYPE_STREAM         0x02
#define KIWI_TRIGGER_TYPE_MAX            0x03


typedef USHORT_T KIWI_TRIGGER_EVENT_TYPE_E;
#define TRIGGER_EVENT_TYPE_ANTI_PRY                          0x0000
#define TRIGGER_EVENT_TYPE_REMOTE_UNLOCK_REQ                 0x0001
#define TRIGGER_EVENT_TYPE_FINGER_PRINT_ALARM                0x0002
#define TRIGGER_EVENT_TYPE_PASSWORD_ALARM                    0x0003
#define TRIGGER_EVENT_TYPE_IC_CARD_ALARM                     0x0004
#define TRIGGER_EVENT_TYPE_FACE_ALARM                        0x0005
#define TRIGGER_EVENT_TYPE_PALM_PRINT_ALARM                  0x0006
#define TRIGGER_EVENT_TYPE_FINGER_VEIN_ALARM                 0x0007
#define TRIGGER_EVENT_TYPE_FINGER_PRINT_UNLOCK               0x0008
#define TRIGGER_EVENT_TYPE_PASSWORD_UNLOCK                   0x0009
#define TRIGGER_EVENT_TYPE_IC_CARD_UNLOCK                    0x000A
#define TRIGGER_EVENT_TYPE_FACE_UNLOCK                       0x000B
#define TRIGGER_EVENT_TYPE_PALM_PRINT_UNLOCK                 0x000C
#define TRIGGER_EVENT_TYPE_FINGER_VEIN_UNLOCK                0x000D
#define TRIGGER_EVENT_TYPE_TEMPORARY_UNLOCK                  0x000E
#define TRIGGER_EVENT_TYPE_TRENDS_UNLOCK                     0x000F
#define TRIGGER_EVENT_TYPE_REMOTE_UNLOCK                     0x0010
#define TRIGGER_EVENT_TYPE_OFFLINE_PASSWORD_UNLOCK           0x0011
#define TRIGGER_EVENT_TYPE_DOOR_BELL                         0x0012
#define TRIGGER_EVENT_TYPE_LOW_ELECTRICITY_ALARM             0x0014
#define TRIGGER_EVENT_TYPE_KEY_INSERT_ALARM                  0x0015



#define TRIGGER_EVENT_TYPE_IRIS_UNLOCK                       0x001D
#define TRIGGER_EVENT_TYPE_KEY_UNLOCK                        0x001E



#define TRIGGER_EVENT_TYPE_LOCK_DAMAGGED_ALARM         0x1000
#define TRIGGER_EVENT_TYPE_FORCE_OPEN_DOOR_ALARM       0x1001
#define TRIGGER_EVENT_TYPE_FINGER_PRINT_TRY_FREEZE     0x1002
#define TRIGGER_EVENT_TYPE_PASSWORD_TRY_FREEZE         0x1003
#define TRIGGER_EVENT_TYPE_IC_CARD_TRY_FREEZE          0x1004
#define TRIGGER_EVENT_TYPE_KEY_TRY_FREEZE              0x1005
#define TRIGGER_EVENT_TYPE_REMOTE_TRY_FREEZE           0x1006

#define TRIGGER_EVENT_TYPE_STRESS_UNLOCK_ALARM         0x1008
#define TRIGGER_EVENT_TYPE_TESLA_UNLOCK_ALARM          0x1009
#define TRIGGER_EVENT_TYPE_WANTONLY_UNLOCK_FREEZE      0x100A
#define TRIGGER_EVENT_TYPE_FACE_TRY_ALARM              0x100B
#define TRIGGER_EVENT_TYPE_PALM_PRINT_TRY_ALARM        0x100C
#define TRIGGER_EVENT_TYPE_STAY_ALARM                  0x100D
#define TRIGGER_EVENT_TYPE_FIRE_ALARM                  0x100E
#define TRIGGER_EVENT_TYPE_STRANGER_ALARM              0x100F
#define TRIGGER_EVENT_TYPE_NO_LIVING_FACE_ALARM        0x1010
#define TRIGGER_EVENT_TYPE_HOLD_ALARM                  0x1011
#define TRIGGER_EVENT_TYPE_TAILGATING_ALARM            0x1012
#define TRIGGER_EVENT_TYPE_SOMEONE_WANDERINFG_ARALM    0x1013
#define TRIGGER_EVENT_TYPE_FINGER_PRINT_TRY_ALARM      0x1014
#define TRIGGER_EVENT_TYPE_PASSWORD_TRY_ALARM          0x1015
#define TRIGGER_EVENT_TYPE_IC_CARD_TRY_ALARM           0x1016
#define TRIGGER_EVENT_TYPE_SYSTEM_LOCK_ALARM           0x1017
#define TRIGGER_EVENT_TYPE_DEVICE_ABNORMAL_ALARM       0x1018
#define TRIGGER_EVENT_TYPE_FACE_TRY_FREEZE             0x1019
#define TRIGGER_EVENT_TYPE_PALM_PRINT_TRY_FREEZE       0x101A
#define TRIGGER_EVENT_TYPE_IRIS_TRY_FREEZE             0x101B
#define TRIGGER_EVENT_TYPE_FINGER_VEIN_TRY_FREEZE      0x101C
#define TRIGGER_EVENT_TYPE_PALM_VEIN_TRY_FREEZE        0x101D
#define TRIGGER_EVENT_TYPE_IRIS_TRY_ALARM              0x101E
#define TRIGGER_EVENT_TYPE_FINGER_VEIN_TRY_ALARM       0x101F
#define TRIGGER_EVENT_TYPE_PALM_VEIN_TRY_ALARM         0x1020
#define TRIGGER_EVENT_TYPE_HIGH_TEMP_ALARM             0x1021
#define TRIGGER_EVENT_TYPE_SMOKE_ALARM                 0x1022

typedef USHORT_T UART_KIWI_MCU_REMIND_TYPE_E;
#define REMIND_TYPE_FORGOT_KEY                 0x1000
#define REMIND_TYPE_LOCK_DOOR                  0x1001
#define REMIND_TYPE_KNOCK_DOOR                 0x1002
#define REMIND_TYPE_SOS                        0x1003
#define REMIND_TYPE_NOT_CLOSE_DOOR             0x1004
#define REMIND_TYPE_DOOR_LOCKED                0x1005
#define REMIND_TYPE_DOOR_UNLOCKED              0x1006
#define REMIND_TYPE_NORMALLY_OPEN              0x1007
#define REMIND_TYPE_LOW_BATTERY                0x1008
#define REMIND_TYPE_ADD_USER                   0x1009
#define REMIND_TYPE_DEL_USER                   0x100A
#define REMIND_TYPE_INIT_USER                  0x100B
#define REMIND_TYPE_DOOR_BELL                  0x100C
#define REMIND_TYPE_DEL_ALL_USER               0x100D
#define REMIND_TYPE_TIMED_LOCK                 0x100E
#define REMIND_TYPE_PROACT_VIEW                0x100F
#define REMIND_TYPE_BUTTON_UNLOCK              0x1010
#define REMIND_TYPE_HANDLE_UNLOCK              0x1011
#define REMIND_TYPE_BUTTON_LOCK                0x1012
#define REMIND_TYPE_HANDLE_LOCK                0x1013
#define REMIND_TYPE_NORMALLY_CLOSE             0x1014
#define REMIND_TYPE_COVER_OPENED               0x1015
#define REMIND_TYPE_COVER_CLOSED               0x1016
#define REMIND_TYPE_DOOR_NOT_CLOSED            0x1017
#define REMIND_TYPE_LAMP_OPENED                0x1018
#define REMIND_TYPE_LAMP_CLOSED                0x1019
#define REMIND_TYPE_TONGGUE_BLOCKED            0x101A
#define REMIND_TYPE_TONGGUE_RETRACT_FAILED     0x101B
#define REMIND_TYPE_EMERGEM_UNLOCK             0x101C



VOID send_kiwi_common_result(UCHAR_T cmd,  UCHAR_T first, UCHAR_T second);





#ifdef __cplusplus
}
#endif

#endif

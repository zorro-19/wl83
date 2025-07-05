/**
 * @file tbl_lock_kiwi_password.h
 * @author www.tuya.com
 * @brief 休眠唤醒
 * @version 1.0
 * @date 2023-03-13
 * @copyright Copyright (c) tuya.inc 2021
 * Provides a serial port service interface that supports multithreaded calls
 */
#ifndef __TDL_LOCK_KIWI_PASSWOARD_H__
#define __TDL_LOCK_KIWI_PASSWOARD_H__

#ifdef __cplusplus
extern "C" {
#endif


#define    MAX_PASS_WORAD_COUNT          (10)
#define    KIWI_PASS_FILE_NAME           "kiwi_pw"
#define    MAX_PASS_WORAD_LEN            32


#pragma pack(1)


typedef struct {
    UINT_T startTime; // 每天生效的开始时间
    UINT_T endTime;   // 每天生效的结束时间
    UINT_T workingDay;    // 周循环生效的日期
    UINT_T allDay;        // 是否全天有效 TRUE是全天有效
} tTUYA_KIWI_PASS_CYCLE_INFO_V3;



typedef struct {
    UINT_T effectiveTime;     // 开始生效时间
    UINT_T invalidTime;       // 失效时间
    UINT_T sn;                // 硬件编号
    UINT_T tyNum;             // 云端编号
    UINT_T phase;             // 密码状态
    UINT_T password_len;      // 解码后密码长度
    UCHAR_T password_dec[MAX_PASS_WORAD_LEN]; // 解码后的密码
    UINT_T availTime;         // 可使用的次数, 0:多次 1：1次
    tTUYA_KIWI_PASS_CYCLE_INFO_V3  cycleInfo;
} tTUYA_KIWI_PASS_BODY_INFO_V3;


typedef struct {
    BOOL_T isUsed;            // 表示该内存是否已经使用
    tTUYA_KIWI_PASS_BODY_INFO_V3  bodyInfo;
} tTUYA_KIWI_PASS_INFO_V3;




typedef struct {
    UINT_T count; //已有的密码个数
    tTUYA_KIWI_PASS_INFO_V3 passInfo[MAX_PASS_WORAD_COUNT];
} tTUYA_KIWI_PASS_LIST_V3;


typedef struct {
    UINT_T    effectiveTime;     // 开始生效时间
    UINT_T    invalidTime;       // 失效时间
    UCHAR_T   loopmode;          // 循环方式
    UCHAR_T   loopflag[4];       // 循环标志
    UCHAR_T   starthour;         // 每天开始的小时
    UCHAR_T   startmin;          // 每天开始的分钟
    UCHAR_T   endhour;           // 每天结束的小时
    UCHAR_T   endmin;            // 每天结束的分钟
} tPASS_WOARD_TIME_INFO;



typedef struct {
    USHORT_T                        tyNum;    // 云端预分配编号
    UCHAR_T                         phase;    // 密码状态
    tPASS_WOARD_TIME_INFO           timeInfo; // 时效性
    UCHAR_T                         availTime;// 生效时次数
    UCHAR_T                         len;      // 密码字节数
    UCHAR_T                         passwordInfo[MAX_PASS_WORAD_LEN]; // 密码
} tTUYA_KIWI_DP_ADD_PASS_WOARD;

typedef struct {
    UCHAR_T                         sn;       // 硬件id
    UCHAR_T                         phase;    // 密码状态
    tPASS_WOARD_TIME_INFO           timeInfo; // 时效性
    UCHAR_T                         availTime;// 生效时次数
    UCHAR_T                         len;      // 密码字节数
    UCHAR_T                         passwordInfo[MAX_PASS_WORAD_LEN]; // 密码
} tTUYA_KIWI_DP_MODIFY_PASS_WOARD;

typedef struct {
    USHORT_T                        sn;       // 硬件id
    UCHAR_T                         phase;    // 密码状态
    tPASS_WOARD_TIME_INFO           timeInfo; // 时效性
    UCHAR_T                         availTime;// 生效时次数
    UCHAR_T                         len;      // 密码字节数
    UCHAR_T                         passwordInfo[MAX_PASS_WORAD_LEN]; // 密码
} tTUYA_KIWI_DP_MODIFY_PASS_WOARD_BIG;



typedef struct {
    UCHAR_T                 pw_len;      // len of the password
    UCHAR_T                 *password;   // the ASCII of password
    TIME_T                  utc;         // 当前UTC时间
    UCHAR_T                 time_zone;   // 时区
    UCHAR_T                 feature_type; // 特征类型
} tTUYA_KIWI_CHECK_PASS_INFO_V3;

typedef struct {
    UCHAR_T                 result;     // 验证结果
    UCHAR_T                 user_power; // 用户权限
    UCHAR_T                 user_type;  // 用户类型
    USHORT_T                user_id;    // 用户id
} tTUYA_KIWI_CHECK_PASS_RESULT_V3;


typedef struct {
    UCHAR_T                    unlock_method;    // 要添加的解锁方式类型
    UCHAR_T                    cur_stage;        // 当前阶段
    UCHAR_T                    member_type;      // 成员类型
    USHORT_T                   member_id;        // 成员id
    USHORT_T                   sn;               // 硬件id
    tPASS_WOARD_TIME_INFO      timeInfo;          // 时效性
    UCHAR_T                    effect_cnt;        // 生效次数
    UCHAR_T                    pw_len;            // 密码长度
    UCHAR_T                    passwordInfo[0];   // 密码内容 + msgid
} tTUYA_KIWI_DP_UNLOCK_METHOD_ADD_BIG;

typedef struct {
    UCHAR_T                    unlock_method;    // 要添加的解锁方式类型
    UCHAR_T                    cur_stage;        // 当前阶段
    UCHAR_T                    member_type;      // 成员类型
    USHORT_T                   member_id;        // 成员id
    USHORT_T                   sn;               // 硬件id
    UCHAR_T                    entry_cnt;        // 录入需要的次数
    UCHAR_T                    state;            // 回复云端状态
    USHORT_T                   msg_id;            // 与云端交互的消息id
} tTUYA_KIWI_DP_UNLOCK_METHOD_ADD_BIG_ACK;


typedef struct {
    UCHAR_T                    unlock_method;    // 解锁方式类型
    UCHAR_T                    cur_stage;        // 当前阶段
    UCHAR_T                    admin_tag;        // 管理员标记
    USHORT_T                   member_id;        // 成员id
    USHORT_T                   sn;               // 硬件id
    UCHAR_T                    del_tag;          // 删除标志
} tTUYA_KIWI_DP_UNLOCK_METHOD_DEL_BIG;

typedef struct {
    UCHAR_T                    unlock_method;    // 解锁方式类型
    UCHAR_T                    cur_stage;        // 当前阶段
    UCHAR_T                    admin_tag;        // 管理员标记
    USHORT_T                   member_id;        // 成员id
    USHORT_T                   sn;               // 硬件id
    UCHAR_T                    del_tag;          // 删除标志
    UCHAR_T                    modify_status;    // 修改后的状态
} tTUYA_KIWI_DP_UNLOCK_METHOD_DEL_BIG_ACK;


typedef struct {
    UCHAR_T                    switch_number;    // 切换编号
} tTUYA_KIWI_DP_SELECT_VIDEO_CHANNEL;


#pragma pack()


OPERATE_RET tuya_kiwi_password_init(VOID);





#ifdef __cplusplus
} // extern "C"
#endif
#endif // __TAL_GPIO_H__



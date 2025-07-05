#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "board_config.h"


#define CONFIG_DEBUG_ENABLE                             //打印开关

#define CONFIG_RTOS_STACK_CHECK_ENABLE                  //是否启用定时检查任务栈
// #define CONFIG_MEM_LEAK_CHECK_ENABLE                 //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)

#define CONFIG_PCM_ENC_ENABLE
// #define CONFIG_AEC_ENC_ENABLE
#define CONFIG_DNS_ENC_ENABLE
#define CONFIG_AAC_DEC_ENABLE
#define CONFIG_SBC_DEC_ENABLE
#define CONFIG_SBC_ENC_ENABLE
#define CONFIG_MSBC_DEC_ENABLE
#define CONFIG_MSBC_ENC_ENABLE
#define CONFIG_CVSD_DEC_ENABLE
#define CONFIG_CVSD_ENC_ENABLE
#define CONFIG_VIRTUAL_DEV_ENC_ENABLE
#define CONFIG_NEW_M4A_DEC_ENABLE


//*********************************************************************************//
//                                  BT_BLE配置                                     //
//*********************************************************************************//
#define BT_EMITTER_EN                               1
#define BT_RECEIVER_EN                              2

#define TCFG_BT_MODE                                BT_NORMAL

#define TCFG_USER_BT_CLASSIC_ENABLE                 1   //经典蓝牙功能
#define TCFG_USER_BLE_ENABLE                        0   //BLE功能使能
#define TCFG_USER_EMITTER_ENABLE                    1   //蓝牙发射功能
#define TCFG_BT_SNIFF_ENABLE                        1
#define TCFG_BT_SUPPORT_MUSIC_VOL_SYNC              0   //音量同步
#define TCFG_BT_SUPPORT_DISPLAY_BAT                 1   //电池电量同步显示功能
#define TCFG_SPP_TRANS_DATA_EN                      1   //SPP数传demo
#define TCFG_BT_SUPPORT_AAC                         0   //蓝牙AAC格式支持
#define TCFG_BT_DUAL_CONN_ENABLE                    1   //经典蓝牙支持同时连接2台设备
#define TCFG_BT_SUPPORT_RECEIVER_AUTO_A2DP_START    1   //接收器器连上后自动打开A2DP流
#define TCFG_BT_ENABLE_AUTO_RECONNECT               0   //打开蓝牙自动回连上一个设备

#define TCFG_BT_SUPPORT_PROFILE_SPP                 1
#define TCFG_BT_SUPPORT_PROFILE_HFP                 1
#define TCFG_BT_SUPPORT_PROFILE_A2DP                1
#define TCFG_BT_SUPPORT_PROFILE_AVCTP               1
#define TCFG_BT_SUPPORT_PROFILE_HID                 0
#define TCFG_BT_SUPPORT_PROFILE_PNP                 0
#define TCFG_BT_SUPPORT_PROFILE_PBAP                0
#define TCFG_BT_SUPPORT_PROFILE_PAN                 0
#define TCFG_BT_SUPPORT_PROFILE_MAP                 0
#define TCFG_BT_SUPPORT_PROFILE_HFP_AG              1


#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#endif


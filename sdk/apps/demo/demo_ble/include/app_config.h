#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "board_config.h"

#define CONFIG_DEBUG_ENABLE                             //打印开关

#define CONFIG_RTOS_STACK_CHECK_ENABLE                  //是否启用定时检查任务栈
// #define CONFIG_MEM_LEAK_CHECK_ENABLE                 //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)


//*********************************************************************************//
//                                  BT_BLE配置                                     //
//*********************************************************************************//
#ifdef CONFIG_BT_ENABLE

#define TCFG_BT_MODE                                BT_NORMAL   //BT_BQB

#define TCFG_USER_BLE_ENABLE                        1   //BLE功能使能
#define TCFG_USER_BT_CLASSIC_ENABLE                 0   //经典蓝牙功能

#if TCFG_USER_BLE_ENABLE
//BLE DEMO选择
#define TCFG_BLE_HID_EN                             0   //从机 hid
#define TCFG_TRANS_DATA_EN                          1   //从机 传输数据
#define TCFG_BLE_MASTER_CENTRAL_EN                  0   //主机 client角色
#define TCFG_TRANS_MULTI_BLE_EN                     0   //多机通讯
#define TCFG_BLE_MESH_ENABLE                        0   //mesh测试demo
#define TCFG_NONCONN_24G_EN                         0   //2.4g加密通讯

#if (TCFG_TRANS_MULTI_BLE_EN + TCFG_BLE_HID_EN + TCFG_BLE_MASTER_CENTRAL_EN + TCFG_TRANS_DATA_EN + TCFG_BLE_MESH_ENABLE + TCFG_NONCONN_24G_EN > 1)
#error "they can not enable at the same time,just select one!!!"
#endif

#define TCFG_BLE_SECURITY_EN                        1   //配对加密使能

#if TCFG_TRANS_MULTI_BLE_EN
#define TCFG_TRANS_MULTI_BLE_SLAVE_NUMS             1
#define TCFG_TRANS_MULTI_BLE_MASTER_NUMS            2
#endif

#endif

#endif

#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#endif


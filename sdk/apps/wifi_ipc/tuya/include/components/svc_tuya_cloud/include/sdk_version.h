/***********************************************************
*  File: sdk_version.h
*  Author:
*  Date:
***********************************************************/
#ifndef _SDK_VERSION_H
#define _SDK_VERSION_H

#include "tuya_iot_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
IOT_BV(BS_VER) 30.00 < - > IOT_SDK 4.1.0
IOT_BV(BS_VER) 30.01 < - > IOT_SDK 4.1.1 < - > RTL8170 2.0.0
IOT_BV(BS_VER) 30.02 < - > IOT_SDK 4.1.2
IOT_BV(BS_VER) 30.03 < - > IOT_SDK 4.1.3
IOT_BV(BS_VER) 30.04 < - > IOT_SDK 4.1.4 < - > RTL8170 2.0.1
IOT_BV(BS_VER) 30.05 < - > IOT_SDK 4.1.5


IOT_BV(BS_VER) 40.00 < - > IOT_SDK 4.2.0

*/

#define BS_VER "40.00"

#if (TUYA_MQ_VERSION&TUYA_MQ_V23)
#define PT_VER "2.3"
#else
#define PT_VER "2.2"
#endif

#if (TUYA_LAN_VERSION&TUYA_LAN_V35)
#define LAN_PRO_VER "3.5"   //必须3.3版本及以上才支持局域网加密功能
#else
#define LAN_PRO_VER "3.3"
#endif

//1.0.0:启用CID机制,固件升级启用4.1
//1.0.1:APP优化流程
//1.0.2:增加mbid，用于群组控制
//1.0.3:OTA channel升级（该升级处理不可跳过）
//1.0.4:支持动态增删OTA channel（1.0.3的处理可以移除）
//1.0.5:支持mqtt和蓝牙通道同时在线时;互斥上报DP业务;云端对蓝牙上报数据不再过滤(解决数据去重问题).
#define CAD_VER "1.0.5"
#define CD_VER "1.0.0" //固件支持mqtt消息确认


#if defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE==1)
#define DEV_ATTR_THINGCONFIG        (1 << 0)
#else
#define DEV_ATTR_THINGCONFIG        (0)
#endif

#define DEV_ATTR_LOCAL_DEV_DP_QUERY           (1<<1)

#if defined(ENABLE_LOCAL_LINKAGE) && (ENABLE_LOCAL_LINKAGE==1)
#define DEV_ATTR_LOCAL_SCENE_LINKAGE      (1<<2)
#else
#define DEV_ATTR_LOCAL_SCENE_LINKAGE      (0)
#endif


#if defined(WIFI_CONTROL_SUPPORT) && (WIFI_CONTROL_SUPPORT==1)
#define DEV_WIFI_SCAN_SUPPORT             (1<<3)
#else
#define DEV_WIFI_SCAN_SUPPORT             (0)
#endif

#if defined(ENABLE_GOOGLE_LOCAL_HOME) && (ENABLE_GOOGLE_LOCAL_HOME==1)
#define DEV_ATTR_GOOGLE_LOCAL_HOME           (1<<4)
#else
#define DEV_ATTR_GOOGLE_LOCAL_HOME           (0<<4)
#endif

#if defined(ENABLE_WIFI_PEGASUS) && (ENABLE_WIFI_PEGASUS==1)
#define DEV_ATTR_PEGASUS_CONFIG     (1 << 5)
#else
#define DEV_ATTR_PEGASUS_CONFIG     (0)
#endif

#if defined(ENABLE_BT_SERVICE) && (ENABLE_BT_SERVICE==1)
#define DEV_ATTR_BLT_CONTROL        (1 << 6)
#else
#define DEV_ATTR_BLT_CONTROL        (0)
#endif


#if defined(ENABLE_ALARM) && (ENABLE_ALARM==1)
#define DEV_ATTR_HOME_SECURITY           (1<<7)
#else
#define DEV_ATTR_HOME_SECURITY           (0<<7)
#endif



#if defined(ENABLE_ASTRO_TIMER) && (ENABLE_ASTRO_TIMER==1)
#define DEV_ATTR_ASTRO_TIMER                (1<<9)
#else
#define DEV_ATTR_ASTRO_TIMER                (0)
#endif

#if defined(ENABLE_WIFI_PROTECT) && (ENABLE_WIFI_PROTECT==1)
#define DEV_ATTR_WIFI_PROTECT               (1<<12)
#else
#define DEV_ATTR_WIFI_PROTECT               (0)
#endif


#define DEV_ATTR_OTA                (1<<11)

#if defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE==1)
#define DEV_ATTR_AP_OTA                (1<<13)
#else
#define DEV_ATTR_AP_OTA                (0)
#endif

//设备属性,采用按位与方式
#define DEV_ATTRIBUTE               (DEV_ATTR_THINGCONFIG | DEV_ATTR_LOCAL_DEV_DP_QUERY | DEV_ATTR_LOCAL_SCENE_LINKAGE | DEV_WIFI_SCAN_SUPPORT | DEV_ATTR_BLT_CONTROL | DEV_ATTR_GOOGLE_LOCAL_HOME | DEV_ATTR_ASTRO_TIMER | DEV_ATTR_PEGASUS_CONFIG | DEV_ATTR_WIFI_PROTECT | DEV_ATTR_AP_OTA)


#if defined(ENABLE_IOT_DEBUG)
#define DEV_ATTR_IOT_DEBUG ENABLE_IOT_DEBUG
#else
#define DEV_ATTR_IOT_DEBUG 0
#endif

#if defined(KV_FILE)
#define DEV_ATTR_KV_FILE KV_FILE
#else
#define DEV_ATTR_KV_FILE 0
#endif

#if defined(RELIABLE_TRANSFER)
#define DEV_ATTR_RELIABLE_TRANSFER RELIABLE_TRANSFER
#else
#define DEV_ATTR_RELIABLE_TRANSFER 0
#endif


#define INT2STR(NUM) #NUM
#define I2S(R) INT2STR(R)

#define SDK_INFO_1 "< TuyaOS V:"IOT_SDK_VER" BS:"BS_VER"_PT:"PT_VER"_LAN:"LAN_PRO_VER"_CAD:"CAD_VER"_CD:"CD_VER" >"
#define SDK_INFO_2 "< BUILD AT:"BUILD_DATE"_"BUILD_TIME" BY "GIT_USER" FOR "PROJECT_NAME" AT "TARGET_PLATFORM" >"
#define SDK_IOT_ATTR "IOT DEFS <"\
" WIFI_GW:"I2S(ENABLE_WIFI_SERVICE)\
" DEBUG:"I2S(DEV_ATTR_IOT_DEBUG)\
" KV_FILE:"I2S(DEV_ATTR_KV_FILE)\
" LITTLE_END:"I2S(LITTLE_END)\
" SL:"I2S(TUYA_SECURITY_LEVEL)\
" OPERATING_SYSTEM:"I2S(OPERATING_SYSTEM)\
" RELIABLE_TRANSFER:"I2S(DEV_ATTR_RELIABLE_TRANSFER)\
" >"

#define SDK_INFO SDK_INFO_1"\r\n"SDK_INFO_2"\r\n"SDK_IOT_ATTR"\r\n"

#ifdef __cplusplus
}
#endif
#endif /*_SDK_VERSION_H*/


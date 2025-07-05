#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "board_config.h"


#define CONFIG_DEBUG_ENABLE                 // 打印开关

#define CONFIG_RTOS_STACK_CHECK_ENABLE      //是否启用定时检查任务栈
// #define CONFIG_MEM_LEAK_CHECK_ENABLE     //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)

#define CONFIG_LOCAL_MUSIC_MODE_ENABLE      //mode:本地播放模式使能
#define CONFIG_RECORDER_MODE_ENABLE         //mode:录音模式使能

#ifdef CONFIG_NET_ENABLE
#define CONFIG_NET_MUSIC_MODE_ENABLE        //mode:网络播放模式使能

#ifdef CONFIG_SFC_ENABLE
#ifdef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_RF_TRIM_CODE_MOVABLE         //把RF TRIM 的运行代码动态加载到ram运行(节省4K ram内存), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#else
#define CONFIG_RF_TRIM_CODE_AT_RAM          //把RF TRIM 的运行代码定死到ram运行(浪费4K ram内存,否则若动态加载到sdram需清cache), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#endif
#endif

//*********************************************************************************//
//                          预留区UI和AUDIO资源配置                                //
//*********************************************************************************//
//注意：ui和audio资源的起始地址和大小, 根据产品生命周期最大情况定义,根据实际需求进行配置
//FLASH后面4K用于一些配置存储，所以禁止覆盖
//具体说明和注意事项请阅读文档

//(1)ui和audio资源 ,如果存在ui资源则位于扩展预留区末尾,
//还存在audio则位于ui项前面，其他配置项则位于它们之前.
/*
#------------------------------|
#  (其他预留区配置项)          |
#------------------------------|<----CONFIG_UI_PACKRES_ADR - CONFIG_AUDIO_PACKRES_LEN = CONFIG_AUDIO_PACKRES_ADR
#  (CONFIG_AUDIO_PACKRES_LEN)  |
#------------------------------|<----__FLASH_SIZE__ - 0x1000 - CONFIG_UI_PACKRES_LEN = CONFIG_UI_PACKRES_ADR
#  (CONFIG_UI_PACKRES_LEN)     |
#------------------------------|<----__FLASH_SIZE__ - 0x1000
#  (4K Reserved)               |
#------------------------------+<----__FLASH_SIZE__
*/

//(2)只有audio资源,则将其位于扩展预留区末尾.
/*
#------------------------------|
#  (其他预留区配置项)          |
#------------------------------|<----__FLASH_SIZE__ - 0x1000 - CONFIG_AUDIO_PACKRES_LEN = CONFIG_AUDIO_PACKRES_ADR
#  (CONFIG_AUDIO_PACKRES_LEN)  |
#------------------------------|<----__FLASH_SIZE__ - 0x1000
#  (4K Reserved)               |
#------------------------------+<----__FLASH_SIZE__
*/

#if defined CONFIG_UI_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
//#define CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //UI资源打包后放在扩展预留区
#endif

#if defined CONFIG_AUDIO_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //AUDIO资源打包后放在扩展预留区
#endif

#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_UI_PACKRES_LEN 0x200000
#define CONFIG_UI_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000)
#else
#define CONFIG_UI_PACKRES_LEN 0
#define CONFIG_UI_PACKRES_ADR 0
#endif

#if defined CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_AUDIO_PACKRES_LEN 0x180000
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN)
#else
#define CONFIG_AUDIO_PACKRES_LEN 0x180000
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - CONFIG_AUDIO_PACKRES_LEN - 0x1000)
#endif
#endif


#define INIT_SSID "WL83"                    //WIFI名称
#define INIT_PWD  "12345678"                //WIFI密码
#define CONFIG_ASSIGN_MACADDR_ENABLE        //第一次开机连上外网后，使用杰理服务器分配WIFI模块的MAC地址, 关闭则使用<蓝牙地址更新工具*.exe>或者随机数作为MAC地址
#define CONFIG_DLNA_SDK_ENABLE              //打开DLNA音乐播放功能

// #define CONFIG_ASR_ALGORITHM_ENABLE         //mode:打断唤醒模式使能

#ifdef CONFIG_ASR_ALGORITHM_ENABLE
#define AISP_ALGORITHM              1       //思必驰双mic唤醒,未授权版本只支持运行10分钟
#define ROOBO_ALGORITHM             2       //ROOBO 单/双MIC唤醒 ROOBO_DUAL_MIC_ALGORITHM ,,,测试版本只支持运行10分钟
#define WANSON_ALGORITHM            3       //华镇算法,测试版只能够正确识别1000次
#define JLKWS_ALGORITHM             4       //杰理算法,现阶段仅用于测试效果
#define CONFIG_ASR_ALGORITHM JLKWS_ALGORITHM//本地打断唤醒算法选择
#endif
#endif


//编解码器使能
#define CONFIG_JLA_ENC_ENABLE
#define CONFIG_JLA_DEC_ENABLE
#define CONFIG_PCM_DEC_ENABLE
#define CONFIG_PCM_ENC_ENABLE
#define CONFIG_DTS_DEC_ENABLE
#define CONFIG_ADPCM_DEC_ENABLE
#define CONFIG_MP3_DEC_ENABLE
#define CONFIG_MP3_ENC_ENABLE
#define CONFIG_WMA_DEC_ENABLE
#define CONFIG_M4A_DEC_ENABLE
#define CONFIG_WAV_DEC_ENABLE
#define CONFIG_AMR_DEC_ENABLE
#define CONFIG_APE_DEC_ENABLE
#define CONFIG_FLAC_DEC_ENABLE
#define CONFIG_SPEEX_DEC_ENABLE
#define CONFIG_ADPCM_ENC_ENABLE
#define CONFIG_WAV_ENC_ENABLE
#define CONFIG_VAD_ENC_ENABLE
#define CONFIG_VIRTUAL_DEV_ENC_ENABLE
#define CONFIG_OPUS_ENC_ENABLE
#define CONFIG_OPUS_DEC_ENABLE
#define CONFIG_SPEEX_ENC_ENABLE
#define CONFIG_AMR_ENC_ENABLE
#define CONFIG_AEC_ENC_ENABLE
#define CONFIG_DNS_ENC_ENABLE
#define CONFIG_AAC_ENC_ENABLE
#define CONFIG_OGG_DEC_ENABLE
#define CONFIG_OGG_ENC_ENABLE

#define CONFIG_AUDIO_MIX_ENABLE             //打开叠音功能
// #define CONFIG_AUDIO_PS_ENABLE           //打开变调变速功能
// #define CONFIG_DEC_DIGITAL_VOLUME_ENABLE //数字音量淡入淡出功能
// #define CONFIG_SPECTRUM_FFT_EFFECT_ENABLE//频谱运算


#define CONFIG_STORE_VOLUME                 //保存音量设置到VM
#define VOLUME_STEP         5
#define GAIN_STEP           5
#define MIN_VOLUME_VALUE	5
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE   50

#define CONFIG_JLFAT_ENABLE

#if TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                 "storage/sd0"
#define SDX_DEV                             "sd0"
#endif

#if TCFG_SD1_ENABLE
#define CONFIG_STORAGE_PATH                 "storage/sd1"
#define SDX_DEV                             "sd1"
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH                 "storage/sdx"
#define SDX_DEV                             "sdx"
#endif

#define CONFIG_UDISK_STORAGE_PATH           "storage/udisk0"

#define CONFIG_ROOT_PATH                    CONFIG_STORAGE_PATH"/C/"
#define CONFIG_UDISK_ROOT_PATH              CONFIG_UDISK_STORAGE_PATH"/C/"

#define CONFIG_MUSIC_PATH_SD                CONFIG_ROOT_PATH
#define CONFIG_MUSIC_PATH_UDISK             CONFIG_UDISK_ROOT_PATH

#define CONFIG_MUSIC_PATH_FLASH             "mnt/sdfile/res/"

#define CONFIG_EQ_FILE_NAME                 "mnt/sdfile/res/cfg/eq_cfg_hw.bin"

#define CONFIG_VOICE_PROMPT_FILE_PATH       "mnt/sdfile/EXT_RESERVED/aupackres/tone/"

#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)


#endif


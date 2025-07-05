#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#define AUDIO_ENC_SAMPLE_SOURCE_MIC         0
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK0       1
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK1       2
#define AUDIO_ENC_SAMPLE_SOURCE_IIS0        3
#define AUDIO_ENC_SAMPLE_SOURCE_IIS1        4
#define AUDIO_ENC_SAMPLE_SOURCE_LINEIN      5

#define CONFIG_AUDIO_DEC_PLAY_SOURCE        "dac"

#include "board_config.h"

#ifdef CONFIG_MEDIA_ENABLE
#include "to_compile_audio/sdk_config.h"    //TODO
#endif

//*********************************************************************************//
//                                 资源分配相关配置                                //
//*********************************************************************************//
#ifdef CONFIG_SDFILE_EXT_ENABLE

#undef CONFIG_SFC_ENABLE
#undef __FLASH_SIZE__
#define __FLASH_SIZE__    (16 * 1024 * 1024)

#define CONFIG_SDNAND_HFS_LEN_TEXT  16M
#define CONFIG_SDNAND_HFAT_LEN_TEXT 4G
#define CONFIG_SDNAND_FAT1_LEN_TEXT 8G
#define CONFIG_SDNAND_HFS_LEN       (16llu * 1024 * 1024)
#define CONFIG_SDNAND_HFAT_LEN      (4llu * 1024 * 1024 * 1024)
#define CONFIG_SDNAND_FAT1_LEN      (8llu * 1024 * 1024 * 1024)

//每个簇有多少个block，比如簇大小设置为32768时，该值为32768 / 512 = 0x40
#if CONFIG_SDNAND_HFAT_LEN > 0x80000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x40
#elif CONFIG_SDNAND_HFAT_LEN > 0x40000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x20
#elif CONFIG_SDNAND_HFAT_LEN > 0x20000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x10
#elif CONFIG_SDNAND_HFAT_LEN > 0x10000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x8
#elif CONFIG_SDNAND_HFAT_LEN > 0x8000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x4
#elif CONFIG_SDNAND_HFAT_LEN > 0x4000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x2
#else
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x1
#endif

#if CONFIG_SDNAND_FAT1_LEN > 0x80000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x40
#elif CONFIG_SDNAND_FAT1_LEN > 0x40000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x20
#elif CONFIG_SDNAND_FAT1_LEN > 0x20000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x10
#elif CONFIG_SDNAND_FAT1_LEN > 0x10000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x8
#elif CONFIG_SDNAND_FAT1_LEN > 0x8000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x4
#elif CONFIG_SDNAND_FAT1_LEN > 0x4000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x2
#else
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x1
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
#define CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //UI资源打包后放在扩展预留区
#endif

#if defined CONFIG_AUDIO_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //AUDIO资源打包后放在扩展预留区
#endif

#if (defined CONFIG_AUDIO_ENABLE || defined CONFIG_UI_ENABLE) && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_LOGO_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //开关机logo资源打包后放在扩展预留区
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
#else
#define CONFIG_AUDIO_PACKRES_LEN 0
#define CONFIG_AUDIO_PACKRES_ADR 0
#endif

#if defined CONFIG_LOGO_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_LOGO_PACKRES_LEN 0x32000
#define CONFIG_LOGO_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN - CONFIG_LOGO_PACKRES_LEN)
#endif
//*********************************************************************************//
//                                   DEBUG相关配置                                 //
//*********************************************************************************//
#define CONFIG_DEBUG_ENABLE                     //打印开关
// #define CONFIG_FLOAT_DEBUG_ENABLE
// #define CONFIG_CPU_EFFICIENCY_CALCULATE_ENABLE
// #define CONFIG_ICACHE_EFFICIENCY_CALCULATE_ENABLE
#ifndef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_DCACHE_EFFICIENCY_CALCULATE_ENABLE
#endif
#define CONFIG_MPU_DEBUG_ENABLE
// #define CONFIG_TRUSTZONE_ENABLE
#define CONFIG_RTOS_STACK_CHECK_ENABLE          //是否启用定时检查任务栈
// #define CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH   //保存异常打印信息到flash
// #define CONFIG_MEM_LEAK_CHECK_ENABLE         //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)
#define CONFIG_LZ4_COMPRESS_APP_CODE_ENABLE     //使用LZ4压缩代码


// #define CONFIG_SYS_VDD_CLOCK_ENABLE          //系统可使用动态电源、时钟配置
// #define CONFIG_IPMASK_ENABLE                 //系统使用不可屏蔽中断


//*********************************************************************************//
//                                  网络相关配置                                   //
//*********************************************************************************//
#ifdef CONFIG_NET_ENABLE
// #define CONFIG_LTE_PHY_ENABLE                //usb网卡

#ifdef CONFIG_SFC_ENABLE
#ifdef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_RF_TRIM_CODE_MOVABLE             //把RF TRIM 的运行代码动态加载到ram运行(节省4K ram内存), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#else
#define CONFIG_RF_TRIM_CODE_AT_RAM              //把RF TRIM 的运行代码定死到ram运行(浪费4K ram内存,否则若动态加载到sdram需清cache), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#endif
#endif

#define CONFIG_IPERF_ENABLE                     // iperf测试
// #define CONFIG_WIFIBOX_ENABLE                //WIFI测试盒性能测试
// #define CONFIG_MP_TEST_ENABLE                //RF量产测试
// #define CONFIG_READ_RF_PARAM_FROM_CFGTOOL_ENABLE    //从配置文件读取RF参数
#define CONFIG_SERVER_ASSIGN_PROFILE            //第三方平台的profile由杰理服务器分配
// #define CONFIG_PROFILE_UPDATE                //每次开机都从杰理服务器获取第三方平台的profile,不读flash
// #define CONFIG_STATIC_IPADDR_ENABLE          //记忆路由器分配的IP,下次直接使用记忆IP节省DHCP时间
#define CONFIG_ASSIGN_MACADDR_ENABLE            //第一次开机连上外网后，使用杰理服务器分配WIFI模块的MAC地址, 关闭则使用<蓝牙地址更新工具*.exe>或者随机数作为MAC地址
// #define CONFIG_TURING_SDK_ENABLE             //使用图灵平台
// #define CONFIG_DUER_SDK_ENABLE               //使用百度平台
// #define CONFIG_DUI_SDK_ENABLE                //使用思必驰DUI平台
// #define CONFIG_ALI_SDK_ENABLE                //使用天猫精灵平台
// #define CONFIG_TVS_SDK_ENABLE                //使用腾讯云平台
// #define CONFIG_TELECOM_SDK_ENABLE            //电信云平台
// #define CONFIG_JL_CLOUD_SDK_ENABLE           //打开使用杰理云平台
// #define CONFIG_DLNA_SDK_ENABLE               //打开DLNA音乐播放功能
// #define CONFIG_DOWNLOAD_SAVE_FILE            //保存网络下载的音乐文件
// #define CONFIG_SCAN_PEN_ENABLE               //扫描笔图像拼接
// #define CONFIG_HTTP_SERVER_ENABLE            //HTTP服务器
// #define CONFIG_FTP_SERVER_ENABLE             //FTP服务器

/*************电信云平台配网方式选择*************/
#ifdef CONFIG_TELECOM_SDK_ENABLE
#define CONFIG_APLINK_NET_CFG                   //电信AP配网。注意：1.电信AP配网不能与elink无感配网同时使能。2.wifi库需要支持ap
#ifndef CONFIG_APLINK_NET_CFG
#define CONFIG_ELINK_QLINK_NET_CFG              //电信elink无感配网。注意：elink无感配网不能与AIRKISS配网同时使能。
#endif
#define CONFIG_CTEI_DEVICE_ENABLE               //电信非蜂窝类串码对接设备使用
//#define CONFIG_MC_DEVICE_ENABLE               //电信mc接口类直连设备使用
#endif

#ifdef CONFIG_VIDEO_ENABLE
/*************绘本识别服务器*************/
#ifdef CONFIG_TURING_SDK_ENABLE
#define CONFIG_TURING_PAGE_TURNING_DET_ENABLE   //图灵翻页算法，需要配合图灵绘本平台使用
#endif

// #define CONFIG_WT_SDK_ENABLE                 //新玩瞳接口
#define CONFIG_QR_CODE_NET_CFG                  //二维码配网
#endif

#if TCFG_WIFI_ENABLE
// #define CONFIG_AIRKISS_NET_CFG               //AIRKISS配网
// #define CONFIG_WSC_NET_CFG                   //WSC配网
#endif

#ifdef CONFIG_AUDIO_ENABLE
#define CONFIG_ACOUSTIC_COMMUNICATION_ENABLE    //声波配网

#define AISP_ALGORITHM                      1   //思必驰双mic唤醒,未授权版本只支持运行10分钟
#define ROOBO_ALGORITHM                     2   //ROOBO 单/双MIC唤醒 ROOBO_DUAL_MIC_ALGORITHM ,,,测试版本只支持运行10分钟
#define WANSON_ALGORITHM                    3   //华镇算法,测试版只能够正确识别1000次
#define JLKWS_ALGORITHM                     4   //杰理算法,现阶段仅用于测试效果
#define CONFIG_ASR_ALGORITHM  JLKWS_ALGORITHM //本地打断唤醒算法选择

#ifdef CONFIG_ASR_ALGORITHM
#define WIFI_PCM_STREAN_SOCKET_ENABLE           //打开打断唤醒pcm音频流局域网传输工具
#endif
#endif

#endif


//*********************************************************************************//
//                                AUDIO功能配置                                    //
//*********************************************************************************//
#ifdef CONFIG_AUDIO_ENABLE

#ifdef CONFIG_BT_ENABLE
#define CONFIG_SBC_DEC_ENABLE
#define CONFIG_SBC_ENC_ENABLE
#define CONFIG_MSBC_DEC_ENABLE
#define CONFIG_MSBC_ENC_ENABLE
#define CONFIG_CVSD_DEC_ENABLE
#define CONFIG_CVSD_ENC_ENABLE
#endif

#define CONFIG_PCM_DEC_ENABLE
#define CONFIG_PCM_ENC_ENABLE
#define CONFIG_WAV_DEC_ENABLE
#define CONFIG_WAV_ENC_ENABLE
#define CONFIG_MP3_DEC_ENABLE
#define CONFIG_M4A_DEC_ENABLE
#define CONFIG_NEW_M4A_DEC_ENABLE               //需要把lib_m4a_dec.a替换成lib_m4a_dec_seek.a
#ifdef CONFIG_NEW_M4A_DEC_ENABLE
#define CONFIG_AAC_DEC_ENABLE
#endif
#define CONFIG_VIRTUAL_DEV_ENC_ENABLE
#define CONFIG_SPEEX_ENC_ENABLE
#define CONFIG_OPUS_ENC_ENABLE
#define CONFIG_VAD_ENC_ENABLE
#define CONFIG_DTS_DEC_ENABLE
#define CONFIG_ADPCM_DEC_ENABLE
#define CONFIG_MP3_ENC_ENABLE
#define CONFIG_WMA_DEC_ENABLE
#define CONFIG_AMR_DEC_ENABLE
#define CONFIG_APE_DEC_ENABLE
#define CONFIG_FLAC_DEC_ENABLE
#define CONFIG_SPEEX_DEC_ENABLE
#define CONFIG_ADPCM_ENC_ENABLE
#define CONFIG_OPUS_DEC_ENABLE
#define CONFIG_AMR_ENC_ENABLE
#define CONFIG_AEC_ENC_ENABLE
#define CONFIG_DNS_ENC_ENABLE
#define CONFIG_OGG_DEC_ENABLE

// #define CONFIG_VIRTUAL_BASS_ENABLE           //虚拟低音
// #define CONFIG_SPECTRUM_FFT_EFFECT_ENABLE    //频谱运算
// #define CONFIG_REVERB_MODE_ENABLE            //打开混响功能
#define CONFIG_AUDIO_MIX_ENABLE              //打开叠音功能
#define CONFIG_AUDIO_PS_ENABLE                  //打开变调变速功能

// #define CONFIG_DEC_DIGITAL_VOLUME_ENABLE     //数字音量淡入淡出功能
// #define CONFIG_RESUME_LOCAL_PLAY_FILE        //本地断点恢复播放

#if (!defined CONFIG_SFC_ENABLE) && (defined __SDRAM_SIZE__ && __SDRAM_SIZE__ >= (8 * 1024 * 1024))
//TODO
// #define CONFIG_LOAD_SDRAM_PROMPT_PLAY        0   //0 首次调用提示音装载全部进sdram  1 装载当前提示音
#endif

#ifdef CONFIG_AEC_ENC_ENABLE
#define CONFIG_USB_AUDIO_AEC_ENABLE             //usb mic使能回声消除功能
#define CONFIG_AEC_HW_REC_LINEIN_ENABLE     //AEC回采使用硬件通道数据
// #define CONFIG_AEC_USE_PLAY_MUSIC_ENABLE     //播歌时需要使用AEC
// #define CONFIG_AUDIO_ENC_AEC_DATA_CHECK      //打开查看AEC操作数据(mic/dac/aec数据)
#endif

#endif


//*********************************************************************************//
//                                  路径配置                                       //
//*********************************************************************************//
#define CONFIG_JLFAT_ENABLE

#if TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                         "storage/sd0"   //定义对应SD0的路径
#define SDX_DEV                                     "sd0"
#endif

#if TCFG_SD1_ENABLE && !TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                         "storage/sd1"   //定义对应SD1的路径
#define SDX_DEV                                     "sd1"
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH                         "storage/sdx"   //不使用SD定义对应别的路径，防止编译出错
#define SDX_DEV                                     "sdx"
#endif

#define CONFIG_UDISK_STORAGE_PATH                   "storage/udisk0"

#define CONFIG_ROOT_PATH                            CONFIG_STORAGE_PATH"/C/"        //定义对应SD文件系统的根目录路径
#define CONFIG_UDISK_ROOT_PATH                      CONFIG_UDISK_STORAGE_PATH"/C/"  //定义对应U盘文件系统的根目录路径

#define CONFIG_MUSIC_PATH_SD                        CONFIG_ROOT_PATH
#define CONFIG_MUSIC_PATH_SD0                       "storage/sd0/C/"
#define CONFIG_MUSIC_PATH_SD1                       "storage/sd1/C/"
#define CONFIG_MUSIC_PATH_UDISK                     CONFIG_UDISK_ROOT_PATH
#define CONFIG_MUSIC_PATH_UDISK0                    "storage/udisk0/C/"
#define CONFIG_MUSIC_PATH_UDISK1                    "storage/udisk1/C/"

#define CONFIG_MUSIC_PATH_FLASH                     "mnt/sdfile/res/"
#define CONFIG_EQ_FILE_NAME                         "mnt/sdfile/res/cfg/eq_cfg_hw.bin"

#ifdef CONFIG_AUDIO_ENABLE
#define CONFIG_VOICE_PROMPT_FILE_PATH               "mnt/sdfile/EXT_RESERVED/aupackres/tone/"
#endif


//*********************************************************************************//
//                                  升级配置                                       //
//*********************************************************************************//
// #define CONFIG_DOUBLE_BANK_ENABLE                   //双备份方式升级
#ifdef CONFIG_DOUBLE_BANK_ENABLE
#define CONFIG_SUPPORT_DOUBLE_UBOOT                 //开启双uboot架构支持
#endif

#define CONFIG_UPGRADE_FILE_NAME                    "update.ufw"
#define CONFIG_UPGRADE_PATH                         CONFIG_ROOT_PATH\
                                                    CONFIG_UPGRADE_FILE_NAME

#define CONFIG_SD0_UPGRADE_PATH                     "storage/sd0/C/" CONFIG_UPGRADE_FILE_NAME
#define CONFIG_SD1_UPGRADE_PATH                     "storage/sd1/C/" CONFIG_UPGRADE_FILE_NAME
#define CONFIG_UDISK0_UPGRADE_PATH                  "storage/udisk0/C/" CONFIG_UPGRADE_FILE_NAME
#define CONFIG_UDISK1_UPGRADE_PATH                  "storage/udisk1/C/" CONFIG_UPGRADE_FILE_NAME


//*********************************************************************************//
//                                VIDEO功能配置                                    //
//*********************************************************************************//
#ifdef CONFIG_VIDEO_ENABLE

#ifdef CONFIG_SCAN_PEN_ENABLE
#define CONFIG_VIDEO1_ENABLE
#define CONFIG_SPI_VIDEO_ENABLE
#define CONFIG_VIDEO_720P
#endif

// #define CONFIG_MASS_PRODUCTION_ENABLE               //启用产测模式
// #define CONFIG_OSD_ENABLE			                //视频OSD时间戳开关

#ifdef CONFIG_MASS_PRODUCTION_ENABLE
#define STA_WIFI_SSID     "test"    //量产模式的路由器名称
#define STA_WIFI_PWD      "12345678"  //量产模式的路由器密码
//#define CONFIG_PRODUCTION_IO_PORT			IO_PORTB_01 //配置进入量产莫模式的IO
//#define CONFIG_PRODUCTION_IO_STATE		0 			//配置进入量产莫模式的IO状态：0低电平，1高电平
#endif

//*********************************************************************************//
//                             编码图片分辨率                                      //
//*********************************************************************************//
//#define CONFIG_VIDEO_720P
#ifdef CONFIG_VIDEO_720P
#define CONFIG_VIDEO_IMAGE_W    1280
#define CONFIG_VIDEO_IMAGE_H    720
#else
#define CONFIG_VIDEO_IMAGE_W    640
#define CONFIG_VIDEO_IMAGE_H    480
#endif

//*********************************************************************************//
//                             视频流相关配置                                      //
//*********************************************************************************//
#define CONFIG_USR_VIDEO_ENABLE                     //自定义VIDEO流使能

#ifdef CONFIG_USR_VIDEO_ENABLE
#ifdef CONFIG_USER_VIDEO_720P
#define CONFIG_USER_VIDEO_WIDTH                 1280
#define CONFIG_USER_VIDEO_HEIGHT                720
#define CONFIG_USER_VIDEO_ISC_SBUF_SIZE         (CONFIG_USER_VIDEO_WIDTH*64*3/2)
#define CONFIG_USER_VIDEO_SBUF_SIZE             (200 * 1024)
#else
#define CONFIG_USER_VIDEO_WIDTH                 640
#define CONFIG_USER_VIDEO_HEIGHT                480
#define CONFIG_USER_VIDEO_ISC_SBUF_SIZE         (CONFIG_USER_VIDEO_WIDTH*32*3/2)
#define CONFIG_USER_VIDEO_SBUF_SIZE             (300 * 1024)
#endif
// #define CONFIG_USER_VIDEO_ISC_STATIC_BUF_ENABLE
#define CONFIG_USER_VIDEO_PATH                  "192.168.1.1:8000"  //用户路径可随意设置
#define CONFIG_USER_VIDEO_REC_FPS               20  //自定义视频流帧率设置，0为默认
#define CONFIG_USER_VIDEO_REC_AUDIO_SAMPLE_RATE 0   //视频流的音频采样率，设成0为关闭mic
#endif

#endif


//*********************************************************************************//
//                                  EDR和BLE配置                                   //
//*********************************************************************************//
#ifdef CONFIG_BT_ENABLE

#define TCFG_BT_MODE                                BT_NORMAL

#define BT_EMITTER_EN                               1
#define BT_RECEIVER_EN                              2

#define TCFG_POWER_ON_ENABLE_EMITTER                0   //开机自动打开发射器
#define TCFG_POWER_ON_ENABLE_BT                     1   //开机自动打开经典蓝牙
#define TCFG_POWER_ON_ENABLE_BLE                    1   //开机自动打开BLE
#define TCFG_USER_BT_CLASSIC_ENABLE                 1   //经典蓝牙功能
#define TCFG_USER_TWS_ENABLE                        0   //tws功能使能
#define TCFG_USER_BLE_ENABLE                        1   //BLE功能使能
#define TCFG_USER_EDR_ENABLE                        0   //EDR用户自定义协议功能
#define TCFG_USER_EMITTER_ENABLE                    0   //蓝牙发射功能
#define TCFG_BT_DUAL_CONN_ENABLE                    0   //经典蓝牙支持同时连接2台设备
#if TCFG_RF_FCC_TEST_ENABLE
#define TCFG_BT_SNIFF_ENABLE                        0   //经典蓝牙低功耗sniff模式
#define TCFG_BT_SUPPORT_AAC                         0   //蓝牙AAC格式支持
#define TCFG_BT_SUPPORT_MUSIC_VOL_SYNC              0   //音量同步
#define TCFG_BT_SUPPORT_DISPLAY_BAT                 0   //电池电量同步显示功能
#else
#define TCFG_BT_SNIFF_ENABLE                        1   //经典蓝牙低功耗sniff模式
#define TCFG_BT_SUPPORT_AAC                         1   //蓝牙AAC格式支持
#define TCFG_BT_SUPPORT_MUSIC_VOL_SYNC              1   //音量同步
#define TCFG_BT_SUPPORT_DISPLAY_BAT                 1   //电池电量同步显示功能
#endif
#define TCFG_BT_SUPPORT_EMITTER_AUTO_A2DP_START     1   //发射器连上后自动打开A2DP流
#define TCFG_BT_SUPPORT_RECEIVER_AUTO_A2DP_START    1   //接收器器连上后自动打开A2DP流
#define TCFG_BT_SUPPORT_EMITTER_PAGE_SCAN           0   //发射器打开可发现性
#define TCFG_BT_SUPPORT_WIFI_CFG_COEXISTENCE        0   //wifi配网时保持蓝牙连接

//---------------------------用户选择蓝牙支持的协议--------------------------------//
#if TCFG_RF_FCC_TEST_ENABLE
#define TCFG_BT_SUPPORT_PROFILE_SPP                 0
#define TCFG_BT_SUPPORT_PROFILE_HFP                 0
#define TCFG_BT_SUPPORT_PROFILE_A2DP                0
#define TCFG_BT_SUPPORT_PROFILE_AVCTP               0
#else
#define TCFG_BT_SUPPORT_PROFILE_SPP                 1
#define TCFG_BT_SUPPORT_PROFILE_HFP                 1
#define TCFG_BT_SUPPORT_PROFILE_A2DP                1
#define TCFG_BT_SUPPORT_PROFILE_AVCTP               1
#endif
#define TCFG_BT_SUPPORT_PROFILE_HID                 0
#define TCFG_BT_SUPPORT_PROFILE_PNP                 0
#define TCFG_BT_SUPPORT_PROFILE_PBAP                0
#define TCFG_BT_SUPPORT_PROFILE_PAN                 0
#define TCFG_BT_SUPPORT_PROFILE_MAP                 0
#if TCFG_USER_EMITTER_ENABLE
#define TCFG_BT_SUPPORT_PROFILE_HFP_AG              1
#else
#define TCFG_BT_SUPPORT_PROFILE_HFP_AG              0
#endif

#if TCFG_USER_EDR_ENABLE
#define TCFG_SPP_TRANS_DATA_EN                      1
#endif

#if TCFG_USER_BLE_ENABLE

#define TCFG_BLE_SECURITY_EN                        0   //配对加密使能

#define TCFG_BLE_MESH_ENABLE                        0   //SIG MESH功能

#ifdef CONFIG_NET_ENABLE

#ifdef CONFIG_DUI_SDK_ENABLE
#define TCFG_BT_NET_CFG_DUI_EN                      1   //从机 思必驰配网专用
#else
#define TCFG_BT_NET_CFG_DUI_EN                      0   //从机 思必驰配网专用
#endif

#ifdef CONFIG_TURING_SDK_ENABLE
#define TCFG_BT_NET_CFG_TURING_EN                   1   //从机 图灵配网专用
#else
#define TCFG_BT_NET_CFG_TURING_EN                   0   //从机 图灵配网专用
#endif

#ifdef CONFIG_TVS_SDK_ENABLE
#define TCFG_BT_NET_CFG_TENCENT_EN                  1   //从机 腾讯云配网专用
#else
#define TCFG_BT_NET_CFG_TENCENT_EN                  0   //从机 腾讯云配网专用
#endif

#if TCFG_BT_NET_CFG_TURING_EN + TCFG_BT_NET_CFG_DUI_EN + TCFG_BT_NET_CFG_TENCENT_EN + TCFG_APP_BT_ENABLE > 0
#define TCFG_BT_NET_CFG_EN                          0   //从机 杰理配网专用
#else
#define TCFG_BT_NET_CFG_EN                          1   //从机 杰理配网专用
#endif

#define TCFG_TRANS_DATA_EN                          0   //从机 传输数据

#else

#define TCFG_BT_NET_CFG_DUI_EN                      0   //从机 思必驰配网专用
#define TCFG_BT_NET_CFG_TURING_EN                   0   //从机 图灵配网专用
#define TCFG_BT_NET_CFG_TENCENT_EN                  0   //从机 腾讯云配网专用
#define TCFG_BT_NET_CFG_EN                          0   //从机 配网专用
#define TCFG_TRANS_DATA_EN                          1   //从机 传输数据

#endif

#define TCFG_BLE_MASTER_CENTRAL_EN                  0   //主机 client角色
#define TCFG_BLE_HID_EN                             0   //从机 hid
#define TCFG_TRANS_MULTI_BLE_EN                     0   //多机通讯
#define TCFG_NONCONN_24G_EN                         0   //2.4g加密通讯

#if (TCFG_TRANS_MULTI_BLE_EN + TCFG_BT_NET_CFG_TURING_EN + TCFG_BT_NET_CFG_DUI_EN + TCFG_BT_NET_CFG_EN + TCFG_BLE_HID_EN + TCFG_TRANS_DATA_EN + TCFG_APP_BT_ENABLE + TCFG_NONCONN_24G_EN > 1)
#error "they can not enable at the same time, just select one!!!"
#endif
#endif

#if TCFG_TRANS_MULTI_BLE_EN
#define TCFG_TRANS_MULTI_BLE_SLAVE_NUMS             1
#define TCFG_TRANS_MULTI_BLE_MASTER_NUMS            1
#endif

#if (TCFG_BLE_MESH_ENABLE || TCFG_USER_EMITTER_ENABLE) && TCFG_WIFI_ENABLE && !defined CONFIG_LOW_POWER_ENABLE
// #define CONFIG_WIFI_IDLE_RESUME_BASEBAND_ENABLE
#endif

#endif


//*********************************************************************************//
//                                UI DEMO配置                                      //
//*********************************************************************************//
#if TCFG_LCD_ENABLE
#define USE_LVGL_V8_UI_DEMO
/* LV_DISP_UI_FB_NUM: LVGL UI绘制的FB帧显存个数 */
/* 0:表示 LVGL UI直接在LCD显存上绘制,不需要额外的帧buffer (使用于UI刷新要求不高的方案)
 * 1:表示 LVGL UI 单独申请1块帧buffer
 * 2:表示 LVGL UI 单独申请2块帧buffer
 * */
/* FB_LCD_BUF_NUM : LCD使用的帧显存个数 */
/* 0:表示 LCD不需要额外帧buf,用UI绘制FB 或者摄像头图像FB 直接推屏显示
 * 1:表示 LCD只开一块帧显存,只能拷贝更新或者旋转更新推屏数据
 * 2:表示 LCD开2块帧显存,可以通过交换的方式来更新推屏数据
 * 3:表示 LCD开3块帧显存,其中2块通过交换的方式来更新推屏数据,另外1块用做合成输出
 * */
/* 2个宏组合更多详细说明,请移步开源文档 */
#define LV_DISP_UI_FB_NUM      2
#define FB_LCD_BUF_NUM         2

//开发板硬件测试UI
#define DEV_HARDWARE_VERIFY_UI_ENABLE   0

//描述当前SDK能够兼容的UI项目模板最低版本
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR 1
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MINOR 0
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_PATCH 0

//描述当前SDK能够兼容的UI项目模板最高版本
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR 1
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MINOR 0
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_PATCH 0

#endif


#define CONFIG_CXX_SUPPORT //使能C++支持

#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    1
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#endif


/*****************************************************************************
 * ut_xciot.c
 *
 *
 ****************************************************************************/

/*****************************************************************************
 * Included Files
 ****************************************************************************/


#include "xciot_api.h"

#include "ut_dev_ipc_cmd.h"


#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "camx.h"

#include "action.h" //app_core

/*****************************************************************************
 * Trace Definitions
 ****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "ut_xciot.c"
#include "xc_log.h"

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* #define USE_INI //使用配置文件 */

/*****************************************************************************
 * Private Types
 ****************************************************************************/

/*****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

extern void osal_mdelay(uint64_t millisecond);


/*****************************************************************************
 * Private Data
 ****************************************************************************/
uint8_t is_conn_plat_ok = 0;
uint8_t g_is_distribution_network = 0;
uint32_t g_platform_check_timer_hdl = 0;
extern bool g_camx_wifi_connected;

static void iot_dev_on_platform_utc(uint64_t utc_ms)
{
    set_utc_ms(utc_ms);
}
void check(void *arg)
{
    if (g_camx_wifi_connected) {
        /* if(!avsdk_poll_conn_platfrom()) { */
        check_platform_invaild();
        /* } */
    }


}

extern void test_cs(void);

static void iot_dev_on_connect_platform(iot_conn_platform_state_t state)
{
    int rc = 0;

    switch (state) {

    case E_IOT_CONN_PLATFORM_STATE_DISCONN:
        printf("-----------platform connected is disconnected------------");

        is_conn_plat_ok = 0;
        break;
    case E_IOT_CONN_PLATFORM_STATE_CONNECTED:
        printf("------------platform connected is ok--------------------");
        avsdk_report_Battary(100, E_IOT_STATUS_NOCHARGE);

        static int flag = 0;
        if (flag == 0) {
            flag = 1;
            char vcode[13] = {0};
            extern int get_net_cfg_info(char *ssid, char *pwd, char *vcode);
            get_net_cfg_info(NULL, NULL, vcode);
            if (vcode[0]) {
                extern int avsdk_report_vcode(char *vcode);
                avsdk_report_vcode(vcode);
            }

        }

        if (db_select("rec_evet") == 2) {
            /* user_video_rec0_open();  //事件录像 */
            //todo
            /* motion_detection_init(); */
        } else {
            //todo
            /* motion_detection_uninit(); */
            void **user_video_handle = get_user_video_handle();
            if (*user_video_handle) {
                user_video_rec_close(*user_video_handle);
                *user_video_handle = NULL;

            }

            //重新打开录像
            struct intent it;
            init_intent(&it);
            it.name	= "video_rec";//APP状态机在：video_rec.c
            it.action = ACTION_VIDEO_REC_MAIN;
            start_app(&it);
            /* 这个连接，SDK相关资源已经被清除，可以接收新的连接 */
        }
        break;
    case E_IOT_CONN_PLATFORM_STATE_ERROR_UCODE:
        /* 每个设备提供的唯一代码: MAC，芯片序列号，IMEI都OK; 下次通讯必须一致，如果不一致平台不允许登录 */
        T_E("ERROR: Different ucode,Please check whether DID is repeated!");
        break;
    default:
        break;
    }
}

static void iot_dev_on_reconnect_platform(iot_conn_platform_state_t state)
{
    int rc = 0;

    switch (state) {

    case E_IOT_CONN_PLATFORM_STATE_DISCONN:
        printf("-----------platform connected is disconnected------------");

        is_conn_plat_ok = 0;
        break;
    case E_IOT_CONN_PLATFORM_STATE_CONNECTED:
        printf("------------platform connected is ok--------------------");
        avsdk_report_Battary(50, E_IOT_STATUS_NOCHARGE);

        // test_cs();
        break;

    default:
        break;
    }
}

int IOT_CONNECT_FLAG = 0;
extern u8 storage_format_flag;
static void iot_dev_on_connect(int32_t          conn_id,
                               iot_conn_state_t state,
                               iot_conn_type_t  type)
{
    int rc = 0;

    switch (state) {
    case E_IOT_CONN_STATE_IDEL:
        printf("=====================I'm dev conn[%d] idel", conn_id);
        if (db_select("rec_evet") == 2) {
            /* user_video_rec0_open();  //事件录像 */
            void **user_video_handle = get_user_video_handle();
            if (*user_video_handle) {
                user_video_rec_close(*user_video_handle);
                *user_video_handle = NULL;

            }


            //todo
            /* motion_detection_init(); */
        } else {

            //todo
            /* motion_detection_uninit(); */

            void **user_video_handle = get_user_video_handle();
            if (*user_video_handle) {
                user_video_rec_close(*user_video_handle);
                *user_video_handle = NULL;

            }


            //重新打开录像
            struct intent it;
            init_intent(&it);
            it.name	= "video_rec";//APP状态机在：video_rec.c
            it.action = ACTION_VIDEO_REC_MAIN;
            /* start_app(&it); */

            if (storage_format_flag) {
                os_time_dly(100);
                cloud_playback_list_init();
                storage_format_flag = 0;
            }

            /* 这个连接，SDK相关资源已经被清除，可以接收新的连接 */
        }

#if defined CONFIG_FORCE_UPGRAGE
        g_platform_check_timer_hdl = sys_timer_add_to_task("app_core", NULL, check, 10000);
#endif


        break;
    case E_IOT_CONN_STATE_INIT:
        printf("===========================I'm dev conn[%d] init", conn_id);
        {
            /* 远端向device发起的一个连接请求，SDK将尝试建立连接
             * Device实现可以初始化相关资源
             */
        }
        break;
    case E_IOT_CONN_STATE_OPENED:
        printf("=======================I'm dev conn[%d] opened", conn_id);
        {
            IOT_CONNECT_FLAG = 1;
            /* 连接已经建立，添加device相关代码 */

            //关闭录像
            if (db_select("rec_evet") == 2) {
                extern int isCS;
                isCS = 0;
                /* user_video_rec0_open();  //事件录像 */
                dev_cs_video_end();

                //todo
                /* motion_detection_uninit(); */
            } else {
                struct intent it;
                init_intent(&it);
                it.name	= "video_rec";//APP状态机在：video_rec.c
                it.action = ACTION_BACK;
                /* start_app(&it); */

            }

#if defined CONFIG_FORCE_UPGRAGE
            sys_timer_del(g_platform_check_timer_hdl);
#endif

            //上报时区信息，校准时间
            dev_base_info_t info = {0};
            int TIMEZONE = db_select("tzone");

            if (TIMEZONE > 8000) {
                int t1 = (TIMEZONE ^ 0x7FFF) + 1;
                TIMEZONE = -(t1 & 0x7FFF);
            }

            info.timeOffset = TIMEZONE;

            T_D("info.timeOffset = %d", info.timeOffset);

            avsdk_push_info(&info);
        }
        break;
    case E_IOT_CONN_STATE_CLOSED:
        printf("==========================I'm dev conn[%d] closed", conn_id);
        {
            IOT_CONNECT_FLAG = 0;
            /* 连接已经关闭 */
            avsdk_video_del_conn(conn_id, -1);
            avsdk_audio_del_conn(conn_id);
            avsdk_custom_del_conn(conn_id);


        }
        break;
    default:
        break;
    }
}

static void iot_dev_on_packet_dropout(iot_packet_state_t state)
{
    int rc = 0;

    switch (state) {

    case E_IOT_PACKET_NORMAL:
        T_A("-----------The current data transfer is normal------------");
        {
            /* 数据传输恢复正常 */
        }
        break;
    case E_IOT_PACKET_DROPOUT:
        T_A("------------packet dropout ing --------------------");
        {
            /* 数据开始丢包 */
            //todo:降低视频的码流
        }
        break;


    default:
        break;
    }
}


/*****************************************************************************
 * Public Functions
 ****************************************************************************/
char sw_ver[32] = "1.01.02.14_230831";


#include "app_config.h"



int xc_main(void)
{

    int rc;
    osal_log_lowPrintf("printf", NULL);
    /* step 0: 设置SDK打印日志等级 */
    avsdk_set_loglevel(E_IOT_LOG_LEVEL_NONE);

#if USE_NET_GET_UUID
//如果使用这种方式获取uuid，提前获取一下为空不跑。

    char *test_uuid  = get_uuid_code();
    if (test_uuid == NULL) {
        printf("get_uuid_code is NULL!!!!\n");
        return 0;
    }

#endif
    camx_uwifi_init();

    /* step 1: 设置初始化参数 */
    {
        avsdk_init_params_t init_params;
        memset(&init_params, 0, sizeof(init_params));

        /* ipc dev */
        init_params.roletype = E_IOT_ROLE_TYPE_DEV;

        /* conn maxsize */
        init_params.conn_maxsz = 1;

        /* cfg file buffer and len */
#ifdef USE_INI
        /*从文件导入配置文件*/
        char buffer[512] = {0};
        uint16_t readed = 0;
        /*读取did*/
        do {
            rc = xc_iotcfg_read(buffer, &readed, sizeof(buffer));
            if (rc || readed < 100) {
                T_E("read did error,rc:%d", rc);
                //等待cli烧did
                osal_mdelay(2000);
            } else {

                init_params.cfg_buf = buffer;
                init_params.cfg_buf_len = strlen(buffer);
                T_I("buffer: %s, len = %d", buffer, readed);
                T_IH_HEX("cfg:", buffer, readed);
                break;
                // T_I("init_params.cfg_buf: %s, len = %d", init_params.cfg_buf, readed);
            }
        } while (1);

#else
        // 使用杰里平台分配UUID

        init_params.cfg_buf = get_uuid_code();
        if (init_params.cfg_buf == NULL) {
            printf("get_uuid_code is NULL!!!!\n");
            return 0;
        }
        init_params.cfg_buf_len = strlen(init_params.cfg_buf);

        T_IH_HEX("cfg:", init_params.cfg_buf, init_params.cfg_buf_len);


#endif

        /*hardware version*/
        strcpy(init_params.hardware_version, "AC792N");

        /*firmware version*/
        strcpy(init_params.firmware_version, FIRMWARE_VER);
        printf("firmware_version = %s\n", FIRMWARE_VER);

        /*每个设备提供的唯一代码: MAC，芯片序列号，IMEI都OK;
         *下次通讯必须一致，如果不一致平台不允许登录;
         *填""则平台连接不检查ucode字段。
         */
        strcpy(init_params.ucode, "");
        malloc_stats();
        /* step2: sdk 初始化 */
        rc = avsdk_init(&init_params);
        if (rc) {
            printf("Failed to avsdk_init, rc:%d(%s)\n",
                   rc,
                   avsdk_strerror(rc));
            return (rc);
        }

    }

    /*wifi启动*/
    struct wifi_stored_sta_info wifi_stored_sta_info[32];
    u8 ssid_stored_cnt;
    ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);

    if (!ssid_stored_cnt) { //启动蓝牙配网
        T_E("read wifi error");
        g_is_distribution_network = 1;

#ifdef CONFIG_VIDEO2_ENABLE
        while (!dev_online("uvc")) {
            putchar('u');
            osal_mdelay(1000);
        }
#endif
        osal_mdelay(3000);
        camx_uwifi_netcfg_start();
        while (1) {
            ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);

            if (ssid_stored_cnt) { //配网成功
                break;
            }
            osal_mdelay(1000);
        }
    }


    avsdk_set_sendcap(30, 4, 20, 1);
    avsdk_set_wnd(12, 12);
    /* step3: 注册平台回调函数 */

    /*平台连接utc回调，可用于同步时间*/
    avsdk_set_on_platform_utc(iot_dev_on_platform_utc);
    /*平台连接状态回调*/
    avsdk_set_on_connect_platform(iot_dev_on_connect_platform);
    avsdk_set_on_reconnect_platform(iot_dev_on_reconnect_platform);
    /*APP连接状态回调*/
    avsdk_set_on_connect(iot_dev_on_connect);
    /*音视频丢包通知回调*/
    avsdk_set_on_PacketDropout(iot_dev_on_packet_dropout);

    /* step4: 注册业务回调函数 */
    {
        /* 实时音视频 */
        avsdk_set_on_ipc_VideoPlay(dev_on_ipc_VideoPlay);
        avsdk_set_on_ipc_VideoPause(dev_on_ipc_VideoPause);
        avsdk_set_on_ipc_AudioPlay(dev_on_ipc_AudioPlay);
        avsdk_set_on_ipc_AudioPause(dev_on_ipc_AudioPause);
        avsdk_set_on_ipc_ChanState(dev_on_ipc_ChanState);

        /* 音视频设置参数 */
        /* avsdk_set_on_ipc_VideoQosSet(dev_on_ipc_VideoQosSet); */
        avsdk_set_on_ipc_FlipSet(dev_on_ipc_FlipSet);
        avsdk_set_on_ipc_FlipGet(dev_on_ipc_FlipGet);
        /* avsdk_set_on_ipc_VolumeGet(dev_on_ipc_VolumeGet); */
        /* avsdk_set_on_ipc_VolumeSet(dev_on_ipc_VolumeSet); */

        /* 对讲 */
        avsdk_set_on_media(dev_on_ipc_talkbackcb);
        avsdk_set_on_ipc_TalkbackPlay(dev_on_ipc_TalkbackPlay);
        avsdk_set_on_ipc_TalkbackPause(dev_on_ipc_TalkbackPause);

        /* 历史播放 */
        avsdk_set_on_ipc_HistoryPlay(dev_on_ipc_HistoryPlay);
        avsdk_set_on_ipc_HistoryPause(dev_on_ipc_HistoryPause);

        /* 历史播放设置 */
        avsdk_set_on_ipc_HistoryPlanSet(dev_on_ipc_HistoryPlanSet);
        avsdk_set_on_ipc_HistoryPlanGet(dev_on_ipc_HistoryPlanGet);
        avsdk_set_on_ipc_HistoryDays(dev_on_ipc_HistoryDays);
        avsdk_set_on_ipc_HistoryDayList(dev_on_ipc_HistoryDayList);
        avsdk_set_on_ipc_HistoryThumGet(dev_on_ipc_HistoryThumGet);
        avsdk_set_on_ipc_HistoryDel(dev_on_ipc_HistoryDel);

        /* 平台命令,防撬 */
        /* avsdk_set_on_ipc_TamperSet(dev_on_ipc_TamperSet); */

        /* 配置网络 */
        /* avsdk_set_on_ipc_Discovery(dev_on_ipc_Discovery); */
        avsdk_set_on_ipc_WifiAPGet(dev_on_ipc_WifiAPGet);
        avsdk_set_on_ipc_WifiSet(dev_on_ipc_WifiSet);
        avsdk_set_on_ipc_WifiGet(dev_on_ipc_WifiGet);
        /* avsdk_set_on_ipc_GetNetworkInfo(dev_on_ipc_GetNetworkInfo); */

        /*时间设置*/
        avsdk_set_on_ipc_TimeSet(dev_on_ipc_TimeSet);
        avsdk_set_on_ipc_TimeGet(dev_on_ipc_TimeGet);

        /* LED */
//		avsdk_set_on_ipc_LedSet(dev_on_ipc_LedSet);
//		avsdk_set_on_ipc_LedGet(dev_on_ipc_LedGet);

        /* 夜视功能 */
        avsdk_set_on_ipc_IRCutSet(dev_on_ipc_IRCutSet);
        avsdk_set_on_ipc_IRCutGet(dev_on_ipc_IRCutGet);

        /* 私有模式 实际是是否开启麦克风*/
        avsdk_set_on_ipc_SecretSet(dev_on_ipc_SecretSet);
        avsdk_set_on_ipc_SecretGet(dev_on_ipc_SecretGet);

        /* 运动设置 */
//		avsdk_set_on_ipc_MotionzoneSet(dev_on_ipc_MotionzoneSet);
//		avsdk_set_on_ipc_MotionzoneGet(dev_on_ipc_MotionzoneGet);
//		avsdk_set_on_ipc_PspAdd(dev_on_ipc_PspAdd);
//		avsdk_set_on_ipc_PspDel(dev_on_ipc_PspDel);
//		avsdk_set_on_ipc_PspList(dev_on_ipc_PspList);
//		avsdk_set_on_ipc_PspCall(dev_on_ipc_PspCall);
//		avsdk_set_on_ipc_TimedcruiseSet(dev_on_ipc_TimedcruiseSet);
//		avsdk_set_on_ipc_TimedcruiseGet(dev_on_ipc_TimedcruiseGet);
//		avsdk_set_on_ipc_PtzCtrl(dev_on_ipc_PtzCtrl);
//        avsdk_set_on_ipc_SetAutoTrack(dev_on_ipc_SetAutoTrack);
//        avsdk_set_on_ipc_GetAutoTrack(dev_on_ipc_GetAutoTrack);

        /*电源频率*/
        /* avsdk_set_on_ipc_PowerFreqSet(dev_on_ipc_PowerFreqSet); */
        /* avsdk_set_on_ipc_PowerFreqGet(dev_on_ipc_PowerFreqGet); */

        /* 异常事件 */
//		avsdk_set_on_ipc_EventRecordGet(dev_on_ipc_EventRecordGet);
//		avsdk_set_on_ipc_EventRecordSet(dev_on_ipc_EventRecordSet);
        avsdk_set_on_ipc_NotifySet(dev_on_ipc_NotifySet);
        avsdk_set_on_ipc_NotifyGet(dev_on_ipc_NotifyGet);
        avsdk_set_on_ipc_AlarmSet(dev_on_ipc_AlarmSet);
        avsdk_set_on_ipc_AlarmGet(dev_on_ipc_AlarmGet);
        /* avsdk_set_on_ipc_PirSet(dev_on_ipc_PirSet); */
        /* avsdk_set_on_ipc_PirGet(dev_on_ipc_PirGet); */

        /* 文件传输 */
//		avsdk_set_on_ipc_FileStart(dev_on_ipc_FileStart);
//		avsdk_set_on_ipc_FileStop(dev_on_ipc_FileStop);

        /* 用户自定义命令 */
        avsdk_set_on_ipc_CustomCmd(dev_on_ipc_CustomCmd);

        /*获取所有配置信息*/
        avsdk_set_on_ipc_ConfigGet(dev_on_ipc_ConfigGet);

        /* 其他接口 */
        avsdk_set_on_ipc_Screenshot(dev_on_ipc_Screenshot);
        avsdk_set_on_ipc_FirmwareNotify(dev_on_ipc_FirmwareNotify);
        avsdk_set_on_ipc_Reboot(dev_on_ipc_Reboot);
        avsdk_set_on_ipc_Reset(dev_on_ipc_Reset);
        avsdk_set_on_ipc_LanAuth(dev_on_ipc_LanAuth);
        avsdk_set_on_ipc_StorageInfo(dev_on_ipc_StorageInfo);
        avsdk_set_on_ipc_StorageFormat(dev_on_ipc_StorageFormat);
        avsdk_set_on_ipc_LogSet(dev_on_ipc_LogSet);
        avsdk_set_on_ipc_VideoChanChange(dev_on_ipc_VideoChanChange);

        /* 文件接收 */
//        avsdk_set_on_RecvFile(dev_on_RecvFile);
        /* 相册相关命令 */
//        avsdk_set_on_ipc_DirCreate(dev_on_ipc_DirCreate);
//
//        avsdk_set_on_ipc_DirDel(dev_on_ipc_DirDel);
//        avsdk_set_on_ipc_DirEdit(dev_on_ipc_DirEdit);
//        avsdk_set_on_ipc_DirList(dev_on_ipc_DirList);
//
//        avsdk_set_on_ipc_FileAdd(dev_on_ipc_FileAdd);
//        avsdk_set_on_ipc_FileDel(dev_on_ipc_FileDel);
//        avsdk_set_on_ipc_FileEdit(dev_on_ipc_FileEdit);
//        avsdk_set_on_ipc_FileRecvRate(dev_on_ipc_FileRecvRate);
//        avsdk_set_on_ipc_FileThumList(dev_on_ipc_FileThumList);

        avsdk_set_on_ipc_ExecIOTCMD(dev_on_ipc_ExecIOTCMD);
    }

#if defined CONFIG_FORCE_UPGRAGE
    g_platform_check_timer_hdl = sys_timer_add_to_task("app_core", NULL, check, 10000);
#endif

    /* step5: 开始运行 sdk */
    rc = avsdk_start();
    T_I("--->avsdk_start, rc:%d(%s)\n", rc, avsdk_strerror(rc));
    /* os_time_dly(800); */
    /* while(1) { */

    /* motion_detection_init(); */
    /* os_time_dly(800); */
    /* motion_detection_uninit(); */
    /* os_time_dly(100); */

    /* } */
    /* os_time_dly(400); */
    /* user_video_rec0_open(); */

    return 0;
}



/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

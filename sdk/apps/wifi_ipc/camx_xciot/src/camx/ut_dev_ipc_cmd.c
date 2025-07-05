/*****************************************************************************
 * ut_ipc_cmd.c
 *
 ****************************************************************************/

/*****************************************************************************
 * Included Files
 ****************************************************************************/
#include "camx.h"
#include "app_database.h"
#include "xciot_api.h"
#include "wifi/wifi_connect.h"
// #include <stdbool.h>

#if ENABLE_DEMO_AV > 1
#include "example_ctx.h"
#endif

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>



/*****************************************************************************
 * Trace Definitions
 ****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "ut_dev_ipc_cmd.c"
#include "xc_log.h"



#ifdef ENABLE_OSAL
#include "osal/osal_api.h"
#endif

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define OSAL_POINTER_TO_UINT(x) ((uintptr_t)(x))
#define OSAL_UINT_TO_POINTER(x) ((void *)(uintptr_t)(x))
#define OSAL_POINTER_TO_INT(x) ((intptr_t)(x))
#define OSAL_INT_TO_POINTER(x) ((void *)(intptr_t)(x))

/*****************************************************************************
 * Private Types
 ****************************************************************************/
#define USE_CONTINUOUS_VIDEO 1
/*****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/*****************************************************************************
 * Private Data
 ****************************************************************************/

/*****************************************************************************
 * Public Data
 ****************************************************************************/
#if ENABLE_DEMO_AV > 1

extern pthread_ctx_t thr_hv_ctx;
extern char g_history_h264_file[2048];
extern void *video_history_thread(void *);
//extern void set_night_sensor_GC0328(u16 rev_flag);
/* extern void set_rev_sensor_GC0328(u16 rev_flag); */

#endif

/*****************************************************************************
 * Private Functions
 ****************************************************************************/

#if 1

struct xc_test {
    char wifi_ssid[50];
    char wifi_key[50];
    int32_t video_qos;
    int32_t video_speed;
    int32_t flip;  //翻转信息: 1: Upright, 2: Flip Horizontal，3 :Flip Vertical，4: turn 180
    uint32_t volume_value;

    int32_t  history_plan_record_type;           // 录像类型: 1, 连续录像; 2, 事件录像
    xciot_Timetask  history_plan_tt[3];             // 时间段(最多3个)
    int32_t   history_plan_plan_count;               // 个数
    int32_t   history_plan_enable;                    //  是否开启录像；0：disable;1 enable

    int32_t  led_mode;            //  LED状态: 1 常开；2 常关；
    int32_t  ircut_mode;          // IRCut状态: 1 常开；2 常关； 3 自动
    int32_t  secret_mode;         // 私密模式: 0 不开启私有模式; 1 开始私有模式
    ipc_ConfigGet_NotifyInfo  notify;          //  通知参数
    uint32_t power_freq;

    char time_zone[32];              // 字符串，采用标准时区，时区信息携带了夏令时等信息
    int32_t time_dst;                  //  是否开启夏令时: 0: disable; 1: enable
    int32_t time_offset;			// 时间偏移，分钟
    ipc_MotionzoneSet_Req_mz_t motion_mz;              //  将显示区域划分为: 22x18的区块，共需要50个字节来表示，该区块被选中，则为1，反之为0
    ipc_MotionzoneSet_XYPoint  motion_xy_point[5];              //  界面设置的坐标
    int32_t   motion_num_point;                 //  坐标的点数, 最大5个

    ipc_PspList_PspInfo  pspinfo_arr[5];

    int32_t  Timedcruise_states;                //  status: 0 disable; 1 enable;
    int32_t  Timedcruise_mode;                  //  巡航模式: 1, 完整巡航; 2, 预置点巡航;
    xciot_Timetask Timedcruise_tt;                //  时间参数
    int32_t  Timedcruise_interval;               // 巡航时间间隔,单位秒；取值范围: 600-43200 之间的数据
    int64_t  autotrack;                         //自动跟踪: 0, 关闭; 1, 开启，

    int32_t motion_detection;
    int32_t opensound_detection;
    int32_t smoke_detection;
    int32_t shadow_detection;

    uint32_t  event_record_duration; //录像时间长度

};

struct xc_test g_test_t;

int32_t get_time_offset()
{
    return g_test_t.time_offset;
}


void cmd_test_init(void)
{
    memset(&g_test_t, 0, sizeof(g_test_t));
    strcpy(g_test_t.wifi_ssid, "ssid");
    strcpy(g_test_t.wifi_key, "wifi_key");
    g_test_t.video_qos = 15;
    g_test_t.flip = 0;
    g_test_t.volume_value = 2;
    g_test_t.history_plan_record_type = 1;

    g_test_t.history_plan_plan_count = 0;
    g_test_t.history_plan_enable = 1;
    g_test_t.led_mode = 1;
    g_test_t.ircut_mode = 1;
    g_test_t.secret_mode = 0;

    g_test_t.power_freq = 50;
    strcpy(g_test_t.time_zone, "UTC-8");
    g_test_t.time_dst = 1;
    g_test_t.notify.states = 1;
    g_test_t.notify.level = 1;
    g_test_t.motion_mz.bytes[0] = 1;

    g_test_t.motion_num_point = 3;
    for (int i = 0; i < g_test_t.motion_num_point; i++) {
        g_test_t.motion_xy_point[i].leftup_x = 20 + i;
        g_test_t.motion_xy_point[i].leftup_y = i;
        g_test_t.motion_xy_point[i].rightdown_x = 10 + i;
        g_test_t.motion_xy_point[i].rightdown_y = 5 + i;
    }

    g_test_t.Timedcruise_states = 1;
    g_test_t.motion_detection = 1;
    g_test_t.smoke_detection = 1;
    g_test_t.shadow_detection = 1;
    g_test_t.event_record_duration = 2;
}



void *firmware_notify_thread(void *arg)
{
#if 0
    int rc = 0;
    if ((rc = pthread_detach(pthread_self())) != 0) {
        T_E("pthread_detach: %s", strerror(rc));
    }

    int32_t  conn_id = OSAL_POINTER_TO_UINT(arg);
    // here we notice the user progress of upgrading
    for (int index = 1; index <= 100; index += 1) {
        avsdk_firmware_rate(conn_id, 0, index);
        T_D("avsdk_firmware_rate %d", index);
        usleep(100);
    }

    // reach progress 100%, upgrade finish success
    avsdk_firmware_rate(conn_id, 0, 100);
#endif
    return NULL;

}


void *storage_format_thread(void *arg)
{
#if 0
    int rc = 0;
    if ((rc = pthread_detach(pthread_self())) != 0) {
        T_E("pthread_detach: %s", strerror(rc));
    }

    int32_t  conn_id = OSAL_POINTER_TO_UINT(arg);
    T_D("conn_id: %d ", conn_id);
    // here we notice the user progress of upgrading
    for (int index = 1; index <= 100; index += 1) {
        T_D("storage_format_rate: %d ", index);
        avsdk_storage_format_rate(conn_id, 0, index);
        sleep(1);
    }

    // reach progress 100%, upgrade finish success
    avsdk_storage_format_rate(conn_id, 0, 100);
#endif
    return NULL;
}

void *demo_report_timezone(void *arg)
{
#if 0
    int rc = 0;
    if ((rc = pthread_detach(pthread_self())) != 0) {
        T_E("pthread_detach: %s", strerror(rc));
    }
    int32_t  conn_id = OSAL_POINTER_TO_UINT(arg);
    T_D("conn_id: %d ", conn_id);
    avsdk_report_TimeZone(g_test_t.time_zone);
#endif
    return NULL;
}

void report_timezone(int32_t conn_id)
/* void report_timezone(void *arg) */
{
    T_D("g_test_t.time_zone = %s", g_test_t.time_zone);

    avsdk_report_TimeZone(g_test_t.time_zone);
    dev_base_info_t info = {0};
    int TIMEZONE = db_select("tzone");

    if (TIMEZONE > 8000) {
        int t1 = (TIMEZONE ^ 0x7FFF) + 1;
        TIMEZONE = -(t1 & 0x7FFF);
    }

    info.timeOffset = TIMEZONE;

    T_D("info.timeOffset = %d", info.timeOffset);
    avsdk_push_info(&info);

#if 0
    pthread_t tidp;
    int rc = pthread_create(&tidp, NULL, demo_report_timezone, OSAL_UINT_TO_POINTER(conn_id));
    OSAL_ASSERT(rc == 0);
#endif
}



#if 0
bool dev_on_ipc_Discovery(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_Discovery_Req *req,
    /* output  */ ipc_Discovery_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_I("conn[%d]ipc_Discovery_Req:", conn_id);
    T_T("\t did       :%s", req->did);
    T_T("\t class_code:%s", req->class_code);

    /*注意，该接口只需填入mode、ipaddr、netmask三个参数，其他内部复写填充*/

    /*设备模式(wifi)： 1 AP 模式; 2 STD模式;*/
    rsp->mode = 1;

    /*需要用户填写真实的ip和netmask*/
#if 1
    snprintf(rsp->ipaddr, sizeof(rsp->ipaddr), "%s", "192.168.1.1");
    snprintf(
        rsp->netmask, sizeof(rsp->netmask), "%s", "255.255.255.0");
#endif
    return retval;
}
#endif

bool dev_on_ipc_WifiAPGet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_WifiAPGet_Req *req,
    /* output  */ ipc_WifiAPGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("conn[%d]ipc_WifiAPGet_Req:", conn_id);
    T_I("\t channel:%d", req->channel);

    struct wifi_scan_ssid_info *sta_ssid_info;
    u32 sta_ssid_num;

    wifi_clear_scan_result();// 测试之前清掉之前连接路由器的扫描缓存,也可以放在STA连上后调用

    wifi_scan_req();
    sta_ssid_num = 0;
    os_time_dly(250);
    sta_ssid_info = wifi_get_scan_result(&sta_ssid_num);


    /* printf("wifi_sta_scan_test ssid_num =%d \r\n", sta_ssid_num); */
    for (int i = 0; i < sta_ssid_num; i++) {
        /* printf("wifi_sta_scan_test ssid = [%s],rssi = %d,snr = %d, enc = %d\r\n", sta_ssid_info[i].ssid, sta_ssid_info[i].rssi, sta_ssid_info[i].snr, sta_ssid_info[i].enc); */
        strcpy(rsp->wifis[i].ssid, sta_ssid_info[i].ssid);

        rsp->wifis[i].qos  = sta_ssid_info[i].rssi;
        if (ENC_MODE_BIT_IS_SET(sta_ssid_info[i].enc, ENC_WPA2)) {
            rsp->wifis[i].encrypt = 11;

        } else if (ENC_MODE_BIT_IS_SET(sta_ssid_info[i].enc, ENC_WPA)) {
            rsp->wifis[i].encrypt = 11;

        } else if (ENC_MODE_BIT_IS_SET(sta_ssid_info[i].enc, ENC_WEP)) {
            rsp->wifis[i].encrypt = 11;

        } else {
            rsp->wifis[i].encrypt =	 1;

        }

        printf("rsp->wifis[i].encrypt === %d\n", rsp->wifis[i].encrypt);
        T_D("wifi_info->info_arr_[%d].ssid_ :%s ", i, rsp->wifis[i].ssid);
    }

    rsp->wifis_count  = sta_ssid_num;
    rsp->support = 1;


    /* free(resp); */
    /* resp = NULL; */
    // todo 填充设备扫描到wifi列表

    return retval;
}

static void wifi_sta_connect(void)
{
    /* save_ssid_flag = save; */
    char *ssid = g_test_t.wifi_ssid;
    char *pwd = g_test_t.wifi_key;
    int err = 0;
    wifi_set_sta_connect_best_ssid(0);
    wifi_enter_sta_mode(ssid, pwd);
    wifi_store_mode_info(STA_MODE, ssid, pwd);

    wifi_enter_sta_mode(ssid, pwd);
    os_time_dly(600);
    cpu_reset(); //切换网络成功，设备重启
}

bool dev_on_ipc_WifiSet(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_WifiSet_Req *req,
    /* output  */ ipc_WifiSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("conn[%d]ipc_WifiSet_Req:", conn_id);
    T_I("\t channel:%d", req->channel);
    T_I("\t ssid   :%s", req->ssid);
    T_I("\t pwd    :%d", req->pwd);

    //@todo 退出AP模式，去连接下发wifi网络
    strcpy(g_test_t.wifi_ssid, req->ssid);
    strcpy(g_test_t.wifi_key, req->pwd);
//异步处理
    thread_fork("WIFI_STA_SWITCH_THREAD", 10, 2048, 64, 0,	wifi_sta_connect, NULL);


    /* snprintf(g_IpcParam.wifi_ssid, sizeof(g_IpcParam.wifi_ssid), "%s", ssid); */
    /* snprintf(g_IpcParam.wifi_key, sizeof(g_IpcParam.wifi_key), "%s", key); */
    return retval;
}

bool dev_on_ipc_WifiGet(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_WifiGet_Req *req,
    /* output  */ ipc_WifiGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("conn[%d]ipc_WifiGet_Req:", conn_id);
    T_I("\t channel:%d", req->channel);

    //todo填充wifi信息
    struct wifi_mode_info mode_info = {0};
    mode_info.mode = STA_MODE;

    wifi_get_mode_cur_info(&mode_info);

    strcpy(rsp->ssid, mode_info.ssid);
    rsp->qos = wifi_get_cqi();

    /* printf("mode_info.ssid===%s\n",mode_info.ssid); */
    /* printf("rsp->ssid===%s\n",rsp->ssid); */
    /* printf("rsp->qos===%d\n",rsp->qos); */

    rsp->support = 1;


    return retval;
}

bool dev_on_ipc_VideoPlay(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_VideoPlay_Req *req,
    /* output  */ ipc_VideoPlay_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    int ret = 0;
    int i = 0;
    T_I("conn[%d]ipc_VideoPlay_Req:", conn_id);
    T_I("\t channel:%d", req->channel);
    T_I("\t qos    :%d", req->qos);
    T_I("\t speed  :%d", req->speed);

    /*将连接ID添加到视频播放用户组*/
    extern int cloud_playback_uninit(int32_t conn_id,  uint64_t file_id);
    cloud_playback_uninit(conn_id, 0);

    avsdk_video_add_conn(conn_id, req->channel);

#if 0
    do {
        struct application *app = get_current_app();
        if (app) {
            os_time_dly(50);
            continue;
        }
        ret = user_video_rec0_open();
        i++;
        if (ret < 0) {
            os_time_dly(50);
        }
        printf("==================%s  %d\n", __func__, __LINE__);
    } while (ret < 0 && i < 3);
#endif

    void **user_video_handle = get_user_video_handle();
    *user_video_handle = user_video_rec_open(TCFG_USER_VIDEO_SOURCE);

    //todo填充视频信息
    rsp->qos = 16;
    rsp->fps = VIDEO_REC_FPS;
    rsp->format = E_IOT_MEDIASTREAM_TYPE_MJPEG;
    rsp->render = 0;
    return retval;
}

bool dev_on_ipc_VideoPause(
    /* conn_id */ int32_t              conn_id,
    /* input   */ ipc_VideoPause_Req *req,
    /* output  */ ipc_VideoPause_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    printf("conn[%d]ipc_VideoPause_Req:", conn_id);
    printf("\t channel:%d", req->channel);
    void **user_video_handle = get_user_video_handle();
    if (*user_video_handle) {
        user_video_rec_close(*user_video_handle);
        *user_video_handle = NULL;

    }

    /*将连接ID从视频播放用户组删除*/
    avsdk_video_del_conn(conn_id, req->channel);

    return retval;
}

#if 0
bool dev_on_ipc_VideoQosSet(
    /* conn_id */ int32_t               conn_id,
    /* input   */ ipc_VideoQosSet_Req *req,
    /* output  */ ipc_VideoQosSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    printf("conn[%d]ipc_VideoQosSet_Req:", conn_id);
    printf("\t channel:%d", req->channel);
    printf("\t qos    :%d", req->qos);
    printf("\t speed  :%d", req->speed);

    //todo设置视频质量
    g_test_t.video_qos = req->qos;
    g_test_t.video_speed = req->speed;

    return retval;
}
#endif

bool dev_on_ipc_FlipSet(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_FlipSet_Req *req,
    /* output  */ ipc_FlipSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_I("---->dev_on_ipc_FlipSet");
    T_I("\t req->flip:%d", req->flip);
    // todo 视频翻转
#define HORIZONTAL_FLIP    0x0
#define VERTICAL_FLIP      0x1
    static u8 status = 0;
    //需要立刻更新
    switch (req->flip) {
    case 1:
        status = 0;
        break;
    case 2:
        if (status & BIT(HORIZONTAL_FLIP)) {
            status &= ~BIT(HORIZONTAL_FLIP);
        } else {
            status |= BIT(HORIZONTAL_FLIP);
        }
        break;
    case 3:
        if (status & BIT(VERTICAL_FLIP)) {
            status &= ~BIT(VERTICAL_FLIP);
        } else {
            status |= BIT(VERTICAL_FLIP);
        }
        break;
    case 4:
        status = BIT(HORIZONTAL_FLIP) | BIT(VERTICAL_FLIP);
        break;

    default:
        break;

    }

    db_update("mir", status); //同步tg
    printf(" filp status:%d\n", status);


//todo 暂时关掉
    /* set_rev_sensor(status); */


    return retval;

}

bool dev_on_ipc_AudioPlay(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_AudioPlay_Req *req,
    /* output  */ ipc_AudioPlay_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_I("conn[%d]ipc_AudioPlay_Req:", conn_id);
    T_I("\t channel:%d", req->channel);

    /*将连接ID添加到音频播放用户组*/
    avsdk_audio_add_conn(conn_id);

    //todo 填充音频参数
    rsp->bit = 16;
    rsp->code = 0;
    rsp->codec = E_IOT_MEDIASTREAM_TYPE_PCM;
    rsp->track = 1;
    rsp->rate = 8000;

#if 0
    static uint8_t init = 0;
    extern int audio_start(void);
    if (init == 0) {
        audio_start();
        init = 1;
    }

#endif

    T_I("rsp->bit:%d", rsp->bit);
    T_I("rsp->code:%d", rsp->code);
    T_I("rsp->codec:%d", rsp->codec);
    T_I("rsp->track:%d", rsp->track);
    T_I("rsp->rate:%d", rsp->rate);
    return retval;
}

bool dev_on_ipc_AudioPause(
    /* conn_id */ int32_t              conn_id,
    /* input   */ ipc_AudioPause_Req *req,
    /* output  */ ipc_AudioPause_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("conn[%d]ipc_AudioPause_Req:", conn_id);
    T_I("\t channel:%d", req->channel);

    /*将连接ID从音频播放用户组删除*/
    avsdk_audio_del_conn(conn_id);

    return retval;
}

bool dev_on_ipc_TalkbackPlay(
    /* conn_id */ int32_t                conn_id,
    /* input   */ ipc_TalkbackPlay_Req *req,
    /* output  */ ipc_TalkbackPlay_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    /* 返回设置支持的音频格式 */

    rsp->codec = E_IOT_MEDIASTREAM_TYPE_PCM;       	// codec type
    rsp->rate  = 8000;               					// 8000? audio frequency
    rsp->bit   = 16;                 					// 16bit?
    rsp->track = 1;                  					// mono
    rsp->code  = 2;                  					// normal mode
    int xc_talkback_start(void);
    xc_talkback_start();
    return retval;
}

bool dev_on_ipc_TalkbackPause(
    /* conn_id */ int32_t                 conn_id,
    /* input   */ ipc_TalkbackPause_Req *req,
    /* output  */ ipc_TalkbackPause_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    //设备不需要处理
    int xc_talkback_stop(void);
    xc_talkback_stop();
    printf("=======================================%s %d\n", __func__, __LINE__);
    return retval;
}

bool dev_on_ipc_HistoryPlanSet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_HistoryPlanSet_Req *req,
    /* output  */ ipc_HistoryPlanSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("---->dev_on_ipc_HistoryPlanSet");
    T_D("%s called ", __func__);

    //todo 配置录像方式

    T_D("plan_count: %d ", req->tt_count);
    T_D("enable = %d", req->enable);

    extern unsigned char REC_FLAG; /*0-不录像;1-录像*/

    REC_FLAG = req ->enable;
    db_update("rec_evet", req->record_type); //1 默认是连续录像，2是事件录像
    T_D("req->record_type: %d ", req->record_type);

    /* g_test_t.history_plan_record_type = req->record_type; */
    /* g_test_t.history_plan_plan_count = req->tt_count; */
    /* for (int32_t i = 0; i < req->tt_count; i++) { */
    /* memcpy(&g_test_t.history_plan_tt[i], &req->tt[i], sizeof(req->tt[i])); */
    /* } */
    /* g_test_t.history_plan_enable = req->enable; */

    return retval;
}

bool dev_on_ipc_HistoryPlanGet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_HistoryPlanGet_Req *req,
    /* output  */ ipc_HistoryPlanGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("---->dev_on_ipc_HistoryPlanGet");
    //todo 返回录像方式

    extern unsigned char REC_FLAG; /*0-不录像;1-录像*/
    rsp->enable = REC_FLAG;
    rsp->record_type = db_select("rec_evet");

    /* memset(rsp->tt, 0, sizeof(rsp->tt)); */
    /* rsp->record_type = g_test_t.history_plan_record_type; */
    /* rsp->tt_count = g_test_t.history_plan_plan_count; */

    /* for (int32_t i = 0; i < g_test_t.history_plan_plan_count; i++) { */
    /* memcpy(&rsp->tt[i], &g_test_t.history_plan_tt[i], sizeof(g_test_t.history_plan_tt[i])); */
    /* } */
    /* rsp->enable = g_test_t.history_plan_enable; */

    /* T_D("plan_count: %d ", rsp->tt_count); */
    T_D("rsp->record_type: %d ", rsp->record_type);
    T_D("enable = %d", rsp->enable);


    return retval;
}

bool dev_on_ipc_HistoryDays(
    /* conn_id */ int32_t               conn_id,
    /* input   */ ipc_HistoryDays_Req *req,
    /* output  */ ipc_HistoryDays_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    printf("\n >>>>>>>>>>>>>>>>>>>>  %s %d\n", __func__, __LINE__);
    /* retval - true: support, false: unsupport */
    bool retval = true;

    // todo 返回历史记录天数
    /* extern int cloud_playback_list_get_days(void *__req, void *__rsp); */
    cloud_playback_list_get_days(req, rsp);

    return retval;
}

bool dev_on_ipc_HistoryDayList(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_HistoryDayList_Req *req,
    /* output  */ ipc_HistoryDayList_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_I("----------dev_on_ipc_HistoryDayList--------");
    // todo 返回历史记录列表
    /* Fill output rsp, after this function, sdk will send rsp to remote */
    /* 录像分为两类，1.事件录像；2.全添录像,选择一种填写rsp */
    extern int cloud_playback_list_get(void *req, void *rsp);
    cloud_playback_list_get(req, rsp);

    return retval;
}

bool dev_on_ipc_HistoryPlay(
    /* conn_id */ int32_t               conn_id,
    /* input   */ ipc_HistoryPlay_Req *req,
    /* output  */ ipc_HistoryPlay_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_I("conn[%d]dev_on_ipc_HistoryPlay:", conn_id);
    T_I("\t channel:%d", req->channel);
    T_D("\t file_id:%lld", req->file_id);
    T_D("\t start_time:%lld", req->start_time);
    int file_id = 0;
    //todo 播放file_id响应的历史视频
    if (!req->file_id) {
        file_id = cloud_playback_file(req->start_time / 1000);
        printf("file_id:%d\n", file_id);
    } else {
        file_id = req->file_id;
    }
    //sprintf(g_history_h264_file, "%llu.h264", req->file_id)

    /* Fill output rsp, after this function, sdk will send rsp to remote */
    {

        rsp->code = 0; //成功
        //本地录像无mp4封装，声音格式只能为pcm
        rsp->codec = E_IOT_MEDIASTREAM_TYPE_PCM;
        rsp->rate = video_rec_get_audio_sampel_rate();
        rsp->bit = 16;
        rsp->track = 1;
        rsp->fps = VIDEO_REC_FPS;


        extern int cloud_playback_uninit(int32_t conn_id,  uint64_t file_id);
        cloud_playback_uninit(conn_id, file_id);
        extern int cloud_playback_init(int32_t conn_id,  uint64_t file_id, int64_t start_time);
        cloud_playback_init(conn_id, file_id, req->start_time / 1000);
    }

    return retval;
}

bool dev_on_ipc_HistoryPause(
    /* conn_id */ int32_t                conn_id,
    /* input   */ ipc_HistoryPause_Req *req,
    /* output  */ ipc_HistoryPause_Resp *rsp)
{
    printf("\n >>>>>>>>>>>>>>>>>>>>  %s %d\n", __func__, __LINE__);
    T_D("----------------dev_on_ipc_HistoryPause-----------------");
    /* retval - true: support, false: unsupport */
    bool retval = true;

    extern int cloud_playback_uninit(int32_t conn_id,  uint64_t file_id);
    cloud_playback_uninit(conn_id, req->file_id);

#if ENABLE_DEMO_AV > 1
    // todo 停止播放历史视频
    if (thr_hv_ctx.init == false) {
        /* 未建立线程 */
    } else {
        thr_hv_ctx.init = false;
        thr_hv_ctx.conn_id = -1;
        thr_hv_ctx.toexit = true;
        T_D("----------------close_video_history_thread-----------------");
    }
#endif
    return retval;
}

bool dev_on_ipc_HistoryThumGet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_HistoryThumGet_Req *req,
    /* output  */ ipc_HistoryThumGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    // todo 获取历史视频的缩略图

    // Fill output rsp, after this function, sdk will send rsp to remote
    {
        int get_file_thm(char *name, char type, char *thm_addr, int len);
        char name[64] = {0};
        char file_name[64] = {0};
        printf("\nreq->thum_fid =%llu \n", req->thum_fid);
        snprintf(file_name, sizeof(file_name), "%sVID_%04d.AVI", CONFIG_REC_PATH_0, req->thum_fid);
        printf("thum file path:%s\n", file_name);
        rsp->thum_body.size = 3000;//get_file_thm(file_name, 0, rsp->thum_body.bytes, sizeof(rsp->thum_body.bytes));

        /* put_buf(rsp->thum_body.bytes, 64); */
    }
    /* printf("size:%d\n", rsp->thum_body.size); */
    return retval;




}

bool dev_on_ipc_HistoryDel(
    /* conn_id */ int32_t              conn_id,
    /* input   */ ipc_HistoryDel_Req *req,
    /* output  */ ipc_HistoryDel_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    printf("\n >>>>>>>>>>>>>>>>>>>>  %s %d\n", __func__, __LINE__);
    //todo 删除对应的历史视频
    extern int cloud_playback_list_remove(void *__req, void *__rsp);
    cloud_playback_list_remove(req, rsp);
    return retval;
}

bool dev_on_ipc_ConfigGet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_ConfigGet_Req *req,
    /* output  */ ipc_ConfigGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------dev_on_ipc_ConfigGet-------");
    //todo 获取所有的配置信息
#if 1
    /* Fill output rsp, after this function, sdk will send rsp to remote */
    {
        T_D("dev_on_ipc_ConfigGet");
        /* rsp->flip = g_test_t.flip; */
        rsp->flip = db_select("mir");
        rsp->led_mode = g_test_t.led_mode;
        /* rsp->ircut_mode = g_test_t.ircut_mode; */
        rsp->ircut_mode = db_select("irc");
        rsp->secret_mode = g_test_t.secret_mode;
        memcpy(&rsp->notify, &g_test_t.notify, sizeof(g_test_t.notify));
        rsp->power_freq = g_test_t.power_freq;
        rsp->volume = g_test_t.volume_value;
        rsp->duration = 15;
    }
#endif

    return retval;
}

bool dev_on_ipc_TimeSet(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_TimeSet_Req *req,
    /* output  */ ipc_TimeSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("-------dev_on_ipc_TimeSet--------");
    T_D("req->now_time = %ld", req->now_time);
    T_D("req->dst = %d", req->dst);
    T_D("req->offset = %d", req->offset);
    T_D("req->time_zone = %s", req->time_zone);
    // todo 设置设备的时间
    strcpy(g_test_t.time_zone, req->time_zone);
    db_update("tzone", req->offset);
    g_test_t.time_dst = req->dst;
    g_test_t.time_offset = req->offset;

    thread_fork("REPORT_TIMERZONE_THREAD", 10, 1024, 64, 0, report_timezone, g_test_t.time_zone);
    extern void set_utc_ms(uint64_t utc_ms);
    extern	uint64_t get_utc_ms(void);
    set_utc_ms(get_utc_ms());

    /* report_timezone(conn_id); */
    /* avsdk_report_TimeZone(req->time_zone); */
    return retval;
}

bool dev_on_ipc_TimeGet(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_TimeGet_Req *req,
    /* output  */ ipc_TimeGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("-------dev_on_ipc_TimeGet--------");
    // todo 获取设备的时间
    /* extern void set_utc_ms(uint64_t utc_ms); */
    /* extern	uint64_t get_utc_ms(void); */
    /* set_utc_ms(get_utc_ms()); */

    /* rsp->now_time = set_utc_ms(get_utc_ms()); */
    int TIMEZONE = db_select("tzone");

    if (TIMEZONE > 8000) {
        int t1 = (TIMEZONE ^ 0x7FFF) + 1;
        TIMEZONE = -(t1 & 0x7FFF);
    }


    rsp->now_time    = time(0) + TIMEZONE;
    T_D("req->now_time = %lld", rsp->now_time);
    strcpy(rsp->time_zone, g_test_t.time_zone);
    rsp->dst = g_test_t.time_dst;
    rsp->offset = g_test_t.time_offset;

    return retval;
}
#if 0
bool dev_on_ipc_LedSet(
    /* conn_id */ int32_t          conn_id,
    /* input   */ ipc_LedSet_Req *req,
    /* output  */ ipc_LedSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    // todo 设置LED模式
    g_test_t.led_mode = req->mode;

    return retval;
}

bool dev_on_ipc_LedGet(
    /* conn_id */ int32_t          conn_id,
    /* input   */ ipc_LedGet_Req *req,
    /* output  */ ipc_LedGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    //todo 获取led的模式
    rsp->mode = g_test_t.led_mode;


    return retval;
}
#endif

bool dev_on_ipc_IRCutSet(
    /* conn_id */ int32_t            conn_id,
    /* input   */ ipc_IRCutSet_Req *req,
    /* output  */ ipc_IRCutSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("-------dev_on_ipc_IRCutSet--------");
    // todo 设置夜视模式
    printf("req->mode ====%d\n", req->mode);
    if (req->mode == 1) {
        db_update("irc", 1);
        //todo
        /* set_night_sensor(1); */

        /*set_night_sensor_GC0328(1);*/

    } else {
        db_update("irc", 2);
        //todo
        /* set_night_sensor(0); */

        /*set_night_sensor_GC0328(0);*/
    }



    /* g_test_t.ircut_mode = req->mode; */

    return retval;

}

bool dev_on_ipc_IRCutGet(
    /* conn_id */ int32_t            conn_id,
    /* input   */ ipc_IRCutGet_Req *req,
    /* output  */ ipc_IRCutGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("-------dev_on_ipc_IRCutGet--------");
    //todo 获取夜视模式
    /* rsp->mode = g_test_t.ircut_mode; */


    rsp->mode = db_select("irc");
    if (rsp ->mode == 0) {
        printf("------------->>>>db_write_irc err\n");
        db_update("irc", 2);
        rsp ->mode = db_select("irc");
    }

    printf("req->mode ====%d\n", rsp->mode);
    return retval;
}

bool dev_on_ipc_SecretSet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_SecretSet_Req *req,
    /* output  */ ipc_SecretSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    // todo 设置私有模式
    T_D("-------dev_on_ipc_SecretSet--------");
    extern unsigned char MICO_CTL;
    printf("req->secret ====%d\n", req->secret);
    MICO_CTL = req->secret;
    /* g_test_t.secret_mode = ; */
    /* db_update("mirco",req->secret); */


    return retval;
}

bool dev_on_ipc_SecretGet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_SecretGet_Req *req,
    /* output  */ ipc_SecretGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    // todo 返回私有模式
    T_D("-------dev_on_ipc_SecretGet--------");
    /* rsp->secret = g_test_t.secret_mode; */
    extern unsigned char MICO_CTL;
    rsp->secret = MICO_CTL;

    printf("rsp->secret ====%d\n", rsp->secret);

    return retval;
}

bool dev_on_ipc_NotifySet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_NotifySet_Req *req,
    /* output  */ ipc_NotifySet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    //todo 设置事件触发方式

    /* Analysis input req */
    {
        g_test_t.notify.states = req->states;
        T_D("notify.states: %d ", g_test_t.notify.states);
        T_D("days_count_: %d ", req->tt.days_count);
        for (int i = 0; i < req->tt.days_count; i++) {
            T_D("days_[%d]: %d ", i, req->tt.days[i]);
        }

        T_D("week_day_count_: %d ", req->tt.week_day_count);
        for (int i = 0; i < req->tt.week_day_count; i++) {
            T_D("week_day_[%d]: %d ", i, req->tt.week_day[i]);
        }

        T_D("time_count_: %d ", req->tt.time_count);
        for (int i = 0; i < req->tt.time_count; i++) {
            T_D("time_info_[%d].start_sec_: %d ", i, req->tt.time[i].start_sec);
            T_D("time_info_[%d].end_sec_: %d ", i, req->tt.time[i].end_sec);
        }

        memcpy(&g_test_t.notify.tt, &req->tt, sizeof(req->tt));
        g_test_t.notify.level = req->level;
        printf("g_test_t.notify.level%d\n", req->level);
        switch (g_test_t.notify.level) {
        case 3 :
            db_update("time_level", 30);
            break;
        case 2 :
            db_update("time_level", 60);
            break;
        case 1 :
            db_update("time_level", 180);
            break;
        default:
            break;


        }
    }


    return retval;
}

bool dev_on_ipc_NotifyGet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_NotifyGet_Req *req,
    /* output  */ ipc_NotifyGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    //todo 获取事件触发方式

    /* Fill output rsp, after this function, sdk will send rsp to remote */
    {
        memcpy(&rsp->tt, &g_test_t.notify.tt, sizeof(g_test_t.notify.tt));
        rsp->level  = g_test_t.notify.level;
        rsp->states = g_test_t.notify.states;

        T_D("resp_level: %d ", rsp->level);
        T_D("resp_states: %d ", rsp->states);

        T_D("days_count_: %d ", rsp->tt.days_count);
        for (int i = 0; i < rsp->tt.days_count; i++) {
            T_D("days_[%d]: %d ", i, rsp->tt.days[i]);
        }

        T_D("week_day_count_: %d ", rsp->tt.week_day_count);
        for (int i = 0; i < rsp->tt.week_day_count ; i++) {
            T_D("week_day_[%d]: %d ", i, rsp->tt.week_day[i]);
        }

        T_D("time_count_: %d ", rsp->tt.time_count);
        for (int i = 0; i < rsp->tt.time_count ; i++) {
            T_D("time_info_[%d].start_sec_: %d ", i, rsp->tt.time[i].start_sec);
            T_D("time_info_[%d].end_sec_: %d ", i, rsp->tt.time[i].end_sec);
        }
    }

    return retval;
}

bool is_need_mov_detecte(time_t time)
{
    struct tm *time_te = NULL;
    int flag;
    int32_t cur_sec;
    if (0 == (g_test_t.notify.states)) {
        return false;
    }

    time_te = localtime(&time);
    flag = 0;
    for (int i = 0; i < 7; i++) {
        if ((time_te->tm_wday) == (g_test_t.notify.tt.week_day[i])) {
            flag = 1;
            break;

        }
    }
    if (flag == 0) {
        return false;
    }
    cur_sec = (time_te->tm_hour) * 60 * 60 + time_te->tm_sec;
    printf("cur_sec=====%d\n", cur_sec);
    if ((cur_sec > (g_test_t.notify.tt.time[0].start_sec)) && (cur_sec < (g_test_t.notify.tt.time[0].end_sec))) {
        return true;
    }
    return false;
}

#if 0
bool dev_on_ipc_MotionzoneSet(
    /* conn_id */ int32_t                 conn_id,
    /* input   */ ipc_MotionzoneSet_Req *req,
    /* output  */ ipc_MotionzoneSet_Resp *rsp)
{
    T_I("---------dev_on_ipc_MotionzoneSet--------");
    /* retval - true: support, false: unsupport */
    bool retval = true;

    /* Motionzone */
    {
        T_I("---------MotionzoneSet  mz.size=%d--------", req->mz.size);
        for (int i = 0; i < req->mz.size; i++) {
            T_I("[%d]=%d", i, req->mz.bytes[i]);
        }
    }
    /* Analysis XYPoint req */
    {
        for (int i = 0; i < req->points_count; i++) {
            T_D("xy_point[%d].leftup_x: %d ", i, req->points[i].leftup_x);
            T_D("xy_point[%d].leftup_y: %d ", i, req->points[i].leftup_y);
            T_D("xy_point[%d].rightdown_x: %d ", i, req->points[i].rightdown_x);
            T_D("xy_point[%d].rightdown_y: %d ", i, req->points[i].rightdown_y);

        }

        memcpy(&g_test_t.motion_mz, &req->mz, sizeof(ipc_MotionzoneSet_Req_mz_t));
        g_test_t.motion_num_point = req->points_count;
        for (int i = 0; i < req->points_count; i++) {
            g_test_t.motion_xy_point[i].leftup_x = req->points[i].leftup_x;
            g_test_t.motion_xy_point[i].leftup_y = req->points[i].leftup_y;
            g_test_t.motion_xy_point[i].rightdown_x = req->points[i].rightdown_x;
            g_test_t.motion_xy_point[i].rightdown_y = req->points[i].rightdown_y;
        }
    }

    return retval;
}

bool dev_on_ipc_MotionzoneGet(
    /* conn_id */ int32_t                 conn_id,
    /* input   */ ipc_MotionzoneGet_Req *req,
    /* output  */ ipc_MotionzoneGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    memcpy(&rsp->mz, &g_test_t.motion_mz, sizeof(ipc_MotionzoneGet_Resp_mz_t));
    rsp->points_count = g_test_t.motion_num_point;
    for (int i = 0; i < rsp->points_count; i++) {
        rsp->points[i].leftup_x = g_test_t.motion_xy_point[i].leftup_x;
        rsp->points[i].leftup_y = g_test_t.motion_xy_point[i].leftup_y;
        rsp->points[i].rightdown_x = g_test_t.motion_xy_point[i].rightdown_x;
        rsp->points[i].rightdown_y = g_test_t.motion_xy_point[i].rightdown_y;
    }


    return retval;
}

bool dev_on_ipc_PspAdd(
    /* conn_id */ int32_t          conn_id,
    /* input   */ ipc_PspAdd_Req *req,
    /* output  */ ipc_PspAdd_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    for (int index = 0; index < 5; index++) {
        T_D("g_test_t.pspinfo_arr[%d].psp_id: %d ", index, g_test_t.pspinfo_arr[index].psp_id);
        if (g_test_t.pspinfo_arr[index].psp_id == 0) {
            g_test_t.pspinfo_arr[index].psp_id = index + 1;
            memcpy(g_test_t.pspinfo_arr[index].psp_name, req->psp_name, 16);
            g_test_t.pspinfo_arr[index].is_def = req->is_def;
            break;
        }
    }

    return retval;
}

bool dev_on_ipc_PspDel(
    /* conn_id */ int32_t          conn_id,
    /* input   */ ipc_PspDel_Req *req,
    /* output  */ ipc_PspDel_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    for (int index = 0; index < 5; index++) {
        if (g_test_t.pspinfo_arr[index].psp_id == req->psp_id) {
            memset(&g_test_t.pspinfo_arr[index], 0, sizeof(ipc_PspList_PspInfo));
        }
    }


    return retval;
}

bool dev_on_ipc_PspList(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_PspList_Req *req,
    /* output  */ ipc_PspList_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    int num = 0;
    for (int index = 0; index < 5; index++) {
        T_D("g_test_t.pspinfo_arr[%d].psp_id_: %d ", index, g_test_t.pspinfo_arr[index].psp_id);
        if (g_test_t.pspinfo_arr[index].psp_id != 0) {
            memcpy(&rsp->psps[num], &g_test_t.pspinfo_arr[index], sizeof(ipc_PspList_PspInfo));
            num++;
        }
    }
    rsp->psps_count = num;
    T_D("resp_pspinfo_count: %d ", rsp->psps_count);

    return retval;
}

bool dev_on_ipc_PspCall(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_PspCall_Req *req,
    /* output  */ ipc_PspCall_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_I("dev_on_ipc_PspCall");
    T_I("psp_id=%d", req->psp_id);
    return retval;
}
#endif

int reboot_thread(int conn_id)
{

    os_time_dly(50);
    camx_plat_reboot(0); //默认用0
    return 0;
}


bool dev_on_ipc_Reboot(
    /* conn_id */ int32_t          conn_id,
    /* input   */ ipc_Reboot_Req *req,
    /* output  */ ipc_Reboot_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("conn[%d].ipc.Reboot.channel:%d", conn_id, req->channel);
    thread_fork("REBOOT_THREAD", 10, 1024, 64, 0, reboot_thread, conn_id);
    return retval;
}


static iot_sleep_t s_iotsleep = {0};

bool dev_on_ipc_Reset(
    /* conn_id */ int32_t         conn_id,
    /* input   */ ipc_Reset_Req *req,
    /* output  */ ipc_Reset_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    int size = get_db_config_table_size();

    for (int i = 0; i < size; i++) {

        syscfg_write(db_config_table[i].index, &db_config_table[i].value, db_config_table[i].len);
    }

    int rc;

    s_iotsleep.way = 1;
    rc = avsdk_sleep(&s_iotsleep);
    T_I("conn[%d].ipc.Reset.channel:%d", conn_id, req->channel);

    thread_fork("REBOOT_THREAD", 10, 1024, 64, 0, reboot_thread, conn_id);

    return retval;
}

bool dev_on_ipc_FlipGet(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_FlipGet_Req *req,
    /* output  */ ipc_FlipGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("---->dev_on_ipc_FlipGet");
    /* rsp->flip = g_test_t.flip; */

    /* printf("db_select ======%d\n",db_select("mir")); */

    if (db_select("mir") == 0) {
        rsp->flip = 1;
    } else {
        rsp->flip = db_select("mir");
    }
    printf("rsp->flip ===%d\n", rsp->flip);
    return retval;
}

bool dev_on_ipc_LanAuth(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_LanAuth_Req *req,
    /* output  */ ipc_LanAuth_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    return retval;
}

#if 0
bool dev_on_ipc_TimedcruiseSet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_TimedcruiseSet_Req *req,
    /* output  */ ipc_TimedcruiseSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_I("dev_on_ipc_TimedcruiseSet");
    g_test_t.Timedcruise_states = req->states;
    g_test_t.Timedcruise_mode = req->mode;
    g_test_t.Timedcruise_interval = req->interval;
    memcpy(&g_test_t.Timedcruise_tt, &req->tt, sizeof(xciot_Timetask));

    return retval;
}

bool dev_on_ipc_TimedcruiseGet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_TimedcruiseGet_Req *req,
    /* output  */ ipc_TimedcruiseGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_I("dev_on_ipc_TimedcruiseGet");
    rsp->states = g_test_t.Timedcruise_states;
    rsp->mode = g_test_t.Timedcruise_mode;
    rsp->interval = g_test_t.Timedcruise_interval;
    memcpy(&rsp->tt, &g_test_t.Timedcruise_tt, sizeof(xciot_Timetask));

    return retval;
}
#endif

bool dev_on_ipc_StorageInfo(
    /* conn_id */ int32_t               conn_id,
    /* input   */ ipc_StorageInfo_Req *req,
    /* output  */ ipc_StorageInfo_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("------------dev_on_ipc_StorageInfo-----------");


    if (storage_device_ready()) {
        rsp->status = 0;

    } else {
        rsp->status = 4;
        return retval;
        /* return -1;	 */
    }

    u32 total = 0, _free = 0;
    int err1, err2;
    err1 = fget_free_space(CONFIG_ROOT_PATH, &_free);

    err2 = fget_physical_total_space(CONFIG_ROOT_PATH, &total);
    printf("total :%d _free:%d\n", total, _free);

    if (_free > total) {
        _free = total;
    }
    if (err1 || err2) {
        rsp->total_size = 0;    //MB
        rsp->use_size = 0;     //MB
    } else {
        rsp->total_size = total / 1024 ;
        rsp->use_size = (total - _free) / 1024;
    }

    /* rsp->total_size = 1024; */
    /* rsp->use_size = 512; */

    T_D("status =%d", rsp->status);
    T_D("total_size =%lld", rsp->total_size);
    T_D("use_size =%lld", rsp->use_size);


    return retval;
}
u8 storage_format_flag = 0;
int Storage_Format(int conn_id)
{
    if (storage_device_ready()) {
        cloud_playback_list_uninit();
        cloud_playback_list_clear();
        sdcard_storage_device_format(SDX_DEV);
        avsdk_storage_format_rate(conn_id, 0, 100);
        storage_format_flag = 1;

        return 0;
    }

    avsdk_storage_format_rate(conn_id, 0, 0);
    return 0;
}

bool dev_on_ipc_StorageFormat(
    /* conn_id */ int32_t                 conn_id,
    /* input   */ ipc_StorageFormat_Req *req,
    /* output  */ ipc_StorageFormat_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("------------dev_on_ipc_StorageFormat-----------");
    thread_fork("STORAGE_FORMAT_THREAD", 10, 1024, 64, 0, Storage_Format, conn_id);

#if 0
    pthread_t format_tidp;
    int rc = pthread_create(&format_tidp, NULL, storage_format_thread, OSAL_UINT_TO_POINTER(conn_id));
    OSAL_ASSERT(rc == 0);
#endif
    return retval;
}



bool dev_on_ipc_LogSet(
    /* conn_id */ int32_t          conn_id,
    /* input   */ ipc_LogSet_Req *req,
    /* output  */ ipc_LogSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("--------------dev_on_ipc_LogSet-------------------");

    T_D("channel =%s", req->channel);
    T_D("log_ipaddr =%d", req->states);

    return retval;
}

#if 0
bool dev_on_ipc_VolumeSet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_VolumeSet_Req *req,
    /* output  */ ipc_VolumeSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    g_test_t.volume_value = req->volume;

    return retval;
}
#endif

#if 0
bool dev_on_ipc_PowerFreqSet(
    /* conn_id */ int32_t                conn_id,
    /* input   */ ipc_PowerFreqSet_Req *req,
    /* output  */ ipc_PowerFreqSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("----------dev_on_ipc_PowerFreqSet-----------");
    T_D("power freq = %d", req->power_freq);

    g_test_t.power_freq = req->power_freq;

    return retval;
}

bool dev_on_ipc_PowerFreqGet(
    /* conn_id */ int32_t                conn_id,
    /* input   */ ipc_PowerFreqGet_Req *req,
    /* output  */ ipc_PowerFreqGet_Resp *rsp)
{
    T_D("----------dev_on_ipc_PowerFreqGet-----------");


    /* retval - true: support, false: unsupport */
    bool retval = true;

    rsp->power_freq = g_test_t.power_freq;
    T_D("power freq = %d", rsp->power_freq);
    return retval;
}
bool dev_on_ipc_VolumeGet(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_VolumeGet_Req *req,
    /* output  */ ipc_VolumeGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    rsp->volume = g_test_t.volume_value;
    return retval;
}
#endif

bool dev_on_ipc_AlarmSet(
    /* conn_id */ int32_t            conn_id,
    /* input   */ ipc_AlarmSet_Req *req,
    /* output  */ ipc_AlarmSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("----------dev_on_ipc_AlarmSet-----------");

    g_test_t.motion_detection = req->motion;
    /* g_test_t.opensound_detection = req->sound; */
    /* g_test_t.smoke_detection = req->smoke; */
    /* g_test_t.shadow_detection = req->shadow; */
    printf("req->motion ===%d\n", req->motion);
    switch (req->motion) {
    case 1 :
        db_update("motion", 250);
        break;
    case 2 :
        db_update("motion", 350);
        break;
    case 3 :
        db_update("motion", 500);
        break;
    default:
        break;

    }


    return retval;
}

bool dev_on_ipc_AlarmGet(
    /* conn_id */ int32_t            conn_id,
    /* input   */ ipc_AlarmGet_Req *req,
    /* output  */ ipc_AlarmGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("dev_on_ipc_AlarmGet");
    switch (db_select("motion")) {
    case 250:
        rsp->motion = 1;
        break;
    case 350:
        rsp->motion = 2;
        break;
    case 500:
        rsp->motion = 3;
        break;
    default:
        break;

    }
    printf("rsp->motion ==%d\n", rsp->motion);

    /* rsp->motion = g_test_t.motion_detection; */
    /* rsp->sound = g_test_t.opensound_detection; */
    /* rsp->smoke = g_test_t.smoke_detection; */
    /* rsp->shadow = g_test_t.shadow_detection; */

    return retval;
}

bool dev_on_ipc_Screenshot(
    /* conn_id */ int32_t              conn_id,
    /* input   */ ipc_Screenshot_Req *req,
    /* output  */ ipc_Screenshot_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("dev_on_ipc_Screenshot");
    rsp->format = 0;     // set the image format
    T_D("sizeof(rsp->body.bytes) = %d", sizeof(rsp->body.bytes));
    rsp->body.size = 0;   // set the image data length

    // @todo here get the image data ;
    unsigned char image_data[10] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

    //@todo
    if (true) {
        const char *image_ptr = (const char *) image_data;
        int image_len  = sizeof(image_data);

        rsp->format = 2; // 1 png; 2jpg
        rsp->body.size = image_len;
        memcpy(rsp->body.bytes, image_ptr, image_len);

    }


    return retval;
}

#if 0
bool dev_on_ipc_PtzCtrl(
    /* conn_id */ int32_t           conn_id,
    /* input   */ ipc_PtzCtrl_Req *req,
    /* output  */ ipc_PtzCtrl_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("req_func_code: %d ", req->func_code);
    T_D("req_para1: %d ", req->para1);
    T_D("req_para2: %d ", req->para2);

    return retval;
}

bool dev_on_ipc_SetAutoTrack(
    /* conn_id */ int32_t                conn_id,
    /* input   */ ipc_SetAutoTrack_Req  *req,
    /* output  */ ipc_SetAutoTrack_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("dev_on_ipc_SetAutoTrack");
    T_D("autoTrack: %d ", req->autoTrack);
    g_test_t.autotrack = req->autoTrack;
    rsp->respCode = 0;

    return retval;
}

bool dev_on_ipc_GetAutoTrack(
    /* conn_id */ int32_t                conn_id,
    /* input   */ ipc_GetAutoTrack_Req  *req,
    /* output  */ ipc_GetAutoTrack_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("dev_on_ipc_GetAutoTrack");
    T_D("autoTrack: %d ", g_test_t.autotrack);
    rsp->autoTrack = g_test_t.autotrack;

    return retval;
}
#endif

void ota_update(void)
{
    //python -m SimpleHTTPServer 9999
    /* const char *url = "http://cn.rom.xcthings.com:80/IPCB/update-ota.ufw"; */
    ipc_FirmwareCheckByDevice_Resp rsp;

    int avsdk_firmware_poll(ipc_FirmwareCheckByDevice_Resp * rsp);
    avsdk_firmware_poll(&rsp);

    camx_ota_upgrade(rsp.firmware_url);
}

bool dev_on_ipc_FirmwareNotify(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_FirmwareNotify_Req  *req,
    /* output  */ ipc_FirmwareNotify_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    /** TODO:异步操作
     * 1.调用avsdk_firmware_poll查询固件信息和url。
     * 2.使用http下载固件。
     * 3.调用avsdk_firmware_rate上报升级进度
     * 4.更新固件重启。
     */

    T_D("----------dev_on_ipc_FirmwareNotify-----------");

    thread_fork("OTA_UPDATE", 10, 2048, 64, 0,	ota_update, NULL);
#if 0
    thread_fork("OTA_UPDATE", 10, 2048, 64, 0,	ota_update, NULL);
    pthread_t Firmware_tidp;
    int rc = pthread_create(&Firmware_tidp, NULL, firmware_notify_thread, OSAL_UINT_TO_POINTER(conn_id));
    OSAL_ASSERT(rc == 0);
#endif

    rsp->rate = 0;
    return retval;
}


bool dev_on_ipc_EventRecordGet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_EventRecordGet_Req *req,
    /* output  */ ipc_EventRecordGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    rsp->duration = g_test_t.event_record_duration;

    return retval;
}

bool dev_on_ipc_EventRecordSet(
    /* conn_id */ int32_t                  conn_id,
    /* input   */ ipc_EventRecordSet_Req *req,
    /* output  */ ipc_EventRecordSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    g_test_t.event_record_duration = req->duration;

    return retval;
}

#if 0
bool dev_on_ipc_GetNetworkInfo(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_GetNetworkInfo_Req *req,
    /* output  */ ipc_GetNetworkInfo_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("---------------dev_on_ipc_GetNetworkInfo------------------");

    snprintf(rsp->ssid, sizeof(rsp->ssid), "%s", "test_xc");
    rsp->qos = 3;
    snprintf(rsp->ipaddr, sizeof(rsp->ipaddr), "%s", "192.168.0.123");
    snprintf(rsp->netmask, sizeof(rsp->netmask), "%s", "255.255.255.0");
    snprintf(rsp->gateway, sizeof(rsp->gateway), "%s", "192.168.0.1");
    snprintf(rsp->dns1, sizeof(rsp->dns1), "%s", "8.8.8.8");
    snprintf(rsp->dns2, sizeof(rsp->dns2), "%s", "114.114.114.114");
    snprintf(rsp->mac, sizeof(rsp->mac), "%s", "ab:cb:qw:12:34:56");

    T_D("channel: %d ", req->channel);
    T_D("ssid: %s ", rsp->ssid);
    T_D("qos: %d ", rsp->qos);
    T_D("ipaddr: %s ", rsp->ipaddr);
    T_D("netmask: %s ", rsp->netmask);
    T_D("gateway: %s ", rsp->gateway);
    T_D("dns1: %s ", rsp->dns1);
    T_D("dns2: %s ", rsp->dns2);
    T_D("mac: %s ", rsp->mac);


    return retval;
}
#endif


bool dev_on_ipc_FileStart(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_FileStart_Req *req,
    /* output  */ ipc_FileStart_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------------dev_on_ipc_FileStart------------------");

    T_D("req_func_code: %lld ", req->file_id);
    T_D("req_para1: %lld ", req->length);
    T_D("req_para2: %lld ", req->offset);

    return retval;
}

bool dev_on_ipc_FileStop(
    /* conn_id */ int32_t            conn_id,
    /* input   */ ipc_FileStop_Req *req,
    /* output  */ ipc_FileStop_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("---------------dev_on_ipc_FileStop------------------");
    T_D("req_func_code: %lld ", req->file_id);

    return retval;
}

bool dev_on_ipc_CustomCmd(
    /* conn_id */ int32_t             conn_id,
    /* input   */ ipc_CustomCmd_Req *req,
    /* output  */ ipc_CustomCmd_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    static char time = 0;
    avsdk_custom_add_conn(conn_id);
    T_D("req_byte: len = %d", req->arg_int32_count);

    for (char i = 0; i < req->arg_int32_count; i++) {
        T_D("req_int [%d]=%d", i, req->arg_int32[i]);
    }

    T_D("req_byte: len = %d", req->arg_bytes.size);
    for (int i = 0; i < req->arg_bytes.size; i++) {
        T_D("req_byte[%d] = %02x", i, req->arg_bytes.bytes[i]);
    }

    for (int index = 0; index < req->arg_string_count; index++) {
        T_D("req_str_[%d]: %s, len = %d", index, req->arg_string[index], strlen(req->arg_string[index]));

    }


    //if 收到什么，将connid加入custom用户组
    //avsdk_custom_add_conn(conn_id);
    //if 收到什么，将connid从custom用户组删除
    //avsdk_custom_del_conn(conn_id);

    return retval;
}

bool dev_on_ipc_PirSet(
    /* conn_id */ int32_t			 conn_id,
    /* input   */ ipc_PirSet_Req *req,
    /* output  */ ipc_PirSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------------dev_on_ipc_PirSet------------------");

    T_D("req->pir.num: %d ", req->pir.num);
    T_D("req->pir.level: %d ", req->pir.level);

    return retval;
}


bool dev_on_ipc_PirGet(
    /* conn_id */ int32_t			 conn_id,
    /* input   */ ipc_PirGet_Req *req,
    /* output  */ ipc_PirGet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------------dev_on_ipc_PirGet------------------");

    rsp->pirs_count = 1;
    rsp->pirs[0].num = 2;
    rsp->pirs[0].level = 3;
    T_D("rsp->pirs_count: %d ", rsp->pirs_count);
    T_D("rsp->pirs[0].num: %d ", rsp->pirs[0].num);
    T_D("rsp->pirs[0].level: %d ", rsp->pirs[0].level);

    return retval;
}

bool dev_on_ipc_ChanState(
    /* conn_id */ int32_t			  conn_id,
    /* input   */ ipc_ChanState_Req  *req,
    /* output  */ ipc_ChanState_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------------dev_on_ipc_ChanState------------------");



    rsp->chans_count = 1;
    rsp->chans[0].channel = 0;
    rsp->chans[0].state = 1;

    return retval;
}

bool dev_on_ipc_VideoChanChange(
    /* conn_id */ int32_t			 conn_id,
    /* input   */ ipc_VideoChanChange_Req *req,
    /* output  */ ipc_VideoChanChange_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------------dev_on_ipc_VideoChanChange------------------");

    T_D("rsp->channel_count: %d ", req->channel_count);
    for (int i = 0; i < req->channel_count; i++) {
        T_D("rsp->channel[%d]: %d ", i, req->channel[i]);
    }

    rsp->render_count = 1;
    rsp->render[0] = 5;

    return retval;
}

#if 0
bool dev_on_ipc_TamperSet(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_TamperSet_Req *req,
    /* output  */ ipc_TamperSet_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    static int num = 0;
    T_D("---------------dev_on_TamperSet num%d------------------", num++);

    //参考iot_tamper_status_t
    T_D("TamperSet state: %"PRIu64, req->state);

    return retval;
}
#endif

bool dev_on_ipc_DirCreate(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_DirCreate_Req *req,
    /* output  */ ipc_DirCreate_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;
    T_D("---------------%s------------------", OSAL_STRFUNC);
    T_D("dir_name:%s", req->dir_name);
    T_D("dir_name:%s", req->dir_path);
    return retval;
}

bool dev_on_ipc_DirDel(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_DirDel_Req *req,
    /* output  */ ipc_DirDel_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("---------------%s------------------", OSAL_STRFUNC);

    T_D("dir_name:%s", req->dir_name);
    T_D("dir_name:%s", req->dir_path);

    return retval;
}

bool dev_on_ipc_DirEdit(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_DirEdit_Req *req,
    /* output  */ ipc_DirEdit_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("---------------%s------------------", OSAL_STRFUNC);


    T_D("dir_name:%s", req->dir_path);
    T_D("old_dir_name:%s", req->old_dir_name);
    T_D("new_dir_name:%s", req->new_dir_name);

    return retval;
}

bool dev_on_ipc_DirList(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_DirList_Req *req,
    /* output  */ ipc_DirList_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_D("---------------%s------------------", OSAL_STRFUNC);
    T_D("dir_name:%s", req->dir_path);
    T_D("page:%d", req->page);
    T_D("page_size:%d", req->page_size);

    return retval;
}

#if 1 //文件传输

typedef struct {
    int32_t conn_id;
    bool tosend;
    bool recv_end;
    bool init;
    uint64_t total_size;
    uint64_t last_offset;
    ipc_FileRecvRate_Req    req;

} frr_ctx_t;


frr_ctx_t frr;

bool dev_on_ipc_FileAdd(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_FileAdd_Req *req,
    /* output  */ ipc_FileAdd_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    T_D("---------------%s------------------", OSAL_STRFUNC);

    T_I("req->dir_path:%s", req->dir_path);

    T_I("req->file_name:%s", req->file_name);
    T_I("req->file_id:%lld", req->file_id);
    T_I("req->total_size:%lld", req->total_size);

    frr.total_size = req->total_size;

    return retval;
}


void *report_recvfile_thread(void *arg)
{

    frr_ctx_t *frrp = &frr;
    int32_t  conn_id;
    int rc = 0;
    ipc_FileRecvRate_Req    req;
    ipc_FileRecvRate_Resp   rsp;
#if 0
    while (1) {

        /* diff > 40K */
        if (!frrp->tosend && (frrp->req.recv_size != 0) && (frrp->req.recv_size - frrp->last_offset > 40000)) {
            T_I("set tosend =1, (receive,last)  (%lld-%lld)", frrp->req.recv_size, frrp->last_offset);
            frrp->tosend = true;
        }

        /* 判定是不是文件结束 */
        if (!frrp->tosend && (frrp->total_size == frrp->req.recv_size)) {
            if (frrp->last_offset != frrp->total_size) {

                frrp->tosend = true;
                T_I("receive file end %lld", req.recv_size);
            } else {
                /* 已经发送了最后一包 */
                frr.last_offset = 0;
                frr.recv_end = false;
                frr.tosend = false;
                frr.total_size = 0;
                frr.conn_id = -1;
                memset(&frr.req, 0, sizeof(ipc_FileRecvRate_Req));
                memset(&req, 0, sizeof(ipc_FileRecvRate_Req));
            }

        }

        if (frrp->tosend) {
            if (frrp->req.recv_size - frrp->last_offset == 0) {
                frrp->tosend = false;
                continue ;
            }

            if (frrp->conn_id < 0) {
                continue;
            }
            conn_id = frrp->conn_id;
            memcpy(&req, &frrp->req, sizeof(req));
            rc = avsdk_report_FileRecvRate(conn_id,
                                           &req,
                                           &rsp);
            if (rc != 0 && rc != 9 && rc != 5) {
                T_E("error: avsdk_report_FileRecvRate, rc=%d", rc);
            } else {
                T_W("report diff = %lld", (req.recv_size - frrp->last_offset));

                frrp->last_offset = req.recv_size;

                T_W("report_recvfile filed == %lld,(total-recv-last) (%lld-%lld-%lld)",
                    frrp->req.file_id,
                    frrp->total_size,
                    req.recv_size,
                    frrp->last_offset);

                frrp->tosend = false;

            }
        } else {
            usleep(10);
        }
    }
#endif

}


void dev_on_RecvFile(int32_t            conn_id,
                     ipc_RecvFile_Req   *req,
                     ipc_RecvFile_Resp  *rsp)
{
    if (req->offset % 100 * 1024 == 0) {
        T_I("dev_on_RecvFile");
        T_D("conn_id=%d", conn_id);
        T_I("file_id=%"PRIi64, req->file_id);
        T_I("offset=%"PRIi64, req->offset);
        T_D("payload_len=%"PRIi64, req->payload_len);
        T_T("msg:%s", req->payload);
    }

    frr.req.file_id = req->file_id;
    frr.req.recv_size = req->offset + req->payload_len;
    frr.conn_id = conn_id;
#if 0
    if (!frr.init) {
        pthread_t frr_tidp;
        pthread_create(&frr_tidp, NULL, report_recvfile_thread, (void *)&frr);
        frr.init = true;
    }
#endif
    rsp->recode = 0;
}

#endif //文件传输demo

bool dev_on_ipc_FileDel(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_FileDel_Req *req,
    /* output  */ ipc_FileDel_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_D("---------------%s------------------", OSAL_STRFUNC);

    return retval;
}

bool dev_on_ipc_FileEdit(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_FileEdit_Req *req,
    /* output  */ ipc_FileEdit_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_D("---------------%s------------------", OSAL_STRFUNC);

    return retval;
}

bool dev_on_ipc_FileRecvRate(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_FileRecvRate_Req *req,
    /* output  */ ipc_FileRecvRate_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_D("---------------%s------------------", OSAL_STRFUNC);

    return retval;
}

bool dev_on_ipc_FileThumList(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_FileThumList_Req *req,
    /* output  */ ipc_FileThumList_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;


    T_D("---------------%s------------------", OSAL_STRFUNC);

    return retval;
}

bool dev_on_ipc_ExecIOTCMD(
    /* conn_id */ int32_t conn_id,
    /* input   */ ipc_ExecIOTCMD_Req *req,
    /* output  */ ipc_ExecIOTCMD_Resp *rsp)
{
    /* retval - true: support, false: unsupport */
    bool retval = true;

    /* 注意：
     * req中iot_cmds与ttcmd为互斥，每次命令只会有其中一个赋值，
     * 可以通过cmds_count是否为0，来判定命令为iot_cmds还是ttcmd。
     */
    printf("req->iot_cmds.cmds[0].cid:%x\n", req->iot_cmds.cmds[0].cid);
    T_D("-------dev_on_ipc_ExecIOTCMD--------");
    if (req->iot_cmds.cmds[0].cid == 530000) {
        rsp->iot_cmds.cmds_count = 1;
        rsp->iot_cmds.cmds[0].pint_count = 1;
        rsp->iot_cmds.cmds[0].cid = req->iot_cmds.cmds[0].cid;

        if (storage_device_ready()) {
            rsp-> iot_cmds.cmds[0].pint[0] = 1;
        } else {
            rsp-> iot_cmds.cmds[0].pint[0] = 0;
        }
        printf("req->iot_cmds.cmds[0].cid =====%d\n", req->iot_cmds.cmds[0].cid);
        printf("rsp-> iot_cmds.cmds[0].pint[0] =====%d\n", rsp-> iot_cmds.cmds[0].pint[0]);

    } else if (req->iot_cmds.cmds[0].cid == 0x232) {
        /* strcpy(rsp->iot_cmds.did,avsdk_cfg_did()); */
        printf("req-> iot_cmds.cmds[0].pint[0] =%d\n", req->iot_cmds.cmds[0].pint[0]);
        printf("req-> iot_cmds.cmds[0].pint[1] =%d\n", req->iot_cmds.cmds[0].pint[1]);

        if (!req->iot_cmds.cmds[0].pint[1]) {
            rsp-> iot_cmds.cmds[0].pint[1] = cloud_playback_get_speed();
        } else {

            cloud_playback_set_speed(req->iot_cmds.cmds[0].pint[1]);
            rsp->iot_cmds.cmds[0].pint[1] = cloud_playback_get_speed();
        }
        rsp->iot_cmds.cmds_count = 1;
        rsp->iot_cmds.cmds[0].pint_count = 2;
        rsp->iot_cmds.cmds[0].cid = req->iot_cmds.cmds[0].cid;


        /* rsp-> iot_cmds.cmds[0].pint[1] = 2; */
        printf("req->iot_cmds.cmds[0].cid =====%d\n", req->iot_cmds.cmds[0].cid);
        printf("rsp-> iot_cmds.cmds[0].pint[0] =====%d\n", rsp-> iot_cmds.cmds[0].pint[0]);
        printf("rsp-> iot_cmds.cmds[0].pint[1] =====%d\n", rsp-> iot_cmds.cmds[0].pint[1]);

    } else if (req->iot_cmds.cmds[0].cid == 530002) {

        rsp->iot_cmds.cmds_count = 1;
        rsp->iot_cmds.cmds[0].pint_count = 3;
        rsp->iot_cmds.cmds[0].cid = req->iot_cmds.cmds[0].cid;
        rsp-> iot_cmds.cmds[0].pint[0] = get_product_pid();
        rsp-> iot_cmds.cmds[0].pint[1] = get_platfrom_type();
        rsp-> iot_cmds.cmds[0].pint[2] = get_jl_ver();



        rsp->iot_cmds.cmds[0].pstr_count = 2;
        strcpy(&rsp->iot_cmds.cmds[0].pstr[0], get_platfrom_name());
        strcpy(&rsp->iot_cmds.cmds[0].pstr[1], get_platfrom_ver());

    }

    return retval;
}

void dev_on_ipc_talkbackcb(int32_t              conn_id,
                           iot_exhdr_media_t    *exhdr,
                           const uint8_t        *media_data,
                           size_t               media_len)
{
//	printf("media[%d],type=%d,seq=%d, iskey=%d, data len=%d",
    //    (int)exhdr->avchannel, exhdr->avformat.streamtype, (int)exhdr->avseq, exhdr->avformat.iskeyframe, media_len);

    int xc_talkback(const uint8_t *audio, int len);
    xc_talkback(media_data, media_len);
}




#endif

/*****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

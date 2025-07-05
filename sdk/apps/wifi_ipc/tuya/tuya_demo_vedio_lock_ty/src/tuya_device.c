/***********************************************************
*  File: tuya_device.c
*  Author: pyx
*  Date: 20190915
***********************************************************/
#include "gw_intf.h"
#include "mf_test.h"
#include "tal_sw_timer.h"
#include "tuya_cloud_types.h"
#include "uni_log.h"
#include "tuya_iot_com_api.h"
#include "sys_timer.h"
#include "tfm_gpio_test.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_uart_legacy.h"
#include "tdl_data_send_recv_init.h"
#include "tfm_data_frame_recv.h"
#include "tfm_cmd_list.h"
#include "tdd_uart_driver.h"
#include "base_event.h"
#include "tbl_common_basic_service.h"
#include "tbl_common_public_iot.h"
#include "tuya_device.h"
#include "tbl_kiwi_cmd_def.h"
#include "tuya_stream.h"
#include "tfm_cmd_list.h"
#include "tuya_device.h"
#include "tuya_video.h"

/***********************************************************************
 ** VARIABLE                                                          **
 **********************************************************************/
#define CLEAR_WIFI_DELAY_MAX_TIME   10 * 1000


#define USER_SW_VER   "0.0.1"
#define APP_BIN_NAME  "tuya"

/**
* @brief mcu信息
*/
typedef struct {
    CHAR_T product_key[PRODUCT_KEY_LEN + 1];         //产品key
} MCU_INFO_S;

STATIC TY_TRANS_HANDLE_S sg_trans_handle = NULL;
STATIC MCU_INFO_S mcu_info = {0};
STATIC TIMER_ID  clear_wifi_timer_id;
STATIC UINT_T local_reset_type;
STATIC BOOL_T is_net_cfg_reset;
STATIC BOOL_T init_flag;

STATIC VOID tuya_clear_wifi_timer_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    OPERATE_RET op_ret = OPRT_OK;

    is_net_cfg_reset = FALSE;
    local_reset_type = CMD_KIWI_CLEAR_DATA;
    op_ret = tuya_iot_wf_gw_reset();
    if (op_ret) {
        PR_ERR("tuya_iot_wf_gw_reset failed err:%d", op_ret);
    }

    PR_INFO("tuya_clear_wifi_timer_cb\n");
}
STATIC OPERATE_RET tuya_clear_wifi_timer_start(VOID)
{
    return tal_sw_timer_start(clear_wifi_timer_id, CLEAR_WIFI_DELAY_MAX_TIME, TAL_TIMER_ONCE);
}

STATIC OPERATE_RET tuya_clear_wifi_timer_stop(VOID)
{
    return tal_sw_timer_stop(clear_wifi_timer_id);
}

OPERATE_RET kiwi_uart_start_wifi(IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (FALSE == init_flag) {
        return OPRT_OK;
    }

    is_net_cfg_reset = TRUE;
    local_reset_type = CMD_KIWI_START_WIFI;

#if 1
    op_ret = tuya_flash_set_wifi_en(TRUE);
    if (op_ret) {
        PR_ERR("tuya_flash_set_wifi_en failed\n");
    }

    op_ret = tuya_flash_set_wifi_to_mcu(p_service_data->data[4]);
    if (op_ret) {
        PR_ERR("tuya_flash_set_wifi_to_mcu failed\n");
    }
#endif

    op_ret = tuya_iot_wf_gw_reset();
    if (op_ret) {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x02, 0x01);
    }

    return op_ret;
}

OPERATE_RET kiwi_uart_clear_wifi(IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (FALSE == init_flag) {
        return OPRT_OK;
    }

    op_ret = tuya_flash_set_wifi_en(FALSE);
    if (op_ret) {
        PR_ERR("tuya_flash_set_wifi_en failed\n");
    }

    op_ret = tuya_clear_wifi_timer_start();
    if (op_ret) {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x02, 0x05);
    } else {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x00, 0x05);
    }


    return op_ret;
}

OPERATE_RET kiwi_uart_stop_wifi(IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (FALSE == init_flag) {
        return OPRT_OK;
    }

    op_ret = tuya_flash_set_wifi_en(FALSE);
    if (op_ret) {
        PR_ERR("tuya_flash_set_wifi_en failed\n");
    }


    is_net_cfg_reset = FALSE;
    local_reset_type = CMD_KIWI_STOP_WIFI;
    op_ret = tuya_iot_wf_gw_reset();
    if (op_ret) {
        PR_ERR("tuya_iot_wf_gw_reset err");
    }

    return op_ret;
}

OPERATE_RET kiwi_uart_close_power(IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;


    send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x00, 0x04);

    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK == op_ret && (STAT_AP_STA_UNCFG == cur_nw_stat || STAT_UNPROVISION == cur_nw_stat)) {

        PR_INFO("lock close power, but is pair wifi, stop pair wifi\n");
        is_net_cfg_reset = FALSE;
        local_reset_type = CMD_KIWI_STOP_WIFI;
        op_ret = tuya_iot_wf_gw_reset();
        if (op_ret) {
            PR_ERR("tuya_iot_wf_gw_reset err");
        }

    }


    return op_ret;
}


OPERATE_RET kiwi_uart_set_pid(IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    tKIWI_MCU_PID_INFO *pid_info = NULL;

    pid_info = (tKIWI_MCU_PID_INFO *)p_service_data->data;

    if (PRODUCT_KEY_LEN != pid_info->lenth) {
        PR_ERR("pid_info->lenth:%d is failed\n", pid_info->lenth);
        goto out;
    }

    PR_INFO("kiwi_uart_set_pid:%s\n", pid_info->pid);

    op_ret = ty_param_save(PID_CFG_PARAM_E, pid_info->pid, PRODUCT_KEY_LEN);
    if (op_ret) {
        PR_ERR("ty_param_save is failed\n");
    }

out:
    if (op_ret) {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x02, CMD_KIWI_SET_PID);
    } else {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x00, CMD_KIWI_SET_PID);
        // 先校验密码, 优质云家的密码只支持前7位
        if (strncmp(mcu_info.product_key, pid_info->pid, PRODUCT_KEY_LEN)) {
            PR_WARN("pid is change, need reboot\n");
            tuya_hal_system_sleep(250);
            tkl_system_reset();
        }
    }

    return op_ret;
}


OPERATE_RET kiwi_uart_get_pid(IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    tKIWI_MCU_GET_PID_INFO  get_pid_info = {0};

    PR_INFO("kiwi_uart_get_pid:%s\n", mcu_info.product_key);

    if (mcu_info.product_key) {
        get_pid_info.result = 0x00;
        get_pid_info.lenth = strlen(mcu_info.product_key) + 1;
        memcpy(get_pid_info.pid, mcu_info.product_key, PRODUCT_KEY_LEN);
    } else {
        get_pid_info.result = 0x02;
        get_pid_info.lenth = strlen(mcu_info.product_key) + 1;
    }

out:

    tfm_data_frame_send_direct(sg_trans_handle, CMD_KIWI_GET_PID_ACK, &get_pid_info, SIZEOF(tKIWI_MCU_GET_PID_INFO));

    return op_ret;
}



STATIC OPERATE_RET ty_uart_start_wifi(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_start_wifi(p_service_data);
}

STATIC OPERATE_RET ty_uart_clear_wifi(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_clear_wifi(p_service_data);
}

STATIC OPERATE_RET ty_uart_get_time(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_get_time(p_service_data);
}

STATIC OPERATE_RET ty_uart_stop_wifi(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_stop_wifi(p_service_data);
}

STATIC OPERATE_RET ty_uart_update_mcu_state(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_update_mcu_state(p_service_data);
}

STATIC OPERATE_RET ty_uart_update_info(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_update_info(p_service_data);
}

STATIC OPERATE_RET ty_uart_close_power(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_close_power(p_service_data);
}

STATIC OPERATE_RET ty_uart_remote_unlock_ack(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_remote_unlock_ack(p_service_data);
}


STATIC OPERATE_RET ty_uart_start_snap_pic(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_start_snap_pic(p_service_data);
}

STATIC OPERATE_RET ty_uart_update_cache_info(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_update_cache_info(p_service_data);
}
STATIC OPERATE_RET ty_uart_get_check_user_info_result(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_get_check_user_info_result(p_service_data);
}

STATIC OPERATE_RET ty_uart_get_video_status(IN TY_CMD_S *p_service_data)
{
    return OPRT_OK;
}

STATIC OPERATE_RET ty_uart_get_module_info(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_get_module_info(p_service_data);
}

STATIC OPERATE_RET ty_uart_get_version(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_get_version(p_service_data);
}

STATIC OPERATE_RET ty_uart_get_dev_cap(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_get_dev_cap(p_service_data);
}

STATIC OPERATE_RET ty_uart_set_proactive_view(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_set_proactive_view(p_service_data);
}

STATIC OPERATE_RET ty_uart_user_control_ack(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_user_control_ack(p_service_data);
}

STATIC OPERATE_RET ty_uart_user_control_feed_back(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_user_control_feed_back(p_service_data);
}

STATIC OPERATE_RET ty_uart_product_test(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_product_test(p_service_data);
}

STATIC OPERATE_RET ty_uart_set_pid(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_set_pid(p_service_data);
}

STATIC OPERATE_RET ty_uart_get_pid(IN TY_CMD_S *p_service_data)
{
    return kiwi_uart_get_pid(p_service_data);
}


STATIC TY_CMD_CFG_S sg_kiwi_cmd_msg[] = {
    {CMD_KIWI_START_WIFI, ty_uart_start_wifi, 0, NULL},
    {CMD_KIWI_CLEAR_DATA, ty_uart_clear_wifi, 0, NULL},
    {CMD_KIWI_GET_GMT_TIME, ty_uart_get_time, 0, NULL},
    {CMD_KIWI_STOP_WIFI, ty_uart_stop_wifi, 0, NULL},
    {CMD_KIWI_UPDATE_MCU_STATE, ty_uart_update_mcu_state, 0, NULL},
    {CMD_KIWI_UPDATE_INFO, ty_uart_update_info, 0, NULL},  //
    {CMD_KIWI_CLOSE_POWER, ty_uart_close_power, 0, NULL},
    {CMD_KIWI_REMOTE_UNLOCK_ACK, ty_uart_remote_unlock_ack, 0, NULL},
    {CMD_KIWI_START_SNAP_PIC, ty_uart_start_snap_pic, 0, NULL},
    {CMD_KIWI_UPDATE_CACHE_INFO, ty_uart_update_cache_info, 0, NULL},
    {CMD_KIWI_GET_CHECK_USER_INFO_RESULT, ty_uart_get_check_user_info_result, 0, NULL},  //
    {CMD_KIWI_GET_VIDEO_STATUS, ty_uart_get_video_status, 0, NULL},
    {CMD_KIWI_GET_MODULE_INFO, ty_uart_get_module_info, 0, NULL},
    {CMD_KIWI_GET_VERSION, ty_uart_get_version, 0, NULL},
    {CMD_KIWI_GET_DEV_CAP, ty_uart_get_dev_cap, 0, NULL},
    {CMD_KIWI_PROACTIVE_VIEW, ty_uart_set_proactive_view, 0, NULL},
    {CMD_KIWI_USER_CONTROL_ACK, ty_uart_user_control_ack, 0, NULL},
    {CMD_KIWI_USER_CONTROL_FEED_BACK, ty_uart_user_control_feed_back, 0, NULL},
    {CMD_KIWI_PRODUCT_TEST, ty_uart_product_test, 0, NULL},
    {CMD_KIWI_SET_PID, ty_uart_set_pid, 0, NULL},
    {CMD_KIWI_GET_PID, ty_uart_get_pid, 0, NULL},
};

/**
 * @brief 通信数据接收命令回调注册
 * @param[in] p_cmd_data 接收的串口命令数据
 * @return 操作结果，OPRT_OK表示成功，其他表示失败，具体查看@OPERATE_RET 定义
 * @note 无
 */
STATIC OPERATE_RET __tbl_uart_recv_data_cb(IN TY_CMD_S *p_cmd_data)
{
    if (NULL == p_cmd_data) {
        return OPRT_INVALID_PARM;
    }

    PR_NOTICE("RX cmd 0x%x datalen=%d", p_cmd_data->cmd, p_cmd_data->datalen);
    //tal_log_print_raw("55 AA 00 %02X %02X %02X ",p_cmd_data->cmd,p_cmd_data->datalen>>8,p_cmd_data->datalen & 0xFF);
    tal_log_print_raw("AA 55 %02X ", p_cmd_data->cmd);
    if (p_cmd_data->datalen + 1) {
        tuya_print_data(p_cmd_data->data, p_cmd_data->datalen + 1);
    }
    tal_log_print_raw("\r\n");
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tfm_cmd_list_proc((TY_CMD_S *)p_cmd_data);
    return op_ret;
}

VOID __tbl_read_pre_cb(VOID)
{
    return;
}


VOID __tbl_send_pre_cb(VOID)
{
    return;
}
/**
 * @brief
 * @return
 * @notice
 */
STATIC OPERATE_RET __get_dev_info(IN UCHAR_T *pdata, IN UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (NULL == pdata || 0 == len) {
        return OPRT_INVALID_PARM;
    }

    PR_DEBUG("prod:%s", pdata);

    CHAR_T pid_buf[20] = {0};
    UINT_T read_len = 0;
    OPERATE_RET ret = OPRT_OK;
    memset(pid_buf, 0, sizeof(pid_buf));

    ret = ty_param_load(PID_CFG_PARAM_E, pid_buf, SIZEOF(pid_buf), &read_len);
    if (ret != OPRT_OK) {
        strcpy(mcu_info.product_key, pdata);
    } else {
        strcpy(mcu_info.product_key, pid_buf);
        PR_INFO("load pid:%s\n", mcu_info.product_key);
    }
    return op_ret;
}


OPERATE_RET product_infor_parase(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    CHAR_T *infor = "jxgtpryvda64ikp4";  //可以更换自己的pid

    PR_NOTICE("product_infor_parase in\n");
    op_ret = __get_dev_info(infor, strlen(infor));
    if (op_ret) {
        PR_ERR("__get_dev_info is error\n");
    }
    PR_NOTICE("product_infor_parase out\n");
    return op_ret;
}

STATIC OPERATE_RET __tbl_uart_func_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T detect_baud = 9600;

    op_ret = product_infor_parase();
    if (op_ret) {
        PR_ERR("product_infor_parase err:%d", op_ret);
        return op_ret;
    }

    TY_UART_MULTI_CONFIG_S config = {.port = TY_UART0,
                                     .baud_rate = detect_baud,
                                     .bits = TYWL_8B,
                                     .parity = TYP_NONE,
                                     .stop = TYS_STOPBIT1,
                                     .cache_len = TY_USER_RECV_MAX,
                                     .unblock_marks = FALSE
                                    };

    op_ret = tdd_uart_driver_register(TY_USER_UART_, config);
    if (OPRT_OK != op_ret) {
        PR_ERR("tdd_uart_driver_register err:%d", op_ret);
        return op_ret;
    }

    op_ret = tdl_com_dev_find(TY_USER_UART_, &sg_trans_handle);
    if (OPRT_OK != op_ret) {
        PR_ERR("tdl_com_dev_find err:%d", op_ret);
        return op_ret;
    }

    op_ret = tdl_hw_com_data_init(sg_trans_handle, __tbl_send_pre_cb, __tbl_read_pre_cb);
    if (OPRT_OK != op_ret) {
        PR_ERR("tdl_hw_com_data_init err:%d", op_ret);
        return op_ret;
    }

    TY_RECV_MSG_S recv_cfg;
    recv_cfg.port = sg_trans_handle;
    recv_cfg.cache_len = TY_USER_RECV_MAX;
    recv_cfg.recv_cb = __tbl_uart_recv_data_cb;
    recv_cfg.loop_wait_time_ms = 0; //使用默认数据50ms
    recv_cfg.priority = TRD_PRIO_0;
    recv_cfg.stackDepth = 1024 * 2;
    op_ret = tfm_data_frame_proc_init(&recv_cfg, 20, NULL);
    if (OPRT_OK != op_ret) {
        PR_ERR("tfm_data_frame_recv_init err:%d", op_ret);
    }

    return op_ret;

}



// tuya main api

VOID_T mf_user_enter_callback(VOID_T)
{
    return ;
}

VOID mf_user_callback(VOID)
{
    return;
}

OPERATE_RET mf_user_product_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_prod_test(cmd, data, len, ret_data, ret_len);
    return OPRT_OK;
}

OPERATE_RET mf_user_basic_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len)
{
    return OPRT_OK;
}

static void wifi_app_timer_func(void *p)
{
    if (wifi_is_on()) {
        /* stats_display(); //LWIP stats */
        printf("WIFI U= %d KB/s, D= %d KB/s\r\n", wifi_get_upload_rate() / 1024, wifi_get_download_rate() / 1024);
    }
}


VOID_T pre_app_init(VOID_T)
{
    OPERATE_RET op_ret = OPRT_OK;

    SetLogManageAttr(TY_LOG_LEVEL_DEBUG);

    TY_AUDIO_PARAM audio_param;
    audio_param.audio_power_off = FALSE;
    audio_param.bit_dept = 16;
    audio_param.channel_num = 1;
    audio_param.sample_rate = 8000;//8000;//8000;
    tuya_audio_init(&audio_param);


    TY_CAMERA_PARAM carmer_param;
    carmer_param.video_width = 640;//CONFIG_VIDEO_IMAGE_W;
    carmer_param.video_height = 480;//CONFIG_VIDEO_IMAGE_H;
    carmer_param.video_fps = 10;//10;//10;//10;
    carmer_param.video_rotat_angle = 180;
    carmer_param.video_power_off = FALSE;
    tuya_video_init(&carmer_param);

    /* sys_timer_add_to_task("sys_timer", NULL, wifi_app_timer_func, 1 * 1000); */

    op_ret = system_timer_init();
    if (op_ret) {
        PR_ERR("system_timer_init failed\n");
    }

    return;
}


STATIC OPERATE_RET tuya_stream_frame_cb(IN TY_STREAM_SEND_FRAME_S *p_stream_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (STREAM_SEND_TYPE_DIRECT == p_stream_data->type) {
        op_ret = tfm_data_frame_send_direct(sg_trans_handle, p_stream_data->cmd, p_stream_data->data, p_stream_data->data_len);
    }
    return op_ret;
}

VOID app_init(VOID)
{
#define LOW_POWER_MODE_TIMEOUT 180
    OPERATE_RET op_ret = OPRT_OK;
    VOID tuya_svc_lock_dp_report_thrd_stack_set(UINT_T stack_size);
    tuya_svc_lock_dp_report_thrd_stack_set(4096);
    tuya_iot_wf_timeout_set(LOW_POWER_MODE_TIMEOUT);

    op_ret = __tbl_uart_func_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("__tbl_uart_func_init err:%d", op_ret);
        return ;
    }

    op_ret = tfm_cmd_list_reg(sg_kiwi_cmd_msg, CNTSOF(sg_kiwi_cmd_msg));
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_service_list_init err:%d", op_ret);
        return ;
    }

    op_ret = tal_sw_timer_create(tuya_clear_wifi_timer_cb, NULL, &clear_wifi_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("creat clear_wifi_timer_id failed err:%d", op_ret);
        return ;
    }

    op_ret = tbl_common_basic_funtion_init(sg_trans_handle);
    if (OPRT_OK != op_ret) {
        PR_ERR("tbl_common_basic_funtion_init err:%d", op_ret);
        return ;
    }

    op_ret = ty_photo_proc_init(tuya_stream_frame_cb);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_photo_proc_init failed op_ret:%d", op_ret);
        return ;
    }

    tuya_change_wifi_en();

    return ;
}

VOID __meme_check_tiemr_cb(TIMER_ID timer_id, VOID_T *arg)
{
    PR_NOTICE("notice heap %d", tuya_hal_system_getheapsize());
}

VOID pre_device_init(VOID)
{
    /* SetLogManageAttr(TY_LOG_LEVEL_DEBUG); */
    SetLogManageAttr(TY_LOG_LEVEL_ERR);
    PR_NOTICE("%s", tuya_iot_get_sdk_info());
    PR_NOTICE("reset_reason:%d", tal_system_get_reset_reason(NULL));
    PR_NOTICE("%s:%s", APP_BIN_NAME, USER_SW_VER);
#if 0
    TIMER_ID timer_id = NULL;
    tal_sw_timer_create(__meme_check_tiemr_cb, NULL, &timer_id);
    tal_sw_timer_start(timer_id, 1000, TAL_TIMER_CYCLE);
#endif
}


// 各种重置的回调接口
STATIC VOID __gw_reset_cb(GW_RESET_TYPE_E type)
{
    tuya_kiwi_password_deinit();
    wd_mf_test_close_if_write(FALSE);
    PR_NOTICE("tuya_gw_reset_cb type is :%d", type);

    OPERATE_RET op_ret = OPRT_OK;

    if (FALSE == is_net_cfg_reset && GW_RESET_DATA_FACTORY != type) {
        PR_NOTICE("enter lowpower");
        GW_CNTL_S *gw_cntl = get_gw_cntl();
        gw_cntl->gw_wsm.nc_tp = GWNS_LOWPOWER;
        op_ret = wd_gw_wsm_write(&(gw_cntl->gw_wsm));
        if (OPRT_OK != op_ret) {
            PR_ERR("wd_gw_wsm_write failed! op_ret:%d", op_ret);
        }

        if (CMD_KIWI_STOP_WIFI == local_reset_type) {
            if (!op_ret) {
                send_kiwi_common_result(CMD_KIWI_STOP_WIFI_ACK, 0x00, 0x00);
            }
        }

    } else {
        if (is_net_cfg_reset) {
            PR_NOTICE("enter AP cfg");
            GW_WORK_STAT_MAG_S wsm;
            op_ret = wd_gw_wsm_read(&wsm);
            if ((op_ret == OPRT_OK) && (wsm.nc_tp != GWNS_UNCFG_AP)) {
                PR_NOTICE("wsm.nc_tp %d", wsm.nc_tp);
                wsm.nc_tp = GWNS_UNCFG_AP;
                op_ret = wd_gw_wsm_write(&wsm);
                if (OPRT_OK != op_ret) {
                    PR_ERR("wd_gw_wsm_write failed! op_ret:%d", op_ret);
                }
            }

        }

    }

    PR_NOTICE("gw_reset_cb %d", type);
    return ;
}



STATIC VOID __gw_status_cb(IN CONST GW_STATUS_E status)
{
    if (GW_ACTIVED == status) {
        ty_stream_actice_force_uplord();
    }
    if (GW_NORMAL == status) {
        tuya_ble_set_serv_switch(FALSE);
//        tkl_hci_deinit();
    }
    PR_NOTICE("gw_status_cb %d", status);
    return ;
}

STATIC OPERATE_RET __gw_ug_cb(IN CONST FW_UG_S *fw)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_NOTICE("gw_ug_cb Rev GW Upgrade Info");
    PR_NOTICE("fw->fw_url:%s", fw->fw_url);
    PR_NOTICE("fw->tp:%d fw->type:%d", fw->tp, fw->type);
    PR_NOTICE("fw->sw_ver:%s", fw->sw_ver);
    PR_NOTICE("fw->file_size:%d", fw->file_size);

    return op_ret;
}

STATIC INT_T __pre_gw_ug_cb(IN CONST FW_UG_S *fw)
{
    INT_T op_ret = OPRT_OK;
    PR_NOTICE("Rev GW Upgrade Info");
    PR_NOTICE("fw->fw_url:%s", fw->fw_url);
    PR_NOTICE("fw->tp:%d fw->type:%d", fw->tp, fw->type);
    PR_NOTICE("fw->sw_ver:%s", fw->sw_ver);
    PR_NOTICE("fw->file_size:%d", fw->file_size);

    op_ret = pre_gw_ug_kiwi_proc(fw);

    return op_ret;
}

STATIC VOID __dev_dp_recv_cb(IN CONST TY_DATAPOINT_DATA_S *datapoint)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;

    if (NULL == datapoint) {
        PR_ERR("datapoint is null\n");
        return ;
    }
    PR_DEBUG("dev_dp_recv_cb id %d type %d len %d", datapoint->dpid, datapoint->type, datapoint->len);

    ty_proc_dp(datapoint);

    return;
}

STATIC VOID __wf_net_change(IN CONST GW_WIFI_NW_STAT_E conn_state)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_NOTICE("wifi status is :%d", conn_state);
    STATIC BOOL_T cloud_flag = FALSE;
    BOOL_T wifi_to_mcu = FALSE;
    GW_CNTL_S *gw_cntl = NULL;

    if (STAT_LOW_POWER == conn_state) {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x02, 0x01);
    }

    if (STAT_CLOUD_CONN == conn_state || STAT_AP_CLOUD_CONN == conn_state) {
        send_kiwi_common_result(CMD_KIWI_COMMON_ACK, 0x00, 0x01);
#if 1
        op_ret = tuya_get_wifi_to_mcu(&wifi_to_mcu);
        if (op_ret) {
            PR_ERR("tuya_get_wifi_to_mcu err:%d", op_ret);
        } else {
            if (TRUE == wifi_to_mcu) {
                tuya_hal_system_sleep(100);
                send_kiwi_wf_state(WF_ST_KIWI_CONNECT_CLOUDE);
            }
        }
#endif
        ty_proc_kiwi_req_secret_key();
        if (!cloud_flag) {
            tuya_iot_reset_upgrade_detect_timer(100);
            ty_work_queue_add(tuya_get_time, NULL);
            ty_work_queue_add(proc_kiwi_dp_54_upload, NULL);
            ty_stream_init();
            cloud_flag = TRUE;
        }
        ty_work_queue_add(proc_kiwi_update_tem_password_cache, NULL);
    }
    return;
}


#define PID         "o0jaxrxrjdanps7w"
#define UUID        "uuida80736284ad3d95a"
#define AUTHKEY     "buWiMl8xVAiBEAGy1iVAOXgP42IOGHBv"

OPERATE_RET tuya_prod_info_cloud_handle(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (init_flag) {
        return op_ret;
    }
    ws_db_init_mf();
    WF_GW_PROD_INFO_S prod_info = {UUID, AUTHKEY};
    tuya_iot_set_wf_gw_prod_info(&prod_info);


    TY_IOT_INFO_S  iot_info;
    strcpy(iot_info.firmware_key, FIRM_KEY);
    strcpy(iot_info.firmware_version, USER_SW_VER);
    strcpy(iot_info.product_key, mcu_info.product_key);
    strcpy(iot_info.app_sw_version, "1.0.0");
    iot_info.cfg_mode = GWCM_LOW_POWER;
    iot_info.start_mode = WF_START_AP_ONLY;
    TY_IOT_CB_S ty_iot_cb;
    ty_iot_cb.gw_reset_cb = __gw_reset_cb; //重置回调
    ty_iot_cb.gw_status_cb = __gw_status_cb;//wifi状态回调
    ty_iot_cb.gw_ug_cb = __gw_ug_cb; //ota相关
    ty_iot_cb.ty_dev_dp_recv_cb = __dev_dp_recv_cb;//dp下发回调
    ty_iot_cb.wf_nw_stat_cb = __wf_net_change; //配网状态
    ty_iot_cb.pre_gw_ug_cb = __pre_gw_ug_cb; //ota相关

    ty_photo_cloudp2p_iot_init();

    op_ret = tuya_uart_cloud_init(&iot_info, ty_iot_cb);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_uart_cloud_init err:%d", op_ret);
        return op_ret;
    }
    init_flag = TRUE;
    return op_ret;
}


OPERATE_RET device_init(VOID)
{
    tuya_prod_info_cloud_handle();
    return OPRT_OK;
}



/**
 * @file tuya_main.c
 * @brief 涂鸦应用入口文件，原厂main()->user_main()->pre_app_init()->tuya_iot_init()->app_init()->
 *        pre_deivce_init()->device_init()
 *
 *        对于每一个芯片平台，存在一些差异性，此处可以对差异性进行处理，应用的特殊处理，应该放到应用预留接口里实现。应用
 *        预留接口包括：
 *        pre_app_init(): 用于系统初始的前置准备工作，此时涂鸦Device OS尚未启动
 *        app_init(): 用于应用初始化，此时涂鸦Device OS已经初始化
 *        pre_device_init()： 设备功能启动前置准备工作，此时设备功能尚未启动
 *        device_init()： 设备功能启动，完成之后设备进入正常工作状态
 *
 * @warning 此文件如非必要，禁止修改。
 *
 * @copyright Copyright (c) {2018-2020} 涂鸦科技 www.tuya.com
 *
 */
#ifndef TUYA_SDK_CLI_ADAPTER
#include "app_config.h"
#include "system/includes.h"
#include "mf_test.h"
#include "uni_log.h"
#include "tal_uart.h"
#include "tuya_gpio.h"
#include "gw_intf.h"
#include "tal_sleep.h"
#include "tuya_ble_sdk.h"
#include "tkl_wifi.h"
#include "tal_workq_service.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_error_code.h"
#include "tkl_thread.h"
#include "ws_db_gw.h"
#if defined(TY_BT_MOD) && (TY_BT_MOD==1)
#include "tuya_bt.h"
#include "tal_bluetooth_def.h"
#endif

#if defined(ENABLE_LWIP) && (ENABLE_LWIP == 1)
#include "lwip_init.h"
#endif

#if defined(ENABLE_PRODUCT_AUTOTEST) && (ENABLE_PRODUCT_AUTOTEST == 1)
#include "prod_test.h"
#endif

#if TY_SECURITY_CHIP
#include "Z32HUA_encrypt.h"
#endif

#include "tuya_uart_legacy.h"
#include "syscfg_id.h"

#define USER_SW_VER   "0.0.1"
#define APP_BIN_NAME  "tuya"

#include "tuya_video.h"
#include "app_agent.h"


/***********************************************************
*************************micro define***********************
***********************************************************/
#define TEST_SSID "tuya_mdev_test1"
#define WF_SSID_LEN 32
/***********************************************************
*************************variable define********************
***********************************************************/

/**
 * @brief gwcm_mode 是当前设备的配网工作模式，定义了不同模式下，设备的未配网、配网前、配网后、配网超时等场景的具体行为
 *      具体请参照Tuya Device OS 说明文档
 *
 */
STATIC GW_WF_CFG_MTHD_SEL gwcm_mode = GWCM_OLD;

/**
 * @brief prod_ssid_name 是产测扫描指定路由器的SSID，用于生产测试
 *
 */
STATIC CHAR_T prod_ssid_name[WF_SSID_LEN + 1] = TEST_SSID;

/**
 * @brief app_prod_test 是产测扫描到指定路由器之后，调用的产测回调函数，执行具体的应用产测功能
 *
 */
STATIC APP_PROD_CB app_prod_test = NULL;

STATIC THREAD_HANDLE ty_app_thread = NULL;

/***********************************************************
*************************function define********************
***********************************************************/

/**
 * @brief 应用初始化前置准备工作
 *
 *
 * @return VOID_T
 *
 * @note 在此函数中，应用可以执行一些配置设置、事件关注等和具体功能操作无关的工作，应用必须对其进行实现，如果不需要，则实现空函数。
 */
extern VOID_T pre_app_init(VOID_T);

/**
 * @brief 应用初始化接口
 *
 * @return VOID_T
 *
 * @note 在此函数，应用进行自身的初始化工作，应用必须对其进行实现，如果不需要，则实现空函数。
 */
extern VOID_T app_init(VOID_T);

/**
 * @brief 设备初始化前置准备工作
 *
 * @return VOID_T
 *
 * @note 应用必须对其进行实现，如果不需要，则实现空函数
 *
 */
extern VOID_T pre_device_init(VOID_T);

/**
 * @brief 设备初始化接口
 *
 * @return OPERATE_RET
 *
 * @note 应用必须对其进行实现，如果不需要，则实现空函数
 *
 */
extern OPERATE_RET device_init(VOID_T);


/**
 * @brief pre_gpio_test gpio测试前置接口，用于对gpio测试做准备工作，
 * 例如对gpio进行重新初始化，或者是关闭gpio test，关闭gpio test的时候，
 * gpio test会返回Ture
 *
 * @return VOID_T
 *
 * @note 应用必须对其进行实现，如果不需要，则实现空函数
 */
extern VOID_T mf_user_pre_gpio_test_cb(VOID_T);


/**
 * @brief mf_user_enter_callback 是配置进入产测回调接口
 *
 * @return VOID_T
 *
 * @note 应用必须对其进行实现，如果不需要，则实现空函数
 */
extern VOID_T mf_user_enter_callback(VOID_T);

/**
 * @brief mf_user_callback 是配置写入回调接口
 *
 * @return VOID_T
 *
 * @note 应用必须对其进行实现，如果不需要，则实现空函数
 */
extern VOID_T mf_user_callback(VOID_T);

/**
 * @brief mf_user_product_test_cb 是成品产测回调接口
 *
 * @return VOID_T
 *
 * @note 应用必须对其进行实现，如果不需要，则实现空函数
 *
 */
extern OPERATE_RET mf_user_product_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len);


/**
 * @brief mf_user_basic_test_cb 是基础产测回调接口
 *
 * @return VOID_T
 *
 * @note 用于处理gpio测试
 *
 */
extern OPERATE_RET mf_user_basic_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len);


#ifdef TUYA_SDK_FLASH_TEST
extern void flash_test_handle(void);
#endif /* TUYA_SDK_FLASH_TEST */

/**
 * @brief 应用设置产测回调和工作模式接口
 *
 * @param mthd 工作模式
 * @param callback 产测回调
 * @return VOID_T
 */
VOID app_cfg_set(IN CONST GW_WF_CFG_MTHD_SEL mthd, APP_PROD_CB callback)
{
    app_prod_test = callback;
    gwcm_mode = mthd;
}

/**
 * @brief 应用设置产测默认ssid
 *
 * @param ssid 产测默认ssid
 * @return VOID_T
 */
void set_prod_ssid(CHAR_T *ssid)
{
    if (strlen(ssid) > WF_SSID_LEN) {
        PR_ERR("ssid len over max value 32");
        return;
    }
    memset(prod_ssid_name, 0, sizeof(prod_ssid_name));
    strncpy(prod_ssid_name, ssid, WF_SSID_LEN);
    return;
}

#if !defined(ENABLE_PRODUCT_AUTOTEST)
/**
 * @brief 扫描产测ssid
 *
 * @return BOOL_T
 */
STATIC BOOL_T scan_test_ssid(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    GW_WORK_STAT_MAG_S read_gw_wsm;
    BOOL_T mf_close = FALSE;

    mf_close = mf_test_is_timeout();
    if (TRUE == mf_close) {
        PR_NOTICE("have actived over 15min, don't scan prod test ssid");
        return FALSE;
    }

    op_ret = wd_gw_wsm_read(&read_gw_wsm);

    if ((gwcm_mode == GWCM_OLD_PROD) || (gwcm_mode == GWCM_LOW_POWER_AUTOCFG) || (gwcm_mode == GWCM_SPCL_AUTOCFG)) { /* 上电默认配网或者第一次是配网的模式 */
        if ((read_gw_wsm.nc_tp >= GWNS_TY_SMARTCFG) && (read_gw_wsm.nc_tp != GWNS_UNCFG_SMC_AP)) { /* 已经存在ssid等配网信息但是并不是EZ和AP共存配网 */
            return FALSE;
        }
    } else if (gwcm_mode == GWCM_SPCL_MODE || gwcm_mode == GWCM_LOW_POWER) { /* 上电默认不配网 */
        if (read_gw_wsm.nc_tp >= GWNS_UNCFG_SMC) { /* 处于配网的状态 */
            return FALSE;
        }
    } else {
        ;
    }

    tal_wifi_set_work_mode(WWM_STATION);
    AP_IF_S *ap = NULL;
    BOOL_T flag = TRUE;
    PR_NOTICE("current product ssid name:%s", prod_ssid_name);
    op_ret = tal_wifi_assign_ap_scan((SCHAR_T *)prod_ssid_name, &ap);
    tal_wifi_station_disconnect();
    if (OPRT_OK != op_ret) {
        PR_DEBUG("tal_wifi_assign_ap_scan failed(%d)", op_ret);
        return FALSE;
    }

    //check if has authorized
    op_ret = wd_gw_base_if_read(&(get_gw_cntl()->gw_base));
    if (OPRT_OK != op_ret) {
        PR_DEBUG("read flash err");
        flag = FALSE;
    }

    // gateway base info verify
#if TY_SECURITY_CHIP
    if (!get_gw_cntl()->gw_base.has_auth) {
        PR_DEBUG("please write uuid and auth_key first");
        flag = FALSE;
    }
#else
    if (0 == get_gw_cntl()->gw_base.auth_key[0] || \
        0 == get_gw_cntl()->gw_base.uuid[0]) {
        PR_DEBUG("please write uuid and auth_key first");
        flag = FALSE;
    }
#endif

    if (app_prod_test) {
        app_prod_test(flag, ap->rssi);
    }

    return TRUE;
}
#endif

STATIC VOID __tuya_mf_uart_init(UINT_T baud, UINT_T bufsz)
{
    TAL_UART_CFG_T cfg;

    memset(&cfg, 0, sizeof(TAL_UART_CFG_T));
    cfg.base_cfg.baudrate = baud;
    cfg.base_cfg.databits = TUYA_UART_DATA_LEN_8BIT;
    cfg.base_cfg.parity = TUYA_UART_PARITY_TYPE_NONE;
    cfg.base_cfg.stopbits = TUYA_UART_STOP_LEN_1BIT;
    cfg.rx_buffer_size = bufsz;

    tal_uart_init(TY_UART0, &cfg);
}
STATIC VOID __tuya_mf_uart_free(VOID)
{

    tal_uart_deinit(TY_UART0);
}

STATIC VOID __tuya_mf_send(IN CONST BYTE_T *data, IN CONST UINT_T len)
{

    OPERATE_RET ret = tal_uart_write(TY_UART0, data, len);
}

STATIC UINT_T __tuya_mf_recv(OUT BYTE_T *buf, IN CONST UINT_T len)
{
    return tal_uart_read(TY_UART0, buf, len);
}


/**
 * @brief 涂鸦Deivce OS 启动入口
 *
 * @warning 如非必要，禁止修改。 修改请联系愚者（maht@tuya.com）确认
 */
static void user_main(void)
{
    OPERATE_RET rt = OPRT_OK;




    // 初始化LWIP
#if defined(ENABLE_LWIP) && (ENABLE_LWIP == 1)
    TUYA_LwIP_Init();
#endif

    //JL适配串口调试
#if 0
    const BYTE_T value_to_write[] = {0xDE, 0xAD, 0xBE, 0xEF};
    const UINT_T len = sizeof(value_to_write);
    char read_buf[300];
    TAL_UART_CFG_T cfg;
    memset(&cfg, 0, sizeof(TAL_UART_CFG_T));
    cfg.base_cfg.baudrate = 9600;
    cfg.base_cfg.databits = TUYA_UART_DATA_LEN_8BIT;
    cfg.base_cfg.parity = TUYA_UART_PARITY_TYPE_NONE;
    cfg.base_cfg.stopbits = TUYA_UART_STOP_LEN_1BIT;
    cfg.rx_buffer_size = 1024;
    tal_uart_init(TY_UART0, &cfg);
    while (1) {
        tkl_uart_write(TY_UART0, value_to_write, len);
        mdelay(500);
        tkl_uart_read(TY_UART0, (BYTE_T *)read_buf, 32);
    }
#endif



    // 应用初始化前置准备工作，用户在此处可以进行一些设置，为后续继续标准化预留
    pre_app_init();
    lan_pro_cntl_disable();
    // 涂鸦Device OS SDK 初始化， 因为DB初始化耗时较长，影响一些设备的启动效率，因此初始化的时候进行特殊处理
    // 对DB进行延后初始化
    TY_INIT_PARAMS_S init_param = {0};
    init_param.init_db = FALSE;
    strcpy(init_param.sys_env, TARGET_PLATFORM);
    TUYA_CALL_ERR_LOG(tuya_iot_init_params(NULL, &init_param));

    //设置授权时的mac地址
    unsigned char mac_read[6];
    syscfg_read(VM_TUYA_MAC_IDX, mac_read, 6);
    wifi_set_mac(mac_read);


    // 设备功能初始化前置准备工作，处理一些依赖于基线的基础能力，又需要快速处理的业务
    pre_device_init();

    // DB延后初始化
    tuya_iot_kv_flash_init(NULL);

    // 产测初始化， 注册函数需要应用实现，其中串口驱动不需要应用提供
    MF_IMPORT_INTF_S intf = {
        .uart_init = __tuya_mf_uart_init,
        .uart_send = (MF_UART_SEND_CB)__tuya_mf_send,
        .uart_recv = __tuya_mf_recv,
        .uart_free = __tuya_mf_uart_free,
        .mf_user_basic_test = mf_user_basic_test_cb,
        .mf_user_product_test = mf_user_product_test_cb,
        .user_callback = mf_user_callback,
        .user_enter_mf_callback = mf_user_enter_callback
    };
    TUYA_CALL_ERR_LOG(mf_init(&intf, APP_BIN_NAME, USER_SW_VER, TRUE));
    PR_NOTICE("mf_init succ");

    // 应用初始化
    app_init();

#if defined(ENABLE_PRODUCT_AUTOTEST) && (ENABLE_PRODUCT_AUTOTEST == 1)
    if (prodtest_ssid_scan(500)) {
        return;
    }
    // 初始化设备
    PR_DEBUG("device_init in");
    TUYA_CALL_ERR_LOG(device_init());
#else
    // 功能启动，其中 GWCM_OLD 模式特殊，在任意时刻都可以扫描SSID，进入产测模式。
    PR_DEBUG("gwcm_mode %d", gwcm_mode);//默认没有低功耗模式
    if (gwcm_mode != GWCM_OLD) {
        PR_DEBUG("low_power select");

        // 扫描到产测路由，进入产测模式，不需要进行设备初始化
        if (TRUE == scan_test_ssid()) {
            PR_DEBUG("prodtest");
            return;
        }

        // 没有扫描到产测路由，初始化设备
        PR_DEBUG("no tuya_mdev_test1!");
        PR_DEBUG("device_init in");
        TUYA_CALL_ERR_LOG(device_init());
    } else {
        // 初始化设备
        PR_DEBUG("device_init in");
        TUYA_CALL_ERR_LOG(device_init());
    }
#endif
    return;
}

static void tuya_app_thread(void *arg)
{
#ifdef TUYA_SDK_FLASH_TEST
    flash_test_handle();
#else
    user_main();
#endif /* TUYA_SDK_FLASH_TEST  */
    tkl_thread_release(ty_app_thread);
    ty_app_thread = NULL;
}

STATIC TKL_THREAD_HANDLE ty_test_thread = NULL;

#define BK7236_FLASH_TEST 1

#ifdef BK7236_FLASH_TEST
#define FLASH_TEST_START_ADDR       0x300000
#define FLASH_TEST_BUFFER_SIZE      4096
extern OPERATE_RET tkl_flash_erase(UINT_T addr, UINT_T size);
extern OPERATE_RET tkl_flash_read(UINT_T addr, UCHAR_T *dst, UINT_T size);
extern OPERATE_RET tkl_flash_write(UINT_T addr, CONST UCHAR_T *src, UINT_T size);
extern VOID_T *tkl_system_malloc(CONST SIZE_T size);
extern VOID_T tkl_system_free(VOID_T *ptr);
extern INT_T tkl_system_get_random(CONST UINT_T range);
#endif // BK7236_FLASH_TEST

static void tuya_test_thread(void *arg)
{
    uint32_t cnt = 0;
    tkl_system_sleep(5000);

#ifdef BK7236_FLASH_TEST
    int i;
    uint8_t *buf = (uint8_t *)tkl_system_malloc(FLASH_TEST_BUFFER_SIZE);
    uint8_t *check_buf = (uint8_t *)tkl_system_malloc(FLASH_TEST_BUFFER_SIZE);
#endif // BK7236_FLASH_TEST
    if (buf == NULL || check_buf == NULL) {
        bk_printf("malloc failed, exit test\r\n");
        goto _err_exit;
    }

    PR_DEBUG("------[%s %d] test start ------", __func__, __LINE__);
    while (1) {
#ifdef BK7236_FLASH_TEST
        memset(buf, 0, FLASH_TEST_BUFFER_SIZE);
        memset(check_buf, 0, FLASH_TEST_BUFFER_SIZE);

        tkl_flash_erase(FLASH_TEST_START_ADDR, FLASH_TEST_BUFFER_SIZE);

        for (i = 0; i < FLASH_TEST_BUFFER_SIZE; i++) {
            buf[i] = tkl_system_get_random(0);
        }
        tkl_flash_write(FLASH_TEST_START_ADDR, buf, FLASH_TEST_BUFFER_SIZE);

        tkl_flash_read(FLASH_TEST_START_ADDR, check_buf, FLASH_TEST_BUFFER_SIZE);
        for (i = 0; i < FLASH_TEST_BUFFER_SIZE; i++) {
            if (buf[i] != check_buf[i]) {
                bk_printf("flash test failed, %d %d\r\n", buf[i], check_buf[i]);
                goto _err_exit;
            }
        }
#endif // BK7236_FLASH_TEST

        cnt++;
        tkl_system_sleep(200);
        if (cnt >= 100000) {
            break;
        }
        if ((cnt % 100) == 0) {
            bk_printf("flash test %d\r\n", cnt);
        }
    }

    bk_printf("flash test complete successfully\r\n");

_err_exit:
#ifdef BK7236_FLASH_TEST
    if (buf != NULL) {
        tkl_system_free(buf);
        buf = NULL;
    }
    if (check_buf != NULL) {
        tkl_system_free(check_buf);
        check_buf = NULL;
    }
#endif // BK7236_FLASH_TEST

    tkl_thread_release(ty_test_thread);
    ty_test_thread = NULL;
}

void tuya_app_main(void)
{
    //tkl_thread_create(&ty_test_thread, "tuya_test", 4096, 4, tuya_test_thread, NULL);
    tkl_thread_create(&ty_app_thread, "tuya_app_main", 4096, 4, tuya_app_thread, NULL);
}

#ifdef CONFIG_TUYA_SDK_ENABLE
late_initcall(tuya_app_main);
#endif

#else
#include "tuya_error_code.h"
#include "tkl_thread.h"

STATIC TKL_THREAD_HANDLE ty_app_thread = NULL;

/**
 * @brief 涂鸦Deivce OS 启动入口
 *
 * @warning 如非必要，禁止修改。 修改请联系愚者（maht@tuya.com）确认
 */
static void user_main(void)
{
    OPERATE_RET rt = OPRT_OK;
    TUYA_LwIP_Init();
    cli_printf("begin cli init \r\n");

    tuya_cli_init(2, NULL);

    return;
}

static void tuya_app_thread(void *arg)
{
    user_main();
    tkl_thread_release(ty_app_thread);
    ty_app_thread = NULL;
}

void tuya_app_main(void)
{
    tkl_thread_create(&ty_app_thread, "tuya_app_main", 4096, 4, tuya_app_thread, NULL);
}
#endif

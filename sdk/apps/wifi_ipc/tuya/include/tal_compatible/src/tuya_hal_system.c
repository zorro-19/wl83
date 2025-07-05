/**
 * @file tuya_hal_system.c
 * @author sunkz@tuya.com
 * @brief 系统接口封装
 * @version 0.1
 * @date 2020-05-15
 *
 * @copyright Copyright (c) tuya.inc 2019
 *
 */

#include "tuya_hal_system.h"
#include "tuya_hal_ota.h"
#include "tuya_hal_network.h"

/**
* @brief Watch dog init and start
*
* @param[in] timeval: interval time for watch dog detection
*
* @note This API is used to init and start watch dog.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
UINT_T tuya_hal_watchdog_init_start(CONST UINT_T timeval)
{
    TUYA_WDOG_BASE_CFG_T cfg;
    cfg.interval_ms = timeval * 1000;
    return tal_watchdog_start(&cfg) / 1000;
}


int tuya_hal_ota_start_inform(unsigned int file_size, OTA_TYPE type)
{
    TUYA_OTA_PATH_E path = TUYA_OTA_PATH_AIR;

    if (type == UART_OTA_TYPE) {
        path = TUYA_OTA_PATH_UART;
    }

    return tal_ota_start_notify(file_size, TUYA_OTA_FULL, path);
}

int tuya_hal_ota_data_process(const unsigned int total_len, const unsigned int offset,
                              const unsigned char *data, const unsigned int len, unsigned int *remain_len, void *pri_data)
{
    TUYA_OTA_DATA_T pack;

    pack.data      = (UCHAR_T *)data;
    pack.len       = len;
    pack.offset    = offset;
    pack.total_len = total_len;
    pack.pri_data  = pri_data;

    return tal_ota_data_process(&pack, remain_len);
}


int tuya_hal_ota_end_inform(BOOL_T reset)
{
//    int ret = tal_ota_end_notify(NULL);
//    if ((ret == OPRT_OK) && (reset == TRUE)) {
//        tal_system_reset();
//    }

    return tal_ota_end_notify(reset);
}

int tuya_hal_net_socket_bind(int fd, const char *ip)
{
    TUYA_IP_ADDR_T addr = TY_IPADDR_ANY;

    if (ip) {
        addr = tal_net_str2addr(ip);
    }

    return tal_net_bind(fd, addr, 0);
}


#include "gw_intf.h"
#include "tuya_devos_utils.h"

OPERATE_RET wf_get_country_code(IN CONST CHAR_T *p_country_code)
{
    if (NULL == p_country_code) {
        return OPRT_INVALID_PARM;
    }

#if (defined(WIFI_GW) && (WIFI_GW==1))
    if (get_gw_cntl()->gw_base.country_code[0] != 0) {
        strcpy((CHAR_T *)p_country_code, get_gw_cntl()->gw_base.country_code);
        return OPRT_OK;
    }
#endif

    return OPRT_COM_ERROR;
}


void tuya_hal_system_reset(void)
{
    tal_system_reset();
}

int tuya_hal_get_random_data(const unsigned int range)
{
    extern int uni_random_range(unsigned int range);
    return uni_random_range(range);
}


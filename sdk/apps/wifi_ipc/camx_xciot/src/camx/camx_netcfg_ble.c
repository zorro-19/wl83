/****************************************************************************/
/* camx_netcfg_ble.c
 *
 ****************************************************************************/

/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/
#if 1
#include "camx.h"

/****************************************************************************/
/* Trace Definitions                                                        */
/****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "netcfg"
#include "xc_log.h"
/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/****************************************************************************/
/* Private Types                                                            */
/****************************************************************************/

/****************************************************************************/
/* Private Function Prototypes                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Data                                                             */
/****************************************************************************/

/* ble netcfg */
iot_bdn_ref_t s_camx_xciot_bdn;

/* ble module init */
bool s_camx_ble_init = false;

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Functions                                                        */
/****************************************************************************/

int netcfg_ble_send(uint8_t *data, uint16_t len)
{
    int rc = 0;

    camx_netcfg_ble_tx_data(data, len);

    return (rc);
}

int netcfg_ble_wifi_set(char *ssid, char *pwd)
{
    int rc = 0;

    T_I("BLE, get wifi ssid(%s), pwd(%s)", ssid, pwd);
    /* success  */
    osal_mdelay(1);
    // camx_audio_player_file_NetConnting();
    camx_uwifi_sta_connect(ssid, pwd, 1);
    T_I("ble do wifi_sta_connect, ssid(%s), passwd(%s)", ssid, pwd);

    return (rc);
}
/****************************************************************************/
/* Public Functions                                                         */
/****************************************************************************/

int camx_netcfg_ble_start(void)
{
    int rc = 0;

    if (s_camx_xciot_bdn) {
        avsdk_bdn_fini(&s_camx_xciot_bdn);
        s_camx_xciot_bdn = NULL;
    }
    rc = avsdk_bdn_init(
             &s_camx_xciot_bdn, netcfg_ble_send, netcfg_ble_wifi_set);
    if (rc) {
        T_E("Failed to avsdk_bdn_init, rc:%d", rc);
        return (-1);
    }

    if (s_camx_ble_init == false) {
        extern void bt_ble_module_init(void);
        bt_ble_module_init();


//
//        extern void bt_ble_init(void);
//        bt_ble_init();

        s_camx_ble_init = true;
    }

    return (0);
}

int camx_netcfg_ble_stop(void)
{

    if (s_camx_ble_init == true) {
        extern void bt_ble_exit(void);
        bt_ble_exit();

        extern void bt_ble_module_fini(void);
        bt_ble_module_fini();
        s_camx_ble_init = false;
    }

    if (s_camx_xciot_bdn) {
        avsdk_bdn_fini(&s_camx_xciot_bdn);
        s_camx_xciot_bdn = NULL;
    }

    return (0);
}

int camx_netcfg_ble_tx_data(uint8_t *data, int len)
{

    extern void xciot_ble_netcfg_send_data(const unsigned char *data,
                                           int                  len);
    xciot_ble_netcfg_send_data(data, len);
    T_IH_HEX("`--->BLE-TX`", data, len);


    return (0);
}

int camx_netcfg_ble_on_data(unsigned char *data, int len)
{


#if TCFG_USER_BLE_ENABLE && TCFG_BT_NET_CFG_XC_EN
    T_IH_HEX("`<---BLE-RX`", data, len);
    if (s_camx_xciot_bdn) {
        avsdk_bdn_recv(s_camx_xciot_bdn, data, len);
    }
#endif /* TCFG_USER_BLE_ENABLE && BT_NET_CFG_EN */

    return (0);
}
#endif
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

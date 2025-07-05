/****************************************************************************/
/* camx_uwifi.h
 *
 ****************************************************************************/
#ifndef CAMX_UWIFI_H_INCLUDE
#define CAMX_UWIFI_H_INCLUDE
/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

#if !defined(CAMX_H_INCLUDE)
#error "Only 'camx.h' can be included directly."
#endif /* CAMX_H_INCLUDE */

/* group */

/****************************************************************************/
/* Configure Definitions                                                    */
/****************************************************************************/

/* wifi stat default ssid/pwd */
#define CAMX_UWIFI_DEFULT_STA_SSID ""
#define CAMX_UWIFI_DEFULT_STA_PWD  ""


/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/****************************************************************************/
/* Public Types                                                             */
/****************************************************************************/

typedef struct camx_uwifi_sta_info {
    char ssid[64];
    char pwd[64];
    int  channel;
    char local_mac[64];
    char gw_mac[64];
    char ipaddr[64];
    char netmask[64];
    char gateway[64];
    char dns1[64];
    char dns2[64];
} camx_uwifi_sta_info_t;

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

// 标记是否在配网状态
extern bool g_camx_wifi_netcfg_running;

// 标记是否在配网连接中
extern bool g_camx_wifi_netcfg_connecting;

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************/
/* Public Function Prototypes                                               */
/****************************************************************************/

void camx_uwifi_init(void);
void camx_uwifi_netcfg_start(void);
void camx_uwifi_netcfg_stop(void);
void camx_uwifi_sta_connect(char *ssid, char *pwd, char save);
void camx_uwifi_sta_get_info(camx_uwifi_sta_info_t *info);
void camx_uwifi_show_info(void);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* CAMX_UWIFI_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

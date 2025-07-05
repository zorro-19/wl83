/****************************************************************************/
/* camx.h
 *
 ****************************************************************************/
#ifndef CAMX_H_INCLUDE
#define CAMX_H_INCLUDE
/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

/* csdk */
#ifdef CAMX_APP_SIMULATOR
#else
#include "app_config.h"
/* driver/cpu */
#include "asm/includes.h"
/* driver/device */
#include "device/includes.h"
#include "device/device.h"
#include "device/gpio.h"
// #include "device/gpcnt.h"
#include "device/uart.h"
#include "device/iic.h"
// #include "device/spiflash.h"
/* system */
#include "system/includes.h"
#include "sys_common.h"
#include "fs/fs.h"

/* utils */
#include "character_coding.h"
#include "yuv_soft_scalling.h"
#include "yuv_to_rgb.h"
/* utils/event */
#include "event/event.h"
#include "event/bt_event.h"
#include "event/device_event.h"
#include "event/key_event.h"
#include "event/net_event.h"
#include "event/touch_event.h"
/* utils/fs */
// #include "fs/fs.h"
/* utils/syscfg */
#include "syscfg/syscfg_id.h"
// #include "syscfg/config_interface.h"
// #include "syscfg/config_transport.h"
// #include "syscfg/config_target.h"
/* utils/ui */
// #include "ui/includes.h"

/* server */
#include "server/ai_server.h"
// #include "server/asr_server.h"
#include "server/audio_dev.h"
#include "server/audio_server.h"
#include "server/video_dec_server.h"
#include "server/video_engine_server.h"
#include "server/video_server.h"
#include "server/vpkg_server.h"
#include "server/vunpkg_server.h"
#include "server/usb_syn_api.h"
//#include "server/md.h"
#include "server/led_ui_server.h"
// #include "server/ui_server.h"
// #include "server/upgrade_server.h"
/* update */
#include "update/update.h"
#include "update/update_loader_download.h"
#include "update/net_update.h"

/* net/wifi */
#include "wifi/wifi_connect.h"
/* net/http */
#include "http/http_cli.h"
/* net/server */
#include "server/rt_stream_pkg.h"

/* apps/demo/project */
#include "storage_device.h"
#include "get_yuv_data.h"
//#include "rt_stream_pkg.h"

#endif /* CAMX_APP_SIMULATOR */

/* lib osal */
#include "osal/osal_api.h"
/* lib xciot */
#include "xciot_api.h"


/* camx group */

#include "camx_netcfg_ble.h"
#include "camx_ota.h"
#include "camx_uwifi.h"
#include "camx_types.h"


/****************************************************************************/
/* Configure Definitions                                                    */
/****************************************************************************/


//////////////////////
// 是否支持二维码配网
//////////////////////
#define CAMX_HW_SUPPORT_NETCFG_BLE    1 ///< 蓝牙配网是否支持
//////////////////////
// 是否支持 cs
//////////////////////
#define CAMX_HW_SUPPORT_CS_VIDEO 1 ///< 是否支持视频-云存储
//////////////////////


#define CAMX_APP_USE_JL_SDK_1_1_X    1 //1使用杰里最新sdk1.1.x; 0.使用1.0.3版本sdk
/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/* version */
#define CAMX_APP_SW_VER "1.00.01.02_220601"
#define CAMX_APP_HW_VER "v1"


/****************************************************************************/
/* Public Types                                                             */
/****************************************************************************/


/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/



/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************/
/* Public Function Prototypes                                               */
/****************************************************************************/

int xc_main(void);

int xc_send_video(uint8_t *data, int len);
int xc_send_audio(uint8_t *data, int len);

int camx_key_handler(u8 from, u8 action, u8 keyval);
/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* CAMX_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/* camx_plat.h
 *
 ****************************************************************************/
#ifndef CAMX_PLAT_H_INCLUDE
#define CAMX_PLAT_H_INCLUDE
/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

#if !defined(CAMX_H_INCLUDE)
#error "Only 'camx.h' can be included directly."
#endif /* CAMX_H_INCLUDE */

/****************************************************************************/
/* Configure Definitions                                                    */
/****************************************************************************/

// pc模拟延时5秒网络ready
#define CAMX_SIM_NETWORK_READY_DELAY_SECONDS 1

/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

// fmt
#define PRId64_FMT PRId64
#define PRIi64_FMT PRIi64
#define PRIo64_FMT PRIo64
#define PRIu64_FMT PRIu64
#define PRIx64_FMT PRIx64
#define PRIX64_FMT PRIX64

// std clibs
#define camx_snprintf  snprintf
#define camx_vsnprintf vsnprintf

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
//读取配置文件
int xc_iotcfg_read(uint8_t *data, uint16_t *len, uint16_t cap);
// 设备网络已经启动
bool camx_plat_network_is_started(void);
// 获取设备macaddr
void camx_plat_get_mac(uint8_t macaddr[6]);
// 同步重启设备
void camx_plat_reboot(uint8_t flag);
//创建线程异步重启
void reboot_async(int sleep_ms);
// 打印复位的原因
void camx_plat_reset_reason(void);
int camx_plat_reset(uint32_t flag);

// 打印os运行状态
void camx_plat_os_stats(void);
// 打印mem统计状态
void camx_plat_mem_stats(void);

// wifi信号质量(1-6)
int camx_plat_wifi_qos(void);



/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* CAMX_PLAT_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

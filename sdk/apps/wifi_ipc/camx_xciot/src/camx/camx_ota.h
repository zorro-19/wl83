/****************************************************************************/
/* camx_ota.h
 *
 ****************************************************************************/
#ifndef CAMX_OTA_H_INCLUDE
#define CAMX_OTA_H_INCLUDE
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

/* ota recv data */
#define CAMX_OTA_RECV_SIZE (1024 * 8)

/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

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

typedef enum {
    OTA_FAILED = 0,
    OTA_SUCCESSFUL = 1,
    OTA_NO_UPDATE = 2,
} OTA_RESULT_E;

// typedef enum {
// VIDEO_STREAM_NONE = 0,
// VIDEO_STREAM_STOP = 1,
// VIDEO_STREAM_START = 2,
// } VIDEO_STREAM_STATUS_E;

typedef struct {
    unsigned crc32;
    unsigned magic;
    char     uuid[32];
} BACKUP_UUID_S;

typedef struct {
    unsigned file_size;
    struct sys_time write_time;
} SD_UPGRADE_INFO_S;

typedef struct {
    BACKUP_UUID_S bak_uuid;
    SD_UPGRADE_INFO_S sd_upgrade_info;
} RESERVED_EXPAND_CONFIG_S;


typedef enum {
    PARAM_INT = 0,
    PARAM_STR = 1,
} CONFIG_PARAM_TYPE_E;

//保存SD卡升级信息, 过滤SD卡重复升级
int write_sd_upgrade_info(SD_UPGRADE_INFO_S *pInfo);

//读取SD卡升级信息，过滤SD卡重复升级
int read_sd_upgrade_info(SD_UPGRADE_INFO_S *pInfo);

//检测设备是否处于正在升级状态
// int check_in_upgrade(void);


int camx_ota_upgrade(const char *url);
int camx_ota_check(void);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* CAMX_OTA_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

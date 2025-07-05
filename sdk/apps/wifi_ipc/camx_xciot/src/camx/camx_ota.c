/****************************************************************************/
/* camx_ota.c
 *
 ****************************************************************************/

/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

#include "camx.h"

/****************************************************************************/
/* Trace Definitions                                                        */
/****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "ota"
#include "xc_log.h"

/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/****************************************************************************/
/* Private Types                                                            */
/****************************************************************************/

/**
 * @brief camx ota ctx.
 */
/* struct IpcWorkData { */
/* uint32_t device_idle_status: 1; */
/* uint32_t in_upgrade: 1; */
/* uint32_t tci_startup_failed: 1; */
/* uint32_t tci_logon: 1; */
/* uint32_t tci_init_ok: 1; */
/* uint32_t time_sync_flag: 1; */
/* uint32_t recv_config_network_cmd: 1; */
/* uint32_t client_delete_device: 1; */
/* uint32_t cli_num: 4; */
/* }; */
/* static struct IpcWorkData _IpcDat; */

/* int check_in_upgrade(void) */
/* { */
/* return !!_IpcDat.in_upgrade; */
/* } */

/* int set_upgrade(u8 status) */
/* { */
/* _IpcDat.in_upgrade = status; */
/* } */

struct camx_ota {
    uint32_t running : 1;
    char     url[1024];
    int      file_size;
    int      file_offset;
};

/****************************************************************************/
/* Private Function Prototypes                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Data                                                             */
/****************************************************************************/

struct camx_ota s_camx_ota;

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Functions                                                        */
/****************************************************************************/


static int ota_upgrade_http_callback(void         *ctx,
                                     void         *buf,
                                     unsigned int  size,
                                     void         *priv,
                                     httpin_status status)
{
    httpcli_ctx *c = ctx;

    if (status == HTTPIN_HEADER) {
        //第一次连接时，记录文件总长度
        if (c->lowRange == 0) {
            s_camx_ota.file_size = c->content_length;
            T_I("~~~~~~~~~~~OTA Download file size:%d",
                s_camx_ota.file_size);
        }
    }

    return 0;
}

static int ota_upgrade(const char *url)
{
    int                            error       = 0;
    int                            ret         = 0;
    int                            offset      = 0;
    int                            remain      = 0;
    u8                            *buffer      = NULL;
    int                            data_offset = 0;
    int                            total_len   = 0;
    const struct net_download_ops *ops         = &http_ops;
    void                          *update_fd   = NULL;

    /* lwip read/close undef it */
#undef read
#undef close

    /* show url */
    T_I("camx ota url(`%s`)", url);

    /* clean it */
    s_camx_ota.file_size   = 0;
    s_camx_ota.file_offset = 0;

    /* httpclient ctx */
    httpcli_ctx *ctx = (httpcli_ctx *)calloc(1, sizeof(httpcli_ctx));
    if (NULL == ctx) {
        return -1;
    }
    ctx->url             = url;
    ctx->connection      = "close"; //"keep-alive";//"close";
    ctx->timeout_millsec = 10000;
    ctx->cb              = ota_upgrade_http_callback;

    /* download init */
    error = ops->init(ctx);
    if (error != HERROR_OK) {
        goto __exit;
    }
    T_I("camx ota init......");

    /* net open CONFIG_UPGRADE_OTA_FILE_NAME */
    error     = -1;
    update_fd = net_fopen(CONFIG_UPGRADE_OTA_FILE_NAME, "w");
    if (!update_fd) {
        goto __exit;
    }
    T_I("camx ota net_fopen file:%s", CONFIG_UPGRADE_OTA_FILE_NAME);

    /* alloc recv buffer */
    buffer = (u8 *)malloc(CAMX_OTA_RECV_SIZE);
    if (!buffer) {
        goto __exit;
    }

    total_len = ctx->content_length;
    if (total_len <= 0) {
        goto __exit;
    }
    s_camx_ota.file_size = total_len;
    T_I("camx ota download file size:%d", total_len);

    /* recv file */
    while (total_len > 0) {
        if (total_len >= CAMX_OTA_RECV_SIZE) {
            remain = CAMX_OTA_RECV_SIZE;
            total_len -= CAMX_OTA_RECV_SIZE;
        } else {
            remain    = total_len;
            total_len = 0;
        }

        do {
            ret = ops->read(ctx, (char *)buffer + offset, remain - offset);
            if (ret < 0) {
                T_E("Failed camx ota donwload, ret:%d", ret);
                goto __exit;
            }
            offset += ret;
        } while (remain != offset);

        if (data_offset == 0) {
            //此处延时是为了避免播放提示音时刷写flash导致卡音问题
            os_time_dly(500);
        }

        ret = net_fwrite(update_fd, buffer, offset, 0);
        if (ret != offset) {
            T_E("Failed camx ota net_fwrite, ret:%d", ret);
            goto __exit;
        }

        data_offset += offset;
        /* offset add */
        s_camx_ota.file_offset = data_offset;
        /* cost stop */
        float percent = s_camx_ota.file_offset * 100.0 / s_camx_ota.file_size;
        uint8_t percent_integer = (uint8_t)percent;
        uint8_t percent_fraction =
            (uint8_t)((percent - percent_integer) * 100);
        T_I("camx ota upg [%d/%d/%d] %u.%02u%%",
            offset,
            data_offset,
            s_camx_ota.file_size,
            percent_integer,
            percent_fraction);


        avsdk_firmware_rate_v2(0, percent_integer);
        offset = 0;
    }

    error = 0;

__exit:
    if (buffer) {
        free(buffer);
    }
    if (update_fd) {
        net_fclose(update_fd, error);
    }
    ops->close(ctx);
    free(ctx);

    return error;
}

static void ota_upgrade_task(void *arg)
{
    int         rc;

    rc = ota_upgrade(s_camx_ota.url);

    T_I("camx_ota_upg(%s), rc:%d",
        s_camx_ota.url,
        rc);
    if (rc == 0) {
        T_I("camx_ota_upg success, reboot it...");
        /* osal_mdelay(2000); */
        camx_plat_reboot(0);
    } else {
        T_E("camx_ota_upg(%s) error:%d", rc);
    }
    s_camx_ota.running = 0;
    (void)arg;
}

/****************************************************************************/
/* Public Functions                                                         */
/****************************************************************************/

int camx_ota_upgrade(const char *url)
{
    int rc = -1;

    if (s_camx_ota.running == 0) {
        s_camx_ota.running = 1;
        snprintf(s_camx_ota.url, sizeof(s_camx_ota.url), "%s", url);
        rc =
            thread_fork("T@camx.ota", 22, 1024, 0, 0, ota_upgrade_task, NULL);
        T_I("camx ota create task, url(%s), rc:%d", url, rc);
        // 这里假设thread_fork不能失败
    } else {
        T_W("camx ota is running, try later!!!");
        rc = -1;
    }

    return (rc);
}

int camx_ota_check(void)
{
    return (0);
}

static int read_reserved_expand_config(void *buf, int buf_size)
{
    u32 flash_addr = __FLASH_SIZE__ - 0x1000;
    if (0 != norflash_open(NULL, NULL, NULL)) {
        printf("norflash_open failed\n");
        return -1;
    }
    int ret = norflash_origin_read((u8 *)buf, flash_addr, buf_size);
    if (buf_size != ret) {
        printf("norflash_origin_read error, buf_size = %d, ret = %d\n", buf_size, ret);
        return -1;
    }

    return 0;
}
int write_sd_upgrade_info(SD_UPGRADE_INFO_S *pInfo)
{
    RESERVED_EXPAND_CONFIG_S st_expand_config;
    memset(&st_expand_config, 0x0, sizeof(st_expand_config));

    if (0 != read_reserved_expand_config(&st_expand_config, sizeof(st_expand_config))) {
        printf("write sd upgrade info failed\n");
        return -1;
    }
    memcpy(&st_expand_config.sd_upgrade_info, pInfo, sizeof(SD_UPGRADE_INFO_S));

    u32 flash_addr = __FLASH_SIZE__ - 0x1000;
    norflash_open(NULL, NULL, NULL);
    //擦除一个扇区
    norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, flash_addr);
    //写入数据
    int ret = norflash_write(NULL, (void *)&st_expand_config, sizeof(st_expand_config), flash_addr);
    if (ret != sizeof(st_expand_config)) {
        printf("write sd upgrade info error\n");
    } else {
        printf("write sd upgrade info successful\n");
    }
    return 0;
}

int read_sd_upgrade_info(SD_UPGRADE_INFO_S *pInfo)
{
    RESERVED_EXPAND_CONFIG_S st_expand_config;
    memset(&st_expand_config, 0x0, sizeof(st_expand_config));

    if (0 != read_reserved_expand_config(&st_expand_config, sizeof(st_expand_config))) {
        printf("read sd upgrade info failed\n");
        return -1;
    }
    memcpy(pInfo, &st_expand_config.sd_upgrade_info, sizeof(SD_UPGRADE_INFO_S));
    return 0;
}
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

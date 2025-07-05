#include <time.h>
#include "app_config.h"
#include "system/timer.h"
#include "os/os_api.h"
#include "device/device.h"
#include "wifi/wifi_connect.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
//#include "dev_net_oauth.h"
#include "boot.h"
#include "asm/sfc_norflash_api.h"
#include "asm/crc16.h"
#include "http/http_cli.h"
#include "fs/fs.h"
#include "init.h"
#include "generic/circular_buf.h"
#include "syscfg_id.h"
#include "action.h" //app_core
#include "app_core.h" //app_core

#define PROFILE_FLASH_PATH "mnt/sdfile/app/profile"

#define PROFILE_HOST "log.jieliapp.com"

#define GET_MAC_PROFILE 			"https://"PROFILE_HOST"/jltange/v1/api/firmware/license/mac/allocate?pid=%d"
#define GET_JLK_PROFILE 			"https://"PROFILE_HOST"/jltange/v1/api/firmware/license/allocate?pid=%d&mac=%s"
#define GET_KEY_PROFILE 			"https://"PROFILE_HOST"/jltange/v1/api/firmware/license/exchange?JLKey=%s&thirdType=%d"
#define GET_FORCE_UPGRADE 			"http://"PROFILE_HOST"/jltange/v1/api/firmware/license/upgrade/force?pid=%d&versionCode=%d"

#ifdef CONFIG_XCIOT_ENABLE
#define KEY_PRIFILE  1
#else
#define KEY_PRIFILE  2
#endif // CONFIG_XCIOT_ENABLE
#define MAGIC  0x55AA66CC
struct profile {
    u32 magic;
    u8 mac_adr[14];
    u8 jlkey[64];
    u8 uuid[512];
    char *url;

} ipc_profile;


static void flash_data_secret(const char *src, char *dst, u32 len, u32 seed)
{
    u32 i;
    u32 *ptr_src = (u32 *)src;
    u32 *ptr_dst = (u32 *)dst;
    seed *=  seed;
    for (i = 0; i < len / 4; i++) {
        ptr_dst[i] = ptr_src[i] ^  seed;
    }
}

static int __https_get_mothed(const char *url, int (*cb)(char *, void *), void *priv)
{
    int error = 0;
    http_body_obj http_body_buf;
    httpcli_ctx ctx;
    printf("profile_get_url->%s\n", url);
    memset(&http_body_buf, 0x0, sizeof(http_body_obj));
    memset(&ctx, 0x0, sizeof(httpcli_ctx));

    http_body_buf.recv_len = 0;
    http_body_buf.buf_len = 1 * 1024;
    http_body_buf.buf_count = 1;
    http_body_buf.p = (char *) malloc(http_body_buf.buf_len * sizeof(char));

    ctx.url = url;
    ctx.priv = &http_body_buf;
    ctx.connection = "close";
    ctx.timeout_millsec = 5000;
    error = httpcli_get(&ctx);
    if (error == HERROR_OK) {
        error = cb(http_body_buf.p, priv);
    } else {

        error = -1;
    }
    if (http_body_buf.p) {
        free(http_body_buf.p);
    }
    return error;
}


static int get_profile_mac_cb(char *buf, void *priv)
{
    printf("%s\n", buf);
    json_object *new_obj;
    const char *json_str;
    json_str = strstr(buf, "{\"");
    if (!json_str) {
        return -1;
    }
    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        return -1;
    }

    char *mac = json_object_get_string(json_object_object_get(new_obj, "data"));
    printf("mac->%s\n", mac);
    strcpy(ipc_profile.mac_adr, mac);
    json_object_put(new_obj);

    return 0;

}

int get_profile_mac(void)
{
    char url[256];
    sprintf(url, GET_MAC_PROFILE, PRODUCT_PID);
    return __https_get_mothed(url, get_profile_mac_cb, NULL);


}



static int get_profile_jlk_cb(char *buf, void *priv)
{
    printf("%s\n", buf);
    json_object *new_obj;
    const char *json_str;
    json_str = strstr(buf, "{\"");
    if (!json_str) {
        return -1;
    }

    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        return -1;
    }

    char *key = json_object_get_string(json_object_object_get(new_obj, "data"));
    printf("key->%s\n", key);
    strcpy(ipc_profile.jlkey, key);
    json_object_put(new_obj);


    return 0;

}

int get_profile_jlk(void)
{
    char url[256];
    sprintf(url, GET_JLK_PROFILE, PRODUCT_PID, ipc_profile.mac_adr);
    return __https_get_mothed(url, get_profile_jlk_cb, NULL);
}


static int get_profile_third_party_key_cb(char *buf, void *priv)
{
    printf("%s\n", buf);
    json_object *new_obj;
    const char *json_str;
    json_str = strstr(buf, "{\"");
    if (!json_str) {
        return -1;
    }



    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        return -1;
    }

    char *key = json_object_get_string(json_object_object_get(new_obj, "data"));
    printf("key->%s\n", key);
    strcpy(ipc_profile.uuid, key);
    json_object_put(new_obj);

    return 0;

}

int get_profile_third_party_key(void)
{
    char url[256];
    sprintf(url, GET_KEY_PROFILE, ipc_profile.jlkey, KEY_PRIFILE);
    return __https_get_mothed(url, get_profile_third_party_key_cb, NULL);

}



static int get_force_upgrade_cb(char *buf, void *priv)
{
    printf("%s\n", buf);
    json_object *new_obj;
    const char *json_str;
    json_str = strstr(buf, "{\"");
    if (!json_str) {
        return -1;
    }



    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        return -1;
    }

    char *url = json_object_get_string(json_object_object_get(new_obj, "data"));
    printf("key->%s\n", url);
    if (url[0] == '\0') {
        json_object_put(new_obj);
        return -1;
    }

    ipc_profile.url = calloc(1, strlen(url));

    strcpy(ipc_profile.url, url);
    /* strcpy(ipc_profile.uuid, key); */
    json_object_put(new_obj);

    return 0;

}

int get_force_upgrade(void)
{
    char url[256];
    sprintf(url, GET_FORCE_UPGRADE, PRODUCT_PID, JL_VERISON);
    return __https_get_mothed(url, get_force_upgrade_cb, NULL);

}





int profile_flash_read(const unsigned int addr, unsigned char *dst, const unsigned int size)
{
    if (NULL == dst) {
        return -1;
    }

    norflash_origin_read(dst, addr, size);

    return 0;
}

int profile_flash_write(const unsigned int addr, const unsigned char *src, const unsigned int size)
{
    if (NULL == src) {
        return -1;
    }

    norflash_write(NULL, src, size, addr);

    return 0;
}

int profile_flash_erase(const unsigned int addr, const unsigned int size)
{
#define FLASH_BLOCK 4096
    norflash_open(NULL, NULL, NULL);

    int beginBlock = (addr / FLASH_BLOCK);
    int endBlock = (((addr + size) / FLASH_BLOCK));

    int writeLength = 0;
    int length = FLASH_BLOCK - (addr % FLASH_BLOCK);

    norflash_ioctl(NULL, IOCTL_SET_WRITE_PROTECT, 0);

    if (length >= size) {
        norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, beginBlock * FLASH_BLOCK);//每个块，写之前擦除对应块
        return 0;
    } else {
        norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, beginBlock * FLASH_BLOCK);//每个块，写之前擦除对应块
        writeLength = length;
    }

    for (int i = beginBlock + 1; i < endBlock; i++) {
        norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, i * FLASH_BLOCK);
        norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, i * FLASH_BLOCK);
        writeLength += FLASH_BLOCK;
    }

    if (beginBlock != endBlock && (size > writeLength)) {
        norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, endBlock * FLASH_BLOCK);
    }

    return 0;
}

int str_to_hex(char *out_string, int length, char *in_string)
{
    int index;
    char *fmt = "%02x";

    for (index = 0; index < length; index++) {
        snprintf((char *)&out_string[index << 1], 3, fmt, in_string[index]);
    }
    return (length << 1);
}
static int set_flash_wifi_mac(char *mac)
{
    int ret = 0;

    ret = syscfg_write(CFG_BT_MAC_ADDR, mac, 6);

    wifi_set_mac(mac);
    set_wireless_netif_macaddr(mac);
    return ret;
}

#if 1
int get_third_party_platform_info(void)
{
    int ret = 0;

    //1.查看flash是否已经有了
    int len;
    u8 mac_data[6];
    ret = syscfg_read(CFG_BT_MAC_ADDR, mac_data, 6);

    snprintf(ipc_profile.mac_adr, sizeof(ipc_profile.mac_adr), "%02x%02x%02x%02x%02x%02x", mac_data[0], mac_data[1], mac_data[2], mac_data[3], mac_data[4], mac_data[5]);

    printf("mac:%x:%x:%x:%x:%x:%x\n", mac_data[0], mac_data[1], mac_data[2], mac_data[3], mac_data[4], mac_data[5]);
    printf("ret = %d ipc_profile.mac_adr:%s\n", ret, ipc_profile.mac_adr);

    if (ret <= 0) {
        printf("get_flash_mac_addr syscfg_read fail! %d\r\n", ret);
        ret = get_profile_mac();
        if (ret < 0) {
            printf("Get Third Party Mac Fail\n");
            return ret;

        }
    }

    snprintf(ipc_profile.mac_adr, sizeof(ipc_profile.mac_adr), "%02x%02x%02x%02x%02x%02x", mac_data[0], mac_data[1], mac_data[2], mac_data[3], mac_data[4], mac_data[5]);



    /* strcpy(ipc_profile.mac_adr, "a4648a7b6db6"); */
    printf("syscfg_read success mac:%s\n", ipc_profile.mac_adr);
    ret = get_profile_jlk();
    if (ret < 0) {
        printf("Get Third Party JKL Fail\n");
        return ret;

    }

#if 1
    ret = get_profile_third_party_key();
    if (ret < 0) {
        printf("Get Third Party Key Fail\n");
        return ret;

    }

    char __mac[16] = {0};
    u32 tmp;

    memcpy(__mac, ipc_profile.mac_adr, 12);
    //bug fix
    sscanf(&__mac[10], "%x", &tmp);
    mac_data[5] = tmp;
    __mac[10] = '\0';
    sscanf(&__mac[8], "%x", &tmp);
    mac_data[4] = tmp;
    __mac[8] = '\0';
    sscanf(&__mac[6], "%x", &tmp);
    mac_data[3] = tmp;
    __mac[6] = '\0';
    sscanf(&__mac[4], "%x", &tmp);
    mac_data[2] = tmp;
    __mac[4] = '\0';
    sscanf(&__mac[2], "%x", &tmp);
    mac_data[1] = tmp;
    __mac[2] = '\0';
    sscanf(&__mac[0], "%x", &tmp);
    mac_data[0] = tmp;

    printf("mac->%x:%x:%x:%x:%x:%x\n", mac_data[0], mac_data[1], mac_data[2], mac_data[3], mac_data[4], mac_data[5]);
    ret = set_flash_wifi_mac((char *)mac_data);
    if (ret < 0) {
        printf("set_flash_wifi_mac err, %d\n", ret);
    }


    /* int set_auth_code(char *buf, int len) */

    set_auth_code(ipc_profile.uuid, strlen(ipc_profile.uuid));

#endif
    return 0;

}
#endif


#ifdef CONFIG_XCIOT_ENABLE
char avsdk_cfg[] = "[iot]\n\n"
                   "did = 000000000000000000\n\n"
                   "signkey = 000000000000000000000000\n\n"
                   "lslat = 000000000000000000000000\n\n"
                   "scode = 000000\n\n"
                   "gdomain = prod.glbs.xcthings.com\n\n"
                   "gipaddr = 47.240.1.244,39.108.59.60,8.209.77.49,47.252.5.225\n\n";

#endif

const char *get_uuid_code(void)
{
#if USE_NET_GET_UUID
    char code[127]; //用于保存读取到的auth code
    int len;        //读取到的auth code长度

    if (0 == get_auth_code(code, &len)) {
        /* put_buf(code, len); */
    } else {
        puts("get_auth_code err\n");
        return 0;
    }

    code[len] = '\0';

#ifdef CONFIG_XCIOT_ENABLE
    // 分割出的四个子字符串
    char *token;
    char *delimiters = " ";
    char *did_position;
    char *signkey_position;
    char *lslat_position;
    char *scode_position;

    // 将分割出来的子字符串赋值给相应变量
    token = strtok(code, delimiters);
    did_position = token;

    for (int i = 0; i < 3; i++) {
        token = strtok(NULL, delimiters);
        if (i == 0) {
            signkey_position = token;
        } else if (i == 1) {
            lslat_position = token;
        } else if (i == 2) {
            scode_position = token;
        }
    }

    // 替换 avsdk_cfg 中的内容
    char *did_pos = strstr(avsdk_cfg, "did = ");
    if (did_pos != NULL) {
        char *digit_pos = did_pos + strlen("did = ");
        strncpy(digit_pos, did_position, strlen(did_position));
    }

    char *signkey_pos = strstr(avsdk_cfg, "signkey = ");
    if (signkey_pos != NULL) {
        char *digit_pos = signkey_pos + strlen("signkey = ");
        strncpy(digit_pos, signkey_position, strlen(signkey_position));
    }

    char *lslat_pos = strstr(avsdk_cfg, "lslat = ");
    if (lslat_pos != NULL) {
        char *digit_pos = lslat_pos + strlen("lslat = ");
        strncpy(digit_pos, lslat_position, strlen(lslat_position));
    }

    char *scode_pos = strstr(avsdk_cfg, "scode = ");
    if (scode_pos != NULL) {
        char *digit_pos = scode_pos + strlen("scode = ");
        strncpy(digit_pos, scode_position, strlen(scode_position));
    }

    /* printf("did_position: %s\n", did_position); */
    /* printf("signkey_position: %s\n", signkey_position); */
    /* printf("lslat_position: %s\n", lslat_position); */
    /* printf("scode_position: %s\n", scode_position); */


    /* printf("avsdk_cfg[] =%s\n",avsdk_cfg); */
    /* put_buf(avsdk_cfg,215); */


    return avsdk_cfg;
#endif

    strcpy(ipc_profile.uuid, code);
    /* printf("ipc_profile.uuid =%s\n",ipc_profile.uuid); */
#endif
    return ipc_profile.uuid;
}


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
        }
    }

    return 0;
}

int ota_upgrade(const char *url)
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

    /* clean it */

    /* httpclient ctx */
    httpcli_ctx *ctx = (httpcli_ctx *)calloc(1, sizeof(httpcli_ctx));
    if (NULL == ctx) {
        return -1;
    }
    ctx->url             = url;
    ctx->connection      = "close"; //"keep-alive";//"close";
    ctx->timeout_millsec = 10000;
    ctx->cb              = ota_upgrade_http_callback;
    printf("====================%s   %d\n", __func__, __LINE__);
    /* download init */
    error = ops->init(ctx);
    if (error != HERROR_OK) {
        goto __exit;
    }

    printf("====================%s   %d\n", __func__, __LINE__);
    /* net open CONFIG_UPGRADE_OTA_FILE_NAME */
    error     = -1;
    update_fd = net_fopen("update-ota.ufw", "w");
    if (!update_fd) {
        goto __exit;
    }

    printf("====================%s   %d\n", __func__, __LINE__);
    /* alloc recv buffer */
    buffer = (u8 *)malloc(8 * 1024);
    if (!buffer) {
        goto __exit;
    }

    printf("====================%s   %d\n", __func__, __LINE__);
    total_len = ctx->content_length;
    if (total_len <= 0) {
        goto __exit;
    }
    printf("ota download file size:%d", total_len);

    /* recv file */
    while (total_len > 0) {
        if (total_len >= 8 * 1024) {
            remain = 8 * 1024;
            total_len -= 8 * 1024;
        } else {
            remain    = total_len;
            total_len = 0;
        }

        do {
            ret = ops->read(ctx, (char *)buffer + offset, remain - offset);
            if (ret < 0) {
                printf("Failed camx ota donwload, ret:%d", ret);
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
            printf("Failed camx ota net_fwrite, ret:%d", ret);
            goto __exit;
        }

        data_offset += offset;

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
    printf("url :%s\n", ipc_profile.url);
    rc = ota_upgrade(ipc_profile.url);

    if (rc == 0) {
        printf("jl upgrade ota_upg success, reboot it...");
        /* osal_mdelay(2000); */
        /* camx_plat_reboot(0); */
        os_time_dly(200);
        cpu_reset();
    } else {
        printf("jl ota_upg(%s) error:%d", rc);
    }
}

/****************************************************************************/
/* Public Functions                                                         */
/****************************************************************************/

/* int ota_upgrade(const char *url) */
/* { */

/* } */


void check_platform_invaild()
{
    /* printf("=========================check platform \n\n"); */
    static u8 ota_update = 0;
    if (ota_update) {
        return;
    }



    int ret = get_force_upgrade();
    if (ret != 0) {
        printf("not switch  platform\n");

    } else {
        struct intent it;
        init_intent(&it);
        it.name	= "video_rec";//APP状态机在：video_rec.c
        it.action = ACTION_BACK;
        start_app(&it);

        //get uuid
        get_third_party_platform_info();
        ota_update = 1;
        //upgrade
        thread_fork("jl_ota", 22, 2048, 0, 0, ota_upgrade_task, NULL);
    }



}

#define TANGE_TYPE    1
#define XCIOT_TYPE    2


#ifdef CONFIG_XCIOT_ENABLE
#define PLATFORM_TPYE  XCIOT_TYPE
#define PLATFORM_NAME  "XCIOT"
#else
#define PLATFORM_TPYE  TANGE_TYPE
#define PLATFORM_NAME  "TANGE"
#endif // CONFIG_XCIOT_ENABLE


int get_product_pid()
{
    return PRODUCT_PID;
}

int get_platfrom_type()
{
    return PLATFORM_TPYE;
}

char *get_platfrom_ver()
{
    return FIRMWARE_VER;
}
int get_jl_ver()
{
    return JL_VERISON;
}
char *get_platfrom_name()
{
    return PLATFORM_NAME;
}









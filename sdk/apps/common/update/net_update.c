
#include "system/includes.h"
#include "system/task.h"
#include "app_config.h"
#include "net_update.h"
#include "update/update_loader_download.h"
#include "generic/errno-base.h"
#include "update.h"
#include "timer.h"
#include "fs/fs.h"
#include "os/os_api.h"
#include "device/device.h"
#include "asm/includes.h"
#include "ota_impl.h"
#if (defined THIRD_PARTY_PROTOCOLS_SEL && (THIRD_PARTY_PROTOCOLS_SEL & MIJIA_EN))
#include "syscfg/syscfg_id.h"
#include "user_cfg_id.h"
#endif

//=======================net_update==========================================================
#define NET_UPDATE_STATE_NONE	0
#define NET_UPDATE_STATE_OK		1
#define NET_UPDATE_STATE_ERR	2
#define NET_UPDATE_STATE_CLOSE	3

#define NET_UPDATE_BUF_CHECK	0x12345678 //防止写超buf检测
/* #define DUAL_BANK_VERIFY_ENABLE */    //回读flash进行校验
/* #define DATA_DOWNLOAD_VERIFY_ENABLE */ //对下载的数据进行校验

#define FLASH_SECTOR_SIZE 			(4*1024)
#define NET_UPDATE_BUFF_SIZE_MAX	(4*1024) //缓存要>=4K，否则可能会引起在初始化时候升级失败

struct net_update {
    u8 update_doing;
    u8 update_state;
    u8 write_to_flash;
    u8 *recv_buf;
    u32 recv_buf_size;
    u32 offset;
    u32 recv_cnt;
    u32 req_seek;
    OS_SEM sem;
    FILE *fd;
};

#if defined DATA_DOWNLOAD_VERIFY_ENABLE
typedef struct stJL_FILE_HEAD {
    u16 u16Crc;
    u16 u16DataCrc;
    u32 u32Address;
    u32 u32Length;

    u8 u8Attribute;
    u8 u8Res;
    u16 u16Index;
    char szFileName[16];
} JL_FILE_HEAD;

extern u16 calc_crc16_with_init_val(u16 init_crc, u8 *ptr, u16 len);
static int firstBlock = 1;
static u16 calcCrc = 0;
static JL_FILE_HEAD gUpdateHead;
#elif (defined THIRD_PARTY_PROTOCOLS_SEL && (THIRD_PARTY_PROTOCOLS_SEL & MIJIA_EN))
typedef struct stJL_FILE_HEAD {
    u16 u16Crc;
    u16 u16DataCrc;
    u32 u32Address;
    u32 u32Length;

    u8 u8Attribute;
    u8 u8Res;
    u16 u16Index;
    char szFileName[16];
} JL_FILE_HEAD;

static int firstBlock = 1;
static JL_FILE_HEAD gUpdateHead;
static u32 update_file_size = 0;
u32 get_update_file_size(void)
{
    syscfg_read(CFG_OTA_PART_SIZE, &update_file_size, sizeof(u32));
    return update_file_size;
}
#endif

static struct net_update *net_update_info = NULL;
int storage_device_ready(void);
u32 get_target_udate_addr(void);


void test_update_process_notify_callback(void *priv)
{
    static u32 percent = 0;
    update_file_info *info = (update_file_info *)priv;
    u32 tmp = info->finish_len * 100 / info->file_size;
#if (defined THIRD_PARTY_PROTOCOLS_SEL && (THIRD_PARTY_PROTOCOLS_SEL & MIJIA_EN))
    if (update_file_size) {
        info->file_size = update_file_size;
    }
#endif
    if (percent != tmp || tmp == 0) {
        printf("update[%s] >> %d%% \n", info->FileName, tmp);
        percent = tmp;
    }

    if (percent == 100) {
        percent = 0;
    }
}

//=======================net_update==========================================================
#ifdef DUAL_BANK_VERIFY_ENABLE
static int dual_bank_verify_hdl(int result)
{
    if (result) {
        printf("app core verify OK!");
        //回读校验正确，更新启动信息
        dual_bank_update_burn_boot_info(net_update_finish_callback);
    } else if (net_update_info) {
        //回读校验错误
        net_update_info->update_state = NET_UPDATE_STATE_ERR;
        os_sem_post(&net_update_info->sem);
        printf("net_update err\n\n");
        return -1;
    }

    return 0;
}
#endif

#if defined DATA_DOWNLOAD_VERIFY_ENABLE
static int net_update_check(JL_FILE_HEAD *head, const u8 *buf, const u32 len)
{
    int ret;

    if ((32 > len) || (NULL == head)) {
        return -1;
    }

    memcpy((u8 *)head, buf, sizeof(JL_FILE_HEAD));

    ret = jl_file_head_valid_check(head);
    if (ret) {
        return -1;
    }

    if (0 == strcmp((head->szFileName), "update_data")) {
        return 0;
    }

    printf("update file not match!\n");
    return -1;
}
#elif (defined THIRD_PARTY_PROTOCOLS_SEL && (THIRD_PARTY_PROTOCOLS_SEL & MIJIA_EN))
static int net_update_check(JL_FILE_HEAD *head, const u8 *buf, const u32 len)
{
    int ret;
    u32 size = 0;

    if ((32 > len) || (NULL == head)) {
        return -1;
    }

    memcpy((u8 *)head, buf, sizeof(JL_FILE_HEAD));

    ret = jl_file_head_valid_check(head);
    if (!ret) {
        update_file_size = head->u32Length;
        syscfg_write(CFG_OTA_PART_SIZE, &update_file_size, sizeof(u32));
    } else {
        syscfg_read(CFG_OTA_PART_SIZE, &size, sizeof(u32));
        if (size > 0) {
            update_file_size = size;
        }
    }
    printf("%s=%d==size = %d", __func__, __LINE__, head->u32Length);
    return 0;
}
#endif

static void net_update_system_reset(void *priv)//to do
{
#if 0
    if (get_power_keep_state() & POWER_KEEP_RTC) { //需要使用软关机唤醒的方式复位,否则系统复位会导致RTC时间掉
        printf("cpu by rtc reset soft_poweroff....\n\n");
        power_set_soft_poweroff(10);//first pwoer off 10ms will power on
    } else
#endif
    {
        printf("cpu system_reset ....\n\n");
        system_soft_reset();
    }
}
static int net_update_doing_callback(void *result)
{
    if (result) {
        if (net_update_info) {
            net_update_info->update_state = NET_UPDATE_STATE_ERR;
            os_sem_post(&net_update_info->sem);
        }
        printf("net_update doing err\n\n");
    }

    return 0;
}
static int net_update_finish_callback(int result)
{
    if (!result) {
        if (net_update_info) {
            net_update_info->update_state = NET_UPDATE_STATE_OK;
            os_sem_post(&net_update_info->sem);
        }
        printf("net_update successfuly\n\n");
    } else if (net_update_info) {
        net_update_info->update_state = NET_UPDATE_STATE_ERR;
        os_sem_post(&net_update_info->sem);
        printf("net_update err\n\n");
        return -1;
    }
    return 0;
}
int net_update_request(void)
{
    if (net_update_info) {
        return net_update_info->update_doing;
    }
    return 0;
}
void *net_fopen(char *path, char *mode)//net_fopen支持写flash固件升级和写到SD卡，当名字字符有CONFIG_UPGRADE_OTA_FILE_NAME时是固件升级
{
    //防止超时时，在没退出时，客户端再次重入
    int ret = net_update_request();
    if (ret) {
        printf("err ota update is doing !!!!!!!!!!!!!!\n");//保证FTP传输等网络升级请求需要确保传输队列只有一次OTA文件请求（否则后续无法升级）
        return NULL;
    }

    struct net_update *net_update = zalloc(sizeof(struct net_update));
    if (!net_update) {
        printf("err in no mem \n\n");
        goto err;
    }
    if (strstr(path, CONFIG_UPGRADE_OTA_FILE_NAME)) {//名字是OTA升级名字就进行写flash升级模式
        net_update->recv_buf = malloc(NET_UPDATE_BUFF_SIZE_MAX + 4);
        if (!net_update->recv_buf) {
            goto err;
        }
        net_update->update_doing = true;
        net_update->write_to_flash = true;
        net_update->offset = 0;
        net_update->req_seek = 0;
        net_update->recv_cnt = 0;
        net_update->update_state = NET_UPDATE_STATE_NONE;
        net_update->recv_buf_size = NET_UPDATE_BUFF_SIZE_MAX;
        os_sem_create(&net_update->sem, 0);
        net_update_info = net_update;
        u32 *check = (u32 *)(net_update->recv_buf + net_update->recv_buf_size);
        *check = NET_UPDATE_BUF_CHECK;
        set_update_process_notify_cb(test_update_process_notify_callback);
        return (void *)net_update;
    } else if (storage_device_ready()) {
        net_update->fd = fopen(path, mode);
        if (!net_update->fd) {
            goto err;
        }
        return (void *)net_update;
    }
err:
    if (net_update) {
        if (net_update->recv_buf) {
            free(net_update->recv_buf);
        }
        free(net_update);
    }
    net_update_info = NULL;
    return NULL;
}
int net_fclose(void *fd, char is_socket_err)
{
    struct net_update *net_update = (struct net_update *)fd;
    int err = 0;

    if (!net_update) {
        net_update = net_update ? net_update : net_update_info;
        printf("warnning net_fclose fd NULL \n");
    }
    if (net_update->write_to_flash) {
        u32 *check = (u32 *)(net_update->recv_buf + net_update->recv_buf_size);
        if (*check != NET_UPDATE_BUF_CHECK) {
            printf("err check in %s, check = 0x%x \n\n\n", __func__, *check);
        }
        printf("net close %s \n", is_socket_err ? "is_socket_err" : "normal");
        if (net_update->offset && net_update->update_state == NET_UPDATE_STATE_NONE && !is_socket_err) {
            err = net_fwrite(net_update, NULL, net_update->offset, 1);//写剩余的缓存到flash
            if (err != net_update->offset) {
                err = -1;
                printf("err net_fclose write  = %d \n", err);
            }
        }

        if (net_update->update_state == NET_UPDATE_STATE_NONE && !is_socket_err) {
#ifdef DATA_DOWNLOAD_VERIFY_ENABLE
            if (calcCrc == gUpdateHead.u16DataCrc) {
                dual_bank_update_burn_boot_info(net_update_finish_callback);
                err = os_sem_pend(&net_update_info->sem, 500);
                if (err) {
                    err = -1;
                    printf("net_update verify wait time out err\n\n\n\n");
                }
            } else {
                printf("crc err, calcCrc = 0x%x, headCrc = 0x%x\n", calcCrc, gUpdateHead.u16DataCrc);
                net_update->update_state == NET_UPDATE_STATE_ERR;
            }
#else

#ifdef DUAL_BANK_VERIFY_ENABLE
            dual_bank_update_verify(NULL, NULL, dual_bank_verify_hdl);
#else
            //更新启动信息
            dual_bank_update_burn_boot_info(net_update_finish_callback);
#endif //DUAL_BANK_VERIFY_ENABLE

            err = os_sem_pend(&net_update_info->sem, 500);
            if (err) {
                err = -1;
                printf("net_update verify wait time out err\n\n\n\n");
            }
#endif //DATA_DOWNLOAD_VERIFY_ENABLE
        }

        net_update->update_doing = 0;
        if (net_update->update_state == NET_UPDATE_STATE_OK) {//升级成功，2s后重启系统
            sys_timeout_add_to_task("sys_timer", NULL, net_update_system_reset, 2000);
            printf(">>>>>>>>>>>net_update successfuly , system will reset after 2s ...\n\n");
        } else {
            err = -1;
            printf(">>>>>>>>>>>net_update err\n\n\n\n");
        }
        net_update->update_state = NET_UPDATE_STATE_CLOSE;
        os_sem_del(&net_update->sem, OS_DEL_ALWAYS);
        dual_bank_passive_update_exit(NULL);
    } else if (net_update->fd) {
        fclose(net_update->fd);
    }
    if (net_update->recv_buf) {
        free(net_update->recv_buf);
    }
    net_update_info = NULL;
    free(net_update);
    return err;
}
int net_flen(void *fd)
{
    struct net_update *net_update = (struct net_update *)fd;
    if (net_update && !net_update->write_to_flash && net_update->fd) {
        return flen(net_update->fd);
    }
    return 0;
}
int net_fread(void *fd, char *buf, int len)
{
    struct net_update *net_update = (struct net_update *)fd;
    if (net_update && !net_update->write_to_flash && net_update->fd) {
        return fread(buf, 1, len, net_update->fd);
    }
    return 0;
}
int net_fwrite(void *fd, unsigned char *buf, int len, int end)
{
    struct net_update *net_update = (struct net_update *)fd;
    int ret = len;
    int err;
    int wr_len = 0;
    int wr_offset = 0;
    int rd_len = 0;
    int rd_offset = 0;
    int buf_offset = 0;
    int cp_remain = net_update->recv_buf_size;
    u8 *cp_buf = (u8 *)net_update->recv_buf;
    u32 *check = (u32 *)(net_update->recv_buf + net_update->recv_buf_size);

#ifdef DATA_DOWNLOAD_VERIFY_ENABLE
    if (buf) {
        if (firstBlock) {
            err = net_update_check(&gUpdateHead, buf, len);
            if (err) {
                printf("net_update_check err!");
                return -EINVAL;
            }
            calcCrc = calc_crc16_with_init_val(calcCrc, buf + 32, len - 32);
            firstBlock = 0;
        } else {
            calcCrc = calc_crc16_with_init_val(calcCrc, buf, len);
        }
    }
#elif (defined THIRD_PARTY_PROTOCOLS_SEL && (THIRD_PARTY_PROTOCOLS_SEL & MIJIA_EN))
    if (buf) {
        if (firstBlock) {
            err = net_update_check(&gUpdateHead, buf, len);
            if (err) {
                printf("net_update_check err!");
                return -EINVAL;
            }
            firstBlock = 0;
        }
    }
#endif

    if (net_update->write_to_flash) {
        if (net_update->update_state == NET_UPDATE_STATE_OK) {
            net_update->offset = 0;
            return ret;
        } else if (net_update->update_state == NET_UPDATE_STATE_ERR || net_update->update_state == NET_UPDATE_STATE_CLOSE) {
            return -EINVAL;
        }
        while (len) {
            if (net_update->offset < net_update->recv_buf_size && !end) {//写到缓存，直到缓存满才写flash
                rd_len = MIN(net_update->recv_buf_size - net_update->offset, len);
                memcpy(net_update->recv_buf + net_update->offset, buf + rd_offset, rd_len);
                net_update->offset += rd_len;
                rd_offset += rd_len;
                len -= rd_len;
                if (*check != NET_UPDATE_BUF_CHECK) {
                    printf("err check in %s, check = 0x%x \n\n\n", __func__, *check);
                }
                if (net_update->offset < net_update->recv_buf_size) {
                    return ret;
                }
            }
            if (!end) {
                net_update->offset = 0;
                cp_remain = net_update->recv_buf_size - net_update->offset;
            } else {
                cp_remain = net_update->offset;
                len -= cp_remain;
            }
            while (cp_remain) {
                if (!net_update->recv_cnt) {//第一次写则初始化双备份升级
                    err = dual_bank_passive_update_init(0, 0, NET_UPDATE_BUFF_SIZE_MAX, NULL);
                    if (err || dual_bank_update_allow_check(0)) {
                        net_update->update_state = NET_UPDATE_STATE_ERR;
                        printf("net_fwrite init check err \n\n");
                        return err;
                    }
                    u32 target_addr = get_target_udate_addr();
                    u32 addr = ADDR_ALIGNE(target_addr, FLASH_SECTOR_SIZE);
                    u32 first_size = addr - target_addr;
                    if (first_size) {
                        //要先写前4K对齐剩下字节，否则出现数据包不完整
                        err = dual_bank_update_write(cp_buf, first_size, NULL);
                        if (err) {
                            net_update->update_state = NET_UPDATE_STATE_ERR;
                            return err;
                        }

                        memcpy(cp_buf, cp_buf + first_size, \
                               cp_remain > first_size ? (cp_remain - first_size) : cp_remain);

                        net_update->offset = (cp_remain > first_size ? (cp_remain - first_size) : cp_remain);
                        net_update->recv_cnt += first_size;
                        break;
                    }
                }
                if (net_update->update_state) {
                    printf("net_update update_state = %d \n\n", net_update->update_state);
                    net_update->offset = 0;
                    return net_update->update_state == NET_UPDATE_STATE_OK ? ret : -EINVAL;
                }
                if (*check != NET_UPDATE_BUF_CHECK) {
                    printf("err check in %s, check = 0x%x \n\n\n", __func__, *check);
                }
                //写数据到flash
                err = dual_bank_update_write(cp_buf, cp_remain, net_update_doing_callback);
                if (err) {
                    net_update->update_state = NET_UPDATE_STATE_ERR;
                    return err;
                }
                net_update->recv_cnt += cp_remain;
                cp_remain -= cp_remain;
            }
        }
    } else if (net_update->fd) {
        fwrite(buf, 1, len, net_update->fd);
    }
    return ret;
}




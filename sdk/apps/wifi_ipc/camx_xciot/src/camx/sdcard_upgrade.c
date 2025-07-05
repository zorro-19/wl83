#include "system/includes.h"
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "app_config.h"
#include "update/update.h"
#include "fs/fs.h"
#include "update/update_loader_download.h"
/* #include "ipc_tool.h" */
#include "camx.h"

struct fs_update {
    void *fd;
    const char *update_path;
};
static struct fs_update fs_update = {0};
#define __this 		(&fs_update)

//static u8 disk_upgrade_status = 0;

//void  set_disk_upgrade_status(u8 status)
//{
//     disk_upgrade_status = status;
//}
//
//u8 get_disk_upgrade_status()
//{
//    return disk_upgrade_status;
//}

static u16 fs_open(void)
{
    if (!__this->update_path) {
        printf("file path err \n\n");
        return false;
    }
    if (__this->fd) {
        return true;
    }
    __this->fd = fopen(__this->update_path, "r");
    if (!__this->fd) {
        printf("file open err \n\n");
        return false;
    }
    return true;
}

static u16 fs_read(void *fp, u8 *buff, u16 len)
{
    if (!__this->fd) {
        return (u16) - 1;
    }
    int ret = fread(buff, 1, len, __this->fd);
    if (ret != len) {
        printf("fread file error\n\n");
        return -1;
    }
    return len;
}
static int fs_seek(void *fp, u8 type, u32 offset)
{
    if (!__this->fd) {
        return (int) - 1;
    }
    return fseek(__this->fd, offset, type);
}
static u16 fs_stop(u8 err)
{
    if (__this->fd) {
        fclose(__this->fd);
        __this->fd = NULL;
    }
    return true;
}
static const update_op_api_t fs_update_opt = {
    .f_open = fs_open,
    .f_read = fs_read,
    .f_seek = fs_seek,
    .f_stop = fs_stop,
};


static int fs_update_set_file_path(const char *update_path)
{
    void *fd;
    fd = fopen(update_path, "r");
    if (!fd) {
        printf("update file open err: %s\n", update_path);
        return false;
    }

    if (check_upgrade_file_same(fd)) {
        fclose(fd);
        return false;
    }

    __this->update_path = update_path;
    printf("update file path = %s\n", update_path);

    fclose(fd);
    return true;
}

int record_upgrade_file_info(const char *update_path)
{
    void *fd;
    fd = fopen(update_path, "r");
    if (!fd) {
        printf("update path open err: %s\n", update_path);
        return -1;
    }

    struct vfs_attr attr;

    if (0 != fget_attrs(fd, &attr)) {
        printf("get update file attr err\n");
        fclose(fd);
        return -1;
    }

    SD_UPGRADE_INFO_S sInfo;
    sInfo.file_size = attr.fsize;
    sInfo.write_time = attr.wrt_time;
    int ret = write_sd_upgrade_info(&sInfo);
    if (ret < 0) {
        printf("save sd upgrade file info error\n");
    } else {
        unsigned file_size = attr.fsize;
        struct sys_time t = attr.wrt_time;
        printf("record upgrade file size = %u, write time : %4d%02d%02d_%02d%02d%02d\n", file_size, t.year, t.month, t.day, t.hour, t.min, t.sec);
    }
    fclose(fd);
    return ret;
}
int check_upgrade_file_same(void *fd)
{
    struct vfs_attr attr;

    if (0 != fget_attrs(fd, &attr)) {
        printf("get update file attr err\n");
        fclose(fd);
        return 0;
    }

    unsigned file_size = attr.fsize;
    struct sys_time t = attr.wrt_time;
    printf("upgrade file size = %u, write time : %4d%02d%02d_%02d%02d%02d\n", file_size, t.year, t.month, t.day, t.hour, t.min, t.sec);

    SD_UPGRADE_INFO_S sInfo;
    memset(&sInfo, 0x0, sizeof(SD_UPGRADE_INFO_S));
    int ret = read_sd_upgrade_info(&sInfo);
    if (ret == 0) {
        file_size = sInfo.file_size;
        t = sInfo.write_time;
        printf("record upgrade file size = %u, write time : %4d%02d%02d_%02d%02d%02d\n", file_size, t.year, t.month, t.day, t.hour, t.min, t.sec);
        if (file_size == attr.fsize &&
            t.year == attr.wrt_time.year &&
            t.month == attr.wrt_time.month &&
            t.day == attr.wrt_time.day &&
            t.hour == attr.wrt_time.hour &&
            t.min == attr.wrt_time.min &&
            t.sec == attr.wrt_time.sec) {
            printf("upgrade file is same, no need to upgrade again!\n");
            return 1;
        }
    }

    return 0;
}

#if !CONFIG_DOUBLE_BANK_ENABLE
//单备份升级
static void fs_update_param_private_handle(UPDATA_PARM *p)
{
    u16 up_type = p->parm_type;
    void *start = (void *)((u32)p + sizeof(UPDATA_PARM));
    extern const char updata_file_name[];

    if ((up_type == SD0_UPDATA) || (up_type == SD1_UPDATA)) {
        UPDATA_SD sd = {0};
        /* #if TCFG_SD0_ENABLE */
        /* sd.control_type = SD_CONTROLLER_0; */
        /* sd.control_io = (TCFG_SD_PORTS == 'A') ? SD0_IO_A : ((TCFG_SD_PORTS == 'B') ? SD0_IO_B : ((TCFG_SD_PORTS == 'C') ? SD0_IO_C : SD0_IO_D)); */
        /* #elif TCFG_SD1_ENABLE */
        /* sd.control_type = SD_CONTROLLER_1; */
        /* sd.control_io = (TCFG_SD_PORTS == 'A') ? SD1_IO_A : SD1_IO_B; */
        /* #endif */
        sd.power = 0;//是否启用SDPG电源引脚，1则开启SDPG电源
        memcpy(start, &sd, sizeof(UPDATA_SD));
    } else if (up_type == USB_UPDATA) {
        //
    }
    memcpy(p->file_patch, updata_file_name, strlen(updata_file_name));
}
#endif
static void fs_update_state_cbk(int type, u32 state, void *priv)
{
    update_ret_code_t *ret_code = (update_ret_code_t *)priv;
    switch (state) {
    case UPDATE_CH_EXIT:
        if ((0 == ret_code->stu) && (0 == ret_code->err_code)) {
            UPDATA_PARM *update_ram = UPDATA_FLAG_ADDR;
            memset(update_ram, 0, 32);
            if (support_dual_bank_update_en) {
                memset(update_ram, 0, sizeof(UPDATA_PARM));
                update_ram->magic = type;
                update_result_set(UPDATA_SUCC);
                printf("app >>>>>>>>>>>>>>>>>>sdcard update ok , cpu reset ...\n");
            } else {
#if !CONFIG_DOUBLE_BANK_ENABLE
                //单备份
                update_mode_api_v2(type, fs_update_param_private_handle, NULL);
#endif
                printf(">>>>>>>>>>>>>>>>>> cpu reset , uboot todo update ...\n");
            }
#if CONFIG_DOUBLE_BANK_ENABLE
            printf("fdelete_by_name:%s\n", __this->update_path);
            fdelete_by_name(__this->update_path);
            os_time_dly(500);
#endif

            system_reset(1);//todo
        } else {
            printf("ret_code->stu:%d  ret_code->err_code:%d\n", ret_code->stu, ret_code->err_code);
            update_result_set(UPDATA_DEV_ERR);
            printf("\nsdcard update err !!! \n");


            /* int set_upgrade(u8 status) ; */

            /* set_upgrade(0); */
            /* os_time_dly(100); */
            /* voice_playing(VOICE_UPGRADE_FAIL); */
            /* os_time_dly(500); */

        }
        break;
    }
}

#if CONFIG_DOUBLE_BANK_ENABLE
static void get_update_percent_info(update_percent_info *info)
{
    printf("update >>> total_len=%u, finish_len = %u, %d%%\n", info->total_len, info->finish_len, info->percent);
}
#endif

//sd卡/u盘文件系统升级例子
static void do_disk_upgrade(void *arg)
{
    os_time_dly(300);
    /* voice_playing(VOICE_DISK_UPGRADE); */
    os_time_dly(500);
    struct intent it;
    init_intent(&it);
    it.name	= "video_rec";//APP状态机在：video_rec.c
    it.action = ACTION_BACK;
    start_app(&it);


    update_mode_info_t info = {

#if TCFG_SD0_ENABLE
        .type = SD0_UPDATA,
#elif TCFG_SD1_ENABLE
        .type = SD1_UPDATA,
#endif

        .state_cbk = fs_update_state_cbk,
        .p_op_api = &fs_update_opt,
        .task_en = 0,
    };

#if CONFIG_DOUBLE_BANK_ENABLE
    register_update_percent_info_callback_handle(get_update_percent_info);
#endif

    app_active_update_task_init(&info);

}

extern bool update_success_boot_check2(const char *update_path);
int check_disk_upgrade(void)
{
    /* if (update_success_boot_check2(CONFIG_UPGRADE_PATH)) { */
    /* return -1; */
    /* } */

    if (fs_update_set_file_path(CONFIG_UPGRADE_PATH) == false) {
        return -1;
    }

    if (thread_fork("do_disk_upgrade", 10, 1024, 0, NULL, do_disk_upgrade, NULL) != OS_NO_ERR) {
        printf("do_disk_upgrade thread fork fail\n");
        return -1;
    }

    return 0;
}

//late_initcall(c_app_upgrade);

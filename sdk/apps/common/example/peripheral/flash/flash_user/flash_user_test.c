#include "app_config.h"
#include "system/includes.h"
#include "fs/fs.h"
#include "asm/sfc_norflash_api.h"

#ifdef USE_FLASH_USER_TEST_DEMO

#define USER_FLASH_SPACE_PATH "mnt/sdfile/EXT_RESERVED/user"

static u32 user_get_flash_exif_addr(void)
{
    u32 addr;
    FILE *profile_fp = fopen(USER_FLASH_SPACE_PATH, "r");
    if (profile_fp == NULL) {
        puts("user_get_flash_addr ERROR!!!\r\n");
        return 0;
    }
    struct vfs_attr file_attr;
    fget_attrs(profile_fp, &file_attr);
    addr = sdfile_cpu_addr2flash_addr(file_attr.sclust);
    fclose(profile_fp);

    printf("user_get_flash_exif_addr = 0x%x, size = 0x%x \r\n", addr, file_attr.fsize);
    return addr;
}

static void flash_user_test_task(void *arg)
{
    printf("\r\n\r\n\r\n\r\n\r\n ----------- USER_FLASH_EXIF example run %s-------------\r\n\r\n\r\n\r\n\r\n", __TIME__);

    u8 buf[256];
    u32 flash_exif_addr = user_get_flash_exif_addr();
    if (flash_exif_addr == 0) {
        return;
    }

    puts("USER_FLASH_EXIF ERASE_SECTOR...\r\n");
    norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, flash_exif_addr);

    puts("USER_FLASH_EXIF READ\r\n");
    memset(buf, 0, sizeof(buf));
    norflash_read(NULL, buf, sizeof(buf), flash_exif_addr);
    put_buf((u8 *)buf, sizeof(buf));

    puts("\r\n USER_FLASH_EXIF WRITE\r\n");
    for (int i = 0; i < sizeof(buf); i++) {
        buf[i] = i;
    }
    norflash_write(NULL, buf, sizeof(buf), flash_exif_addr);

    puts("USER_FLASH_EXIF READ\r\n");
    memset(buf, 0, sizeof(buf));
    norflash_read(NULL, buf, sizeof(buf), flash_exif_addr);
    put_buf((u8 *)buf, sizeof(buf));

}

static int c_main_flash_user(void)
{
    os_task_create(flash_user_test_task, NULL, 12, 1000, 0, "flash_user_test_task");
    return 0;
}

late_initcall(c_main_flash_user);

#endif // USE_FLASH_USER_TEST_DEMO

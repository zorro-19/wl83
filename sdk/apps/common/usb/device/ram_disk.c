#include "os/os_api.h"
#include "device/device.h"
#include "app_config.h"

/*
使用方法
1、在app_config.h使用USB从机的读卡器功能
2、在版籍board_xxx.c声明:extern const struct device_operations ram_disk_dev_ops;
3、在版籍board_xxx.c添加
在REGISTER_DEVICES(device_table) = {
	//数组中添加
    {"vir_udisk",  &ram_disk_dev_ops, NULL},
*/

#if TCFG_VIR_UDISK_ENABLE

#define RAM_ONLINE_FORMAT	0	//盘符上线格式化
#define RAM_DISK_SIZE	30*1024	//固定30K, RAM_DISK_SIZE大小与WIN_FAT_HEAD数组有关,

static const unsigned char WIN_FAT_HEAD[512] = {
    0xEB, 0x3C, 0x90, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30, 0x00, 0x02, 0x01, 0x06, 0x00,
    0x02, 0x00, 0x02, 0x3C, 0x00, 0xF8, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29, 0x17, 0x90, 0xC6, 0xC4, 0x4E, 0x4F, 0x20, 0x4E, 0x41,
    0x4D, 0x45, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x31, 0x32, 0x20, 0x20, 0x20, 0x33, 0xC9,
    0x8E, 0xD1, 0xBC, 0xF0, 0x7B, 0x8E, 0xD9, 0xB8, 0x00, 0x20, 0x8E, 0xC0, 0xFC, 0xBD, 0x00, 0x7C,
    0x38, 0x4E, 0x24, 0x7D, 0x24, 0x8B, 0xC1, 0x99, 0xE8, 0x3C, 0x01, 0x72, 0x1C, 0x83, 0xEB, 0x3A,
    0x66, 0xA1, 0x1C, 0x7C, 0x26, 0x66, 0x3B, 0x07, 0x26, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA,
    0x02, 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xEB, 0x33, 0xC9, 0x8A, 0x46, 0x10, 0x98, 0xF7,
    0x66, 0x16, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0x03, 0x46, 0x0E, 0x13, 0xD1, 0x8B, 0x76, 0x11,
    0x60, 0x89, 0x46, 0xFC, 0x89, 0x56, 0xFE, 0xB8, 0x20, 0x00, 0xF7, 0xE6, 0x8B, 0x5E, 0x0B, 0x03,
    0xC3, 0x48, 0xF7, 0xF3, 0x01, 0x46, 0xFC, 0x11, 0x4E, 0xFE, 0x61, 0xBF, 0x00, 0x00, 0xE8, 0xE6,
    0x00, 0x72, 0x39, 0x26, 0x38, 0x2D, 0x74, 0x17, 0x60, 0xB1, 0x0B, 0xBE, 0xA1, 0x7D, 0xF3, 0xA6,
    0x61, 0x74, 0x32, 0x4E, 0x74, 0x09, 0x83, 0xC7, 0x20, 0x3B, 0xFB, 0x72, 0xE6, 0xEB, 0xDC, 0xA0,
    0xFB, 0x7D, 0xB4, 0x7D, 0x8B, 0xF0, 0xAC, 0x98, 0x40, 0x74, 0x0C, 0x48, 0x74, 0x13, 0xB4, 0x0E,
    0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEF, 0xA0, 0xFD, 0x7D, 0xEB, 0xE6, 0xA0, 0xFC, 0x7D, 0xEB,
    0xE1, 0xCD, 0x16, 0xCD, 0x19, 0x26, 0x8B, 0x55, 0x1A, 0x52, 0xB0, 0x01, 0xBB, 0x00, 0x00, 0xE8,
    0x3B, 0x00, 0x72, 0xE8, 0x5B, 0x8A, 0x56, 0x24, 0xBE, 0x0B, 0x7C, 0x8B, 0xFC, 0xC7, 0x46, 0xF0,
    0x3D, 0x7D, 0xC7, 0x46, 0xF4, 0x29, 0x7D, 0x8C, 0xD9, 0x89, 0x4E, 0xF2, 0x89, 0x4E, 0xF6, 0xC6,
    0x06, 0x96, 0x7D, 0xCB, 0xEA, 0x03, 0x00, 0x00, 0x20, 0x0F, 0xB6, 0xC8, 0x66, 0x8B, 0x46, 0xF8,
    0x66, 0x03, 0x46, 0x1C, 0x66, 0x8B, 0xD0, 0x66, 0xC1, 0xEA, 0x10, 0xEB, 0x5E, 0x0F, 0xB6, 0xC8,
    0x4A, 0x4A, 0x8A, 0x46, 0x0D, 0x32, 0xE4, 0xF7, 0xE2, 0x03, 0x46, 0xFC, 0x13, 0x56, 0xFE, 0xEB,
    0x4A, 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x91, 0x8B, 0x46, 0x18, 0x96, 0x92, 0x33,
    0xD2, 0xF7, 0xF6, 0x91, 0xF7, 0xF6, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8,
    0xC0, 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42,
    0x8B, 0xF4, 0x8A, 0x56, 0x24, 0xCD, 0x13, 0x61, 0x61, 0x72, 0x0B, 0x40, 0x75, 0x01, 0x42, 0x03,
    0x5E, 0x0B, 0x49, 0x75, 0x06, 0xF8, 0xC3, 0x41, 0xBB, 0x00, 0x00, 0x60, 0x66, 0x6A, 0x00, 0xEB,
    0xB0, 0x42, 0x4F, 0x4F, 0x54, 0x4D, 0x47, 0x52, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x52, 0x65,
    0x6D, 0x6F, 0x76, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x73, 0x20, 0x6F, 0x72, 0x20, 0x6F, 0x74,
    0x68, 0x65, 0x72, 0x20, 0x6D, 0x65, 0x64, 0x69, 0x61, 0x2E, 0xFF, 0x0D, 0x0A, 0x44, 0x69, 0x73,
    0x6B, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20,
    0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x72, 0x65, 0x73, 0x74, 0x61,
    0x72, 0x74, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xCB, 0xD8, 0x55, 0xAA
};
static u32 ram_disk_block_size;
static u32 ram_disk_block_num;
static u32 ram_disk_sector_size;
static u8 ram_disk_buf[RAM_DISK_SIZE] ALIGNE(4);
static struct device norflash_dev;

u8 *ram_disk_buf_get(int *size)
{
    *size = RAM_DISK_SIZE;
    return ram_disk_buf;
}
static int ram_disk_dev_init(const struct dev_node *node, void *arg)
{
    ram_disk_sector_size = 64;
    ram_disk_block_size = 512;
    ram_disk_block_num = RAM_DISK_SIZE / ram_disk_block_size;
    memset(ram_disk_buf, 0x00, sizeof(ram_disk_buf));

#if !RAM_ONLINE_FORMAT
    memcpy(ram_disk_buf, WIN_FAT_HEAD, sizeof(WIN_FAT_HEAD));
    ram_disk_buf[0xC00] = 0xF8;
    ram_disk_buf[0xC00 + 1] = 0xFF;
    ram_disk_buf[0xC00 + 2] = 0xFF;
    ram_disk_buf[0xE00] = 0xF8;
    ram_disk_buf[0xE00 + 1] = 0xFF;
    ram_disk_buf[0xE00 + 2] = 0xFF;
#endif
    return 0;
}
static int ram_disk_dev_open(const char *name, struct device **device, void *arg)
{
    *device = &norflash_dev;
    (*device)->private_data = (void *)NULL;
    return 0;
}
static int ram_disk_dev_close(struct device *device)
{
    return 0;
}
static int ram_disk_dev_read(struct device *device, void *buf, u32 len, u32 offset)
{
    len = len * ram_disk_block_size;
    offset = offset * ram_disk_block_size;

    memcpy(buf, ram_disk_buf + offset, len);
    return len / ram_disk_block_size;
}
static int ram_disk_dev_write(struct device *device, void *buf, u32 len, u32 offset)
{
    u8 *write_buf = (u8 *)buf;
    u32 write_len = len * ram_disk_block_size;
    u32 addr = offset * ram_disk_block_size;

    memcpy(ram_disk_buf + addr, write_buf, write_len);
    return len;
}
static int ram_disk_dev_ioctl(struct device *device, u32 cmd, u32 arg)
{
    switch (cmd) {
    case IOCTL_GET_ID:
        *((int *)arg) = 0;
        break;
    case IOCTL_GET_BLOCK_NUMBER:
        *((int *)arg) = ram_disk_block_num;
        break;
    case IOCTL_GET_SECTOR_SIZE:
        *((int *)arg) = ram_disk_sector_size;
        break;
    case IOCTL_GET_BLOCK_SIZE:
        *((int *)arg) = ram_disk_block_size;
        break;
    case IOCTL_GET_CAPACITY:
        *((int *)arg) = ram_disk_block_num * ram_disk_block_size;
        break;
    case  IOCTL_GET_STATUS:
        *((int *)arg) = 1;//reg ? 1 : 0;
        break;
    case IOCTL_ERASE_SECTOR:
        memset(ram_disk_buf + arg * ram_disk_sector_size, 0xFF, ram_disk_sector_size);
        break;
    case IOCTL_ERASE_BLOCK:
        memset(ram_disk_buf + arg * ram_disk_block_size, 0xFF, ram_disk_block_size);
        break;
    case IOCTL_ERASE_CHIP:
        memset(ram_disk_buf, 0xFF, sizeof(ram_disk_buf));
        break;
    default:
        break;
    }
    return 0;
}
static bool ram_disk_dev_online(const struct dev_node *node)
{
    return true;
}
const struct device_operations ram_disk_dev_ops = {
    .online = ram_disk_dev_online,
    .init  = ram_disk_dev_init,
    .open  = ram_disk_dev_open,
    .read  = ram_disk_dev_read,
    .write = ram_disk_dev_write,
    .ioctl = ram_disk_dev_ioctl,
    .close = ram_disk_dev_close,
};

#endif


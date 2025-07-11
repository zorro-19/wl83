#include "os/os_api.h"
#include "spinlock.h"
#include "device/device.h"
#include "app_config.h"
#include "usb/usb_phy.h"
#include "server/audio_server.h"
#include "server/server_core.h"

/*
使用方法
1、在app_config.h使用USB从机的MASSSTORAGE_CLASS功能
2、在版籍board_xxx.c声明:extern const struct device_operations ram_disk_dev_ops;
3、在版籍board_xxx.c添加
在REGISTER_DEVICES(device_table) = {
	//数组中添加
    {"vir_udisk",  &ram_disk_dev_ops, NULL},
*/

#if TCFG_VIR_UDISK_ENABLE

#define LOG_TAG_CONST       USB
#define LOG_TAG             "[RAM_DISK]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

//模拟2GByte U盘的配置
#define BLOCK_SIZE 512u
#define CLUSTER_SIZE 0x4000u
#define BLOCK_NUM (2 * 1024 * 1024 * 1024u / BLOCK_SIZE)

#define RESERVED_SECTOR_SIZE 0x1806u
#define TOTAL_SECTOR_SIZE 0x3fe800u
#define FAT_TABLE_SECTOR_SIZE 0x3fdu
#define BSP_VOL_ID 0x4cfc8d04u

#define FILE_START_CLUSTER 6
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
#define FILE_SIZE 0x25800000ull
/* #define FILE_SIZE 0x12c00000u */
#define FILE_NUM 3
#else
#define FILE_SIZE 0
#define FILE_NUM 0
#endif

#define DATE_TIME_YEAR 		2022u
#define DATE_TIME_MONTH		2u
#define DATE_TIME_DAY		14u
#define DATE_TIME_HOUR		13u
#define DATE_TIME_MINUTE	14u
#define DATE_TIME_SEC		0u
#define DATE_TIME			(((((DATE_TIME_YEAR - 1980) << 9) | (DATE_TIME_MONTH << 5) | DATE_TIME_DAY) << 16) | (DATE_TIME_HOUR << 11) | (DATE_TIME_MINUTE << 5) | (DATE_TIME_SEC / 2))

#define TOTAL_FILE_SIZE (FILE_SIZE * FILE_NUM + FILE_START_CLUSTER * CLUSTER_SIZE)
#define FAT_TABLE1_OFFSET (RESERVED_SECTOR_SIZE * BLOCK_SIZE)
#define FAT_TABLE2_OFFSET ((RESERVED_SECTOR_SIZE + FAT_TABLE_SECTOR_SIZE) * BLOCK_SIZE)
#define ROOT_TABLE_OFFSET ((RESERVED_SECTOR_SIZE + FAT_TABLE_SECTOR_SIZE * 2) * BLOCK_SIZE)
#define FILE_START_OFFSET ((RESERVED_SECTOR_SIZE + FAT_TABLE_SECTOR_SIZE * 2) * BLOCK_SIZE + CLUSTER_SIZE * 4)

static u8 ram_disk_online;

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
static struct {
    const char *file_name;	//暂时只支持短文件名8+3规则
    u32 file_size;			//需要对齐到簇大小
} file_inf[FILE_NUM] = {
    {"MUSIC1.WAV", FILE_SIZE},
    {"MUSIC2.MP3", FILE_SIZE},
    {"MUSIC3.WAV", FILE_SIZE},
};
#endif

static const unsigned char WIN_FAT32_HEAD[] = {
    0xEB, 0x58, 0x90, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30, 0x00, 0x02, 0x20, LOBYTE(RESERVED_SECTOR_SIZE), HIBYTE(RESERVED_SECTOR_SIZE), //offset:14-15 保留扇区数目
    0x02, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x3F, 0x00, 0xFF, 0x00, 0x80, 0x00, 0x00, 0x00, //offset:28-31 FAT区前隐藏扇区数
    DW1BYTE(TOTAL_SECTOR_SIZE), DW2BYTE(TOTAL_SECTOR_SIZE), DW3BYTE(TOTAL_SECTOR_SIZE), DW4BYTE(TOTAL_SECTOR_SIZE), DW1BYTE(FAT_TABLE_SECTOR_SIZE), DW2BYTE(FAT_TABLE_SECTOR_SIZE), DW3BYTE(FAT_TABLE_SECTOR_SIZE), DW4BYTE(FAT_TABLE_SECTOR_SIZE), 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, //offset:32-35 该卷总扇区数   offset:36-39 一个FAT表扇区数
    0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x29, DW1BYTE(BSP_VOL_ID), DW2BYTE(BSP_VOL_ID), DW3BYTE(BSP_VOL_ID), DW4BYTE(BSP_VOL_ID), 0x4E, 0x4F, 0x20, 0x4E, 0x41, 0x4D, 0x45, 0x20, 0x20, //offset:67-70 BS volID
    0x20, 0x20, 0x46, 0x41, 0x54, 0x33, 0x32, 0x20, 0x20, 0x20, 0x33, 0xC9, 0x8E, 0xD1, 0xBC, 0xF4,
    0x7B, 0x8E, 0xC1, 0x8E, 0xD9, 0xBD, 0x00, 0x7C, 0x88, 0x56, 0x40, 0x88, 0x4E, 0x02, 0x8A, 0x56,
    0x40, 0xB4, 0x41, 0xBB, 0xAA, 0x55, 0xCD, 0x13, 0x72, 0x10, 0x81, 0xFB, 0x55, 0xAA, 0x75, 0x0A,
    0xF6, 0xC1, 0x01, 0x74, 0x05, 0xFE, 0x46, 0x02, 0xEB, 0x2D, 0x8A, 0x56, 0x40, 0xB4, 0x08, 0xCD,
    0x13, 0x73, 0x05, 0xB9, 0xFF, 0xFF, 0x8A, 0xF1, 0x66, 0x0F, 0xB6, 0xC6, 0x40, 0x66, 0x0F, 0xB6,
    0xD1, 0x80, 0xE2, 0x3F, 0xF7, 0xE2, 0x86, 0xCD, 0xC0, 0xED, 0x06, 0x41, 0x66, 0x0F, 0xB7, 0xC9,
    0x66, 0xF7, 0xE1, 0x66, 0x89, 0x46, 0xF8, 0x83, 0x7E, 0x16, 0x00, 0x75, 0x39, 0x83, 0x7E, 0x2A,
    0x00, 0x77, 0x33, 0x66, 0x8B, 0x46, 0x1C, 0x66, 0x83, 0xC0, 0x0C, 0xBB, 0x00, 0x80, 0xB9, 0x01,
    0x00, 0xE8, 0x2C, 0x00, 0xE9, 0xA8, 0x03, 0xA1, 0xF8, 0x7D, 0x80, 0xC4, 0x7C, 0x8B, 0xF0, 0xAC,
    0x84, 0xC0, 0x74, 0x17, 0x3C, 0xFF, 0x74, 0x09, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB,
    0xEE, 0xA1, 0xFA, 0x7D, 0xEB, 0xE4, 0xA1, 0x7D, 0x80, 0xEB, 0xDF, 0x98, 0xCD, 0x16, 0xCD, 0x19,
    0x66, 0x60, 0x80, 0x7E, 0x02, 0x00, 0x0F, 0x84, 0x20, 0x00, 0x66, 0x6A, 0x00, 0x66, 0x50, 0x06,
    0x53, 0x66, 0x68, 0x10, 0x00, 0x01, 0x00, 0xB4, 0x42, 0x8A, 0x56, 0x40, 0x8B, 0xF4, 0xCD, 0x13,
    0x66, 0x58, 0x66, 0x58, 0x66, 0x58, 0x66, 0x58, 0xEB, 0x33, 0x66, 0x3B, 0x46, 0xF8, 0x72, 0x03,
    0xF9, 0xEB, 0x2A, 0x66, 0x33, 0xD2, 0x66, 0x0F, 0xB7, 0x4E, 0x18, 0x66, 0xF7, 0xF1, 0xFE, 0xC2,
    0x8A, 0xCA, 0x66, 0x8B, 0xD0, 0x66, 0xC1, 0xEA, 0x10, 0xF7, 0x76, 0x1A, 0x86, 0xD6, 0x8A, 0x56,
    0x40, 0x8A, 0xE8, 0xC0, 0xE4, 0x06, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0xCD, 0x13, 0x66, 0x61, 0x0F,
    0x82, 0x74, 0xFF, 0x81, 0xC3, 0x00, 0x02, 0x66, 0x40, 0x49, 0x75, 0x94, 0xC3, 0x42, 0x4F, 0x4F,
    0x54, 0x4D, 0x47, 0x52, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0A, 0x44, 0x69,
    0x73, 0x6B, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x50, 0x72, 0x65, 0x73, 0x73,
    0x20, 0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x72, 0x65, 0x73, 0x74,
    0x61, 0x72, 0x74, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0x01, 0xB9, 0x01, 0x00, 0x00, 0x55, 0xAA,
};

static const unsigned char WIN_FAT32_HEAD1[] = {
    0x00, 0x00, 0x00, 0x00, 0x72, 0x72, 0x41, 0x61, 0x3A, 0x1D, 0x01, 0x00, 0x08, 0xE1, 0x00, 0x00, //offset:9-15 上一个读写簇号缓存
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA,
};

static const unsigned char WIN_FAT32_HEAD2[] = {
    0x00, 0x00, 0x00, 0x00, 0x72, 0x72, 0x41, 0x61, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA,
};

static const unsigned char WIN_FAT32_HEAD3[] = {
    0x0D, 0x0A, 0x41, 0x6E, 0x20, 0x6F, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x73,
    0x79, 0x73, 0x74, 0x65, 0x6D, 0x20, 0x77, 0x61, 0x73, 0x6E, 0x27, 0x74, 0x20, 0x66, 0x6F, 0x75,
    0x6E, 0x64, 0x2E, 0x20, 0x54, 0x72, 0x79, 0x20, 0x64, 0x69, 0x73, 0x63, 0x6F, 0x6E, 0x6E, 0x65,
    0x63, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x61, 0x6E, 0x79, 0x20, 0x64, 0x72, 0x69, 0x76, 0x65, 0x73,
    0x20, 0x74, 0x68, 0x61, 0x74, 0x20, 0x64, 0x6F, 0x6E, 0x27, 0x74, 0x0D, 0x0A, 0x63, 0x6F, 0x6E,
    0x74, 0x61, 0x69, 0x6E, 0x20, 0x61, 0x6E, 0x20, 0x6F, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6E,
    0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x2E, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x66,
    0x0F, 0xB6, 0x46, 0x10, 0x66, 0x8B, 0x4E, 0x24, 0x66, 0xF7, 0xE1, 0x66, 0x03, 0x46, 0x1C, 0x66,
    0x0F, 0xB7, 0x56, 0x0E, 0x66, 0x03, 0xC2, 0x66, 0x89, 0x46, 0xFC, 0x66, 0xC7, 0x46, 0xF4, 0xFF,
    0xFF, 0xFF, 0xFF, 0x66, 0x8B, 0x46, 0x2C, 0x66, 0x83, 0xF8, 0x02, 0x0F, 0x82, 0x47, 0xFC, 0x66,
    0x3D, 0xF8, 0xFF, 0xFF, 0x0F, 0x0F, 0x83, 0x3D, 0xFC, 0x66, 0x50, 0x66, 0x83, 0xE8, 0x02, 0x66,
    0x0F, 0xB6, 0x5E, 0x0D, 0x8B, 0xF3, 0x66, 0xF7, 0xE3, 0x66, 0x03, 0x46, 0xFC, 0xBB, 0x00, 0x82,
    0x8B, 0xFB, 0xB9, 0x01, 0x00, 0xE8, 0x28, 0xFC, 0x38, 0x2D, 0x74, 0x1E, 0xB1, 0x0B, 0x56, 0xBE,
    0x6D, 0x7D, 0xF3, 0xA6, 0x5E, 0x74, 0x1B, 0x03, 0xF9, 0x83, 0xC7, 0x15, 0x3B, 0xFB, 0x72, 0xE8,
    0x4E, 0x75, 0xDA, 0x66, 0x58, 0xE8, 0x65, 0x00, 0x72, 0xBF, 0x83, 0xC4, 0x04, 0xE9, 0xF6, 0xFB,
    0x00, 0x20, 0x83, 0xC4, 0x04, 0x8B, 0x75, 0x09, 0x8B, 0x7D, 0x0F, 0x8B, 0xC6, 0x66, 0xC1, 0xE0,
    0x10, 0x8B, 0xC7, 0x66, 0x83, 0xF8, 0x02, 0x0F, 0x82, 0xDB, 0xFB, 0x66, 0x3D, 0xF8, 0xFF, 0xFF,
    0x0F, 0x0F, 0x83, 0xD1, 0xFB, 0x66, 0x50, 0x66, 0x83, 0xE8, 0x02, 0x66, 0x0F, 0xB6, 0x4E, 0x0D,
    0x66, 0xF7, 0xE1, 0x66, 0x03, 0x46, 0xFC, 0xBB, 0x00, 0x00, 0x06, 0x8E, 0x06, 0x00, 0x81, 0xE8,
    0xBE, 0xFB, 0x07, 0x66, 0x58, 0xC1, 0xEB, 0x04, 0x01, 0x1E, 0x00, 0x81, 0xE8, 0x0E, 0x00, 0x0F,
    0x83, 0x02, 0x00, 0x72, 0xD0, 0x8A, 0x56, 0x40, 0xEA, 0x00, 0x00, 0x00, 0x20, 0x66, 0xC1, 0xE0,
    0x02, 0xE8, 0x11, 0x00, 0x26, 0x66, 0x8B, 0x01, 0x66, 0x25, 0xFF, 0xFF, 0xFF, 0x0F, 0x66, 0x3D,
    0xF8, 0xFF, 0xFF, 0x0F, 0xC3, 0xBF, 0x00, 0x7E, 0x66, 0x0F, 0xB7, 0x4E, 0x0B, 0x66, 0x33, 0xD2,
    0x66, 0xF7, 0xF1, 0x66, 0x3B, 0x46, 0xF4, 0x74, 0x3A, 0x66, 0x89, 0x46, 0xF4, 0x66, 0x03, 0x46,
    0x1C, 0x66, 0x0F, 0xB7, 0x4E, 0x0E, 0x66, 0x03, 0xC1, 0x66, 0x0F, 0xB7, 0x5E, 0x28, 0x83, 0xE3,
    0x0F, 0x74, 0x16, 0x3A, 0x5E, 0x10, 0x0F, 0x83, 0x4C, 0xFB, 0x52, 0x66, 0x8B, 0xC8, 0x66, 0x8B,
    0x46, 0x24, 0x66, 0xF7, 0xE3, 0x66, 0x03, 0xC1, 0x5A, 0x52, 0x8B, 0xDF, 0xB9, 0x01, 0x00, 0xE8,
    0x3E, 0xFB, 0x5A, 0x8B, 0xDA, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA,
};

static const unsigned char WIN_FAT32_FAT_TABLE_HEAD[] = {
    0xF8, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F,
    0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F,
};

static const unsigned char WIN_FAT32_ROOT_TABLE_HEAD[] = {
    0x4A, 0x4c, 0x2D, 0x55, 0x44, 0x49, 0x53, 0x4B, 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, //u盘名称
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x42, 0x20, 0x00, 0x49, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x6F, 0x00, 0x0F, 0x00, 0x72, 0x72, 0x00,
    0x6D, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00,
    0x01, 0x53, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74, 0x00, 0x65, 0x00, 0x0F, 0x00, 0x72, 0x6D, 0x00,
    0x20, 0x00, 0x56, 0x00, 0x6F, 0x00, 0x6C, 0x00, 0x75, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x65, 0x00,
    0x53, 0x59, 0x53, 0x54, 0x45, 0x4D, 0x7E, 0x31, 0x20, 0x20, 0x20, 0x16, 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME),
    DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const unsigned char WIN_FAT32_SYSTEM_VOLUME_INF_HEAD[] = {
    0x2E, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME),
    DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2E, 0x2E, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME),
    DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x42, 0x74, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0xCE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x01, 0x57, 0x00, 0x50, 0x00, 0x53, 0x00, 0x65, 0x00, 0x74, 0x00, 0x0F, 0x00, 0xCE, 0x74, 0x00,
    0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x73, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x64, 0x00, 0x61, 0x00,
    0x57, 0x50, 0x53, 0x45, 0x54, 0x54, 0x7E, 0x31, 0x44, 0x41, 0x54, 0x20, 0x00, 0x01, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME),
    DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x04, 0x00, 0x0C, 0x00, 0x00, 0x00,
    0x42, 0x47, 0x00, 0x75, 0x00, 0x69, 0x00, 0x64, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x01, 0x49, 0x00, 0x6E, 0x00, 0x64, 0x00, 0x65, 0x00, 0x78, 0x00, 0x0F, 0x00, 0xFF, 0x65, 0x00,
    0x72, 0x00, 0x56, 0x00, 0x6F, 0x00, 0x6C, 0x00, 0x75, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x65, 0x00,
    0x49, 0x4E, 0x44, 0x45, 0x58, 0x45, 0x7E, 0x31, 0x20, 0x20, 0x20, 0x20, 0x00, 0x02, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME),
    DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x00, 0x00, DW1BYTE(DATE_TIME), DW2BYTE(DATE_TIME), DW3BYTE(DATE_TIME), DW4BYTE(DATE_TIME), 0x05, 0x00, 0x4C, 0x00, 0x00, 0x00,
};

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
static const unsigned char WAV_INF_HEAD[44] = {
    0x52, 0x49, 0x46, 0x46, DW1BYTE(FILE_SIZE - 8), DW2BYTE(FILE_SIZE - 8), DW3BYTE(FILE_SIZE - 8), DW4BYTE(FILE_SIZE - 8), 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, DW1BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE), DW2BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE), DW3BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE), DW4BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE), DW1BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE * 4), DW2BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE * 4), DW3BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE * 4), DW4BYTE(TCFG_USER_VIRTUAL_PLAY_SAMPLERATE * 4),
    0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, DW1BYTE(FILE_SIZE - 44), DW2BYTE(FILE_SIZE - 44), DW3BYTE(FILE_SIZE - 44), DW4BYTE(FILE_SIZE - 44),
};

struct user_virtual_vfs_handle {
    volatile u8 open;
    volatile u8 reading;
    volatile u8 wait_stop;
    spinlock_t lock;
    OS_SEM sem;
    OS_SEM rd_sem;
    void *audio_enc;
    struct audio_cbuf_t *virtual;
    cbuffer_t cbuf;
    void *buf;
};

static struct user_virtual_vfs_handle user_virtual_vfs_handle;
#define ufs      (&user_virtual_vfs_handle)

#define USER_VIRTUAL_AUDIO_CBUF_SIZE	(1024 * 4)

static int user_virtual_vfs_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;

    while (ufs->open) {
        if (cbuf_write(cbuf, data, len) == len) {
            os_sem_set(&ufs->rd_sem, 0);
            os_sem_post(&ufs->rd_sem);
            break;
        }
        os_sem_pend(&ufs->sem, 0);
    }

    return len;
}

static int user_virtual_vfs_fclose(void *file)
{
    return 0;
}

static const struct audio_vfs_ops user_virtual_vfs_ops = {
    .fwrite = user_virtual_vfs_fwrite,
    .fclose = user_virtual_vfs_fclose,
};

static int mp3_read_input(u8 *buf, u32 len)
{
    u32 rlen = 0;

    do {
        spin_lock(&ufs->lock);
        if (!ufs->open || !ufs->virtual || ufs->wait_stop) {
            ufs->reading = 0;
            spin_unlock(&ufs->lock);
            memset(buf, 0, len);
            return len;
        }
        ufs->reading = 1;
        spin_unlock(&ufs->lock);

        rlen = cbuf_read(ufs->virtual->cbuf, buf, len);
        if (rlen == len) {
            break;
        }
        if (ufs->virtual->end) {
            ufs->virtual->end = 2;
            os_sem_post(ufs->virtual->wr_sem);
            ufs->reading = 0;
            return 0;
        }
        if (!ufs->virtual->state || 0 != os_sem_pend(ufs->virtual->rd_sem, 5)) {
            rlen = len;
            break;
        }
    } while (!rlen);

    os_sem_post(ufs->virtual->wr_sem);
    ufs->reading = 0;

    return rlen;
}

void set_user_virtual_play_hdl(void *virtual)
{
    spin_lock(&ufs->lock);
    ufs->wait_stop = virtual ? 0 : 1;
    while (ufs->reading) {
        spin_unlock(&ufs->lock);
        if (!virtual && ufs->virtual && ufs->virtual->rd_sem) {
            os_sem_post(ufs->virtual->rd_sem);
        }
        os_time_dly(1);
        spin_lock(&ufs->lock);
    }
    ufs->virtual = virtual;
    spin_unlock(&ufs->lock);
}

int user_virtual_play_read_data(void *buf, u32 len)
{
    u32 rlen = 0;
    u32 data_size;

    if (ufs->audio_enc) {
        while (rlen < len) {
            data_size = cbuf_get_data_size(&ufs->cbuf);
            if (data_size > 0) {
                rlen += cbuf_read(&ufs->cbuf, (u8 *)buf + rlen, data_size > len - rlen ? len - rlen : data_size);
                os_sem_set(&ufs->sem, 0);
                os_sem_post(&ufs->sem);
            }
            if (rlen < len) {
                os_sem_pend(&ufs->rd_sem, 0);
            }
        }
    } else {
        do {
            spin_lock(&ufs->lock);
            if (!ufs->virtual || ufs->wait_stop) {
                ufs->reading = 0;
                spin_unlock(&ufs->lock);
                memset(buf, 0, len);
                return 0;
            }
            ufs->reading = 1;
            spin_unlock(&ufs->lock);

            rlen = cbuf_read(ufs->virtual->cbuf, buf, len);
            if (rlen == len) {
                break;
            }
            if (ufs->virtual->end) {
                ufs->virtual->end = 2;
                break;
            }
            if (!ufs->virtual->state || 0 != os_sem_pend(ufs->virtual->rd_sem, 5)) {
                break;
            }
        } while (!rlen);

        os_sem_post(ufs->virtual->wr_sem);
        ufs->reading = 0;
    }

    return rlen;
}

int check_user_virtual_audio_if_running(void)
{
    return ram_disk_online;
}

void *get_user_virtual_audio_server(void)
{
    return ufs->audio_enc;
}

int virtual_mp3_encoder_init(void)
{
    union audio_req req = {0};

    log_info("audio udisk virtual audio server open");

    os_sem_create(&ufs->sem, 0);
    os_sem_create(&ufs->rd_sem, 0);

    ufs->buf = malloc(USER_VIRTUAL_AUDIO_CBUF_SIZE);
    if (!ufs->buf) {
        return -1;
    }

    ufs->audio_enc = server_open("audio_server", "enc");
    if (!ufs->audio_enc) {
        free(ufs->buf);
        ufs->buf = NULL;
        return -1;
    }

    cbuf_init(&ufs->cbuf, ufs->buf, USER_VIRTUAL_AUDIO_CBUF_SIZE);

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 2;
    req.enc.frame_size = 512;
    req.enc.output_buf_len = 2 * req.enc.frame_size;
    req.enc.format = "mp3";
    req.enc.sample_source = "virtual";
    req.enc.read_input = mp3_read_input;
    req.enc.vfs_ops = &user_virtual_vfs_ops;
    req.enc.file = (FILE *)&ufs->cbuf;
    req.enc.vir_data_wait = 1;
    req.enc.delay_ms = 50;
    /* req.enc.no_auto_start = 1; */
    req.enc.bitrate = 128000;//64000;
    req.enc.sample_rate = TCFG_USER_VIRTUAL_PLAY_SAMPLERATE;

    ufs->open = 1;

    return server_request(ufs->audio_enc, AUDIO_REQ_ENC, &req);
}

int virtual_mp3_encoder_close(void)
{
    union audio_req req = {0};

    log_info("audio udisk virtual audio server close");

    ufs->open = 0;
    os_sem_set(&ufs->sem, 0);
    os_sem_post(&ufs->sem);

    if (ufs->audio_enc) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(ufs->audio_enc, AUDIO_REQ_ENC, &req);
        server_close(ufs->audio_enc);
        ufs->audio_enc = NULL;
    }
    if (ufs->buf) {
        cbuf_clear(&ufs->cbuf);
        free(ufs->buf);
        ufs->buf = NULL;
    }

    return 0;
}

void virtual_mp3_encoder_reset_cbuf(void)
{
    if (ufs->buf) {
        cbuf_clear(&ufs->cbuf);
        os_sem_post(&ufs->sem);
    }
}

#endif

/* static u8 ram_disk_buf[RAM_DISK_SIZE] ALIGNE(4); */
static struct device ram_disk_dev;

static int ram_disk_dev_init(const struct dev_node *node, void *arg)
{
    return 0;
}

static int ram_disk_dev_open(const char *name, struct device **device, void *arg)
{
    *device = &ram_disk_dev;
    (*device)->private_data = NULL;
    ram_disk_online = 1;
    return 0;
}

static int ram_disk_dev_close(struct device *device)
{
    ram_disk_online = 0;
    return 0;
}

static int ram_disk_dev_read(struct device *device, void *buf, u32 len, u32 offset)
{
    u32 wlen = 0;
    u8 *data = (u8 *)buf;
    len *= BLOCK_SIZE;
    offset *= BLOCK_SIZE;

    while (len > wlen) {
        if (offset < FAT_TABLE1_OFFSET) {
            //引导扇区
            if (offset == 0 || offset == 0xc00) {
                memcpy(data + wlen, WIN_FAT32_HEAD, sizeof(WIN_FAT32_HEAD));
            } else if (offset == 0x200) {
                memset(data + wlen, 0x00, BLOCK_SIZE);
                memcpy(data + wlen, "RRaA", 4);
                memcpy(data + wlen + 0x1e0, WIN_FAT32_HEAD1, sizeof(WIN_FAT32_HEAD1));
            } else if (offset == 0xc00 + 0x200) {
                memset(data + wlen, 0x00, BLOCK_SIZE);
                memcpy(data + wlen, "RRaA", 4);
                memcpy(data + wlen + 0x1e0, WIN_FAT32_HEAD2, sizeof(WIN_FAT32_HEAD2));
            } else if (offset == 0x200 * 2 || offset == 0xc00 + 0x200 * 2) {
                memset(data + wlen, 0x00, BLOCK_SIZE);
                data[wlen + 0x200 - 2] = 0x55;
                data[wlen + 0x200 - 1] = 0xAA;
            } else if (offset == 0x1800) {
                memcpy(data + wlen, WIN_FAT32_HEAD3, 0x200);
            } else {
                memset(data + wlen, 0, BLOCK_SIZE);
            }
        } else if (offset >= FAT_TABLE1_OFFSET && offset < FAT_TABLE2_OFFSET) {
            //FAT表1
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
            if (offset + BLOCK_SIZE < FAT_TABLE1_OFFSET + (TOTAL_FILE_SIZE * 4 / CLUSTER_SIZE)) {
                for (int i = 0; i < BLOCK_SIZE / 4; ++i) {
                    *((int *)(data + wlen) + i) = (offset - FAT_TABLE1_OFFSET) / 4 + i + 1;
                }
                if (offset == FAT_TABLE1_OFFSET) {
                    memcpy(data + wlen, WIN_FAT32_FAT_TABLE_HEAD, sizeof(WIN_FAT32_FAT_TABLE_HEAD));
                }
            } else if (offset < FAT_TABLE1_OFFSET + (TOTAL_FILE_SIZE * 4 / CLUSTER_SIZE)) {
                memset(data + wlen, 0, BLOCK_SIZE);
                for (int i = 0; i < (FAT_TABLE1_OFFSET + (TOTAL_FILE_SIZE * 4 / CLUSTER_SIZE) - offset) / 4; ++i) {
                    *((int *)(data + wlen) + i) = (offset - FAT_TABLE1_OFFSET) / 4 + i + 1;
                }
            } else {
                memset(data + wlen, 0, BLOCK_SIZE);
            }
            for (u32 j = 0, start_clust = FILE_START_CLUSTER; j < ARRAY_SIZE(file_inf); ++j) {
                int end_offset = FAT_TABLE1_OFFSET + (start_clust + file_inf[j].file_size / CLUSTER_SIZE) * 4;
                if (end_offset - (int)offset >= 0 && end_offset - (int)offset < BLOCK_SIZE) {
                    *((int *)(data + wlen) + (end_offset - offset) / 4 - 1) = 0xfffffff;
                }
                start_clust += file_inf[j].file_size / CLUSTER_SIZE;
            }
#else
            if (offset == FAT_TABLE1_OFFSET) {
                memcpy(data + wlen, WIN_FAT32_FAT_TABLE_HEAD, sizeof(WIN_FAT32_FAT_TABLE_HEAD));
            } else {
                memset(data + wlen, 0, BLOCK_SIZE);
            }
#endif
        } else if (offset >= FAT_TABLE2_OFFSET && offset < ROOT_TABLE_OFFSET) {
            //FAT表2
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
            if (offset + BLOCK_SIZE < FAT_TABLE2_OFFSET + (TOTAL_FILE_SIZE * 4 / CLUSTER_SIZE)) {
                for (int i = 0; i < BLOCK_SIZE / 4; ++i) {
                    *((int *)(data + wlen) + i) = (offset - FAT_TABLE2_OFFSET) / 4 + i + 1;
                }
                if (offset == FAT_TABLE2_OFFSET) {
                    memcpy(data + wlen, WIN_FAT32_FAT_TABLE_HEAD, sizeof(WIN_FAT32_FAT_TABLE_HEAD));
                }
            } else if (offset < FAT_TABLE2_OFFSET + (TOTAL_FILE_SIZE * 4 / CLUSTER_SIZE)) {
                memset(data + wlen, 0, BLOCK_SIZE);
                for (int i = 0; i < (FAT_TABLE2_OFFSET + (TOTAL_FILE_SIZE * 4 / CLUSTER_SIZE) - offset) / 4; ++i) {
                    *((int *)(data + wlen) + i) = (offset - FAT_TABLE2_OFFSET) / 4 + i + 1;
                }
            } else {
                memset(data + wlen, 0, BLOCK_SIZE);
            }
            for (u32 j = 0, start_clust = FILE_START_CLUSTER; j < ARRAY_SIZE(file_inf); ++j) {
                int end_offset = FAT_TABLE2_OFFSET + (start_clust + file_inf[j].file_size / CLUSTER_SIZE) * 4;
                if (end_offset - (int)offset >= 0 && end_offset - (int)offset < BLOCK_SIZE) {
                    *((int *)(data + wlen) + (end_offset - offset) / 4 - 1) = 0xfffffff;
                }
                start_clust += file_inf[j].file_size / CLUSTER_SIZE;
            }
#else
            if (offset == FAT_TABLE2_OFFSET) {
                memcpy(data + wlen, WIN_FAT32_FAT_TABLE_HEAD, sizeof(WIN_FAT32_FAT_TABLE_HEAD));
            } else {
                memset(data + wlen, 0, BLOCK_SIZE);
            }
#endif
        } else if (offset == ROOT_TABLE_OFFSET) {
            //根目录
            memset(data + wlen, 0, BLOCK_SIZE);
            memcpy(data + wlen, WIN_FAT32_ROOT_TABLE_HEAD, sizeof(WIN_FAT32_ROOT_TABLE_HEAD));

#if TCFG_USER_VIRTUAL_PLAY_ENABLE
            for (int i = 0, start_clust = FILE_START_CLUSTER; i < ARRAY_SIZE(file_inf); ++i) {
                const char *p = strchr(file_inf[i].file_name, '.');
                if (p) {
                    memcpy(data + wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20, file_inf[i].file_name, p - file_inf[i].file_name);
                    if (p - file_inf[i].file_name < 8) {
                        memset(data + wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + (p - file_inf[i].file_name), 0x20, 8 - (p - file_inf[i].file_name));
                    }
                    memcpy(data + wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 8, p + 1, strlen(p + 1));
                }
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 11] = 0x20;
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 12] = 0x18;
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 13] = i;
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 14] = DW1BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 15] = DW2BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 16] = DW3BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 17] = DW4BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 18] = DW3BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 19] = DW4BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 20] = DW3BYTE(start_clust);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 21] = DW4BYTE(start_clust);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 22] = DW1BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 23] = DW2BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 24] = DW3BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 25] = DW4BYTE(DATE_TIME);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 26] = DW1BYTE(start_clust);
                data[wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 27] = DW2BYTE(start_clust);
                memcpy(data + wlen + sizeof(WIN_FAT32_ROOT_TABLE_HEAD) + i * 0x20 + 28, &file_inf[i].file_size, sizeof(file_inf[i].file_size));
                start_clust += file_inf[i].file_size / CLUSTER_SIZE;
            }
#endif
        } else if (offset == ROOT_TABLE_OFFSET + CLUSTER_SIZE) {
            //system volume information
            memset(data + wlen, 0, BLOCK_SIZE);
            memcpy(data + wlen, WIN_FAT32_SYSTEM_VOLUME_INF_HEAD, sizeof(WIN_FAT32_SYSTEM_VOLUME_INF_HEAD));
        } else if (offset == ROOT_TABLE_OFFSET + CLUSTER_SIZE * 2) {
            //WPSettings.dat
            memset(data + wlen, 0, BLOCK_SIZE);
        } else if (offset == ROOT_TABLE_OFFSET + CLUSTER_SIZE * 3) {
            //IndexerVolumeGuid
            memset(data + wlen, 0, BLOCK_SIZE);
#if TCFG_USER_VIRTUAL_PLAY_ENABLE
        } else if (offset >= FILE_START_OFFSET && offset < FILE_START_OFFSET + FILE_SIZE * FILE_NUM) {
            u8 has_read = 0;

            for (int i = 0, start_file_offset = FILE_START_OFFSET; i < ARRAY_SIZE(file_inf); ++i) {
                //用户数据在此读取
                if (offset == start_file_offset) {
                    if (ufs->audio_enc) {
                        virtual_mp3_encoder_close();
                    }
                    if (strstr(file_inf[i].file_name, ".WAV")) {
                        memcpy(data + wlen, WAV_INF_HEAD, sizeof(WAV_INF_HEAD));
                        user_virtual_play_read_data(data + wlen + sizeof(WAV_INF_HEAD), BLOCK_SIZE - sizeof(WAV_INF_HEAD));
                        has_read = 1;
                        break;
                    } else if (strstr(file_inf[i].file_name, ".MP3")) {
                        virtual_mp3_encoder_init();
                    }
                }

                start_file_offset += file_inf[i].file_size;
            }

            if (!has_read) {
                user_virtual_play_read_data(data + wlen, BLOCK_SIZE);
            }
#endif
        } else {
            memset(data + wlen, 0, BLOCK_SIZE);
        }

        wlen += BLOCK_SIZE;
        offset += BLOCK_SIZE;
        len -= BLOCK_SIZE;
    }

    return wlen / BLOCK_SIZE;
}

static int ram_disk_dev_write(struct device *device, void *buf, u32 len, u32 offset)
{

#if TCFG_VIR_UPDATE_ENABLE
    int ram_disk_update(const u8 * buf, const u32 len, const u32 offset);
    ram_disk_update(buf, len, offset);
#endif

    return len;
}

static int ram_disk_dev_ioctl(struct device *device, u32 cmd, u32 arg)
{
    switch (cmd) {
    case IOCTL_GET_ID:
        *((int *)arg) = 0;
        break;
    case IOCTL_GET_BLOCK_NUMBER:
        *((int *)arg) = BLOCK_NUM;
        break;
    case IOCTL_GET_SECTOR_SIZE:
        *((int *)arg) = TOTAL_SECTOR_SIZE;
        break;
    case IOCTL_GET_BLOCK_SIZE:
        *((int *)arg) = BLOCK_SIZE;
        break;
    case IOCTL_GET_CAPACITY:
        *((int *)arg) = BLOCK_NUM * BLOCK_SIZE;
        break;
    case  IOCTL_GET_STATUS:
        *((int *)arg) = 1;
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


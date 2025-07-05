#include "dev_reg.h"
#include "app_config.h"

//*----------------------------------------------------------------------------*/
/**@brief    设备配置表
   @param	 具体配置项请看struct __dev_reg结构体描述
   @return
   @note	 注意：
   			 例如logo逻辑盘符sd0_rec/sd1_rec/udisk_rec是做录音文件夹区分使用的,
			 在定义新的设备逻辑盘发的时候， 注意避开"_rec"后缀作为设备逻辑盘符
*/
/*----------------------------------------------------------------------------*/
#ifdef CONFIG_JLFAT_ENABLE
#define FAT_FILE_SYSTEM_NAME "jlfat"
#else
#define FAT_FILE_SYSTEM_NAME "fat"
#endif

static const struct __dev_reg dev_reg[] = {
#if 1//TCFG_CODE_FLASH_ENABLE
    //内置flash
    {
        /*logo*/			"sdfile",
        /*name*/			NULL,
        /*storage_path*/	SDFILE_MOUNT_PATH,
        /*root_path*/		SDFILE_RES_ROOT_PATH,
        /*fs_type*/			"sdfile",
    },
#endif
#if TCFG_FLASH_INSIDE_REC_ENABLE
    //内置录音
    {
        /*logo*/			"rec_sdfile",
        /*name*/			NULL,
        /*storage_path*/	"mnt/rec_sdfile",
        /*root_path*/		"mnt/rec_sdfile/C/",
        /*fs_type*/			"rec_sdfile",
    },
#endif
#if (TCFG_SD0_ENABLE)
    //sd0
    {
        /*logo*/			"sd0",
        /*name*/			"sd0",
        /*storage_path*/	"storage/sd0",
        /*root_path*/		"storage/sd0/C/",
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_SD1_ENABLE)
    //sd1
    {
        /*logo*/			"sd1",
        /*name*/			"sd1",
        /*storage_path*/	"storage/sd1",
        /*root_path*/		"storage/sd1/C/",
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_UDISK_ENABLE)
    //u盘0
    {
        /*logo*/			"udisk0",
        /*name*/			"udisk0",
        /*storage_path*/	"storage/udisk0",
        /*root_path*/		"storage/udisk0/C/",
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_UDISK_ENABLE)
    //u盘1
    {
        /*logo*/			"udisk1",
        /*name*/			"udisk1",
        /*storage_path*/	"storage/udisk1",
        /*root_path*/		"storage/udisk1/C/",
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_SD0_ENABLE && TCFG_RECORD_FOLDER_DEV_ENABLE)
    //sd0录音文件夹分区
    {
        /*logo*/			"sd0_rec",
        /*name*/			"sd0",
        /*storage_path*/	"storage/sd0",
        /*root_path*/		"storage/sd0/C/"REC_FOLDER_NAME,
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_SD1_ENABLE && TCFG_RECORD_FOLDER_DEV_ENABLE)
    //sd1录音文件夹分区
    {
        /*logo*/			"sd1_rec",
        /*name*/			"sd1",
        /*storage_path*/	"storage/sd1",
        /*root_path*/		"storage/sd1/C/"REC_FOLDER_NAME,
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_UDISK0_ENABLE && TCFG_RECORD_FOLDER_DEV_ENABLE)
    //u盘0录音文件夹分区
    {
        /*logo*/			"udisk0_rec",
        /*name*/			"udisk0",
        /*storage_path*/	"storage/udisk0",
        /*root_path*/		"storage/udisk0/C/"REC_FOLDER_NAME,
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if (TCFG_UDISK1_ENABLE && TCFG_RECORD_FOLDER_DEV_ENABLE)
    //u1盘录音文件夹分区
    {
        /*logo*/			"udisk1_rec",
        /*name*/			"udisk1",
        /*storage_path*/	"storage/udisk1",
        /*root_path*/		"storage/udisk1/C/"REC_FOLDER_NAME,
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if TCFG_NOR_FAT
    //外挂fat分区
    {
        /*logo*/			"fat_nor",
        /*name*/			"fat_nor",
        /*storage_path*/	"storage/fat_nor",
        /*root_path*/		"storage/fat_nor/C/",
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if TCFG_NOR_FS
    //外挂flash资源分区
    {
        /*logo*/			"res_nor",
        /*name*/			"res_nor",
        /*storage_path*/	"storage/res_nor",
        /*root_path*/		"storage/res_nor/C/",
        /*fs_type*/			"nor_sdfile",
    },
#endif
#if TCFG_NOR_REC
    ///外挂录音分区
    {
        /*logo*/			"rec_nor",
        /*name*/			"rec_nor",
        /*storage_path*/	"storage/rec_nor",
        /*root_path*/		"storage/rec_nor/C/",
        /*fs_type*/			"rec_fs",
    },
#endif
#if TCFG_VIR_UDISK_ENABLE
    // 虚拟U盘
    {
        /*logo*/			"vir_udisk",
        /*name*/			"vir_udisk",
        /*storage_path*/	"storage/vir_udisk",
        /*root_path*/		"storage/vir_udisk/C/",
        /*fs_type*/			FAT_FILE_SYSTEM_NAME,
    },
#endif
#if TCFG_VIRFAT_FLASH_ENABLE
    //flash 虚拟fat
    {
        /*logo*/			"virfat_flash",
        /*name*/			"virfat_flash",
        /*storage_path*/	"storage/virfat_flash",
        /*root_path*/		"storage/virfat_flash/C/",
        /*fs_type*/			"sdfile_fat",
    },
#endif
    //<新加设备参数请在reg end前添加!!
    //<reg end
    {
        /*logo*/			NULL,
        /*name*/			NULL,
        /*storage_path*/	NULL,
        /*root_path*/		NULL,
        /*fs_type*/			NULL,
    },
};



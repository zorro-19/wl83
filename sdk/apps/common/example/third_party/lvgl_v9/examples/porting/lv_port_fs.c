/**
 * @file lv_port_fs_templ.c
 *
 */

/*Copy this file as "lv_port_fs.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#define BOOL_DEFINE_CONFLICT
#include <assert.h>
#include "lv_port_fs.h"
#include "../../lvgl.h"
#include "fs/fs.h"
#include "character_coding.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br);
static lv_fs_res_t fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_size(lv_fs_drv_t *drv, void *file_p, uint32_t *size_p);
static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p);

static void *fs_dir_open(lv_fs_drv_t *drv, const char *path);
static lv_fs_res_t fs_dir_read(lv_fs_drv_t *drv, void *rddir_p, char *fn, uint32_t fn_len);
static lv_fs_res_t fs_dir_close(lv_fs_drv_t *drv, void *rddir_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_fs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();

    /*---------------------------------------------------
     * Register the file system interface in LVGL
     *--------------------------------------------------*/

    /*Add a simple drive to open images*/
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);

    /*Set up fields...*/
    fs_drv.letter = 's'; //从sd卡读取,路径首字符为's'
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = fs_write;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = fs_dir_close;
    fs_drv.dir_open_cb = fs_dir_open;
    fs_drv.dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv);

    /*添加文件系统适配flash读取*/
    static lv_fs_drv_t fs_drv_m;
    lv_fs_drv_init(&fs_drv_m);

    /*Set up fields...*/
    fs_drv_m.letter = 'm'; //flash路径首字符为'm'
    fs_drv_m.open_cb = fs_open;
    fs_drv_m.close_cb = fs_close;
    fs_drv_m.read_cb = fs_read;
    fs_drv_m.write_cb = fs_write;
    fs_drv_m.seek_cb = fs_seek;
    fs_drv_m.tell_cb = fs_tell;

    fs_drv_m.dir_close_cb = fs_dir_close;
    fs_drv_m.dir_open_cb = fs_dir_open;
    fs_drv_m.dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv_m);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your Storage device and File system.*/
static void fs_init(void)
{
    /*E.g. for FatFS initialize the SD card and FatFS itself*/

    /*You code here*/
}

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
    FILE *file;
    const char *fmode;

    if (mode == LV_FS_MODE_WR) {
        /*Open a file for write*/
        fmode = "w";
    } else if (mode == LV_FS_MODE_RD) {
        /*Open a file for read*/
        fmode = "r";
    } else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) {
        /*Open a file for read and write*/
        assert(0);
    }

    --path;

#ifdef CONFIG_JLFAT_ENABLE
    char _path[128];
    _path[long_file_name_encode(path, (unsigned char *)_path, sizeof(_path))] = '\0';

    if (path[0] == 'm') {
        file = fopen(path, "r");
    } else {
        file = fopen(_path, "r");
    }
#else
    file = fopen(path, "r");
#endif
    if (file == NULL) {
        printf("%s, open [%s][%s] fail! \r\n", __FUNCTION__, path, fmode);
        return NULL;
    }
    return file;
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p)
{
    fclose(file_p);
    return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br)
{
    lv_fs_res_t res = LV_FS_RES_OK;
    *br = fread(buf, 1, btr, file_p);
    if (*br == (uint32_t) - 1) {
        res = LV_FS_RES_FS_ERR;
    }

    return res;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btw       Bytes To Write
 * @param bw        the number of real written bytes (Bytes Written). NULL if unused.
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw)
{
    lv_fs_res_t res = LV_FS_RES_OK;
    *bw = fwrite((void *)buf, 1, btw, file_p);
    if (*bw == (uint32_t) - 1) {
        res = LV_FS_RES_FS_ERR;
    }

    return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
    lv_fs_res_t res = LV_FS_RES_OK;
    int orig;

    switch (whence) {
    case LV_FS_SEEK_SET:
        orig = SEEK_SET;
        break;
    case LV_FS_SEEK_CUR:
        orig = SEEK_CUR;
        break;
    case LV_FS_SEEK_END:
        orig = SEEK_END;
        break;
    }

    if (0 != fseek(file_p, pos, orig)) {
        res = LV_FS_RES_FS_ERR;
    }

    return res;
}
/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param pos_p     pointer to to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
    *pos_p = ftell(file_p);

    return LV_FS_RES_OK;
}

/**
 * Initialize a 'lv_fs_dir_t' variable for directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to a directory
 * @return          pointer to the directory read descriptor or NULL on error
 */
static void *fs_dir_open(lv_fs_drv_t *drv, const char *path)
{
    void *dir = NULL;
    assert(0);
    return dir;
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @param fn        pointer to a buffer to store the filename
 * @param fn_len    length of the buffer to store the filename
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read(lv_fs_drv_t *drv, void *rddir_p, char *fn, uint32_t fn_len)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/
    assert(0);

    return res;
}

/**
 * Close the directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close(lv_fs_drv_t *drv, void *rddir_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /*Add your code here*/
    assert(0);

    return res;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif

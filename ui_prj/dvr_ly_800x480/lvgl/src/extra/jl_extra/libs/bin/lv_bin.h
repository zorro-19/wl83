/**
 * @file lv_bin.h
 *
 */


#ifndef LV_BIN_H
#define LV_BIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../../lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*******************JL************************/
typedef struct {
    uint8_t res_type;
    uint8_t res_compress;
    uint16_t res_crc;
    uint32_t res_size;
    uint32_t nop;
} JLBinResourceHeader;

typedef struct {
    char JL[2];
    uint16_t version;
    JLBinResourceHeader jl_header;
    void *resource;
} JLBinResource;
/*******************JL************************/
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*JL获取.bin文件位图数据接口*/
//get lv_img_dsc_t结构体数据
lv_res_t lv_get_img_dsc_bin(const char *src, lv_img_dsc_t *bin_dsc);
lv_res_t lv_get_img_dsc_bin_nodata(const char *src, lv_img_dsc_t *bin_dsc);
lv_res_t lv_get_JLBinResource(const char *src, JLBinResource *bin_res);
lv_img_src_t lv_get_img_src_type(const char *src);
uint8_t lv_get_compress_type(const void *src);
uint32_t lv_get_flash_src_addr(const char *src);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BIN_H*/


/**
 * @file lv_gpu_jl_dma2d.h
 *
 */

#ifndef LV_GPU_JL_DMA2D_H
#define LV_GPU_JL_DMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../misc/lv_color.h"
#include "../../../hal/lv_hal_disp.h"
#include "../../sw/lv_draw_sw.h"

#if LV_USE_GPU_JL_DMA2D

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/
typedef lv_draw_sw_ctx_t lv_draw_jl_dma2d_ctx_t;

struct _lv_disp_drv_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Turn on the peripheral and set output color mode, this only needs to be done once
 */
void lv_draw_jl_dma2d_init(void);

void lv_draw_jl_dma2d_ctx_init(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx);

void lv_draw_jl_dma2d_ctx_deinit(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx);

void lv_draw_jl_dma2d_blend(lv_draw_ctx_t *draw_ctx, const lv_draw_sw_blend_dsc_t *dsc);

void lv_gpu_jl_dma2d_wait_cb(lv_draw_ctx_t *draw_ctx);

/**********************
 *      MACROS
 **********************/

#endif  /*LV_GPU_JL_DMA2D_H*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_GPU_JL_DMA2D_H*/

/**
 * @file sdl.h
 *
 */

#ifndef SDL_H
#define SDL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif
#endif

#if USE_MONITOR || USE_SDL

#include "sdl_common.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize SDL to be used as display, mouse and mouse wheel drivers.
 */
void sdl_init(void);

/**
 * Flush a buffer to the marked area
 * @param disp_drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixels to copy to the `area` part of the screen
 */
void sdl_display_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**
 * Flush a buffer to the marked area
 * @param disp_drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixels to copy to the `area` part of the screen
 */
void sdl_display_flush2(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**
 * Get the current position and state of the mouse
 * @param indev_drv pointer to the related input device driver
 * @param data store the mouse data here
 */
void sdl_mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/**
 * Get encoder (i.e. mouse wheel) ticks difference and pressed state
 * @param indev_drv pointer to the related input device driver
 * @param data store the read data here
 */
void sdl_mousewheel_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/**
 * Get input from the keyboard.
 * @param indev_drv pointer to the related input device driver
 * @param data store the red data here
 */
void sdl_keyboard_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/*For backward compatibility. Will be removed.*/
#define monitor_init sdl_init
#define monitor_flush sdl_display_flush
#define monitor_flush2 sdl_display_flush2

/**********************
 *      MACROS
 **********************/

#endif /* USE_MONITOR || USE_SDL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SDL_H */

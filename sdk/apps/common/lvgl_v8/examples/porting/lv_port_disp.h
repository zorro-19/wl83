/**
 * @file lv_port_disp_templ.h
 *
 */

/*Copy this file as "lv_port_disp.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_DISP_TEMPL_H
#define LV_PORT_DISP_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl_v8/lvgl.h"
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
/* Initialize low level display driver */
void lv_port_disp_init(void);


uint32_t lv_get_timer_handler_start_time_ms(void);

void lv_disp_draw_buf_user_config(void *buf1, void *buf2);

void lvgl_set_ui_flush_mode(u8 mode, void *buf1, void *buf2);

u8 lvgl_get_flush_mode(void);

u8 lvgl_get_fb_num(void);

char lvgl_ui_is_suspended(void);
void lvgl_ui_suspend(void);
void lvgl_ui_resume(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/

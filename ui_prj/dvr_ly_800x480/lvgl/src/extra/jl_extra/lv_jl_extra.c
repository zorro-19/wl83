/**
 * @file lv_extra.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_jl_extra_init(void)
{

#if LV_USE_RLE
    lv_rle_init();
#endif

#if LV_USE_JL_GUI_COMP

#if LV_USE_GUI_SCR
    gui_scr_init();
#endif
#if LV_USE_GUI_SCR_STACK
    gui_scr_stack_init();
#endif

#if LV_USE_JLJPEG
    lv_jlhw_jpeg_init();
#endif
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

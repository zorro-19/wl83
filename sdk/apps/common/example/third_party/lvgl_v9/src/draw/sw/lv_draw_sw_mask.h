/**
 * @file lv_draw_sw_mask.h
 *
 */

#ifndef LV_DRAW_SW_MASK_H
#define LV_DRAW_SW_MASK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../misc/lv_area.h"
#include "../../misc/lv_color.h"
#include "../../misc/lv_math.h"
#include "../../misc/lv_types.h"

/*********************
 *      DEFINES
 *********************/
#define LV_MASK_ID_INV  (-1)
#if LV_DRAW_SW_COMPLEX
# define LV_MASK_MAX_NUM     16
#else
# define LV_MASK_MAX_NUM     1
#endif

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LV_DRAW_SW_MASK_RES_TRANSP,
    LV_DRAW_SW_MASK_RES_FULL_COVER,
    LV_DRAW_SW_MASK_RES_CHANGED,
    LV_DRAW_SW_MASK_RES_UNKNOWN
} lv_draw_sw_mask_res_t;

#if LV_DRAW_SW_COMPLEX

typedef enum {
    LV_DRAW_SW_MASK_TYPE_LINE,
    LV_DRAW_SW_MASK_TYPE_ANGLE,
    LV_DRAW_SW_MASK_TYPE_RADIUS,
    LV_DRAW_SW_MASK_TYPE_FADE,
    LV_DRAW_SW_MASK_TYPE_MAP,
} lv_draw_sw_mask_type_t;

typedef enum {
    LV_DRAW_SW_MASK_LINE_SIDE_LEFT = 0,
    LV_DRAW_SW_MASK_LINE_SIDE_RIGHT,
    LV_DRAW_SW_MASK_LINE_SIDE_TOP,
    LV_DRAW_SW_MASK_LINE_SIDE_BOTTOM,
} lv_draw_sw_mask_line_side_t;

/**
 * A common callback type for every mask type.
 * Used internally by the library.
 */
typedef lv_draw_sw_mask_res_t (*lv_draw_sw_mask_xcb_t)(lv_opa_t *mask_buf, int32_t abs_x, int32_t abs_y,
        int32_t len,
        void *p);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_draw_sw_mask_init(void);

void lv_draw_sw_mask_deinit(void);

//! @cond Doxygen_Suppress

/**
 * Apply the added buffers on a line. Used internally by the library's drawing routines.
 * @param masks the masks list to apply, must be ended with NULL pointer in array.
 * @param mask_buf store the result mask here. Has to be `len` byte long. Should be initialized with `0xFF`.
 * @param abs_x absolute X coordinate where the line to calculate start
 * @param abs_y absolute Y coordinate where the line to calculate start
 * @param len length of the line to calculate (in pixel count)
 * @return One of these values:
 * - `LV_DRAW_MASK_RES_FULL_TRANSP`: the whole line is transparent. `mask_buf` is not set to zero
 * - `LV_DRAW_MASK_RES_FULL_COVER`: the whole line is fully visible. `mask_buf` is unchanged
 * - `LV_DRAW_MASK_RES_CHANGED`: `mask_buf` has changed, it shows the desired opacity of each pixel in the given line
 */
lv_draw_sw_mask_res_t /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_sw_mask_apply(void *masks[], lv_opa_t *mask_buf,
        int32_t abs_x,
        int32_t abs_y,
        int32_t len);

//! @endcond

/**
 * Free the data from the parameter.
 * It's called inside `lv_draw_sw_mask_remove_id` and `lv_draw_sw_mask_remove_custom`
 * Needs to be called only in special cases when the mask is not added by `lv_draw_mask_add`
 * and not removed by `lv_draw_mask_remove_id` or `lv_draw_mask_remove_custom`
 * @param p pointer to a mask parameter
 */
void lv_draw_sw_mask_free_param(void *p);

/**
 *Initialize a line mask from two points.
 * @param param pointer to a `lv_draw_mask_param_t` to initialize
 * @param p1x X coordinate of the first point of the line
 * @param p1y Y coordinate of the first point of the line
 * @param p2x X coordinate of the second point of the line
 * @param p2y y coordinate of the second point of the line
 * @param side and element of `lv_draw_mask_line_side_t` to describe which side to keep.
 * With `LV_DRAW_MASK_LINE_SIDE_LEFT/RIGHT` and horizontal line all pixels are kept
 * With `LV_DRAW_MASK_LINE_SIDE_TOP/BOTTOM` and vertical line all pixels are kept
 */
void lv_draw_sw_mask_line_points_init(lv_draw_sw_mask_line_param_t *param, int32_t p1x, int32_t p1y,
                                      int32_t p2x,
                                      int32_t p2y, lv_draw_sw_mask_line_side_t side);

/**
 *Initialize a line mask from a point and an angle.
 * @param param  pointer to a `lv_draw_mask_param_t` to initialize
 * @param px     X coordinate of a point of the line
 * @param py     X coordinate of a point of the line
 * @param angle  right 0 deg, bottom: 90
 * @param side   an element of `lv_draw_mask_line_side_t` to describe which side to keep.
 * With `LV_DRAW_MASK_LINE_SIDE_LEFT/RIGHT` and horizontal line all pixels are kept
 * With `LV_DRAW_MASK_LINE_SIDE_TOP/BOTTOM` and vertical line all pixels are kept
 */
void lv_draw_sw_mask_line_angle_init(lv_draw_sw_mask_line_param_t *param, int32_t px, int32_t py, int16_t angle,
                                     lv_draw_sw_mask_line_side_t side);

/**
 * Initialize an angle mask.
 * @param param pointer to a `lv_draw_mask_param_t` to initialize
 * @param vertex_x X coordinate of the angle vertex (absolute coordinates)
 * @param vertex_y Y coordinate of the angle vertex (absolute coordinates)
 * @param start_angle start angle in degrees. 0 deg on the right, 90 deg, on the bottom
 * @param end_angle end angle
 */
void lv_draw_sw_mask_angle_init(lv_draw_sw_mask_angle_param_t *param, int32_t vertex_x, int32_t vertex_y,
                                int32_t start_angle, int32_t end_angle);

/**
 * Initialize a fade mask.
 * @param param pointer to an `lv_draw_mask_radius_param_t` to initialize
 * @param rect coordinates of the rectangle to affect (absolute coordinates)
 * @param radius radius of the rectangle
 * @param inv true: keep the pixels inside the rectangle; keep the pixels outside of the rectangle
 */
void lv_draw_sw_mask_radius_init(lv_draw_sw_mask_radius_param_t *param, const lv_area_t *rect, int32_t radius,
                                 bool inv);

/**
 * Initialize a fade mask.
 * @param param pointer to a `lv_draw_mask_param_t` to initialize
 * @param coords coordinates of the area to affect (absolute coordinates)
 * @param opa_top opacity on the top
 * @param y_top at which coordinate start to change to opacity to `opa_bottom`
 * @param opa_bottom opacity at the bottom
 * @param y_bottom at which coordinate reach `opa_bottom`.
 */
void lv_draw_sw_mask_fade_init(lv_draw_sw_mask_fade_param_t *param, const lv_area_t *coords, lv_opa_t opa_top,
                               int32_t y_top,
                               lv_opa_t opa_bottom, int32_t y_bottom);

/**
 * Initialize a map mask.
 * @param param pointer to a `lv_draw_mask_param_t` to initialize
 * @param coords coordinates of the map (absolute coordinates)
 * @param map array of bytes with the mask values
 */
void lv_draw_sw_mask_map_init(lv_draw_sw_mask_map_param_t *param, const lv_area_t *coords, const lv_opa_t *map);

#endif /*LV_DRAW_SW_COMPLEX*/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DRAW_SW_MASK_H*/

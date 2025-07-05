/**
 * @file lv_imglist.h
 *
 */

#ifndef LV_IMG_LIST_H
#define LV_IMG_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../../lvgl.h"

#if LV_USE_IMGLIST != 0

/*Testing of dependencies*/
#if LV_USE_IMG == 0
#error "lv_imglist: lv_img is required. Enable it in lv_conf.h (LV_USE_IMG 1)"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

extern const lv_obj_class_t lv_imglist_class;

/*Data of image*/
typedef struct {
    lv_img_t img;
    /*picture sequence */
    const void **dsc;
    int8_t  pic_count;
    uint32_t act_idx;
} lv_imglist_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create an image list objects
 * @param parent pointer to an object, it will be the parent of the new button
 * @return pointer to the created image list object
 */
lv_obj_t *lv_imglist_create(lv_obj_t *parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the image list images source.
 * @param obj pointer to an image list object
 * @param dsc pointer to a series images
 * @param num images' number
 */
void lv_imglist_set_src(lv_obj_t *obj, const void *dsc[], uint8_t num);

/**
 * Set the current image of the image list
 * @param obj pointer to an image list object
 * @param act_idx index of the image to show
 */
void lv_imglist_set_act(lv_obj_t *obj, uint32_t act_idx);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the current image of the image list
 * @param obj pointer to an image list object
 * @return uint32_t index of the image to show
 */
uint32_t lv_imglist_get_act(lv_obj_t *obj);

#endif /*LV_USE_IMGLIST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_IMG_LIST_H*/

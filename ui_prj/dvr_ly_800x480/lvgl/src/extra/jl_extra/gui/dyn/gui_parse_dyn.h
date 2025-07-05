/**
 * @file gui_parse_dyn.h
 *
 */

#ifndef GUI_PARSE_DYN_H
#define GUI_PARSE_DYN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/


#include "../gui_common.h"
#include "../scr/gui_scr.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*dynamic resource header*/
typedef struct {
    char JL[2];          // 标识符
    int16_t version;     // 版本号
    int32_t ts;          // 时间戳
    int32_t page_cnt;    // 页面数量
    int32_t page_offset; // 页面偏移
} JLDynResource;

/*dynamic page header*/
typedef struct {
    int32_t id;  // 控件ID
    int8_t type; // 控件类型
    int8_t nop1;
    int8_t nop2;
    int8_t nop3;
    int16_t children_cnt;    // 子控件数量
    int32_t children_offset; // 子控件偏移
    int16_t prop_cnt;        // 属性数量
    int32_t prop_offset;     // 属性偏移
    int16_t style_cnt;       // 样式数量
    int32_t style_offset;    // 样式偏移
    int16_t event_cnt;       // 事件数量
    int32_t event_offset;    // 事件偏移
} JLDynControl;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * @brief Get the dyn file data
 *
 * @param path dyn file path
 * @param res dynamic resource header
 * @param size data size
 * @return char* data buffer
 */
char *gui_dyn_get_data(const char *path, JLDynResource *res, int32_t *size);

/**
 * @brief Free the dyn data buffer
 *
 * @param buf data buffer
 */
void gui_dyn_free_data(char *buf);

/**
 * @brief Parse the dyn data to screen by page index
 *
 * @param buf data buffer
 * @param size data size
 * @param page_idx page index
 * @param parent parent object
 * @return lv_obj_t* object
 */
lv_obj_t *gui_dyn_parse_obj_by_idx(char *buf, int32_t size, int32_t page_idx, lv_obj_t *parent);

/**
 * @brief Parse the dyn data to screen by page id
 *
 * @param buf data buffer
 * @param size data size
 * @param page_id page id
 * @param parent parent object
 * @return lv_obj_t* object
 */
lv_obj_t *gui_dyn_parse_obj_by_id(char *buf, int32_t size, int32_t page_id, lv_obj_t *parent);

/**
 * @brief Parse the dyn data to screen by page index
 *
 * @param buf data buffer
 * @param size data size
 * @param page_idx page index
 * @return gui_scr_t* screen
 */
gui_scr_t *gui_dyn_parse_src_by_idx(char *buf, int32_t size, int32_t page_idx);

/**
 * @brief Parse the dyn data to screen by page id
 *
 * @param buf data buffer
 * @param size data size
 * @param page_id page id
 * @return gui_scr_t* screen
 */
gui_scr_t *gui_dyn_parse_src_by_id(char *buf, int32_t size, int32_t page_id);

/**
 * @brief Get the page data by page index
 *
 * @param buf data buffer
 * @param size data size
 * @param page_idx page index
 * @param page_data page data buffer
 * @param page_size page data size
 * @return JLDynControl* page control
 */
JLDynControl *gui_dyn_get_page_by_idx(char *buf, int32_t size, int32_t page_idx, char **page_data, int32_t *page_size);

/**
 * @brief Get the page data by page id
 *
 * @param buf data buffer
 * @param size data size
 * @param page_id page id
 * @param page_data page data buffer
 * @param page_size page data size
 * @return JLDynControl* page control
 */
JLDynControl *gui_dyn_get_page_by_id(char *buf, int32_t size, int32_t page_id, char **page_data, int32_t *page_size);

#endif


#ifdef __cplusplus
} /*extern "C"*/
#endif


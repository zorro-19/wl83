/*Generate Code, Do NOT Edit!*/
#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "./common.h"
#include "./gui_fonts/gui_fonts.h"
#include "./gui_images/gui_images.h"
#include "./gui_scr/ui_scr_manager.h"
#include "./gui_scr/ui_style.h"

#ifdef JL_GUI_KERNEL_VERSION_MAJOR
#if GUI_CORE_VERSION_MAJOR != JL_GUI_KERNEL_VERSION_MAJOR
#error "Current Kernel Version is not compatible, please replace or upgrade the kernel!"
#endif
#if GUI_CORE_VERSION_MINOR > JL_GUI_KERNEL_VERSION_MINOR
#warning "Current Kernel Version is too low, some features may not be available, please update the kernel version!"
#endif
#else
#error "Current Kernel Version is not defined, please replace or upgrade the kernel!"
#endif

#ifndef LV_USE_GUIBUILDER_SIMULATOR
#if defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR) && defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR)
#if GUI_TEMPLATE_VERSION_MAJOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR || GUI_TEMPLATE_VERSION_MAJOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR
#error "Current Project Template Version is not compatible with the SDK version. Please select a compatible SDK version!"
#endif
#if GUI_TEMPLATE_VERSION_MINOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MINOR || GUI_TEMPLATE_VERSION_MINOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MINOR
#warning "Current Project Template Version has minor incompatibilities with the SDK. Some features may not be available. Consider updating the SDK version."
#endif
#endif
#endif

typedef struct {
    // Screen home
    lv_obj_t *home;
    bool      home_del;
    lv_obj_t *home_imgbtn_2;
    lv_obj_t *home_imgbtn_2_label;
    lv_obj_t *home_imgbtn_1;
    lv_obj_t *home_imgbtn_1_label;
    lv_obj_t *home_imgbtn_3;
    lv_obj_t *home_imgbtn_3_label;
} lv_ui_home;

typedef struct {
    // Screen pair_status
    lv_obj_t *pair_status;
    bool      pair_status_del;
    lv_obj_t *g_kb_pair_status;
    lv_obj_t *pair_status_imglist_1;
    lv_obj_t *pair_status_imglist_2;
    lv_obj_t *pair_status_imglist_3;
    lv_obj_t *pair_status_imglist_4;
    lv_obj_t *pair_status_imglist_5;
    lv_obj_t *pair_status_imglist_6;
    lv_obj_t *pair_status_imgbtn_1;
    lv_obj_t *pair_status_imgbtn_1_label;
    lv_obj_t *pair_status_lbl_1;
    lv_obj_t *pair_status_lbl_2;
    lv_obj_t *pair_status_lbl_3;
    lv_obj_t *pair_status_lbl_4;
    lv_obj_t *pair_status_lbl_5;
    lv_obj_t *pair_status_lbl_6;
    lv_obj_t *pair_status_ddlist_1;
    lv_obj_t *pair_status_lbl_7;
} lv_ui_pair_status;

typedef struct {
    // Screen rt_stream
    lv_obj_t *rt_stream;
    bool      rt_stream_del;
    lv_obj_t *rt_stream_imgbtn_1;
    lv_obj_t *rt_stream_imgbtn_1_label;
    lv_obj_t *rt_stream_lbl_1;
} lv_ui_rt_stream;

typedef struct {
    // Screen file_browser
    lv_obj_t *file_browser;
    bool      file_browser_del;
    lv_obj_t *file_browser_view_2;
    lv_obj_t *file_browser_imgbtn_1;
    lv_obj_t *file_browser_imgbtn_1_label;
    lv_obj_t *file_browser_imgbtn_2;
    lv_obj_t *file_browser_imgbtn_2_label;
    lv_obj_t *file_browser_imgbtn_3;
    lv_obj_t *file_browser_imgbtn_3_label;
    lv_obj_t *file_browser_lbl_1;
    lv_obj_t *file_browser_imgbtn_4;
    lv_obj_t *file_browser_imgbtn_4_label;
    lv_obj_t *file_browser_browser_cont;
    lv_obj_t *file_browser_file_cont1;
    lv_obj_t *file_browser_img_1;
    lv_obj_t *file_browser_lbl_2;
    lv_obj_t *file_browser_cb_1;
    lv_obj_t *file_browser_file_cont2;
    lv_obj_t *file_browser_img_2;
    lv_obj_t *file_browser_lbl_3;
    lv_obj_t *file_browser_cb_2;
    lv_obj_t *file_browser_file_cont3;
    lv_obj_t *file_browser_img_3;
    lv_obj_t *file_browser_lbl_4;
    lv_obj_t *file_browser_cb_3;
    lv_obj_t *file_browser_file_cont4;
    lv_obj_t *file_browser_img_4;
    lv_obj_t *file_browser_lbl_5;
    lv_obj_t *file_browser_cb_4;
    lv_obj_t *file_browser_file_cont5;
    lv_obj_t *file_browser_img_5;
    lv_obj_t *file_browser_lbl_6;
    lv_obj_t *file_browser_cb_5;
    lv_obj_t *file_browser_file_cont6;
    lv_obj_t *file_browser_img_6;
    lv_obj_t *file_browser_lbl_7;
    lv_obj_t *file_browser_cb_6;
} lv_ui_file_browser;

typedef struct {
    // Screen pair_options
    lv_obj_t *pair_options;
    bool      pair_options_del;
    lv_obj_t *pair_options_imgbtn_1;
    lv_obj_t *pair_options_imgbtn_1_label;
    lv_obj_t *pair_options_imgbtn_2;
    lv_obj_t *pair_options_imgbtn_2_label;
    lv_obj_t *pair_options_lbl_1;
    lv_obj_t *pair_options_lbl_2;
    lv_obj_t *pair_options_imgbtn_4;
    lv_obj_t *pair_options_imgbtn_4_label;
} lv_ui_pair_options;

typedef struct {
    // Screen pairing
    lv_obj_t *pairing;
    bool      pairing_del;
    lv_obj_t *pairing_lbl_1;
} lv_ui_pairing;

typedef struct {
    // Screen unpair
    lv_obj_t *unpair;
    bool      unpair_del;
    lv_obj_t *unpair_lbl_1;
} lv_ui_unpair;

typedef struct {
    // Screen video_play
    lv_obj_t *video_play;
    bool      video_play_del;
    lv_obj_t *video_play_imgbtn_1;
    lv_obj_t *video_play_imgbtn_1_label;
    lv_obj_t *video_play_view_1;
    lv_obj_t *video_play_imglist_1;
    lv_obj_t *video_play_imgbtn_3;
    lv_obj_t *video_play_imgbtn_3_label;
    lv_obj_t *video_play_imgbtn_2;
    lv_obj_t *video_play_imgbtn_2_label;
    lv_obj_t *video_play_bar_1;
} lv_ui_video_play;

typedef struct {
    // Screen sys_prompt
    lv_obj_t *sys_prompt;
    bool      sys_prompt_del;
    lv_obj_t *sys_prompt_view_1;
    lv_obj_t *sys_prompt_lbl_1;
    lv_obj_t *sys_prompt_img_1;
} lv_ui_sys_prompt;

typedef struct {
    // Screen dir_select
    lv_obj_t *dir_select;
    bool      dir_select_del;
    lv_obj_t *dir_select_view_1;
    lv_obj_t *dir_select_img_1;
    lv_obj_t *dir_select_lbl_2;
    lv_obj_t *dir_select_view_2;
    lv_obj_t *dir_select_img_2;
    lv_obj_t *dir_select_lbl_3;
    lv_obj_t *dir_select_view_3;
    lv_obj_t *dir_select_img_3;
    lv_obj_t *dir_select_lbl_4;
    lv_obj_t *dir_select_view_4;
    lv_obj_t *dir_select_img_4;
    lv_obj_t *dir_select_lbl_5;
    lv_obj_t *dir_select_view_5;
    lv_obj_t *dir_select_img_5;
    lv_obj_t *dir_select_lbl_6;
    lv_obj_t *dir_select_view_6;
    lv_obj_t *dir_select_img_6;
    lv_obj_t *dir_select_lbl_7;
    lv_obj_t *dir_select_lbl_1;
    lv_obj_t *dir_select_imgbtn_1;
    lv_obj_t *dir_select_imgbtn_1_label;
} lv_ui_dir_select;

typedef struct {
    // Screen device_select
    lv_obj_t *device_select;
    bool      device_select_del;
    lv_obj_t *device_select_view_1;
    lv_obj_t *device_select_img_1;
    lv_obj_t *device_select_lbl_2;
    lv_obj_t *device_select_view_2;
    lv_obj_t *device_select_img_2;
    lv_obj_t *device_select_lbl_3;
    lv_obj_t *device_select_lbl_1;
    lv_obj_t *device_select_imgbtn_1;
    lv_obj_t *device_select_imgbtn_1_label;
} lv_ui_device_select;

typedef struct {
    // Screen sys_options
    lv_obj_t *sys_options;
    bool      sys_options_del;
    lv_obj_t *sys_options_view_1;
    lv_obj_t *sys_options_lbl_1;
    lv_obj_t *sys_options_btn_1;
    lv_obj_t *sys_options_btn_1_label;
    lv_obj_t *sys_options_btn_2;
    lv_obj_t *sys_options_btn_2_label;
} lv_ui_sys_options;

// generate lv_ui gui_guider
typedef struct {
    lv_ui_home *home;
    lv_ui_pair_status *pair_status;
    lv_ui_rt_stream *rt_stream;
    lv_ui_file_browser *file_browser;
    lv_ui_pair_options *pair_options;
    lv_ui_pairing *pairing;
    lv_ui_unpair *unpair;
    lv_ui_video_play *video_play;
    lv_ui_sys_prompt *sys_prompt;
    lv_ui_dir_select *dir_select;
    lv_ui_device_select *device_select;
    lv_ui_sys_options *sys_options;

    lv_group_t *default_group;
} lv_ui;

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck);

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck);

gui_scr_t *ui_get_scr(int32_t scr_id);
gui_scr_t *ui_get_setup_scr(int32_t scr_id);
void *ui_get_scr_ptr(lv_ui *ui, int32_t scr_id);
void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id);
void ui_init_style(lv_style_t *style);
void setup_ui(lv_ui *ui);
#include "./gui_msg/gui_msg.h"
extern lv_ui guider_ui;// Screen home
lv_obj_t *setup_scr_home(lv_ui *ui);
void unload_scr_home(lv_ui *ui);
// Screen pair_status
lv_obj_t *setup_scr_pair_status(lv_ui *ui);
void unload_scr_pair_status(lv_ui *ui);






// Screen rt_stream
lv_obj_t *setup_scr_rt_stream(lv_ui *ui);
void unload_scr_rt_stream(lv_ui *ui);
// Screen file_browser
lv_obj_t *setup_scr_file_browser(lv_ui *ui);
void unload_scr_file_browser(lv_ui *ui);
// Screen pair_options
lv_obj_t *setup_scr_pair_options(lv_ui *ui);
void unload_scr_pair_options(lv_ui *ui);
// Screen pairing
lv_obj_t *setup_scr_pairing(lv_ui *ui);
void unload_scr_pairing(lv_ui *ui);
// Screen unpair
lv_obj_t *setup_scr_unpair(lv_ui *ui);
void unload_scr_unpair(lv_ui *ui);
// Screen video_play
lv_obj_t *setup_scr_video_play(lv_ui *ui);
void unload_scr_video_play(lv_ui *ui);

// Screen sys_prompt
lv_obj_t *setup_scr_sys_prompt(lv_ui *ui);
void unload_scr_sys_prompt(lv_ui *ui);
// Screen dir_select
lv_obj_t *setup_scr_dir_select(lv_ui *ui);
void unload_scr_dir_select(lv_ui *ui);
// Screen device_select
lv_obj_t *setup_scr_device_select(lv_ui *ui);
void unload_scr_device_select(lv_ui *ui);
// Screen sys_options
lv_obj_t *setup_scr_sys_options(lv_ui *ui);
void unload_scr_sys_options(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif

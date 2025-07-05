/*Generate Code, Do NOT Edit!*/
#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "common.h"
#include "gui_fonts.h"
#include "gui_images.h"
#include "lv_i18n.h"

#if LV_USE_GUIBUILDER_SIMULATOR
#define GUI_WEAKREF __attribute__((weakref))
#define GUI_WEAK __attribute__((weak))
#else
#define GUI_WEAKREF
#define GUI_WEAK __attribute__((weak))
#endif

#ifdef JL_GUI_KERNEL_VERSION_MAJOR
#if GUI_CORE_VERSION_MAJOR > JL_GUI_KERNEL_VERSION_MAJOR
#error "Current Kernel Version is too low, please update the kernel version!"
#endif
#if GUI_CORE_VERSION_MINOR > JL_GUI_KERNEL_VERSION_MINOR
#warning "Current Kernel Version is too low, some features may not be available, please update the kernel version!"
#endif
#else
#error "Current Kernel Version is not defined, please replace or upgrade the kernel!"
#endif

// generate lv_ui gui_guider
typedef struct {
    // Screen start
    lv_obj_t *start;
    bool      start_del;
    lv_obj_t *start_img_logo;

    // Screen home
    lv_obj_t *home;
    bool      home_del;
    lv_obj_t *home_img_wifi;
    lv_obj_t *home_lbl_bat;
    lv_obj_t *home_lbl_2;
    lv_obj_t *home_lbl_4;
    lv_obj_t *home_lbl_5;
    lv_obj_t *home_img_funkey1;
    lv_obj_t *home_img_funkey3;
    lv_obj_t *home_img_funkey2;
    lv_obj_t *home_digitclock_time;
    lv_obj_t *home_img_weather;
    lv_obj_t *home_img_bat;
    lv_obj_t *home_lbl_note;
    lv_obj_t *home_img_menu;
    lv_obj_t *home_imglist_bat;
    lv_obj_t *home_imglist_wifi;

    // Screen menu
    lv_obj_t *menu;
    bool      menu_del;
    lv_obj_t *menu_edit_return;
    lv_obj_t *menu_edit_download;
    lv_obj_t *menu_edit_netcfg;
    lv_obj_t *menu_edit_language;
    lv_obj_t *menu_edit_sysset;
    lv_obj_t *menu_img_return;
    lv_obj_t *menu_edit_sysinfo;
    lv_obj_t *menu_img_download;
    lv_obj_t *menu_img_netcfg;
    lv_obj_t *menu_img_language;
    lv_obj_t *menu_img_sysset;
    lv_obj_t *menu_img_sysinfo;

    // Screen language
    lv_obj_t *language;
    bool      language_del;
    lv_obj_t *language_btn_return;
    lv_obj_t *language_btn_return_label;
    lv_obj_t *language_list_language;
    lv_obj_t *language_list_language_item0;
    lv_obj_t *language_list_language_item1;
    lv_obj_t *language_list_language_item2;

    // Screen app
    lv_obj_t *app;
    bool      app_del;
    lv_obj_t *app_btn_return;
    lv_obj_t *app_btn_return_label;
    lv_obj_t *app_img_qrcode;

    // Screen syscfg
    lv_obj_t *syscfg;
    bool      syscfg_del;
    lv_obj_t *syscfg_btn_return;
    lv_obj_t *syscfg_btn_return_label;
    lv_obj_t *syscfg_list_sysset;
    lv_obj_t *syscfg_list_sysset_item0;
    lv_obj_t *syscfg_list_sysset_item1;
    lv_obj_t *syscfg_list_sysset_item2;

    // Screen sysinfo
    lv_obj_t *sysinfo;
    bool      sysinfo_del;
    lv_obj_t *sysinfo_img_info;
    lv_obj_t *sysinfo_btn_return;
    lv_obj_t *sysinfo_btn_return_label;

} lv_ui;

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck);

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck);

void ui_init_style(lv_style_t *style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
#include "gui_msg.h"
extern lv_ui guider_ui;// Screen start
lv_obj_t *setup_scr_start(lv_ui *ui);
void unload_scr_start(lv_ui *ui);
// Screen home
lv_obj_t *setup_scr_home(lv_ui *ui);
void unload_scr_home(lv_ui *ui);
/*DigitalClock*/
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec);


// Screen menu
lv_obj_t *setup_scr_menu(lv_ui *ui);
void unload_scr_menu(lv_ui *ui);
// Screen language
lv_obj_t *setup_scr_language(lv_ui *ui);
void unload_scr_language(lv_ui *ui);
// Screen app
lv_obj_t *setup_scr_app(lv_ui *ui);
void unload_scr_app(lv_ui *ui);
// Screen syscfg
lv_obj_t *setup_scr_syscfg(lv_ui *ui);
void unload_scr_syscfg(lv_ui *ui);
// Screen sysinfo
lv_obj_t *setup_scr_sysinfo(lv_ui *ui);
void unload_scr_sysinfo(lv_ui *ui);

// Image Declare
LV_IMG_DECLARE(_img_logo_alpha_332x82);
#ifdef __cplusplus
}
#endif
#endif

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

// generate lv_ui gui_guider
typedef struct {
    // Screen audio
    lv_obj_t *audio;
    bool      audio_del;
    lv_obj_t *audio_title;
    lv_obj_t *audio_back_btn;
    lv_obj_t *audio_back_btn_label;
    lv_obj_t *audio_local_music_btn;
    lv_obj_t *audio_local_music_btn_label;
    lv_obj_t *audio_recorder_btn;
    lv_obj_t *audio_recorder_btn_label;
    lv_obj_t *audio_bt_music_btn;
    lv_obj_t *audio_bt_music_btn_label;
    lv_obj_t *audio_net_music_btn;
    lv_obj_t *audio_net_music_btn_label;

    // Screen camera
    lv_obj_t *camera;
    bool      camera_del;
    lv_obj_t *camera_title;
    lv_obj_t *camera_back_btn;
    lv_obj_t *camera_back_btn_label;
    lv_obj_t *camera_camera1_btn;
    lv_obj_t *camera_camera1_btn_label;
    lv_obj_t *camera_camera2_btn;
    lv_obj_t *camera_camera2_btn_label;
    lv_obj_t *camera_camera3_btn;
    lv_obj_t *camera_camera3_btn_label;

    // Screen boot_animation
    lv_obj_t *boot_animation;
    bool      boot_animation_del;
    lv_obj_t *boot_animation_jl_logo;

    // Screen home
    lv_obj_t *home;
    bool      home_del;
    lv_obj_t *home_list;
    lv_obj_t *home_list_item0;
    lv_obj_t *home_list_item1;
    lv_obj_t *home_list_item2;
    lv_obj_t *home_list_item3;
    lv_obj_t *home_list_item4;
    lv_obj_t *home_list_item5;
    lv_obj_t *home_title;

    // Screen key
    lv_obj_t *key;
    bool      key_del;
    lv_obj_t *key_title;
    lv_obj_t *key_back_btn;
    lv_obj_t *key_back_btn_label;
    lv_obj_t *key_show_label;

    // Screen camera1_mipi
    lv_obj_t *camera1_mipi;
    bool      camera1_mipi_del;
    lv_obj_t *camera1_mipi_title;

    // Screen audio_local_music
    lv_obj_t *audio_local_music;
    bool      audio_local_music_del;
    lv_obj_t *audio_local_music_title;
    lv_obj_t *audio_local_music_back_btn;
    lv_obj_t *audio_local_music_back_btn_label;
    lv_obj_t *audio_local_music_switch_btn;
    lv_obj_t *audio_local_music_switch_btn_label;
    lv_obj_t *audio_local_music_prev_btn;
    lv_obj_t *audio_local_music_prev_btn_label;
    lv_obj_t *audio_local_music_next_btn;
    lv_obj_t *audio_local_music_next_btn_label;
    lv_obj_t *audio_local_music_volume_slider;
    lv_obj_t *audio_local_music_lbl_1;
    lv_obj_t *audio_local_music_music_time;

    // Screen audio_recorder
    lv_obj_t *audio_recorder;
    bool      audio_recorder_del;
    lv_obj_t *audio_recorder_title;
    lv_obj_t *audio_recorder_back_btn;
    lv_obj_t *audio_recorder_back_btn_label;
    lv_obj_t *audio_recorder_volume_slider;
    lv_obj_t *audio_recorder_enc_gain_slider;
    lv_obj_t *audio_recorder_enc_label;
    lv_obj_t *audio_recorder_lbl_1;

    // Screen audio_net_music
    lv_obj_t *audio_net_music;
    bool      audio_net_music_del;
    lv_obj_t *audio_net_music_title;
    lv_obj_t *audio_net_music_back_btn;
    lv_obj_t *audio_net_music_back_btn_label;

    // Screen wifi
    lv_obj_t *wifi;
    bool      wifi_del;
    lv_obj_t *g_kb_wifi;
    lv_obj_t *wifi_title;
    lv_obj_t *wifi_back_btn;
    lv_obj_t *wifi_back_btn_label;
    lv_obj_t *wifi_show_current_ssid;
    lv_obj_t *wifi_login_wifi;
    lv_obj_t *wifi_ssid_txt;
    lv_obj_t *wifi_pwd_txt;
    lv_obj_t *wifi_connect_btn;
    lv_obj_t *wifi_connect_btn_label;
    lv_obj_t *wifi_ssid_label;
    lv_obj_t *wifi_pwd_label;

    // Screen audio_bt_music
    lv_obj_t *audio_bt_music;
    bool      audio_bt_music_del;
    lv_obj_t *audio_bt_music_title;
    lv_obj_t *audio_bt_music_back_btn;
    lv_obj_t *audio_bt_music_back_btn_label;

    // Screen bluetooth
    lv_obj_t *bluetooth;
    bool      bluetooth_del;
    lv_obj_t *bluetooth_title;
    lv_obj_t *bluetooth_back_btn;
    lv_obj_t *bluetooth_back_btn_label;
    lv_obj_t *bluetooth_show_bt_name;
    lv_obj_t *bluetooth_bt_state;

    // Screen camera2_dvp
    lv_obj_t *camera2_dvp;
    bool      camera2_dvp_del;
    lv_obj_t *camera2_dvp_title;

    // Screen camera3_dvp
    lv_obj_t *camera3_dvp;
    bool      camera3_dvp_del;
    lv_obj_t *camera3_dvp_title;

    // Screen sdcard
    lv_obj_t *sdcard;
    bool      sdcard_del;
    lv_obj_t *sdcard_title;
    lv_obj_t *sdcard_back_btn;
    lv_obj_t *sdcard_back_btn_label;
    lv_obj_t *sdcard_show_sdcard_state;
    lv_obj_t *sdcard_capacity_bar;
    lv_obj_t *sdcard_sdcard_path_label;
    lv_obj_t *sdcard_sdcard_total_label;
    lv_obj_t *sdcard_not_found_label;

    lv_group_t *default_group;
} lv_ui;

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck);

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck);

void ui_init_style(lv_style_t *style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
#include "./gui_msg/gui_msg.h"
extern lv_ui guider_ui;// Screen audio
lv_obj_t *setup_scr_audio(lv_ui *ui);
void unload_scr_audio(lv_ui *ui);
// Screen camera
lv_obj_t *setup_scr_camera(lv_ui *ui);
void unload_scr_camera(lv_ui *ui);
// Screen boot_animation
lv_obj_t *setup_scr_boot_animation(lv_ui *ui);
void unload_scr_boot_animation(lv_ui *ui);
// Screen home
lv_obj_t *setup_scr_home(lv_ui *ui);
void unload_scr_home(lv_ui *ui);
// Screen key
lv_obj_t *setup_scr_key(lv_ui *ui);
void unload_scr_key(lv_ui *ui);
// Screen camera1_mipi
lv_obj_t *setup_scr_camera1_mipi(lv_ui *ui);
void unload_scr_camera1_mipi(lv_ui *ui);
// Screen audio_local_music
lv_obj_t *setup_scr_audio_local_music(lv_ui *ui);
void unload_scr_audio_local_music(lv_ui *ui);
// Screen audio_recorder
lv_obj_t *setup_scr_audio_recorder(lv_ui *ui);
void unload_scr_audio_recorder(lv_ui *ui);
// Screen audio_net_music
lv_obj_t *setup_scr_audio_net_music(lv_ui *ui);
void unload_scr_audio_net_music(lv_ui *ui);
// Screen wifi
lv_obj_t *setup_scr_wifi(lv_ui *ui);
void unload_scr_wifi(lv_ui *ui);
// Screen audio_bt_music
lv_obj_t *setup_scr_audio_bt_music(lv_ui *ui);
void unload_scr_audio_bt_music(lv_ui *ui);
// Screen bluetooth
lv_obj_t *setup_scr_bluetooth(lv_ui *ui);
void unload_scr_bluetooth(lv_ui *ui);
// Screen camera2_dvp
lv_obj_t *setup_scr_camera2_dvp(lv_ui *ui);
void unload_scr_camera2_dvp(lv_ui *ui);
// Screen camera3_dvp
lv_obj_t *setup_scr_camera3_dvp(lv_ui *ui);
void unload_scr_camera3_dvp(lv_ui *ui);
// Screen sdcard
lv_obj_t *setup_scr_sdcard(lv_ui *ui);
void unload_scr_sdcard(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif

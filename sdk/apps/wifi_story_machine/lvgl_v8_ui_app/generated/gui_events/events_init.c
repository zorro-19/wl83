/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"


void events_init(lv_ui *ui)
{
}

static void audio_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_ON, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void audio_local_music_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio_local_music
        {
            lv_obj_t *dest = ui->audio_local_music;
            extern void gui_open_local_music(void);
            gui_open_local_music();
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO_LOCAL_MUSIC);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO_LOCAL_MUSIC, "audio_local_music", guider_ui.audio_local_music, (gui_scr_setup_cb_t)setup_scr_audio_local_music, (gui_scr_unload_cb_t)unload_scr_audio_local_music);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void audio_recorder_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio_recorder
        {
            lv_obj_t *dest = ui->audio_recorder;
            extern void gui_open_recorder(void);
            gui_open_recorder();
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO_RECORDER);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO_RECORDER, "audio_recorder", guider_ui.audio_recorder, (gui_scr_setup_cb_t)setup_scr_audio_recorder, (gui_scr_unload_cb_t)unload_scr_audio_recorder);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void audio_bt_music_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO_BT_MUSIC);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO_BT_MUSIC, "audio_bt_music", guider_ui.audio_bt_music, (gui_scr_setup_cb_t)setup_scr_audio_bt_music, (gui_scr_unload_cb_t)unload_scr_audio_bt_music);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void audio_net_music_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO_NET_MUSIC);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO_NET_MUSIC, "audio_net_music", guider_ui.audio_net_music, (gui_scr_setup_cb_t)setup_scr_audio_net_music, (gui_scr_unload_cb_t)unload_scr_audio_net_music);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_audio(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->audio_back_btn, audio_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_local_music_btn, audio_local_music_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_recorder_btn, audio_recorder_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_bt_music_btn, audio_bt_music_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_net_music_btn, audio_net_music_btn_event_handler, LV_EVENT_ALL, ui);
}

static void camera_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void camera_camera1_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code camera1_mipi
        {
            lv_obj_t *dest = ui->camera1_mipi;
            extern void gui_open_camera(unsigned char id);
            gui_open_camera(3);
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA1_MIPI);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA1_MIPI, "camera1_mipi", guider_ui.camera1_mipi, (gui_scr_setup_cb_t)setup_scr_camera1_mipi, (gui_scr_unload_cb_t)unload_scr_camera1_mipi);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void camera_camera2_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code camera2_dvp
        {
            lv_obj_t *dest = ui->camera2_dvp;
            extern void gui_open_camera(unsigned char id);
            gui_open_camera(0);
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA2_DVP);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA2_DVP, "camera2_dvp", guider_ui.camera2_dvp, (gui_scr_setup_cb_t)setup_scr_camera2_dvp, (gui_scr_unload_cb_t)unload_scr_camera2_dvp);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void camera_camera3_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code camera3_dvp
        {
            lv_obj_t *dest = ui->camera3_dvp;
            extern void gui_open_camera(unsigned char id);
            gui_open_camera(1);
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA3_DVP);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA3_DVP, "camera3_dvp", guider_ui.camera3_dvp, (gui_scr_setup_cb_t)setup_scr_camera3_dvp, (gui_scr_unload_cb_t)unload_scr_camera3_dvp);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_camera(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->camera_back_btn, camera_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->camera_camera1_btn, camera_camera1_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->camera_camera2_btn, camera_camera2_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->camera_camera3_btn, camera_camera3_btn_event_handler, LV_EVENT_ALL, ui);
}

static void boot_animation_jl_logo_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 1000, 0, true, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_boot_animation(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->boot_animation_jl_logo, boot_animation_jl_logo_event_handler, LV_EVENT_ALL, ui);
}

static void home_list_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_KEY);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_KEY, "key", guider_ui.key, (gui_scr_setup_cb_t)setup_scr_key, (gui_scr_unload_cb_t)unload_scr_key);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void home_list_item1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA, "camera", guider_ui.camera, (gui_scr_setup_cb_t)setup_scr_camera, (gui_scr_unload_cb_t)unload_scr_camera);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void home_list_item3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_WIFI);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_WIFI, "wifi", guider_ui.wifi, (gui_scr_setup_cb_t)setup_scr_wifi, (gui_scr_unload_cb_t)unload_scr_wifi);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void home_list_item4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_BLUETOOTH);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_BLUETOOTH, "bluetooth", guider_ui.bluetooth, (gui_scr_setup_cb_t)setup_scr_bluetooth, (gui_scr_unload_cb_t)unload_scr_bluetooth);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void home_list_item2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO, "audio", guider_ui.audio, (gui_scr_setup_cb_t)setup_scr_audio, (gui_scr_unload_cb_t)unload_scr_audio);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void home_list_item5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_SDCARD);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_SDCARD, "sdcard", guider_ui.sdcard, (gui_scr_setup_cb_t)setup_scr_sdcard, (gui_scr_unload_cb_t)unload_scr_sdcard);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_home(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_list_item0, home_list_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_list_item1, home_list_item1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_list_item3, home_list_item3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_list_item4, home_list_item4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_list_item2, home_list_item2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_list_item5, home_list_item5_event_handler, LV_EVENT_ALL, ui);
}

static void key_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_key(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->key_back_btn, key_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void camera1_mipi_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code camera
        {
            lv_obj_t *dest = ui->camera;
#if LV_USE_GUIBUILDER_SIMULATOR

#else
            //CAM1(MIPI)  video_id:3
            extern void gui_close_camera(unsigned char id);
            gui_close_camera(3);
#endif
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA, "camera", guider_ui.camera, (gui_scr_setup_cb_t)setup_scr_camera, (gui_scr_unload_cb_t)unload_scr_camera);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_camera1_mipi(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->camera1_mipi, camera1_mipi_event_handler, LV_EVENT_ALL, ui);
}

static void audio_local_music_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio
        {
            lv_obj_t *dest = ui->audio;
            extern void gui_close_local_music(void);
            gui_close_local_music();

        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO, "audio", guider_ui.audio, (gui_scr_setup_cb_t)setup_scr_audio, (gui_scr_unload_cb_t)unload_scr_audio);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void audio_local_music_switch_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio_local_music_switch_btn
        {
            lv_obj_t *dest = ui->audio_local_music_switch_btn;
            extern void gui_play_pause_music(void);
            gui_play_pause_music();
        }
    }
    break;
    default:
        break;
    }
}

static void audio_local_music_prev_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void gui_play_prev_music(void);
            gui_play_prev_music();
        }
    }
    break;
    default:
        break;
    }
}

static void audio_local_music_next_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern void gui_play_next_music(void);
            gui_play_next_music();
        }
    }
    break;
    default:
        break;
    }
}

static void audio_local_music_volume_slider_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_obj_t *obj = lv_event_get_target(e);
            uint8_t val = lv_slider_get_value(obj);

            extern void gui_set_music_volume(int value);
            gui_set_music_volume(val);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_audio_local_music(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->audio_local_music_back_btn, audio_local_music_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_local_music_switch_btn, audio_local_music_switch_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_local_music_prev_btn, audio_local_music_prev_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_local_music_next_btn, audio_local_music_next_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_local_music_volume_slider, audio_local_music_volume_slider_event_handler, LV_EVENT_ALL, ui);
}

static void audio_recorder_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio
        {
            lv_obj_t *dest = ui->audio;
            extern void gui_close_recorder(void);
            gui_close_recorder();
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO, "audio", guider_ui.audio, (gui_scr_setup_cb_t)setup_scr_audio, (gui_scr_unload_cb_t)unload_scr_audio);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void audio_recorder_volume_slider_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_obj_t *obj = lv_event_get_target(e);
            uint8_t val = lv_slider_get_value(obj);

            extern void gui_set_music_volume(int value);
            gui_set_music_volume(val);
        }
    }
    break;
    default:
        break;
    }
}

static void audio_recorder_enc_gain_slider_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_obj_t *obj = lv_event_get_target(e);
            uint8_t val = lv_slider_get_value(obj);

            extern void gui_set_recoder_volume(int value);
            gui_set_recoder_volume(val);
        }
    }
    break;
    default:
        break;
    }
}

void events_init_audio_recorder(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->audio_recorder_back_btn, audio_recorder_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_recorder_volume_slider, audio_recorder_volume_slider_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->audio_recorder_enc_gain_slider, audio_recorder_enc_gain_slider_event_handler, LV_EVENT_ALL, ui);
}

static void audio_net_music_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio
        {
            lv_obj_t *dest = ui->audio;
#if LV_USE_GUIBUILDER_SIMULATOR
            printf("back audio \n");
#else
            printf("back audio \n");

#endif
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO, "audio", guider_ui.audio, (gui_scr_setup_cb_t)setup_scr_audio, (gui_scr_unload_cb_t)unload_scr_audio);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_audio_net_music(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->audio_net_music_back_btn, audio_net_music_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void wifi_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void wifi_connect_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            extern gui_connect_wifi(void);
            gui_connect_wifi();
        }
    }
    break;
    default:
        break;
    }
}

void events_init_wifi(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->wifi_back_btn, wifi_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->wifi_connect_btn, wifi_connect_btn_event_handler, LV_EVENT_ALL, ui);
}

static void audio_bt_music_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code audio
        {
            lv_obj_t *dest = ui->audio;
#if LV_USE_GUIBUILDER_SIMULATOR
            printf("back audio \n");
#else
            printf("back audio \n");

#endif
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_AUDIO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_AUDIO, "audio", guider_ui.audio, (gui_scr_setup_cb_t)setup_scr_audio, (gui_scr_unload_cb_t)unload_scr_audio);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_audio_bt_music(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->audio_bt_music_back_btn, audio_bt_music_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void bluetooth_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_bluetooth(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->bluetooth_back_btn, bluetooth_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void camera2_dvp_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code camera
        {
            lv_obj_t *dest = ui->camera;
#if LV_USE_GUIBUILDER_SIMULATOR

#else
            //CAM2(DVP)  video_id:0
            extern void gui_close_camera(unsigned char id);
            gui_close_camera(0);
#endif
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA, "camera", guider_ui.camera, (gui_scr_setup_cb_t)setup_scr_camera, (gui_scr_unload_cb_t)unload_scr_camera);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_camera2_dvp(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->camera2_dvp, camera2_dvp_event_handler, LV_EVENT_ALL, ui);
}

static void camera3_dvp_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code camera
        {
            lv_obj_t *dest = ui->camera;
#if LV_USE_GUIBUILDER_SIMULATOR

#else
            //CAM3(DVP)  video_id:1
            extern void gui_close_camera(unsigned char id);
            gui_close_camera(1);
#endif
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_CAMERA);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_CAMERA, "camera", guider_ui.camera, (gui_scr_setup_cb_t)setup_scr_camera, (gui_scr_unload_cb_t)unload_scr_camera);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_camera3_dvp(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->camera3_dvp, camera3_dvp_event_handler, LV_EVENT_ALL, ui);
}

static void sdcard_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 800, 0, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_sdcard(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->sdcard_back_btn, sdcard_back_btn_event_handler, LV_EVENT_ALL, ui);
}

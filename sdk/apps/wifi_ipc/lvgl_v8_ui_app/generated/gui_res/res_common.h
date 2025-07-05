/*Generate Code, Do NOT Edit!*/
#ifndef __RES_COMMON_H__
#define __RES_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef enum {
    GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x10000000,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000000.rle
    GUI_RES_SIMSUN_22_WOFF = 0x10000001,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000001.rle
    GUI_RES_MONTSERRATMEDIUM_32_TTF = 0x10000002,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000002.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF = 0x10000003,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000003.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF = 0x10000004,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000004.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF = 0x10000005,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000005.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x10000006,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\ui_res\rle\font\10000006.rle

    GUI_RES_WIFI_04_PNG = 0x56000000,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_04.png
    GUI_RES_ICON_CALL_OUT_PNG = 0x56000001,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_call_out.png
    GUI_RES_ICON_RECOVER_PNG = 0x56000002,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_recover.png
    GUI_RES_ICON_WALKIE_TALKIE_PNG = 0x56000003,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_walkie_talkie.png
    GUI_RES_WEATHER_013_HOME_IMG_WEATHER_PNG = 0x56000004,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_013.png
    GUI_RES_ICON_BATTERY_CHARGING_PNG = 0x56000005,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_charging.png
    GUI_RES_ICON_BATTERY_15_PNG = 0x56000006,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_15.png
    GUI_RES_ICON_BATTERY_25_PNG = 0x56000007,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_25.png
    GUI_RES_ICON_BATTERY_50_PNG = 0x56000008,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_50.png
    GUI_RES_ICON_BATTERY_75_PNG = 0x56000009,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_75.png
    GUI_RES_ICON_BATTERY_100_PNG = 0x5600000A,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_100.png
    GUI_RES_WIFI_00_PNG = 0x5600000B,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_00.png
    GUI_RES_WIFI_01_PNG = 0x5600000C,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_01.png
    GUI_RES_WIFI_2_PNG = 0x5600000D,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_2.png
    GUI_RES_WIFI_03_PNG = 0x5600000E,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_03.png
    GUI_RES_ICON_BACK_PNG = 0x5600000F,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_back.png
    GUI_RES_ICON_DOWNLOAD_PNG = 0x56000010,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_download.png
    GUI_RES_ICON_CONFNET_PNG = 0x56000011,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_confnet.png
    GUI_RES_ICON_LANGUAGE_PNG = 0x56000012,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_language.png
    GUI_RES_ICON_SETTLE_PNG = 0x56000013,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_settle.png
    GUI_RES_ICON_ABOUT_PNG = 0x56000014,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_about.png
    GUI_RES_ICON_CODE_PNG = 0x56000015,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_code.png
    GUI_RES_QRCODE_PNG = 0x56000016,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\qrcode.png
} GUI_RES_ID;

typedef enum {
    RES_ICON_BATTERY_100 = 0xD6000000,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_100.png 51x51
    RES_ICON_BATTERY_15 = 0xD6000001,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_15.png 51x51
    RES_ICON_BATTERY_25 = 0xD6000002,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_25.png 51x51
    RES_ICON_BATTERY_50 = 0xD6000003,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_50.png 51x51
    RES_ICON_BATTERY_75 = 0xD6000004,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_75.png 51x51
    RES_ICON_BATTERY_CHARGING = 0xD6000005,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_battery_charging.png 51x51
    RES_ICON_CALL_OUT = 0xD6000006,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_call_out.png 98x98
    RES_ICON_HANGUP = 0xD6000007,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_hangup.png 98x98
    RES_ICON_LOUDSPEAKER_OFF = 0xD6000008,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_loudspeaker_off.png 98x98
    RES_ICON_LOUDSPEAKER_ON = 0xD6000009,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_loudspeaker_on.png 98x98
    RES_ICON_WALKIE_TALKIE = 0xD600000A,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_walkie_talkie.png 98x98
    RES_ICON_WIFI = 0xD600000B,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_wifi.png 48x48
    RES_IC_MIC_OFF = 0xD600000C,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\ic_mic_off.png 98x98
    RES_IC_MIC_ON = 0xD600000D,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\ic_mic_on.png 98x98
    RES_IMG_LOGO = 0xD600000E,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\img_logo.png 332x82
    RES_ICON_RECOVER = 0xD600000F,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\icon_recover.png 98x98
    RES_WEATHER_001 = 0xD6000010,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_001.png 200x200
    RES_WEATHER_002 = 0xD6000011,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_002.png 200x200
    RES_WEATHER_003 = 0xD6000012,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_003.png 200x200
    RES_WEATHER_004 = 0xD6000013,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_004.png 200x200
    RES_WEATHER_005 = 0xD6000014,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_005.png 200x200
    RES_WEATHER_006 = 0xD6000015,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_006.png 200x200
    RES_WEATHER_008 = 0xD6000016,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_008.png 200x200
    RES_WEATHER_007 = 0xD6000017,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_007.png 200x200
    RES_WEATHER_009 = 0xD6000018,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_009.png 200x200
    RES_WEATHER_010 = 0xD6000019,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_010.png 200x200
    RES_WEATHER_011 = 0xD600001A,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_011.png 200x200
    RES_WEATHER_012 = 0xD600001B,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_012.png 200x200
    RES_WEATHER_013 = 0xD600001C,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_013.png 200x200
    RES_WEATHER_014 = 0xD600001D,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_014.png 200x200
    RES_WEATHER_015 = 0xD600001E,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_015.png 200x200
    RES_WEATHER_016 = 0xD600001F,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_016.png 200x200
    RES_WEATHER_017 = 0xD6000020,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\weather_017.png 200x200
    RES_WIFI_00 = 0xD6000021,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_00.png 32x32
    RES_WIFI_01 = 0xD6000022,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_01.png 32x32
    RES_WIFI_03 = 0xD6000023,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_03.png 32x32
    RES_WIFI_04 = 0xD6000024,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_04.png 32x32
    RES_WIFI_2 = 0xD6000025,   //F:\wl83_411\wifi_video_master\ui_prj\door_bell_480x800\import\image\wifi_2.png 32x32
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

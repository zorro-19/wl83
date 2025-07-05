/*Generate Code, Do NOT Edit!*/
#include "res_common.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
char path_buf[20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_MONTSERRATMEDIUM_22_TTF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000000.rle";
    case GUI_RES_SIMSUN_22_WOFF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000001.rle";
    case GUI_RES_MONTSERRATMEDIUM_32_TTF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000002.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000004.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000005.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF:
        return "F:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\ui_res\\rle\\font\\10000006.rle";
    case GUI_RES_WIFI_04_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png";
    case GUI_RES_ICON_CALL_OUT_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_call_out.png";
    case GUI_RES_ICON_RECOVER_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_recover.png";
    case GUI_RES_ICON_WALKIE_TALKIE_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_walkie_talkie.png";
    case GUI_RES_WEATHER_013_HOME_IMG_WEATHER_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_013.png";
    case GUI_RES_ICON_BATTERY_CHARGING_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png";
    case GUI_RES_ICON_BATTERY_15_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_15.png";
    case GUI_RES_ICON_BATTERY_25_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_25.png";
    case GUI_RES_ICON_BATTERY_50_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_50.png";
    case GUI_RES_ICON_BATTERY_75_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_75.png";
    case GUI_RES_ICON_BATTERY_100_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_100.png";
    case GUI_RES_WIFI_00_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_00.png";
    case GUI_RES_WIFI_01_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_01.png";
    case GUI_RES_WIFI_2_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_2.png";
    case GUI_RES_WIFI_03_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_03.png";
    case GUI_RES_ICON_BACK_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_back.png";
    case GUI_RES_ICON_DOWNLOAD_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_download.png";
    case GUI_RES_ICON_CONFNET_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_confnet.png";
    case GUI_RES_ICON_LANGUAGE_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_language.png";
    case GUI_RES_ICON_SETTLE_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_settle.png";
    case GUI_RES_ICON_ABOUT_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_about.png";
    case GUI_RES_ICON_CODE_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_code.png";
    case GUI_RES_QRCODE_PNG:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\qrcode.png";
    case RES_ICON_BATTERY_100:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_100.png";
    case RES_ICON_BATTERY_15:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_15.png";
    case RES_ICON_BATTERY_25:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_25.png";
    case RES_ICON_BATTERY_50:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_50.png";
    case RES_ICON_BATTERY_75:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_75.png";
    case RES_ICON_BATTERY_CHARGING:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png";
    case RES_ICON_CALL_OUT:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_call_out.png";
    case RES_ICON_HANGUP:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_hangup.png";
    case RES_ICON_LOUDSPEAKER_OFF:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_loudspeaker_off.png";
    case RES_ICON_LOUDSPEAKER_ON:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_loudspeaker_on.png";
    case RES_ICON_WALKIE_TALKIE:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_walkie_talkie.png";
    case RES_ICON_WIFI:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_wifi.png";
    case RES_IC_MIC_OFF:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\ic_mic_off.png";
    case RES_IC_MIC_ON:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\ic_mic_on.png";
    case RES_IMG_LOGO:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\img_logo.png";
    case RES_ICON_RECOVER:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\icon_recover.png";
    case RES_WEATHER_001:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_001.png";
    case RES_WEATHER_002:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_002.png";
    case RES_WEATHER_003:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_003.png";
    case RES_WEATHER_004:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_004.png";
    case RES_WEATHER_005:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_005.png";
    case RES_WEATHER_006:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_006.png";
    case RES_WEATHER_008:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_008.png";
    case RES_WEATHER_007:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_007.png";
    case RES_WEATHER_009:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_009.png";
    case RES_WEATHER_010:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_010.png";
    case RES_WEATHER_011:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_011.png";
    case RES_WEATHER_012:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_012.png";
    case RES_WEATHER_013:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_013.png";
    case RES_WEATHER_014:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_014.png";
    case RES_WEATHER_015:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_015.png";
    case RES_WEATHER_016:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_016.png";
    case RES_WEATHER_017:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\weather_017.png";
    case RES_WIFI_00:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_00.png";
    case RES_WIFI_01:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_01.png";
    case RES_WIFI_03:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_03.png";
    case RES_WIFI_04:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png";
    case RES_WIFI_2:
        return "A:\\wl83_411\\wifi_video_master\\ui_prj\\door_bell_480x800\\import\\image\\wifi_2.png";
    default:
        return NULL;
    }
#else
    memset(path_buf, 0, sizeof(path_buf));
    if (id >= 0x10000000 && id < 0x10000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.rle", id);
    } else if (id >= 0x30000000 && id < 0x31000000) {
        sprintf(path_buf, "storage/sd0/C/%x.mp4", id);
    } else if (id >= 0x31000000 && id < 0x32000000) {
        sprintf(path_buf, "storage/sd0/C/%x.avi", id);
    } else if (id >= 0x40000000 && id < 0x50000000) {
        sprintf(path_buf, "storage/sd0/C/%x.gif", id);
    } else if (id >= 0x50000000 && id < 0x51000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.png", id);
    } else if (id >= 0x51000000 && id < 0x52000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.jpg", id);
    } else if (id >= 0x52000000 && id < 0x53000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.jpeg", id);
    } else if (id >= 0x53000000 && id < 0x54000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.bmp", id);
    } else if (id >= 0x54000000 && id < 0x55000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.svg", id);
    } else if (id >= 0x55000000 && id < 0x56000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.bin", id);
    } else if (id >= 0x56000000 && id < 0x57000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.rle", id);
    } else if (id >= 0x57000000 && id < 0x58000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.etc", id);
    } else if (id >= 0x80000000 && id < 0x90000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.bin", id);
    } else if (id >= 0xA0000000 && id < 0xA1000000) {
        sprintf(path_buf, "storage/sd0/C/%x.mp4", id);
    } else if (id >= 0xA1000000 && id < 0xA2000000) {
        sprintf(path_buf, "storage/sd0/C/%x.avi", id);
    } else if (id >= 0xB0000000 && id < 0xC0000000) {
        sprintf(path_buf, "storage/sd0/C/%x.gif", id);
    } else if (id >= 0xD0000000 && id < 0xD1000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.png", id);
    } else if (id >= 0xD1000000 && id < 0xD2000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.jpg", id);
    } else if (id >= 0xD2000000 && id < 0xD3000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.jpeg", id);
    } else if (id >= 0xD3000000 && id < 0xD4000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.bmp", id);
    } else if (id >= 0xD4000000 && id < 0xD5000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.svg", id);
    } else if (id >= 0xD5000000 && id < 0xD6000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.bin", id);
    } else if (id >= 0xD6000000 && id < 0xD7000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.rle", id);
    } else if (id >= 0xD7000000 && id < 0xD8000000) {
        sprintf(path_buf, "mnt/sdfile/EXT_RESERVED/uipackres/ui/%x.etc", id);
    } else {
        return NULL;
    }
    return path_buf;
#endif
}

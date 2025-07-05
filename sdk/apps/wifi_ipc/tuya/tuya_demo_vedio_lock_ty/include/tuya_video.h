/***********************************************************
*  File: tuya_video.h
*  Author: mengjinlong
*  Date: 20210401
***********************************************************/
#ifndef _TUYA_VIDEO_H
#define _TUYA_VIDEO_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#define TY_REVERS_ANGLE  3
//#define  LCD_FROM_INTR   1
//#define  LCD_FROM_APP    2
//#define  LCD_FROM_TIMER  3
//#define  LCD_FROM_BUTTON 4
//#define  LCD_FROM_UART   5
//#define  LCD_FROM_QRCODE 6

#define CAMERA_CFG_PARAM_E       "camera_cfg"
#define AUDIO_CFG_PARAM_E        "audio_cfg"
#define LCD_CFG_PARAM_E          "lcd_cfg"
#define USB_CFG_PARAM_E          "usb_cfg"
#define USB_AUTO_CFG_PARAM_E     "usb_auto_cfg"
#define LORD_CFG_PARAM_E          "lord_cfg"
#define LORD2_CFG_PARAM_E         "lord2_cfg"

#define USB_TYPE_NONE_E          0
#define USB_TYPE_UVC_E           1
#define USB_TYPE_UVC_UAC_E       2

typedef struct {
    INT_T video_width;
    INT_T video_height;
    INT_T video_rotat_angle;
    INT_T video_fps;
    INT_T video_power_off;
} TY_CAMERA_PARAM;

typedef struct {
    INT_T channel_num;
    INT_T bit_dept;
    INT_T sample_rate;
    INT_T audio_power_off;
} TY_AUDIO_PARAM;

typedef struct {
    INT_T usb_type; //uvc ??UVC+UAC
    INT_T usb_speed; //1.1 2.0  ??2.0
    INT_T default0;
    INT_T default1;
    INT_T default2;
    INT_T default3;
    INT_T default4;
    INT_T default5;
} TY_USB_PARAM;

typedef struct {
    INT_T static_electricity_close; //??????
    INT_T phone_rotation;      //??????
    INT_T local_door_bell_ring;  //uac????????
    INT_T lcd_auto_install_direction_open; //lcd ???????????
    INT_T ui_language;
    CHAR_T lcd_open_time;
    CHAR_T default1;
    CHAR_T default2;
    CHAR_T default3;
    INT_T default4;
    INT_T default5;
} TY_LORD_PARAM;

#if 0
enum {
    DISP_MAIN_WIN  = 0, //大小窗
    DISP_HALF_WIN,      //各半屏
    DISP_FRONT_WIN,     //只前窗
    DISP_BACK_WIN,      //只后窗
    DISP_PARK_WIN,      //parking win
    DISP_RESET_WIN,
    DISP_FORBIDDEN,     //forbidden
    DISP_MAX_WIN   = DISP_FORBIDDEN,
};

enum {
    DISP_WIN_SW_SHOW_SMALL,
    DISP_WIN_SW_SHOW_NEXT,
    DISP_WIN_SW_SHOW_PARKING,
    DISP_WIN_SW_HIDE_PARKING,
    DISP_WIN_SW_DEV_IN,
    DISP_WIN_SW_DEV_OUT,
    DISP_WIN_SW_MIRROR,
};
#endif

INT_T tuya_video_init(TY_CAMERA_PARAM *camera_param);
VOID_T tuya_video_lcd_ctr(BOOL_T status, INT_T from_set, INT_T pic);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

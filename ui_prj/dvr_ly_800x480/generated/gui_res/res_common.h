/*Generate Code, Do NOT Edit!*/
#ifndef __RES_COMMON_H__
#define __RES_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_USE_GUIBUILDER_SIMULATOR
	#define GUI_WEAKREF __attribute__((weakref))
	#define GUI_WEAK __attribute__((weak))
#else
	#define GUI_WEAKREF
	#define GUI_WEAK __attribute__((weak))
#endif

#define CONV_RES_ID(id) (((id) >> 24) | ((id) & 0x00FFFFFF) << 8)
typedef enum {
	GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x10000000,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000000.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF = 0x10000001,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000001.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF = 0x10000002,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000002.rle
	GUI_RES_MONTSERRATMEDIUM_18_TTF = 0x10000003,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000003.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF = 0x10000004,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000004.rle
	GUI_RES_MONTSERRATMEDIUM_24_TTF = 0x10000005,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000005.rle
	GUI_RES_MONTSERRATMEDIUM_12_TTF = 0x10000006,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000006.rle
	GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x10000007,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000007.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF = 0x10000008,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000008.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF = 0x10000009,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000009.rle
	GUI_RES_MONTSERRATMEDIUM_16_TTF = 0x1000000A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\1000000a.rle
	GUI_RES_MONTSERRATMEDIUM_20_TTF = 0x1000000B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\1000000b.rle

	GUI_RES_S_PC_PNG = 0x55000000,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\USB\s_PC.png
	GUI_RES_S_MASS_PNG = 0x55000001,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\USB\s_MASS.png
	GUI_RES_I_REC_PNG = 0x55000002,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_rec.png
	GUI_RES_CYCLIC_VIDEO_3_PNG = 0x55000003,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_3.png
	GUI_RES_EXP_A0_PNG = 0x55000004,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a0.png
	GUI_RES_I_MOT_PNG = 0x55000005,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_mot.png
	GUI_RES_I_TEAR_PNG = 0x55000006,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_tear.png
	GUI_RES_MIC_ON_PNG = 0x55000007,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\mic_on.png
	GUI_RES_I_HDR_PNG = 0x55000008,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_hdr.png
	GUI_RES_I_GRA_L_PNG = 0x55000009,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_l.png
	GUI_RES_PARK_PNG = 0x5500000A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\park.png
	GUI_RES_BAT_FULL_PNG = 0x5500000B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_full.png
	GUI_RES_CARD_ONLINE_PNG = 0x5500000C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_online.png
	GUI_RES_RED_CIRCLE_PNG = 0x5500000D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\red_circle.png
	GUI_RES_FLIG_ON_PNG = 0x5500000E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\flig_on.png
	GUI_RES_KEY_PNG = 0x5500000F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\key.png
	GUI_RES_M_SOLU_PNG = 0x55000010,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_solu.png
	GUI_RES_M_TWO_REC_PNG = 0x55000011,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_two_rec.png
	GUI_RES_M_CYC_PNG = 0x55000012,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_cyc.png
	GUI_RES_REC_NOCYC_PNG = 0x55000013,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\rec_nocyc.png
	GUI_RES_M_HDR_PNG = 0x55000014,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_hdr.png
	GUI_RES_M_EXP_PNG = 0x55000015,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_exp.png
	GUI_RES_M_MOT_PNG = 0x55000016,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_mot.png
	GUI_RES_M_AUD_PNG = 0x55000017,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_aud.png
	GUI_RES_M_DAT_PNG = 0x55000018,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_dat.png
	GUI_RES_M_GRA_PNG = 0x55000019,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_gra.png
	GUI_RES_M_PARK_PNG = 0x5500001A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_park.png
	GUI_RES_M_NUM_PNG = 0x5500001B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_num.png
	GUI_RES_M_FLIG_PNG = 0x5500001C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_flig.png
	GUI_RES_MENU_STA_PNG = 0x5500001D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\menu_sta.png
	GUI_RES_REC_PNG = 0x5500001E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\rec.png
	GUI_RES_SET_PNG = 0x5500001F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\set.png
	GUI_RES_LEFT_PNG = 0x55000020,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\left.png
	GUI_RES_UP_PNG = 0x55000021,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\up.png
	GUI_RES_DOWN_PNG = 0x55000022,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\down.png
	GUI_RES_RIGHT_PNG = 0x55000023,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\right.png
	GUI_RES_POP_UP_WINDOW_PNG = 0x55000024,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\pop_up_window.png
	GUI_RES_FLIG_ON_1_PNG = 0x55000025,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\flig_on.png
	GUI_RES_ASTERN_PNG = 0x55000026,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\astern.png
	GUI_RES_LCD_AU_PNG = 0x55000027,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\lcd_au.png
	GUI_RES_AUTO_OFF_PNG = 0x55000028,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\auto_off.png
	GUI_RES_HZ_PNG = 0x55000029,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\hz.png
	GUI_RES_KEY_V_PNG = 0x5500002A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\key_v.png
	GUI_RES_LANGUAGE_PNG = 0x5500002B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\language.png
	GUI_RES_TIME_PNG = 0x5500002C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\time.png
	GUI_RES_TV_PNG = 0x5500002D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\tv.png
	GUI_RES_MDK_PNG = 0x5500002E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\mdk.png
	GUI_RES_DEF_SET_PNG = 0x5500002F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\def_set.png
	GUI_RES_VERSION_PNG = 0x55000030,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\version.png
	GUI_RES_NUM_L_PNG = 0x55000031,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\NUM_l.png
	GUI_RES_NUM_D_PNG = 0x55000032,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\NUM_d.png
	GUI_RES_TP_3_PNG = 0x55000033,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\tp_3.png
	GUI_RES_TP_PNG = 0x55000034,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\tp.png
	GUI_RES_AWB_AUTO_PNG = 0x55000035,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_auto.png
	GUI_RES_ISO_AUTO_PNG = 0x55000036,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_auto.png
	GUI_RES_Q1_PNG = 0x55000037,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q1.png
	GUI_RES_DL2_PNG = 0x55000038,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl2.png
	GUI_RES_SHAKE_OFF_PNG = 0x55000039,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\shake_off.png
	GUI_RES_LIANP_PNG = 0x5500003A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\lianp.png
	GUI_RES_PAIZ_PNG = 0x5500003B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\paiz.png
	GUI_RES_LIANP_1_PNG = 0x5500003C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\lianp.png
	GUI_RES_IMG_Q_PNG = 0x5500003D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\img_q.png
	GUI_RES_RUIDU_PNG = 0x5500003E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\ruidu.png
	GUI_RES_COLOR_PNG = 0x5500003F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\color.png
	GUI_RES_ISO_PNG = 0x55000040,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\iso.png
	GUI_RES_SHAKE_PNG = 0x55000041,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\shake.png
	GUI_RES_SCAN_PNG = 0x55000042,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\scan.png
	GUI_RES_PHOTO_PNG = 0x55000043,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\photo.png
	GUI_RES_VIDEO_PLAY_PNG = 0x55000044,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_play.png
	GUI_RES_VIDEO_PAUSE_PNG = 0x55000045,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_pause.png
	GUI_RES_SKIP_PREVIOUS_PNG = 0x55000046,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\skip_previous.png
	GUI_RES_SKIP_NEXT_PNG = 0x55000047,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\skip_next.png
	GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x55000048,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\volumeLouder_solid_1.png
	GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x55000049,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\volumeMute_solid_1.png
	GUI_RES_PHOTO_1_PNG = 0x5500004A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\PHOTO.png
	GUI_RES_PHOTO_ON_PNG = 0x5500004B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\photo_on.png
	GUI_RES_UP_1_PNG = 0x5500004C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\up.png
	GUI_RES_DOWN_1_PNG = 0x5500004D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\down.png
	GUI_RES_DELET_PNG = 0x5500004E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\delet.png
	GUI_RES_PROTECT_PNG = 0x5500004F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\protect.png
	GUI_RES_PLAY_PNG = 0x55000050,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\play.png
	GUI_RES_VIDEO_PNG = 0x55000051,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\video.png
	GUI_RES_PHOTO_2_PNG = 0x55000052,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\photo.png
	GUI_RES_CARD_OFFLINE_PNG = 0x55000053,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_offline.png
	GUI_RES_PLAY_1_PNG = 0x55000054,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\play.png
	GUI_RES_PAUSE_PNG = 0x55000055,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\pause.png
} GUI_RES_ID;

typedef enum {
	RES_0 = 0xD5000000,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\battery\0.png 48x48
	RES_1 = 0xD5000001,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\battery\1.png 48x48
	RES_2 = 0xD5000002,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\battery\2.png 48x48
	RES_3 = 0xD5000003,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\battery\3.png 48x48
	RES_CHARGING = 0xD5000004,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\battery\charging.png 48x48
	RES_FULL = 0xD5000005,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\battery\full.png 48x48
	RES_GRAVITY_SENSOR_LOW = 0xD5000006,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\gravity_sensor_low.png 48x48
	RES_GRAVITY_SENSOR_MIDLLER = 0xD5000007,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\gravity_sensor_midller.png 48x48
	RES_GRAVITY_SENSOR_HIGH = 0xD5000008,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\gravity_sensor_high.png 48x48
	RES_INTERVAL_VIDEO_CLOSE = 0xD5000009,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_close.png 48x48
	RES_INTERVAL_VIDEO_500 = 0xD500000A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_500.png 48x48
	RES_INTERVAL_VIDEO_200 = 0xD500000B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_200.png 48x48
	RES_INTERVAL_VIDEO_100 = 0xD500000C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_100.png 48x48
	RES_SD = 0xD500000D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\SD.png 45x45
	RES_SD_CLOSE = 0xD500000E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\SD_close.png 45x45
	RES_SOUND = 0xD500000F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sound.png 48x48
	RES_SOUND_CLOSE = 0xD5000010,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sound_close.png 48x48
	RES_EXPOSURE = 0xD5000011,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\exposure.png 80x80
	RES_DOUBLE_VIDEO = 0xD5000012,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\double_video.png 80x80
	RES_DATE = 0xD5000013,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\date.png 80x80
	RES_CYCLIC_VIDEO = 0xD5000014,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\cyclic_video.png 80x80
	RES_CHECK_SPORT = 0xD5000015,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\check_sport.png 80x80
	RES_CAR_NUM = 0xD5000016,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\car_num.png 80x80
	RES_GRAVITY_SENSOR = 0xD5000017,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\gravity_sensor.png 80x80
	RES_HDR = 0xD5000018,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\HDR.png 80x80
	RES_INTERVAL_VIDEO = 0xD5000019,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\interval_video.png 80x80
	RES_RESOLUTION_RATIO = 0xD500001A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\resolution_ratio.png 80x80
	RES_SOUND_1 = 0xD500001B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\sound.png 80x80
	RES_STOPPING_MONITOR = 0xD500001C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\stopping_monitor.png 80x80
	RES_AUTO_OFF = 0xD500001D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\auto_off.png 80x80
	RES_CAR_NUM_1 = 0xD500001E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\car_num.png 80x80
	RES_FLIG = 0xD500001F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\flig.png 80x80
	RES_FORMAT = 0xD5000020,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\format.png 80x80
	RES_FREQUENCY = 0xD5000021,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\frequency.png 80x80
	RES_LANE = 0xD5000022,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\lane.png 80x80
	RES_LANGUAGES = 0xD5000023,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\languages.png 80x80
	RES_LCD_OFF = 0xD5000024,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\lcd_off.png 80x80
	RES_RESET = 0xD5000025,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\reset.png 80x80
	RES_VERSION = 0xD5000026,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\version.png 80x80
	RES_VOICE = 0xD5000027,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\voice.png 80x80
	RES_DATE_1 = 0xD5000028,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\date.png 80x80
	RES_AWB = 0xD5000029,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\awb.png 48x48
	RES_AWB_FLUORESCENT_LAMP = 0xD500002A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\awb_fluorescent_lamp.png 48x48
	RES_AWB_OSRAM_LAMP = 0xD500002B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\awb_osram_lamp.png 48x48
	RES_AWB_SUN_CLOUDY = 0xD500002C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\awb_sun_cloudy.png 48x48
	RES_AWB_SUN_LIGHT = 0xD500002D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\awb_sun_light.png 48x48
	RES_HIGH = 0xD500002E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\high.png 48x48
	RES_LOW = 0xD500002F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\low.png 48x48
	RES_MIDDLE = 0xD5000030,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\middle.png 48x48
	RES_TIMING_PHOTO_2 = 0xD5000031,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\timing_photo_2.png 48x48
	RES_TIMING_PHOTO_5 = 0xD5000032,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\timing_photo_5.png 48x48
	RES_TIMING_PHOTO_10 = 0xD5000033,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\timing_photo_10.png 48x48
	RES_FILE_DIR = 0xD5000034,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\file_dir.png 160x160
	RES_DELETE = 0xD5000035,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\DELETE.png 48x48
	RES_DELETE_ON = 0xD5000036,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\delete_on.png 48x48
	RES_EDIT = 0xD5000037,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\EDIT.png 48x48
	RES_EDITOR_ON = 0xD5000038,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\editor_on.png 48x48
	RES_HOME = 0xD5000039,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\HOME.png 48x48
	RES_HOME_ON = 0xD500003A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\home_on.png 48x48
	RES_LOCK = 0xD500003B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LOCK.png 48x48
	RES_LOCK_ON = 0xD500003C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\lock_on.png 48x48
	RES_PHOTO = 0xD500003D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\PHOTO.png 48x48
	RES_PHOTO_ON = 0xD500003E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\photo_on.png 48x48
	RES_RETURN = 0xD500003F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\RETURN.png 48x48
	RES_RETURN_ON = 0xD5000040,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\return_on.png 48x48
	RES_SELETE = 0xD5000041,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\SELETE.png 48x48
	RES_UNLOCK = 0xD5000042,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\UNLOCK.png 48x48
	RES_UNLOCK_ON = 0xD5000043,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\unlock_on.png 48x48
	RES_VIDEO = 0xD5000044,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\VIDEO.png 48x48
	RES_VOLUMELOUDER_SOLID_1 = 0xD5000045,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\volumeLouder_solid_1.png 48x48
	RES_VIDEO_PAUSE = 0xD5000046,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_pause.png 48x48
	RES_SKIP_NEXT = 0xD5000047,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\skip_next.png 48x48
	RES_SKIP_PREVIOUS = 0xD5000048,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\skip_previous.png 48x48
	RES_PLAY = 0xD5000049,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\play.png 32x32
	RES_VIDEO_PLAY = 0xD500004A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_play.png 48x48
	RES_VOLUMEMUTE_SOLID_1 = 0xD500004B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\volumeMute_solid_1.png 48x48
	RES_SOFTWARE = 0xD500004C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\software.png 80x80
	RES_LOCK_FLAG = 0xD500004D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\lock_flag.png 24x24
	RES_CYCLIC_VIDEO_10 = 0xD500004E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_10.png 29x31
	RES_CYCLIC_VIDEO_3 = 0xD500004F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_3.png 29x31
	RES_CYCLIC_VIDEO_5 = 0xD5000050,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_5.png 29x31
	RES_MIC_OFF = 0xD5000051,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\mic_off.png 26x29
	RES_MIC_ON = 0xD5000052,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\mic_on.png 26x29
	RES_I_GRA_H = 0xD5000053,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_h.png 34x31
	RES_I_GRA_M = 0xD5000054,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_m.png 34x31
	RES_I_GRA_L = 0xD5000055,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_l.png 34x31
	RES_BAT_0 = 0xD5000056,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_0.png 25x15
	RES_BAT_L = 0xD5000057,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_l.png 25x15
	RES_BAT_HALF = 0xD5000058,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_half.png 25x15
	RES_BAT_H = 0xD5000059,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_h.png 25x15
	RES_CHAR = 0xD500005A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\char.png 25x15
	RES_CARD_OFFLINE = 0xD500005B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_offline.png 29x29
	RES_CARD_ONLINE = 0xD500005C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_online.png 29x29
	RES_PARK = 0xD500005D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\park.png 16x13
	RES_EXP_A3 = 0xD500005E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a3.png 29x29
	RES_EXP_A2 = 0xD500005F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a2.png 29x29
	RES_EXP_A1 = 0xD5000060,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a1.png 29x29
	RES_EXP_A0 = 0xD5000061,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a0.png 29x29
	RES_EXP_D1 = 0xD5000062,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_d1.png 29x29
	RES_EXP_D2 = 0xD5000063,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_d2.png 29x29
	RES_EXP_D3 = 0xD5000064,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_d3.png 29x29
	RES_AWB_AUTO = 0xD5000065,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_auto.png 29x29
	RES_AWB_CLOUDY = 0xD5000066,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_cloudy.png 29x29
	RES_AWB_FINE = 0xD5000067,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_fine.png 29x29
	RES_AWB_FLUORESCENT_LAMP_1 = 0xD5000068,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_fluorescent_lamp.png 29x29
	RES_AWB_TUNGSTEN_LAMP = 0xD5000069,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_tungsten_lamp.png 29x29
	RES_ISO_1 = 0xD500006A,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_1.png 29x29
	RES_ISO_2 = 0xD500006B,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_2.png 29x29
	RES_ISO_4 = 0xD500006C,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_4.png 29x29
	RES_ISO_AUTO = 0xD500006D,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_auto.png 29x29
	RES_Q1 = 0xD500006E,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q1.png 29x29
	RES_Q2 = 0xD500006F,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q2.png 29x29
	RES_Q3 = 0xD5000070,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q3.png 29x29
	RES_DL2 = 0xD5000071,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl2.png 29x29
	RES_DL5 = 0xD5000072,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl5.png 29x29
	RES_DL10 = 0xD5000073,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl10.png 29x29
	RES_SHAKE_OFF = 0xD5000074,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\shake_off.png 29x29
	RES_SHAKE_ON = 0xD5000075,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\shake_on.png 29x29
	RES_BAT_FULL = 0xD5000076,   //H:\WL83\jxc\2.2.2\fw-AC792_SDK\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_full.png 25x15
} RES_ID;

extern char * gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

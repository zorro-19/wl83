#ifndef __VIDEO_REC_H_
#define __VIDEO_REC_H_

#include "system/includes.h"
#include "server/video_server.h"
#include "app_config.h"

enum VIDEO_REC_STA {
    VIDREC_STA_IDLE,
    VIDREC_STA_START,
    VIDREC_STA_STARTING,
    VIDREC_STA_STOP,
    VIDREC_STA_STOPING,
    VIDREC_STA_FORBIDDEN,
};

enum vrec_err_code {
    VREC_ERR_NONE,
    VREC_ERR_V0_SERVER_OPEN,
    VREC_ERR_V1_SERVER_OPEN,
    VREC_ERR_V2_SERVER_OPEN,
    VREC_ERR_V3_SERVER_OPEN,
    VREC_ERR_START_FREE_SPACE,
    VREC_ERR_SAVE_FREE_SPACE,

    VREC_ERR_REQ_START,
    VREC_ERR_V0_REQ_START,
    VREC_ERR_V1_REQ_START,
    VREC_ERR_V2_REQ_START,
    VREC_ERR_V3_REQ_START,
    VREC_ERR_V0_REQ_STOP,
    VREC_ERR_V1_REQ_STOP,
    VREC_ERR_V2_REQ_STOP,
    VREC_ERR_V3_REQ_STOP,
    VREC_ERR_V0_REQ_SAVEFILE,
    VREC_ERR_V1_REQ_SAVEFILE,
    VREC_ERR_V2_REQ_SAVEFILE,
    VREC_ERR_V3_REQ_SAVEFILE,

    VREC_ERR_PKG,
    VREC_ERR_MKDIR,
    VREC_ERR_UVC_OFFLINE,
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

#ifdef CONFIG_VIDEO4_ENABLE
enum {
    DISP_MAIN_WIN  = 0, //大小窗
    DISP_HALF_WIN,      //各半屏
    DISP_VIDEO0,
    DISP_VIDEO1,
    DISP_VIDEO2,
    DISP_VIDEO3,
    DISP_PARK_WIN,      //parking win
    DISP_RESET_WIN,
    DISP_FORBIDDEN,     //forbidden
    DISP_MAX_WIN   = DISP_FORBIDDEN,
};
#else
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
#endif




struct video_rec_sys_info {

    u32 ctime;
    u32 tlp_time;
    u8 pixel_sel;
    u8 photo_pixel_sel;
    u8 osd_on;
    u8 voice_on;
    u8 ctime_sel;
    u8 mdet_on;
    u8 tlp_time_sel;
    u8 park_guad;
    s8 exposure_val;
    s8 wb_val;
    u8 double_rec;

};


struct video_menu_sta {

    char video_resolution;
    char video_double_route;
    char video_mic;
    char video_gravity;
    char video_motdet;
    char video_park_guard;
    char video_wdr;
    char video_cycle_rec;
    char video_net;
    char video_car_num;
    char video_dat_label;
    char video_white_balance;
    char video_exposure;
    char video_gap;
    char car_num_str[20];
};

struct video_rec_hdl {
    enum VIDEO_REC_STA state;
    struct server *ui;
    struct server *video_rec0;
    struct server *video_rec1;
    struct server *video_rec2;
    struct server *video_rec3;
    struct server *video_uvc_rec0;
    struct server *video_uvc_rec1;
    struct server *video_uvc_rec2;
    struct server *video_uvc_rec3;
    struct server *video_display[CONFIG_VIDEO_REC_NUM];
    struct server *video_uvc_display[CONFIG_VIDEO_UVC_REC_NUM];
    struct server *video_engine;


    struct vfscan *fscan[2][CONFIG_VIDEO_REC_NUM];
    struct vfscan *fscan_uvc[2][CONFIG_VIDEO_UVC_REC_NUM];

    u16 file_number[2][CONFIG_VIDEO_REC_NUM];
    u16 file_uvc_number[2][CONFIG_VIDEO_UVC_REC_NUM];
    u16 old_file_number[2][CONFIG_VIDEO_REC_NUM];
    u16 old_file_uvc_number[2][CONFIG_VIDEO_UVC_REC_NUM];

    u32 total_size;
    u32 lock_fsize;

    u8 *video_buf[CONFIG_VIDEO_REC_NUM];
    u8 *video_uvc_buf[CONFIG_VIDEO_UVC_REC_NUM];
    u8 *cap_buf;
    u8 *audio_buf[CONFIG_VIDEO_REC_NUM];
    u8 *audio_uvc_buf[CONFIG_VIDEO_UVC_REC_NUM];

    FILE *file[CONFIG_VIDEO_REC_NUM];
    FILE *file_uvc[CONFIG_VIDEO_UVC_REC_NUM];

    FILE *new_file[CONFIG_VIDEO_REC_NUM];
    FILE *new_file_uvc[CONFIG_VIDEO_UVC_REC_NUM];

    u32 new_file_size[CONFIG_VIDEO_REC_NUM];
    u32 new_file_uvc_size[CONFIG_VIDEO_UVC_REC_NUM];

    char fname[CONFIG_VIDEO_REC_NUM][MAX_FILE_NAME_LEN];
    char fname_uvc[CONFIG_VIDEO_UVC_REC_NUM][MAX_FILE_NAME_LEN];

    u16 park_wait;
    u16 sd_wait;
    u16 char_wait;

    u8 photo_camera_sel;
    u8 exposure_set;
    u8 white_balance_set;

    u8 lock_fsize_count;
    /*u8 avin_dev;*/
    u8 video_online[CONFIG_VIDEO_REC_NUM];
    u8 video_uvc_online[CONFIG_VIDEO_UVC_REC_NUM];
    u8 disp_video_ctrl;
    u8 disp_sw_flag;
    u8 disp_park_sel;
    int uvc_id;
    u8 avin_cnt;
    u8 menu_inout;
    u8 isp_scenes_status;
    u8 gsen_lock;
    u8 ui_get_config;
    u8 disp_state;
    u8 second_disp_dev;

    u16 car_head_y;//lane det parm
    u16 vanish_y;
    u16 len_factor;
    u8  lan_det_setting;

    u16 uvc_width;
    u16 uvc_height;

    u8 user_rec;
    int park_wait_timeout;

    u8 need_restart_rec;

};


struct VideoConfig {
    u8 channel;
    const char *path_main;
    union video_req req;
    struct video_text_osd text_osd;

};









extern u16 AVIN_WIDTH;
extern u16 AVIN_HEIGH;
extern u16 UVC_ENC_WIDTH;
extern u16 UVC_ENC_HEIGH;
extern u16 VIRTUAL_ENC_WIDTH;
extern u16 VIRTUAL_ENC_HEIGH;

extern void video_rec_config_init();
extern int video_rec_set_white_balance();
extern int video_rec_set_exposure(u32 exp);
extern void mic_set_toggle();

extern char video_rec_osd_buf[64] ;

extern void uvc_parking_enable(u8 on);
extern int get_parking_status();
extern u32 get_video_disp_state();


extern int video_rec_control_doing(void);
extern int video_rec_take_photo(void);

extern void ve_server_reopen();
extern void video_rec_fun_restore();


extern struct VideoConfig *get_video_configs(void);
extern int get_config_viedo_num(void);
extern void *get_video_rec_handler(void);
extern int video_rec_state_notify(void);
extern int video_rec_start();
extern int video_rec_stop(u8 close);
extern void assign_video_rec_params(union video_req *req, struct video_text_osd *text_osd, struct VideoConfig *config);
extern int video_rec_savefile(int dev_id);
extern void video_rec_close_file(int dev_id);
extern int video_rec_del_old_file(int dev_id);
#endif



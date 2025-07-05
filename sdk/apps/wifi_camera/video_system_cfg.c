#include "system/includes.h"
/* #include "server/ui_server.h" */
#include "video_system.h"
/* #include "ui/res/resfile.h" */
/* #include "res.h" */

#include "action.h"
/* #include "style.h" */
#include "app_config.h"
#include "storage_device.h"
#include "key_voice.h"
#include "app_database.h"

#ifdef CONFIG_WIFI_ENABLE
#include "server/net_server.h"
#endif



extern struct video_system_hdl sys_handler;
extern int sys_cur_mod;  /* 1:rec, 2:tph, 3:dec, 4:audio, 5:music */
#define __this 	(&sys_handler)




int kvo_set_function(u32 parm)
{
    return 0;
}
int hlight_set_function(u32 parm)
{
    return 0;
}

int fre_set_function(u32 parm)
{
    return 0;
}

int aff_set_function(u32 parm)
{
    sys_power_auto_shutdown_stop();
    sys_power_auto_shutdown_start(parm * 60);
    return 0;
}

extern void ui_lcd_light_time_set(int sec);

int pro_set_function(u32 parm)
{
    ui_lcd_light_time_set(parm);
    return 0;
}

int lag_set_function(u32 parm)
{
    /* ui_language_set(parm); */

    return 0;
}

int tvm_set_function(u32 parm)
{
    return 0;
}

int frm_set_function(u32 parm)
{
    int err;

    key_event_disable();
    /* touch_event_disable(); */

    /* err = storage_device_format(); */

#ifdef CONFIG_WIFI_ENABLE
    net_video_rec_fmt_notify();
#endif

    key_event_enable();
    /* touch_event_enable(); */

    return err;
}

u8 get_default_setting_st()
{
    return	(__this->default_set);
}

void clear_default_setting_st()
{
    __this->default_set = 0;
}

static int def_set_function(u32 parm)
{
    puts("def_set_function\n");
    __this->default_set = 1;
    /* db_reset(); */
    /* os_time_dly(200); */
    /* cpu_reset(); */
    sys_fun_restore();

    return 0;
}

static int lane_det_set_function(u32 parm)
{


    return 0;
}

/*
 * 在此处添加所需配置即可
 */
const static struct app_cfg cfg_table[] = {
    {"kvo", kvo_set_function},
    {"fre", fre_set_function},
    {"aff", aff_set_function},
    {"pro", pro_set_function},
    {"lag", lag_set_function},
    {"tvm", tvm_set_function},
    {"frm", frm_set_function},
    {"def", def_set_function},
    {"hlw", hlight_set_function},
    {"lan", lane_det_set_function },
};

void sys_fun_restore()
{
    aff_set_function(db_select("aff"));
    pro_set_function(db_select("pro"));
    lag_set_function(db_select("lag"));
}


/*
 * 被请求设置参数
 */
int video_sys_set_config(struct intent *it)
{

    ASSERT(it != NULL);
    ASSERT(it->data != NULL);

    return app_set_config(it, cfg_table, ARRAY_SIZE(cfg_table));
}


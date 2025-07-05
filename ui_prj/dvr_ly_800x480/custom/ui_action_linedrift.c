/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#include "custom.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_config.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"
#include "ui.h"
#include "sys_time.h"
#endif


#if !LV_USE_GUIBUILDER_SIMULATOR

 //注册页面加载卸载回调
int gui_src_action_lane(int action)
{
	struct intent it;
	struct application* app;

	init_intent(&it);
	app = get_current_app();

	printf("[chili] %s %d   \n", __func__, __LINE__);

	switch (action) {
	case GUI_SCREEN_ACTION_LOAD:
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(guider_ui.line_drift, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(guider_ui.line_drift, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        if (app) {
            printf("[chili] %s %d   \n", app->name, __LINE__);
            it.name = app->name;//APP状态机在：video_rec.c
            it.action = ACTION_BACK;
            start_app(&it);
        }
        it.name = "video_rec";//APP状态机在：video_rec.c
        it.action = ACTION_VIDEO_REC_MAIN;
        start_app(&it);
		break;
	case GUI_SCREEN_ACTION_UNLOAD:
        if (app) {
            printf("[chili] %s %d   \n", app->name, __LINE__);
            it.name = app->name;//APP状态机在：video_rec.c
            it.action = ACTION_BACK;
            start_app(&it);
        }
		break;
	}
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_LINE_DRIFT)
.onchange = gui_src_action_lane,
};

#endif

 /*
 * 显示车道偏移设置页面
 *
 */
void line_drift_page_show(int arg)
{
    printf("[chili]: %s %d\n", __func__, __LINE__);
    gui_scr_t* screen = gui_scr_get(GUI_SCREEN_LINE_DRIFT);
    if (screen == NULL) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        screen = gui_scr_create(GUI_SCREEN_LINE_DRIFT, "line_drift", guider_ui.line_drift, (gui_scr_setup_cb_t)setup_scr_line_drift, (gui_scr_unload_cb_t)unload_scr_line_drift);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);//不压栈


}

/*
*
* 隐藏车道偏移设置页面跳转到系统设置页面
*
*/
void line_drift_page_hide(int arg)
{

    printf("[chili]: %s %d\n", __func__, __LINE__);

    gui_scr_t* screen = gui_scr_get(GUI_SCREEN_SYS_SETTING);
    if (screen == NULL) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        screen = gui_scr_create(GUI_SCREEN_SYS_SETTING, "sys_setting", guider_ui.sys_setting, (gui_scr_setup_cb_t)setup_scr_sys_setting, (gui_scr_unload_cb_t)unload_scr_sys_setting);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);

}

#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "../gui_guider.h"
#include "lvgl.h"
#include "./callback_handler.h"

// Generate video_rec_timer_1 CallBack Handler
void video_rec_timer_1_timer_cb(lv_timer_t *src)
{
    extern int video_rec_record_time();
    lvgl_rpc_post_func(video_rec_record_time, 0);

    if (src->repeat_count == 0) {
        guider_ui.video_rec_timer_1 = NULL;
    }
}
// Generate video_play_hide_bar CallBack Handler
void video_play_hide_bar_timer_cb(lv_timer_t *src)
{
    if (lv_obj_is_valid(guider_ui.video_play_view_1)) {
        lv_obj_add_flag(guider_ui.video_play_view_1, LV_OBJ_FLAG_HIDDEN);
    }
    if (guider_ui.video_play_hide_bar) {
        lv_timer_del(guider_ui.video_play_hide_bar);
        guider_ui.video_play_hide_bar = NULL;
    }


    if (src->repeat_count == 0) {
        guider_ui.video_play_hide_bar = NULL;
    }
}
// Generate video_play_hide_label CallBack Handler
void video_play_hide_label_timer_cb(lv_timer_t *src)
{
    if (guider_ui.video_play_hide_label) {
        lv_timer_del(guider_ui.video_play_hide_label);
        guider_ui.video_play_hide_label = NULL;
    }


    if (src->repeat_count == 0) {
        guider_ui.video_play_hide_label = NULL;
    }
}

#endif

#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "../gui_guider.h"
#include "lvgl.h"
#include "./callback_handler.h"

// Generate video_rec_timer_1 CallBack Handler
void video_rec_timer_1_timer_cb(lv_timer_t * src)
{
	lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, NULL, 0, 0);
	printf("enter time cb send msg\n");
	
	if (src->repeat_count == 0) {
		guider_ui.video_rec_timer_1 = NULL;
	}
}

#endif

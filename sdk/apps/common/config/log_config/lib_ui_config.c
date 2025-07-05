#include "generic/typedef.h"
#include "app_config.h"

#ifdef CONFIG_UI_ENABLE

const uint8_t lv_jlffmpeg_debug_time = 0;    //读卡时间debug
const uint8_t lv_jlffmpeg_use_frame_ctl = 1; //使用avi实际帧率
const uint8_t frame_control_sens = 0;        //灵敏度设置:单位ms,作用是减小帧率波动极值
const char log_tag_const_v_JLFFMPEG AT(.LOG_TAG_CONST) = CONFIG_DEBUG_LIB(FALSE);
const char log_tag_const_d_JLFFMPEG AT(.LOG_TAG_CONST) = CONFIG_DEBUG_LIB(FALSE);
const char log_tag_const_i_JLFFMPEG AT(.LOG_TAG_CONST) = CONFIG_DEBUG_LIB(FALSE);
const char log_tag_const_w_JLFFMPEG AT(.LOG_TAG_CONST) = CONFIG_DEBUG_LIB(FALSE);
const char log_tag_const_e_JLFFMPEG AT(.LOG_TAG_CONST) = CONFIG_DEBUG_LIB(TRUE);

#endif



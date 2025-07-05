
#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void custom_init(lv_ui *ui);
void hide_label_timer_cb(lv_timer_t *timer);
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */

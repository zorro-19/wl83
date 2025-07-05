#include "app_config.h"
#include "gui_guider.h"

lv_ui guider_ui;

#if DEV_HARDWARE_VERIFY_UI_ENABLE
void jl_gui_init(void)
{
    setup_ui(&guider_ui);
    events_init(&guider_ui);
}

#endif


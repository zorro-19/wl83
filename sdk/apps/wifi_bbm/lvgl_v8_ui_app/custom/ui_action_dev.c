#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#define LOCAL_PATH "storage/sd0/C/DCIM/"

static char dev_path[64];

// 0:local  1:remote
void gui_bbm_set_cur_dev_path(int dev)
{
    if (dev == 0) {
        strcpy(dev_path, LOCAL_PATH);
    } else {
        memset(dev_path, 0x00, sizeof(dev_path));
    }
}

//local: storage/....
//remote: 000000000000
char *gui_bbm_get_cur_dev_path(void)
{
    return dev_path;
}






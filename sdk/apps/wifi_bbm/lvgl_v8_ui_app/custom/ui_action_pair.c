#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

static uint8_t cur_pair_channel;
static int is_cancel_option = 0;
static int cancel_wifi_channel = 0;

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#ifdef USE_ADDITIONAL_CHANNELS
//23->2360， 24->2370， 25->2380，26->2390
const int wifi_channel_table[4] = {23, 24, 25, 26};
#else
//1-13
const int wifi_channel_table[4] = {1, 6, 11, 13};
#endif

void set_cur_pair_channel(uint8_t channel)
{
    cur_pair_channel = channel;
}

uint8_t get_cur_pair_channel(void)
{
    return cur_pair_channel;
}


#if !LV_USE_GUIBUILDER_SIMULATOR

void post_pair_msg_to_ui(const char *msg)
{
    printf("post msg :%s \n", msg);

    if (!strcmp(msg, "pair success")) {
        char *lab = lvgl_module_msg_get_ptr(GUI_PAIR_MSG_ID_PARING_LAB, 50);
        sprintf(lab, "Pair Success! \n\nPlease click to return");
        lvgl_module_msg_send_ptr(lab, 0);
    } else {
        printf("Unknow Msg\n");
    }
}

//返回0未配对/返回1已配对
int gui_get_bbm_pair_status(uint8_t ch)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_GET_PAIR_STATUS;
    it.exdata = ch;
    start_app(&it);

    return it.exdata;
}

int gui_set_bbm_enter_pairing(uint8_t ch)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_ENTER_PAIRING;
    it.exdata = ch;
    start_app(&it);

    return 0;
}

int gui_set_bbm_exit_pairing(void)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_EXIT_PAIRING;
    start_app(&it);

    return 0;
}

int gui_set_bbm_unpair(uint8_t ch)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_UNPAIR;
    it.exdata = ch;
    start_app(&it);

    return 0;
}

static void gui_bbm_pair_confirm_wifi_ch(void)
{
    //清空配对表
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_CLEAN_PAIR;
    start_app(&it);

    int wifi_channel;
    if (syscfg_read(BBM_WIFI_CH_INDEX, &wifi_channel, sizeof(wifi_channel))) {
        wifi_set_channel(wifi_channel);
    }

    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_PAIR_CH0, 0, 0);
    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_PAIR_CH1, 0, 0);
    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_PAIR_CH2, 0, 0);
    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_PAIR_CH3, 0, 0);
    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_PAIR_CH4, 0, 0);
    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_PAIR_CH5, 0, 0);
}

static void gui_bbm_pair_cancel_wifi_ch(void)
{
    int index;
    is_cancel_option = 1;

    for (index = 0; index < ARRAY_SIZE(wifi_channel_table); index++) {
        if (cancel_wifi_channel == wifi_channel_table[index]) {
            break;
        }
    }

    lvgl_module_msg_send_value(GUI_PAIR_MSG_ID_WIFI_CH_SELECT, index, 1);
}

int gui_set_bbm_wifi_channel(void)
{
    char lab[128];
    sprintf(lab, "This will disconnect all connections. \nAre you sure you want to do this?");
    gui_set_sys_options_yes_cb(gui_bbm_pair_confirm_wifi_ch);
    gui_set_sys_options_no_cb(gui_bbm_pair_cancel_wifi_ch);
    post_home_msg_to_ui("show_sys_options", lab);
}

int gui_pair_msg_pair_ch0_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(0);
    }
    data->value_int = pair_ch_var;
    return 0;
}

int gui_pair_msg_pair_ch1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(1);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(2);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(3);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(4);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(5);
    }
    data->value_int = pair_ch_var;
    return 0;
}


int gui_pair_msg_paring_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        uint8_t pair_ch = get_cur_pair_channel();
        int pair_status = gui_get_bbm_pair_status(pair_ch);

        if (pair_status) {
            //已配对.
            data->value_string = "This channel is paired. \n\nPlease click to return !!";
            //返回解除配对后才能配对

        } else {
            //未配对
            data->value_string = "Pairing... \n\nPlease press the pairing button of the camera and Make sure the camera is within 30cm";
            //开启配对
            gui_set_bbm_enter_pairing(pair_ch);
        }
    }

    return 0;
}

int gui_pair_msg_unpair_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        uint8_t pair_ch = get_cur_pair_channel();
        int pair_status = gui_get_bbm_pair_status(pair_ch);

        if (pair_status) {
            //已配对
            data->value_string = "Unpair success ! \n\nPlease click to return";
            //解除配对
            gui_set_bbm_unpair(pair_ch);
        } else {
            //未配对
            data->value_string = "This channel not paired ! \n\nPlease click to return";
            //返回,配对后才能取消配对
        }
    }

    return 0;
}

int gui_pair_msg_wifi_ch_select_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int wifi_channel;
    int ret = 0;
    if (access == GUI_MSG_ACCESS_SET) {

        syscfg_read(BBM_WIFI_CH_INDEX, &cancel_wifi_channel, sizeof(cancel_wifi_channel));

        wifi_channel = wifi_channel_table[data->value_int];

        syscfg_write(BBM_WIFI_CH_INDEX, &wifi_channel, sizeof(wifi_channel));

        if (!is_cancel_option) {
            gui_set_bbm_wifi_channel();
        }
        is_cancel_option = 0;
    }

    if (access == GUI_MSG_ACCESS_GET) {
        syscfg_read(BBM_WIFI_CH_INDEX, &wifi_channel, sizeof(wifi_channel));
        int i;
        for (i = 0; i < ARRAY_SIZE(wifi_channel_table); i++) {
            if (wifi_channel == wifi_channel_table[i]) {
                data->value_int = i;
                break;
            }
        }
    }

    return 0;
}

int gui_pair_msg_ddlist_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int index = 0, wifi_channel = 1;
    static char *ddlist_lab_var = NULL;
    if (!ddlist_lab_var) {
        ddlist_lab_var = lv_mem_alloc(128);
    }

    if (access == GUI_MSG_ACCESS_GET) {
        int i, len;
        char tmp[32];
        memset(ddlist_lab_var, 0x00, 128);
        for (i = 0; i < ARRAY_SIZE(wifi_channel_table); i++) {
            sprintf(tmp, "Channel-%d\n", wifi_channel_table[i]);
            strcat(ddlist_lab_var, tmp);
        }
        /* snprinf(ddlist_lab_var,"Channel-1\nChannel-6\nChannel-13") */
        //去掉最后一个\n
        len = strlen(ddlist_lab_var);
        ddlist_lab_var[len - 1] = '\0';
    }

    data->value_string = ddlist_lab_var;

    return 0;
}


REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH0)
.onchange = gui_pair_msg_pair_ch0_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH1)
.onchange = gui_pair_msg_pair_ch1_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH2)
.onchange = gui_pair_msg_pair_ch2_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH3)
.onchange = gui_pair_msg_pair_ch3_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH4)
.onchange = gui_pair_msg_pair_ch4_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH5)
.onchange = gui_pair_msg_pair_ch5_cb,
};


REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PARING_LAB)
.onchange = gui_pair_msg_paring_lab_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_UNPAIR_LAB)
.onchange = gui_pair_msg_unpair_lab_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_DDLIST_LAB)
.onchange = gui_pair_msg_ddlist_lab_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_WIFI_CH_SELECT)
.onchange = gui_pair_msg_wifi_ch_select_cb,
};
#endif

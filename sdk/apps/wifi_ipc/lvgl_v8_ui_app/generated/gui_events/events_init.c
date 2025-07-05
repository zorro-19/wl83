/*Generate Code, Do NOT Edit!*/
#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "callback_handler.h"
#include "gui_timelines.h"


static int calling_now = 0;//当前是否远程对讲

/* 设置列表按钮文字内容
* btn 列表项
* item_str 需要设置的字符串
*/
static void lv_list_set_btn_text(lv_obj_t *btn, char *item_str)
{
    uint32_t i;

    for (i = 0; i < lv_obj_get_child_cnt(btn); i++) {
        lv_obj_t *child = lv_obj_get_child(btn, i);
        if (lv_obj_check_type(child, &lv_label_class)) {
            return lv_label_set_text(child, item_str);
        }

    }

}
static int16_t index_sysinfo = 0;
#if LV_USE_GUIBUILDER_SIMULATOR == 0
#include "syscfg/syscfg_id.h"
#endif // LV_USE_GUIBUILDER_SIMULATOR
extern lv_group_t *adkey_group;

enum {
    MENU_ITEM_APP = 1,
    MENU_ITEM_LANGUAGE,
    MENU_ITEM_SYSSET,
    MENU_ITEM_SYSINFO,
};
static int16_t index_language = 0;
void events_init(lv_ui *ui)
{
}

static void start_img_logo_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    default:
        break;
    }
    // LV_EVENT_ALL
    {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_FADE_OUT, 300, 2600, false, true, false);
    }
}

void events_init_start(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->start_img_logo, start_img_logo_event_handler, LV_EVENT_ALL, ui);
}

static void home_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            extern void home_timer_create(void);
            home_timer_create();
#endif
        }
    }
    break;
    case LV_EVENT_SCREEN_UNLOADED: {
        //custom code
        {
            lv_obj_t *dest = src;
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            extern void home_timer_delete(void);
            home_timer_delete();
#endif
        }
    }
    break;
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_DOWN) {
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
            }
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void home_img_funkey1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code home_img_funkey1
        {
            lv_obj_t *dest = ui->home_img_funkey1;

            {
#if LV_USE_GUIBUILDER_SIMULATOR
                printf("[chili] %s %d   \n",  __func__, __LINE__);
#else
                static int32_t keyfun1_var = RES_ICON_CALL_OUT;
                static int32_t keyfun2_var = RES_ICON_CALL_OUT;
                static int32_t keyfun3_var = RES_ICON_CALL_OUT;
                if (!calling_now) {
                    calling_now = 1;
                    //change icon & note
                    keyfun1_var = RES_ICON_LOUDSPEAKER_OFF;
                    keyfun2_var = RES_ICON_HANGUP;
                    keyfun3_var = RES_IC_MIC_OFF;
                    lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN1, keyfun1_var,  0);
                    lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN2, keyfun2_var,  0);
                    lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN3, keyfun3_var,  0);
                    lv_obj_add_flag(ui->home_lbl_2, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(ui->home_lbl_4, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(ui->home_lbl_5, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(ui->home_lbl_note, LV_OBJ_FLAG_HIDDEN);
                } else { //no calling

                    static int spk_state = 0;
                    if (!spk_state) {
                        keyfun1_var = RES_ICON_LOUDSPEAKER_ON;

                        spk_state = 1;
                    } else {
                        keyfun1_var = RES_ICON_LOUDSPEAKER_OFF;
                        spk_state = 0;
                    }
                    lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN1, keyfun1_var,  0);

                }
#endif
            }


        }
    }
    break;
    default:
        break;
    }
}

static void home_img_funkey3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void home_img_funkey2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code home_img_funkey2
        {
            lv_obj_t *dest = ui->home_img_funkey2;
#if LV_USE_GUIBUILDER_SIMULATOR

            static int MicroPhone = 0;
            printf("[chili] %s %d   \n",  __func__, __LINE__);
            if (!MicroPhone) {
                //lv_img_set_src(ui->home_img_funkey2,&_ic_mic_on_alpha_98x98);
                MicroPhone = 1;
            } else {
                //lv_img_set_src(ui->home_img_funkey2,&_icon_walkie_talkie_alpha_98x98);
                MicroPhone = 0;
            }

#else
            static int32_t keyfun2_var = RES_ICON_WALKIE_TALKIE;
            if (!calling_now) {
                static int MicroPhone = 0;
                if (!MicroPhone) {
                    keyfun2_var = RES_IC_MIC_ON;

                    MicroPhone = 1;
                } else {
                    keyfun2_var = RES_ICON_WALKIE_TALKIE;
                    MicroPhone = 0;
                }
                lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN2, keyfun2_var,  0);
            } else { //hangup
                calling_now = 0;
                //change icon & note

                static int32_t keyfun1_var = RES_ICON_CALL_OUT;
                keyfun2_var = RES_ICON_WALKIE_TALKIE;
                static int32_t keyfun3_var = RES_ICON_RECOVER;
                lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN1, keyfun1_var, 0);
                lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN2, keyfun2_var, 0);
                lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_KEYFUN3, keyfun3_var, 0);

                lv_obj_clear_flag(ui->home_lbl_2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(ui->home_lbl_4, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(ui->home_lbl_5, LV_OBJ_FLAG_HIDDEN);
            }


#endif

        }
    }
    break;
    default:
        break;
    }
}

static void home_img_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_home(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home, home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_img_funkey1, home_img_funkey1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_img_funkey3, home_img_funkey3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_img_funkey2, home_img_funkey2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_img_menu, home_img_menu_event_handler, LV_EVENT_ALL, ui);
}

static void menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_UP) {
            //custom code home
            {
                lv_obj_t *dest = ui->home;


            }
        }
        if (*key == LV_KEY_UP) {
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
            }
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void menu_edit_return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void menu_edit_download_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_APP);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_APP, "app", guider_ui.app, (gui_scr_setup_cb_t)setup_scr_app, (gui_scr_unload_cb_t)unload_scr_app);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void menu_edit_netcfg_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code menu_edit_netcfg
        {
            lv_obj_t *dest = ui->menu_edit_netcfg;
            {
#if LV_USE_GUIBUILDER_SIMULATOR

#else
                int net_qr_start = 1;
                int netcfg_rest = 0;
                syscfg_write(CFG_USER_NET_CFG, &net_qr_start, sizeof(net_qr_start));
                syscfg_write(CFG_USER_NET_CFG_REST, &netcfg_rest, sizeof(netcfg_rest));
#endif
                lv_event_send(guider_ui.menu_edit_return, LV_EVENT_CLICKED, NULL);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void menu_edit_language_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_LANGUAGE);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_LANGUAGE, "language", guider_ui.language, (gui_scr_setup_cb_t)setup_scr_language, (gui_scr_unload_cb_t)unload_scr_language);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void menu_edit_sysset_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_SYSCFG);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_SYSCFG, "syscfg", guider_ui.syscfg, (gui_scr_setup_cb_t)setup_scr_syscfg, (gui_scr_unload_cb_t)unload_scr_syscfg);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void menu_edit_sysinfo_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_SYSINFO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_SYSINFO, "sysinfo", guider_ui.sysinfo, (gui_scr_setup_cb_t)setup_scr_sysinfo, (gui_scr_unload_cb_t)unload_scr_sysinfo);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_menu(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu, menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_edit_return, menu_edit_return_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_edit_download, menu_edit_download_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_edit_netcfg, menu_edit_netcfg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_edit_language, menu_edit_language_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_edit_sysset, menu_edit_sysset_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_edit_sysinfo, menu_edit_sysinfo_event_handler, LV_EVENT_ALL, ui);
}

static void language_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_UP) {
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
            }
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
        }
        if (*key == LV_KEY_DOWN) {
            //custom code language_list_language
            {
                lv_obj_t *dest = ui->language_list_language;
                lv_obj_t *item = lv_obj_get_child(dest, index_language);
                int16_t child_cnt = lv_obj_get_child_cnt(dest); // 获取列表项的总数
                // 处理 "NextItem" 按键事件
                if (item != NULL) {
                    lv_obj_clear_state(item, LV_STATE_FOCUSED);
                    lv_obj_add_state(item, LV_STATE_DEFAULT);
                }
                index_language = (index_language + 1) % child_cnt; // 循环到下一个列表项，到达底部
                item = lv_obj_get_child(dest, index_language);
                if (item != NULL) {
                    // 设置当前项为聚焦状态
                    lv_obj_add_state(item, LV_STATE_FOCUSED);
                }


            }
        }
        if (*key == LV_KEY_ENTER) {
            //custom code language_list_language
            {
                lv_obj_t *dest = ui->language_list_language;
                // 处理 "Select" 按键事件
                lv_obj_t *item = lv_obj_get_child(dest, index_language);
                if (item != NULL) {
                    lv_obj_clear_state(item, LV_STATE_FOCUSED);
                    lv_obj_add_state(item, LV_STATE_DEFAULT);
                    // 执行点击事件
                    lv_event_send(item, LV_EVENT_CLICKED, NULL);
                    // 重新设置焦点状态
                    lv_obj_add_state(item, LV_STATE_FOCUSED);
                }

            }
        }
    }
    break;
    default:
        break;
    }
}

static void language_btn_return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void language_list_language_item1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code language_list_language
        {
            lv_obj_t *dest = ui->language_list_language;
            int now_item_id = 1;
            static int switch_status = 0;

            lv_obj_t *item = lv_obj_get_child(dest, now_item_id);
            if (item != NULL) {
                if (!switch_status) {
                    switch_status = 1;
                    lv_list_set_btn_text(item, "    中文                                   已设置");
                    lv_i18n_set_locale("zh_cn");
                } else {
                    switch_status = 0;
                    lv_list_set_btn_text(item, "    中文                                    设置");
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void language_list_language_item2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code language_list_language
        {
            lv_obj_t *dest = ui->language_list_language;
            int now_item_id = 2;
            static int switch_status = 0;

            lv_obj_t *item = lv_obj_get_child(dest, now_item_id);
            if (item != NULL) {
                if (!switch_status) {
                    switch_status = 1;
                    lv_list_set_btn_text(item, "    英文                                   已设置");
                    lv_i18n_set_locale("en");
                } else {
                    switch_status = 0;
                    lv_list_set_btn_text(item, "    英文                                    设置");
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void language_list_language_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_language(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->language, language_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->language_btn_return, language_btn_return_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->language_list_language_item1, language_list_language_item1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->language_list_language_item2, language_list_language_item2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->language_list_language_item0, language_list_language_item0_event_handler, LV_EVENT_ALL, ui);
}

static void app_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_UP) {
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
            }
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void app_btn_return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_app(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->app, app_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->app_btn_return, app_btn_return_event_handler, LV_EVENT_ALL, ui);
}

static void syscfg_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_UP) {
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
            }
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
        }
        if (*key == LV_KEY_DOWN) {
            //custom code syscfg_list_sysset
            {
                lv_obj_t *dest = ui->syscfg_list_sysset;
                lv_obj_t *item = lv_obj_get_child(dest, index_sysinfo);
                int16_t child_cnt = lv_obj_get_child_cnt(dest); // 获取列表项的总数
                // 处理 "NextItem" 按键事件
                if (item != NULL) {
                    lv_obj_clear_state(item, LV_STATE_FOCUSED);
                    lv_obj_add_state(item, LV_STATE_DEFAULT);
                }
                index_sysinfo = (index_sysinfo + 1) % child_cnt; // 循环到下一个列表项，到达底部
                item = lv_obj_get_child(dest, index_sysinfo);
                if (item != NULL) {
                    // 设置当前项为聚焦状态
                    lv_obj_add_state(item, LV_STATE_FOCUSED);
                }
            }
        }
        if (*key == LV_KEY_ENTER) {
            //custom code syscfg_list_sysset
            {
                lv_obj_t *dest = ui->syscfg_list_sysset;
                lv_obj_t   *item = lv_obj_get_child(dest, index_sysinfo);
                if (item != NULL) {
                    lv_obj_clear_state(item, LV_STATE_FOCUSED);
                    lv_obj_add_state(item, LV_STATE_DEFAULT);
                    // 执行点击事件
                    lv_event_send(item, LV_EVENT_CLICKED, NULL);
                    // 重新设置焦点状态
                    lv_obj_add_state(item, LV_STATE_FOCUSED);
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

static void syscfg_btn_return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void syscfg_list_sysset_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

static void syscfg_list_sysset_item1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code syscfg_list_sysset
        {
            lv_obj_t *dest = ui->syscfg_list_sysset;
            int now_item_id = 1;
#ifdef CONFIG_AUTO_SHUTDOWN_ENABLE
            unsigned char auto_off_time = 0;
            syscfg_read(CFG_USER_POWER_OFF, &auto_off_time, sizeof(auto_off_time));
            switch (auto_off_time) {
            case 15:
                auto_off_time = 30;
                break;
            case 30:
                auto_off_time = 60;
                break;
            case 60:
                auto_off_time = 15;
                break;
            default:
                auto_off_time = 15;
                break;
            }
            printf("[chili] %s auto_off_time %d   \n",  __func__, auto_off_time);
            syscfg_write(CFG_USER_POWER_OFF, &auto_off_time, sizeof(auto_off_time));
            sys_power_auto_shutdown_start(auto_off_time);
            char str_buf[64];
            lv_obj_t *item = lv_obj_get_child(dest, now_item_id);
            if (item != NULL) {
                sprintf(str_buf, "   休眠时长                               %dsec", auto_off_time);
                if (!auto_off_time) {
                    memcpy(str_buf, "   休眠时长                                永不", strlen("   休眠时长                                永不") + 1);
                }
                lv_list_set_btn_text(item, str_buf);
            }
#else
            static unsigned char auto_off_time = 0;
            switch (auto_off_time) {
            case 15:
                auto_off_time = 30;
                break;
            case 30:
                auto_off_time = 60;
                break;
            case 60:
                auto_off_time = 15;
                break;
            default:
                auto_off_time = 15;
                break;
            }
            char str_buf[64];
            lv_obj_t *item = lv_obj_get_child(dest, now_item_id);
            if (item != NULL) {
                sprintf(str_buf, "   休眠时长                               %dsec", auto_off_time);
                if (!auto_off_time) {
                    memcpy(str_buf, "   休眠时长                                永不", strlen("   休眠时长                                永不") + 1);
                }
                lv_list_set_btn_text(item, str_buf);
            }
#endif
        }
    }
    break;
    default:
        break;
    }
}

static void syscfg_list_sysset_item2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code syscfg_list_sysset
        {
            lv_obj_t *dest = ui->syscfg_list_sysset;
            int now_item_id = 2;
            static int weather_show_switch = 0;

            lv_obj_t *item = lv_obj_get_child(dest, now_item_id);
            if (item != NULL) {
                if (!weather_show_switch) {
                    weather_show_switch = 1;
                    lv_list_set_btn_text(item, "   天气显示                        关 ");
                } else {
                    weather_show_switch = 0;
                    lv_list_set_btn_text(item, "   天气显示                        开 ");
                }
            }
        }
    }
    break;
    default:
        break;
    }
}

void events_init_syscfg(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->syscfg, syscfg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->syscfg_btn_return, syscfg_btn_return_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->syscfg_list_sysset_item0, syscfg_list_sysset_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->syscfg_list_sysset_item1, syscfg_list_sysset_item1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->syscfg_list_sysset_item2, syscfg_list_sysset_item2_event_handler, LV_EVENT_ALL, ui);
}

static void sysinfo_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_KEY: {
        uint32_t *key = lv_event_get_param(e);
        if (*key == LV_KEY_UP) {
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
            }
            ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void sysinfo_btn_return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_MENU);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_MENU, "menu", guider_ui.menu, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
    }
    break;
    default:
        break;
    }
}

void events_init_sysinfo(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->sysinfo, sysinfo_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->sysinfo_btn_return, sysinfo_btn_return_event_handler, LV_EVENT_ALL, ui);
}

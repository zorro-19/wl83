#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".adv_bt_name_setting.data.bss")
#pragma data_seg(".adv_bt_name_setting.data")
#pragma const_seg(".adv_bt_name_setting.text.const")
#pragma code_seg(".adv_bt_name_setting.text")
#endif
#include "app_config.h"
#include "user_cfg.h"
#include "syscfg_id.h"
#include "ble_rcsp_server.h"

#include "rcsp_setting_opt.h"

#if (RCSP_MODE && RCSP_ADV_EN && RCSP_ADV_NAME_SET_ENABLE)

static u8 g_edr_name[32] = {0};

extern int get_bt_tws_connect_status();

void adv_edr_name_change_now(void)
{
    printf("=====================%s=%d=yuring=\n\r", __func__, __LINE__);
#if 0 //RCSP TODO
    extern BT_CONFIG bt_cfg;
    extern const char *bt_get_local_name();
    extern void lmp_hci_write_local_name(const char *name);
    memcpy(bt_cfg.edr_name, g_edr_name, LOCAL_NAME_LEN);
    lmp_hci_write_local_name(bt_get_local_name());
#endif
}

static void set_bt_name_setting(u8 *bt_name_setting)
{
    memcpy(g_edr_name, bt_name_setting, 32);
}

static int get_bt_name_setting(u8 *bt_name_setting)
{
    memcpy(bt_name_setting, g_edr_name, 32);
    return 0;
}

// 1、写入VM
static void update_bt_name_vm_value(u8 *bt_name_setting)
{
    syscfg_write(CFG_BT_NAME, bt_name_setting, 32);
}
// 2、同步对端
static void bt_name_sync(u8 *bt_name_setting)
{
#if TCFG_USER_TWS_ENABLE
    if (get_bt_tws_connect_status()) {
        update_rcsp_setting(ATTR_TYPE_EDR_NAME);
    }
#endif
}

static void deal_bt_name_setting(u8 *bt_name_setting, u8 write_vm, u8 tws_sync)
{
    if (!bt_name_setting) {
        get_bt_name_setting(g_edr_name);
    } else {
        memcpy(g_edr_name, bt_name_setting, 32);
    }
    if (write_vm) {
        update_bt_name_vm_value(g_edr_name);
    }
    if (tws_sync) {
        bt_name_sync(g_edr_name);
    }
}

static int bt_name_set_setting_extra_handle(void *setting_data, void *setting_data_len)
{
    int ret = 0;
    u8 dlen = *((u8 *)setting_data_len);
    u8 *bt_name_setting_data = (u8 *) setting_data;
    u8 bt_name[32] = {0};
    if (dlen > 20) {
        ret = 2;
    } else {
        memcpy(bt_name, bt_name_setting_data, dlen);
        bt_name[dlen] = '\0';
        memcpy(g_edr_name, bt_name, sizeof(bt_name));
    }
    return ret;
}

static int bt_name_get_setting_extra_handle(void *setting_data, void *setting_data_len)
{
    int **setting_data_ptr = (int **)setting_data;
    *setting_data_ptr = (int *)g_edr_name;
    return strlen((const char *)g_edr_name);
}

static RCSP_SETTING_OPT adv_bt_name_opt = {
    .data_len = 32,
    .setting_type =	ATTR_TYPE_EDR_NAME,
    .syscfg_id = CFG_BT_NAME,
    .deal_opt_setting = deal_bt_name_setting,
    .set_setting = set_bt_name_setting,
    .get_setting = get_bt_name_setting,
    .custom_setting_init = NULL,
    .custom_vm_info_update = NULL,
    .custom_setting_update = NULL,
    .custom_sibling_setting_deal = NULL,
    .custom_setting_release = NULL,
    .set_setting_extra_handle = bt_name_set_setting_extra_handle,
    .get_setting_extra_handle = bt_name_get_setting_extra_handle,
};

REGISTER_APP_SETTING_OPT(adv_bt_name_opt);

#else

void adv_edr_name_change_now(void)
{

}


#endif

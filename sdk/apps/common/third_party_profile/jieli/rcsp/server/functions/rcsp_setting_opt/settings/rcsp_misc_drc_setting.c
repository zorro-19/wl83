#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_misc_drc_setting.data.bss")
#pragma data_seg(".rcsp_misc_drc_setting.data")
#pragma const_seg(".rcsp_misc_drc_setting.text.const")
#pragma code_seg(".rcsp_misc_drc_setting.text")
#endif
#include "app_config.h"
#include "syscfg_id.h"

#include "rcsp_misc_setting.h"
#include "ble_rcsp_server.h"
#include "node_param_update.h"

#if (RCSP_MODE && RCSP_DRC_VAL_SETTING &&  TCFG_LIMITER_NODE_ENABLE && RCSP_ADV_EQ_SET_ENABLE)


static s16 drc_val = 0;

static int drc_setting_set(u8 *misc_setting, u8 is_conversion)
{
    u32 offset = 0;
    if (is_conversion) {
        drc_val = misc_setting[0] << 8 | misc_setting[1];
        offset += 2;
        drc_val = drc_val < 0 ? (drc_val + 61) : drc_val;
    } else {
        memcpy((u8 *)&drc_val, misc_setting, sizeof(drc_val));
        offset += 2;
    }
    return offset;
}

static int drc_setting_get(u8 *misc_setting, u8 is_conversion)
{
    u32 offset = 0;
    if (is_conversion) {
        drc_val = drc_val > 0 ? (drc_val - 61) : drc_val;
        misc_setting[offset++] = (drc_val >> 8) & 0xFF;
        misc_setting[offset++] = (drc_val) & 0xFF;
    } else {
        memcpy(misc_setting, (u8 *)&drc_val, sizeof(drc_val));
        offset += 2;
    }
    return offset;
}

static int drc_state_update(u8 *misc_setting)
{
    // 值不相同才设置
    static s16 prev_drc_val = -1;
    if (-1 == prev_drc_val || prev_drc_val != drc_val) {
        user_limiter_update_parm(0, "Limiter1", 0, (drc_val > 0 ? drc_val - 61 : drc_val));
        prev_drc_val = drc_val;
    }
    return 0;
}

static RCSP_MISC_SETTING_OPT drc_setting_opt = {
    .misc_data_len = 2,
    .misc_setting_type = MISC_SETTING_DRC_VAL,
    .misc_syscfg_id = CFG_RCSP_MISC_DRC_SETTING,
    .misc_set_setting = drc_setting_set,
    .misc_get_setting = drc_setting_get,
    .misc_state_update = drc_state_update,
    .misc_custom_setting_init = NULL,
    .misc_custom_write_vm = NULL,
};
REGISTER_APP_MISC_SETTING_OPT(drc_setting_opt);

#endif

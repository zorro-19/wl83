#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_misc_reverbration_setting.data.bss")
#pragma data_seg(".rcsp_misc_reverbration_setting.data")
#pragma const_seg(".rcsp_misc_reverbration_setting.text.const")
#pragma code_seg(".rcsp_misc_reverbration_setting.text")
#endif
#include "rcsp_misc_setting.h"
#include "app_config.h"
#include "app_msg.h"
#include "mic_effect.h"

#if (RCSP_MODE && RCSP_REVERBERATION_SETTING && TCFG_MIC_EFFECT_ENABLE && RCSP_ADV_EQ_SET_ENABLE)

#include "syscfg_id.h"
#include "rcsp_setting_opt.h"
#include "ble_rcsp_server.h"
#include "mic_effect.h"
/* #include "key_event_deal.h" */



#pragma pack(1)
struct t_reverbration {
    u8 state;
    u16 depth_val;
    u16 strength_val;
};
#pragma pack()

static struct t_reverbration reverbration;

static int reverbration_setting_set(u8 *misc_setting, u8 is_conversion)
{
    u32 offset = 0;
    reverbration.state = misc_setting[offset++];

    if (is_conversion) {
        /* reverbration.depth_val = misc_setting[offset++] << 8 | misc_setting[offset++]; */
        /* reverbration.strength_val = misc_setting[offset++] << 8 | misc_setting[offset++]; */
        reverbration.depth_val = misc_setting[1] << 8 | misc_setting[2];
        reverbration.strength_val = misc_setting[3] << 8 | misc_setting[4];
        offset = 5;
    } else {
        memcpy((u8 *)&reverbration.depth_val, misc_setting + offset, sizeof(reverbration.depth_val));
        offset += 2;
        memcpy((u8 *)&reverbration.strength_val, misc_setting + offset, sizeof(reverbration.strength_val));
        offset += 2;
    }
    return offset;
}

static int reverbration_setting_get(u8 *misc_setting, u8 is_conversion)
{
    u32 offset = 0;
    misc_setting[offset++] = reverbration.state;
    if (is_conversion) {
        misc_setting[offset++] = (reverbration.depth_val >> 8) & 0xFF;
        misc_setting[offset++] = (reverbration.depth_val) & 0xFF;
        misc_setting[offset++] = (reverbration.strength_val >> 8) & 0xFF;
        misc_setting[offset++] = (reverbration.strength_val) & 0xFF;
    } else {
        memcpy(misc_setting + offset, (u8 *)&reverbration.depth_val, sizeof(reverbration.depth_val));
        offset += 2;
        memcpy(misc_setting + offset, (u8 *)&reverbration.strength_val, sizeof(reverbration.strength_val));
        offset += 2;
    }
    return offset;
}

static int reverbration_write_vm(u8 *misc_setting)
{
    u8 reverbration_state = 0;
    syscfg_read(CFG_RCSP_MISC_REVERB_ON_OFF, &reverbration_state, sizeof(reverbration_state));
    if (reverbration_state != reverbration.state) {
        syscfg_write(CFG_RCSP_MISC_REVERB_ON_OFF, &reverbration.state, sizeof(reverbration.state));
    }
    return 0;
}

static int reverbration_state_update(u8 *misc_setting)
{
    // 值不相同才设置
    static u16 prev_depth_val = 0xffff;
    static u16 prev_strength_val = 0xffff;
    if (reverbration.state != mic_effect_player_runing()) {
        app_send_message(APP_MSG_MIC_EFFECT_ON_OFF, 0);
    }

    if (mic_effect_player_runing() && (0xffff == prev_depth_val || reverbration.depth_val != prev_depth_val)) {
        mic_effect_set_echo_delay(reverbration.depth_val * 2);
        prev_depth_val = reverbration.depth_val;
    }

    if (mic_effect_player_runing() && (0xffff == prev_strength_val || reverbration.strength_val != prev_strength_val)) {
        mic_effect_set_echo_decay(reverbration.strength_val * 70 / 100);
        prev_strength_val = reverbration.strength_val;
    }

    if (0 == mic_effect_player_runing()) {
        prev_depth_val = -1;
        prev_strength_val = -1;
    }
    return 0;
}

static int reverbration_custom_setting_init(void)
{
    u8 reverbration_state = 0;
    if (sizeof(reverbration_state) == syscfg_read(CFG_RCSP_MISC_REVERB_ON_OFF, &reverbration_state, sizeof(reverbration_state))) {
        reverbration.state = reverbration_state;
    } else {
        reverbration.state = mic_effect_player_runing();
    }
    reverbration.depth_val = mic_effect_get_echo_delay() / 2;
    reverbration.strength_val = mic_effect_get_echo_decay() * 100 / 70;
    return 0;
}

static int reverbartion_key_event_callback_deal(u32 event, void *param)
{
    int ret = false;
    switch (event) {
    case APP_MSG_MIC_EFFECT_ON_OFF:
        reverbration.state = mic_effect_player_runing();
        reverbration_write_vm(NULL);
        reverbration_state_update(NULL);
        ret = true;
        break;
    }
    return ret;
}

static RCSP_MISC_SETTING_OPT reverbration_setting_opt = {
    .misc_data_len = 5,
    .misc_syscfg_id = CFG_RCSP_MISC_REVERB_ON_OFF,
    .misc_setting_type = MISC_SETTING_REVERBERATION,
    .misc_set_setting = reverbration_setting_set,
    .misc_get_setting = reverbration_setting_get,
    .misc_state_update = reverbration_state_update,
    .misc_custom_setting_init = reverbration_custom_setting_init,
    .misc_custom_write_vm = reverbration_write_vm,
    .misc_custom_key_event_callback_deal = reverbartion_key_event_callback_deal,
};
REGISTER_APP_MISC_SETTING_OPT(reverbration_setting_opt);

void rcsp_close_reverbrateion_state_and_update(void)
{
    if (reverbration.state) {
        app_send_message(APP_MSG_MIC_EFFECT_ON_OFF, 0);
    }
}

#else

void rcsp_close_reverbrateion_state_and_update(void)
{

}
#endif

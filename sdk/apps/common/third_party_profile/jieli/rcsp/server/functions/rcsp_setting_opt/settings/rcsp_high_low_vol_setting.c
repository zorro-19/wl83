#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_high_low_vol_setting.data.bss")
#pragma data_seg(".rcsp_high_low_vol_setting.data")
#pragma const_seg(".rcsp_high_low_vol_setting.text.const")
#pragma code_seg(".rcsp_high_low_vol_setting.text")
#endif
#include "app_config.h"
#include "syscfg_id.h"

#include "rcsp_setting_sync.h"
#include "rcsp_setting_opt.h"
#include "ble_rcsp_server.h"

#include "JL_rcsp_protocol.h"
#include "effects/audio_bass_treble_eq.h"
#include "effects/eq_config.h"

#if (RCSP_MODE && RCSP_ADV_HIGH_LOW_SET && TCFG_BASS_TREBLE_NODE_ENABLE)

struct _HIGH_LOW_VOL {
    int low_vol;
    int high_vol;
};

static struct _HIGH_LOW_VOL high_low_vol = {
    .low_vol  = 12,
    .high_vol = 12,
};

extern int get_bt_tws_connect_status();
extern int audio_out_eq_spec_set_gain(u8 idx, int gain);

static int get_high_low_vol_info(u8 *vol_gain_param)
{
    memcpy(vol_gain_param, &high_low_vol, sizeof(struct _HIGH_LOW_VOL));
    return 0;
}

static void set_high_low_vol_info(u8 *vol_gain_param)
{
    memcpy(&high_low_vol, vol_gain_param, sizeof(struct _HIGH_LOW_VOL));
}

static void update_high_low_vol_vm_value(u8 *vol_gain_param)
{
    printf("====RCSP-TODO=================%s=%d=yuring=\n\r", __func__, __LINE__);
    /* syscfg_write(CFG_RCSP_ADV_HIGH_LOW_VOL, vol_gain_param, sizeof(struct _HIGH_LOW_VOL)); */
}

static void high_low_vol_setting_sync(u8 *vol_gain_param)
{
#if TCFG_USER_TWS_ENABLE
    if (get_bt_tws_connect_status()) {
        update_rcsp_setting(ATTR_TYPE_HIGH_LOW_VOL);
    }
#endif
}

static void high_low_vol_state_update(void)
{
    static int low_vol = 0;
    static int high_vol = 0;
    struct high_bass param = {0};
    if (low_vol != high_low_vol.low_vol) {
        param.gain = high_low_vol.low_vol - 12;
#if 0
        mix_out_high_bass(AUDIO_EQ_BASS, &param);
#else
        //printf("low vol %d gain %d\n",high_low_vol.low_vol,param.gain);
        eq_mode_set_custom_param(2, param.gain);
#endif
        low_vol = high_low_vol.low_vol;
    }
    if (high_vol != high_low_vol.high_vol) {
        param.gain = high_low_vol.high_vol - 12;
#if 0
        mix_out_high_bass(AUDIO_EQ_HIGH, &param);
#else
        //printf("high vol %d gain %d\n",high_low_vol.high_vol,param.gain);
        eq_mode_set_custom_param(8, param.gain);
#endif
        high_vol = high_low_vol.high_vol;
    }
}

static void deal_high_low_vol(u8 *vol_gain_data, u8 write_vm, u8 tws_sync)
{
    if (vol_gain_data) {
        set_high_low_vol_info(vol_gain_data);
        printf("low %d, high %d\n", high_low_vol.low_vol, high_low_vol.high_vol);
    }
    if (write_vm) {
        update_high_low_vol_vm_value((u8 *)&high_low_vol);
    }
    if (tws_sync) {
        high_low_vol_setting_sync((u8 *)&high_low_vol);
    }
    high_low_vol_state_update();
}

static int high_low_set_setting_extra_handle(void *setting_data, void *setting_data_len)
{
    high_low_vol.low_vol = READ_BIG_U32(setting_data) + 12;
    high_low_vol.high_vol = READ_BIG_U32(setting_data + 4) + 12;
    high_low_vol.low_vol = high_low_vol.low_vol > 24 ? 24 : high_low_vol.low_vol;
    high_low_vol.low_vol = high_low_vol.low_vol < 0 ? 0 : high_low_vol.low_vol;
    high_low_vol.high_vol = high_low_vol.high_vol > 24 ? 24 : high_low_vol.high_vol;
    high_low_vol.high_vol = high_low_vol.high_vol < 0 ? 0 : high_low_vol.high_vol;
    return 0;
}

static int high_low_get_setting_extra_handle(void *setting_data, void *setting_data_len)
{
    struct _HIGH_LOW_VOL gain_param = {0};
    gain_param.low_vol = high_low_vol.low_vol < 0  ? 0  : high_low_vol.low_vol;
    gain_param.low_vol = high_low_vol.low_vol > 24 ? 24 : high_low_vol.low_vol;
    gain_param.high_vol = high_low_vol.high_vol < 0  ? 0  : high_low_vol.high_vol;
    gain_param.high_vol = high_low_vol.high_vol > 24 ? 24 : high_low_vol.high_vol;
    gain_param.low_vol  -= 12;
    gain_param.high_vol -= 12;
    gain_param.low_vol  = READ_BIG_U32((u8 *)&gain_param.low_vol);
    gain_param.high_vol = READ_BIG_U32((u8 *)&gain_param.high_vol);
    memcpy(setting_data, &gain_param, sizeof(gain_param));
    return sizeof(gain_param);
}

static RCSP_SETTING_OPT high_low_vol_opt = {
    .data_len = 8,
    .setting_type = ATTR_TYPE_HIGH_LOW_VOL,
    ///RCSP TODO
    /* .syscfg_id = CFG_RCSP_ADV_HIGH_LOW_VOL, */
    .deal_opt_setting = deal_high_low_vol,
    .set_setting = set_high_low_vol_info,
    .get_setting = get_high_low_vol_info,
    .custom_setting_init = NULL,
    .custom_setting_release = NULL,
    .custom_vm_info_update = NULL,
    .custom_setting_update = NULL,
    .custom_sibling_setting_deal = NULL,
    .set_setting_extra_handle = high_low_set_setting_extra_handle,
    .get_setting_extra_handle = high_low_get_setting_extra_handle,
};
REGISTER_APP_SETTING_OPT(high_low_vol_opt);

#endif

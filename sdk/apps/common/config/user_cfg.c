#include "app_config.h"
#include "fs/fs.h"
#include "system/includes.h"
#include "syscfg/syscfg_id.h"
#include "asm/crc16.h"
#include "asm/sfc_norflash_api.h"
#include "server/audio_dev.h"
#if defined CONFIG_BT_ENABLE || TCFG_WIFI_ENABLE
#include "wifi/wifi_connect.h"
#endif

#ifdef PRODUCT_TEST_ENABLE
#include "product_main.h"
#endif

#define LOG_TAG_CONST       USER_CFG
#define LOG_TAG             "[USER_CFG]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

//======================================================================================//
//                                        BTIF配置项表                                  //
//    参数1: 配置项名字                                                                 //
//    参数2: 配置项需要多少个byte存储                                                   //
//    说明: 配置项ID注册到该表后该配置项将读写于BTIF区域, 其它没有注册到该表            //
//          的配置项则默认读写于VM区域.                                                 //
//======================================================================================//

const struct btif_item btif_table[] = {
//   item_id                len      //
    {CFG_BT_MAC_ADDR,           6 },
    {CFG_BLE_MAC_ADDR,          6 },
    {CFG_BT_FRE_OFFSET,         6 },   //测试盒矫正频偏值
    {CFG_WIFI_FRE_OFFSET,       6 },   //测试盒矫正频偏值

#ifdef PRODUCT_TEST_ENABLE
    {CFG_PRODUCT_UUID_INDEX,    PRODUCT_UUID_SIZE}, 		//产品UUID代码
    {CFG_PRODUCT_SN_INDEX,      PRODUCT_SN_SIZE},   		//产品SN代码
    {CFG_PRODUCT_LICENSE_INDEX, PRODUCT_LICENSE_INFO_SIZE}, //产品LICENSE相关信息
    {CFG_PRODUCT_RTC_INDEX,     PRODUCT_RTC_INFO_SIZE},     //产品RTC初始时间
    {CFG_PRODUCT_RES_INDEX,     PRODUCT_RES_SIZE},
    {CFG_PRODUCT_USER_INDEX,    PRODUCT_USER_DATA_SIZE},
    {CFG_PRODUCT_CFG_INDEX,     PRODUCT_CFG_SIZE},
#endif

    {0,                         0 },   //reserved cfg
};


int btif_item_rewrite_en(u16 id, u16 len)
{
    int ret;
    switch (id) {
#if (defined PRODUCT_TEST_ENABLE || defined TCFG_RF_FCC_TEST_ENABLE)
    case CFG_BT_MAC_ADDR:
    case CFG_BLE_MAC_ADDR:
    case CFG_PRODUCT_UUID_INDEX:
    case CFG_PRODUCT_SN_INDEX:
    case CFG_PRODUCT_LICENSE_INDEX:
    case CFG_PRODUCT_RTC_INDEX:
    case CFG_PRODUCT_RES_INDEX:
    case CFG_PRODUCT_USER_INDEX:
    case CFG_PRODUCT_CFG_INDEX:
        ret = 1;
        break;
#endif
    //需要重复写入的id，在此处添加相应case即可
    default:
        ret = 0;
        break;
    }
    return ret;
}

//============================= VM 区域空间最大值 ======================================//
//以下宏在app_cfg中配置:
const int vm_max_page_align_size_config   = VM_MAX_PAGE_ALIGN_SIZE_CONFIG; 		//page对齐vm管理空间最大值配置
const int vm_max_sector_align_size_config = VM_MAX_SECTOR_ALIGN_SIZE_CONFIG; 	//sector对齐vm管理空间最大值配置
const int VM_DEFRAG_SIZE = 60; //VM 碎片整理。百分比
////======================================================================================//

extern int bytecmp(unsigned char *p, unsigned char ch, unsigned int num);

#ifdef CONFIG_BT_ENABLE

#define LOCAL_NAME_LEN	32	/*BD_NAME_LEN_MAX*/

static char edr_name[LOCAL_NAME_LEN] = "JL-AC79XX-";
static char ble_name[LOCAL_NAME_LEN];
static char pincode[5] = "0000";
static u8 update_flag;
static u8 mac_addr[6];

void bt_update_mac_addr(u8 *addr)
{
    update_flag = 1;
    memcpy(mac_addr, addr, 6);
}

const u8 *bt_get_mac_addr(void)
{
    const u8 bc_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    if ((update_flag || syscfg_read(CFG_BT_MAC_ADDR, mac_addr, 6) == 6) && memcmp(mac_addr, bc_mac, 6)) {
        update_flag = 1;
        return mac_addr;
    }

#if TCFG_WIFI_ENABLE
    if (wifi_is_on() && !wifi_get_mac(mac_addr) && bytecmp(mac_addr, 0, 6)) {
        return mac_addr;
    } else
#endif
    {
        u8 flash_uid[16];
        memcpy(flash_uid, get_norflash_uuid(0), 16);
        do {
            u32 crc32 = rand32()^CRC32(flash_uid, sizeof(flash_uid));
            u16 crc16 = rand32()^CRC16(flash_uid, sizeof(flash_uid));
            memcpy(mac_addr, &crc32, sizeof(crc32));
            memcpy(&mac_addr[4], &crc16, sizeof(crc16));
        } while (!bytecmp(mac_addr, 0, 6));
        //此处用户可自行修改为本地生成mac地址的算法
        mac_addr[0] &= ~((1 << 0) | (1 << 1));
        update_flag = 1;
#if !TCFG_WIFI_ENABLE
        syscfg_write(CFG_BT_MAC_ADDR, mac_addr, 6);
#endif
        return mac_addr;
    }
}

const char *bt_get_local_name(void)
{
    int len = strlen(edr_name);
    if (len + 1 < sizeof(edr_name) && (edr_name[len - 1] == '-' || edr_name[len - 1] == '_')) {
        snprintf(edr_name + len, sizeof(edr_name) - len, "%02X%02X", mac_addr[4], mac_addr[5]);
    }
    return edr_name;
}

const char *bt_get_pin_code(void)
{
    return pincode;
}

#if TCFG_BT_SNIFF_ENABLE

typedef struct __LRC_CONFIG {
    u16 lrc_ws_inc;
    u16 lrc_ws_init;
    u16 btosc_ws_inc;
    u16 btosc_ws_init;
    u8 lrc_change_mode;
} _GNU_PACKED_ LRC_CONFIG;

struct lp_ws_t {
    u16 lrc_ws_inc;
    u16 lrc_ws_init;
    u16 bt_osc_ws_inc;
    u16 bt_osc_ws_init;
    u8  osc_change_mode;
};

static struct lp_ws_t default_lp_winsize = {
    .lrc_ws_inc = 480,
    .lrc_ws_init = 400,
    .bt_osc_ws_inc = 480,
    .bt_osc_ws_init = 140,
    .osc_change_mode = 2,
};
#endif

#else

const u8 *bt_get_mac_addr(void)
{
    return NULL;
}

#endif

#ifdef CONFIG_AEC_ENC_ENABLE
typedef struct __AEC_CONFIG {
    u8 mic_again;           //DAC增益,default:31(0~31)
    u8 dac_again;           //MIC增益,default:20(0~31)
    u8 aec_mode;            //AEC模式,AEC_EN:BIT(0) NLP_EN:BIT(1) NS_EN:BIT(2) AGC_EN:BIT(4) DNS_EN:BIT(5)
    u8 ul_eq_en;            //上行EQ使能,default:enable(disable(0), enable(1))
    /*AGC*/
    float ndt_fade_in;      //单端讲话淡入步进default: 1.3f(0.1 ~ 5 dB)
    float ndt_fade_out;     //单端讲话淡出步进default: 0.7f(0.1 ~ 5 dB)
    float dt_fade_in;       //双端讲话淡入步进default: 1.3f(0.1 ~ 5 dB)
    float dt_fade_out;      //双端讲话淡出步进default: 0.7f(0.1 ~ 5 dB)
    float ndt_max_gain;     //单端讲话放大上限,default: 12.f(0 ~ 24 dB)
    float ndt_min_gain;     //单端讲话放大下限,default: 0.f(-20 ~ 24 dB)
    float ndt_speech_thr;   //单端讲话放大阈值,default: -50.f(-70 ~ -40 dB)
    float dt_max_gain;      //双端讲话放大上限,default: 12.f(0 ~ 24 dB)
    float dt_min_gain;      //双端讲话放大下限,default: 0.f(-20 ~ 24 dB)
    float dt_speech_thr;    //双端讲话放大阈值,default: -40.f(-70 ~ -40 dB)
    float echo_present_thr; //单端双端讲话阈值,default:-70.f(-70 ~ -40 dB)
    /*AEC*/
    float aec_dt_aggress;   //原音回音追踪等级, default: 1.0f(1 ~ 5)
    float aec_refengthr;    //进入回音消除参考值, default: -70.0f(-90 ~ -60 dB)
    /*NLP*/
    float nlp_aggress_factor;//回音前级动态压制,越小越强,default: -3.0f(-1 ~ -5)
    float nlp_min_suppress;  //回音后级静态压制,越大越强,default: 4.f(0 ~ 10)
    /*ANS*/
    float ans_aggress;      //噪声前级动态压制,越大越强default: 1.25f(1 ~ 2)
    float ans_suppress;     //噪声后级静态压制,越小越强default: 0.04f(0 ~ 1)
    /*DNS*/
    float dns_gain_floor;	//增益最小值控制, 越小降噪越强, default: 0.1f(0 ~ 1.0)
    float dns_over_drive;	//降噪强度, 越大降噪越强, default: 1.0f(0 ~ 6.0)
} _GNU_PACKED_ AEC_CONFIG;

void get_cfg_file_aec_config(struct aec_s_attr *aec_param)
{
    AEC_CONFIG aec_config = {
        .mic_again           =        3,
        .dac_again           =       22,
#ifdef CONFIG_DNS_ENC_ENABLE
        .aec_mode            =        BIT(0) | BIT(1) | BIT(2) | BIT(5),
#else
        .aec_mode            =        BIT(0) | BIT(1) | BIT(2),
#endif
        .ul_eq_en            =        0,
        /*AGC*/
        .ndt_fade_in         =     1.3f,
        .ndt_fade_out        =     0.9f,
        .dt_fade_in          =     1.3f,
        .dt_fade_out         =     0.9f,
        .ndt_max_gain        =     12.f,
        .ndt_min_gain        =      0.f,
        .ndt_speech_thr      =    -50.f,
        .dt_max_gain         =     12.f,
        .dt_min_gain         =      0.f,
        .dt_speech_thr       =    -40.f,
        .echo_present_thr    =    -70.f,
        /*AEC*/
        .aec_dt_aggress      =      1.f,
        .aec_refengthr       =    -70.f,
        /*ES*/
        .nlp_aggress_factor   =    -3.f,
        .nlp_min_suppress     =     4.f,
        /*ANS*/
        .ans_aggress         =    1.25f,
        .ans_suppress        =    0.04f,
        /*DNS*/
        .dns_gain_floor      =     0.1f,
        .dns_over_drive      =     1.0f,
    };

    //-----------------------------CFG_AEC_ID------------------------------------//
    int ret = syscfg_read(CFG_AEC_ID, &aec_config, sizeof(AEC_CONFIG));
    if (ret > 0) {
        log_info("aec config mode:%d, DNS_gain_floor:%f, dns_over_drive:%f", aec_config.aec_mode, aec_config.dns_gain_floor, aec_config.dns_over_drive);
    }

    aec_param->EnableBit = aec_config.aec_mode;
#ifndef CONFIG_DNS_ENC_ENABLE
    aec_param->EnableBit &= ~BIT(5);
#endif

    aec_param->dac_ref_sr = 16000; //aec软件回采的dac参考采样率，8k或16k的整数倍

    aec_param->AGC_NDT_fade_in_step  = aec_config.ndt_fade_in;
    aec_param->AGC_NDT_fade_out_step = aec_config.ndt_fade_out;
    aec_param->AGC_DT_fade_in_step   = aec_config.dt_fade_in;
    aec_param->AGC_DT_fade_out_step  = aec_config.dt_fade_out;
    aec_param->AGC_NDT_max_gain      = aec_config.ndt_max_gain;
    aec_param->AGC_NDT_min_gain      = aec_config.ndt_min_gain;
    aec_param->AGC_NDT_speech_thr    = aec_config.ndt_speech_thr;
    aec_param->AGC_DT_max_gain       = aec_config.dt_max_gain;
    aec_param->AGC_DT_min_gain       = aec_config.dt_min_gain;
    aec_param->AGC_DT_speech_thr     = aec_config.dt_speech_thr;
    aec_param->AGC_echo_present_thr  = aec_config.echo_present_thr;
    aec_param->AEC_DT_AggressiveFactor = aec_config.aec_dt_aggress;
    aec_param->AEC_RefEngThr         = aec_config.aec_refengthr;
    aec_param->ES_AggressFactor      = aec_config.nlp_aggress_factor;
    aec_param->ES_MinSuppress        = aec_config.nlp_min_suppress;
    aec_param->ANS_AggressFactor     = aec_config.ans_aggress;
    aec_param->ANS_MinSuppress       = aec_config.ans_suppress;
    aec_param->DNS_gain_floor        = aec_config.dns_gain_floor;
    aec_param->DNS_over_drive        = aec_config.dns_over_drive;
    aec_param->DNS_loudness          = 1.0f;
    aec_param->AGC_echo_look_ahead = 100;
    aec_param->AGC_echo_hold = 400;
    aec_param->ES_Unconverge_OverDrive = aec_param->ES_MinSuppress;
}
#endif

#ifdef CONFIG_NET_ENABLE

typedef struct __RF_PARAM_CONFIG {
    u8 xosc_l;
    u8 xosc_r;
    u8 pa_trim_data[7];
    u8 mcs_dgain[20];
    u8 analog_gain;
    u8 force_update_vm;
} _GNU_PACKED_ RF_PARAM_CONFIG;

static RF_PARAM_CONFIG rf_param_config;

#if defined CONFIG_READ_RF_PARAM_FROM_CFGTOOL_ENABLE
u8 get_rf_analog_gain(void)
{
    return rf_param_config.analog_gain;
}

int get_power_config_from_cfg_tools_enalbe(void)
{
    return 1;
}
#endif

#endif

typedef struct __POWER_CONFIG {
    float vddiom_vol;
    float vddiow_vol;
    float vdc14_vol;
    float sysvdd_vol;
} _GNU_PACKED_ POWER_CONFIG;


void cfg_file_parse(void)
{
    u8 tmp[65] = {0};
    int ret = 0;

    /*************************************************************************/
    /*                      CFG READ IN cfg_tools.bin                        */
    /*************************************************************************/

#ifdef CONFIG_RF_TEST_ENABLE
    //-----------------------------CFG_WIFI_TEST_CFG_ID--------------------------------------//
    ret = syscfg_read(CFG_WIFI_TEST_CFG_ID, tmp, 5);
    if (ret > 0) {
        tmp[ret] = 0;

        if (tmp[1] == 'P' && tmp[2] >= 'A' && tmp[2] <= 'H'
            && (tmp[3] == '0' || tmp[3] == '1')
            && tmp[4] >= '0' && tmp[4] <= '9') {
            extern struct uart_platform_data uart2_data;
            uart2_data.tx_pin = (tmp[2] - 'A') * 16 + (tmp[3] - '0') * 10 + (tmp[4] - '0');
            extern int uart_init(const struct uart_platform_data * data);
            uart_init(&uart2_data);
            os_time_dly(5);
        }

        log_info("wifi test mode:%d, debug io:%s", tmp[0], tmp + 1);
    }
#endif

#ifdef CONFIG_BT_ENABLE
    //-----------------------------CFG_BT_NAME--------------------------------------//
    ret = syscfg_read(CFG_BT_NAME, tmp, LOCAL_NAME_LEN);
    if (ret < 0) {
        log_info("read edr name err");
    } else if (ret >= LOCAL_NAME_LEN) {
        memset(edr_name, 0x00, LOCAL_NAME_LEN);
        memcpy(edr_name, tmp, LOCAL_NAME_LEN);
        edr_name[LOCAL_NAME_LEN - 1] = 0;
    } else {
        memset(edr_name, 0x00, LOCAL_NAME_LEN);
        memcpy(edr_name, tmp, ret);
    }
    log_info("edr name config:%s", edr_name);

    //-----------------------------CFG_BLE_NAME--------------------------------------//
    ret = syscfg_read(CFG_BLE_NAME, tmp, LOCAL_NAME_LEN);
    if (ret < 0) {
        log_info("read ble name err");
    } else if (ret >= LOCAL_NAME_LEN) {
        memset(ble_name, 0x00, LOCAL_NAME_LEN);
        memcpy(ble_name, tmp, LOCAL_NAME_LEN);
        ble_name[LOCAL_NAME_LEN - 1] = 0;
    } else {
        memset(ble_name, 0x00, LOCAL_NAME_LEN);
        memcpy(ble_name, tmp, ret);
    }
    log_info("ble name config:%s", ble_name);

    //-----------------------------CFG_BT_MAC_ADDR--------------------------------------//
    ret = syscfg_read(CFG_BT_MAC_ADDR, tmp, 6);
    if (ret < 0) {
        log_info("read edr mac addr err");
    } else {
        log_info("edr mac addr config");
        put_buf(tmp, 6);
    }

    //-----------------------------CFG_BLE_MAC_ADDR--------------------------------------//
    ret = syscfg_read(CFG_BLE_MAC_ADDR, tmp, 6);
    if (ret < 0) {
        log_info("read ble mac addr err");
    } else {
        log_info("ble mac addr config");
        put_buf(tmp, 6);
    }

    u8 bt_power = 8;
    u8 ble_power = 6;

    //-----------------------------CFG_BT_RF_POWER_ID----------------------------//
    ret = syscfg_read(CFG_BT_RF_POWER_ID, &bt_power, 1);
    if (ret < 0) {
        log_error("read edr rf power err");
        bt_power = 8;
    }

    //-----------------------------CFG_BLE_RF_POWER_ID----------------------------//
    ret = syscfg_read(CFG_BLE_RF_POWER_ID, &ble_power, 1);
    if (ret < 0) {
        log_error("read ble rf power err");
        ble_power = 6;
    }

    //-------------若存在BT/BLE功率校准值(RF_FCC校准所得)，则使用校准值-----------//
#if TCFG_RF_FCC_TEST_ENABLE || TCFG_RF_PRODUCT_TEST_ENABLE
    u8 rf_fcc_adj_res_read(char *str, void *data);
    if (rf_fcc_adj_res_read("edr", &bt_power)) {
        log_info("---  [RF_FCC_ADJ]bt_power %d ----", bt_power);
    } else {
        log_info("---  [RF_FCC_ADJ]bt_power NULL ----");
    }

    if (rf_fcc_adj_res_read("ble", &ble_power)) {
        log_info("---  [RF_FCC_ADJ]ble_power %d ----", ble_power);
    } else {
        log_info("---  [RF_FCC_ADJ]ble_power NULL ----");
    }
#endif

    extern void bt_max_pwr_set(u8 pwr, u8 pg_pwr, u8 iq_pwr, u8 ble_pwr);
#if TCFG_RF_FCC_TEST_ENABLE
    bt_max_pwr_set(8, 6, 6, 8);	//0-10 设置蓝牙发射功率
#else
    bt_max_pwr_set(bt_power, 6, 6, ble_power);	//0-10 设置蓝牙发射功率
#endif
    log_info("rf bt_power:%d, ble_power:%d", bt_power, ble_power);

    //-----------------------------CFG_TWS_PAIR_CODE_ID----------------------------//
    u16 pin = 0;
    ret = syscfg_read(CFG_TWS_PAIR_CODE_ID, &pin, sizeof(pin));
    if (ret < 0) {
        log_error("read pincode err");
        pin = 0;
    } else {
        snprintf(pincode, sizeof(pincode), "%04X", pin);
        log_info("pincode : %s", pincode);
    }

#if TCFG_BT_SNIFF_ENABLE
    extern void lp_winsize_init(struct lp_ws_t *lp);
#ifdef CONFIG_MEDIA_ENABLE
    log_info("lrc cfg");
    default_lp_winsize.lrc_ws_inc      = TCFG_LRC_WIN_STEP;
    default_lp_winsize.lrc_ws_init     = TCFG_LRC_WIN_SIZE;
    default_lp_winsize.bt_osc_ws_inc   = TCFG_OSC_WIN_STEP;
    default_lp_winsize.bt_osc_ws_init  = TCFG_OSC_WIN_SIZE;
    default_lp_winsize.osc_change_mode = 2;
#else

    LRC_CONFIG lrc_cfg = {0};
    ret = syscfg_read(CFG_LRC_ID, &lrc_cfg, sizeof(LRC_CONFIG));
    if (ret > 0) {
        log_info("lrc cfg");
        /* log_info_hexdump(&lrc_cfg, sizeof(LRC_CONFIG)); */
        default_lp_winsize.lrc_ws_inc      = lrc_cfg.lrc_ws_inc;
        default_lp_winsize.lrc_ws_init     = lrc_cfg.lrc_ws_init;
        default_lp_winsize.bt_osc_ws_inc   = lrc_cfg.btosc_ws_inc;
        default_lp_winsize.bt_osc_ws_init  = lrc_cfg.btosc_ws_init;
        default_lp_winsize.osc_change_mode = lrc_cfg.lrc_change_mode;
    }
#endif
    lp_winsize_init(&default_lp_winsize);

#endif

#endif

#ifdef CONFIG_NET_ENABLE
    //-----------------------------CFG_WIFI_SSID_ID--------------------------------------//
    ret = syscfg_read(CFG_WIFI_SSID_ID, tmp, 32);
    if (ret <= 0) {
        log_info("read wifi ssid err");
    } else {
        tmp[ret - 1] = 0;
        log_info("wifi ssid config:%s", tmp);
    }

    //-----------------------------CFG_WIFI_PWD_ID--------------------------------------//
    ret = syscfg_read(CFG_WIFI_PWD_ID, tmp, 64);
    if (ret <= 0) {
        log_info("read wifi pwd err");
    } else {
        tmp[ret - 1] = 0;
        log_info("wifi pwd config:%s", tmp);
    }

    //-----------------------------CFG_WIFI_RF_CFG_ID--------------------------------------//
    ret = syscfg_read(CFG_WIFI_RF_CFG_ID, &rf_param_config, sizeof(rf_param_config));
    if (ret < 0) {
        log_info("read wifi rf cfg err");
    } else {
        put_buf((u8 *)&rf_param_config, sizeof(rf_param_config));
    }
#endif

#if 0
    /* g_printf("auto low power config:\n"); */
    log_info("auto low power config:");
    AUTO_LOWPOWER_V_CONFIG auto_lowpower;
    ret = syscfg_read(CFG_LOWPOWER_V_ID, &auto_lowpower, sizeof(AUTO_LOWPOWER_V_CONFIG));
    if (ret > 0) {
        app_var.warning_tone_v = auto_lowpower.warning_tone_v;
        app_var.poweroff_tone_v = auto_lowpower.poweroff_tone_v;
    }
    log_info("warning_tone_v:%d poweroff_tone_v:%d", app_var.warning_tone_v, app_var.poweroff_tone_v);
#endif

    u8 auto_off_time;
    ret = syscfg_read(CFG_AUTO_OFF_TIME_ID, &auto_off_time, sizeof(auto_off_time));
    if (ret > 0) {
        log_info("auto_off_time:%d", auto_off_time);
    }

    //-----------------------------CFG_WIFI_POWER_CFG_ID--------------------------------------//
    POWER_CONFIG power_config = {0};
    ret = syscfg_read(CFG_WIFI_POWER_CFG_ID, &power_config, sizeof(power_config));
    if (ret < 0) {
        log_info("read wifi power config err");
    } else {
        log_info("vddiom:%.2fV, vddiow:%.2fV, vdd14:%.2fV, sysvdd:%.2fV",
                 power_config.vddiom_vol, power_config.vddiow_vol, power_config.vdc14_vol, power_config.sysvdd_vol);
    }
}

#if defined CONFIG_BT_ENABLE || TCFG_WIFI_ENABLE
__attribute__((weak)) void wifi_get_xosc(u8 *xosc)
{
#if defined CONFIG_READ_RF_PARAM_FROM_CFGTOOL_ENABLE
    xosc[0] = rf_param_config.xosc_l;
    xosc[1] = rf_param_config.xosc_r;
#else
    xosc[0] = wifi_calibration_param.xosc_l;
    xosc[1] = wifi_calibration_param.xosc_r;
#endif
    if (syscfg_read(VM_XOSC_INDEX, xosc, 2) != 2) {
        syscfg_write(VM_XOSC_INDEX, xosc, 2);
    }
}

__attribute__((weak)) void wifi_get_mcs_dgain(u8 *mcs_dgain)
{
#if defined CONFIG_READ_RF_PARAM_FROM_CFGTOOL_ENABLE
    memcpy(mcs_dgain, rf_param_config.mcs_dgain, sizeof(rf_param_config.mcs_dgain));
#else
    memcpy(mcs_dgain, wifi_calibration_param.mcs_dgain, sizeof(wifi_calibration_param.mcs_dgain));
#endif
    if (syscfg_read(VM_WIFI_PA_MCS_DGAIN, mcs_dgain, sizeof(wifi_calibration_param.mcs_dgain)) != sizeof(wifi_calibration_param.mcs_dgain)) {
        syscfg_write(VM_WIFI_PA_MCS_DGAIN, mcs_dgain, sizeof(wifi_calibration_param.mcs_dgain));
    }
}

__attribute__((weak)) int wifi_get_pa_trim_data(u8 *pa_data)
{
#if defined CONFIG_READ_RF_PARAM_FROM_CFGTOOL_ENABLE
    memcpy(pa_data, rf_param_config.pa_trim_data, sizeof(rf_param_config.pa_trim_data));
#else
    memcpy(pa_data, wifi_calibration_param.pa_trim_data, sizeof(wifi_calibration_param.pa_trim_data));
#endif
    if (syscfg_read(VM_WIFI_PA_DATA, pa_data, sizeof(wifi_calibration_param.pa_trim_data)) != sizeof(wifi_calibration_param.pa_trim_data)) {
        syscfg_write(VM_WIFI_PA_DATA, pa_data, sizeof(wifi_calibration_param.pa_trim_data));
    }
    return 1;//不使用自动tune
}
#endif

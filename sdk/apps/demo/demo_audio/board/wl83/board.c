#include "app_config.h"
#include "system/includes.h"
#include "device/includes.h"
#include "device/uart.h"
#include "server/audio_dev.h"
#include "asm/includes.h"
#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
#include "otg.h"
#include "usb_host.h"
#include "usb_storage.h"
#endif


// *INDENT-OFF*

#if TCFG_UART0_ENABLE
UART0_PLATFORM_DATA_BEGIN(uart0_data)
#ifdef CONFIG_DEBUG_ENABLE
    .disable_tx_irq         = 1,
#endif
#if TCFG_UART_KEY_ENABLE
    .disable_rx_irq         = 1,
#endif
    .baudrate               = TCFG_UART0_BAUDRATE,
    .tx_pin                 = TCFG_UART0_TX_IO,
    .rx_pin                 = TCFG_UART0_RX_IO,
    .max_continue_recv_cnt  = 1024,
    .idle_sys_clk_cnt       = 500000,
    .clk_src                = STD_24M,
    .flags                  = UART_DEBUG,
    .parity                 = TCFG_UART0_PARITY,
UART0_PLATFORM_DATA_END();
#endif

#if TCFG_UART1_ENABLE
UART1_PLATFORM_DATA_BEGIN(uart1_data)
    .flow_ctl_enable        = TCFG_UART1_FLOW_CTL_ENABLE,
    .rts_hw_enable          = TCFG_UART1_RTS_HW_ENABLE,
    .baudrate               = TCFG_UART1_BAUDRATE,
    .tx_pin                 = TCFG_UART1_TX_IO,
    .rx_pin                 = TCFG_UART1_RX_IO,
    .rts_pin                = TCFG_UART1_RTS_IO,
    .cts_pin                = TCFG_UART1_CTS_IO,
    .rts_idle_level         = TCFG_UART1_RTS_IDLE_LEVEL,
    .cts_idle_level         = TCFG_UART1_CTS_IDLE_LEVEL,
    .rx_thresh              = TCFG_UART1_RTS_RX_THRESH,
    .max_continue_recv_cnt  = TCFG_UART1_MAX_CONTINUE_RECV_CNT,
    .idle_sys_clk_cnt       = 500000,
    .clk_src                = STD_24M,
    .parity                 = TCFG_UART1_PARITY,
UART1_PLATFORM_DATA_END();
#endif


#if TCFG_SD0_ENABLE
SD0_PLATFORM_DATA_BEGIN(sd0_data)
    .port                   = TCFG_SD0_PORTS,
    .port_group             = TCFG_SD0_PORTS_GROUP,
    .priority               = 2,
    .data_width             = TCFG_SD0_DAT_WIDTH,
    .speed                  = TCFG_SD0_CLK,
    .detect_mode            = TCFG_SD0_DET_MODE,
#if (TCFG_SD0_DET_MODE == SD_CLK_DECT)
    .detect_func            = sdmmc_clk_detect,
#elif (TCFG_SD0_DET_MODE == SD_IO_DECT)
    .detect_func            = sdmmc_io_detect,
    .detect_io              = TCFG_SD0_DET_IO,
    .detect_io_level        = TCFG_SD0_DET_IO_LEVEL,
#else
    .detect_func            = NULL,
#endif
    .hd_level               = TCFG_SD0_HD_LEVEL,
#if TCFG_SD0_POWER_ENABLE
    .power                  = sd_set_power,
#endif
SD0_PLATFORM_DATA_END()
#endif

#if TCFG_SD1_ENABLE
SD1_PLATFORM_DATA_BEGIN(sd1_data)
    .port                   = TCFG_SD1_PORTS,
    .port_group             = TCFG_SD1_PORTS_GROUP,
    .priority               = 2,
    .data_width             = TCFG_SD1_DAT_WIDTH,
    .speed                  = TCFG_SD1_CLK,
    .detect_mode            = TCFG_SD1_DET_MODE,
#if (TCFG_SD1_DET_MODE == SD_CLK_DECT)
    .detect_func            = sdmmc_clk_detect,
#elif (TCFG_SD1_DET_MODE == SD_IO_DECT)
    .detect_func            = sdmmc_io_detect,
    .detect_io              = TCFG_SD1_DET_IO,
    .detect_io_level        = TCFG_SD1_DET_IO_LEVEL,
#else
    .detect_func            = NULL,
#endif
    .hd_level               = TCFG_SD1_HD_LEVEL,
#if TCFG_SD1_POWER_ENABLE
    .power                  = sd_set_power,
#endif
SD1_PLATFORM_DATA_END()
#endif


#if TCFG_IRKEY_ENABLE
static const struct irkey_platform_data irkey_data = {
    .timer_index            = TCFG_IRKEY_TIMER_INDEX,
    .port                   = TCFG_IRKEY_INPUT_IO,
};

const struct irkey_platform_data *get_irkey_platform_data(void)
{
    return &irkey_data;
}
#endif

#if TCFG_RDEC_KEY_ENABLE
static const struct rdec_device rdeckey_list[] = {
#if TCFG_QDEC0_ENABLE
    {
        .index              = RDEC0,
        .mode               = TCFG_QDEC0_MODE,
        .clk_spnd           = TCFG_QDEC0_CLK_SPND,
        .sin_port0          = TCFG_QDEC0_INPUT_IO_A,
        .sin_port1          = TCFG_QDEC0_INPUT_IO_B,
        .key_value0         = TCFG_QDEC0_KEY_VALUE_A | BIT(7),
        .key_value1         = TCFG_QDEC0_KEY_VALUE_B | BIT(7),
    },
#endif
};

static const struct rdec_platform_data rdec_key_data = {
    .num                    = ARRAY_SIZE(rdeckey_list),
    .rdec                   = rdeckey_list,
};

const struct rdec_platform_data *get_rdec_key_platform_data(void)
{
    return &rdec_key_data;
}
#endif

#if TCFG_IOKEY_ENABLE
static const struct iokey_port iokey_list[] = {
#if TCFG_IOKEY_INPUT0_ENABLE
    {
        .connect_way        = TCFG_IOKEY_INPUT0_CONNECT_WAY,
        .key_type.one_io.port = TCFG_IOKEY_INPUT0_IO,
        .key_value          = TCFG_IOKEY_INPUT0_VALUE,
    },
#endif
#if TCFG_IOKEY_INPUT1_ENABLE
    {
        .connect_way        = TCFG_IOKEY_INPUT1_CONNECT_WAY,
        .key_type.one_io.port = TCFG_IOKEY_INPUT1_IO,
        .key_value          = TCFG_IOKEY_INPUT1_VALUE,
    },
#endif
#if TCFG_IOKEY_INPUT2_ENABLE
    {
        .connect_way        = TCFG_IOKEY_INPUT2_CONNECT_WAY,
        .key_type.one_io.port = TCFG_IOKEY_INPUT2_IO,
        .key_value          = TCFG_IOKEY_INPUT2_VALUE,
    },
#endif
};

static const struct iokey_platform_data iokey_data = {
    .num                    = ARRAY_SIZE(iokey_list),
    .port                   = iokey_list,
};

const struct iokey_platform_data *get_iokey_platform_data(void)
{
    return &iokey_data;
}
#endif

#if TCFG_TOUCH_KEY_ENABLE
static const struct touch_key_port plcnt_port[] = {
#if TCFG_TOUCH_KEY0_ENABLE
    {
        .port               = TCFG_TOUCH_KEY0_PORT,
        .key_value          = TCFG_TOUCH_KEY0_VALUE,
        .press_delta        = TCFG_TOUCH_KEY0_PRESS_DELTA,
    },
#endif
#if TCFG_TOUCH_KEY1_ENABLE
    {
        .port               = TCFG_TOUCH_KEY1_PORT,
        .key_value          = TCFG_TOUCH_KEY1_VALUE,
        .press_delta        = TCFG_TOUCH_KEY1_PRESS_DELTA,
    },
#endif
#if TCFG_TOUCH_KEY2_ENABLE
    {
        .port               = TCFG_TOUCH_KEY2_PORT,
        .key_value          = TCFG_TOUCH_KEY2_VALUE,
        .press_delta        = TCFG_TOUCH_KEY2_PRESS_DELTA,
    },
#endif
};

static const struct touch_key_platform_data touch_key_data = {
    .num                    = ARRAY_SIZE(plcnt_port),
    .clk_src                = TOUCH_KEY_CLOCK_SOURCE,
    .port_list              = plcnt_port,
};

const struct touch_key_platform_data *get_touch_key_platform_data(void)
{
    return &touch_key_data;
}
#endif

#if TCFG_ADKEY_ENABLE
#define ADC_VDDIO   (0x3FF)

#define ADKEY_V_9   ((TCFG_ADC_LEVEL_09 + ADC_VDDIO) / 2)
#define ADKEY_V_8   ((TCFG_ADC_LEVEL_08 + TCFG_ADC_LEVEL_09) / 2)
#define ADKEY_V_7   ((TCFG_ADC_LEVEL_07 + TCFG_ADC_LEVEL_08) / 2)
#define ADKEY_V_6   ((TCFG_ADC_LEVEL_06 + TCFG_ADC_LEVEL_07) / 2)
#define ADKEY_V_5   ((TCFG_ADC_LEVEL_05 + TCFG_ADC_LEVEL_06) / 2)
#define ADKEY_V_4   ((TCFG_ADC_LEVEL_04 + TCFG_ADC_LEVEL_05) / 2)
#define ADKEY_V_3   ((TCFG_ADC_LEVEL_03 + TCFG_ADC_LEVEL_04) / 2)
#define ADKEY_V_2   ((TCFG_ADC_LEVEL_02 + TCFG_ADC_LEVEL_03) / 2)
#define ADKEY_V_1   ((TCFG_ADC_LEVEL_01 + TCFG_ADC_LEVEL_02) / 2)
#define ADKEY_V_0   ((TCFG_ADC_LEVEL_00 + TCFG_ADC_LEVEL_01) / 2)

static const struct adkey_platform_data adkey_data = {
    .adkey_pin              = TCFG_ADKEY_INPUT_IO,
    .extern_up_en           = 1,
    .ad_channel             = TCFG_ADKEY_INPUT_CHANNEL,
    .ad_value               = {
                                ADKEY_V_0,
                                ADKEY_V_1,
                                ADKEY_V_2,
                                ADKEY_V_3,
                                ADKEY_V_4,
                                ADKEY_V_5,
                                ADKEY_V_6,
                                ADKEY_V_7,
                                ADKEY_V_8,
                                ADKEY_V_9,
    },
    .key_value              = {
                                TCFG_ADKEY_VALUE_0,
                                TCFG_ADKEY_VALUE_1,
                                TCFG_ADKEY_VALUE_2,
                                TCFG_ADKEY_VALUE_3,
                                TCFG_ADKEY_VALUE_4,
                                TCFG_ADKEY_VALUE_5,
                                TCFG_ADKEY_VALUE_6,
                                TCFG_ADKEY_VALUE_7,
                                TCFG_ADKEY_VALUE_8,
                                TCFG_ADKEY_VALUE_9,
    },
};

const struct adkey_platform_data *get_adkey_platform_data(void)
{
    return &adkey_data;
}
#endif


#ifdef CONFIG_AUDIO_ENABLE
#if TCFG_AUDIO_DAC_ENABLE
static const struct dac_platform_data dac_data = {
    .pa_auto_mute           = TCFG_AUDIO_DAC_PA_AUTO_MUTE_ENABLE,
    .pa_mute_port           = TCFG_AUDIO_DAC_PA_MUTE_PORT,
    .pa_mute_value          = TCFG_AUDIO_DAC_PA_MUTE_LEVEL,
    .differ_output          = TCFG_AUDIO_DAC_DIFFER_OUTPUT_ENABLE,
    .hw_channel             = TCFG_AUDIO_DAC_HW_CHANNEL,
#if !TCFG_AUDIO_DAC_DIFFER_OUTPUT_ENABLE && TCFG_AUDIO_DAC_HW_CHANNEL == (AUDIO_DAC_CH_L | AUDIO_DAC_CH_R)
    .ch_num                 = 2,
#else
    .ch_num                 = 1,
#endif
    .vcm_init_delay_ms      = TCFG_AUDIO_DAC_VCM_INIT_DELAY_MS,
    .trim_en                = 0,
    .fade_enable            = 1,
    .fade_points_step       = 1,
    .fade_volume_step       = 1,
    .mute_delay_ms          = TCFG_AUDIO_DAC_PA_MUTE_DELAY_MS,
};
#endif

#if TCFG_AUDIO_ADC_ENABLE
static const struct adc_platform_data adc_data = {
    .mic_port               = TCFG_MIC_IO_PORT,
    .linein_port            = TCFG_LINEIN_IO_PORT,
    .mic_ch_num             = TCFG_MIC_CHANNEL_NUM,
#if TCFG_MIC_CHANNEL_NUM == 2
    .mic_share_micbias      = TCFG_MIC_SHARE_MICBIAS_ENABLE,
#else
    .mic_share_micbias      = 0,
#endif
    .mic_other_power_enable    = TCFG_MIC_OTHER_POWER_ENABLE,
#if TCFG_MIC_OTHER_POWER_ENABLE
    .mic_other_power_port      = TCFG_MIC_OTHER_POWER_IO_PORT,
#endif
    .linein_ch_num          = TCFG_LINEIN_CHANNEL_NUM,
    .all_channel_open       = TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN,
    .dmic_enable            = TCFG_DMIC_ENABLE,
    .dmic_sclk_fre          = TCFG_DMIC_SCLK_FREQUENCY,
    .dmic_io_sclk           = TCFG_DMIC_IO_SCLK,
    .dmic_io_idat0          = TCFG_DMIC_IO_IDAT0,
    .dmic_io_idat1          = TCFG_DMIC_IO_IDAT1,
    .dmic_init_delay_ms     = 150,
    /* .dump_num            = 320, */
};
#endif

#if TCFG_ALNK_ENABLE
static const struct alnk_platform_data alnk_data = {
    .port                   = TCFG_ALNK_PORTS,   ///< [0]MCLK [1]LRCLK [2]SCLK [3]DAT0 [4]DAT1 [5]DAT2 [6]DAT3
    .channel_in             = TCFG_ALNK_CHANNLE_IN_MAP,
    .channel_out            = TCFG_ALNK_CHANNLE_OUT_MAP,
    .data_width             = TCFG_ALNK_DATA_WIDTH,
    .mode                   = TCFG_ALNK_MODE,
    .dma_mode               = TCFG_ALNK_DMA_MODE,
    .slave_mode             = TCFG_ALNK_SLAVE_MODE_ENABLE,
    .mclk_src               = TCFG_ALNK_MCLK_SRC,
    .update_edge            = TCFG_ALNK_UPDATE_EDGE,
#if TCFG_ALNK_DATA_WIDTH == ALNK_DATA_WIDTH_24_BIT
    .dec_width_16_to_24     = 1,
    .enc_width_24_to_32     = 1,
#endif
};
#endif

#if TCFG_PLNK_ENABLE
static const struct plnk_platform_data plnk_data = {
    .hw_channel             = TCFG_PLNK_HW_CHANNEL,
    .share_data_io          = TCFG_PLNK_INPUT_DAT_SHARE_IO_ENABLE,
    .sclk_io                = TCFG_PLNK_SCLK_IO,
    .dat0_io                = TCFG_PLNK_INPUT_DAT0_IO,
    .dat1_io                = TCFG_PLNK_INPUT_DAT1_IO,
    .sclk_fre               = TCFG_PLNK_SCLK_FREQUENCY,
    .ch0_mode               = TCFG_PLNK_CH0_SAMPLE_MODE,
    .ch1_mode               = TCFG_PLNK_CH1_SAMPLE_MODE,
    .order                  = TCFG_PLNK_CIC_ORDER,
    .dfdly_m                = TCFG_PLNK_CIC_DFDLY_M,
    .dc_cancelling_filter   = 4,
    .init_delay_ms          = 80,
    .dump_points_num        = 0,
};
#endif

static const struct audio_pf_data audio_pf_d = {
#if TCFG_AUDIO_DAC_ENABLE
    .dac_pf_data            = &dac_data,
#endif
#if TCFG_AUDIO_ADC_ENABLE
    .adc_pf_data            = &adc_data,
#endif
#if TCFG_ALNK_ENABLE
    .alnk_pf_data           = &alnk_data,
#endif
#if TCFG_PLNK_ENABLE
    .plnk_pf_data           = &plnk_data,
#endif
};

static const struct audio_platform_data audio_data = {
    .private_data           = (void *)&audio_pf_d,
};
#endif


#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
static const struct otg_dev_data otg_data = {
    .usb_dev_en             = TCFG_USB_DEVICE,
#if TCFG_USB_SLAVE_ENABLE
    .slave_online_cnt       = 10,
    .slave_offline_cnt      = 10,
#endif
#if TCFG_USB_HOST_ENABLE
    .host_online_cnt        = 10,
    .host_offline_cnt       = 10,
#endif
    .detect_mode            = OTG_CHARGE_MODE
#if TCFG_USB_SLAVE_ENABLE
                            | OTG_SLAVE_MODE
#endif
#if TCFG_USB_HOST_ENABLE
                            | OTG_HOST_MODE
#endif
                              ,
    .detect_time_interval   = 50,
};
#endif

#if TCFG_VIR_UDISK_ENABLE
extern const struct device_operations ram_disk_dev_ops;
#endif


#if TCFG_WIFI_ENABLE
#include "wifi/wifi_connect.h"
const struct wifi_calibration_param wifi_calibration_param = {
    .xosc_l     = 0x7,// 调节左晶振电容
    .xosc_r     = 0x7,// 调节右晶振电容
    .pa_trim_data = {1, 7, 4, 7, 11, 1, 7},// 根据MP测试生成PA TRIM值
	.mcs_dgain    = {
        50,//11B_1M
        50,//11B_2.2M
        50,//11B_5.5M
        50,//11B_11M

        72,//11G_6M
        72,//11G_9M
        85,//11G_12M
        80,//11G_18M
        64,//11G_24M
        64,//11G_36M
        62,//11G_48M
        52,//11G_54M

        72,//11N_MCS0
        90,//11N_MCS1
        80,//11N_MCS2
        64,//11N_MCS3
        64,//11N_MCS4
        64,//11N_MCS5
        50,//11N_MCS6
        43,//11N_MCS7
    }
};
#endif


#if TCFG_RTC_ENABLE
static void alarm_wakeup_cb_in_irq(void)
{

}

static void pr_wakeup_cb_in_irq(int port)
{

}

RTC_PLATFORM_DATA_BEGIN(rtc_data)
    .default_sys_time       = {
        .year               = 2024,
        .month              = 1,
        .day                = 1,
        .hour               = 0,
        .min                = 0,
        .sec                = 0,
    },
    .alarm_wakeup_cb_in_irq = alarm_wakeup_cb_in_irq,
    .pr_wakeup_cb_in_irq    = pr_wakeup_cb_in_irq,
    .clk_sel                = TCFG_RTC_CLK_SEL,
    .x32xs                  = TCFG_RTC_X32XS_LEVEL,
RTC_PLATFORM_DATA_END()
#endif


REGISTER_DEVICES(device_table) = {
#if TCFG_UART0_ENABLE
    { "uart0", &uart_dev_ops, (void *) &uart0_data },
#endif
#if TCFG_UART1_ENABLE
    { "uart1", &uart_dev_ops, (void *) &uart1_data },
#endif

#if TCFG_SD0_ENABLE
    { "sd0", &sd_dev_ops, (void *)&sd0_data },
#endif
#if TCFG_SD1_ENABLE
    { "sd1", &sd_dev_ops, (void *)&sd1_data },
#endif

#ifdef CONFIG_AUDIO_ENABLE
    { "audio", &audio_dev_ops, (void *)&audio_data },
#endif

#if TCFG_RTC_ENABLE
    { "rtc", &rtc_dev_ops, (void *)&rtc_data },
#endif

#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
    { "otg", &usb_dev_ops, (void *)&otg_data },
#endif
#if TCFG_UDISK_ENABLE
    { "udisk0", &mass_storage_ops, NULL },
#endif
#if TCFG_VIR_UDISK_ENABLE
    { "vir_udisk", &ram_disk_dev_ops, NULL },
#endif
};


static const power_param_t power_param = {
    .config                 = TCFG_LOWPOWER_FUNCTION,
    .btosc_hz               = 24000000,
    .vddiom_lev             = TCFG_LOWPOWER_VDDIOM_LEVEL,
    .vddiow_lev             = TCFG_LOWPOWER_VDDIOW_LEVEL,
    .vdc14_lev              = TCFG_LOWPOWER_VDC14_LEVEL,
    .osc_type               = TCFG_LOWPOWER_OSC_TYPE,
    .osc_delay_us           = 8000,
#if TCFG_POWER_AVDD18_ENABLE
    .avdd18_enable          = 1,
#endif
#if TCFG_POWER_AVDD28_ENABLE
    .avdd28_enable          = 1,
#endif
};

static const power_pdata_t power_pdata = {
    .power_param            = &power_param,
};

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
static void wakeup_port0_callback_in_irq(p33_io_wkup_edge_t edge)
{

}

static const p33_io_wakeup_config_t wakeup_port0 = {
    .pullup_down_enable     = 1,
    .filter                 = TCFG_LOWPOWER_WAKEUP_PORT0_FILTER,
    .edge                   = TCFG_LOWPOWER_WAKEUP_PORT0_EDGE,
    .gpio                   = TCFG_LOWPOWER_WAKEUP_PORT0_IO,
    .callback               = wakeup_port0_callback_in_irq,
};
#endif

static u32 fusb_io_con = 0;
static u32 husb_io_con = 0;

// 进入、退出低功耗函数回调状态，函数单核操作、关中断，请勿做耗时操作
void sleep_enter_callback(u8 step)
{
    /* 此函数禁止添加打印 */
    putchar('<');

    //USB IO打印引脚特殊处理
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPA) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMA))
    fusb_io_con = JL_PORTFUSB->DIR;
    gpio_close(PORTFUSB, 0xffff);
#endif
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPB) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMB))
    husb_io_con = JL_PORTHUSB->DIR;
    gpio_close(PORTHUSB, 0xffff);
#endif
}

void sleep_exit_callback(u32 usec)
{
    //USB IO打印引脚特殊处理
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPA) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMA))
    JL_PORTFUSB->DIR = fusb_io_con;
#endif
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPB) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMB))
    JL_PORTHUSB->DIR = husb_io_con;
#endif

    putchar('>');
}

//maskrom 使用到的io
static void __mask_io_cfg(void)
{
    struct boot_soft_flag_t g_boot_soft_flag = {0};

    g_boot_soft_flag.flag0.boot_ctrl.wdt_dis                    = 0;
    g_boot_soft_flag.flag0.boot_ctrl.lvd_en                     = 1;
    g_boot_soft_flag.flag0.boot_ctrl.sfc_fast_boot              = 0;
    g_boot_soft_flag.flag0.boot_ctrl.flash_power_keep           = 0;
    g_boot_soft_flag.flag0.boot_ctrl.skip_flash_reset           = 0;
    g_boot_soft_flag.flag0.boot_ctrl.sfc_flash_stable_delay_sel = 0;
    g_boot_soft_flag.flag0.boot_ctrl.flash_stable_delay_sel     = 0;    //0: 0mS;   1: 4mS

    g_boot_soft_flag.flag1.boot_ctrl.fusbdp                      = 0;
    g_boot_soft_flag.flag1.boot_ctrl.fusbdm                      = 0;

    g_boot_soft_flag.flag3.boot_ctrl.husbdp                      = 0;
    g_boot_soft_flag.flag3.boot_ctrl.husbdm                      = 0;

    mask_softflag_config(&g_boot_soft_flag);
}

static void gpio_config_soft_poweroff(void)
{
    PORT_TABLE(g);

#if TCFG_IOKEY_ENABLE
#if TCFG_IOKEY_INPUT0_ENABLE
    PORT_PROTECT(iokey_list[0].key_type.one_io.port);
#endif
#if TCFG_IOKEY_INPUT1_ENABLE
    //cppcheck-suppress arrayIndexOutOfBounds
    PORT_PROTECT(iokey_list[1].key_type.one_io.port);
#endif
#if TCFG_IOKEY_INPUT2_ENABLE
    //cppcheck-suppress arrayIndexOutOfBounds
    PORT_PROTECT(iokey_list[2].key_type.one_io.port);
#endif
#endif

#if TCFG_ADKEY_ENABLE
    PORT_PROTECT(adkey_data.adkey_pin);
#endif

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
    PORT_PROTECT(TCFG_LOWPOWER_WAKEUP_PORT0_IO);
#endif

    __port_init((u32)gpio_config);
}

u8 power_soff_callback(void)
{
    printf("++++++++%s--------", __FUNCTION__);

#if TCFG_RTC_ENABLE
    poweroff_save_rtc_time();
#endif

#if TCFG_ADKEY_ENABLE || TCFG_WIFI_ENABLE || TCFG_RTC_ENABLE
    adc_suspend();
#endif
    /* do_platform_uninitcall(); */

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
    p33_io_wakeup_port_init(&wakeup_port0);
    p33_io_wakeup_enable(TCFG_LOWPOWER_WAKEUP_PORT0_IO, 1);
#endif

    __mask_io_cfg();

    gpio_config_soft_poweroff();

    /* gpio_config_uninit(); */

    return 0;
}

void power_early_flowing(void)
{
    PORT_TABLE(g);

    // 默认关闭长按复位0，由key_driver配置
    gpio_longpress_pin0_reset_config(IO_PORTD_01, 0, 0, 1, 1);

    //前面已经初始化过的IO需要在这里加一下对应IO的保护，否则会被覆盖成高阻状态
#if (defined CONFIG_DEBUG_ENABLE) && (TCFG_DEBUG_PORT != -1)
    PORT_PROTECT(TCFG_DEBUG_PORT);
#endif
#if TCFG_UART_KEY_ENABLE && TCFG_UART_KEY_INPUT_IO != -1
    PORT_PROTECT(TCFG_UART_KEY_INPUT_IO);
#endif

    power_early_init((u32)gpio_config);

    power_set_mode(TCFG_POWER_MODE);

#if TCFG_RTC_ENABLE
    set_rtc_platform_data(&rtc_data);
#endif
}

static void board_power_init(void)
{
    /* gpio_config_init(); */
#if TCFG_RTC_ENABLE
    power_control(PCONTROL_RTC_CLK, TCFG_RTC_CLK_SEL);
#endif
    power_control(PCONTROL_PD_VDDIO_KEEP, VDDIO_KEEP_TYPE_NORMAL);
    power_control(PCONTROL_SF_VDDIO_KEEP, VDDIO_KEEP_TYPE_NORMAL);

    power_init(&power_pdata);
}

#ifdef CONFIG_DEBUG_ENABLE
void debug_uart_init(void)
{
#if TCFG_UART0_ENABLE
    uart_init(&uart0_data);
#endif
}
#endif

void board_early_init(void)
{
    board_power_init();

    devices_init();
}

void board_init(void)
{
#ifdef CONFIG_AUDIO_ENABLE
#if TCFG_AUDIO_DAC_ENABLE || TCFG_AUDIO_ADC_ENABLE
    dac_early_init(dac_data.hw_channel, TCFG_AUDIO_DAC_VCM_CAP_ENABLE);
#endif
#endif

#if TCFG_ADKEY_ENABLE || TCFG_WIFI_ENABLE || TCFG_RTC_ENABLE
    adc_init();
#endif
#if TCFG_RTC_ENABLE
    rtc_early_init();
#endif
#if (TCFG_IOKEY_ENABLE || TCFG_IRKEY_ENABLE || TCFG_RDEC_KEY_ENABLE || TCFG_ADKEY_ENABLE || TCFG_TOUCH_KEY_ENABLE || TCFG_UART_KEY_ENABLE)
    key_driver_init();
#endif
}


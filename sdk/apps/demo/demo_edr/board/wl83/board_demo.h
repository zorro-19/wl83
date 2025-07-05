#ifdef CONFIG_BOARD_DEMO

//*********************************************************************************//
//                                功能模块配置                                     //
//*********************************************************************************//
#define CONFIG_SFC_ENABLE
#define CONFIG_BT_ENABLE
#define CONFIG_AUDIO_ENABLE
#define CONFIG_NO_SDRAM_ENABLE                                //关闭sdram


//*********************************************************************************//
//                                   时钟配置                                      //
//*********************************************************************************//
#define TCFG_OSC_FREQUENCY                  24000000
#define TCFG_SYS_CLK                        192000000         //240M,192M,160M,120M,96M,80M,64M,60M,48M,40M,32M,24M，其他值时启用SYS_PLL
#define TCFG_LSB_CLK                        48000000          //96M,80M,60M,48M,40M,24M,20M,12M
#define TCFG_HSB_CLK_DIV                    2                 //HSB_CLK = SYS_CLK / HSB_CLK_DIV
#define TCFG_SFCTZ_CLK                      48000000          //SFC时钟，和加载代码的速度有关
#define TCFG_SDRAM_CLK                      200000000         //SDRAM/DDR时钟


//*********************************************************************************//
//                                  flash配置                                      //
//*********************************************************************************//
/*
#data_width[1 2 3 4] 3的时候uboot自动识别2或者4线
#clkdiv [1-255] SPITZ_CLK=SYS_CLK/HSB_CLK_DIV/clkdiv
#mode:
#	  0 RD_OUTPUT,		 1 cmd 		 1 addr
#	  1 RD_I/O,   		 1 cmd 		 x addr
#	  2 RD_I/O_CONTINUE] no_send_cmd x add
#port:固定0
*/
#define TCFG_SPITZ_WIDTH_CLKDIV_MODE_PORT   4_3_0_0


//*********************************************************************************//
//                                  sdram配置                                      //
//*********************************************************************************//
#define TCFG_FREE_DCACHE_WAY                0
#define TCFG_SDRAM_MODE                     1              //0-sdram    1-ddr1


//*********************************************************************************//
//                                  UART配置                                       //
//*********************************************************************************//
#define TCFG_DEBUG_PORT                     IO_PORTD_01
#define TCFG_UBOOT_DEBUG_PORT               PD01
#define TCFG_UART_KEY_INPUT_IO              -1
#define TCFG_UART_KEY_ENABLE                0              //串口按键

#define TCFG_UART0_ENABLE                   1              //UART0默认用来打印口
#define TCFG_UART0_TX_IO                    TCFG_DEBUG_PORT
#define TCFG_UART0_RX_IO                    TCFG_UART_KEY_INPUT_IO
#define TCFG_UART0_BAUDRATE                 1000000
#define TCFG_UART0_PARITY                   UART_PARITY_DISABLE

#define TCFG_UART1_ENABLE                   1
#define TCFG_UART1_TX_IO                    IO_PORT_USB_DPA
#define TCFG_UART1_RX_IO                    IO_PORT_USB_DMA
#define TCFG_UART1_BAUDRATE                 1000000
#define TCFG_UART1_FLOW_CTL_ENABLE          0
#define TCFG_UART1_RTS_HW_ENABLE            0
#define TCFG_UART1_RTS_RX_THRESH            80
#define TCFG_UART1_MAX_CONTINUE_RECV_CNT    1024
#define TCFG_UART1_RTS_IO                   -1
#define TCFG_UART1_CTS_IO                   -1
#define TCFG_UART1_RTS_IDLE_LEVEL           0
#define TCFG_UART1_CTS_IDLE_LEVEL           0
#define TCFG_UART1_PARITY                   UART_PARITY_DISABLE


//*********************************************************************************//
//                                  AD按键配置                                     //
//*********************************************************************************//
#define TCFG_ADKEY_ENABLE                   1              //AD按键
#define TCFG_ADKEY_INPUT_IO                 IO_PORTD_00
#define TCFG_ADKEY_INPUT_CHANNEL            ADC_IO_CH_PD00

#define ADKEY_UPLOAD_R                      22             //上拉电阻值
#define TCFG_ADC_LEVEL_09                   0x3FF
#define TCFG_ADC_LEVEL_08                   0x3FF
#define TCFG_ADC_LEVEL_07                   0x3FF
#define TCFG_ADC_LEVEL_06                   0x3FF
#define TCFG_ADC_LEVEL_05                   0x3FF
#define TCFG_ADC_LEVEL_04                   (ADC_VDDIO * 100 / (100 + ADKEY_UPLOAD_R))
#define TCFG_ADC_LEVEL_03                   (ADC_VDDIO * 33  / (33  + ADKEY_UPLOAD_R))
#define TCFG_ADC_LEVEL_02                   (ADC_VDDIO * 15  / (15  + ADKEY_UPLOAD_R))
#define TCFG_ADC_LEVEL_01                   (ADC_VDDIO * 51  / (51  + ADKEY_UPLOAD_R * 10))
#define TCFG_ADC_LEVEL_00                   (0)

#define TCFG_ADKEY_VALUE_0                  KEY_POWER
#define TCFG_ADKEY_VALUE_1                  KEY_MODE
#define TCFG_ADKEY_VALUE_2                  KEY_UP
#define TCFG_ADKEY_VALUE_3                  KEY_DOWN
#define TCFG_ADKEY_VALUE_4                  KEY_OK
#define TCFG_ADKEY_VALUE_5                  KEY_CANCLE
#define TCFG_ADKEY_VALUE_6                  KEY_ENC
#define TCFG_ADKEY_VALUE_7                  KEY_PHOTO
#define TCFG_ADKEY_VALUE_8                  KEY_F1
#define TCFG_ADKEY_VALUE_9                  NO_KEY


//*********************************************************************************//
//                                AUDIO DAC配置                                    //
//*********************************************************************************//
#define TCFG_AUDIO_DAC_ENABLE               1
#define TCFG_AUDIO_DAC_PA_AUTO_MUTE_ENABLE  1
#define TCFG_AUDIO_DAC_PA_MUTE_PORT         IO_PORTE_15
#define TCFG_AUDIO_DAC_PA_MUTE_LEVEL        0
#define TCFG_AUDIO_DAC_DIFFER_OUTPUT_ENABLE 1
#define TCFG_AUDIO_DAC_HW_CHANNEL           (AUDIO_DAC_CH_L | AUDIO_DAC_CH_R)
#define TCFG_AUDIO_DAC_VCM_CAP_ENABLE       1
#if TCFG_AUDIO_DAC_VCM_CAP_ENABLE
#define TCFG_AUDIO_DAC_VCM_INIT_DELAY_MS    1000
#else
#define TCFG_AUDIO_DAC_VCM_INIT_DELAY_MS    0
#endif
#define TCFG_AUDIO_DAC_PA_MUTE_DELAY_MS     500


//*********************************************************************************//
//                                AUDIO ADC配置                                    //
//*********************************************************************************//
//--- AIN_AP0: PC7 AIN_AN0: PC6 AIN_BP0: PC11 AIN_BN0: PC12
//--- AIN_AP1: PC3 AIN_AN1: PC2 AIN_BP1: PC4  AIN_BN1: PC5
#define TCFG_AUDIO_ADC_ENABLE               1
#define TCFG_MIC_IO_PORT                    {IO_PORTC_07/*MIC0P*/, IO_PORTC_06/*MIC0N*/, -1/*MIC1P*/, -1/*MIC1N*/}
#define TCFG_MIC_CHANNEL_NUM                1
#define TCFG_LINEIN_IO_PORT                 {-1/*AUX0P*/, -1/*AUX0N*/, IO_PORTC_11/*AUX1P*/, IO_PORTC_12/*AUX1N*/}
#define TCFG_LINEIN_CHANNEL_NUM             1
#define TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN     0
#define TCFG_DMIC_ENABLE                    0
#define TCFG_DMIC_SCLK_FREQUENCY            2000000
#define TCFG_DMIC_IO_SCLK                   IO_PORTC_11
#define TCFG_DMIC_IO_IDAT0                  IO_PORTA_11
#define TCFG_DMIC_IO_IDAT1                  IO_PORTA_11


//*********************************************************************************//
//                            AUDIO_ADC应用的通道配置                              //
//*********************************************************************************//
#define TCFG_MIC_ADC_CHANNEL_L              0
#define TCFG_MIC_ADC_CHANNEL_R              1
#define TCFG_PHONE_CALL_ADC_CHANNEL         0              //通话mic通道
#define TCFG_AEC_ADC_CHANNEL                1              //回采通道
#define TCFG_AEC_ADC_GAIN                   20             //回采通道增益
#define TCFG_SBC_ENCODER_CHANNEL_NUM        1              //发射器SBC编码通道数
#define TCFG_SBC_ENCODER_SAMPLERATE         16000          //发射器SBC编码采样率


//*********************************************************************************//
//                              电源低功耗配置                                     //
//*********************************************************************************//
#define TCFG_POWER_MODE                     PWR_DCDC15
#define TCFG_POWER_INTERNAL_VDDIO_ENABLE    1
#define TCFG_POWER_AVDD18_ENABLE            1
#define TCFG_POWER_AVDD28_ENABLE            1

#if TCFG_POWER_INTERNAL_VDDIO_ENABLE
#define TCFG_LOWPOWER_VDDIOM_LEVEL          VDDIOM_VOL_330V//强VDDIO电压档位
#else
#define TCFG_LOWPOWER_VDDIOM_LEVEL          VDDIOM_VOL_320V//强VDDIO电压档位，不要高于外部DCDC的电压
#endif
#define TCFG_LOWPOWER_VDDIOW_LEVEL          VDDIOW_VOL_200V //弱VDDIO电压档位
#define TCFG_LOWPOWER_VDC14_LEVEL           DCVDD_VOL_140V
#define TCFG_LOWPOWER_FUNCTION              LOWPOWER_CLOSE
#define TCFG_LOWPOWER_OSC_TYPE              OSC_TYPE_LRC

#define TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE   0
#define TCFG_LOWPOWER_WAKEUP_PORT0_IO       IO_PORTA_01
#define TCFG_LOWPOWER_WAKEUP_PORT0_EDGE     FALLING_EDGE
#define TCFG_LOWPOWER_WAKEUP_PORT0_FILTER   PORT_FLT_DISABLE

#endif

#ifdef CONFIG_BOARD_DEMO

//*********************************************************************************//
//                                功能模块配置                                     //
//*********************************************************************************//
#define CONFIG_SFC_ENABLE
#define CONFIG_NET_ENABLE
#define CONFIG_AUDIO_ENABLE
// #define CONFIG_NO_SDRAM_ENABLE                                //关闭sdram


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
#define TCFG_UART_KEY_INPUT_IO              -1//IO_PORTE_11
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
//                                  SDIO配置                                       //
//*********************************************************************************//
#define TCFG_SD0_ENABLE                     1
#define TCFG_SD0_DAT_WIDTH                  4              //1:单线模式, 4:四线模式
#define TCFG_SD0_DET_MODE                   SD_CLK_DECT    //检测模式:命令检测，时钟检测，IO检测
#define TCFG_SD0_DET_IO                     IO_PORTD_01    //SD_DET_MODE为SD_IO_DECT时有效
#define TCFG_SD0_DET_IO_LEVEL               0              //IO检卡上线的电平(0/1),SD_DET_MODE为SD_IO_DECT时有效
#define TCFG_SD0_CLK                        48000000       //SDIO时钟
#define TCFG_SD0_HD_LEVEL                   0              //强驱等级
#define TCFG_SD0_POWER_ENABLE               0
#define TCFG_SD0_PORTS_GROUP                'A'            //'A''B''C''D'表示使用固定组IO
#define TCFG_SD0_PORTS                      {\
												IO_PORTD_07,	\
												IO_PORTD_06,	\
												IO_PORTD_05,	\
												IO_PORTD_04,	\
												IO_PORTD_03,	\
												IO_PORTD_02,	\
											}              //CLK  CMD  SD0  SD1  SD2  SD3


#define TCFG_SD1_ENABLE                     0
#define TCFG_SD1_DAT_WIDTH                  4              //1:单线模式, 4:四线模式
#define TCFG_SD1_DET_MODE                   SD_CMD_DECT    //检测模式:命令检测，时钟检测，IO检测
#define TCFG_SD1_DET_IO                     -1             //SD_DET_MODE为SD_IO_DECT时有效
#define TCFG_SD1_DET_IO_LEVEL               0              //IO检卡上线的电平(0/1),SD_DET_MODE为SD_IO_DECT时有效
#define TCFG_SD1_CLK                        24000000       //SDIO时钟
#define TCFG_SD1_HD_LEVEL                   0              //强驱等级
#define TCFG_SD1_POWER_ENABLE               0
#define TCFG_SD1_PORTS_GROUP                'A'            //'A''B'表示使用固定组IO
#define TCFG_SD1_PORTS                      {\
												IO_PORTB_15,	\
												IO_PORTB_14,	\
												IO_PORTB_13,	\
												IO_PORTB_12,	\
												IO_PORTB_11,	\
												IO_PORTB_10,	\
											}              //CLK  CMD  SD0  SD1  SD2  SD3


//*********************************************************************************//
//                                  AD按键配置                                     //
//*********************************************************************************//
#define TCFG_ADKEY_ENABLE                   1              //AD按键
#define TCFG_PRESS_LONG_KEY_POWERON_ENABLE  TCFG_ADKEY_ENABLE       //长按开关机功能
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
//                                    IR配置                                       //
//*********************************************************************************//
#define TCFG_IRKEY_ENABLE                   0
#define TCFG_IRKEY_TIMER_INDEX              5
#define TCFG_IRKEY_INPUT_IO                 IO_PORTC_10


//*********************************************************************************//
//                                   QDEC配置                                      //
//*********************************************************************************//
#define TCFG_RDEC_KEY_ENABLE                0
#define TCFG_QDEC0_ENABLE                   1
#define TCFG_QDEC0_MODE                     RDEC_PHASE_1
#define TCFG_QDEC0_CLK_SPND                 0xf
#define TCFG_QDEC0_INPUT_IO_A               IO_PORTE_12
#define TCFG_QDEC0_INPUT_IO_B               IO_PORTE_13
#define TCFG_QDEC0_KEY_VALUE_A              KEY_VOLUME_INC
#define TCFG_QDEC0_KEY_VALUE_B              KEY_VOLUME_DEC


//*********************************************************************************//
//                                  IO按键配置                                     //
//*********************************************************************************//
#define TCFG_IOKEY_ENABLE                   0
#define TCFG_IOKEY_INPUT0_ENABLE            1
#define TCFG_IOKEY_INPUT0_CONNECT_WAY       ONE_PORT_TO_LOW
#define TCFG_IOKEY_INPUT0_IO                IO_PORTC_00
#define TCFG_IOKEY_INPUT0_VALUE             KEY_VOLUME_DEC
#define TCFG_IOKEY_INPUT1_ENABLE            1
#define TCFG_IOKEY_INPUT1_CONNECT_WAY       ONE_PORT_TO_LOW
#define TCFG_IOKEY_INPUT1_IO                IO_PORTC_01
#define TCFG_IOKEY_INPUT1_VALUE             KEY_VOLUME_INC
#define TCFG_IOKEY_INPUT2_ENABLE            1
#define TCFG_IOKEY_INPUT2_CONNECT_WAY       ONE_PORT_TO_LOW
#define TCFG_IOKEY_INPUT2_IO                IO_PORTC_02
#define TCFG_IOKEY_INPUT2_VALUE             KEY_MODE


//*********************************************************************************//
//                                 触摸按键配置                                    //
//*********************************************************************************//
#define TCFG_TOUCH_KEY_ENABLE               0
#define TOUCH_KEY_CLOCK_SOURCE              TOUCH_KEY_CLK_PLL_480M
#define TCFG_TOUCH_KEY0_ENABLE              1
#define TCFG_TOUCH_KEY0_PORT                IO_PORTC_09
#define TCFG_TOUCH_KEY0_VALUE               KEY_OK
#define TCFG_TOUCH_KEY0_PRESS_DELTA         100
#define TCFG_TOUCH_KEY1_ENABLE              0
#define TCFG_TOUCH_KEY1_PORT                IO_PORTA_00
#define TCFG_TOUCH_KEY1_VALUE               KEY_VOLUME_DEC
#define TCFG_TOUCH_KEY1_PRESS_DELTA         100
#define TCFG_TOUCH_KEY2_ENABLE              0
#define TCFG_TOUCH_KEY2_PORT                IO_PORTC_08
#define TCFG_TOUCH_KEY2_VALUE               KEY_VOLUME_INC
#define TCFG_TOUCH_KEY2_PRESS_DELTA         100


//*********************************************************************************//
//                                AUDIO DAC配置                                    //
//*********************************************************************************//
#define TCFG_AUDIO_DAC_ENABLE               1
#define TCFG_AUDIO_DAC_PA_AUTO_MUTE_ENABLE  1
#define TCFG_AUDIO_DAC_PA_MUTE_PORT         IO_PORTE_15
#define TCFG_AUDIO_DAC_PA_MUTE_LEVEL        0
#define TCFG_AUDIO_DAC_DIFFER_OUTPUT_ENABLE 0
#define TCFG_AUDIO_DAC_HW_CHANNEL           (AUDIO_DAC_CH_L)// | AUDIO_DAC_CH_R)
#define TCFG_AUDIO_DAC_VCM_CAP_ENABLE       0
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
#define TCFG_MIC_IO_PORT                    {IO_PORTC_07/*MIC0P*/, IO_PORTC_06/*MIC0N*/, IO_PORTC_11/*MIC1P*/, IO_PORTC_12/*MIC1N*/}
#define TCFG_MIC_CHANNEL_NUM                2
#define TCFG_MIC_SHARE_MICBIAS_ENABLE       0 //使用到两个mic时候，共用偏置电压MICBIASB:PC10使用
#define TCFG_MIC_OTHER_POWER_ENABLE         0 //不使用micbias使能普通io或外部ldo供电做mic电源
#define TCFG_MIC_OTHER_POWER_IO_PORT        {-1/*MIC0_POWER*/, -1/*MIC1_POWER*/} //不使用micbias时的供电io，外部ldo供电填-1
#define TCFG_LINEIN_IO_PORT                 {IO_PORTC_07/*AUX0P*/, IO_PORTC_06/*AUX0N*/, IO_PORTC_11/*AUX1P*/, IO_PORTC_12/*AUX1N*/}
#define TCFG_LINEIN_CHANNEL_NUM             2
#define TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN     1
#define TCFG_DMIC_ENABLE                    0
#define TCFG_DMIC_SCLK_FREQUENCY            2000000
#define TCFG_DMIC_IO_SCLK                   IO_PORTC_11
#define TCFG_DMIC_IO_IDAT0                  IO_PORTA_11
#define TCFG_DMIC_IO_IDAT1                  IO_PORTA_11


//*********************************************************************************//
//                                   PLNK配置                                      //
//*********************************************************************************//
#define TCFG_PLNK_ENABLE                    1
#define TCFG_PLNK_HW_CHANNEL                PLNK_CH_MIC_DAT0
#define TCFG_PLNK_INPUT_DAT_SHARE_IO_ENABLE 0
#define TCFG_PLNK_SCLK_IO                   IO_PORTC_11
#define TCFG_PLNK_INPUT_DAT0_IO             IO_PORTA_11
#define TCFG_PLNK_INPUT_DAT1_IO             IO_PORTA_11
#define TCFG_PLNK_SCLK_FREQUENCY            2000000
#define TCFG_PLNK_CH0_SAMPLE_MODE           DATA0_SCLK_RISING_EDGE_SAMPLE
#define TCFG_PLNK_CH1_SAMPLE_MODE           DATA0_SCLK_FALLING_EDGE_SAMPLE
#define TCFG_PLNK_CIC_ORDER                 3
#define TCFG_PLNK_CIC_DFDLY_M               2


//*********************************************************************************//
//                                   ALNK配置                                      //
//*********************************************************************************//
#define TCFG_ALNK_ENABLE                    1
#define TCFG_ALNK_PORTS                     {\
                                                IO_PORTC_03/*MCLK*/, IO_PORTB_14/*LRCLK*/, IO_PORTB_13/*SCLK*/, \
                                                IO_PORTC_00/*DAT0*/, IO_PORTB_12/*DAT1*/, IO_PORTB_08/*DAT2*/, IO_PORTB_11/*DAT3*/, \
                                            }
#define TCFG_ALNK_CHANNLE_IN_MAP            ALNK_INPUT_CHANNEL1
#define TCFG_ALNK_CHANNLE_OUT_MAP           ALNK_OUTPUT_CHANNEL0
#define TCFG_ALNK_DATA_WIDTH                0
#define TCFG_ALNK_MODE                      ALNK_BASIC_IIS_MODE
#define TCFG_ALNK_DMA_MODE                  ALNK_DMA_PINGPANG_BUFFER
#define TCFG_ALNK_SLAVE_MODE_ENABLE         0
#define TCFG_ALNK_MCLK_SRC                  ALNK_MCLK_FROM_PLL_ALNK_CLOCK
#define TCFG_ALNK_UPDATE_EDGE               0


//*********************************************************************************//
//                            AUDIO_ADC应用的通道配置                              //
//*********************************************************************************//
#define AUDIO_ENC_SAMPLE_SOURCE_MIC         0  //录音输入源：MIC
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK0       1  //录音输入源：数字麦PLNK0
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK1       2  //录音输入源：数字麦PLNK1
#define AUDIO_ENC_SAMPLE_SOURCE_IIS0        3  //录音输入源：IIS0
#define AUDIO_ENC_SAMPLE_SOURCE_IIS1        4  //录音输入源：IIS1
#define AUDIO_ENC_SAMPLE_SOURCE_LINEIN      5  //录音输入源：LINEIN

#define CONFIG_AUDIO_ENC_SAMPLE_SOURCE      AUDIO_ENC_SAMPLE_SOURCE_MIC    //录音输入源选择
#define CONFIG_AUDIO_DEC_PLAY_SOURCE        "dac"                          //播放输出源选择
#define CONFIG_AUDIO_RECORDER_SAMPLERATE    16000                          //录音采样率
#define CONFIG_AUDIO_RECORDER_CHANNEL       1                              //录音通道数
#define CONFIG_AUDIO_RECORDER_DURATION      (30 * 1000)                    //录音时长ms
#define CONFIG_AUDIO_RECORDER_SAVE_FORMAT   "wav"                          //录音文件保存格式
#define CONFIG_AUDIO_RECORDER_PLAY_FORMAT   "pcm"                          //自编自解格式仅支持pcm/mp3/aac/jla/amr/opus/ogg/speex格式

#define CONFIG_AUDIO_ADC_CHANNEL_L          0        //左mic/aux通道
#define CONFIG_AUDIO_ADC_CHANNEL_R          1        //右mic/aux通道
#define CONFIG_UAC_MIC_ADC_CHANNEL          0        //UAC mic通道
#define CONFIG_AUDIO_ADC_GAIN               100      //mic/aux增益

#define CONFIG_AISP_MIC0_ADC_CHANNEL        0		//本地唤醒左mic通道
#define CONFIG_AISP_MIC1_ADC_CHANNEL        1		//本地唤醒右mic通道
#define CONFIG_AISP_LINEIN_ADC_CHANNEL      1		//本地唤醒LINEIN回采DAC通道
#define CONFIG_AISP_MIC_ADC_GAIN            80		//本地唤醒mic增益
#define CONFIG_AISP_LINEIN_ADC_GAIN         60		//本地唤醒LINEIN增益


//*********************************************************************************//
//                                  EQ配置                                         //
//*********************************************************************************//
//EQ配置，使用在线EQ时，EQ文件和EQ模式无效。有EQ文件时，默认不用EQ模式切换功能
#define TCFG_EQ_ENABLE                      0              //支持EQ功能
#define TCFG_EQ_ONLINE_ENABLE               0              //支持在线EQ调试
#define TCFG_LIMITER_ENABLE                 1              //限幅器
#define TCFG_EQ_FILE_ENABLE                 1              //从bin文件读取eq配置数据
#define TCFG_DRC_ENABLE                     TCFG_LIMITER_ENABLE
#define TCFG_EQ_MODE_CHOOSE                 0              //0:多通道共用1个eq, drc功能丰富; 1:多通道独立eq,独立drc, 请替换对应的bin文件
#if (TCFG_EQ_MODE_CHOOSE == 0)
#define TCFG_AUDIO_MDRC_ENABLE              2              //0:不使能低中DRC 1: 多带分频器使能 2: 多带分频后，再做一次全带处理使能
#define TCFG_LAST_WHOLE_DRC_ENABLE          1              //0:不使能最后的全带DRC; 1:使能
#elif (TCFG_EQ_MODE_CHOOSE == 1)
#define TCFG_EQ_DIVIDE_ENABLE               1              //0:前后通道共用EQ/DRC  1:支持EQ/DRC前后声道独立处理
#define TCFG_EQ_SPILT_ENABLE                1              //0:左右通道共用EQ  1:支持EQ左右声道独立处理
#define TCFG_DRC_SPILT_ENABLE               1              //0:左右通道共用DRC 1:支持DRC左右声道独立处理
#endif
#define TCFG_NULL_COMM                      0              //不支持通信
#define TCFG_USB_COMM                       1              //USB通信
#define TCFG_COMM_TYPE                      TCFG_USB_COMM  //EQ在线调试通信类型


//*********************************************************************************//
//                                  USB配置                                        //
//*********************************************************************************//
#define TCFG_FUSB_DEVICE                    BIT(0)
#define TCFG_HUSB_DEVICE                    BIT(1)
#define TCFG_USB_DEVICE                     TCFG_FUSB_DEVICE | TCFG_HUSB_DEVICE

//*********************************************************************************//
//                                USB从机配置                                      //
//*********************************************************************************//
#define TCFG_PC_ENABLE                      0              //使用USB从机功能一定要打开
#define USB_PC_NO_APP_MODE                  2
#define USB_MALLOC_ENABLE                   1
#if TCFG_EQ_ONLINE_ENABLE
#define USB_DEVICE_CLASS_CONFIG             (CDC_CLASS)
#elif defined CONFIG_AUDIO_ENABLE
#define USB_DEVICE_CLASS_CONFIG             (MASSSTORAGE_CLASS | AUDIO_CLASS)
#define USB_DEVICE_CLASS_CONFIG_2_0         (MASSSTORAGE_CLASS | AUDIO_CLASS)
#else
#define USB_DEVICE_CLASS_CONFIG             (MASSSTORAGE_CLASS)
#define USB_DEVICE_CLASS_CONFIG_2_0         (MASSSTORAGE_CLASS)
#endif
#define TCFG_VIR_UDISK_ENABLE               0              //虚拟U盘, 需要使能从机MASSSTORAGE_CLASS
#if TCFG_VIR_UDISK_ENABLE
#define TCFG_USER_VIRTUAL_PLAY_ENABLE       0
#define TCFG_USER_VIRTUAL_PLAY_SAMPLERATE   44100
#endif

//*********************************************************************************//
//                                USB主机配置                                      //
//*********************************************************************************//
#define TCFG_UDISK_ENABLE                   1              //U盘主机功能
#if defined CONFIG_AUDIO_ENABLE
#define TCFG_HOST_AUDIO_ENABLE              1              //uac主机功能，用户需要自己补充uac_host_demo.c里面的两个函数
#endif

#include "usb_std_class_def.h"
#include "usb_common_def.h"


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


//*********************************************************************************//
//                                  RTC配置                                        //
//*********************************************************************************//
#define TCFG_RTC_ENABLE                     1
#define TCFG_RTC_CLK_SEL                    CLK_SEL_32K
#define TCFG_RTC_X32XS_LEVEL                X32XS_LEVEL_1


//*********************************************************************************//
//                                 WIFI配置                                        //
//*********************************************************************************//
#ifdef CONFIG_NET_ENABLE
#define TCFG_WIFI_ENABLE                    1
#endif


#endif

#ifndef __USB_STD_CLASS_DEF_H__
#define __USB_STD_CLASS_DEF_H__

#ifndef USB_MALLOC_ENABLE
#define USB_MALLOC_ENABLE           0
#endif
#ifndef USB_HOST_ASYNC
#define USB_HOST_ASYNC              1
#endif
#ifndef USB_H_MALLOC_ENABLE
#define USB_H_MALLOC_ENABLE         1
#endif
#ifndef USB_DEVICE_CLASS_CONFIG
#define USB_DEVICE_CLASS_CONFIG     (SPEAKER_CLASS|MIC_CLASS|HID_CLASS|MASSSTORAGE_CLASS)
#endif
#ifndef USB_DEVICE_CLASS_CONFIG_2_0
#define USB_DEVICE_CLASS_CONFIG_2_0 0
#endif

///////////MassStorage Class
#ifndef MSD_BULK_EP_OUT
#define MSD_BULK_EP_OUT             1
#endif
#ifndef MSD_BULK_EP_IN
#define MSD_BULK_EP_IN              1
#endif
#ifndef MAXP_SIZE_BULKOUT_FS
#define MAXP_SIZE_BULKOUT_FS        64
#endif
#ifndef MAXP_SIZE_BULKIN_FS
#define MAXP_SIZE_BULKIN_FS         64
#endif
#ifndef MAXP_SIZE_BULKOUT_HS
#define MAXP_SIZE_BULKOUT_HS        512
#endif
#ifndef MAXP_SIZE_BULKIN_HS
#define MAXP_SIZE_BULKIN_HS         512
#endif
#ifndef MAXP_SIZE_BULKOUT
#define MAXP_SIZE_BULKOUT           MAXP_SIZE_BULKOUT_FS
#endif
#ifndef MAXP_SIZE_BULKIN
#define MAXP_SIZE_BULKIN            MAXP_SIZE_BULKIN_FS
#endif
#ifndef MSD_STR_INDEX
#define MSD_STR_INDEX               7
#endif

///////////HID class
#ifndef HID_EP_IN
#define HID_EP_IN                   2
#endif
#ifndef HID_EP_OUT
#define HID_EP_OUT                  2
#endif
#ifndef MAXP_SIZE_HIDOUT
#define MAXP_SIZE_HIDOUT            64
#endif
#ifndef MAXP_SIZE_HIDIN
#define MAXP_SIZE_HIDIN             64
#endif
#ifndef HID_INTR_INTERVAL_FS
#define HID_INTR_INTERVAL_FS        1
#endif
#ifndef HID_INTR_INTERVAL_HS
#define HID_INTR_INTERVAL_HS        4
#endif
#ifndef HID_INTR_INTERVAL
#define HID_INTR_INTERVAL           HID_INTR_INTERVAL_FS
#endif
#ifndef HID_INTR_INTERVAL_2_0
#define HID_INTR_INTERVAL_2_0       4
#endif

/////////////Audio Class
#define USB_AUDIO_VERSION_1_0       0x10
#define USB_AUDIO_VERSION_2_0       0x20
#ifndef USB_AUDIO_VERSION
#define USB_AUDIO_VERSION           USB_AUDIO_VERSION_1_0
#endif
#ifndef UAC_ISO_INTERVAL_FS
#define UAC_ISO_INTERVAL_FS         1
#endif
#ifndef UAC_ISO_INTERVAL_HS
#define UAC_ISO_INTERVAL_HS         4
#endif
#ifndef UAC_ISO_INTERVAL
#define UAC_ISO_INTERVAL            UAC_ISO_INTERVAL_FS
#endif
#ifndef UAC_24BIT_IN_4BYTE
//0: 24bit in 3byte, 1: 24 bit in 4byte
//Windows不支持这种数据格式，安卓支持这种数据格式
#define UAC_24BIT_IN_4BYTE          0
#endif
//speaker class
#ifndef SPK_AUDIO_RATE_NUM
#define SPK_AUDIO_RATE_NUM          1
#endif
#if SPK_AUDIO_RATE_NUM == 1
#define SPK_AUDIO_RATE              48000
#else
#define SPK_AUDIO_RATE              96000
#define SPK_AUDIO_RATE_1            44100
#define SPK_AUDIO_RATE_2            48000
#endif
#ifndef SPK_AUDIO_RES
#define SPK_AUDIO_RES               16
#endif
#ifndef SPK_AUDIO_RES_2
#define SPK_AUDIO_RES_2             0//24
#endif
#ifndef SPK_CHANNEL
#define SPK_CHANNEL                 2
#endif
#ifndef SPK_FRAME_LEN
#define SPK_FRAME_LEN               (((SPK_AUDIO_RATE) * SPK_AUDIO_RES / 8 * SPK_CHANNEL)/1000+4)
#endif
#ifndef SPK_PCM_TYPE
#define SPK_PCM_TYPE                (SPK_AUDIO_RES >> 4)                // 0=8 ,1=16
#endif
#ifndef SPK_AUDIO_TYPE
#define SPK_AUDIO_TYPE              (0x02 - SPK_PCM_TYPE)           // TYPE1_PCM16
#endif
#ifndef SPK_ISO_EP_OUT
#define SPK_ISO_EP_OUT              3
#endif
#ifndef SPEAKER_STR_INDEX
#define SPEAKER_STR_INDEX           5
#endif
#ifndef SPK_INPUT_TERMINAL_ID
#define SPK_INPUT_TERMINAL_ID       1
#endif
#ifndef SPK_FEATURE_UNIT_ID
#define SPK_FEATURE_UNIT_ID         2
#endif
#ifndef SPK_OUTPUT_TERMINAL_ID
#define SPK_OUTPUT_TERMINAL_ID      3
#endif
#ifndef SPK_SELECTOR_UNIT_ID
#define SPK_SELECTOR_UNIT_ID        8
#endif

/////////////Microphone Class
#ifndef MIC_AUDIO_RATE_NUM
#define MIC_AUDIO_RATE_NUM          1
#endif
#if MIC_AUDIO_RATE_NUM == 1
#define MIC_AUDIO_RATE              48000
#else
#define MIC_AUDIO_RATE              192000
#define MIC_AUDIO_RATE_1            44100
#define MIC_AUDIO_RATE_2            48000
#define MIC_AUDIO_RATE_4            96000
#endif
#ifndef MIC_AUDIO_RES
#define MIC_AUDIO_RES               16
#endif
#ifndef MIC_AUDIO_RES_2
#define MIC_AUDIO_RES_2             0//24
#endif
#ifndef MIC_CHANNEL
#define MIC_CHANNEL                 1
#endif
#ifndef MIC_FRAME_LEN
#define MIC_FRAME_LEN               ((MIC_AUDIO_RATE * MIC_AUDIO_RES / 8 * MIC_CHANNEL)/1000)
#endif
#ifndef MIC_PCM_TYPE
#define MIC_PCM_TYPE                (MIC_AUDIO_RES >> 4)                // 0=8 ,1=16
#endif
#ifndef MIC_AUDIO_TYPE
#define MIC_AUDIO_TYPE              (0x02 - MIC_PCM_TYPE)
#endif
#ifndef MIC_ISO_EP_IN
#define MIC_ISO_EP_IN               3
#endif
#ifndef MIC_STR_INDEX
#define MIC_STR_INDEX               6
#endif
#ifndef MIC_INPUT_TERMINAL_ID
#define MIC_INPUT_TERMINAL_ID       4
#endif
#ifndef MIC_FEATURE_UNIT_ID
#define MIC_FEATURE_UNIT_ID         5
#endif
#ifndef MIC_OUTPUT_TERMINAL_ID
#define MIC_OUTPUT_TERMINAL_ID      6
#endif
#ifndef MIC_SELECTOR_UNIT_ID
#define MIC_SELECTOR_UNIT_ID        7
#endif

////////////CDC Class
#ifndef CDC_DATA_EP_IN
#define CDC_DATA_EP_IN              2
#endif
#ifndef CDC_DATA_EP_OUT
#define CDC_DATA_EP_OUT             2
#endif
#ifndef CDC_INTR_FUSB_EP_IN
#define CDC_INTR_FUSB_EP_IN         4
#endif
#ifndef CDC_INTR_HUSB_EP_IN
#define CDC_INTR_HUSB_EP_IN         6
#endif
#ifndef MAXP_SIZE_CDC_BULKIN_FS
#define MAXP_SIZE_CDC_BULKIN_FS     64
#endif
#ifndef MAXP_SIZE_CDC_BULKOUT_FS
#define MAXP_SIZE_CDC_BULKOUT_FS    64
#endif
#ifndef MAXP_SIZE_CDC_BULKIN_HS
#define MAXP_SIZE_CDC_BULKIN_HS     256
#endif
#ifndef MAXP_SIZE_CDC_BULKOUT_HS
#define MAXP_SIZE_CDC_BULKOUT_HS    256
#endif
#ifndef MAXP_SIZE_CDC_INTRIN
#define MAXP_SIZE_CDC_INTRIN        8
#endif
#ifndef CDC_INTR_INTERVAL_FS
#define CDC_INTR_INTERVAL_FS        1
#endif
#ifndef CDC_INTR_INTERVAL_HS
#define CDC_INTR_INTERVAL_HS        4
#endif
#ifndef CDC_INTR_INTERVAL
#define CDC_INTR_INTERVAL           CDC_INTR_INTERVAL_FS
#endif
#ifndef CDC_INTR_EP_ENABLE
#define CDC_INTR_EP_ENABLE          0
#endif

///////////USB Video Class
#ifndef UVC_ISO_MODE
#define UVC_ISO_MODE                1
#endif
#ifndef UVC_STREAM_EP_IN
#define UVC_STREAM_EP_IN            4
#endif
#ifndef VIDEO_STATUS_EP_IN
#define VIDEO_STATUS_EP_IN          5
#endif
#ifndef VIDEO_STR_INDEX
#define VIDEO_STR_INDEX             8
#endif

#if UVC_ISO_MODE
#define UVC_FIFO_TXMAXP             1023
#define UVC_PKT_SPILT               1
#else
#define UVC_FIFO_TXMAXP             512
#define UVC_PKT_SPILT               1
#endif

#ifndef VIDEO_STATUS_TXMAXP
#define VIDEO_STATUS_TXMAXP         16
#endif

///////////PRINTER Class
#ifndef PTR_BULK_EP_OUT
#define PTR_BULK_EP_OUT             2
#endif
#ifndef PTR_BULK_EP_IN
#define PTR_BULK_EP_IN              2
#endif

///////////CUSTOM_HID class
#ifndef CUSTOM_HID_EP_IN
#define CUSTOM_HID_EP_IN            2
#endif
#ifndef CUSTOM_HID_EP_OUT
#define CUSTOM_HID_EP_OUT           2
#endif
#ifndef MAXP_SIZE_CUSTOM_HIDIN
#define MAXP_SIZE_CUSTOM_HIDIN      64
#endif
#ifndef MAXP_SIZE_CUSTOM_HIDOUT
#define MAXP_SIZE_CUSTOM_HIDOUT     64
#endif

//speaker host
#ifndef HOST_SPK_AUDIO_RATE
#define HOST_SPK_AUDIO_RATE         0	//建议不要使用44100采样率，有点数对齐问题
#endif
#ifndef HOST_SPK_AUDIO_RES
#define HOST_SPK_AUDIO_RES          16
#endif
#ifndef HOST_SPK_CHANNEL
#define HOST_SPK_CHANNEL            2
#endif
#ifndef HOST_SPK_VOLUME
#define HOST_SPK_VOLUME             100
#endif

//mic host
#ifndef HOST_MIC_AUDIO_RATE
#define HOST_MIC_AUDIO_RATE         0	//建议不要使用44100采样率，有点数对齐问题
#endif
#ifndef HOST_MIC_AUDIO_RES
#define HOST_MIC_AUDIO_RES          16
#endif
#ifndef HOST_MIC_CHANNEL
#define HOST_MIC_CHANNEL            1
#endif
#ifndef HOST_MIC_VOLUME
#define HOST_MIC_VOLUME             100
#endif

#endif

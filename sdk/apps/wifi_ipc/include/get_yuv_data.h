#ifndef _GET_YUV_DATA_H_
#define _GET_YUV_DATA_H_

#include "app_config.h"



#ifdef CONFIG_VIDEO2_ENABLE
#define YUV_DATA_SOURCE      "video2.2"
#else
#define YUV_DATA_SOURCE      "video0.2"
#endif

#ifndef CONFIG_VIDEO_IMAGE_W
#define CONFIG_VIDEO_IMAGE_W    640
#define CONFIG_VIDEO_IMAGE_H    480
#endif
#define YUV_DATA_WIDTH       CONFIG_VIDEO_IMAGE_W
#define YUV_DATA_HEIGHT      CONFIG_VIDEO_IMAGE_H

typedef struct {
    int pid;
    // void (*cb)(u8 *data, u32 len, int width, int height) ;
    void (*cb)(u8 *data) ;
    char init;
    char exit_state;
} get_yuv_cfg;

void get_yuv_init(void (*cb)(u8 *data, u32 len, int width, int height));
void get_yuv_uninit(void);

#endif //_GET_YUV_DATA_H__

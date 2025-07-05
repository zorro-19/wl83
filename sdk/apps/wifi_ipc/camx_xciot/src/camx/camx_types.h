/****************************************************************************/
/* camx_types.h
 *
 ****************************************************************************/
#ifndef CAMX_TYPES_H_INCLUDE
#define CAMX_TYPES_H_INCLUDE
/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/

#if !defined(CAMX_H_INCLUDE)
#error "Only 'camx.h' can be included directly."
#endif /* CAMX_H_INCLUDE */

/* group */

/****************************************************************************/
/* Configure Definitions                                                    */
/****************************************************************************/

// 抓图最大bytes
#define CAMX_IMAGE_FRAME_MAX_LEN (1024 * 100)

/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/****************************************************************************/
/* Public Types                                                             */
/****************************************************************************/

typedef enum camx_media_src {
    E_CAMX_MEDIA_SRC_REMOTE = (1 << 0),
    E_CAMX_MEDIA_SRC_DEVICE = (1 << 1),
    E_CAMX_MEDIA_SRC_FILE   = (1 << 2),

    /* add above here */
    E_CAMX_MEDIA_SRC_LAST
} camx_media_src_e;

typedef struct camx_video_frame {
    camx_media_src_e src;       ///< 产生数据的源头
    uint64_t         pts;       ///< pts
    uint64_t         timestamp; ///< utc 时间戳
    uint32_t         seq;       ///< 序列号
    uint32_t         len;       ///< 数据长度
    const uint8_t   *data;      ///< 数据
    bool             iskey;     ///< 是否
} camx_video_frame_t;

typedef struct camx_audio_frame {
    camx_media_src_e src;       ///< 产生数据的源头
    uint64_t         pts;       ///< pts
    uint64_t         timestamp; ///< utc 时间戳
    uint32_t         seq;       ///< 序列号
    uint32_t         len;       ///< 数据长度
    const uint8_t   *data;      ///< 数据
} camx_audio_frame_t;

typedef struct camx_image_frame {
    uint64_t pts;
    uint8_t  data[CAMX_IMAGE_FRAME_MAX_LEN];
    uint32_t len;
} camx_image_frame_t;

typedef struct camx_yuv420_frame {
    uint8_t *data;
    uint32_t len;
    int      width;
    int      height;
} camx_yuv420_frame_t;

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************/
/* Public Function Prototypes                                               */
/****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* CAMX_TYPES_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

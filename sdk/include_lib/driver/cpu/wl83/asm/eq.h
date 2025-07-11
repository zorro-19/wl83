#ifndef __AUDIO_EQ_H__
#define __AUDIO_EQ_H__

#include "generic/typedef.h"
#include "generic/list.h"
#include "os/os_api.h"

#define EQ_SECTION_MAX 20

/**
 * @brief EQ运行模式
 */
enum {
    NORMAL = 0,		/*!< 正常模式 */
    MONO,			/*!< 单声道模式 */
    STEREO,			/*!< 立体声模式 */
};

/**
 * @brief 输出数据类型
 */
enum {
    DATO_SHORT = 0, /*!< short短整型 */
    DATO_INT,		/*!< int整型 */
    DATO_FLOAT,		/*!< float浮点型 */
};

/**
 * @brief 输入数据类型
 */
enum {
    DATI_SHORT = 0, /*!< short短整型 */
    DATI_INT,		/*!< int整型 */
    DATI_FLOAT,		/*!< float浮点型 */
};

/**
 * @brief 输入数据存放模式
 */
enum {
    BLOCK_DAT_IN = 0, 	/*!< 块模式，例如输入数据是2通道，先存放完第1通道的所有数据，再存放第2通道的所有数据 */
    SEQUENCE_DAT_IN,	/*!< 序列模式，例如输入数据是2通道，先存放第1通道的第一个数据，再存放第2个通道的第一个数据，以此类推 */
};

/**
 * @brief 输出数据存放模式
 */
enum {
    BLOCK_DAT_OUT = 0,  /*!< 块模式，例如输出数据是2通道，先存放完第1通道的所有数据，再存放第2通道的所有数据 */
    SEQUENCE_DAT_OUT,   /*!< 序列模式，例如输入数据是2通道，先存放第1通道的第一个数据，再存放第2个通道的第一个数据，以此类推 */
};


/**
 * @brief eq IIR type滤波器类型
 */
typedef enum {
    EQ_IIR_TYPE_HIGH_PASS = 0x00,  /*!< 高通滤波器 */
    EQ_IIR_TYPE_LOW_PASS,          /*!< 低通滤波器 */
    EQ_IIR_TYPE_BAND_PASS,         /*!< 带通滤波器 */
    EQ_IIR_TYPE_HIGH_SHELF,        /*!< 高架滤波器 */
    EQ_IIR_TYPE_LOW_SHELF,         /*!< 低架滤波器 */
} EQ_IIR_TYPE;

/**
 * @brief eq段信息
 */
struct eq_seg_info {
    u16 index;            /*!< eq段序号 */
    u16 iir_type;         /*!< 滤波器类型EQ_IIR_TYPE */
    int freq;             /*!< 中心截止频率 */
    float gain;           /*!< 增益（-12 ~12 db） */
    float q;              /*!< q值（0.3~30） */
};

/**
 * @brief eq系数信息
 */
struct eq_coeff_info {
    u16 nsection : 6;                /*!< eq段数 */
    u16 no_coeff : 1;	             /*!< 不是滤波系数 */
#ifdef CONFIG_EQ_NO_USE_COEFF_TABLE
    u32 sr;                          /*!< 采样率 */
#endif
    float *L_coeff;                  /*!< 左声道滤波器系数地址 */
    float *R_coeff;                  /*!< 右声道滤波器系数地址 */
    float L_gain;                    /*!< 左声道总增益(-20~20db) */
    float R_gain;                    /*!< 右声道总增益（-20~20db）*/
    float *N_coeff[8];               /*!< 滤波器系数 */
    float N_gain[8];                 /*!< 滤波器增益 */
};

/// \cond DO_NOT_DOCUMENT
struct hw_eq_ch;
/// \endcond

/**
 * @brief 硬件eq
 */
struct hw_eq {
    struct list_head head;            /*!< 链表头 */
    OS_MUTEX mutex;                   /*!< 互斥锁 */
    struct hw_eq_ch *cur_ch;          /*!< 当前需要处理的eq通道 */
};

/// \cond DO_NOT_DOCUMENT
enum {
    HW_EQ_CMD_CLEAR_MEM = 0xffffff00,
    HW_EQ_CMD_CLEAR_MEM_L,
    HW_EQ_CMD_CLEAR_MEM_R,
};
/// \endcond

/**
 * @brief 硬件eq句柄
 */
struct hw_eq_handler {
    int (*eq_probe)(struct hw_eq_ch *);                   /*!< eq驱动内前处理 */
    int (*eq_output)(struct hw_eq_ch *, s16 *, u16);      /*!< eq驱动内输出处理回调 */
    int (*eq_post)(struct hw_eq_ch *);                    /*!< eq驱动内处理后回调 */
    int (*eq_input)(struct hw_eq_ch *, void **, void **); /*!< eq驱动内输入处理回调 */
};

// *INDENT-OFF*
/**
 * @brief 硬件eq通道信息
 */
struct hw_eq_ch {
    unsigned int updata_coeff_only : 1;	     /*!< 只更新参数，不更新中间数据 */
    unsigned int no_wait : 1;                /*!< 是否是异步eq处理  0：同步的eq  1：异步的eq */
    unsigned int channels : 4;               /*!< 输入通道数 */
    unsigned int SHI : 4;                    /*!< eq运算输出数据左移位数控制,记录*/
    unsigned int countL : 4;                 /*!< eq运算输出数据左移位数控制临时记录 */
    unsigned int stage : 9;                  /*!< eq运算开始位置标识 */
    unsigned int nsection : 6;               /*!< eq段数 */
    unsigned int no_coeff : 1;	             /*!< 非滤波系数 */
    unsigned int reserve : 2;

    volatile unsigned char updata;           /*!< 更新参数以及中间数据 */
    volatile unsigned char active ;          /*!< 已启动eq处理  1：busy  0:处理结束 */
    volatile unsigned char need_run;         /*!< 多eq同时使用时，未启动成功的eq，是否需要重新唤醒处理  1：需要  0：否*/
    unsigned short run_mode: 2;              /*!< 0按照输入的数据排布方式 ，输出数据 1:单入多出，  2：立体声入多出 */
    unsigned short in_mode : 2;              /*!< 输入数据的位宽 0：short  1:int  2:float */
    unsigned short out_32bit : 2;            /*!< 输出数据的位宽 0：short  1:int  2:float */
    unsigned short out_channels: 4;          /*!< 输出通道数 */
    unsigned short data_in_mode: 1;          /*!< 输入数据存放模式 */
    unsigned short data_out_mode: 1;         /*!< 输出数据存放模式*/
#ifdef CONFIG_EQ_NO_USE_COEFF_TABLE
    u32 sr;                                  /*!< 采样率 */
#endif
    float *L_coeff;                          /*!< 输入给左声道系数地址 */
    float *R_coeff;                          /*!< 输入给右声道系数地址 */
    float L_gain;                            /*!< 输入给左声道总增益(-20~20) */
    float R_gain;                            /*!< 输入给右声道总增益(-20~20) */
    float *N_coeff[8];                       /*!<  */
    float N_gain[8];                         /*!<  */
    float *eq_LRmem;                         /*!< eq系数地址（包含运算的中间数据） */
    int ram_inbuf_size;                      /*!< 内部ram输入buf大小 */
    int ram_outbuf_size;                     /*!< 内部ram输出buf大小 */
    s16 *ram_inbuf;                          /*!< 内部ram输入buf地址 */
    s16 *ram_outbuf;                         /*!< 内部ram输出buf地址 */
    s16 *out_buf;                            /*!< 输出buf地址 */
	s16 *tmp_outbuf;				 //临时输出buf地址, 目的为了规避DMA读的慢导致越界问题
	int tmp_outbuf_size;			 //临时输出buf地址大小
    s16 *in_buf;                             /*!< 输入buf地址 */
    int in_len;                              /*!< 输入数据长度 */
    void *priv;                              /*!< 保存eq管理层的句柄 */
    OS_SEM sem;                              /*!< 信号量，用于通知驱动，当前一次处理完成 */
    struct list_head entry;                  /*!< 当前eq通道的节点 */
    struct hw_eq *eq;                        /*!< 底层eq操作句柄 */
    const struct hw_eq_handler *eq_handler;  /*!< q操作的相关回调函数句柄 */
    void *irq_priv;                          /*!< eq管理层传入的私有指针 */
    void (*irq_callback)(void *priv);        /*!< 需要eq中断执行的回调函数 */
};

//系数计算子函数
/*----------------------------------------------------------------------------*/
/**@brief    低通滤波器
   @param    fc:中心截止频率
   @param    fs:采样率
   @param    quality_factor:q值
   @param    coeff:计算后，系数输出地址
*/
/*----------------------------------------------------------------------------*/
void design_lp(int fc, int fs, float quality_factor, float *coeff);

/*----------------------------------------------------------------------------*/
/**@brief    高通滤波器
   @param    fc:中心截止频率
   @param    fs:采样率
   @param    quality_factor:q值
   @param    coeff:计算后，系数输出地址
*/
/*----------------------------------------------------------------------------*/
void design_hp(int fc, int fs, float quality_factor, float *coeff);

/*----------------------------------------------------------------------------*/
/**@brief    带通滤波器
   @param    fc:中心截止频率
   @param    fs:采样率
   @param    gain:增益
   @param    quality_factor:q值
   @param    coeff:计算后，系数输出地址
*/
/*----------------------------------------------------------------------------*/
void design_pe(int fc, int fs, float gain, float quality_factor, float *coeff);

/*----------------------------------------------------------------------------*/
/**@brief    低频搁架式滤波器
   @param    fc:中心截止频率
   @param    fs:采样率
   @param    gain:增益
   @param    quality_factor:q值
   @param    coeff:计算后，系数输出地址
*/
/*----------------------------------------------------------------------------*/
void design_ls(int fc, int fs, float gain, float quality_factor, float *coeff);

/*----------------------------------------------------------------------------*/
/**@brief    高频搁架式滤波器
   @param    fc:中心截止频率
   @param    fs:采样率
   @param    gain:增益
   @param    quality_factor:q值
   @param    coeff:计算后，系数输出地址
*/
/*----------------------------------------------------------------------------*/
void design_hs(int fc, int fs, float gain, float quality_factor, float *coeff);

/*----------------------------------------------------------------------------*/
/**@brief    滤波器系数检查
   @param    coeff:滤波器系数
   @return   0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int eq_stable_check(float *coeff);

float eq_db2mag(float x);

/*----------------------------------------------------------------------------*/
/**@brief    获取直通的滤波器系数
   @param    coeff:滤波器系数
*/
/*----------------------------------------------------------------------------*/
void audio_eq_get_AllpassCoeff(void *Coeff);

/*----------------------------------------------------------------------------*/
/**@brief    滤波器计算管理函数
   @param    seg:提供给滤波器的基本信息
   @param    sample_rate:采样率
   @param    coeff:计算后，系数输出地址
   @return   true:成功 false:失败
*/
/*----------------------------------------------------------------------------*/
int eq_seg_design(struct eq_seg_info *seg, int sample_rate, float *coeff);

/*----------------------------------------------------------------------------*/
/**@brief    打开一个通道
   @param    ch:通道句柄
   @param    eq:句柄
   @return   0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int hw_eq_ch_open(struct hw_eq_ch *ch, struct hw_eq *eq);

/*----------------------------------------------------------------------------*/
/**@brief    设置回调接口
   @param    ch:通道句柄
   @param    handler:回调的句柄
   @return   0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int hw_eq_ch_set_handler(struct hw_eq_ch *ch, struct hw_eq_handler *handler);

/*----------------------------------------------------------------------------*/
/**@brief    设置通道基础信息
   @param    ch:通道句柄
   @param    channels:通道数
   @param    out_32bit:是否输出32bit位宽数据 1：是  0：16bit位宽
   @return   0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int hw_eq_ch_set_info(struct hw_eq_ch *ch, u8 channels, u8 out_32bit);

/*----------------------------------------------------------------------------*/
/**@brief    设置硬件转换系数
   @param    ch:通道句柄
   @param    info:系数、增益等信息
   @return   0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int hw_eq_ch_set_coeff(struct hw_eq_ch *ch, struct eq_coeff_info *info);

/*----------------------------------------------------------------------------*/
/**@brief    启动一次转换
   @param  ch:eq句柄
   @param  input:输入数据地址
   @param  output:输出数据地址
   @param  len:输入数据长度
   @return 输出数据的长度
*/
/*----------------------------------------------------------------------------*/
int hw_eq_ch_start(struct hw_eq_ch *ch, void *input, void *output, int len);

/*----------------------------------------------------------------------------*/
/**@brief  关闭一个通道
   @param  ch:eq句柄
   @return 0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int hw_eq_ch_close(struct hw_eq_ch *ch);

/*----------------------------------------------------------------------------*/
/**@brief  挤出eq中的数据
   @param  eq:eq句柄
   @return 0:成功 -1:失败
*/
/*----------------------------------------------------------------------------*/
int hw_eq_flush_out(struct hw_eq *eq);

/*----------------------------------------------------------------------------*/
/**@brief  获取eq是否正在运行状态
   @param  eq:eq句柄
   @return true or false
*/
/*----------------------------------------------------------------------------*/
int hw_eq_is_running(struct hw_eq *eq);

void eq_irq_enable(void);

void eq_irq_disable(void);

int hw_eq_ch_set_info_new(struct hw_eq_ch *ch, u8 channels, u8 in_mode, u8 out_mode, u8 run_mode, u8 data_in_mode, u8 data_out_mode);

#endif


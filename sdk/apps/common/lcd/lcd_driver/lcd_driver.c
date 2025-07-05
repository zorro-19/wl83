#include "lcd_config.h"
#include "lcd_driver.h"
#include "asm/spi.h"
#include "asm/dpi.h"
#include "asm/dmm.h"
#include "asm/exti.h"
#include "device/gpio.h"
#include "asm/dsi_api.h"
#include "dma2d_common_api.h"
#include "asm/jldma2d.h"
#include "asm/dcache.h"


#define LOG_TAG_CONST       LCD
#define LOG_TAG             "[LCD]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#if TCFG_LCD_ENABLE

struct lcd_device_info {
    struct device device;
    struct lcd_dev_drive *lcd;       ///< 屏驱配置
    struct lcd_platform_data *pdata; ///< 板级配置
    struct lcd_board_cfg *bd_cfg;    ///< 板级配置项
    void *lcd_if_hdl;                      ///< spi/mcu屏的接口(spi/pap)句柄
    OS_SEM *lcd_wait_sem;                  ///< 指向等待init完成的信号量
    u8 *draw_buf;                          ///< spi/mcu屏图像大小端转换的存放buf
    int te_id;                             ///< TE的IO的外部中断ID
    OS_SEM te_sem;                         ///< TE信号到来的信号量
    u8 start_disp_flag : 1;                ///< 启动显示标志
    u8 lcd_open_flag   : 1;                ///< lcd驱动open标志
    u8 is_early_init   : 6;                ///< 是否已经提前初始化标志(开机时进行初始化)
};
static struct lcd_device_info lcd_dev_info_t = {0};
#define __this (&lcd_dev_info_t)


#if TCFG_LCD_TE_ENABLE
/*
 * 为解决MCU/SPI屏显示出现撕裂问题(Tearing effect)，lcd driver可配置为检测到帧TE信号后才开始推数据给屏幕，
 * 并且推屏速率需要遵循2倍关系:
 *    1.不能让读屏指针赶上写屏指针。写屏ram的数据时间(W)应该小于等于2倍MCU/SPI屏的自刷新时间(R)。
 *    2.不能让写屏指针赶上读屏指针。写屏ram的数据时间(W)应该大于MCU/SPI屏的自刷新时间(R)。
 * 即lcd_te_int_time < lcd_push_data_time <= 2 * lcd_te_int_time
 *
 * 调整推屏
 * A.可调整接口推屏速率。推屏接口的时钟频率决定了推数据速率，各个接口的时钟频率调整位置:
 *     1.SPI接口——修改波特率和LSB时钟;
 *     2.PAP接口——修改TS、TH、TW时钟以及LSB时钟;(PAP的WR速率 = LSB / (TS + TH + TW))
 *     3.DPI接口——修改.dclk_cfg的时钟源和分配值;
 * B.当然，也可以调整MCU/SPI屏刷新帧率，需要咨询屏厂怎么修改。
 */
#define LCD_TE_DEBUG_EN         0          ///< 开启TE调试。通过打印判断推屏速率是否在合适范围。
#if LCD_TE_DEBUG_EN
#include "perf_counter.h"
static volatile u32 lcd_te_int_time;       ///< TE信号中断间隔时间
static u32 lcd_push_data_time;             ///< 接口推一帧数据间隔时间
static u32 lcd_push_data_start;            ///< 开始推数时间
static u32 lcd_push_data_end;              ///< 推数结束时间
static void lcd_te_int_time_calc(void)
{
    static u32 last_time;
    u32 current_time;
    current_time = get_system_us();
    if (last_time) {
        lcd_te_int_time = current_time - last_time;
    }
    last_time = current_time;
}
static void lcd_push_data_time_calc_start(void)
{
    lcd_push_data_start = get_system_us();
}
static void lcd_push_data_time_calc_end(void)
{
    lcd_push_data_end = get_system_us();
    lcd_push_data_time = lcd_push_data_end - lcd_push_data_start;
    if (lcd_te_int_time) {
        log_info("\n~~~~~~~~~~~~~~~~~~LCD TE DEBUG~~~~~~~~~~~~~~~~~~\n");
        log_info("lcd_push_data_time = %d\n", lcd_push_data_time);
        if ((lcd_push_data_time < lcd_te_int_time) || (lcd_te_int_time * 2 < lcd_push_data_time)) {
            log_info("TE issue! Not within %d < lcd_push_data_time < %d scope\n", \
                     lcd_te_int_time, 2 * lcd_te_int_time);
        } else {
            log_info("TE normal! lcd_te_int_time = %d, 2 * lcd_te_int_time = \n", \
                     lcd_te_int_time, 2 * lcd_te_int_time);
        }

    }
}
#endif // LCD_TE_DEBUG_EN
#endif // TCFG_LCD_TE_ENABLE


extern int dma2d_init();
extern int dma2d_free();
extern void jldma2d_endian_trans(uint8_t *dest_buf, uint8_t *src_buf, uint32_t w, uint32_t h, uint32_t format);

void lcd_cs_pinstate(u8 state)
{
    if (!__this->lcd || !__this->bd_cfg) {
        log_error("lcd / board_config is NULL!");
        return;
    }

    if (__this->bd_cfg->lcd_io.lcd_cs != -1) {
        gpio_direction_output(__this->bd_cfg->lcd_io.lcd_cs, state);
    }
}

void lcd_rs_pinstate(u8 state)
{
    if (!__this->lcd || !__this->bd_cfg) {
        log_error("lcd / board_config is NULL - %d!", __LINE__);
        return;
    }

    if (__this->bd_cfg->lcd_io.lcd_rs != -1) {
        gpio_direction_output(__this->bd_cfg->lcd_io.lcd_rs, state);
    }
}

void lcd_rst_pinstate(u8 state)
{
    if (!__this->lcd || !__this->bd_cfg) {
        log_error("lcd / board_config is NULL - %d!", __LINE__);
        return;
    }

    if (__this->bd_cfg->lcd_io.lcd_reset != -1) {
        gpio_direction_output(__this->bd_cfg->lcd_io.lcd_reset, state);
    }
}

void lcd_backlight_ctrl(u8 onoff)
{
    if (!__this->lcd || !__this->bd_cfg) {
        log_error("lcd / board_config is NULL - %d!", __LINE__);
        return;
    }

    if (onoff) {
        log_info(">>>>>>lcd_backlight open");
    } else {
        log_info(">>>>>>lcd_backlight close");
    }

    if (__this->lcd && __this->lcd->bl_ctrl) {
        __this->lcd->bl_ctrl(__this->bd_cfg, onoff);
    }
}

void WriteCOM(u8 cmd)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!__this->lcd_if_hdl) {
        log_error("WriteCOM fail, open device first\n");
        return;
    }

    lcd_cs_pinstate(0);
    lcd_rs_pinstate(0);//cmd

    if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
        dev_ioctl(__this->lcd_if_hdl, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_if_hdl, &cmd, 1);
    } else if (lcd->type == LCD_SPI) {
        dev_ioctl(__this->lcd_if_hdl, IOCTL_SPI_SEND_BYTE, (u32)cmd);
    }

    lcd_cs_pinstate(1);
}

void ReadDAT(u8 cmd, u8 *buf, u8 len)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!__this->lcd_if_hdl) {
        log_error("WriteCOM fail, open device first\n");
        return;
    }

    if (lcd->type == LCD_SPI) {
        lcd_cs_pinstate(0);
        lcd_rs_pinstate(0);//cmd
        dev_ioctl(__this->lcd_if_hdl, IOCTL_SPI_SEND_BYTE, (u32)cmd);
        lcd_rs_pinstate(1);//dat
        for (u8 i = 0; i < len; i++) {
            dev_ioctl(__this->lcd_if_hdl, IOCTL_SPI_READ_BYTE, (u32)(buf + i));
        }
        lcd_cs_pinstate(1);
    } else if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
        lcd_cs_pinstate(0);
        lcd_rs_pinstate(0);//cmd
        dev_ioctl(__this->lcd_if_hdl, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_if_hdl, (void *)&cmd, 1);
        lcd_rs_pinstate(1);//dat
        dev_read(__this->lcd_if_hdl, (void *)buf, (u32)len);
        lcd_cs_pinstate(1);
    }
}

void WriteDAT_8(u8 dat)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!__this->lcd_if_hdl) {
        log_error("WriteDAT fail, open device first\n");
        return;
    }

    lcd_cs_pinstate(0);
    lcd_rs_pinstate(1);//dat

    if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
        dev_ioctl(__this->lcd_if_hdl, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_if_hdl, &dat, 1);
    } else if (lcd->type == LCD_SPI) {
        dev_ioctl(__this->lcd_if_hdl, IOCTL_SPI_SEND_BYTE, (u32)dat);
    }

    lcd_cs_pinstate(1);
}

void WriteDAT_one_page(u8 *dat, int len)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!(__this->lcd_if_hdl && __this->lcd_open_flag)) {
        log_error("WriteDAT_one_page fail, open device first\n");
        return;
    }

    lcd_cs_pinstate(0);
    lcd_rs_pinstate(1);//dat

    DcuFlushRegion((u32 *)dat, len);

    if (__this->bd_cfg->te_mode.te_mode_en) {
        os_sem_set(&__this->te_sem, 0);
        int err = os_sem_pend(&__this->te_sem, 100);
        if (err == OS_TIMEOUT) {
            log_warn("wait TE timeout!");
        }
    }

#if LCD_TE_DEBUG_EN
    lcd_push_data_time_calc_start();
#endif

    if (lcd->type == LCD_SPI) {
        dev_write(__this->lcd_if_hdl, dat, (u32)len);
    } else if (lcd->type == LCD_MCU_SINGLE_FRAME) {
        if (__this->start_disp_flag) {
            dev_ioctl(__this->lcd_if_hdl, IOCTL_PAP_DISABLE, 0);
            dpi_wait_fb_swap_finish((u32)dat); //size
        } else {
            dpi_start_display((u32)dat);
            __this->start_disp_flag = 1;
        }
    } else if (lcd->type == LCD_MCU) {
        dev_ioctl(__this->lcd_if_hdl, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_if_hdl, dat, (u32)len);
    }

#if LCD_TE_DEBUG_EN
    lcd_push_data_time_calc_end();
#endif

    lcd_cs_pinstate(1);
}

u16 lcd_get_rotate(void)
{
    if (__this->lcd) {
        return __this->lcd->dev->imd.info.rotate;
    }

    return 0;
}

int lcd_touch_width_height_rotate(u16 *w, u16 *h)
{
    u16 lcd_w;
    u16 lcd_h;
    u16 rotate;
    if (__this->lcd) {
        lcd_w = __this->lcd->dev->imd.info.target_xres;
        lcd_h = __this->lcd->dev->imd.info.target_yres;
        rotate = __this->lcd->dev->imd.info.rotate;
        if (rotate == ROTATE_90 || rotate == ROTATE_270) {
            *w = lcd_h;
            *h = lcd_w;
        } else {
            *w = lcd_w;
            *h = lcd_h;
        }
    }

    return 0;
}
int lcd_touch_xy_coord_rotate(u16 *x, u16 *y, u8 status)
{
    u16 rotate;
    u16 touch_w;
    u16 touch_h;
    u16 tmp = 0;
    if (__this->lcd) {
        touch_w = __this->lcd->dev->imd.info.target_xres;
        touch_h = __this->lcd->dev->imd.info.target_yres;
        rotate = __this->lcd->dev->imd.info.rotate;
        if (status) {
            /* log_debug("\n>>>> [%d]touch (%d,%d)\n",status,*x,*y); */
            switch (rotate) {
            case ROTATE_90:
                tmp = *y;
                *y = *x;
                *x = touch_w - tmp - 1;
                break;
            case ROTATE_270:
                tmp = *x;
                *x = *y;
                *y = touch_h - tmp - 1;
                break;
            case ROTATE_180:
                *x = touch_w - *x - 1;
                *y = touch_h - *y - 1;
                break;
            }
            /* log_debug(">>>> [%d]rotate:%d touch (%d,%d)\n",status,rotate,*x,*y); */
        }
    }

    return 0;
}

static struct lcd_board_cfg *lcd_bd_cfg_match(char *name, struct lcd_platform_data *pdata)
{
    if (pdata && pdata->cfg_num && pdata->config_ptr) {
        if (name == NULL) {
            return &pdata->config_ptr[0];
        }
        for (u8 i = 0; i < pdata->cfg_num; i++) {
            if (!strcmp(pdata->config_ptr[i].lcd_name, name)) {
                return &pdata->config_ptr[i];
            }
        }
    } else {
        log_error("board config error!");
    }
    return NULL;
}

static struct lcd_dev_drive *lcd_dev_match(char *name)
{
    struct lcd_dev_drive *p;
    list_for_each_lcd_device_drive(p) {
        if (name == NULL) {
            return p;
        }
        if (!p->logo) {
            continue;
        }
        if (!strcmp(p->logo, name)) {
            return p;
        }
    }
    return NULL;
}

static int lcd_early_init_wait_done(void)
{
    int err = 0;
    if (!__this->lcd_wait_sem) {
        log_warn("lcd_wait_sem is null\n", err);
        return err;
    }

    err = os_sem_pend(__this->lcd_wait_sem, 500);
    os_sem_del(__this->lcd_wait_sem, OS_DEL_ALWAYS);
    __this->lcd_wait_sem = NULL;
    if (err) {
        log_error("wait init err %d\n", err);
    }
    return err;
}

static int lcd_open_pap(void)
{
    __this->lcd_if_hdl = dev_open("pap", NULL);
    if (!__this->lcd_if_hdl) {
        log_error("open pap fail\n");
        log_error("\"pap\" device must be register and placed in front of \"lcd\"\n");
        return -1;
    }
    log_info("open pap ok\n");
    return 0;
}

static int lcd_open_spi(char *if_name)
{
    __this->lcd_if_hdl = dev_open(if_name, NULL);
    if (!__this->lcd_if_hdl) {
        log_error("open spi fail\n");
        log_error("\"%s\"device must be register and placed in front of \"lcd\"\n", if_name);
        return -1;
    }
    log_info("open spi ok\n");
    return 0;
}

// 打开发送init code的接口
static int lcd_open_send_code_port(struct lcd_dev_drive *lcd, struct lcd_board_cfg *bd_cfg)
{
    if (!lcd) {
        log_error("can't get lcd dev drive!!!\n");
        return -1;
    }

    switch (lcd->type) {
    case LCD_RGB:
        break;

    case LCD_MIPI:
        dsi_dev_init(&lcd->dev->mipi);
        break;

    case LCD_MCU:
    case LCD_MCU_SINGLE_FRAME:
        // MCU屏依赖于PAP接口进行初始化，需要提前打开。注.板级中PAP设备注册位置在LCD前面。
        if (lcd_open_pap() < 0) {
            return -1;
        }
        break;

    case LCD_SPI:
        // SPI屏依赖于SPI接口进行初始化，需要提前打开。注.板级中SPI设备注册位置在LCD前面。
        if (!bd_cfg) {
            log_error("open send code port fail! can't get board config parameter!!!\n");
            return -1;
        }
        if (lcd_open_spi(bd_cfg->spi_lcd_interface) < 0) {
            return -1;
        }
        break;
    }
    return 0;
}

static void lcd_te_interrupt(void *arg, u32 parm)
{
#if LCD_TE_DEBUG_EN
    lcd_te_int_time_calc();
#endif
    os_sem_post(&__this->te_sem);
    /* putchar('a'); */
}

static int lcd_send_init_code(struct lcd_dev_drive *lcd, struct lcd_board_cfg *bd_cfg)
{
    int ret;
    if (!lcd) {
        log_error("lcd is null");
        return -EFAULT;
    }

    if (lcd->type == LCD_MIPI) {
        ret = dsi_send_init_code(&lcd->dev->mipi);
        ASSERT(ret == 0, "dsi send init code fail!!!\n");
    } else {
        if (lcd->send_init_code) {
            lcd->send_init_code(bd_cfg);
        } else {
            log_warn("%s does not have the send_init_code() interface.", lcd->logo);
        }
    }
    return 0;
}

static void lcd_early_init_task(void *arg)
{
    struct lcd_dev_drive *lcd = __this->lcd;
    struct lcd_board_cfg *bd_cfg = __this->bd_cfg;
    OS_SEM _wait_sem;

    if (!lcd || !bd_cfg) {
        log_error("lcd / bd_cfg is NULL! - %d", __LINE__);
        return;
    }

    if (lcd_open_send_code_port(lcd, bd_cfg)) {
        return;
    }

    os_sem_create(&_wait_sem, 0);
    __this->lcd_wait_sem = &_wait_sem;

    if (lcd->init) {
        lcd->init(bd_cfg);
    } else {
        log_warn("%s does not have the init() interface.", lcd->logo);
    }

    lcd_send_init_code(lcd, bd_cfg);

    os_sem_post(&_wait_sem);
    log_info("lcd init done\n");
    while (__this->lcd_wait_sem != NULL) {
        log_warn("lcd early init task is waitting\n");
        os_time_dly(500);
    }
}

static int lcd_dev_init(const struct dev_node *node, void *pdata)
{
    int lcd_num = 0;
    int bd_num;
    struct lcd_dev_drive *p;
    __this->pdata = (struct lcd_platform_data *)pdata;

    list_for_each_lcd_device_drive(p) {
        lcd_num++;
    }
    bd_num = __this->pdata->cfg_num;

#if TCFG_LCD_SUPPORT_MULTI_DRIVER_EN
    // 支持多屏驱配置
    ASSERT(lcd_num > 0, "please enable at least 1 lcd, check board_xxx.h!!!\n");
    ASSERT(bd_num > 0, "you should have at least 1 lcd board config, check board_xxx.c!!!\n");
    __this->is_early_init = 0;
#else
    // 仅支持一个屏驱配置
    ASSERT(lcd_num < 2, "you have enable more than 2 lcd, check board_xxx.h!!!\n");
    ASSERT(bd_num > 0, "you should have at least 1 lcd board config, check board_xxx.c!!!\n");

    __this->lcd = lcd_dev_match((char *)NULL);
    __this->bd_cfg = lcd_bd_cfg_match((char *)NULL, __this->pdata);
    __this->is_early_init = 1;

    thread_fork("lcd_early_init_task", 30, 1024, 0, 0, lcd_early_init_task, NULL);
#endif

    return 0;
}

static int __lcd_open(struct lcd_dev_drive *lcd, struct lcd_board_cfg *bd_cfg)
{
    union lcd_dev_info *dev = lcd->dev;
    struct te_mode_ctrl *te_mode = &__this->bd_cfg->te_mode;

    if (__this->lcd_open_flag) {
        log_warn("lcd device has been open");
        return 0;
    }

    if (!(lcd && bd_cfg)) {
        log_error("lcd / bd_cfg is NULL! - %d", __LINE__);
        return -ENODEV;
    }

    if (!__this->is_early_init) {
        if (lcd_open_send_code_port(lcd, bd_cfg)) {
            return -ENODEV;
        }
        if (lcd->init) {
            lcd->init(bd_cfg);
        }
    }

    switch (lcd->type) {
    case LCD_RGB:
        dev->imd.info.drive_mode = LCD_RGB;
        if (!__this->is_early_init) {
            if (lcd->check && lcd->check(bd_cfg)) {
                return -ENODEV;
            }
            lcd_send_init_code(lcd, bd_cfg);
        }
        dpi_open(&dev->imd);
        dmm_config(&dev->imd.info);
        log_info("open lcd_rgb_imd ok");
        break;

    case LCD_MIPI:
        dev->mipi.info.drive_mode = LCD_MIPI;
        if (!__this->is_early_init) {
            if (lcd->check && lcd->check(bd_cfg)) {
                dsi_dev_deinit();
                return -ENODEV;
            }
            lcd_send_init_code(lcd, bd_cfg);
        }
        dmm_config(&dev->mipi.info);
        log_info("open lcd_mipi....");
        break;

    case LCD_MCU:
        dev->imd.info.drive_mode = LCD_MCU;
        if (!__this->is_early_init) {
            if (lcd->check && lcd->check(bd_cfg)) {
                dev_close(__this->lcd_if_hdl);
                return -ENODEV;
            }
            lcd_send_init_code(lcd, bd_cfg);
        }
        if (dev->imd.data_out_endian == MODE_BE) {
            __this->draw_buf = malloc(LCD_RGB565_DATA_SIZE);
            if (!__this->draw_buf) {
                dev_close(__this->lcd_if_hdl);
                log_error("lcd driver draw buf malloc fail!!!");
                return -ENODEV;
            }
            dma2d_init();/// 使用dma2d进行数据端序转换需要先初始化模块
        }
        if (te_mode && te_mode->te_mode_en) {
            os_sem_create(&__this->te_sem, 0);
            __this->te_id = exti_init(te_mode->gpio, te_mode->edge, lcd_te_interrupt, NULL);
            log_info("te mode en!");
        }
        log_info("open lcd_mcu ok");
        break;

    case LCD_MCU_SINGLE_FRAME:
        dev->imd.info.drive_mode = LCD_MCU_SINGLE_FRAME;
        if (!__this->is_early_init) {
            if (lcd->check && lcd->check(bd_cfg)) {
                log_error("%s check fail!!", lcd->logo);
                dev_close(__this->lcd_if_hdl);
                return -ENODEV;
            }
            lcd_send_init_code(lcd, bd_cfg);
        }
        dpi_open(&dev->imd);
        dmm_config(&dev->imd.info);
        if (te_mode && te_mode->te_mode_en) {
            os_sem_create(&__this->te_sem, 0);
            __this->te_id = exti_init(te_mode->gpio, te_mode->edge, lcd_te_interrupt, NULL);
            log_info("te mode en!");
        }
        log_info("open lcd_mcu_imd ok");
        break;

    case LCD_SPI:
        dev->spi.info.drive_mode = LCD_SPI;
        if (!__this->is_early_init) {
            if (lcd->check && lcd->check(bd_cfg)) {
                dev_close(__this->lcd_if_hdl);
                return -ENODEV;
            }
            lcd_send_init_code(lcd, bd_cfg);
        }
        if (dev->spi.data_out_endian == MODE_BE) {
            __this->draw_buf = malloc(LCD_RGB565_DATA_SIZE);
            if (!__this->draw_buf) {
                dev_close(__this->lcd_if_hdl);
                log_error("lcd driver draw buf malloc fail!!!");
                return -ENODEV;
            }
            dma2d_init();///< 使用dma2d进行数据端序转换需要先初始化模块
        }
        if (te_mode && te_mode->te_mode_en) {
            os_sem_create(&__this->te_sem, 0);
            __this->te_id = exti_init(te_mode->gpio, te_mode->edge, lcd_te_interrupt, NULL);
            log_info("te mode en!");
        }
        break;
    }
    __this->lcd_open_flag = 1;
    return 0;
}

static int lcd_dev_open(const char *name, struct device **device, void *arg)
{
    *device = &__this->device;

#if TCFG_LCD_SUPPORT_MULTI_DRIVER_EN
    struct lcd_dev_drive *lcd;
    if (arg == NULL) {
        // open时未指定屏型号，则遍历屏驱配置，check屏是否在线
        list_for_each_lcd_device_drive(lcd) {
            if (!lcd->logo) {
                log_error("lcd / board_config doesn't have a name!");
                continue;
            }
            __this->bd_cfg = lcd_bd_cfg_match((char *)lcd->logo, __this->pdata);
            if (!__this->bd_cfg) {
                continue;
            }
            __this->lcd = lcd;
            if (!__lcd_open(__this->lcd, __this->bd_cfg)) {
                log_info("find matching LCD and board config!");
                goto __find_lcd;
            }
        }
        __this->bd_cfg = NULL;
        __this->lcd = NULL;
        log_error("lcd open fail!!!");
        return -ENODEV;
    } else {
        // open时指定了屏幕型号
        __this->lcd = lcd_dev_match((char *)arg);
        __this->bd_cfg = lcd_bd_cfg_match((char *)arg, __this->pdata);
        ASSERT(__this->lcd, "can't find lcd, check board_xxx.h!!!\n");
        ASSERT(__this->bd_cfg, "can't find lcd board config, check board_xxx.c!!!\n");

        if (__lcd_open(__this->lcd, __this->bd_cfg)) {
            log_error("open %s fail!!!", (char *)arg);
            return -ENODEV;
        }
    }
__find_lcd:

#else
    if (__this->is_early_init) {
        if (lcd_early_init_wait_done()) {///< 等待dev init里创建的初始化任务完成
            return -ENODEV;
        }
    }
    if (__lcd_open(__this->lcd, __this->bd_cfg)) {
        log_error("open %s fail!!!", (char *)arg);
        return -ENODEV;
    }
#endif

    (*device)->private_data = (void *)__this->lcd;

    return 0;
}

static int lcd_dev_ioctl(struct device *device, u32 cmd, u32 arg)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)device->private_data;

    if (!__this->lcd_open_flag) {
        log_error("LCD dev not open!!!");
        return 0;
    }

    switch (cmd) {
    case IOCTL_LCD_RGB_SET_ISR_CB:
        if (lcd->type == LCD_RGB) {
            dpi_set_isr_cb(arg);
        } else if (lcd->type == LCD_MIPI) {
            mipi_set_isr_cb(arg);
        }
        break;
    case IOCTL_LCD_RGB_SET_LINE_ISR_CB:
        if (lcd->type == LCD_RGB) {
            dpi_set_line_isr_cb(arg);
        } else if (lcd->type == LCD_MIPI) {
            mipi_set_line_isr_cb(arg);
        }
        break;

    case IOCTL_LCD_RGB_WAIT_FB_SWAP_FINISH:
        if (lcd->type == LCD_MCU_SINGLE_FRAME) {
            lcd->draw((void *)arg);
        } else if (lcd->type == LCD_MCU) {
            if (__this->lcd->dev->imd.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        } else if (lcd->type == LCD_SPI) {
            if (__this->lcd->dev->spi.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        } else if (lcd->type == LCD_MIPI) {
            if (lcd->dev->mipi.info.drive_mode == LCD_MIPI) {
                mipi_wait_fb_swap_finish(0);
            }
        } else {
            if (lcd->dev->imd.info.drive_mode == LCD_RGB) {
                dpi_wait_fb_swap_finish(0);
            }
        }
        break;
    case IOCTL_LCD_RGB_WAIT_LINE_FINISH:
        if (lcd->type == LCD_MIPI) {
            if (lcd->dev->mipi.info.drive_mode == LCD_MIPI) {
                mipi_wait_line_finish(0);
            }
        } else if (lcd->type == LCD_RGB) {
            if (lcd->dev->imd.info.drive_mode == LCD_RGB) {
                dpi_wait_line_finish(0);
            }
        } else {
            log_warn("lcd type unsupport wait line :%d\n", lcd->type);
        }
        break;

    case IOCTL_LCD_RGB_START_DISPLAY:
        if (lcd->type == LCD_MCU_SINGLE_FRAME) {
            lcd->draw((void *)arg);
        } else if (lcd->type == LCD_RGB) {
            dpi_start_display(arg);
        } else if (lcd->type == LCD_MIPI) {
            mipi_start_display(arg);
        }
        __this->start_disp_flag = 1;

        if (lcd->type == LCD_MCU) {
            if (__this->lcd->dev->imd.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        }

        if (lcd->type == LCD_SPI) {
            if (__this->lcd->dev->spi.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        }

        lcd_backlight_ctrl(true);//开启背光
        break;

    case IOCTL_LCD_RGB_GET_LCD_HANDLE:
        *(struct lcd_dev_drive **)arg = lcd;
        break;
    }

    return 0;
}

static int lcd_dev_close(struct device *device)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)device->private_data;

    if (!__this->lcd_open_flag) {
        log_warn("The LCD has already been in the closed state!");
        return 0;
    }

    switch (lcd->type) {
    case LCD_RGB:
        dpi_close();
        dmm_deinit();
        __this->start_disp_flag = 0;
        break;
    case LCD_MIPI:
        dsi_dev_deinit();
        dmm_deinit();
        __this->start_disp_flag = 0;
        break;
    case LCD_MCU_SINGLE_FRAME:
        dpi_close();
        dmm_deinit();
        if (__this->lcd_if_hdl) {
            dev_close(__this->lcd_if_hdl);
            __this->lcd_if_hdl = NULL;
        }
        if (__this->bd_cfg->te_mode.te_mode_en) {
            os_sem_del(&__this->te_sem, OS_DEL_ALWAYS);
            exti_uninit(__this->te_id);
            __this->te_id = 0;
        }
        break;
    case LCD_MCU:
        if (__this->lcd_if_hdl) {
            dev_close(__this->lcd_if_hdl);
            __this->lcd_if_hdl = NULL;
        }
        if (__this->lcd->dev->imd.data_out_endian == MODE_BE) {
            free(__this->draw_buf);
            __this->draw_buf = NULL;
            dma2d_free();
        }
        if (__this->bd_cfg->te_mode.te_mode_en) {
            os_sem_del(&__this->te_sem, OS_DEL_ALWAYS);
            exti_uninit(__this->te_id);
            __this->te_id = 0;
        }
        break;
    case LCD_SPI:
        if (__this->lcd_if_hdl) {
            dev_close(__this->lcd_if_hdl);
            __this->lcd_if_hdl = NULL;
        }
        if (__this->lcd->dev->spi.data_out_endian == MODE_BE) {
            free(__this->draw_buf);
            __this->draw_buf = NULL;
            dma2d_free();
        }
        if (__this->bd_cfg->te_mode.te_mode_en) {
            os_sem_del(&__this->te_sem, OS_DEL_ALWAYS);
            exti_uninit(__this->te_id);
            __this->te_id = 0;
        }
        break;
    }
    __this->is_early_init = 0; ///< 提前初始化仅在开机时有效，该变量close后置零，以让open时能走初始化
    __this->lcd_open_flag = 0;

    return 0;
}

const struct device_operations lcd_dev_ops = {
    .init  = lcd_dev_init,
    .open  = lcd_dev_open,
    .ioctl = lcd_dev_ioctl,
    .close = lcd_dev_close,
};


#endif

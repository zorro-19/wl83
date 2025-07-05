/**
 * @file lv_port_disp.c
 *
 */
#include "lcd_config.h"

#ifdef USE_LVGL_V9_UI_DEMO

/*********************
 *      INCLUDES
 *********************/
#define BOOL_DEFINE_CONFLICT
#include "lv_port_disp.h"
#include "src/display/lv_display_private.h"
#include "src/core/lv_global.h"
#include "video/fb.h"
#include "lcd_driver.h"


/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES        LCD_W
#define MY_DISP_VER_RES        LCD_H


/**********************
 *      TYPEDEFS
 **********************/
#if LV_COLOR_DEPTH==16
#define LV_PIXEL_COLOR_T lv_color16_t
#elif LV_COLOR_DEPTH==24
#define LV_PIXEL_COLOR_T lv_color24_t
#elif LV_COLOR_DEPTH==32
#define LV_PIXEL_COLOR_T lv_color32_t
#endif
/**********************
 *  STATIC PROTOTYPES
 **********************/

static void disp_init(void);
static void *lv_lcd_frame_end_hook_func(void);
static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

/**********************
 *  STATIC VARIABLES
 **********************/

static u32 debug_draw_time_ms; //用于观察从开始渲染一帧开始到渲染完成一帧(推屏之前)需要的时间
static u64 debug_lcd_latency_us;//用于观察每帧推屏引起的延迟,如果有开TE,等TE时间也会计算进入,如果单纯评估测试DMA造成的时延,请关闭TE测试
static u32 debug_draw_max_time_ms;//用于观察记录从绘制完第一帧的第一片后开始推屏到绘制完最后一片消耗的历史最长时间
static uint8_t first_render = 1;
static uint32_t lcd_rotate_task_pid = 0;

/**********************
 *      MACROS
 **********************/
//#define THREE_FB_ACCELERATION  //利用3FB加速 ,防止LVGL渲染完要等待LCD垂直同步才能够切换BUF, 但是LVGL每部没实现3FB，因此需要这里自行切换buf_act ,实际意义不大，比2FB还要差


struct lv_fb_t {
    LV_PIXEL_COLOR_T *fb;
};
volatile static struct lv_fb_t next_disp;/* 下一帧待显示的next_fb地址 */

#ifdef THREE_FB_ACCELERATION
#include "spinlock.h"
#include "asm/dma.h"
static LV_PIXEL_COLOR_T buf_3_3[MY_DISP_HOR_RES * MY_DISP_VER_RES] __attribute__((aligned(32)));            /*3th screen sized buffer*/
static struct lv_fb_t cur_disp;/*当前LCD的显示显存 online_fb*/
static struct lv_fb_t next_offline_disp;/* 上一帧online_fb，也是下一帧offline_fb */
static spinlock_t fb_lock; //双核互斥锁
static OS_SEM dma_cpy_done_sem;
static void dma_copy_done_irq_cb(dma_execute_status_t status)
{
    os_sem_post(&dma_cpy_done_sem);
    ASSERT(status == DMA_EXEC_STATUS_COMPLETE);
}
#endif //THREE_FB_ACCELERATION

static void *lcd_dev = NULL;
static uint8_t *lcd_disp_buffer = NULL;
static uint16_t lcd_rotate;
static uint16_t lcd_format;
static volatile u8  g_dmm_line_period; //dmm读取一行所需时间
static volatile u32 g_last_vsync_trig_time;
static volatile u64 g_vsync_start_time;
static volatile u16 g_dmm_line;
static volatile u16 lcd_vert_total = 0;
static OS_SEM rotate_sem;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

#if LV_USE_PERF_MONITOR == 0 //只是为了适应LVGL_V9的benchmark帧率统计
    lv_timer_delete(disp->refr_timer);
    disp->refr_timer = NULL;
#endif

    /* Example 3
     * Two buffers screen sized buffer for double buffering.
     * Both LV_DISPLAY_RENDER_MODE_DIRECT and LV_DISPLAY_RENDER_MODE_FULL works, see their comments*/
    static LV_PIXEL_COLOR_T buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES] __attribute__((aligned(32)));            /*A screen sized buffer*/
    static LV_PIXEL_COLOR_T buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES] __attribute__((aligned(32)));            /*Another screen sized buffer*/

#ifdef THREE_FB_ACCELERATION
    //每次都重绘整个FB
    /*lv_display_set_buffers(disp, buf_3_1, buf_3_2, buf_3_3, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_FULL);*/
    //3FB 暂未很好完善脏矩形刷新机制, 因为LVGL内部不支持3FB，需要修改refr_sync_areas对3个FB同步
    lv_display_set_buffers(disp, buf_3_1, buf_3_2, buf_3_3, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_DIRECT);
#else
    //RGB/MIPI屏幕配置FB必须是屏幕大小，使得LVGL内部直接渲染到FB对应的绝对坐标 && 内部会同步双BUF脏矩阵区域
    lv_display_set_buffers(disp, buf_3_1, buf_3_2, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_DIRECT);
#endif //THREE_FB_ACCELERATION
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static u16 __lcd_abs(int x, int y)
{
    if ((x) > (y)) {
        return ((x) - (y)) ;
    }
    return ((y) - (x));
}

static void *lv_lcd_frame_end_hook_func(void)
{
    if (!next_disp.fb) {
        return NULL; //软件还未渲染完整一帧，继续显示上一帧显存
    }
#ifdef THREE_FB_ACCELERATION
    spin_lock(&fb_lock);
    /* next_offline_fb 变量保存上一帧的 online_fb 地址 */
    next_offline_disp.fb = cur_disp.fb;
    /* 把已经绘制好的next_disp fb地址设置为 online_fb 的地址 */
    cur_disp.fb = next_disp.fb;
    next_disp.fb = NULL;
    spin_unlock(&fb_lock);

    /*返回 online_fb 的地址为当前 LCD 的显示显存 */
    return ((lv_draw_buf_t *)cur_disp.fb)->data;
#else
    lv_draw_buf_t *cur_fb = next_disp.fb;
    next_disp.fb = NULL;
    return cur_fb->data;
#endif
}

void dmm_vsync_int_handler(void)
{
    struct lcd_dev_drive *lcd = NULL;
    struct imd_dev *imd;
    struct mipi_dev *mipi;
    static u32 dmm_frame_period = 16000; //先给一个最小周期的值,单位微秒
    static u8 statistics_cnt = 0;
    if (statistics_cnt < 10) {
        /* 计算dmm 读取一行最小周期 */
        ++statistics_cnt;
        dmm_frame_period = get_system_us() - g_last_vsync_trig_time;
        g_last_vsync_trig_time = get_system_us();
        if (lcd_dev && lcd_rotate) {
            dev_ioctl(lcd_dev, IOCTL_LCD_RGB_GET_LCD_HANDLE, (u32)&lcd);
            lcd_vert_total = lcd->dev->imd.info.target_xres;
            if (lcd->type == LCD_MIPI) {
                mipi = &lcd->dev->mipi;
                lcd_vert_total = mipi->video_timing.dsi_vdo_vsa_v + mipi->video_timing.dsi_vdo_vbp_v + mipi->video_timing.dsi_vdo_vact_v + mipi->video_timing.dsi_vdo_vfp_v;
            } else if (lcd->type == LCD_RGB) {
                imd = &lcd->dev->imd;
                lcd_vert_total = imd->timing.vert_total;
            }
            if (lcd_vert_total) {
                g_dmm_line_period = (dmm_frame_period + (lcd_vert_total / 2)) / lcd_vert_total;//四舍五入
            }
        }
    }
    g_vsync_start_time = get_system_us(); //记录Vsync起始时间点
}

static void lcd_rotate_task(void *p)
{
#define CALC_CNT  60
    int ret = 0;
    u32 rotate_start_time, rotate_use_time;
    int msg[3] = {0};
    uint8_t *frame_buffer = (uint8_t *)p;
    u8 statistics_cnt = CALC_CNT;
    u32 *rotate_times = NULL;
    u8 err_cnt = 0;

    u16 out_w = (lcd_rotate == ROTATE_180) ? MY_DISP_HOR_RES : MY_DISP_VER_RES;
    u16 out_h = (lcd_rotate == ROTATE_180) ? MY_DISP_VER_RES : MY_DISP_HOR_RES;

    os_sem_create(&rotate_sem, 1);
    printf("lcd_rotate_task run...\n");
    rotate_start_time = get_system_us();
    fb_frame_buf_rotate(frame_buffer, lcd_disp_buffer, MY_DISP_HOR_RES, MY_DISP_VER_RES, 0, out_w, out_h, 0, lcd_rotate, 0, 0, lcd_format, lcd_format, 0);
    rotate_use_time = get_system_us() - rotate_start_time;
    g_dmm_line = __lcd_abs(lcd_vert_total, (rotate_use_time / g_dmm_line_period));
    dmm_line_pend_init(g_dmm_line);
    while (1) {
        ret = os_taskq_pend_timeout(msg, ARRAY_SIZE(msg), 0);
        if (ret == OS_TASKQ)  {
            frame_buffer = msg[1];
            //1. wait line pend
            if (lcd_dev) {
                dev_ioctl(lcd_dev, IOCTL_LCD_RGB_WAIT_LINE_FINISH, (u32)0);
            }
            //2. rotate to lcd buffer
            rotate_start_time = get_system_us();
            fb_frame_buf_rotate(frame_buffer, lcd_disp_buffer, MY_DISP_HOR_RES, MY_DISP_VER_RES, 0, out_w, out_h, 0, lcd_rotate, 0, 0, lcd_format, lcd_format, 0);
            rotate_use_time = get_system_us() - rotate_start_time;
            //下面是旋转时间统计
            if (statistics_cnt > 0) {
                if (rotate_times == NULL) {
                    rotate_times = (u32 *)malloc(CALC_CNT * sizeof(u32));
                }
                if (g_dmm_line_period) {
                    rotate_times[statistics_cnt - 1]  = rotate_use_time;
                    g_dmm_line = __lcd_abs(lcd_vert_total, (rotate_use_time / g_dmm_line_period));
                    dmm_line_pend_init(g_dmm_line);
                    statistics_cnt--;
                    if (statistics_cnt == 0) {
                        //去掉最大最小值并求平均
                        int rotate_time_sum = 0;
                        u32 max_rotate_time = 0;
                        u32 min_rotate_time = 0xffffffff;
                        for (int i = 0; i < CALC_CNT; i++) {
                            if (min_rotate_time > rotate_times[i]) {
                                min_rotate_time = rotate_times[i];
                            } else if (max_rotate_time < rotate_times[i]) {
                                max_rotate_time = rotate_times[i];
                            }
                            rotate_time_sum += rotate_times[i];
                        }
                        rotate_time_sum -= (min_rotate_time + max_rotate_time);
                        g_dmm_line = __lcd_abs(lcd_vert_total, (rotate_time_sum / (CALC_CNT - 2) / g_dmm_line_period));
                        printf("rotate_ava_use_time==%dus g_dmm_line_period=%d,g_dmm_line=%d\n", rotate_time_sum / (CALC_CNT - 2), g_dmm_line_period, g_dmm_line);
                        dmm_line_pend_init(g_dmm_line);
                        if (rotate_times) {
                            free(rotate_times);
                            rotate_times = NULL;
                        }
                    }
                }
            } else {
                if (g_dmm_line_period) {
                    u32 rotate_line = __lcd_abs(lcd_vert_total, (rotate_use_time / g_dmm_line_period));
                    if (rotate_line > g_dmm_line + 3) {
                        if (++err_cnt > 2) {
                            g_dmm_line = rotate_line;
                            dmm_line_pend_init(g_dmm_line);
                        }
                    } else {
                        err_cnt = 0;
                    }
                }
            }

            os_sem_post(&rotate_sem);
        }
    }
}
static void lv_lcd_swap_fb(lv_display_t *disp_drv, const lv_area_t *area, LV_PIXEL_COLOR_T *px_map)
{
#ifdef THREE_FB_ACCELERATION

    if (lcd_dev == NULL) { //LVGL首次启动渲染
        lcd_dev = dev_open("lcd", NULL);
        dev_ioctl(lcd_dev, IOCTL_LCD_RGB_SET_ISR_CB, (u32)lv_lcd_frame_end_hook_func);

        cur_disp.fb = LV_GLOBAL_DEFAULT()->disp_refresh->buf_1;//LVGL第一轮渲染在BUF1，因此设置为第一个推屏显存
        LV_GLOBAL_DEFAULT()->disp_refresh->buf_act = LV_GLOBAL_DEFAULT()->disp_refresh->buf_2; //切换LVGL第二轮渲染在BUF2

        dev_ioctl(lcd_dev, IOCTL_LCD_RGB_START_DISPLAY, (u32)(((lv_draw_buf_t *)cur_disp.fb)->data)); //启动推屏显示

        if (LV_GLOBAL_DEFAULT()->disp_refresh->render_mode != LV_DISPLAY_RENDER_MODE_FULL) {
            os_sem_create(&dma_cpy_done_sem, 0);
        }
        return;
    }

    if (next_offline_disp.fb == NULL) {
        //这个时刻是LVGL第二轮渲染，由于有3FB，因此不需要等待LCD Vsync SWAP完成就可以渲染下一个FB
        next_offline_disp.fb = LV_GLOBAL_DEFAULT()->disp_refresh->buf_3;//准备LVGL第三轮渲染在BUF3
    } else {
        //第三轮渲染以后都要等待LCD Vsync SWAP FB完成
        /*while (next_disp.fb != NULL) {};*/
        dev_ioctl(lcd_dev, IOCTL_LCD_RGB_WAIT_FB_SWAP_FINISH, 0);
        /* 等到s_next_fb空闲同步已完成 */
        ASSERT(next_disp.fb == NULL);
    }

    if (LV_GLOBAL_DEFAULT()->disp_refresh->render_mode != LV_DISPLAY_RENDER_MODE_FULL) {
        //FIXME,由于LVGL没实现3FB，因此需要修改refr_sync_area对online_fb的脏矩阵也要同步到buf_act
        dma_copy_async_with_execute_status(((lv_draw_buf_t *)next_offline_disp.fb)->data, NO_CACHE_ADDR(LV_GLOBAL_DEFAULT()->disp_refresh->buf_act->data), MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(LV_PIXEL_COLOR_T), dma_copy_done_irq_cb);
    }

    spin_lock(&fb_lock);
    /* 将绘制好的 offline_fb 设置为 next_fb */
    next_disp.fb = LV_GLOBAL_DEFAULT()->disp_refresh->buf_act;
    /* 把上一帧的 online_fb 作为下一帧的 offline_fb */
    LV_GLOBAL_DEFAULT()->disp_refresh->buf_act = next_offline_disp.fb;

    if (LV_GLOBAL_DEFAULT()->disp_refresh->render_mode != LV_DISPLAY_RENDER_MODE_FULL) {
        //FIXME:这两步是为了弥补3FB情况下让LVGL内部可以从屏上显存复制脏矩阵到正在渲染的显存
        LV_GLOBAL_DEFAULT()->disp_refresh->buf_1 = LV_GLOBAL_DEFAULT()->disp_refresh->buf_act;
        LV_GLOBAL_DEFAULT()->disp_refresh->buf_2 = next_disp.fb;
    }
    spin_unlock(&fb_lock);
    if (LV_GLOBAL_DEFAULT()->disp_refresh->render_mode != LV_DISPLAY_RENDER_MODE_FULL) {
        os_sem_pend(&dma_cpy_done_sem, 0);
    }
#else

    if (first_render == 1) { //LVGL首次启动渲染
        first_render = 0;
        if (lcd_rotate != 0) {
            thread_fork("lcd_rotate_task", 20, 1024, 256, &lcd_rotate_task_pid, lcd_rotate_task, px_map);
        } else {
            dev_ioctl(lcd_dev, IOCTL_LCD_RGB_SET_ISR_CB, (u32)lv_lcd_frame_end_hook_func);
            dev_ioctl(lcd_dev, IOCTL_LCD_RGB_START_DISPLAY, (u32)LV_GLOBAL_DEFAULT()->disp_refresh->buf_act->data);
        }
        return;
    }
    if (lcd_rotate) {
        int msg[1];
        msg[0] = (int)px_map;
        os_sem_pend(&rotate_sem, 0);
        os_taskq_post_type("lcd_rotate_task", Q_USER, ARRAY_SIZE(msg), msg);
        return;
    }
    next_disp.fb = LV_GLOBAL_DEFAULT()->disp_refresh->buf_act;
    dev_ioctl(lcd_dev, IOCTL_LCD_RGB_WAIT_FB_SWAP_FINISH, 0);
#endif
}
/*Initialize your display and the required peripherals.*/
void disp_init(void)
{
    struct lcd_dev_drive *lcd = NULL;
    //yuv422,rgb565,rgb888,argb888
    const u8 lcd_in_format[] = {
        FB_COLOR_FORMAT_YUV422,
        FB_COLOR_FORMAT_RGB565,
        FB_COLOR_FORMAT_RGB888,
        FB_COLOR_FORMAT_ARGB8888
    };
    if (lcd_dev == NULL) {
        lcd_dev = dev_open("lcd", NULL);
        dev_ioctl(lcd_dev, IOCTL_LCD_RGB_GET_LCD_HANDLE, (u32)&lcd);
        lcd_rotate = lcd->dev->imd.info.rotate;
        lcd_format = lcd_in_format[lcd->dev->imd.info.in_fmt];
        if (lcd_rotate != 0) {
            if (lcd_disp_buffer == NULL) {
                lcd_disp_buffer = zalloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(LV_PIXEL_COLOR_T));
                DcuFlushRegion((void *)lcd_disp_buffer, MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(LV_PIXEL_COLOR_T));
                dev_ioctl(lcd_dev, IOCTL_LCD_RGB_SET_ISR_CB, (u32)lv_lcd_frame_end_hook_func);
                dev_ioctl(lcd_dev, IOCTL_LCD_RGB_START_DISPLAY, (u32)lcd_disp_buffer);
                os_time_dly(50); //为了稳定计算dmm读取一行所需时间
            }
        }
    }
}
void disp_uninit(void)
{
    if (lcd_dev) {
        dev_close(lcd_dev);
        lcd_dev = NULL;
    }
    if (lcd_disp_buffer) {
        free(lcd_disp_buffer);
        lcd_disp_buffer = NULL;
    }
    if (lcd_rotate_task_pid) {
        thread_kill(&lcd_rotate_task_pid, KILL_WAIT);
        lcd_rotate_task_pid = 0;
    }
    first_render = 1;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/

static void disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map)
{
    u64 temp_system_us;
    /*printf("disp_flush->0x%x,%d,%d,%d,%d",px_map,area->x1, area->x2, area->y1, area->y2);*/
    if (LV_GLOBAL_DEFAULT()->disp_refresh->render_mode != LV_DISPLAY_RENDER_MODE_FULL) {

        if (LV_GLOBAL_DEFAULT()->disp_refresh->flushing_last) {

            u32 tmp_draw_time_ms = timer_get_ms() - lv_get_timer_handler_start_time_ms();
            debug_draw_time_ms += tmp_draw_time_ms;
            if (tmp_draw_time_ms > debug_draw_max_time_ms) {
                debug_draw_max_time_ms = tmp_draw_time_ms;
                printf("debug_draw_max_time_ms=%dms", debug_draw_max_time_ms);//注意由于中途打印,或者被其他高优先级任务抢占导致的统计不准
            }

            temp_system_us = get_system_us();
            DcuFlushRegion(px_map, MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(LV_PIXEL_COLOR_T));//这个地方可以优化，仅flush脏矩形部分的区域即可(需要从LVGL内部获取得到), 但是二维的，因此最好cache那边封装一个接口出来用
            //局部脏矩形刷新策略下，当一帧里面最后一个脏矩形被渲染完毕才切换帧BUF
            lv_lcd_swap_fb(disp_drv, area, px_map);
            debug_lcd_latency_us += (get_system_us() - temp_system_us);
        }
    } else {
        if (lv_get_timer_handler_start_time_ms()) { //过滤第一帧引入初始化屏等东西导致的延时不准
            u32 tmp_draw_time_ms = timer_get_ms() - lv_get_timer_handler_start_time_ms();
            debug_draw_time_ms += tmp_draw_time_ms;
            if (tmp_draw_time_ms > debug_draw_max_time_ms) {
                debug_draw_max_time_ms = tmp_draw_time_ms;
                printf("debug_draw_max_time_ms=%dms", debug_draw_max_time_ms);//注意由于中途打印,或者被其他高优先级任务抢占导致的统计不准
            }
        }
        temp_system_us = get_system_us();
        DcuFlushRegion(px_map, MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(LV_PIXEL_COLOR_T));
        lv_lcd_swap_fb(disp_drv, area, px_map);
        debug_lcd_latency_us += (get_system_us() - temp_system_us);
    }

    if (LV_GLOBAL_DEFAULT()->disp_refresh->flushing_last) {
#if 1
        static u32 time_lapse_hdl;
        static u8 fps_cnt;
        ++fps_cnt;
        u32 tdiff = time_lapse(&time_lapse_hdl, 1000);
        if (tdiff) {//注意由于中途打印,或者被其他高优先级任务抢占导致的统计不准
            printf("lv9 render %u mspf, lcd_latency %u mspf, render+flush %d fps\n", debug_draw_time_ms / fps_cnt, (u32)((debug_lcd_latency_us) / 1000 / fps_cnt), fps_cnt *  1000 / tdiff);
            debug_lcd_latency_us = 0;
            fps_cnt = 0;
            debug_draw_time_ms = 0;
        }
#endif
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

#endif

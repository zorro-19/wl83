/**
 * @file lv_port_disp.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "asm/dcache.h"
#include "lcd_driver.h"
#include "video/fb.h"
#include "lcd_config.h"

#ifdef USE_LVGL_V8_UI_DEMO

/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES        LCD_W
#define MY_DISP_VER_RES        LCD_H

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void disp_init(void);
static void *lv_lcd_frame_end_hook_func(void);
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
void disp_clear(struct _lv_disp_drv_t *disp_drv, uint8_t *buf, uint32_t size);
void ui_render_begin_cb(struct _lv_disp_drv_t *disp_drv);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_disp_drv_t s_disp_drv;                         /*Descriptor of a display driver*/
static void *fb = NULL;
static struct fb_map_user map0 = {0};
static struct fb_map_user map1 = {0};
static lv_disp_draw_buf_t draw_buf_dsc_2;

static u32 debug_draw_time_ms; //用于观察从开始渲染一帧开始到渲染完成一帧(推屏之前)需要的时间
static u32 debug_draw_max_time_ms;//用于观察记录从绘制完第一帧的第一片后开始推屏到绘制完最后一片消耗的历史最长时间
/**********************
 *      MACROS
 **********************/

struct lv_fb_t {
    lv_color_t *fb;
};
volatile static struct lv_fb_t next_disp;/* 下一帧待显示的next_fb地址 */

static void *lcd_dev;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static volatile u8 g_ui_flush_mode = LV_DISP_UI_FB_NUM; //非0:自刷模式 0:外部驱动刷新模式
u8 lvgl_get_fb_num(void)
{
    return LV_DISP_UI_FB_NUM;
}
u8 lvgl_get_flush_mode(void)
{
    return g_ui_flush_mode;
}
void lvgl_set_flush_mode(u8 mode)
{
    g_ui_flush_mode = mode;
}
void lv_disp_draw_buf_user_config(void *buf1, void *buf2)
{
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf1, buf2, MY_DISP_VER_RES * MY_DISP_HOR_RES);
}
#if (LV_DISP_UI_FB_NUM <= 1)
extern int fb_combine_task(void *priv);
static char lvgl_send_fb_combine_event_remain_cnt = 0;
static void _fb_combine_task(void *priv)
{
    lvgl_set_ui_flush_mode(0, NULL, NULL);
    fb_combine_task(NULL);

    lvgl_send_fb_combine_event_remain_cnt = 0;

}
int lvgl_send_fb_combine_event(void)
{
    char *task_name;
    if (lvgl_send_fb_combine_event_remain_cnt) { //LVGL 线程忙着，丢弃合成一帧
        return -1;
    }

    lvgl_send_fb_combine_event_remain_cnt = 1;

    if (os_task_get_handle(LVGL_TASK_NAME) == NULL) {
        //如果lvgl线程不存在,默认交给app_core来处理
        task_name = "app_core";
    } else {
        task_name = LVGL_TASK_NAME;
    }

    int err;
    int msg[2];
    msg[0] = (int)_fb_combine_task;
    msg[1] = NULL;
    err =  os_taskq_post_type(task_name, Q_CALLBACK, ARRAY_SIZE(msg), msg);
    if (err) {
        lvgl_send_fb_combine_event_remain_cnt = 0;
        printf("lvgl_send_fb_combine_event err=%d\n", err);
    }
}
#endif

/* set invalid area in full refresh mode, redraw the whole screen */
static void lvgl_redraw_all_now()
{
    int err;
    int msg[2];
    lv_disp_t *disp = lv_disp_get_default();
    lv_area_t a;
    lv_area_set(&a, 0, 0, lv_disp_get_hor_res(disp) - 1, lv_disp_get_ver_res(disp) - 1);
    _lv_inv_area(disp, &a);
}

void lvgl_set_ui_flush_mode(u8 mode, void *buf1, void *buf2)
{
#if (LV_DISP_UI_FB_NUM == 0)
    static uint8_t *_ui_draw_buf;
    void *p1 = NULL;
    void *p2 = NULL;
    lvgl_set_flush_mode(mode);
    if (mode) {
        if (buf1) {
            p1 = buf1;
            p2 = buf2;
        } else if (buf2) {
            p1 = buf2;
        }
        //进入自刷模式
        if (mode == 2) {
            _ui_draw_buf = zalloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * LV_COLOR_DEPTH  / 8);
            printf("malloc ui draw buf %x\n", _ui_draw_buf);
            ASSERT(_ui_draw_buf, "ui self flush mode buffer malloc err!");
            lv_disp_draw_buf_user_config(_ui_draw_buf, NULL);
        } else {
            lv_disp_draw_buf_user_config(p1, p2);
        }
        if (fb) {
            lvgl_ui_resume();
        }
    } else {
        if (_ui_draw_buf) {
            printf("free ui draw buf %x\n", _ui_draw_buf);
            free(_ui_draw_buf);
            _ui_draw_buf = NULL;
        }
        lv_disp_draw_buf_user_config(NULL, NULL);
    }
#endif
}

int fb_combine_output_handler(void *out, u32 in0_addr, u32 in1_addr)
{
#if (LV_DISP_UI_FB_NUM <= 1)
    struct fb_map_user *omap = (struct fb_map_user *)out;
    uint16_t _bpp = dma2d_get_format_bpp(omap->format) >> 3;

    if (lvgl_get_flush_mode()) {
        DcuInvalidRegion(omap->baddr, omap->width * omap->height * _bpp);
        return 1;
    }

    //在合成输出buffer上直接进行LVGL渲染
    DcuInvalidRegion(omap->baddr, omap->width * omap->height * _bpp);
    lv_disp_draw_buf_user_config((void *)omap->baddr, NULL);

    //整屏重绘
    lvgl_redraw_all_now();
    lv_timer_handler();
    /* 在 flush_cb 已有刷cache操作,这里不用重复刷了*/
    /* DcuFlushRegion(omap->baddr,omap->width * omap->height * _bpp); */
#endif
    return 0;
}
void lv_fb_combine_task_handler(void)
{
    lv_disp_draw_buf_t *draw_buf = lv_disp_get_draw_buf(_lv_refr_get_disp_refreshing());
    if (fb_combine_task(draw_buf->buf_act) == 0) {
        /* memset(draw_buf->buf_act, 0x00, draw_buf->size * sizeof(lv_color_t)); */
        dma_memset_sync(NO_CACHE_ADDR(draw_buf->buf_act), 0x00, draw_buf->size * sizeof(lv_color_t));
#if LV_COLOR_DEPTH_EXTEN == 24
        DcuInvalidRegion(draw_buf->buf_act, draw_buf->size * 3);
#else
        DcuInvalidRegion(draw_buf->buf_act, draw_buf->size * (sizeof(lv_color_t)));
#endif
    }
}
static void _lv_ui_suspend_resume_cb(uint8_t state)
{
    struct fb_draw_info info = {0};
    if (state == 0) {
        printf("lvgl ui pause!\n");
        if (fb) {
            fb_draw_close(fb);
            fb = NULL;
        }
    } else {
        printf("lvgl ui resume!\n");
        info.name = "fb0";
        info.fb_num = LV_DISP_UI_FB_NUM; //ui渲染buffer个数
        info.width = MY_DISP_HOR_RES;
        info.height = MY_DISP_VER_RES;
        info.real_width = info.width;
        info.real_height = info.height;
        info.x = 0;
        info.y = 0;
#if LV_COLOR_DEPTH == 32
        info.format = FB_COLOR_FORMAT_ARGB8888;
#elif LV_COLOR_DEPTH == 16
#if LV_COLOR_DEPTH_EXTEN == 24
        info.format = FB_COLOR_FORMAT_ARGB8565;
#else
        info.format = FB_COLOR_FORMAT_RGB565;
#endif
#else
#error "FB NOT SUPPORT INFO_FORMAT"
#endif
        info.combine = 1;
        info.z_order = 255; //最顶层
        if (fb == NULL) {
            fb = fb_draw_open(&info);
#if (LV_DISP_UI_FB_NUM != 0)
            if (fb) {
                lv_color_t *buf_2_1 = NULL;
                lv_color_t *buf_2_2 = NULL;
                fb_draw_getmap(fb, &map1);
                buf_2_2 = (lv_color_t *)map1.baddr;
                fb_draw_putmap(fb, &map1);
                fb_draw_getmap(fb, &map0);
                buf_2_1 = (lv_color_t *)map0.baddr;
                if (buf_2_1 == NULL) {
                    //单buffer
                    buf_2_1 = buf_2_2;
                    buf_2_2 = NULL;
                    memcpy(&map0, &map1, sizeof(struct fb_map_user));
                }
                lv_disp_draw_buf_user_config(buf_2_1, buf_2_2);
            }
#endif
        }
        lvgl_redraw_all_now(); //设置全屏脏矩形
    }
}
void lvgl_ui_suspend(void)
{
    _lvgl_ui_task_suspend_resume(0, _lv_ui_suspend_resume_cb);
}
void lvgl_ui_resume(void)
{
    _lvgl_ui_task_suspend_resume(1, _lv_ui_suspend_resume_cb);
}

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /**
     * LVGL requires a buffer where it internally draws the widgets.
     * Later this buffer will passed to your display driver's `flush_cb` to copy its content to your display.
     * The buffer has to be greater than 1 display row
     *
     * There are 3 buffering configurations:
     * 1. Create ONE buffer:
     *      LVGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer:
     *      LVGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LVGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Double buffering
     *      Set 2 screens sized buffers and set disp_drv.full_refresh = 1.
     *      This way LVGL will always provide the whole rendered screen in `flush_cb`
     *      and you only need to change the frame buffer's address.
     */

    /* static lv_color_t buf_2_1[MY_DISP_HOR_RES * MY_DISP_VER_RES] __attribute__((aligned(32)));            [>A screen sized buffer<] */
    /* static lv_color_t buf_2_2[MY_DISP_HOR_RES * MY_DISP_VER_RES] __attribute__((aligned(32)));            [>Another screen sized buffer<] */
    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
    static lv_color_t *buf_2_1 = NULL;
    static lv_color_t *buf_2_2 = NULL;
#if (LV_DISP_UI_FB_NUM != 0)
    if (fb) {
        fb_draw_getmap(fb, &map1);
        buf_2_2 = (lv_color_t *)map1.baddr;
        fb_draw_putmap(fb, &map1);

        fb_draw_getmap(fb, &map0);
        buf_2_1 = (lv_color_t *)map0.baddr;
        if (buf_2_1 == NULL) {
            //单buffer
            buf_2_1 = buf_2_2;
            buf_2_2 = NULL;
            memcpy(&map0, &map1, sizeof(struct fb_map_user));
        }
    }
#endif

#if (LV_DISP_UI_FB_NUM != 0)
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_VER_RES * MY_DISP_HOR_RES);   /*Initialize the display buffer*/
#endif
    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    lv_disp_drv_init(&s_disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    s_disp_drv.hor_res = MY_DISP_HOR_RES;
    s_disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    s_disp_drv.flush_cb = disp_flush;
    /* s_disp_drv.clear_cb = disp_clear; */

    /*called when start rendering*/
    s_disp_drv.render_start_cb = ui_render_begin_cb;

    /*Set a display buffer*/
    s_disp_drv.draw_buf = &draw_buf_dsc_2;

    /*Required for Example 3)*/
    s_disp_drv.full_refresh = 0;//仅重绘脏矩阵区域，LVGL内部双BUF会同步
    s_disp_drv.direct_mode = 1; //RGB/MIPI屏幕配置FB必须是屏幕大小，使得LVGL内部直接渲染到FB对应的绝对坐标 && 内部会同步双BUF脏矩阵区域
#if (LV_DISP_UI_FB_NUM == 0)
    s_disp_drv.full_refresh = 1;//UI不单独申请显存的情况下,直接在推屏显存上绘制完再推屏,必须用full refresh模式全屏刷新
    s_disp_drv.direct_mode = 0;
#endif

#if LV_COLOR_DEPTH == 32
    /* s_disp_drv.screen_transp = LV_COLOR_SCREEN_TRANSP;   //如果需要显示器的背景颜色或图像将可见,创建例如 OSD 菜单，视频在下层播放，菜单覆盖在上层 */
#endif

    /*Finally register the driver*/
    lv_disp_t *disp = lv_disp_drv_register(&s_disp_drv);
    lv_timer_del(disp->refr_timer);
    disp->refr_timer = NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void *lv_lcd_frame_end_hook_func(void)
{
    if (!next_disp.fb) {
        return NULL; //软件还未渲染完整一帧，继续显示上一帧显存
    }
    void *cur_fb = next_disp.fb;
    next_disp.fb = NULL;
    return cur_fb;
}

static void lv_lcd_swap_fb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    lv_disp_draw_buf_t *draw_buf = lv_disp_get_draw_buf(_lv_refr_get_disp_refreshing());

    struct fb_map_user map = {0};
#if (LV_DISP_UI_FB_NUM != 0)
    if (map0.baddr == (unsigned char *)draw_buf->buf_act) {
        fb_draw_putmap(fb, &map0);
    } else {
        fb_draw_putmap(fb, &map1);
    }
    fb_draw_getmap(fb, &map);
#else
    if (lvgl_get_flush_mode()) {
        map.baddr = draw_buf->buf_act;
        map.transp = 1;
        fb_draw_putmap(fb, &map);
    }
#endif /*LV_DISP_UI_FB_NUM*/
}
/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    struct fb_draw_info info = {0};
    info.name = "fb0";
    info.fb_num = LV_DISP_UI_FB_NUM; //ui渲染buffer个数
    info.width = MY_DISP_HOR_RES;
    info.height = MY_DISP_VER_RES;
    info.real_width = info.width;
    info.real_height = info.height;
    info.x = 0;
    info.y = 0;
#if LV_COLOR_DEPTH == 32
    info.format = FB_COLOR_FORMAT_ARGB8888;
#elif LV_COLOR_DEPTH == 16
#if LV_COLOR_DEPTH_EXTEN == 24
    info.format = FB_COLOR_FORMAT_ARGB8565;
#else
    info.format = FB_COLOR_FORMAT_RGB565;
#endif
#else
#error "FB NOT SUPPORT INFO_FORMAT"
#endif
    info.combine = 1;
    info.z_order = 255; //最顶层
    if (fb == NULL) {
        fb = fb_draw_open(&info);
    }
}

static void ui_render_begin_cb(struct _lv_disp_drv_t *disp_drv)
{
    if (lvgl_get_flush_mode()) {
        if (lvgl_get_fb_num() == 0) {
            //渲染前启动合成
            lv_fb_combine_task_handler();
        }
    }

}
static void disp_clear(struct _lv_disp_drv_t *disp_drv, uint8_t *buf, uint32_t size)
{
}
/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    /*printf("disp_flush->0x%x,%d,%d,%d,%d",color_p,area->x1, area->x2, area->y1, area->y2);*/

    if (disp_drv->full_refresh == 0) {
        if (lv_disp_get_draw_buf(_lv_refr_get_disp_refreshing())->flushing_last) {

            u32 tmp_draw_time_ms = timer_get_ms() - lv_get_timer_handler_start_time_ms();
            debug_draw_time_ms += tmp_draw_time_ms;
            if (tmp_draw_time_ms > debug_draw_max_time_ms) {
                debug_draw_max_time_ms = tmp_draw_time_ms;
                printf("lv max_render_time=%dms", debug_draw_max_time_ms);//注意由于中途打印,或者被其他高优先级任务抢占导致的统计不准
            }

#if LV_COLOR_DEPTH_EXTEN == 24
            DcuFlushRegion((u32 *)color_p, MY_DISP_HOR_RES * MY_DISP_VER_RES * 3);
#else
            DcuFlushRegion((u32 *)color_p, MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t)); //这个地方可以优化，仅flush脏矩形部分的区域即可(需要从LVGL内部获取得到), 但是二维的，因此最好cache那边封装一个接口出来用
#endif
            //局部脏矩形刷新策略下，当一帧里面最后一个脏矩形被渲染完毕才切换帧BUF
            lv_lcd_swap_fb(disp_drv, area, color_p);
        }
    } else {

        if (lv_get_timer_handler_start_time_ms()) { //过滤第一帧引入初始化屏等东西导致的延时不准
            u32 tmp_draw_time_ms = timer_get_ms() - lv_get_timer_handler_start_time_ms();
            debug_draw_time_ms += tmp_draw_time_ms;
            if (tmp_draw_time_ms > debug_draw_max_time_ms) {
                debug_draw_max_time_ms = tmp_draw_time_ms;
                printf("lv max_render_time=%dms", debug_draw_max_time_ms);//注意由于中途打印,或者被其他高优先级任务抢占导致的统计不准
            }
        }

        DcuFlushRegion(color_p, MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
        lv_lcd_swap_fb(disp_drv, area, color_p);
    }

    if (lv_disp_get_draw_buf(_lv_refr_get_disp_refreshing())->flushing_last) {

#if 1
        static u32 time_lapse_hdl;
        static u8 fps_cnt;
        ++fps_cnt;
        u32 tdiff = time_lapse(&time_lapse_hdl, 1000);
        if (tdiff) {//注意由于中途打印,或者被其他高优先级任务抢占导致的统计不准
            /* printf("lv render %u mspf, render+flush %d fps\n", debug_draw_time_ms / fps_cnt, fps_cnt *  1000 / tdiff); */
            printf("lv render %ums pf\n", debug_draw_time_ms / fps_cnt);
            fps_cnt = 0;
            debug_draw_time_ms = 0;
        }
#endif
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif /* USE_LVGL_V8_UI_DEMO */


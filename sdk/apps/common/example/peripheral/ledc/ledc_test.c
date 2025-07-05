#include "app_config.h"
#include "device/device.h"
#include "system/includes.h"
#include "generic/includes.h"
#include "gpio.h"
#include "asm/ledc.h"

#ifdef USE_LEDC_TEST_DEMO

#define LED_NUM             6
#define LED_DIV_SEC         3

#define LED_MODE_TIME       4   ///< 一个模式运行时间，单位：s
#define LED_FREQ            10  ///< 时基：1ms

void *ledc_hdl = NULL;

static u8 led_rgb_val_buf[24 * LED_NUM * LED_DIV_SEC] __attribute__((aligned(4)));

/***********************************************************************************************
                 ********            **
r:              *        *          *
               *          *        *
        *******            ********
        **           ********
g:        *         *        *
           *       *          *
            *******            ********
        ******           ********
b:            *         *        *
               *       *          *
                *******            ****
 * 流水灯控制驱动原理：
 *1. 每个模式都会一个周期                                                                      ***********
 *2. 以一个灯为例，一个模式周期内，又分三个颜色，即每个颜色各有各的周期。                     *           *
 *3. 最核心的思维是：一个灯的三个颜色的地位是相等的，灯与灯之间，每个灯的地位是相等。        *             *
 *4. 每个颜色在一个周期里分为几个阶段：最暗到最亮，最亮维持，最亮到最暗，最暗维持    ********               *******
 *5. 颜色之间可以存在相位差，
 *6. 灯与灯之间的计数值可以存在相位差
***********************************************************************************************/

struct led_rgb_t {
    u8 mode_idx;                 //灯亮的模式号
    u8 div_sec_num;              //一条灯带分几段
    u8 sec_led_num;              //每段灯带几个灯
    u8 cnt_freq;                 //CNT多久加一次，单位10ms，这个值越大，灯变化越慢
    u8 rgb_val_max[3];           //可配置某颜色值的最大值，一般是255
    u8 rgb_val_min[3];           //可配置某颜色值的最大值，一般是0
    int cnt[3];                  //单个灯，颜色的变化计数值，cnt的初值，就是三个颜色的相位差。
    int next_cnt_dir[3];         //同个颜色灯与灯之间的传递方向和传递间隔, 下一个灯的cnt是上一个灯的cnt+next_cnt_dir
    int next_sec_cnt_phase[3];   //同个颜色段与段之间的相位差,即下一段灯带的颜色cnt初始值是上一段灯带的cnt+next_sec_cnt_phase
    int cnt_unit[3];             //CNT加一次加多少，这个值越大，灯变化越快，CNT加到最大周期值后，又从0开始加
    int cnt_max_prd[3];          //一个颜色的整个模式的周期, 不管CNT怎么加，都映射在这个周期里，即cnt %= cnt_max_prd
    int pu_cnt_start[3];         //一个周期内，颜色值上升开始的时间，即这个颜色开始亮了
    int pu_cnt_end[3];           //一个周期内，颜色值上升结束的时间，即颜色值达到最大值
    int keep_cnt_start[3];       //一个周期内，颜色值维持最大的开始时间，一般为颜色值上升结束的时间
    int keep_cnt_end[3];         //一个周期内，颜色值维持最大的结束时间
    int pd_cnt_start[3];         //一个周期内，颜色值下降开始的时间，一般为颜色值维持最大的结束时间
    int pd_cnt_end[3];           //一个周期内，颜色值下降结束的时间，即颜色值没有为0了
};

static struct led_rgb_t mode0_led_rgb = {
    .mode_idx           = 0,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 0,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = -10,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 90,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 30,
    .keep_cnt_start[0]  = 30,       .keep_cnt_end[  0]  = 30,
    .pd_cnt_start[  0]  = 30,       .pd_cnt_end[    0]  = 60,
//g:
    .rgb_val_max[   1]  = 255,      .rgb_val_min[   1]  = 0,
    .cnt[           1]  = 30,       .next_cnt_dir[  1]  = -10,
    .cnt_unit[      1]  = 1,        .cnt_max_prd[   1]  = 90,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 30,
    .keep_cnt_start[1]  = 30,       .keep_cnt_end[  1]  = 30,
    .pd_cnt_start[  1]  = 30,       .pd_cnt_end[    1]  = 60,
//b:
    .rgb_val_max[   2]  = 255,      .rgb_val_min[   2]  = 0,
    .cnt[           2]  = 60,       .next_cnt_dir[  2]  = -10,
    .cnt_unit[      2]  = 1,        .cnt_max_prd[   2]  = 90,
    .pu_cnt_start[  2]  = 0,        .pu_cnt_end[    2]  = 30,
    .keep_cnt_start[2]  = 30,       .keep_cnt_end[  2]  = 30,
    .pd_cnt_start[  2]  = 30,       .pd_cnt_end[    2]  = 60,
};
static struct led_rgb_t mode1_led_rgb = {
    .mode_idx           = 1,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 0,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = 6,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 108,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 0,
    .keep_cnt_start[0]  = 0,        .keep_cnt_end[  0]  = 54,
    .pd_cnt_start[  0]  = 54,       .pd_cnt_end[    0]  = 54,
//g:
    .rgb_val_max[   1]  = 255,      .rgb_val_min[   1]  = 0,
    .cnt[           1]  = 36,       .next_cnt_dir[  1]  = 6,
    .cnt_unit[      1]  = 1,        .cnt_max_prd[   1]  = 108,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 0,
    .keep_cnt_start[1]  = 0,        .keep_cnt_end[  1]  = 54,
    .pd_cnt_start[  1]  = 54,       .pd_cnt_end[    1]  = 54,
//b:
    .rgb_val_max[   2]  = 255,      .rgb_val_min[   2]  = 0,
    .cnt[           2]  = 72,       .next_cnt_dir[  2]  = 6,
    .cnt_unit[      2]  = 1,        .cnt_max_prd[   2]  = 108,
    .pu_cnt_start[  2]  = 0,        .pu_cnt_end[    2]  = 0,
    .keep_cnt_start[2]  = 0,        .keep_cnt_end[  2]  = 54,
    .pd_cnt_start[  2]  = 54,       .pd_cnt_end[    2]  = 54,
};
static struct led_rgb_t mode2_led_rgb = {
    .mode_idx           = 2,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 0,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = -5,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 90,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 0,
    .keep_cnt_start[0]  = 0,        .keep_cnt_end[  0]  = 30,
    .pd_cnt_start[  0]  = 30,       .pd_cnt_end[    0]  = 30,
//g:
    .rgb_val_max[   1]  = 255,      .rgb_val_min[   1]  = 0,
    .cnt[           1]  = 30,       .next_cnt_dir[  1]  = -5,
    .cnt_unit[      1]  = 1,        .cnt_max_prd[   1]  = 90,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 0,
    .keep_cnt_start[1]  = 0,        .keep_cnt_end[  1]  = 30,
    .pd_cnt_start[  1]  = 30,       .pd_cnt_end[    1]  = 30,
//b:
    .rgb_val_max[   2]  = 255,      .rgb_val_min[   2]  = 0,
    .cnt[           2]  = 60,       .next_cnt_dir[  2]  = -5,
    .cnt_unit[      2]  = 1,        .cnt_max_prd[   2]  = 90,
    .pu_cnt_start[  2]  = 0,        .pu_cnt_end[    2]  = 0,
    .keep_cnt_start[2]  = 0,        .keep_cnt_end[  2]  = 30,
    .pd_cnt_start[  2]  = 30,       .pd_cnt_end[    2]  = 30,
};
static struct led_rgb_t mode3_led_rgb = {
    .mode_idx           = 3,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 0,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = 2,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 108,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 0,
    .keep_cnt_start[0]  = 0,        .keep_cnt_end[  0]  = 36,
    .pd_cnt_start[  0]  = 36,       .pd_cnt_end[    0]  = 36,
//g:
    .rgb_val_max[   1]  = 255,      .rgb_val_min[   1]  = 0,
    .cnt[           1]  = 36,       .next_cnt_dir[  1]  = 2,
    .cnt_unit[      1]  = 1,        .cnt_max_prd[   1]  = 108,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 0,
    .keep_cnt_start[1]  = 0,        .keep_cnt_end[  1]  = 36,
    .pd_cnt_start[  1]  = 36,       .pd_cnt_end[    1]  = 36,
//b:
    .rgb_val_max[   2]  = 255,      .rgb_val_min[   2]  = 0,
    .cnt[           2]  = 72,       .next_cnt_dir[  2]  = 2,
    .cnt_unit[      2]  = 1,        .cnt_max_prd[   2]  = 108,
    .pu_cnt_start[  2]  = 0,        .pu_cnt_end[    2]  = 0,
    .keep_cnt_start[2]  = 0,        .keep_cnt_end[  2]  = 36,
    .pd_cnt_start[  2]  = 36,       .pd_cnt_end[    2]  = 36,
};
static struct led_rgb_t mode4_led_rgb = {
    .mode_idx           = 4,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 0,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = -12,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 108,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 12,
    .keep_cnt_start[0]  = 12,       .keep_cnt_end[  0]  = 24,
    .pd_cnt_start[  0]  = 24,       .pd_cnt_end[    0]  = 36,
//g:
    .rgb_val_max[   1]  = 255,      .rgb_val_min[   1]  = 0,
    .cnt[           1]  = 36,       .next_cnt_dir[  1]  = -12,
    .cnt_unit[      1]  = 1,        .cnt_max_prd[   1]  = 108,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 12,
    .keep_cnt_start[1]  = 12,       .keep_cnt_end[  1]  = 24,
    .pd_cnt_start[  1]  = 24,       .pd_cnt_end[    1]  = 36,
//b:
    .rgb_val_max[   2]  = 255,      .rgb_val_min[   2]  = 0,
    .cnt[           2]  = 72,       .next_cnt_dir[  2]  = -12,
    .cnt_unit[      2]  = 1,        .cnt_max_prd[   2]  = 108,
    .pu_cnt_start[  2]  = 0,        .pu_cnt_end[    2]  = 12,
    .keep_cnt_start[2]  = 12,       .keep_cnt_end[  2]  = 24,
    .pd_cnt_start[  2]  = 24,       .pd_cnt_end[    2]  = 36,
};
static struct led_rgb_t mode5_led_rgb = {
    .mode_idx           = 5,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 0,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = 2,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 108,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 0,
    .keep_cnt_start[0]  = 0,        .keep_cnt_end[  0]  = 2,
    .pd_cnt_start[  0]  = 2,        .pd_cnt_end[    0]  = 2,
//g:
    .rgb_val_max[   1]  = 255,      .rgb_val_min[   1]  = 0,
    .cnt[           1]  = 36,       .next_cnt_dir[  1]  = 2,
    .cnt_unit[      1]  = 1,        .cnt_max_prd[   1]  = 108,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 0,
    .keep_cnt_start[1]  = 0,        .keep_cnt_end[  1]  = 2,
    .pd_cnt_start[  1]  = 2,        .pd_cnt_end[    1]  = 2,
//b:
    .rgb_val_max[   2]  = 255,      .rgb_val_min[   2]  = 0,
    .cnt[           2]  = 72,       .next_cnt_dir[  2]  = 2,
    .cnt_unit[      2]  = 1,        .cnt_max_prd[   2]  = 108,
    .pu_cnt_start[  2]  = 0,        .pu_cnt_end[    2]  = 0,
    .keep_cnt_start[2]  = 0,        .keep_cnt_end[  2]  = 2,
    .pd_cnt_start[  2]  = 2,        .pd_cnt_end[    2]  = 2,
};
static struct led_rgb_t mode6_led_rgb = {
    .mode_idx           = 6,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 200,
    .cnt[           0]  = 0,        .next_cnt_dir[  0]  = -18,
    .cnt_unit[      0]  = 1,        .cnt_max_prd[   0]  = 48,
    .pu_cnt_start[  0]  = 0,        .pu_cnt_end[    0]  = 0,
    .keep_cnt_start[0]  = 0,        .keep_cnt_end[  0]  = 24,
    .pd_cnt_start[  0]  = 24,        .pd_cnt_end[    0]  = 24,
    .next_sec_cnt_phase[0] = 18,
//g:
    .rgb_val_max[   1]  = 128,      .rgb_val_min[   1]  = 32,
    .cnt[           1]  = 0,        .next_cnt_dir[  1]  = 18,
    .cnt_unit[      1]  = 0,        .cnt_max_prd[   1]  = 108,
    .pu_cnt_start[  1]  = 0,        .pu_cnt_end[    1]  = 0,
    .keep_cnt_start[1]  = 0,        .keep_cnt_end[  1]  = 1,
    .pd_cnt_start[  1]  = 1,        .pd_cnt_end[    1]  = 108,
};
static struct led_rgb_t mode7_led_rgb = {
    .mode_idx           = 7,
    .div_sec_num        = LED_DIV_SEC,
    .sec_led_num        = LED_NUM,
    .cnt_freq           = 1,
//r:
    .rgb_val_max[   0]  = 255,      .rgb_val_min[   0]  = 255,
};
static struct led_rgb_t *led_rgb_table[] = {
    &mode0_led_rgb, ///< 流水灯
    &mode1_led_rgb, ///< 流水灯
    &mode2_led_rgb, ///< 流水灯
    &mode3_led_rgb, ///< 流水灯
    &mode4_led_rgb, ///< 流水灯
    &mode5_led_rgb, ///< 流水灯
    &mode6_led_rgb, ///< 用于4X6火焰效果
    &mode7_led_rgb, ///< 用于显示播歌的频点能量
};


static void ledc_rgb_to_buf(u8 r, u8 g, u8 b, u8 *buf, int idx)
{
    buf = buf + idx * 3;
    buf[2] = b;
    buf[1] = r;
    buf[0] = g;
}


/*
 * @brief 一段灯带亮灯的数量
 * @param led_rgb 该模式结构体参数
 * @param sec_num 第几段灯带
 * @return 可以亮灯的数量
 */
static int get_led_sec_on_num(struct led_rgb_t *led_rgb, int sec_num)
{
    int on_num = led_rgb->sec_led_num;
    switch (led_rgb->mode_idx) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    }
    return on_num;
}


/*
 * @brief 约束CNT值在周期值内
 * @param led_rgb 该模式结构体参数
 * @param colour 颜色号：0,红色  1,绿色  2,蓝色
 * @param cnt 颜色对应的计数值
 * @return 映射后的值
 */
static int get_map_cnt(struct led_rgb_t *led_rgb, int colour, int cnt)
{
    if (led_rgb->cnt_max_prd[colour] == 0) {
        return 0;
    }
    while (cnt < 0) {
        cnt += led_rgb->cnt_max_prd[colour];
    }
    cnt %= led_rgb->cnt_max_prd[colour];
    return cnt;
}


/*
 * @brief 将CNT值转换为RGB值
 * @param led_rgb 该模式结构体参数
 * @param colour 颜色号：0,红色  1,绿色  2,蓝色
 * @param cnt 颜色对应的计数值
 * @return 对应的颜色亮度值
 */
static u8 led_cnt_to_rgb_val(struct led_rgb_t *led_rgb, int colour, int cnt)
{
    u8 rgb_val = led_rgb->rgb_val_min[colour];
    int tmp_cnt;
    int i = colour;
    int rgb_val_delta = led_rgb->rgb_val_max[i] - led_rgb->rgb_val_min[i];
    if ((led_rgb->pu_cnt_start[i] <= cnt) && (cnt < led_rgb->pu_cnt_end[i])) {              //递增区间
        tmp_cnt = cnt - led_rgb->pu_cnt_start[i] + 1;
        rgb_val = led_rgb->rgb_val_min[i] + (tmp_cnt * rgb_val_delta / (led_rgb->pu_cnt_end[i] - led_rgb->pu_cnt_start[i]));
    } else if ((led_rgb->keep_cnt_start[i] <= cnt) && (cnt < led_rgb->keep_cnt_end[i])) {   //高维持区间
        rgb_val = led_rgb->rgb_val_max[i];
    } else if ((led_rgb->pd_cnt_start[i] <= cnt) && (cnt < led_rgb->pd_cnt_end[i])) {       //递减区间
        tmp_cnt = led_rgb->pd_cnt_end[i] - cnt - 1;
        rgb_val = led_rgb->rgb_val_min[i] + (tmp_cnt * rgb_val_delta / (led_rgb->pd_cnt_end[i] - led_rgb->pd_cnt_start[i]));
    }
    return rgb_val;
}


/*
 * @brief 更新RGB的DMA buf数据，并发送出去，更新灯带
 * @param led_rgb 该模式结构体参数
 * @param cnt 基础节拍计数值
 */
static void led_rgb_upgrade(struct led_rgb_t *led_rgb, int cnt)
{
    u8 r_val;
    u8 g_val;
    u8 b_val;
    if ((cnt % led_rgb->cnt_freq) == 0) {
        led_rgb->cnt[0] = get_map_cnt(led_rgb, 0, led_rgb->cnt[0] + led_rgb->cnt_unit[0]);
        led_rgb->cnt[1] = get_map_cnt(led_rgb, 1, led_rgb->cnt[1] + led_rgb->cnt_unit[1]);
        led_rgb->cnt[2] = get_map_cnt(led_rgb, 2, led_rgb->cnt[2] + led_rgb->cnt_unit[2]);
        for (int i = 0; i < led_rgb->div_sec_num; i ++) {
            int led_on_num = get_led_sec_on_num(led_rgb, i);
            for (int j = 0; j < led_rgb->sec_led_num; j ++) {
                r_val = led_cnt_to_rgb_val(led_rgb, 0, get_map_cnt(led_rgb, 0, led_rgb->cnt[0] + (i * led_rgb->next_sec_cnt_phase[0] + j) * led_rgb->next_cnt_dir[0]));
                g_val = led_cnt_to_rgb_val(led_rgb, 1, get_map_cnt(led_rgb, 1, led_rgb->cnt[1] + (i * led_rgb->next_sec_cnt_phase[1] + j) * led_rgb->next_cnt_dir[1]));
                b_val = led_cnt_to_rgb_val(led_rgb, 2, get_map_cnt(led_rgb, 2, led_rgb->cnt[2] + (i * led_rgb->next_sec_cnt_phase[2] + j) * led_rgb->next_cnt_dir[2]));
                if (j >= led_on_num) {
                    r_val = 0;
                    g_val = 0;
                    b_val = 0;
                }
                ledc_rgb_to_buf(r_val, g_val, b_val, led_rgb_val_buf, i * led_rgb->sec_led_num + j);
            }
        }
        dev_write(ledc_hdl, led_rgb_val_buf, led_rgb->div_sec_num * led_rgb->sec_led_num * 3);
        /* dev_ioctl(ledc_hdl, IOCTL_LEDC_WAIT_TX_END, 0); */
    }
}


/*
 * @brief 定时轮询各模式
 */
static void led_rgb_scan(void *priv)
{
    static u32 step_cnt = 0;
    static u32 mode_idx = 0;
    static struct led_rgb_t *led_rgb = NULL;
    if ((step_cnt % (LED_MODE_TIME * 1000 / LED_FREQ)) == 0) {
        step_cnt = 0;
        printf("mode:%d\n", mode_idx);
        led_rgb = led_rgb_table[mode_idx];
        mode_idx ++;
        if (mode_idx >= (sizeof(led_rgb_table) / 4)) {
            mode_idx = 0;
        }
    }
    led_rgb_upgrade(led_rgb, step_cnt);
    step_cnt ++;
}


__attribute__((aligned(4))) static u8 ledc_color_1[] = {
    /* G     R     B */
    255,  255,  255,
    255,    0,    0,
    0,  255,    0,
    0,    0,  255,
};


static void ledc_irq_cb(void)
{
    printf("i am ledc_irq_cb\n");
}


/*
 * LEDC1_PLATFORM_DATA_BEGIN(ledc_data)
 *     .port = IO_PORTA_05,
 *     .idle_level = LEDC_IDLE_LEVEL_L,
 *     .out_inv = LEDC_OUT_INV_NREV,
 *     .bit_inv = LEDC_BIT_INV_8BIT,
 *     .time_base = LEDC_TIME_BASE_42NS,
 *     .t1h_cnt = 24,
 *     .t1l_cnt = 7,
 *     .t0h_cnt = 7,
 *     .t0l_cnt = 24,
 *     .rst_time_cnt = 20000,
 * LEDC1_PLATFORM_DATA_END()
 */


static void ledc_test_task(void *arg)
{
    printf("******************  led test  *******************\n");

    //1.打开spi设备
    /* ledc_hdl = dev_open("ledc1", ledc_data);///< 使用传入的参数配置LEDC */
    ledc_hdl = dev_open("ledc1", NULL); ///< 使用板级的参数配置LEDC
    if (!ledc_hdl) {
        printf("ledc open err \n");
        goto exit;
    }

    dev_ioctl(ledc_hdl, IOCTL_LEDC_SET_LOOP_TIMES, 0); ///< 设置循环发送次数(循环过程中不会发送RESET信号)
    /* dev_ioctl(ledc_hdl, IOCTL_LEDC_SET_TX_ASYNC, 1); ///< 设置异步发送*/
    /* dev_ioctl(ledc_hdl, IOCTL_LEDC_SET_IRQ_CB, (u32)ledc_irq_cb); ///< 设置发送完成中断回调*/

    sys_timer_add(NULL, led_rgb_scan, LED_FREQ); ///< 使用上面的算法刷新LED灯
    /* dev_write(ledc_hdl, ledc_color_1, sizeof(ledc_color_1)); ///< 直接发送一组数据  */


    while (1) {
        os_time_dly(200);
    }

exit:
    if (ledc_hdl) { ///< 关闭spi设备
        dev_close(ledc_hdl);
    }
    while (1) {
        os_time_dly(100);
    }
}


static int c_main_ledc(void)
{
    os_task_create(ledc_test_task, NULL, 10, 1000, 0, "ledc_test_task");
    return 0;
}


late_initcall(c_main_ledc);

#endif // USE_LEDC_TEST_DEMO

#include "app_config.h"
#include "system/includes.h"
#include "device/device.h"
#include "asm/clock.h"

/*
 * 用户只能选择：JL_TIMER2、JL_TIMER3、JL_TIMER4、JL_TIMER5
 * 使用定时器2或者3映射PWM时，不能用于定时
 */

#ifdef  USE_TIMER_TEST1_DEMO

static SEC_USED(.volatile_ram) JL_TIMER_TypeDef *TMR = JL_TIMER4; ///< 选择定时器4
static SEC_USED(.volatile_ram) u8 timer_irq = IRQ_TIMER4_IDX;///< 选择定时器4
static SEC_USED(.volatile_ram) u32 timer_clk = 0;

#define AWINLINE   __attribute__((always_inline))
#define TSEC SEC_USED(.volatile_ram_code) ///< 当中断1ms一下，建议使用函数放在内部ram


static AWINLINE TSEC void timer_cfg(u32 freq, u32 us)
{
    u8 timer_index[16] =  {0, 4, 1, 5, 2,  6,  3,  7,   8,   12,  9,    13,   10,   14,   11,    15};
    u32 timer_table[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
    u32 clock = timer_clk;
    u8 psc = 0;
    /* u8 tmp = 0; */
    u32 prd = 0;
    u32 ts = us / (1000 * 1000); ///< 计算秒
    u32 tu = us % (1000 * 1000); ///< 计算秒剩余us
    /* u8 i; */
    float tp = 0;

    if (freq >= clock) {
        freq = clock;
    } else if (freq <= 1) {
        freq = 1;
        if (ts) {
            tp = (float)tu / (1000 * 1000);
        }
    }
    // 求prd值
    prd = clock / freq;
    if (prd > 65535) {
        for (psc = 0; psc < 16; psc++) {
            prd = (u32)(clock / (timer_table[psc]) / freq);
            if (prd <= 65535) {
                break;
            } else if (psc == 15) {
                prd = 65535;
                break;
            }
        }
    }

    prd = ts ? (prd * ts + tp * prd) : prd;
    psc = timer_index[psc];
    TMR->CON = 0;
    TMR->CNT = 0;
    SFR(TMR->CON, 10, 4, 1);///< 选择LSB作为TIMER时钟源
    TMR->CON |= BIT(14);
    TMR->PRD = prd;
    TMR->CON |= psc << 4; ///< lsb_clk分频
    TMR->CON |= BIT(0);
}


// 设置时间，该函数可以在中断调用重新设置定时器值
static void TSEC timer_set(u32 us)
{
    u32 freq = 1000000 / us;
    timer_cfg(freq, us);
}


// 设置频率，该函数可以在中断调用重新设置定时器值
static void TSEC timer_freq_set(u32 freq)
{
    timer_cfg(freq, 0);
}


static ___interrupt TSEC void timer_isr(void)
{
    if (TMR->CON & BIT(15)) {
        TMR->CON |= BIT(14);
        putchar('@');
        //todo，中断函数执行程序...
    }
}


static void timer_test1_task(void *arg)
{
    // 先获取定时器的时钟源
    timer_clk = clk_get("timer");

    // 注册中断函数定和中断优先级
    request_irq(timer_irq, 3, timer_isr, 0);

#if 1
    // 初始化50ms进一次中断
    timer_set(50 * 1000);
#else
    // 设置10K频率进中断
    timer_freq_set(10000);
#endif

    while (1) {
        printf("TMR->CON: 0x%x\n", TMR->CON);
        printf("TMR->CNT: 0x%x\n", TMR->CNT);
        os_time_dly(100);
    }
}


static int c_main_timer_1(void)
{
    os_task_create(timer_test1_task, NULL, 22, 1000, 0, "timer_test1_task");
    return 0;
}

late_initcall(c_main_timer_1);

#endif // USE_TIMER_TEST1_DEMO

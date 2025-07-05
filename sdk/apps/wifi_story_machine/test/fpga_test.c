#include "system/includes.h"
#include "os/os_api.h"
#include "database.h"
#include "asm/crc16.h"
#include "http/http_cli.h"
#include "fs/fs.h"
#include "app_config.h"
#include "system/init.h"
#include "device/device.h"
#include "asm/debug.h"
#include "asm/cache.h"
#include "asm/pwm.h"
#include "asm/dma.h"
#include "asm/clock.h"
#include "asm/eq.h"
#include "asm/includes.h"
#include "device/gpio.h"
#include "server/audio_server.h"
#include "generic/ascii.h"
#include "uart.h"

extern void early_puts(char *s);

/* #define CONFIG_FPGA_TEST_ENABLE */
/* #define CONFIG_FPGA_RTC_TEST_ENABLE */
/* #define CONFIG_FPGA_VM_TEST_ENABLE */
/* #define CONFIG_FPGA_IIC_TEST_ENABLE */
/* #define CONFIG_FPGA_SPI_TEST_ENABLE */
/* #define CONFIG_FPGA_FFT_TEST_ENABLE */
/* #define CONFIG_FPGA_SRC_TEST_ENABLE */
/* #define COFNIG_FPGA_SRC_REUSE_TEST_ENBALE */
/* #define CONFIG_FPGA_EQ_TEST_ENABLE */
/* #define CONFIG_FPGA_DMA_COPY_TEST_ENABLE */
/* #define CONFIG_FPGA_DCACHE_TEST_ENABLE */
/* #define CONFIG_FPGA_AES_SHA_TEST_ENABLE */
/* #define CONFIG_FPGA_ICACHE_TEST_ENABLE */
/* #define CONFIG_FPGA_UART_TEST_ENABLE */
/* #define CONFIG_FPGA_TIMER_PWM_TEST_ENABLE */
/* #define CONFIG_FPGA_PLNK_TEST_ENABLE */
/* #define CONFIG_FPGA_AUDIO_ADC_TEST_ENABLE */

#ifdef CONFIG_FPGA_RTC_TEST_ENABLE
static void rtc_test_task(void *p)
{
    struct sys_time test_rtc_time;
    void *rtc_hdl = dev_open("rtc", NULL);
    u8 alarm_set_flag = 1;

    while (1) {
        os_time_dly(100);
        dev_ioctl(rtc_hdl, IOCTL_GET_SYS_TIME, (u32)&test_rtc_time);
        printf("get_sys_time: %d-%d-%d %d:%d:%d", test_rtc_time.year, test_rtc_time.month, test_rtc_time.day, test_rtc_time.hour, test_rtc_time.min, test_rtc_time.sec);
        if (!alarm_set_flag) {
            test_rtc_time.min += 1;
            dev_ioctl(rtc_hdl, IOCTL_SET_ALARM, (u32)&test_rtc_time);
            alarm_set_flag = 0;
            dev_ioctl(rtc_hdl, IOCTL_GET_ALARM, (u32)&test_rtc_time);
            printf("get_alarm_time: %d-%d-%d %d:%d:%d", test_rtc_time.year, test_rtc_time.month, test_rtc_time.day, test_rtc_time.hour, test_rtc_time.min, test_rtc_time.sec);
            power_set_soft_poweroff(0);
        }
    }
}

static int rtc_test_init(void)
{
    return thread_fork("rtc_test", 1, 512, 0, 0, rtc_test_task, NULL);
}
late_initcall(rtc_test_init);
#endif


#ifdef CONFIG_FPGA_AES_SHA_TEST_ENABLE
static void aes_bt_test_task(void *p)
{
    int check_log_en = 1;
    extern void aes_ccm_test(int verbose);
    while (1) {
        aes_ccm_test(check_log_en);
    }
}


static void aes_thread_test_task(void *p)
{
    int check_log_en = 1;
    extern void aes_hal_test(int verbose);
    while (1) {
        aes_hal_test(check_log_en);
    }
}

static void aes_sha_test_task(void *p)
{
    int check_log_en = 1;
    while (1) {
        int mbedtls_aes_self_test(int verbose);
        int mbedtls_ccm_self_test(int verbose);
        int mbedtls_gcm_self_test(int verbose);
        int mbedtls_sha1_self_test(int verbose);
        int mbedtls_sha256_self_test(int verbose);
        ASSERT(mbedtls_aes_self_test(check_log_en) == 0);
        ASSERT(mbedtls_ccm_self_test(check_log_en) == 0);
        ASSERT(mbedtls_gcm_self_test(check_log_en) == 0);
        ASSERT(mbedtls_sha1_self_test(check_log_en) == 0);
        ASSERT(mbedtls_sha256_self_test(check_log_en) == 0);
    }
}

static int aes_sha_test_init(void)
{
    thread_fork("aes_bt_test", 1, 512, 0, 0, aes_bt_test_task, NULL);
    thread_fork("aes_thread_test", 1, 512, 0, 0, aes_thread_test_task, NULL);
    thread_fork("aes_sha_test", 1, 512, 0, 0, aes_sha_test_task, NULL);

    return 0;
}
#ifdef CONFIG_NET_ENABLE
late_initcall(aes_sha_test_init);
#endif
#endif


#ifdef CONFIG_FPGA_VM_TEST_ENABLE
static void vm_write_read_test(void)
{
    u8 vm_buf[252];
    u16 crc1 = 0;
    u16 crc2 = 0;

    while (1) {
        for (int i = 0; i < sizeof(vm_buf); ++i) {
            vm_buf[i] = JL_RAND->R64L;
        }
        crc1 = CRC16(vm_buf, sizeof(vm_buf));
        if (syscfg_write(253, vm_buf, sizeof(vm_buf)) < 0) {
            printf("buffer write fail !");
        }
        memset(vm_buf, 0, sizeof(vm_buf));
        if (syscfg_read(253, vm_buf, sizeof(vm_buf)) < 0) {
            printf("buffer read fail !");
        }
        crc2 = CRC16(vm_buf, sizeof(vm_buf));
        if (crc1 != crc2) {
            printf("vm crc1 : 0x%x != crc2 : 0x%x", crc1, crc2);
        }
        os_time_dly(100);
    }
}

static void vm_test(void)
{
    u8 *buf = malloc(1024);

    u32 seed = JL_RAND->R64L;

    int r = 0;
#define     WRITE_DATA  1

#if WRITE_DATA
    for (int id = 1; id < 32; id++) {
        srand(id + seed);
        u16 len = rand() % 1024;
        for (int i = 0; i < len; i++) {
            buf[i] = rand();
        }

        r = vm_write(id, buf, len);
        if (r != len) {
            printf("vm_write %d", r);
            while (1);
        }
    }
#endif

    u8 *buf_rd = malloc(1024);

    for (int id = 1; id < 32; id++) {

        srand(id + seed);
        u16 len = rand() % 1024;
        for (int i = 0; i < len; i++) {

            buf[i] = rand();
        }

        r = vm_read(id, buf_rd, len);
        if (r != len) {
            printf("vm_read %d", r);
            while (1);
        }

        if (memcmp(buf, buf_rd, len)) {
            printf("data error ");
            printf_buf(buf, len);
            printf_buf(buf_rd, len);
        }

    }

    for (int id = 32; id < 64; id++) {

        srand(id + seed);
        u16 len = rand() % 1024;
        for (int i = 0; i < len; i++) {

            buf[i] = rand();
        }

#if WRITE_DATA
        r = vm_write(id, buf, len);
        if (r != len) {
            printf("vm_write %d", r);
            while (1);
        }
#endif

        r = vm_read(id, buf_rd, len);
        if (r != len) {
            printf("vm_read %d", r);
            while (1);
        }

        if (memcmp(buf, buf_rd, len)) {
            printf("data error ");
            printf_buf(buf, len);
            printf_buf(buf_rd, len);
        }
    }
}

#include "vm.h"
#include <stdlib.h>
static u32 hw_random(void)
{
    return JL_RAND->R64L;
}

static void tz_flash_task(void *p)
{
    u8 *buf = malloc(1024);
    u8 *buf_rd = malloc(1024);

    const u32 seed = 1;//JL_RAND->R64L;

    int r = 0;
    while (1) {
        u32 id = hw_random() % 255 + 1;

        srand(id + seed);
        u16 len = rand() % 1024 + 1;
        for (int i = 0; i < len; i++) {
            buf[i] = rand();
        }

        r = vm_write(id, buf, len);
        if (r != len) {
            r_printf("vm_write %d", r);
            if (r == -509) {
                /* vm_eraser(); */
                continue;
            }
        }

        r = vm_read(id, buf_rd, len);
        if (r != len) {
            r_printf("vm_read %d", r);
        }

        if (memcmp(buf, buf_rd, len)) {
            r_printf("data error ");
            put_buf(buf, len);
            put_buf(buf_rd, len);
            while (1) {
                asm("lockset");
            }
        }

        os_time_dly(hw_random() % 100);
    }
}
#endif


#ifdef CONFIG_FPGA_IIC_TEST_ENABLE

#include "device/iic.h"

static void *iic1_dev_handel;

#define _24CXX_HARDADDR_DEAL(addr) (addr/MEM_SIZE+0)

//芯片基本信息
#define MEM_SIZE		0x0080

//芯片常量
#define DEV_24CXX_MAIN_ADDR	0xA0
#define DEV_24CXX_READ	0x01
#define DEV_24CXX_WRITE	0x00

#define _24_ADDR 0

static void _24cxx_writebyte(u32 addr, u8 data)
{
    int err = 0;
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE_WITH_START_BIT, DEV_24CXX_MAIN_ADDR | (_24CXX_HARDADDR_DEAL(addr) << 1) | DEV_24CXX_WRITE);
    if (err) {
        printf("IOCTL_IIC_TX_BYTE_WITH_START_BIT FIAL\n");
        return;
    }
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE, addr & (MEM_SIZE - 1));
    if (err) {
        printf("IOCTL_IIC_TX_BYTE FIAL\n");
        return;
    }
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, data);
    if (err) {
        printf("IOCTL_IIC_TX_BYTE_WITH_STOP_BIT FIAL\n");
        return;
    }
}

static u8 _24cxx_readbyte(u32 addr)
{
    int err = 0;
    unsigned char temp;
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE_WITH_START_BIT, DEV_24CXX_MAIN_ADDR | (_24CXX_HARDADDR_DEAL(addr) << 1) | DEV_24CXX_WRITE);
    if (err) {
        printf("IOCTL_IIC_TX_BYTE_WITH_START_BIT FIAL\n");
        return -1;
    }
    /* err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE, addr & (MEM_SIZE - 1)); */
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, addr & (MEM_SIZE - 1));
    if (err) {
        printf("IOCTL_IIC_TX_BYTE FIAL\n");
        return -1;
    }
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_TX_BYTE_WITH_START_BIT, DEV_24CXX_MAIN_ADDR | (_24CXX_HARDADDR_DEAL(addr) << 1) | DEV_24CXX_READ);
    if (err) {
        printf("IOCTL_IIC_TX_BYTE_WITH_START_BIT FIAL\n");
        return -1;
    }
    err = dev_ioctl(iic1_dev_handel, IOCTL_IIC_RX_BYTE_WITH_STOP_BIT, (int)&temp);
    if (err) {
        printf("IOCTL_IIC_RX_BYTE_WITH_STOP_BIT FIAL\n");
        return -1;
    }
    return temp;
}

static void iic_24cxx_test(void)
{
    u8 test_buf[0x80];
    u8 res = 0;

    iic1_dev_handel = dev_open("iic0", NULL);
    if (!iic1_dev_handel) {
        printf("iic0 dev open err\n");
        ASSERT(0);
    }

#if 0
    request_irq(IRQ_IIC_IDX, 2, iic_isr, 0);
    JL_IIC->CON0 |= BIT(8);
#endif

    /* printf(" iic open ok!\n"); */

#if 0
    for (u32 i = 0; i < sizeof(test_buf); i++) {
        /* test_buf[i] = 0x20 + i; */
        test_buf[i] = JL_RAND->R64L;
        _24cxx_writebyte(i + _24_ADDR, test_buf[i]);
        delay(48000);
        res = _24cxx_readbyte(i + _24_ADDR);
        if (res != test_buf[i]) {
            /* gpio_direction_output(IO_PORTH_02, 1); */
            printf("\n_24cxx_writebyte[%d] = 0x%x \n", i, test_buf[i]);
            printf("_24CXXX_ReadByte[%d] = 0x%x\n", i, res);
            printf("test fail!\n");
            /* gpio_direction_output(IO_PORTH_02, 0); */
            /* while (1); */
        }
        delay(48000);
    }
#else
    static u8 i = 0;
    test_buf[i] = JL_RAND->R64L;
    dev_ioctl(iic1_dev_handel, IOCTL_IIC_START, 0);
    _24cxx_writebyte(i + _24_ADDR, test_buf[i]);
    dev_ioctl(iic1_dev_handel, IOCTL_IIC_STOP, 0);
    os_time_dly(1);
    dev_ioctl(iic1_dev_handel, IOCTL_IIC_START, 0);
    res = _24cxx_readbyte(i + _24_ADDR);
    dev_ioctl(iic1_dev_handel, IOCTL_IIC_STOP, 0);
    if (res != test_buf[i]) {
        /* gpio_direction_output(IO_PORTH_02, 1); */
        printf("\n_24cxx_writebyte[%d] = 0x%x \n", i, test_buf[i]);
        printf("_24CXXX_ReadByte[%d] = 0x%x\n", i, res);
        printf("test fail!\n");
        /* gpio_direction_output(IO_PORTH_02, 0); */
        /* while (1); */
    }
    if (++i >= 128) {
        i = 0;
    }
#endif

    dev_close(iic1_dev_handel);

    iic1_dev_handel = NULL;

    /* printf("iic test end!\n"); */
}

static void iic_test_task(void *p)
{
    while (1) {
        os_time_dly(100);
        iic_24cxx_test();
    }
}

static int iic_test_init(void)
{
    return thread_fork("iic_test", 3, 512, 0, 0, iic_test_task, NULL);
}
late_initcall(iic_test_init);

#endif


/********************DMA COPY TEST*****************************/
#if defined CONFIG_FPGA_DMA_COPY_TEST_ENABLE && !defined CONFIG_NO_SDRAM_ENABLE

#define DMA_TEST_BUF_SIZE	(100 * 1024)
#define SRAM_DMA_TEST_BUF_SIZE	(10 * 1024)

static const u8 dma_tx_buf_rom[DMA_TEST_BUF_SIZE] ALIGNE(4) = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,	31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,	47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,	63,
    [1024 * 10] = 1, [1024 * 20] = 2, [1024 * 30] = 3, [1024 * 40] = 4, [1024 * 50] = 5,
    [1024 * 60] = 6, [1024 * 70] = 7, [1024 * 80] = 8, [1024 * 90] = 9, [1024 * 100 - 1] = 10,
};

static u8 dma_tx_buf_sdram[DMA_TEST_BUF_SIZE] ALIGNE(32);
static u8 dma_rx_buf_sdram[DMA_TEST_BUF_SIZE] ALIGNE(32);
static u8 dma_tx_buf_ram[SRAM_DMA_TEST_BUF_SIZE] sec(.sram) ALIGNE(4);
static u8 dma_rx_buf_ram[SRAM_DMA_TEST_BUF_SIZE] sec(.sram) ALIGNE(4);

static void dma_rom_to_sdram(void)
{
    int ret = 0;

    dma_copy_sync(dma_rx_buf_sdram, (void *)dma_tx_buf_rom, sizeof(dma_rx_buf_sdram));
    for (int i = 0; i < sizeof(dma_rx_buf_sdram); ++i) {
        if (dma_rx_buf_sdram[i] != dma_tx_buf_rom[i]) {
            printf("dma_rom_to_sdram\n");
            printf("dma_tx_buf_rom = 0x%x, dma_rx_buf_sdram = 0x%x\n", dma_tx_buf_rom[i], dma_rx_buf_sdram[i]);
            ASSERT(0);
        }
    }
}

static void dma_rom_to_ram0(void)
{
    int ret = 0;

    dma_copy_sync(dma_rx_buf_ram, (void *)dma_tx_buf_rom, sizeof(dma_rx_buf_ram));
    for (int i = 0; i < sizeof(dma_rx_buf_ram); ++i) {
        if (dma_rx_buf_ram[i] != dma_tx_buf_rom[i]) {
            printf("dma_rom_to_ram0\n");
            printf("dma_tx_buf_rom = 0x%x, dma_rx_buf_ram = 0x%x\n", dma_tx_buf_rom[i], dma_rx_buf_ram[i]);
            ASSERT(0);
        }
    }
}

static void dma_sdram_to_sdram(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_sdram) - 2; i++) {
        dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram) - 2);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));

    /* put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram)); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_sdram)); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(dma_rx_buf_sdram, dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
    /* put_buf(dma_rx_buf[j], sizeof(dma_rx_buf)); */
    ret = CRC16(dma_rx_buf_sdram, sizeof(dma_tx_buf_sdram));
    if (ret) {
        printf("dma_sdram_to_sdram\n");
        printf("dma_tx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_tx_buf_sdram, ret);
        printf("dma_rx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_rx_buf_sdram, ret);
        put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
        put_buf(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
        ASSERT(0);
    }
}

static void dma_ram0_to_ram0(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_ram) - 2; i++) {
        dma_tx_buf_ram[i] = (u8)JL_RAND->R64L;
    }
    ret = CRC16(dma_tx_buf_ram, sizeof(dma_tx_buf_ram) - 2);
    dma_tx_buf_ram[sizeof(dma_tx_buf_ram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_ram[sizeof(dma_tx_buf_ram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_ram, 0, sizeof(dma_rx_buf_ram));

    /* put_buf(dma_tx_buf_ram[j], sizeof(dma_tx_buf_ram[j])); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_ram[0])); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(dma_rx_buf_ram, dma_tx_buf_ram, sizeof(dma_tx_buf_ram));
    /* put_buf(dma_rx_buf_ram[j], sizeof(dma_rx_buf_ram[j])); */
    ret = CRC16(dma_rx_buf_ram, sizeof(dma_tx_buf_ram));
    if (ret) {
        printf("dma_ram0_to_ram0 ret = 0x%x  \n", ret);
        put_buf(dma_tx_buf_ram, sizeof(dma_tx_buf_ram));
        put_buf(dma_rx_buf_ram, sizeof(dma_rx_buf_ram));
        ASSERT(0);
    }
}

static void dma_ram0_to_sdram(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_ram) - 2; i++) {
        dma_tx_buf_ram[i] = (u8)JL_RAND->R64L;
    }
    ret = CRC16(dma_tx_buf_ram, sizeof(dma_tx_buf_ram) - 2);
    dma_tx_buf_ram[sizeof(dma_tx_buf_ram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_ram[sizeof(dma_tx_buf_ram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_sdram, 0, sizeof(dma_tx_buf_ram));
    /* put_buf(dma_tx_buf_ram[j], sizeof(dma_tx_buf_ram[j])); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_ram[0])); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(dma_rx_buf_sdram, dma_tx_buf_ram, sizeof(dma_tx_buf_ram));
    /* put_buf(dma_rx_buf_sdram[j], sizeof(dma_rx_buf_sdram[j])); */
    ret = CRC16(dma_rx_buf_sdram, sizeof(dma_tx_buf_ram));
    if (ret) {
        printf("dma_ram0_to_sdram ret = 0x%x  \n", ret);
        put_buf(dma_tx_buf_ram, sizeof(dma_tx_buf_ram));
        put_buf(dma_rx_buf_sdram, sizeof(dma_tx_buf_ram));
        ASSERT(0);
    }
}

static void dma_flash_to_sdram(void)
{
    int ret = 0;

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));
    dma_copy_sync(dma_rx_buf_sdram, (void *)0x8000000, sizeof(dma_rx_buf_sdram));
    /* put_buf(dma_rx_buf_sdram[j], sizeof(dma_rx_buf_sdram[j])); */
    for (int i = 0; i < sizeof(dma_rx_buf_sdram); ++i) {
        if (dma_rx_buf_sdram[i] != *(u8 *)(0x8000000 + i)) {
            printf("dma_flash_to_sdram i = 0x%x \n", i);
            put_buf(&dma_rx_buf_sdram[i], 4096);
            put_buf((u8 *)(0x8000000 + i), 4096);
            ASSERT(0);
        }
    }
}

static void dma_flash_to_sdram_nocache(void)
{
    int ret = 0;

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));
    DcuFlushinvRegion((u32 *)dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
    dma_copy_sync((void *)NO_CACHE_ADDR(dma_rx_buf_sdram), (void *)0x8000000, sizeof(dma_rx_buf_sdram));
    if ((u32)dma_rx_buf_sdram % 32) {
        DcuInvalidRegion((u32 *)dma_rx_buf_sdram, 32 - (u32)dma_rx_buf_sdram % 32);
    }
    if ((u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32) {
        DcuInvalidRegion((u32 *)(dma_rx_buf_sdram + sizeof(dma_rx_buf_sdram) - (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32), (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32);
    }
    /* put_buf(dma_rx_buf_sdram[j], sizeof(dma_rx_buf_sdram[j])); */
    for (int i = 0; i < sizeof(dma_rx_buf_sdram); ++i) {
        if (dma_rx_buf_sdram[i] != *(u8 *)(0x8000000 + i)) {
            printf("dma_flash_to_sdram i = 0x%x \n", i);
            put_buf(&dma_rx_buf_sdram[i], 4096);
            put_buf((u8 *)(0x8000000 + i), 4096);
            ASSERT(0);
        }
    }
}

static void dma_sdram_to_ram0(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_rx_buf_ram) - 2; i++) {
        dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_tx_buf_sdram, sizeof(dma_rx_buf_ram) - 2);
    dma_tx_buf_sdram[sizeof(dma_rx_buf_ram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_sdram[sizeof(dma_rx_buf_ram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_ram, 0, sizeof(dma_rx_buf_ram));
    /* put_buf(dma_tx_buf_sdram[j], sizeof(dma_tx_buf_sdram[j])); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_sdram[0])); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(dma_rx_buf_ram, dma_tx_buf_sdram, sizeof(dma_rx_buf_ram));
    /* put_buf(dma_rx_buf_ram[j], sizeof(dma_rx_buf_ram[j])); */
    ret = CRC16(dma_rx_buf_ram, sizeof(dma_rx_buf_ram));
    if (ret) {
        printf("dma_sdram_to_ram0 ret = 0x%x  \n", ret);
        put_buf(dma_rx_buf_ram, sizeof(dma_rx_buf_ram));
        put_buf(dma_tx_buf_sdram, sizeof(dma_rx_buf_ram));
        ASSERT(0);
    }
}

static void dma_sdram_nocache_to_sdram_nocache(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_sdram) - 2; i++) {
        dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram) - 2);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));

    DcuFlushRegion((u32 *)dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
    DcuFlushinvRegion((u32 *)dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
    dma_copy_sync((void *)NO_CACHE_ADDR(dma_rx_buf_sdram), (void *)NO_CACHE_ADDR(dma_tx_buf_sdram), sizeof(dma_tx_buf_sdram));
    if ((u32)dma_rx_buf_sdram % 32) {
        DcuInvalidRegion((u32 *)dma_rx_buf_sdram, 32 - (u32)dma_rx_buf_sdram % 32);
    }
    if ((u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32) {
        DcuInvalidRegion((u32 *)(dma_rx_buf_sdram + sizeof(dma_rx_buf_sdram) - (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32), (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32);
    }

    ret = CRC16(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
    if (ret) {
        printf("dma_sdram_nocache_to_sdram_nocache\n");
        printf("dma_tx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_tx_buf_sdram, ret);
        printf("dma_rx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_rx_buf_sdram, ret);
        put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
        put_buf(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
        ASSERT(0);
    }
}

static void dma_sdram_nocache_to_sdram(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_sdram) - 2; i++) {
        dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram) - 2);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));

    DcuFlushRegion((u32 *)dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
    dma_copy_sync(dma_rx_buf_sdram, (void *)NO_CACHE_ADDR(dma_tx_buf_sdram), sizeof(dma_tx_buf_sdram));

    ret = CRC16(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
    if (ret) {
        printf("dma_sdram_nocache_to_sdram\n");
        printf("dma_tx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_tx_buf_sdram, ret);
        printf("dma_rx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_rx_buf_sdram, ret);
        put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
        put_buf(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
        ASSERT(0);
    }
}

static void dma_sdram_to_sdram_nocache(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_sdram) - 2; i++) {
        dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram) - 2);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_sdram[sizeof(dma_tx_buf_sdram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));

    DcuFlushinvRegion((u32 *)dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
    dma_copy_sync((void *)NO_CACHE_ADDR(dma_rx_buf_sdram), dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
    if ((u32)dma_rx_buf_sdram % 32) {
        DcuInvalidRegion((u32 *)dma_rx_buf_sdram, 32 - (u32)dma_rx_buf_sdram % 32);
    }
    if ((u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32) {
        DcuInvalidRegion((u32 *)(dma_rx_buf_sdram + sizeof(dma_rx_buf_sdram) - (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32), (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32);
    }

    ret = CRC16(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
    if (ret) {
        printf("dma_sdram_to_sdram_nocache\n");
        printf("dma_tx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_tx_buf_sdram, ret);
        printf("dma_rx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)dma_rx_buf_sdram, ret);
        put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram));
        put_buf(dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));
        ASSERT(0);
    }
}

static void dma_ram0_to_sdram_nocache(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_tx_buf_ram) - 2; i++) {
        dma_tx_buf_ram[i] = (u8)JL_RAND->R64L;
    }
    ret = CRC16(dma_tx_buf_ram, sizeof(dma_tx_buf_ram) - 2);
    dma_tx_buf_ram[sizeof(dma_tx_buf_ram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_ram[sizeof(dma_tx_buf_ram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_sdram, 0, sizeof(dma_tx_buf_ram));

    DcuFlushinvRegion((u32 *)dma_rx_buf_sdram, sizeof(dma_tx_buf_ram));
    dma_copy_sync((void *)NO_CACHE_ADDR(dma_rx_buf_sdram), dma_tx_buf_ram, sizeof(dma_tx_buf_ram));
    if ((u32)dma_rx_buf_sdram % 32) {
        DcuInvalidRegion((u32 *)dma_rx_buf_sdram, 32 - (u32)dma_rx_buf_sdram % 32);
    }
    if ((u32)&dma_rx_buf_sdram[sizeof(dma_tx_buf_ram)] % 32) {
        DcuInvalidRegion((u32 *)(dma_rx_buf_sdram + sizeof(dma_tx_buf_ram) - (u32)&dma_rx_buf_sdram[sizeof(dma_tx_buf_ram)] % 32), (u32)&dma_rx_buf_sdram[sizeof(dma_tx_buf_ram)] % 32);
    }

    ret = CRC16(dma_rx_buf_sdram, sizeof(dma_tx_buf_ram));
    if (ret) {
        printf("dma_ram0_to_sdram_nocache ret = 0x%x  \n", ret);
        put_buf(dma_tx_buf_ram, sizeof(dma_tx_buf_ram));
        put_buf(dma_rx_buf_sdram, sizeof(dma_tx_buf_ram));
        ASSERT(0);
    }
}

static void dma_sdram_to_ram0_nocache(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_rx_buf_ram) - 2; i++) {
        dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_tx_buf_sdram, sizeof(dma_rx_buf_ram) - 2);
    dma_tx_buf_sdram[sizeof(dma_rx_buf_ram) - 2] = (ret >> 8 & 0x00ff);
    dma_tx_buf_sdram[sizeof(dma_rx_buf_ram) - 1] = (ret & 0x00ff);

    memset(dma_rx_buf_ram, 0, sizeof(dma_rx_buf_ram));

    DcuFlushRegion((u32 *)dma_tx_buf_sdram, sizeof(dma_rx_buf_ram));
    dma_copy_sync(dma_rx_buf_ram, (void *)NO_CACHE_ADDR(dma_tx_buf_sdram), sizeof(dma_rx_buf_ram));

    ret = CRC16(dma_rx_buf_ram, sizeof(dma_rx_buf_ram));
    if (ret) {
        printf("dma_sdram_to_ram0_nocache ret = 0x%x  \n", ret);
        put_buf(dma_rx_buf_ram, sizeof(dma_rx_buf_ram));
        put_buf(dma_tx_buf_sdram, sizeof(dma_rx_buf_ram));
        ASSERT(0);
    }
}

#if __SDRAM_SIZE__ >= (16 * 1024 * 1024)
static u8 large_dma_tx_buf_sdram[6 * 1024 * 1024] ALIGNE(32);
static u8 large_dma_rx_buf_sdram[6 * 1024 * 1024] ALIGNE(32);
#else
static u8 large_dma_tx_buf_sdram[1280 * 1024] ALIGNE(32);
static u8 large_dma_rx_buf_sdram[1280 * 1024] ALIGNE(32);
#endif

static void large_dma_sdram_to_sdram(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(large_dma_tx_buf_sdram) - 2; i++) {
        large_dma_tx_buf_sdram[i] = (u8)JL_RAND->R64L;
    }
    ret = CRC16(large_dma_tx_buf_sdram, sizeof(large_dma_tx_buf_sdram) - 2);
    large_dma_tx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 2] = (ret >> 8 & 0x00ff);
    large_dma_tx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 1] = (ret & 0x00ff);

    memset(large_dma_rx_buf_sdram, 0, sizeof(large_dma_rx_buf_sdram));

    /* put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram)); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_sdram)); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(large_dma_rx_buf_sdram, large_dma_tx_buf_sdram, sizeof(large_dma_tx_buf_sdram));
    /* put_buf(dma_rx_buf[j], sizeof(dma_rx_buf)); */
    ret = CRC16(large_dma_rx_buf_sdram, sizeof(large_dma_tx_buf_sdram));
    if (ret) {
        printf("large_dma_sdram_to_sdram\n");
        printf("dma_tx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)large_dma_tx_buf_sdram, ret);
        printf("dma_rx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)large_dma_rx_buf_sdram, (large_dma_rx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 2] << 8) | large_dma_rx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 1]);
        for (u32 i = 0; i < sizeof(large_dma_tx_buf_sdram) - 2; ++ i) {
            if (large_dma_tx_buf_sdram[i] != large_dma_rx_buf_sdram[i]) {
                printf("offset:0x%x, tx:0x%x, rx:0x%x", i, large_dma_tx_buf_sdram[i], large_dma_rx_buf_sdram[i]);
                put_buf(&large_dma_tx_buf_sdram[i], 4096);
                put_buf(&large_dma_rx_buf_sdram[i], 4096);
                break;
            }
        }
        ret = CRC16(large_dma_rx_buf_sdram, sizeof(large_dma_rx_buf_sdram));
        if (ret) {
            printf("again crc : 0x%x", ret);
        }
        os_time_dly(10);
        ASSERT(0);
    }
}

static void large_dma_sdram_to_sdram_nocache(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(large_dma_tx_buf_sdram) - 2; i++) {
        large_dma_tx_buf_sdram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(large_dma_tx_buf_sdram, sizeof(large_dma_tx_buf_sdram) - 2);
    large_dma_tx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 2] = (ret >> 8 & 0x00ff);
    large_dma_tx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 1] = (ret & 0x00ff);

    memset(large_dma_rx_buf_sdram, 0, sizeof(large_dma_rx_buf_sdram));

    DcuFlushRegion((u32 *)large_dma_tx_buf_sdram, sizeof(large_dma_tx_buf_sdram));
    DcuFlushinvRegion((u32 *)large_dma_rx_buf_sdram, sizeof(large_dma_rx_buf_sdram));
    dma_copy_sync((void *)NO_CACHE_ADDR(large_dma_rx_buf_sdram), (void *)NO_CACHE_ADDR(large_dma_tx_buf_sdram), sizeof(large_dma_tx_buf_sdram));

    ret = CRC16(large_dma_rx_buf_sdram, sizeof(large_dma_rx_buf_sdram));
    if (ret) {
        printf("large_dma_sdram_to_sdram_nocache\n");
        printf("dma_tx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)large_dma_tx_buf_sdram, ret);
        printf("dma_rx_buf_sdram = 0x%x, ret = 0x%x\n", (u32)large_dma_rx_buf_sdram, (large_dma_rx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 2] << 8) | large_dma_rx_buf_sdram[sizeof(large_dma_tx_buf_sdram) - 1]);
        for (u32 i = 0; i < sizeof(large_dma_tx_buf_sdram) - 2; ++ i) {
            if (large_dma_tx_buf_sdram[i] != large_dma_rx_buf_sdram[i]) {
                printf("offset:0x%x, tx:0x%x, rx:0x%x", i, large_dma_tx_buf_sdram[i], large_dma_rx_buf_sdram[i]);
                put_buf(&large_dma_tx_buf_sdram[i], 4096);
                put_buf(&large_dma_rx_buf_sdram[i], 4096);
                break;
            }
        }
        ret = CRC16(large_dma_rx_buf_sdram, sizeof(large_dma_rx_buf_sdram));
        if (ret) {
            printf("again crc : 0x%x", ret);
        }
        os_time_dly(10);
        ASSERT(0);
    }
}

#if 0
static u8 dma_buf_cacheram[27 * 1024] ALIGNE(32) sec(.memp_memory_x);
static u8 dma_buf_ram[27 * 1024] ALIGNE(32) sec(.sram);

static void dma_cacheram_to_ram(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_buf_cacheram) - 2; i++) {
        dma_buf_cacheram[i] = (u8)JL_RAND->R64L;
    }
    ret = CRC16(dma_buf_cacheram, sizeof(dma_buf_cacheram) - 2);
    dma_buf_cacheram[sizeof(dma_buf_cacheram) - 2] = (ret >> 8 & 0x00ff);
    dma_buf_cacheram[sizeof(dma_buf_cacheram) - 1] = (ret & 0x00ff);

    memset(dma_buf_ram, 0, sizeof(dma_buf_ram));

    /* put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram)); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_sdram)); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(dma_buf_ram, dma_buf_cacheram, sizeof(dma_buf_cacheram));
    /* put_buf(dma_rx_buf[j], sizeof(dma_rx_buf)); */
    ret = CRC16(dma_buf_ram, sizeof(dma_buf_cacheram));
    if (ret) {
        printf("dma_cacheram_to_ram\n");
        printf("dma_buf_cacheram = 0x%x, ret = 0x%x\n", (u32)dma_buf_cacheram, ret);
        printf("dma_buf_ram = 0x%x, ret = 0x%x\n", (u32)dma_buf_ram, ret);
        ASSERT(0);
    }
}

static void dma_ram_to_cacheram(void)
{
    int ret = 0;

    for (int i = 0; i < sizeof(dma_buf_ram) - 2; i++) {
        dma_buf_ram[i] = (u8)JL_RAND->R64H;
    }
    ret = CRC16(dma_buf_ram, sizeof(dma_buf_ram) - 2);
    dma_buf_ram[sizeof(dma_buf_ram) - 2] = (ret >> 8 & 0x00ff);
    dma_buf_ram[sizeof(dma_buf_ram) - 1] = (ret & 0x00ff);

    memset(dma_buf_cacheram, 0, sizeof(dma_buf_cacheram));

    /* put_buf(dma_tx_buf_sdram, sizeof(dma_tx_buf_sdram)); */
    /* printf("sizeof:%d\n", sizeof(dma_tx_buf_sdram)); */
    /* puts("\n\n\n\n!!!\n\n\n"); */
    dma_copy_sync(dma_buf_cacheram, dma_buf_ram, sizeof(dma_buf_ram));
    /* put_buf(dma_rx_buf[j], sizeof(dma_rx_buf)); */
    ret = CRC16(dma_buf_cacheram, sizeof(dma_buf_ram));
    if (ret) {
        printf("dma_cacheram_to_ram\n");
        printf("dma_buf_ram = 0x%x, ret = 0x%x\n", (u32)dma_buf_ram, ret);
        printf("dma_buf_cacheram = 0x%x, ret = 0x%x\n", (u32)dma_buf_cacheram, ret);
        ASSERT(0);
    }
}

#endif

static void dma_ram0_memset(void)
{
    u8 rand = JL_RAND->R64L;

    memset(dma_rx_buf_ram, 0, sizeof(dma_rx_buf_ram));

    dma_memset_sync(dma_rx_buf_ram, rand, sizeof(dma_rx_buf_ram));

    for (int i = 0; i < sizeof(dma_rx_buf_ram); ++i) {
        if (dma_rx_buf_ram[i] != rand) {
            printf("dma_ram0_memset err result = 0x%x, rand = 0x%x, offset = 0x%x\n", dma_rx_buf_ram[i], rand, i);
            ASSERT(0);
        }
    }
}

static void dma_sdram_memset(void)
{
    u8 rand = JL_RAND->R64L;

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));

    dma_memset_sync(dma_rx_buf_sdram, rand, sizeof(dma_rx_buf_sdram));

    for (int i = 0; i < sizeof(dma_rx_buf_sdram); ++i) {
        if (dma_rx_buf_sdram[i] != rand) {
            printf("dma_sdram_memset err result = 0x%x, rand = 0x%x, offset = 0x%x\n", dma_rx_buf_sdram[i], rand, i);
            ASSERT(0);
        }
    }
}

static void dma_sdram_nocache_memset(void)
{
    u8 rand = JL_RAND->R64L;

    memset(dma_rx_buf_sdram, 0, sizeof(dma_rx_buf_sdram));

    DcuFlushinvRegion((u32 *)dma_rx_buf_sdram, sizeof(dma_rx_buf_sdram));

    dma_memset_sync(dma_rx_buf_sdram, rand, sizeof(dma_rx_buf_sdram));

    if ((u32)dma_rx_buf_sdram % 32) {
        DcuInvalidRegion((u32 *)dma_rx_buf_sdram, 32 - (u32)dma_rx_buf_sdram % 32);
    }
    if ((u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32) {
        DcuInvalidRegion((u32 *)(dma_rx_buf_sdram + sizeof(dma_rx_buf_sdram) - (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32), (u32)&dma_rx_buf_sdram[sizeof(dma_rx_buf_sdram)] % 32);
    }

    for (int i = 0; i < sizeof(dma_rx_buf_sdram); ++i) {
        if (dma_rx_buf_sdram[i] != rand) {
            printf("dma_sdram_nocache_memset err result = 0x%x, rand = 0x%x, offset = 0x%x\n", dma_rx_buf_sdram[i], rand, i);
            ASSERT(0);
        }
    }
}

static void dma_copy_test_task(void *p)
{
    while (1) {
        dma_rom_to_sdram();
        dma_rom_to_ram0();
        dma_sdram_to_sdram();
        dma_ram0_to_ram0();
        dma_ram0_to_sdram();
        dma_sdram_to_ram0();
        dma_sdram_to_ram0_nocache();
        dma_sdram_nocache_to_sdram_nocache();
        dma_sdram_nocache_to_sdram();
        dma_sdram_to_sdram_nocache();
        dma_ram0_to_sdram_nocache();
        large_dma_sdram_to_sdram_nocache();
        large_dma_sdram_to_sdram();
        dma_ram0_memset();
        dma_sdram_memset();
        dma_sdram_nocache_memset();
        dma_flash_to_sdram_nocache();
        dma_flash_to_sdram();
    }
}

static int dma_copy_test_init(void)
{
    return thread_fork("dma_copy_test", 1, 512, 0, 0, dma_copy_test_task, NULL);
}
late_initcall(dma_copy_test_init);

#endif


#ifdef CONFIG_FPGA_TIMER_PWM_TEST_ENABLE
static void timer_pwm_test(void)
{
    int ret;
    u32 duty;
    void *pwm_dev_handl = NULL;

    printf("timer pwm test start");

    /*1.open ，open之后的PWM通道最多支持同一个通道的H和L设置，不能进行多通道的设置*/
    pwm_dev_handl = dev_open("pwm1", NULL);
    if (!pwm_dev_handl) {
        return;
    }
    os_time_dly(100);

    /*open PWM设备之后就会初始化PWM，PWM相关参数为board.c配置，在不需要更改参数时，只需要open就行，不需要进行以下操作*/

    /*2.write and read 配置占空比*/
    pwm_config_t pwm = {0};
    pwm.pwm_ch = PWM_TIMER2_OPCH;
    pwm.duty = 0;
    pwm.point_bit = 0;
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_DUTY, (u32)&pwm);
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_GET_DUTY, (u32)&pwm);//占空比（不带小数点）0-100
    printf("pwm read duty : %f", pwm.duty);
    os_time_dly(10);

    pwm.duty = 100;
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_DUTY, (u32)&pwm);
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_GET_DUTY, (u32)&pwm);//占空比（不带小数点）0-100
    printf("pwm read duty : %f", pwm.duty);
    os_time_dly(10);

    pwm.duty = 50;
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_DUTY, (u32)&pwm);
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_GET_DUTY, (u32)&pwm);//占空比（不带小数点）0-100
    printf("pwm read duty : %f", pwm.duty);
    os_time_dly(10);

    /*3.ioctl控制PWM暂停、运行、正反向,调用1次ioctl只支持1组通道PWMCH_H/L控制*/
    printf("----pwm ioctl-------");
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_STOP, (u32)&pwm);//PWM停止
    os_time_dly(10);
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_RUN, (u32)&pwm);//PWM运行
    os_time_dly(10);
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_REVDIRC, (u32)&pwm);//PWM正向
    os_time_dly(10);
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_FORDIRC, (u32)&pwm);//PWM反向
    os_time_dly(10);

    printf("----pwm set freq-------");
    /*4.ioctl配置频率和占空比*/
    pwm.freq = 5000;
    pwm.duty = 50;
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_FREQ, (u32)&pwm);//设置频率
    os_time_dly(100);

    pwm.duty = 0;
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_DUTY, (u32)&pwm);//设置占空比
    printf("pwm set duty : %f", pwm.duty);
    os_time_dly(100);

    pwm.duty = 80;
    dev_ioctl(pwm_dev_handl, IOCTL_PWM_SET_DUTY, (u32)&pwm);//设置占空比
    printf("pwm set duty : %f", pwm.duty);
    os_time_dly(100);

    dev_close(pwm_dev_handl);

    printf("timer pwm test end");
}

static void timer_pwm_test_task(void *p)
{
    while (1) {
        timer_pwm_test();
    }
}

static int timer_pwm_test_init(void)
{
    return thread_fork("timer_pwm_test", 2, 512, 0, 0, timer_pwm_test_task, NULL);
}
late_initcall(timer_pwm_test_init);
#endif


#ifdef CONFIG_FPGA_EMU_TEST_ENABLE
void tzemu_test(void)
{
    volatile u32 ptr = 0;

#if 1
    //某个地址框内，只允许某个外设的写权限（允许CPU读权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cr0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，只允许某个外设的写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，只允许某个外设的读权限（允许CPU写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cr0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，只允许某个外设的读权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，禁止某个外设的写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPrw0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止某个外设的写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Prw0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止某个外设的读权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPrw0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止某个外设的读权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Prw0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的读权限，禁止所有外设的写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPr", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的读权限，禁止所有外设的写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Pr", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的写权限，禁止所有外设的读权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPw", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的写权限，禁止所有外设的读权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Pw", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的读写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Prw", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止所有外设的读写权限（只允许CPU写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cw");
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0);// | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
    /* ptr = *(volatile u32 *)0x110000; */
    *(volatile u32 *)0x110000 = 0x12345678;
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，禁止所有外设的读写权限（只允许CPU写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cr");
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0);// | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，禁止所有外设的读写权限（只允许CPU读写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Crw");
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0);// | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    /* void (*fun)(void) = 0x110000; */
    /* fun(); */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框外，只允许某个外设的写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "Cxrw0w", get_debug_dev_id("DBG_SPI2"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0) | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    //某个地址框外，只允许某个外设的读权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "Cxrw0r", get_debug_dev_id("DBG_SPI2"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0) | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    //某个地址框外，只允许某个外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "Cxrw0rw", get_debug_dev_id("DBG_SPI2"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0) | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    //某个地址框外，禁止某个外设的写权限，允许其他外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "CxrwPrw0w", get_debug_dev_id("DBG_SPI1"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
#endif

#if 1
    //某个地址框外，禁止某个外设的读权限，允许其他外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "CxrwPrw0r", get_debug_dev_id("DBG_SPI1"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
#endif

#if 1
    //某个地址框外，禁止某个外设的读写权限，允许其他外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "CxrwPrw0rw", get_debug_dev_id("DBG_SPI1"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x111000;
    JL_SPI1->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);
    JL_SPI1->ADR = 0x111000;
    JL_SPI1->CNT = 512;
#endif

#if 0
    //某个地址框内，只允许CPU0的读写权限，不允许CPU1的所有权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0w1r", get_debug_dev_id("DBG_CPU0_WR"), get_debug_dev_id("DBG_CPU0_RD"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
#endif

#if 1
    //某个地址框内，只允许CPU0的读写权限，不允许CPU1的所有权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0w1r", get_debug_dev_id("DBG_CPU1_WR"), get_debug_dev_id("DBG_CPU1_RD"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
#endif

#if 1
    //某个地址框内，只允许CPU0的读和执行权限，只允许CPU1的写权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0r1r2w", get_debug_dev_id("DBG_CPU0_RD"), get_debug_dev_id("DBG_CPU0_IF"), get_debug_dev_id("DBG_CPU1_WR"));
    /* ptr = *(volatile u32 *)0x110000; */
    *(volatile u32 *)0x110000 = 0;
    /* void (*fun)(void) = 0x110000; */
    /* fun(); */
#endif

#if 1
    //某个地址框内，只允许CPU1的读和执行权限，只允许CPU0的写权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0r1r2w", get_debug_dev_id("DBG_CPU1_RD"), get_debug_dev_id("DBG_CPU1_IF"), get_debug_dev_id("DBG_CPU0_WR"));
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0; */
    /* void (*fun)(void) = 0x110000; */
    /* fun(); */
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0); */
    /* JL_SPI1->ADR = 0x111000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "h0r1r2w", get_debug_dev_id("DBG_CPU1_RD"), get_debug_dev_id("DBG_CPU1_IF"), get_debug_dev_id("DBG_CPU0_WR"));
#endif

    mpu_disable_by_index(3);

#if 1
    //某个sdram地址框内，只允许dcache读访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "0r", AXI_MASTER_DCACHE);
    DcuFlushinvAll();
    ptr = *(volatile u32 *)0x18700000;
    /* dma_memset_sync(NO_CACHE_ADDR(0x18700000), 0x12, 4096); */
    /* *(volatile u32 *)0x18700000 = 0x12345678; */
    /* DcuFlushAll(); */
#endif

#if 1
    //某个sdram地址框内，只允许dcache写访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "0w", AXI_MASTER_DCACHE);
    /* DcuFlushinvAll(); */
    /* ptr = *(volatile u32 *)0x18700000; */
    *(volatile u32 *)0x18700000 = 0x12345678;
    DcuFlushAll();
    /* dma_memset_sync(NO_CACHE_ADDR(0x18700000), 0x12, 4096); */
#endif

#if 1
    //某个sdram地址框内，只允许icache读访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR((u32)&sdram_text_code_begin), NO_CACHE_ADDR((u32)&sdram_text_code_end - 1), "0r", AXI_MASTER_ICACHE);
    IcuFlushinvAll();
    /* dma_memset_sync(NO_CACHE_ADDR((u32)&sdram_text_code_begin), 0x12, 4096); */
#endif

#if 1
    //某个sdram地址框内，只允许icache读访问和dcache读写访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR((u32)&sdram_text_code_begin), NO_CACHE_ADDR((u32)&sdram_text_code_end - 1), "0r1rw", AXI_MASTER_ICACHE, AXI_MASTER_DCACHE);
    *(volatile u32 *)((u32)&sdram_text_code_end - 4) = 0;
    DcuFlushAll();
    /* dma_memset_sync(NO_CACHE_ADDR((u32)&sdram_text_code_begin), 0x12, 4096); */
#endif

#if 1
    //某个sdram地址框内，只允许dma_copy读和写访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "0wr", AXI_MASTER_DMA_COPY);
    dma_copy_sync(NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18710000), 4096);
    /* DcuFlushinvAll(); */
    /* ptr = *(volatile u32 *)0x18700000; */
    /* *(volatile u32 *)0x18700000 = 0x12345678; */
    /* DcuFlushAll(); */
#endif

#if 1
    //某个sdram地址框内，不允许icache读访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "Prw0r", AXI_MASTER_ICACHE);
    IcuFlushinvAll();
    *(volatile u32 *)0x18700000 = 0x12345678;
    DcuFlushAll();
    dma_memset_sync(0x18700000, 0x12, 4096);
    dma_memset_sync(NO_CACHE_ADDR(0x18700000), 0x12, 4096);
    IcuFlushinvAll();
    /* void (*fun)(void) = 0x18700000; */
    /* fun(); */
#endif

#if 1
    DcuFlushinvAll();
    //某个sdram地址框内，不允许dcache读和写访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "Prw0wr", AXI_MASTER_DCACHE);
    IcuFlushinvAll();
    /* *(volatile u32 *)0x18700000 = 0x12345678; */
    DcuFlushAll();
#endif

#if 1
    DcuFlushinvAll();
    //某个sdram地址框内，不允许dcache读和写访问，不允许icache访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "Prw0wr1r", AXI_MASTER_DCACHE, AXI_MASTER_ICACHE);
    IcuFlushinvAll();
    /* *(volatile u32 *)0x18700000 = 0x12345678; */
    DcuFlushAll();
    /* void (*fun)(void) = 0x18700000; */
    /* fun(); */
#endif

#if 1
    //某个sdram地址框内，不允许dma_copy读和写访问
    tzasc_enable_by_index(3, NO_CACHE_ADDR(0x18700000), NO_CACHE_ADDR(0x18800000) - 1, "Prw0wr", AXI_MASTER_DMA_COPY);
    /* dma_memset_sync(NO_CACHE_ADDR(0x18700000), 0x12, 4096); */
    dma_memset_sync(0x18700000, 0x12, 4096);
#endif

#if 1
    //某个flash地址框内，只允许dcache读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "0r", AXI_MASTER_DCACHE);
    DcuFlushinvAll();
    ptr = *(volatile u32 *)0x8400000;
    /* dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096); */
    /* void (*fun)(void) = 0x8400000; */
    /* fun(); */
#endif

#if 1
    //某个flash地址框内，只允许icache读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "0r", AXI_MASTER_ICACHE);
    DcuFlushinvAll();
    /* ptr = *(volatile u32 *)0x8400000; */
    /* dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096); */
    /* void (*fun)(void) = 0x8400000; */
    /* fun(); */
#endif

#if 1
    //某个flash地址框内，只允许icache读访问和dcache读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "0r1r", AXI_MASTER_ICACHE, AXI_MASTER_DCACHE);
    DcuFlushinvAll();
    ptr = *(volatile u32 *)0x8400000;
    /* dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096); */
    /* void (*fun)(void) = 0x8400000; */
    /* fun(); */
#endif

#if 1
    //某个flash地址框内，只允许dma_copy读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "0r", AXI_MASTER_DMA_COPY);
    DcuFlushinvAll();
    /* ptr = *(volatile u32 *)0x8400000; */
    dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096);
#endif

#if 1
    //某个flash地址框内，不允许icache读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "Pr0r", AXI_MASTER_ICACHE);
    IcuFlushinvAll();
    DcuFlushinvAll();
    ptr = *(volatile u32 *)0x8400000;
    dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096);
    /* void (*fun)(void) = 0x18700000; */
    /* fun(); */
#endif

#if 1
    //某个flash地址框内，不允许dcache读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "Pr0r", AXI_MASTER_DCACHE);
    IcuFlushinvAll();
    DcuFlushinvAll();
    /* ptr = *(volatile u32 *)0x8400000; */
    dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096);
    /* void (*fun)(void) = 0x18700000; */
    /* fun(); */
#endif

#if 1
    //某个flash地址框内，不允许icache和dcache读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "Pr0r1r", AXI_MASTER_DCACHE, AXI_MASTER_ICACHE);
    IcuFlushinvAll();
    DcuFlushinvAll();
    /* ptr = *(volatile u32 *)0x8400000; */
    dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096);
    /* void (*fun)(void) = 0x18700000; */
    /* fun(); */
#endif

#if 1
    //某个flash地址框内，不允许dma_copy读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "Pr0r", AXI_MASTER_DMA_COPY);
    IcuFlushinvAll();
    DcuFlushinvAll();
    ptr = *(volatile u32 *)0x8400000;
    /* dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096); */
#endif

#if 1
    //某个flash地址框内，不允许dma_copy读访问
    tzasc_enable_by_index(3, 0x8400000, 0x8500000 - 1, "Pr0r", AXI_MASTER_DMA_COPY);
    IcuFlushinvAll();
    DcuFlushinvAll();
    ptr = *(volatile u32 *)0x8400000;
    /* dma_copy_sync(NO_CACHE_ADDR(0x18700000), 0x8400000, 4096); */
#endif

#if 0
    tzasc_enable_by_index(3, 0x8300000, 0x8500000 - 1, "lPr0r", AXI_MASTER_DMA_COPY);
#endif


#if defined CONFIG_TRUSTZONE_ENABLE
    trustzone_exit();

#if 1
    //某个地址框内，只允许某个外设的写权限（允许CPU读权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cr0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，只允许某个外设的写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，只允许某个外设的读权限（允许CPU写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cr0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，只允许某个外设的读权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，禁止某个外设的写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPrw0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止某个外设的写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Prw0w", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止某个外设的读权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPrw0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止某个外设的读权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Prw0r", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的读权限，禁止所有外设的写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPr", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的读权限，禁止所有外设的写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Pr", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的写权限，禁止所有外设的读权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "CxrwPw", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的写权限，禁止所有外设的读权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Pw", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，允许所有外设的读写权限（禁止CPU所有权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Prw", get_debug_dev_id("DBG_SPI1"));
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
    /* ptr = *(volatile u32 *)0x110000; */
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
#endif

#if 1
    //某个地址框内，禁止所有外设的读写权限（只允许CPU写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cw");
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0);// | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
    /* ptr = *(volatile u32 *)0x110000; */
    *(volatile u32 *)0x110000 = 0x12345678;
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，禁止所有外设的读写权限（只允许CPU写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Cr");
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0);// | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0x12345678; */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框内，禁止所有外设的读写权限（只允许CPU读写权限）
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "Crw");
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0);// | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    /* void (*fun)(void) = 0x110000; */
    /* fun(); */
    /* JL_SPI2->CON = 0; */
    /* JL_SPI2->CON = BIT(0);// | BIT(12); */
    /* JL_SPI2->ADR = 0x110000; */
    /* JL_SPI2->CNT = 512; */
#endif

#if 1
    //某个地址框外，只允许某个外设的写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "Cxrw0w", get_debug_dev_id("DBG_SPI2"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0) | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    //某个地址框外，只允许某个外设的读权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "Cxrw0r", get_debug_dev_id("DBG_SPI2"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0) | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    //某个地址框外，只允许某个外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "Cxrw0rw", get_debug_dev_id("DBG_SPI2"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0) | BIT(12); */
    /* JL_SPI1->ADR = 0x110000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    //某个地址框外，禁止某个外设的写权限，允许其他外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "CxrwPrw0w", get_debug_dev_id("DBG_SPI1"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);// | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
#endif

#if 1
    //某个地址框外，禁止某个外设的读权限，允许其他外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "CxrwPrw0r", get_debug_dev_id("DBG_SPI1"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x110000;
    JL_SPI1->CNT = 512;
#endif

#if 1
    //某个地址框外，禁止某个外设的读写权限，允许其他外设的读写权限（允许CPU所有权限）
    mpu_enable_by_index(3, 0x111000, 0x112000 - 1, 1, "CxrwPrw0rw", get_debug_dev_id("DBG_SPI1"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
    JL_SPI2->CON = 0;
    JL_SPI2->CON = BIT(0);// | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI2->CON = BIT(0) | BIT(12);
    JL_SPI2->ADR = 0x110000;
    JL_SPI2->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0) | BIT(12);
    JL_SPI1->ADR = 0x111000;
    JL_SPI1->CNT = 512;
    JL_SPI1->CON = 0;
    JL_SPI1->CON = BIT(0);
    JL_SPI1->ADR = 0x111000;
    JL_SPI1->CNT = 512;
#endif

#if 0
    //某个地址框内，只允许CPU0的读写权限，不允许CPU1的所有权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0w1r", get_debug_dev_id("DBG_CPU0_WR"), get_debug_dev_id("DBG_CPU0_RD"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
#endif

#if 1
    //某个地址框内，只允许CPU0的读写权限，不允许CPU1的所有权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0w1r", get_debug_dev_id("DBG_CPU1_WR"), get_debug_dev_id("DBG_CPU1_RD"));
    ptr = *(volatile u32 *)0x110000;
    *(volatile u32 *)0x110000 = 0x12345678;
#endif

#if 1
    //某个地址框内，只允许CPU0的读和执行权限，只允许CPU1的写权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0r1r2w", get_debug_dev_id("DBG_CPU0_RD"), get_debug_dev_id("DBG_CPU0_IF"), get_debug_dev_id("DBG_CPU1_WR"));
    /* ptr = *(volatile u32 *)0x110000; */
    *(volatile u32 *)0x110000 = 0;
    /* void (*fun)(void) = 0x110000; */
    /* fun(); */
#endif

#if 1
    //某个地址框内，只允许CPU1的读和执行权限，只允许CPU0的写权限
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "0r1r2w", get_debug_dev_id("DBG_CPU1_RD"), get_debug_dev_id("DBG_CPU1_IF"), get_debug_dev_id("DBG_CPU0_WR"));
    ptr = *(volatile u32 *)0x110000;
    /* *(volatile u32 *)0x110000 = 0; */
    /* void (*fun)(void) = 0x110000; */
    /* fun(); */
    /* JL_SPI1->CON = 0; */
    /* JL_SPI1->CON = BIT(0); */
    /* JL_SPI1->ADR = 0x111000; */
    /* JL_SPI1->CNT = 512; */
#endif

#if 1
    mpu_enable_by_index(3, 0x110000, 0x112000 - 1, 0, "h0r1r2w", get_debug_dev_id("DBG_CPU1_RD"), get_debug_dev_id("DBG_CPU1_IF"), get_debug_dev_id("DBG_CPU0_WR"));
#endif

#endif

    /* JL_TZMPU->BEG[0] = 0; */
    /* JL_TZMPU->END[0] = 0x1000000; */
    /* JL_TZMPU->CON[0] = BIT(29) | BIT(5) | BIT(3) | BIT(4); */

    /* JL_TZMPU->BEG[0] = 0; */
    /* JL_TZMPU->END[0] = 0; */
    /* JL_TZMPU->CON[0] = BIT(29) | BIT(5) | BIT(3) | BIT(4) | BIT(0); */

    /* JL_TZMPU->BEG[0] = 0; */
    /* JL_TZMPU->END[0] = 0; */
    /* JL_TZMPU->CON[0] = BIT(29) | BIT(5) | BIT(3) | BIT(4) | BIT(0) | BIT(2); */

    /* JL_TZMPU->BEG[0] = 0; */
    /* JL_TZMPU->END[0] = 0; */
    /* JL_TZMPU->CON[0] = BIT(29) | BIT(5) | BIT(3) | BIT(4) | BIT(0) | BIT(2) | BIT(1); */

    /* JL_TZMPU->BEG[0] = 0; */
    /* JL_TZMPU->END[0] = 0; */
    /* JL_TZMPU->CID[0] = 0x10; */
    /* JL_TZMPU->CON[0] = BIT(29) | BIT(9) | BIT(5) |  BIT(0) | BIT(2) | BIT(1); */

    /* JL_TZMPU->BEG[0] = 0x100000; */
    /* JL_TZMPU->END[0] = 0x140000; */
    /* JL_TZMPU->CID[0] = 0x10; */
    /* JL_TZMPU->CON[0] = BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0) | BIT(9) | BIT(5); */

    /* volatile u32 aa = *(volatile u32 *)0x140000; */
    /* *(volatile u32 *)0x140000 = 0x12345678;	//dslv_inv */

    /* JL_MMU->TLB1_BEG = 0x140000; */
    /* JL_MMU->TLB1_END = 0x150000; */
    /* JL_MMU->CON |= BIT(0); */
    /* volatile u32 aa = *(volatile u32 *)0x100000; */
    /* *(volatile u32 *)0x100000 = 0x12345678;	//dslv_inv */

    /* volatile u32 aa = *(volatile u32 *)0x4000; */
    /* volatile u32 aa = *(volatile u32 *)0x2f0000; */
    /* volatile u32 aa = *(volatile u32 *)0x300000; */
    /* volatile u32 aa = *(volatile u32 *)0x340000; */
    /* volatile u32 aa = *(volatile u32 *)0x3e0000; */
    /* volatile u32 aa = *(volatile u32 *)0x1000000; */
    /* volatile u32 aa = *(volatile u32 *)0x378000; */
    /* volatile u32 aa = *(volatile u32 *)0x37e000; */
    /* volatile u32 aa = *(volatile u32 *)0x37f400; */
    /* volatile u32 aa = *(volatile u32 *)0x3c8000; */
    /* volatile u32 aa = *(volatile u32 *)0x3ce000; */
    /* volatile u32 aa = *(volatile u32 *)0x3cf400; */
    /* volatile u32 aa = *(volatile u32 *)0x2000000; */
    /* volatile u32 aa = *(volatile u32 *)0x4000000; */
    /* volatile u32 aa = *(volatile u32 *)0x6000000; */
    /* volatile u32 aa = *(volatile u32 *)0x1d000000; */
    /* volatile u32 aa = *(volatile u32 *)(0x1c000000 - 4); */
    /* printf("aa : 0x%x", aa); */

    /* volatile u32 aa = *(volatile u32 *)0xf12000; */
    /* *(volatile u32 *)0xf12000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0xf22000; */
    /* *(volatile u32 *)0xf22000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0xfd4000; */
    /* *(volatile u32 *)0xfd4000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0xfe2000; */
    /* *(volatile u32 *)0xfe2000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0xf40000; */
    /* *(volatile u32 *)0xf40000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0xfff000; */
    /* *(volatile u32 *)0xfff000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0x2f0000; */
    /* *(volatile u32 *)0x2f0000 = 0x12345678; */

    /* volatile u32 aa = *(volatile u32 *)0x300000; */
    /* volatile u32 aa = *(volatile u32 *)0x330000; */
    /* volatile u32 aa = *(volatile u32 *)0x340000; */
    /* volatile u32 aa = *(volatile u32 *)0x360000; */
    /* volatile u32 aa = *(volatile u32 *)0x378000; */
    /* volatile u32 aa = *(volatile u32 *)0x37e000; */
    /* volatile u32 aa = *(volatile u32 *)0x37f400; */
    /* volatile u32 aa = *(volatile u32 *)0x380000; */
    /* volatile u32 aa = *(volatile u32 *)0x390000; */
    /* volatile u32 aa = *(volatile u32 *)0x3a0000; */
    /* volatile u32 aa = *(volatile u32 *)(0x3c0000 - 4); */
    /* volatile u32 aa = *(volatile u32 *)0x3c8000; */
    /* volatile u32 aa = *(volatile u32 *)0x3ce000; */
    /* volatile u32 aa = *(volatile u32 *)0x3cf400; */
    /* volatile u32 aa = *(volatile u32 *)0x3e0000; */
    /* volatile u32 aa = *(volatile u32 *)0x3f0000; */
    /* volatile u32 aa = *(volatile u32 *)(0x400000 - 4); */
    /* *(volatile u32 *)0x3e0000 = 0x12345678; */
}
#endif


#ifdef CONFIG_FPGA_ICACHE_TEST_ENABLE
void icache_test(void)
{
    int cnt = 0;
    int cpu_id = current_cpu_id();

#ifdef CONFIG_FPGA_ICACHE_TEST_ENABLE
    IcuLockRegion(&rom_text_code_begin, 32);
    IcuUnlockRegion(&rom_text_code_begin, 32);
    IcuLockRegion(&rom_text_code_begin, 32);
    IcuUnlockAll();
    IcuLockRegion(&rom_text_code_begin, 4096);
    IcuFlushinvRegion(&rom_text_code_begin, 4096);
    IcuPfetchRegion(&rom_text_code_begin, 4 * 1024);
    IcuFlushinvAll();
    return;
#endif

#if 0	//非安全环境下测试
    IcuLockRegion(&rom_text_code_begin, 32);
    IcuUnlockRegion(&rom_text_code_begin, 32);
    IcuLockRegion(&rom_text_code_begin, 4096);
    IcuUnlockAll();
    IcuLockRegion(&rom_text_code_begin, 4096);
    IcuFlushinvRegion(&rom_text_code_begin, 4096);
    IcuPfetchRegion(&rom_text_code_begin, 32 * 1024);
    IcuFlushinvAll();
    IcuSetWayNum(0);
    /* q32DSP_icu(cpu_id)->EMU_CON = 0; */
    return;
#endif

    /* IcuLockRegion(&rom_text_code_begin, 32 * 1024); //icmd_lock_err */
    /* IcuLockRegion(&rom_text_code_begin, 4096 + 32);  */
    /* IcuLockRegion(&rom_text_code_begin, 4);  */
    IcuLockRegion(&rom_text_code_begin, 32);

    u64 *itag_ptr = cpu_id ? (u64 *)0x3dc000 : (u64 *)0x3cc000;
    /* *itag_ptr = 0; //islv_inv */
    /* *(volatile u32 *)0x3db000 = 0; //islv_inv  */

    /* JL_SPI1->CON |= BIT(0); */
    /* JL_SPI1->ADR = 0x3c0000; */
    /* JL_SPI1->CNT = 512; */

    for (int i = 0; i < 1024; ++i) {
        if (*itag_ptr & BIT(19)) {
            put_buf(itag_ptr, sizeof(u64));
            cnt++;
        }
        ++itag_ptr;
    }
    printf("itag lock cnt : %d", cnt);

    IcuUnlockRegion(&rom_text_code_begin, 32);

    itag_ptr = cpu_id ? (u64 *)0x3dc000 : (u64 *)0x3cc000;

    for (int i = 0; i < 1024; ++i) {
        if (*itag_ptr & BIT(19)) {
            ASSERT(0);
        }
        ++itag_ptr;
    }

    IcuLockRegion(&rom_text_code_begin, 4096);

    itag_ptr = cpu_id ? (u64 *)0x3dc000 : (u64 *)0x3cc000;
    cnt = 0;

    for (int i = 0; i < 1024; ++i) {
        if (*itag_ptr & BIT(19)) {
            /* put_buf(itag_ptr, sizeof(u64)); */
            cnt++;
        }
        ++itag_ptr;
    }
    printf("itag lock cnt : %d", cnt);

    IcuUnlockAll();

    itag_ptr = cpu_id ? (u64 *)0x3dc000 : (u64 *)0x3cc000;

    for (int i = 0; i < 1024; ++i) {
        if (*itag_ptr & BIT(19)) {
            ASSERT(0);
        }
        ++itag_ptr;
    }

    IcuLockRegion(&rom_text_code_begin, 4096);
    IcuFlushinvRegion(&rom_text_code_begin, 4096);
    /* IcuFlushinvAll(); */

    itag_ptr = cpu_id ? (u64 *)0x3dc000 : (u64 *)0x3cc000;

    for (int i = 0; i < 1024; ++i) {
        if ((*itag_ptr & BIT(18)) && (*itag_ptr & BIT(19)))  {
            ASSERT(0);
        }
        ++itag_ptr;
    }

    IcuSetWayNum(7);

    if (cpu_id) {
        for (int i = 0; i < 4096; ++i) {
            *(volatile u8 *)(0x3d7000 + i) = i;
            if (*(volatile u8 *)(0x3d7000 + i) != (u8)i) {
                ASSERT(0);
            }
        }
        printf("--------0x%x---------", *(volatile u32 *)0x3d7000);
    } else {
        for (int i = 0; i < 4096; ++i) {
            *(volatile u8 *)(0x3c7000 + i) = i;
            if (*(volatile u8 *)(0x3c7000 + i) != (u8)i) {
                ASSERT(0);
            }
        }
        printf("--------0x%x---------", *(volatile u32 *)0x3c7000);
    }

    IcuSetWayNum(8);

    IcuFlushinvAll();
    IcuPfetchRegion(&rom_text_code_begin, 32 * 1024); //iway_rhit_err

    itag_ptr = cpu_id ? (u64 *)0x3dc000 : (u64 *)0x3cc000;
    cnt = 0;

    for (int i = 0; i < 1024; ++i) {
        if (*itag_ptr & BIT(18)) {
            /* put_buf(itag_ptr, sizeof(u64)); */
            cnt++;
        }
        ++itag_ptr;
    }
    printf("itag fetch cnt : %d", cnt);

    /* put_buf(0x3cc000, 4096 * 2); */
    /* put_buf(0x3dc000, 4096 * 2); */
}
#endif

#ifdef CONFIG_FPGA_DCACHE_TEST_ENABLE
void dcache_test(void)
{
#ifdef CONFIG_FPGA_DCACHE_TEST_ENABLE
    DcuPfetchRegion((u32 *)0x19F00000, 32 * 1024);
    DcuFlushRegion((u32 *)0x19F00000, 32 * 1024);
    DcuFlushinvRegion((u32 *)0x19F00000, 32 * 1024);
    DcuPfetchRegion((u32 *)0x19F00000, 32 * 1024);
    DcuFlushinvAll();
    DcuPfetchRegion((u32 *)0x19F00000, 32 * 1024);
    DcuInvalidRegion((u32 *)0x19F00000, 32 * 1024);
    DcuPfetchRegion((u32 *)0x19F00000, 32 * 1024);
    DcuFlushAll();
    DcuPfetchRegion((u32 *)0x8100120, 32 * 1024);
    DcuFlushinvRegion((u32 *)0x8100120, 32 * 1024);
    DcuPfetchRegion((u32 *)0x8100120, 32 * 1024);
    DcuFlushinvAll();
    DcuPfetchRegion((u32 *)0x8100120, 32 * 1024);
    DcuInvalidRegion((u32 *)0x8100120, 32 * 1024);
    return;
#endif

    u64 *dtag_ptr = (u64 *)0x37c000;
    /* *(volatile u32 *)0x370000 = 0x1234;	//dslv_inv */
    /* *(volatile u32 *)0x378000 = 0x1234;	//dslv_inv */
    /* *(volatile u32 *)0x3a0000 = 0x1234;	//dslv_inv */
    /* *(volatile u32 *)0x380000 = 0x1234;	//dslv_inv */
    /* *(volatile u32 *)0x180000 = 0x1234;	//dslv_inv */
    /* printf("=========0x%x=========\n", *(volatile u32 *)0x180000); */

    /* JL_SPI1->CON |= BIT(0); */
    /* JL_SPI1->ADR = 0x3c0000; */
    /* JL_SPI1->CNT = 512; */

#ifdef CONFIG_NO_SDRAM_ENABLE
    *(volatile u32 *)0x37c400 = 0x12345678;	//dslv_inv
    printf("aa:0x%x", *(volatile u32 *)0x37c400);
    *(volatile u32 *)0x37dc00 = 0x12345678;	//dslv_inv
    printf("bb:0x%x", *(volatile u32 *)0x37dc00);

    DcuInvalidAll();
#else
    printf("-----------test dcache------------");
    put_buf(dtag_ptr, 8 * 1024);
    DcuPfetchRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuFlushRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuFlushinvRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuPfetchRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuFlushinvAll();
    put_buf(dtag_ptr, 8 * 1024);
    DcuPfetchRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuInvalidRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuPfetchRegion((u32 *)0x18700000, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuFlushAll();
    put_buf(dtag_ptr, 8 * 1024);
#endif

    printf("-----------test rocache------------");
    DcuPfetchRegion((u32 *)0x8100120, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuFlushinvRegion((u32 *)0x8100120, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuPfetchRegion((u32 *)0x8100120, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuFlushinvAll();
    put_buf(dtag_ptr, 8 * 1024);
    DcuPfetchRegion((u32 *)0x8100120, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    DcuInvalidRegion((u32 *)0x8100120, 32 * 1024);
    put_buf(dtag_ptr, 8 * 1024);
    return;

    DcuSetWayNum(1);

    for (int i = 0; i < 4096; ++i) {
        *(volatile u8 *)(0x372000 + i) = i;
        if (*(volatile u8 *)(0x372000 + i) != (u8)i) {
            ASSERT(0);
        }
    }
    printf("--------0x%x---------", *(volatile u32 *)0x372000);

    DcuSetWayNum(7);
}
#endif

void axi_mmu_test(void)
{
#if 1
    u32 page_size = 4096;

    JL_SFC0_MMU->TLB1_BEG = 0x372000;
    JL_SFC0_MMU->TLB1_END = 0x377000 - 1;

    memset((void *)JL_SFC0_MMU->TLB1_BEG, 0, JL_SFC0_MMU->TLB1_END - JL_SFC0_MMU->TLB1_BEG + 1);

    u32 va_adr = 0xc200000;
    u32 va_beg = 0xc000000;
    u32 vpn = (va_adr - va_beg) / page_size;

    u32 pa_adr = 0x8020000;
    u32 pa_beg = 0x8000000;
    u32 ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC0_MMU_TLB1[vpn].page = ppn;
    JL_SFC0_MMU_TLB1[vpn].vld = 1;

    JL_SFC0_MMU->CON0 = BIT(0);		//异常1

    __asm_csync();

    va_adr += page_size;
    vpn = (va_adr - va_beg) / page_size;

    pa_adr = 0x8010000;
    ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC0_MMU_TLB1[vpn].page = ppn;
    JL_SFC0_MMU_TLB1[vpn].vld = 1;

    __asm_csync();

    put_buf((void *)(va_adr - page_size), 4096);
    put_buf((void *)va_adr, 4096);

    va_adr += page_size * 10;
    vpn = (va_adr - va_beg) / page_size;

    pa_adr = 0x8000000 + 16 * 1024 * 1024;
    ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC0_MMU_TLB1[vpn].page = ppn;
    JL_SFC0_MMU_TLB1[vpn].vld = 1;	//异常3

    __asm_csync();

    put_buf((void *)va_adr, 4096);
    return;

    JL_SFC0_MMU_TLB1[vpn].vld = 0;	//异常3
    JL_SFC0_MMU->CON1 = BIT(0);
    __asm_csync();

    put_buf((void *)va_adr, 4096);
    /* put_buf((void *)0xF000000, 4096); //异常3 */

    va_adr = 0x2800000 + va_beg;
    vpn = (va_adr - va_beg) / page_size;

    pa_adr = 0x8000000 + 40 * 1024 * 1024;
    ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC0_MMU_TLB1[vpn].page = ppn;
    JL_SFC0_MMU_TLB1[vpn].vld = 1;	//异常3

    __asm_csync();

    put_buf((void *)va_adr, 4096);	//异常2
#else
    u32 page_size = 4096;

    JL_SFC1_MMU->TLB1_BEG = 0x372000;
    JL_SFC1_MMU->TLB1_END = 0x377000 - 1;

    memset((void *)JL_SFC1_MMU->TLB1_BEG, 0, JL_SFC1_MMU->TLB1_END - JL_SFC1_MMU->TLB1_BEG + 1);

    u32 va_adr = 0x14006000;
    u32 va_beg = 0x14000000;
    u32 vpn = (va_adr - va_beg) / page_size;

    u32 pa_adr = __SFC1_ADDR_BEGIN__ + 0x6000;
    u32 pa_beg = __SFC1_ADDR_BEGIN__;
    u32 ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC1_MMU_TLB1[vpn].page = ppn;
    JL_SFC1_MMU_TLB1[vpn].vld = 1;

    JL_SFC1_MMU->CON0 = BIT(0);		//异常1

    __asm_csync();

    va_adr += page_size;
    vpn = (va_adr - va_beg) / page_size;

    pa_adr = __SFC1_ADDR_BEGIN__ + 0xC000;
    ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC1_MMU_TLB1[vpn].page = ppn;
    JL_SFC1_MMU_TLB1[vpn].vld = 1;

    __asm_csync();

    put_buf((void *)(va_adr - page_size), 4096);
    put_buf((void *)va_adr, 4096);

    va_adr += page_size * 10;
    vpn = (va_adr - va_beg) / page_size;

    pa_adr = __SFC1_ADDR_BEGIN__ + 16 * 1024 * 1024;
    ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC1_MMU_TLB1[vpn].page = ppn;
    JL_SFC1_MMU_TLB1[vpn].vld = 1;	//异常3

    __asm_csync();

    put_buf((void *)va_adr, 4096);
    return;

    JL_SFC1_MMU_TLB1[vpn].vld = 0;	//异常3
    JL_SFC1_MMU->CON1 = BIT(0);
    __asm_csync();

    put_buf((void *)va_adr, 4096);
    /* put_buf((void *)0xF000000, 4096); //异常3 */

    va_adr = 0x2800000 + va_beg;
    vpn = (va_adr - va_beg) / page_size;

    pa_adr = __SFC1_ADDR_BEGIN__ + 40 * 1024 * 1024;
    ppn = (pa_adr - pa_beg) / page_size;

    JL_SFC1_MMU_TLB1[vpn].page = ppn;
    JL_SFC1_MMU_TLB1[vpn].vld = 1;	//异常3

    __asm_csync();

    put_buf((void *)va_adr, 4096);	//异常2
#endif
}

void sram_mmu_test(void)
{
    u32 page_size = 128;

    JL_MMU->TLB1_BEG = 0x130000;
    JL_MMU->TLB1_END = 0x131000 - 1;

    memset((void *)JL_MMU->TLB1_BEG, 0, JL_MMU->TLB1_END - JL_MMU->TLB1_BEG + 1);

    u32 va_adr = 0x400000;
    u32 va_beg = 0x400000;
    u32 vpn = (va_adr - va_beg) / page_size;

    u32 pa_adr = 0x132000;
    u32 pa_beg = 0;
    u32 ppn = (pa_adr - pa_beg) / page_size;

    JL_MMU->CON = BIT(0);		//异常1

    JL_MMU->CON |= BIT(4 + current_cpu_id());
    JL_MMU_TLB1[vpn].page = ppn;
    JL_MMU_TLB1[vpn].vld = 1;
    JL_MMU->CON &= ~BIT(4 + current_cpu_id());

    __asm_csync();

    printf("JL_MMU->CON : 0x%x, JL_MMU->TLB1_BEG : 0x%x, JL_MMU->TLB1_END : 0x%x", JL_MMU->CON, JL_MMU->TLB1_BEG, JL_MMU->TLB1_END);
    put_buf(JL_MMU->TLB1_BEG, 2);
    put_buf(va_adr, 4);
    *(volatile u32 *)va_adr = 0x12345678;
    put_buf(va_adr, 4);
}

void etm_test(void)
{
    /* cpu_etm_range_value_limit_detect(0x130000, 0x13000f, 0, 4, CPU_RD_WR_BUS_DETECT_MODE, 1); */
    /* *(volatile u32 *)0x130000 = 0x12345678; */

    /* cpu_etm_range_value_limit_detect(0x130000, 0x13000f, 0, 4, CPU_RD_BUS_DETECT_MODE, 1); */
    /* *(volatile u32 *)0x130000 = 0x12345678; */
    /* volatile u32 aa = *(volatile u32 *)0x130000; */

    /* cpu_etm_range_value_limit_detect(0x130000, 0x13000f, 1, 2, CPU_WR_BUS_DETECT_MODE, 1); */
    /* volatile u32 aa = *(volatile u32 *)0x130000;  */
    /* *(volatile u32 *)0x130000 = 1; */

    JL_SPI1->BAUD = 0;
    cpu_etm_range_value_limit_detect(&JL_SPI1->BAUD, &JL_SPI1->BAUD, 0, 1, CPU_WR_BUS_DETECT_MODE, 0);
    JL_SPI1->BAUD = 1;
}


#ifdef CONFIG_FPGA_SRC_TEST_ENABLE
static const u32 src_sr_tab[] = {
    8000,
    11025,
    16000,
    22050,
    32000,
    44100,
    48000,
    64000,
    88200,
    96000,
};

#define RESAMPLE_PCM_FRAME_SIZE 256

extern const int config_resample_pcm_frame_buffer;

static void *cmp_data;
static FILE *g_c_fp;
static short src_rdata[RESAMPLE_PCM_FRAME_SIZE];
static u8 src_err_flag;

static int audio_src_output_handler(void *priv, void *data, int len)
{
    FILE *fp = (FILE *)priv;
    int ret;

    if (cmp_data && g_c_fp) {
        /* memset(cmp_data, 0, len); */
        ret = fread(cmp_data, 1, len, g_c_fp);
        if (ret != len) {
            ASSERT(0);
        }
        if (memcmp(cmp_data, data, len) != 0) {
            printf("wr offset : 0x%x, buf : 0x%x, len : %d", ftell(g_c_fp) - len, data, len);
            put_buf(data, len);
            put_buf(cmp_data, len);
            src_err_flag = 1;
            return len;
        }
    }

    ret = fwrite(data, 1, len, fp);

    ASSERT(ret == len);

    return len;
}

static int audio_src_once_test(int in_sr, int out_sr, u8 channel)
{
    void *src;
    char file_name[64];
    char long_file_name[128];
    short data[RESAMPLE_PCM_FRAME_SIZE];
    short rdata[RESAMPLE_PCM_FRAME_SIZE];
    int ret = 0, rlen = 0, total_len = 0;

    snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/compare/%d/%d-%d.pcm", channel, in_sr, out_sr);
    long_file_name_encode(file_name, long_file_name, sizeof(long_file_name));

    FILE *c_fp = fopen(long_file_name, "r");
    if (c_fp) {
        snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/out/%d/%d-%d.pcm", channel, in_sr, out_sr);
        long_file_name_encode(file_name, long_file_name, sizeof(long_file_name));
    } else {
        snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/compare/%d/%d-%d.pcm", channel, in_sr, out_sr);
        long_file_name_encode(file_name, long_file_name, sizeof(long_file_name));
    }

    FILE *w_fp = fopen(long_file_name, "w+");
    if (!w_fp) {
        return -1;
    }

    snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/in/%d/%d.pcm", channel, in_sr);

    FILE *r_fp = fopen(file_name, "r");
    if (!r_fp) {
        fclose(w_fp);
        return -1;
    }

    printf("src resample test %d -> %d, channel : %d", in_sr, out_sr, channel);

    if (c_fp) {
        cmp_data = malloc((int)((float)config_resample_pcm_frame_buffer * channel * 2 * ((float)out_sr / in_sr)) + 64);
        g_c_fp = c_fp;
    }

    src = audio_src_base_open(channel, in_sr, out_sr, AUDIO_ONLY_RESAMPLE);
    if (src) {
        audio_src_base_set_output_handler(src, w_fp, audio_src_output_handler);
        while (1) {
            if (ret == rlen) {
                memcpy(src_rdata, data, sizeof(data));
                rlen = fread(data, 1, sizeof(data), r_fp);
                if (rlen <= 0) {
                    printf("src resample read over %d", rlen);
                    break;
                }
            }
            ret = audio_src_base_write(src, data, rlen);
            if (src_err_flag) {
                printf("orig read offset : 0x%x", ftell(r_fp) - sizeof(data));
                put_buf(data, sizeof(data));
                put_buf(src_rdata, sizeof(src_rdata));
                ASSERT(0);
            }
        }
        audio_src_base_push_data_out(src);
        audio_src_base_stop(src);
        audio_src_base_close(src);
    }

    fclose(w_fp);
    fclose(r_fp);
    free(cmp_data);
    cmp_data = NULL;

    if (!src) {
        return -1;
    }

    if (!c_fp) {
        return 0;
    }

    r_fp = fopen(long_file_name, "r");
    if (!r_fp) {
        return -1;
    }

    snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/compare/%d/%d-%d.pcm", channel, in_sr, out_sr);
    long_file_name_encode(file_name, long_file_name, sizeof(long_file_name));

    fseek(c_fp, 0, SEEK_SET);

    printf("src resample compare %d -> %d", in_sr, out_sr);

    while (1) {
        ret = fread(rdata, 1, sizeof(rdata), c_fp);
        if (ret <= 0) {
            break;
        }
        rlen = fread(data, 1, sizeof(data), r_fp);
        if (rlen <= 0) {
            break;
        }
#if 0
        for (int i = 0; i < ret / 2; ++i) {
            if (data[i] > rdata[i] + 6 || data[i] < rdata[i] - 6) {
                printf("offset : 0x%x, i : %d, data : 0x%x, rdata : 0x%x", total_len, i, (u16)data[i], (u16)rdata[i]);
                put_buf(data, ret);
                put_buf(rdata, ret);
                ASSERT(0);
            }
        }
#else
        ASSERT(ret == rlen);

        if (memcmp(data, rdata, ret) != 0) {
            printf("offset : 0x%x", total_len);
            put_buf(data, ret);
            put_buf(rdata, ret);
            ASSERT(0);
        }
#endif
        total_len += ret;
    }

    if (total_len != flen(c_fp)) {
        ASSERT(0, "compare len not equal %d, %d", total_len, flen(c_fp));
    }

    fclose(c_fp);
    fclose(r_fp);

    return 0;
}

static void audio_src_test_task(void *p)
{
    while (1) {
        while (0 == storage_device_ready()) {
            os_time_dly(100);
        }

        for (int i = 0; i < ARRAY_SIZE(src_sr_tab); ++i) {
            for (int k = 0; k < ARRAY_SIZE(src_sr_tab); ++k) {
                if (src_sr_tab[i] == src_sr_tab[ARRAY_SIZE(src_sr_tab) - k - 1]) {
                    continue;
                }
                int ret = audio_src_once_test(src_sr_tab[i], src_sr_tab[ARRAY_SIZE(src_sr_tab) - k - 1], 1);
                ASSERT(ret == 0, "%s", __FUNCTION__);
            }
        }
        for (int i = 0; i < ARRAY_SIZE(src_sr_tab); ++i) {
            for (int k = 0; k < ARRAY_SIZE(src_sr_tab); ++k) {
                if (src_sr_tab[i] == src_sr_tab[ARRAY_SIZE(src_sr_tab) - k - 1]) {
                    continue;
                }
                int ret = audio_src_once_test(src_sr_tab[i], src_sr_tab[ARRAY_SIZE(src_sr_tab) - k - 1], 2);
                ASSERT(ret == 0, "%s", __FUNCTION__);
            }
        }
    }
}

static int audio_src_test_init(void)
{
    return thread_fork("src_test", 2, 768, 0, NULL, audio_src_test_task, NULL);
}
late_initcall(audio_src_test_init);
#endif


#ifdef COFNIG_FPGA_SRC_REUSE_TEST_ENBALE

#include "src_testdata.c"

#define RESAMPLE_PCM_FRAME_SIZE 200//256
extern const int config_resample_pcm_frame_buffer;

static int audio_src_out_hdl(void *priv, void *data, int len)
{
    FILE *fp = (FILE *)priv;
    int ret;
    ret = fwrite(data, len, 1, fp);
    ASSERT(ret == len);
    return len;
}
static int audio_src1_out_hdl(void *priv, void *data, int len)
{
    FILE *fp = (FILE *)priv;
    int ret;
    ret = fwrite(data, len, 1, fp);
    ASSERT(ret == len);
    return len;
}

static int audio_src_reuse_test(int in_sr, int out_sr, u8 channel)
{
#if 0
    FILE *in_fp;
    if (in_sr == 48000 && out_sr == 192000 && channel == 2) {
        in_fp = fopen(CONFIG_ROOT_PATH"sr4812.pcm", "r");
    } else if (in_sr == 48000 && out_sr == 192000 && channel == 4) {
        in_fp = fopen(CONFIG_ROOT_PATH"4ch16bit.pcm", "r");
    } else if (in_sr == 44100 && out_sr == 48000 && channel == 4) {
        in_fp = fopen(CONFIG_ROOT_PATH"4ch24bit.pcm", "r");
    } else if (in_sr == 44100 && out_sr == 192000 && channel == 2) {
        in_fp = fopen(CONFIG_ROOT_PATH"2ch24bit.pcm", "r");
    } else if (in_sr == 192000 && out_sr == 16000 && channel == 4) {
        in_fp = fopen(CONFIG_ROOT_PATH"192424b.pcm", "r");
    } else if (in_sr == 8000 && out_sr == 192000 && channel == 2) {
        in_fp = fopen(CONFIG_ROOT_PATH"8k12.pcm", "r");
    }

    if (!in_fp) {
        ASSERT(0);
    }
#endif

    char file_name[64];
    char long_file_name[128];
    snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/%dch-%d-%d.pcm", channel, in_sr, out_sr);
    long_file_name_encode(file_name, long_file_name, sizeof(long_file_name));

    FILE *out_fp = fopen(long_file_name, "w+");
    if (!out_fp) {
        ASSERT(0);
    }

    void *src;
    int data[RESAMPLE_PCM_FRAME_SIZE / 2];
    int ret = 0;
    /* int rlen = 0; */
    int offset = 0;
    int first_time = 1;
    int offset_total = 0;
    int *source_data;
    int frame_size = sizeof(data);

#if 1
    if (in_sr == 48000 && out_sr == 192000 && channel == 4) {
        offset_total = 2400;
        source_data = malloc(9600);
        memcpy(source_data, sr48k_4ch_16bit, 9600);
    } else if (in_sr == 48000 && out_sr == 192000 && channel == 2) {
        offset_total = 2400;
        source_data = malloc(9600);
        memcpy(source_data, sr48k_2ch_16bit, 9600);
    } else if (in_sr == 8000 && out_sr == 192000 && channel == 2) {
        offset_total = 8000;
        source_data = malloc(32000);
        memcpy(source_data, sr8k_2ch_16bit, 32000);
    } else if (in_sr == 44100 && out_sr == 192000 && channel == 2) {
        offset_total = 11025;
        source_data = malloc(44100);
        memcpy(source_data, sr44100_2ch_24bit, 44100);
    } else if (in_sr == 44100 && out_sr == 48000 && channel == 4) {
        offset_total = 11025;
        source_data = malloc(44100);
        memcpy(source_data, sr44100_4ch_24bit, 44100);
    } else if (in_sr == 192000 && out_sr == 16000 && channel == 4) {
        offset_total = 4800;
        source_data = malloc(19200);
        memcpy(source_data, sr192k_4ch_24bit, 19200);
    }
#endif

    src = audio_src_base_open(channel, in_sr, out_sr, AUDIO_ONLY_RESAMPLE);
    if (src) {
        audio_src_base_set_output_handler(src, out_fp, audio_src_out_hdl);
        while (1) {
            os_time_dly(1);
#if 0
            if (ret == rlen) {
                rlen = fread(data, 1, sizeof(data), in_fp);
                if (rlen <= 0) {
                    printf("src resample read over %d", rlen);
                    break;
                }
            }

            ret = audio_src_base_write(src, data, rlen);
#else

            if (ret == frame_size || first_time) {
                first_time = 0;
                if (offset < offset_total) {
                    if (in_sr == 44100 && out_sr == 192000 && channel == 2 && offset == 11000) {
                        frame_size = 100;
                    } else if (in_sr == 44100 && out_sr == 48000 && channel == 4 && offset == 11000) {
                        frame_size = 100;
                    }

                    memcpy(data, source_data + offset, frame_size);

                    offset += (frame_size / 4);
                } else {
                    printf("src resample 0 read over ");
                    break;
                }
            }

            ret = audio_src_base_write(src, data, frame_size);
#endif
        }

        audio_src_base_push_data_out(src);
        audio_src_base_stop(src);
        audio_src_base_close(src);
    }

    /* fclose(in_fp); */
    fclose(out_fp);

}

static int audio_src1_reuse_test(int in_sr, int out_sr, u8 channel)
{
#if 0
    FILE *in_fp;

    if (in_sr == 48000 && out_sr == 8000 && channel == 2) {
        in_fp = fopen(CONFIG_ROOT_PATH"sr4812.pcm", "r");
    } else if (in_sr == 48000 && out_sr == 8000 && channel == 4) {
        in_fp = fopen(CONFIG_ROOT_PATH"4ch16bit.pcm", "r");
    } else if (in_sr == 44100 && out_sr == 44100 && channel == 4) {
        in_fp = fopen(CONFIG_ROOT_PATH"4ch24bit.pcm", "r");
    } else if (in_sr == 44100 && out_sr == 8000 && channel == 2) {
        in_fp = fopen(CONFIG_ROOT_PATH"2ch24bit.pcm", "r");
    }

    if (!in_fp) {
        ASSERT(0);
    }
#endif

    char file_name[64];
    char long_file_name[128];
    snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"src/%dch-%d-%d.pcm", channel, in_sr, out_sr);
    long_file_name_encode(file_name, long_file_name, sizeof(long_file_name));


    FILE *out_fp = fopen(long_file_name, "w+");
    if (!out_fp) {
        ASSERT(0);
    }

    void *src;
    int data[RESAMPLE_PCM_FRAME_SIZE / 2];
    int ret = 0;
    /* int rlen = 0; */
    int offset = 0;
    int first_time = 1;
    int offset_total = 0;
    int *source_data1;
    int frame_size = sizeof(data);

#if 1
    if (in_sr == 48000 && out_sr == 8000 && channel == 4) {
        offset_total = 2400;
        source_data1 = malloc(9600);
        memcpy(source_data1, sr48k_4ch_16bit, 9600);
    } else if (in_sr == 48000 && out_sr == 8000 && channel == 2) {
        offset_total = 2400;
        source_data1 = malloc(9600);
        memcpy(source_data1, sr48k_2ch_16bit, 9600);
    } else if (in_sr == 44100 && out_sr == 8000 && channel == 2) {
        offset_total = 11025;
        source_data1 = malloc(44100);
        memcpy(source_data1, sr44100_2ch_24bit, 44100);
    } else if (in_sr == 44100 && out_sr == 44100 && channel == 4) {
        offset_total = 11025;
        source_data1 = malloc(44100);
        memcpy(source_data1, sr44100_4ch_24bit, 44100);
    }
#endif

    src = audio_src_base_open(channel, in_sr, out_sr, AUDIO_ONLY_RESAMPLE);
    if (src) {
        audio_src_base_set_output_handler(src, out_fp, audio_src1_out_hdl);
        while (1) {
            os_time_dly(1);
#if 0
            if (ret == rlen) {
                rlen = fread(data, 1, sizeof(data), in_fp);
                if (rlen <= 0) {
                    printf("src resample1 read over %d", rlen);
                    break;
                }
            }

            ret = audio_src_base_write(src, data, rlen);
#else

            if (ret == frame_size || first_time) {
                first_time = 0;
                if (offset < offset_total) {
                    if (in_sr == 44100 && out_sr == 8000 && channel == 2 && offset == 11000) {
                        frame_size = 100;
                    } else if (in_sr == 44100 && out_sr == 44100 && channel == 4 && offset == 11000) {
                        frame_size = 100;
                    }
                    memcpy(data, source_data1 + offset, frame_size);
                    offset += (frame_size / 4);
                } else {
                    printf("src resample 1 read over");
                    break;
                }
            }

            ret = audio_src_base_write(src, data, frame_size);
#endif
        }

        audio_src_base_push_data_out(src);
        audio_src_base_stop(src);
        audio_src_base_close(src);
    }

    /* fclose(in_fp); */
    fclose(out_fp);

}

static audio_src_test_run()
{
    /* audio_src_reuse_test(48000, 192000, 2); //reuse 48-192-2 */
    audio_src_reuse_test(48000, 192000, 4); //reuse 48-192-4
    /* audio_src_reuse_test(8000, 192000, 2);  //8-192-2 */


    /* audio_src_reuse_test(44100, 192000, 2); //reuse 44.1-192-2 24bit  */
    /* audio_src_reuse_test(44100, 48000, 4); //reuse 44.1-48-4 24bit  */
    /* audio_src_reuse_test(192000, 16000, 4); //192-16-4 24bit  */

}
static audio_src_test1_run()
{
    /* audio_src1_reuse_test(48000, 8000, 2); //reuse 48-8-2 */
    audio_src1_reuse_test(48000, 8000, 4); //reuse-48-8-4

    /* audio_src1_reuse_test(44100, 8000, 2);  //reuse 44.1-8-2 24bit  */
    /* audio_src1_reuse_test(44100, 44100, 4); //reuse 44.1-44.1-4 24bit  */
}

static void audio_src_reuse_test_task(void *p)
{
    while (0 == storage_device_ready()) {
        os_time_dly(100);
    }

    thread_fork("src_one", 2, 768 * 1, 0, NULL, audio_src_test_run, NULL);
    thread_fork("src_two", 2, 768 * 1, 0, NULL, audio_src_test1_run, NULL);
}

static int audio_src_reuse_test_init(void)
{
    return thread_fork("src_reuse_test", 2, 768, 0, NULL, audio_src_reuse_test_task, NULL);
}
late_initcall(audio_src_reuse_test_init);
#endif

#ifdef CONFIG_FPGA_EQ_TEST_ENABLE

#include "eq_testdata.c"

#define EQ_TEST_SEC_NUM 10
#define TEST_CNT 4

static struct hw_eq eq_hdl = {0};
static struct hw_eq_ch eq_ch_hdl[2] = {0};
static float EQ_Coeff_table[8][EQ_TEST_SEC_NUM * 5];
static float hw_eq_LRmem[2][3 * EQ_TEST_SEC_NUM * 8] = {0};
static u8 write_file = 0;

static const struct eq_seg_info eq_tab_normal[EQ_TEST_SEC_NUM] = {
    {0, EQ_IIR_TYPE_BAND_PASS, 31,    0, 0.7f },
    {1, EQ_IIR_TYPE_BAND_PASS, 62,    0, 0.7f },
    {2, EQ_IIR_TYPE_BAND_PASS, 125,   0, 0.7f },
    {3, EQ_IIR_TYPE_BAND_PASS, 250,   0, 0.7f },
    {4, EQ_IIR_TYPE_BAND_PASS, 500,   0, 0.7f },
    {5, EQ_IIR_TYPE_BAND_PASS, 1000,  0, 0.7f },
    {6, EQ_IIR_TYPE_BAND_PASS, 2000,  0, 0.7f },
    {7, EQ_IIR_TYPE_BAND_PASS, 4000,  0, 0.7f },
    {8, EQ_IIR_TYPE_BAND_PASS, 8000,  0, 0.7f },
    {9, EQ_IIR_TYPE_BAND_PASS, 16000, 0, 0.7f },
};

static const struct eq_seg_info eq_tab_rock[EQ_TEST_SEC_NUM] = {
    {0, EQ_IIR_TYPE_BAND_PASS, 31,    -2, 0.7f },
    {1, EQ_IIR_TYPE_BAND_PASS, 62,     0, 0.7f },
    {2, EQ_IIR_TYPE_BAND_PASS, 125,    2, 0.7f },
    {3, EQ_IIR_TYPE_BAND_PASS, 250,    4, 0.7f },
    {4, EQ_IIR_TYPE_BAND_PASS, 500,   -2, 0.7f },
    {5, EQ_IIR_TYPE_BAND_PASS, 1000,  -2, 0.7f },
    {6, EQ_IIR_TYPE_BAND_PASS, 2000,   0, 0.7f },
    {7, EQ_IIR_TYPE_BAND_PASS, 4000,   0, 0.7f },
    {8, EQ_IIR_TYPE_BAND_PASS, 8000,   4, 0.7f },
    {9, EQ_IIR_TYPE_BAND_PASS, 16000,  4, 0.7f },
};

static const struct eq_seg_info eq_tab_pop[EQ_TEST_SEC_NUM] = {
    {0, EQ_IIR_TYPE_BAND_PASS, 31,     3, 0.7f },
    {1, EQ_IIR_TYPE_BAND_PASS, 62,     1, 0.7f },
    {2, EQ_IIR_TYPE_BAND_PASS, 125,    0, 0.7f },
    {3, EQ_IIR_TYPE_BAND_PASS, 250,   -2, 0.7f },
    {4, EQ_IIR_TYPE_BAND_PASS, 500,   -4, 0.7f },
    {5, EQ_IIR_TYPE_BAND_PASS, 1000,  -4, 0.7f },
    {6, EQ_IIR_TYPE_BAND_PASS, 2000,  -2, 0.7f },
    {7, EQ_IIR_TYPE_BAND_PASS, 4000,   0, 0.7f },
    {8, EQ_IIR_TYPE_BAND_PASS, 8000,   1, 0.7f },
    {9, EQ_IIR_TYPE_BAND_PASS, 16000,  2, 0.7f },
};

static const struct eq_seg_info eq_tab_rand[EQ_TEST_SEC_NUM] = {
#if EQ_TEST_SEC_NUM <= 10
    {0, EQ_IIR_TYPE_HIGH_PASS, 31,   -5.2,   5 },
    {1, EQ_IIR_TYPE_HIGH_SHELF, 62,     -4.8, 5 },
    {2, EQ_IIR_TYPE_LOW_SHELF, 125,    0,    3 },
    {3, EQ_IIR_TYPE_BAND_PASS, 250,    -7.4,  11.4f},
    {4, EQ_IIR_TYPE_BAND_PASS, 500,    -2.3, 0.7f },
    {5, EQ_IIR_TYPE_BAND_PASS, 1000,   9.5,  0.7f },
    {6, EQ_IIR_TYPE_BAND_PASS, 2000,   0,    0.7f },
    {7, EQ_IIR_TYPE_BAND_PASS, 4000,   -8.4, 27.8f },
    {8, EQ_IIR_TYPE_BAND_PASS, 8000,   5,    30 },
    {9, EQ_IIR_TYPE_LOW_PASS, 16000,   4,    12.3f },
#else
    {0, EQ_IIR_TYPE_HIGH_PASS, 25,   3,  	3 },
    {1, EQ_IIR_TYPE_HIGH_SHELF, 31,  -3, 	5 },
    {2, EQ_IIR_TYPE_BAND_PASS, 39,  -2,  	30},
    {3, EQ_IIR_TYPE_LOW_SHELF, 48,  -3.8,  	4.6f},
    {4, EQ_IIR_TYPE_BAND_PASS, 60,   5.6,  	0.7f},
    {5, EQ_IIR_TYPE_BAND_PASS, 75,   0,  	0.7f},
    {6, EQ_IIR_TYPE_LOW_SHELF, 93,   -5.9, 4.7f },
    {7, EQ_IIR_TYPE_BAND_PASS, 116,   -5.2, 20.2f},
    {8, EQ_IIR_TYPE_HIGH_SHELF, 144,   1.6, 5 },
    {9, EQ_IIR_TYPE_BAND_PASS, 179,   9.9, 20.2f },
    {10, EQ_IIR_TYPE_BAND_PASS, 223,   0, 	30 },
    {11, EQ_IIR_TYPE_BAND_PASS, 277,   4.5, 30 },
    {12, EQ_IIR_TYPE_BAND_PASS, 345,   0, 	0.7f },
    {13, EQ_IIR_TYPE_BAND_PASS, 430,   0, 	0.7f },
    {14, EQ_IIR_TYPE_BAND_PASS, 535,   2.0, 21.1f },
    {15, EQ_IIR_TYPE_BAND_PASS, 698,   5.9, 30 },
    {16, EQ_IIR_TYPE_BAND_PASS, 828,   0, 	0.7f },
    {17, EQ_IIR_TYPE_BAND_PASS, 1031,  0, 	0.7f },
    {18, EQ_IIR_TYPE_BAND_PASS, 1283,  5.6, 0.3f },
    {19, EQ_IIR_TYPE_BAND_PASS, 1583,  -9.9, 7.8f },
    {20, EQ_IIR_TYPE_BAND_PASS, 1987,  0, 	0.7f },
    {21, EQ_IIR_TYPE_BAND_PASS, 2473,  0, 	0.7f },
    {22, EQ_IIR_TYPE_BAND_PASS, 3078,  4.8, 0.7f },
    {23, EQ_IIR_TYPE_BAND_PASS, 3831,  -2,  12.7f },
    {24, EQ_IIR_TYPE_BAND_PASS, 4768,  -3.4, 0.7f },
    {25, EQ_IIR_TYPE_BAND_PASS, 5934,  12, 	30 },
    {26, EQ_IIR_TYPE_BAND_PASS, 7285,  4.8, 5.6f },
    {27, EQ_IIR_TYPE_BAND_PASS, 9191,  0,   11.8f },
    {28, EQ_IIR_TYPE_BAND_PASS, 11438, 4,   23.8f },
    {29, EQ_IIR_TYPE_BAND_PASS, 15000, 0.8,  11.4f },
    {30, EQ_IIR_TYPE_BAND_PASS, 16000, -12,  14.9f },
    {31, EQ_IIR_TYPE_LOW_PASS,  17000, 0,   3.8f },
#endif
};

#define DATA_IN_SHORT_OUT_SHORT 0
#define DATA_IN_SHORT_OUT_INT 1
#define DATA_IN_INT_OUT_SHORT 2
#define DATA_IN_INT_OUT_INT 3
#define DATA_IN_FLOAT_OUT_FLOAT 4
#define DATA_IN_SHORT_OUT_FLOAT 5
#define DATA_IN_INT_OUT_FLOAT 6
#define DATA_IN_FLOAT_OUT_SHORT 7
#define DATA_IN_FLOAT_OUT_INT 8

#define NORMAL_TEST 0
#define MONO_TEST 1
#define STERO_TEST 2

static const s16 key_voice_44100Hz_tab[] = {
    0,
    0x2AAA,
    0x4ED5,
    0x66FF,
    0x6F7C,
    0x66FF,
    0x4ED5,
    0x2AAA,
    0,
    0xD556,
    0xB12B,
    0x9901,
    0x9084,
    0x9901,
    0xB12B,
    0xD556,
};

static const s16 key_voice_44100Hz_tab_dual[] = {
    0,
    0,
    0x2AAA,
    0x2AAA,
    0x4ED5,
    0x4ED5,
    0x66FF,
    0x66FF,
    0x6F7C,
    0x6F7C,
    0x66FF,
    0x66FF,
    0x4ED5,
    0x4ED5,
    0x2AAA,
    0x2AAA,
    0,
    0,
    0xD556,
    0xD556,
    0xB12B,
    0xB12B,
    0x9901,
    0x9901,
    0x9084,
    0x9084,
    0x9901,
    0x9901,
    0xB12B,
    0xB12B,
    0xD556,
    0xD556,
};

static const char *const str_test_mode[] = {
    "NORMAL",
    "MONO",
    "STERO",
};

static const char *const str_data_in_mode[] = {
    "BLOCK_IN",
    "SEQUENCE_IN",
};

static const char *const str_data_out_mode[] = {
    "BLOCK_OUT",
    "SEQUENCE_OUT",
};

static const char *const str_data_type_mode[] = {
    "DATA_IN_SHORT_OUT_SHORT",
    "DATA_IN_SHORT_OUT_INT",
    "DATA_IN_INT_OUT_SHORT",
    "DATA_IN_INT_OUT_INT",
    "DATA_IN_FLOAT_OUT_FLOAT",
    "DATA_IN_SHORT_OUT_FLOAT",
    "DATA_IN_INT_OUT_FLOAT",
    "DATA_IN_FLOAT_OUT_SHORT",
    "DATA_IN_FLOAT_OUT_INT"
};

static const char *const str_coeff_mode[] = {
    "TAB_RAND",
    "TAB_NORMAL",
    "TAB_ROCK",
    "TAB_POP",
};

#define ONCE_TEST_POINTS 256
static short inputbuf_short[ONCE_TEST_POINTS * 8];
static int inputbuf_int[ONCE_TEST_POINTS * 8];
static float inputbuf_float[ONCE_TEST_POINTS * 8];
static short outputbuf_short[ONCE_TEST_POINTS * 8];
static int outputbuf_int[ONCE_TEST_POINTS * 8];
static float outputbuf_float[ONCE_TEST_POINTS * 8];

static int hw_eq_probe(struct hw_eq_ch *ch)
{
    return 0;
}
static int hw_eq_output(struct hw_eq_ch *ch, s16 *buf, u16 len)
{
    return 0;
#if 0
//直通时，判断输出的是否正常
    if (&eq_ch_hdl[0] == ch) {
        s16 *datin = ch->in_buf;
        printf("ch0 out:%d ", len);
        if (ch->out_32bit) {
            int *dat = buf;
            for (int i = 0; i < len / 4; i++) {
                /* printf("0x%x,", dat[i]);	 */
                if (datin[i] != dat[i]) {
                    log_error("datin[%d] 0x%x 0x%x\n", i, datin[i], dat[i]);
                }
            }
        } else {
            s16 *dat = buf;
            for (int i = 0; i < len / 2; i++) {
                /* printf("0x%x,", dat[i]);	 */
                if (datin[i] != dat[i]) {
                    log_error("datin[%d] 0x%x 0x%x\n", i, datin[i], dat[i]);
                }
            }

        }
    } else {
        printf("ch1 out:%d ", len);

        if (ch->out_32bit) {
            if (ch->out_32bit == DATO_FLOAT) {
                float *datin = ch->in_buf;
                float *dat = buf;
                float dat_in_tmp = 0;
                float dat_out_tmp = 0;
                for (int i = 0; i < len / 4; i++) {
                    dat_in_tmp = datin[i];
                    dat_out_tmp = dat[i];
                    if (dat_in_tmp != dat_out_tmp) {
                        printf("---------------------------float i%d 0x%x 0x%x,", i, *(int *)&dat_in_tmp, *(int *)&dat_out_tmp);
                    }
                }
                /* log_error("datin[%d] 0x%x 0x%x\n", i, datin[i], dat[i]); */
            } else {
                int *dat = buf;
                int *datin = ch->in_buf;
                for (int i = 0; i < len / 4; i++) {
                    /* printf("0x%x,", dat[i]);	 */
                    if (datin[i] != dat[i]) {
                        log_error("------------------ int datin[%d] 0x%x 0x%x\n", i, datin[i], dat[i]);
                    }
                }
            }
        } else {
            s16 *dat = buf;
            s16 *datin = ch->in_buf;
            printf("points %d\n", len / 2);
            for (int i = 0; i < len / 2; i++) {
                /* printf("0x%x,", dat[i]); */
                if (datin[i] != dat[i]) {
                    log_error("---------------short datin[%d] 0x%x 0x%x\n", i, datin[i], dat[i]);
                }
            }

        }
    }
#endif
    /* printf_buf(buf, len); */
    return 0;
}
static int hw_eq_post(struct hw_eq_ch *ch)
{
    return 0;
}

static struct hw_eq_handler eq_handler = {
    .eq_probe = hw_eq_probe,
    .eq_output = hw_eq_output,
    .eq_post = hw_eq_post,
};

static void hw_eq_test(u8 channels, u8 test_mode, u8 data_type_mode, u8 data_in_mode, u8 data_out_mode, u32 total_cnt)
{
    void *inputbuf = NULL;
    void *outputbuf = NULL;
    FILE *fp = NULL;
    u8 intype = 0, outtype = 0;
    int tmp_buf[ONCE_TEST_POINTS];
    char file_name[128];
    u32 cnt = 0;
    short error_short, correct_short;
    int error_int, correct_int;

    printf("channels : %d, test_mode : %s, data_type_mode : %s, data_in_mode : %s, data_out_mode : %s\n",
           channels,
           str_test_mode[test_mode],
           str_data_type_mode[data_type_mode],
           str_data_in_mode[data_in_mode],
           str_data_out_mode[data_out_mode]
          );

    //24M clk时测试的耗时
    /* u8 channels = 4;//367us */
    /* u8 channels = 3;//273us */
    /* u8 channels = 2;//180us */
    /* u8 channels = 1;//116us */

    int TEST_CPU_SECTION = 10;
    if (channels * EQ_TEST_SEC_NUM > 20) {
        TEST_CPU_SECTION += (channels * EQ_TEST_SEC_NUM - 20);
    }
    memset(&hw_eq_LRmem, 0, sizeof(hw_eq_LRmem));
    audio_hw_eq_init(&eq_hdl, TEST_CPU_SECTION);
    audio_hw_eq_ch_open(&eq_ch_hdl[0], &eq_hdl);
    audio_hw_eq_ch_open(&eq_ch_hdl[1], &eq_hdl);
    eq_ch_hdl[0].eq_LRmem = hw_eq_LRmem[0];
    eq_ch_hdl[1].eq_LRmem = hw_eq_LRmem[1];

    audio_hw_eq_ch_set_handler(&eq_ch_hdl[0], &eq_handler);
    audio_hw_eq_ch_set_handler(&eq_ch_hdl[1], &eq_handler);

    // 测试设置不同的声道
    /* audio_hw_eq_ch_set_info(&eq_ch_hdl[0], 1, 1); */
    /* audio_hw_eq_ch_set_info(&eq_ch_hdl[1], channels, 0); */

    if (data_type_mode == DATA_IN_SHORT_OUT_SHORT) {
        intype = 0;
        outtype = 0;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_SHORT, DATO_SHORT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_SHORT_OUT_INT) {
        intype = 0;
        outtype = 1;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_SHORT, DATO_INT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_INT_OUT_SHORT) {
        intype = 1;
        outtype = 0;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_INT, DATO_SHORT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_INT_OUT_INT) {
        intype = 1;
        outtype = 1;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_INT, DATO_INT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_FLOAT_OUT_FLOAT) {
        intype = 2;
        outtype = 2;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_FLOAT, DATO_FLOAT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_SHORT_OUT_FLOAT) {
        intype = 0;
        outtype = 2;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_SHORT, DATO_FLOAT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_INT_OUT_FLOAT) {
        intype = 1;
        outtype = 2;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_INT, DATO_FLOAT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_FLOAT_OUT_SHORT) {
        intype = 2;
        outtype = 0;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_FLOAT, DATO_SHORT, test_mode, data_in_mode, data_out_mode);//正常
    } else if (data_type_mode == DATA_IN_FLOAT_OUT_INT) {
        intype = 2;
        outtype = 1;
        audio_hw_eq_ch_set_info_new(&eq_ch_hdl[1], channels, DATI_FLOAT, DATO_INT, test_mode, data_in_mode, data_out_mode);//正常
    }

    // 测试使用不同的转换系数
    float *ptr;
    /* int j = 30; */
    if (channels <= 2) {
        for (int i = 0; i < EQ_TEST_SEC_NUM; i++) {
            /* printf("---------------i %d\n", i); */
            eq_seg_design(&eq_tab_rand[i], 44100, &EQ_Coeff_table[0][5 * i]);
            /* ptr = &EQ_Coeff_table[0][5*i]; */
            /* ptr[4] = i; */
            eq_seg_design(&eq_tab_rand[i], 44100, &EQ_Coeff_table[1][5 * i]);
            /* ptr = &EQ_Coeff_table[1][5*i]; */
            /* ptr[4] = j; */
            /* j++; */
            /* log_info("0x%x, 0x%x, 0x%x, 0x%x, 0x%x", *(int *)&ptr[0], *(int *)&ptr[1], *(int *)&ptr[2], *(int *)&ptr[3], *(int *)&ptr[4]); */
        }
    } else {
        for (int i = 0; i < EQ_TEST_SEC_NUM; i++) {
            for (int j = 0; j < channels; j++) {
                eq_seg_design(&eq_tab_rand[i], 44100, &EQ_Coeff_table[j][5 * i]);
                /* #if DATA_IN_16_OUT_32 */
                /* ptr = &EQ_Coeff_table[j][5*i]; */
                /* ptr[4] = 8; */
                /* #endif */
            }
        }
    }

    struct eq_coeff_info info = {0};
#ifdef CONFIG_EQ_NO_USE_COEFF_TABLE
    info.sr = sr;
#endif
    info.nsection = EQ_TEST_SEC_NUM;
    info.L_gain = info.R_gain = 0;
    info.L_coeff = info.R_coeff = EQ_Coeff_table[0];
    /* audio_hw_eq_ch_set_coeff(&eq_ch_hdl[0], &info); */
    /* info.L_coeff = EQ_Coeff_table[1]; */
    /* info.R_coeff = &EQ_Coeff_table[1][5*20]; */
    if (channels <= 2) {
        info.L_coeff = EQ_Coeff_table[0];
        info.R_coeff = EQ_Coeff_table[1];
        /* info.L_gain = -3; */
        /* info.R_gain = 3; */
    } else {
        for (int i = 0; i < channels; i++) {
            info.N_coeff[i] = EQ_Coeff_table[i];
            /* info.N_gain[i] = i; */
        }
    }
    audio_hw_eq_ch_set_coeff(&eq_ch_hdl[1], &info);

    while (cnt < total_cnt) {
        if (write_file) {
            snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"eq/%d-%s-%s-%s-%s-%s.pcm",
                     channels,
                     str_test_mode[test_mode],
                     str_data_type_mode[data_type_mode],
                     str_data_in_mode[data_in_mode],
                     str_data_out_mode[data_out_mode],
                     str_coeff_mode[cnt % 4]
                    );

            /* ASCII_ToLower(file_name + strlen(CONFIG_ROOT_PATH), strlen(file_name) - strlen(CONFIG_ROOT_PATH)); */

            fp = fopen_by_utf8(file_name, "w+");
        } else {
            snprintf(file_name, sizeof(file_name), CONFIG_ROOT_PATH"eq/%d-%s-%s-%s-%s-%s.pcm",
                     1,
                     str_test_mode[NORMAL_TEST],
                     str_data_type_mode[data_type_mode],
                     str_data_in_mode[SEQUENCE_DAT_IN],
                     str_data_out_mode[SEQUENCE_DAT_OUT],
                     str_coeff_mode[cnt % 4]
                    );

            /* ASCII_ToLower(file_name + strlen(CONFIG_ROOT_PATH), strlen(file_name) - strlen(CONFIG_ROOT_PATH)); */

            fp = fopen_by_utf8(file_name, "r");
        }

        u32 remain = sizeof(eq_testdata);
        u32 offset = 0;
        u32 total_len = sizeof(eq_testdata);

        while (offset < total_len) {
            if (remain > ONCE_TEST_POINTS * 2) {
                remain = ONCE_TEST_POINTS * 2;
            }
            /* if (remain > 128) { */
            /*     remain = 128; */
            /* } */

            if (outtype == 0) {
                outputbuf = outputbuf_short;
                memset(outputbuf_short, 0, sizeof(outputbuf_short));
            } else if (outtype == 1) {
                outputbuf = outputbuf_int;
                memset(outputbuf_int, 0, sizeof(outputbuf_int));
            } else if (outtype == 2) {
                outputbuf = outputbuf_float;
                memset(outputbuf_float, 0, sizeof(outputbuf_float));
            }

            if (test_mode == STERO_TEST) {
                if (intype == 0) {
                    if (data_in_mode == SEQUENCE_DAT_IN) {
                        for (int i = 0, j = 0 ; j < remain / 2; j++) {
                            inputbuf_short[i] = (short)eq_testdata[offset / 2 + j];
                            inputbuf_short[i + 1] = (short)eq_testdata[offset / 2 + j];
                            i += 2;
                        }
                    } else {
                        for (int i = 0; i < remain / 2; i++) {
                            inputbuf_short[i] = (short)eq_testdata[offset / 2 + i];
                        }
                        for (int i = 0; i < remain / 2; i++) {
                            inputbuf_short[remain / 2 + i] = (short)eq_testdata[offset / 2 + i];
                        }
                    }
                    inputbuf = inputbuf_short;
                } else if (intype == 1) {
                    if (data_in_mode == SEQUENCE_DAT_IN) {
                        for (int i = 0, j = 0 ; j < remain / 2; j++) {
                            inputbuf_int[i] = (int)eq_testdata[offset / 2 + j];
                            inputbuf_int[i + 1] = (int)eq_testdata[offset / 2 + j];
                            i += 2;
                        }
                    } else {
                        for (int i = 0; i < remain / 2; i++) {
                            inputbuf_int[i] = (int)eq_testdata[offset / 2 + i];
                        }
                        for (int i = 0; i < remain / 2; i++) {
                            inputbuf_int[remain / 2 + i] = (int)eq_testdata[offset / 2 + i];
                        }
                    }
                    inputbuf = inputbuf_int;
                } else if (intype == 2) {
                    if (data_in_mode == SEQUENCE_DAT_IN) {
                        for (int i = 0, j = 0 ; j < remain / 2; j++) {
                            inputbuf_float[i] = (float)eq_testdata[offset / 2 + j];
                            inputbuf_float[i + 1] = (float)eq_testdata[offset / 2 + j];
                            i += 2;
                        }
                    } else {
                        for (int i = 0; i < remain / 2; i++) {
                            inputbuf_float[i] = (float)eq_testdata[offset / 2 + i];
                        }
                        for (int i = 0; i < remain / 2; i++) {
                            inputbuf_float[remain / 2 + i] = (float)eq_testdata[offset / 2 + i];
                        }
                    }
                    inputbuf = inputbuf_float;
                }

                if (intype == 0) {
                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 2);
                } else if (intype == 1) {
                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 4);
                } else if (intype == 2) {
                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 4);
                }

                if (fp && write_file) {
                    if (outtype == 0) {
                        fwrite(outputbuf, remain * channels, 1, fp);
                    } else if (outtype == 1) {
                        fwrite(outputbuf, remain * 2 * channels, 1, fp);
                    } else if (outtype == 2) {
                        fwrite(outputbuf, remain * 2 * channels, 1, fp);
                    }
                }
                if (fp && !write_file) {
                    if (outtype == 0) {
                        fread(tmp_buf, remain, 1, fp);
                    } else {
                        fread(tmp_buf, remain * 2, 1, fp);
                    }
                    if (data_out_mode == SEQUENCE_DAT_OUT) {
                        for (int i = 0, j = 0; j < remain / 2; j++) {
                            for (int n = 0; n < channels; ++n) {
                                if (outtype == 0) {
                                    if (((s16 *)outputbuf)[i + n] != ((s16 *)tmp_buf)[j]) {
                                        error_short = ((s16 *)outputbuf)[i + n];
                                        correct_short = ((s16 *)tmp_buf)[j];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL SEQUENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, j : %d, n : %d, offset : %d\n", i, j, n, offset);
                                        printf("correct_short : %d, error_short : %d\n", correct_short, error_short);
                                        while (1);
                                    }
                                } else {
                                    if (((int *)outputbuf)[i + n] != ((int *)tmp_buf)[j]) {
                                        error_int = ((int *)outputbuf)[i + n];
                                        correct_int = ((int *)tmp_buf)[j];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL SEQUENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, j : %d, n : %d\n", i, j, n);
                                        printf("correct_int : %d, error_int : %d\n", correct_int, error_int);
                                        while (1);
                                    }
                                }
                            }
                            i += channels;
                        }
                    } else {
                        for (int n = 0; n < channels; ++n) {
                            for (int i = 0; i < remain / 2; i++) {
                                if (outtype == 0) {
                                    if (((s16 *)outputbuf)[remain / 2 * n + i] != ((s16 *)tmp_buf)[i]) {
                                        error_short = ((s16 *)outputbuf)[remain / 2 * n + i];
                                        correct_short = ((s16 *)tmp_buf)[i];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, n : %d, offset : %d\n", i, n, offset);
                                        printf("correct_short : %d, error_short : %d\n", correct_short, error_short);
                                        while (1);
                                    }
                                } else {
                                    if (((int *)outputbuf)[remain / 2 * n + i] != ((int *)tmp_buf)[i]) {
                                        error_int = ((int *)outputbuf)[remain / 2 * n + i];
                                        correct_int = ((int *)tmp_buf)[i];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, n : %d\n", i, n);
                                        printf("correct_int : %d, error_int : %d\n", correct_int, error_int);

                                        while (1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (test_mode == MONO_TEST) {
                if (intype == 0) {
                    for (int i = 0; i < remain / 2; i++) {
                        inputbuf_short[i] = (short)eq_testdata[offset / 2 + i];
                    }
                    inputbuf = inputbuf_short;
                } else if (intype == 1) {
                    for (int i = 0; i < remain / 2; i++) {
                        inputbuf_int[i] = (int)eq_testdata[offset / 2 + i];
                    }
                    inputbuf = inputbuf_int;
                } else if (intype == 2) {
                    for (int i = 0; i < remain / 2; i++) {
                        inputbuf_float[i] = (float)eq_testdata[offset / 2 + i];
                    }
                    inputbuf = inputbuf_float;
                }

                if (intype == 0) {
                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain);
                } else if (intype == 1) {
                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 2);
                } else if (intype == 2) {
                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 2);
                }

                if (fp && write_file) {
                    if (outtype == 0) {
                        fwrite(outputbuf, remain * channels, 1, fp);
                    } else if (outtype == 1) {
                        fwrite(outputbuf, remain * 2 * channels, 1, fp);
                    } else if (outtype == 2) {
                        fwrite(outputbuf, remain * 2 * channels, 1, fp);
                    }
                }
                if (fp && !write_file) {
                    if (outtype == 0) {
                        fread(tmp_buf, remain, 1, fp);
                    } else {
                        fread(tmp_buf, remain * 2, 1, fp);
                    }
                    if (data_out_mode == SEQUENCE_DAT_OUT) {
                        for (int i = 0, j = 0; j < remain / 2; j++) {
                            for (int n = 0; n < channels; ++n) {
                                if (outtype == 0) {
                                    if (((s16 *)outputbuf)[i + n] != ((s16 *)tmp_buf)[j]) {
                                        error_short = ((s16 *)outputbuf)[i + n];
                                        correct_short = ((s16 *)tmp_buf)[j];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL SEQUENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, j : %d, n : %d, offset : %d\n", i, j, n, offset);
                                        printf("correct_short : %d, error_short : %d\n", correct_short, error_short);
                                        while (1);
                                    }
                                } else {
                                    if (((int *)outputbuf)[i + n] != ((int *)tmp_buf)[j]) {
                                        error_int = ((int *)outputbuf)[i + n];
                                        correct_int = ((int *)tmp_buf)[j];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL SEQUENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, j : %d, n : %d\n", i, j, n);
                                        printf("correct_int : %d, error_int : %d\n", correct_int, error_int);
                                        while (1);
                                    }
                                }
                            }
                            i += channels;
                        }
                    } else {
                        for (int n = 0; n < channels; ++n) {
                            for (int i = 0; i < remain / 2; i++) {
                                if (outtype == 0) {
                                    if (((s16 *)outputbuf)[remain / 2 * n + i] != ((s16 *)tmp_buf)[i]) {
                                        error_short = ((s16 *)outputbuf)[remain / 2 * n + i];
                                        correct_short = ((s16 *)tmp_buf)[i];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, n : %d, offset : %d\n", i, n, offset);
                                        printf("correct_short : %d, error_short : %d\n", correct_short, error_short);
                                        while (1);
                                    }
                                } else {
                                    if (((int *)outputbuf)[remain / 2 * n + i] != ((int *)tmp_buf)[i]) {
                                        error_int = ((int *)outputbuf)[remain / 2 * n + i];
                                        correct_int = ((int *)tmp_buf)[i];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, n : %d\n", i, n);
                                        printf("correct_int : %d, error_int : %d\n", correct_int, error_int);
                                        while (1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (test_mode == NORMAL_TEST) {
                if (intype == 0) {
                    if (data_in_mode == SEQUENCE_DAT_IN) {
                        for (int i = 0, j = 0; j < remain / 2; j++) {
                            for (int n = 0; n < channels; ++n) {
                                inputbuf_short[i + n] = (short)eq_testdata[offset / 2 + j];
                            }
                            i += channels;
                        }
                    } else {
                        for (int n = 0; n < channels; ++n) {
                            for (int i = 0; i < remain / 2; i++) {
                                inputbuf_short[(remain / 2) * n + i] = (short)eq_testdata[offset / 2 + i];
                            }
                        }
                    }
                    inputbuf = inputbuf_short;

                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * channels);
                } else if (intype == 1) {
                    if (data_in_mode == SEQUENCE_DAT_IN) {
                        for (int i = 0, j = 0; j < remain / 2; j++) {
                            for (int n = 0; n < channels; ++n) {
                                inputbuf_int[i + n] = (int)eq_testdata[offset / 2 + j];
                            }
                            i += channels;
                        }
                    } else {
                        for (int n = 0; n < channels; ++n) {
                            for (int i = 0; i < remain / 2; i++) {
                                inputbuf_int[(remain / 2) * n + i] = (int)eq_testdata[offset / 2 + i];
                            }
                        }
                    }
                    inputbuf = inputbuf_int;

                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 2 * channels);
                } else if (intype == 2) {
                    if (data_in_mode == SEQUENCE_DAT_IN) {
                        for (int i = 0, j = 0; j < remain / 2; j++) {
                            for (int n = 0; n < channels; ++n) {
                                inputbuf_float[i + n] = (float)eq_testdata[offset / 2 + j];
                            }
                            i += channels;
                        }
                    } else {
                        for (int n = 0; n < channels; ++n) {
                            for (int i = 0; i < remain / 2; i++) {
                                inputbuf_float[(remain / 2) * n + i] = (float)eq_testdata[offset / 2 + i];
                            }
                        }
                    }
                    inputbuf = inputbuf_float;

                    audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, remain * 2 * channels);
                }

                if (fp && write_file) {
                    if (outtype == 0) {
                        fwrite(outputbuf, remain * channels, 1, fp);
                    } else if (outtype == 1) {
                        fwrite(outputbuf, remain * 2 * channels, 1, fp);
                    } else if (outtype == 2) {
                        fwrite(outputbuf, remain * 2 * channels, 1, fp);
                    }
                }
                if (fp && !write_file) {
                    if (outtype == 0) {
                        fread(tmp_buf, remain, 1, fp);
                    } else {
                        fread(tmp_buf, remain * 2, 1, fp);
                    }
                    if (data_out_mode == SEQUENCE_DAT_OUT) {
                        for (int i = 0, j = 0; j < remain / 2; j++) {
                            for (int n = 0; n < channels; ++n) {
                                if (outtype == 0) {
                                    if (((s16 *)outputbuf)[i + n] != ((s16 *)tmp_buf)[j]) {
                                        error_short = ((s16 *)outputbuf)[i + n];
                                        correct_short = ((s16 *)tmp_buf)[j];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL SEQUENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, j : %d, n : %d, offset : %d\n", i, j, n, offset);
                                        printf("correct_short : %d, error_short : %d\n", correct_short, error_short);
                                        while (1);
                                    }
                                } else {
                                    if (((int *)outputbuf)[i + n] != ((int *)tmp_buf)[j]) {
                                        error_int = ((int *)outputbuf)[i + n];
                                        correct_int = ((int *)tmp_buf)[j];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL SEQUENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, j : %d, n : %d\n", i, j, n);
                                        printf("correct_int : %d, error_int : %d\n", correct_int, error_int);
                                        while (1);
                                    }
                                }
                            }
                            i += channels;
                        }
                    } else {
                        for (int n = 0; n < channels; ++n) {
                            for (int i = 0; i < remain / 2; i++) {
                                if (outtype == 0) {
                                    if (((s16 *)outputbuf)[remain / 2 * n + i] != ((s16 *)tmp_buf)[i]) {
                                        error_short = ((s16 *)outputbuf)[remain / 2 * n + i];
                                        correct_short = ((s16 *)tmp_buf)[i];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, n : %d, offset : %d\n", i, n, offset);
                                        printf("correct_short : %d, error_short : %d\n", correct_short, error_short);
                                        while (1);
                                    }
                                } else {
                                    if (((int *)outputbuf)[remain / 2 * n + i] != ((int *)tmp_buf)[i]) {
                                        error_int = ((int *)outputbuf)[remain / 2 * n + i];
                                        correct_int = ((int *)tmp_buf)[i];
                                        ___trig;
                                        put_buf(outputbuf, remain * channels);
                                        put_buf((u8 *)tmp_buf, remain);
                                        printf("EQ TEST FAIL BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                        printf("i : %d, n : %d\n", i, n);
                                        printf("correct_int : %d, error_int : %d\n", correct_int, error_int);
                                        while (1);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            offset += remain;
            remain = total_len - offset;
        }

        if (fp) {
            fclose(fp);
            fp = NULL;
        }
#if 0
        /* memcpy(inputbuf, key_voice_44100Hz_tab_dual, sizeof(key_voice_44100Hz_tab_dual)); */
        /* audio_hw_eq_ch_start(&eq_ch_hdl[1], inputbuf, outputbuf, sizeof(key_voice_44100Hz_tab_dual)); */
#endif

#if 0
        memcpy(inputbuf, key_voice_44100Hz_tab, sizeof(key_voice_44100Hz_tab));
        audio_hw_eq_ch_start(&eq_ch_hdl[0], inputbuf, outputbuf, sizeof(key_voice_44100Hz_tab));
#endif

        if (++cnt < total_cnt) {
            // 测试中间过程变化转换系数
            for (int i = 0; i < EQ_TEST_SEC_NUM; i++) {
                for (int j = 0; j < channels; j++) {
                    if (cnt % 4 == 0) {
                        eq_seg_design(&eq_tab_rand[i], 44100, &EQ_Coeff_table[j][5 * i]);
                    } else if (cnt % 4 == 1) {
                        eq_seg_design(&eq_tab_normal[i], 44100, &EQ_Coeff_table[j][5 * i]);
                    } else if (cnt % 4 == 2) {
                        eq_seg_design(&eq_tab_rock[i], 44100, &EQ_Coeff_table[j][5 * i]);
                    } else if (cnt % 4 == 3) {
                        eq_seg_design(&eq_tab_pop[i], 44100, &EQ_Coeff_table[j][5 * i]);
                    }
                }
            }
            audio_hw_eq_ch_set_coeff(&eq_ch_hdl[1], &info);
        }
    }

    audio_hw_eq_ch_close(&eq_ch_hdl[0]);
    audio_hw_eq_ch_close(&eq_ch_hdl[1]);
}

static void eq_test_task(void *priv)
{
    while (0 == storage_device_ready()) {
        os_time_dly(100);
    }

    while (1) {
        for (int j = 1; j <= 8; ++j) {
            for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                hw_eq_test(j, NORMAL_TEST, i, SEQUENCE_DAT_IN, SEQUENCE_DAT_OUT, TEST_CNT);
            }
            for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                hw_eq_test(j, NORMAL_TEST, i, SEQUENCE_DAT_IN, BLOCK_DAT_OUT, TEST_CNT);
            }
            for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                hw_eq_test(j, NORMAL_TEST, i, BLOCK_DAT_IN, SEQUENCE_DAT_OUT, TEST_CNT);
            }
            for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                hw_eq_test(j, NORMAL_TEST, i, BLOCK_DAT_IN, BLOCK_DAT_OUT, TEST_CNT);
            }
            for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                hw_eq_test(j, MONO_TEST, i, SEQUENCE_DAT_IN, SEQUENCE_DAT_OUT, TEST_CNT);
            }
            for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                hw_eq_test(j, MONO_TEST, i, SEQUENCE_DAT_IN, BLOCK_DAT_OUT, TEST_CNT);
            }
            if (j % 2 == 0) {
                for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                    hw_eq_test(j, STERO_TEST, i, SEQUENCE_DAT_IN, SEQUENCE_DAT_OUT, TEST_CNT);
                }
                for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                    hw_eq_test(j, STERO_TEST, i, SEQUENCE_DAT_IN, BLOCK_DAT_OUT, TEST_CNT);
                }
                for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                    hw_eq_test(j, STERO_TEST, i, BLOCK_DAT_IN, SEQUENCE_DAT_OUT, TEST_CNT);
                }
                for (int i = 0; i <= DATA_IN_FLOAT_OUT_INT; ++i) {
                    hw_eq_test(j, STERO_TEST, i, BLOCK_DAT_IN, BLOCK_DAT_OUT, TEST_CNT);
                }
            }
        }
        write_file = 0;
    }
}

static int eq_test_init(void)
{
    return thread_fork("eq_test", 2, 1024, 0, 0, eq_test_task, NULL);
}
late_initcall(eq_test_init);

#endif


#ifdef CONFIG_FPGA_FFT_TEST_ENABLE
static const int real_fft_test_input_data_512[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 20, -83, 58, -40, 140, -161, 110, -102, 80, -17, 41, -101, 26, 35, -54, -28, 180, -49, -180, 87, 70, 34, -222, 272, -129, 2, 44, 86, -186, 84, 32, -99, 126, -90, 44, -44, 94, -167, 55, 42, 1, -55, 65, -15, -79, 156, -64, -29, 9, 99, -125, -10, 133, -88, -6, 0, 5, 38, -65, 25, -64, 104, -79, -10, 28, -50, 105, -89, 92, -125, 159, -143, 27, 41, -25, 56, -135, 134, -108, 87, -26, 0, -35, 62, 18, -83, 41, 42, -66, -1, 69, -54, -14, 26, 48, -64, 5, 38, -4, -44, 74, -59, 10, 24, 1, -40, 23, 31, -81, 58, -2, -10, 0, 26, -44, 2, 25, -1, -30, 37, -27, 0, 5, 8, -13, -13, 37, -25, 13, -10, 23, -30, 22, -1, -10, 2, 4, -2, -3, 11, -10, 0, 4, 3, -10, 9, -2, -2, -2, 4, -1, -2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const int real_fft_test_output_data_real_512[] = {
    16, -15, 15, -17, 26, -39, 50, -51, 32, 7, -43, 45, -16, -17, 23, -17, 24, -44, 49, -24, -13, 45, -66, 89, -108, 116, -105, 84, -62, 32, 12, -50, 47, 1, -49, 49, -6, -43, 65, -66, 56, -32, -7, 39, -47, 36, -19, -2, 31, -63, 85, -93, 108, -133, 143, -118, 84, -87, 144, -208, 224, -189, 147, -128, 120, -96, 57, -37, 61, -110, 128, -80, -11, 75, -78, 48, -28, 3, 71, -191, 288, -305, 258, -221, 246, -327, 414, -452, 431, -398, 392, -369, 263, -116, 66, -174, 336, -418, 401, -357, 321, -271, 216, -212, 277, -323, 242, -45, -122, 116, 52, -226, 269, -148, -72, 294, -446, 496, -449, 285, 6, -372, 672, -793, 715, -487, 226, -92, 164, -326, 374, -266, 153, -156, 263, -421, 568, -591, 393, -52, -214, 290, -257, 287, -498, 837, -1075, 991, -594, 77, 383, -612, 327, 521, -1311, 1229, -380, -106, -581, 1888, -2622, 2366, -1699, 1257, -1084, 895, -529, 57, 313, -397, 220, -37, 51, -157, 113, 89, -177, -41, 439, -717, 718, -534, 347, -270, 308, -409, 498, -498, 373, -180, 32, 4, 38, -58, 14, 48, -84, 109, -155, 233, -351, 532, -725, 773, -562, 194, 76, -64, -199, 484, -517, 207, 197, -297, -22, 465, -727, 837, -953, 932, -417, -602, 1538, -1694, 934, 243, -1241, 1793, -1868, 1439, -612, -169, 432, -182, -193, 514, -872, 1058, -524, -755, 1863, -1893, 1041, -279, 131, -279, 279, -114, -20, 88, -168, 270, -355, 420, -474, 507, -516
};

static const int real_fft_test_output_data_img_512[] = {
    0, -5, 14, -22, 29, -28, 16, 9, -34, 43, -20, -21, 43, -30, 3, 9, -11, 30, -72, 111, -127, 123, -115, 104, -81, 46, -12, -11, 29, -44, 44, -10, -43, 70, -40, -19, 53, -42, 11, 18, -44, 66, -68, 41, -3, -31, 52, -72, 86, -85, 73, -67, 68, -59, 29, -5, 23, -75, 105, -72, 3, 49, -60, 55, -65, 83, -80, 49, -17, 34, -102, 172, -181, 123, -49, 3, 29, -85, 150, -164, 99, -11, -22, -23, 100, -146, 128, -66, 22, -23, 28, 6, -32, -55, 252, -417, 433, -339, 248, -200, 166, -132, 130, -154, 123, 18, -207, 293, -212, 59, -11, 151, -404, 636, -750, 718, -573, 374, -153, -62, 203, -174, -50, 381, -688, 861, -833, 633, -438, 418, -536, 604, -526, 389, -308, 327, -484, 777, -1067, 1169, -1061, 910, -887, 1009, -1137, 1074, -736, 284, 1, 27, -367, 1010, -1776, 2123, -1622, 733, -531, 1372, -2304, 2202, -1105, -10, 489, -525, 579, -784, 973, -952, 668, -273, 34, -63, 176, -141, 3, -26, 293, -573, 585, -306, -39, 235, -241, 150, -69, 68, -167, 332, -477, 507, -413, 285, -227, 248, -278, 269, -248, 255, -284, 318, -348, 331, -176, -119, 383, -395, 116, 268, -497, 427, -154, -8, -217, 741, -1159, 1200, -996, 784, -512, -6, 604, -725, 8, 1224, -2201, 2400, -1873, 961, 80, -1027, 1537, -1407, 919, -605, 653, -883, 1299, -2131, 3144, -3489, 2686, -1398, 712, -893, 1285, -1333, 1126, -971, 908, -817, 681, -553, 442, -328, 215, -108, 0
};

static const int complex_fft_test_output_data_256[] = {
    65280, 65536, -21115, 20602, -10685, 10172, -7207, 6694, -5467, 4955, -4423, 3912, -3727, 3214, -3229, 2716, -2855, 2343, -2564, 2053, -2332, 1820, -2142, 1629, -1982, 1470, -1847, 1335, -1731, 1220, -1631, 1119, -1543, 1031, -1465, 953, -1396, 884, -1334, 822, -1278, 766, -1227, 716, -1181, 669, -1139, 627, -1100, 588, -1064, 552, -1030, 519, -1000, 488, -972, 459, -944, 432, -919, 407, -896, 384, -874, 362, -853, 341, -833, 322, -814, 303, -797, 286, -781, 268, -764, 252, -749, 237, -735, 223, -721, 209, -708, 196, -695, 183, -683, 171, -671, 160, -660, 149, -650, 138, -639, 127, -629, 117, -620, 107, -610, 98, -601, 89, -593, 81, -584, 72, -576, 64, -568, 56, -560, 48, -553, 41, -546, 33, -539, 27, -532, 20, -525, 13, -518, 6, -512, 0, -506, -6, -500, -13, -494, -18, -488, -24, -482, -30, -477, -35, -471, -41, -466, -46, -461, -51, -456, -56, -451, -61, -446, -66, -441, -71, -436, -76, -432, -80, -427, -85, -423, -90, -418, -94, -414, -98, -410, -103, -405, -107, -401, -111, -397, -115, -393, -119, -389, -123, -385, -127, -381, -131, -377, -135, -373, -139, -370, -143, -366, -146, -362, -150, -358, -154, -355, -157, -351, -161, -348, -164, -344, -168, -340, -171, -337, -175, -334, -178, -331, -182, -327, -185, -324, -189, -320, -192, -317, -195, -313, -199, -310, -202, -307, -205, -304, -208, -301, -212, -297, -215, -294, -218, -291, -221, -288, -224, -284, -228, -281, -231, -278, -234, -275, -237, -272, -241, -269, -243, -265, -247, -262, -250, -259, -253, -256, -256, -253, -259, -250, -262, -247, -265, -243, -269, -241, -272, -237, -275, -234, -278, -231, -281, -228, -284, -224, -288, -221, -291, -218, -294, -215, -297, -212, -301, -208, -304, -205, -307, -202, -310, -199, -313, -195, -317, -192, -320, -189, -324, -185, -327, -182, -331, -178, -334, -175, -337, -171, -340, -168, -344, -164, -348, -161, -351, -157, -355, -154, -358, -150, -362, -146, -366, -143, -370, -139, -373, -135, -377, -131, -381, -127, -385, -123, -389, -119, -393, -115, -397, -111, -401, -107, -405, -103, -410, -98, -414, -94, -418, -90, -423, -85, -427, -80, -432, -76, -436, -71, -441, -66, -446, -61, -451, -56, -456, -51, -461, -46, -466, -41, -471, -35, -477, -30, -482, -24, -488, -18, -494, -13, -500, -6, -506, 0, -512, 6, -518, 13, -525, 20, -532, 27, -539, 33, -546, 41, -553, 48, -560, 56, -568, 64, -576, 72, -584, 81, -593, 89, -601, 98, -610, 107, -620, 117, -629, 127, -639, 138, -650, 149, -660, 160, -671, 171, -683, 183, -695, 196, -708, 209, -721, 223, -735, 237, -749, 252, -764, 268, -781, 286, -797, 303, -814, 322, -833, 341, -853, 362, -874, 384, -896, 407, -919, 432, -944, 459, -972, 488, -1000, 519, -1030, 552, -1064, 588, -1100, 627, -1139, 669, -1181, 716, -1227, 766, -1278, 822, -1334, 884, -1396, 953, -1465, 1031, -1543, 1119, -1631, 1220, -1731, 1335, -1847, 1470, -1982, 1629, -2142, 1820, -2332, 2053, -2564, 2343, -2855, 2716, -3229, 3214, -3727, 3912, -4423, 4955, -5467, 6694, -7207, 10172, -10685, 20602, -21115
};

static const int complex_fft_test_output_data_512[] = {
    261632, 262144, -83954, 82931, -42230, 41204, -28325, 27297, -21369, 20345, -17196, 16168, -14414, 13386, -12426, 11398, -10934, 9909, -9773, 8752, -8844, 7823, -8084, 7063, -7453, 6429, -6917, 5894, -6457, 5433, -6058, 5036, -5711, 4686, -5402, 4379, -5128, 4105, -4883, 3861, -4663, 3638, -4463, 3438, -4283, 3257, -4117, 3090, -3964, 2939, -3824, 2799, -3694, 2670, -3575, 2551, -3463, 2438, -3358, 2335, -3262, 2238, -3172, 2148, -3086, 2062, -3007, 1983, -2931, 1907, -2859, 1835, -2792, 1769, -2729, 1704, -2668, 1644, -2610, 1587, -2556, 1533, -2503, 1481, -2454, 1431, -2406, 1384, -2362, 1338, -2319, 1294, -2277, 1254, -2238, 1214, -2200, 1176, -2163, 1139, -2128, 1104, -2095, 1070, -2062, 1038, -2030, 1006, -2001, 976, -1971, 947, -1943, 919, -1915, 892, -1890, 866, -1864, 840, -1839, 815, -1815, 792, -1792, 769, -1770, 746, -1748, 724, -1727, 703, -1706, 682, -1687, 662, -1667, 643, -1648, 624, -1630, 606, -1612, 588, -1594, 571, -1578, 554, -1561, 537, -1545, 521, -1529, 505, -1514, 490, -1499, 475, -1484, 461, -1470, 446, -1456, 432, -1442, 419, -1429, 405, -1416, 391, -1403, 378, -1391, 366, -1378, 354, -1366, 342, -1355, 330, -1343, 319, -1332, 308, -1321, 296, -1310, 286, -1299, 275, -1289, 265, -1278, 254, -1269, 244, -1259, 234, -1248, 225, -1239, 215, -1230, 206, -1220, 196, -1211, 188, -1202, 178, -1193, 170, -1185, 161, -1176, 153, -1168, 144, -1160, 136, -1152, 128, -1144, 120, -1136, 112, -1128, 104, -1121, 96, -1113, 89, -1105, 82, -1099, 74, -1091, 67, -1084, 60, -1077, 53, -1070, 46, -1063, 39, -1057, 33, -1050, 26, -1043, 19, -1037, 13, -1030, 6, -1024, 0, -1018, -6, -1012, -12, -1006, -19, -1000, -25, -994, -31, -988, -36, -982, -43, -976, -48, -970, -54, -965, -59, -959, -65, -954, -70, -948, -76, -943, -81, -938, -87, -932, -92, -927, -97, -922, -102, -917, -107, -912, -113, -906, -118, -901, -123, -897, -128, -892, -132, -887, -138, -882, -142, -878, -147, -873, -151, -868, -156, -864, -161, -859, -165, -854, -170, -850, -175, -845, -179, -841, -183, -836, -188, -832, -192, -827, -197, -823, -201, -819, -205, -815, -209, -811, -213, -806, -218, -802, -222, -798, -226, -794, -230, -790, -234, -786, -238, -782, -243, -778, -246, -774, -251, -770, -254, -766, -258, -762, -262, -758, -266, -754, -270, -750, -274, -747, -278, -743, -281, -739, -285, -735, -289, -731, -293, -728, -296, -724, -300, -720, -304, -717, -307, -713, -311, -709, -315, -706, -318, -702, -322, -699, -325, -695, -329, -692, -332, -688, -336, -685, -339, -681, -343, -678, -346, -674, -350, -671, -353, -667, -357, -664, -360, -660, -364, -657, -367, -654, -370, -650, -374, -647, -377, -643, -381, -640, -384, -637, -387, -634, -390, -630, -394, -627, -397, -624, -400, -621, -404, -617, -407, -614, -410, -611, -414, -607, -417, -604, -420, -601, -423, -598, -427, -594, -430, -591, -433, -588, -436, -585, -439, -582, -442, -578, -445, -575, -449, -572, -452, -569, -455, -566, -458, -562, -462, -559, -465, -556, -468, -553, -471, -550, -474, -547, -478, -543, -481, -540, -484, -537, -487, -534, -490, -531, -493, -528, -496, -525, -499, -521, -503, -518, -506, -515, -509, -512, -512, -509, -515, -506, -518, -503, -521, -499, -525, -496, -528, -493, -531, -490, -534, -487, -537, -484, -540, -481, -543, -478, -547, -474, -550, -471, -553, -468, -556, -465, -559, -462, -562, -458, -566, -455, -569, -452, -572, -449, -575, -445, -578, -442, -582, -439, -585, -436, -588, -433, -591, -430, -594, -427, -598, -423, -601, -420, -604, -417, -607, -414, -611, -410, -614, -407, -617, -404, -621, -400, -624, -397, -627, -394, -630, -390, -634, -387, -637, -384, -640, -381, -643, -377, -647, -374, -650, -370, -654, -367, -657, -364, -660, -360, -664, -357, -667, -353, -671, -350, -674, -346, -678, -343, -681, -339, -685, -336, -688, -332, -692, -329, -695, -325, -699, -322, -702, -318, -706, -315, -709, -311, -713, -307, -717, -304, -720, -300, -724, -296, -728, -293, -731, -289, -735, -285, -739, -281, -743, -278, -747, -274, -750, -270, -754, -266, -758, -262, -762, -258, -766, -254, -770, -251, -774, -246, -778, -243, -782, -238, -786, -234, -790, -230, -794, -226, -798, -222, -802, -218, -806, -213, -811, -209, -815, -205, -819, -201, -823, -197, -827, -192, -832, -188, -836, -183, -841, -179, -845, -175, -850, -170, -854, -165, -859, -161, -864, -156, -868, -151, -873, -147, -878, -142, -882, -138, -887, -132, -892, -128, -897, -123, -901, -118, -906, -113, -912, -107, -917, -102, -922, -97, -927, -92, -932, -87, -938, -81, -943, -76, -948, -70, -954, -65, -959, -59, -965, -54, -970, -48, -976, -43, -982, -36, -988, -31, -994, -25, -1000, -19, -1006, -12, -1012, -6, -1018, 0, -1024, 6, -1030, 13, -1037, 19, -1043, 26, -1050, 33, -1057, 39, -1063, 46, -1070, 53, -1077, 60, -1084, 67, -1091, 74, -1099, 82, -1105, 89, -1113, 96, -1121, 104, -1128, 112, -1136, 120, -1144, 128, -1152, 136, -1160, 144, -1168, 153, -1176, 161, -1185, 170, -1193, 178, -1202, 188, -1211, 196, -1220, 206, -1230, 215, -1239, 225, -1248, 234, -1259, 244, -1269, 254, -1278, 265, -1289, 275, -1299, 286, -1310, 296, -1321, 308, -1332, 319, -1343, 330, -1355, 342, -1366, 354, -1378, 366, -1391, 378, -1403, 391, -1416, 405, -1429, 419, -1442, 432, -1456, 446, -1470, 461, -1484, 475, -1499, 490, -1514, 505, -1529, 521, -1545, 537, -1561, 554, -1578, 571, -1594, 588, -1612, 606, -1630, 624, -1648, 643, -1667, 662, -1687, 682, -1706, 703, -1727, 724, -1748, 746, -1770, 769, -1792, 792, -1815, 815, -1839, 840, -1864, 866, -1890, 892, -1915, 919, -1943, 947, -1971, 976, -2001, 1006, -2030, 1038, -2062, 1070, -2095, 1104, -2128, 1139, -2163, 1176, -2200, 1214, -2238, 1254, -2277, 1294, -2319, 1338, -2362, 1384, -2406, 1431, -2454, 1481, -2503, 1533, -2556, 1587, -2610, 1644, -2668, 1704, -2729, 1769, -2792, 1835, -2859, 1907, -2931, 1983, -3007, 2062, -3086, 2148, -3172, 2238, -3262, 2335, -3358, 2438, -3463, 2551, -3575, 2670, -3694, 2799, -3824, 2939, -3964, 3090, -4117, 3257, -4283, 3438, -4463, 3638, -4663, 3861, -4883, 4105, -5128, 4379, -5402, 4686, -5711, 5036, -6058, 5433, -6457, 5894, -6917, 6429, -7453, 7063, -8084, 7823, -8844, 8752, -9773, 9909, -10934, 11398, -12426, 13386, -14414, 16168, -17196, 20345, -21369, 27297, -28325, 41204, -42230, 82931, -83954
};

static const int real_fft_test_output_data_1024[] = {
    523776, 0, -511, 166887, -514, 83437, -515, 55627, -512, 41720, -516, 33372, -515, 27809, -515, 23835, -512, 20855, -510, 18539, -509, 16683, -509, 15164, -513, 13901, -511, 12831, -512, 11912, -511, 11117, -512, 10422, -511, 9808, -512, 9261, -511, 8774, -513, 8333, -514, 7934, -514, 7575, -514, 7243, -513, 6941, -513, 6662, -512, 6405, -512, 6168, -513, 5945, -512, 5739, -512, 5547, -512, 5369, -512, 5198, -512, 5042, -512, 4891, -512, 4749, -511, 4617, -513, 4491, -512, 4372, -512, 4259, -511, 4151, -511, 4048, -511, 3952, -511, 3857, -511, 3769, -513, 3685, -512, 3603, -512, 3526, -512, 3452, -512, 3380, -512, 3311, -513, 3246, -512, 3182, -512, 3120, -513, 3063, -512, 3006, -512, 2950, -512, 2897, -512, 2847, -512, 2797, -512, 2750, -511, 2704, -512, 2659, -512, 2616, -512, 2574, -512, 2533, -512, 2494, -512, 2456, -512, 2419, -512, 2382, -512, 2348, -512, 2313, -512, 2280, -512, 2248, -511, 2216, -511, 2186, -512, 2156, -512, 2127, -512, 2098, -512, 2071, -512, 2044, -512, 2017, -512, 1993, -512, 1967, -512, 1942, -513, 1918, -513, 1895, -513, 1872, -512, 1850, -512, 1828, -512, 1807, -512, 1786, -513, 1765, -512, 1745, -512, 1726, -512, 1708, -512, 1688, -512, 1670, -512, 1652, -512, 1633, -512, 1616, -512, 1599, -512, 1582, -511, 1566, -512, 1550, -511, 1534, -512, 1518, -511, 1503, -512, 1489, -512, 1474, -512, 1459, -512, 1445, -512, 1431, -512, 1417, -512, 1404, -512, 1390, -512, 1377, -512, 1365, -513, 1351, -512, 1340, -512, 1327, -511, 1315, -512, 1303, -512, 1292, -512, 1281, -512, 1269, -512, 1258, -512, 1247, -512, 1236, -512, 1225, -512, 1215, -512, 1205, -512, 1195, -512, 1184, -512, 1174, -512, 1164, -512, 1155, -512, 1146, -511, 1136, -512, 1127, -512, 1118, -512, 1109, -512, 1100, -512, 1091, -512, 1083, -512, 1074, -512, 1066, -512, 1058, -512, 1049, -512, 1040, -512, 1033, -512, 1025, -512, 1017, -512, 1009, -512, 1002, -512, 994, -512, 987, -512, 979, -512, 973, -512, 965, -512, 958, -512, 951, -512, 944, -512, 937, -512, 930, -512, 923, -512, 917, -512, 911, -512, 904, -512, 897, -512, 891, -512, 885, -512, 878, -512, 872, -512, 866, -512, 860, -512, 854, -512, 848, -512, 842, -512, 837, -512, 831, -512, 825, -512, 819, -512, 814, -512, 808, -512, 803, -512, 798, -512, 792, -512, 787, -512, 782, -512, 776, -512, 771, -512, 766, -512, 761, -512, 756, -512, 751, -512, 746, -512, 741, -512, 737, -512, 732, -512, 727, -512, 722, -512, 718, -512, 713, -512, 708, -512, 704, -512, 699, -512, 695, -512, 690, -512, 686, -512, 681, -512, 677, -512, 673, -512, 668, -512, 664, -512, 660, -512, 656, -512, 652, -512, 648, -512, 644, -512, 640, -512, 636, -512, 632, -512, 628, -512, 624, -512, 620, -512, 616, -512, 612, -512, 608, -512, 605, -512, 601, -512, 597, -512, 594, -512, 590, -512, 586, -512, 583, -512, 579, -512, 575, -512, 572, -512, 568, -512, 565, -512, 561, -512, 558, -512, 555, -512, 551, -512, 548, -512, 544, -512, 541, -512, 538, -512, 534, -512, 531, -512, 528, -512, 525, -512, 522, -512, 518, -512, 515, -512, 512, -512, 509, -512, 506, -512, 503, -512, 500, -512, 496, -512, 493, -512, 490, -512, 487, -512, 485, -512, 482, -512, 479, -512, 476, -512, 473, -512, 470, -512, 467, -512, 464, -512, 461, -512, 458, -512, 456, -512, 453, -512, 450, -512, 447, -512, 444, -512, 442, -512, 439, -512, 436, -512, 434, -512, 431, -512, 428, -512, 426, -512, 423, -512, 420, -512, 418, -512, 415, -512, 412, -512, 410, -512, 407, -512, 405, -512, 402, -512, 400, -512, 397, -512, 395, -512, 392, -512, 390, -512, 387, -512, 385, -512, 382, -512, 380, -512, 377, -512, 375, -512, 372, -512, 370, -512, 368, -512, 365, -512, 363, -512, 361, -512, 358, -512, 356, -512, 354, -512, 351, -512, 349, -512, 347, -512, 344, -512, 342, -512, 340, -512, 338, -512, 335, -512, 333, -512, 331, -512, 329, -512, 326, -512, 324, -512, 322, -512, 320, -512, 318, -512, 316, -512, 313, -512, 311, -512, 309, -512, 307, -512, 305, -512, 303, -512, 301, -512, 298, -512, 296, -512, 294, -512, 292, -512, 290, -512, 288, -512, 286, -512, 284, -512, 282, -512, 280, -512, 278, -512, 276, -512, 274, -512, 272, -512, 270, -512, 268, -512, 266, -512, 264, -512, 262, -512, 260, -512, 258, -512, 256, -512, 254, -512, 252, -512, 250, -512, 248, -512, 246, -512, 244, -512, 242, -512, 240, -512, 238, -512, 236, -512, 235, -512, 233, -512, 230, -512, 229, -512, 227, -512, 225, -512, 223, -512, 221, -512, 220, -512, 218, -512, 216, -512, 214, -512, 212, -512, 210, -512, 208, -512, 207, -512, 205, -512, 203, -512, 201, -512, 199, -512, 198, -512, 196, -512, 194, -512, 192, -512, 190, -512, 189, -512, 187, -512, 185, -512, 183, -512, 182, -512, 180, -512, 178, -512, 176, -512, 174, -512, 173, -512, 171, -512, 169, -512, 167, -512, 166, -512, 164, -512, 162, -512, 160, -512, 159, -512, 157, -512, 155, -512, 154, -512, 152, -512, 150, -512, 149, -512, 147, -512, 145, -512, 143, -512, 142, -512, 140, -512, 139, -512, 137, -512, 135, -512, 133, -512, 132, -512, 130, -512, 128, -512, 127, -512, 125, -512, 123, -512, 122, -512, 120, -512, 118, -512, 117, -512, 115, -512, 113, -512, 112, -512, 110, -512, 108, -512, 107, -512, 105, -512, 104, -512, 102, -512, 100, -512, 99, -512, 97, -512, 95, -512, 94, -512, 92, -512, 90, -512, 89, -512, 87, -512, 86, -512, 84, -512, 82, -512, 81, -512, 79, -512, 78, -512, 76, -512, 74, -512, 73, -512, 71, -512, 70, -512, 68, -512, 66, -512, 65, -512, 63, -512, 62, -512, 60, -512, 58, -512, 57, -512, 55, -512, 54, -512, 52, -512, 50, -512, 49, -512, 47, -512, 46, -512, 44, -512, 43, -512, 41, -512, 39, -512, 38, -512, 36, -512, 35, -512, 33, -512, 32, -512, 30, -512, 28, -512, 27, -512, 25, -512, 24, -512, 22, -512, 20, -512, 19, -512, 17, -512, 16, -512, 14, -512, 13, -512, 11, -512, 9, -512, 8, -512, 6, -512, 5, -512, 3, -512, 2, -512, 0
};

#include "jl_math/fftvec_math_drv.h"

static int test_datain[4096];// sec(.sram);
static int test_dataout[4096];// sec(.sram);
static hwfft_ctx_t test_fft_config;// sec(.sram);

static const struct {
    u32 block;
    u32 config;
} complex_tab[] = {
    { 128, COMPLEX_FFT128_CONFIG  },
    { 128, COMPLEX_IFFT128_CONFIG },
    { 256, COMPLEX_FFT256_CONFIG  },
    { 256, COMPLEX_IFFT256_CONFIG },
    { 512, COMPLEX_FFT512_CONFIG  },
    { 512, COMPLEX_IFFT512_CONFIG },
    { 1024, COMPLEX_FFT1024_CONFIG },
    { 1024, COMPLEX_IFFT1024_CONFIG},
    { 2048, COMPLEX_FFT2048_CONFIG },
    { 2048, COMPLEX_IFFT2048_CONFIG},
    { 10, COMPLEX_FFT10_CONFIG   },
    { 10, COMPLEX_IFFT10_CONFIG  },
    { 15, COMPLEX_FFT15_CONFIG   },
    { 15, COMPLEX_IFFT15_CONFIG  },
    { 20, COMPLEX_FFT20_CONFIG   },
    { 20, COMPLEX_IFFT20_CONFIG  },
    { 30, COMPLEX_FFT30_CONFIG   },
    { 30, COMPLEX_IFFT30_CONFIG  },
    { 32, COMPLEX_FFT32_CONFIG   },
    { 32, COMPLEX_IFFT32_CONFIG  },
    { 40, COMPLEX_FFT40_CONFIG   },
    { 40, COMPLEX_IFFT40_CONFIG  },
    { 60, COMPLEX_FFT60_CONFIG   },
    { 60, COMPLEX_IFFT60_CONFIG  },
    { 64, COMPLEX_FFT64_CONFIG   },
    { 64, COMPLEX_IFFT64_CONFIG  },
    { 80, COMPLEX_FFT80_CONFIG   },
    { 80, COMPLEX_IFFT80_CONFIG  },
    { 120, COMPLEX_FFT120_CONFIG  },
    { 120, COMPLEX_IFFT120_CONFIG },
    { 160, COMPLEX_FFT160_CONFIG  },
    { 160, COMPLEX_IFFT160_CONFIG },
    { 240, COMPLEX_FFT240_CONFIG  },
    { 240, COMPLEX_IFFT240_CONFIG },
    { 320, COMPLEX_FFT320_CONFIG  },
    { 320, COMPLEX_IFFT320_CONFIG },
    { 480, COMPLEX_FFT480_CONFIG  },
    { 480, COMPLEX_IFFT480_CONFIG },
    { 960, COMPLEX_FFT960_CONFIG  },
    { 960, COMPLEX_IFFT960_CONFIG },
};

static const struct {
    u32 block;
    u32 config;
} real_tab[] = {
    { 128, REAL_FFT128_CONFIG  },
    { 128, REAL_IFFT128_CONFIG },
    { 256, REAL_FFT256_CONFIG  },
    { 256, REAL_IFFT256_CONFIG },
    { 512, REAL_FFT512_CONFIG  },
    { 512, REAL_IFFT512_CONFIG },
    { 1024, REAL_FFT1024_CONFIG },
    { 1024, REAL_IFFT1024_CONFIG},
    { 2048, REAL_FFT2048_CONFIG },
    { 2048, REAL_IFFT2048_CONFIG},
    { 20, REAL_FFT20_CONFIG   },
    { 20, REAL_IFFT20_CONFIG  },
    { 30, REAL_FFT30_CONFIG   },
    { 30, REAL_IFFT30_CONFIG  },
    { 40, REAL_FFT40_CONFIG   },
    { 40, REAL_IFFT40_CONFIG  },
    { 60, REAL_FFT60_CONFIG   },
    { 60, REAL_IFFT60_CONFIG  },
    { 64, REAL_FFT64_CONFIG   },
    { 64, REAL_IFFT64_CONFIG  },
    { 80, REAL_FFT80_CONFIG   },
    { 80, REAL_IFFT80_CONFIG  },
    { 120, REAL_FFT120_CONFIG  },
    { 120, REAL_IFFT120_CONFIG },
    { 160, REAL_FFT160_CONFIG  },
    { 160, REAL_IFFT160_CONFIG },
    { 240, REAL_FFT240_CONFIG  },
    { 240, REAL_IFFT240_CONFIG },
    { 320, REAL_FFT320_CONFIG  },
    { 320, REAL_IFFT320_CONFIG },
    { 480, REAL_FFT480_CONFIG  },
    { 480, REAL_IFFT480_CONFIG },
    { 960, REAL_FFT960_CONFIG  },
    { 960, REAL_IFFT960_CONFIG },
};

___interrupt
static void fft_isr(void)
{
    if (JL_FFT->CON & BIT(7)) {

    }
}

static void hw_fft_test(void)
{
    /* request_irq(IRQ_FFT_IDX, 0, fft_isr, 0); */

    static u8 fft_test_cnt = 0;
    int *out_ptr = NULL;

    if (fft_test_cnt++ % 2) {
        out_ptr = test_datain;
    } else {
        out_ptr = test_dataout;
    }

    if (fft_test_cnt == 64) {
        fft_test_cnt = 0;
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, REAL_FFT512_CONFIG, (long *)test_datain, (long *)out_ptr);

    for (int i = 0; i < ARRAY_SIZE(real_fft_test_input_data_512); i++) {
        test_datain[i] = real_fft_test_input_data_512[i];
    }

    hwfft_fft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(real_fft_test_input_data_512) + 2; i++) {
        /* printf("%d, ", out_ptr[i]); */
        if (i % 2 == 0 && out_ptr[i] != real_fft_test_output_data_real_512[i / 2]) {
            ___trig;
            printf("fft test real fail !!!\n");
            put_buf((u8 *)out_ptr, sizeof(real_fft_test_input_data_512) + 8);
            ASSERT(0);
        } else if (i % 2 && out_ptr[i] != real_fft_test_output_data_img_512[i / 2]) {
            ___trig;
            printf("fft test img fail !!!\n");
            put_buf((u8 *)out_ptr, sizeof(real_fft_test_input_data_512) + 8);
            ASSERT(0);
        }
    }

    if (out_ptr != test_datain) {
        memset(test_datain, 0, sizeof(test_datain));
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, REAL_IFFT512_CONFIG, (long *)out_ptr, (long *)test_datain);

    hwfft_ifft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(real_fft_test_input_data_512); i++) {
        /* printf("%d, ", test_datain[i]); */
        if (test_datain[i] != real_fft_test_input_data_512[i]) {
            ___trig;
            printf("ifft test real fail !!!\n");
            put_buf((u8 *)test_datain, sizeof(real_fft_test_input_data_512));
            ASSERT(0);
        }
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, COMPLEX_FFT256_CONFIG, (long *)test_datain, (long *)out_ptr);

    for (int i = 0; i < ARRAY_SIZE(complex_fft_test_output_data_256); i++) {
        test_datain[i] = i;
    }

    hwfft_fft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(complex_fft_test_output_data_256); i++) {
        /* printf("%d, ", out_ptr[i]); */
        if (out_ptr[i] != complex_fft_test_output_data_256[i]) {
            ___trig;
            printf("fft test complex fail !!!\n");
            put_buf((u8 *)out_ptr, sizeof(complex_fft_test_output_data_256));
            ASSERT(0);
        }
    }

    if (out_ptr != test_datain) {
        memset(test_datain, 0, sizeof(test_datain));
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, COMPLEX_IFFT256_CONFIG, (long *)out_ptr, (long *)test_datain);

    hwfft_ifft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(complex_fft_test_output_data_256); i++) {
        /* printf("%d, ", test_datain[i]); */
        if (test_datain[i] != i) {
            ___trig;
            printf("ifft test complex fail !!!\n");
            put_buf((u8 *)test_datain, sizeof(complex_fft_test_output_data_256));
            ASSERT(0);
        }
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, COMPLEX_FFT512_CONFIG, (long *)test_datain, (long *)out_ptr);

    for (int i = 0; i < ARRAY_SIZE(complex_fft_test_output_data_512); i++) {
        test_datain[i] = i;
    }

    hwfft_fft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(complex_fft_test_output_data_512); i++) {
        /* printf("%d, ", out_ptr[i]); */
        if (out_ptr[i] != complex_fft_test_output_data_512[i]) {
            ___trig;
            printf("fft test complex fail !!!\n");
            put_buf((u8 *)out_ptr, sizeof(complex_fft_test_output_data_512));
            ASSERT(0);
        }
    }

    if (out_ptr != test_datain) {
        memset(test_datain, 0, sizeof(test_datain));
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, COMPLEX_IFFT512_CONFIG, (long *)out_ptr, (long *)test_datain);

    hwfft_ifft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(complex_fft_test_output_data_512); i++) {
        /* printf("%d, ", test_datain[i]); */
        if (test_datain[i] != i) {
            ___trig;
            printf("ifft test complex fail !!!\n");
            put_buf((u8 *)test_datain, sizeof(complex_fft_test_output_data_512));
            ASSERT(0);
        }
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, REAL_FFT1024_CONFIG, (long *)test_datain, (long *)out_ptr);

    for (int i = 0; i < ARRAY_SIZE(real_fft_test_output_data_1024) - 2; i++) {
        test_datain[i] = i;
    }

    hwfft_fft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(real_fft_test_output_data_1024); i++) {
        /* printf("%d, ", out_ptr[i]); */
        if (out_ptr[i] != real_fft_test_output_data_1024[i]) {
            ___trig;
            printf("fft test complex fail !!!\n");
            put_buf((u8 *)out_ptr, sizeof(real_fft_test_output_data_1024));
            ASSERT(0);
        }
    }

    if (out_ptr != test_datain) {
        memset(test_datain, 0, sizeof(test_datain));
    }

    hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, REAL_IFFT1024_CONFIG, (long *)out_ptr, (long *)test_datain);

    hwfft_ifft_i32((hwfft_ctx_t *)&test_fft_config);

    for (int i = 0; i < ARRAY_SIZE(real_fft_test_output_data_1024) - 2; i++) {
        /* printf("%d, ", test_datain[i]); */
        if (test_datain[i] != i) {
            ___trig;
            printf("ifft test complex fail !!!\n");
            put_buf((u8 *)test_datain, sizeof(real_fft_test_output_data_1024) - 2);
            ASSERT(0);
        }
    }

    //循环测试
    for (int n = 0; n < ARRAY_SIZE(real_tab); n += 2) {
        hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, real_tab[n].config, (long *)test_datain, (long *)out_ptr);

        for (int i = 0; i < real_tab[n].block; i++) {
            test_datain[i] = i * fft_test_cnt;
        }

        hwfft_fft_i32((hwfft_ctx_t *)&test_fft_config);

        if (out_ptr != test_datain) {
            memset(test_datain, 0, sizeof(test_datain));
        }

        hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, real_tab[n + 1].config, (long *)out_ptr, (long *)test_datain);

        hwfft_ifft_i32((hwfft_ctx_t *)&test_fft_config);

        for (int i = 0; i < real_tab[n + 1].block; i++) {
            /* printf("%d, ", test_datain[i]); */
            if (test_datain[i] != i * fft_test_cnt && test_datain[i] != i * fft_test_cnt + 1 && test_datain[i] != i * fft_test_cnt - 1) {
                ___trig;
                printf("real test fail n : %d, i : %d, cnt : %d !!!\n", n, i, fft_test_cnt);
                for (int i = 0; i < real_tab[n + 1].block; i++) {
                    printf("%d, ", test_datain[i]);
                }
                /* put_buf((u8 *)test_datain, real_tab[n + 1].block * 4); */
                ASSERT(0);
            }
        }
    }

    for (int n = 0; n < ARRAY_SIZE(complex_tab); n += 2) {
        hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, complex_tab[n].config, (long *)test_datain, (long *)out_ptr);

        for (int i = 0; i < complex_tab[n].block * 2; i++) {
            test_datain[i] = i * fft_test_cnt;
        }

        hwfft_fft_i32((hwfft_ctx_t *)&test_fft_config);

        if (out_ptr != test_datain) {
            memset(test_datain, 0, sizeof(test_datain));
        }

        hwfft_fill_fft_ctx((hwfft_ctx_t *)&test_fft_config, complex_tab[n + 1].config, (long *)out_ptr, (long *)test_datain);

        hwfft_ifft_i32((hwfft_ctx_t *)&test_fft_config);

        for (int i = 0; i < complex_tab[n + 1].block * 2; i++) {
            /* printf("%d, ", test_datain[i]); */
            if (test_datain[i] != i * fft_test_cnt && test_datain[i] != i * fft_test_cnt + 1 && test_datain[i] != i * fft_test_cnt - 1) {
                ___trig;
                printf("complex test fail n : %d, i : %d, cnt : %d !!!\n", n, i, 2);
                for (int i = 0; i < real_tab[n + 1].block * 2; i++) {
                    printf("%d, ", test_datain[i]);
                }
                /* put_buf((u8 *)test_datain, complex_tab[n + 1].block * 2 * 4); */
                ASSERT(0);
            }
        }
    }
}

static void fft_test_task(void *priv)
{
    while (1) {
        hw_fft_test();
    }
}

static int fft_test_init(void)
{
    return thread_fork("fft_test", 1, 256, 0, 0, fft_test_task, NULL);
}
late_initcall(fft_test_init);
#endif


#ifdef CONFIG_UI_ENABLE

static void spi_lcd_test_task(void *p)
{
    user_lcd_init();

    while (1) {
        st7735s_test();
    }
}

static int spi_lcd_test_init(void)
{
    return thread_fork("spi_lcd_test", 2, 256, 0, NULL, spi_lcd_test_task, NULL);
}
#ifdef CONFIG_FPGA_SPI_TEST_ENABLE
late_initcall(spi_lcd_test_init);
#endif

#endif


#ifdef CONFIG_FPGA_UART_TEST_ENABLE

#define UART_DMABUF_LEN  4*1024
static u8 uart_buf[UART_DMABUF_LEN] __attribute__((aligned(4))); //用于串口接收缓存数据的循环buf

static void uart_test_main(void *p)
{
    u8 recv_buf[16];
    u8 send_buf[16];
    int len;
    int cnt = 0;
    const char *str = "0123456789ABCDEF";
    void *hdl = dev_open("uart0", NULL);
    if (!hdl) {
        return;
    }
    /* 1 . 设置串口接收缓存数据的循环buf地址 */
    dev_ioctl(hdl, IOCTL_UART_SET_CIRCULAR_BUFF_ADDR, (int)uart_buf);

    /* 1 . 设置串口接收缓存数据的循环buf长度 */
    dev_ioctl(hdl, IOCTL_UART_SET_CIRCULAR_BUFF_LENTH, sizeof(uart_buf));

    /* 3 . 设置接收数据为阻塞方式,需要非阻塞可以去掉,建议加上超时设置 */
    dev_ioctl(hdl, IOCTL_UART_SET_RECV_BLOCK, 1);

    /* u32 parm = 10; */
    /* dev_ioctl(hdl, IOCTL_UART_SET_RECV_TIMEOUT, (u32)parm); //超时设置 */

    /* 4 . 使能特殊串口,启动收发数据 */
    dev_ioctl(hdl, IOCTL_UART_START, 0);

    printf("uart_test_task running");

    while (1) {
        memset(recv_buf, 0, sizeof(recv_buf));
        /* 5 . 接收数据 */
        /* len = dev_read(hdl, recv_buf, UART_DMABUF_LEN); */
        len = dev_read(hdl, recv_buf, 16);     //test rts
        if (len <= 0) {
            /* printf("\n  uart recv err len = %d\n", len); */
            if (len == UART_CIRCULAR_BUFFER_WRITE_OVERLAY) {
                printf("\n uart_circular_buffer_write_overlay err\n");
                dev_ioctl(hdl, IOCTL_UART_FLUSH, 0); //如果由于用户长期不取走接收的数据导致循环buf接收回卷覆盖,因此直接冲掉循环buf所有数据重新接收
            } else if (len == UART_RECV_TIMEOUT) {
                puts("UART_RECV_TIMEOUT...\r\n");
            }
            continue;
        }
        /* printf("\n uart recv len = %d\n", len); */
#if 0
        //把串口接收到的数据发送回去
        dev_write(hdl, recv_buf, len);
        cnt += len;
        /* printf("\n uart recv len = %d  rx_cnt = %d\n", len, cnt); */
        len = sprintf(send_buf, "Rx_Cnt = %d\n", cnt);
        //统计串口接收到的数据发送回去
        dev_write(hdl, send_buf, len);
#else
        if (len != strlen(str) || memcmp(recv_buf, str, len) != 0) {
            putchar('U');
            /* printf("uart error, recv len = %d", len); */
            /* put_buf(recv_buf, len); */
        }
#endif
    }
    dev_close(hdl);
}
static int uart_dma_rx_tx_test(void)
{
    thread_fork("uart_test", 6, 256, 0, NULL, uart_test_main, NULL);
}
late_initcall(uart_dma_rx_tx_test);

#endif


#ifdef CONFIG_FPGA_PLNK_TEST_ENABLE

static void *plnk_server;
static FILE *plnk_fp;

static void enc_server_event_handler(void *priv, int argc, int *argv)
{
    union audio_req req = {0};

    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
    case AUDIO_SERVER_EVENT_END:
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(plnk_server, AUDIO_REQ_ENC, &req);
        if (plnk_fp) {
            fclose(plnk_fp);
            plnk_fp = NULL;
        }
        server_close(plnk_server);
        plnk_server = NULL;
        break;
    default:
        break;
    }
}

static void plnk_test_main(void)
{
    union audio_req req = {0};

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
    req.enc.volume = 100;
    req.enc.frame_size = 1600;
    req.enc.output_buf_len = 1600 * 3;
    req.enc.sample_rate = 16000;
    req.enc.format = "wav";
    req.enc.sample_source = "plnk0";
    req.enc.msec = 30000;
    req.enc.file = plnk_fp = fopen(CONFIG_ROOT_PATH"plnk/rec.wav", "w+");

    plnk_server = server_open("audio_server", "enc");
    if (plnk_server) {
        server_register_event_handler_to_task(plnk_server, NULL, enc_server_event_handler, "app_core");
        server_request(plnk_server, AUDIO_REQ_ENC, &req);
    }
}

#endif


#ifdef CONFIG_FPGA_AUDIO_ADC_TEST_ENABLE

static void *audio_adc_server;
static FILE *audio_adc_fp;

static void enc_server_event_handler(void *priv, int argc, int *argv)
{
    union audio_req req = {0};

    switch (argv[0]) {
    case AUDIO_SERVER_EVENT_ERR:
    case AUDIO_SERVER_EVENT_END:
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(audio_adc_server, AUDIO_REQ_ENC, &req);
        if (audio_adc_fp) {
            fclose(audio_adc_fp);
            audio_adc_fp = NULL;
        }
        server_close(audio_adc_server);
        audio_adc_server = NULL;
        break;
    default:
        break;
    }
}

static void audio_adc_test_main(void)
{
    union audio_req req = {0};

    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
    req.enc.volume = 100;
    req.enc.frame_size = 1600;
    req.enc.output_buf_len = 1600 * 3;
    req.enc.sample_rate = 16000;
    req.enc.format = "wav";
    req.enc.sample_source = "mic";
    req.enc.msec = 30000;
    req.enc.file = audio_adc_fp = fopen(CONFIG_ROOT_PATH"mic/rec.wav", "w+");

    audio_adc_server = server_open("audio_server", "enc");
    if (audio_adc_server) {
        server_register_event_handler_to_task(audio_adc_server, NULL, enc_server_event_handler, "app_core");
        server_request(audio_adc_server, AUDIO_REQ_ENC, &req);
    }
}

#endif

static void wl83_test_task(void *p)
{
    u32 cnt = 0;

    /* os_time_dly(300); */

#if defined CONFIG_EXFLASH_ENABLE
    put_buf((void *)(__SFC1_ADDR_BEGIN__ + 0x6000), 4096);
    FILE *fp = fopen("storage/virfat_flash/C/font/ascii.res", "r");
    if (fp) {
        u8 buf[512] = {0};
        fread(buf, 1, 512, fp);
        put_buf(buf, 512);
    }
#endif

    /* void hw_iic_slave_test(const char *dev_name); */
    /* hw_iic_slave_test("iic1"); */

    while (1) {
        /* printf("cnt:%d\n", cnt++); */
#ifdef CONFIG_FPGA_DCACHE_TEST_ENABLE
        dcache_test();
#endif
#ifdef CONFIG_FPGA_ICACHE_TEST_ENABLE
        icache_test();
#endif
    }
}

static int wl83_test_init(void)
{
    return thread_fork("wl83_test", 1, 2048, 0, 0, wl83_test_task, NULL);
}
#ifdef CONFIG_FPGA_TEST_ENABLE
late_initcall(wl83_test_init);
#endif



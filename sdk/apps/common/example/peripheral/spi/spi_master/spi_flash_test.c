/********************************测试例程说明************************************
 *  功能说明：
 *      外挂25qxx进行SPI1测试
 * ******************************************************************************/

/*
 * 参考板级配置:
 * SPI1_PLATFORM_DATA_BEGIN(spi1_data)
 *     .io = {
 *         .cs_pin             = -1,
 *         .di_pin             = IO_PORTA_06,
 *         .do_pin             = IO_PORTA_05,
 *         .clk_pin            = IO_PORTA_04,
 *         .d2_pin             = -1,
 *         .d3_pin             = -1,
 *     },
 *     .clk                    = 200000,
 *     .mode                   = SPI_STD_MODE,
 *     .priority               = 6,
 *     .cpu_id                 = 1,
 *     .hd_level               = 0,
 *     .attr                   = SPI_SCLK_L_UPL_SMPH,
 *     .role                   = SPI_MODE_MASTER,
 * SPI1_PLATFORM_DATA_END()
 */

#include "app_config.h"
#include "os/os_api.h"
#include "system/includes.h"
#include "device/device.h"
#include "asm/spi.h"
#include "device/gpio.h"

#ifdef USE_SPI_FLASH_TEST_DEMO
#if 1
#define log_info(x, ...)    printf("\n\n>>>>>>[spi_test]" x " ", ## __VA_ARGS__)
#else
#define log_info(...)
#endif

#define     TEST_DATA_SIZE      (1024)

struct _25Q64_ {
    void *spi;
};

static struct _25Q64_ hdl;

#define FLASH_PAGE_SIZE 256


#define WINBOND_READ_DATA	        0x03
#define WINBOND_DUAL_READ_DATA	    0x3b
#define WINBOND_DUAL_READ	        0xbb
#define WINBOND_READ_SR1            0x05
#define DUMMY_BYTE                  0xff
#define WINBOND_CHIP_ERASE          0xC7
#define W25X_JedecDeviceID          0x9f
#define WINBOND_WRITE_ENABLE        0x06
#define WINBOND_PAGE_PROGRAM_QUAD	0x32
#define W25X_SectorErase		    0x20
#define W25X_PageProgram         	0x02



#define W25Q16 0XEF4015
#define W25Q32 0XEF4016
#define W25Q64 0XEF4017
#define W25Q128 0XEF4018
#define W25Q256 0XEF4019

static void cs_gpio(int sta)
{
    if (sta) {
        gpio_direction_output(IO_PORTA_01, 1);
    } else {
        gpio_direction_output(IO_PORTA_01, 0);
    }
}
static void spiflash_send_write_enable(void)
{
    cs_gpio(0);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, WINBOND_WRITE_ENABLE);
    cs_gpio(1);
}
static void W25X_GetChipID(void)
{
    u8 id[0x3] = {0, 0, 0};
    int id_mub = 0;
    int err;

    cs_gpio(0);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, W25X_JedecDeviceID);

    for (u8 i = 0; i < sizeof(id); i++) {
        err = dev_ioctl(hdl.spi, IOCTL_SPI_READ_BYTE, (u32)&id[i]);
        printf(">>>>>>>>>>id = 0x%x", id[i]);
        if (err) {
            log_info(">>>>>>>>>>>ERR");
            id[0] = id[1] = id[2] = 0xff;
            break;
        }
    }

    cs_gpio(1);

    id_mub = id[0] << 16 | id[1] << 8 | id[2];

    switch (id_mub) {
    case W25Q16:
        log_info("\n>>>>>flash IC is W25Q16\n");
        break;

    case W25Q32:
        log_info("\n>>>>>flash IC is W25Q32\n");
        break;

    case W25Q64:
        log_info("\n>>>>>flash IC is W25Q64\n");
        break;

    case W25Q128:
        log_info("\n>>>>>flash IC is W25Q128\n");
        break;

    case W25Q256:
        log_info("\n>>>>>flash IC is W25Q256\n");
        break;

    default:
        log_info("\n>>>>>no flash\n");
        break;
    }
}

static int spiflash_wait_ok(void)
{
    u8 state = 0;

    cs_gpio(0);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, WINBOND_READ_SR1);
    dev_ioctl(hdl.spi, IOCTL_SPI_READ_BYTE, (u32)&state);
    cs_gpio(1);
    os_time_dly(1);
    while ((state & 0x01) == 0x01) {
        cs_gpio(0);
        dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, WINBOND_READ_SR1);
        dev_ioctl(hdl.spi, IOCTL_SPI_READ_BYTE, (u32)&state);
        cs_gpio(1);
        os_time_dly(1);
    }
    return 0;
}

static void spiflash_send_addr(u32 addr)
{
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, addr >> 16);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, addr >> 8);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, addr);
}

static void SectorErase(u32 addr)
{
    spiflash_send_write_enable();
    cs_gpio(0);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, W25X_SectorErase);//擦除当前页
    spiflash_send_addr(addr) ;
    cs_gpio(1);
    spiflash_wait_ok();
}

static void write_data(u8 *buf, u32 addr, u32 len)
{
    spiflash_send_write_enable();
    cs_gpio(0);
    dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, W25X_PageProgram);//向当前页写入数据
    spiflash_send_addr(addr);
    dev_write(hdl.spi, buf, len);
    cs_gpio(1);
    spiflash_wait_ok();
}

static s32 spiflash_write(u8 *buf, u32 addr, u32 len)
{

    s32 pages = len >> 8;
    // u32 waddr = addr;

    //每次最多写入SPI_FLASH_PAGE_SIZE字节
    do {
        SectorErase(addr);

        write_data(buf, addr, FLASH_PAGE_SIZE);
        // waddr += FLASH_PAGE_SIZE;
        buf	 += FLASH_PAGE_SIZE;
    } while (pages--);

    return 0;
}

static int spiflash_read(u8 *buf, u32 addr, u16 len)
{

    int err = 0;
    cs_gpio(0);
    err = dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, WINBOND_READ_DATA);

    if (err == 0) {
        spiflash_send_addr(addr);
        dev_bulk_read(hdl.spi, buf, addr, len);
    }
    cs_gpio(1);
    return err ? -EFAULT : len;
}

//spi双线使用这个接口读
static int spiflash_dual_read(u8 *buf, u32 addr, u16 len)
{
    int err = 0;
    cs_gpio(0);
    err = dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, WINBOND_DUAL_READ_DATA);
    if (err == 0) {
        spiflash_send_addr(addr);
        dev_ioctl(hdl.spi, IOCTL_SPI_SEND_BYTE, WINBOND_DUAL_READ);
        dev_bulk_read(hdl.spi, buf, addr, len);
    }
    cs_gpio(1);
    return err ? -EFAULT : len;
}
static void spi_open(void)
{
    // int spi_mode;
    cs_gpio(1);
    os_time_dly(100);
    hdl.spi = dev_open("spi1", NULL);

    if (hdl.spi == NULL) {
        log_info(">>>>>>>>>>open_fail");
    }
}

static void spi_flash_test_task(void *arg)
{
    u8 buf[50];

    spi_open(); //打开spi设备
    /* gpio_set_hd(IO_PORTA_04, 1); //开强驱 */

    W25X_GetChipID(); //获取flashID

    for (u8 i = 1; i < 4; i++) {
        /* 写入数据  */
        memset(buf, i, sizeof(buf));
        spiflash_write(buf, 0x01, sizeof(buf));

        /* 读出数据  */
        memset(buf, 0, sizeof(buf));
        spiflash_read(buf, 0x01, sizeof(buf));
        log_info(">>>>>>>>> read_spiflash_data addr = 0x01 , len = 500");
        put_buf(buf, sizeof(buf));
    }

    dev_close(hdl.spi);

    while (1) {
        os_time_dly(100);
    }
}

static int c_main_spi_flash(void)
{
    os_task_create(spi_flash_test_task, NULL, 10, 1000, 0, "spi_flash_test_task");
    return 0;
}

late_initcall(c_main_spi_flash);

#endif // USE_SPI_FLASH_TEST_DEMO


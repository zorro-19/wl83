#include "system/init.h"
#include "device/device.h"
#include "device/iic.h"
#include "device/gpio.h"

#include "asm/cpu.h"
#include "asm/gpio.h"

#define IIC_DELAY_COUNT  iic->sw_iic_delay

#define INIT_IIC(iic) \
    do { \
        __gpio_direction_output(iic->dat_pin, 1); \
        __gpio_set_pull_down(iic->dat_pin, 0); \
        __gpio_set_pull_up(iic->dat_pin, 1); \
        __gpio_set_die(iic->dat_pin, 1); \
        __gpio_set_hd(iic->dat_pin, iic->hd_level); \
        __gpio_direction_output(iic->clk_pin, 1); \
        __gpio_set_pull_down(iic->clk_pin, 0); \
        __gpio_set_pull_up(iic->clk_pin, 1); \
        __gpio_set_die(iic->clk_pin, 1); \
        __gpio_set_hd(iic->clk_pin, iic->hd_level); \
    }while(0)

#define SCCB_SID_H(iic)    \
		do { \
            __gpio_set_pull_up(iic->dat_pin, 1); \
            __gpio_direction_output(iic->dat_pin, 1); \
		}while(0)

#define SCCB_SID_L(iic)    \
		do { \
            __gpio_set_pull_up(iic->dat_pin, 1); \
            __gpio_direction_output(iic->dat_pin, 0); \
		}while(0)

#define SCCB_SIC_H(iic)    \
		do { \
            __gpio_set_pull_up(iic->clk_pin, 1); \
            __gpio_direction_output(iic->clk_pin, 1); \
		}while(0)

#define SCCB_SIC_L(iic)    \
		do { \
            __gpio_set_pull_up(iic->clk_pin, 1); \
            __gpio_direction_output(iic->clk_pin, 0); \
		}while(0)

#define SCCB_SID_IN(iic) \
	do { \
        __gpio_direction_input(iic->dat_pin); \
	}while(0)

#define SCCB_SID_OUT(iic) \
	do { \
        __gpio_direction_output(iic->dat_pin, 0); \
	}while(0)

#define SCCB_SID_STATE(iic) \
    __gpio_read(iic->dat_pin)


/*
 ********************************************************************************
 *
 * Description : 软IIC 发送start信号
 *
 * Arguments   : iic    --iic设备
 *
 ********************************************************************************
 */
static void iic_start(const iic_software_t *iic)
{
    INIT_IIC(iic);

    SCCB_SID_H(iic);
    SCCB_SIC_H(iic);
    delay(IIC_DELAY_COUNT * 2);

    SCCB_SID_L(iic);
    delay(IIC_DELAY_COUNT);

    SCCB_SIC_L(iic);
    delay(IIC_DELAY_COUNT);
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 发送stop信号
 *
 * Arguments   : iic    --iic设备
 *
 ********************************************************************************
 */
static void iic_stop(const iic_software_t *iic)
{
    SCCB_SIC_L(iic);
    delay(IIC_DELAY_COUNT);

    SCCB_SID_L(iic);
    delay(IIC_DELAY_COUNT);

    SCCB_SIC_H(iic);
    delay(IIC_DELAY_COUNT * 2);

    SCCB_SID_H(iic);
    delay(IIC_DELAY_COUNT);
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 等待ack信号
 *
 * Arguments   : iic    --iic设备
 *
 * Returns     : 1      --超时未收到ack
 *               0      --收到了ack
 *
 ********************************************************************************
 */
static u8 iic_wait_ack(const iic_software_t *iic)
{
    int ucErrTime = 0;

    SCCB_SID_IN(iic);
    delay(IIC_DELAY_COUNT);

    SCCB_SIC_H(iic);
    delay(IIC_DELAY_COUNT);

    while (SCCB_SID_STATE(iic)) {
        if (++ucErrTime > 250) {
            iic_stop(iic);
            return 1;
        }
    }

    delay(IIC_DELAY_COUNT);

    SCCB_SIC_L(iic);
    delay(IIC_DELAY_COUNT);

    return 0;
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 发送ack信号
 *
 * Arguments   : iic    --iic设备
 *
 ********************************************************************************
 */
static void iic_ack(const iic_software_t *iic)
{
    /* SCCB_SIC_L(iic); */
    /* delay(IIC_DELAY_COUNT); */

    SCCB_SID_L(iic);
    delay(IIC_DELAY_COUNT);

    SCCB_SIC_H(iic);
    delay(IIC_DELAY_COUNT * 2);

    SCCB_SIC_L(iic);
    delay(IIC_DELAY_COUNT);
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 发送nack信号
 *
 * Arguments   : iic    --iic设备
 *
 ********************************************************************************
 */
static void iic_noack(const iic_software_t *iic)
{
    /* SCCB_SIC_L(iic); */
    /* delay(IIC_DELAY_COUNT); */

    SCCB_SID_H(iic);
    delay(IIC_DELAY_COUNT);

    SCCB_SIC_H(iic);
    delay(IIC_DELAY_COUNT * 2);

    SCCB_SIC_L(iic);
    delay(IIC_DELAY_COUNT);
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 发送1 byte数据 (不带start)
 *
 * Arguments   : iic    --iic设备
 *               m_iic  --发送的数据
 *
 * Returns     : 1      --超时未收到ack
 *               0      --收到了ack
 *
 ********************************************************************************
 */
static u8 iic_tx(const iic_software_t *iic, u8 m_iic)
{
    unsigned char j, tem;

    SCCB_SIC_L(iic);

    for (j = 0; j < 8; j++) {
        if ((m_iic << j) & 0x80) {
            SCCB_SID_H(iic);
        } else {
            SCCB_SID_L(iic);
        }
        delay(IIC_DELAY_COUNT);

        SCCB_SIC_H(iic);
        delay(IIC_DELAY_COUNT * 2);

        SCCB_SIC_L(iic);
        delay(IIC_DELAY_COUNT);
    }

    tem = iic_wait_ack(iic);

    SCCB_SID_OUT(iic);

    return tem;
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 接收1 byte数据 (不带ack)
 *
 * Arguments   : iic    --iic设备
 *
 * Returns     : read   --接收到的数据
 *
 ********************************************************************************
 */
static u8 iic_rx(const iic_software_t *iic)
{
    u8 read = 0, j;

    SCCB_SID_IN(iic);

    for (j = 8; j > 0; j--) {
        delay(IIC_DELAY_COUNT);

        SCCB_SIC_H(iic);
        delay(IIC_DELAY_COUNT);

        read = read << 1;
        if (SCCB_SID_STATE(iic)) {
            read = read + 1;
        }
        delay(IIC_DELAY_COUNT);

        SCCB_SIC_L(iic);
        delay(IIC_DELAY_COUNT);
    }

    return read;
}

static int iic_read(iic_device_t *iic, void *buf, int len)
{
    return 0;
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 发送指定长度数据，发送buf中的第一byte数据需要放置设备addr
 *
 * Arguments   : iic    --iic设备
 *               buf       --数据的buf地址
 *               len       --发送数据长度
 *
 * Returns     : 发送的数据长度
 *
 ********************************************************************************
 */
static int iic_write(iic_device_t *iic, void *buf, int len)
{
    int i;
    u8 *p = (u8 *)buf;

    iic_start(iic->hw);

    for (i = 0; i < len; i++) {
        iic_tx(iic->hw, p[i]);

        /* if (iic->nrate > 1 && ((i + 1) % iic->nrate) == 0) { */
        /* iic_stop(iic->hw); */
        /* if (i + 1 == len) { */
        /* return len; */
        /* } */
        /* delay(100); */
        /* iic_start(iic->hw); */
        /* } */
    }

    iic_stop(iic->hw);
    return len;
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 设备命令控制接口
 *
 * Arguments   : iic       --iic设备
 *               cmd       --命令
 *               arg       --参数
 *
 * Returns     :
 *
 ********************************************************************************
 */
static int iic_ioctl(iic_device_t *iic, int cmd, int arg)
{
    int ret = 0;
    iic_software_t *hw = (iic_software_t *)iic->hw;
    u8 tmp = 0;

    switch (cmd) {
    case IOCTL_IIC_SET_BAUDRATE:
        break;
    /* case IOCTL_IIC_TX_START_BIT: */
    /* iic_start(iic->hw); */
    /* break; */
    case IOCTL_IIC_TX_STOP_BIT:
        iic_stop(iic->hw);
        break;
    case IOCTL_IIC_TX_BYTE_WITH_START_BIT:
        iic_start(iic->hw);
        ret = iic_tx(iic->hw, arg);
        if (ret) {
            iic_stop(iic->hw);
        }
        delay(hw->sw_iic_byte_gap_time);
        break;
    case IOCTL_IIC_TX_BYTE:
        ret = iic_tx(iic->hw, arg);
        if (ret) {
            iic_stop(iic->hw);
        }
        delay(hw->sw_iic_byte_gap_time);
        break;
    case IOCTL_IIC_TX_BYTE_WITH_STOP_BIT:
        ret = iic_tx(iic->hw, arg);
        iic_stop(iic->hw);
        delay(hw->sw_iic_byte_gap_time);
        break;
    case IOCTL_IIC_RX_BYTE:
        tmp = iic_rx(iic->hw);
        if (arg) {
            *((u8 *)arg) = tmp;
        }
        /* iic_ack(iic->hw); */
        delay(hw->sw_iic_byte_gap_time);
        break;
    case IOCTL_IIC_RX_BYTE_WITH_STOP_BIT:
        tmp = iic_rx(iic->hw);
        if (arg) {
            *((u8 *)arg) = tmp;
        }
        iic_noack(iic->hw);
        iic_stop(iic->hw);
        delay(hw->sw_iic_byte_gap_time);
        break;
    case IOCTL_IIC_RX_BYTE_WITH_NACK:
        tmp = iic_rx(iic->hw);
        if (arg) {
            *((u8 *)arg) = tmp;
        }
        iic_noack(iic->hw);
        delay(hw->sw_iic_byte_gap_time);
        break;
    case IOCTL_IIC_RX_BYTE_WITH_ACK:
        tmp = iic_rx(iic->hw);
        if (arg) {
            *((u8 *)arg) = tmp;
        }
        iic_ack(iic->hw);
        delay(hw->sw_iic_byte_gap_time);
        break;
    /* case IOCTL_IIC_SET_NORMAT_RATE: */
    /* iic->nrate = arg + 1; */
    /* break; */
    case IOCTL_IIC_START:
        gpio_port_lock(GPIO2PORT(hw->dat_pin));
        if (GPIO2PORT(hw->dat_pin) != GPIO2PORT(hw->clk_pin)) {
            gpio_port_lock(GPIO2PORT(hw->clk_pin));
        }
        break;
    case IOCTL_IIC_STOP:
        gpio_port_unlock(GPIO2PORT(hw->dat_pin));
        if (GPIO2PORT(hw->dat_pin) != GPIO2PORT(hw->clk_pin)) {
            gpio_port_unlock(GPIO2PORT(hw->clk_pin));
        }
        break;
    default:
        return -EINVAL;
    }

    return ret;
}

/*
 ********************************************************************************
 *
 * Description : 软IIC 关闭设备
 *
 * Arguments   : iic   --iic设备
 *
 * Returns     : 关闭完成
 *
 ********************************************************************************
 */
static int iic_close(iic_device_t *iic)
{
    iic_software_t *hw = (iic_software_t *)iic->hw;

    gpio_direction_input(hw->clk_pin);
    gpio_set_pull_down(hw->clk_pin, 0);
    gpio_set_pull_up(hw->clk_pin, 0);
    gpio_set_die(hw->clk_pin, 0);

    gpio_direction_input(hw->dat_pin);
    gpio_set_pull_down(hw->dat_pin, 0);
    gpio_set_pull_up(hw->dat_pin, 0);
    gpio_set_die(hw->dat_pin, 0);

    return 0;
}

REGISTER_IIC_DEVICE(sw_iic_ops) = {
    .type   = IIC_TYPE_SW,
    .read   = iic_read,
    .write  = iic_write,
    .ioctl  = iic_ioctl,
    .close  = iic_close,
};


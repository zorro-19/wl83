#include "tuya_uart.h"
#include "tal_uart.h"
/**
 * @brief uart init
 *
 * @param[in] port refer to TY_UART_PORT_E
 * @param[in] badu refer to TY_UART_BAUD_E
 * @param[in] bits refer to TY_DATA_BIT_E
 * @param[in] parity refer to TY_PARITY_E
 * @param[in] stop refer to TY_STOPBITS_E
 * @param[in] bufsz buf size
 * @param[in] unblock block flag
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_uart_init(TY_UART_PORT_E port, TY_UART_BAUD_E badu, TY_DATA_BIT_E bits, TY_PARITY_E parity,
                         TY_STOPBITS_E stop, UINT_T bufsz, BOOL_T unblock)
{
    TAL_UART_CFG_T cfg;
    memset(&cfg, 0, sizeof(TAL_UART_CFG_T));
    cfg.base_cfg.baudrate = badu;
    cfg.base_cfg.databits = bits + 5;
    cfg.base_cfg.parity = parity;
    cfg.base_cfg.stopbits = stop;
    cfg.rx_buffer_size = bufsz;
    if (!unblock) {
        cfg.open_mode |= O_BLOCK;
    }

    return tal_uart_init(port, &cfg);
}

/**
 * @brief uart init
 *
 * @param[in] port refer to TY_UART_PORT_E
 * @param[in] badu refer to TY_UART_BAUD_E
 * @param[in] bits refer to TY_DATA_BIT_E
 * @param[in] parity refer to TY_PARITY_E
 * @param[in] stop refer to TY_STOPBITS_E
 * @param[in] bufsz buf size
 * @param[in] unblock block flag
 * @param[in] flowctl
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_uart_flowctrl_init(TY_UART_PORT_E port, TY_UART_BAUD_E badu,
                                  TY_DATA_BIT_E  bits, TY_PARITY_E parity,
                                  TY_STOPBITS_E  stop, UINT_T bufsz, BOOL_T unblock, BOOL_T flowctl)
{
    TAL_UART_CFG_T cfg;
    memset(&cfg, 0, sizeof(TAL_UART_CFG_T));
    cfg.base_cfg.baudrate = badu;
    cfg.base_cfg.databits = bits + 5;
    cfg.base_cfg.parity = parity;
    cfg.base_cfg.stopbits = stop;
    cfg.rx_buffer_size = bufsz;
    if (unblock == TRUE) {
        cfg.open_mode |= O_BLOCK;
    }

    if (flowctl == TRUE) {
        cfg.open_mode |= O_FLOW_CTRL;
    }

    return tal_uart_init(port, &cfg);
}

/**
 * @brief uart free
 *
 * @param[in] port refer to TY_UART_PORT_E
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_uart_free(TY_UART_PORT_E port)
{
    return tal_uart_deinit(port);
}

/**
 * @brief uart send data
 *
 * @param[in] port refer to TY_UART_PORT_E
 * @param[in] data send buf
 * @param[in] len send length
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
VOID ty_uart_send_data(TY_UART_PORT_E port, CONST BYTE_T *data, UINT_T len)
{
    tal_uart_write(port, data, len);
}

/**
 * @brief uart read data
 *
 * @param[in] port refer to TY_UART_PORT_E
 * @param[out] buf read buf
 * @param[in] len read length
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
UINT_T ty_uart_read_data(TY_UART_PORT_E port, BYTE_T *buf, UINT_T len)
{
    INT_T ret = tal_uart_read(port, buf, len);

    if (ret < 0) {
        ret = 0;
    }

    return (UINT_T)ret;
}

/**
 * @brief uart data size
 *
 * @param[in] port refer to TY_UART_PORT_E
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
INT_T ty_uart_read_data_size(TY_UART_PORT_E port)
{
    return tal_uart_get_rx_data_size(port);
}

#if 0
//! tuya gpio
#include "tal_gpio.h"
#include "tuya_gpio.h"

OPERATE_RET tuya_gpio_inout_set(IN CONST TY_GPIO_PORT_E port, IN CONST BOOL_T in)
{
    TUYA_GPIO_BASE_CFG_T gpio_cfg;

    gpio_cfg.mode   = in ? TUYA_GPIO_PULLUP : TUYA_GPIO_PUSH_PULL;
    gpio_cfg.direct = in ? TUYA_GPIO_INPUT  : TUYA_GPIO_OUTPUT;

    //! TODO: default
    gpio_cfg.level  = TUYA_GPIO_LEVEL_HIGH;

    return tal_gpio_init(port, &gpio_cfg);
}

OPERATE_RET tuya_gpio_inout_set_select(IN CONST TY_GPIO_PORT_E port, IN CONST BOOL_T in, IN CONST BOOL_T high)
{
    TUYA_GPIO_BASE_CFG_T gpio_cfg;

    gpio_cfg.direct = in   ? TUYA_GPIO_INPUT      : TUYA_GPIO_OUTPUT;
    gpio_cfg.mode   = in   ? TUYA_GPIO_PULLUP     : TUYA_GPIO_PUSH_PULL;
    gpio_cfg.level  = high ? TUYA_GPIO_LEVEL_HIGH : TUYA_GPIO_LEVEL_LOW;

    return tal_gpio_init(port, &gpio_cfg);
}

OPERATE_RET tuya_gpio_mode_set(IN CONST TY_GPIO_PORT_E port, IN CONST TY_GPIO_MODE_E mode)
{
    return OPRT_COM_ERROR;
}


INT_T tuya_gpio_read(IN CONST TY_GPIO_PORT_E port)
{
    TUYA_GPIO_LEVEL_E level;

    tal_gpio_read(port, &level);

    return level;
}

OPERATE_RET tuya_gpio_write(IN CONST TY_GPIO_PORT_E port, IN CONST BOOL_T high)
{
    return tal_gpio_write(port, high);
}
#endif

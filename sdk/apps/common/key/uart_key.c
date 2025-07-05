#include "key/key_driver.h"
#include "asm/uart.h"
#include "app_config.h"

extern int getbyte(char *c);

#if TCFG_UART_KEY_ENABLE

static struct key_driver_para uart_key_scan_param = {
    .scan_time        = 10,             //按键扫描频率, 单位: ms
    .last_key         = NO_KEY,         //上一次get_value按键值, 初始化为NO_KEY;
    .filter_time      = 0,              //按键消抖延时;
    .long_time        = 75,             //按键判定长按数量
    .hold_time        = (75 + 15),      //按键判定HOLD数量
    .click_delay_time = 20,             //按键被抬起后等待连击延时数量
    .key_type         = KEY_DRIVER_TYPE_UART,
};

static u8 uart_key_get_value(void)
{
    char c;
    u8 key_value;

    if (getbyte(&c) == 0) {
        return NO_KEY;
    }

    switch (c) {
    case 'm':
        key_value = KEY_MODE;
        break;
    case 'u':
        key_value = KEY_UP;
        break;
    case 'd':
        key_value = KEY_DOWN;
        break;
    case 'o':
        key_value = KEY_OK;
        break;
    case 'e':
        key_value = KEY_MENU;
        break;
    case 'p':
        key_value = KEY_POWER;
        break;
    case 'c':
        key_value = KEY_CANCLE;
        break;
    default:
        key_value = NO_KEY;
        break;
    }

    return key_value;
}

static int uart_key_init(void)
{
    return 0;
}

REGISTER_KEY_DRIVER_OPS(uart_key) = {
    .param          = &uart_key_scan_param,
    .get_value      = uart_key_get_value,
    .key_init       = uart_key_init,
};

#endif /* #if TCFG_UART_KEY_ENABLE */


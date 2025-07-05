#ifndef __ASM_EXTI_H__
#define __ASM_EXTI_H__

#include "generic/typedef.h"

/**
 * \name exti trigger edge
 * \{
 */
typedef enum {
    EDGE_POSITIVE = 0,
    EDGE_NEGATIVE,
} trigger_edge_t;
/* \} name */

/**
 * @brief 注册外部中断
 *
 * @param gpio 参考宏IO_PORTx_xx，如IO_PORTA_00
 * @param edge 触发边沿
 * @param callback_in_irq 中断回调函数
 * @param priv 中断回调函数的私有指针
 *
 * @return 非负数: 注册成功的外部中断序号  负值: 参数有误注册失败
 */
int exti_init(unsigned int gpio, trigger_edge_t edge, void (*callback_in_irq)(void *priv, unsigned int gpio), void *priv);

/**
 * @brief 卸载外部中断
 *
 * @param index 注册时返回的外部中断序号
 *
 * @return 0: 成功  负值: 失败
 */
int exti_uninit(int index);

#endif


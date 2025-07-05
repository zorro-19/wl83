#ifndef TASK_PRIORITY_H
#define TASK_PRIORITY_H

#include "os/os_api.h"

/**
 * @brief 任务创建信息
 */
struct task_info {
    const char *name;	/*!< 任务名，需要独一无二 */
    u8 prio;			/*!< 任务优先级 */
    u32 stack_size;		/*!< 任务堆栈大小，以word为单位 */
    u16 qsize;			/*!< 任务队列消息大小，以word为单位 */
    u8 *tcb_stk_q;		/*!< 静态堆栈和队列消息内存，填空则采用动态分配 */
    u8 core;			/*!< 任务绑定核，1表示任务绑定到核0，2表示任务绑定到核1，默认0值表示动态分配核 */
};

/**
 *  @brief 创建任务
 *  @param task:		任务执行函数
 *  @param p:			任务私有指针
 *  @param name:		任务名称
 *  @return 0:成功 非0:失败
 *  @note 创建的任务信息一定要注册到app_main.c的任务信息列表上
 */
int task_create(void (*task)(void *p), void *p, const char *name);

/**
 *  @brief 请求删除任务
 *  @param name:		被删除的任务名称
 *  @param post_sem:	信号量
 *  @return 0:成功 非0:失败
 *  @note 等待被删除的任务杀死
 */
int task_delete(const char *name, OS_SEM *post_sem);

/**
 *  @brief 杀死任务
 *  @param name:		被杀死的任务名称
 *  @return 0:成功 非0:失败
 *  @note 调用此函数的任务名称不能和被杀死的任务名称一样
 */
int task_kill(const char *name);

#endif

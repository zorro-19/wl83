/**
* @file ty_work_queue.c
* @brief provide work queue operate api
* @version 0.1
* @date 2010-09-09
*
* @copyright Copyright 2019-2021 Tuya Inc. All Rights Reserved.
*
*/

#include "ty_work_queue.h"
#include "tal_log.h"
#include "tal_thread.h"
#include "tal_workqueue.h"
#include "tal_workq_service.h"

STATIC WORKQUEUE_HANDLE ty_wq_hand = NULL;

/**
 * @brief init ty work queue
 *
 * @param[in] NONE
 *
 * @note This API is used for init work queue
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_work_queue_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    op_ret = tal_workq_init();
    ty_wq_hand = tal_workq_get_handle(WORKQ_SYSTEM);

    return op_ret;
}

/**
 * @brief add work to work queue
 *
 * @param[in] cb, call back of work
 * @param[in] data, parameter of call back
 *
 * @note This API is used for add work to work queue
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET ty_work_queue_add(IN CONST TY_WK_CB cb, IN CONST VOID *data)
{
    if (NULL == ty_wq_hand) {
        ty_wq_hand = tal_workq_get_handle(WORKQ_SYSTEM);
    }

    return tal_workqueue_schedule(ty_wq_hand, (TY_WK_CB)cb, (VOID *)data);
}

/**
 * @brief get current work number in work queue.
 *
 * @param[in] NONE
 *
 * @note This API is used for get the current work number in work queue.
 *
 * @return current work number in the work queue
 */
UINT_T ty_work_queue_depth(VOID)
{
    if (NULL == ty_wq_hand) {
        ty_wq_hand = tal_workq_get_handle(WORKQ_SYSTEM);
    }

    return tal_workqueue_get_num(ty_wq_hand);
}


/**
* @file com_mmod.h
* @author nzy@tuya.com
* @brief Common process - Initialization
* @version 0.1
* @date 2020-11-09
*
* @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
*
*/

#include "com_mmod.h"

#include "tkl_mutex.h"
#include "tkl_memory.h"

#include "tal_log.h"
#include "tal_mutex.h"
#include "tal_memory.h"
#include "tal_thread.h"
#include "tal_workqueue.h"
#include "tal_workq_service.h"

#define TY_MQ_POOL_STEP      (5)

typedef struct {
    WORKQUEUE_HANDLE workqueue;

    MSG_CALLBACK *mcb_pool;
    UINT16_T mcb_pool_size;
    UINT16_T mcb_num;
    MUTEX_HANDLE mutexHandle;

    MSG_CALLBACK last_cb;
} MSG_QUE_MANAGE;

STATIC MSG_QUE_MANAGE ty_msgq_hand = {0};

STATIC VOID_T __msg_cb(VOID_T *data)
{
    MESSAGE *msg = (MESSAGE *)data;
    MSG_CALLBACK msg_cb = NULL;

    if (!msg) {
        return ;
    }

    tal_mutex_lock(ty_msgq_hand.mutexHandle);
    if (msg->msgID < ty_msgq_hand.mcb_pool_size) {
        msg_cb = ty_msgq_hand.mcb_pool[msg->msgID];
    }
    tal_mutex_unlock(ty_msgq_hand.mutexHandle);

    if (msg_cb) {
        ty_msgq_hand.last_cb = msg_cb;
        msg_cb(msg);
        ty_msgq_hand.last_cb = NULL;
    } else {
        TAL_PR_NOTICE("msg_cb is null %d", msg->msgID);
    }

    tal_free(msg);
}

STATIC OPERATE_RET __msg_enqueue(IN CONST MSG_ID msgID, IN CONST P_MSG_DATA pMsgData,
                                 IN CONST MSG_DATA_LEN msgDataLen, IN BOOL_T instant, IN BOOL_T need_malloc)
{
    OPERATE_RET op_ret = OPRT_OK;
    P_MSG_DATA msg_data = pMsgData;
    MESSAGE *msg = NULL;

    tal_mutex_lock(ty_msgq_hand.mutexHandle);
    if ((msgID >= ty_msgq_hand.mcb_pool_size) || (NULL == ty_msgq_hand.mcb_pool[msgID])) {
        TAL_PR_NOTICE("cb is null %d", msgID);
        tal_mutex_unlock(ty_msgq_hand.mutexHandle);
        return OPRT_INVALID_PARM;
    }
    tal_mutex_unlock(ty_msgq_hand.mutexHandle);

    if (need_malloc) {
        msg_data = (P_MSG_DATA)tal_malloc(msgDataLen);
        if (NULL == msg_data) {
            TAL_PR_ERR("malloc failed");
            return OPRT_MALLOC_FAILED;
        } else {
            memcpy(msg_data, pMsgData, msgDataLen);
        }
    }

    msg = tal_malloc(sizeof(MESSAGE));
    if (NULL == msg) {
        TAL_PR_ERR("malloc failed");
        op_ret = OPRT_MALLOC_FAILED;
        goto EXIT;
    }

    msg->msgID = msgID;
    msg->pMsgData = msg_data;
    msg->msgDataLen = msgDataLen;

    if (instant) {
        op_ret = tal_workqueue_schedule_instant(ty_msgq_hand.workqueue, __msg_cb, msg);
    } else {
        op_ret = tal_workqueue_schedule(ty_msgq_hand.workqueue, __msg_cb, msg);
    }

EXIT:
    if (OPRT_OK != op_ret) {

        if (msg) {
            tal_free(msg);
        }

        if (need_malloc) {
            tal_free(msg_data);
        }
    }

    return op_ret;
}

STATIC BOOL_T __msg_cancel(WORK_ITEM_T *item, VOID_T *ctx)
{
    BOOL_T is_same = TRUE;
    MESSAGE *src = (MESSAGE *)item->data;
    MESSAGE *dst = (MESSAGE *)ctx;

    if (src && dst) {
        if (dst->msgID != src->msgID) {
            is_same = FALSE;
        } else {
            TAL_PR_DEBUG("cancel msgID:%d", src->msgID);
        }
    }

    if (is_same) {
        item->cb = NULL; //stop exe
    }

    return TRUE;
}

/**
 * @brief Release module handle.
 *
 * @param VOID
 *
 * @note This API is used for releasing module handle.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_release(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    return op_ret;
}

/**
 * @brief Init module handle.
 *
 * @param VOID
 *
 * @note This API is used for initializing module handle.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (ty_msgq_hand.mcb_pool) {
        return OPRT_OK;
    }

    ty_msgq_hand.mcb_num = 0;
    ty_msgq_hand.mcb_pool_size = TY_MQ_POOL_STEP;
    ty_msgq_hand.mcb_pool = (MSG_CALLBACK *)tal_calloc(ty_msgq_hand.mcb_pool_size, SIZEOF(MSG_CALLBACK *));
    if (NULL == ty_msgq_hand.mcb_pool) {
        return OPRT_MALLOC_FAILED;
    }

    op_ret = tal_mutex_create_init(&ty_msgq_hand.mutexHandle);
    if (OPRT_OK != op_ret) {
        goto EXIT;
    }

    op_ret = tal_workq_init();
    ty_msgq_hand.workqueue = tal_workq_get_handle(WORKQ_HIGHTPRI);

EXIT:
    if (OPRT_OK != op_ret) {
        if (ty_msgq_hand.mcb_pool) {
            tal_free(ty_msgq_hand.mcb_pool);
            ty_msgq_hand.mcb_pool = NULL;
        }

        if (ty_msgq_hand.mutexHandle) {
            tal_mutex_release(ty_msgq_hand.mutexHandle);
            ty_msgq_hand.mutexHandle = NULL;
        }
    }

    return op_ret;
}

/**
 * @brief Regist callback function for message.
 *
 * @param[in] msg_cb: message callback function
 * @param[out] msg_id: message id
 *
 * @note This API is used for registing message's callback function.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_reg_msgcb(IN CONST MSG_CALLBACK msg_cb, OUT MSG_ID *msg_id)
{
    if (NULL == msg_cb || NULL == msg_id) {
        return OPRT_INVALID_PARM;
    }

    if (NULL == ty_msgq_hand.mcb_pool) {
        OPERATE_RET op_ret = cmmod_init();
        if (op_ret) {
            return op_ret;
        }
    }

    tal_mutex_lock(ty_msgq_hand.mutexHandle);

    if (ty_msgq_hand.mcb_num >= ty_msgq_hand.mcb_pool_size) {
        UINT16_T new_mcb_pool_size = ty_msgq_hand.mcb_pool_size + TY_MQ_POOL_STEP;
        MSG_CALLBACK *new_mcb_pool = (MSG_CALLBACK *)tal_calloc(new_mcb_pool_size, SIZEOF(MSG_CALLBACK *));
        if (NULL == new_mcb_pool) {
            TAL_PR_ERR("tal_calloc failed");
            tal_mutex_unlock(ty_msgq_hand.mutexHandle);
            return OPRT_MALLOC_FAILED;
        } else {
            memcpy(new_mcb_pool, ty_msgq_hand.mcb_pool, ty_msgq_hand.mcb_pool_size * SIZEOF(MSG_CALLBACK *));
            tal_free(ty_msgq_hand.mcb_pool);
            ty_msgq_hand.mcb_pool = new_mcb_pool;
            ty_msgq_hand.mcb_pool_size = new_mcb_pool_size;
        }
    }

    UINT16_T i = 0;
    for (i = 0; i < ty_msgq_hand.mcb_pool_size; i++) {
        if (NULL == ty_msgq_hand.mcb_pool[i]) {
            *msg_id = i;
            ty_msgq_hand.mcb_pool[i] = msg_cb;
            ty_msgq_hand.mcb_num ++;
            break;
        }
    }

    TAL_PR_DEBUG("reg msgID:%d", i);

    tal_mutex_unlock(ty_msgq_hand.mutexHandle);

    return OPRT_OK;
}

/**
 * @brief Unregist callback function for message.
 *
 * @param[in] msgID: message id
 *
 * @note This API is used for unRegisting message's callback function.
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_unreg_msgcb(IN CONST MSG_ID msgID)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (msgID >= ty_msgq_hand.mcb_pool_size) {
        return OPRT_INVALID_PARM;
    }

    MESSAGE msg = {.msgID = msgID};

    tal_mutex_lock(ty_msgq_hand.mutexHandle);

    TAL_PR_DEBUG("unreg msgID:%d", msgID);

    tal_workqueue_traverse(ty_msgq_hand.workqueue, __msg_cancel, &msg);
    ty_msgq_hand.mcb_pool[msgID] = NULL;
    ty_msgq_hand.mcb_num--;
    tal_mutex_unlock(ty_msgq_hand.mutexHandle);

    return op_ret;
}

/**
 * @brief Post a message.
 *
 * @param[in] msgID: message id
 * @param[in] pMsgData: message data
 * @param[in] msgDataLen: message data len
 *
 * @note This API is used for posting a message
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_post_msg(IN CONST MSG_ID msgID, IN CONST P_MSG_DATA pMsgData, IN CONST MSG_DATA_LEN msgDataLen)
{
    return __msg_enqueue(msgID, pMsgData, msgDataLen, FALSE, FALSE);
}

/**
 * @brief Post a message with memory alloc
 *
 * @param[in] msgID: message id
 * @param[in] pMsgData: message data
 * @param[in] msgDataLen: message data len
 *
 * @note This API is used for posting a message with memory alloc, the param of message data can be local variable
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_post_msg_malloc(IN CONST MSG_ID msgID, IN CONST P_MSG_DATA pMsgData, IN CONST MSG_DATA_LEN msgDataLen)
{
    return __msg_enqueue(msgID, pMsgData, msgDataLen, FALSE, TRUE);
}

/**
 * @brief Post a message instantly
 *
 * @param[in] msgID: message id
 * @param[in] pMsgData: message data
 * @param[in] msgDataLen: message data len
 *
 * @note This API is used for posting a message instantly
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_post_instancy_msg(IN CONST MSG_ID msgID, IN CONST P_MSG_DATA pMsgData, IN CONST MSG_DATA_LEN msgDataLen)
{
    return __msg_enqueue(msgID, pMsgData, msgDataLen, TRUE, FALSE);
}

/**
 * @brief Post a instant message with memory alloc
 *
 * @param[in] msgID: message id
 * @param[in] pMsgData: message data
 * @param[in] msgDataLen: message data len
 *
 * @note This API is used for posting a instant message with memory alloc, the param of message data can be local variable
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_post_instancy_msg_malloc(IN CONST MSG_ID msgID, IN CONST P_MSG_DATA pMsgData, IN CONST MSG_DATA_LEN msgDataLen)
{
    return __msg_enqueue(msgID, pMsgData, msgDataLen, TRUE, TRUE);
}

STATIC VOID __tm_timer_cb(TIMER_ID timerID, PVOID_T pTimerArg)
{
    TM_MSG_S *tm_msg = (TM_MSG_S *)pTimerArg;

    __msg_enqueue(tm_msg->msgID, tm_msg, sizeof(TM_MSG_S *), FALSE, FALSE);
}

STATIC VOID __tm_msg_cb(MESSAGE *msg)
{
    TM_MSG_S *tm_msg = (TM_MSG_S *)msg->pMsgData;
    if (NULL == tm_msg) {
        TAL_PR_ERR("param invalid");
        return;
    }

    if ((msg->msgID < ty_msgq_hand.mcb_pool_size) &&
        (NULL != ty_msgq_hand.mcb_pool[msg->msgID])) {
        ty_msgq_hand.last_cb = (MSG_CALLBACK)tm_msg->cb;
        if (tm_msg->cb) {
            tm_msg->cb(tm_msg);
        } else {
            TAL_PR_NOTICE("cb is null %d", msg->msgID);
        }
        ty_msgq_hand.last_cb = NULL;
    } else {
        TAL_PR_NOTICE("cb is null %d", msg->msgID);
    }
}

/**
 * @brief Create timer message handle.
 *
 * @param[in] cb: callback function
 * @param[in] data: message data
 * @param[out] tm_msg: timer message info
 *
 * @note This API is used for creating a timer message handle
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_cr_tm_msg_hand(IN CONST TM_MSG_CB cb, IN CONST VOID *data, OUT TM_MSG_S **tm_msg)
{
    OPERATE_RET op_ret = OPRT_OK;

    MSG_ID msgID = UNVALUED_MSGID;
    op_ret = cmmod_reg_msgcb(__tm_msg_cb, &msgID);
    if (OPRT_OK != op_ret) {
        return op_ret;
    }

    TM_MSG_S *tmp_tm_msg = (TM_MSG_S *)tal_calloc(1, sizeof(TM_MSG_S));
    if (NULL == tmp_tm_msg) {
        cmmod_unreg_msgcb(msgID);
        return OPRT_MALLOC_FAILED;
    }

    tmp_tm_msg->data = (VOID *)data;
    tmp_tm_msg->msgID = msgID;
    tmp_tm_msg->cb = cb;

    op_ret = sys_add_timer(__tm_timer_cb, tmp_tm_msg, &(tmp_tm_msg->timer));
    if (OPRT_OK != op_ret) {
        cmmod_unreg_msgcb(msgID);
        tal_free(tmp_tm_msg);
    }

    *tm_msg = tmp_tm_msg;

    TAL_PR_DEBUG("create msg:%p----cb:%p data:%p msgID:%d", tmp_tm_msg, cb, data, msgID);

    return op_ret;
}

/**
 * @brief Start the timer message.
 *
 * @param[in] tm_msg: timer message info
 * @param[in] timeCycle: cycle time of the timer
 * @param[in] timer_type: timer type, cycle or once
 *
 * @note This API is used for starting the timer message
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_start_tm_msg(IN CONST TM_MSG_S *tm_msg, IN CONST TIME_MS timeCycle, IN CONST TIMER_TYPE timer_type)
{
    if (NULL == tm_msg) {
        return OPRT_INVALID_PARM;
    }

    return sys_start_timer(tm_msg->timer, timeCycle, timer_type);
}

/**
 * @brief Stop the timer message.
 *
 * @param[in] tm_msg: timer message info
 *
 * @note This API is used for stopping the timer message
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_stop_tm_msg(IN CONST TM_MSG_S *tm_msg)
{
    if (NULL == tm_msg) {
        return OPRT_INVALID_PARM;
    }

    return sys_stop_timer(tm_msg->timer);
}

/**
 * @brief Release the timer message.
 *
 * @param[in] tm_msg: timer message info
 *
 * @note This API is used for releasing the timer message
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET cmmod_release_tm_msg(IN CONST TM_MSG_S *tm_msg)
{
    OPERATE_RET op_ret = OPRT_OK;

    if ((NULL == tm_msg) || (tm_msg->msgID >= ty_msgq_hand.mcb_pool_size)) {
        return OPRT_INVALID_PARM;
    }

    TAL_PR_DEBUG("release msg:%p----cb:%p data:%p msgID:%d",
                 tm_msg, tm_msg->cb, tm_msg->data, tm_msg->msgID);

    sys_delete_timer(tm_msg->timer);
    cmmod_unreg_msgcb(tm_msg->msgID);

    tal_free((VOID_T *)tm_msg);

    return op_ret;
}

/**
 * @brief Get message node count.
 *
 * @param VOID
 *
 * @note This API is used for getting the count of message node.
 *
 * @return the count of message node.
 */
INT_T cmmod_get_msg_node_num(VOID)
{
    if (ty_msgq_hand.last_cb) {
        TAL_PR_NOTICE("last_cb %p", ty_msgq_hand.last_cb);
    }

    return tal_workqueue_get_num(ty_msgq_hand.workqueue);
}


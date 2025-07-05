/*****************************************************************************
 * osal_thread.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_THREAD_H_INCLUDE
#define OSAL_THREAD_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_thread
 * @{
 */
/*****************************************************************************
 * Included Files
 ****************************************************************************/

#if !defined(OSAL_API_H_INCLUDE)
#error "Only 'osal/osal_api.h' can be included directly."
#endif

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define C_OSAL_THREAD_NAME_SZ (16)

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/**
 * @brief Priority values.
 * - E_OSAL_PRIORITY_NONE           0
 * - E_OSAL_PRIORITY_IDLE           1
 * - E_OSAL_PRIORITY_LOW            10 ~ 19
 * - E_OSAL_PRIORITY_NORMAL         20 ~ 29
 * - E_OSAL_PRIORITY_HIGH           30 ~ 39
 */
typedef enum {
    /* No priority (not initialized). */
    E_OSAL_PRIORITY_NONE = 0,
    E_OSAL_PRIORITY_IDLE = 1,

    /* Priority low. */
    E_OSAL_PRIORITY_LOW  = 10,
    E_OSAL_PRIORITY_LOW1 = 11,
    E_OSAL_PRIORITY_LOW2 = 12,
    E_OSAL_PRIORITY_LOW3 = 13,

    /* Priority normal. */
    E_OSAL_PRIORITY_NORMAL  = 20,
    E_OSAL_PRIORITY_NORMAL1 = 21,
    E_OSAL_PRIORITY_NORMAL2 = 22,
    E_OSAL_PRIORITY_NORMAL3 = 23,

    /* Priority high. */
    E_OSAL_PRIORITY_HIGH  = 30,
    E_OSAL_PRIORITY_HIGH1 = 31,
    E_OSAL_PRIORITY_HIGH2 = 32,
    E_OSAL_PRIORITY_HIGH3 = 33,
} osal_priority_t;

/**
 * @brief Mutex object.
 */
typedef struct osal_mtx *osal_mtx_ref_t;

/**
 * @brief Sem object.
 */
typedef struct osal_sem *osal_sem_ref_t;

/**
 * @brief Entry point of a thread.
 */
typedef void (*osal_thr_fn_t)(void *);

/**
 * @brief Thread object.
 */
typedef struct osal_thr *osal_thr_ref_t;

/**
 * @brief Message queue object.
 */
typedef struct osal_mq *osal_mq_ref_t;

/**
 * @brief Wait queue run before wait callback function.
 *
 * @param[in]  waitor - To Match waitor, see @ref osal_waitq_wait.
 *
 * @param[in]  ud  - The user data, see @ref osal_waitq_create, ud.
 *
 * @return 0: success, others:failed.
 */
typedef int (*osal_waitq_prewait_fn_t)(void *waitor, void *ud);

/**
 * @brief Wait queue run to match callback function.
 *
 * @param[in]  waitor  - To Match waitor, see @ref osal_waitq_wait.
 *
 * @param[in]  tomatch - To Match item, see @ref osal_waitq_wakeup.
 *
 * @param[in]  ud  - The user data, see @ref osal_waitq_create, ud.
 *
 * @return true: match, false: unmatch.
 */
typedef bool (*osal_waitq_match_fn_t)(void *waitor, void *tomatch, void *ud);

/**
 * @brief Wait queue object.
 */
typedef struct osal_waitq *osal_waitq_ref_t;

/**
 * @brief Fsm event action function.
 */
typedef void (*osal_fsm_event_fn_t)(void *arg);

/**
 * @brief Fsm event state table entry.
 */
typedef struct osal_fsm_event {
    /** current state */
    int current_state;

    /** trigger event */
    int trigger_ev;

    /** next state */
    int next_state;

    /** ev handler */
    osal_fsm_event_fn_t do_action;
} osal_fsm_event_t;

/**
 * @brief Fsm object.
 */
typedef struct osal_fsm *osal_fsm_ref_t;

/*****************************************************************************
 * Public Data
 ****************************************************************************/

/*****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * @brief Create and initialize a mutex object.
 *
 * @param[out]  mtxp - The pointer of mutex object.
 *
 * @param[in]   name - Mutex object name.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_mtx_create(osal_mtx_ref_t *mtxp, const char *name);

/**
 * @brief Delete a Mutex object.
 *
 * @param[in] mtx - Mutex ID obtained by @ref osal_mtx_create.
 */
void osal_mtx_delete(osal_mtx_ref_t mtx);

/**
 * @brief Lock the given mutex.
 *
 * Recursive entry is not supported; attempts to do so will result in
 * undefined behavior.
 *
 * @param[in] mtx - Mutex object obtained by @ref osal_mtx_create.
 */
void osal_mtx_lock(osal_mtx_ref_t mtx);

/**
 * @brief Unlock the given mutex.
 *
 * The mutex must be owned by the calling thread.
 *
 * @param[in] mtx - Mutex ID obtained by @ref osal_mtx_create.
 */
void osal_mtx_unlock(osal_mtx_ref_t mtx);

/**
 * @brief Create and initialize a sem object.
 *
 * @param[out] semp - The pointer of sem object.
 *
 * @param[in]  name - Sem object name.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_sem_create(osal_sem_ref_t *semp,
                    const char     *name,
                    uint32_t        initvalue);

/**
 * @brief Delete a sem object.
 *
 * @param[in] sem - sem ID obtained by @ref osal_sem_create.
 */
void osal_sem_delete(osal_sem_ref_t sem);

/**
 * @brief Post a sem object.
 *
 * @param[in] sem - sem ID obtained by @ref osal_sem_create.
 */
void osal_sem_post(osal_sem_ref_t sem);

/**
 * @brief Wait a sem object.
 *
 * @param[in] sem - sem ID obtained by @ref osal_sem_create.
 */
void osal_sem_wait(osal_sem_ref_t sem);

/**
 * @brief Try wait a sem object.
 *
 * @param[in] sem - sem ID obtained by @ref osal_sem_create.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_sem_trywait(osal_sem_ref_t sem);

/**
 * @brief Timed wait a sem object.
 *
 * @param[in] sem     - sem ID obtained by @ref osal_sem_create.
 *
 * @param[in] timeout - Wait until abs time(ms).
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_sem_timedwait(osal_sem_ref_t sem, uint64_t timeout);

/**
 * @brief Create a thread and add it to Active Threads.
 *
 * @param[out] thrp - The pointer of thread object.
 *
 * @param[in]  name - Thread object name.
 *
 * @param[in]  fn   - The entry thread function.
 *
 * @param[in]  arg  - The arg of thread function.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_thr_create(osal_thr_ref_t *thrp,
                    const char     *name,
                    osal_thr_fn_t   fn,
                    void           *arg);

/**
 * @brief Delete a thread object.
 *
 * @param[in] thr - Thread object obtained by @ref osal_thr_create.
 */
void osal_thr_delete(osal_thr_ref_t thr);

/**
 * @brief Check the caller is the samed thread.
 *
 * @return true if the caller is the samed thread.
 */
bool osal_thr_is_self(osal_thr_ref_t thr);

/**
 * @brief Create a Async Task and Internally released resources.
 *
 * @param[in]  name - Thread object name.
 *
 * @param[in]  fn   - The entry thread function.
 *
 * @param[in]  arg  - The arg of thread function.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_thr_dowork(const char *name, osal_thr_fn_t fn, void *arg);

/**
 * @brief Create and Initialize a Message Queue object.
 *
 * @param[out] mqp  - The pointer of mq object.
 *
 * @param[in]  name - Message Queue name.
 *
 * @param[in]  cap  - Maximum number of messages in queue.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_mq_create(osal_mq_ref_t *mqp, const char *name, size_t cap);

/**
 * @brief Delete a Message Queue object.
 *
 * @param[in] mq - Mq object obtained by @ref osal_mq_create.
 */
void osal_mq_delete(osal_mq_ref_t mq);

/**
 * @brief Put a Message into a Queue or if Queue is full.
 *
 * @param[in] mq      - Mq object obtained by @ref osal_mq_create.
 *
 * @param[in] msgptr  - Pointer to buffer with message to put into a queue.
 *
 * @param[in] msgprio - Message priority.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_mq_put(osal_mq_ref_t mq, const void *msg, osal_priority_t prio);

/**
 * @brief Get a Message from a Queue or timeout if Queue is empty.
 *
 * @param[in]  mq      - Mq object obtained by @ref osal_mq_create.
 *
 * @param[in]  msg     - The Pointer Pointer of message to get from a queue.
 *
 * @param[out] prio    - The Pointer of message priority or NULL.
 *
 * @param[in]  timeout - Absolute time in millisecond or 0 no time-out.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_mq_get(osal_mq_ref_t    mq,
                void           **msg,
                osal_priority_t *prio,
                uint64_t         timeout);

/**
 * @brief The count of message in queue.
 *
 * @param[in] mq - Mq object obtained by @ref osal_mq_create.
 *
 * @return The count of message in queue.
 */
size_t osal_mq_count(osal_mq_ref_t mq);

/**
 * @brief The maxmsg of message queue.
 *
 * @param[in] mq - Mq object obtained by @ref osal_mq_create.
 *
 * @return The cap of message queue.
 */
size_t osal_mq_capacity(osal_mq_ref_t mq);

/**
 * @brief Create and Initialize a Wait Queue object.
 *
 * @param[out] waitqp      - The pointer of waitq object.
 *
 * @param[in]  name        - Wait Queue name.
 *
 * @param[in]  cap         - Maximum number of waitor in queue.
 *
 * @param[in]  prewait_fn  - Prewait callback.
 *
 * @param[in]  match_fn    - To match waitor callback.
 *
 * @param[in]  ud          - user data for callback.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_waitq_create(osal_waitq_ref_t       *waitqp,
                      const char             *name,
                      size_t                  cap,
                      osal_waitq_prewait_fn_t prewait_fn,
                      osal_waitq_match_fn_t   match_fn,
                      void                   *ud);

/**
 * @brief Delete a Wait Queue object.
 *
 * @param[in] waitq - Wait Queue ID obtained by @ref osal_waitq_create.
 *
 * @return status code that indicates the execution status of the function.
 */
void osal_waitq_delete(osal_waitq_ref_t waitq);

/**
 * @brief Add a waiter to queue and wait match done.
 *
 * @param[in]  waitq   - Wait Queue by @ref osal_waitq_create.
 *
 * @param[in]  waitor  - To waitor item.
 *
 * @param[in]  timeout - Absolute time in millisecond.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_waitq_wait(osal_waitq_ref_t waitq, void *waitor, uint64_t timeout);

/**
 * @brief Try match rsp and wakeup corresponding waitor.
 *
 * @param[in]  waitq    - Wait Queue by @ref osal_waitq_create.
 *
 * @param[out] tomatch  - To Match waitor.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_waitq_wakeup(osal_waitq_ref_t waitq, void *tomatch);

/*
 * wiki
 * ====
 * @page osal_fsm FSM (Finite State Machine) API
 *
 *      +------+     event1    +------+
 *      |state1| ------------> |state2|
 *      +------+ <------------ +------+
 *        |  ^       event2      |  ^
 *  event3|  |event4             |  |
 *        v  |                   |  |
 *      +------+     event5      |  | event6
 *      |state3|<----------------+  |
 *      +------+--------------------+
 *
 * Code sample:
 *
 * @code
 * osal_fsm_ref_t fsm;
 *
 * const struct osal_fsm_event fsm_ev_table[] = {
 *     { state1, event1, state2, do_state1_ev1_action },
 *     { state1, event3, state3, do_satet1_ev3_action },
 *     { state2, event2, state1, do_satet2_ev2_action },
 *     { state2, event3, state3, do_satet2_ev3_action },
 *     { state3, event4, state1, do_satet3_ev4_action },
 *     { state3, event6, state2, do_satet3_ev6_action },
 * };
 * OSAL_ASSERT(osal_fsm_create(&fsm, fsm_ev_table, OSAL_ARRAY_SIZE(fsm_ev_table), state1) != 0);
 *
 * //state1, trigger event1 -> state2
 * osal_fsm_action(fsm, event1, NULL);
 *
 * @endcode
 */
/**
 * @brief Create and initialize a fsm object.
 *
 * @param[out] fsmp     - The pointer of fsm object.
 *
 * @param[in]  name     - Fsm name.
 *
 * @param[in]  table    - The pointer of fsm event table.
 *
 * @param[in]  tablenum - The number of fsm event table.
 *
 * @param[in]  curstate - The current of fsm state.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_fsm_create(osal_fsm_ref_t        *fsmp,
                    const char            *name,
                    struct osal_fsm_event *table,
                    size_t                 tablenum,
                    int                    curstate);

/**
 * @brief Delete a fsm object.
 *
 * @param[in] fsm - Fsm ID obtained by @ref osal_fsm_create.
 */
void osal_fsm_delete(osal_fsm_ref_t fsm);

/**
 * @brief Get fsm current state.
 *
 * @param[in]  fsm      - The pointer of fsm object.
 *
 * @param[out] curstate - The current of fsm state.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_fsm_curstate(osal_fsm_ref_t fsm, int *curstate);

/**
 * @brief Trigger event to a fsm object.
 *
 * @param[in] fsm - Fsm ID obtained by @ref osal_fsm_create.
 *
 * @param[in] ev  - Trigger event id.
 *
 * @param[in] arg - Param for do_action, see @ref osal_fsm_ev_fn_t.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_fsm_action(osal_fsm_ref_t fsm, int ev, void *arg);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************
 * @} (end addtogroup osal_thread)
 */
/****************************************************************************/
#endif /* OSAL_THREAD_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

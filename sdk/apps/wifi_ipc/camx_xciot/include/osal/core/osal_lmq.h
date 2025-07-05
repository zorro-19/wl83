/*****************************************************************************
 * osal_lmq.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_LMQ_H_INCLUDE
#define OSAL_LMQ_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_lmq
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

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/* Message queue */
typedef struct osal_lmq *osal_lmq_ref_t;

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

#if 1
/**
 * @brief Create and initialize a message queue object.
 *
 * @param[out] lmqp - Message Queue object for reference by other functions.
 *
 * @param[in]  cap  - Maximum number of messages in queue.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_lmq_create(osal_lmq_ref_t *lmqp, const char *name, size_t cap);

/**
 * @brief Delete a Message Queue object.
 *
 * @param[in] lmq Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @return status code that indicates the execution status of the function.
 */
void osal_lmq_delete(osal_lmq_ref_t lmq);

/**
 * @brief The count of message in queue.
 *
 * @param[in] lmq Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @return The count of message in queue.
 */
size_t osal_lmq_count(osal_lmq_ref_t lmq);

/**
 * @brief The cap of message queue.
 *
 * @param[in] lmq Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @return The cap of message queue.
 */
size_t osal_lmq_cap(osal_lmq_ref_t lmq);

/**
 * @brief Put a Message into a Queue of head.
 *
 * @param[in] lmq   - Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @param[in] data  - Pointer to buffer with message to put into a queue.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_lmq_put_head(osal_lmq_ref_t lmq, void *data);

/**
 * @brief Put a Message into a Queue of tail.
 *
 * @param[in] lmq   - Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @param[in] data  - Pointer to buffer with message to put into a queue.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_lmq_put_tail(osal_lmq_ref_t lmq, void *data);

/**
 * @brief Get a Message from a Queue of head.
 *
 * @param[in] lmq   - Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @return The pointer of message data.
 */
void *osal_lmq_get_head(osal_lmq_ref_t lmq);

/**
 * @brief Get a Message from a Queue of tail.
 *
 * @param[in] lmq   - Message Queue ID obtained by @ref osal_lmq_create.
 *
 * @return The pointer of message data.
 */
void *osal_lmq_get_tail(osal_lmq_ref_t lmq);
#endif

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************
 * @} (end addtogroup osal_lmq)
 */
/****************************************************************************/
#endif /* OSAL_LMQ_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

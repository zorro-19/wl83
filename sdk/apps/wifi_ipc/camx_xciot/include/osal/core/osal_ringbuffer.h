/*****************************************************************************
 * osal_ringbuffer.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_RINGBUFFER_H_INCLUDE
#define OSAL_RINGBUFFER_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_ringbuffer
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

struct osal_ringbuffer {
    void *buffer;
    int    length;
    size_t start;
    size_t end;
};

typedef struct osal_rb *osal_rb_ref_t;

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
int    osal_ringbuffer_init(struct osal_ringbuffer *rb, int len);
void   osal_ringbuffer_fini(struct osal_ringbuffer *rb);
void   osal_ringbuffer_reset(struct osal_ringbuffer *rb);
size_t osal_ringbuffer_spacefree(struct osal_ringbuffer *rb);
size_t osal_ringbuffer_spaceused(struct osal_ringbuffer *rb);
size_t osal_ringbuffer_write(struct osal_ringbuffer *rb,
                             const void             *buf,
                             size_t                  len);
size_t
osal_ringbuffer_read(struct osal_ringbuffer *rb, void *buf, size_t len);
#endif

#if 1
int    osal_rb_create(osal_rb_ref_t *rbp, size_t size);
void   osal_rb_delete(osal_rb_ref_t rb);
void   osal_rb_reset(osal_rb_ref_t rb);
size_t osal_rb_spacefree(osal_rb_ref_t rb);
size_t osal_rb_spaceused(osal_rb_ref_t rb);
size_t osal_rb_write(osal_rb_ref_t rb, const void *buf, size_t len);
size_t osal_rb_read(osal_rb_ref_t rb, void *buf, size_t len);
#endif

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************
 * @} (end addtogroup osal_ringbuffer)
 */
/****************************************************************************/
#endif /* OSAL_RINGBUFFER_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

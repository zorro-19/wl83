/*****************************************************************************
 * osal_mbuf.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_MBUF_H_INCLUDE
#define OSAL_MBUF_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_mbuf
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

#define OSAL_MBUF_TRIM
#define OSAL_MBUF_CHOP
#define OSAL_MBUF_APPEND
#define OSAL_MBUF_INSERT

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/* Message buffer */
struct osal_mbuf {
    /** allocated size */
    size_t cap;

    /** length in use */
    size_t len;

    /** underlying buffer */
    uint8_t *buffer;

    /** pointer to actual data */
    uint8_t *data;
};

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

int osal_mbuf_grow(struct osal_mbuf *mbuf, size_t newsz, size_t headwanted);
int osal_mbuf_dup(struct osal_mbuf *dst, const struct osal_mbuf *src);

void osal_mbuf_free(struct osal_mbuf *mbuf);
void osal_mbuf_clear(struct osal_mbuf *mbuf);

size_t   osal_mbuf_len(struct osal_mbuf *mbuf);
size_t   osal_mbuf_cap(struct osal_mbuf *mbuf);
uint8_t *osal_mbuf_buffer(struct osal_mbuf *mbuf);
uint8_t *osal_mbuf_data(struct osal_mbuf *mbuf);

#ifdef OSAL_MBUF_TRIM
/* osal_mbuf_trim removes bytes from the beginning of the mbuf. */
int osal_mbuf_trim(struct osal_mbuf *mbuf, size_t len);
int osal_mbuf_trim_u8(struct osal_mbuf *mbuf, uint8_t *val);
int osal_mbuf_trim_le16(struct osal_mbuf *mbuf, uint16_t *val);
int osal_mbuf_trim_be16(struct osal_mbuf *mbuf, uint16_t *val);
int osal_mbuf_trim_le32(struct osal_mbuf *mbuf, uint32_t *val);
int osal_mbuf_trim_be32(struct osal_mbuf *mbuf, uint32_t *val);
int osal_mbuf_trim_le64(struct osal_mbuf *mbuf, uint64_t *val);
int osal_mbuf_trim_be64(struct osal_mbuf *mbuf, uint64_t *val);
int osal_mbuf_trim_varint(struct osal_mbuf *mbuf, uint64_t *val);
#endif /* OSAL_MBUF_TRIM */

#ifdef OSAL_MBUF_CHOP
/* osal_mbuf_chop truncates bytes from the end of the mbuf. */
int osal_mbuf_chop(struct osal_mbuf *mbuf, size_t len);
int osal_mbuf_chop_u8(struct osal_mbuf *mbuf, uint8_t *val);
int osal_mbuf_chop_le16(struct osal_mbuf *mbuf, uint16_t *val);
int osal_mbuf_chop_be16(struct osal_mbuf *mbuf, uint16_t *val);
int osal_mbuf_chop_le32(struct osal_mbuf *mbuf, uint32_t *val);
int osal_mbuf_chop_be32(struct osal_mbuf *mbuf, uint32_t *val);
int osal_mbuf_chop_le64(struct osal_mbuf *mbuf, uint64_t *val);
int osal_mbuf_chop_be64(struct osal_mbuf *mbuf, uint64_t *val);
#endif /* OSAL_MBUF_CHOP */

#ifdef OSAL_MBUF_APPEND
/*
 * osal_mbuf_append appends the data to the mbuf, growing as necessary.
 * If the data pointer is NULL, then the mbuf data region is allocated,
 * but uninitialized.
 */
int osal_mbuf_append(struct osal_mbuf *mbuf, const void *data, size_t len);
int osal_mbuf_append_u8(struct osal_mbuf *mbuf, uint8_t v);
int osal_mbuf_append_le16(struct osal_mbuf *mbuf, uint16_t v);
int osal_mbuf_append_be16(struct osal_mbuf *mbuf, uint16_t v);
int osal_mbuf_append_le32(struct osal_mbuf *mbuf, uint32_t v);
int osal_mbuf_append_be32(struct osal_mbuf *mbuf, uint32_t v);
int osal_mbuf_append_le64(struct osal_mbuf *mbuf, uint64_t v);
int osal_mbuf_append_be64(struct osal_mbuf *mbuf, uint64_t v);
int osal_mbuf_append_varint(struct osal_mbuf *mbuf, uint64_t v);
#endif /* OSAL_MBUF_APPEND */

#ifdef OSAL_MBUF_INSERT
/*
 * osal_mbuf_insert prepends data to the mbuf, as efficiently as possible.
 * If the data pointer is NULL, then no data is actually copied, but the
 * data region will have "grown" in the beginning, with uninitialized data.
 */
int osal_mbuf_insert(struct osal_mbuf *mbuf, const void *data, size_t len);
int osal_mbuf_insert_u8(struct osal_mbuf *mbuf, uint8_t v);
int osal_mbuf_insert_le16(struct osal_mbuf *mbuf, uint16_t v);
int osal_mbuf_insert_be16(struct osal_mbuf *mbuf, uint16_t v);
int osal_mbuf_insert_le32(struct osal_mbuf *mbuf, uint32_t v);
int osal_mbuf_insert_be32(struct osal_mbuf *mbuf, uint32_t v);
int osal_mbuf_insert_le64(struct osal_mbuf *mbuf, uint64_t v);
int osal_mbuf_insert_be64(struct osal_mbuf *mbuf, uint64_t v);
int osal_mbuf_insert_varint(struct osal_mbuf *mbuf, uint64_t v);
#endif /* OSAL_MBUF_INSERT */

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************
 * @} (end addtogroup osal_mbuf)
 */
/****************************************************************************/
#endif /* OSAL_MBUF_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

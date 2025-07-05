/*****************************************************************************
 * osal_mempool.h
 *
 * Copyright (C) 2019 wanshijie wanshijie@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_MEMPOOL_H_INCLUDE
#define OSAL_MEMPOOL_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_mempool
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

/**
 * @brief mempool object.
 */
typedef struct osal_mempool *osal_mempool_ref_t;

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
 * @brief Create and initialize a mempool object.
 *
 * @param[out] mpp         - The pointer of mempool object.
 *
 * @param[in]  name        - Mempool object name.
 *
 * @param[in]  block_count - The count of blocks in memory pool.
 *
 * @param[in]  block_size  - The size for each block.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_mempool_create(osal_mempool_ref_t *mpp,
                        const char         *name,
                        size_t              block_count,
                        size_t              block_size);
/**
 * @brief Delete a mempool object.
 *
 * @param[in] mp - Mempool object obtained by @ref osal_mempool_create.
 */
void osal_mempool_delete(osal_mempool_ref_t mp);

/**
 * @brief Allocate a block from memory pool.
 *
 * @param[in] mp - Mempool object obtained by @ref osal_mempool_create.
 *
 * @return the allocated memory block or NULL on allocated failed.
 */
void *osal_mempool_alloc(osal_mempool_ref_t mp);

/**
 * @brief Release a memory block to memory pool.
 *
 * @param[in] mp    - Mempool object obtained by @ref osal_mempool_create.
 *
 * @param[in] block - The address of memory block to be released.
 */
void osal_mempool_free(osal_mempool_ref_t mp, void *block);

/**
 * @brief Stringfy memory pool stat.
 *
 * @param[in] mp  - Mempool object obtained by @ref osal_mempool_create.
 *
 * @param[in] buf - Dump string buffer.
 *
 * @param[in] len - The length of buffer.
 *
 * @return The Human readable of memory pool stat.
 */
const char *
osal_mempool_stringfystat(osal_mempool_ref_t mp, char *buf, size_t len);

/**
 * @brief Dump memory pool.
 *
 * @param[in] mp     - Mempool object obtained by @ref osal_mempool_create.
 *
 * @param[in] prefix - Dump prefix string.
 */
void osal_mempool_dump(osal_mempool_ref_t mp, const char *prefix);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_mempool)
 */
/****************************************************************************/
#endif /* OSAL_MEMPOOL_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

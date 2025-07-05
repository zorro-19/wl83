/*****************************************************************************
 * osal_mem.h
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
#ifndef OSAL_MEM_H_INCLUDE
#define OSAL_MEM_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_mem
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

//#define OSAL_MEM_TRACE

/*****************************************************************************
 * Public Types
 ****************************************************************************/

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

#ifdef OSAL_MEM_TRACE
void *osal_mem_alloc_trace(uint32_t size, const char *func, int line);
void *osal_mem_zalloc_trace(size_t sz, const char *func, int line);
void *
osal_mem_realloc_trace(void *mem, size_t newsz, const char *func, int line);
void osal_mem_free_trace(void *mem, const char *func, int line);

#define osal_mem_alloc(size)                                                 \
    osal_mem_alloc_trace(size, OSAL_STRFUNC, __LINE__)
#define osal_mem_zalloc(size)                                                \
    osal_mem_zalloc_trace(size, OSAL_STRFUNC, __LINE__)
#define osal_mem_realloc(mem, size)                                          \
    osal_mem_realloc_trace(mem, size, OSAL_STRFUNC, __LINE__)
#define osal_mem_free(mem) osal_mem_free_trace(mem, OSAL_STRFUNC, __LINE__)
#else
/**
 * @brief Allocate a memory.
 *
 * @param[in] sz The length of bytes.
 *
 * @return The pointer of mem or NULL in case of error.
 */
void *osal_mem_alloc(size_t sz);

/**
 * @brief Allocate a memory, but ensures that memory is initialized to zero.
 *
 * @param[in] sz The length of bytes.
 *
 * @return The pointer of mem or NULL in case of error.
 */
void *osal_mem_zalloc(size_t sz);

/**
 * @brief Realloc a memory.
 *
 * @param[in] mem The pointer of old mem.
 *
 * @param[in] newsz The length of bytes.
 *
 * @return The pointer of newmem or NULL in case of error.
 */
void *osal_mem_realloc(void *mem, size_t newsz);

/**
 * @brief Free a memory.
 *
 * @param[in] mem Pointer of mem to free.
 */
void osal_mem_free(void *mem);
#endif
/* Structure allocation conveniences. */
#define OSAL_ALLOC_STRUCT(s) osal_mem_zalloc(sizeof(*s))
#define OSAL_FREE_STRUCT(s) osal_mem_free((s))
#define OSAL_ALLOC_STRUCTS(s, n) osal_mem_zalloc(sizeof(*s) * n)
#define OSAL_FREE_STRUCTS(s) osal_mem_free((s))

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_mem)
 */
/****************************************************************************/
#endif /* OSAL_MEM_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

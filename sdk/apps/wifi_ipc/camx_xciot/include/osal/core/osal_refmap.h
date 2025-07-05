/*****************************************************************************
 * osal_refmap.h
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
#ifndef OSAL_REFMAP_H_INCLUDE
#define OSAL_REFMAP_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_refmap
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
 * @brief Refmap object.
 */
typedef struct osal_refmap *osal_refmap_ref_t;

typedef enum osal_refmap_type {
    /* 1 - 0xFF for osal core */
    E_OSAL_REFMAP_TYPE_MTX   = 0x1,
    E_OSAL_REFMAP_TYPE_SEM   = 0x2,
    E_OSAL_REFMAP_TYPE_THR   = 0x3,
    E_OSAL_REFMAP_TYPE_MQ    = 0x4,
    E_OSAL_REFMAP_TYPE_WAITQ = 0x5,

    /* 0x100 ~ 0x1FF for app */
    E_OSAL_REFMAP_TYPE_APP = 0x100,

    /* add above here */
    E_OSAL_REFMAP_TYPE_LAST
} osal_refmap_type_t;

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
 * @brief Create and initialize a refmap object.
 *
 * @param[out] refmapp - The pointer of refmap object.
 *
 * @param[in]  name    - Refmap object name.
 *
 * @param[in]  cap     - Maximum number of ref in refmap.
 *
 * @param[in]  sz      - The size of ref mem.
 *
 * @param[in]  type    - The type of refmap, see @ref osal_refmap_type_t.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_refmap_create(osal_refmap_ref_t *refmapp,
                       const char        *name,
                       size_t             cap,
                       size_t             sz,
                       int                type);

/**
 * @brief Delete a refmap object.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 */
void osal_refmap_delete(osal_refmap_ref_t refmap);

/**
 * @brief Allocate a ref from refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @param[in]  name  - Ref object name.
 *
 * @return the allocated memory block or NULL on allocated failed.
 */
void *osal_refmap_alloc_ref(osal_refmap_ref_t refmap, const char *refname);

/**
 * @brief Release a ref to refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @param[in] ref    - The address of ref to be released.
 */
void osal_refmap_free_ref(osal_refmap_ref_t refmap, void *ref);

/**
 * @brief Find a ref in refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @param[in] ref    - The address of ref to be check.
 *
 * @return The index of refmap, 0~cap: success, -1: failed.
 */
int osal_refmap_find_ref(osal_refmap_ref_t refmap, void *ref);

/**
 * @brief The name of ref in refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @return The name of ref in refmap.
 */
const char *osal_refmap_name(osal_refmap_ref_t refmap);

/**
 * @brief The cap of ref in refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @return The cap of ref in refmap.
 */
size_t osal_refmap_cap(osal_refmap_ref_t refmap);

/**
 * @brief The count of ref in refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @return The count of ref in refmap.
 */
size_t osal_refmap_count(osal_refmap_ref_t refmap);

/**
 * @brief The type of refmap.
 *
 * @param[in] refmap - Refmap object obtained by @ref osal_refmap_create.
 *
 * @return The type of refmap.
 */
int osal_refmap_type(osal_refmap_ref_t refmap);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_refmap)
 */
/****************************************************************************/
#endif /* OSAL_REFMAP_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

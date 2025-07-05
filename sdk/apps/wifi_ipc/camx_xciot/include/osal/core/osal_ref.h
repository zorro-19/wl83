/*****************************************************************************
 * osal_ref.h
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
#ifndef OSAL_REF_H_INCLUDE
#define OSAL_REF_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_ref
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

typedef uint16_t osal_reftype_t;
enum osal_reftype {
    /** 1 - 0xFF for osal sys */
    E_OSAL_REFTYPE_SYS_BASE  = 0x0000,
    E_OSAL_REFTYPE_SYS_MTX   = (E_OSAL_REFTYPE_SYS_BASE + 1),
    E_OSAL_REFTYPE_SYS_SEM   = (E_OSAL_REFTYPE_SYS_BASE + 2),
    E_OSAL_REFTYPE_SYS_THR   = (E_OSAL_REFTYPE_SYS_BASE + 3),
    E_OSAL_REFTYPE_SYS_MQ    = (E_OSAL_REFTYPE_SYS_BASE + 4),
    E_OSAL_REFTYPE_SYS_WAITQ = (E_OSAL_REFTYPE_SYS_BASE + 5),

    /** 0x100 ~ 0x1FF for app */
    E_OSAL_REFTYPE_APP_BASE = 0x0100
};

typedef void (*osal_ref_cleanup_cb_t)(void *ref);

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
 * @brief Allocates memory of the specified size and sets reference count to 1
 * for the newly allocated object. Memory must be freed by calling
 * @ref osal_ref_release(void *) on the returned pointer.
 *
 * @param[in]  type - The ref type, see @ref osal_reftype_t.
 *
 * @param[in]  sz   - The size in bytes of memory to allocate.
 *
 * @param[in]  cb   - The ref delete callback.
 *
 * @return The pointer to the allocated memory of ref or NULL on error.
 */
void *
osal_ref_alloc(osal_reftype_t type, size_t sz, osal_ref_cleanup_cb_t cb);

/**
 * @brief Increases the retain count of an object.
 *
 * Call this function on a pointer (obtained from osal_ref_alloc) to increase
 * the retain count on the object to keep it from being freed. Ensure
 * osal_ref_release(void *) is called on the object when it is no longer needed.
 *
 * A parent process must retain a reference on behalf of any child process
 * prior to passing along the pointer to the object to the new thread.
 * Processes are only allowed to retain reference for objects they already
 * have a reference to.
 *
 * @param[in] oref - The pointer to ref.
 *
 * @return The pointer to ref or NULL on error.
 */
void *osal_ref_retain(void *oref);

/**
 * @brief Decreases the retain count of an object by 1 freeing the object when
 * it is no longer referenced (when the reference count reaches 0).
 *
 * Call this function on a pointer (obtained from osal_ref_alloc to decrease
 * the retain count when finished with it. Only call this function on
 * an object created with osal_ref_alloc or retained with osal_ref_retain.
 *
 * @param[in] oref - The pointer to ref.
 */
void osal_ref_release(void *oref);

/**
 * @brief Get the current reference count for the object.
 *
 * @param[in] oref - The pointer to ref.
 */
int osal_ref_count(void *oref);

/**
 * @brief Lock the mutex for the object.
 *
 * @param[in] oref - The pointer to ref.
 */
void osal_ref_mtx_lock(void *oref);

/**
 * @brief Unlock the mutex for the object.
 *
 * @param[in] oref - The pointer to ref.
 */
void osal_ref_mtx_unlock(void *oref);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_ref)
 */
/****************************************************************************/
#endif /* OSAL_REF_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

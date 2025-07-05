/*****************************************************************************
 * osal_dispatcher.h
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
#ifndef OSAL_DISPATCHER_H_INCLUDE
#define OSAL_DISPATCHER_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_dispatcher
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

struct osal_dispatcher_item {
    uint64_t id;
    void    *handler;
    void    *ud;
};

typedef struct osal_dispatcher *osal_dispatcher_ref_t;

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

int osal_dispatcher_create(osal_dispatcher_ref_t *dispatcherp, size_t size);

void osal_dispatcher_delete(osal_dispatcher_ref_t dispatcher);

int osal_dispatcher_add(osal_dispatcher_ref_t        dispatcher,
                        struct osal_dispatcher_item *item);

int osal_dispatcher_adds(osal_dispatcher_ref_t        dispatcher,
                         struct osal_dispatcher_item *items,
                         size_t                       itemsz);

int osal_dispatcher_find(osal_dispatcher_ref_t        dispatcher,
                         uint64_t                     id,
                         struct osal_dispatcher_item *item);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_dispatcher)
 */
/****************************************************************************/
#endif /* OSAL_DISPATCHER_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

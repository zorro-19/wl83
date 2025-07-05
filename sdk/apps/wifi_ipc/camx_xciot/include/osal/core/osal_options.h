/*****************************************************************************
 * osal_options.h
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
#ifndef OSAL_OPTIONS_H_INCLUDE
#define OSAL_OPTIONS_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_options
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

typedef struct osal_option {
    /** o_name is the name of the option. */
    const char *o_name;

    /**
     * o_get is used to retrieve the value of the option.  The
     * size supplied will limit how much data is copied.  Regardless,
     * the actual size of the object that would have been copied
     * is supplied by the function in the size.  If the object did
     * not fit, then E_OSAL_EINVAL is returned.
     */
    int (*o_get)(void *arg, void *, size_t *, osal_type_t);

    /**
     * o_set is used to set the value of the option.  For transport
     * endpoints only, the instance parameter (first argument) may be
     * NULL, in which case only a generic validation of the parameters
     * is performed.  (This is used when setting socket options before
     */
    int (*o_set)(void *arg, const void *, size_t, osal_type_t);
} osal_option_t;

typedef struct osal_chkoption {
    /** o_name is the name of the chkoption. */
    const char *o_name;

    /** o_check can be NULL for read-only options */
    int (*o_check)(const void *, size_t, osal_type_t);
} osal_chkoption_t;

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
int osal_getopt(const osal_option_t *opts,
                const char          *nm,
                void                *arg,
                void                *buf,
                size_t              *szp,
                osal_type_t          otype);
int osal_setopt(const osal_option_t *opts,
                const char          *nm,
                void                *arg,
                const void          *buf,
                size_t               sz,
                osal_type_t          otype);
int osal_chkopt(const osal_chkoption_t *opts,
                const char             *nm,
                const void             *buf,
                size_t                  sz,
                osal_type_t             t);
#endif

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_options)
 */
/****************************************************************************/
#endif /* OSAL_OPTIONS_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

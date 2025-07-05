/*****************************************************************************
 * osal_errno.h
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
#ifndef OSAL_ERRNO_H_INCLUDE
#define OSAL_ERRNO_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_errno
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

enum osal_errno_enum {
    E_OSAL_SUCCESS      = 0,
    E_OSAL_EINTR        = -1,
    E_OSAL_ENOMEM       = -2,
    E_OSAL_EINVAL       = -3,
    E_OSAL_EBUSY        = -4,
    E_OSAL_ETIMEDOUT    = -5,
    E_OSAL_ECONNREFUSED = -6,
    E_OSAL_ECLOSED      = -7,
    E_OSAL_EAGAIN       = -8,
    E_OSAL_ENOTSUP      = -9,
    E_OSAL_EADDRINUSE   = -10,
    E_OSAL_ESTATE       = -11,
    E_OSAL_ENOENT       = -12,
    E_OSAL_EPROTO       = -13,
    E_OSAL_EUNREACHABLE = -14,
    E_OSAL_EADDRINVAL   = -15,
    E_OSAL_EPERM        = -16,
    E_OSAL_EMSGSIZE     = -17,
    E_OSAL_ECONNABORTED = -18,
    E_OSAL_ECONNRESET   = -19,
    E_OSAL_ECANCELED    = -20,
    E_OSAL_ENOFILES     = -21,
    E_OSAL_ENOSPC       = -22,
    E_OSAL_EEXIST       = -23,
    E_OSAL_EREADONLY    = -24,
    E_OSAL_EWRITEONLY   = -25,
    E_OSAL_ECRYPTO      = -26,
    E_OSAL_EPEERAUTH    = -27,
    E_OSAL_ENOARG       = -28,
    E_OSAL_EAMBIGUOUS   = -29,
    E_OSAL_EBADTYPE     = -30,
    E_OSAL_EIO          = -31,
    E_OSAL_EINTERNAL    = -1000,
    E_OSAL_ESYSERR      = -0x10000000,
    E_OSAL_ETRANERR     = -0x20000000,
    E_OSAL_EUSER        = -0x30000000
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

const char *osal_strerror(int errnum);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_errno)
 */
/****************************************************************************/
#endif /* OSAL_ERRNO_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

/*****************************************************************************
 * osal_type.h
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
#ifndef OSAL_TYPE_H_INCLUDE
#define OSAL_TYPE_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_type
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

/**
 * Format specifiers for size_t
 */
#if (__STDC_VERSION__ >= 199901L) ||                                         \
    (CONFIG_OSAL_PLATFORM == OSAL_PLATFORM_POSIX)
#define __PRIS_PREFIX "z"
#elif defined(__LP64__) || defined(_LP64)
#define __PRIS_PREFIX "ll"
#else
#define __PRIS_PREFIX "l"
#endif
#define PRIdS __PRIS_PREFIX "d"
#define PRIxS __PRIS_PREFIX "x"
#define PRIuS __PRIS_PREFIX "u"
#define PRIXS __PRIS_PREFIX "X"
#define PRIoS __PRIS_PREFIX "o"

#define FPRI02d "%02" PRId8
#define FPRI04d "%04" PRId16
#define FPRI08d "%08" PRId32
#define FPRI016d "%016" PRId64

#define FPRI02X "%02" PRIX8
#define FPRI04X "%04" PRIX16
#define FPRI08X "%08" PRIX32
#define FPRI016X "%016" PRIX64

#define FPRI02x "%02" PRIx8
#define FPRI04x "%04" PRIx16
#define FPRI08x "%08" PRIx32
#define FPRI016x "%016" PRIx64

/* osal name max len */
#define C_OSAL_NAME_MAX_LEN (32 + 1)

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/*
 * Types. These are used to provide more structured access to options
 * (and maybe later statistics).  For now these are internal only.
 */
typedef enum {
    E_OSAL_TYPE_OPAQUE,

    E_OSAL_TYPE_BOOL,
    E_OSAL_TYPE_INT,
    E_OSAL_TYPE_SIZE,
    E_OSAL_TYPE_POINTER,
    E_OSAL_TYPE_STRING,

    E_OSAL_TYPE_INT32,
    E_OSAL_TYPE_UINT32,
    E_OSAL_TYPE_INT64,
    E_OSAL_TYPE_UINT64,

    E_OSAL_TYPE_SOCKADDR,
} osal_type_t;

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

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_type)
 */
/****************************************************************************/
#endif /* OSAL_TYPE_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

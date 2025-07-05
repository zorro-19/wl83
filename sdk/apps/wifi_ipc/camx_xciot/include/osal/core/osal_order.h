/*****************************************************************************
 * osal_order.h
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
#ifndef OSAL_ORDER_H_INCLUDE
#define OSAL_ORDER_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_order
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

/* Internal helpers only used by the osal_* APIs further below */
#define SWAP16(_x_)                                                          \
    ((uint16_t)((((uint16_t)(_x_) & (uint16_t)0x00ffU) << 8) |               \
                (((uint16_t)(_x_) & (uint16_t)0xff00U) >> 8)))

#define SWAP32(_x_)                                                          \
    ((uint32_t)((((uint32_t)(_x_) & (uint32_t)0x000000ffUL) << 24) |         \
                (((uint32_t)(_x_) & (uint32_t)0x0000ff00UL) << 8) |          \
                (((uint32_t)(_x_) & (uint32_t)0x00ff0000UL) >> 8) |          \
                (((uint32_t)(_x_) & (uint32_t)0xff000000UL) >> 24)))

#define SWAP64(_x_)                                                          \
    ((uint64_t)(                                                             \
        (((uint64_t)(_x_) & (uint64_t)0x00000000000000ffULL) << 56) |        \
        (((uint64_t)(_x_) & (uint64_t)0x000000000000ff00ULL) << 40) |        \
        (((uint64_t)(_x_) & (uint64_t)0x0000000000ff0000ULL) << 24) |        \
        (((uint64_t)(_x_) & (uint64_t)0x00000000ff000000ULL) << 8) |         \
        (((uint64_t)(_x_) & (uint64_t)0x000000ff00000000ULL) >> 8) |         \
        (((uint64_t)(_x_) & (uint64_t)0x0000ff0000000000ULL) >> 24) |        \
        (((uint64_t)(_x_) & (uint64_t)0x00ff000000000000ULL) >> 40) |        \
        (((uint64_t)(_x_) & (uint64_t)0xff00000000000000ULL) >> 56)))

/**
 * @def osal_le16_to_cpu
 * @brief Convert 16-bit integer from little-endian to host endianness.
 *
 * @param _x_ 16-bit integer in little-endian format.
 *
 * @return 16-bit integer in host endianness.
 */

/**
 * @def osal_cpu_to_le16
 * @brief Convert 16-bit integer from host endianness to little-endian.
 *
 * @param _x_ 16-bit integer in host endianness.
 *
 * @return 16-bit integer in little-endian format.
 */

/**
 * @def osal_be16_to_cpu
 * @brief Convert 16-bit integer from big-endian to host endianness.
 *
 * @param _x_ 16-bit integer in big-endian format.
 *
 * @return 16-bit integer in host endianness.
 */

/**
 * @def osal_cpu_to_be16
 * @brief Convert 16-bit integer from host endianness to big-endian.
 *
 * @param _x_ 16-bit integer in host endianness.
 *
 * @return 16-bit integer in big-endian format.
 */

/**
 * @def osal_le32_to_cpu
 * @brief Convert 32-bit integer from little-endian to host endianness.
 *
 * @param _x_ 32-bit integer in little-endian format.
 *
 * @return 32-bit integer in host endianness.
 */

/**
 * @def osal_cpu_to_le32
 * @brief Convert 32-bit integer from host endianness to little-endian.
 *
 * @param _x_ 32-bit integer in host endianness.
 *
 * @return 32-bit integer in little-endian format.
 */

/**
 * @def osal_be32_to_cpu
 * @brief Convert 32-bit integer from big-endian to host endianness.
 *
 * @param _x_ 32-bit integer in big-endian format.
 *
 * @return 32-bit integer in host endianness.
 */

/**
 * @def osal_cpu_to_be32
 * @brief Convert 32-bit integer from host endianness to big-endian.
 *
 * @param _x_ 32-bit integer in host endianness.
 *
 * @return 32-bit integer in big-endian format.
 */
#ifndef OSAL_BYTE_ORDER_BIG_ENDIAN /* LE */
#define osal_le16_to_cpu(_x_) (_x_)
#define osal_cpu_to_le16(_x_) (_x_)
#define osal_be16_to_cpu(_x_) SWAP16(_x_)
#define osal_cpu_to_be16(_x_) SWAP16(_x_)

#define osal_le32_to_cpu(_x_) (_x_)
#define osal_cpu_to_le32(_x_) (_x_)
#define osal_be32_to_cpu(_x_) SWAP32(_x_)
#define osal_cpu_to_be32(_x_) SWAP32(_x_)

#define osal_le64_to_cpu(_x_) (_x_)
#define osal_cpu_to_le64(_x_) (_x_)
#define osal_be64_to_cpu(_x_) SWAP64(_x_)
#define osal_cpu_to_be64(_x_) SWAP64(_x_)
#else /* BE */
#define osal_le16_to_cpu(_x_) SWAP16(_x_)
#define osal_cpu_to_le16(_x_) SWAP16(_x_)
#define osal_be16_to_cpu(_x_) (_x_)
#define osal_cpu_to_be16(_x_) (_x_)

#define osal_le32_to_cpu(_x_) SWAP32(_x_)
#define osal_cpu_to_le32(_x_) SWAP32(_x_)
#define osal_be32_to_cpu(_x_) (_x_)
#define osal_cpu_to_be32(_x_) (_x_)

#define osal_le64_to_cpu(_x_) SWAP64(_x_)
#define osal_cpu_to_le64(_x_) SWAP64(_x_)
#define osal_be64_to_cpu(_x_) (_x_)
#define osal_cpu_to_be64(_x_) (_x_)
#endif

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

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_order)
 */
/****************************************************************************/
#endif /* OSAL_ORDER_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

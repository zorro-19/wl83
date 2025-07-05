/*****************************************************************************
 * osal_bytes.h
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
 * Bytes Management Functions
 *
 *
 */
#ifndef OSAL_BYTES_H_INCLUDE
#define OSAL_BYTES_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_bytes
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

/*****************************************************************************
 * Public Data
 ****************************************************************************/

/*****************************************************************************
 * Inline Functions
 ****************************************************************************/

/**
 * @addtogroup osal_bytes - Bytes Management Functions
 * @ingroup osal
 * @{
 */
/**
 * @brief Put a 8-bit intger to arbitrary location.
 *
 * Put a 8-bit integer, to a potentially unaligned memory location.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 8-bit integer.
 */
static __INLINE void osal_bytes_put_u8(uint8_t dst[1], uint8_t val)
{
    dst[0] = val;
}

/**
 * @brief Put a 16-bit intger as little-endian to arbitrary location.
 *
 * Put a 16-bit integer, originally in host endianness, to a
 * potentially unaligned memory location in little-endian format.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 16-bit integer in host endianness.
 */
static __INLINE void osal_bytes_put_le16(uint8_t dst[2], uint16_t val)
{
    dst[0] = val;
    dst[1] = val >> 8;
}

/**
 * @brief Put a 16-bit intger as big-endian to arbitrary location.
 *
 * Put a 16-bit integer, originally in host endianness, to a
 * potentially unaligned memory location in big-endian format.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 16-bit integer in host endianness.
 */
static __INLINE void osal_bytes_put_be16(uint8_t dst[2], uint16_t val)
{
    dst[0] = val >> 8;
    dst[1] = val;
}

/**
 * @brief Put a 32-bit intger as little-endian to arbitrary location.
 *
 * Put a 32-bit integer, originally in host endianness, to a
 * potentially unaligned memory location in little-endian format.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 32-bit integer in host endianness.
 */
static __INLINE void osal_bytes_put_le32(uint8_t dst[4], uint32_t val)
{
    osal_bytes_put_le16(dst, val);
    osal_bytes_put_le16(&dst[2], val >> 16);
}

/**
 * @brief Put a 32-bit intger as big-endian to arbitrary location.
 *
 * Put a 32-bit integer, originally in host endianness, to a
 * potentially unaligned memory location in big-endian format.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 32-bit integer in host endianness.
 */
static __INLINE void osal_bytes_put_be32(uint8_t dst[4], uint32_t val)
{
    osal_bytes_put_be16(dst, val >> 16);
    osal_bytes_put_be16(&dst[2], val);
}

/**
 * @brief Put a 64-bit integer as little-endian to arbitrary location.
 *
 * Put a 64-bit integer, originally in host endianness, to a
 * potentially unaligned memory location in little-endian format.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 64-bit integer in host endianness.
 */
static __INLINE void osal_bytes_put_le64(uint8_t dst[8], uint64_t val)
{
    osal_bytes_put_le32(dst, val);
    osal_bytes_put_le32(&dst[4], val >> 32);
}

/**
 * @brief Put a 64-bit intger as big-endian to arbitrary location.
 *
 * Put a 64-bit integer, originally in host endianness, to a
 * potentially unaligned memory location in big-endian format.
 *
 * @param[in] dst Destination memory address to store the result.
 * @param[in] val 64-bit integer in host endianness.
 */
static __INLINE void osal_bytes_put_be64(uint8_t dst[8], uint64_t val)
{
    osal_bytes_put_be32(dst, val >> 32);
    osal_bytes_put_be32(&dst[4], val);
}

/**
 * @brief Put varint value to arbitrary location.
 *
 * @param[in] dst Destination memory address to store the result.
 *
 * @param[in] len Destination memory length.

 * @param[in] varint varint in host endianness.
 *
 * @return length to encode.
 */
static __INLINE int
osal_bytes_put_varint(uint8_t dst[], size_t len, uint64_t varint)
{
    int i;

    varint = osal_cpu_to_le64(varint);

    for (i = 0; varint > 0x7F; i++) {
        if (i > (int)len) {
            return -1;
        }
        dst[i] = ((uint8_t)(varint & 0x7F) | 0x80);
        varint >>= 7;
    }

    dst[i] = ((uint8_t)(varint & 0x7F));

    /* bytes length */
    return (i + 1);
}

/**
 * @brief Get a 8-bit intger.
 *
 * Get a 8-bit integer, stored in a potentially unaligned memory location.
 *
 * @param[in] src Location of the 8-bit integer to get.
 *
 * @return 8-bit integer in host endianness.
 */
static __INLINE uint8_t osal_bytes_get_u8(const uint8_t src[1])
{
    return src[0];
}

/**
 * @brief Get a 16-bit intger stored in little-endian format.
 *
 * Get a 16-bit integer, stored in little-endian format in a potentially
 * unaligned memory location, and convert it to the host endianness.
 *
 * @param[in] src Location of the little-endian 16-bit integer to get.
 *
 * @return 16-bit integer in host endianness.
 */
static __INLINE uint16_t osal_bytes_get_le16(const uint8_t src[2])
{
    return ((uint16_t)src[1] << 8) | src[0];
}

/**
 * @brief Get a 16-bit intger stored in big-endian format.
 *
 * Get a 16-bit integer, stored in big-endian format in a potentially
 * unaligned memory location, and convert it to the host endianness.
 *
 * @param[in] src Location of the big-endian 16-bit integer to get.
 *
 * @retval 16-bit integer in host endianness.
 */
static __INLINE uint16_t osal_bytes_get_be16(const uint8_t src[2])
{
    return ((uint16_t)src[0] << 8) | src[1];
}

/**
 * @brief Get a 32-bit intger stored in little-endian format.
 *
 * Get a 32-bit integer, stored in little-endian format in a potentially
 * unaligned memory location, and convert it to the host endianness.
 *
 * @param[in] src Location of the little-endian 32-bit integer to get.
 *
 * @return 32-bit integer in host endianness.
 */
static __INLINE uint32_t osal_bytes_get_le32(const uint8_t src[4])
{
    return ((uint32_t)osal_bytes_get_le16(&src[2]) << 16) |
           osal_bytes_get_le16(&src[0]);
}

/**
 * @brief Get a 32-bit intger stored in big-endian format.
 *
 * Get a 32-bit integer, stored in big-endian format in a potentially
 * unaligned memory location, and convert it to the host endianness.
 *
 * @param[in] src Location of the big-endian 32-bit integer to get.
 *
 * @return 32-bit integer in host endianness.
 */
static __INLINE uint32_t osal_bytes_get_be32(const uint8_t src[4])
{
    return ((uint32_t)osal_bytes_get_be16(&src[0]) << 16) |
           osal_bytes_get_be16(&src[2]);
}

/**
 * @brief Get a 64-bit integer stored in little-endian format.
 *
 * Get a 64-bit integer, stored in little-endian format in a potentially
 * unaligned memory location, and convert it to the host endianness.
 *
 * @param[in] src Location of the little-endian 64-bit integer to get.
 *
 * @return 64-bit integer in host endianness.
 */
static __INLINE uint64_t osal_bytes_get_le64(const uint8_t src[8])
{
    return ((uint64_t)osal_bytes_get_le32(&src[4]) << 32) |
           osal_bytes_get_le32(&src[0]);
}

/**
 * @brief Get a 64-bit intger stored in big-endian format.
 *
 * Get a 64-bit integer, stored in big-endian format in a potentially
 * unaligned memory location, and convert it to the host endianness.
 *
 * @param[in] src Location of the big-endian 64-bit integer to get.
 *
 * @return 32-bit integer in host endianness.
 */
static __INLINE uint64_t osal_bytes_get_be64(const uint8_t src[8])
{
    return ((uint64_t)osal_bytes_get_be32(&src[0]) << 32) |
           osal_bytes_get_be32(&src[4]);
}

/**
 * @brief Get varint from buffer.
 *
 * @param[in]  src Source memory of the varint to get.
 *
 * @param[in]  len Source memory length.
 *
 * @param[out] varint The result in host endianness.
 *
 * @return length to decode.
 */
static __INLINE int
osal_bytes_get_varint(const uint8_t src[], size_t len, uint64_t *varint)
{
    uint8_t  byte, bitpos = 0;
    uint64_t result = 0;
    int      n      = 0;
    do {
        if (bitpos >= 64) {
            return -1;
        }

        if (n >= (int)len) {
            return 0;
        }
        byte = src[n++];

        result |= (uint64_t)(byte & 0x7F) << bitpos;
        bitpos += 7;
    } while (byte & 0x80);

    *varint = result;

    return n;
}
/** @} End of group osal_bytes */

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
 * @} (end addtogroup osal_bytes)
 */
/****************************************************************************/
#endif /* OSAL_BYTES_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

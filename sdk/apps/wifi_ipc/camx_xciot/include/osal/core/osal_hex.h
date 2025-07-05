/*****************************************************************************
 * osal_hex.h
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
/**
 * wiki
 * ====
 * @page osal_hex Hex string API
 *
 *
 * @ref osal_hex.h "API Reference"
 *
 * <HR>
 *
 * This API provides convertion api to switch between:
 *  - @ref osal_hex_StrToBin  Hex-String to binary
 *  - @ref osal_hex_bin2str  Binary to Hex-String
 *
 *
 * @section hex_conversion Conversion
 *
 * Code sample:
 *
 * @code
 * char     hexString[] = "136ABC";
 * uint8_t  binBytes[]  = { 0x13, 0x6A, 0xBC };
 * @endcode
 *
 * So @ref osal_hex_StrToBin will convert hexString to binBytes.
 *
 * and @ref osal_hex_bin2str will convert binBytes to hexString.
 *
 * <HR>
 */

#ifndef OSAL_HEX_H_INCLUDE
#define OSAL_HEX_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_hex
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

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * @brief Convert a string of valid hexadecimal characters [0-9a-fA-F] into a
 * byte array where each element of the byte array holds the value corresponding
 * to a pair of hexadecimal characters.
 *
 * The input string is not required to be NULL terminated.
 *
 * @param[in]  stringPtr string to convert.
 *
 * @param[in]  stringLength string length.
 *
 * @param[out] binaryPtr binary result.
 *
 * @param[in]  binarySize size of the binary bytes array, Must be >= stringLength / 2.
 *
 * @return - number of bytes written into binaryPtr
 *         - -1 if the binarySize is too small or
 *              stringLength is odd or stringPtr contains an invalid character.
 */
int32_t osal_hex_str2bin(const char *stringPtr,
                         uint32_t    stringLength,
                         uint8_t    *binaryPtr,
                         uint32_t    binarySize);

/**
 * @brief Convert a bin bytes into a string of uppercase hexadecimal characters.
 *
 * The string written to stringPtr will be NULL terminated.
 *
 * @param[in]  binaryPtr binary array to convert.
 *
 * @param[in]  binarySize size of binary array.
 *
 * @param[out] stringPtr hex string array, terminated with '\0'.
 *
 * @param[in]  stringSize size of string array.  Must be >= (2 * binarySize) + 1.
 *
 * @return - number of bytes written into binaryPtr
 *         - -1 if the binarySize is too small or
 *              stringLength is odd or stringPtr contains an invalid character.
 */
int32_t osal_hex_bin2str(const uint8_t *binaryPtr,
                         uint32_t       binarySize,
                         char          *stringPtr,
                         uint32_t       stringSize);

char *osal_iota(int num, char *str, int radix);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_hex)
 */
/****************************************************************************/
#endif /* OSAL_HEX_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

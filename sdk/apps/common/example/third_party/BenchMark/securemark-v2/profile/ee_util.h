/*
 * Copyright (C) EEMBC(R). All Rights Reserved
 *
 * All EEMBC Benchmark Software are products of EEMBC and are provided under the
 * terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
 * are proprietary intellectual properties of EEMBC and its Members and is
 * protected under all applicable laws, including all applicable copyright laws.
 *
 * If you received this EEMBC Benchmark Software without having a currently
 * effective EEMBC Benchmark License Agreement, you must discontinue use.
 */
#ifndef __EE_UTIL_H
#define __EE_UTIL_H

#include <stdint.h>
#include <stddef.h>
#include "ee_main.h"

#define EE_PRINTMEM_DEFAULT_HEADER "m-hexdump-";

/**
 * @brief Convert a hexidecimal string to a signed long will not produce or
 * process negative numbers except to signal error.
 *
 * @param hex  - Input buffer of hex characters [a-fA-0-9]
 * @return long - Returns the converted value, or -1 on error; but if the result
 * is > size(long) the number is invalid (there is no character counting) and
 * no error is generated.
 *
 */
long ee_hexdec(char *p_hex);

/**
 * @brief Seed our trivial PRNG.
 *
 * This is used for generating reproducable input, the quality of which is
 * not important. It just needs to be fast and pseudo-random.
 *
 * @param seed - A one-byte seed.
 */
void ee_srand(uint8_t seed);

/**
 * @brief Return a PRNG byte.
 *
 * This is used for generating reproducable input, the quality of which is
 * not important. It just needs to be fast and pseudo-random.
 *
 * @return uint8_t - The "random" byte.
 */
uint8_t ee_rand(void);

/**
 * @brief Prints out a number of hex bytes from an addres (max 16 per line) in
 * the format of %02x. The user can provide their own header for debugging.
 *
 * @param p_addr - Pointer to buffer
 * @param len - Number of bytes to print
 * @param p_user_header - Pointer to a text string, or NULL for default
 */
void ee_printmem(uint8_t *p_addr, uint32_t len, char *p_user_header);

/**
 * @brief Prints out hex bytes from an address in a single line.
 *
 * @param p_addr - Pointer to buffer
 * @param len - Number of bytes to print
 */
void ee_hextotxt(uint8_t *p_addr, uint32_t len);

/**
 * @brief Prints out hex bytes from an address in a single line including
 * a header, an '0x' prefix, and a '\r\n' termination.
 *
 * @param p_addr - Pointer to buffer
 * @param len - Number of bytes to print
 * @param p_user_header - Pointer to a text string, or NULL for default
 */
void ee_printmemline(uint8_t *p_addr, uint32_t len, char *p_user_header);


/**
 * @brief Swap the bytes in a 32-bit value. This is due to the fact that
 * int32 values are stored in the DUT's `th_buffer` from the host GUI. The
 * host GUI always writes big-endian, but the architecture port will need to
 * make sure that the macros in `profile/th_util.h` can figure out the DUT
 * endianness.
 *
 * @param x - The 32-bit value to swap
 * @return uint32_t - The swapped 32-bit value
 */
uint32_t ee_fix_endian32(uint32_t x);

/**
 * @brief If self hosted, we don't need to swap endian
 *
 */
#if EE_CFG_SELFHOSTED == 1
#define EE_FIX_ENDIAN(x) (x)
#else
#define EE_FIX_ENDIAN(x) ee_fix_endian32(x)
#endif

#endif /* _EE_UTIL_H */

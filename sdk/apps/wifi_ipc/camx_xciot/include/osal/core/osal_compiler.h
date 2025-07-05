/*****************************************************************************
 * osal_compiler.h
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
#ifndef OSAL_COMPILER_H_INCLUDE
#define OSAL_COMPILER_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_compiler
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
 * @brief Compiler message.
 */
#define OSAL_COMPILER_NOTE(x) COMPILER_MESSAGE(message("--NOTE-- " #x))
#define OSAL_COMPILER_TODO(x) COMPILER_MESSAGE(message("--TODO-- " #x))
#define OSAL_COMPILER_WARN(x) COMPILER_MESSAGE(message("--WARN-- " #x))
#define COMPILER_MESSAGE(x) _Pragma(#x)

#define _IN_
#define _OU_
#define _IO_

#define MODULE_API
#define EXPORT_API
#define IMPORT_API

/**
 * @brief Compiler Marco.
 * - __ASM
 * - __INLINE
 * - __STATIC_INLINE
 * - __STATIC_FORCEINLINE
 * - __NO_RETURN
 * - __USED
 * - __WEAK
 * - __ALIGNED
 * - __PACKED
 * - __RESTRICT
 */

/* @Arm Compiler 4/5
 * @{
 */
#if defined(__CC_ARM)
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 400677)
#error "Please use Arm Compiler Toolchain V4.0.677 or later!"
#endif

#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __INLINE
#define __INLINE __inline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __inline
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE static __forceinline
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __declspec(noreturn)
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif
#ifndef __RESTRICT
#define __RESTRICT __restrict
#endif
/* @} End Arm Compiler 4/5
 */
/**
 * @IAR Compiler
 * @{
 */
#elif defined(__ICCARM__)
#if (__VER__ >= 8000000)
#define __ICCARM_V8 1
#else
#define __ICCARM_V8 0
#endif

#ifndef __ASM
#define __ASM __asm
#endif

#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif
#ifndef __FORCEINLINE
#define __FORCEINLINE _Pragma("inline=forced")
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE __FORCEINLINE __STATIC_INLINE
#endif
#ifndef __NO_RETURN
#if __ICCARM_V8
#define __NO_RETURN __attribute__((__noreturn__))
#else
#define __NO_RETURN _Pragma("object_attribute=__noreturn")
#endif
#endif

#ifndef __USED
#if __ICCARM_V8
#define __USED __attribute__((used))
#else
#define __USED _Pragma("__root")
#endif
#endif
#ifndef __WEAK
#if __ICCARM_V8
#define __WEAK __attribute__((weak))
#else
#define __WEAK _Pragma("__weak")
#endif
#endif
#ifndef __ALIGNED
#if __ICCARM_V8
#define __ALIGNED(x) __attribute__((aligned(x)))
#elif (__VER__ >= 7080000)
/* Needs IAR language extensions */
#define __ALIGNED(x) __attribute__((aligned(x)))
#else
//#warning No compiler specific solution for __ALIGNED.__ALIGNED is ignored.
#define __ALIGNED(x)
#endif
#endif
#ifndef __PACKED
#if __ICCARM_V8
#define __PACKED __attribute__((packed, aligned(1)))
#else
/* Needs IAR language extensions */
#define __PACKED __packed
#endif
#endif
#ifndef __RESTRICT
#define __RESTRICT __restrict
#endif
/* @} End IAR Compiler
 */
/**
 * @GNU Compiler
 * @{
 */
#elif defined(__GNUC__)
#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((__noreturn__))
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#ifndef __RESTRICT
#define __RESTRICT __restrict
#endif
/* @} End GNU Compiler
 */
#else
#error Unknown compiler.
#endif
/** @} End of group CompilerMacro */

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
 * @} (end addtogroup osal_compiler)
 */
/****************************************************************************/
#endif /* OSAL_COMPILER_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

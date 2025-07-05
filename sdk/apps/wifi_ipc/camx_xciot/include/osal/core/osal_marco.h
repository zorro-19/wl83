/*****************************************************************************
 * osal_marco.h
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
#ifndef OSAL_MARCO_H_INCLUDE
#define OSAL_MARCO_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_marco
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
 * @def OSAL_BUILD_ASSERT
 * @brief assert a build-time dependency.
 *
 * Your compile will fail if the condition isn't true, or can't be evaluated
 * by the compiler.  This can only be used within a function.
 *
 * @param[in] cond The compile-time condition which must be true.
 *
 * Example:
 * @code
 * #include <stddef.h> // offsetof
 * static char *foo_to_char(struct foo *foo)
 * {
 *     //This code needs string to be at start of foo.
 *     OSAL_BUILD_ASSERT(offsetof(struct foo, string) == 0);
 *     return (char *)foo;
 * }
 * @endcode
 */
#define OSAL_BUILD_ASSERT(cond)                                              \
    do {                                                                     \
        (void)sizeof(char[1 - 2 * !(cond)]);                                 \
    } while (0)

/**
 * @def OSAL_BUILD_ASSERT_OR_ZERO
 * @brief assert a build-time dependency, as an expression.
 *
 * Your compile will fail if the condition isn't true, or can't be evaluated
 * by the compiler.  This can be used in an expression: its value is "0".
 *
 * @param[in] cond The compile-time condition which must be true.
 *
 * Example:
 * @code
 * #define foo_to_char(foo)					                                 \
 *     ((char *)(foo)						                                 \
 *         + OSAL_BUILD_ASSERT_OR_ZERO(offsetof(struct foo, string) == 0))
 * @endcode
 */
#define OSAL_BUILD_ASSERT_OR_ZERO(cond) (sizeof(char[1 - 2 * !(cond)]) - 1)

/**
 * @def OSAL_OFFSET_OF
 * @brief Return the offset of the given field in the given type.
 *
 * @param[in] type  - The type containing the filed.
 * @param[in] field - The field in the type.
 *
 * @return the offset of field in type.
 */
#define OSAL_OFFSET_OF(type, field) ((size_t)(&((type *)0)->field))

/**
 * @def OSAL_CONTAINER_OF
 * @brief Find the address of a containing structure or union,
 * based on the address of one of its members.
 *
 * If @c countPtr points to the @c count member of an object type
 * @c my_class_t, then a pointer to that object should use this:
 *
 * @code
 * my_class_t* myObjPtr = OSAL_CONTAINER_OF(countPtr, my_class_t, count);
 * @endcode
 */
#define OSAL_CONTAINER_OF(memberPtr, type, member)                           \
    ((type *)(((uint8_t *)(memberPtr)) - ((size_t)(&(((type *)0)->member)))))

/**
 * @def OSAL_STRINGIFY
 * @brief converts a macro argument into a character constant.
 *
 * @param[in] x A macro argument to stringify.
 */
#define OSAL_STRINGIFY(x) OSAL_STRINGIFY_(x)
#define OSAL_STRINGIFY_(x) #x

/**
 * @def OSAL_CONCAT2
 * @brief Concatenates two parameters.
 *
 * It realizes two level expansion to make it sure that all the parameters
 * are actually expanded before gluing them together.
 *
 * @param[in] p1 First parameter to concatenating
 * @param[in] p2 Second parameter to concatenating
 *
 * @return Two parameters glued together.
 *         They have to create correct C mnemonic in other case
 *         preprocessor error would be generated.
 */
#define OSAL_CONCAT2(p1, p2) OSAL_CONCAT2_(p1, p2)
/** Auxiliary macro used by @ref OSAL_CONCAT2 */
#define OSAL_CONCAT2_(p1, p2) p1##p2

/**
 * @def OSAL_CONCAT3
 * @brief Concatenates three parameters.
 *
 * It realizes two level expansion to make it sure that all the parameters
 * are actually expanded before gluing them together.
 *
 * @param[in] p1 First parameter to concatenating
 * @param[in] p2 Second parameter to concatenating
 * @param[in] p3 Third parameter to concatenating
 *
 * @return Three parameters glued together.
 *         They have to create correct C mnemonic in other case
 *         preprocessor error would be generated.
 */
#define OSAL_CONCAT3(p1, p2, p3) OSAL_CONCAT3_(p1, p2, p3)
/** Auxiliary macro used by @ref OSAL_CONCAT3 */
#define OSAL_CONCAT3_(p1, p2, p3) p1##p2##p3

/**
 * @def OSAL_STRFILE
 * @brief Provide a string identifying the current code filename.
 */
#define OSAL_STRFILE __FILE__

/**
 * @def OSAL_STRLOC
 * @brief Provide a string identifying the current code position.
 */
#define OSAL_STRLOC __FILE__ "/" OSAL_STRINGIFY(__LINE__)

/**
 * @def OSAL_STRLINE
 * @brief Provide a string identifying the current code line.
 */
#define OSAL_STRLINE OSAL_STRINGIFY(__LINE__)

/**
 * @def OSAL_STRFUNC
 * @brief Provide a string identifying the current function, non-concatenatable.
 */
#define OSAL_STRFUNC ((const char *)(__FUNCTION__))

/**
 * @def OSAL_IS_ARRAY
 * @brief Evaluates to 0 if array is an array; compile error if not array (e.g.
 * pointer).
 */
#if defined(__GNUC__)
#define OSAL_IS_ARRAY(array)                                                 \
    OSAL_BUILD_ASSERT_OR_ZERO(!__builtin_types_compatible_p(                 \
        __typeof__(array), __typeof__(&(array)[0])))
#else /* Unkown iar or keil */
#define OSAL_IS_ARRAY(array) (0)
#endif

/**
 * @def OSAL_ARRAY_SIZE
 * @brief Counts number of elements inside the array.
 */
#define OSAL_ARRAY_SIZE(array)                                               \
    ((size_t)(OSAL_IS_ARRAY((array)) +                                       \
              (sizeof((array)) / sizeof((array)[0]))))

/**
 * @def OSAL_PART_OF_ARRAY
 * @brief Evaluates to 1 if ptr is part of array, 0 otherwise; compile error if
 * "array" argument is not an array (e.g. "ptr" and "array" mixed up)
 */
#define OSAL_PART_OF_ARRAY(array, ptr)                                       \
    ((ptr) && ((void *)(ptr) >= (void *)&((array)[0]) &&                     \
               (void *)(ptr) < (void *)&((array)[OSAL_ARRAY_SIZE(array)])))

/**
 * @def OSAL_ABS
 * @brief
 */
#define OSAL_ABS(x) ((x) > 0 ? (x) : -(x))

/**
 * @def OSAL_MIN
 * @brief Leaves the minimum of the two 32-bit arguments
 */
#define OSAL_MIN(a, b) ((a) < (b) ? (a) : (b))
/**
 * @def OSAL_MAX
 * @brief Leaves the maximum of the two 32-bit arguments
 */
#define OSAL_MAX(a, b) ((a) < (b) ? (b) : (a))

/**
 * @def OSAL_MSB_32
 * @brief The upper 8 bits of a 32 bit value
 */
/**
 * @def OSAL_LSB_32
 * @brief The lower 8 bits (of a 32 bit value)
 */
//lint -emacro(572,MSB_32) // Suppress warning 572 "Excessive shift value"
#define OSAL_MSB_32(a) (((a)&0xFF000000) >> 24)
#define OSAL_LSB_32(a) ((a)&0x000000FF)

/**
 * @def OSAL_MSB_16
 * @brief The upper 8 bits of a 16 bit value
 */
/**
 * @def OSAL_LSB_16
 * @brief The lower 8 bits (of a 16 bit value)
 */
//lint -emacro(572,MSB_16) // Suppress warning 572 "Excessive shift value"
#define OSAL_MSB_16(a) (((a)&0xFF00) >> 8)
#define OSAL_LSB_16(a) ((a)&0x00FF)

/**
 * @def OSAL_SET_BIT
 * @brief Set a bit in the uint32 word.
 *
 * @param[in] W  Word whose bit is being set.
 * @param[in] B  Bit number in the word to be set.
 */
#define OSAL_SETBIT(W, B) ((W) |= (uint32_t)(1U << (B)))

/**
 * @def OSAL_CLR_BIT
 * @brief Clears a bit in the uint32 word.
 *
 * @param[in] W   Word whose bit is to be cleared.
 * @param[in] B   Bit number in the word to be cleared.
 */
#define OSAL_CLRBIT(W, B) ((W) &= (~(uint32_t)(1U << (B))))

/**
 * @def OSAL_CHECKBIT
 * @brief Checks if a bit is set.
 *
 * @param[in] W   Word whose bit is to be checked.
 * @param[in] B   Bit number in the word to be checked.
 *
 * @retval 1 if bit is set.
 * @retval 0 if bit is not set.
 */
#define OSAL_CHECKBIT(W, B) (((W) >> (B)) & 1)

/* Bit value */
#define OSAL_BIT0 0x01 /**< The value of bit  0 */
#define OSAL_BIT1 0x02 /**< The value of bit  1 */
#define OSAL_BIT2 0x04 /**< The value of bit  2 */
#define OSAL_BIT3 0x08 /**< The value of bit  3 */
#define OSAL_BIT4 0x10 /**< The value of bit  4 */
#define OSAL_BIT5 0x20 /**< The value of bit  5 */
#define OSAL_BIT6 0x40 /**< The value of bit  6 */
#define OSAL_BIT7 0x80 /**< The value of bit  7 */
#define OSAL_BIT8 0x0100 /**< The value of bit  8 */
#define OSAL_BIT9 0x0200 /**< The value of bit  9 */
#define OSAL_BIT10 0x0400 /**< The value of bit 10 */
#define OSAL_BIT11 0x0800 /**< The value of bit 11 */
#define OSAL_BIT12 0x1000 /**< The value of bit 12 */
#define OSAL_BIT13 0x2000 /**< The value of bit 13 */
#define OSAL_BIT14 0x4000 /**< The value of bit 14 */
#define OSAL_BIT15 0x8000 /**< The value of bit 15 */
#define OSAL_BIT16 0x00010000 /**< The value of bit 16 */
#define OSAL_BIT17 0x00020000 /**< The value of bit 17 */
#define OSAL_BIT18 0x00040000 /**< The value of bit 18 */
#define OSAL_BIT19 0x00080000 /**< The value of bit 19 */
#define OSAL_BIT20 0x00100000 /**< The value of bit 20 */
#define OSAL_BIT21 0x00200000 /**< The value of bit 21 */
#define OSAL_BIT22 0x00400000 /**< The value of bit 22 */
#define OSAL_BIT23 0x00800000 /**< The value of bit 23 */
#define OSAL_BIT24 0x01000000 /**< The value of bit 24 */
#define OSAL_BIT25 0x02000000 /**< The value of bit 25 */
#define OSAL_BIT26 0x04000000 /**< The value of bit 26 */
#define OSAL_BIT27 0x08000000 /**< The value of bit 27 */
#define OSAL_BIT28 0x10000000 /**< The value of bit 28 */
#define OSAL_BIT29 0x20000000 /**< The value of bit 29 */
#define OSAL_BIT30 0x40000000 /**< The value of bit 30 */
#define OSAL_BIT31 0x80000000 /**< The value of bit 31 */

/* bitmap interal use @ref OSAL_BITMAP_DECODER and @ref OSAL_BITMAP_ENCODER */
#define OSAL_BITMAP_VALMASK(x) ((1U << (x)) - 1)
#define OASL_BITMAP_MASK(o, w) (OSAL_BITMAP_VALMASK(w) << (o))
#define OSAL_BITMAP_DECODE(v, o, w) (((v) >> (o)) & OSAL_BITMAP_VALMASK(w))
#define OSAL_BITMAP_ENCODE(v, o, w) (((v)&OSAL_BITMAP_VALMASK(w)) << (o))

/**
 * @def OSAL_BITMAP_DECODER
 * @brief decoder bitmap value
 *
 * @param[in] v   Value to decode
 * @param[in] e   End Bit number.
 * @param[in] s   End Bit number.
 *
 * @code
 * uint8_t ctrl;
 *  - bit7-2: type
 *  - bit1-0: id
 * type = OSAL_BITMAP_DECODER(ctrl, 7, 2);
 * id   = OSAL_BITMAP_DECODER(ctrl, 1, 0);
 * @endcode
 */
#define OSAL_BITMAP_DECODER(v, e, s)                                         \
    (OSAL_BUILD_ASSERT_OR_ZERO(((s) <= (e))) +                               \
     OSAL_BITMAP_DECODE((v), (s), (e) - (s) + 1))

/**
 * @def OSAL_BITMAP_ENCODER
 * @brief encoder bitmap value
 *
 * @param[in] v   Value to encode
 * @param[in] e   End Bit number.
 * @param[in] s   End Bit number.
 *
 * @code
 * uint8_t ctrl;
 *  - bit7-2: type
 *  - bit1-0: id
 * ctrl = OSAL_BITMAP_ENCODER(type, 7, 2) | OSAL_BITMAP_ENCODER(id, 1, 0);
 * @endcode
 */
#define OSAL_BITMAP_ENCODER(v, e, s)                                         \
    (OSAL_BUILD_ASSERT_OR_ZERO(((s) <= (e))) +                               \
     OSAL_BITMAP_ENCODE((v), (s), (e) - (s) + 1))

/**
 * @def OSAL_ALIGN(size, align)
 * Return the most contiguous size aligned at specified width. OSAL_ALIGN(13, 4)
 * would return 16.
 */
#define OSAL_ALIGN(size, align) (((size) + (align)-1) & ~((align)-1))

/**
 * @def RT_ALIGN_DOWN(size, align)
 * Return the down number of aligned at specified width. OSAL_ALIGN_DOWN(13, 4)
 * would return 12.
 */
#define OSAL_ALIGN_DOWN(size, align) ((size) & ~((align)-1))

/**
 * @def   OSAL_SECTION_ALIGNMENT
 * @brief The operation of acquiring the stored symbol relies on the size of
 *        the stored type
 */
#define OSAL_SECTION_ALIGNMENT __attribute__((aligned(16)))

/**@brief   Macro for obtaining the address of the beginning of a section.
 *
 * param[in]    section_name    Name of the section.
 * @hideinitializer
 */
#if defined(__CC_ARM)
#define OSAL_SECTION_START_ADDR(section_name)                                \
    &OSAL_CONCAT2(section_name, $$Base)

#elif defined(__GNUC__)
#define OSAL_SECTION_START_ADDR(section_name)                                \
    &OSAL_CONCAT2(__start_, section_name)

#elif defined(__ICCARM__)
#define OSAL_SECTION_START_ADDR(section_name)                                \
    __section_begin(OSAL_STRINGIFY(section_name))
#endif

/**@brief    Macro for obtaining the address of the end of a section.
 *
 * @param[in]   section_name    Name of the section.
 * @hideinitializer
 */
#if defined(__CC_ARM)
#define OSAL_SECTION_END_ADDR(section_name)                                  \
    &OSAL_CONCAT2(section_name, $$Limit)

#elif defined(__GNUC__)
#define OSAL_SECTION_END_ADDR(section_name)                                  \
    &OSAL_CONCAT2(__stop_, section_name)

#elif defined(__ICCARM__)
#define OSAL_SECTION_END_ADDR(section_name)                                  \
    __section_end(OSAL_STRINGIFY(section_name))
#endif

/**@brief   Macro for retrieving the length of a given section, in bytes.
 *
 * @param[in]   section_name    Name of the section.
 * @hideinitializer
 */
#define OSAL_SECTION_LENGTH(section_name)                                    \
    ((size_t)OSAL_SECTION_END_ADDR(section_name) -                           \
     (size_t)OSAL_SECTION_START_ADDR(section_name))

/**@brief   Macro for creating a section.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   data_type       Data type of the variables to be registered in the section.
 *
 * @warning Data type must be word aligned to prevent padding.
 * @hideinitializer
 */
#if defined(__CC_ARM)
#define OSAL_SECTION_DEF(section_name, data_type)                            \
    extern data_type *OSAL_CONCAT2(section_name, $$Base);                    \
    extern void *     OSAL_CONCAT2(section_name, $$Limit)

#elif defined(__GNUC__)
#define OSAL_SECTION_DEF(section_name, data_type)                            \
    extern data_type *OSAL_CONCAT2(__start_, section_name);                  \
    extern void *     OSAL_CONCAT2(__stop_, section_name)

#elif defined(__ICCARM__)
#define OSAL_SECTION_DEF(section_name, data_type)                            \
    _Pragma(OSAL_STRINGIFY(section = OSAL_STRINGIFY(section_name)));
#endif

/**@brief   Macro for declaring a variable and registering it in a section.
 *
 * @details Declares a variable and registers it in a named section. This macro ensures that the
 *          variable is not stripped away when using optimizations.
 *
 * @note The order in which variables are placed in a section is dependent on the order in
 *       which the linker script encounters the variables during linking.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   section_var     Variable to register in the given section.
 * @hideinitializer
 */
#if defined(__CC_ARM)
#define OSAL_SECTION_ITEM_REGISTER(section_name, section_var)                \
    section_var __attribute__((section(OSAL_STRINGIFY(section_name))))       \
        __attribute__((used))

#elif defined(__GNUC__)
#if 0
#define OSAL_SECTION_ITEM_REGISTER(section_name, section_var)                \
    section_var __attribute__((section("." OSAL_STRINGIFY(section_name))))   \
        __attribute__((used))
#else
#define OSAL_SECTION_ITEM_REGISTER(section_name, section_var)                \
    section_var __attribute__((section(OSAL_STRINGIFY(section_name))))       \
        __attribute__((used))
#endif
#elif defined(__ICCARM__)
#define OSAL_SECTION_ITEM_REGISTER(section_name, section_var)                \
    __root section_var @OSAL_STRINGIFY(section_name)
#endif

/**@brief   Macro for retrieving a variable from a section.
 *
 * @warning     The stored symbol can only be resolved using this macro if the
 *              type of the data is word aligned. The operation of acquiring
 *              the stored symbol relies on the size of the stored type. No
 *              padding can exist in the named section in between individual
 *              stored items or this macro will fail.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   data_type       Data type of the variable.
 * @param[in]   i               Index of the variable in section.
 * @hideinitializer
 */
#define OSAL_SECTION_ITEM_GET(section_name, data_type, i)                    \
    ((data_type *)OSAL_SECTION_START_ADDR(section_name) + (i))

/**@brief   Macro for getting the number of variables in a section.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   data_type       Data type of the variables in the section.
 * @hideinitializer
 */
#define OSAL_SECTION_ITEM_COUNT(section_name, data_type)                     \
    OSAL_SECTION_LENGTH(section_name) / sizeof(data_type)

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
 * @} (end addtogroup osal_marco)
 */
/****************************************************************************/
#endif /* OSAL_MARCO_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

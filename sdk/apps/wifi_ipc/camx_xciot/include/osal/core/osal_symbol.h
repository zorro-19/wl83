/*****************************************************************************
 * osal_symbol.h
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
#ifndef OSAL_SYMBOL_H_INCLUDE
#define OSAL_SYMBOL_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_symbol
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

/** syscall section name */
#define OSAL_SYSCALL_SECTION syscall
/** sysvar section name */
#define OSAL_SYSVAR_SECTION sysvar

/* sysvar type */
typedef uint16_t osal_sysvar_type_t;
enum {
    SYSVAR_U8 = 0,
    SYSVAR_U16,
    SYSVAR_U32,
    SYSVAR_U64,
    SYSVAR_S8,
    SYSVAR_S16,
    SYSVAR_S32,
    SYSVAR_S64,
    SYSVAR_PTR,
};

typedef struct {
    /** The name of system variable(Must be first) */
    const char *name;

    /** The address of system variable */
    void *var;

    /** The size of system variable */
    uint16_t size;

    /** The type of system variable */
    osal_sysvar_type_t type;
} OSAL_SECTION_ALIGNMENT osal_sysvar_t;

/* syscall type */
typedef void (*osal_syscall_func_t)(void);

typedef struct {
    /** The name of system call (Must be first) */
    const char *name;

    /** The function address of system call */
    osal_syscall_func_t func;
} OSAL_SECTION_ALIGNMENT osal_syscall_t;

/* use section table record osal_syscall_t */
OSAL_SECTION_DEF(OSAL_SYSCALL_SECTION, osal_syscall_t);

#define OSAL_SYSCALL_EXPORT(func)                                            \
    OSAL_SECTION_ITEM_REGISTER(OSAL_SYSCALL_SECTION,                         \
                               osal_syscall_t syscall_##func) = {            \
        (const char *)OSAL_STRINGIFY(func), (osal_syscall_func_t)func,       \
    };

/* use section table record osal_sysvar_t */
OSAL_SECTION_DEF(OSAL_SYSVAR_SECTION, osal_sysvar_t);

#define OSAL_SYSVAR_EXPORT(var, type)                                        \
    OSAL_SECTION_ITEM_REGISTER(OSAL_SYSVAR_SECTION,                          \
                               osal_sysvar_t sysvar_##var) = {               \
        (const char *)OSAL_STRINGIFY(var), (void *)&var, sizeof(var), type,  \
    };

#define OSAL_SYSVAR_START_ADDR OSAL_SECTION_START_ADDR(OSAL_SYSVAR_SECTION)
#define OSAL_SYSVAR_END_ADDR OSAL_SECTION_END_ADDR(OSAL_SYSVAR_SECTION)
#define OSAL_SYSVAR_COUNT                                                    \
    OSAL_SECTION_ITEM_COUNT(OSAL_SYSVAR_SECTION, osal_sysvar_t)
#define OSAL_SYSVAR_GET(i)                                                   \
    OSAL_SECTION_ITEM_GET(OSAL_SYSVAR_SECTION, osal_sysvar_t, i)

#define OSAL_SYSCALL_START_ADDR OSAL_SECTION_START_ADDR(OSAL_SYSCALL_SECTION)
#define OSAL_SYSCALL_END_ADDR OSAL_SECTION_END_ADDR(OSAL_SYSCALL_SECTION)
#define OSAL_SYSCALL_COUNT                                                   \
    OSAL_SECTION_ITEM_COUNT(OSAL_SYSCALL_SECTION, osal_syscall_t)
#define OSAL_SYSCALL_GET(i)                                                  \
    OSAL_SECTION_ITEM_GET(OSAL_SYSCALL_SECTION, osal_syscall_t, i)

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

#if defined(OSAL_SYMBOL_ENABLE)
const char     *osal_sysvar_typename(osal_sysvar_type_t type);
osal_sysvar_t *osal_sysvar_search(const char *name);
osal_syscall_t *osal_syscall_search(const char *name);
void            osal_syscall_dump(void);
#define SYSCALL_EXPORT(func) OSAL_SYSCALL_EXPORT(func)
#define SYSVAR_EXPORT(var, type) OSAL_SYSVAR_EXPORT(var, type)
#else
#define SYSCALL_EXPORT(func)
#define SYSVAR_EXPORT(var, type)
#endif /* defined(OSAL_SYMBOL_ENABLE) */

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_symbol)
 */
/****************************************************************************/
#endif /* OSAL_SYMBOL_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

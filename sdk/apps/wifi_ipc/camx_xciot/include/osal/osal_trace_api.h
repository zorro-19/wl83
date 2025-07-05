/*****************************************************************************
 * osal_trace_api.h
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
#ifndef OSAL_TRACE_API_H_INCLUDE
#define OSAL_TRACE_API_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_trace_api
 * @{
 */
/*****************************************************************************
 * Included Files
 ****************************************************************************/

#if !defined(OSAL_API_H_INCLUDE)
#error "Only 'osal/osal_api.h' can be included first."
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

#if defined(OSAL_LOG_ENABLE)
/* Log domain name */
#if !defined(OSAL_LOG_DOMAIN)
#define OSAL_LOG_DOMAIN "General"
#endif

/* Log compile level */
#if !defined(OSAL_LOG_COMPILE_LEVEL)
#define OSAL_LOG_COMPILE_LEVEL OSAL_LOG_LEVEL_TRACE
#endif

/* Log run level */
#ifndef OSAL_LOG_RUN_LEVEL
#define OSAL_LOG_RUN_LEVEL OSAL_LOG_LEVEL_DEBUG
#endif

/* log message */
#if 0
#define OSAL_LOG_MESSAGE(domain, level, fmt, ...)                            \
    do {                                                                     \
        if (OSAL_LOG_RUN_LEVEL >= level) {                                   \
            osal_log_message(                                                \
                domain, level, __FILE__, __LINE__, fmt, ##__VA_ARGS__);      \
        }                                                                    \
    } while (0)

/* log hexdump */
#define OSAL_LOG_HEXDUMP(domain, level, prefix, ptr, len)                    \
    do {                                                                     \
        if (OSAL_LOG_RUN_LEVEL >= level) {                                   \
            osal_log_hexdump(                                                \
                domain, level, __FILE__, __LINE__, prefix, ptr, len);        \
        }                                                                    \
    } while (0)
#endif
#if 1
#define OSAL_LOG_MESSAGE(domain, level, fmt, ...)                            \
    do {                                                                     \
        if (OSAL_LOG_RUN_LEVEL >= level) {                                   \
            osal_log_message(                                                \
                domain, level, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__);  \
        }                                                                    \
    } while (0)

/* log hexdump */
#define OSAL_LOG_HEXDUMP(domain, level, prefix, ptr, len)                    \
    do {                                                                     \
        if (OSAL_LOG_RUN_LEVEL >= level) {                                   \
            osal_log_hexdump(                                                \
                domain, level, __FUNCTION__, __LINE__, prefix, ptr, len);    \
        }                                                                    \
    } while (0)
#endif

/**
 * @def T_E/T_E_HEX/T_EH_HEX
 *
 * @brief Writes an ERROR level message to the log.
 *
 * @details Lowest logging level, these messages are logged whenever osal log is
 * active. it's meant to report severe errors, such as those from which it's
 * not possible to recover.
 *
 * @param ... A string optionally containing printf valid conversion specifier,
 * followed by as many values as specifiers.
 */

/**
 * @def T_W/T_W_HEX/T_WH_HEX
 *
 * @brief Writes a WARNING level message to the log.
 *
 * @details available if OSAL_LOG_LEVEL is OSAL_LOG_LEVEL_WARN or higher.
 * It's meant to register messages related to unusual situations that are
 * not necessarily errors.
 *
 * @param ... A string optionally containing printf valid conversion specifier,
 * followed by as many values as specifiers.
 */

/**
 * @def T_I/T_I_HEX/T_IH_HEX
 *
 * @brief Writes an INFO level message to the log.
 *
 * @details available if OSAL_LOG_LEVEL is OSAL_LOG_LEVEL_INFO or higher.
 * It's meant to write generic user oriented messages.
 *
 * @param ... A string optionally containing printf valid conversion specifier,
 * followed by as many values as specifiers.
 */

/**
 * @def T_D/T_D_HEX/T_DH_HEX
 *
 * @brief Writes a DEBUG level message to the log.
 *
 * @details highest logging level, available if OSAL_LOG_LEVEL is
 * OSAL_LOG_LEVEL_DEBUG. It's meant to write developer oriented information.
 *
 * @param ... A string optionally containing printf valid conversion specifier,
 * followed by as many values as specifiers.
 */

/**
 * @def T_T/T_T_HEX/T_TH_HEX
 *
 * @brief Writes a TRACE level message to the log.
 *
 * @details highest logging level, available if OSAL_LOG_LEVEL is
 * OSAL_LOG_LEVEL_TRACE. It's meant to write internal developer oriented information.
 *
 * @param ... A string optionally containing printf valid conversion specifier,
 * followed by as many values as specifiers.
 */
#if (OSAL_LOG_COMPILE_LEVEL >= OSAL_LOG_LEVEL_ALWAY)
#define T_A(...)                                                             \
    OSAL_LOG_MESSAGE(OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_ALWAY, ##__VA_ARGS__)
#define T_A_HEX(byteptr, bytecnt)                                            \
    OSAL_LOG_HEXDUMP(                                                        \
        OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_ALWAY, "", (byteptr), (bytecnt))
#define T_AH_HEX(prefix, byteptr, bytecnt)                                   \
    OSAL_LOG_HEXDUMP(OSAL_LOG_DOMAIN,                                        \
                     OSAL_LOG_LEVEL_ALWAY,                                   \
                     (prefix),                                               \
                     (byteptr),                                              \
                     (bytecnt))
#endif

#if (OSAL_LOG_COMPILE_LEVEL >= OSAL_LOG_LEVEL_ERROR)
#define T_E(...)                                                             \
    OSAL_LOG_MESSAGE(OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_ERROR, ##__VA_ARGS__)
#define T_E_HEX(byteptr, bytecnt)                                            \
    OSAL_LOG_HEXDUMP(                                                        \
        OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_ERROR, "", (byteptr), (bytecnt))
#define T_EH_HEX(prefix, byteptr, bytecnt)                                   \
    OSAL_LOG_HEXDUMP(OSAL_LOG_DOMAIN,                                        \
                     OSAL_LOG_LEVEL_ERROR,                                   \
                     (prefix),                                               \
                     (byteptr),                                              \
                     (bytecnt))
#endif

#if (OSAL_LOG_COMPILE_LEVEL >= OSAL_LOG_LEVEL_WARN)
#define T_W(...)                                                             \
    OSAL_LOG_MESSAGE(OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_WARN, ##__VA_ARGS__)
#define T_W_HEX(byteptr, bytecnt)                                            \
    OSAL_LOG_HEXDUMP(                                                        \
        OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_WARN, "", (byteptr), (bytecnt))
#define T_WH_HEX(prefix, byteptr, bytecnt)                                   \
    OSAL_LOG_HEXDUMP(OSAL_LOG_DOMAIN,                                        \
                     OSAL_LOG_LEVEL_WARN,                                    \
                     (prefix),                                               \
                     (byteptr),                                              \
                     (bytecnt))
#endif

#if (OSAL_LOG_COMPILE_LEVEL >= OSAL_LOG_LEVEL_INFO)
#define T_I(...)                                                             \
    OSAL_LOG_MESSAGE(OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_INFO, ##__VA_ARGS__)
#define T_I_HEX(byteptr, bytecnt)                                            \
    OSAL_LOG_HEXDUMP(                                                        \
        OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_INFO, "", (byteptr), (bytecnt))
#define T_IH_HEX(prefix, byteptr, bytecnt)                                   \
    OSAL_LOG_HEXDUMP(OSAL_LOG_DOMAIN,                                        \
                     OSAL_LOG_LEVEL_INFO,                                    \
                     (prefix),                                               \
                     (byteptr),                                              \
                     (bytecnt))
#endif

#if (OSAL_LOG_COMPILE_LEVEL >= OSAL_LOG_LEVEL_DEBUG)
#define T_D(...)                                                             \
    OSAL_LOG_MESSAGE(OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_DEBUG, ##__VA_ARGS__)
#define T_D_HEX(byteptr, bytecnt)                                            \
    OSAL_LOG_HEXDUMP(                                                        \
        OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_DEBUG, "", (byteptr), (bytecnt))
#define T_DH_HEX(prefix, byteptr, bytecnt)                                   \
    OSAL_LOG_HEXDUMP(OSAL_LOG_DOMAIN,                                        \
                     OSAL_LOG_LEVEL_DEBUG,                                   \
                     (prefix),                                               \
                     (byteptr),                                              \
                     (bytecnt))
#endif

#if (OSAL_LOG_COMPILE_LEVEL >= OSAL_LOG_LEVEL_TRACE)
#define T_T(...)                                                             \
    OSAL_LOG_MESSAGE(OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_TRACE, ##__VA_ARGS__)
#define T_T_HEX(byteptr, bytecnt)                                            \
    OSAL_LOG_HEXDUMP(                                                        \
        OSAL_LOG_DOMAIN, OSAL_LOG_LEVEL_TRACE, "", (byteptr), (bytecnt))
#define T_TH_HEX(prefix, byteptr, bytecnt)                                   \
    OSAL_LOG_HEXDUMP(OSAL_LOG_DOMAIN,                                        \
                     OSAL_LOG_LEVEL_TRACE,                                   \
                     (prefix),                                               \
                     (byteptr),                                              \
                     (bytecnt))
#endif
#endif /* defined(OSAL_LOG_ENABLE) */

/* create dummy macros */
#ifndef T_E
#define T_E(...)
#endif

#ifndef T_W
#define T_W(...)
#endif

#ifndef T_I
#define T_I(...)
#endif

#ifndef T_D
#define T_D(...)
#endif

#ifndef T_T
#define T_T(...)
#endif

#ifndef T_E_HEX
#define T_E_HEX(...)
#endif

#ifndef T_W_HEX
#define T_W_HEX(...)
#endif

#ifndef T_I_HEX
#define T_I_HEX(...)
#endif

#ifndef T_D_HEX
#define T_D_HEX(...)
#endif

#ifndef T_T_HEX
#define T_T_HEX(...)
#endif

#ifndef T_EH_HEX
#define T_EH_HEX(...)
#endif

#ifndef T_WH_HEX
#define T_WH_HEX(...)
#endif

#ifndef T_IH_HEX
#define T_IH_HEX(...)
#endif

#ifndef T_DH_HEX
#define T_DH_HEX(...)
#endif

#ifndef T_TH_HEX
#define T_TH_HEX(...)
#endif

#ifdef OSAL_ASSERT_ENABLE
#define OSAL_ASSERT(exp)                                                     \
    do {                                                                     \
        if (!(exp)) {                                                        \
            T_E("Assert to %s[%s:%d]", #exp, OSAL_STRFUNC, __LINE__);        \
        }                                                                    \
    } while (0)
#else
/* create dummy macros */
#define OSAL_ASSERT(exp)
#endif

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_trace_api)
 */
/****************************************************************************/
#endif /* OSAL_TRACE_API_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

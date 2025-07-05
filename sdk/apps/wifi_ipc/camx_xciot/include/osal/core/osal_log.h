/*****************************************************************************
 * osal_log.h
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

#ifndef OSAL_LOG_H_INCLUDE
#define OSAL_LOG_H_INCLUDE
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
 * @brief Log level.
 */
#define OSAL_LOG_LEVEL_ALWAY 0
#define OSAL_LOG_LEVEL_NONE 1
#define OSAL_LOG_LEVEL_ERROR 2
#define OSAL_LOG_LEVEL_WARN 3
#define OSAL_LOG_LEVEL_INFO 4
#define OSAL_LOG_LEVEL_DEBUG 5
#define OSAL_LOG_LEVEL_TRACE 6

/**
 * @brief Log attributes mask.
 */
typedef enum {
    M_osalLogAttrLevelTag  = 0x01, /**< Level tag.              */
    M_osalLogAttrTimestamp = 0x02, /**< Timestamp.              */
    M_osalLogAttrFuncname  = 0x04, /**< Current function name.  */
    M_osalLogAttrDomain    = 0x08, /**< Domain name.            */
} osalLogAttr_t;

#define OASL_LOG_ATTR_ALL                                                    \
    (M_osalLogAttrLevelTag | M_osalLogAttrDomain | M_osalLogAttrTimestamp |  \
     M_osalLogAttrFuncname)

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

void osal_log_set_level(int level);

int  osal_log_get_level(void);
void osal_log_init(void);
void osal_log_fini(void);
void avsdk_log_start(void);

void osal_log_message(const char *domain,
                      int         level,
                      const char *filename,
                      int         line,
                      const char *fmt,
                      ...);

void osal_log_hexdump(const char *domain,
                      int         level,
                      const char *filename,
                      int         line,
                      const char *prefix,
                      const void *ptr,
                      size_t      len);
void osal_log_lowPrintf(char *domain, int (*log_output)(const char *fmt, ...));

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* OSAL_LOG_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

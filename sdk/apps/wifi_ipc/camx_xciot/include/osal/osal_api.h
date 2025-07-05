/*****************************************************************************
 * osal_api.h
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
#ifndef OSAL_API_H_INCLUDE
#define OSAL_API_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_api
 * @{
 */

/*****************************************************************************
 * API Version Definitions
 ****************************************************************************/

/* OSAL_API_VERSION */
#define OSAL_BUILD_VERSION(major, mirror, build)                             \
    ((major) | (mirror) | (build))
#define OSAL_API_VERSION OSAL_BUILD_VERSION(1, 0, 0)

/* OSAL_PLATFORM */
#define OSAL_PLATFORM_POSIX 0
//#define OSAL_PLATFORM_CMSIS 1
//#define OSAL_PLATFORM_NOOS 2

/*****************************************************************************
 * Configure Definitions
 ****************************************************************************/

/* UT Test */
#define OSAL_UT_TEST

/* 多线程 */
#define OSAL_MULTITHREAD_ENABLE

/* 内存管理 */
#define OSAL_MEM_ENABLE

/* 日志打印 */
#define OSAL_LOG_ENABLE
#define OSAL_ASSERT_ENABLE

/* 符号表 */
#define OSAL_SYMBOL_ENABLE

/* 时间 */
#define OSAL_TIME_ENABLE

/* 双向链表 */
#define OSAL_DLIST_ENABLE

/* 编解码 */
#define OSAL_CODER_ENABLE

/** osal platform */
#define CONFIG_OSAL_PLATFORM OSAL_PLATFORM_POSIX

/* osal components configure */

/*****************************************************************************
 * Included Files
 ****************************************************************************/

/* system */
// #include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
//#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "osal/core/osal_type.h"
#include "osal/core/osal_compiler.h"
#include "osal/core/osal_marco.h"

#include "osal/core/osal_errno.h"
#include "osal/core/osal_symbol.h"
#include "osal/core/osal_log.h"
#include "osal/core/osal_clock.h"
#include "osal/core/osal_panic.h"
#include "osal/core/osal_mem.h"
#include "osal/core/osal_mempool.h"
#include "osal/core/osal_refmap.h"
#include "osal/core/osal_ref.h"

#include "osal/core/osal_options.h"

#include "osal/core/osal_order.h"
#include "osal/core/osal_hex.h"
#include "osal/core/osal_bytes.h"
#include "osal/core/osal_mbuf.h"
#include "osal/core/osal_ringbuffer.h"
#include "osal/core/osal_ini.h"
#include "osal/core/osal_dispatcher.h"

#include "osal/core/osal_dlist.h"
#include "osal/core/osal_lmq.h"
#include "osal/core/osal_thread.h"

#include "osal/core/osal_socket.h"
#include "osal/core/osal_mbedtls.h"

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
 * @brief osal_init is called each time the user enters the library.
 *
 * It ensures that the library is initlialized properly, and also deals with
 * checks such as whether the process has forked since last initialization.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_init(void);

/**
 * @brief osal_fini tears everything down.
 *
 * In the future it may be used to ensure that all resources used by the
 * library are released back to the system.
 */
void osal_fini(void);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_api)
 */
/****************************************************************************/
#endif /* OSAL_API_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

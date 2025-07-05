/*****************************************************************************
 * osal_clock.h
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
#ifndef OSAL_CLOCK_H_INCLUDE
#define OSAL_CLOCK_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_clock
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

#define OSAL_TIME_FOREVER ((uint64_t)-1)
#define OSAL_TIME_ZERO ((uint64_t)0)

/*****************************************************************************
 * Public Types
 ****************************************************************************/

typedef struct {
    /** milliseconds(ms) */
    uint64_t start;

    /** milliseconds(ms) */
    uint64_t end;

    /** active */
    bool active;
} osal_clock_t;

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
 * @brief Wait for Timeout (Time Delay).
 *
 * @param[in] millisecond Absolute time in millisecond.
 */
void osal_mdelay(uint64_t millisecond);

/**
 * @brief Get relative time since a fixed but unspecified starting point.
 *
 * Relative time includes any time that the processor is suspended.
 *
 * @return The relative time in milliseconds(ms).
 */
uint64_t osal_clock_reltime(void);

/**
 * @brief Get absolute time since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
 *
 * @return The absolute time in milliseconds(ms).
 */
uint64_t osal_clock_utctime(void);

/**
 * @brief Mark a start time, so that future calls to osal_clock_elapsed will
 * report the time since osal_clock_start() was called.
 *
 * @param[in] clockptr clockTime record.
 */
void osal_clock_start(osal_clock_t *clockptr);

/**
 * @brief Mark an end time, so calls to osal_clock_elapsed() will return the
 * difference between this end time and the start time.
 *
 * @param[in] clockptr clockTime record.
 */
void osal_clock_stop(osal_clock_t *clockptr);

/**
 * @brief Reset a start time.
 *
 * @param[in] clockptr clockTime record.
 */
void osal_clock_reset(osal_clock_t *clockptr);

/**
 * @brief Resumes a timer that has previously been stopped with osal_clock_stop.
 *
 * @param[in] clockptr clockTime record.
 */
void osal_clock_continue(osal_clock_t *clockptr);

/**
 * @brief Elapsed time values(milliseconds).
 *
 * If @clockptr has been started but not stopped,
 * - obtains the time since the timer was started.
 *
 * If @pTime has been stopped,
 * -  obtains the elapsed time between the time it was started and
 *    the time it was stopped.
 *
 * @param[in] clockptr - clocktime record.
 *
 * @return milliseconds elapsed.
 */
uint64_t osal_clock_elapsed(osal_clock_t *clockptr);

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_clock)
 */
/****************************************************************************/
#endif /* OSAL_CLOCK_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/

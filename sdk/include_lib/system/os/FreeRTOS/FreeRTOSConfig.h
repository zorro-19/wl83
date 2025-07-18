/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.  See
 * http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION					1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1
#define configUSE_IDLE_HOOK						1
#define configUSE_TICK_HOOK						0
#define configUSE_DAEMON_TASK_STARTUP_HOOK		1
#define configTICK_RATE_HZ						( 100 ) /* In this non-real time simulated environment the tick frequency has to be at least a multiple of the Win32 tick frequency, and therefore very slow. */
#define configMINIMAL_STACK_SIZE				( ( unsigned int) 256) /* In this simulated case, the stack only has to hold one small structure as the real stack is part of the win32 thread. */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 30 * 1024 ) )
#define configMAX_TASK_NAME_LEN					( 64 )
#define configUSE_TRACE_FACILITY				1
#define configUSE_16_BIT_TICKS					0
#define configIDLE_SHOULD_YIELD					1
#define configUSE_MUTEXES						1
#define configCHECK_FOR_STACK_OVERFLOW			0
#define configUSE_RECURSIVE_MUTEXES				1
#define configQUEUE_REGISTRY_SIZE				20
#define configUSE_MALLOC_FAILED_HOOK			1
#define configUSE_APPLICATION_TASK_TAG			1
#define configUSE_COUNTING_SEMAPHORES			1
#define configUSE_ALTERNATIVE_API				0
#define configUSE_QUEUE_SETS					0
#ifdef CONFIG_FPGA_ENABLE
#define configUSE_TASK_NOTIFICATIONS		    1
#else
#define configUSE_TASK_NOTIFICATIONS			0
#endif
#define configSUPPORT_STATIC_ALLOCATION			1
#define configCPU_USAGE_CALCULATE				0

#if ( configCPU_USAGE_CALCULATE != 0)
#define configCPU_USAGE_CALC_PERIOD				10
#undef  configUSE_TICK_HOOK
#define configUSE_TICK_HOOK						1
unsigned char ucGetCpuUsage(unsigned char cpuid);
#endif


/* Software timer related configuration options. */
#define configUSE_TIMERS						0
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH				20
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

#define configMAX_PRIORITIES					( 31 )


#ifdef __GCC_PI32V2__
#include "pi32v2/portmacro.h"
#endif

#ifdef __GCC_PI32_LTO__
#include "pi32_lto/portmacro.h"
#endif

#ifdef __GCC_Q32S__
#include "q32s/portmacro.h"
#endif


/* Run time stats gathering configuration options. */
unsigned long ulGetRunTimeCounterValue(void);   /* Prototype of function that returns run time counter. */
void vConfigureTimerForRunTimeStats(void);	/* Prototype of function that initialises the run time counter. */
void vMainConfigureTimerForRunTimeStats(void);
unsigned long ulMainGetRunTimeCounterValue(void);
#define configGENERATE_RUN_TIME_STATS			1
// #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    vMainConfigureTimerForRunTimeStats();
#define portGET_RUN_TIME_COUNTER_VALUE() ulGetRunTimeCounterValue()

/* Co-routine related configuration options. */
#define configUSE_CO_ROUTINES 					1
#define configMAX_CO_ROUTINE_PRIORITIES			( 2 )

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function.  In most cases the linker will remove unused
functions anyway. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			0
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_uxTaskGetStackHighWaterMark		1
#define INCLUDE_xTaskGetSchedulerState			0
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1
#define INCLUDE_xTaskGetIdleTaskHandle			1
#define INCLUDE_xTaskGetHandle					1
#define INCLUDE_eTaskGetState					1
#define INCLUDE_xSemaphoreGetMutexHolder		1
#define INCLUDE_xTimerPendFunctionCall			0
#define INCLUDE_xTaskAbortDelay					1

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 1
#define configTHREAD_LOCAL_STORAGE_DELETE_CALLBACKS 1
/* It is a good idea to define configASSERT() while developing.  configASSERT()
uses the same semantics as the standard C assert() macro. */
#ifndef configASSERT
#include "generic/printf.h"
static inline  void vAssertCalled(const char *str, unsigned int ulLine)
{
    /*
    if(OS_CPU_ID == 0)
    {
    	C1_CON |=BIT(1) ;
    }else
    {
    	C0_CON |=BIT(1) ;
    }*/
    local_irq_disable();
    printf("%s %d\n", str, ulLine) ;
    ASSERT(0);
    /*while (1);*/

}
#endif

#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled(__func__, __LINE__)

/* Include the FreeRTOS+Trace FreeRTOS trace macro definitions. */
#define TRACE_ENTER_CRITICAL_SECTION() portENTER_CRITICAL()
#define TRACE_EXIT_CRITICAL_SECTION() portEXIT_CRITICAL()
//#include "trcKernelPort.h"

#endif /* FREERTOS_CONFIG_H */

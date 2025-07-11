/***********************************Jieli tech************************************************
File : os_cfg.h
By   : Juntham
date : 2014-07-03 09:09
 ********************************************************************************************/

#ifndef OS_CFG_H
#define OS_CFG_H
#include "os/os_cpu.h"

#define OS_TIME_SLICE_EN          1

#define OS_PRIORITY_INVERSION     1     /*是否处理优先级翻转*/

/* ---------------------- MISCELLANEOUS ----------------------- */
#define OS_ARG_CHK_EN             0    /* Enable (1) or Disable (0) argument checking                  */
#define OS_CPU_HOOKS_EN           1    /* hooks are found in the processor port files         */

#if OS_TIME_SLICE_EN > 0
#define OS_LOWEST_PRIO            (0)    /* Defines the lowest priority that can be assigned ...         */
#define tskIDLE_PRIORITY		OS_LOWEST_PRIO
#else
#define OS_LOWEST_PRIO            (0+OS_CPU_CORE-1)/* Defines the lowest priority that can be assigned   */
#endif

#define  OS_IDLE_PRIO            (OS_LOWEST_PRIO)     /* IDLE      task priority                     */

#define OS_MAX_TASKS              31    /* Max. number of tasks in your application, MUST be >= 2       */
#define configMAX_PRIORITIES	OS_MAX_TASKS

#define OS_SCHED_LOCK_EN          1    /*  Include code for OSSchedLock() and OSSchedUnlock()       */

#define OS_PARENT_TCB             1    /* 是否记录父任务的TCB */

#define OS_CHILD_TCB              1    /* 是否记录子任务的TCB */

/* ----------------------TASK MESSAGE QUEUES ---------------------- */
#define OS_TASKQ_EN               1   /* Enable (1) or Disable (0) code generation for QUEUES         */
#define OS_TASKQ_ACCEPT_EN        1    /*     Include code for OSTaskQAccept()                             */
#define OS_TASKQ_PEND_EN          1    /*     Include code for OSTaskQAccept()                             */
#define OS_TASKQ_FLUSH_EN         1    /*     Include code for OSTaskQFlush()                              */
#define OS_TASKQ_POST_EN          1    /*     Include code for OSTaskQPost()                               */
#define OS_TASKQ_POST_FRONT_EN    1    /*     Include code for OSTaskQPostFront()                          */
#define OS_TASKQ_QUERY_EN         1    /*     Include code for OSTaskQQuery()                              */

/* ---------------- MUTUAL EXCLUSION SEMAPHORES --------------- */
#define OS_MUTEX_EN               1    /* Enable (1) or Disable (0) code generation for MUTEX          */
#define OS_MUTEX_ACCEPT_EN        1    /*     Include code for OSMutexAccept()                         */
#define OS_MUTEX_DEL_EN           1    /*     Include code for OSMutexDel()                            */
#define OS_MUTEX_QUERY_EN         0    /*     Include code for OSMutexQuery()                          */

/* ------------------------ SEMAPHORES ------------------------ */
#define OS_SEM_EN                 1    /* Enable (1) or Disable (0) code generation for SEMAPHORES     */
#define OS_SEM_ACCEPT_EN          1    /*    Include code for OSSemAccept()                            */
#define OS_SEM_DEL_EN             1    /*    Include code for OSSemDel()                               */
#define OS_SEM_QUERY_EN           1    /*    Include code for OSSemQuery()                             */
#define OS_SEM_SET_EN             1    /*    Include code for OSSemSet()                               */

/* ---------------------- MESSAGE QUEUES ---------------------- */
#define OS_Q_EN                   1    /* Enable (1) or Disable (0) code generation for QUEUES         */
#define OS_Q_ACCEPT_EN            1    /*     Include code for OSQAccept()                             */
#define OS_Q_DEL_EN               1    /*     Include code for OSQDel()                                */
#define OS_Q_FLUSH_EN             1    /*     Include code for OSQFlush()                              */
#define OS_Q_POST_EN              1    /*     Include code for OSQPost()                               */
#define OS_Q_POST_FRONT_EN        1    /*     Include code for OSQPostFront()                          */
#define OS_Q_POST_OPT_EN          1    /*     Include code for OSQPostOpt()                            */
#define OS_Q_QUERY_EN             1    /*     Include code for OSQQuery()                              */

/* ----------------------- EVENT FLAGS ------------------------ */
#define OS_FLAG_EN                1    /* Enable (1) or Disable (0) code generation for EVENT FLAGS    */
#define OS_MAX_FLAGS              1    /* Max. number of Event Flag Groups    in your application      */
#define OS_FLAG_WAIT_CLR_EN       1    /* Include code for Wait on Clear EVENT FLAGS                   */
#define OS_FLAG_ACCEPT_EN         1    /*     Include code for OSFlagAccept()                          */
#define OS_FLAG_DEL_EN            1    /*     Include code for OSFlagDel()                             */
#define OS_FLAG_NAME_SIZE         0//32    /*     Determine the size of the name of an event flag group    */
#define OS_FLAG_QUERY_EN          1    /*     Include code for OSFlagQuery()                           */
#define OS_FLAGS_NBITS           32    /* Size in #bits of OS_FLAGS data type (8, 16 or 32)            */

/* --------------------- TASK MANAGEMENT ---------------------- */
#define OS_TASK_CHANGE_PRIO_EN    1    /*     Include code for OSTaskChangePrio()                      */
#define OS_TASK_CREATE_EN         1    /*     Include code for OSTaskCreate()                          */
#define OS_TASK_DEL_EN            1    /*     Include code for OSTaskDel()                             */
#define OS_TASK_QUERY_EN          0    /*     Include code for OSTaskQuery()                           */
#define OS_TASK_SUSPEND_EN        1    /*     Include code for OSTaskSuspend() and OSTaskResume()      */
#define OS_TASK_SW_HOOK_EN        0    /*     Include code for OSTaskSwHook()                          */
#define OS_TASK_STK_CHK           1

/* --------------------- TIME MANAGEMENT ---------------------- */
#define OS_TIME_DLY_HMSM_EN       0    /*     Include code for OSTimeDlyHMSM()                         */
#define OS_TIME_DLY_RESUME_EN     1    /*     Include code for OSTimeDlyResume()                       */
#define OS_TIME_GET_SET_EN        1    /*     Include code for OSTimeGet() and OSTimeSet()             */
#define OS_TIME_TICK_HOOK_EN      0    /*     Include code for OSTimeTickHook()                        */

#define  OS_EVENT_EN      ((OS_Q_EN > 0) || (OS_SEM_EN > 0) || (OS_MUTEX_EN > 0) || (OS_FLAG_EN > 0))


//for make
#ifndef configSUPPORT_DYNAMIC_ALLOCATION
/* Defaults to 1 for backward compatibility. */
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#endif

#ifndef OS_CPU_NUM
#define OS_CPU_NUM              CPU_CORE_NUM
#endif /* #ifndef OS_CPU_NUM */

#ifndef OS_MBOX_EN
#define OS_MBOX_EN 0
#endif

#ifndef OS_MEM_EN
#define OS_MEM_EN 0
#endif

#ifndef configAPPLICATION_ALLOCATED_HEAP
#define configAPPLICATION_ALLOCATED_HEAP 0
#endif

#ifndef configUSE_MALLOC_FAILED_HOOK
#define configUSE_MALLOC_FAILED_HOOK 0
#endif

#ifndef portTICK_PERIOD_MS
#define portTICK_PERIOD_MS          (1000 / OS_TICKS_PER_SEC)
#endif

#ifndef configMAX_TASK_NAME_LEN
#define configMAX_TASK_NAME_LEN     64
#endif

#ifndef portMAX_DELAY
#define portMAX_DELAY               0xffff
#endif

#ifndef configSYSTICK_CLOCK_HZ
#define configSYSTICK_CLOCK_HZ      clk_get("sys")
#endif

#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP       4

#endif

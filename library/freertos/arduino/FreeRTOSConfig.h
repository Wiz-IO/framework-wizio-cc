#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

#define configCPU_CLOCK_HZ              ( ( unsigned long ) 48000000 )
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configUSE_PREEMPTION            1
#define configUSE_TIME_SLICING          0
#define configMAX_PRIORITIES            ( 10UL )
#define configIDLE_SHOULD_YIELD         0
#define configUSE_16_BIT_TICKS          0
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 256 )
#define configMAX_TASK_NAME_LEN         ( 12 )

#define configAPPLICATION_ALLOCATED_HEAP 2 /* max size */

#define configSUPPORT_STATIC_ALLOCATION 0 /* need vApplicationGetIdleTaskMemory() */

/* Use the system definition, if there is one. */
#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS       __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS       3     /* 8 priority levels */
#endif
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    1
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         0x07
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configKERNEL_INTERRUPT_PRIORITY                 (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))


/* Constants that build features in or out. */
#define configUSE_MUTEXES                       1
#define configUSE_TICKLESS_IDLE                 1
#define configUSE_APPLICATION_TASK_TAG          1  /* Need by POSIX/pthread */
#define configUSE_CO_ROUTINES                   0
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_QUEUE_SETS                    0
#define configUSE_TASK_NOTIFICATIONS            1

/* Constants that define which hook (callback) functions should be used. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_MALLOC_FAILED_HOOK            0

#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           0
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTaskResumeFromISR              0
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xSemaphoreGetMutexHolder        0
#define INCLUDE_xTimerPendFunctionCall          0

#endif // FREERTOS_CONFIG_H
#pragma once

#include <stdint.h>


/** @name Configuration State Flags */
/// @{
#define EW32_CONFIG_YES                         1    /**< Affirmative state flag. */
#define EW32_CONFIG_NO                          0    /**< Negative state flag. */
/// @}

/** @name Target Platform Identifiers */
/// @{
#define EW32_PLATFORM_ESP                       1    /**< Espressif ESP-IDF platform target. */
#define EW32_PLATFORM_ARDUINO                   2    /**< Arduino framework target. */
#define EW32_PLATFORM_ARDUINO_ESP32             3    /**< Arduino ESP32 framework target. */
#define EW32_PLATFORM_STM32                     4    /**< STM32 microcontroller target. */
#define EW32_PLATFORM_RPPICO                    5    /**< Raspberry PI Pico microcontroller target. */

#define EW32_PLATFORM_TAKSAPI_RTOS                  1   /**< RTOS as driver tasks */
#define EW32_PLATFORM_TAKSAPI_TIMER                 2   /**< timer as driver tasks */
#define EW32_PLATFORM_TAKSAPI_ASYNC                 3   /**< Raspberry PI Pico FreeRTOS + async as driver tasks */
/// @}

#ifndef EW32_LOGGING_NUMOFHANDLER
#define EW32_LOGGING_NUMOFHANDLER                   2 
#endif 

#define EW32_LOGGING_LOCKAPI_ATOMIC                 1
#define EW32_LOGGING_LOCKAPI_CSECTION               2
#define EW32_LOGGING_LOCKAPI_MUTEX                  3

#define EW32_LOGGING_LEVEL_DEBUG    0
#define EW32_LOGGING_LEVEL_INFO     1
#define EW32_LOGGING_LEVEL_WARNING  2
#define EW32_LOGGING_LEVEL_ERROR    3
#define EW32_LOGGING_LEVEL_CRITICAL 4

#ifndef EW32_LOGGING_MIN_LEVEL
#ifdef _DEBUG
    #define EW32_LOGGING_MIN_LEVEL  EW32_LOGGING_LEVEL_DEBUG
#else
    #define EW32_LOGGING_MIN_LEVEL  EW32_LOGGING_LEVEL_ERROR
#endif
#endif


/// ================ DO NOT EDIT AFTER THIS LINE ================


#ifndef EW32_FREERTOS_ON_CORE
#define EW32_FREERTOS_ON_CORE 0
#endif

#ifndef EW32_PLATFORM
#error "No Platform Defined, please set build flag -DEW32_PLATFORM={PLATFORMID}" 
#endif

#if EW32_PLATFORM == EW32_PLATFORM_ESP
#define EW32_TASKAPI_PLATFORM   EW32_PLATFORM_TAKSAPI_RTOS
#define EW32_TASK_IDLE_PRIORITY 0U
#define EW32_LOGGING_LOCKAPI    EW32_LOGGING_LOCKAPI_ATOMIC
#endif

#if EW32_PLATFORM == EW32_PLATFORM_RPPICO
#define EW32_TASKAPI_PLATFORM   EW32_PLATFORM_TAKSAPI_RTOS
#define EW32_TASK_IDLE_PRIORITY 0U
#define EW32_LOGGING_LOCKAPI    EW32_LOGGING_LOCKAPI_ATOMIC

#endif


#define EW32_WEAK           __attribute__((weak))
#define EW32_WEAK_INLINE    __attribute__((weak, always_inline)) inline
#define EW32_PACKED         __attribute__((packed))

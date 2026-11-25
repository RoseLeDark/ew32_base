/*
 * SPDX-License-Identifier: EUPL-1.2
 *
 * Copyright (c) 2026 Amber-Sophia "RoseLeBlood" Schröck (gender:divers dey/deren )
 *
 * This file is part of ew32_devm.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.2 or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see:
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

 
#pragma once

#include <stdint.h>


/** @name Configuration State Flags */
/// @{
#define EW32_CONFIG_YES                         1    /**< Affirmative state flag. */
#define EW32_CONFIG_NO                          0    /**< Negative state flag. */
/// @}

#define EW32_YES 1
#define EW32_NO 0

/** @name Target Platform Identifiers */
/// @{
#define EW32_PLATFORM_ESP                       1    /**< Espressif ESP-IDF platform target. */
#define EW32_PLATFORM_ARDUINO                   2    /**< Arduino framework target. */
#define EW32_PLATFORM_ARDUINO_ESP32             3    /**< Arduino ESP32 framework target. */
#define EW32_PLATFORM_STM32                     4    /**< STM32 microcontroller target. */
#define EW32_PLATFORM_RPPICO                    5    /**< Raspberry PI Pico microcontroller target. */

#define EW32_PLATFORM_OSAPI_FREERTOS                  1   /**< RTOS as driver tasks */

/// @}

#ifndef EW32_MAX_OPEN_FILES
#define EW32_MAX_OPEN_FILES                     16
#endif

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
#if EW32_DEBUG == 1
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



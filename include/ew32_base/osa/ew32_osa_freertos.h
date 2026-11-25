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

#include "../ew32_config.h"
#include "../ew32_types.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

typedef TaskHandle_t        ew32_osa_task_t;
typedef SemaphoreHandle_t   ew32_semaphore_t;

#ifdef EW32_OSA_TASK_IDLE_PRIORITY
#undef EW32_OSA_TASK_IDLE_PRIORITY
#endif

#define EW32_OSA_TASK_IDLE_PRIORITY tskIDLE_PRIORITY

#define EW32_OSA_HAVE_YIELD                        1
#define EW32_OSA_HAVE_CRITICAL_SECTION             1
#define EW32_OSA_HAVE_DELAY                        1



#define EW32_OSA_CS_INIT                     portMUX_INITIALIZER_UNLOCKED

#define ew32_osa_cs_lock(X)                  taskENTER_CRITICAL( (X) )
#define ew32_osa_cs_ulock(X)                 taskEXIT_CRITICAL( (X) )


#define  ew32_osa_delay(X)                   vTaskDelay( (X) )
#define  ew32_osa_delay_until(LASTTIME, INC) xTaskDelayUntil( (LASTTIME), (INC) )

#ifdef __cplusplus
extern "C" {
#endif


void ew32_osa_task_yield(uint8_t isr);


#ifdef __cplusplus
}
#endif

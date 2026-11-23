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

#if EW32_PLATFORM == EW32_PLATFORM_RPPICO
#define EW32_TASKAPI_PLATFORM       EW32_PLATFORM_OSAPI_FREERTOS
#define EW32_TASK_IDLE_PRIORITY     0U
#define EW32_LOGGING_LOCKAPI        EW32_LOGGING_LOCKAPI_ATOMIC
#define EW32_TASKAPI_PLATFORM_SUB   2
#include "ew32_osa_freertos.h"
#endif

#if EW32_PLATFORM == EW32_PLATFORM_ESP
#define EW32_TASKAPI_PLATFORM   EW32_PLATFORM_OSAPI_FREERTOS
#define EW32_LOGGING_LOCKAPI    EW32_LOGGING_LOCKAPI_ATOMIC
#define EW32_TASKAPI_PLATFORM_SUB   1

#include "../hwd/esp32/ew32_hal_esp32.h"
#include "ew32_osa_freertos.h"
#endif



typedef uint32_t ew32_error_t;

#define EW32_OSA_TASK_PRIORITY_IDLE         EW32_OSA_TASK_IDLE_PRIORITY           /*!< Priority for no real time operations - idle task */
#define EW32_OSA_TASK_PRIORITY_LOWEST     ( EW32_TASK_IDLE_PRIORITY + 1U )  /*!< Priority for lowest operation  */
#define EW32_OSA_TASK_PRIORITY_LOW        ( EW32_TASK_IDLE_PRIORITY + 2U )  /*!< Priority for low operation  */
#define EW32_OSA_TASK_PRIORITY_NORMAL     ( EW32_TASK_IDLE_PRIORITY + 3U )  /*!< Priority for tasks for normal operatins - user interfaces for example */
#define EW32_OSA_TASK_PRIORITY_HALFCRT    ( EW32_TASK_IDLE_PRIORITY + 4U )  /*!< Priority for tasks with normal deadlines and not a lot of processings*/
#define EW32_OSA_TASK_PRIORITY_URGENT     ( EW32_TASK_IDLE_PRIORITY + 5U )  /*!< priority for tasks with short deadlines and a lot of processings */
#define EW32_OSA_TASK_PRIORITY_CRITICAL   ( EW32_TASK_IDLE_PRIORITY + 6U )  /*!< Priority for critical tasks - the highest priority  */


#define EW32_OSA_TASK_RUNNING               0     /* A task is querying the state of itself, so must be running. */
#define EW32_OSA_TASK_READY                 1            /* The task being queried is in a read or pending ready list. */
#define EW32_OSA_TASK_BLOCKED               2         /* The task being queried is in the Blocked state. */
#define EW32_OSA_TASK_SUSPEND               3       /* The task being queried is in the Suspended state, or is in the Blocked state with an infinite time out. */
#define EW32_OSA_TASK_DELETED               4         /* The task being queried has been deleted, but its TCB has not yet been freed. */
#define EW32_OSA_TASK_INVALID               5       /* Used as an 'invalid state' value. */


#ifdef __cplusplus
extern "C" {
#endif

typedef void (* ew32_task_handle)( void * );
typedef uint8_t* ew32_osa_csec_t;

void ew32_osa_task_init();

ew32_error_t ew32_osa_task_create(ew32_task_handle task, uint16_t stackSize, uint8_t prio, const char* strName, 
                             void* userdata, uint8_t core, ew32_osa_task_t* tk);

ew32_error_t ew32_osa_task_delay(uint32_t delay);
ew32_error_t ew32_osa_task_suspend(ew32_osa_task_t task);
ew32_error_t ew32_osa_task_resume(ew32_osa_task_t task, uint8_t isr);
ew32_error_t ew32_osa_task_resumeall();

ew32_osa_task_t  ew32_osa_task_current(uint8_t isr);
void             ew32_osa_task_destroy(ew32_osa_task_t task);

uint32_t        ew32_osa_task_getstate(ew32_osa_task_t task);
ew32_error_t    ew32_osa_task_setprio(ew32_osa_task_t task, uint8_t prio);
uint8_t         ew32_osa_task_getprio(ew32_osa_task_t task, uint8_t isr);



ew32_error_t    ew32_osa_task_getbyname(const char* strName, ew32_osa_task_t* task);

#if EW32_OSA_HAVE_YIELD == 0
void ew32_osa_task_yield(uint8_t isr);
#endif

/// --------------  Semaphore API --------------
#define EW32_INFINITY                   -1

ew32_semaphore_t ew32_osa_smph_mutex_create();
ew32_semaphore_t ew32_osa_smph_binary_create();
ew32_semaphore_t ew32_osa_smph_counting_create(uint32_t baseCount, uint32_t startCount);

ew32_error_t ew32_osa_smph_lock_ex(ew32_semaphore_t handle, int32_t timeout, uint8_t isr);
ew32_error_t ew32_osa_smph_unlock_ex(ew32_semaphore_t handle, uint8_t isr);
ew32_error_t ew32_osa_smph_desroy(ew32_semaphore_t handle);

uint32_t     ew32_osa_smph_getcount(ew32_semaphore_t handle);


ew32_bool_t ew32_osa_semph_ifowner(ew32_semaphore_t handle, ew32_osa_task_t task, const uint8_t isr);

ew32_semaphore_t ew32_osa_smph_recursive_create();

ew32_error_t ew32_osa_smph_recursive_lock(ew32_semaphore_t handle, int32_t timeout);
ew32_error_t ew32_osa_smph_recursive_unlock(ew32_semaphore_t handle);


#define ew32_osa_smph_trylock( HANDLE )            ew32_osa_smph_lock ( (HANDLE), 1, EW32_NO)

#define ew32_osa_smph_lock( LOCK, TIMEOUT )     ew32_osa_smph_lock_ex( (LOCK), (TIMEOUT), EW32_NO )
#define ew32_osa_smph_unlock( LOCK )            ew32_osa_smph_unlock_ex( (LOCK),  EW32_NO )

#define ew32_osa_smph_trylock_isr( HANDLE )        ew32_osa_smph_lock_ex ( (HANDLE), 1, EW32_YES)
#define ew32_osa_smph_lock_isr( HANDLE, TIMEOUT ) ew32_osa_smph_lock_ex( (HANDLE), (TIMEOUT), EW32_YES )
#define ew32_osa_smph_unlock_isr( HANDLE )        ew32_osa_smph_unlock_ex( (HANDLE),  EW32_YES )

#define ew32_osa_smph_owner( HANDLE )              ew32_osa_semph_ifowner( (HANDLE) , ew32_osa_task_current(EW32_NO), EW32_NO )        
#define ew32_osa_smph_owner_isr( HANDLE )          ew32_osa_semph_ifowner( (HANDLE) , ew32_osa_task_current(EW32_YES), EW32_YES ) 

/// --------------  System API --------------



#if EW32_OSA_HAVE_DELAY == 0
void ew32_osa_delay(uint32_t x);
ew32_error_t ew32_osa_delay_until(uint32_t* lastTime, const uint32_t increment);
#endif

void ew32_osa_cli();
void ew32_osa_sti();

uint64_t         ew32_osa_getticks();

#ifdef __cplusplus
}
#endif

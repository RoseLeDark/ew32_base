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

#include <stdio.h>
#include "ew32_base/osa/ew32_api.h"
#include "ew32_base/ew32_error.h"
// TODO: Add C source content

#ifdef EW32_PLATFORM == EW32_PLATFORM_ESP
#include "ew32_base/ew32_logging.h"

#if EW32_PLATFORM == EW32_PLATFORM_ESP || EW32_PLATFORM ==  EW32_PLATFORM_ARDUINO_ESP32
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#endif


ew32_semaphore_t ew32_osa_smph_mutex_create() {
    return xSemaphoreCreateMutex();
}
ew32_semaphore_t ew32_osa_smph_binary_create() {
    return xSemaphoreCreateBinary();
}
ew32_semaphore_t ew32_osa_smph_counting_create(uint32_t baseCount, uint32_t startCount)  {
    return xSemaphoreCreateCounting(baseCount, startCount);

}
ew32_error_t ew32_osa_smph_desroy(ew32_semaphore_t handle) {
    if(handle == NULL) return EW32_ERROR_NULL;
    vSemaphoreDelete(handle);
    return 0;
}


ew32_error_t ew32_osa_smph_lock_ex(ew32_semaphore_t handle, int32_t timeout, uint8_t isr) {
    ew32_error_t _ret = EW32_ERROR;

    if(handle == NULL) return EW32_ERROR_NULL;

    if(isr == EW32_YES) { 
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        if(xSemaphoreTakeFromISR(handle, &xHigherPriorityTaskWoken)   == pdTRUE ) {
            _ret = EW32_ERROR_OK;
        }
        if (xHigherPriorityTaskWoken == pdTRUE) {
            portYIELD_FROM_ISR();
        }
        
    } else {
        if(xSemaphoreTake(handle, timeout == EW32_INFINITY ? portMAX_DELAY : timeout )  == pdTRUE ) {
            _ret = EW32_ERROR_OK;
        }
    }
    return _ret;
}
ew32_error_t ew32_osa_smph_unlock_ex(ew32_semaphore_t handle, uint8_t isr) {
    ew32_error_t _ret = EW32_ERROR;

    if(isr == EW32_YES) { 
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        if(xSemaphoreGiveFromISR(handle, &xHigherPriorityTaskWoken)   == pdTRUE ) {
            _ret = EW32_ERROR_OK;
        }
        if (xHigherPriorityTaskWoken == pdTRUE) {
            portYIELD_FROM_ISR();
        }
    } else {
        if(xSemaphoreGive(handle)  == pdTRUE ) {
            _ret = EW32_ERROR_OK;
        }
    }
    return _ret;
}

uint32_t     ew32_osa_smph_getcount(ew32_semaphore_t handle) {
    return uxSemaphoreGetCount(handle);
}



ew32_semaphore_t ew32_osa_smph_recursive_create() {
    return xSemaphoreCreateRecursiveMutex();
}

ew32_error_t ew32_osa_smph_recursive_lock_ex(ew32_semaphore_t handle, int32_t timeout) {
    ew32_error_t _ret = EW32_ERROR;

    if(handle == NULL) return EW32_ERROR_NULL;


    if(xSemaphoreTakeRecursive(handle, timeout == EW32_INFINITY ? portMAX_DELAY : timeout )  == pdTRUE ) {
        _ret = EW32_ERROR_OK;
    }
    
    return _ret;
}
ew32_error_t ew32_osa_smph_recursive_unlock_ex(ew32_semaphore_t handle) {
    ew32_error_t _ret = EW32_ERROR;

    if(handle == NULL) return EW32_ERROR_NULL;


    if(xSemaphoreGiveRecursive(handle)  == pdTRUE ) {
        _ret = EW32_ERROR_OK;
    }
    
    return _ret;
}

ew32_bool_t ew32_osa_semph_ifowner(ew32_semaphore_t handle, ew32_osa_task_t task, const uint8_t isr) {
    ew32_osa_task_t _ownerTask;

    if(isr == EW32_YES) {
        _ownerTask = xSemaphoreGetMutexHolderFromISR(handle);
    } else {
        _ownerTask = xSemaphoreGetMutexHolder(handle);
    }
    
    return (_ownerTask == task ) ? ewTRUE :  ewFALSE;
}
#endif
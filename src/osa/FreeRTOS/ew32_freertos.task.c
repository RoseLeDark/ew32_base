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


#if EW32_TASKAPI_PLATFORM_SUB ==   2
#include <pico/time.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

extern "C" {

    void idle_task (void*) {
        for(;;) {
            vPortYield();
        }
    }
}
#endif

#if EW32_PLATFORM == EW32_PLATFORM_ESP || EW32_PLATFORM ==  EW32_PLATFORM_ARDUINO_ESP32
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#endif



void ew32_osa_task_init() {
    #if EW32_TASKAPI_PLATFORM_SUB ==   2
        TaskHandle_t _task;
        xTaskCreate(idle_task, "idle_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &_task);


        #if configUSE_CORE_AFFINITY && configNUMBER_OF_CORES > 1
            vTaskCoreAffinitySet(_task, EW32_FREERTOS_ON_CORE);
        #else
            (void)_task;
        #endif

        vTaskStartScheduler ();
    #endif
}

ew32_error_t ew32_osa_task_create(ew32_task_handle task, uint16_t stackSize, uint8_t prio, const char* strName, 
                             void* userdata, uint8_t core, ew32_osa_task_t* tk) {
         BaseType_t _ret = 1;

    #if EW32_TASKAPI_PLATFORM_SUB ==   2
        _ret = xTaskCreate(task, strName, stackSize, userdata, prio, tk);
        #if configUSE_CORE_AFFINITY && configNUMBER_OF_CORES > 1
            vTaskCoreAffinitySet(tk, core);
        #endif
    #else
        _ret = xTaskCreatePinnedToCore(task, strName, stackSize, userdata, 
            prio, tk, core);
    #endif
       
    return _ret;                       

}

ew32_error_t ew32_osa_task_delay(uint32_t delay) {
    #if EW32_TASKAPI_PLATFORM_SUB ==   2
        sleep_ms(delay);
    #else
        vTaskDelay(delay / portTICK_PERIOD_MS);
    #endif

    return 0;
}
ew32_error_t ew32_osa_task_suspend(ew32_osa_task_t task) {
    vTaskSuspend( task );
    return 0;
}
ew32_error_t ew32_osa_task_resume(ew32_osa_task_t task, uint8_t isr) {
    if(task == NULL) return EW32_DEVICE_ERROR_NULL;

    if(isr == EW32_YES) xTaskResumeFromISR(task);
    else vTaskResume( task );

    return 0;
}
ew32_error_t    ew32_osa_task_resumeall() {
   return xTaskResumeAll();
}

ew32_error_t    ew32_osa_task_getbyname(const char* strName, ew32_osa_task_t* task) {
    ew32_error_t _ret = 0;
    ew32_osa_task_t _hndl = xTaskGetHandle(strName);

    if(_hndl == NULL) _ret = 1;
    else {
        if(task != NULL) *task = _hndl;
    }
    return _ret;
    
}

void ew32_osa_task_yield(uint8_t isr) {
    if(isr == EW32_YES)  portYIELD_FROM_ISR();
    else portYIELD();

}

ew32_osa_task_t  ew32_osa_task_current() {
    return xTaskGetCurrentTaskHandle();
}
void     ew32_osa_task_destroy(ew32_osa_task_t task) {
    if(task == NULL) return ;

    vTaskDelete(task);
}

uint32_t        ew32_osa_task_getstate(ew32_osa_task_t task) {
    return (uint32_t)eTaskGetState(task);
}
ew32_error_t    ew32_osa_task_setprio(ew32_osa_task_t task, uint8_t prio) {
    if(task == NULL) return EW32_DEVICE_ERROR_NULL;
    vTaskPrioritySet(task, prio);
    return 0;
}
uint8_t         ew32_osa_task_getprio(ew32_osa_task_t task, uint8_t isr) {
    if(task == NULL) return EW32_DEVICE_ERROR_NULL;

    uint8_t _ret = (isr == EW32_YES) ? 
        uxTaskPriorityGetFromISR(task) : 
        uxTaskPriorityGet(task);

    return _ret;
}
#endif
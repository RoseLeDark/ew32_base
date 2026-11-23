#pragma once

#include <ew32_base/ew32_config.h>

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

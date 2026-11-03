#include <Arduino.h>
#include "ew32_base/ew32_api.h"
#include "ew32_base/ew32_logging.h"


ew32_semaphore_t __logging_lock;

int8_t __logging_handler(uint8_t level, const char* tag, const char* text) {
   Serial.printf("[%d:%s] %s", level, tag, text); return 0;
}

void setup() {
   Serial.begin(115200);

   xewLoggingInitEx(&__logging_handler, EW32_LOGGING_LEVEL_DEBUG, EW32_LOGGING_LEVEL_CRITICAL);

   ew32_tasksystem_init();

   xewLoggingSerial(EW32_LOGGING_LEVEL_INFO, "MAIN", "Initializing Example binary mutex...\n");
   __logging_lock = ew32_semaphore_create(EW32_SEMAPHORE_BIN_MUTEX);

}

uint32_t __ticks = 0, __last_ticks = 0;
void loop(void) {
   __ticks = ew32_task_get_ticks();

   if( (__last_ticks - __ticks) >= 1000) {
      __last_ticks = __ticks;
      ew32_semaphore_lock(__logging_lock, EW32_INFINITY);
      xewLoggingSerial(EW32_LOGGING_LEVEL_INFO, "MAIN", "Hello from ew32 example binary mutex!\n");
      ew32_semaphore_unlock(__logging_lock);
   }

}



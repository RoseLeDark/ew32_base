#include "ew32_base/ew32_logging.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdatomic.h>

#include "ew32_base/ew32_config.h"
#include <ew32_base/ew32_spinlock.h>
#include <ew32_base/ew32_api.h>

struct logging_handler_struct {
    logging_handler handle;
    uint8_t minLevel;
    uint8_t maxLevel;
    #if EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_ATOMIC
    ew32_spinlock_t lock;
    #elif EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_MUTEX
    ew32_semaphore_t lock;
    #endif
};
struct logging_handler_struct ___ew32_logging_handle[EW32_LOGGING_NUMOFHANDLER] = {NULL};
uint8_t __index = 0;


int8_t xewLoggingInitEx(logging_handler handle, uint8_t minLevel, uint8_t maxLevel) {
    
    if(__index >= EW32_LOGGING_NUMOFHANDLER) return -1;

    ___ew32_logging_handle[__index].handle = handle;
    ___ew32_logging_handle[__index].minLevel = minLevel;
    ___ew32_logging_handle[__index].maxLevel = maxLevel;
    #if EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_ATOMIC
        ew32_spinlock_init( &___ew32_logging_handle[__index].lock );
    #elif EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_MUTEX
   ___ew32_logging_handle[__index].lock = ew32_semaphore_create(EW32_SEMAPHORE_BIN_MUTEX);
    #endif


    int8_t _ret = __index;
    __index++;

    return _ret;
}
int8_t xewLoggingSerial(uint8_t level, const char* tag, const char* text, ...) {
    char loc_buf[64];
    char * temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, text);
    va_copy(copy, arg);
    int len = vsnprintf(temp, sizeof(loc_buf), text, copy);
    va_end(copy);
    if(len < 0) {
        va_end(arg);
        return 0;
    }
    if(len >= (int)sizeof(loc_buf)){ 
        temp = (char*) malloc(len+1);
        if(temp == NULL) {
            va_end(arg);
            return 0;
        }
        len = vsnprintf(temp, len+1, text, arg);
    }
    va_end(arg);

    #if EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_ATOMIC
        ew32_spinlock_lock(&___ew32_logging_handle[__index].lock );
    #elif EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_MUTEX
        ew32_semaphore_lock(___ew32_logging_handle[__index].lock, EW32_INFINITY);
    #endif

    for(int i=0; i<__index; i++) {
        if(level >= ___ew32_logging_handle[i].minLevel && level <= ___ew32_logging_handle[i].maxLevel) {
            if(___ew32_logging_handle[i].handle != NULL) {
                ___ew32_logging_handle[i].handle(level, tag, temp);
            }
        }
    }
    
    #if EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_ATOMIC
        ew32_spinlock_unlock(&___ew32_logging_handle[__index].lock );
    #elif EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_MUTEX
        ew32_semaphore_unlock(___ew32_logging_handle[__index].lock);
    #endif
    
    if(temp != loc_buf) {
        free(temp);
    }

    return 0;
}

void xewSetLoggingLevel(uint8_t index, uint8_t minLevel, uint8_t maxLevel) {
    if(index < EW32_LOGGING_NUMOFHANDLER) {
        ___ew32_logging_handle[index].minLevel = minLevel;
        ___ew32_logging_handle[index].maxLevel = maxLevel;
    }
}

uint8_t xewGetLoggingLevel(uint8_t index) {
    if(index < EW32_LOGGING_NUMOFHANDLER) {
        return ___ew32_logging_handle[index].minLevel;
    }
    return 0;
}
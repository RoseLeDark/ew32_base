#include "ew32_base/ew32_logging.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ew32_base/ew32_config.h"

struct logging_handler_struct {
    logging_handler handle;
    uint8_t minLevel;
    uint8_t maxLevel;
};
struct logging_handler_struct ___ew32_logging_handle[EW32_LOGGING_NUMOFHANDLER] = {NULL};
uint8_t __index = 0;


int8_t xewLoggingInitEx(logging_handler handle, uint8_t minLevel, uint8_t maxLevel) {
    
    if(__index >= EW32_LOGGING_NUMOFHANDLER) return -1;

    ___ew32_logging_handle[__index].handle = handle;
    ___ew32_logging_handle[__index].minLevel = minLevel;
    ___ew32_logging_handle[__index].maxLevel = maxLevel;

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

    for(int i=0; i<__index; i++) {
        if(level >= ___ew32_logging_handle[i].minLevel && level <= ___ew32_logging_handle[i].maxLevel) {
            if(___ew32_logging_handle[i].handle != NULL) {
                ___ew32_logging_handle[i].handle(level, tag, temp);
            }
        }
    }
  
    
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
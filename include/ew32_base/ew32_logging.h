#pragma once

#include <stdint.h>
#include "ew32_config.h"
/* Log-Level Definitionen */


#if EW32_LOGGING_MIN_LEVEL <= EW32_LOGGING_LEVEL_DEBUG
#define xewLoggingDebug(tag, text)    xewLoggingSerial(EW32_LOGGING_LEVEL_DEBUG, (tag), (text) )
#define xewLoggingDebug1(tag, text, ARG)    xewLoggingSerial(EW32_LOGGING_LEVEL_DEBUG, (tag), (text), ARG )
#else
#define xewLoggingDebug(tag, text)  
#define xewLoggingDebug1(tag, text, ARG)   
#endif

#if EW32_LOGGING_MIN_LEVEL <= EW32_LOGGING_LEVEL_INFO
#define xewLoggingInfo(tag, text )     xewLoggingSerial(EW32_LOGGING_LEVEL_INFO, (tag), (text) )
#define xewLoggingInfo1(tag, text, ARG )     xewLoggingSerial(EW32_LOGGING_LEVEL_INFO, (tag), (text), ARG )
#else
#define xewLoggingInfo(tag, text )    
#define xewLoggingInfo1(tag, text, ARG )  
#endif

#if EW32_LOGGING_MIN_LEVEL <= EW32_LOGGING_LEVEL_WARNING
#define xewLoggingWarning(tag, text )  xewLoggingSerial(EW32_LOGGING_LEVEL_WARNING, (tag), (text) )
#define xewLoggingWarning1(tag, text, ARG )  xewLoggingSerial(EW32_LOGGING_LEVEL_WARNING, (tag), (text), ARG )
#else
#define xewLoggingWarning(tag, text)   
#define xewLoggingWarning1(tag, text, ARG ) 
#endif

#if EW32_LOGGING_MIN_LEVEL <= EW32_LOGGING_LEVEL_ERROR
#define xewLoggingError(tag, text )    xewLoggingSerial(EW32_LOGGING_LEVEL_ERROR, (tag), (text) )
#define xewLoggingError1(tag, text, ARG )    xewLoggingSerial(EW32_LOGGING_LEVEL_ERROR, (tag), (text), ARG )
#else
#define xewLoggingError(tag, text) 
#define xewLoggingError1(tag, text, ARG )   
#endif

#if EW32_LOGGING_MIN_LEVEL <= EW32_LOGGING_LEVEL_CRITICAL
#define xewLoggingCritical(tag, text ) xewLoggingSerial(EW32_LOGGING_LEVEL_CRITICAL, (tag), (text) )
#define xewLoggingCritical1(tag, text, ARG ) xewLoggingSerial(EW32_LOGGING_LEVEL_CRITICAL, (tag), (text), ARG )
#else
#define xewLoggingCritical(tag, text)    
#define xewLoggingCritical1(tag, text, ARG )
#endif






#ifdef __cplusplus
extern "C" {
#endif

typedef int8_t (* logging_handler)(uint8_t level, const char* tag, const char* text);

// return the number of the new handler, or -1 if no more handlers can be added
int8_t xewLoggingInitEx(logging_handler handle, uint8_t minLevel, uint8_t maxLevel);
/**
 * Zentrale Logging-Funktion.
 * 
 * @param tag   Kategorisierung oder Modul-Name (TAG)
 * @param text  Zu loggender Text (Null-terminiert)
 * @param level Log-Level des Eintrags (z.B. EW32_LOGGING_LEVEL_INFO)
 * @return      0 bei Erfolg, Fehlercode ungleich 0 bei Fehlschlag
 */
int8_t xewLoggingSerial(uint8_t level, const char* tag, const char* text, ...);

/**
 * Setzt das minimale globale Log-Level. Eintrags-Level unterhalb
 * dieses Wertes werden verworfen.
 * 
 * @param level Das minimale auszugebende Log-Level
 * @return      0 bei Erfolg, Fehlercode ungleich 0 bei Fehlschlag
 */
void xewSetLoggingLevel(uint8_t index, uint8_t minLevel, uint8_t maxLevel);

/**
 * Gibt das aktuell aktive minimale Log-Level zurück.
 */
uint8_t xewGetLoggingLevel(uint8_t index);

#ifdef __cplusplus
}
#endif



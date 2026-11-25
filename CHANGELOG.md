# Changelog

## Version 0.5.01
### Add
- Add new Types and remove bugs in osa level in rpi core task init system 
- Add ew32_version.h and ew32_types.h

!! PLEASE UPDATE TO VERSION 0.5.01 !!
---
## 
## Version 0.4.51
### Changed
- Spinlock is now in osa, "ew32_base/osa/ew32_osa_spinlock.h" rema,e functions ew32_osa_spinlock_{init, lock, unlock} add defines for old api name 
- rename "ew32_base/osa/ew32_api.h" to "ew32_base/osa/ew32_osa_api.h"

---
## Version 0.4.0

### Changed
- Change the ew32_api system. ew32_task rename to ew32_osa_task_... and the semaphore api ew32_mutex to ew32_osa_smph_ .. 
- Changed the API for creating a semaphore type from `ew32_semaphore_create(TYPE)` to:
   - `ew32_semaphore_t ew32_osa_smph_mutex_create();`
   - `ew32_semaphore_t ew32_osa_smph_binary_create();`
   - `ew32_semaphore_t ew32_osa_smph_counting_create(uint32_t baseCount, uint32_t startCount);`
   
### Add
- Add Operationg System API (OSA) - see directory ew32_base/include/ew32_base/osa/ew32_api.h:
   - This file include the right header for used platform
- Add typedef `ew32_bool_t` with ewTRUE : 1 and ewFALSE : 0
- Add OSA Platform FreeRTOS with CriticalSection, Yield, Delay, Interrupt cli / sli system
- Add API for recursive mutex:
   - `ew32_osa_smph_recursive_create();`
   - `ew32_osa_smph_recursive_lock(ew32_semaphore_t handle, int32_t timeout);`
   - `ew32_osa_smph_recursive_unlock(ew32_semaphore_t handle);`
- Add to semph stack the function `ew32_osa_smph_owner(SMPHORE)` return `ewTRUE (1)` when the current task owner of this lock is.

## Remove
- Remove old api configs
   - `EW32_PLATFORM_TAKSAPI_TIMER`               
   - `EW32_PLATFORM_TAKSAPI_ASYNC` - raspberry pi pico used `EW32_PLATFORM_TAKSAPI_RTOS`  with sub platform config              


## Version 0.3.2

### Add
add `EW32_PLATFORM_ARDUINO_ESP32` to `ew32_config.h` (board esp32)
add `EW32_LOGGING_MIN_LEVEL` to `ew32_config.h`:
   - when build with ``build_flag = ... -D_DEBUG=1`` then set `EW32_LOGGING_MIN_LEVEL` to `EW32_LOGGING_LEVEL_DEBUG`
   - without `-D_DEBUG=1`  then set `EW32_LOGGING_MIN_LEVEL` to `EW32_LOGGING_LEVEL_WARNING`

### Changed
changed `EW32_PLATFORM_STM32` from 3 to 4
changed `EW32_PLATFORM_RPPICO` from 4 to 5 

---

## Version 0.3.0

### Added
add ew32_spinlock atomic spinlock handling 
add example in `example/arduino.cpp`
add Changelog

### Change
change logging, this used now atomic lock or mutex see `ew32_config.h`
update version to 0.3.0

---

## Version 0.2.0

### Added
Add `EW32_LOGGING_NUMOFHANDLER` to the `ew32_config.h`. 
Add `EW32_LOGGING_LOCK_API` to the `ew32_config.h`. 

### Change
Remove the ew32 semaphore bug
The logging api can now add more as one handle for logging and is locked with atomics or mutex see `EW32_LOGGING_LOCK_API` 

---
## Version 0.1.5
### Added
Added `ew32_config.h` and added the `ew32_task.freertos` API from ew32_devm - this api is common and will be used in all ew32 libarys



---

## Version 0.0.2
First public version




# Changelog

## Version 0.3.0

### Added
add ew32_spinlock atomic spinlock handling 
add example in example/arduino.cpp
add Changelog

### Change
change logging, this used now atomic lock or mutex see ew32_config.h
update version to 0.3.0

---

## Version 0.2.0

### Added
Add EW32_LOGGING_NUMOFHANDLER to the ew32_config.h. 
Add EW32_LOGGING_LOCK_API to the ew32_config.h. 

### Change
Remove the ew32 semaphore bug
The logging api can now add more as one handle for logging and is locked with atomics or mutex see EW32_LOGGING_LOCK_API 

---
## Version 0.1.5
### Added
Added ew32_config.h and added the ew32_task.freertos API from ew32_devm - this api is common and will be used in all ew32 libarys



---

## Version 0.0.2
First public version




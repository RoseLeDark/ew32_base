#pragma once

#include <stdatomic.h>

#define EW32_SPINLOCK_INIT { ATOMIC_FLAG_INIT }



#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    atomic_bool flag; // true = locked, false = unlocked
} ew32_spinlock_t;

void ew32_spinlock_init(ew32_spinlock_t *lock);
void ew32_spinlock_lock(ew32_spinlock_t *lock);
void ew32_spinlock_unlock(ew32_spinlock_t *lock);


#ifdef __cplusplus
}
#endif


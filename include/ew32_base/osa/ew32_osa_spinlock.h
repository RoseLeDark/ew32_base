#pragma once

#include <stdatomic.h>
#include <stdint.h>
#include "ew32_osa_api.h"

#define EW32_SPINLOCK_INIT { ATOMIC_FLAG_INIT }

#define ew32_spinlock_init( L ) ew32_osa_spinlock_init(L)
#define ew32_spinlock_lock( L ) ew32_osa_spinlock_lock(L)
#define ew32_spinlock_unlock( L ) ew32_osa_spinlock_unlock(L)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    atomic_bool flag; // true = locked, false = unlocked
    ew32_osa_task_t holder;
} ew32_spinlock_t;

void ew32_osa_spinlock_init(ew32_spinlock_t *lock);
void ew32_osa_spinlock_lock(ew32_spinlock_t *lock);
void ew32_osa_spinlock_unlock(ew32_spinlock_t *lock);


#ifdef __cplusplus
}
#endif


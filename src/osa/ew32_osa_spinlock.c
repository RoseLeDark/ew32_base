#include <ew32_base/osa/ew32_osa_spinlock.h>
#include "ew32_base/osa/ew32_osa_api.h"

#include <stdbool.h>
#if EW32_LOGGING_LOCKAPI == EW32_LOGGING_LOCKAPI_ATOMIC

void ew32_osa_spinlock_init(ew32_spinlock_t *lock) {
     if (!lock) return;
    atomic_init(&lock->flag, 0);
}

void ew32_osa_spinlock_lock(ew32_spinlock_t *lock) {
    bool expected;
    // Loop until we acquire the lock
    do {
        expected = false; // We expect it to be unlocked
        // Try to set flag to true (locked)
        // Memory order: acquire semantics for lock, relaxed for failure
    } while (!atomic_compare_exchange_weak_explicit(
                 &lock->flag,
                 &expected,
                 true,
                 memory_order_acquire,
                 memory_order_relaxed));

    lock->holder = ew32_osa_task_current(0);
}
void ew32_osa_spinlock_unlock(ew32_spinlock_t *lock) {
    if(ew32_osa_task_current(0) != lock->holder) return;
    
     // Release semantics to ensure all writes before unlock are visible
    atomic_store_explicit(&lock->flag, 0, memory_order_release);
}

#endif
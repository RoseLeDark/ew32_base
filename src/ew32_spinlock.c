#include <ew32_base/ew32_spinlock.h>

#include <stdbool.h>

void ew32_spinlock_init(ew32_spinlock_t *lock) {
     if (!lock) return;
    atomic_init(&lock->flag, false);
}
void ew32_spinlock_lock(ew32_spinlock_t *lock) {
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
}
void ew32_spinlock_unlock(ew32_spinlock_t *lock) {
     // Release semantics to ensure all writes before unlock are visible
    atomic_store_explicit(&lock->flag, false, memory_order_release);
}
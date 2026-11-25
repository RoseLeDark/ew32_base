/*
 * SPDX-License-Identifier: EUPL-1.2
 *
 * Copyright (c) 2026 Amber-Sophia "RoseLeBlood" Schröck (gender:divers dey/deren )
 *
 * This file is part of ew32_devm.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.2 or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see:
 * https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */


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


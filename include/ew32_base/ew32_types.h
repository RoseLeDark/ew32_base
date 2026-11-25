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

#include <stdint.h>
#include "ew32_config.h"


#define EW32_WEAK               __attribute__((weak))
#define EW32_WEAK_INLINE        __attribute__((weak, always_inline)) inline
#define EW32_PACKED             __attribute__((packed))
#define EW32_WEAK_ALIAS(FUNC)   __attribute__((weak, alias(FUNC)))


#define ewTRUE              1
#define ewFALSE             0

typedef uint8_t             ew32_bool_t;
typedef uint8_t             ew32_ui8_t;
typedef uint16_t            ew32_ui16_t;
typedef uint32_t            ew32_ui32_t;
typedef uint64_t            ew32_ui64_t;

typedef int8_t              ew32_i8_t;
typedef int16_t             ew32_i16_t;
typedef int32_t             ew32_i32_t;
typedef int64_t             ew32_i64_t;

typedef uint8_t             ew32_error_t;
typedef uint32_t            ew32_size_t;
typedef int32_t             ew32_ssize_t;

typedef ew32_ui8_t          ew32_prio_t;
typedef uint64_t            ew32_ticks_t;
typedef ew32_i8_t           ew32_state_t;

#if EW32_MAX_OPEN_FILES >= __INT16_MAX__
    typedef int32_t ew32_file_t;
    typedef int32_t ew32_devid_t;
#elif EW32_MAX_OPEN_FILES >= __INT8_MAX__     
    typedef int16_t ew32_file_t;
    typedef int16_t ew32_devid_t;
#else
   typedef int8_t ew32_file_t;
   typedef int8_t ew32_devid_t;
#endif

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

#include <stdio.h>
#include "ew32_base/osa/ew32_api.h"
#include "ew32_base/ew32_error.h"
// TODO: Add C source content

#ifdef EW32_PLATFORM == EW32_PLATFORM_ESP
#include "ew32_base/ew32_logging.h"

#if EW32_PLATFORM == EW32_PLATFORM_ESP || EW32_PLATFORM ==  EW32_PLATFORM_ARDUINO_ESP32
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#endif

void ew32_osa_cli() {
    taskDISABLE_INTERRUPTS();
}
void ew32_osa_sti() {
    taskENABLE_INTERRUPTS();
}

uint64_t         ew32_osa_getticks() {
    return xTaskGetTickCount();
}
#endif
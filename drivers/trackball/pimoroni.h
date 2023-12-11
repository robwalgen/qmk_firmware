/* Copyright 2021 L. K. Post (crote)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include "i2c_master.h"

#ifndef TRACKBALL_ADDRESS
    #define TRACKBALL_ADDRESS 0x0A
#endif

#ifndef TRACKBALL_TIMEOUT
    #define TRACKBALL_TIMEOUT 100
#endif

#ifndef TRACKBALL_INTERVAL
    #define TRACKBALL_INTERVAL 35
#endif

#ifndef TRACKBALL_ORIENTATION
    #define TRACKBALL_ORIENTATION 0
#endif

#ifndef TRACKBALL_MOUSE_BTN
    #define TRACKBALL_MOUSE_BTN MOUSE_BTN1
#endif

#if defined(TRACKBALL_RGBLIGHT) && !defined(RGBLIGHT_ENABLE)
    #error You must enable RGB lighting for the trackball to be able to clone a RGB led!
#endif

typedef enum {
    TB_MOVED  = 0b01,
    TB_BUTTON = 0b10,
    TB_BOTH   = 0b11,
} trackball_flags_t;

typedef struct {
    int16_t x;
    int16_t y;
    bool pressed;
    trackball_flags_t type;
} trackball_record_t;

void trackball_init(void);
void trackball_task(void);

i2c_status_t trackball_setrgb(uint8_t r, uint8_t g, uint8_t b);
i2c_status_t trackball_sethsv(uint8_t h, uint8_t s, uint8_t v);

__attribute__((weak)) void process_trackball_kb(trackball_record_t *record);
__attribute__((weak)) void process_trackball_user(trackball_record_t *record);
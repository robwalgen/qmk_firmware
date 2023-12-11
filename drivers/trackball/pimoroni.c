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

#include "pimoroni.h"

#include "i2c_master.h"
#include "color.h"
#ifdef TRACKBALL_RGBLIGHT
    #include "rgblight.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
    #include "pointing_device.h"
#endif
#include "matrix.h"
#include "keyboard.h"
#include "timer.h"

// See https://github.com/pimoroni/trackball-python/blob/master/library/trackball/__init__.py

#define LED_REG 0x00
#define INPUT_REG 0x04
#define INTERRUPT_REG 0xF9

#define MSK_BTN_STATE  0b10000000
#define MSK_BTN_CHANGE 0b00000001
#define MSK_INT_TRIGGER 0b00000001

typedef struct {
    uint8_t left;
    uint8_t right;
    uint8_t up;
    uint8_t down;
    // bit 1: button changed
    // bit 8: button state
    uint8_t button;
} input_t;

// Defined in `quantum/matrix_common.c`
extern matrix_row_t matrix[MATRIX_ROWS];

#ifdef TRACKBALL_RGBLIGHT
// Defined in `quantum/rgblight.c`
extern LED_TYPE led[RGBLED_NUM];
#endif

uint16_t update_timer;

void trackball_init(void) {
    if (!is_keyboard_master()) return;
    i2c_init();

    // The trackball may already have some stale data, so clear its registers
    input_t input;
    i2c_readReg(TRACKBALL_ADDRESS << 1, INPUT_REG, (uint8_t*)&input, sizeof(input), TRACKBALL_TIMEOUT);
    update_timer = timer_read();

    // Clear the LED
    trackball_setrgb(0, 0, 0);
}

void trackball_task(void) {
    i2c_status_t status;

#ifdef TRACKBALL_RGBLIGHT
    trackball_setrgb(led[TRACKBALL_RGBLIGHT].r, led[TRACKBALL_RGBLIGHT].g, led[TRACKBALL_RGBLIGHT].b);
#endif

    if (timer_elapsed(update_timer) < TRACKBALL_INTERVAL) {
        return;
    }
    update_timer = timer_read();

    uint8_t interrupt;
    status = i2c_readReg(TRACKBALL_ADDRESS << 1, INTERRUPT_REG, &interrupt, sizeof(interrupt), TRACKBALL_TIMEOUT);
    if (status != I2C_STATUS_SUCCESS || !(interrupt & MSK_INT_TRIGGER)) {
        // Interrupt is not triggered, so there is no data to read
        return;
    }

    input_t input;
    status = i2c_readReg(TRACKBALL_ADDRESS << 1, INPUT_REG, (uint8_t*)&input, sizeof(input), TRACKBALL_TIMEOUT);
    if (status != I2C_STATUS_SUCCESS) {
        return;
    }

    trackball_record_t record = { .type = 0 };

#if TRACKBALL_ORIENTATION == 0
    // Pimoroni text is pointing up
    record.x += input.right - input.left;
    record.y += input.down - input.up;
#elif TRACKBALL_ORIENTATION == 1
    // Pimoroni text is pointing right
    record.x += input.up - input.down;
    record.y += input.right - input.left;
#elif TRACKBALL_ORIENTATION == 2
    // Pimoroni text is pointing down
    record.x += input.left - input.right;
    record.y += input.up - input.down;
#else
    // Pimoroni text is pointing left
    record.x += input.down - input.up;
    record.y += input.left - input.right;
#endif
    if (record.x != 0 || record.y != 0) {
        record.type |= TB_MOVED;
    }

    record.pressed = input.button & MSK_BTN_STATE;
    if (input.button & MSK_BTN_CHANGE) {
        record.type |= TB_BUTTON;
    }

    process_trackball_kb(&record);

#if defined(TRACKBALL_MATRIX_ROW) && defined(TRACKBALL_MATRIX_COL)
    if (record.type & TB_BUTTON) {
        // The trackball is used as a regular key in the matrix
        matrix[TRACKBALL_MATRIX_ROW] &= ~(MATRIX_ROW_SHIFTER << TRACKBALL_MATRIX_COL);
        matrix[TRACKBALL_MATRIX_ROW] |= record.pressed ? (MATRIX_ROW_SHIFTER << TRACKBALL_MATRIX_COL) : 0;
        record.type &= ~TB_BUTTON;
    }
#endif

#ifdef POINTING_DEVICE_ENABLE
    report_mouse_t mouse;

    if (record.type & TB_BUTTON) {
        mouse = pointing_device_get_report();
        if (record.pressed) {
            mouse.buttons |= TRACKBALL_MOUSE_BTN;
        } else {
            mouse.buttons &= ~TRACKBALL_MOUSE_BTN;
        }
        pointing_device_set_report(mouse);
    }

    if (record.type & TB_MOVED) {
        mouse = pointing_device_get_report();
        // The report may already contain unsend movement,
        // so we need to take that into account.
        record.x += mouse.x;
        record.y += mouse.y;
        // We need to send our movement in multiple reports,
        // because a report has a range of -127..127,
        // whereas our movement frequently exceeds that.
        while (record.x != 0 || record.y != 0) {
            mouse.x = record.x > 127 ? 127 : (record.x < -127 ? -127 : record.x);
            mouse.y = record.y > 127 ? 127 : (record.y < -127 ? -127 : record.y);
            record.x -= mouse.x;
            record.y -= mouse.y;
            pointing_device_set_report(mouse);
            pointing_device_send();
        }
    }
#endif
}

i2c_status_t trackball_setrgb(uint8_t r, uint8_t g, uint8_t b) {
    // Trackball supports RGBW, but we just ignore the W
    uint8_t led_buf[] = { r, g, b, 0 };
    return i2c_writeReg(TRACKBALL_ADDRESS << 1, LED_REG, led_buf, sizeof(led_buf), TRACKBALL_TIMEOUT);
}

i2c_status_t trackball_sethsv(uint8_t h, uint8_t s, uint8_t v) {
    RGB out = hsv_to_rgb((HSV){.h = h, .s = s, .v = v});
    return trackball_setrgb(out.r, out.g, out.b);
}

__attribute__((weak)) void process_trackball_kb(trackball_record_t *record) { return process_trackball_user(record); }
__attribute__((weak)) void process_trackball_user(trackball_record_t *record) { return; }
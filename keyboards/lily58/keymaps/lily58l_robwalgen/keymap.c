 /* Copyright 2017 F_YUUCHI
  * Copyright 2020 Drashna Jaelre <@drashna>
  * Copyright 2020 Ben Roesner (keycapsss.com)
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

#include QMK_KEYBOARD_H
#include "drivers/sensors/pimoroni_trackball.h"

extern uint8_t is_master;

enum layers {
    _COLEMAK,
    _GAME,
    _QWERTY,
    _LOWER,
    _MEINS,
    _NUMBER,
    _RAISE
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define MEINS MO(_MEINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DHm
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Z  |      |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |BackSP|   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |      |
 * |------+------+------+------+------+------|   <   |    |   >   |------+------+------+------+------+------|
 * |LShift|   Y  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI |LCTL  |LOWER | /Enter  /       \ Space\  |RAISE | LALT | RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_COLEMAK] = LAYOUT(
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_VOLU, KC_DEL,
  KC_BSPC,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    XXXXXXX,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V, KC_NUBS, S(KC_NUBS), KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        KC_LGUI, KC_LCTL, LOWER, KC_ENT, KC_SPACE, RAISE, KC_LALT, KC_RALT
),
/* GAME
* ,-----------------------------------------.                    ,-----------------------------------------.
* |   K  | ESC  |   1  |   2  |   3  |   4  |                    |   6  |   7  |   8  |   9  |   0  |  DEL |
* |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* |   J  | Tab  |   Q  |   W  |   E  |   R  |                    |   Y  |   U  |   I  |   O  |   P  |Backsp|
* |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* |   X  |LSHIFT|   A  |   S  |   D  |   F  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |Enter |
* |------+------+------+------+------+------|  H    |    |       |------+------+------+------+------+------|
* |   U  |LCTRL |   Z  |   C  |   B  |   T  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
* `-----------------------------------------/       /     \      \-----------------------------------------'
*                   | LGUI |LCTL  |LOWER | /Space  /       \ Enter\  |RAISE | LALT | RALT |
*                   |      |      |      |/       /         \      \ |      |      |      |
*                   `----------------------------'           '------''--------------------'
*/
 [_GAME] = LAYOUT(
 KC_K,  KC_ESC,   KC_1,    KC_2,      KC_3,    KC_4,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_DELETE, 
 KC_J,  KC_TAB,   KC_Q,    KC_W,      KC_E,    KC_R,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, 
 KC_X,  KC_LSFT,  KC_A,    KC_S,      KC_D,    KC_F,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_ENT, 
 KC_U,  KC_LCTRL, KC_Y,    KC_C,      KC_B,    KC_T,   KC_H,           _______,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_QUOT, 
  	                      KC_LGUI, KC_LCTL, LOWER, KC_SPC, KC_ENT, RAISE, KC_LALT, KC_RALT 
),
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |BackSP|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI |LCTL  |LOWER | /Enter  /       \ Space\  |RAISE | LALT | RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_GESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_BSPC,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LGUI, KC_LCTL, LOWER, KC_ENT, KC_SPACE, RAISE, KC_LALT, KC_RALT
),
/* LOWER
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |   ^°  |  F1  |  F2  |  F3  |  F4  | F5   |                    |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ralttab|  F11 |  F12 |      |      |      |                    |      |   [  |   ]  |      |      |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Caps |      |      |      |   !  |      |-------.    ,-------|  ´ ` |   (  |   )  |   #  |      |      |
 * |-------+------+------+------+------+------|   /   |    |   \   |------+------+------+------+------+------|
 * |       |      |  M1  |  M2  |  M3  |      |-------|    |-------|   +  |   {  |   }  |      |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *                    |NUMBER|LCTRL |LOWER | /Enter  /       \Space \  |ADJUST| LALT | RALT |
 *                    |      |      |      |/       /         \      \ |      |      |      |
 *                    `----------------------------'           '------''--------------------'
 */
 [_LOWER] = LAYOUT(
  KC_GRV,       KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                            KC_F6,      KC_F7,      KC_F8,   KC_F9,  KC_F10, _______,
 RALT(KC_TAB), KC_F10,  KC_F12,  _______, _______, _______,                          _______, RALT(KC_8), RALT(KC_9), _______, _______, _______,
  KC_CAPS,    _______, _______,  _______, S(KC_1), _______,                           KC_EQL,    S(KC_8),    S(KC_9), KC_BSLS, _______, _______,
  _______,    _______, KC_BTN1,  KC_BTN2, KC_BTN3, _______, S(KC_7),  RALT(KC_MINS), KC_RBRC, RALT(KC_7), RALT(KC_0), _______, _______, _______,
                         MO(_NUMBER), _______, _______, _______,         _______, MO(_MEINS), _______, _______
),
/* NUMBER
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |   ^°  |  F1  |  F2  |  F3  |  F4  | F5   |                    |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ralttab|  F11 |  F12 |      |      |      |                    |      |   7  |   8  |   9  |      |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Caps |      |      |      |   !  |      |-------.    ,-------|  ´ ` |   4  |   5  |   6  |      |      |
 * |-------+------+------+------+------+------|   /   |    |   \   |------+------+------+------+------+------|
 * |       |      |      |      |      |      |-------|    |-------|   +  |   1  |   2  |   3  |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *                    | LGUI |LCTRL |LOWER | /Enter  /       \Space \  |ADJUST|   0  |   ,  |
 *                    |      |      |      |/       /         \      \ |      |      |      |
 *                    `----------------------------'           '------''--------------------'
 */
 [_NUMBER] = LAYOUT(
  KC_GRV,  DF(_COLEMAK), DF(_GAME), DF(_QWERTY),   KC_F4,   KC_F5,                             DF(_COLEMAK), DF(_GAME), DF(_QWERTY),   KC_F9,  KC_F10, _______,
 RALT(KC_TAB), KC_F10,  KC_F12,  _______, _______, _______,                           _______,       KC_7,       KC_8, 	  KC_9, _______, KC_PSCR,
  _______,    _______, _______,  _______, _______, KC_MPRV,                           KC_MNXT,       KC_4,       KC_5,    KC_6, _______, _______,
  _______,    _______, _______,  _______, _______, KC_VOLD, _______,      _______,    KC_VOLU,       KC_1,       KC_2,    KC_3, _______, _______,
                          _______, _______, _______, _______,              _______,   MO(_MEINS),        KC_0,       KC_COMM
),
/* MEINS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |DF(0) |DF(1) |DF(2) |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |PRSCR |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      | PREV |-------.    ,-------| NEXT | PLAY |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      | Vol- |-------|    |-------| Vol+ | MUTE |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI |LCTRL |LOWER | /Enter  /       \Space \  |RAISE | LALT | RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_MEINS] = LAYOUT(
  XXXXXXX, DF(_COLEMAK), DF(_GAME), DF(_QWERTY),   XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV,                   KC_MNXT, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          _______, _______, _______, _______, _______, _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ^°  |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   @  |      |   €  |      |      |                    |      |      |   Ü  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   ä  |      |   ß  |      |      |-------.    ,-------|   µ  |   ?  |  Up  |   '  |   Ö  |      |
 * |------+------+------+------+------+------|   |   |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   ~  | Left | Down | Right|      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI |LCTRL |ADJUST| /Enter  /       \Space \  |RAISE | LALT | RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_RAISE] = LAYOUT(
  KC_GRV,    _______, _______, _______,    _______, _______,                                 _______,    _______, _______,    _______, _______, _______,
 _______, RALT(KC_Q), _______, RALT(KC_E), _______, _______,                                 _______,    _______, KC_LBRC,    _______, _______, _______,
  KC_CAPS,   KC_QUOT, _______, KC_MINS,    _______, _______,                              RALT(KC_M), S(KC_MINS),   KC_UP, S(KC_BSLS), KC_SCLN, _______,
  _______,   _______, _______, _______,    _______, _______, RALT(KC_NUBS),   _______, RALT(KC_RBRC),    KC_LEFT, KC_DOWN,    KC_RGHT, _______, _______,
                               _______, _______, MO(_MEINS), _______,         _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _MEINS);
    return state;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_0;
    }
}

void render_lily58_logo(void) {
    static const char PROGMEM lily58_logo[] = {
    // 'logo', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x40, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x80, 0xe0, 0x70, 0x3c, 0x0e, 0x06, 0x0e, 0x3c, 0x70, 0xe0, 0x80, 0x00, 0x00, 0xc0, 0xc0, 0x00,
    0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x80,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83,
    0x07, 0x07, 0x0c, 0x18, 0x70, 0xe0, 0x80, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x80, 0xb6, 0xb6, 0x80,
    0xb0, 0xb0, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x30, 0xf0, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf0,
    0x30, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xe1, 0x71, 0x71, 0xf1, 0xf1, 0xe1, 0xc1, 0x81, 0x00, 0x00,
    0x00, 0x00, 0x0c, 0x3f, 0xff, 0xf3, 0xe1, 0xc1, 0xc1, 0x81, 0x81, 0xc3, 0xff, 0x7f, 0x1c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x70, 0x78, 0xdc, 0xcc, 0x86, 0x06, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x03, 0x02, 0x06, 0x84, 0xe1, 0xfb, 0x38, 0x1c, 0x0c, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x03, 0x03, 0x06, 0x86, 0xcc, 0xdc, 0x78, 0x70, 0x20, 0x00, 0xff, 0xff, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x7e, 0xf8, 0xe0, 0xf0, 0x7e, 0x1f, 0x03, 0x00,
    0x00, 0x00, 0x00, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe1, 0xff, 0x7f, 0x3f, 0x00,
    0x00, 0x00, 0x3e, 0xff, 0xff, 0xc1, 0xc0, 0x80, 0x81, 0x81, 0xc3, 0xc3, 0xff, 0xfe, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x06,
    0x06, 0x02, 0x03, 0x01, 0x01, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04,
    0x06, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x60, 0x60, 0x70, 0x38, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
};
    oled_write_raw_P(lily58_logo, sizeof(lily58_logo));
}


#    define KEYLOG_LEN 6
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_P(PSTR(" "), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("COLE"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("GAME"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QRTY"), false);
            break;
        case _NUMBER:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOW"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("HIGH"), false);
            break;
        case _MEINS:
            oled_write_ln_P(PSTR("ADJ"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void render_keylock_status(led_t led_state) {
    oled_write_ln_P(PSTR("Lock"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_state.scroll_lock);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Mods"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_status_main(void) {
    // Show keyboard layout
    render_default_layer_state();
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show host keyboard led status
    render_keylock_status(host_keyboard_led_state());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show modifier status
    render_mod_status(get_mods());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    render_keylogger_status();
}

bool oled_task_user(void) {
  update_log();
  if (is_keyboard_master()) {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_lily58_logo();
  }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}
#endif // OLED_ENABLE


// Rotary encoder related code
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if(IS_LAYER_ON(_LOWER)) { // on Lower layer
      //
      if (clockwise) {
          tap_code(KC_RIGHT);
      } else {
          tap_code(KC_LEFT);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
      }
    }
  }
  else if (index == 1) { // Encoder on slave side
    if(IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
          tap_code(KC_MNXT);
      } else {
          tap_code(KC_MPRV);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    }
  }
    return true;
}
#endif

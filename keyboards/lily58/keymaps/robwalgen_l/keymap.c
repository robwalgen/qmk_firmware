// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
//#include "keymap_french.h"
#include "transactions.h"

// global
#include "gui_state.h"
#include "boot.h"
#include "navi_logo.h"

#include "draw_helper.h"
#include "fast_random.h"

// left side
#include "layer_frame.h"
#include "burst.h"

// right side
#include "ring.h"


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak DHm
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
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
  KC_ESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_VOLU, KC_DEL,
  KC_BSPC,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    XXXXXXX,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V, KC_NUBS, S(KC_NUBS), KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        KC_LGUI, KC_LCTL, MO(_LOWER), KC_ENT, KC_SPACE, MO(_RAISE), KC_LALT, KC_RALT
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
 KC_U,  KC_LCTL, KC_Y,    KC_C,      KC_B,    KC_T,   KC_H,           _______,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_QUOT, 
  	                      KC_LGUI, KC_LCTL, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_LALT, KC_RALT 
),
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
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
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_BSPC,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LGUI, KC_LCTL, MO(_LOWER), KC_ENT, KC_SPACE, MO(_RAISE), KC_LALT, KC_RALT
),
/* LOWER
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |   ^°  |  F1  |  F2  |  F3  |  F4  | F5   |                    |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ralttab|  F11 |  F12 |      |      |      |                    |      |   [  |   ]  |      |      |      |
 * |-------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Caps |      |      |  M3-U|   !  |      |-------.    ,-------|  ´ ` |   (  |   )  |   #  |      |      |
 * |-------+------+------+------+------+------|   /   |    |   \   |------+------+------+------+------+------|
 * |       |      |  M2  |  M3-D|   M1 |      |-------|    |-------|   +  |   {  |   }  |      |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *                    |NUMBER|LCTRL |LOWER | /Enter  /       \Space \  |ADJUST| LALT | RALT |
 *                    |      |      |      |/       /         \      \ |      |      |      |
 *                    `----------------------------'           '------''--------------------'
 */
 [_LOWER] = LAYOUT(
  KC_GRV,       KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                            KC_F6,      KC_F7,      KC_F8,   KC_F9,  KC_F10, _______,
 RALT(KC_TAB), KC_F10,  KC_F12,  _______, _______, _______,                          _______, RALT(KC_8), RALT(KC_9), _______, _______, _______,
  KC_CAPS,    _______, _______,  KC_WH_U, S(KC_1), _______,                           KC_EQL,    S(KC_8),    S(KC_9), KC_BSLS, _______, _______,
  _______,    _______, KC_BTN2,  KC_WH_D, KC_BTN1, _______, S(KC_7),  RALT(KC_MINS), KC_RBRC, RALT(KC_7), RALT(KC_0), _______, _______, _______,
                         MO(_NUMBER), _______, _______, _______,         _______, MO(_ADJUST), _______, _______
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
  KC_GRV,       KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                             KC_F6,      KC_F7,      KC_F8,   KC_F9,  KC_F10, _______,
 RALT(KC_TAB), KC_F10,  KC_F12,  _______, _______, _______,                           _______,       KC_7,       KC_8, 	  KC_9, _______, _______,
  _______,    _______, _______,  _______, _______, _______,                           _______,       KC_4,       KC_5,    KC_6, _______, _______,
  _______,    _______, _______,  _______, _______, _______, _______,      _______,    _______,       KC_1,       KC_2,    KC_3, _______, _______,
                          _______, _______, _______, _______,              _______,   MO(_ADJUST),    KC_0,       KC_COMM
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
                               _______, _______, MO(_ADJUST), _______,         _______, _______, _______, _______
),
/* ADJUST
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
  [_ADJUST] = LAYOUT(
  XXXXXXX, DF(0),   DF(1),   DF(2),   XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV,                   KC_MNXT, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          _______, _______, _______, _______, _______, _______, _______, _______
)
};
// clang-format on

// sync transport
typedef struct _sync_keycode_t {
    uint16_t keycode;
} sync_keycode_t;

// force rigth side to update
bool b_sync_need_send = false;

// last keycode typed
sync_keycode_t last_keycode;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // vertical orientation
    return OLED_ROTATION_270;
}

void render(gui_state_t t) {
    // logo
    render_logo(t);

#if IS_LEFT
    // left side
    render_layer_frame(t);
    render_gears();

    decay_scope();
    render_scope(t);
#endif

#if IS_RIGHT
    // right side
    render_circle(t);
#endif
}

void update(uint16_t keycode) {
#if IS_LEFT
    update_scope();
#endif

#if IS_RIGHT
    update_circle(keycode);
#endif
}

void reset(void) {
#if IS_LEFT
    reset_scope();
#endif

#if IS_RIGHT
    reset_ring();
#endif
}

void set_wackingup_mode_clean(void) {
    oled_clear();
    reset();
}

bool oled_task_user(void) {
    gui_state_t t = get_gui_state();

    // in sleep mode => turn display off
    if (t == _SLEEP) {
        oled_off();
        return false;
    }

    // not in sleep mode => screen is on
    oled_on();

#ifdef WITH_BOOT
    // in booting mode => display booting animation
    if (t == _BOOTING) {
        bool boot_finished = render_boot();
        if (boot_finished) {
            // end of the boot : wacking up
            set_wackingup_mode_clean();
            update_gui_state();
        }
        return false;
    }
#endif

    // in halting mode => display booting animation
    if (t == _HALTING) {
        render_halt();
        return false;
    }

    render(t);
    return false;
}

void process_key(uint16_t keycode) {
    // update screen with the new key
    update(keycode);

    gui_state_t t = get_gui_state();

    if (t == _IDLE) {
        // wake up animation
        reset();
    }

    if (t == _BOOTING || t == _HALTING) {
        // cancel booting or halting : waking_up
        set_wackingup_mode_clean();
    }

    if (t == _SLEEP) {
        // boot sequence
        set_wackingup_mode_clean();
        reset_boot();
    }

    update_gui_state();
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const sync_keycode_t* m2s = (const sync_keycode_t*)in_data;
    // get the last char typed on left side and update the right side
    process_key(m2s->keycode);
}

void keyboard_post_init_user(void) {
    // callback for tranport sync data
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

void housekeeping_task_user(void) {
    // only for master side
    if (!is_keyboard_master()) return;

    // only if a new char was typed
    if (!b_sync_need_send) return;

    // send the char to the slave side : sync is done
    if (transaction_rpc_send(USER_SYNC_A, sizeof(last_keycode), &last_keycode)) {
        b_sync_need_send = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        // master : store keycode to sent to the other side to be process_key
        last_keycode.keycode = keycode;
        b_sync_need_send     = true;

        // gui process the input
        process_key(keycode);
    }
    return true;
}

#if IS_LEFT
layer_state_t layer_state_set_user(layer_state_t state) {
    // update the frame with the layer name
    update_layer_frame(state);
    return state;
}
#endif

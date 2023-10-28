// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <avr/power.h>
#include "print.h"
#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE,
    _CUSTOM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
  [_BASE] = LAYOUT_iso(
    /*  0      1        2        3        4        5        6        7        8        9        10       11       12       13       14       15       16  */
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14 , KC_F15,  KC_F16,
    KC_NUBS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_DEL,  KC_HOME,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                            KC_END,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_INS,  KC_PGUP,
    KC_LSFT, KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,   KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,  KC_SPC,                    KC_RALT, KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_CUSTOM] = LAYOUT_iso(
    /*  0      1        2        3        4        5        6        7        8        9        10       11       12       13       14       15       16  */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, LCTL(LGUI(KC_Q)),
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______,
    KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
    _______, KC_LALT, KC_LGUI,                            _______, _______,                   _______, _______, _______,          _______, _______, _______
  ),
};

void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();

    // The default fuse bit from the factory enables CLKDIV,
    // so enable full frequency in software.
    clock_prescale_set(clock_div_1);

    // Power reduction. Doesn't save much. :(
    PRR0 = 0b10000101;
    PRR1 = 0b00000001;

    // TODO: check what to do about this
    // Default the charge pump's EN to off
    PORTB &= ~1;
    DDRB |= 1;

}

void keyboard_post_init_kb(void) {
    // This runs after dip_switch_init. We cannot rely on the internal
    // pull-up on the Fn switch pin because the pull-down is weak at about
    // 47K and the AT90USB's internal pull-up is between 20K and 50K.
    setPinInput(F4);

    // enable charge pump to supply green LED with -5V
    setPinOutput(CHARGE_PUMP_ENABLE_PIN);
    writePinHigh(CHARGE_PUMP_ENABLE_PIN);

    // LED on PCB, invisible when assembled
    setPinOutput(PCB_LED_PIN);

    // green LED in between the space keys, lights up on low
    setPinOutput(GREEN_LED_PIN);

    // red LED in between the space keys
    setPinOutput(RED_LED_PIN);

    debug_enable = true;
    debug_matrix = true;

    keyboard_post_init_user();
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
    case 0:
        if (active) {
            layer_off(_CUSTOM);
            writePinHigh(GREEN_LED_PIN);
         } else {
            layer_on(_CUSTOM);
            writePinLow(GREEN_LED_PIN);
        }
    }
    return dip_switch_update_user(index, active);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

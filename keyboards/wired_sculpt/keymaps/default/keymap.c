// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <avr/power.h>
#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
  [_BASE] = LAYOUT_iso(
    /*  0      1        2        3        4        5         6        7       8        9         10      11          12         13         14        15       16  */
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,     KC_F12,  KC_PSCR, KC_SCRL, KC_PAUSE, KC_CALC,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,    KC_EQL,           KC_BSPC, KC_DEL, KC_HOME,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC,                           KC_END,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_NUHS, KC_ENT,  KC_INS,  KC_PGUP,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,          KC_UP,   KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,  KC_SPC,           KC_RALT, KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
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

    // Default the charge pump's EN to off
    PORTB &= ~1;
    DDRB |= 1;

#if LATENCY_MODE_ENABLE
    setPinOutput(LATENCY_MODE_PIN);
#endif
}

void keyboard_post_init_kb(void) {
    // This runs after dip_switch_init. We cannot rely on the internal
    // pull-up on the Fn switch pin because the pull-down is weak at about
    // 47K and the AT90USB's internal pull-up is between 20K and 50K.
    setPinInput(F4);

    debug_enable = true;

    keyboard_post_init_user();
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
    case 0:
        if (active) {
            layer_off(1);
        } else {
            layer_on(1);
        }
    }
    return dip_switch_update_user(index, active);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#if LATENCY_MODE_ENABLE
    static int count = 0;
    if (record->event.pressed) {
        ++count;
#ifdef LATENCY_MODE_PIN
        writePinHigh(LATENCY_MODE_PIN);
#endif
    } else {
        --count;
        if (count < 0) {
            count = 0;
        }
        if (count == 0) {
            writePinLow(LATENCY_MODE_PIN);
        }
    }
#endif
#if DEBOUNCE_DEBUG_ENABLE
    const uint8_t both_shifts = MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT);
    switch (keycode) {
    case KC_H:
        if ((get_mods() & both_shifts) == both_shifts) {
            debounce_debug();
            return false;
        }
    }
#endif

    return process_record_user(keycode, record);
}

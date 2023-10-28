// Copyright 2023 leobossmann (@leobossmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DIP_SWITCH_PINS {F4}
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// the green led requires -5V, the board has a charge pump for this purpose. This pin enables it.
#define CHARGE_PUMP_ENABLE_PIN B0

#define PCB_LED_PIN B5
#define GREEN_LED_PIN B6
#define RED_LED_PIN B7

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

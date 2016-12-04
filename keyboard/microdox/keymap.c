/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "keymap_common.h"
#include "backlight.h"

/* const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(ESC,  1,    2,    3,    4,    5,    EQL,  \
           TAB,  Q,    W,    E,    R,    T,    FN1,  \
           FN0,  A,    S,    D,    F,    G,          \
           LCTL, Z,    X,    C,    V,    B,    LSFT,  \
                                         SPC,  BSPC, \
           MINS, 6,    7,    8,    9,    0,    BSPC, \
           FN0,  Y,    U,    I,    O,    P,    BSLS, \
                 H,    J,    K,    L,    SCLN, LALT, \
           LGUI, N,    M,    COMM, DOT,  SLSH, RSFT, \
           ENT,  SPC),

    KEYMAP(TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, QUOT, COMM, DOT,  P,    Y,    TRNS, \
           TRNS, A,    O,    E,    U,    I,          \
           TRNS, SCLN, Q,    J,    K,    X,    TRNS, \
                                         TRNS, TRNS, \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, F,    G,    C,    R,    L,    SLSH, \
                 D,    H,    T,    N,    S,    TRNS, \
           TRNS, B,    M,    W,    V,    Z,    TRNS, \
           TRNS, TRNS),

    KEYMAP(GRV,  F1,   F2,   F3,   F4,   F5,   F6,   \
           TRNS, WH_L, UP,   WH_R, WH_U, NLCK, FN0,  \
           TRNS, LEFT, DOWN, RGHT, WH_D, FN2,        \
           TRNS, TRNS, TRNS, TRNS, TRNS, FN4,  LGUI, \
                                         HOME, PGUP, \
           F7,   F8,   F9,   F10,  F11,  F12,  DEL,  \
           TRNS, TRNS, TRNS, SLCK, INS,  PSCR, QUOT, \
                 PGUP, PAUS, LBRC, RBRC, EQL,  MINS, \
           RGUI, PGDN, TRNS, COMM, TRNS, TRNS, TRNS, \
           PGDN, END),
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(2),
    [1] = ACTION_LAYER_TOGGLE(1),
    [2] = ACTION_BACKLIGHT_TOGGLE(),
    [3] = ACTION_BACKLIGHT_LEVEL(CASELIGHT),
    [4] = ACTION_BACKLIGHT_LEVEL(OFF)
};

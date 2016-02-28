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


/* const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(ESC,  1,    2,    3,    4,    5,    LGUI, \
           TAB,  Q,    W,    E,    R,    T,    FN0,  \
           LSFT, A,    S,    D,    F,    G,          \
           LCTL, Z,    X,    C,    V,    B,    HOME, \
                                         SPC,  BSPC, \
           SLCK, 6,    7,    8,    9,    0,    BSPC, \
           FN0,  Y,    U,    I,    O,    P,    BSLS, \
                 H,    J,    K,    L,    SCLN, RSFT, \
           EQL,  N,    M,    COMM, DOT,  SLSH, RCTL, \
           SPC,  ENT),

    KEYMAP(ESC,  F1,   F2,   F3,   F4,   F5,   F6,   \
           TAB,  WH_L, UP,   WH_R, WH_U, TRNS, FN0,  \
           LSFT, LEFT, DOWN, RGHT, WH_D, TRNS,       \
           LCTL, TRNS, TRNS, TRNS, TRNS, TRNS, PGUP, \
                                         TRNS, TRNS, \
           F7,   F8,   F9,   F10,  F11,  F10,  BSPC, \
           FN0,  TRNS, TRNS, TRNS, INS,  PSCR, BSLS, \
                 HOME, TRNS, TRNS, TRNS, TRNS, RSFT, \
           MINS, END,  TRNS, COMM, TRNS, TRNS, RCTL, \
           TRNS, TRNS),
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};

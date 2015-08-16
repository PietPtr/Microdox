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


#define KC_S1       ACTION_MODS_KEY(MOD_LSFT, KC_1)
#define KC_S2       ACTION_MODS_KEY(MOD_LSFT, KC_2)
#define KC_S3       ACTION_MODS_KEY(MOD_LSFT, KC_3)
#define KC_S4       ACTION_MODS_KEY(MOD_LSFT, KC_4)
#define KC_S5       ACTION_MODS_KEY(MOD_LSFT, KC_5)

#define KC_S6       ACTION_MODS_KEY(MOD_LSFT, KC_6)
#define KC_S7       ACTION_MODS_KEY(MOD_LSFT, KC_7)
#define KC_S8       ACTION_MODS_KEY(MOD_LSFT, KC_8)
#define KC_S9       ACTION_MODS_KEY(MOD_LSFT, KC_9)
#define KC_S0       ACTION_MODS_KEY(MOD_LSFT, KC_0)

#define KC_S_GRV    ACTION_MODS_KEY(MOD_LSFT, KC_GRV)
#define KC_S_SLSH   ACTION_MODS_KEY(MOD_LSFT, KC_SLSH)
#define KC_S_MINS   ACTION_MODS_KEY(MOD_LSFT, KC_MINS)
#define KC_S_EQL    ACTION_MODS_KEY(MOD_LSFT, KC_EQL)
#define KC_S_LBRC   ACTION_MODS_KEY(MOD_LSFT, KC_LBRC)
#define KC_S_RBRC   ACTION_MODS_KEY(MOD_LSFT, KC_RBRC)
#define KC_S_BSLS   ACTION_MODS_KEY(MOD_LSFT, KC_BSLS)

#define KC_C_UP     ACTION_MODS_KEY(MOD_LCTL, KC_UP)
#define KC_C_DOWN   ACTION_MODS_KEY(MOD_LCTL, KC_DOWN)
#define KC_C_LEFT   ACTION_MODS_KEY(MOD_LCTL, KC_LEFT)
#define KC_C_RIGHT  ACTION_MODS_KEY(MOD_LCTL, KC_RIGHT)
#define KC_C_HOME   ACTION_MODS_KEY(MOD_LCTL, KC_HOME)
#define KC_C_END    ACTION_MODS_KEY(MOD_LCTL, KC_END)

#define KC_C_BSPC   ACTION_MODS_KEY(MOD_LCTL, KC_BSPC)
#define KC_C_DEL    ACTION_MODS_KEY(MOD_LCTL, KC_DEL)



    /* KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \ */
    /*        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \ */
    /*        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NO,  ENT,  \ */
    /*        LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,NO,  RSFT, \ */
    /*        LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL), */
/* static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
/*     {{KC_A}}, */
/* }; */
/* const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
/*     /1* 0: qwerty *1/ */
/*     /1* KC_TAB,  KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, *1/ */
/*     /1*     KC_ENT,  KC_A,    KC_O,    KC_E,   KC_U, KC_I, *1/ */
/*     /1*     KC_LSFT, KC_SCLN, KC_Q,    KC_J,   KC_K, KC_X, *1/ */
/*     /1*     KC_SPC,  KC_BSPC, KC_LALT, KC_LCTL, KC_Z, KC_ESC, *1/ */
/*         /1* left hand *1/ */
/*         KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R , KC_T   , */
/*         KC_ESC  , KC_A    , KC_S    , KC_D    , KC_F , KC_G   , */
/*         KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V , KC_B   , */
/*         KC_NO  , KC_LCTL , KC_SPC, KC_LGUI , KC_LALT , KC_ENT, */
/*         /1* right hand *1/ */
/*         KC_Y   , KC_U   , KC_I    , KC_O   , KC_P    , KC_BSPC  , */
/*         KC_H   , KC_J   , KC_K    , KC_L   , KC_SCLN , KC_QUOT  , */
/*         KC_N   , KC_M   , KC_COMM , KC_DOT , KC_BSLS , KC_RSHIFT, */
/*         KC_SPC , KC_RALT , KC_RGUI , KC_RSHIFT , KC_RCTL , KC_NO */
/* }; */

/* const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(
        /* left hand */
           FN6  , Q    , W   , E    , R    , T ,
           FN5  , A    , S   , D    , F    , G ,
           LALT , Z    , X   , C    , V    , B ,
           NO, FN2 , FN1 , SPC , LCTL ,
        /* right hand */
           /* Y    , U    , I   , O    , P    , DEL , */
           Y    , U    , I   , O    , P    , BSLS ,
           H    , J    , K   , L    , SCLN , QUOT ,
           N    , M    , COMM, DOT  , SLSH , RALT ,
           /* FN3 , BSPC , FN0  , RGUI, NO */
           BSPC , FN3 , FN0  , RGUI, NO
        )
    , /* 1: symbol */
    KEYMAP_NO_PREFIX(
       /* /1* left hand *1/ */
       /*     KC_GRV         , SHIFT(KC_GRV) , KC_2           , KC_3        , KC_4           , KC_5        , */
       /*     KC_TRNS        , SHIFT(KC_1)   , SHIFT(KC_LBRC) , KC_1        , SHIFT(KC_9)    , KC_MINS     , */
       /*     KC_TRNS        , SHIFT(KC_4)   , SHIFT(KC_2)    , SHIFT(KC_3) , SHIFT(KC_MINS) , SHIFT(KC_5) , */
       /*     KC_TRNS        , KC_TRNS       , KC_TRNS        , KC_TRNS     , KC_TRNS        , */
       /*  /1* right hand *1/ */
       /*     KC_6           , KC_7          , KC_8           , KC_9        , SHIFT(KC_BSLS) , KC_TRNS     , */
       /*     KC_EQL         , SHIFT(KC_0)   , KC_0           , KC_RBRC     , KC_LBRC        , KC_BSLS     , */
       /*     SHIFT(KC_6)    , SHIFT(KC_EQL) , SHIFT(KC_8)    , */
       /*     SHIFT(KC_RBRC) , SHIFT(KC_7)   , KC_TRNS        , */
       /*     KC_TRNS        , KC_TRNS       , KC_TRNS        , KC_TRNS     , KC_TRNS */
       /* left hand */
           KC_TRNS , KC_W      , KC_2        , KC_3        , KC_4        , KC_5           ,
           KC_TRNS , KC_1        , KC_LBRC     , SHIFT(KC_9) , KC_MINS     , SHIFT(KC_MINS) ,
           KC_TRNS , SHIFT(KC_1) , SHIFT(KC_2) , SHIFT(KC_3) , SHIFT(KC_4) , SHIFT(KC_5)    ,
           KC_TRNS , KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS     ,
        /* right hand */
           KC_6          , KC_7        , KC_8        , KC_9           , KC_E           , KC_GRV        ,
           SHIFT(KC_EQL) , KC_EQL      , SHIFT(KC_0) , KC_RBRC        , KC_0           , SHIFT(KC_GRV) ,
           SHIFT(KC_6)   , SHIFT(KC_7) , SHIFT(KC_8) , SHIFT(KC_RBRC) , SHIFT(KC_LBRC) , KC_TRNS       ,
           KC_TRNS       , KC_TRNS     , KC_TRNS     , KC_TRNS        , KC_TRNS
    )
    , /* 2: fn */
    KEYMAP_NO_PREFIX(
        /* left hand */
           KC_INS        , KC_DEL        , KC_HOME       , KC_UP          , KC_END      , KC_PGUP   ,
           KC_BSPC       , KC_ESC        , KC_LEFT       , KC_DOWN        , KC_RIGHT    , KC_PGDOWN ,
           KC_TRNS       , KC_F1         , KC_F2         , KC_F3          , KC_F4       , KC_F5     ,
           KC_TRNS       , KC_TRNS       , KC_TRNS       , KC_TRNS        , KC_TRNS     ,
        /* right hand */
           KC_NO        , CTRL(KC_HOME) , CTRL(KC_UP)   , CTRL(KC_END)   , KC_DEL       , KC_F12    ,
           /* CTRL(KC_DEL) , CTRL(KC_LEFT) , CTRL(KC_DOWN) , CTRL(KC_RIGHT) , CTRL(KC_BSPC) , KC_F11    , */
           KC_TAB , CTRL(KC_LEFT) , CTRL(KC_DOWN) , CTRL(KC_RIGHT) , KC_ENT , KC_F11    ,
           KC_F6        , KC_F7         , KC_F8         , KC_F9          , KC_F10        , KC_TRNS   ,
           KC_TRNS      , KC_TRNS       , KC_TRNS       , KC_TRNS        , KC_TRNS
        )
    , /* 3: media */
    KEYMAP_NO_PREFIX(
        /* left hand */
           ALT(KC_TAB) , KC_PSCR   , KC_MSTP   , KC__VOLUP  , KC_STOP  , KC_F11    ,
           /* SHIFT(ALT(KC_TAB)) , KC__MUTE  , KC_MNXT   , KC__VOLDOWN, KC_MPRV , */
           SHIFT(ALT(KC_TAB)) , KC__MUTE  , KC_MNXT   , KC__VOLDOWN, KC_MPRV ,
           KC_APP,
           KC_LGUI , CTRL(KC_SLSH), CTRL(KC_B), CTRL(KC_I) , CTRL(KC_DOT), CTRL(KC_SCLN) ,
           KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS   ,
        /* right hand */
           KC_NO   , KC_BTN1   , KC_MS_U   , KC_BTN2    , KC_NO     , KC_NO      ,
           KC_NO   , KC_MS_L   , KC_MS_D   , KC_MS_R    , KC_NO     , KC_NO      ,
           KC_NO   , KC_NO     , KC_NO     , KC_NO      , KC_NO     , KC_TRNS    ,
           KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS
        )
    , /* 4: num pad */
    KEYMAP_NO_PREFIX(
        /* left hand */
           KC_NO   , KC_W    , KC_P7 , KC_P8   , KC_P9   , KC_PSLS ,
           KC_PENT , KC_PDOT , KC_P4 , KC_P5   , KC_P6   , KC_PAST ,
           KC_DEL  , KC_NLCK , KC_P1 , KC_P2   , KC_P3   , KC_BSPC ,
           KC_TRNS , KC_PMNS , KC_P0  , KC_PPLS , KC_TRNS ,
        /* right hand */
           KC_NO   , KC_NO   , KC_NO   , KC_NO    , KC_NO     , KC_NO      ,
           KC_NO   , KC_NO   , KC_NO   , KC_NO    , KC_NO     , KC_NO      ,
           KC_NO   , KC_NO   , KC_NO   , KC_NO    , KC_NO     , KC_TRNS    ,
           KC_TRNS , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS
        )
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_MOMENTARY(1), // FN0 (L1)
    ACTION_LAYER_MOMENTARY(2), // FN1 (fn)
    ACTION_LAYER_MOMENTARY(3), // FN2 (media)

    ACTION_MODS_ONESHOT(MOD_LSFT), // FN3 (sticky L shift)
    ACTION_MODS_ONESHOT(MOD_RSFT), // FN4 (sticky R shift)
    ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ENT), // FN5
    ACTION_LAYER_TAP_KEY(1, KC_TAB), // FN6
    ACTION_LAYER_TOGGLE(4), // FN7 (num pad)
    ACTION_LAYER_TOGGLE(0), // FN8 (L0)
    /* MACRO(T(END), D(LSHIFT), T(HOME), U(LSHIFT), D(LCTRL), T(X), U(LCTRL), END), // FN9 cut line */
    /* MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END ), */
};



#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
/* uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key) */
uint16_t actionmap_key_to_action(uint8_t layer, keypos_t key)
{
    if (layer < KEYMAPS_SIZE) {
        /* return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]); */
        return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        /* return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]); */
        return pgm_read_word(&keymaps[0][(key.row)][(key.col)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}

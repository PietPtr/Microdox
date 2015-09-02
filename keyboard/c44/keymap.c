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


/* const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    // qwfpg jluy;
    // arstd hneio
    // zxcvb km,./

    // qwfdk jluy;
    // arstg bnhio
    // zvcpx -m,./
    //   _     e
    KEYMAP(
        /* left hand */
           FN6  , Q   , W    , F    , D    , K    ,
           FN5  , A   , R    , S    , T    , G    ,
           LALT , Z   , V    , C    , P    , X    ,
           NO   , FN2 , FN1  , SPC  , LCTL ,
        /* right hand */
           J    , L   , U    , Y    , SCLN , BSPC    ,
           B    , N   , H    , I    , O    , QUOT ,
           MINS , M   , COMM , DOT  , SLSH , ENT  ,
           /* BSPC , FN3 , FN0  , RGUI , NO */
           FN3 , E, FN0  , RGUI , NO
        )
    , /* 1: symbol */
    KEYMAP_NO_PREFIX(
       /* left hand */
           KC_TRNS        , KC_GRV      , KC_2        , KC_3          , KC_4          , KC_5           ,
           KC_TRNS        , KC_1        , KC_BSLS     , SHIFT(KC_9)   , KC_LBRC       , SHIFT(KC_LBRC) ,
           KC_TRNS        , SHIFT(KC_1) , SHIFT(KC_2) , SHIFT(KC_3)   , SHIFT(KC_4)   , SHIFT(KC_5)    ,
           KC_TRNS        , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_TRNS       ,
        /* right hand */
           KC_6           , KC_7        , KC_8        , KC_9          , KC_DOT        , KC_COMM        ,
           SHIFT(KC_RBRC) , KC_RBRC     , SHIFT(KC_0) , KC_EQL        , KC_0          , KC_MINS        ,
           SHIFT(KC_6)    , SHIFT(KC_7) , SHIFT(KC_8) , SHIFT(KC_EQL) , SHIFT(KC_GRV) , KC_TRNS        ,
           KC_TRNS        , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_TRNS
    )
    , /* 2: fn */
    KEYMAP_NO_PREFIX(
        /* left hand */
           KC_INS        , KC_DEL        , KC_HOME       , KC_UP          , KC_END      , KC_PGUP   ,
           KC_BSPC       , KC_ESC        , KC_LEFT       , KC_DOWN        , KC_RIGHT    , KC_PGDOWN ,
           KC_TRNS       , KC_F1         , KC_F2         , KC_F3          , KC_F4       , KC_F5     ,
           KC_TRNS       , KC_TRNS       , KC_TRNS       , KC_TRNS        , KC_TRNS     ,
        /* right hand */
           CTRL(KC_PGUP)   , CTRL(KC_HOME) , CTRL(KC_UP)   , CTRL(KC_END)   , CTRL(KC_DEL)   , KC_F12  ,
           CTRL(KC_PGDOWN) , CTRL(KC_LEFT) , CTRL(KC_DOWN) , CTRL(KC_RIGHT) , CTRL(KC_BSPC) , KC_F11  ,
           KC_F6           , KC_F7         , KC_F8         , KC_F9          , KC_F10        , KC_TRNS ,
           KC_TRNS         , KC_BSPC       , KC_TRNS       , KC_TRNS        , KC_TRNS
        )
    , /* 3: media */
    KEYMAP_NO_PREFIX(
        /* left hand */
           ALT(KC_TAB)        , KC_PSCR       , 164        , KC__VOLUP   , KC_STOP      , KC_F11        ,
           SHIFT(ALT(KC_TAB)) , KC__MUTE      , KC_MNXT    , KC__VOLDOWN , KC_MPRV      , KC_APP        ,
           KC_LGUI            , CTRL(KC_SLSH) , CTRL(KC_B) , CTRL(KC_I)  , CTRL(KC_DOT) , CTRL(KC_SCLN) ,
           KC_TRNS            , KC_TRNS       , KC_TRNS    , KC_TRNS     , KC_TRNS      ,
        /* right hand */
           KC_NO              , KC_BTN1       , KC_MS_U    , KC_BTN2     , KC_NO        , KC_NO         ,
           KC_NO              , KC_MS_L       , KC_MS_D    , KC_MS_R     , KC_NO        , KC_NO         ,
           KC_NO              , KC_NO         , KC_NO      , KC_NO       , KC_NO        , KC_TRNS       ,
           KC_TRNS            , KC_TRNS       , KC_TRNS    , KC_TRNS     , KC_TRNS
        )
    , /* 4: num pad */
    KEYMAP_NO_PREFIX(
        /* left hand */
           KC_NO         , KC_W    , KC_P7   , KC_P8   , KC_P9   , KC_PSLS ,
           KC_PENT       , KC_PDOT , KC_P4   , KC_P5   , KC_P6   , KC_PAST ,
           KC_DEL        , KC_NLCK , KC_P1   , KC_P2   , KC_P3   , KC_BSPC ,
           KC_TRNS       , KC_PMNS , KC_P0   , KC_PPLS , KC_TRNS ,
        /* right hand */
           KC_NO         , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
           KC_NO         , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
           KC_NO         , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_TRNS ,
           KC_TRNS       , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
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
    ACTION_MODS_TAP_KEY(MOD_LSFT, KC_MINS), // FN9
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

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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(
        /* left hand */
           FN7   , Q   , W    , E    , R    , T    ,
           FN6   , A   , S    , D    , F    , G    ,
           LALT  , Z   , X    , C    , V    , B    ,
           FN16  , FN3 , LCTL , SPC  , FN2 ,
        /* right hand */
           Y    , U   , I    , O    , P    , MINS ,
           H    , J   , K    , L    , SCLN , QUOT ,
           N    , M   , COMM , DOT  , SLSH , ESC  ,
           BSPC , FN4 , FN1 , LGUI , FN16
        )
    , /* 1: dvorak */
    KEYMAP(
        /* left hand */
           FN7   , QUOT , DOT  , COMM , R   , T     ,
           FN6   , A    , O    , E    , U   , I     ,
           LALT  , SCLN , Q    , J    , K   , X     ,
           TRNS  , FN3  , LCTL , SPC  , FN2 ,
        /* right hand */
           F     , G    , C    , R    , L   , SLASH ,
           D     , H    , T    , N    , S   , MINS  ,
           B     , M    , W    , V    , Z   , ESC   ,
           BSPC  , FN4  , FN1  , LGUI , TRNS
        )
    , /* 2: colemak */
    KEYMAP(
        /* left hand */
           FN7   , Q   , W    , F    , P    , G    ,
           FN6   , A   , R    , S    , T    , D    ,
           LALT  , Z   , X    , C    , V    , B    ,
           TRNS  , FN3 , LCTL , SPC  , FN2  ,
        /* right hand */
           J    , L   , U    , Y    , SCLN , MINS ,
           H    , N   , E    , I    , O    , QUOT ,
           K    , M   , COMM , DOT  , SLSH , ESC  ,
           BSPC , FN4 , FN1  , LGUI , TRNS
        )
    , /* 3: symbol */
    KEYMAP_NO_PREFIX(
       /* left hand */
           KC_TRNS        , KC_GRV      , KC_2        , KC_3          , KC_4          , KC_5           ,
           KC_TRNS        , KC_1        , KC_BSLS     , SHIFT(KC_9)   , KC_LBRC       , SHIFT(KC_LBRC) ,
           KC_TRNS        , SHIFT(KC_1) , SHIFT(KC_2) , SHIFT(KC_3)   , SHIFT(KC_4)   , SHIFT(KC_5)    ,
           KC_TRNS        , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_TRNS       ,
        /* right hand */
           KC_6           , KC_7        , KC_8        , KC_9          , KC_DOT        , KC_COMM        ,
           SHIFT(KC_RBRC) , KC_RBRC     , SHIFT(KC_0) , KC_EQL        , KC_0          , KC_MINS        ,
           SHIFT(KC_6)    , SHIFT(KC_7) , SHIFT(KC_8) , SHIFT(KC_EQL) , SHIFT(KC_GRV) , KC_FN0        ,
           KC_TRNS        , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_TRNS
    )
    , /* 4: fn */
    KEYMAP_NO_PREFIX(
        /* left hand */
           KC_INS        , KC_BSPC       , KC_HOME       , KC_UP          , KC_END      , KC_PGUP   ,
           KC_DEL        , KC_ESC        , KC_LEFT       , KC_DOWN        , KC_RIGHT    , KC_PGDOWN ,
           KC_TRNS       , KC_F1         , KC_F2         , KC_F3          , KC_F4       , KC_F5     ,
           KC_TRNS       , KC_TRNS       , KC_TRNS       , KC_TRNS        , KC_TRNS     ,
        /* right hand */
           CTRL(KC_PGUP)   , CTRL(KC_HOME) , CTRL(KC_UP)   , CTRL(KC_END)   , CTRL(KC_DEL)  , KC_F12  ,
           CTRL(KC_PGDOWN) , CTRL(KC_LEFT) , CTRL(KC_DOWN) , CTRL(KC_RIGHT) , CTRL(KC_BSPC) , KC_F11  ,
           KC_F6           , KC_F7         , KC_F8         , KC_F9          , KC_F10        , KC_FN0 ,
           KC_TRNS         , KC_TRNS       , KC_TRNS       , KC_TRNS        , KC_TRNS
        )
    , /* 5: media */
    KEYMAP_NO_PREFIX(
        /* left hand */
           ALT(KC_TAB)        , KC_PSCR       , KC_MPLY    , KC__VOLUP   , KC_STOP      , KC_F11        ,
           SHIFT(ALT(KC_TAB)) , KC__MUTE      , KC_MPRV    , KC__VOLDOWN , KC_MNXT      , KC_APP        ,
           KC_LGUI            , CTRL(KC_Y)    , CTRL(KC_B) , CTRL(KC_I)  , CTRL(KC_DOT) , CTRL(KC_SCLN) ,
           KC_TRNS            , KC_TRNS       , KC_TRNS    , KC_TRNS     , KC_TRNS      ,
        /* right hand */
           KC_WH_U , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_NO   , KC_NO  ,
           KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_NO   , KC_NO  ,
           KC_FN12 , KC_FN13 , KC_FN14 , KC_FN15   , KC_NO   , KC_FN0 ,
           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
        )
    , /* 6: mirrored - L0 */
    KEYMAP(
        /* left hand */
           MINS , P    , O    , I    , U    , Y    ,
           QUOT , SCLN , L    , K    , J    , H    ,
           FN0  , SLSH , DOT  , COMM , M    , N    ,
           FN16 , RGUI  , FN9  , FN4  , BSPC  ,
        /* right hand */
           T    , R   , E    , W    , Q    , FN7 ,
           G    , F   , D    , S    , A    , FN6 ,
           B    , V   , C    , X    , Z , LALT  ,
           FN10  , SPC , LCTL , FN11 , FN16
        )
    , /* 7: mirrored - L1 */
    KEYMAP_NO_PREFIX(
       /* left hand */
           KC_TRNS        , KC_GRV      , KC_9        , KC_8          , KC_7          , KC_6           ,
           KC_TRNS        , KC_0        , KC_BSLS     , SHIFT(KC_9)   , KC_LBRC       , SHIFT(KC_LBRC) ,
           KC_TRNS        , SHIFT(KC_1) , SHIFT(KC_2) , SHIFT(KC_3)   , SHIFT(KC_4)   , SHIFT(KC_5)    ,
           KC_TRNS        , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_TRNS       ,
        /* right hand */
           KC_6           , KC_7        , KC_8        , KC_9          , KC_DOT        , KC_COMM        ,
           SHIFT(KC_RBRC) , KC_RBRC     , SHIFT(KC_0) , KC_EQL        , KC_0          , KC_MINS        ,
           SHIFT(KC_6)    , SHIFT(KC_7) , SHIFT(KC_8) , SHIFT(KC_EQL) , SHIFT(KC_GRV) , KC_FN0        ,
           KC_TRNS        , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_TRNS
        )
    , /* 8: mirrored - fn */
    KEYMAP_NO_PREFIX(
        /* left hand */
           KC_F12  , CTRL(KC_DEL)  , CTRL(KC_HOME) , CTRL(KC_UP)   , CTRL(KC_END)   , CTRL(KC_PGUP)   ,
           KC_F11  , CTRL(KC_BSPC) , CTRL(KC_LEFT) , CTRL(KC_DOWN) , CTRL(KC_RIGHT) , CTRL(KC_PGDOWN) ,
           KC_TRNS , KC_F10        , KC_F9         , KC_F8         , KC_F7          , KC_F6           ,
           KC_TRNS , KC_TRNS       , KC_TRNS       , KC_TRNS       , KC_TRNS        ,
        /* right hand */
           KC_PGUP   , KC_HOME , KC_UP   , KC_END   , KC_DEL  , KC_INS  ,
           KC_PGDOWN , KC_LEFT , KC_DOWN , KC_RIGHT , KC_ESC  , KC_BSPC ,
           KC_F5     , KC_F4   , KC_F3   , KC_F2    , KC_F1   , KC_TRNS ,
           KC_TRNS   , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS
        )
    , /* 9: mirrored - media */
    KEYMAP_NO_PREFIX(
        /* /1* right hand *1/ */
        /*    KC_FN12 , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_NO   , KC_NO  , */
        /*    KC_FN13 , KC_MS_L , KC_MS_D , KC_MS_R , KC_NO   , KC_NO  , */
        /*    KC_FN14 , KC_FN8  , KC_FN12 , KC_NO   , KC_NO   , KC_FN0 , */
        /*    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS */
        /* left hand */
           KC_NO   , KC_NO   , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_FN12 ,
           KC_NO   , KC_NO   , KC_MS_L , KC_MS_D , KC_MS_R , KC_FN13 ,
           KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_FN14 ,
           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        /* /1* left hand *1/ */
        /*    ALT(KC_TAB)        , KC_PSCR       , 164        , KC__VOLUP   , KC_STOP      , KC_F11        , */
        /*    SHIFT(ALT(KC_TAB)) , KC__MUTE      , KC_MNXT    , KC__VOLDOWN , KC_MPRV      , KC_APP        , */
        /*    KC_LGUI            , CTRL(KC_SLSH) , CTRL(KC_B) , CTRL(KC_I)  , CTRL(KC_DOT) , CTRL(KC_SCLN) , */
        /*    KC_TRNS            , KC_TRNS       , KC_TRNS    , KC_TRNS     , KC_TRNS      , */
        /* right hand */
           KC_F11  , KC_STOP , KC__VOLUP   , KC_MPLY , KC_PSCR  , KC_NO ,
           KC_APP  , KC_MPRV , KC__VOLDOWN , KC_MNXT , KC__MUTE , KC_NO ,
           KC_NO   , KC_NO   , KC_NO       , KC_NO   , KC_NO    , KC_NO ,
           KC_TRNS , KC_TRNS , KC_TRNS     , KC_TRNS , KC_TRNS
        )
    , /* 10:  */
        KEYMAP(
            /* left hand */
            FN7   , Q   , W    , E    , R    , T    ,
            FN6   , Z   , X    , Z    , X    , G    ,
            LALT  , Z   , X    , C    , V    , B    ,
            FN16  , FN3 , LCTL , Z  , FN2    ,
            /* right hand */
            Y    , U   , I    , O    , P    , MINS ,
            H    , X   , Z    , X    , Z    , QUOT ,
            N    , M   , COMM , DOT  , SLSH , FN0  ,
            BSPC , Z , FN1  , LGUI , FN16
            )
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_SET_CLEAR(0), // FN0 (L0)
    ACTION_LAYER_ONESHOT(3), // FN1 (L1)
    ACTION_LAYER_ONESHOT(4), // FN2 (fn)
    ACTION_LAYER_ONESHOT(5), // FN3 (media)

    ACTION_MODS_ONESHOT(MOD_LSFT), // FN4 (sticky L shift)
    ACTION_MODS_ONESHOT(MOD_RSFT), // FN5 (sticky R shift)
    ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ENT), // FN6
    ACTION_LAYER_TAP_KEY(1, KC_TAB), // FN7

    ACTION_LAYER_SET_CLEAR(6), // FN8 (mirrored)
    ACTION_LAYER_TAP_TOGGLE(7), // FN9 (L1 mirrored)
    ACTION_LAYER_TAP_TOGGLE(8), // FN10 (fn mirrored)
    ACTION_LAYER_TAP_TOGGLE(9), // FN11 (media mirrored)
    ACTION_DEFAULT_LAYER_SET(0), // FN12 Switch base layer to Qwerty
    ACTION_DEFAULT_LAYER_SET(1), // FN13 Switch base layer to Dvorak
    ACTION_DEFAULT_LAYER_SET(2), // FN14 Switch base layer to Colemak
    ACTION_LAYER_TOGGLE(10), // FN15
    ACTION_LAYER_TOGGLE(6), // FN16 (mirrored)
    ACTION_LAYER_ONESHOT(3), // FN17 (L1 oneshot)
    ACTION_LAYER_ONESHOT(4), // FN18 (fn layer)
};

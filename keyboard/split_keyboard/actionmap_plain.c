#include <avr/pgmspace.h>
#include "actionmap.h"
#include "actionmap_common.h"
#include "action_code.h"
#include "action_layer.h"

/* id for user defined functions */
enum function_id {
    GOTO_DEFAULT_LAYER,
};

#define AC_FN1            ACTION_LAYER_ONESHOT(3)
#define AC_FN2            ACTION_LAYER_ONESHOT(4)
#define AC_FN3            ACTION_LAYER_ONESHOT(5)
#define AC_SSFT           ACTION_MODS_ONESHOT(MOD_LSFT)
#define AC_SFT_ENT        ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ENT)

#define AC_FN0            ACTION_FUNCTION(GOTO_DEFAULT_LAYER)
#define AC_QWERTY         ACTION_DEFAULT_LAYER_SET(0)
#define AC_DVORAK         ACTION_DEFAULT_LAYER_SET(1)
#define AC_COLEMAK        ACTION_DEFAULT_LAYER_SET(2)

const uint16_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* qwerty */
    [0] = ACTIONMAP(
        /* left hand */
           TAB     , Q   , W    , E   , R   , T ,
           SFT_ENT , A   , S    , D   , F   , G ,
           LALT    , Z   , X    , C   , V   , B ,
           NO      , FN3 , LCTL , SPC , FN2 ,
        /* right hand */
           Y    , U    , I    , O    , P    , MINS ,
           H    , J    , K    , L    , SCLN , QUOT ,
           N    , M    , COMM , DOT  , SLSH , ESC  ,
           BSPC , SSFT , FN1  , LGUI , NO
    ),
    /* dvorak */
    [1] = ACTIONMAP(
        /* left hand */
           TRNS , QUOT , COMM , DOT  , P    , Y ,
           TRNS , A    , O    , E    , U    , I ,
           TRNS , SCLN , Q    , J    , K    , X ,
           TRNS , TRNS , TRNS , TRNS , TRNS ,
        /* right hand */
           F    , G    , C    , R    , L    , SLSH ,
           D    , H    , T    , N    , S    , MINS ,
           B    , M    , W    , V    , Z    , TRNS  ,
           TRNS , TRNS , TRNS , TRNS , TRNS
    ),
    /* colemak */
    [2] = ACTIONMAP(
        /* left hand */
           TRNS , Q    , W    , F    , P    , G ,
           TRNS , A    , R    , S    , T    , D ,
           TRNS , Z    , X    , C    , V    , B ,
           TRNS , TRNS , TRNS , TRNS , TRNS ,
        /* right hand */
           J    , L    , U    , Y    , SCLN , MINS ,
           H    , N    , E    , I    , O    , QUOT ,
           K    , M    , COMM , DOT  , SLSH , TRNS ,
           TRNS , TRNS , TRNS , TRNS , TRNS
   ),
   /* symbol */
   [3] = ACTIONMAP(
       /* left hand */
           TRNS , GRV  , 2    , 3    , 4    , 5       ,
           TRNS , 1    , BSLS , s(9) , LBRC , s(LBRC) ,
           TRNS , s(1) , s(2) , s(3) , s(4) , s(5)    ,
           TRNS , TRNS , TRNS , TRNS , TRNS ,
        /* right hand */
           6       , 7    , 8    , 9      , DOT    , COMM ,
           s(RBRC) , RBRC , s(0) , EQL    , 0      , MINS ,
           s(6)    , s(7) , s(8) , s(EQL) , s(GRV) , FN0  ,
           TRNS    , TRNS , TRNS , TRNS   , TRNS
    ),
    /* fn */
    [4] = ACTIONMAP(
        /* left hand */
           INS  , BSPC , HOME , UP   , END  , PGUP ,
           DEL  , ESC  , LEFT , DOWN , RGHT , PGDN ,
           TRNS , F1   , F2   , F3   , F4   , F5   ,
           TRNS , TRNS , TRNS , TRNS , TRNS ,
        /* right hand */
           c(PGUP) , c(HOME) , c(UP)   , c(END)  , c(DEL)  , F12 ,
           c(PGDN) , c(LEFT) , c(DOWN) , c(RGHT) , c(BSPC) , F11 ,
           F6      , F7      , F8      , F9      , F10     , FN0 ,
           TRNS    , TRNS    , TRNS    , TRNS    , TRNS
        ),
    /* media */
    [5] = ACTIONMAP(
        /* left hand */
           NO   , PSCR , MPLY , VOLU , MSTP   , F11     ,
           NO   , MUTE , MPRV , VOLD , MNXT   , APP     ,
           LGUI , c(Y) , c(B) , c(I) , c(DOT) , c(SCLN) ,
           TRNS , TRNS , TRNS , TRNS , TRNS   ,
        /* right hand */
           WH_U , BTN1   , MS_U   , BTN2    , NO   , NO  ,
           WH_D , MS_L   , MS_D   , MS_R    , NO   , NO  ,
           NO   , QWERTY , DVORAK , COLEMAK , NO   , FN0 ,
           TRNS , TRNS   , TRNS   , TRNS    , TRNS
    ),
};

/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case GOTO_DEFAULT_LAYER:
            if (!record->event.pressed) {
                layer_clear();
            }
            break;
        default:
            break;
    }
}

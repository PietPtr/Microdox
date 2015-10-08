#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);
action_t keymap_fn_to_action(uint16_t keycode);
action_t keymap_func_to_action(uint16_t keycode);
action_t action_for_key(uint8_t layer, keypos_t key);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

#endif


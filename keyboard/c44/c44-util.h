#ifndef SETUP_H
#define SETUP_H

#include <stdbool.h>
#include <avr/eeprom.h>

extern bool EEMEM EEMEM_isLeftHand;
extern bool isLeftHand;

// slave version of matix scan, defined in matrix.c
void matrix_slave_scan(void);

void setup_hardware(void);
void setup_set_handedness(void);
bool has_usb(void);
void keyboard_slave_loop(void);

#endif

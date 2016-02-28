#ifndef SETUP_H
#define SETUP_H

#include <stdbool.h>
#include <avr/eeprom.h>

extern bool EEMEM EEMEM_isLeftHand;
extern bool isLeftHand;

void setup_hardware(void);
void setup_set_handedness(void);
bool has_usb(void);

#endif

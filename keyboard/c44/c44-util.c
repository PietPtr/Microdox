#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "c44-util.h"
#include "keyboard.h"


bool EEMEM EEMEM_isLeftHand = true;
extern bool isLeftHand = true;

bool has_usb(void) {
   USBCON |= (1 << OTGPADE); //enables VBUS pad
   _delay_us(5);
   return (USBSTA & (1<<VBUS));  //checks state of VBUS
}

void setup_hardware(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    setup_set_handedness();
    sei();
}

void keyboard_slave_loop(void) {
   matrix_init();
   serial_slave_init();

   while (1) {
      matrix_slave_scan();
   }
}

void setup_set_handedness(void) {
    isLeftHand = eeprom_read_byte(&EEMEM_isLeftHand);
}

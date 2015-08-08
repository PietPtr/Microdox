#include "../i2c-slave.h"
#include "uno-matrix.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void setup(void) {
  // turn off arduino uno's led on pin 13
  DDRB |= (1 << 5);
  PORTB &= ~(1 << 5);

  matrix_init();
  i2c_slave_init(0x32);

  // need interrupts for i2c slave code to work
  sei();
}

void loop(void) {
  matrix_scan();
  for(int i=0; i<MATRIX_ROWS; ++i)
    slaveBuffer[i] = matrix_get_row(i);
}

int main(int argc, char *argv[]) {
  setup();
  while (1)
    loop();
}

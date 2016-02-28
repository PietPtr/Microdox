#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <stdbool.h>

#include "i2c-slave.h"

#define BUFFER_POS_INC() (bufferPos = (bufferPos+1)%SLAVE_BUFFER_SIZE)

volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];

static volatile uint8_t bufferPos;
static volatile uint8_t hasSetRegister = false;

ISR(TWI_vect);

void i2c_slave_init(uint8_t address) {
  TWAR = address << 0; // slave i2c address
  // TWEN  - twi enable
  // TWEA  - enable address acknowledgement
  // TWINT - twi interrupt flag
  // TWIE  - enable the twi interrupt
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}

ISR(TWI_vect) {
  uint8_t ack = 1;
  switch(TW_STATUS) {
    case TW_SR_SLA_ACK:
      // this device has been addressed as a slave receiver
      hasSetRegister = false;
      break;

    case TW_SR_DATA_ACK:
      // this device has received data as a slave receiver
      // The first byte that we receive in this transaction sets the location
      // of the read/write location of the slaves memory that it exposes over
      // i2c.  After that, bytes will be written at bufferPos, incrementing
      // bufferPos after each write.
      if(!hasSetRegister) {
        bufferPos = TWDR;
        // don't acknowledge the master if this memory loctaion is out of bounds
        if ( bufferPos >= SLAVE_BUFFER_SIZE ) {
          ack = 0;
          bufferPos = 0;
        }
        hasSetRegister = true;
      } else {
        slaveBuffer[bufferPos] = TWDR;
        BUFFER_POS_INC();
      }
      break;

    case TW_ST_SLA_ACK:
    case TW_ST_DATA_ACK:
      // master has addressed this device as a slave transmitter and is
      // requesting data.
      TWDR = slaveBuffer[bufferPos];
      BUFFER_POS_INC();
      break;

    case TW_BUS_ERROR: // something went wrong, reset twi state
      TWCR = 0;
    default:
      break;
  }
  // Reset everything, so we are ready for the next TWI interrupt
  TWCR |= (1<<TWIE) | (1<<TWINT) | (ack<<TWEA) | (1<<TWEN);
}

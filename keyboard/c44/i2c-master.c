#include <util/twi.h>
#include "i2c-master.h"

// Limits the amount of we wait for any one i2c transaction.
// Since were running SCL line 100kHz (=> 10μs/bit), and each transactions is
// 9 bits, a single transaction will take around 90μs to complete.
//
// (F_CPU/SCL_CLOCK)  =>  # of μC cycles to transfer a bit
// poll loop takes at least 8 clock cycles to execute
#define I2C_LOOP_TIMEOUT (9+1)*(F_CPU/SCL_CLOCK)/8

// Wait for an i2c operation to finish
inline static
void i2c_delay(void) {
  uint16_t lim = 0;
  while(!(TWCR & (1<<TWINT)) && lim < I2C_LOOP_TIMEOUT)
    lim++;

  // easier way, but will wait slightly longer
  // _delay_us(100);
}

// Setup twi to run at 100kHz
void i2c_master_init(void) {
  // no prescaler
  TWSR = 0;
  // Set TWI clock frequency to SCL_CLOCK. Need TWBR>10.
  // Check datasheets for more info.
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}

// Start a transaction with the given i2c slave address. The direction of the
// transfer is set with I2C_READ and I2C_WRITE.
// returns: 0 => success
//          1 => error
uint8_t i2c_master_start(uint8_t address) {
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);

  i2c_delay();

  // check that we started successfully
  if ( (TW_STATUS != TW_START) && (TW_STATUS != TW_REP_START))
    return 1;

  TWDR = address;
  TWCR = (1<<TWINT) | (1<<TWEN);

  i2c_delay();

  if ( (TW_STATUS != TW_MT_SLA_ACK) && (TW_STATUS != TW_MR_SLA_ACK) )
    return 1; // slave did not acknowledge
  else
    return 0; // success
}


// Finish the i2c transaction.
void i2c_master_stop(void) {
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

  uint16_t lim = 0;
  while(!(TWCR & (1<<TWSTO)) && lim < I2C_LOOP_TIMEOUT)
    lim++;
}

// Write one byte to the i2c slave.
// returns 0 => slave ACK
//         1 => slave NACK
uint8_t i2c_master_write(uint8_t data) {
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);

  i2c_delay();

  // check if the slave acknowledged us
  return (TW_STATUS == TW_MT_DATA_ACK) ? 0 : 1;
}

// Read one byte from the i2c slave. If ack=1 the slave is acknowledged,
// if ack=0 the acknowledge bit is not set.
// returns: byte read from i2c device
uint8_t i2c_master_read(int ack) {
  TWCR = (1<<TWINT) | (1<<TWEN) | (ack<<TWEA);

  i2c_delay();
  return TWDR;
}

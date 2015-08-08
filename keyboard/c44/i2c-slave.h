#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include <stdint.h>

#define SLAVE_BUFFER_SIZE 0x10

extern volatile uint8_t slaveBuffer[SLAVE_BUFFER_SIZE];

void i2c_slave_init(uint8_t address);

#endif

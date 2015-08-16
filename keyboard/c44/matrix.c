/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lufa.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "i2c-master.h"
#include "serial.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

static uint8_t debouncing = DEBOUNCE;
static const int ROWS_PER_HAND = MATRIX_ROWS/2;
static const uint8_t SLAVE_I2C_ADDRESS = 0x32;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    debug_enable = true;
    debug_matrix = true;
    debug_mouse = true;
    // initialize row and col
    unselect_rows();
    init_cols();

#ifdef USE_I2C
    i2c_master_init();
#else
    serial_master_init();
#endif

    int x = USB_IsInitialized;
    if (x) {
        DDRD  |= 1<<5;
        PORTD &= ~(1<<5);
    } else {

    // use the pro micro TX led as an indicator
    // pull D5 low to turn on
    DDRD  |= 1<<5;
    PORTD |= (1<<5);
    }

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

}

uint8_t _matrix_scan(void)
{
    for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}


uint8_t matrix_scan(void)
{
    int ret = _matrix_scan();

#ifdef USE_I2C
    // Get rows from other half over i2c
    // Matrix stored at 0x00-0x03
    int err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_WRITE);
    if (err) goto i2c_error;
    err = i2c_master_write(0x00);
    if (err) goto i2c_error;
    err = i2c_master_start(SLAVE_I2C_ADDRESS + I2C_READ);
    if (err) goto i2c_error;

    if (!err) {
        // turn off the indicator led on no error
        PORTD |= (1<<5);

        matrix[4] = i2c_master_read(I2C_ACK);
        matrix[5] = i2c_master_read(I2C_ACK);
        matrix[6] = i2c_master_read(I2C_ACK);
        matrix[7] = i2c_master_read(I2C_NACK);
        i2c_master_stop();
    } else {
i2c_error: // the cable is disconnceted, or something else went wrong

        // reset the i2c state
        TWCR = 0;

        // turn on the indicator led
        PORTD &= ~(1<<5);

        // if we cannot communicate with the other half, then unset all of its keys
        matrix[4] = 0;
        matrix[5] = 0;
        matrix[6] = 0;
        matrix[7] = 0;
    }
#else
    if( serial_transaction() ) {
        // turn on the indicator led
        PORTD &= ~(1<<5);
        // if we cannot communicate with the other half, then unset all of its keys
        matrix[4] = 0;
        matrix[5] = 0;
        matrix[6] = 0;
        matrix[7] = 0;
    } else {
        // turn off the indicator led on no error
        PORTD |= (1<<5);
        // no error
        matrix[4] = serial_slave_buffer[0];
        matrix[5] = serial_slave_buffer[1];
        matrix[6] = serial_slave_buffer[2];
        matrix[7] = serial_slave_buffer[3];
    }
#endif

    return ret;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * col: 0
 * pin: B2

 * col: 0   1   2   3   4   5
 * pin: F6  F7  B1  B3  B2  B6
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRB  &= ~(1<<1 | 1<<3 | 1<<2 | 1<<6);
    PORTB |=  (1<<1 | 1<<3 | 1<<2 | 1<<6);
    DDRF  &= ~(1<<6 | 1<<7);
    PORTF |=  (1<<6 | 1<<7);
}

static matrix_row_t read_cols(void)
{
    return (PINF&(1<<6) ? 0 : (1<<0)) |
           (PINF&(1<<7) ? 0 : (1<<1)) |
           (PINB&(1<<1) ? 0 : (1<<2)) |
           (PINB&(1<<3) ? 0 : (1<<3)) |
           (PINB&(1<<2) ? 0 : (1<<4)) |
           (PINB&(1<<6) ? 0 : (1<<5));
}

/* Row pin configuration
 * row: 0
 * pin: B1
 *
 * row: 0  1  2  4
 * pin: D7 E6 B4 B6
 */
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~0b00110000;
    PORTB &= ~0b00110000;

    DDRD  &= ~0b10000000;
    PORTD &= ~0b10000000;

    DDRE  &= ~0b01000000;
    PORTE &= ~0b01000000;
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
            DDRD  |= (1<<7);
            PORTD &= ~(1<<7);
            break;
        case 1:
            DDRE  |= (1<<6);
            PORTE &= ~(1<<6);
            break;
        case 2:
            DDRB  |= (1<<4);
            PORTB &= ~(1<<4);
            break;
        case 3:
            DDRB  |= (1<<5);
            PORTB &= ~(1<<5);
            break;
    }
}

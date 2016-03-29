#include <avr/io.h>
#include "backlight.h"

/* Backlight pin configuration
 *
 * Case: PD4
 */

void backlight_set(uint8_t level)
{
    // Set as output.
    DDRD |= (1<<4);

    if (level & CASELIGHT)
    {
        PORTD |= (1<<4);
    }
}

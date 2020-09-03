#include <stdint.h>
#include <avr/io.h>
#include <math.h>

#include "defines.h"

/*!
 * @brief Setting pin to \c INPUT or \c OUTPUT
 * @param port Pointer of Port (B, C, D)
 * @param bit Bit number of \c port
 * @param mode \c INPUT or \c OUTPUT
 */
void set_pin_mode(volatile uint8_t *port, uint8_t bit, uint8_t mode) {
    uint8_t sreg = SREG;
    cli();

    if (mode == INPUT) {
        set_input(*(port - 1), bit);
        bit_clear(*port, bit);
    } else if (mode == INPUT_PULLUP) {
        set_input(*(port - 1), bit);
        bit_set(*port, bit);
    } else if (mode == OUTPUT)
        set_output(*(port - 1), bit);
    
    SREG = sreg;
}

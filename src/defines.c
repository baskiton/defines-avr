#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "defines.h"

struct freelist {
    size_t sz;
    struct freelist *nx;
};

extern struct freelist *__flp;
extern uint8_t *__brkval;

/*!
 * @brief Get approximate free memory space
 * @return Amount of free memory
 */
int32_t get_free_mem_size(void) {
    int32_t free_sz;
    struct freelist *next;
    uint16_t brkval;

    brkval = (uint16_t)__brkval;
    if (!brkval)
        brkval = (uint16_t)__malloc_heap_start;

    free_sz = (int32_t)SP - (int32_t)brkval - (int32_t)__malloc_margin;

    next = __flp;
    while (next) {
        free_sz += next->sz + 2;
        next = next->nx;
    }
    
    return free_sz;
}

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

/*!
 * @brief Reversing bits on an octet.
 * Method attributed to Rich Schroeppel in the Programming Hacks section
 * http://www.inwap.com/pdp10/hbaker/hakmem/hakmem.html
 * http://www.inwap.com/pdp10/hbaker/hakmem/hacks.html#item167
 * 
 * @example:
 *   1 byte
 * ____________
 *  0110  0001
 *      ||
 *      \/
 *  1000  0110
 */
uint8_t bits_swap(uint8_t data) {
    return (uint8_t)(((uint64_t)data * 0x0202020202U & 0x010884422010U) % 0x3ffU);
}

#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>

#include <stdint.h>

#define INPUT 0x00
#define OUTPUT 0x01
#define INPUT_PULLUP 0x02

#define nop() __asm__ __volatile__("nop")

#define bit_read(value, bit) (((value) >> (bit)) & 1U)
#define bit_set(value, bit) ((value) |= (1U << (bit)))
#define bit_clear(value, bit) ((value) &= ~(1U << (bit)))
#define bit_write(value, bit, bitvalue) ((bitvalue) ? bit_set((value), (bit)) : bit_clear((value), (bit)))

#define set_output(port, bit) ((port) |= (1U << (bit)))
#define set_input(port, bit) ((port) &= ~(1U << (bit)))

struct avr_pin_s {
    uint8_t pin_num;
    volatile uint8_t *port;
};

extern void set_pin_mode(volatile uint8_t *port, uint8_t bit, uint8_t mode);
extern int32_t get_free_mem_size(void);
extern uint8_t bits_swap(uint8_t data);

#endif  /* !DEFINES_H */

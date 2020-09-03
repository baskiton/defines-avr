#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>
#include <avr/builtins.h>

#define INPUT 0x00
#define OUTPUT 0x01
#define INPUT_PULLUP 0x02

#define cli() __builtin_avr_cli()
#define sti() __builtin_avr_sei()
#define nop() __asm__ __volatile__("nop")

#define bit_read(value, bit) (((value) >> (bit)) & 1U)
#define bit_set(value, bit) ((value) |= (1U << (bit)))
#define bit_clear(value, bit) ((value) &= ~(1U << (bit)))
#define bit_write(value, bit, bitvalue) ((bitvalue) ? bit_set((value), (bit)) : bit_clear((value), (bit)))

#define set_output(port, bit) ((port) |= (1U << (bit)))
#define set_input(port, bit) ((port) &= ~(1U << (bit)))

extern void set_pin_mode(volatile uint8_t *port, uint8_t bit, uint8_t mode);

#endif  /* !DEFINES_H */

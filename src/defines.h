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

/* Return a value with all bytes in the 16 bit argument swapped */
#define bswap_16(x) ((uint16_t)     \
    ((((x) >> 8) & 0xFFU) | (((x) & 0xFFU) << 8)))

/* Return a value with all bytes in the 32 bit argument swapped */
#define bswap_32(x) ((uint32_t)     \
    ((((x) & 0xFF000000U) >> 24) | (((x) & 0x00FF0000U) >> 8) | \
     (((x) & 0x0000FF00U) << 8) | (((x) & 0x000000FFU) << 24)))

/* Return a value with all bytes in the 64 bit argument swapped */
#define bswap_64(x) ((uint64_t)     \
    ((((x) & 0xff00000000000000ull) >> 56) |    \
     (((x) & 0x00ff000000000000ull) >> 40) |    \
     (((x) & 0x0000ff0000000000ull) >> 24) |    \
     (((x) & 0x000000ff00000000ull) >> 8)  |    \
     (((x) & 0x00000000ff000000ull) << 8)  |    \
     (((x) & 0x0000000000ff0000ull) << 24) |    \
     (((x) & 0x000000000000ff00ull) << 40) |    \
     (((x) & 0x00000000000000ffull) << 56)))

struct avr_pin_s {
    uint8_t pin_num;
    volatile uint8_t *port;
};

void set_pin_mode(volatile uint8_t *port, uint8_t bit, uint8_t mode);
int32_t get_free_mem_size(void);
uint8_t bits_swap(uint8_t data);

#endif  /* !DEFINES_H */

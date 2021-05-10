#include "nibble.h"

#include <stdint.h>

// Code provided by Professor Darrell Long (asgn5 lab document)

//
// Returns lower nibble of a byte
//
// val: byte to take lower nibble from
//
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

//
// Returns higher nibble of a byte (returned nibble placed in lower nibble position)
//
// val: byte to take higher nibble from
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

//
// Returns two nibbles packed back into a byte
//
// upper: upper nibble (in position of lower nibble)
// lower: lower nibble
//
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

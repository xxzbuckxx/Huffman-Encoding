#include "code.h"

#include <stdio.h>

//
// Initializes a Code
//
Code code_init(void) {
    Code c = { 0, { 0 } };
    return c;
}

//
// Size of a Code
//
// c: an address to a Code
//
uint32_t code_size(Code *c) {
    return c->top; // should be bits
}

//
// Returns if Code is empty or not
//
// c: an address to a Code
//
bool code_empty(Code *c) {
    return c->top == 0;
}

//
// Returns if Code is full or not
//
// c: an address to a code
//
bool code_full(Code *c) {
    return c->top >= MAX_CODE_SIZE - 1;
}

//
// Returns if bit was successfully pushed to Code
//
// c: an address to a code
// bit: a bit to push
//
bool code_push_bit(Code *c, uint8_t bit) {
    // each bit in uint8_t should be filled
    if (!code_full(c)) { // cannot push if Code full
        c->bits[c->top / 8] |= bit << c->top % 8;
        c->top++;
        return true;
    }
    return false;
}

//
// Returns true if bit was successfully popped from Code
//
// c: an address to a code
// bit: an address to store the popped bit
//
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (!code_empty(c)) { // cannot pop if Code empty
        c->top--;
        *bit = (c->bits[c->top / 8] & (1 << (c->top % 8))) >> (c->top % 8);
        return true;
    }
    return false;
}

//
// Print a Code for debugging
//
// c: an adress to a code
//
void code_print(Code *c) {
    printf("[ ");
    for (uint32_t i = 0; i < c->top; i += 1) { // iterate through item indices
        printf("%d ", (c->bits[i / 8] & (1 << (i % 8))) >> (i % 8));
    }
    printf("]\n");
    return;
}

#include "code.h"

#include <stdint.h>
#include <stdio.h>

Code code_init(void) {
    uint8_t bits[MAX_CODE_SIZE] = { 0 };
    Code c = { 0, { *bits } }; // seems hacky should fix
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    return c->top == 0;
}

bool code_full(Code *c) {
    return c->top >= MAX_CODE_SIZE - 1;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (!code_full(c)) {
        c->bits[c->top] = bit;
        c->top++;
        return true;
    }
    return false;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (!code_empty(c)) {
        c->top--;
        *bit = c->bits[c->top];
        return true;
    }
    return false;
}

void code_print(Code *c) {
    printf("[");
    for (uint32_t i = 0; i < c->top; i += 1) { // iterate through item indices
        printf("%d ", c->bits[i]);
    }
    printf("]\n");
    return;
}

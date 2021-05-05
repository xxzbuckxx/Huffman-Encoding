#include "bv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct BitVector {
    uint32_t length;
    uint8_t *vector;
} BitVector;

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) {
        v->length = length;
        v->vector = (uint8_t *) malloc(length);
        if (!v->vector) {
            free(v);
            v = NULL;
            return NULL;
        } else {
            for (uint32_t i = 0; i < length; i++) {
                v->vector[i] = 0;
            }
        }
    }
    return v;
}

void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *v) {
    return v ? v->length : 0;
}

void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] = v->vector[i / 8] | ((uint8_t) 0x1 << (i % 8));
    return;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] = v->vector[i / 8] & ~((uint8_t) 0x1 << (i % 8));
    return;
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    return;
    v->vector[i] = bit;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] & ((uint8_t) 0x1 << (i % 8))) >> (i % 8);
}

void bv_print(BitVector *v) {
    for (int32_t i = v->length; i > 0; i--) {
        printf("%c", '0' + (unsigned char) bv_get_bit(v, i));
    }
    printf("\n");
    return;
}

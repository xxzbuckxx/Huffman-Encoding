#include "bv.h"

#include <inttypes.h> // int types
#include <stdio.h> // print debug
#include <stdlib.h> // malloc

// 
// A structure for defining a BitVector
//
typedef struct BitVector {
    uint32_t length; // number of elements
    uint8_t *vector; // array of elements
} BitVector;

// 
// Creates a BitVector
//
// length: length of BitVector
//
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) { // if memory allocated successfully
        v->length = length;
        v->vector = (uint8_t *) malloc(length);
        if (!v->vector) { // if memory not allocated successfully for array
            free(v);
            v = NULL;
            return NULL;
        } else { // initialize with 0s
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

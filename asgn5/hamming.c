#include "hamming.h"

#include "bm.h"
#include "nibble.h"
#include "translator.h"

#include <stdio.h>

uint8_t encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *V = bm_from_data(msg, 4);
    BitMatrix *P = bm_multiply(V, G);
    uint8_t res = bm_to_data(P);
    // add memoization lookup table
    bm_delete(&V);
    bm_delete(&P);
    return res;
}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *V = bm_from_data(code, 8);
    BitMatrix *E = bm_multiply(V, Ht);

    uint8_t error = bm_to_data(E);
    uint8_t bit_correct = 0;

    bm_delete(&V);
    bm_delete(&E);
    // add memoization lookup table

    switch (error) {
    case 0:
        *msg = lower_nibble(code);
        return HAM_OK;
        break;
    case 1: bit_correct = 4; break;
    case 2: bit_correct = 5; break;
    case 4: bit_correct = 6; break;
    case 7: bit_correct = 3; break;
    case 8: bit_correct = 7; break;
    case 11: bit_correct = 2; break;
    case 13: bit_correct = 1; break;
    case 14: bit_correct = 0; break;
    default: return HAM_ERR; break;
    }

    *msg = lower_nibble(code ^ (1 << bit_correct));
    return HAM_CORRECT;
}

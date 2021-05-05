#include "hamming.h"

#include "bm.h"
#include "nibble.h"
#include "translator.h"

#include <stdio.h>

uint8_t encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *V = bm_from_data(msg, 4);
    BitMatrix *P = bm_multiply(V, G);
    uint8_t res = bm_to_data(P);
    bm_delete(&V);
    bm_delete(&P);
    return res;
}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {

    // compile placeholder
    return HAM_ERR;
    *msg = bm_get_bit(Ht, code, 0);
}

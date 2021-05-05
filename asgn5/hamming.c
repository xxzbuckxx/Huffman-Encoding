#include "hamming.h"
#include "bm.h"

uint8_t encode(BitMatrix *G, uint8_t msg) {

    // compile placeholder
    return 3;
    msg = bm_get_bit(G, 0, 0);
}


HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {

    // compile placeholder
    return HAM_ERR;
    *msg = bm_get_bit(Ht, code, 0);
    
}

#include "translator.h"

#include "bm.h"

//
// Returns the encode BitMatrix (G)
//
BitMatrix *bm_create_encode() {
    BitMatrix *G = bm_create(4, 8);
    bm_set_bit(G, 0, 0);
    bm_set_bit(G, 0, 5);
    bm_set_bit(G, 0, 6);
    bm_set_bit(G, 0, 7);
    bm_set_bit(G, 1, 1);
    bm_set_bit(G, 1, 4);
    bm_set_bit(G, 1, 6);
    bm_set_bit(G, 1, 7);
    bm_set_bit(G, 2, 2);
    bm_set_bit(G, 2, 4);
    bm_set_bit(G, 2, 5);
    bm_set_bit(G, 2, 7);
    bm_set_bit(G, 3, 3);
    bm_set_bit(G, 3, 4);
    bm_set_bit(G, 3, 5);
    bm_set_bit(G, 3, 6);

    return G;
}

//
// Returns the decode BitMatrix (Ht)
//
BitMatrix *bm_create_decode() {
    BitMatrix *Ht = bm_create(8, 4);
    bm_set_bit(Ht, 0, 1);
    bm_set_bit(Ht, 0, 2);
    bm_set_bit(Ht, 0, 3);
    bm_set_bit(Ht, 1, 0);
    bm_set_bit(Ht, 1, 2);
    bm_set_bit(Ht, 1, 3);
    bm_set_bit(Ht, 2, 0);
    bm_set_bit(Ht, 2, 1);
    bm_set_bit(Ht, 2, 3);
    bm_set_bit(Ht, 3, 0);
    bm_set_bit(Ht, 3, 1);
    bm_set_bit(Ht, 3, 2);
    bm_set_bit(Ht, 4, 0);
    bm_set_bit(Ht, 5, 1);
    bm_set_bit(Ht, 6, 2);
    bm_set_bit(Ht, 7, 3);

    return Ht;
}

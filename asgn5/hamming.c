#include "hamming.h"

#include "bm.h"
#include "nibble.h"
#include "translator.h"

// 
// Encodes a nibble with a hamming(8,4) code
//
// G: Encode BitMatrix
// msg: input nibble to encode
//
uint8_t encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *V = bm_from_data(msg, 4); // create input vector from nibble (1d BitMatrix)
    BitMatrix *P = bm_multiply(V, G); // create encoded (output) vector (1d BitMatrix)
    uint8_t res = bm_to_data(P); // convert output to byte
    // add memorization lookup table ///
    bm_delete(&V); // free input vector BitMatrix 
    bm_delete(&P); // free encoded (output) vector
    return res;
}

// 
// Decodes am encoded hamming(8,4) code into a nibble and returns status of decoding
//
// Ht: Decode BitMatrix
// code: encoded byte to decode
// msg: address to store decoded message
//
HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *V = bm_from_data(code, 8); // create input vector from encoded byte (1d BitMatrix)
    BitMatrix *E = bm_multiply(V, Ht); // create error vector (1d BitMatrix)

    uint8_t error = bm_to_data(E); // convert error output to byte
    uint8_t bit_correct = 0; // bit to correct

    bm_delete(&V);
    bm_delete(&E);

    // add memoization lookup table ///

    switch (error) {
    case 0: // decoded without error
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
    default: return HAM_ERR; break; // 2 or more errors (cannot be fixed)
    }

    *msg = lower_nibble(code ^ (1 << bit_correct)); // correct bit
    return HAM_CORRECT;
}

#include "bm.h"

#include "bv.h"

#include <assert.h> // assert()
#include <inttypes.h> // int types
#include <stdio.h> // debugging print
#include <stdlib.h> // malloc

//
// Structre for defining a BitMatrix
//
typedef struct BitMatrix {
    uint32_t rows; // number of rows
    uint32_t cols; // number of columns
    BitVector *vector; // 2d matrix stored as BitVector
} BitMatrix;

//
// Creates a BitMatrix
//
// rows: number of rows
// cols: number of columns
//
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (m) {
        m->rows = rows;
        m->cols = cols;
        if ((m->vector = bv_create(rows * cols)) == NULL) {
            free(m);
            return NULL;
        }
    }
    return m;
}

//
// Deletes a BitMatrix
//
// m: address to an address of a BitMatrix
//
void bm_delete(BitMatrix **m) {
    bv_delete(&((*m)->vector));
    free(*m);
    *m = NULL;
}

//
// Gives the number of rows
//
// m: an address of a BitMatrix
//
uint32_t bm_rows(BitMatrix *m) {
    return m ? m->rows : 0;
}

//
// Gives the number of columns
//
// m: an address of a BitMatrix
//
uint32_t bm_cols(BitMatrix *m) {
    return m ? m->cols : 0;
}

//
// Sets a bit to 1
//
// r: row index to set
// c: column index to set
// m: an address of a BitMatrix
//
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, (r * m->cols) + c);
}

//
// Sets a bit to 0
//
// r: row index to set
// c: column index to set
// m: an address of a BitMatrix
//
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, (r * m->cols) + c);
}

//
// Returns value of a specified bit
//
// r: row index to check
// c: column index to check
// m: an address of a BitMatrix
//
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, (r * m->cols) + c);
}

//
// Creates a single rowed BitMatrix given a byte or nibble of data
//
// byte: data to convert to a 1d BitMatrix
// length: number of elements in BitMatrix
//
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    if (length > 8) {
        return NULL;
    }
    BitMatrix *m = bm_create(1, length);
    for (uint8_t i = 0; i < length; i++) {
        if (1 & byte) {
            bm_set_bit(m, 0, i);
        }
        byte = byte >> 1;
    }
    return m;
}

//
// Converts a single rowed BitMatrix to a byte or nibble of data
//
// m: an address of a BitMatrix
//
uint8_t bm_to_data(BitMatrix *m) {
    uint32_t byte = 0x0;
    for (uint8_t i = 0; i < m->cols; i++) {
        byte = byte | (bv_get_bit(m->vector, i) << i);
    }
    return byte;
}

//
// Multiply two matrices
//
// A: address of first matrix to multiply
// B: address of second matrix to multiply
//
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    uint32_t height = bm_rows(A);
    uint32_t length = bm_cols(B);
    BitMatrix *P = bm_create(height, length);

    assert(bm_cols(A) == bm_rows(B));
    for (uint32_t r = 0; r < height; r++) {
        for (uint32_t c = 0; c < length; c++) {
            uint32_t dot_product = 0;
            for (uint32_t i = 0; i < bm_cols(A); i++) {
                bv_xor_bit(A->vector, (r * A->cols) + i, dot_product);
                bv_xor_bit(B->vector, (i * B->cols) + c, dot_product);

                /* dot_product += bm_get_bit(A, r, i) * bm_get_bit(B, i, c); // use xor */
            }
            if (dot_product % 2) {
                bm_set_bit(P, r, c);
            }
        }
    }
    return P;
}

//
// Prints a BitMatrix for debugging
//
// m: address of a BitMatrix
//
void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < bv_length(m->vector); i++) {
        printf("%c", '0' + (unsigned char) bv_get_bit(m->vector, i));
        if (i % m->cols == m->cols - 1) {
            printf("\n");
        }
    }
    return;
}

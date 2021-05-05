#include "bm.h"

#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
} BitMatrix;

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

void bm_delete(BitMatrix **m) {
    bv_delete(&((*m)->vector));
    free(*m);
    /* bv_delete(&(*m)->vector); */
    *m = NULL;
}

uint32_t bm_rows(BitMatrix *m) {
    return m ? m->rows : 0;
}

uint32_t bm_cols(BitMatrix *m) {
    return m ? m->cols : 0;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, (r * m->cols) + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, (r * m->cols) + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, (r * m->cols) + c);
}

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

uint8_t bm_to_data(BitMatrix *m) {
    uint32_t byte = 0x0;
    for (uint8_t i = 0; i < m->cols; i++) {
        byte = byte | (bv_get_bit(m->vector, i) << i);
    }
    return byte;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    uint32_t height = bm_rows(A);
    uint32_t length = bm_cols(B);
    BitMatrix *P = bm_create(height, length);

    assert(bm_cols(A) == bm_rows(B));
    for (uint32_t r = 0; r < height; r++) {
        for (uint32_t c = 0; c < length; c++) {
            uint32_t dot_product = 0;
            for (uint32_t i = 0; i < bm_cols(A); i++) {
                dot_product += bm_get_bit(A, r, i) * bm_get_bit(B, i, c); // use xor
            }
            if (dot_product % 2) {
                bm_set_bit(P, r, c);
            }
        }
    }
    return P;
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < bv_length(m->vector); i++) {
        printf("%c", '0' + (unsigned char) bv_get_bit(m->vector, i));
        if (i % m->cols == m->cols - 1) {
            printf("\n");
        }
    }
    return;
}

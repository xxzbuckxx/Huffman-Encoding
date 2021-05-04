#include "bv.h"
#include "bm.h"
#include <inttypes.h>
#include <stdlib.h> // malloc
#include <stdio.h>

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
    free(*m);
    bv_delete(&(*m)->vector);
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
    bv_get_bit(m->vector, (r * m->cols) + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    if (length > 8) {
        return NULL;
    }
    BitMatrix *m = bm_create(1, length);
    for (uint8_t i = 0; i < length; i++) {
        bm_set_bit(m, 0, 1  | byte);
        byte = byte >> 1;
    }
    return m;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint32_t byte = 0x1;
    for (uint8_t i = 0; i < m->cols) {
    }
    return;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {

}

void bm_print(BitMatrix *m) {
    for (int32_t i = 0; i < ((m->rows * m->cols) + m->cols); i++) {
        printf("%c", '0' + (unsigned char) bv_get_bit(m->vectors, i));
    }
}

int main(){
    BitMatrix *m = bm_create(5, 5);
    bm_print(m);
    return 0;
}

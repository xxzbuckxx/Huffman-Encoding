#include "io.h"

#include "defines.h"

#include <fcntl.h> // open and close
#include <stdio.h>
#include <unistd.h> // read and write

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;
static uint8_t buf_code[BLOCK];
static uint64_t buf_code_idx;
static uint8_t buf_code_idx_bit;

//
// Read bytes from a file
//
// infile: file to read from
// buf: a pointer to a buffer
// nbytes: number of bytes to read
//
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int b_read = 0; // bytes read so far
    int read_last = 0; // bytes read on last

    while ((b_read += read(infile, buf, nbytes - b_read)) < nbytes) {
        if (read_last == b_read) {
            break;
        }
        read_last = b_read;
    }

    return b_read;
}

//
// Write bytes to a file
//
// infile: file to write to
// buf: a pointer to a buffer
// nbytes: number of bytes to write
//
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    // imp correct?
    int b_written = 0;

    if (outfile == 0) {
        return 0;
    }

    while (b_written < nbytes) {
        b_written += write(outfile, buf, nbytes - b_written);
        if (b_written == 0) {
            break;
        }
    }

    return bytes_written;
}

bool read_bit(int infile, uint8_t *bit) {
    static uint32_t buffer = BLOCK;
    uint8_t *buff = (uint8_t *) &buffer;
    static uint32_t bi = 0;

    if (bi == 0 && (read_bytes(infile, buff, 1)) == 0) {
        return false;
        buff = (uint8_t *) &buffer;
    }

    *bit = 1 & (buffer >> bi);

    bi++;

    if (bi > 7) {
        bi = 0;
    }

    return true;
}

void write_code(int outfile, Code *c) {
    if (code_size(c) + buf_code_idx >= BLOCK) {
        write_bytes(outfile, buf_code, buf_code_idx);
    }

    for (uint64_t i = 0; i < code_size(c); i++) {
        buf_code[buf_code_idx] |=  ((c->bits[i/8] >> i % 8) & 1)  << buf_code_idx_bit++;
        if (buf_code_idx_bit >= 8) {
            buf_code_idx++;
            buf_code_idx_bit = 0;
        }
    }

    return;
}

void flush_codes(int outfile) {
    write_bytes(outfile, buf_code, buf_code_idx);
    return;
}

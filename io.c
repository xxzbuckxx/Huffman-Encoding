#include "io.h"

#include "defines.h"
#include "io_extnd.h"

#include <fcntl.h> // open and close
#include <stdio.h> // Printing
#include <unistd.h> // read and write

// global
uint64_t bytes_read = 0; // total bytes read
uint64_t bytes_written = 0; // total bytes written

// private
uint8_t buf_code[BLOCK];
uint64_t buf_code_idx = 0;
uint8_t buf_code_idx_bit = 0;

//
// Read bytes from a file
//
// infile: file to read from
// buf: a pointer to a buffer
// nbytes: number of bytes to read
//
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int b_read = 0; // bytes read so far
    int last_read = 0; // bytes read on last

    while ((b_read += read(infile, buf, nbytes - b_read)) < nbytes) {
        if (last_read == b_read) { // if no bytes read
            break;
        }
        last_read = b_read;
    }

    bytes_read += (uint64_t) b_read;
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
    int b_written = 0; // bytes written so far
    int last_written = 0; // bytes written on last

    while ((b_written += write(outfile, buf, nbytes - b_written)) < nbytes) {
        if (last_written == b_written) { // if no bytes written
            break;
        }
        last_written = b_written;
    }

    bytes_written += (uint64_t) b_written;
    return b_written;
}

//
// Write a Header to a file
//
// infile: file to write to
// h: a pointer to the Header
//
int read_header(int infile, Header *h) {
    uint64_t b_read = 0; // bytes read so far
    uint64_t last_read = 0; // bytes read on last

    while ((b_read += read(infile, h, sizeof(Header) - b_read)) < sizeof(Header)) {
        if (last_read == b_read) { // if no bytes read
            break;
        }
        last_read = b_read;
    }

    bytes_read += b_read;
    return b_read;
}

//
// Reads a Header to a file
//
// infile: file to write to
// h: a pointer to the Header
//
int write_header(int outfile, Header *h) {
    uint64_t b_written = 0; // bytes written so far
    uint64_t last_written = 0; // bytes written on last

    while ((b_written += write(outfile, h, sizeof(Header) - b_written)) < sizeof(Header)) {
        if (last_written == b_written) { // if no bytes written
            break;
        }
        last_written = b_written;
    }

    bytes_written += b_written;
    return bytes_written;
}

//
// Read bit by bit from a file
//
// infile: file to read from
// bit: buffer to store bit
//
bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buf[BLOCK];
    static uint64_t b_read = 0;
    static uint64_t buf_idx = 1;
    static uint8_t buf_bit = 0;

    if (buf_idx >= b_read) {
        if ((b_read = read_bytes(infile, buf, BLOCK)) == 0) {
            return false;
        }
        buf_bit = 0;
        buf_idx = 0;
    }

    *bit = 1 & (buf[buf_idx] >> buf_bit++);

    if (buf_bit > 7) {
        buf_bit = 0;
        buf_idx++;
    }

    return true;
}

//
// Write a Code to a file
//
// outfile: file to write top
// c: an address to a code to write
//
void write_code(int outfile, Code *c) {
    for (uint64_t i = 0; i < code_size(c); i++) {
        if (buf_code_idx_bit == 0) {
            buf_code[buf_code_idx] = 0;
        }
        buf_code[buf_code_idx] |= ((c->bits[i / 8] >> i % 8) & 1) << buf_code_idx_bit++;
        if (buf_code_idx_bit >= 8) {
            buf_code_idx++;
            buf_code_idx_bit = 0;
        }
        if (buf_code_idx > BLOCK) {
            write_bytes(outfile, buf_code, buf_code_idx + (buf_code_idx_bit == 0 ? 0 : 1));
            buf_code_idx_bit = 0;
            buf_code_idx = 0;
        }
    }
    return;
}

//
// Write any codes still in buffer
//
// outfile: file to write to
//
void flush_codes(int outfile) {
    write_bytes(outfile, buf_code, buf_code_idx + (buf_code_idx_bit == 0 ? 0 : 1));
    return;
}

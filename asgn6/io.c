#include "io.h"

#include "defines.h"

#include <fcntl.h> // open and close
#include <stdio.h>
#include <unistd.h> // read and write

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint8_t bytes_read = 0;
    uint8_t read_last = 0;

    if (infile == 0) {
        return 0;
    }

    while (bytes_read < nbytes) {
        bytes_read += read(infile, buf, nbytes - bytes_read);
        if (read_last == bytes_read) {
            break;
        }
        read_last = bytes_read;
    }

    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    uint8_t bytes_written = 0;

    if (outfile == 0) {
        return 0;
    }

    while (bytes_written < nbytes) {
        bytes_written += write(outfile, buf, nbytes - bytes_written);
        if (bytes_written == 0) {
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

void write_code(int outfile, Code *c);

void flush_codes(int outfile);

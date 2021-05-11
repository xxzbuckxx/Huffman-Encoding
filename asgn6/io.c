#include "io.h"

#include <fcntl.h> // open and close
#include <stdio.h>
#include <unistd.h> // read and write

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint8_t bytes_read = 0;
    uint8_t read_last = 0;

    if (infile == 0) {
        return 0;
    }

    while (bytes_read < nbytes - 1) {
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

bool read_bit(int infile, uint8_t *bit);

void write_code(int outfile, Code *c);

void flush_codes(int outfile);

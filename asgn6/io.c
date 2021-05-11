#include "code.h"

#include <unistd.h> // read and write
#include <fcntl.h> // open and close

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    uint8_t bytes_read = 0;

    while (bytes_read < nbytes) {
        bytes_read += read(infile, buf, nbytes - bytes_read);
    }

    return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes);

bool read_bit(int infile, uint8_t *bit);

void write_code(int outfile, Code *c);

void flush_codes(int outfile);


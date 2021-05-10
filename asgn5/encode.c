#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "nibble.h"
#include "translator.h"

#include <stdbool.h>
#include <stdio.h> // Printing
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h> // For getopt()

#define OPTIONS "hi:o:"

#define FILE_NOT_FOUND "File not found ;(\n"

#define HELP                                                                                       \
    "SYNOPSIS\n  A hamming(8,4) code encoder.\n\nUSAGE\n  pipe or specify a file to "              \
    "encode.\n\nOPTIONS\n  -h               Program usage and help.\n  -i               Input "    \
    "file: file that to be encoded.\n  -o               Output file: file that stores the "        \
    "encoding.\n"
int main(int argc, char **argv) {

    // File descriptors
    FILE *file_in = stdin;
    FILE *file_out = stdout;
    struct stat statbuf; // file permissions

    // Parse

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(HELP);
            return 0;
            break;
        case 'i':
            if ((file_in = fopen(optarg, "rb")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        case 'o':
            if ((file_out = fopen(optarg, "wb")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        default: return 1; // error
        }
    }

    // Transfer File permissions
    if (file_in != stdin && file_out != stdout) {
        fstat(fileno(file_in), &statbuf);
        fchmod(fileno(file_out), statbuf.st_mode);
    }

    // Initialize
    BitMatrix *G = bm_create_encode();
    int buffer = 0x00;

    while ((buffer = fgetc(file_in)) != EOF) {
        uint8_t lower = lower_nibble(buffer);
        uint8_t encoded_lower = encode(G, lower);
        fputc(encoded_lower, file_out);

        uint8_t upper = upper_nibble((uint8_t) buffer);
        uint8_t encoded_upper = encode(G, upper);
        fputc(encoded_upper, file_out);
        // now inherit file permission
    }

    bm_delete(&G);
    fclose(file_in);
    fclose(file_out);
    return 0;
}

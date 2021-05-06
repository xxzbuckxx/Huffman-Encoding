#include "bm.h"
#include <sys/stat.h>
#include "bv.h"
#include "hamming.h"
#include "nibble.h"
#include "translator.h"

#include <stdbool.h>
#include <stdio.h> // Printing
#include <stdlib.h>
#include <unistd.h> // For getopt()

#define OPTIONS "hvi:o:"

#define FILE_NOT_FOUND "File not found ;(\n"

#define HELP "how to use here"

int main(int argc, char **argv) {

    /* if (argc < 2) { */
    /*     printf(HELP); */
    /*     return 1; // error */
    /* } */

    FILE *file_in = stdin;
    FILE *file_out = stdout;

    bool verbose = false;

    // Parse
    struct stat statbuf;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(HELP); break;
        case 'v': verbose = true; break;
        case 'i':
            // UNIX PERMISSIONS
            if ((file_in = fopen(optarg, "r")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            fstat(fileno(file_in), &statbuf);
            break;
        case 'o':
            if ((file_out = fopen(optarg, "w")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            fchmod(fileno(file_out), statbuf.st_mode);
            break;
        default: return 1; // error
        }
    }

    // Initalize
    BitMatrix *G = bm_create_encode();
    int buffer = 0x00;

    while ((buffer = fgetc(file_in)) != EOF) {
        uint8_t lower = lower_nibble(buffer);
        uint8_t encoded_lower = encode(G, lower);
        fputc(encoded_lower, file_out);

        uint8_t upper = upper_nibble((uint8_t) buffer);
        uint8_t encoded_upper = encode(G, upper);
        fputc(encoded_upper, file_out);
        // now inherit file permision
    }

    bm_delete(&G);
    fclose(file_in);
    fclose(file_out);
    return 0;
}

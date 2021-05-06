#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "nibble.h"
#include "translator.h"

#include <stdbool.h>
#include <sys/stat.h>
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
            if ((file_in = fopen(optarg, "rb")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            fstat(fileno(file_in), &statbuf);
            break;
        case 'o':
            if ((file_out = fopen(optarg, "wb")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            fchmod(fileno(file_out), statbuf.st_mode);

            break;
        default: return 1; // error
        }
    }

    // Initalize
    BitMatrix *Ht = bm_create_decode();
    int buffer1 = 0x00;

    uint64_t processed = 0;
    uint64_t corrected = 0;
    uint64_t error_bytes = 0;
    uint8_t last = 0;

    while ((buffer1 = fgetc(file_in)) != EOF) {
        processed++;

        uint8_t msg = 0;
        HAM_STATUS error = decode(Ht, buffer1, &msg);
        switch (error) {
        case HAM_OK: break;
        case HAM_ERR: error_bytes++; break;
        case HAM_CORRECT: corrected++; break;
        default: break;
        }

        // now inherit file permision

        if (processed % 2) {
            last = msg;
        } else {
            uint8_t decoded = pack_byte(msg, last);
            fputc(decoded, file_out);
        }
    }

    double error_rate = (double) error_bytes / (double) processed;

    if (verbose) {
        fprintf(stderr,
            "\nProcessed Bytes: %lu\nUncorrected errors: %lu\nCorrected Errors: %lu\nError: %f\n",
            processed, error_bytes, corrected, error_rate);
    }

    bm_delete(&Ht);
    fclose(file_in);
    fclose(file_out);
    return 0;
}

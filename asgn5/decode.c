#include "bm.h"
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
            break;
        case 'o':
            if ((file_out = fopen(optarg, "w")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        default: return 1; // error
        }
    }

    // Initalize
    BitMatrix *Ht = bm_create_decode();
    int buffer1 = 0x00;
    int buffer2 = 0x00;

    uint64_t processed = 0;
    uint64_t corrected = 0;
    uint64_t error = 0;

    while ((buffer1 = fgetc(file_in)) != EOF && (buffer2 = fgetc(file_in)) != EOF) {
        processed += 2;

        uint8_t msg_lower = 0;
        HAM_STATUS error_lower = decode(Ht, buffer1, &msg_lower);
        switch (error_lower) {
        case HAM_OK: break;
        case HAM_ERR: error++; break;
        case HAM_CORRECT: corrected++; break;
        default: break;
        }
        printf("lower is %d or %c\n", msg_lower, msg_lower);

        uint8_t msg_upper = 0;
        HAM_STATUS error_upper = decode(Ht, buffer2, &msg_upper);
        switch (error_upper) {
        case HAM_OK: break;
        case HAM_ERR: error++; break;
        case HAM_CORRECT: corrected++; break;
        default: break;
        }
        printf("upper is %d or %c\n", msg_upper, msg_upper);

        uint8_t decoded = pack_byte(msg_upper, msg_lower);
        printf("\n\n%d or %c\n", decoded, decoded);
        fputc(decoded, file_out);
        // now inherit file permision
    }

    printf("\nProcessed: %lu\nCorrected: %lu\n Error: %lu\n", processed, corrected, error);

    /* BitMatrix *Ht = bm_create_decode(); */

    // while data still in file:
    // Read a byte using fgetc()
    // Generate Hamming(8,4) for both upper and lower nubble using ham_encode()
    //      write to file with fputc()
    //      Lower first then upper
    //

    bm_delete(&Ht);
    fclose(file_in);
    fclose(file_out);
    return 0;
}

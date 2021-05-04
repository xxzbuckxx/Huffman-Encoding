#include <stdio.h> // Printing
#include <stdlib.h>
#include <unistd.h> // For getopt()
#include <stdbool.h>

#define OPTIONS "hvi:o:"

#define FILE_NOT_FOUND "File not found ;(\n"

#define HELP "how to use here"

int main(int argc, char **argv) {

    if (argc < 2) {
        printf(HELP);
        return 1; // error
    }

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

    // Graph *G = bm_create();
    
    // while data still in file:
    // Read a byte using fgetc()
    // Generate Hamming(8,4) for both upper and lower nubble using ham_encode()
    //      write to file with fputc()
    //      Lower first then upper
    //

    fclose(file_in);
    fclose(file_out);
}

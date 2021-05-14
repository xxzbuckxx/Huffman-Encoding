#include "code.h"
#include "huffman.h"
#include "io.h"
#include "stack.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h> // Printing
/* #include <sys/stat.h> */
#include <unistd.h> // For getopt()

#define OPTIONS "hi:o:v:"

#define FILE_NOT_FOUND "File not found ;(\n"

#define HELP                                                                                       \
    "SYNOPSIS\n  A hamming(8,4) code encoder.\n\nUSAGE\n  pipe or specify a file to "              \
    "encode.\n\nOPTIONS\n  -h               Program usage and help.\n  -i               Input "    \
    "file: file that to be encoded.\n  -o               Output file: file that stores the "        \
    "encoding.\n"
int main(int argc, char **argv) {

    /* if (argc < 2) { */
    /*     printf(HELP); */
    /*     return 0; */
    /* } */

    // File descriptors
    int file_in = 0;
    int file_out = 0;

    bool verbose = false;

    // Parse
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(HELP);
            return 0;
            break;
        case 'v': verbose = true; break;
        case 'i':
            if ((file_in = open(optarg, O_RDONLY)) == -1) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        case 'o':
            if ((file_out = open(optarg, O_WRONLY | O_TRUNC)) == -1) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        default: return 1; // error
        }
    }

    // Transfer File permissions
    /* if (file_in != stdin && file_out != stdout) { */
    /*     fstat(fileno(file_in), &statbuf); */
    /*     fchmod(fileno(file_out), statbuf.st_mode); */
    /* } */

    // Parse
    uint64_t hist[ALPHABET] = {0};
    uint8_t buf = 0; // character
    while (true) {
        if (read_bytes(file_in, &buf, 1) == 0) { // if bu
            break;
        }
        hist[buf]++; // increment frequency of character in histogram
    }
    
    Node *root = build_tree(hist);
    node_print(root);

    close(file_in);
    close(file_out);

    return 0;
}

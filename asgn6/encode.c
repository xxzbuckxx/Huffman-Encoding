#include "code.h" // Code ADT
#include "defines.h" // BLOCK, MAGIC, ALPHABET, etc.
#include "header.h" // file header
#include "huffman.h" // Huffman tree construction and traversal
#include "io.h" // writing and reading files
#include "tree_info.h" // tree buffer and size

#include <fcntl.h> // open and close
#include <stdbool.h> // boolean
#include <stdio.h> // Printing
#include <stdlib.h>
#include <sys/stat.h> // file properties
#include <unistd.h> // For getopt()

#define OPTIONS "hi:o:v"

#define FILE_NOT_FOUND "File not found ;(\n"

#define HELP                                                                                       \
    "SYNOPSIS\n  A hamming(8,4) code encoder.\n\nUSAGE\n  pipe or specify a file to "              \
    "encode.\n\nOPTIONS\n  -h               Program usage and help.\n  -i               Input "    \
    "file: file that to be encoded.\n  -o               Output file: file that stores the "        \
    "encoding.\n"

int tree_out;

int main(int argc, char **argv) {

    // File descriptors
    int file_in = STDIN_FILENO;
    int file_out = tree_out = STDOUT_FILENO;
    struct stat statbuf; // file permissions

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
            if ((file_out = tree_out = open(optarg, O_WRONLY | O_TRUNC | O_CREAT)) == -1) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        default: return 1; // error
        }
    }

    fstat(file_in, &statbuf);
    // Transfer File permissions
    if (file_in != STDIN_FILENO && file_out != STDOUT_FILENO) {
        fchmod(file_out, statbuf.st_mode);
    }

    // Parse

    // Create Histogram
    uint64_t hist[ALPHABET] = { 0 };
    hist[0] = 1;
    hist[255] = 1;
    uint8_t buf[BLOCK] = { 0 };
    int length = 0;
    while ((length = read_bytes(file_in, buf, BLOCK)) > 0) {
        for (int i = 0; i < length; i++) {
            hist[buf[i]]++; // increment frequency of character in histogram
        }
    }

    printf("HISTOGRAM CREATED\n");

    // Create tree

    Node *root = build_tree(hist);

    // Construct header
    Header h = { MAGIC, statbuf.st_mode, tree_size, statbuf.st_size };
    uint8_t buf_header[16];
    // Magic
    buf_header[0] = h.magic & 0xFF;
    buf_header[1] = (h.magic >> 8) & 0xFF;
    buf_header[2] = (h.magic >> 16) & 0xFF;
    buf_header[3] = (h.magic >> 24) & 0xFF;
    // permissions
    buf_header[4] = (h.permissions >> 0) & 0xFF;
    buf_header[5] = (h.permissions >> 8) & 0xFF;
    // tree_size
    buf_header[6] = (h.tree_size >> 0) & 0xFF;
    buf_header[7] = (h.tree_size >> 8) & 0xFF;
    // file_size
    buf_header[8] = h.file_size & 0xFF;
    buf_header[9] = (h.file_size >> 8) & 0xFF;
    buf_header[10] = (h.file_size >> 16) & 0xFF;
    buf_header[11] = (h.file_size >> 24) & 0xFF;
    buf_header[12] = (h.file_size >> 32) & 0xFF;
    buf_header[13] = (h.file_size >> 40) & 0xFF;
    buf_header[14] = (h.file_size >> 48) & 0xFF;
    buf_header[15] = (h.file_size >> 56) & 0xFF;

    write_bytes(file_out, buf_header, 16);

    // Create codes

    // Populate a table with empty codes
    Code table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) { // create empty table
        table[i] = code_init();
    }

    build_codes(root, table); // create codes

    // Write tree
    if (buf_tree_idx != 0) {
        write_bytes(file_out, buf_tree, buf_tree_idx);
    }

    // Encode
    lseek(file_in, 0, SEEK_SET);

    uint8_t buf_encode[BLOCK] = { 0 };
    length = 0;
    while ((length = read_bytes(file_in, buf_encode, BLOCK)) > 0) {
        /* printf("\n\nREAD AGAIN\n\n"); */
        /* printf("\n\n%d read\n\n", length); */
        for (int i = 0; i < length; i++) {
            write_code(file_out, &table[buf_encode[i]]);
        }
    }
    flush_codes(file_out);

    // Print statistics
    if (verbose) {
        uint64_t comp_size = bytes_written;
        printf("Uncompressed file size: %lu bytes\n", h.file_size);
        printf("Compressed file size: %lu bytes\n", comp_size);
        printf("Space saving: %2.2f%%\n", 100 * (1 - ((double)comp_size/(double)h.file_size)));
    }

    // Clean exit
    delete_tree(&root);
    close(file_in);
    close(file_out);

    return 0;
}

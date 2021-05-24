#include "code.h" // Code ADT
#include "defines.h" // BLOCK, MAGIC, ALPHABET, etc.
#include "huffman.h" // Huffman tree construction and traversal
#include "io.h" // writing and reading files
#include "io_extnd.h"
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
    int file_temp = -1;
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

    // Create tempfile if needed
    if (file_in == STDIN_FILENO) {
        FILE* temp = tmpfile();
        if (temp == NULL) { // If not created successfully
            return 1; 
        }
        file_temp = fileno(temp);
    }

    // Transfer File permissions
    fstat(file_in, &statbuf);
    if (file_in != STDIN_FILENO && file_out != STDOUT_FILENO) {
        fchmod(file_out, statbuf.st_mode);
    }

    // Parse

    // Create Histogram
    // NEED TEMPFILE STUFF
    uint64_t hist[ALPHABET] = { 0 };
    hist[0] = 1;
    hist[255] = 1;
    uint8_t buf[BLOCK] = { 0 };
    int length = 0;

    while ((length = read_bytes(file_in, buf, BLOCK)) > 0) {
        // Fill tempfile with original file
        if (file_temp > 0) {
            write_bytes(file_temp, buf, length);
            printf("writing to tempfile");
        }

        for (int i = 0; i < length; i++) {
            hist[buf[i]]++; // increment frequency of character in histogram
        }
    }
    uint64_t uncomp_size = bytes_read;

    // Create tree

    Node *root = build_tree(hist);

    // Construct header
    Header h = { MAGIC, statbuf.st_mode, tree_size, statbuf.st_size };
    write_header(file_out, &h);

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
    if (file_temp <= 0) {
        lseek(file_in, 0, SEEK_SET);
    } else {
        file_in = file_temp;
        printf("reading from tempfile");
    }

    length = 0;
    while ((length = read_bytes(file_in, buf, BLOCK)) > 0) {
        for (int i = 0; i < length; i++) {
            write_code(file_out, &table[buf[i]]);
        }
    }
    flush_codes(file_out);

    // Print statistics
    if (verbose) {
        uint64_t comp_size = bytes_written;
        printf("Uncompressed file size: %lu bytes\n", uncomp_size);
        printf("Compressed file size: %lu bytes\n", comp_size);
        printf("Space saving: %2.2f%%\n", 100 * (1 - ((double) comp_size / (double) uncomp_size)));
    }

    // Clean exit
    delete_tree(&root);
    close(file_in);
    close(file_temp);
    close(file_out);

    return 0;
}

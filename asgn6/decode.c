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
    "SYNOPSIS\n  A Huffman code decoder.\n\nUSAGE\n  pipe or specify a file to "                   \
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
            fprintf(stderr, HELP);
            return 0;
            break;
        case 'v': verbose = true; break;
        case 'i':
            if ((file_in = open(optarg, O_RDONLY)) == -1) {
                fprintf(stderr, FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        case 'o':
            if ((file_out = tree_out = open(optarg, O_WRONLY | O_TRUNC | O_CREAT)) == -1) {
                fprintf(stderr, FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        default: return 1; // error
        }
    }

    fstat(file_in, &statbuf);

    // Read Header
    Header h;
    read_header(file_in, &h);

    // Verify magic number
    if (h.magic != MAGIC) {
        fprintf(stderr, "not a magic number\n");
        close(file_in);
        close(file_out);
        return 0;
    }

    // Transfer file permissions
    if (file_in != STDIN_FILENO && file_out != STDOUT_FILENO) {
        fchmod(file_out, h.permissions);
    }

    // Reconstruct tree
    uint8_t *tree = (uint8_t *) malloc(h.tree_size);
    read_bytes(file_in, tree, h.tree_size);
    Node *root = rebuild_tree(h.tree_size, tree);
    free(tree);

    uint8_t buf[BLOCK] = { 0 };
    uint64_t buf_idx = 0;
    uint8_t bit = 0;
    /* uint64_t i = 0; */
    Node *curr = root;
    while (read_bit(file_in, &bit)) {
        if (bit == 0) {
            curr = node_left(curr);
        } else {
            curr = node_right(curr);
        }

        if (curr->left == NULL) {
            buf[buf_idx++] = node_symbol(curr);
            curr = root;

            if (buf_idx >= BLOCK) {
                /* printf("printing %lu\n", buf_idx); */
                write_bytes(file_out, buf, buf_idx);
                buf_idx = 0;
            }
        }
    }

    // Flush decoded bytes
    write_bytes(file_out, buf, buf_idx);

    // Print statistics
    if (verbose) {
        uint64_t uncomp_size = bytes_written;
        uint64_t comp_size = bytes_read;
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", uncomp_size);
        fprintf(stderr, "Compressed file size: %lu bytes\n", comp_size);
        fprintf(stderr, "Space saving: %2.2f%%\n",
            100 * (1 - ((double) comp_size / (double) uncomp_size)));
    }

    // Clean exit
    delete_tree(&root);
    close(file_in);
    close(file_out);
    return 0;
}

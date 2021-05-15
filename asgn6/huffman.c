#include "huffman.h"
#include "node_extnd.h"
#include <stdlib.h>

#include "pq.h"
#include <stdio.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {

    // Create PriorityQueue from histogram
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint64_t i = 0; i < 256; i++) {
        if (hist[i] != 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }

    // Join together tree
    Node *one; // left placeholder
    Node *two; // right placeholder
    while (true) {
        if (pq_size(q) <= 1) {
            break;
        }
        dequeue(q, &one); // left placeholder
        dequeue(q, &two); // right placeholder
        enqueue(q, node_join(one, two));
    }

    // Return root
    Node *o;
    dequeue(q, &o); // root
    return o;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init(); 
    Node *curr = root;
    uint8_t go = 0;
    uint8_t went = 0;

    while (true) {
        printf("At: ");
        node_print(curr);
        printf("going %s\n", go ? "right" : "left");
        if (go == 0 && node_left(curr) != NULL) {
            curr = node_left(curr);
            code_push_bit(&c, 0);
        } else {
            curr = node_right(curr);
            code_push_bit(&c, 1);
            go = 0;
        }
        // coming back up from a 0 go right
        // coming back up from a 1 go up
        if (node_symbol(curr) != '$' && node_right(curr) == NULL) {
            table[node_symbol(curr)] = c;
            node_print(curr);
            code_print(&c);
            printf("\n");
            code_pop_bit(&c, &went);
            if (went == 1) {
                code_pop_bit(&c, &went);
                while (went == 1) {
                    code_pop_bit(&c, &went);
                    if (code_empty(&c)) {
                        return;
                    }
                }
            }
            go = 1;
        }

    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root);


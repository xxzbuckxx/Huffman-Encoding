#include "huffman.h"
#include "pq.h"

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

void build_codes(Node *root, Code table[static ALPHABET]);

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root);


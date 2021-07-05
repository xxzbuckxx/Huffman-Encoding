#include "huffman.h"

#include "node_extnd.h"
#include "pq.h"
#include "stack.h"
#include "tree_info.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t buf_tree[BLOCK] = { 0 };
uint32_t buf_tree_idx = 0;
uint64_t tree_size = 0;

//
// Builds a Huffman tree from a histogram
//
// hist: a histogram where indecies correspond to ascii characters
//
Node *build_tree(uint64_t hist[static ALPHABET]) {

    // Create PriorityQueue from histogram
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint64_t i = 0; i < 256; i++) {
        if (hist[i] != 0) {
            tree_size++;
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
    pq_delete(&q);
    tree_size = tree_size * 3 - 1;
    return o;
}

//
// Recursive depth first search of the Huffman tree
//
// table: a table to store the produced codes
// curr: the address to the node being searched currently
// c: code being produced
// go: 0 if searching left, 1 if searching right
//
void dfs(Code table[static ALPHABET], Node *curr, Code c, uint8_t go) {
    static bool first_call = true;
    code_push_bit(&c, go);

    // No extra 0 (since calling on root)
    if (first_call) {
        uint8_t trash;
        code_pop_bit(&c, &trash);
        first_call = false;
    }

    if (buf_tree_idx >= BLOCK - 2) {
        write_bytes(tree_out, buf_tree, buf_tree_idx);
        buf_tree_idx = 0;
    }

    // Recursion
    if (node_symbol(curr) == '$' && node_right(curr) != NULL) { // if not a leaf node
        dfs(table, node_left(curr), c, 0); // left recursion
        dfs(table, node_right(curr), c, 1); // rigth recursion
        buf_tree[buf_tree_idx++] = 'I';
    } else { // base case
        table[node_symbol(curr)] = c;
        buf_tree[buf_tree_idx++] = 'L';
        buf_tree[buf_tree_idx++] = node_symbol(curr);
    }
    return;
}

//
// Build codes given a Huffman tree
//
// root: an address to a node that is the root of the Huffman tree
// table: a table of produced codes (indices correspond to ascii chars)
//
void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init(); // initalize code table
    dfs(table, root, c, 0); // recursive depth first search
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *tree_out = stack_create(nbytes / 3); // point of error?
    uint64_t i = 0;
    while (i < nbytes) {
        if (tree[i] == 'L') {
            stack_push(tree_out, node_create(tree[++i], 0));
        } else {
            // Pop Right
            Node *r;
            stack_pop(tree_out, &r);

            // Pop Left
            Node *l;
            stack_pop(tree_out, &l);

            // Join
            stack_push(tree_out, node_join(l, r));
        }
        i++;
    }
    Node *root;
    stack_pop(tree_out, &root);
    stack_delete(&tree_out);
    return root;
}

//
// Recursive depth first delete of Huffman tree
//
// curr: the address to the node whose children are being delete
//
void dfd(Node *curr) {
    if (node_symbol(curr) == '$' && node_right(curr) != NULL) { // if not leaf
        // left
        Node *l = node_left(curr); // store pointer to left child
        dfd(l); // left recursion
        node_delete(&l); // left delete

        // right
        Node *r = node_right(curr); // store pointer to right child
        dfd(r); // right recursion
        node_delete(&r); // right delete
    }
    return;
}

//
// Deletes a Huffman tree
//
// root: the address to the address of the root node of the Huffman tree
//
void delete_tree(Node **root) {
    dfd(*root); // recursive depth first delete
    node_delete(root); // delete root node
    return;
}

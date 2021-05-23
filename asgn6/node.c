#include "node.h"

#include "node_extnd.h"

#include <stdio.h>
#include <stdlib.h>

//
// Creates a Node
//
// symbol: symbol of node
// frequency: frequency of node
//
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
        n->right = NULL;
        n->left = NULL;
    }
    return n;
}

// Helper Functions from node_extnd.h //

//
// Returns Node frequency
//
// n: an adress to a Node
//
uint64_t node_frequency(Node *n) {
    return n ? n->frequency : 0;
}

//
// Returns Node symbol
//
// n: an address to a node
//
uint8_t node_symbol(Node *n) {
    return n ? n->symbol : 0;
}

//
// Returns left node
//
// n: an address to a node
//
Node *node_left(Node *n) {
    return n && n->left ? n->left : NULL;
}

//
// Returns right node
//
// n: an address to a node
//
Node *node_right(Node *n) {
    return n && n->right ? n->right : NULL;
}

///////////////////////////////////////

//
// Delete a Node
//
// n: an adress to an address of a Node
//
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

//
// Join two nodes together
//
// left: an address of a Node to be stored to the left
// right: an address of a Node to be stored toe the right
//
Node *node_join(Node *left, Node *right) {
    Node *n = node_create((uint8_t) '$', right->frequency + left->frequency);
    n->left = left;
    n->right = right;
    return n;
}

//
// Prints a node for debugging
//
// n: an address of a node to be stored
//
void node_print(Node *n) {
    printf("%c:%ld\n", n->symbol, n->frequency);
    if (n->left != NULL && n->right != NULL) {
        printf("left:[%c:%ld]   right:[%c:%ld]\n", n->left->symbol, n->left->frequency,
            n->right->symbol, n->right->frequency);
    }
    return;
}

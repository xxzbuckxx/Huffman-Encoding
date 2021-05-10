#include "node.h"

#include <stdlib.h>
#include <stdio.h>

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
    }
    n->left = NULL;
    n->right = NULL;
    return n;
}

// 
// Delete a Node
//
// n: an adress to an address of a Node
//
void node_delete(Node **n) {
    free(&n);
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
    printf("   %c:%ld\n", n->symbol, n->frequency);
    if (n->left != NULL && n->right != NULL) {
        printf("   /  \\\n%c:%ld   %c:%ld\n", n->left->symbol, n->left->frequency, n->right->symbol, n->right->frequency);
    }

    return;
}

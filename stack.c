#include "stack.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h> // malloc

//
// Structure for defining Stack data structure
//
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

//
// Creates a stack
//
// capacity: max size of the stack
//
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) { // if allocation successful
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!s->items) { // if no room in memory
            free(s);
            s = NULL; // Ensure pointer is not pointing to memory no longer used
        }
    }
    return s;
}

//
// Deletes a stack
//
// s: a stack to delete
//
void stack_delete(Stack **s) {
    if (*s && (*s)->items) { // if stack exists and has items
        free((*s)->items);
        free(*s);
        *s = NULL; // ensure pointer is not pointing to memory no longer used
    }
    return;
}

//
// Returns if stack is empty or not
//
// s: a stack to check
//
bool stack_empty(Stack *s) {
    return s->top == 0;
}

//
// Returns if stack is full or not
//
// s: stack to check
//
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

//
// Returns size of the stack
//
// s: the stack to return the size of
//
uint32_t stack_size(Stack *s) {
    return (s && s->items) ? s->top : 0; //if stack exists and has items
}

//
// Adds the given item to the top of the stack and returns if successful
//
// s: stack to push item to
// n: Node to add to stack
//
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) { // can not add to a full stack
        return false;
    }
    s->items[s->top] = n; // top item = x
    s->top += 1;
    return true;
}

//
// Removes last item on the stack and stores returns the
//
// s: the stack to pop from
// x: the address to store the popped Node
//
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) { // can not pop from an empty stack
        return false;
    }
    s->top -= 1;
    *n = s->items[s->top]; // store top item at given address
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i += 1) { // iterate through item indices
        printf("%d is:\n", i);
        node_print(s->items[i]);
        if (i + 1 != s->top) { // do not print newline for last case
            printf("\n");
        }
    }
}

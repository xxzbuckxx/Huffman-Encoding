#include "stack.h"

#include <inttypes.h> // PRIu32
#include <stdbool.h> // true and false
#include <stdint.h> // extended integer library
#include <stdio.h> // print
#include <stdlib.h> // malloc

//
// Structure for defining stack data structure
//
// Structure taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
typedef struct Stack {
    uint32_t top; // index of the next empty slot.
    uint32_t capacity; // number of items that can be pushed.
    uint32_t *items; // array of items, each with type uint32_t.
} Stack;

//
// Creates a stack
//
// capacity: max size of the stack
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); // allocate memory for stack structure
    if (s) { // if allocation successful
        s->top = 0;
        s->capacity = capacity;
        s->items
            = (uint32_t *) calloc(capacity, sizeof(uint32_t)); // Allocate memory for stack items
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
// s: the address of the stack to delete
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
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
// s: the address of the stack to check
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
bool stack_empty(Stack *s) {
    return s->top == 0;
}

//
// Returns if stack is full or not
//
// s: the address of the stack to test
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

//
// Returns size of the stack
//
// s: the address of the stack to return the size of
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
uint32_t stack_size(Stack *s) {
    return (s && s->items) ? s->top : (uint32_t) -1; //if stack exists and has items
}

//
// Adds the given item to the top of the stack and returns if successful
//
// s: the address of the stack to push item to
// x: item to add to stack
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) { // can not add to a full stack
        return false;
    }
    s->items[s->top] = x; // top item = x
    s->top += 1;
    return true;
}

//
// Removes last item on the stack and stores returns the
//
// s: the address of the stack to pop from
// x: the address to store the popped value
// Function taken from Professor Darrell Long (Stacks and Queues Lecture 4/19/21)
//
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) { // can not pop from an empty stack
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top]; // store top item at given address
    return true;
}

//
// Gives the top element of the stack without popping
//
// s: the address of the stack to peek from
// x: the address to store the peeked value
//
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top - 1];
        return true;
    }
    return true;
}

//
// Copies a given stack
//
// dst: the address to where the stack should be copied
// src: the address of the stack to be copied
//
void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;
    dst->capacity = src->capacity;
    for (uint32_t i = 0; i < dst->capacity; i++) {
        dst->items[i] = src->items[i];
    }
    return;
}

//
// Prints elements of the stack
//
// s: the stack to print
// outfile: file to print to
// cities: address to addresses to city names
// Function given by Professor Darrell Long in Lab Document (Circumnavigations of Denver Long)
//
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) { // iterate through item indices
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) { // do not print comma for last case
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}

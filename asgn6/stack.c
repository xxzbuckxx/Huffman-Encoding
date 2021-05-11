#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> // malloc

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) { // if allocation successful
        s->top = 0;
        s->capacity = capacity;
        *s->items = (Node *) calloc(capacity, sizeof(Node));
        if (!s->items) { // if no room in memory
            free(s);
            s = NULL; // Ensure pointer is not pointing to memory no longer used
        }
    }
    return s;
}

void stack_delete(Stack **s);

bool stack_empty(Stack *s);

bool stack_full(Stack *s);

uint32_t stack_size(Stack *s);

bool stack_push(Stack *s, Node *n);

bool stack_pop(Stack *s, Node **n);

void stack_print(Stack *s);

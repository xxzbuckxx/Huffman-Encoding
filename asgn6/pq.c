#include "pq.h"

#include "node.h"
#include "node_extnd.h"

#include <stdio.h>
#include <stdlib.h> // malloc
#include <sys/types.h>

// implemented using explanation from pages.cs.wisc.edu/~vernon/cs367/notes/11.PRIORITY-Q.html

typedef struct PriorityQueue {
    Node **min_heap;
    uint32_t top;
    uint32_t capacity;
} PriorityQueue;

//
// Creates a PriorityQueue
//
// capacity: max size of the PriorityQueue
//
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) { // if allocation successful
        q->capacity = capacity;
        q->top = 1;
        q->min_heap = (Node **) calloc(capacity, sizeof(Node));
        if (!q->min_heap) { // if no room in memory
            free(q);
            q = NULL; // Ensure pointer is not pointing to memory no longer used
        }
    }
    return q;
}

//
// Deletes a PriorityQueue
//
// s: a PriorityQueue to delete
//
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->min_heap) { // if PriorityQueue exists and has items
        free((*q)->min_heap);
        free(*q);
        *q = NULL; // ensure pointer is not pointing to memory no longer used
    }
    return;
}

// Helper

uint64_t pq_node_frequency(PriorityQueue *q, uint32_t idx) {
    return node_frequency(q->min_heap[idx]);
}

//
// Returns if PriorityQueue is empty or not
//
// s: a PriorityQueue to check
//
bool pq_empty(PriorityQueue *q) {
    return q->top == 1;
}

//
// Returns if PriorityQueue is empty or not
//
// s: a PriorityQueue to check
//
bool pq_full(PriorityQueue *q) {
    return q->top == q->capacity;
}

//
// Returns size of the PriorityQueue
//
// s: the PriorityQueue to return the size of
//
uint32_t pq_size(PriorityQueue *q) {
    return (q && q->min_heap) ? q->top : 0; //if PriorityQueue exists and has items
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    q->min_heap[q->top] = n;

    // Fix heap
    uint32_t i = q->top;
    while (i > 1) {
        if (pq_node_frequency(q, i) < pq_node_frequency(q, i / 2)) {
            Node *temp = q->min_heap[i];
            q->min_heap[i] = q->min_heap[i / 2];
            q->min_heap[i / 2] = temp;
        } else {
            break;
        }
        i /= 2;
    }
    q->top++;
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }

    *n = q->min_heap[1];
    q->top--;

    // Fix heap
    q->min_heap[1] = q->min_heap[q->top];
    uint32_t i = 1;
    uint32_t smallest_idx = 0;
    Node *swap;
    while (i < q->top) {

        // Find smaller leaf
        if (i * 2 + 1 <= q->top && pq_node_frequency(q, i * 2) > pq_node_frequency(q, i * 2 + 1)) {
            smallest_idx = i * 2 + 1;
        } else if (i * 2 <= q->top) {
            smallest_idx = i * 2;
        } else {
            break;
        }
        swap = q->min_heap
                   [smallest_idx]; // smaller leaf will be swapped if smaller then current element

        // Fix spot?
        if (pq_node_frequency(q, i) > node_frequency(swap)) { // swap if leaf smaller
            q->min_heap[smallest_idx] = q->min_heap[i];
            q->min_heap[i] = swap;
        } else { // if not then tree fixed
            break;
        }

        i = smallest_idx;
    }

    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->top; i += 1) { // iterate through item indices
        printf("%ld", node_frequency(q->min_heap[i]));
        if (i + 1 != q->top) { // do not print newline for last case
            printf(" ");
        }
    }
    printf("\n");
}

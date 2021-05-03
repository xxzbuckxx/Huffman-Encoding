#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdlib.h>

//
// Structure for defining a path
//
typedef struct Path {
    Stack *vertices; // vertices in path
    uint32_t length; // length of path (sum of length between vertices)

} Path;

//
// Creates a path
//
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) { // if allocation is successful
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    }
    return p;
}

//
// Deletes a path
//
// p: the address of the path to delete
//
void path_delete(Path **p) {
    if (*p && (*p)->vertices) { // if path exists and has items
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL; // ensure pointer is not pointing to memory no longer used
    }
    return;
}

//
// Pushes a vertex to the path
//
// p: the address of the path to push to
// v: vertex to push to path
// G: the address of the graph containing reference edge lengths
//
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (!stack_full(p->vertices)) {
        if (!stack_empty(p->vertices)) {
            uint32_t top = 0;
            stack_peek(p->vertices, &top); // need to know last element to calculate length
            p->length += graph_edge_weight(G, top, v);
        } else {
            p->length += graph_edge_weight(G, START_VERTEX, v);
        }
        if (stack_push(p->vertices, v)) {
            return 1; // true
        }
    }
    return 0; // false
}

//
// Pops a vertex from the path
//
// p: the address of the path to pop from
// v: the address to store the popped value
// G: the address of the graph containing reference edge lengths
//
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_pop(p->vertices, v)) {
        uint32_t top = 0;
        if (stack_peek(p->vertices, &top)) { // need to know last element to calculate length
            p->length -= graph_edge_weight(G, top, *v);
        } else {
            p->length -= graph_edge_weight(G, START_VERTEX, *v);
        }
        return 0; // true
    }
    return 1; // false
}

//
// Returns the number of vertices in a given path
//
// p: the address of the path to check
//
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

//
// Returns the length of a given path
//
// p: the address of the path to check
//
uint32_t path_length(Path *p) {
    return p->length;
}

//
// Copies a specified path
//
// dst: the address to destination of copied path
// src: the address of the path to copy
//
void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
    return;
}

//
// Prints a specified path with names
//
// p: path to print
// outfile: where to print
// cities: address to addresses to city names
//
void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
    return;
}

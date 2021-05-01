#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdlib.h>

typedef struct Path {
    Stack *vertices;
    uint32_t length;

} Path;

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    }
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (!stack_full(p->vertices)) {
        if (!stack_empty(p->vertices)) {
            uint32_t top = 0;
            stack_peek(p->vertices, &top);
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

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_pop(p->vertices, v)) {
        uint32_t top = 0;
        if (stack_peek(p->vertices, &top)) {
            p->length -= graph_edge_weight(G, top, *v);
        } else {
            p->length -= graph_edge_weight(G, START_VERTEX, *v);
        }
        return 0; // true
    }
    return 1; // false
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
    return;
}

#include "path.h"
#include "graph.h"
#include "vertices.h"

#include <inttypes.h> // PRIu32
#include <stdbool.h> // true and false
#include <stdlib.h> // Malloc
#include <stdio.h> // Print

uint32_t adjacent_edges(Graph *G, uint32_t v, uint32_t *adjacent) {
    if (graph_vertices(G) == 0) {
        return -1;
    }

    uint32_t n = 0;
    adjacent[n] = v;
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (graph_has_edge(G, v, i)) {
            adjacent[n] = i;
            n++;
        }
    }
    return n;
}

void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    graph_mark_visited(G, v); // Mark visited

    // Iterate through edges
    uint32_t number_nodes = graph_vertices(G);
    uint32_t *adj = (uint32_t *) malloc(number_nodes * sizeof(uint32_t));
    uint32_t adj_n = adjacent_edges(G, v, adj);

    for (uint32_t i = 0; i < adj_n; i++) {
        if (!graph_visited(G, adj[i])) {
            path_push_vertex(curr, adj[i], G);
            DFS(G, adj[i], curr, shortest, cities, outfile);
        }
    }

    graph_mark_unvisited(G, v);
    
    free(adj);
    return;
}

#include "graph.h"
#include "search.h"
#include "path.h"
#include "vertices.h"

#include <inttypes.h> // PRIu32
#include <stdbool.h> // true and false
#include <stdio.h> // Print
#include <stdlib.h> // Malloc


uint32_t adjacent_edges(Graph *G, uint32_t v, uint32_t *adjacent) {
    if (graph_vertices(G) == 0) {
        return 0;
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
    calls++;
    path_push_vertex(curr, v, G);
    graph_mark_visited(G, v); // Mark visited

    // Iterate through edges
    uint32_t number_nodes = graph_vertices(G);
    uint32_t *adj = (uint32_t *) malloc(number_nodes * sizeof(uint32_t));
    uint32_t adj_n = adjacent_edges(G, v, adj);
    /* printf("\n%d edges checking", adj_n); */

    /* static bool error = false; */
    /* if (path_vertices(curr) == 3) { */
    /*     if (v == 7) { */
    /*         error = true; */
    /*     } else { */
    /*         error = false; */
    /*     } */
    /* } */

    /* if (error) { */
    /*     path_print(curr, outfile, cities); */
    /* } */
    /* printf("\nprint graph? well path is %d long and total is %d\n", path_vertices(curr), */
        /* graph_vertices(G)); */

    if (path_vertices(curr) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        path_push_vertex(curr, START_VERTEX, G);
        if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
            printf("\nBOTTOM\n");
            printf("%d long\n", path_length(curr));
            path_print(curr, outfile, cities);
            printf("\n");
            /* graph_print(G); */
            path_copy(shortest, curr);
        }
        uint32_t trash = 0;
        path_pop_vertex(curr, &trash, G);
    } else if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
        printf("currently path has %d destinations and is %d long:\n", path_vertices(curr),
            path_length(curr));
        for (uint32_t i = 0; i < adj_n; i++) {
            /* printf("    %s has edge?\n", cities[adj[i]]); */
            printf("%d out of %d\n", i, adj_n);
            if (!graph_visited(G, adj[i])) {
                /* printf("  YEAH\n"); */
                /* printf("Recursive %s\n", cities[adj[i]]); */
                DFS(G, adj[i], curr, shortest, cities, outfile);
            }
        }
    }


    graph_mark_unvisited(G, v);

    free(adj);
    uint32_t pop = 0;
    path_pop_vertex(curr, &pop, G);
    return;
}

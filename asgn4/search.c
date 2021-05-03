#include "search.h"

#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <inttypes.h> // PRIu32
#include <stdbool.h> // true and false
#include <stdio.h> // Print
#include <stdlib.h> // Malloc

//
// Fills given pointer to array with parameter vectors adjacent edges
//
// G: graph that contains edge values
// v: given vector to check
// adjacent: array pointer that will store adjacent edges
//

uint32_t adjacent_edges(Graph *G, uint32_t v, uint32_t *adjacent) {
    if (graph_vertices(G) == 0) { // if graph has no vertices
        return 0;
    }

    uint32_t n = 0; // adjacent index
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (graph_has_edge(G, v, i)) {
            adjacent[n++] = i; // fill open element than increment to next open
        }
    }
    return n;
    adjacent[v] = v;
}

//
// Searches through possible paths using a depth first search
//
// G: graph that contains edge values
// v: vertex to check for connecting vertices
// curr: current path that is being checked
// shortest: shortest path
// outfile: file to print verbose output to
//
void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    calls++; // increment recursive call counter

    // Add start vertex on first call
    if (calls == 1) {
        path_push_vertex(curr, v, G);
    }

    graph_mark_visited(G, v); // ensures nodes are not visted twice

    // Calculate edges through edges
    uint32_t *adj = (uint32_t *) malloc(graph_vertices(G) * sizeof(uint32_t)); // array of edges
    uint32_t adj_n = adjacent_edges(G, v, adj); // number of edges

    // Recursion
    if (path_vertices(curr) == graph_vertices(G)
        && graph_has_edge(G, v, START_VERTEX)) { // base case

        path_push_vertex(curr, START_VERTEX, G);
        // Check if new path is shorter
        if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
            if (verbose) { // print all found paths when verbose
                fprintf(outfile, "Path length: %d\nPath: ", path_length(curr));
                path_print(curr, outfile, cities);
            }
            path_copy(shortest, curr);
        }
        uint32_t trash = 0;
        path_pop_vertex(curr, &trash, G);
    } else { // recursive check
        for (uint32_t i = 0; i < adj_n; i++) { // iterate through adjacent edges
            if (!graph_visited(G, adj[i])) {
                path_push_vertex(curr, adj[i], G);
                // Check if new path is shorter
                if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
                    DFS(G, adj[i], curr, shortest, cities, outfile); // recursive call
                }
                uint32_t trash = 0;
                path_pop_vertex(curr, &trash, G);
            }
        }
    }

    graph_mark_unvisited(G, v); // ensures when checking a new path node is not visited

    free(adj);
    return;
}

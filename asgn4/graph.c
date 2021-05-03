#include "graph.h"

#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

// Colors for graph print
// Color code found at https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

//
//  Structure for defining a graph
//
struct Graph {
    uint32_t vertices; // Number of vertices.
    bool undirected; // Undirected graph?
    bool visited[VERTICES]; // Where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; // matrix of stored vertices and edge lengths
};

//
// Creates a graph
//
// vertices: number of vertices
// undirected: if true vertices can be traveresed in both directions
//
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph)); // allocate memory for graph struct
    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;
        // Fill visited and matrix with 0s
        for (uint32_t i = 0; i < VERTICES; i++) {
            G->visited[i] = false;
            for (uint32_t j = 0; j < VERTICES; j++) {
                G->matrix[i][j] = 0;
            }
        }
    }
    return G;
}

//
// Delete a graph
//
// G: the address of the graph to delete
//
void graph_delete(Graph **G) {
    free(*G);
    G = NULL;
}

//
// Returns the number of vertices in a given graph
//
// G: the address of the graph to check
//
uint32_t graph_vertices(Graph *G) {
    return G ? G->vertices : 0;
}

//
// Add an edge with a length between two graph nodes
//
// G: the address of the graph to add an edge to
// i: origin vertex
// j: destination vertex
// k: length
//
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (G && i < graph_vertices(G) && j < graph_vertices(G)) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    }
    return false;
}

//
// Check if a graph contains a specified edge
//
// G: the address of the graph to check
// i: origin vertex
// j: destination vertex
//
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G && i < G->vertices && j < G->vertices) {
        return G->matrix[i][j];
    }
    return false;
}

//
// Return an edge between two vertices
//
// G: the address of the graph to check
// i: origin vertex
// j: destination vertex
//
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    return graph_has_edge(G, i, j) ? G->matrix[i][j] : 0;
}

//
// Returns if a specified vertex has been visited
//
// G: the address of the graph to check
// v: vertex to check
//
bool graph_visited(Graph *G, uint32_t v) {
    return G ? G->visited[v] : false;
}

//
// Mark a specified vertex as visited
//
// G: the address of the graph to change
// v: vertex to mark
//
void graph_mark_visited(Graph *G, uint32_t v) {
    if (G && v < graph_vertices(G)) {
        G->visited[v] = 1;
    }
    return;
}

//
// Mark a specified vertex as not visited
//
// G: the address of the graph to change
// v: vertex to unmark
//
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (G) {
        G->visited[v] = 0;
    }
    return;
}

//
// Prints graph as a matrix (for debugging)
//
// G: the address of the graph to print
//
void graph_print(Graph *G) {
    if (G) {
        printf("     ");
        // Draw Row labels
        for (uint32_t i = 0; i < G->vertices; i++) {
            printf("%s%d %s" RESET, graph_visited(G, i) ? GRN : RED, i,
                i < 9 ? " " : ""); // add space if single digit
        }
        printf("\n   ");
        // Draw Row dashes
        for (uint32_t i = 0; i < G->vertices; i++) {
            printf(YEL " --" RESET);
        }
        printf("\n");
        // Draw weights in matrix
        for (uint32_t r = 0; r < G->vertices; r++) {
            printf("%s%s%d" YEL " | " RESET, graph_visited(G, r) ? GRN : RED, r < 10 ? " " : "",
                r); // add space if single digit
            for (uint32_t c = 0; c < G->vertices; c++) {
                if (graph_has_edge(G, r, c)) {
                    printf(MAG "%d%s " RESET, G->matrix[r][c], G->matrix[r][c] < 10 ? " " : "");
                } else {
                    printf("%s%d  " RESET, graph_visited(G, r) || graph_visited(G, c) ? BLU : YEL,
                        G->matrix[r][c]);
                }
            }
            printf("\n");
        }
    }
    return;
}

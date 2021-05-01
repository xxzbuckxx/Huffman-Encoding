#include "graph.h"

#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

// FOR PRINT COLORS
// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

//

struct Graph {
    uint32_t vertices; // Number of vertices.
    bool undirected; // Undirected graph?
    bool visited[VERTICES]; // Where have we gone?
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph)); // allocate memory for graph struct
    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;
    }
    return G;
}

void graph_delete(Graph **G) {
    free(*G);
    G = NULL;
}

uint32_t graph_vertices(Graph *G) {
    return G ? G->vertices : -1;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (G && i < VERTICES && j < VERTICES && k > 0) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return 1;
    }
    return 0;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G && i < VERTICES && j < VERTICES) {
        return G->matrix[i][j];
    }
    return 0;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    return graph_has_edge(G, i, j) ? G->matrix[i][j] : 0;
}

bool graph_visited(Graph *G, uint32_t v) {
    return G ? G->visited[v] : -1;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (G) {
        G->visited[v] = 1;
    }
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (G) {
        G->visited[v] = 0;
    }
    return;
}

void graph_print(Graph *G) {
    if (G) {
        printf("     ");
        // Draw Row labels
        for (uint32_t i = 0; i < VERTICES; i++) {
            printf("%s%d %s" RESET, graph_visited(G, i) ? GRN : RED, i,
                i < 9 ? " " : ""); // add space if single digit
        }
        printf("\n   ");
        // Draw Row dashes
        for (uint32_t i = 0; i < VERTICES; i++) {
            printf(YEL " --" RESET);
        }
        printf("\n");
        // Draw weights in matrix
        for (uint32_t r = 0; r < VERTICES; r++) {
            printf("%s%s%d" YEL " | " RESET, graph_visited(G, r) ? GRN : RED, r < 10 ? " " : "",
                r); // add space if single digit
            for (uint32_t c = 0; c < VERTICES; c++) {
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

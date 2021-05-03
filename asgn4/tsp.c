#include "graph.h"
#include "path.h"
#include "search.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h> // PRIu32
#include <stdio.h> // Printing
#include <stdlib.h>
#include <string.h> // strlen
#include <unistd.h> // For getopt()

#define OPTIONS "hvui:o:"

#define HELP                                                                                       \
    "SYNOPSIS\n    A path finding thingy.\n\nUSAGE\n    ./tsp [-hvu] [-i in path] [-o out "        \
    "path]\n\nOPTIONS\n    -h              Display program help and usage.\n    -v              "  \
    "Print all Hamiltonian paths found.\n    -u				Specify the graph to be "                       \
    "undirected.\n    -i in path		Specify input file path.\n    -o out path	"                      \
    "	Specify output file path\n"

#define FILE_NOT_FOUND "File not found ;(\n"

#define BUFFER_SIZE 1024

// Global variable definitions
uint64_t calls = 0;
bool verbose = false;

void free_cities(char *cities[], uint32_t nodes);

//
// Main execution
//
int main(int argc, char **argv) {

    // If no arguments given
    if (argc < 2) {
        printf(HELP);
        return 1; // error
    }

    FILE *file_in = stdin;
    FILE *file_out = stdout;
    bool directed = 0; // false

    //-------- PARSE --------//

    // Parse program arguments
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(HELP); break;
        case 'v': verbose = true; break;
        case 'u': directed = 1; break;
        case 'i':
            if ((file_in = fopen(optarg, "r")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        case 'o':
            if ((file_out = fopen(optarg, "w")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1; // error
            }
            break;
        default: return 1; // error
        }
    }

    // CITIES
    char buffer[BUFFER_SIZE];
    uint32_t number_nodes = 0;

    if ((number_nodes = strtol(fgets(buffer, BUFFER_SIZE, file_in), NULL, 10)) == 0) {
        printf("There's nowhere to go.\n");
        return 1; // error
    }

    char *cities[number_nodes]; // should use malloc

    // store cities
    for (uint32_t i = 0; i < number_nodes; i++) {
        if (fgets(buffer, BUFFER_SIZE, file_in) != NULL) {
            buffer[strlen(buffer) - 1] = '\0';
            char *city = (char *) malloc(50);
            strcpy(city, buffer); // DO NOT USE STRING COPY
            cities[i] = city;
        } else {
            free_cities(cities, i);
            printf("Incorrectly formatted input ;(\n");
            return 1; // error
        }
    }

    Graph *G = graph_create(number_nodes, directed); // vertex adjacency graph

    int i, j, w;
    int returned = 0;
    while ((returned = fscanf(file_in, "%d %d %d", &i, &j, &w)) != EOF) {
        if (!graph_add_edge(G, i, j, w) || returned < 3) {
            free_cities(cities, number_nodes);
            printf("Error: malformed edge.\n");
            return 1; // error
        }
    }

    fclose(file_in); // close input file (done scanning)

    //-------- RECURSION  --------//

    calls = 0; // number of recursive calls

    Path *curr = path_create(); // path that DFS is currently checking
    Path *shortest = path_create(); // shortest path

    DFS(G, START_VERTEX, curr, shortest, cities, file_out); // recursive depth first search

    // Print shortest path
    if (path_vertices(shortest) > 0) { // found a shortest path
        fprintf(file_out, "Path length: %d\nPath: ", path_length(shortest));
        path_print(shortest, file_out, cities);
        fprintf(file_out, "Total recursive calls: %lu\n", calls);
    } else { // no shortest path found
        fprintf(file_out, "There's nowhere to go.\n");
    }

    //-------- MEMORY FREE --------//

    // Free all allocated memory
    free_cities(cities, number_nodes);
    path_delete(&shortest);
    path_delete(&curr);
    graph_delete(&G);
    fclose(file_out);
    return 0;
}

//
// Frees allocated memory from cities array
//
// cities: address to allocated character arrays for city names
// nodes: number of allocated character arrays to free
//
void free_cities(char *cities[], uint32_t nodes) {
    for (uint32_t i = 0; i < nodes; i++) {
        free(cities[i]);
    }
}

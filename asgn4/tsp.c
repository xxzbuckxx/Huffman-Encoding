#include "graph.h"
#include "path.h"
#include "search.h"
#include "stack.h"
#include "vertices.h"
#include "search.h"

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

// global variable definitions
uint64_t calls = 0;
bool verbose = false;

//
// Main execution
//
int main(int argc, char **argv) {

    // if no arguments given
    if (argc < 2) {
        printf(HELP);
        return 1;
    }

    FILE *file_in = stdin;
    FILE *file_out = stdout;
    bool directed = 0; // false

    //-------- PARSE --------//
    // ARGUMENTS
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(HELP); break;
        case 'v': verbose = true; break;
        case 'u': directed = 1; break;
        // https://www.tutorialspoint.com/c_standard_library/c_function_freopen.htm
        case 'i':
            if ((file_in = fopen(optarg, "r")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1;
            }
            break;
        case 'o':
            if ((file_out = fopen(optarg, "w")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1;
            }
            break;
        default: return 1; // ERROR
        }
    }

    calls = 0;

    // CITIES
    char buffer[BUFFER_SIZE];
    uint32_t number_nodes = 0;

    if ((number_nodes = strtol(fgets(buffer, BUFFER_SIZE, file_in), NULL, 10)) == 0) {
        printf("Input configured incorrectly ;(\n");
        return 1; // ERROR
    }

    char *cities[number_nodes]; // should use malloc

    // store cities
    for (uint32_t i = 0; i < number_nodes && fgets(buffer, BUFFER_SIZE, file_in) != NULL; i++) {
        buffer[strlen(buffer) - 1] = '\0';
        char *city = (char *) malloc(50);
        strcpy(city, buffer); // DO NOT USE STRING COPY
        cities[i] = city;
    }

    Graph *G = graph_create(number_nodes, directed);

    uint32_t i, j, w;

    while (fscanf(file_in, "%u %d %d", &i, &j, &w) != EOF) {
        graph_add_edge(G, i, j, w);
    }

    // BEGIN SEARCH

    ////// RECURISON
    Path *curr = path_create();
    Path *shortest = path_create();

    DFS(G, START_VERTEX, curr, shortest, cities, file_out);

    /////

    /* printf("shortest\n"); */
    fprintf(file_out, "Length: %d\nPath: ", path_length(shortest));
    path_print(shortest, file_out, cities);
    fprintf(file_out, "Total recursive calls: %lu\n", calls);

    // FREE MEMORY FROM CITIES
    for (i = 0; i < number_nodes; i++) {
        free(cities[i]);
    }

    path_delete(&shortest);
    path_delete(&curr);
    graph_delete(&G);
    fclose(file_in);
    fclose(file_out);
    return 0;
}

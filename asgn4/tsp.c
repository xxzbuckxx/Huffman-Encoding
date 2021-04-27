#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h> // PRIu32
#include <stdio.h> // Printing
#include <unistd.h> // For getopt()

#define OPTIONS "hvui:o:"

#define HELP "chicken"

#define FILE_NOT_FOUND "File not found ;("

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
    bool verbose = 1; // false
    bool directed = 1; // false

    //-------- PARSE --------//
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printf(HELP); break;
        case 'v': verbose = 0; break;
        case 'u': directed = 0; break;
        // https://www.tutorialspoint.com/c_standard_library/c_function_freopen.htm
        case 'i':
            if ((file_in = fopen(optarg, "r")) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1;
            }
            break;
        case 'o':
            if ((file_out = freopen(optarg, "w", stdout)) == NULL) {
                printf(FILE_NOT_FOUND);
                return 1;
            }
            break;
        default: return 1; //ERROR
        }
    }

    printf("CHICKEN");
    Graph *G = graph_create(13, 0);
    graph_add_edge(G, 3, 5, 7);
    graph_mark_visited(G, 3);
    graph_mark_visited(G, 5);
    printf("%d vertices\n", graph_vertices(G));
    graph_print(G);
    fclose(file_in);
    fclose(file_out);
    return 0;
}

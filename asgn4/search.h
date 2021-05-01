#include "graph.h"
#include "path.h"
#include <inttypes.h> // PRIu32
#include <stdbool.h>

extern uint64_t calls;

uint32_t adjacent_edges(Graph *G, uint32_t v, uint32_t *adjacent);

void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile);

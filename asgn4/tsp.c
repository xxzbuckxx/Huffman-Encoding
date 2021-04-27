#include "path.h"
#include "vertices.h"
#include "graph.h"
#include "stack.h"

#include <stdio.h> // Printing
#include <inttypes.h> // PRIu32
#include <unistd.h> // For getopt()

#define OPTIONS "hvui:o:";

#define HELP "chicken"

//
// Main execution
//
int main(int argc, char **argc) {

    // if no arguments given
    if (argc < 2) {
        printf(HELP);
        return 1;
    }

    FILE *file_in;



    // STDIN USE FIXED SIZE 

    // If statement taken from Tutor Eric
    if ((file = freopen("file.txt", "r")) == NULL) {

    }
    // 

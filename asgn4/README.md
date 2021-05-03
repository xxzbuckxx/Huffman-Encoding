
# Assignment 4 - The circumnavigation of Denver Long

A program (tsp) that finds the shortest path to hit all given destinations once.

# How to Build

Execute the command `make` and it should compile using the provided makefile.

Run the compiled binary with `./tsp`

#### Options

* -v : print verbose output (all found paths)
* -u : specifies an undirected graph
* -i `input file` : file that contains a graph to search
* -o `output file`: file that is printed to
* -h help : how to use function

# File Explanation

#### Makefile

This makefile compiles the program.

* remove binaries using `make clean`
* run a memory leak test using `make leak-check`
* format code using `make format`

#### tsp.c

This is the program that is compiled and executed

#### search.c

This is the file that contains DFS (depth first search) and adjacent_edges (a function for finding adjacent edges)

#### search.h

Header file for search.h

This file contains a global definition for recursive calls

#### graph.c

Graph implementation which uses an adjacency matrix to represent edge lengths.

#### graph.h

Graph header file defining graph functions

#### path.c

Path implementation: contains the path length and vertices

#### path.h

Header file containing path functions

#### stack.c

Stack datatype implementation

#### stack.h

Header file defining stack functions

#### DESIGN.pdf

This document details how the program was designed. This includes:

* The objective of the assignment
* What was given in the lab doc
* General explanation for code implementation

#### HIDDEN FOLDERS

.DESIGN contains the LaTeX document for the design document

.WRITEUP contains the LaTeX document for the writeup as well as the graph jpgs
and bash scripts used to produce them
 

# Assignment 5 - Hamming Codes



# How to Build

Execute the command `make` and it should compile using the provided makefile.

Run the compiled binary with `./tsp`

#### Options

* -i `input file` : file that contains a graph to search
* -o `output file`: file that is printed to
* -v : print verbose output (all found paths)
* -h help : how to use function

# File Explanation

#### Makefile

This makefile compiles the program.

* remove binaries using `make clean`
* run a memory leak test using `make leak-check`
* format code using `make format`

#### encode.c

This file contains the implementation of the Hamming Code encoder.

#### decode.c

This file contains the implementation of the Hamming Code decoder.

#### error.c - provided

This file contains.

#### entropy.c - provided

This file contains.

#### bv.h -	provided

This file contains the bit vector ADT interface.

#### bv.c

This file contains the implementation of the bit vector ADT.

#### bm.h - provided

This file contains the bit matrix ADT interface

#### bm.c

This file contains the implementation for the bit matrix ADT interface.

#### hamming.h - provided

This file contains the interface of the Hamming Code module.

#### hamming.c

This file contains the implementation of the Hamming Code module.

#### DESIGN.pdf

This document details how the program was designed. This includes:

* The objective of the assignment
* What was given in the lab doc
* General explanation for code implementation

#### HIDDEN FOLDERS

.DESIGN contains the LaTeX document for the design document


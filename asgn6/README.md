# Assignment 6 - Huffman Coding

Create lossless static compression using Huffman trees. 

# How to Build

Execute the command `make` and it should compile using the provided makefile.

Run the compiled binary with `./encode` or `./decode` or `./entropy`

#### Options

* -i `input file` : file that is encoded/decoded
* -o `output file`: file that encoding/decoding is stored in
* -v : print compression statistics
* -h help : how to use function

# File Explanation

#### Makefile

This makefile compiles the program.

* remove binaries using `make clean`
* run a memory leak test using `make scan-build`
* format code using `make format`

#### encode.c

This file contains the implementation of the Huffman encoder.

#### decode.c

This file contains the implementation of the Huffman decoder.

#### entropy.c - provided

This file contains a program for calculating entropy.

#### defines.h - provided

This file contains macro definitions for common values like
the buffer size and max tree size.

#### node.h - provided

This file contains the node ADT interface.

#### node.c

This file contains the implementation of the node ADT.

#### pq.h - provided

This file contains the stack priority queue ADT interface.

#### pq.c

This file contains the implementation of the priority queue ADT.

#### code.h - provided

This file contains the code ADT interface.

#### code.c

This file contains the implementation of the code ADT interface.

#### io.h - provided

This file contains the I/O module interface.

#### io.c

This file contains the implementation for the I/O module.

#### stack.h - provided

This file contains the stack ADT interface.

#### stack.c

This file contains the implementation of the stack ADT.

#### huffman.h - provided

This file contains the Huffman coding module interface.

#### huffman.c

This file contains the implementation of the Huffman coding module interface.

#### DESIGN.pdf

This document details how the program was designed. This includes:

* The objective of the assignment
* What was given in the lab doc
* General explanation for code implementation

#### HIDDEN FOLDERS

.DESIGN contains the LaTeX document for the design document

## RESOURCES

* priority queue
	http://pages.cs.wisc.edu/~vernon/cs367/notes/11.PRIORITY-Q.html

# What is a process

* code, data, and stack
* program state
	* CPU rigisters
	* program counter
	* Stack pointer
* Only 1 thread per cpu core 
* Programs execute code
* loader can relocate instructions by address a a base address

## In an ideal world

* memory is very fast, large, and no-volatile
* in real world you can only pick two

## Fixed partitions: mulitple progams

* divide memory into fixed spaces
* queue/ assign memory to a space when it is free

## Allocating memory

* first fit: first suitable hole
* next fit: first suitable after the previously allocate hole
	* tends to be the best 
	* really only used on disk not memory
* best fit: the smallest hole that is larger than the desired region
	* actually the worst to use 
* worst fit: the largest available hole

#### Buddy allocation

* split larger chunks into to two smaller chunks
	* recursive
	* when freed it can be combined with its buddy to rebuild a larger chunk

#### Principle of locality

the most recent thing done is most probably the thing that will be done next

* most of execution time is in small loops (~90%) so caches are mad decent

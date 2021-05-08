# Makefile compiling (lines 2-16) adapted from Proffessor Long https://piazza.com/class/kmfs2bmdr9syz?cid=63

CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: encode decode error entropy

encode:
	$(CC) $(CFLAGS) -o encode encode.c nibble.c translator.c bv.c bm.c hamming.c

decode:
	$(CC) $(CFLAGS) -o decode decode.c nibble.c translator.c bv.c bm.c hamming.c

error:
	$(CC) $(CFLAGS) -o error nibble.c error.c bv.c bm.c hamming.c

entropy:
	$(CC) $(CFLAGS) -o entropy nibble.c entropy.c bv.c bm.c hamming.c -lm

clean:
	rm -f encode decode error entropy *.o valgrind-out.txt

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make


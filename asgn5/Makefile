# Makefile compiling (lines 2-16) adapted from Proffessor Long https://piazza.com/class/kmfs2bmdr9syz?cid=63

CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: encode decode error entropy

encode:
	$(CC) $(CFLAGS) -o encode.c bv.c bm.c hamming.c

decode:
	$(CC) $(CFLAGS) -o decode.c bv.c bm.c hamming.c

error:
	$(CC) $(CFLAGS) -o error.c bv.c bm.c hamming.c

entropy:
	$(CC) $(CFLAGS) -o entropy.c bv.c bm.c hamming.c

clean:
	rm -f tsp *.o valgrind-out.txt

bm:
	$(CC) $(CFLAGS) -o bm bm.c bv.c

format:
	clang-format -i -style=file *.[ch]

leak-check: clean all
	valgrind --leak-check=full\
         --show-leak-kinds=all\
         --track-origins=yes\
         --verbose\
         --log-file=valgrind-out.txt\
         ./tsp
	vim valgrind-out.txt

scan-build: clean
	scan-build make


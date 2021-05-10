# Makefile compiling (lines 2-16) adapted from Proffessor Long https://piazza.com/class/kmfs2bmdr9syz?cid=63
ENCODE = encode.c 
DECODE = decode.c
ERROR = error.c
ENTROPY = entropy.c

SOURCES = hamming.c bv.c bm.c translator.c nibble.c encode.c decode.c error.c entropy.c
OBJECTS = $(SOURCES:%.c=%.o)

CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: $(ENCODE) $(DECODE) $(ERROR) $(ENTROPY)

$(ENCODE): $(ENCODE)
	$(CC) -o $@ $^ $(LFLAGS)

$(ENCODE): $(DECODE)
	$(CC) -o $@ $^ $(LFLAGS)

$(ENCODE): $(ERROR)
	$(CC) -o $@ $^ $(LFLAGS)

$(ENCODE): $(ENTROPY)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.clean
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode error entropy *.o valgrind-out.txt

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make


ENCODE = encode
DECODE = decode
ENTROPY = entropy

SOURCES = io.c
# SOURCES = node.c pq.c code.c io.c stack.c huffman.c
OBJECTS = $(SOURCES:%.c=%.o)

CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: $(ENCODE) $(DECODE) $(ENTROPY)

encode: encode.o $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

decode: decode.o $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

entropy: entropy.o $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS) -lm

%.o: %.clean
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode error entropy *.o

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make

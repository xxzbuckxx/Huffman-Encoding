# Makefile compiling (lines 2-16) adapted from Proffessor Long https://piazza.com/class/kmfs2bmdr9syz?cid=63
EXEC = tsp

SOURCES = tsp.c graph.c path.c stack.c
OBJECTS = $(SOURCES:%.c=%.o)

CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.clean
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tsp *.o valgrind-out.txt

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

CFLAGS = -Wall -Wextra -g

CC = gcc

SRCS = src/cJSON.c src/bmphandlers.c src/solver.c src/main.c

LIBS = -lm

OBJS = $(SRCS:.c=.o)

build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o sudoku

.c.o : 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: sudoku
	./sudoku

clean: $(OBJS)
	rm -rf src/*.o

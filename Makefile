CC = gcc
CFLAGS = -Wall -Wextra -pedantic
DEPS = bheader.h functions.h
OBJ = bmain.o bheader.o functions.o

all: bcomp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bcomp: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f -- *.o

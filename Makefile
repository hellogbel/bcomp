CC = gcc
CFLAGS = -Wall
DEPS = bheader.h functions.h
OBJ = bmain.o bheader.o functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bcomp: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

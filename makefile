VPATH=src
CC=gcc
CFLAGS=-I.
DEPS=list.h rbtree.h littletalk.h
OBJ=util.o rbtree.o littletalk.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

littletalk: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	-rm *.o littletalk


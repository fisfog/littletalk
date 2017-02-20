VPATH=src
CC=gcc
CFLAGS=-I.
OPT=-Wall
DEPS=list.h rbtree.h littlelog.h littletalk.h 
OBJ=util.o rbtree.o littlelog.o littletalk.o

%.o: %.c $(DEPS)
	$(CC) $(OPT) -c -o $@ $< $(CFLAGS)

littletalk: $(OBJ)
	$(CC) $(OPT) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	-rm *.o littletalk


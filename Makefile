all: mines

clean:
	rm -f mines mines.o cutils.o

mines: mines.c cutils.o
	gcc mines.c cutils.o -o mines

cutils.o: cutils.c cutils.h
	gcc -c cutils.c -o cutils.o


CFLAGS = -Wall -g

all: proy1.o matriz.o matriz.h
	gcc $(CFLAGS) proy1.o matriz.o -o proy1

proy1.o: proy1.c
	gcc $(CFLAGS) proy1.c -o proy1.o -c

matriz.o: matriz.c matriz.h
	gcc $(CFLAGS) matriz.c -o matriz.o -c

clear:
	rm -f *.o
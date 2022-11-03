proy1: proy1.o matriz.o matriz.h
	gcc -o proy1 proy1.c matriz.c

proy1.o: proy1.c
	gcc -c -o proy1.o proy1.c

matriz.o: matriz.c matriz.h
	gcc -c -o matriz.o matriz.c

clear:
	rm -f *.o

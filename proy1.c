// Programa principal
#include <stdio.h>
#include "matriz.h"

/*typedef struct Node{
	float value;
	unsigned int cordX;
	struct Node *next;
} node;

typedef struct Matriz{
	node *list;
	unsigned int cordY;
	struct Matriz *next;
} matriz;*/

void main(){
	matriz *A = NULL, *B = NULL, *C = NULL, *D = NULL, *E = NULL, *F = NULL;
	unsigned int size_x1 = 5, size_y1 = 5, size_x2 = 5, size_y2 = 5;

	A = AsignarElemento(1, 1, 1, A, size_x1, size_y1);
	A = AsignarElemento(2, 1, 2, A, size_x1, size_y1);
	A = AsignarElemento(3, 2, 3, A, size_x1, size_y1);
	A = AsignarElemento(2, 3, 4, A, size_x1, size_y1);

	A = AsignarElemento(2, 2, 5, A, size_x2, size_y2);
        A = AsignarElemento(3, 1, 6, A, size_x2, size_y2);
        A = AsignarElemento(3, 2, 7, A, size_x2, size_y2);
        A = AsignarElemento(2, 3, 8, A, size_x2, size_y2);
	
	printf("Numero: %.2f\n\n", ObtenerElemento(2, 1, A));
	printf("Numero: %.2f\n\n", ObtenerElemento(2, 1, B));

	C = Sumar(A, B, size_x1, size_y1, size_x2, size_y2);
	D = ProductoPorEscalar(2, A);
	E = Producto(A, B, size_x1, size_y1, size_x2, size_y2);
	F = Transponer(A, size_x1, size_y1);

	Imprimir(A, size_x1, size_y1);
	Imprimir(B, size_x2, size_y2);
	Imprimir(C, size_x1, size_y1);
	Imprimir(D, size_x1, size_y1);
	Imprimir(E, size_x1, size_y1);
	Imprimir(F, size_y1, size_x1);
}

// Programa principal

#include "matriz.h"

typedef struct Node{
	int value;
	unsigned int cord;
	struct Node *next;
	struct Node *last;
} node;

typedef struct Matriz{
	node *list;
	unsigned int cordX;
	struct Matriz *next;
	struct Matriz *last;
} matriz;

void main(){
	node A, B, C;
	A = B = C = NULL;
	int i;

	AsignarElemento(1, 1, 1, A);
	printf("%d\n\n", ObtenerElemento(1, 1, A));
	Imprimir(A);
}

// Funciones para operaciones de matrices

#include <stdio.h>
#include <stdlib.h>

// Estructura de la matriz
typedef struct Node{
	int value;
	unsigned int cordX;
	struct Node *next;
	struct Node *last;
} node;

typedef struct Matriz{
	node *list;
	unsigned int cordY;
	struct Matriz *next;
	struct Matriz *last;
} matriz;

/* Devuelve el elemento de la fila i y la columna j de la matriz M */
int ObtenerElemento(unsigned int i, unsigned int j, matriz *M){
	if (!M)
		return -1;
	while (M->next && M->cordY < j)
		M = M->next;
	while (M->list->next && M->list->cordX < i)
		M->list = M->list->next;
	if (M->cordY == j && M->list->cordX == i)
		return M->list->value;
	return 0;
}

/* Asigna x al elemento de la fila i y la columna j de la matriz M */
matriz *AsignarElemento(unsigned int i, unsigned int j, int x, matriz *M){
	matriz *p = NULL;
	node *q = NULL;
	matriz *r = NULL;

	// Crear nuevo nodo
	if ((q = (node *)malloc(sizeof(node))) == NULL){
		printf("error en malloc\n");
		exit(1);
	}
	q->value = x;
	q->cordX = i;
	q->next = NULL;
	q->last = NULL;

	// Si M esta vacia
	if (!M){
		if ((M = (matriz *)malloc(sizeof(matriz))) == NULL){
			printf("error en malloc\n");
			exit(1);
		}
		M->cordY = j;
		M->next = NULL;
		M->last = M;
		M->list = q;
		M->list->last = q;
		return M;
	}

	// Si j esta fuera de la matriz
	if (M->last->cordY > j){
		// Crear nueva lista
		if ((r = (matriz *)malloc(sizeof(matriz))) == NULL){
			printf("error en malloc\n");
			exit(1);
		}
		// Asignar elemento
		r->cordY = j;
		r->list = q;
		M->last->next = r;
		M->last = r;
		return M;
	}

	// Si j esta dentro de la matriz
	p = M;
	while (p->next && p->cordY < j) // Recorrer lista
		p = p->next;
	while (p->list->next && p->list->cordX < i) // Recorrer lista en lista
		p->list = p->list->next;
	if (p->cordY == j && p->list->cordX == i){
		p->list->value = x;
		return M;
	}
	// Asignar elemento
	if (!p->next)
		p->list->last = q;
	q->next = p->list->next;
	p->list->next = q;
	q->last = p->list->last;
	return M;
}

/* Devuelve la matriz resultante de sumar M1 y M2, las matrices M1 y M2 deben tener la misma dimensión. */
matriz Sumar(M1, M2){
	;
}

/* Devuelve la matriz resultante de multiplicar M1 por el escalar e */
matriz ProductoPorEscalar(e, M){
	;
}

/* Devuelve la matriz resultante de multiplicar M1 y M2, 
 * el número de columnas de M1 debe ser igual al número de filas de M2. 
 * La matriz resultante tiene el mismo número de filas de M1 y 
 * el mismo número de columnas de M2. */
matriz Producto(M1, M2){
	;
}

/* Devuelve la transpuesta de M */
matriz Transponer(M){
	;
}

/* Muestra la matriz M */
void Imprimir(matriz *M){
	int i, j;
	matriz *p = M;
	i = j = 1;

	while (M->next){
		while (M->list->next){
			printf("%d ", ObtenerElemento(i, j, p));
			M->list = M->list->next;
			i++;
		}
		j++;
		M = M->next;
		printf("\n");
	}
}

void main(){
        matriz *A, *B, *C;
        A = B = C = NULL;
        int i;

	A = AsignarElemento(1, 1, 1, A);
	A = AsignarElemento(2, 2, 2, A);
	A = AsignarElemento(3, 3, 3, A);
        printf("numero: %d\n\n", ObtenerElemento(1, 1, A));
        Imprimir(A);
}

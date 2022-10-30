// Funciones para operaciones de matrices

#include <stdio.h>
#include <stdlib.h>

// Estructura de la matriz
typedef struct Node{
	int value;
	unsigned int cordX;
	struct Node *nextX;
} node;

typedef struct Matriz{
	node *list;
	unsigned int cordY;
	struct Matriz *nextY;
} matriz;

/* Devuelve el elemento de la fila i y la columna j de la matriz M */
int ObtenerElemento(unsigned int i, unsigned int j, matriz *M){
	if (!M)
		return -1;
	while (M->nextY && M->cordY < j) // Mover puntero por columna
		M = M->nextY;
	while (M->list->nextX && M->list->cordX < i) // Mover punetro por fila
		M->list = M->list->nextX;
	if (M->cordY == j && M->list->cordX == i)
		return M->list->value;
	return 0;
}

/* Asigna x al elemento de la fila i y la columna j de la matriz M */
matriz *AsignarElemento(unsigned int i, unsigned int j, int x, matriz *M, unsigned int size_x, unsigned int size_y){
	matriz *p = NULL;
	node *q = NULL;
	matriz *qp = NULL;

	// Validar tamano
	if (i > size_x || j > size_y){
		printf("Coordenada fuera de la matriz\n");
		exit(1);
	}

	// Crear nuevo nodo
	if((q = (node *)malloc(sizeof(node))) == NULL){
		printf("q: error en malloc\n");
		exit(1);
	}
	q->value = x;
	q->cordX = i;
	q->nextX = NULL;
	
	if((qp = (matriz *)malloc(sizeof(matriz))) == NULL){
		printf("qp: error en malloc\n");
		exit(1);
	}
	qp->list = q;
	qp->cordY = j;
	qp->nextY = NULL;

	// Si matriz no existe
	if (!M)
		return qp;
	p = M;
	// Mover puntero por columna
	while (p->cordY < j && p->nextY)
		p = p->nextY;
	
	// Insertar nuevo nodo en la columna
	if (p->cordY < j){
		qp->nextY = p->next;
		p->nextY = qp;
		return M;
	}
	
	// Mover puntero por fila
	while (p->list->cordX < i && p->list->nextX)
		p->list = p->list->nextX;
	
	//Insertar nuevo elemento en un nodo existente
	if (p->list->cordX == i && p->cordY == j){
		free(q);
		free(qp);
		p->list->value = x;
	}
	//Insertar nuevo nodo en la fila
	else{
		qp->list->nextX = p->list->nextX;
		p->list->nextX = qp->list;
	}
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
void Imprimir(matriz *M, unsigned int size_x, unsigned int size_y){
	int i = 1, j = 1, k = 0;

	for (j = 1; j <= size_y; j++){
		for (i = 1; i <= size_x; i++)
			printf("%d ", ObtenerElemento(i, j, M));
		printf("\n");
	}

}

void main(){
        matriz *A = NULL, *B = NULL, *C = NULL;
	unsigned int size_x = 5, size_y = 5;

	A = AsignarElemento(1, 1, 1, A, size_x, size_y);
	printf("numero: %d\n\n", ObtenerElemento(1, 1, A));
	
	A = AsignarElemento(2, 3, 2, A, size_x, size_y);
        printf("numero: %d\n\n", ObtenerElemento(2, 2, A));
	
	A = AsignarElemento(3, 2, 3, A, size_x, size_y);
        printf("numero: %d\n\n", ObtenerElemento(3, 3, A));
	
	A = AsignarElemento(1, 2, 4, A, size_x, size_y);
	printf("numero: %d\n\n", ObtenerElemento(1, 2, A));
	
	A = AsignarElemento(3, 1, 5, A, size_x, size_y);
        printf("numero: %d\n\n", ObtenerElemento(1, 3, A));
        
	Imprimir(A, size_x, size_y);
}

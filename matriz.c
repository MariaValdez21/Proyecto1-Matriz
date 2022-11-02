// Funciones para operaciones de matrices

#include <stdio.h>
#include <stdlib.h>

// Estructura de la matriz
typedef struct Node{
	float value;
	unsigned int cordX;
	struct Node *nextX;
} node;

typedef struct Matriz{
	node *list;
	unsigned int cordY;
	struct Matriz *nextY;
} matriz;

/* Devuelve el elemento de la fila i y la columna j de la matriz M */
float ObtenerElemento(unsigned int i, unsigned int j, matriz *M){
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
matriz *AsignarElemento(unsigned int i, unsigned int j, float x, matriz *M, unsigned int size_x, unsigned int size_y){
	matriz *p = NULL, *qp = NULL, *prevY = NULL;
	node *q = NULL, *prevX = NULL;

	// Validar tamano
	if (i > size_x || j > size_y){
		printf("Coordenada fuera de la matriz\n");
		exit(1);
	}

	// Crear nuevo nodo
	if ((q = (node *)malloc(sizeof(node))) == NULL){
		printf("q: error en malloc\n");
		exit(1);
	}
	q->value = x;
	q->cordX = i;
	q->nextX = NULL;
	
	if ((qp = (matriz *)malloc(sizeof(matriz))) == NULL){
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
	while (p->nextY && p->cordY < j){
		prevY = p;
		p = p->nextY;
	}
	// Insertar nodo en columna
	if (p->cordY != j){
		qp->nextY = p->nextY;
		if (!prevY)
			return M;
		p->nextY = qp;
		return M;
	}

	free(qp);
	// Mover puntero por fila
	while (p->list && p->list->cordX < i){
		p->list = p->list->nextX;
		prevX = p->list;
	}
	// Insertar nodo en fila
	if (p->list->cordX != i){
		q->nextX = p->list;
		if (!prevX)
			return M;
		prevX->nextX = q;
	return M;
	}
	free(q);
	p->list->value = x;
	return M;
}

/* Devuelve la matriz resultante de sumar M1 y M2, las matrices M1 y M2 deben tener la misma dimensión. */
matriz *Sumar(matriz *M1, matriz *M2, unsigned int size_x1, unsigned int size_y1, unsigned int size_x2, unsigned int size_y2){
	matriz *p = NULL;

	if (size_x1 != size_x2 || size_y1 != size_y2){
		printf("Las matrices M1 y M2 no tienen la misma dimensión\n");
		exit(1);
	}

	while (M1 || M2){
		while (M1->list || M2->list){
			//Sumar elementos
			if (M1->list->cordX == M2->list->cordX && M1->cordY == M2->cordY)
				p = AsignarElemento(M1->list->cordX, M1->cordY, M1->list->value + M2->list->value, p, size_x1, size_y1);
			else {
				if (M1->list)
					p = AsignarElemento(M1->list->cordX, M1->cordY, M1->list->value, p, size_x1, size_y1);
				if (M2->list)
					p = AsignarElemento(M2->list->cordX, M2->cordY, M2->list->value, p, size_x1, size_y1);
			}
			if (M1->list)
				M1->list = M1->list->nextX;
			if (M2->list)
				M2->list = M2->list->nextX;
		}
		if (M1)
			M1 = M1->nextY;
		if (M2)
			M2 = M2->nextY;
	}
	return p;
}

/* Devuelve la matriz resultante de multiplicar M1 por el escalar e */
matriz *ProductoPorEscalar(float e, matriz *M){
	matriz *p = M;
	
	while (p){ // Mover puntero por columna
		while (p->list){ // Mover punetro por fila
			p->list->value *= e;
			p->list = p->list->nextX;
		}
		p = p->nextY;
	}
	return M;
}

//* Devuelve la transpuesta de M */
matriz *Transponer(matriz *M, unsigned int size_x, unsigned int size_y){
	matriz *p = M, *q = NULL;

	//Mover puntero por fila cabecera
	while (p){
		//Mover puntero por columna
		while (p->list){
			q = AsignarElemento(p->cordY, p->list->cordX, p->list->value, q, size_y, size_x);
			p->list = p->list->nextX;
		}
		p = p->nextY;
	}
	return q;
}

/* Devuelve la matriz resultante de multiplicar M1 y M2, 
 * el número de columnas de M1 debe ser igual al número de filas de M2. 
 * La matriz resultante tiene el mismo número de filas de M1 y 
 * el mismo número de columnas de M2. */
matriz *Producto(matriz *M1, matriz *M2, unsigned int size_x1, unsigned int size_y1, unsigned int size_x2, unsigned int size_y2){
	matriz *p = NULL, *q = NULL, *r = NULL;
	int i, j;
	float h = 0;

	if (size_x1 != size_y2){
		printf("El número de columnas de M1 no es igual al número de filas de M2\n");
		exit(1);
	}
	
	M2 = Transponer(M2, size_x2, size_y2);
	for (j = 1; M1; j++){
		q = r = M2;
		for (i = 1; q->list; i++){
			while (q){
				while (q->list){
					h += M1->list->value * q->list->value;
					q->list = q->list->nextX;
				}
				// Multiplicar elementos
				p = AsignarElemento(i, j, h, p, size_x1, size_y1);
				M1->list = M1->list->nextX;
			}
			q = r->nextY;
		}
		M1 = M1->nextY;
	}
	return p;
}

/* Muestra la matriz M */
void Imprimir(matriz *M, unsigned int size_x, unsigned int size_y){
	int i = 1, j = 1, k = 0;

	for (j = 1; j <= size_y; j++){
		for (i = 1; i <= size_x; i++)
			printf("%f0.2 ", ObtenerElemento(i, j, M));
		printf("\n");
	}
	printf("\n");
}

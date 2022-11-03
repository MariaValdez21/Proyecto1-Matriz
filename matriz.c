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
	node *p = NULL;

	if (!M)
		return -1;
	while (M->nextY && M->cordY < j) // Mover puntero por columna
		M = M->nextY;
	p = M->list;
	while (p->nextX && p->cordX < i) // Mover punetro por fila
		p = p->nextX;
	if (M->cordY == j && p->cordX == i)
		return p->value;
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
	// Si cordenada es mayor a j
	if (p->cordY > j){
		qp->nextY = M;
		M = qp;
		return M;
	}

	prevY = p;
	// Mover puntero por columna
	while (p->nextY && p->cordY < j){
		p = p->nextY;
		prevY = p;
	}
	// Insertar nodo en columna
	if (p->cordY > j){
		qp->nextY = p->nextY;
		if (!prevY)
			return M;
		p->nextY = qp;
		return M;
	}

	free(qp);
	// Si coordenada es mayor a i
	if (p->list->cordX > i){
		q->nextX = p->list;
		p->list = q;
		return M;
	}
	// Mover puntero por fila
	prevX = p->list;
	while (prevX->nextX && prevX->nextX->cordX < i)
		prevX = prevX->nextX;
	if (prevX->cordX == i){
		free(q);
		p->list->value = x;
		return M;
	}
	// Insertar nodo en fila
	q->nextX = prevX->nextX;
	prevX->nextX = q;
	return M;
}

/* Devuelve la matriz resultante de sumar M1 y M2, las matrices M1 y M2 deben tener la misma dimensión. */
matriz *Sumar(matriz *M1, matriz *M2, unsigned int size_x1, unsigned int size_y1, unsigned int size_x2, unsigned int size_y2){
	matriz *p1 = M1, *p2 = M2, *qp = NULL;
	node *q1 = M1->list , *q2 = M2->list;

	if (size_x1 != size_x2 || size_y1 != size_y2){
		printf("Las matrices M1 y M2 no tienen la misma dimensión\n");
		exit(1);
	}

	while (p1 || p2){
		while (q1 || q2){
			//Sumar elementos
			if (q1->cordX == q2->cordX && p1->cordY == p2->cordY)
				qp = AsignarElemento(q1->cordX, p1->cordY, q1->value + q2->value, qp, size_x1, size_y1);
			else {
				if (p1)
					qp = AsignarElemento(q1->cordX, p1->cordY, q1->value, qp, size_x1, size_y1);
				if (p2)
					qp = AsignarElemento(q2->cordX, p2->cordY, q2->value, qp, size_x1, size_y1);
			}
			if (q1)
				q1 = q1->nextX;
			if (q2)
				q2 = q2->nextX;
		}
		if (p1)
			p1 = p1->nextY;
		if (p2)
			p2 = p2->nextY;
	}
	return qp;
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
	matriz *p = M, *qp = NULL;
	node *q = NULL;

	//Mover puntero por fila cabecera
	while (p){
		q = p->list;
		//Mover puntero por columna
		while (q){
			qp = AsignarElemento(p->cordY, q->cordX, q->value, qp, size_y, size_x);
			q = q->nextX;
		}
		p = p->nextY;
	}
	return qp;
}

/* Devuelve la matriz resultante de multiplicar M1 y M2, 
 * el número de columnas de M1 debe ser igual al número de filas de M2. 
 * La matriz resultante tiene el mismo número de filas de M1 y 
 * el mismo número de columnas de M2. */
matriz *Producto(matriz *M1, matriz *M2, unsigned int size_x1, unsigned int size_y1, unsigned int size_x2, unsigned int size_y2){
	matriz *p1 = M1, *p2 = NULL, *qp = NULL,  *r = NULL;
	node *q1 = NULL, *q2 = NULL;
	int i = 1, j = 1;
	float h = 0;

	if (size_x1 != size_y2){
		printf("El número de columnas de M1 no es igual al número de filas de M2\n");
		exit(1);
	}
	
	p2 = Transponer(M2, size_x2, size_y2);
	while (p1){
		r = p2;
		for (i = 1; q2; i++){
			while (r){
				while (q2){
					h += q1->value * q2->value;
					q2 = q2->nextX;
				}
				// Multiplicar elementos
				qp = AsignarElemento(i, j, h, qp, size_x1, size_y1);
				q1 = q1->nextX;
			}
			r = r->nextY;
			q2 = r->list;
		}
		p1 = p1->nextY;
	}
	return qp;
}

/* Muestra la matriz M */
void Imprimir(matriz *M, unsigned int size_x, unsigned int size_y){
	int i = 1, j = 1;

	for (j = 1; j <= size_y; j++){
		for (i = 1; i <= size_x; i++)
			printf("%f0.2 ", ObtenerElemento(i, j, M));
		printf("\n");
	}
	printf("\n");
}
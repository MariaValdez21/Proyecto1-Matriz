// Libreria de operaciones de matrices
// Estructura de la matriz
typedef struct Node{
	float value;
	unsigned int cordX;
	struct node *next;
} node;

typedef struct Matriz{
	node *list;
	unsigned int cordY;
	struct Matriz *next;
} matriz;

/* Devuelve el elemento de la fila i y la columna j de la matriz M */
float ObtenerElemento(unsigned int i, unsigned int j, matriz *M);

/* Asigna x al elemento de la fila i y la columna j de la matriz M */
matriz *AsignarElemento(unsigned int i, unsigned int j, int x, matriz *M, unsigned int size_x, unsigned int size_y);

/* Devuelve la matriz resultante de sumar M1 y M2, las matrices M1 y M2 deben tener la misma dimensión. */
matriz *Sumar(matriz *M1, matriz *M2, unsigned int size_x1, unsigned int size_y1, unsigned int size_x2, unsigned int size_y2);

/* Devuelve la matriz resultante de multiplicar M1 por el escalar e */
matriz *ProductoPorEscalar(float e, matriz *M);

/* Devuelve la transpuesta de M */
matriz *Transponer(matriz *M, unsigned int size_x, unsigned int size_y);

/* Devuelve la matriz resultante de multiplicar M1 y M2,
 * el número de columnas de M1 debe ser igual al número de filas de M2.
 * La matriz resultante tiene el mismo número de filas de M1 y
 * el mismo número de columnas de M2. */
matriz *Producto(matriz *M1, matriz *M2, unsigned int size_x1, unsigned int size_y1, unsigned int size_x2, unsigned int size_y2);

/* Muestra la matriz M */
void Imprimir(matriz *M, unsigned int size_x, unsigned int size_y);

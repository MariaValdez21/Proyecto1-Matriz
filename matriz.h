// Libreria de operaciones de matrices

// Estructura de la matriz
typedef struct Node{
        int value;
	unsigned int cordY;
        struct node *next;
        struct node *last;
} node;

typedef struct Matriz{
        node *list;
        unsigned int cordX;
        struct Matriz *next;
        struct Matriz *last;
} matriz;

/* Devuelve el elemento de la fila i y la columna j de la matriz M */
int ObtenerElemento(unsigned int i, unsigned int j, matriz *M);

/* Asigna x al elemento de la fila i y la columna j de la matriz M */
matriz *AsignarElemento(unsigned int i, unsigned int j, int x, matriz *M);

/* Devuelve la matriz resultante de sumar M1 y M2, las matrices M1 y M2 deben tener la misma dimensión. */
matriz Sumar(matriz *M1, matriz *M2);

/* Devuelve la matriz resultante de multiplicar M1 por el escalar e */
matriz ProductoPorEscalar(int e, matriz *M);

/* Devuelve la matriz resultante de multiplicar M1 y M2,
 * el número de columnas de M1 debe ser igual al número de filas de M2.
 * La matriz resultante tiene el mismo número de filas de M1 y
 * el mismo número de columnas de M2. */
matriz Producto(matriz *M1, matriz *M2);

/* Devuelve la transpuesta de M */
matriz Transponer(matriz *M);

/* Muestra la matriz M */
void Imprimir(matriz *M);

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXCAR 25

typedef char tString[MAXCAR];

typedef struct {
    int codigo;
    tString nombre;
} tColor;


typedef struct nodoColor {
    tColor color;
    struct nodoColor *siguiente;
} tListaColores;


bool listaVacia(tListaColores *);
void insertarColor(tListaColores **, int, const char *);
void mostrarColoresRecursivo(tListaColores *);
void mostrarColores(tListaColores *);


int main() {
    tListaColores *lista = NULL; 

    printf("--- PRUEBA 1: LISTA VACIA ---\n");
    mostrarColores(lista);

    printf("\n--- CARGANDO ELEMENTOS EN LA LISTA ---\n");
    insertarColor(&lista, 1, "Rojo");
    insertarColor(&lista, 2, "Amarillo");
    insertarColor(&lista, 3, "Verde");

    printf("\n--- PRUEBA 2: LISTA CON ELEMENTOS ---\n");
    mostrarColores(lista);

    return 0;
}

bool listaVacia(tListaColores *pListaColores) {
    return (pListaColores == NULL);
}


void mostrarColoresRecursivo(tListaColores *pListaColores) {
    
    if (pListaColores == NULL) {
        return;
    }

   
    printf("%d - %s\n", pListaColores->color.codigo, pListaColores->color.nombre);

   
    mostrarColoresRecursivo(pListaColores->siguiente);
}

void mostrarColores(tListaColores *pListaColores) {
    if (listaVacia(pListaColores)) {
        printf("No hay colores para mostrar en la lista\n");
    } else {
        printf("*** Lista de colores ***\n");
        mostrarColoresRecursivo(pListaColores);
    }
}

void insertarColor(tListaColores **pListaColores, int pCodigo, const char *pNombre) {
    tListaColores *nuevoNodo = (tListaColores *) malloc(sizeof(tListaColores));
    nuevoNodo->color.codigo = pCodigo;
    strcpy(nuevoNodo->color.nombre, pNombre);
    nuevoNodo->siguiente = NULL;

    if (*pListaColores == NULL) {
        *pListaColores = nuevoNodo;
    } else {
        tListaColores *aux = *pListaColores;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevoNodo;
    }
}

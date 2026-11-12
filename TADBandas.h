#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define N 150

//Tipos de datos definidos por el usuario:
typedef char tString[N];

typedef struct{
	int entradasCampoGeneral;
	int entradasCampoDelantero;
	int entradasTribunasIzq;
	int entradasTribunasDer;
}tEntradas;

typedef struct{
	tString nombreMerch;
	int cantDisponible;
	float precio;
}tMerch;

typedef struct{
	tString nombreBanda;
	tString fechaShow;
	tString genero;
	tString tracklist[N];
	tEntradas entDisponibles;
	tMerch merchDisponible[N];
	int merchTotal;
}tBanda;

typedef struct nodo{
	tBanda unaBanda;
	struct nodo* siguiente;
}tNodo;

typedef tNodo* tLista;

//Interfaz:
void inicializarLista(tLista*);
bool listaVacia(tLista);
tBanda cargarDatosBanda();
void agregarBanda(tLista*, tBanda);
void quitarPrimeraBanda(tLista*);
void quitarBandaPorNombre(tLista*, tString);
bool buscarUnaBanda(tLista, tString);
void todasLasBandas(tLista);

//Implementacion:
void inicializarLista(tLista* pLista){
	*pLista = NULL;
}
bool listaVacia(tLista pLista){
	return  pLista == NULL;
}
tBanda cargarDatosBanda(){
	tBanda nuevo;
	int i, j;
	int cantCanciones;
	int cantMercancia;
	int merchTotal = 0;
	
	printf("\n===== INFO GENERAL DEL GRUPO =====\n");
	printf("\nBANDA: ");
	scanf("%s", nuevo.nombreBanda);
	fflush(stdin);
	
	printf("\nFECHA DEL SHOW: ");
	scanf("%s", nuevo.fechaShow);
	fflush(stdin);
	
	printf("\n===== TRACKLIST DEL CONCIERTO ===== \n");
	printf("\nCuantas canciones tocará el grupo? ");
	scanf("%d", &cantCanciones);
	for (i = 0; i < cantCanciones; i++){
		printf("%d. ", i+1);
		scanf("%s", nuevo.tracklist[i]);
		fflush(stdin);
		printf("\n");
	}
	
	printf("\n===== GESTION DE ENTRADAS =====\n");
	printf("\nEntradas en campo general: ");
	scanf("%d", &nuevo.entDisponibles.entradasCampoGeneral);
	
	printf("\nEntradas en campo delantero: ");
	scanf("%d", &nuevo.entDisponibles.entradasCampoDelantero);
	
	printf("\nEntradas en tribunas izquierdas: ");
	scanf("%d", &nuevo.entDisponibles.entradasTribunasIzq);
	
	printf("\nEntradas en tribunas derechas: ");
	scanf("%d", &nuevo.entDisponibles.entradasTribunasDer);
	
	
	printf("\n===== GESTION DE MERCANCIA DE LA BANDA =====\n");
	printf("\nCuantos objetos de mercancia ofrece la banda? ");
	scanf("%d", &cantMercancia);
	for (j = 0; j < cantMercancia; j++){
		printf("\nProducto %d:\n", j+1);
		printf("Nombre: ");
		scanf("%s", nuevo.merchDisponible[j].nombreMerch);
		fflush(stdin);
		
		printf("\nCantidad disponible del producto: ");
		scanf("%d", &nuevo.merchDisponible[j].cantDisponible);
		
		merchTotal = merchTotal + nuevo.merchDisponible[j].cantDisponible;
		
		printf("\nPrecio: $");		
		scanf("%f", &nuevo.merchDisponible[j].precio);
		printf("\n");
	}
	
	nuevo.merchTotal = merchTotal;
	printf("\nCantidad total de mercancia disponible: %d", nuevo.merchTotal);
	
	return nuevo;
}
void agregarBanda(tLista* pLista, tBanda pBanda){
	tLista nuevoGrupo = (tLista)malloc(sizeof(tNodo));
	if (nuevoGrupo != NULL){
		nuevoGrupo->unaBanda = pBanda;
		nuevoGrupo->siguiente = *pLista;
		*pLista = nuevoGrupo;
		
		printf("\nBanda registrada con exito!\n");
	}else{
		printf("\nHa ocurrido un error al momento de reservar memoria\n");
	}
}
void quitarPrimeraBanda(tLista* pLista){
	if (!listaVacia(*pLista)){
		tLista aEliminar = *pLista;
		*pLista = aEliminar->siguiente;
		free(aEliminar);
	
		printf("\nPrimera banda quitada!\n");
	}else{
		printf("\nNo hay bandas para quitar");
	}
}
void quitarBandaPorNombre(tLista* pLista, tString bandaBuscada){	
	if (listaVacia(*pLista)){
		printf("\nNo hay ninguna banda registrada. No se puede eliminar nada\n");
	}else{
			
		if (strcmp((*pLista)->unaBanda.nombreBanda, bandaBuscada) == 0){
			quitarPrimeraBanda(pLista);
			
		}else{		
			bool encontrado = false;
			tLista aux = (*pLista)->siguiente;
			tLista anterior = *pLista;
			tLista aEliminar;
			while (aux != NULL && !encontrado){
				if (strcmp(aux->unaBanda.nombreBanda, bandaBuscada) == 0){
					aEliminar = aux;
					encontrado = true;
				}else{
					anterior = aux;
					aux = aux->siguiente;
				}
				
				if (encontrado){
					anterior->siguiente = aEliminar->siguiente;	
					free(aEliminar);
					printf("\nLa banda ha sido retirada de la lista\n");
			
				}else{
					printf("\nNo se encontró la banda buscada\n");
				}
			}
		}	
	}
}
bool buscarUnaBanda(tLista pLista, tString bandaBuscada){
	if(listaVacia(pLista)){
		printf("\nNo hay ninguna banda registrada\n");
		return false;
	}else{
		tLista aux = pLista;
		
		while (aux != NULL){
			if (strcmp(aux->unaBanda.nombreBanda, bandaBuscada) == 0){
				return true;
			}else{
				aux = aux->siguiente;
			}
		}
		printf("\nNo se encuentro la banda");
		return false;
	}
}
void todasLasBandas(tLista pLista){
	if (listaVacia(pLista)){
		printf("\nNo hay ninguna banda registrada para mostrar\n");
	}else{
		tLista aux = pLista;
		printf("\n===== TODAS LAS BANDAS DEL FESTIVAL =====\n");
		while (aux != NULL){
			printf("\nNombre de la banda: %s", aux->unaBanda.nombreBanda);
			printf("\nFecha del concierto: %s", aux->unaBanda.fechaShow);
			printf("\nStock total de merch: %d", aux->unaBanda.merchTotal);
			printf("\n--------------------------------------\n");
			
			aux = aux->siguiente;
		}
	}
}

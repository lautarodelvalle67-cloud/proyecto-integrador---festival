#include "TADBandas.h"

int main(){
	tLista lista;
	tBanda bandaActual;
	int opcion;
	int opcion2;
	tString bandaBuscada;
	tString bandaBuscada2;
	
	inicializarLista(&lista);
	
	do {
		
	
		printf("\n===== MENU DE OPCIONES =====\n");
		printf("\n1. Registrar una banda");
		printf("\n2. Quitar una banda");
		printf("\n3. Buscar una banda");
		printf("\n4. Mostrar todas las bandas");
		printf("\n0. Salir del programa");
		printf("\nSeleccione una opcion...");
		scanf("%d", &opcion);
	
		switch (opcion){
		
			case 1:{
				tBanda aRegistrar = cargarDatosBanda();
				agregarBanda(&lista, aRegistrar);
				break;
			}
			
			case 2:
				printf("\nDe que forma desea quitar una banda?(1- por nombre / 2- primera banda)");
				scanf("%d", &opcion2);
				if (opcion2 == 1){
					printf("\nIngrese el nombre de la banda que desea quitar: ");
					scanf("%s", bandaBuscada);
					quitarBandaPorNombre(&lista, bandaBuscada);
				}else{
					quitarPrimeraBanda(&lista);
				}
				break;
				
			case 3:
				printf("\nIngrese el nombre de la banda que desea ubicar: ");
				fflush(stdin);
				scanf("%s", bandaBuscada2);
				fflush(stdin);
				
				bool bandaAMostrar = buscarUnaBanda(lista, bandaBuscada2);
				
				if (bandaAMostrar == true){
					printf("\nLa banda si esta registrada!");
				}else{
					printf("\nLa banda no esta registrada en la lista");
				}
				break;
			
			case 4:
				todasLasBandas(lista);
				break;
			
			case 0:
				printf("\nSaliendo del programa...");
				break;
			
			default:
				printf("\nOpcion invalida. Porfavor pruebe otra vez");
				break;			
		}
	}while (opcion != 0);
	return 0;
}

  


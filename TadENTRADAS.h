#ifndef TADENTRADAS_H
#define TADENTRADAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 150
#define MAX_BANDAS 50
#define CANT_SECTORES 6

typedef char tCadena[MAX_NOMBRE];

typedef struct {
    float campoGeneral;
    float campoDelantero;
    float tribunaIzqInferior;
    float tribunaIzqSuperior;
    float tribunaDerInferior;
    float tribunaDerSuperior;
    bool preciosCargados;
} tPrecios;

/* ABB para cada tribuna: ordena por codigo de ubicacion (inferior < superior) */
typedef struct nodoAbb {
    int codigoSector;
    tCadena descripcion;
    bool esSuperior;
    float precio;
    int vendidas;
    struct nodoAbb *izq;
    struct nodoAbb *der;
} tNodoAbb;

typedef tNodoAbb *tArbolTribuna;

typedef struct {
    tCadena nombreBanda;
    int cantCampoGeneral;
    int cantCampoDelantero;
    int cantTribunaIzqInf;
    int cantTribunaIzqSup;
    int cantTribunaDerInf;
    int cantTribunaDerSup;
    int totalEntradas;
    float dineroRecaudado;
} tRegistroBanda;

typedef struct {
    tCadena nombreSector;
    int entradasVendidas;
    float recaudacion;
} tSectorRanking;

typedef struct {
    tPrecios precios;
    tArbolTribuna arbolIzq;
    tArbolTribuna arbolDer;
    tRegistroBanda bandas[MAX_BANDAS];
    int cantBandas;
    int totalAmbosCampos;
    int totalGeneralEntradas;
    float recaudacionTotal;
} tTADEntradas;

/* Prototipos */
void inicializarTADEntradas(tTADEntradas *pEntradas);
void asignarPrecios(tTADEntradas *pEntradas);
tArbolTribuna insertarEnArbol(tArbolTribuna pArbol, int pCodigo, tCadena pDesc, bool pSuperior, float pPrecio);
void armarArboles(tTADEntradas *pEntradas);
void cargarEntradasBanda(tTADEntradas *pEntradas);
void mostrarTotalesYArboles(tTADEntradas pEntradas);
void mostrarSectorMasVendido(tTADEntradas pEntradas);
void liberarArbol(tArbolTribuna *pArbol);
void liberarTADEntradas(tTADEntradas *pEntradas);

/* Implementacion */
void inicializarTADEntradas(tTADEntradas *pEntradas) {
    pEntradas->precios.campoGeneral = 0.0;
    pEntradas->precios.campoDelantero = 0.0;
    pEntradas->precios.tribunaIzqInferior = 0.0;
    pEntradas->precios.tribunaIzqSuperior = 0.0;
    pEntradas->precios.tribunaDerInferior = 0.0;
    pEntradas->precios.tribunaDerSuperior = 0.0;
    pEntradas->precios.preciosCargados = false;

    pEntradas->arbolIzq = NULL;
    pEntradas->arbolDer = NULL;
    pEntradas->cantBandas = 0;
    pEntradas->totalAmbosCampos = 0;
    pEntradas->totalGeneralEntradas = 0;
    pEntradas->recaudacionTotal = 0.0;
}

tArbolTribuna insertarEnArbol(tArbolTribuna pArbol, int pCodigo, tCadena pDesc, bool pSuperior, float pPrecio) {
    tArbolTribuna nuevoNodo;

    if (pArbol == NULL) {
        nuevoNodo = (tArbolTribuna) malloc(sizeof(tNodoAbb));
        if (nuevoNodo != NULL) {
            nuevoNodo->codigoSector = pCodigo;
            strcpy(nuevoNodo->descripcion, pDesc);
            nuevoNodo->esSuperior = pSuperior;
            nuevoNodo->precio = pPrecio;
            nuevoNodo->vendidas = 0;
            nuevoNodo->izq = NULL;
            nuevoNodo->der = NULL;
        }
        return nuevoNodo;
    } else {
        if (pCodigo < pArbol->codigoSector) {
            pArbol->izq = insertarEnArbol(pArbol->izq, pCodigo, pDesc, pSuperior, pPrecio);
        } else {
            if (pCodigo > pArbol->codigoSector) {
                pArbol->der = insertarEnArbol(pArbol->der, pCodigo, pDesc, pSuperior, pPrecio);
            }
        }
        return pArbol;
    }
}

void armarArboles(tTADEntradas *pEntradas) {
    tCadena descInfIzq = "Mitad inferior (mas lejos, mas barata)";
    tCadena descSupIzq = "Mitad superior (mas cerca, mas cara)";
    tCadena descInfDer = "Mitad inferior (mas lejos, mas barata)";
    tCadena descSupDer = "Mitad superior (mas cerca, mas cara)";

    liberarArbol(&(pEntradas->arbolIzq));
    liberarArbol(&(pEntradas->arbolDer));

    pEntradas->arbolIzq = insertarEnArbol(pEntradas->arbolIzq, 1, descInfIzq, false, pEntradas->precios.tribunaIzqInferior);
    pEntradas->arbolIzq = insertarEnArbol(pEntradas->arbolIzq, 2, descSupIzq, true, pEntradas->precios.tribunaIzqSuperior);

    pEntradas->arbolDer = insertarEnArbol(pEntradas->arbolDer, 1, descInfDer, false, pEntradas->precios.tribunaDerInferior);
    pEntradas->arbolDer = insertarEnArbol(pEntradas->arbolDer, 2, descSupDer, true, pEntradas->precios.tribunaDerSuperior);
}

void asignarPrecios(tTADEntradas *pEntradas) {
    printf("\n--- ASIGNAR PRECIOS POR SECTOR ---\n");

    printf("Precio Campo General: $");
    scanf("%f", &(pEntradas->precios.campoGeneral));

    printf("Precio Campo Delantero: $");
    scanf("%f", &(pEntradas->precios.campoDelantero));

    printf("Precio Tribuna Izquierda - Inferior (lejos/barata): $");
    scanf("%f", &(pEntradas->precios.tribunaIzqInferior));

    printf("Precio Tribuna Izquierda - Superior (cerca/cara): $");
    scanf("%f", &(pEntradas->precios.tribunaIzqSuperior));

    printf("Precio Tribuna Derecha - Inferior (lejos/barata): $");
    scanf("%f", &(pEntradas->precios.tribunaDerInferior));

    printf("Precio Tribuna Derecha - Superior (cerca/cara): $");
    scanf("%f", &(pEntradas->precios.tribunaDerSuperior));

    pEntradas->precios.preciosCargados = true;
    armarArboles(pEntradas);

    printf("\nPrecios guardados y tribunas armadas en ABB.\n");
}

static void sumarVendidasEnArbol(tArbolTribuna pArbol, bool pSuperior, int pCant) {
    if (pArbol != NULL) {
        if (pArbol->esSuperior == pSuperior) {
            pArbol->vendidas = pArbol->vendidas + pCant;
        }
        sumarVendidasEnArbol(pArbol->izq, pSuperior, pCant);
        sumarVendidasEnArbol(pArbol->der, pSuperior, pCant);
    }
}

static void recorrerInOrden(tArbolTribuna pArbol) {
    if (pArbol != NULL) {
        recorrerInOrden(pArbol->izq);
        printf("  Codigo %d | %s | Precio: $%.2f | Vendidas: %d\n",
               pArbol->codigoSector, pArbol->descripcion, pArbol->precio, pArbol->vendidas);
        recorrerInOrden(pArbol->der);
    }
}

void cargarEntradasBanda(tTADEntradas *pEntradas) {
    tRegistroBanda reg;
    float totalDineroBanda;

    if (pEntradas->precios.preciosCargados == false) {
        printf("\nPrimero tenes que asignar los precios de cada sector.\n");
    } else {
        if (pEntradas->cantBandas >= MAX_BANDAS) {
            printf("\nNo se pueden cargar mas bandas.\n");
        } else {
            printf("\n--- CARGAR ENTRADAS VENDIDAS POR BANDA ---\n");
            printf("Nombre de la banda: ");
            fflush(stdin);
            scanf("%s", reg.nombreBanda);

            printf("Entradas Campo General: ");
            scanf("%d", &(reg.cantCampoGeneral));

            printf("Entradas Campo Delantero: ");
            scanf("%d", &(reg.cantCampoDelantero));

            printf("Entradas Tribuna Izquierda - Inferior: ");
            scanf("%d", &(reg.cantTribunaIzqInf));

            printf("Entradas Tribuna Izquierda - Superior: ");
            scanf("%d", &(reg.cantTribunaIzqSup));

            printf("Entradas Tribuna Derecha - Inferior: ");
            scanf("%d", &(reg.cantTribunaDerInf));

            printf("Entradas Tribuna Derecha - Superior: ");
            scanf("%d", &(reg.cantTribunaDerSup));

            reg.totalEntradas = reg.cantCampoGeneral + reg.cantCampoDelantero +
                                reg.cantTribunaIzqInf + reg.cantTribunaIzqSup +
                                reg.cantTribunaDerInf + reg.cantTribunaDerSup;

            totalDineroBanda = (reg.cantCampoGeneral * pEntradas->precios.campoGeneral) +
                               (reg.cantCampoDelantero * pEntradas->precios.campoDelantero) +
                               (reg.cantTribunaIzqInf * pEntradas->precios.tribunaIzqInferior) +
                               (reg.cantTribunaIzqSup * pEntradas->precios.tribunaIzqSuperior) +
                               (reg.cantTribunaDerInf * pEntradas->precios.tribunaDerInferior) +
                               (reg.cantTribunaDerSup * pEntradas->precios.tribunaDerSuperior);

            reg.dineroRecaudado = totalDineroBanda;

            pEntradas->bandas[pEntradas->cantBandas] = reg;
            pEntradas->cantBandas = pEntradas->cantBandas + 1;

            pEntradas->totalAmbosCampos = pEntradas->totalAmbosCampos + reg.cantCampoGeneral + reg.cantCampoDelantero;
            pEntradas->totalGeneralEntradas = pEntradas->totalGeneralEntradas + reg.totalEntradas;
            pEntradas->recaudacionTotal = pEntradas->recaudacionTotal + totalDineroBanda;

            sumarVendidasEnArbol(pEntradas->arbolIzq, false, reg.cantTribunaIzqInf);
            sumarVendidasEnArbol(pEntradas->arbolIzq, true, reg.cantTribunaIzqSup);
            sumarVendidasEnArbol(pEntradas->arbolDer, false, reg.cantTribunaDerInf);
            sumarVendidasEnArbol(pEntradas->arbolDer, true, reg.cantTribunaDerSup);

            printf("\nBanda %s -> Entradas: %d | Recaudado: $%.2f\n",
                   reg.nombreBanda, reg.totalEntradas, reg.dineroRecaudado);
        }
    }
}

void mostrarTotalesYArboles(tTADEntradas pEntradas) {
    int i;

    printf("\n--- RESUMEN GENERAL DE ENTRADAS ---\n");
    printf("Total entradas en ambos campos: %d\n", pEntradas.totalAmbosCampos);
    printf("Total entradas vendidas en general: %d\n", pEntradas.totalGeneralEntradas);
    printf("Dinero total recaudado por entradas: $%.2f\n", pEntradas.recaudacionTotal);

    if (pEntradas.precios.preciosCargados == true) {
        printf("\nTribuna Izquierda (ABB):\n");
        recorrerInOrden(pEntradas.arbolIzq);

        printf("\nTribuna Derecha (ABB):\n");
        recorrerInOrden(pEntradas.arbolDer);
    }

    printf("\nDetalle por banda:\n");
    for (i = 0; i < pEntradas.cantBandas; i++) {
        printf("Banda: %s | Total entradas: %d | Recaudado: $%.2f\n",
               pEntradas.bandas[i].nombreBanda,
               pEntradas.bandas[i].totalEntradas,
               pEntradas.bandas[i].dineroRecaudado);
        printf("  Campo Gral: %d | Campo Del: %d\n",
               pEntradas.bandas[i].cantCampoGeneral,
               pEntradas.bandas[i].cantCampoDelantero);
        printf("  Trib Izq (Inf/Sup): %d / %d | Trib Der (Inf/Sup): %d / %d\n",
               pEntradas.bandas[i].cantTribunaIzqInf,
               pEntradas.bandas[i].cantTribunaIzqSup,
               pEntradas.bandas[i].cantTribunaDerInf,
               pEntradas.bandas[i].cantTribunaDerSup);
    }
}

void mostrarSectorMasVendido(tTADEntradas pEntradas) {
    tSectorRanking ranking[CANT_SECTORES];
    tSectorRanking aux;
    int i;
    int j;
    int posMayor;

    for (i = 0; i < CANT_SECTORES; i++) {
        ranking[i].entradasVendidas = 0;
        ranking[i].recaudacion = 0.0;
    }

    strcpy(ranking[0].nombreSector, "Campo General");
    strcpy(ranking[1].nombreSector, "Campo Delantero");
    strcpy(ranking[2].nombreSector, "Tribuna Izquierda Inferior");
    strcpy(ranking[3].nombreSector, "Tribuna Izquierda Superior");
    strcpy(ranking[4].nombreSector, "Tribuna Derecha Inferior");
    strcpy(ranking[5].nombreSector, "Tribuna Derecha Superior");

    for (i = 0; i < pEntradas.cantBandas; i++) {
        ranking[0].entradasVendidas = ranking[0].entradasVendidas + pEntradas.bandas[i].cantCampoGeneral;
        ranking[0].recaudacion = ranking[0].recaudacion + (pEntradas.bandas[i].cantCampoGeneral * pEntradas.precios.campoGeneral);

        ranking[1].entradasVendidas = ranking[1].entradasVendidas + pEntradas.bandas[i].cantCampoDelantero;
        ranking[1].recaudacion = ranking[1].recaudacion + (pEntradas.bandas[i].cantCampoDelantero * pEntradas.precios.campoDelantero);

        ranking[2].entradasVendidas = ranking[2].entradasVendidas + pEntradas.bandas[i].cantTribunaIzqInf;
        ranking[2].recaudacion = ranking[2].recaudacion + (pEntradas.bandas[i].cantTribunaIzqInf * pEntradas.precios.tribunaIzqInferior);

        ranking[3].entradasVendidas = ranking[3].entradasVendidas + pEntradas.bandas[i].cantTribunaIzqSup;
        ranking[3].recaudacion = ranking[3].recaudacion + (pEntradas.bandas[i].cantTribunaIzqSup * pEntradas.precios.tribunaIzqSuperior);

        ranking[4].entradasVendidas = ranking[4].entradasVendidas + pEntradas.bandas[i].cantTribunaDerInf;
        ranking[4].recaudacion = ranking[4].recaudacion + (pEntradas.bandas[i].cantTribunaDerInf * pEntradas.precios.tribunaDerInferior);

        ranking[5].entradasVendidas = ranking[5].entradasVendidas + pEntradas.bandas[i].cantTribunaDerSup;
        ranking[5].recaudacion = ranking[5].recaudacion + (pEntradas.bandas[i].cantTribunaDerSup * pEntradas.precios.tribunaDerSuperior);
    }

    for (i = 0; i < CANT_SECTORES - 1; i++) {
        posMayor = i;
        for (j = i + 1; j < CANT_SECTORES; j++) {
            if (ranking[j].entradasVendidas > ranking[posMayor].entradasVendidas) {
                posMayor = j;
            }
        }
        if (posMayor != i) {
            aux = ranking[i];
            ranking[i] = ranking[posMayor];
            ranking[posMayor] = aux;
        }
    }

    printf("\n--- SECTORES ORDENADOS POR CANTIDAD VENDIDA ---\n");
    for (i = 0; i < CANT_SECTORES; i++) {
        printf("%d. %s -> %d entradas ($%.2f)\n",
               i + 1, ranking[i].nombreSector, ranking[i].entradasVendidas, ranking[i].recaudacion);
    }
    printf("\nSector que vendio mas entradas: %s (%d entradas)\n",
           ranking[0].nombreSector, ranking[0].entradasVendidas);
}

void liberarArbol(tArbolTribuna *pArbol) {
    if (*pArbol != NULL) {
        liberarArbol(&((*pArbol)->izq));
        liberarArbol(&((*pArbol)->der));
        free(*pArbol);
        *pArbol = NULL;
    }
}

void liberarTADEntradas(tTADEntradas *pEntradas) {
    liberarArbol(&(pEntradas->arbolIzq));
    liberarArbol(&(pEntradas->arbolDer));
}

#endif
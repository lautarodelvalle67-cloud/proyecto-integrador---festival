#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CADENA 150
#define MAX_PRODUCTOS 50
#define MAX_BANDAS 50


typedef char tCadena[MAX_CADENA];

typedef struct {
    tCadena nombreProducto;
    int cantidadDisponible;
    int cantidadVendida;
    float precioUnitario;
    float subtotalRecaudado;
} tProductoMerch;

typedef struct {
    tCadena nombreBanda;
    tProductoMerch listaProductos[MAX_PRODUCTOS];
    int cantidadProductos;
    int totalUnidadesVendidasBanda;
    float totalRecaudadoBanda;
} tBandaMerch;

typedef struct {
    tBandaMerch listaBandas[MAX_BANDAS];
    int cantidadBandas;
    int totalUnidadesVendidasFestival;
    float recaudacionTotalMerchFestival;
} tOrganizacion;


void inicializarOrganizacion(tOrganizacion *pOrganizacion);
void cargarCatalogoMerchBanda(tOrganizacion *pOrganizacion);
void buscarBandaPorNombre(tOrganizacion pOrganizacion, tCadena pNombreBandaBuscada, int *pPosicionBanda);
void buscarProductoPorNombre(tBandaMerch pBanda, tCadena pNombreProductoBuscado, int *pPosicionProducto);
void ordenarProductosPorCantidadVendida(tProductoMerch pArregloProductos[], int pCantidadProductos);
void mostrarProductoMasVendido(tBandaMerch pBanda);
void registrarVentasMerch(tOrganizacion *pOrganizacion);
void mostrarResumenOrganizacion(tOrganizacion pOrganizacion);
void escribirSeccionMerchBanda(FILE *pArchivoInforme, tOrganizacion pOrganizacion, tCadena pNombreBanda, float *pGananciaMerchBanda);


void inicializarOrganizacion(tOrganizacion *pOrganizacion) {
    pOrganizacion->cantidadBandas = 0;
    pOrganizacion->totalUnidadesVendidasFestival = 0;
    pOrganizacion->recaudacionTotalMerchFestival = 0.0;
}

void cargarCatalogoMerchBanda(tOrganizacion *pOrganizacion) {
    int indiceBanda;
    int indiceProducto;
    int cantidadProductosCargar;

    if (pOrganizacion->cantidadBandas >= MAX_BANDAS) {
        printf("\n[Error] Se alcanzo el limite maximo de bandas en organizacion.\n");
    } else {
        indiceBanda = pOrganizacion->cantidadBandas;

        printf("\n===== CARGA DE MERCHANDISING DE BANDA =====\n");
        printf("Nombre de la banda: ");
        fflush(stdin);
        scanf("%s", pOrganizacion->listaBandas[indiceBanda].nombreBanda);

        pOrganizacion->listaBandas[indiceBanda].totalUnidadesVendidasBanda = 0;
        pOrganizacion->listaBandas[indiceBanda].totalRecaudadoBanda = 0.0;

        printf("Cuantos productos de merch ofrece %s?: ", pOrganizacion->listaBandas[indiceBanda].nombreBanda);
        scanf("%d", &cantidadProductosCargar);

        if (cantidadProductosCargar > MAX_PRODUCTOS) {
            cantidadProductosCargar = MAX_PRODUCTOS;
        }
        pOrganizacion->listaBandas[indiceBanda].cantidadProductos = cantidadProductosCargar;

        for (indiceProducto = 0; indiceProducto < cantidadProductosCargar; indiceProducto++) {
            printf("\n  Producto %d:\n", indiceProducto + 1);
            printf("  Nombre del producto: ");
            fflush(stdin);
            scanf("%s", pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].nombreProducto);

            printf("  Cantidad disponible: ");
            scanf("%d", &pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].cantidadDisponible);

            printf("  Precio unitario: $");
            scanf("%f", &pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].precioUnitario);

            pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].cantidadVendida = 0;
            pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].subtotalRecaudado = 0.0;
        }

        pOrganizacion->cantidadBandas++;
        printf("\nCatalogo de merchandising de %s registrado con exito!\n", pOrganizacion->listaBandas[indiceBanda].nombreBanda);
    }
}


void buscarBandaPorNombre(tOrganizacion pOrganizacion, tCadena pNombreBandaBuscada, int *pPosicionBanda) {
    int indice = 0;
    bool bandaEncontrada = false;
    *pPosicionBanda = -1;

    while (indice < pOrganizacion.cantidadBandas && !bandaEncontrada) {
        if (strcmp(pOrganizacion.listaBandas[indice].nombreBanda, pNombreBandaBuscada) == 0) {
            *pPosicionBanda = indice;
            bandaEncontrada = true;
        } else {
            indice++;
        }
    }
}


void buscarProductoPorNombre(tBandaMerch pBanda, tCadena pNombreProductoBuscado, int *pPosicionProducto) {
    int indice = 0;
    bool productoEncontrado = false;
    *pPosicionProducto = -1;

    while (indice < pBanda.cantidadProductos && !productoEncontrado) {
        if (strcmp(pBanda.listaProductos[indice].nombreProducto, pNombreProductoBuscado) == 0) {
            *pPosicionProducto = indice;
            productoEncontrado = true;
        } else {
            indice++;
        }
    }
}

void ordenarProductosPorCantidadVendida(tProductoMerch pArregloProductos[], int pCantidadProductos) {
    int indiceActual;
    int indiceSiguiente;
    int posicionMayor;
    tProductoMerch productoAuxiliar;

    for (indiceActual = 0; indiceActual < pCantidadProductos - 1; indiceActual++) {
        posicionMayor = indiceActual;
        for (indiceSiguiente = indiceActual + 1; indiceSiguiente < pCantidadProductos; indiceSiguiente++) {
            if (pArregloProductos[indiceSiguiente].cantidadVendida > pArregloProductos[posicionMayor].cantidadVendida) {
                posicionMayor = indiceSiguiente;
            }
        }
        if (posicionMayor != indiceActual) {
            productoAuxiliar = pArregloProductos[indiceActual];
            pArregloProductos[indiceActual] = pArregloProductos[posicionMayor];
            pArregloProductos[posicionMayor] = productoAuxiliar;
        }
    }
}

void mostrarProductoMasVendido(tBandaMerch pBanda) {
    tProductoMerch copiaProductos[MAX_PRODUCTOS];
    int indice;

    if (pBanda.cantidadProductos == 0 || pBanda.totalUnidadesVendidasBanda == 0) {
        printf("\n  [Info] %s no registro ventas de merchandising.\n", pBanda.nombreBanda);
    } else {
        for (indice = 0; indice < pBanda.cantidadProductos; indice++) {
            copiaProductos[indice] = pBanda.listaProductos[indice];
        }
        ordenarProductosPorCantidadVendida(copiaProductos, pBanda.cantidadProductos);

        printf("\n  >>> PRODUCTO MAS VENDIDO DE %s: %s (%d unidades - $%.2f) <<<\n",
               pBanda.nombreBanda,
               copiaProductos[0].nombreProducto,
               copiaProductos[0].cantidadVendida,
               copiaProductos[0].subtotalRecaudado);
    }
}

void registrarVentasMerch(tOrganizacion *pOrganizacion) {
    int indiceBanda;
    int indiceProducto;
    int posicionProductoEncontrado;
    int cantidadComprada;
    float montoVenta;
    char respuestaUsuario;
    tCadena nombreProductoBuscado;

    if (pOrganizacion->cantidadBandas == 0) {
        printf("\nNo hay bandas cargadas en el modulo de organizacion.\n");
    } else {
        printf("\n======================================================\n");
        printf("      GESTION DE VENTAS DE MERCHANDISING              \n");
        printf("======================================================\n");

        for (indiceBanda = 0; indiceBanda < pOrganizacion->cantidadBandas; indiceBanda++) {
            printf("\n------------------------------------------------------\n");
            printf("BANDA: %s\n", pOrganizacion->listaBandas[indiceBanda].nombreBanda);
            printf("Catalogo disponible:\n");

            for (indiceProducto = 0; indiceProducto < pOrganizacion->listaBandas[indiceBanda].cantidadProductos; indiceProducto++) {
                printf("  - %s | Stock: %d | Precio: $%.2f\n",
                       pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].nombreProducto,
                       pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].cantidadDisponible,
                       pOrganizacion->listaBandas[indiceBanda].listaProductos[indiceProducto].precioUnitario);
            }

            if (pOrganizacion->listaBandas[indiceBanda].cantidadProductos > 0) {
                printf("\nAlgun producto de %s tuvo ventas? (s/n): ", pOrganizacion->listaBandas[indiceBanda].nombreBanda);
                fflush(stdin);
                scanf(" %c", &respuestaUsuario);

                while (respuestaUsuario == 's' || respuestaUsuario == 'S') {
                    printf("Ingrese el nombre del producto a registrar: ");
                    fflush(stdin);
                    scanf("%s", nombreProductoBuscado);

                    buscarProductoPorNombre(pOrganizacion->listaBandas[indiceBanda], nombreProductoBuscado, &posicionProductoEncontrado);

                    if (posicionProductoEncontrado == -1) {
                        printf("  [Error] El producto '%s' no existe para esta banda.\n", nombreProductoBuscado);
                    } else {
                        if (pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadDisponible == 0) {
                            printf("\n  *** SOLD OUT! Ya no queda stock de %s ***\n", nombreProductoBuscado);
                        } else {
                            printf("  Disponible: %d | Precio: $%.2f\n",
                                   pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadDisponible,
                                   pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].precioUnitario);
                            printf("  Ingrese cantidad vendida: ");
                            scanf("%d", &cantidadComprada);

                            if (cantidadComprada <= 0) {
                                printf("  [Aviso] La cantidad debe ser mayor a 0.\n");
                            } else if (cantidadComprada > pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadDisponible) {
                                printf("  [Error] Stock insuficiente (quedan %d unidades).\n",
                                       pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadDisponible);
                            } else {
                                montoVenta = cantidadComprada * pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].precioUnitario;

                                pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadDisponible -= cantidadComprada;
                                pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadVendida += cantidadComprada;
                                pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].subtotalRecaudado += montoVenta;

                                pOrganizacion->listaBandas[indiceBanda].totalUnidadesVendidasBanda += cantidadComprada;
                                pOrganizacion->listaBandas[indiceBanda].totalRecaudadoBanda += montoVenta;

                                pOrganizacion->totalUnidadesVendidasFestival += cantidadComprada;
                                pOrganizacion->recaudacionTotalMerchFestival += montoVenta;

                                printf("  Venta registrada! Subtotal: $%.2f\n", montoVenta);

                                if (pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].cantidadDisponible == 0) {
                                    printf("\n  ****************************************\n");
                                    printf("  *  SOLD OUT! Se agoto: %-15s *\n",
                                           pOrganizacion->listaBandas[indiceBanda].listaProductos[posicionProductoEncontrado].nombreProducto);
                                    printf("  ****************************************\n");
                                }
                            }
                        }
                    }

                    printf("\nDesea registrar otra venta para %s? (s/n): ", pOrganizacion->listaBandas[indiceBanda].nombreBanda);
                    fflush(stdin);
                    scanf(" %c", &respuestaUsuario);
                }

                mostrarProductoMasVendido(pOrganizacion->listaBandas[indiceBanda]);
                printf("  Total recaudado en merch por %s: $%.2f\n",
                       pOrganizacion->listaBandas[indiceBanda].nombreBanda,
                       pOrganizacion->listaBandas[indiceBanda].totalRecaudadoBanda);
            }
        }
    }
}

void mostrarResumenOrganizacion(tOrganizacion pOrganizacion) {
    int indiceBanda;
    int indiceProducto;

    printf("\n======================================================\n");
    printf("       RESUMEN DE VENTAS DE MERCHANDISING             \n");
    printf("======================================================\n");

    for (indiceBanda = 0; indiceBanda < pOrganizacion.cantidadBandas; indiceBanda++) {
        printf("\nBanda: %s\n", pOrganizacion.listaBandas[indiceBanda].nombreBanda);
        for (indiceProducto = 0; indiceProducto < pOrganizacion.listaBandas[indiceBanda].cantidadProductos; indiceProducto++) {
            printf("  %s: %d\n",
                   pOrganizacion.listaBandas[indiceBanda].listaProductos[indiceProducto].nombreProducto,
                   pOrganizacion.listaBandas[indiceBanda].listaProductos[indiceProducto].cantidadVendida);
        }
        printf("  Ganancias por merchandising: $%.2f\n", pOrganizacion.listaBandas[indiceBanda].totalRecaudadoBanda);
    }
    printf("\nGanancias totales de merchandising del festival: $%.2f\n", pOrganizacion.recaudacionTotalMerchFestival);
}

void escribirSeccionMerchBanda(FILE *pArchivoInforme, tOrganizacion pOrganizacion, tCadena pNombreBanda, float *pGananciaMerchBanda) {
    int posicionBandaEncontrada;
    int indiceProducto;
    *pGananciaMerchBanda = 0.0;

    if (pArchivoInforme != NULL) {
        buscarBandaPorNombre(pOrganizacion, pNombreBanda, &posicionBandaEncontrada);

        fprintf(pArchivoInforme, "\nMERCHANDISING:\n");
        if (posicionBandaEncontrada == -1 || pOrganizacion.listaBandas[posicionBandaEncontrada].cantidadProductos == 0) {
            fprintf(pArchivoInforme, "Sin productos registrados.\n");
            fprintf(pArchivoInforme, "\nGanancias por merchandising: $0.00\n");
        } else {
            for (indiceProducto = 0; indiceProducto < pOrganizacion.listaBandas[posicionBandaEncontrada].cantidadProductos; indiceProducto++) {
                fprintf(pArchivoInforme, "%s: %d\n",
                        pOrganizacion.listaBandas[posicionBandaEncontrada].listaProductos[indiceProducto].nombreProducto,
                        pOrganizacion.listaBandas[posicionBandaEncontrada].listaProductos[indiceProducto].cantidadVendida);
            }
            *pGananciaMerchBanda = pOrganizacion.listaBandas[posicionBandaEncontrada].totalRecaudadoBanda;
            fprintf(pArchivoInforme, "\nGanancias por merchandising: $%.2f\n", *pGananciaMerchBanda);
        }
    }
}

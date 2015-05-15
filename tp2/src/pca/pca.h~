#ifndef _PCA_H
#define _PCA_H
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "../manejoEntrada/entrada.h"
#include "../matriz/matriz.h"

void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos);
vectorNum *calcularMedias(vector<entrada> &v);
matrizNum * matrizDeCovarianza(vector<entrada> &etiquetados);
matrizNum *matCovarianza(vector<entrada> &v, vectorNum *medias);
vectorNum *metodoDeLasPotencias(matrizNum *covarianza);
vectorNum *crearVectorInicial(int dim);
#endif

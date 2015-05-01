#ifndef _PCA_H
#define _PCA_H

#include <iostream>
#include <math.h>
#include "../manejoEntrada/entrada.h"

void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos);
void matMedia(vector<entrada> &v, vector<double> &media);
void matCovarianza(vector<entrada> &v, vector<double> &media, vector< vector<double> > &covar);
void matrizDeCovarianza(vector<entrada> &etiquetados, vector< vector<double> > &covarianza);
double metodoDeLasPotencias(vector< vector<double> > &covarianza, vector<double> &potencias);

#endif

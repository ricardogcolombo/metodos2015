#ifndef _PCA_H
#define _PCA_H

#include <iostream>
#include <cmath.h>
#include "../manejoEntrada/entrada.h"

void matMedia(vector<entrada> &v, vector<double> &media);
void matCovarianza(vector<entrada> &v, vector<double> &media, vector< vector<double> > &covar);
void matrizDeCovarianza(vector<entrada> &etiquetados, vector< vector<double> > &covarianza);

#endif

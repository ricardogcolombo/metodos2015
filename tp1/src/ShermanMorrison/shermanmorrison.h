#ifndef __Sherman_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Sherman_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "../EstructuraBanda/banda.h"
#include "../GeneradorDeInstancias/generador.h"

#include <iostream>
#include <stdio.h>
#include <cmath>

double* resolverShermanMorrison(MatrizB *a, double *vectorY, int i, int j, double temp, int tam);
double denominadorShermanMorrison(double *v, double *z, int tam);
double* numeradorShermanMorrison(double *z, double *v, double *y, int tam);
double* armarVectorU(int i, MatrizB* a, int tam);
double* armarVectorVT(int j, int tam);
double* armarVectorZ(MatrizB *a, double *vectorU, int tam);
#endif

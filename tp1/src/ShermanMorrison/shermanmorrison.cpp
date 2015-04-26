#include "shermanmorrison.h"



using namespace std;

double* resolverShermanMorrison(MatrizB *a, double *vectorY, int i, int j, double temp, int tam) {
	double* vectorU = armarVectorU(i, a, tam);
	double* vectorVT = armarVectorVT(j, tam);
	double* vectorZ = armarVectorZ(a, vectorU, tam);

	vectorY[i] = 0.0;

	double* vectorNumerador = numeradorShermanMorrison(vectorZ, vectorVT, vectorY, tam);
	double denominador = denominadorShermanMorrison(vectorVT, vectorZ, tam);

	for(int i = 0; i < tam; i++) {
        double div = vectorNumerador[i]/denominador;
        vectorNumerador[i] = div;
	}

	double* vectorFinal = new double[tam];
	for(int j = 0; j < tam; j++) {
        vectorFinal[j] = vectorY[j] - vectorNumerador[j];
	}

	return vectorFinal;
}


double denominadorShermanMorrison(double *v, double *z, int tam) {
    int suma = 0;
    for(int i = 0; i < tam; i++) {
        suma = v[i] * z[i];
    }

    suma++;
    return suma;
}

double* numeradorShermanMorrison(double *z, double *v, double *y, int tam) {
    double* vectorzv = new double[tam * tam];

    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            int pos = (i * tam) + j;
            vectorzv[pos] = z[i] * v[j];
        }
    }

    double* vectorfinal = new double[tam];

    for(int i = 0; i < tam; i++) {

        int suma = 0;

        for(int j = 0; j < tam; j++) {
            int pos = (i * tam) + j;
            suma += vectorzv[pos] * y[j];
        }

        vectorfinal[i] = suma;
    }

    return vectorfinal;
}

double* armarVectorU(int i, MatrizB *mat, int tam) {
	double* vectorU = new double[tam];
	for(int pos = 0; pos < tam; pos++) {
			vectorU[pos] = 0;
		}

		if(i % tam != 0 && i % tam != tam - 1 ) {
			vectorU[i] = -5;
			vectorU[i+1] = 1;
			vectorU[i-1] = 1;
			vectorU[i - mat->getM()] = 1;
			vectorU[i - mat->getM()] = 1;
		}

	return vectorU;
}

double* armarVectorVT(int j, int tam) {
	double* vectorVT = new double[tam];
	for(int pos = 0; pos < tam; pos++) {
		if(pos == j){
			vectorVT[pos] = 1;
		} else {
			vectorVT[pos] = 0;
		}
	}

	return vectorVT;
}



double* armarVectorZ(MatrizB *a, double * vectorU, int tam) {
	double* vectorZ = new double[tam];
	for(int pos = 0; pos < tam; pos++) {
		if(vectorU[pos] != 0){
			vectorZ[pos] = vectorU[pos]/-4;
		} else {
			vectorU[pos] = 0;
		}
	}

	return vectorZ;
}



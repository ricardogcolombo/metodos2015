#include "Fowardsub.h"

using namespace std;

/**
 * Foward substitution
 *
 * @param {MatrizB*} m
 * @param {double*} b
 *
 * @return {double*} y
 */

double* foward_substitution(MatrizB *m, double *b){

   //Chequear que las dimensiones son correctas
   //Chequear que la matriz es diagonal inferior
	double* y = new double[m->getN()];
	//lleno de ceros el arreglo
	for (int i = 0; i < m->getN(); i++)
	{
		y[i]=0;	
	}

	for (int i = 0; i < m->getN() ; i++) 
	{
		y[i]  = b[i];
		for (int j = i - m->getP()-1; j < i; j++) 
		{
			if(j >= 0)
				y[i]=y[i]- m->getVal(i,j)*y[j];	
		}
	}
	return y;
}

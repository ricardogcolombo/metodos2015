#include "Fowardsub.h"
using namespace std;
double* foward_substitution(MatrizB *m, double *b) {
	//Chequear que las dimensiones son correctas
	//Chequear que la matriz es diagonal inferior
	double* y = new double[m->getN()];
	for (int i = 0; i < m->getN() ; i++)
	{
		y[i]  = b[i];
		for (int j = i - 1; j > i - (m->getP() +1) ; j--)
		{
			if(j<0)
				break;
			y[i] = y[i] - m->getVal(i, j) * y[j];
		}
	}
	return y;
}

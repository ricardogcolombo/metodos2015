#include "matriz.h"


matrizNum::matrizNum(int dimencion)
{
	dim = dimencion;
	valores = new double*[dim];
	for(int i = 0; i < dim; i++)
	{
		valores[i] = new double[dim];
	}
}
matrizNum::~matrizNum()
{
	for(int i = 0; i < dim; i++)
	{
		delete valores[i];
	}
	delete valores;
}

void matrizNum::resta(matrizNum* otraMat)
{
	if(otraMat->size() != dim)
		throw -1;
	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
			valores[i][j] = valores[i][j] - otraMat->valores[i][j];
}

double matrizNum::get(int x, int y)
{
	if(!(x >= 0 && x < dim))
		throw -1;
	if(!(y >= 0 && y < dim))
		throw -1;
	return valores[x][y];
}
void matrizNum::set(int x, int y, double val)
{
	if(!(x >= 0 && x < dim))
		throw -1;
	if(!(y >= 0 && y < dim))
		throw -1;
	valores[x][y] = val;
}
void matrizNum::print()
{
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++)
			cout << valores[j][i] << " ";
		cout << endl;
	}
}

int matrizNum::size()
{
	return dim;
}

vectorNum *matrizNum::producto(vectorNum *unVector)
{
	if(unVector->size() != dim)
		throw -1;
	vectorNum *vectAux = new vectorNum(dim);
	for(int i = 0; i < dim; i++){
		double aux = 0;
		for(int j = 0; j < dim; j++)
			aux += unVector->get(j)*valores[i][j];	
		vectAux->set(i, aux);
	}
	return vectAux;
}

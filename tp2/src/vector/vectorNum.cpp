#include "vectorNum.h"

vectorNum::vectorNum(int dimencion){
	dim = dimencion;
	valores = new int[dim];
	valorNorma2 = -1;
}

double vectorNum::norma2() {

	if(valorNorma2 != -1)
		return valorNorma2;

	double accum = 0.;
	for (int i = 0; i < dim; i++) {
        accum += valores[i] * valores[i];
    }
    valorNorma2 = sqrt(accum);
    return valorNorma2;	
}

vectorNum *vectorNum::resta(vectorNum *otroVector){

	if(dim != otroVector->dim)
		throw -1;
	vectorNum *nuevoVector = new vectorNum(dim);
	for(int i = 0; i < dim; i++)
		nuevoVector->valores[i] = valores[i] - otroVector->valores[i];
	return nuevoVector;
}

int vectorNum::get(int coordenada)
{
	if(coordenada >= 0 && coordenada < dim)
		return valores[coordenada];
	else
		throw 1;
}

void vectorNum::set(int coordenada, int valor)
{
	if(coordenada >= 0 && coordenada < dim)
		valores[coordenada] = valor;
	else
		throw 1;
}

void vectorNum::print()
{
	for(int i = 0; i < dim; i++)
		cout << valores[i] << " ";
	cout << endl;
}
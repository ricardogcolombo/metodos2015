#include "vectorNum.h"

vectorNum::vectorNum(int dimencion){
	dim = dimencion;
	valores = new double[dim];
	valorNorma2 = -1;
	for(int i = 0; i < dim; i++)
		valores[i] = 0;

}

vectorNum::~vectorNum(){
	delete valores;
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

double vectorNum::get(int coordenada)
{
	if(coordenada >= 0 && coordenada < dim)
		return valores[coordenada];
	else
		throw 1;
}

void vectorNum::set(int coordenada, double valor)
{
	if(coordenada >= 0 && coordenada < dim)
		valores[coordenada] = valor;
	else
		throw 1;
}

void vectorNum::print()
{
	for(int i = 0; i < dim; i++)
		cout << valores[i] << ',';
	cout << endl;
}

int vectorNum::size()
{
	return dim;
}

double vectorNum::multiplicacionVect(vectorNum *otroVector)
{
	double aux = 0;
	for(int i = 0; i < dim; i++)
		aux = aux + (valores[i]* otroVector->valores[i]);
	return aux;
}

void vectorNum::multiplicacionEscalar(double escalar)
{
	for(int i = 0; i < dim; i++)
		valores[i] = valores[i]*escalar;
}

matrizNum* vectorNum::multiplicacionVectTrans(vectorNum *otroVector)
{
	if(otroVector->dim != dim)
		throw -1;
	matrizNum* matriz = new matrizNum(dim);
	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
			matriz->set(i,j, valores[i]*otroVector->valores[j]);
	return matriz;
}

void vectorNum::suma(vectorNum *otroVector){
	if(dim != otroVector->dim)
		throw -1;
	for(int i = 0; i < dim; i++)
		valores[i] = valores[i] + otroVector->valores[i];
}

vectorNum *vectorNum::copy()
{
	vectorNum *aux = new vectorNum(dim);
	for(int i = 0; i < dim; i++)
		aux->valores[i]	= valores[i];
	return aux;
}

double vectorNum::normaInfinito()
{
	double max = 0;
	for(int i = 0; i < dim; i++)
	{
		if(abs(valores[i]) > max)
			max = valores[i];
	}
	return max;
}
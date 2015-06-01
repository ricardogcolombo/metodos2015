#include "SM.h"
using namespace std;
double** encontrarMatrizInversa(MatrizB *m);
double* armarVectorU(int i, MatrizB *mat);
double* armarVectorVT(int j, MatrizB *mat);
double calcularConstanteLoca(double* VT, double **inv, double * U, int dim);
vector<sanguijuelaDiscretizada*> *discretizarSangs(vector<sanguijuela*>* sanguijuelas, double intervalo, int cantidadDeColumnas, int cantidadDeFilas);
double ** calcularMatrizDeShermanMorrison(double *vecU, double* vecVT, double** inversa, int dim);
double *copiarB(double *b, int tam);
double *matrizPorVector( double** inversa, double *vector, int dimencion);
double *salvacionSM(instancia *ins, double *b)
{
	sanguijuela* s;
	sanguijuela* a_eliminar = NULL;
	//Queria ponerle el valor mas grande, pero c es caprichoso
	double punto_critico_global = 10000000000;
	double punto_critico_local = 0;
	double *mejorRespuesta;
	int posPuntoCritico = ins->m->getP() / 2 + (ins->m->getP()) * (ins->m->getP() / 2);
	//Asegurado por matlab que devuelve lo mismo
	double** inversa = encontrarMatrizInversa(ins->m);
	vector<sanguijuelaDiscretizada*> *sangDiscretizadas = discretizarSangs(ins->sanguijuelas, ins->intervalo, ins->m->getP(), ins->m->getP());
	int dimencion = ins->m->getN();
	for (int i = 0; i < sangDiscretizadas->size() ; i++)
	{
		double * vecU = armarVectorU((*sangDiscretizadas)[i]->x, ins->m);
		double * vecVT = armarVectorVT((*sangDiscretizadas)[i]->y, ins->m);
		//Ahora hago la ecuacion horrible de sherman morrison
		double** ShermanMorris = calcularMatrizDeShermanMorrison(vecU, vecVT, inversa, dimencion);
		delete[] vecU;
		delete[] vecVT;
		//Obtengo una copia de B y modifico solo la fila donde esta la sanguijuela
		double *nuevoB = copiarB(b, dimencion);
		nuevoB[(*sangDiscretizadas)[i]->x] = 0;
		//hago x = A^(-1).b y obtengo la nueva respuesta
		double *respuesta = matrizPorVector(ShermanMorris, nuevoB, dimencion);
		//Si es la mejor respuesta obtenida hasta el momento, la guardo.
		punto_critico_local = respuesta[posPuntoCritico];
		if (punto_critico_local < punto_critico_global)
		{
			mejorRespuesta = respuesta;
			punto_critico_global = punto_critico_local;
			a_eliminar = s;
		}
		//Limpio
		for (int w = 0; w < dimencion; w++)
			delete[] ShermanMorris[w];
		delete[] ShermanMorris;
		delete[] nuevoB;
		delete (*sangDiscretizadas)[i];
	}
	delete sangDiscretizadas;
	for (int i = 0; i < dimencion; i++)
		delete[] inversa[i];
	delete[] inversa;
	return mejorRespuesta;
}

double *copiarB(double *b, int tam)
{
	double *nuevoB = new double[tam];
	for (int w = 0; w < tam; w++ )
	{
		nuevoB[w] = b[w];
	}
	return nuevoB;
}

double *matrizPorVector(double** inversa, double *vector, int dimencion) {
	double *respuesta = new double[dimencion];
	for (int j = 0; j < dimencion; j++)
	{
		respuesta[j] = 0;
		for (int w = 0; w < dimencion; w++)
		{
			respuesta[j]++;
			vector[w]++;
			inversa[j][w]++;
			respuesta[j] += (vector[w]) * (inversa[j][w]);
		}
	}
	return respuesta;
}

double *vectorTporMatriz(double* vector, double** matriz, int dimencion) {
	double *respuesta = new double[dimencion];
	for (int j = 0; j < dimencion; j++)
	{
		respuesta[j] = 0;
		for (int w = 0; w < dimencion; w++)
		{
			respuesta[j] += vector[w] * matriz[w][j];
		}
	}
	return respuesta;
}

double **vectorPorVectorT(double* AaLaMenosUnoPorU, double* VTporAalaMenosUno, int dimencion)
{
	double** matrix = new double*[dimencion];
	for (int w = 0; w < dimencion; w++) {
		matrix[w] = new double[dimencion];
		for (int j = 0; j < dimencion; j++) {
			matrix[w][j] = AaLaMenosUnoPorU[w] * VTporAalaMenosUno[j];
		}
	}
	return matrix;
}

void dividirMatrizPorCte(double** matrix, double cte, int dimencion) {
	for (int w = 0; w < dimencion; w++) {
		for (int j = 0; j < dimencion; j++) {
			matrix[w][j] = matrix[w][j] / cte;
		}
	}
}

void restaMatrices(double **matriz1, double **matriz2, int dimencion)
{
	for (int w = 0; w < dimencion; w++) {
		for (int j = 0; j < dimencion; j++) {
			matriz2[w][j] = matriz1[w][j] - matriz2[w][j];
		}
	}
}

double** calcularMatrizDeShermanMorrison(double *vecU, double* vecVT, double** inversa, int dim)
{
	double *AaLaMenosUnoPorU = matrizPorVector( inversa, vecU, dim);
	double *VTporAalaMenosUno = vectorTporMatriz(vecVT, inversa, dim);
	//Aca calculo la constante loca que va dividiendo
	double constanteLoca = calcularConstanteLoca(vecVT, inversa, vecU, dim);
	//Aca termino de calcular sherman morrison
	double** matrix = vectorPorVectorT(AaLaMenosUnoPorU, VTporAalaMenosUno, dim);
	dividirMatrizPorCte(matrix, constanteLoca, dim);
	restaMatrices(inversa, matrix, dim);
	delete[] VTporAalaMenosUno;
	delete[] AaLaMenosUnoPorU;
	return matrix;
}

double vectorTporVector(double *vectorT, double* vect, int dim)
{
	double respuesta = 0;
	for (int i = 0; i < dim; i++)
		respuesta += vect[i] * vectorT[i];
	return respuesta;
}



double calcularConstanteLoca(double* VT, double** inv, double * U, int dim)
{
	double *invPorU = matrizPorVector(inv, U, dim);
	double respuesta = vectorTporVector(VT , invPorU, dim);
	respuesta += 1;
	delete[] invPorU;
	return respuesta;
}

sanguijuelaDiscretizada::sanguijuelaDiscretizada(int _x, int _y, double _temp)
{
	x = _x;
	y = _y;
	temp = _temp;
}

double *generarCanonico(int i, int dim)
{
	double* vectorCanonico = new double[dim];
	for (int j = 0; j < dim; j++)
		vectorCanonico[j] = 0;
	vectorCanonico[i] = 1;
	return vectorCanonico;
}


double** encontrarMatrizInversa(MatrizB *m)
{
	int dim = m->getN();
	MatrizB *U = m;
	MatrizB *L = DescompLU(U);
	double** inversa = new double*[dim];
	for (int i = 0; i < dim; i++)
		inversa[i] = new double[dim];

	for (int i = 0; i < dim; i++)
	{
		double* vectorCanonico = generarCanonico(i, dim);
		double* y = foward_substitution(L, vectorCanonico);
		delete[] vectorCanonico;
		double *respuesta = backward_substitution(U, y);
		delete[] y;
		for (int j = 0; j < dim; j++)
		{
			inversa[j][i] = respuesta[j];
		}
		delete[] respuesta;
	}
	delete L;
	return inversa;
}

double* armarVectorU(int i, MatrizB *mat) {
	int tam = mat->getN();
	double* vectorU = new double[tam];
	for (int pos = 0; pos < tam; pos++) {
		vectorU[pos] = 0;
	}
	if (i % tam != 0 && i % tam != tam - 1 ) {
		vectorU[i] = -5;
		vectorU[i + 1] = 1;
		vectorU[i - 1] = 1;
		vectorU[i - mat->getP()] = 1;
		vectorU[i + mat->getP()] = 1;
	}
	return vectorU;
}
double* armarVectorVT(int j, MatrizB *mat) {
	int tam = mat->getN();
	double* vectorVT = new double[tam];
	for (int pos = 0; pos < tam; pos++) {
		vectorVT[pos] = 0;
	}
	vectorVT[j] = 1;
	return vectorVT;
}
vector<sanguijuelaDiscretizada*> *discretizarSangs(vector<sanguijuela*>* sanguijuelas, double intervalo, int cantidadDeColumnas, int cantidadDeFilas)
{
	vector<sanguijuelaDiscretizada*> *sanguDisc = new vector<sanguijuelaDiscretizada*>();
	for (int i = 0; i < sanguijuelas->size(); i++) {
		sanguijuela *s = (*sanguijuelas)[i];
		int x_comienzo = round((s->x - 1 * (s->radio + 1)) / intervalo);
		int y_comienzo = round((s->y - 1 * (s->radio + 1)) / intervalo);
		int x_fin = round((s->x + 1 * (s->radio + 1)) / intervalo);
		int y_fin = round((s->y + 1 * (s->radio + 1)) / intervalo);
		if (s->radio < intervalo) {
			for (int j = x_comienzo ; j <= x_fin; j++) {
				for (int w = y_comienzo; w <= y_fin; w++) {
					if (pow(j * intervalo - s->x , 2.0) + pow(w * intervalo - s->y, 2.0) <= pow(s->radio, 2.0)) {
						int CoordenadaEnLaMatriz = (w + (j * cantidadDeColumnas));
						if (w > 0 && w < cantidadDeColumnas - 1) {
							if (j > 0 && j < cantidadDeFilas - 1) {
								if (CoordenadaEnLaMatriz % cantidadDeColumnas != 0 && CoordenadaEnLaMatriz % cantidadDeColumnas != cantidadDeColumnas - 1 ) {
									sanguDisc->push_back(new sanguijuelaDiscretizada(CoordenadaEnLaMatriz, CoordenadaEnLaMatriz, (*sanguijuelas)[i]->temperatura));
								}
							}
						}
					}
				}
			}
		}
	}
	return sanguDisc;
}

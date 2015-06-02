#include "SM.h"
#define INFINITO 10000000000
using namespace std;
double* armarVectorU(int i, MatrizB *mat);
double* armarVectorVT(int j, MatrizB *mat);
vector<sanguijuelaDiscretizada*> *discretizarSangs(vector<sanguijuela*>* sanguijuelas, double intervalo, int cantidadDeColumnas, int cantidadDeFilas);
double* calcularMatrizDeShermanMorrison(double *vecU, double* vecVT, MatrizB* L, MatrizB* U , double* b, int dim);
double *copiarB(double *b, int tam);
double *salvacionSM(instancia *ins, double *b) {
	int sanguijuelaParaEliminar = -1;
	sanguijuela* a_eliminar = NULL;
	//Queria ponerle el valor mas grande, pero c es caprichoso
	double punto_critico_global = INFINITO;
	double punto_critico_local = 0;
	double *mejorRespuesta;
	int posPuntoCritico = ins->m->getP() / 2 + (ins->m->getP()) * (ins->m->getP() / 2);
	vector<sanguijuelaDiscretizada*> *sangDiscretizadas = discretizarSangs(ins->sanguijuelas, ins->intervalo, ins->m->getP(), ins->m->getP());
	int dimencion = ins->m->getN();
	MatrizB* U = ins->m;
	MatrizB* L = DescompLU(U);
	for (int i = 0; i < sangDiscretizadas->size() ; i++) {
		//Obtengo una copia de B y modifico solo la fila donde esta la sanguijuela
		double *nuevoB = copiarB(b, dimencion);
		nuevoB[(*sangDiscretizadas)[i]->x] = 0;
		//Creo los vectores
		double * vecU = armarVectorU((*sangDiscretizadas)[i]->x, ins->m);
		double * vecVT = armarVectorVT((*sangDiscretizadas)[i]->y, ins->m);
		//Ahora utilizo la ecuación de sherman morrison
		double* respuesta = calcularMatrizDeShermanMorrison(vecU, vecVT, L, U, nuevoB, dimencion);
		//Si es la mejor respuesta obtenida hasta el momento, la guardo.
		punto_critico_local = respuesta[posPuntoCritico];
		if (punto_critico_local < punto_critico_global) {
			if (punto_critico_global != INFINITO) {
				delete[] mejorRespuesta;
			}
			mejorRespuesta = respuesta;
			punto_critico_global = punto_critico_local;
			sanguijuelaParaEliminar = i;
		}
		//Limpio
		delete[] vecU;
		delete[] vecVT;
		delete[] nuevoB;
		delete (*sangDiscretizadas)[i];
	}
	cout << "MEJOR SANGIJUELA: " << sanguijuelaParaEliminar << endl;
	delete sangDiscretizadas;
	return mejorRespuesta;
}
double *copiarB(double *b, int tam) {
	double *nuevoB = new double[tam];
	for (int w = 0; w < tam; w++ ) {
		nuevoB[w] = b[w];
	}
	return nuevoB;
}
double vectorTporVector(double *vectorT, double* vect, int dim) {
	double respuesta = 0;
	for (int i = 0; i < dim; i++) {
		respuesta += vect[i] * vectorT[i];
	}
	return respuesta;
}
double* calcularMatrizDeShermanMorrison(double *vecVT, double* vecU, MatrizB* L, MatrizB* U , double* b, int dim) {
	//double *b;
	double *aux = foward_substitution(L, b);
	double *y = backward_substitution(U, aux);

	aux = foward_substitution(L, vecU);
	double *z = backward_substitution(U, aux);

	double n1 = vectorTporVector(vecVT, y, dim);
	double divisor = vectorTporVector(vecVT, z, dim);
	divisor = divisor + 1.0;
	n1 = (double) n1 / (double) divisor;
	for (int i = 0; i < dim; i++) {
		z[i] = y[i] - (z[i] * n1);
	}
	return z;
}
sanguijuelaDiscretizada::sanguijuelaDiscretizada(int _x, int _y, double _temp) {
	x = _x;
	y = _y;
	temp = _temp;
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
vector<sanguijuelaDiscretizada*> *discretizarSangs(vector<sanguijuela*>* sanguijuelas, double intervalo, int cantidadDeColumnas, int cantidadDeFilas) {
	int contador;
	vector<sanguijuelaDiscretizada*> *sanguDisc = new vector<sanguijuelaDiscretizada*>();
	for (int i = 0; i < sanguijuelas->size(); i++) {
		contador = 0;
		sanguijuela *s = (*sanguijuelas)[i];

		int x_comienzo = round((s->x - 1 * (s->radio + 1)) / intervalo);
		int y_comienzo = round((s->y - 1 * (s->radio + 1)) / intervalo);

		int x_fin = round((s->x + 1 * (s->radio + 1)) / intervalo);
		int y_fin = round((s->y + 1 * (s->radio + 1)) / intervalo);

		for (int j = x_comienzo ; j <= x_fin; j++) {
			for (int w = y_comienzo; w <= y_fin; w++) {
				if (pow(j * intervalo - s->x , 2.0) + pow(w * intervalo - s->y, 2.0) <= pow(s->radio, 2.0)) {
					int CoordenadaEnLaMatriz = (w + (j * cantidadDeColumnas));
					if (w > 0 && w < cantidadDeColumnas - 1) {
						if (j > 0 && j < cantidadDeFilas - 1) {
							if (CoordenadaEnLaMatriz % cantidadDeColumnas != 0 && CoordenadaEnLaMatriz % cantidadDeColumnas != cantidadDeColumnas - 1 ) {
								sanguDisc->push_back(new sanguijuelaDiscretizada(CoordenadaEnLaMatriz, CoordenadaEnLaMatriz, (*sanguijuelas)[i]->temperatura));
								contador++;
							}
						}
					}
				}
			}
		}
		if(contador > 1)
			cout << "Error, LA SANGUIJUELA NO ES DISCRETIZALE" << endl;
	}
	return sanguDisc;
}

#include "generador.h"

using namespace std;

/**
 * Generador de instancias desde archivo
 *
 * @param {ifstream&} archivo de entrada
 * 
 * @return {instancia*} instancia
 */

instancia* generarInst(ifstream &archivoDeEntrada) {
	double ancho, largo, intervalo;
	int cantidadDeSanguijuelas;
	vector<sanguijuela*> *sanguijuelas = new vector<sanguijuela*>(); 
	archivoDeEntrada >> ancho;
	archivoDeEntrada >> largo;
	archivoDeEntrada >> intervalo;
	archivoDeEntrada >> cantidadDeSanguijuelas;

	for(int i = 0; i < cantidadDeSanguijuelas; i++) {
		double x,  y, radio, temperatura;
		archivoDeEntrada >> x;
		archivoDeEntrada >> y;
		archivoDeEntrada >> radio;
		archivoDeEntrada >> temperatura;
		sanguijuelas->push_back(new sanguijuela(y,x,radio,temperatura,i+1));
	}

	return generarInstMatriz(ancho, largo, intervalo, sanguijuelas);
}

/**
 * Generador de instancias con pasaje de parametros
 *
 * @param {double} ancho
 * @param {double} largo
 * @param {double} intervalo
 * @param {vector<sanguijuela*>*} sanguijuelas
 * 
 * @return {instancia*} instancia
 */


instancia *generarInstMatriz(double ancho, double largo, double intervalo, vector<sanguijuela*> *sanguijuelas) {
	int cantidadDeFilas = largo / intervalo;

	int cantidadDeColumnas = ancho / intervalo;

	cantidadDeColumnas++;
	cantidadDeFilas++;

	int cantidadDeIncognitas = cantidadDeFilas*cantidadDeColumnas;

	MatrizB *matrizDeResolucion = new MatrizB(cantidadDeIncognitas, cantidadDeColumnas);

	double *vectorb = new double[cantidadDeIncognitas+1];

	for(int i = 0; i <= cantidadDeColumnas; i++) {
		matrizDeResolucion->setVal(i,i, 1);
		vectorb[i] = -100;

		matrizDeResolucion->setVal(cantidadDeIncognitas - i  -1, cantidadDeIncognitas - i -1, 1);
		vectorb[cantidadDeIncognitas - i] = -100;
	}

	//Seteo las ecuaciones

	for(int i = cantidadDeColumnas; i < cantidadDeIncognitas - cantidadDeColumnas; i++) {
		if(i % cantidadDeColumnas == 0 || i % cantidadDeColumnas == cantidadDeColumnas - 1 ) {
			matrizDeResolucion->setVal(i,i, 1);
			vectorb[i] = -100;
		} else {
			matrizDeResolucion->setVal(i,i, -4);
			matrizDeResolucion->setVal(i,i-cantidadDeColumnas, 1);
			matrizDeResolucion->setVal(i,i+cantidadDeColumnas, 1);
			matrizDeResolucion->setVal(i,i+1, 1);
			matrizDeResolucion->setVal(i,i-1, 1);
			vectorb[i] = 0.0;
		}
	}

	for(int i = 0; i < sanguijuelas->size(); i++) {

		sanguijuela *s = (*sanguijuelas)[i];

		int x_comienzo = round((s->x -1 * (s->radio + 1))/intervalo);
		int y_comienzo = round((s->y -1 * (s->radio + 1))/intervalo);

		int x_fin = round((s->x + 1 * (s->radio + 1))/intervalo);
		int y_fin = round((s->y + 1 * (s->radio + 1))/intervalo);

		for(int j = x_comienzo ; j <= x_fin; j++) {
			for(int w = y_comienzo; w <= y_fin; w++) {
				if(pow(j*intervalo - s->x ,2.0)+ pow(w*intervalo - s->y,2.0) <= pow(s->radio,2.0)) {
					int CoordenadaEnLaMatriz = (w + (j*cantidadDeColumnas));
					if(w > 0 && w < cantidadDeColumnas -1) {
						if(j > 0 && j < cantidadDeFilas -1) {
							if(CoordenadaEnLaMatriz % cantidadDeColumnas != 0 && CoordenadaEnLaMatriz % cantidadDeColumnas != cantidadDeColumnas - 1 ) {	
							  matrizDeResolucion->setVal( CoordenadaEnLaMatriz ,CoordenadaEnLaMatriz , 1);
							  matrizDeResolucion->setVal( CoordenadaEnLaMatriz ,CoordenadaEnLaMatriz + 1 , 0);
							  matrizDeResolucion->setVal( CoordenadaEnLaMatriz,CoordenadaEnLaMatriz - 1 , 0);
							  matrizDeResolucion->setVal( CoordenadaEnLaMatriz ,CoordenadaEnLaMatriz + cantidadDeColumnas, 0);
							  matrizDeResolucion->setVal( CoordenadaEnLaMatriz, CoordenadaEnLaMatriz - cantidadDeColumnas, 0);
							  vectorb[CoordenadaEnLaMatriz] = s->temperatura;
						  }
						}
					}
				}
			}
		}
	
  }
	
	instancia *nuevaInstancia = new instancia();
	nuevaInstancia->m = matrizDeResolucion;
	nuevaInstancia->b = vectorb;
	nuevaInstancia->sanguijuelas = sanguijuelas;
	nuevaInstancia->ancho = ancho;
	nuevaInstancia->largo = largo;
	nuevaInstancia->intervalo = intervalo;
	return nuevaInstancia;
}

/**
 * Constructor de sanguijuela
 *
 * @param {double} x1
 * @param {double} y
 * @param {double} radio
 * @param {double} temperatura
 *
 * @return {sanguijuela*} nueva instancia de sanguijuela
 */
sanguijuela::sanguijuela(double _x, double _y, double _radio, double _temperatura, int numero) {
	x= _x;
	y=_y;
	radio = _radio;
	temperatura= _temperatura; 
	numeroSang = numero;
	procesar = true;
}

instancia::~instancia(){
	delete m;
	delete b;
	for(int i = 0; i < sanguijuelas->size(); i++)
		delete (*sanguijuelas)[i];
	delete sanguijuelas;
}

int instancia::cantidadDeColumnas(){
	return ((largo)/intervalo) +1;
}

int instancia::cantidadDeFilas(){
	return ((ancho)/intervalo)+1;
}
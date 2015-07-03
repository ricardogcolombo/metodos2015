#include "Salvacion/salvacion.h"
#include "GeneradorDeInstancias/generador.h"
#include "EstructuraBanda/banda.h"
#include "Sustitucion/susti.h"
#include "EliminacionGauss/ElimGauss.h"
#include "FowardSub/Fowardsub.h"
#include "SMAlt/SM.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/time.h>
using namespace std;
//El programa requiere 3 parametros, un archivo de entrada, uno de salida y el modo a ejecutar.
int main(int argc, char *argv[]) {
	timeval startGauss, endGauss;
	timeval startLU, endLU;
	timeval startSalvacion, endSalvacion;
	timeval startSherman, endSherman;
	long elapsed_mtime; /* elapsed time in milliseconds */
	long elapsed_seconds; /* diff between seconds counter */
	long elapsed_useconds; /* diff between microseconds counter */
	if (argc != 4) {
		cout << "Error, Faltan Argumentos" << endl;
		return 1;
	}
	double *respuesta;
	ofstream archivoDeSalida;
	ofstream archivoTiempos;
	archivoDeSalida.setf(ios::fixed, ios::floatfield);
	archivoDeSalida.precision(5);
	ifstream archivoDeEntrada(argv[1], ios::in);
	archivoDeSalida.open(argv[2]);
	instancia *nuevaInstancia = generarInst(archivoDeEntrada);
	//Eliminacion Gaussiana Banda
	if (strcmp(argv[3], "0") == 0) {
		cout << "Corriendo Metodo de gauss..." << endl;
		gettimeofday(&startGauss, NULL);
		gauss(nuevaInstancia->m, nuevaInstancia->b);
		respuesta = backward_substitution(nuevaInstancia->m, nuevaInstancia->b);
		gettimeofday(&endGauss, NULL);
		elapsed_seconds = endGauss.tv_sec - startGauss.tv_sec;
		elapsed_useconds = endGauss.tv_usec - startGauss.tv_usec;
		double timeGauss =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
		archivoTiempos.open("TESTEADOR/tiempos0.txt", std::ofstream::out | std::ofstream::app);
		archivoTiempos << timeGauss << endl;
		archivoTiempos.close();
		for (int i = 0; i <= nuevaInstancia->cantidadDeColumnas(); i++)
			for (int w = 0; w <= nuevaInstancia->cantidadDeFilas(); w++) {
				archivoDeSalida << i << "\t" << w << "\t" << respuesta[w + (i * nuevaInstancia->m->getP())] << endl;
			}
	}
	//Factorizacion LU, explotando banda
	if (strcmp(argv[3], "1") == 0) {
		cout << "Corriendo Metodo LU..." << endl;
		gettimeofday(&startLU, NULL);
		MatrizB *L = DescompLU(nuevaInstancia->m);
		double *y = foward_substitution(L, nuevaInstancia->b);
		respuesta = backward_substitution(nuevaInstancia->m, y);
		gettimeofday(&endLU, NULL);
		elapsed_seconds = endLU.tv_sec - startLU.tv_sec;
		elapsed_useconds = endLU.tv_usec - startLU.tv_usec;
		double timeLU =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
		archivoTiempos.open("TESTEADOR/tiempos1.txt", std::ofstream::out | std::ofstream::app);
		archivoTiempos << timeLU << endl;
		archivoTiempos.close();
		for (int i = 0; i <= nuevaInstancia->cantidadDeColumnas(); i++)
			for (int w = 0; w <= nuevaInstancia->cantidadDeFilas(); w++) {
				archivoDeSalida << i << "\t" << w << "\t" << respuesta[w + (i * nuevaInstancia->m->getP())] << endl;
			}
	}
	//Algoritmo de eliminacion de sanguijuela simple
	if (strcmp(argv[3], "2") == 0) {
		cout << "Corriendo Metodo eliminacion de Sanguijuelas Simple..." << endl;
		gettimeofday(&startSalvacion, NULL);
		respuesta =  buscarSalvacion(nuevaInstancia);
		gettimeofday(&endSalvacion, NULL);
		elapsed_seconds = endSalvacion.tv_sec - startSalvacion.tv_sec;
		elapsed_useconds = endSalvacion.tv_usec - startSalvacion.tv_usec;
		double timeSalvacion =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
		cout << timeSalvacion << endl;
		archivoTiempos.open("TESTEADOR/tiempos2.txt", std::ofstream::out | std::ofstream::app);
		archivoTiempos << timeSalvacion << endl;
		archivoTiempos.close();
		for (int i = 0; i <= nuevaInstancia->cantidadDeColumnas(); i++)
			for (int w = 0; w <= nuevaInstancia->cantidadDeFilas(); w++) {
				archivoDeSalida << i << "\t" << w << "\t" << respuesta[w + (i * nuevaInstancia->m->getP())] << endl;
			}
	}
	//Eliminacion de Sang con sherman morrison
	if (strcmp(argv[3], "3") == 0) {
		cout << "Corriendo Metodo eliminacion de Sanguijuelas sherman morrison..." << endl;
		gettimeofday(&startSherman, NULL);
		respuesta = salvacionSM(nuevaInstancia, nuevaInstancia->b);
		gettimeofday(&endSherman, NULL);
		elapsed_seconds = endSherman.tv_sec - startSherman.tv_sec;
		elapsed_useconds = endSherman.tv_usec - startSherman.tv_usec;
		double timeSherman =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
		cout << timeSherman << endl;
		archivoTiempos.open("TESTEADOR/tiempos3.txt", std::ofstream::out | std::ofstream::app);
		archivoTiempos << timeSherman << endl;
		archivoTiempos.close();
		for (int i = 0; i <= nuevaInstancia->cantidadDeColumnas(); i++)
			for (int w = 0; w <= nuevaInstancia->cantidadDeFilas(); w++) {
				archivoDeSalida << i << "\t" << w << "\t" << respuesta[w + (i * nuevaInstancia->m->getP())] << endl;
			}
	}
	cout << "Fin!" << endl;
	delete nuevaInstancia;
	delete[] respuesta;
	archivoDeSalida.close();
	archivoDeEntrada.close();
}

//TODO generador para el sherman Morris
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
using namespace std;
//El programa requiere 3 parametros, el largo, el ancho y la cantidad de sanguijuelas del sistema
int main(int argc, char *argv[]) {
	if (argc != 5) {
		cout << "Error, Faltan Argumentos" << endl;
		return 1;
	}
	ofstream archivoDeSalida;
	archivoDeSalida.setf(ios::fixed, ios::floatfield);
	archivoDeSalida.open("TESTEADOR/instancia.txt");
	double largo = strtod(argv[1], NULL);
	double ancho = strtod(argv[2], NULL);
	int cantidadSang = strtod(argv[3], NULL);
	double discretizacion = strtod(argv[4], NULL);
	int cantidadDeSanguijuelasMax = (largo - 2) * (ancho - 2);
	if (cantidadDeSanguijuelasMax < cantidadSang) {
		cout << "Error, El sistema no soporta esta cantida de sang" << endl;
		return 1;
	}
	double x = 1;
	double y = 1;
	archivoDeSalida.precision(1);
	archivoDeSalida << largo << " "<< ancho << " " << discretizacion << " " << cantidadSang << endl;
	archivoDeSalida.precision(1);
	for (int i = 0; i < cantidadSang; i++) {
		archivoDeSalida << x << " " << y << " 0.5 100" << endl;
		x++;
		if (x >= largo - 1) {
			x = 1;
			y ++;
		}
	}
	archivoDeSalida.close();
	return 0;
}
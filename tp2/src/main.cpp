#include "manejoEntrada/entrada.h"
#include "knn/knn.h"
#include "pca/pca.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;




int main(int argc, char *argv[]) {

	if(argc != 4){
		cout << "Error en la cantidad de argumentos!!" << endl;
		return -1;		
	}

	string archivoDeEntrada (argv[1]);
	string archivoDeSalida (argv[2]);
	string metodo (argv[3]);

	cout << "Cargando Base de datos..." << endl;
	vector<entrada> entradas = procesarEntrada("minitrain.csv", false);
	cout << "Cargando imagenes a testear..." << endl;
	vector<entrada> test = procesarEntrada("test.csv", true);

	//no estoy devolviendo nada por salida, cuidado
	string salida;
/*
	//knn
	if(metodo.compare(1,1,"0"))
	{
		cout << "Ejecutando metodo knn..." << endl;
		calcularknn(entradas,test, salida, 6);
	}
*/
	//pca + knn
	if(metodo.compare(1,1,"1"))
	{
    vector<double> lambdas = calcularPca(entradas,test, salida, 6);
    for(int i = 0; i < lambdas.size(); i++) cout << "lambda[] " << lambdas[i] << endl;
	}


	cout << "Fin!" << endl;
	return 0;
}

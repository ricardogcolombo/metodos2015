#include "manejoEntrada/entrada.h"

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

	vector<entrada> entradas = procesarEntrada("minitrain.csv");
	


	//knn
	if(metodo.compare("0"))
	{

	}

	//pca + knn
	if(metodo.compare("1"))
	{

	}


	cout << "Fin!" << endl;
	return 0;
}
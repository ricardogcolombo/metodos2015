#include "kNN.h"

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

struct entrada {
	int label;
	int *valores;
	double norma2;
};

double norma2(entrada e) {
	double accum = 0.;
	for (int i = 0; i < 784; i++) {
        accum += e.valores[i] * e.valores[i];
    }
    return sqrt(accum);	
}

int main(int argc, char *argv[]) {

	ifstream file ("minitrain.csv");
	string value;
	string delimiter = ",";
	
	//nline numera los vectores	
	int nline = 0;
	
	vector<entrada> vectores;

	//Leo el encabezado
	getline(file, value);

	while(getline(file, value)) {
		entrada vec;		
		vec.valores = new int[783];
		
		//pos numera la entrada, 0 = label, [1..784] = valores
		int pos = 0;
		
		size_t i = 0;
		string token;
		while ((i = value.find(delimiter)) != string::npos) {
			token = value.substr(0, pos);
			if(pos == 0) {
				vec.label = atoi(value.c_str());
			} else {
				vec.valores[pos-1] = atoi(value.c_str());
			}
			value.erase(0, i + delimiter.length());
			pos++;
		}
		//Leo la posicion 784 que no tiene delimitador
		vec.valores[pos-1] = atoi(value.c_str());
		
		//Calculo la norma
		vec.norma2 = norma2(vec);
		
		//Guardo el vector
		vectores.push_back(vec);
		nline++;
	}

	cout << "Fin!" << endl;
}


	
	

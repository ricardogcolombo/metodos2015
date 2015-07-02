#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <stdlib.h>

#define HOLA 1
using namespace std;

int main(int argc, char *argv[]) {

	int vecinos = atoi(argv[1]);
	int lamda = atoi(argv[2]);
	int cantidadDePruebas = 1;

	fstream myfile("TESTING/test.txt", ios::out | ios::trunc);
	int knn[42000];

	myfile << "../data/ " << vecinos << " " << lamda << " " << cantidadDePruebas << endl;


	for (int j = 0; j  < cantidadDePruebas; j++) {
		for (int i = 0; i  < 42000; i++) {
			knn[i] = 1;
		}
		for (int i = 0; i < 4200; i++) {
			knn[(HOLA+j)*4200+i] = 0;
		}
		for (int i = 0; i < 42000; i++) {
			myfile << knn[i] << " ";
		}
		myfile << endl;
	}

	myfile.close();

}
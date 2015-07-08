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
#include <iostream>
#include <string>
#include <sys/time.h>
using namespace std;

void ejecutar(int metodo, vector<entrada> &entradas, vector<entrada> &test, int lamda, int vecinos, fstream& myfile);
int **kfolds(string archivo, int &cantidadDePruebas, int &lamda, int &vecinos);
void arreglarEntrada(vector<entrada> entradaOriginal, vector<entrada> &entradaNueva, vector<entrada> &testeo, int *kfold);

int main(int argc, char *argv[]) {

	if (argc < 3) {
		cout << "Error en la cantidad de argumentos!!" << endl;
		return -1;
	}

	string archivoDeEntrada (argv[1]);
	string archivoDeSalida (argv[2]);
	string metodo;
	if (argc == 3) {
		metodo = "1";
	} else {
		metodo = argv[3];
	}

	//Esto es para competir
	// int lamda = 50;
	// int vecinos = 5;
	// fstream myfile("autovectores",ios::out | ios::app);
	// cout << "Cargando Base de datos..." << endl;
	// vector<entrada> entrenamiento = procesarEntrada("train.csv", false);
	// cout << "Cargando imagenes a testear..." << endl;
	// vector<entrada> testeo = procesarEntrada("test.csv", true);
	// ejecutar(atoi(metodo.c_str()), entrenamiento, testeo,lamda,vecinos, myfile);
	//Esto es para competir

	//Esto es para hacer el K folds
	int cantidadDePruebas, lamda, vecinos;
	int **kfold = kfolds(archivoDeEntrada, cantidadDePruebas, lamda, vecinos);
	cout << "Iniciando Kfolds...." << endl;
	cout << "Cantidad De Pruebas: " << cantidadDePruebas << endl;
	cout << "Vecinos para el KNN: " << vecinos << endl;
	if (atoi(metodo.c_str()) == 1) {
		cout << "Lamda Para PCA: " << lamda << endl;
	}

	fstream myfile(archivoDeSalida.c_str(), ios::out | ios::trunc);

	for (int i = 0; i < cantidadDePruebas; i++) {
		cout << "Cargando Base de datos..." << endl;
		vector<entrada> entradas = procesarEntrada("train.csv", false);
		vector<entrada> testeo;
		vector<entrada> entrenamiento;

		cout << "Corriendo test: " << i + 1 << endl;
		arreglarEntrada(entradas, entrenamiento, testeo, kfold[i]);
		ejecutar(atoi(metodo.c_str()), entrenamiento, testeo, lamda, vecinos, myfile);

		//Elimino todos los vectores creados
		entradas.erase(entradas.begin(), entradas.end());
		for (int i = 0; i < entrenamiento.size(); i++) {
			delete entrenamiento[i].vect;
		}
		entrenamiento.erase(entrenamiento.begin(), entrenamiento.end());
		for (int i = 0; i < testeo.size(); i++) {
			delete testeo[i].vect;
		}
		testeo.erase(testeo.begin(), testeo.end());
	}
	myfile.close();
	//Esto es para hacer el K folds
	cerr << endl;
	cout << "Fin!" << endl;
	return 0;
}

void ejecutar(int metodo, vector<entrada> &entradas, vector<entrada> &test, int lamda, int vecinos, fstream& myfile) {
	//knn

	/*tiempos*/
	timeval startGauss, endGauss;
	if (metodo == 0) {
		cout << "Ejecutando metodo KNN..." << endl;
		gettimeofday(&startGauss, NULL);
		calcularknn(entradas, test, vecinos);
	}
	//pca + knn
	if (metodo == 1) {
		cout << "Ejecutando metodo PCA..." << endl;
		calcularPca(entradas, test, myfile, lamda);
		cout << "Ejecutando KNN sobre el PCA..." << endl;
		gettimeofday(&startGauss, NULL);
		calcularknn(entradas, test, vecinos);
	}
	long elapsed_seconds; /* diff between seconds counter */
	long elapsed_useconds; /* diff between microseconds counter */
	/*tiempos*/
	gettimeofday(&endGauss, NULL);
	elapsed_seconds = endGauss.tv_sec - startGauss.tv_sec;
	double timeGauss =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
	cerr << timeGauss << " ";
}


int **kfolds(string archivo, int &cantidadDePruebas, int &lamda, int &vecinos) {
	int **kfold;
	string hola;
	fstream myfile(archivo.c_str(), ios_base::in);
	//fix
	myfile >> hola;
	myfile >> vecinos;
	myfile >> lamda;
	myfile >> cantidadDePruebas;

	kfold = new int*[cantidadDePruebas];
	for (int i = 0; i < cantidadDePruebas; i++) {
		kfold[i] = new int[42000];
		for (int j = 0; j < 42000; j++) {
			myfile >> kfold[i][j];
		}
	}
	myfile.close();
	return kfold;
}

void arreglarEntrada(vector<entrada> entradaOriginal, vector<entrada> &entradaNueva, vector<entrada> &testeo, int *kfold) {
	int cantidadDeTests = 0;
	for (int i = 0; i < 42000; i++) {
		if (kfold[i] == 1) {
			entradaNueva.push_back(entradaOriginal[i]);
		} else {
			cantidadDeTests++;
			testeo.push_back(entradaOriginal[i]);
		}
	}
	cout << "Cantidad De imagenes a reconocer: " << cantidadDeTests << endl;
}

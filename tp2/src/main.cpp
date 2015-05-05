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
using namespace std;

void ejecutar(int metodo,vector<entrada> entradas,vector<entrada> test, int lamda, int vecinos);
int **kfolds(string archivo, int &cantidadDePruebas,int &lamda, int &vecinos);
void arreglarEntrada(vector<entrada> entradaOriginal,vector<entrada> &entradaNueva, vector<entrada> &testeo,int *kfold);

int main(int argc, char *argv[]) {

	if(argc != 4){
		cout << "Error en la cantidad de argumentos!!" << endl;
		return -1;		
	}

	string archivoDeEntrada (argv[1]);
	string archivoDeSalida (argv[2]);
	string metodo (argv[3]);



	//Esto es para competir
	// cout << "Cargando Base de datos..." << endl;
	// vector<entrada> entradas = procesarEntrada("minitrain.csv", false);
	// cout << "Cargando imagenes a testear..." << endl;
	//vector<entrada> test = procesarEntrada("test.csv", true);
	//ejecutar(atoi(metodo.c_str()), entradas, test);
	//Esto es para competir

	//Esto es para hacer el K folds
	int cantidadDePruebas,lamda,vecinos;
	cout << "Cargando Base de datos..." << endl;
	vector<entrada> entradas = procesarEntrada("train.csv", false);
	vector<entrada> testeo,entrenamiento ;
	int **kfold = kfolds(archivoDeEntrada, cantidadDePruebas,lamda,vecinos);
	cout << "Iniciando Kfolds...." << endl;
	cout << "Cantidad De Pruebas: " << cantidadDePruebas << endl;
	cout << "Lamda: " << lamda << endl;
	cout << "Vecinos para el KNN: " << vecinos << endl;
	for(int i = 0; i < cantidadDePruebas; i++){
		cout << "Corriendo test: " << i+1 << endl;
		arreglarEntrada(entradas, entrenamiento,testeo,kfold[i]);
		ejecutar(atoi(metodo.c_str()), entrenamiento, testeo,lamda,vecinos);
		entrenamiento.erase(entrenamiento.begin(),entrenamiento.end());
		testeo.erase(testeo.begin(),testeo.end());

	}
	//Esto es para hacer el K folds

	cout << "Fin!" << endl;
	return 0;
}

void ejecutar(int metodo,vector<entrada> entradas,vector<entrada> test, int lamda, int vecinos)
{
	string salida;
	//knn
	if(metodo == 0)
	{
		cout << "Ejecutando metodo knn..." << endl;
		calcularknn(entradas,test, salida, vecinos);
	}
	//pca + knn
	if(metodo == 1)
	{
		cout << "Ejecutando metodo PCA..." << endl;
	   	calcularPca(entradas,test, salida, lamda);
		calcularknn(entradas, test, salida, vecinos);
	}
}


int **kfolds(string archivo, int &cantidadDePruebas,int &lamda, int &vecinos)
{
	int **kfold;
	fstream myfile(archivo.c_str(),ios_base::in);
	myfile >> vecinos;
	myfile >> lamda;
	myfile >> cantidadDePruebas;

	kfold = new int*[cantidadDePruebas]; 
	for(int i = 0; i < cantidadDePruebas; i++)
	{
		kfold[i] = new int[42000];
		for(int j = 0; j < 42000; j++)
		{
			myfile >> kfold[i][j]; 
		}
	}
	return kfold;
}

void arreglarEntrada(vector<entrada> entradaOriginal,vector<entrada> &entradaNueva, vector<entrada> &testeo,int *kfold){
	int cantidadDeTests = 0;
	for(int i = 0; i < 42000; i++){
		if(kfold[i] == 0)
			entradaNueva.push_back(entradaOriginal[i]);
		else
		{
			cantidadDeTests++;
			testeo.push_back(entradaOriginal[i]);
		}
	}
	cout << "Cantidad De imagenes a reconocer: " << cantidadDeTests << endl;
}
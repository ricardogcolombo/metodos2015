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

void ejecutar(int metodo,vector<entrada> entradas,vector<entrada> test, int lamda, int vecinos, fstream& myfile);
int **kfolds(string archivo, int &cantidadDePruebas,int &lamda, int &vecinos);
void arreglarEntrada(vector<entrada> entradaOriginal,vector<entrada> &entradaNueva, vector<entrada> &testeo,int *kfold);

int main(int argc, char *argv[]) {

	if(argc < 3){
		cout << "Error en la cantidad de argumentos!!" << endl;
		return -1;		
	}

	string archivoDeEntrada (argv[1]);
	string archivoDeSalida (argv[2]);
	string metodo;
	if(argc == 3)
		metodo = "1";
	else
		metodo = argv[3];

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
	int cantidadDePruebas,lamda,vecinos;
	int **kfold = kfolds(archivoDeEntrada, cantidadDePruebas,lamda,vecinos);
	cout << "Iniciando Kfolds...." << endl;
	cout << "Cantidad De Pruebas: " << cantidadDePruebas << endl;
	cout << "Lamda: " << lamda << endl;
	cout << "Vecinos para el KNN: " << vecinos << endl;

	fstream myfile(archivoDeSalida.c_str(),ios::out | ios::trunc);

	for(int i = 0; i < cantidadDePruebas; i++){
		cout << "Cargando Base de datos..." << endl;
		vector<entrada> entradas = procesarEntrada("train.csv", false);
		vector<entrada> testeo;
		vector<entrada> entrenamiento;

		cout << "Corriendo test: " << i+1 << endl;
		arreglarEntrada(entradas, entrenamiento,testeo,kfold[i]);
		ejecutar(atoi(metodo.c_str()), entrenamiento, testeo,lamda,vecinos, myfile);

		//Elimino todos los vectores creados
		//for(int i = 0; i < entradas.size(); i++)
			//delete entradas[i].vect;
		entradas.erase(entradas.begin(), entradas.end());
		entrenamiento.erase(entrenamiento.begin(),entrenamiento.end());
		testeo.erase(testeo.begin(),testeo.end());
	}
	myfile.close();
	//Esto es para hacer el K folds

	cout << "Fin!" << endl;
	return 0;
}

void ejecutar(int metodo,vector<entrada> entradas,vector<entrada> test, int lamda, int vecinos, fstream& myfile)
{
	//knn
	if(metodo == 0)
	{
		cout << "Ejecutando metodo KNN..." << endl;
		calcularknn(entradas,test, vecinos);
	}
	//pca + knn
	if(metodo == 1)
	{
		cout << "Ejecutando metodo PCA..." << endl;
	   	calcularPca(entradas,test, myfile, lamda);
		cout << "Ejecutando KNN sobre el PCA..." << endl;
		calcularknn(entradas, test, vecinos);
	}
}


int **kfolds(string archivo, int &cantidadDePruebas,int &lamda, int &vecinos)
{
	int **kfold;
	string hola;
	fstream myfile(archivo.c_str(),ios_base::in);
	//fix
	myfile >> hola;
	myfile >> vecinos;
	myfile >> lamda;
	myfile >> cantidadDePruebas;

	cout << "la puta madre:" << hola << endl;

	kfold = new int*[cantidadDePruebas]; 
	for(int i = 0; i < cantidadDePruebas; i++)
	{
		kfold[i] = new int[42000];
		for(int j = 0; j < 42000; j++)
		{
			myfile >> kfold[i][j]; 
		}
	}
	myfile.close();
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
